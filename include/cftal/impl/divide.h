#if !defined (__CFTAL_IMPL_DIVIDE_H__)
#define __CFTAL_IMPL_DIVIDE_H__ 1

#include <cftal/config.h>
#include <cftal/select.h>
#include <type_traits>
#include <utility>

namespace cftal {

    namespace impl {

        template <class _T>
        std::enable_if_t<std::is_integral<_T>::value, _T>
        divide(const _T& a, const _T& b);

        template <class _T>
        std::enable_if_t<std::is_integral<_T>::value==false, _T>
        divide(const _T& a, const _T& b);

        // _T unsigned integer type or vector of unsigned integer
        // _M bool, something convertible to bool or a vector mask type
        // _N element size
        template <class _T, class _M = bool, std::size_t _N=sizeof(_T)>
        std::pair<_T, _T>
        udiv_double_shift(const _T& a, const _T& b);

    }
}

template <class _T>
std::enable_if_t<std::is_integral<_T>::value, _T>
cftal::impl::divide(const _T& a, const _T& b)
{
    if (b == _T(0))
        return ~_T(0);
    return a/b;
}

template <class _T>
std::enable_if_t<std::is_integral<_T>::value==false, _T>
cftal::impl::divide(const _T& a, const _T& b)
{
    return a/b;
}

template <class _T, class _M, std::size_t _N>
std::pair<_T, _T>
cftal::impl::udiv_double_shift(const _T& a, const _T& b)
{
    _T r(0);
    _T q(a);
    int i;
    for (int i=0; i<_N; ++i) {
        // double word left shift (r,q)
        _T hibit_q = q >> (_N-1);
        r += r + hibit_q;
        q += q;
        // if (r >= b) {
        //    r -= b;
        //    ++q;
        // }
        _M r_ge_b = r >= b;
        _T r_sub = r - b;
        _T q_inc = q + _T(1);
        r = select(r_ge_b, r_sub, r);
        q = select(r_ge_b, q_inc, q);
    }
    return std::make_pair(q, r);
}


// local variables:
// mode: c++
// end:
#endif
