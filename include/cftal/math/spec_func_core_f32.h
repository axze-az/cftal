//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F32_H__)
#define __CFTAL_MATH_ELEM_SPEC_CORE_F32_H__ 1

// This code uses code from sun libm:
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_core_f32.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for float and different
        // traits
        template <typename _T>
        struct spec_func_core<float, _T>
            : public elem_func_core<float, _T> {

            using my_type = spec_func_core<float, _T>;

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using dvf_type = d_real<vf_type>;


            using d_ops=cftal::impl::d_real_ops<vf_type,
                                                d_real_traits<vf_type>::fma>;

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

        };

    }
}


template <typename _T>
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
erf_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    const vf_type erf_i1_left=+7.5000000000e-01f;
    const vf_type erf_i2_left=+1.7500000000e+00f;
    const vf_type erf_i3_left=+3.0000000000e+00f;

    vmf_type x_in_i0 = x <= erf_i1_left;
    vf_type y=0;
    if (likely(any_of(x_in_i0))) {
        // [0, 0.75] : | p - f | <= 2^-29.828125
        // coefficients for erf_i0 generated by sollya
        // x^1 h: +0x9.06ebap-3f
        const float erf_i0_c1h=+1.1283791065e+00f;
        // x^1 l: +0xf.e2ad5p-28f
        const float erf_i0_c1l=+5.9177938994e-08f;
        // x^3 : -0xc.0939dp-5f
        const float erf_i0_c3=-3.7612619996e-01f;
        // x^5 : +0xe.71577p-7f
        const float erf_i0_c5=+1.1283390969e-01f;
        // x^7 : -0xd.bd59bp-9f
        const float erf_i0_c7=-2.6835253462e-02f;
        // x^9 : +0xa.7a005p-11f
        const float erf_i0_c9=+5.1155113615e-03f;
        // x^11 : -0xb.1233p-14f
        const float erf_i0_c11=-6.7572575063e-04f;
        vf_type xx=x*x;
        vf_type i0h= horner(xx,
                            erf_i0_c11,
                            erf_i0_c9,
                            erf_i0_c7,
                            erf_i0_c5,
                            erf_i0_c3)*xx;
        vf_type i0l;
        d_ops::add212(i0h, i0l, erf_i0_c1h, erf_i0_c1l, i0h);
        d_ops::mul122(i0h, i0l, x, i0h, i0l);
        y= i0h;
    };

    vmf_type x_in_i1 = (x > erf_i1_left) & (x<=erf_i2_left);
    if (likely(any_of(x_in_i1))) {
        // [0.75, 1.75] : | p - f | <= 2^-31.609375
        // coefficients for erf_i1 generated by sollya
        // x^0 h: +0xe.c432fp-4f
        const vf_type erf_i1_c0h=+9.2290014029e-01f;
        // x^0 l: -0xc.df0bap-30f
        const vf_type erf_i1_c0l=-1.1987305371e-08f;
        // x^1 : +0xf.23298p-6f
        const vf_type erf_i1_c1=+2.3652112484e-01f;
        // x^2 : -0x9.75f9fp-5f
        const vf_type erf_i1_c2=-2.9565140605e-01f;
        // x^3 : +0xa.b8e83p-6f
        const vf_type erf_i1_c3=+1.6753582656e-01f;
        // x^4 : -0xc.9d451p-11f
        const vf_type erf_i1_c4=-6.1593432911e-03f;
        // x^5 : -0xc.143f5p-8f
        const vf_type erf_i1_c5=-4.7183949500e-02f;
        // x^6 : +0xa.e7e45p-9f
        const vf_type erf_i1_c6=+2.1300444379e-02f;
        // x^7 : +0xf.02551p-12f
        const vf_type erf_i1_c7=+3.6643336061e-03f;
        // x^8 : -0xb.a7584p-11f
        const vf_type erf_i1_c8=-5.6902784854e-03f;
        // x^9 : +0xb.511b8p-14f
        const vf_type erf_i1_c9=+6.9072423503e-04f;
        // x^10 : +0xc.76818p-14f
        const vf_type erf_i1_c10=+7.6067587361e-04f;
        // x^ : +0xap-3f
        const vf_type erf_i1_x0=+1.2500000000e+00f;
        vf_type x_i1 = x - erf_i1_x0;
        vf_type y_i1= horner(x_i1,
                             erf_i1_c10,
                             erf_i1_c9,
                             erf_i1_c8,
                             erf_i1_c7,
                             erf_i1_c6,
                             erf_i1_c5,
                             erf_i1_c4,
                             erf_i1_c3,
                             erf_i1_c2,
                             erf_i1_c1)*x_i1;
        y_i1 += erf_i1_c0l;
        y_i1 += erf_i1_c0h;
        y = _T::sel(x_in_i1, y_i1, y);
    };

    vmf_type x_in_i2 = (x > erf_i2_left) & (x<=erf_i3_left);
    if (likely(any_of(x_in_i2))) {
        // [1.75, 3] : | p - f | <= 2^-32.15625
        // coefficients for erf_i2 generated by sollya
        // x^0 h: +0xf.fccbp-4f
        const vf_type erf_i2_c0h=+9.9921703339e-01f;
        // x^0 l: +0xf.482d6p-29f
        const vf_type erf_i2_c0l=+2.8464835822e-08f;
        // x^1 : +0x8.348cdp-11f
        const vf_type erf_i2_c1=+4.0064812638e-03f;
        // x^2 : -0x9.be676p-10f
        const vf_type erf_i2_c2=-9.5153953880e-03f;
        // x^3 : +0xe.0f54fp-10f
        const vf_type erf_i2_c3=+1.3730361126e-02f;
        // x^4 : -0xd.72b8fp-10f
        const vf_type erf_i2_c4=-1.3132943772e-02f;
        // x^5 : +0x8.8f7bfp-10f
        const vf_type erf_i2_c5=+8.3598485216e-03f;
        // x^6 : -0xc.c4173p-12f
        const vf_type erf_i2_c6=-3.1166940462e-03f;
        // x^7 : +0xe.49ec2p-17f
        const vf_type erf_i2_c7=+1.0901458154e-04f;
        // x^8 : +0x9.ed063p-14f
        const vf_type erf_i2_c8=+6.0582737206e-04f;
        // x^9 : -0x9.e2311p-15f
        const vf_type erf_i2_c9=-3.0162234907e-04f;
        // x^10 : +0xf.ad2bdp-19f
        const vf_type erf_i2_c10=+2.9900455047e-05f;
        // x^ : +0xep-3f
        // const vf_type erf_i2_left=+1.7500000000e+00f;
        // x^ : +0x9.8p-2f
        const vf_type erf_i2_x0=+2.3750000000e+00f;
        vf_type x_i2 = x - erf_i2_x0;
        vf_type y_i2= horner(x_i2,
                             erf_i2_c10,
                             erf_i2_c9,
                             erf_i2_c8,
                             erf_i2_c7,
                             erf_i2_c6,
                             erf_i2_c5,
                             erf_i2_c4,
                             erf_i2_c3,
                             erf_i2_c2,
                             erf_i2_c1)*x_i2;
        y_i2 += erf_i2_c0l;
        y_i2 += erf_i2_c0h;
        y = _T::sel(x_in_i2, y_i2, y);
    };

    vmf_type x_in_i3 = (x > erf_i3_left);
    if (likely(any_of(x_in_i3))) {
        // [3, 4] : | p - f | <= 2^-42.765625
        // coefficients for erf_i3 generated by sollya
        // x^0 h: +0xf.ffff4p-4f
        const vf_type erf_i3_c0h=+9.9999928474e-01f;
        // x^0 l: -0xe.f2acbp-29f
        const vf_type erf_i3_c0l=-2.7842721906e-08f;
        // x^1 : +0xb.52cbdp-21f
        const vf_type erf_i3_c1=+5.3994285736e-06f;
        // x^2 : -0x9.e8715p-19f
        const vf_type erf_i3_c2=-1.8897970222e-05f;
        // x^3 : +0xb.16648p-18f
        const vf_type erf_i3_c3=+4.2295345338e-05f;
        // x^4 : -0x8.e0446p-17f
        const vf_type erf_i3_c4=-6.7718836362e-05f;
        // x^5 : +0xa.c3812p-17f
        const vf_type erf_i3_c5=+8.2120430307e-05f;
        // x^6 : -0xa.301d9p-17f
        const vf_type erf_i3_c6=-7.7727898315e-05f;
        // x^7 : +0xf.3e57cp-18f
        const vf_type erf_i3_c7=+5.8149438701e-05f;
        // x^8 : -0x9.02fa8p-18f
        const vf_type erf_i3_c8=-3.4376658732e-05f;
        // x^9 : +0x8.25ba9p-19f
        const vf_type erf_i3_c9=+1.5539890228e-05f;
        // x^10 : -0x8.ed1e3p-21f
        const vf_type erf_i3_c10=-4.2563638090e-06f;
        // x^ : +0xep-2f
        const vf_type erf_i3_x0=+3.5000000000e+00f;
        vf_type x_i3 = x - erf_i3_x0;
        vf_type y_i3= horner(x_i3,
                             erf_i3_c10,
                             erf_i3_c9,
                             erf_i3_c8,
                             erf_i3_c7,
                             erf_i3_c6,
                             erf_i3_c5,
                             erf_i3_c4,
                             erf_i3_c3,
                             erf_i3_c2,
                             erf_i3_c1)*x_i3;
        y_i3 += erf_i3_c0l;
        y_i3 += erf_i3_c0h;
        y=_T::sel(x_in_i3, y_i3, y);
    };
    y = copysign(y, xc);
    return y;
}

template <typename _T>
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
erfc_k(arg_t<vf_type> xc)
{
    return 1-erf_k(xc);
}


// Local Variables:
// mode: c++
// end:
#endif
