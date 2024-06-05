//
// Copyright (C) 2010-2024 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_MATH_FUNC_DATA_H__)
#define __CFTAL_MATH_FUNC_DATA_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/f16_t.h>

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
                // 2^(i/n) = h + l = h*(1+f)
                // 2^(i/n) correction factor part f
                alignas(64) const _F _2_pow_i_n_f[EXP_N];
                // 2^(i/n) high part h
                alignas(64) const _F _2_pow_i_n_h[EXP_N];
                // 2^(i/n) low part l
                alignas(64) const _F _2_pow_i_n_l[EXP_N];
            };
            static
            const table_t _tbl;
        };

        // the half tables
        template<>
        const exp_data<f16_t>::table_t exp_data<f16_t>::_tbl;

        // the float tables
        template<>
        const exp_data<float>::table_t exp_data<float>::_tbl;

        // the double tables
        template<>
        const exp_data<double>::table_t exp_data<double>::_tbl;

        extern template struct exp_data<f16_t>;

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
                alignas(64) const _T _p_inv_c[LOG_N];
                // log(c) for pow function high part
                alignas(64) const _T _p_log_c_h[LOG_N];
                // log(c) for pow function low part
                alignas(64) const _T _p_log_c_l[LOG_N];
            };
            static
            const table_t _tbl;
        };

        // the float tables
        template<>
        const pow_log_data<f16_t>::table_t pow_log_data<f16_t>::_tbl;

        // the float tables
        template<>
        const pow_log_data<float>::table_t pow_log_data<float>::_tbl;

        // the double tables
        template<>
        const pow_log_data<double>::table_t pow_log_data<double>::_tbl;

        extern template struct pow_log_data<f16_t>;

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
            alignas(64) static const double _tbl[ENTRIES];
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
            alignas(64) static const float _tbl[ENTRIES];
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
            alignas(64) static const double _12_tbl[ENTRIES];
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
            alignas(64) static const float _12_tbl[ENTRIES];
        };

        extern template struct lngamma_data<double>;
        extern template struct lngamma_data<float>;

        template <typename _T>
        struct j01y01_data {};

        template <>
        struct j01y01_data<double> {
            enum {
                IVAL_XR,
                NEG_X_OFFS_H,
                NEG_X_OFFS_M,
                NEG_X_OFFS_L,
                C16,
                C15,
                C14,
                C13,
                C12,
                C11,
                C10,
                C9,
                C8,
                C7,
                C6,
                C5,
                C4,
                C3,
                C2,
                C1H,
                C1L,
                C0H,
                C0L,
                ELEMS,
                INTERVALS=80,
                POLY_ORD=16,
                ENTRIES=INTERVALS*ELEMS
            };
            constexpr
            static const double _max_small_j0=+1.2566272380587477641711e+02;
            alignas(64) static const double _j0_coeffs[ENTRIES];

            constexpr
            static const double _max_small_j1=+1.2565871964045223307949e+02;
            alignas(64) static const double _j1_coeffs[ENTRIES];

            constexpr
            static const double _max_small_y0=+1.2566269893792735956595e+02;
            alignas(64) static const double _y0_coeffs[ENTRIES];

            constexpr
            static const double _max_small_y1=+1.2565874452021265028634e+02;
            alignas(64) static const double _y1_coeffs[ENTRIES];
        };

        extern template struct j01y01_data<double>;

        template <>
        struct j01y01_data<float> {
            enum {
                IVAL_XR,
                NEG_X_OFFS_H,
                NEG_X_OFFS_M,
                NEG_X_OFFS_L,
                C8,
                C7,
                C6,
                C5,
                C4,
                C3,
                C2,
                C1H,
                C1L,
                C0H,
                C0L,
                ELEMS,
                INTERVALS=40,
                POLY_ORD=8,
                ENTRIES=INTERVALS*ELEMS
            };
            constexpr
            static const float _max_small_j0=+6.2829914093e+01f;
            alignas(64) static const float _j0_coeffs[ENTRIES];

            constexpr
            static const float _max_small_j1=+6.2821853638e+01f;
            alignas(64) static const float _j1_coeffs[ENTRIES];

            constexpr
            static const float _max_small_y0=+6.2829814911e+01f;
            alignas(64) static const float _y0_coeffs[ENTRIES];

            constexpr
            static const float _max_small_y1=+6.2821952820e+01f;
            alignas(64) static const float _y1_coeffs[ENTRIES];
        };

        extern template struct j01y01_data<float>;

    }
}

// Local Variables:
// mode: c++
// end:
#endif
