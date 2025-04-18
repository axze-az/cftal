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
#if !defined(__CFTAL_TEST_CHECK_SIG_H__)
#define __CFTAL_TEST_CHECK_SIG_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/func_constants.h>
#include <cftal/math/func_constants_f16.h>
#include <cftal/math/func_constants_f32.h>
#include <cftal/math/func_constants_f64.h>
#include <cftal/math/func_constants_bf16.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {


        template <typename _T>
        struct check_sig {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sig(a);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::sig, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            _T
            s(const _T& a) {
                using fc=cftal::math::func_constants<_T>;
                if (a >= fc::sig_hi_one()) {
                    return _T(1.0);
                } else if (a <= -fc::exp_hi_inf()) {
                    return _T(0.0);
                } else if (a < fc::sig_le_eq_exp()) {
                    using std::exp;
                    return exp(a);
                }
                using std::expm1;
                return _T(1.0)/(_T(2.0)+expm1(-a));
            }

            static
            const char* fname() { return "sig"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
