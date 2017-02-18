//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F64_H__)
#define __CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math/func_constants.h>


namespace cftal {

    namespace math {

        namespace impl {

            template <class _T>
            struct d_real_constants<_T, double> {
                // exp(x) may be to large
                static const double exp_arg_large;
                // log(x): avoid denormals
                static const double log_arg_small;
                // if above factor to multiply with
                static const double log_arg_small_factor;
                // large sin cos argument
                static const double sin_cos_arg_large;
                // large native sin cos argument
                static const double native_sin_cos_arg_large;
                // M_LN2 LOG_E(2) for cody and waite argument reduction
                static const double m_ln2_cw[2];
                // M_LD2 LOG_10(2) for cody and waite argument reduction
                static const double m_ld2_cw[2];
                // M_PI/2 for cody and waite argument reduction
                static const double m_pi_2_cw[];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LD2 LOG_10(2)
                static const _T m_ld2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_LN_2POW106
                static const _T m_ln2pow106;
                // M_LN_2POW48
                static const _T m_ln2pow48;
                // M_LN_2_SMALL_ARG
                static const _T m_ln_small_arg;
                // low half of m_ln2
                // static const _T m_ln2_low;
                // M_1_LN2 1/LOG_E(2)
                static const _T m_1_ln2;
                // M_1_LD2 1/LOG_10(2)
                static const _T m_1_ld2;
                // M_1_LN10 1/LOG_E(10)
                static const _T m_1_ln10;
                // 2*PI
                static const _T m_pi2;
                // 1/(2*PI)
                static const _T m_1_pi2;
                // PI
                static const _T m_pi;
                // 1/PI
                static const _T m_1_pi;
                // PI/2
                static const _T m_pi_2;
                // 2/PI
                static const _T m_2_pi;
                // PI/4
                static const _T m_pi_4;
                // 4/PI
                static const _T m_4_pi;
            };

        } // impl
    } // math
} // cftal

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
exp_arg_large= 7.0900000000000000000000e+02;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
log_arg_small= 2.0041683600089727779961e-292;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
log_arg_small_factor= 8.1129638414606681695789e+31;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
sin_cos_arg_large= 0x1.0p31;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
native_sin_cos_arg_large= 0x1.0p31;

/* ----------------------------------------------------------------*/
template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_ln2_cw[2]={
   +6.9314718036912381649017e-01,
   +1.9082149292705877000220e-10
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_ld2_cw[2]={
   +3.0102999554947018623352e-01,
   +1.1451100898021838421065e-10
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_pi_2_cw[3]={
   +1.5707963267341256141663e+00,
   +6.0771005063039659765955e-11,
   +2.0222662487959506315411e-21
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
    +6.9314718055994528622676e-01, +2.3190468138462995584178e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln2(
    +1.4426950408889633870047e+00, +2.0355273740931033111021e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ld2(
    +3.0102999566398119801747e-01, -2.8037281277851703937326e-18);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ld2(
    +3.3219280948873621817086e+00, +1.6616175169735920064130e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln10(
    +2.3025850929940454570044e+00, +2.2701358751183765644142e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln10(
    +4.3429448190325181666793e-01, +1.0983196502167650727389e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2pow106(
    +7.3473601139354201450260e+01, +1.3479665980519211209217e-15);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2pow48(
    +3.3271064666877371962528e+01, +2.8894993100464744006298e-15);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln_small_arg(
    +7.3473601139354201450260e+01, +1.3479665980519211209217e-15);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi(
    +3.1415926535897931159980e+00, +1.2246467991473532071738e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi2(
    +6.2831853071795862319959e+00, +2.4492935982947064143475e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_2(
    +1.5707963267948965579990e+00, +6.1232339957367660358688e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_4(
    +7.8539816339744827899949e-01, +3.0616169978683830179344e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi(
    +3.1830988618379069121644e-01, -1.9678676675182485881895e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_2_pi(
    +6.3661977236758138243289e-01, -3.9357353350364971763790e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_4_pi(
    +1.2732395447351627648658e+00, -7.8714706700729943527581e-17);

// Local Variables:
// mode: c++
// end:
#endif
