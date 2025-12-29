//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_BF16_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/math/func_constants.h>
#include <cftal/bf16_t.h>
#include <limits>

namespace cftal {

    namespace math {

        template <>
        struct func_constants<bf16_t> {
            static constexpr bf16_t
            min_normal() { return 0x1p-126_bf16; }

            static constexpr bf16_t
            max_denormal() { return 1.175494210692441075487029e-38_bf16; }

            // exp(x) == +inf for x >=
            static constexpr bf16_t
            exp_hi_inf() { return 8.900000000000000000000000e+01_bf16; }
            // exp(x) == 0 for x <=
            static constexpr bf16_t
            exp_lo_zero() { return -8.750000000000000000000000e+01_bf16; }

            // expm1(x) == +inf for x >= 0
            static constexpr bf16_t
            expm1_hi_inf() { return 8.900000000000000000000000e+01_bf16; }
            // expm1(x) == -1 for x <=
            static constexpr bf16_t
            expm1_lo_minus_one() { return -6.250000000000000000000000e+00_bf16; }

            // exp2(x) == +inf for x >=
            static constexpr bf16_t
            exp2_hi_inf() { return 1.280000000000000000000000e+02_bf16; }
            // exp2(x) == 0 for x <=
            static constexpr bf16_t
            exp2_lo_zero() { return -1.265000000000000000000000e+02_bf16; }

            // exp2m1(x) == +inf for x >= 0
            static constexpr bf16_t
            exp2m1_hi_inf() { return 1.280000000000000000000000e+02_bf16; }
            // exp2m1(x) == -1 for x <=
            static constexpr bf16_t
            exp2m1_lo_minus_one() { return -9.000000000000000000000000e+00_bf16; }

            // exp10(x) == +inf for x >=
            static constexpr bf16_t
            exp10_hi_inf() { return 3.875000000000000000000000e+01_bf16; }
            // exp10(x) == 0 for x <=
            static constexpr bf16_t
            exp10_lo_zero() { return -3.800000000000000000000000e+01_bf16; }

            // exp10m1(x) == +inf for x >= 0
            static constexpr bf16_t
            exp10m1_hi_inf() { return 3.875000000000000000000000e+01_bf16; }
            // exp10m1(x) == -1 for x <=
            static constexpr bf16_t
            exp10m1_lo_minus_one() { return -2.718750000000000000000000e+00_bf16; }

            // cosh(x) == +inf for abs(x) >=
            static constexpr bf16_t
            cosh_hi_inf() { return 8.950000000000000000000000e+01_bf16; }

            // sinh(x) == +inf for x >=
            static constexpr bf16_t
            sinh_hi_inf() { return 8.941599273681640625000000e+01_bf16; }
            // sinh(x) == -inf for x <=
            static constexpr bf16_t
            sinh_lo_inf() { return -8.950000000000000000000000e+01_bf16; }

            // tanh(x) == 1 for abs(x) >=
            static constexpr bf16_t
            tanh_one() { return 3.468750000000000000000000e+00_bf16; }

            static constexpr bf16_t
            log_lo_fin() { return 1.203044999669684871436754e-38_bf16; }
            static constexpr bf16_t
            log_lo_val() { return -8.750000000000000000000000e+01_bf16; }

            static constexpr bf16_t
            erf_lt_one_fin() { return 2.187500000000000000000000e+00_bf16; }

            static constexpr bf16_t
            erfc_gt_zero_fin() { return 9.187500000000000000000000e+00_bf16; }

            static constexpr bf16_t
            tgamma_hi_inf() { return 3.525000000000000000000000e+01_bf16; }

            // tgamma(x) == +- 0 for x<
            static constexpr bf16_t
            tgamma_lo_zero() { return -42.0_bf16; }

            static constexpr bf16_t
            lgamma_hi_inf() { return 4.091529924525444171282031e+36_bf16; }

            static constexpr bf16_t
            atan_equal_pi_2() { return 2.280000000000000000000000e+02_bf16; }

            static constexpr bf16_t
            sig_hi_one() {
                // log(0x1p26)
                return 18.0218257904052734375_bf16;
            }
            static constexpr bf16_t
            sig_le_eq_exp() {
                return -sig_hi_one();
            }
        };
    }
} // end namespace cftal


// Local Variables:
// mode: c++
// end:
#endif
