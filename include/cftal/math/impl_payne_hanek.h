//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_IMPL_PAYNE_HANEK_H__)
#define __CFTAL_MATH_IMPL_PAYNE_HANEK_H__ 1

#include <cftal/config.h>

namespace cftal { namespace math { namespace impl {
}}}

namespace cftal::math::impl {

    template <typename _T>
    struct payne_hanek_pi_over_2_base {};


    template <>
    struct payne_hanek_pi_over_2_base<double> {
        // bits of 1/(2*M_PI) in 24 bit chunks as double, i.e.
        // offset 0: bit [0, 24)*2^(1*24)
        // offset 1: bit [24, 48)*2^(2*24)
        // offset 2: bit [48, 62)*2^(3*24)
        static
        const double
        one_over_two_pi_b24_dbl[];
    };

}

#endif
