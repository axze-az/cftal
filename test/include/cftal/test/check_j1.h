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
#if !defined(__CFTAL_TEST_CHECK_J1_H__)
#define __CFTAL_TEST_CHECK_J1_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/func_data.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_j1 {
            constexpr
            static const func_domain<_T> domains[]={
                std::make_pair(-std::numeric_limits<_T>::max(),
                               std::numeric_limits<_T>::max()),
                std::make_pair(math::j01y01_data<_T>::_max_small_j1,
                               _T(2)*math::j01y01_data<_T>::_max_small_j1),
                std::make_pair(-math::j01y01_data<_T>::_max_small_j1,
                                math::j01y01_data<_T>::_max_small_j1)
            };

            constexpr
            static const int shifts[]={
                0,
                -2,
                -2
            };
        };

        template <typename _T>
        struct check_j1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return j1(a);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_j1, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            float
            _s(const float& a) {
                return ::j1f(a);
            }

            static
            double
            _s(const double& a) {
                return ::j1(a);
            }

            static
            _T
            s(const _T& a) {
                return _s(a);
            }

            static
            const char* fname() { return "j1"; }
        };
    }
}

// local variables:
// mode: c++
// end:
#endif
