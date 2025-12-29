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
#if !defined (__CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F32_H__)
#define __CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f32.h>
#include <cftal/std_types.h>
#include <cftal/math/func_constants_f32.h>

namespace cftal {
    namespace math {
        namespace impl {

            template <class _T>
            struct d_real_constants<_T, float> {
                // M_LN2 LOG_E(2) for cody and waite argument reduction
                static const float m_ln2_cw[2];
                // M_LG2 LOG_10(2) for cody and waite argument reduction
                static const float m_lg2_cw[2];
                // M_PI/2 for cody and waite argument reduction
                static const float m_pi_2_cw[3];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_LG(2) LOG_10(2)
                static const _T m_lg2;
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
                // M_1_LG2 1/LOG_10(2)
                static const _T m_1_lg2;
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
                // log_e(PI)
                static const _T m_ln_pi;
            };

        }
    }
}

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
m_lg2_cw[2]={
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
cftal::math::impl::d_real_constants<_T, float>::m_lg2(
    +3.0103000998497e-01f, -1.4320988839245e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_lg2(
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

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln_pi(
    +1.1447298526764e+00f, +3.3173009228449e-08f);


// Local Variables:
// mode: c++
// end:
#endif
