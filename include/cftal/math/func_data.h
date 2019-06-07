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
        struct exp_data {
            enum {
                EXP_N=32,
                EXP_SHIFT=5,
                EXP_IDX_MASK=EXP_N-1
            };
            struct table_t {
                // 2^(i/n) high part
                const _F _2_pow_i_n_h[EXP_N];
                // 2^(i/n) low part
                const _F _2_pow_i_n_l[EXP_N];
            };
            static
            const table_t _tbl;
        };

        // the float tables
        template<>
        const exp_data<float>::table_t exp_data<float>::_tbl;

        // the double tables
        template<>
        const exp_data<double>::table_t exp_data<double>::_tbl;

        extern template struct exp_data<float>;

        extern template struct exp_data<double>;

        // tables for logarithms
        template <typename _T>
        struct log_data {
            enum {
                LOG_N=64,
                LOG_SHIFT=6
            };
            struct table_t {
                const _T _inv_c[LOG_N];
                const _T _log_c_h[LOG_N];
                const _T _log_c_l[LOG_N];
                const _T _log2_c_h[LOG_N];
                const _T _log2_c_l[LOG_N];
                const _T _log10_c_h[LOG_N];
                const _T _log10_c_l[LOG_N];
            };
            static
            const table_t _tbl;
        };

        // the float tables
        template<>
        const log_data<float>::table_t log_data<float>::_tbl;

        // the double tables
        template<>
        const log_data<double>::table_t log_data<double>::_tbl;

        extern template struct log_data<float>;

        extern template struct log_data<double>;

        // tables for complementary error function
        template <typename _T>
        struct erfc_data {};

        template <>
        struct erfc_data<double> {
            constexpr static const double SCALE=8.0;
            constexpr static const double INV_SCALE=1.0/8.0;
            enum {
                COUNT=219,
                POLY_ORDER=10,
                // c0 is stored as c0h + c0l
                ENTRIES=COUNT*(POLY_ORDER+2)
            };
            static const double _tbl[ENTRIES];
        };

        template <>
        struct erfc_data<float> {
            constexpr static const float SCALE=8.0f;
            constexpr static const float INV_SCALE=1.0f/8.0f;
            enum {
                COUNT=81,
                POLY_ORDER=5,
                // c0 is stored as c0h + c0l
                ENTRIES=COUNT*(POLY_ORDER+2)
            };
            static const float _tbl[ENTRIES];
        };

        extern template struct erfc_data<float>;

        extern template struct erfc_data<double>;

    }
}

// Local Variables:
// mode: c++
// end:
#endif
