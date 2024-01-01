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
#if !defined(__CFTAL_TEST_CHECK_EXP2M1_H__)
#define __CFTAL_TEST_CHECK_EXP2M1_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_exp2m1 {};

        template <>
        struct domain_exp2m1<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-57.0, 1026.0),
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
        struct domain_exp2m1<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-25.0f, 129.0f),
                std::make_pair(-0x1p-4f, 0x1p-4f)
            };
            constexpr static
            const int shifts[]={
                0,
                -2
            };
        };

        template <>
        struct domain_exp2m1<f16_t> {
            constexpr static
            const func_domain<f16_t> domains[]={
                std::make_pair(-26.5_f16, 16.5_f16),
                std::make_pair(-0x1p-3_f16, 0x1p-3_f16)
            };
            constexpr static
            const int shifts[]={
                0,
                -2
            };
        };


        template <typename _T>
        struct check_exp2m1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp2m1(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp2m1, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
#if 0
		return std::exp2(a)-1;
#else
                const _T ln2=M_LN2;
                using std::expm1;
                return expm1(a*ln2);
#endif
            }
            static
            const char* fname() { return "exp2m1"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
