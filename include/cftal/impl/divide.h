#if !defined (__CFTAL_IMPL_DIVIDE_H__)
#define __CFTAL_IMPL_DIVIDE_H__ 1

#include <cftal/config.h>
#include <type_traits>

namespace cftal {

    namespace impl {

        template <class _T>
        std::enable_if_t<std::is_integral<_T>::value, _T>
        divide(const _T& a, const _T& b);

        template <class _T>
        std::enable_if_t<std::is_integral<_T>::value==false, _T>
        divide(const _T& a, const _T& b);

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


// local variables:
// mode: c++
// end:
#endif
