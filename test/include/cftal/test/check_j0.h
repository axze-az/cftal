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
#if !defined(__CFTAL_TEST_CHECK_J0_H__)
#define __CFTAL_TEST_CHECK_J0_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/func_data.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct domain_j0 {
            constexpr
            static const func_domain<_T> domains[]={
                std::make_pair(-std::numeric_limits<_T>::max(),
                            std::numeric_limits<_T>::max()),
                std::make_pair(math::j01y01_data<_T>::_max_small_j0,
                            _T(2)*math::j01y01_data<_T>::_max_small_j0),
                std::make_pair(-math::j01y01_data<_T>::_max_small_j0,
                                math::j01y01_data<_T>::_max_small_j0)
            };

            constexpr
            static const int shifts[]={
                0,
                -2,
                -2
            };
        };

        template <>
        struct domain_j0<f16_t> {
            constexpr
            static const func_domain<f16_t> domains[]={
                std::make_pair(-std::numeric_limits<f16_t>::max(),
			       std::numeric_limits<f16_t>::max())
            };

            constexpr
            static const int shifts[]={
                0
            };
        };

        template <>
        struct domain_j0<bf16_t> {
            constexpr
            static const func_domain<bf16_t> domains[]={
                std::make_pair(-std::numeric_limits<bf16_t>::max(),
			       std::numeric_limits<bf16_t>::max())
            };

            constexpr
            static const int shifts[]={
                0
            };
        };

        template <typename _T>
        struct check_j0 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return j0(a);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_j0, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            f16_t
            _s(const f16_t& a) {
                return f16_t(::j0f(float(a)));
            }

            static
            bf16_t
            _s(const bf16_t& a) {
                return bf16_t(::j0f(float(a)));
            }

            static
            float
            _s(const float& a) {
                return ::j0f(a);
            }

            static
            double
            _s(const double& a) {
                return ::j0(a);
            }

            static
            _T
            s(const _T& a) {
                return _s(a);
            }


            static
            const char* fname() { return "j0"; }
        };
    }
}

// local variables:
// mode: c++
// end:
#endif
