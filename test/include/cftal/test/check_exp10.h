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
#if !defined(__CFTAL_TEST_CHECK_EXP10_H__)
#define __CFTAL_TEST_CHECK_EXP10_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_exp10 {};

        template <>
        struct domain_exp10<double> {
            constexpr static
            const double exp10_lo_den_nom= -3.076526555685887842628290e+02;
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-330.0, 310.0),
                // check the denormal result range
                std::make_pair(-330.0, exp10_lo_den_nom)
            };
            constexpr static
            const int shifts[]= {
                0,
                -3
            };
        };

        template <>
        struct domain_exp10<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-46.0f, 39.0f)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <>
        struct domain_exp10<f16_t> {
            static
            const func_domain<f16_t> domains[1];
            constexpr static
            const int shifts[]={
                0
            };
        };


        template <typename _T>
        struct check_exp10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp10(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp10, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_exp10);
            }
            static
            _T
            s(const _T& a) {
                return __exp10(a);
            }

            static
            double
            __exp10(const double& a) {
                return ::exp10(a);
            }

            static
            float
            __exp10(const float& a) {
                return ::exp10f(a);
            }

            static
            f16_t
            __exp10(const f16_t& a) {
                return static_cast<f16_t>(::exp10f(static_cast<float>(a)));
            }

            static
            const char* fname() { return "exp10"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
