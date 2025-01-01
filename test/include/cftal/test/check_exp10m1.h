//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined(__CFTAL_TEST_CHECK_EXP10M1_H__)
#define __CFTAL_TEST_CHECK_EXP10M1_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_exp10m1 {};

        template <>
        struct domain_exp10m1<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-17.0, 310.0),
                // check the denormal result range
                std::make_pair(-0x1p-4, 0x1p-4)
            };
            constexpr static
            const int shifts[]= {
                0,
                -2
            };
        };

        template <>
        struct domain_exp10m1<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-8.0f, 39.0f),
                std::make_pair(-0x1p-4f, 0x1p-4f)
            };
            constexpr static
            const int shifts[]={
                0,
                -2
            };
        };

        template <>
        struct domain_exp10m1<f16_t> {
            constexpr static
            const func_domain<f16_t> domains[]={
                std::make_pair(-3.7_f16, 4.9_f16),
                std::make_pair(-0x1p-3_f16, 0x1p-3_f16)
            };
            constexpr static
            const int shifts[]={
                0,
                -2
            };
        };

        template <>
        struct domain_exp10m1<bf16_t> {
            constexpr static
            const func_domain<bf16_t> domains[]={
                std::make_pair(-8.0_bf16, 39.0_bf16),
                std::make_pair(-0x1p-4_bf16, 0x1p-4_bf16)
            };
            constexpr static
            const int shifts[]={
                0,
                -2
            };
        };

	
        template <typename _T>
        struct check_exp10m1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp10m1(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
#if MPFR_VERSION >= MPFR_VERSION_NUM(4, 2, 0)
                _T v=call_mpfr::func(a, mpfr_exp10m1, &i);
#else
                _T v=call_mpfr::func(a, mpfr_ext::exp10m1, &i);
#endif
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                const _T log10=_T(+2.3025850929940459010936e+00);
                using std::expm1;
                return expm1(a*log10);
            }
            static
            const char* fname() { return "exp10m1"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
