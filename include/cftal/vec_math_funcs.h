//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_MATH_FUNCS_H__)
#define __CFTAL_VEC_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_spec.h>

namespace cftal {

    namespace impl {

        // round to odd implementation, _F floating point type
        // _I integer type with the same size,
        // _FM mask type of _F, _IM mask type of _I
        template <typename _F, typename _FM, typename _I, typename _IM>
        _F
        round_to_odd(const _F& xh, const _F& xl);

        template <typename _T, std::size_t _N>
        struct is_vec_math_func {
            static
            constexpr bool
            fast() { return false; }
        };

        template <std::size_t _N>
        struct is_vec_math_func<double, _N> {
            static
            constexpr bool
            fast() {
#if 0
                bool r=(is_vec_specialized<vec<double, _N> >::value);
                return r;
#else
                bool r=(is_vec_specialized<vec<double, _N> >::value ||
                       (is_vec_specialized<vec<double, _N/2> >::value /* &&
                        is_vec_specialized<vec<int32_t, _N> >::value*/));
#if defined (__tune_btver2__) || defined (__tune_bdver3__)
                r &= _N > 2 ? false : true;
#endif
                return r;
#endif
            }
        };

        template <std::size_t _N>
        struct is_vec_math_func<float, _N> {
            static
            constexpr bool
            fast() {
                bool r=(is_vec_specialized<vec<float, _N> >::value ||
                       (is_vec_specialized<vec<float, _N/2> >::value /*&&
                        is_vec_specialized<vec<int32_t, _N/2> >::value */));
#if defined (__SSE__)
                // r &= _N != 2;
#endif
#if defined (__tune_btver2__) || defined (__tune_bdver3__)
                r &= _N > 4 ? false : true;
#endif
                return r;
            }
        };

    }
}

template <typename _F, typename _FM, typename _I, typename _IM>
_F
cftal::impl::round_to_odd(const _F& xh, const _F& xl)
{
    _I ih=as<_I>(xh);
    // select rounding direction in dependence of the sign of xh, xl
    _I ihp= ih + 1;
    _I ihm= ih - 1;
    _FM msk= (xl > _F(0.0)) ^ (xh < _F(0.0));
    _IM imsk=as<_IM>(msk);
    _I ir0 = select(msk, ihp, ihm);
    // check if xh is already odd
    _IM i_xh_odd= (ih & 1) != _I(0);
    _FM xh_odd= as<_FM>(i_xh_odd);
    _F r0= as<_I>(ir0);
    // check if xl zero
    _FM xl_zero_or_xh_odd= (xl == 0.0) | (xh_odd);
    _F r= select(xl_zero_or_xh_odd, xh, r0);
    return r;
}

// Local variables:
// mode: c++
// end:
#endif
