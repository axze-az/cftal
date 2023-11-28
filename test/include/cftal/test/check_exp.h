//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined(__CFTAL_TEST_CHECK_EXP_H__)
#define __CFTAL_TEST_CHECK_EXP_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>
#include <tuple>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_exp {};

        template <>
        struct domain_exp<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-750.0, 710.0),
                // check the denormal result range
                std::make_pair(-750.0, -7.083964185322641924358322e+02)
            };
            constexpr static
            const int shifts[]= {
                0,
                -3
            };
        };

        template <>
        struct domain_exp<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-104.0f, 89.0f)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <>
        struct domain_exp<f16_t> {
            // TODO: fix the missing constexpr for f16_t literals
            static
            const func_domain<f16_t> domains[];
            constexpr static
            const int shifts[]={
                0
            };
        };

        const func_domain<f16_t>
        domain_exp<f16_t>::domains[]= {
            std::make_pair(-18.0_f16, 12.0_f16)
        };

        template <typename _T>
        struct check_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_exp);
            }
            static
            _T
            s(const _T& a) {
                using std::exp;
                return exp(a);
            }
            static
            const char* fname() { return "exp"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
