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
#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_F64_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_F64_H__ 1

#include <cftal/config.h>
#include <cftal/math/func_constants.h>
#include <limits>

namespace cftal {

    namespace math {

        template <>
        struct func_constants<double> {
            static constexpr double
            min_normal() { return std::numeric_limits<double>::min(); }

            static constexpr double
            max_denormal() { return 2.225073858507200889024587e-308; }
            // exp(x) == +inf for x >=
            static constexpr double
            exp_hi_inf() { return 7.097827128933840867830440e+02; }
            // exp(x) == 0 for x <=
            static constexpr double
            exp_lo_zero() { return -7.451332191019412221066887e+02; }

            // expm1(x) == +inf for x >= 0
            static constexpr double
            expm1_hi_inf() { return 7.097827128933840867830440e+02; }
            // expm1(x) == -1 for x <=
            static constexpr double
            expm1_lo_minus_one() { return -3.742994775023704789873591e+01; }

            // exp2(x) == +inf for x >=
            static constexpr double
            exp2_hi_inf() { return 1.024000000000000000000000e+03; }
            // exp2(x) == 0 for x <=
            static constexpr double
            exp2_lo_zero() { return -1.075000000000000000000000e+03; }

            // exp2m1(x) == +inf for x >= 0
            static constexpr double
            exp2m1_hi_inf() { return 1.024000000000000000000000e+03; }
            // exp2m1(x) == -1 for x <=
            static constexpr double
            exp2m1_lo_minus_one() { return -5.400000000000000000000000e+01; }

            // exp10(x) == +inf for x >=
            static constexpr double
            exp10_hi_inf() { return 3.082547155599167467698862e+02; }
            // exp10(x) == 0 for x <=
            static constexpr double
            exp10_lo_zero() { return -3.236072453387798191215552e+02; }

            // exp10m1(x) == +inf for x >= 0
            static constexpr double
            exp10m1_hi_inf() { return 3.082547155599167467698862e+02; }
            // exp10m1(x) == -1 for x <=
            static constexpr double
            exp10m1_lo_minus_one() { return  -1.625561976585498769054539e+01; }

            // cosh(x) == +inf for abs(x) >=
            static constexpr double
            cosh_hi_inf() { return 7.104758600739439771132311e+02; }

            // sinh(x) == +inf for x >=
            static constexpr double
            sinh_hi_inf() { return 7.104758600739439771132311e+02; }
            // sinh(x) == -inf for x <=
            static constexpr double
            sinh_lo_inf() { return -7.104758600739439771132311e+02; }

            // tanh(x) == 1 for abs(x) >=
            static constexpr double
            tanh_one() { return 1.906154746539849753617091e+01; }

            // nextafter(log(x), -1) == +inf
            static constexpr double
            log_lo_fin() { return 4.940656458412465441765688e-324; }
            // log(log_lo_fin)
            static constexpr double
            log_lo_val() { return -7.444400719213812180896639e+02; }

            // erf(x) != 1.0, x>x0 -->erf(x) == 1.0
            static constexpr double
            erf_lt_one_fin() { return 5.921587195794506541801638e+00; }

            // erfc(x) >0, x < x0
            static constexpr double
            erfc_gt_zero_fin() { return 2.722601711110836220086640e+01; }

            // tgamma(x) == +inf for x>=
            static constexpr double
            tgamma_hi_inf() { return 1.716243769563027399271959e+02; }

            // tgamma(x) == +- 0 for x<
            static constexpr double
            tgamma_lo_zero() { return -184.0; }

            // lgamma(x) == +inf for x>=
            static constexpr double
            lgamma_hi_inf() { return 2.559983327851638715584478e+305; }

            // atan(x) == M_PI/2 for x>=
            static constexpr double
            atan_equal_pi_2() { return 5.805358775541311000000000e+15; }

            static constexpr double
            sig_hi_one() {
                // log(0x1p55);
                return 38.123094930796992017947766680199711244152507389814;
            }
            static constexpr double
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
