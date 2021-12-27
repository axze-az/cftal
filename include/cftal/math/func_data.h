// 
// Copyright (C) 2010-2021 Axel Zeuner
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
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
                // 2^(i/n) = H + L = H*(1+F)
                const _F _2_pow_i_n_f[EXP_N];
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
        struct pow_log_data {
            enum {
                LOG_N=64,
                LOG_SHIFT=6
            };
            struct table_t {
                // 1/c for logarithm calculations in pow function
                const _T _p_inv_c[LOG_N];
                // log(c) for pow function high part
                const _T _p_log_c_h[LOG_N];
                // log(c) for pow function low part
                const _T _p_log_c_l[LOG_N];
            };
            static
            const table_t _tbl;
        };

        // the float tables
        template<>
        const pow_log_data<float>::table_t pow_log_data<float>::_tbl;

        // the double tables
        template<>
        const pow_log_data<double>::table_t pow_log_data<double>::_tbl;

        extern template struct pow_log_data<float>;

        extern template struct pow_log_data<double>;

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


        template <typename _F>
        struct lngamma_data {};

        template <>
        struct lngamma_data<double> {
            constexpr static const double SCALE=32.0;
            constexpr static const double INV_SCALE=1.0/32.0;
            enum {
                COUNT=33,
                POLY_ORDER=10,
                DD_COEFFS=4,
                // c0, c1, c2, c3 are stored as cXh, cXl
                // i.e we have (POLY_ORDER+1+DD_COEFFS) entries per
                // interval, c0h, c0l are stored last
                ELEMS_PER_INTERVAL=(POLY_ORDER+1)+DD_COEFFS,
                ENTRIES = COUNT * ELEMS_PER_INTERVAL
            };
            static const double _12_tbl[ENTRIES];
        };

        template <>
        struct lngamma_data<float> {
            constexpr static const double SCALE=32.0f;
            constexpr static const double INV_SCALE=1.0/32.0f;
            enum {
                COUNT=33,
                POLY_ORDER=5,
                DD_COEFFS=3,
                // c0, c1 ...are stored as cXh, cXl
                // i.e we have (POLY_ORDER+1+DD_COEFFS) entries per
                // interval, c0h, c0l are stored last
                ELEMS_PER_INTERVAL=(POLY_ORDER+1)+DD_COEFFS,
                ENTRIES = COUNT * ELEMS_PER_INTERVAL
            };
            static const float _12_tbl[ENTRIES];
        };

        extern template struct lngamma_data<double>;
        extern template struct lngamma_data<float>;

    }
}

// Local Variables:
// mode: c++
// end:
#endif
