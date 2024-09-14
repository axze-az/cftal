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
#if !defined(__CFTAL_TEST_CHECK_EXP_PX2_H__)
#define __CFTAL_TEST_CHECK_EXP_PX2_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/vec_f16.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_exp_px2 {};

        template <>
        struct domain_exp_px2<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(0.0, 26.7)
            };
            constexpr static
            const int shifts[]= {
                0
            };
        };

        template <>
        struct domain_exp_px2<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(0.0f, 9.5f)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <>
        struct domain_exp_px2<f16_t> {
            constexpr static
            const func_domain<f16_t> domains[]={
                std::make_pair(0.0_f16, 3.5_f16)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <>
        struct domain_exp_px2<bf16_t> {
            constexpr static
            const func_domain<bf16_t> domains[]={
                std::make_pair(0.0_bf16, 9.5_bf16)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <typename _T>
        struct check_exp_px2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp_px2(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::exp_px2, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                using std::exp;
                return exp(a*a);
            }
            static
            const char* fname() { return "exp_px2"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
