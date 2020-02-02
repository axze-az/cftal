//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_IMPL_DIVIDE_H__)
#define __CFTAL_IMPL_DIVIDE_H__ 1

#include <cftal/config.h>
#include <cftal/select.h>
#include <cftal/cast.h>
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
        template <class _U, class _M = bool, std::size_t _N=sizeof(_U)>
        std::pair<_U, _U>
        udiv_double_shift(const _U& a, const _U& b);

        template <class _S, std::size_t _N=sizeof(_S)>
        _S sabs(const _S& v);

        template <class _S, class _U, class _M = bool,
                  std::size_t _N=sizeof(_S)>
        std::pair<_S, _S>
        sdiv_double_shift(const _S& a, const _S& b);
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

template <class _U, class _M, std::size_t _N>
std::pair<_U, _U>
cftal::impl::udiv_double_shift(const _U& a, const _U& b)
{
    _U r(0);
    _U q(a);

    for (std::size_t i=0; i<_N; ++i) {
        // double word left shift (r,q)
        _U hibit_q = q >> (_N-1);
        r += r + hibit_q;
        q += q;
        // if (r >= b) {
        //    r -= b;
        //    ++q;
        // }
        _M r_ge_b = r >= b;
        _U r_sub = r - b;
        _U q_inc = q + _U(1);
        r = select(r_ge_b, r_sub, r);
        q = select(r_ge_b, q_inc, q);
    }
    return std::make_pair(q, r);
}

template <class _S, std::size_t _N>
inline
_S
cftal::impl::sabs(const _S& a)
{
    _S t = a >> (_N-1);
    return  (a^t) -t;
}

template <class _S, class _U, class _M, std::size_t _N>
std::pair< _S, _S >
cftal::impl::sdiv_double_shift(const _S& a, const _S& b)
{
    _S abs_a= sabs<_S, _N>(a);
    _S abs_b= sabs<_S, _N>(b);
    _U ua= as<_U>(abs_a);
    _U ub= as<_U>(abs_b);
    std::pair<_U, _U> qr=udiv_double_shift<_U, _M, _N>(ua, ub);
    _S sgn= (a^b) >> (_N-1);
    _S q0=as<_S>(qr.first);
    _S q= (q0^sgn) -sgn;
    // a/0 == ~_S(0)
    q = select(b == _S(0), ~_S(0), q);
    _S r= a - q*b;
    return std::make_pair(q, r);
}




// local variables:
// mode: c++
// end:
#endif
