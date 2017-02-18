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

    auto i0=[x]()->vf_type {
        // [0, 0.75] : | p - f | <= 2^-29.03125
        // coefficients for erf_i0 generated by sollya
        // x^0 : +0x8p-3f
        const vf_type erf_i0_c0=+1.0000000000e+00f;
        // x^2 : -0xa.aaaa6p-5f
        const vf_type erf_i0_c2=-3.3333319426e-01f;
        // x^4 : +0xc.ccb0dp-7f
        const vf_type erf_i0_c4=+9.9996663630e-02f;
        // x^6 : -0xc.2d43ap-9f
        const vf_type erf_i0_c6=-2.3782838136e-02f;
        // x^8 : +0x9.496e8p-11f
        const vf_type erf_i0_c8=+4.5345909894e-03f;
        // x^10 : -0x9.d2587p-14f
        const vf_type erf_i0_c10=-5.9946667170e-04f;
        // x^ h: +0x9.06ebbp-3f
        const vf_type two_o_sqrt_pih=+1.1283792257e+00f;
        // x^ l: -0xf.bd649p-28f
        const vf_type two_o_sqrt_pil=-5.8635382771e-08f;
        vf_type xx= x* x;
        vf_type y_i0= impl::poly(xx,
                                 // erf_i0_c14,
                                 // erf_i0_c12,
                                 erf_i0_c10,
                                 erf_i0_c8,
                                 erf_i0_c6,
                                 erf_i0_c4,
                                 erf_i0_c2,
                                 erf_i0_c0);
        vf_type yh, yl;
        yh = d_ops::two_prod(y_i0, x, yl);
        // vf_type ye;
        // vf_type p_i;
        // vf_type o_i;
        dvf_type yhl(yh, yl);
        dvf_type tos(two_o_sqrt_pih, two_o_sqrt_pil);
        yhl *= tos;
        y_i0 = yhl.h();
        // y_i0 += p_i;
        return y_i0;
    };

    auto i1=[x]()->vf_type {
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
        vf_type y_i1= impl::poly(x_i1,
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
        return y_i1;
    };

    auto i2 = [x]()->vf_type {
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
        vf_type y_i2= impl::poly(x_i2,
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
        return y_i2;
    };

    auto i3 = [x]()->vf_type {
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
        vf_type y_i3= impl::poly(x_i3,
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
        return y_i3;
    };

    auto s01 = [x, i0, i1]() -> vf_type {
        // x^ : +0xcp-4f
        const vf_type erf_i1_left=+7.5000000000e-01f;
        vf_type r=select_branch(x < erf_i1_left, i0, i1);
        return r;
    };

    auto s12 = [x, s01, i2]() -> vf_type {
        // x^ : +0xep-3f
        const vf_type erf_i2_left=+1.7500000000e+00f;
        vf_type r=select_branch(x < erf_i2_left, s01, i2);
        return r;
    };

    auto s23 = [x, s12, i3]() -> vf_type {
        // x^ : +0xcp-2f
        const vf_type erf_i3_left=+3.0000000000e+00f;
        vf_type r=select_branch(x < erf_i3_left, s12, i3);
        return r;
    };

    vf_type y = s23();
#if 0
    y=_T::sel(x > erf_i1_left, y_i1, y_i0);
    y = _T::sel(x > erf_i2_left, y_i2, y);
    y = _T::sel(x > erf_i3_left, y_i3, y);
    y = _T::sel(x > erf_i4_left, y_i4, y);
#endif
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
