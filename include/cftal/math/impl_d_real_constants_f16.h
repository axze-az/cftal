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
#if !defined (__CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F16_H__)
#define __CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F16_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f16.h>
#include <cftal/std_types.h>
#include <cftal/math/func_constants_f16.h>

namespace cftal {
    namespace math {
        namespace impl {

            template <class _T>
            struct d_real_constants<_T, f16_t> {
                // M_LN2 LOG_E(2) for cody and waite argument reduction
                static const f16_t m_ln2_cw[2];
                // M_LG2 LOG_10(2) for cody and waite argument reduction
                static const f16_t m_lg2_cw[2];
                // M_PI/2 for cody and waite argument reduction
                static const f16_t m_pi_2_cw[3];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_LG(2) LOG_10(2)
                static const _T m_lg2;
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
const cftal::f16_t
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::
m_ln2_cw[2]={
   +6.87500000e-01_f16,
   +5.64575195e-03_f16
};

template <class _T>
const cftal::f16_t
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::
m_lg2_cw[2]={
   +3.00781250e-01_f16,
   +2.48670578e-04_f16
};

template <class _T>
const cftal::f16_t
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::
m_pi_2_cw[3]={
   +1.56250000e+00_f16,
   +8.17871094e-03_f16,
   +1.17599964e-04_f16
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_ln2(
    +6.93359375e-01_f16, -2.12192535e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_ln10(
    +2.30078125e+00_f16, +1.80339813e-03_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_lg2(
    +3.01025391e-01_f16, +4.58955765e-06_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_1_ln2(
    +1.44238281e+00_f16, +3.12328339e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_1_lg2(
    +3.32226562e+00_f16, -3.37600708e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_1_ln10(
    +4.34082031e-01_f16, +2.12430954e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_pi2(
    +6.28125000e+00_f16, +1.93500519e-03_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_pi(
    +3.14062500e+00_f16, +9.67502594e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_1_pi(
    +3.18359375e-01_f16, -4.94718552e-05_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_pi_2(
    +1.57031250e+00_f16, +4.83751297e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_2_pi(
    +6.36718750e-01_f16, -9.90033150e-05_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_pi_4(
    +7.85156250e-01_f16, +2.41875648e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_4_pi(
    +1.27343750e+00_f16, -1.98006630e-04_f16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, cftal::f16_t>::m_ln_pi(
    +1.14453125e+00_f16, +1.98602676e-04_f16);


// Local Variables:
// mode: c++
// end:
#endif
