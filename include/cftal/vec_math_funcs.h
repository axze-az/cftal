//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_MATH_FUNCS_H__)
#define __CFTAL_VEC_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>

namespace cftal {
    namespace impl {

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
                bool r=(is_vec_specialized<double, _N>::value ||
                       (is_vec_specialized<double, _N/2>::value &&
                       is_vec_specialized<int32_t, _N>::value));
#if defined (__tune_btver2__) || defined (__tune_bdver3__)
                r &= _N > 2 ? false : true;
#endif
                return r;
            }
        };

        template <std::size_t _N>
        struct is_vec_math_func<float, _N> {
            static
            constexpr bool
            fast() {
                bool r=(is_vec_specialized<float, _N>::value ||
                       (is_vec_specialized<float, _N/2>::value &&
                        is_vec_specialized<int32_t, _N/2>::value));
#if defined (__SSE__)
                r &= _N != 2;
#endif
#if defined (__tune_btver2__) || defined (__tune_bdver3__)
                r &= _N > 4 ? false : true;
#endif
                return r;
            }
        };

    }
}

// Local variables:
// mode: c++
// end:
#endif
