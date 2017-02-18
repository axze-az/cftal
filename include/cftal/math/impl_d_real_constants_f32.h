//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F32_H__)
#define __CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/math/func_constants.h>

namespace cftal {
    namespace math {

        namespace impl {

            template <class _T>
            struct d_real_constants<_T, float> {
                // large exp argument
                static const float exp_arg_large;
                // log(x): avoid denormals
                static const float log_arg_small;
                // if above factor to multiply with
                static const float log_arg_small_factor;
                // large sin cos argument
                static const float sin_cos_arg_large;
                // large native sin cos argument
                static const float native_sin_cos_arg_large;
                // M_LN2 LOG_E(2) for cody and waite argument reduction
                static const float m_ln2_cw[2];
                // M_LD2 LOG_10(2) for cody and waite argument reduction
                static const float m_ld2_cw[2];
                // M_PI/2 for cody and waite argument reduction
                static const float m_pi_2_cw[3];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_LD(2) LOG_10(2)
                static const _T m_ld2;
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

        }
    }
}

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
exp_arg_large= 8.8000000000000e+01f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
log_arg_small= 1.9721522630525e-31f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
log_arg_small_factor= 2.8147497671066e+14f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
sin_cos_arg_large= 0x1.0p24f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
native_sin_cos_arg_large= 0x1.0p20f;

/* ---------------------------------------------------------------- */
template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_ln2_cw[2]={
   +6.9314575195312e-01f,
   +1.4286067653302e-06f
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_ld2_cw[2]={
   +3.0102539062500e-01f,
   +4.6050390665187e-06f
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_pi_2_cw[3]={
   +1.5707397460938e+00f,
   +5.6579709053040e-05f,
   +9.9209362947050e-10f
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2(
    +6.9314718246460e-01f, -1.9046542121259e-09f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ln2(
    +1.4426950216293e+00f, +1.9259630335000e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ld2(
    +3.0103000998497e-01f, -1.4320988839245e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ld2(
    +3.3219280242920e+00f, +7.0595369550119e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln10(
    +2.3025848865509e+00f, +2.0644314702167e-07f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ln10(
    +4.3429446220398e-01f, +1.9699271547324e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2pow106(
    +7.3473594665527e+01f, +6.4738269429654e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2pow48(
    +3.3271060943604e+01f, +3.7232739487081e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln_small_arg(
    +3.3271060943604e+01f, +3.7232739487081e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi(
    +3.1415927410126e+00f, -8.7422776573476e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi2(
    +6.2831854820251e+00f, -1.7484555314695e-07f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi_2(
    +1.5707963705063e+00f, -4.3711388286738e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi_4(
    +7.8539818525314e-01f, -2.1855694143369e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_pi(
    +3.1830987334251e-01f, +1.2841276486597e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_2_pi(
    +6.3661974668503e-01f, +2.5682552973194e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_4_pi(
    +1.2732394933701e+00f, +5.1365105946388e-08f);

// Local Variables:
// mode: c++
// end:
#endif
