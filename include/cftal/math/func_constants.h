//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace math {

        template <typename _T>
        struct func_constants {};

        template <>
        struct func_constants<double> {
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
        };

        template <>
        struct func_constants<float> {
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
        };

        namespace impl {

            template <class _VEC, typename _FLOAT_T>
            struct d_real_constants {};

            template <class _VEC, typename _FLOAT_T>
            struct t_real_constants {};
        }
    }
} // end namespace cftal


// Local Variables:
// mode: c++
// end:
#endif
