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
#if !defined(__CFTAL_TEST_CHECK_LOG2P1_H__)
#define __CFTAL_TEST_CHECK_LOG10P1_H__ 1

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
        using domain_log10p1 = domain_logx1p<_T>;

        template <typename _T>
        struct check_log10p1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log10p1(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log10p1, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_log);
            }
            static
            _T
            s(const _T& a) {
                using _TT = select_t<std::is_same_v<_T, f16_t>, float, _T>;
                using ctbl=math::impl::d_real_constants<d_real<_TT>, _TT>;
                using std::log1p;
                return log1p(a)*ctbl::m_1_ln10[0];
            }

            static
            const char* fname() { return "log10p1"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
