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
#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_F16_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_F16_H__ 1

#include <cftal/config.h>
#include <cftal/f16_t.h>
#include <cftal/math/func_constants.h>
#include <limits>

namespace cftal {

    namespace math {

        template <>
        struct func_constants<f16_t> {
            constexpr static f16_t
            min_normal() { return 0x1p-14_f16; }

            constexpr static f16_t
            max_denormal() { return 6.097555160522460937500000e-05_f16; }

            // exp(x) == +inf for x >=
            constexpr static f16_t
            exp_hi_inf() { return 1.109375000000000000000000e+01_f16; }
            // exp(x) == 0 for x <=
            constexpr static f16_t
            exp_lo_zero() { return -1.734375000000000000000000e+01_f16; }

            // expm1(x) == +inf for x >= 0
            constexpr static f16_t
            expm1_hi_inf() { return 1.109375000000000000000000e+01_f16; }
            // expm1(x) == -1 for x <=
            constexpr static f16_t
            expm1_lo_minus_one() { return -8.320312500000000000000000e+00_f16; }

            // exp2(x) == +inf for x >=
            constexpr static f16_t
            exp2_hi_inf() { return 1.600000000000000000000000e+01_f16; }
            // exp2(x) == 0 for x <=
            constexpr static f16_t
            exp2_lo_zero() { return -2.500000000000000000000000e+01_f16; }

            // exp2m1(x) == +inf for x >= 0
            constexpr static f16_t
            exp2m1_hi_inf() { return 1.600000000000000000000000e+01_f16; }
            // exp2m1(x) == -1 for x <=
            constexpr static f16_t
            exp2m1_lo_minus_one() { return -1.200000000000000000000000e+01_f16; }

            // exp10(x) == +inf for x >=
            constexpr static f16_t
            exp10_hi_inf() { return 4.816406250000000000000000e+00_f16; }
            // exp10(x) == 0 for x <=
            constexpr static f16_t
            exp10_lo_zero() { return -7.527343750000000000000000e+00_f16; }

            // exp10m1(x) == +inf for x >= 0
            constexpr static f16_t
            exp10m1_hi_inf() { return 4.816406250000000000000000e+00_f16; }
            // exp10m1(x) == -1 for x <=
            constexpr static f16_t
            exp10m1_lo_minus_one() { return -3.613281250000000000000000e+00_f16; }

            // cosh(x) == +inf for abs(x) >=
            constexpr static f16_t
            cosh_hi_inf() { return 1.178906250000000000000000e+01_f16; }

            // sinh(x) == +inf for x >=
            constexpr static f16_t
            sinh_hi_inf() { return 1.178906250000000000000000e+01_f16; }
            // sinh(x) == -inf for x <=
            constexpr static f16_t
            sinh_lo_inf() { return -1.178906250000000000000000e+01_f16; }

            // tanh(x) == 1 for abs(x) >=
            constexpr static f16_t
            tanh_one() { return 4.507812500000000000000000e+00_f16; }

            constexpr static f16_t
            log_lo_fin() { return 5.960464477539062500000000e-08_f16; }
            constexpr static f16_t
            log_lo_val() { return -1.664062500000000000000000e+01_f16; }

            constexpr static f16_t
            erf_lt_one_fin() { return 2.593750000000000000000000e+00_f16; }

            constexpr static f16_t
            erfc_gt_zero_fin() { return 3.917968750000000000000000e+00_f16; }

            constexpr static f16_t
            tgamma_hi_inf() { return 9.226562500000000000000000e+00_f16; }

            // tgamma(x) == +- 0 for x<
            constexpr static f16_t
            tgamma_lo_zero() { return -12.5_f16; }

            constexpr static f16_t
            lgamma_hi_inf() { return 8.18400000e+03_f16; }

            constexpr static f16_t
            atan_equal_pi_2() { return 1.029000000000000000000000e+03_f16; }

            constexpr static f16_t
            sig_hi_one() {
                // ~log(0x1p12)
                return 8.320312500000000000000000e+00_f16;
            }
            constexpr static f16_t
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
