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
#if !defined(__CFTAL_TEST_CHECK_ASIN_H__)
#define __CFTAL_TEST_CHECK_ASIN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_asin {};

        template <>
        struct domain_asin<double> {
            constexpr static
            const func_domain<double> domains[]={
                std::make_pair(-1.000000001, 1.000000001)

            };
            constexpr static
            const int shifts[]= {
                0,
            };
        };

        template <>
        struct domain_asin<float> {
            constexpr static
            const func_domain<float> domains[]={
                std::make_pair(-1.000001f, +1.000001f)
            };
            constexpr static
            const int shifts[]={
                0
            };
        };

        template <typename _T>
        struct check_asin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return asin(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_asin, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_cosh);
            }
            static
            _T
            s(const _T& a) {
                return std::asin(a);
            }
            static
            const char* fname() { return "asin"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
