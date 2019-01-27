//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_FUNC_DATA_H__)
#define __CFTAL_MATH_FUNC_DATA_H__ 1

#include <cftal/config.h>

namespace cftal {
    namespace math {

        // tables for exponential function
        template <typename _F>
        struct exp_data {};

        template <>
        struct exp_data<float> {
            enum {
                EXP_N=32
            };
            struct table_t {
                const float _exp_fxi_h_tbl[EXP_N];
                const float _exp_fxi_l_tbl[EXP_N];
            };
            static
            const table_t _tbl;
        };

        template <>
        struct exp_data<double> {
            enum {
                EXP_N=32
            };
            struct table_t {
                const double _exp_fxi_h_tbl[EXP_N];
                const double _exp_fxi_l_tbl[EXP_N];
            };
            static
            const table_t _tbl;
        };

        extern template
        struct exp_data<float>;

        extern template
        struct exp_data<double>;

    }
}

// Local Variables:
// mode: c++
// end:
#endif
