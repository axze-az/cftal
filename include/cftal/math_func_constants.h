#if !defined (__CFTAL_MATH_FUNC_CONSTANTS_H__)
#define __CFTAL_MATH_FUNC_CONSTANTS_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace math {

        template <typename _T>
        struct func_constants {};

        template <>
        struct func_constants<double> {
            constexpr static const double
            max_denormal= 2.225073858507200889024587e-308;
            // exp(x) == +inf for x >=
            constexpr static const double
            exp_hi_inf= 7.097827128933840867830440e+02;
            // exp(x) == 0 for x <=
            constexpr static const double
            exp_lo_zero= -7.451332191019412221066887e+02;

            // expm1(x) == +inf for x >= 0
            constexpr static const double
            expm1_hi_inf= 7.097827128933840867830440e+02;
            // expm1(x) == 1 for x <=
            constexpr static const double
            expm1_lo_minus_one= -3.742994775023704789873591e+01;

            // exp2(x) == +inf for x >=
            constexpr static const double
            exp2_hi_inf= 1.024000000000000000000000e+03;
            // exp2(x) == 0 for x <=
            constexpr static const double
            exp2_lo_zero= -1.075000000000000000000000e+03;

            // exp10(x) == +inf for x >=
            constexpr static const double
            exp10_hi_inf= 3.082547155599167467698862e+02;
            // exp10(x) == 0 for x <=
            constexpr static const double
            exp10_lo_zero= -3.236072453387798191215552e+02;

            // cosh(x) == +inf for abs(x) >=
            constexpr static const double
            cosh_hi_inf= 7.104758600739439771132311e+02;

            // sinh(x) == +inf for x >=
            constexpr static const double
            sinh_hi_inf= 7.104758600739439771132311e+02;
            // sinh(x) == -inf for x <=
            constexpr static const double
            sinh_lo_inf= -7.104758600739439771132311e+02;

            // nextafter(log(x), -1) == +inf
            constexpr static const double
            log_lo_fin= 4.940656458412465441765688e-324;
            // log(log_lo_fin)
            constexpr static const double
            log_lo_val= -7.444400719213812180896639e+02;

            // erf(x) != 1.0, x>x0 -->erf(x) == 1.0
            constexpr static const double
            erf_lt_one_fin= 5.921587195794506541801638e+00;

        };

        template <>
        struct func_constants<float> {
            constexpr static const float
            max_denormal= 1.175494210692441075487029e-38f;

            constexpr static const float
            exp_hi_inf= 8.872283935546875000000000e+01f;
            constexpr static const float
            exp_lo_zero= -1.039720840454101562500000e+02f;

            // expm1(x) == +inf for x >= 0
            constexpr static const float
            expm1_hi_inf= 8.872283935546875000000000e+01f;
            // expm1(x) == 1 for x <=
            constexpr static const float
            expm1_lo_minus_one= -1.732868003845214843750000e+01f;
            // exp2(x) == +inf for x >=
            constexpr static const float
            exp2_hi_inf= 1.280000000000000000000000e+02f;
            // exp2(x) == 0 for x <=
            constexpr static const float
            exp2_lo_zero= -1.500000000000000000000000e+02f;

            // exp10(x) == +inf for x >=
            constexpr static const float
            exp10_hi_inf= 3.853184127807617187500000e+01f;
            // exp10(x) == 0 for x <=
            constexpr static const float
            exp10_lo_zero= -4.515450286865234375000000e+01f;

            // cosh(x) == +inf for abs(x) >=
            constexpr static const float
            cosh_hi_inf= 8.941599273681640625000000e+01f;

            // sinh(x) == +inf for x >=
            constexpr static const float
            sinh_hi_inf= 8.941599273681640625000000e+01f;
            // sinh(x) == -inf for x <=
            constexpr static const float
            sinh_lo_inf= -8.941599273681640625000000e+01f;

            constexpr static const float
            log_lo_fin= 1.401298464324817070923730e-45f;
            constexpr static const float
            log_lo_val= -1.032789306640625000000000e+02f;

            constexpr static const float
            erf_lt_one_fin= 3.919205665588378906250000e+00f;

        };

        namespace impl {

            template <class _VEC, typename _FLOAT_T>
            struct d_real_constants {};

            template <class _VEC, typename _FLOAT_T>
            struct t_real_constants {};
        }
    }
}


// Local Variables:
// mode: c++
// end:
#endif
