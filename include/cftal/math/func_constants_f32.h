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
#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_F32_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_F32_H__ 1

#include <cftal/config.h>
#include <cftal/math/func_constants.h>
#include <limits>

namespace cftal {

    namespace math {

        template <>
        struct func_constants<float> {
            static constexpr float
            min_normal() { return 0x1p-126f; }

            static constexpr float
            max_denormal() { return 1.175494210692441075487029e-38f; }

            // exp(x) == +inf for x >=
            static constexpr float
            exp_hi_inf() { return 8.872283935546875000000000e+01f; }
            // exp(x) == 0 for x <=
            static constexpr float
            exp_lo_zero() { return -1.039720840454101562500000e+02f; }

            // expm1(x) == +inf for x >= 0
            static constexpr float
            expm1_hi_inf() { return 8.872283935546875000000000e+01f; }
            // expm1(x) == -1 for x <=
            static constexpr float
            expm1_lo_minus_one() { return -1.732868003845214843750000e+01f; }

            // exp2(x) == +inf for x >=
            static constexpr float
            exp2_hi_inf() { return 1.280000000000000000000000e+02f; }
            // exp2(x) == 0 for x <=
            static constexpr float
            exp2_lo_zero() { return -1.500000000000000000000000e+02f; }

            // exp2m1(x) == +inf for x >= 0
            static constexpr float
            exp2m1_hi_inf() { return 1.280000000000000000000000e+02f; }
            // exp2m1(x) == -1 for x <=
            static constexpr float
            exp2m1_lo_minus_one() { return -2.500000000000000000000000e+01f; }

            // exp10(x) == +inf for x >=
            static constexpr float
            exp10_hi_inf() { return 3.853184127807617187500000e+01f; }
            // exp10(x) == 0 for x <=
            static constexpr float
            exp10_lo_zero() { return -4.515450286865234375000000e+01f; }

            // exp10m1(x) == +inf for x >= 0
            static constexpr float
            exp10m1_hi_inf() { return 3.853184127807617187500000e+01f; }
            // exp10m1(x) == -1 for x <=
            static constexpr float
            exp10m1_lo_minus_one() { return -7.525750160217285156250000e+00f; }

            // cosh(x) == +inf for abs(x) >=
            static constexpr float
            cosh_hi_inf() { return 8.941599273681640625000000e+01f; }

            // sinh(x) == +inf for x >=
            static constexpr float
            sinh_hi_inf() { return 8.941599273681640625000000e+01f; }
            // sinh(x) == -inf for x <=
            static constexpr float
            sinh_lo_inf() { return -8.941599273681640625000000e+01f; }

            // tanh(x) == 1 for abs(x) >=
            static constexpr float
            tanh_one() { return 9.010913848876953125000000e+00f; }

            static constexpr float
            log_lo_fin() { return 1.401298464324817070923730e-45f; }
            static constexpr float
            log_lo_val() { return -1.032789306640625000000000e+02f; }

            static constexpr float
            erf_lt_one_fin() { return 3.919205665588378906250000e+00f; }

            static constexpr float
            erfc_gt_zero_fin() { return 1.005419445037841796875000e+01f; }

            static constexpr float
            tgamma_hi_inf() { return 3.504010009765625000000000e+01f; }

            // tgamma(x) == +- 0 for x<
            static constexpr float
            tgamma_lo_zero() { return -42.0f; }

            static constexpr float
            lgamma_hi_inf() { return 4.085003425410169132208425e+36f; }

            static constexpr float
            atan_equal_pi_2() { return 6.291977600000000000000000e+07f; }

            static constexpr float
            sig_hi_one() {
                // log(0x1p26)
                return 18.0218257904052734375f;
            }
            static constexpr float
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
