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
#if !defined(__CFTAL_TEST_CHECK_LOG2P1_H__)
#define __CFTAL_TEST_CHECK_LOG2P1_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/impl_d_real_constants_f64.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        using domain_log2p1 = domain_logx1p<_T>;

        template <typename _T>
        struct check_log2p1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log2p1(a);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log2p1, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return _s(a);
            }

            template <typename _M>
            static
            _M
            _s(const _M& a) {
                return ::log2p1(a);
            }

            static
            float
            _s(const float& a) {
                return ::log2p1f(a);
            }

            static
            double
            _s(const double& a) {
                return ::log2p1(a);
            }

            static
            bf16_t
            _s(const bf16_t& a) {
                return static_cast<bf16_t>(_s(static_cast<float>(a)));
            }

            static
            f16_t
            _s(const f16_t& a) {
                return static_cast<f16_t>(_s(static_cast<float>(a)));
            }

            static
            const char* fname() { return "log2p1"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
