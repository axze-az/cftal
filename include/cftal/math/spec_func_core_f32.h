//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F32_H__)
#define __CFTAL_MATH_ELEM_SPEC_CORE_F32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_core_f32.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/lanczos.h>
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
            using base_type = elem_func_core<float, _T>;

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using dvf_type = d_real<vf_type>;


            using d_ops=cftal::impl::d_real_ops<vf_type,
                                                d_real_traits<vf_type>::fma>;

            static
            vi_type
            __reduce_trigpi_arg(vf_type& __restrict xrh,
                                vf_type& __restrict xrl,
                                arg_t<vf_type> x);

            // calculates sin(pi*x), cos(pi*x)
            static
            void
            sinpi_cospi_k(arg_t<vf_type> xc,
                          vf_type* ps, vf_type *pc);

            static
            void
            sinpi_cospi_k(arg_t<vf_type> xc,
                          dvf_type* ps, dvf_type *pc);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

            static
            vf_type
            tgamma_k(arg_t<vf_type> xc, arg_t<vmf_type> xc_lt_0);

            // calculates lngamma for x in [1, 2]
            static
            dvf_type
            __lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // returns _xr in the range [1, 2]
            // returns _f (including sign)= (x+N)(x+_N-1)...(x-1)(x-2)
            // lgamma(x) = lgamma(xr) * log(abs(_f))
            struct reduced_small_gamma_args {
                dvf_type _xr, _f;
                reduced_small_gamma_args() : _xr(), _f() {};
                reduced_small_gamma_args(const dvf_type& xr, const dvf_type& f)
                    : _xr(xr), _f(f) {};
            };
            static
            reduced_small_gamma_args
            __lgamma_reduce_small_k(arg_t<vf_type> x);

            static
            vf_type
            lgamma_k(arg_t<vf_type> xc, vi_type* signp);

        };

    }
}

template <typename _T>
typename cftal::math::spec_func_core<float, _T>::vi_type
cftal::math::spec_func_core<float, _T>::
__reduce_trigpi_arg(vf_type& xrh, vf_type& xrl, arg_t<vf_type> xc)
{
    vf_type fh= rint(vf_type(xc*2.0f));
    xrh = xc - 0.5f * fh;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    d_ops::mul122(xrh, xrl, xrh, ctbl::m_pi[0], ctbl::m_pi[1]);
    vi_type q= _T::cvt_f_to_i(fh);
    return q;
}

template <typename _T>
void
cftal::math::spec_func_core<float, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type xrh, xrl;
    auto q=__reduce_trigpi_arg(xrh, xrl, xc);
    base_type::__sin_cos_k(xrh, xrl, q, ps, pc);
}

template <typename _T>
void
cftal::math::spec_func_core<float, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, dvf_type* ps, dvf_type* pc)
{
    vf_type xrh, xrl;
    auto q=__reduce_trigpi_arg(xrh, xrl, xc);
    base_type::__sin_cos_k(xrh, xrl, q, ps, pc);
}

template <typename _T>
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
erf_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    const float erf_i1_left=+7.5000000000e-01f;
    const float erf_i2_left=+1.7500000000e+00f;
    const float erf_i3_left=+3.0000000000e+00f;

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

        static const float c_y_i0[]= {
            erf_i0_c11,
            erf_i0_c9,
            erf_i0_c7,
            erf_i0_c5,
            erf_i0_c3
        };
        vf_type i0h= horner2(xx, vf_type(xx*xx), c_y_i0)* xx;

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
        const float erf_i1_c0h=+9.2290014029e-01f;
        // x^0 l: -0xc.df0bap-30f
        const float erf_i1_c0l=-1.1987305371e-08f;
        // x^1 : +0xf.23298p-6f
        const float erf_i1_c1=+2.3652112484e-01f;
        // x^2 : -0x9.75f9fp-5f
        const float erf_i1_c2=-2.9565140605e-01f;
        // x^3 : +0xa.b8e83p-6f
        const float erf_i1_c3=+1.6753582656e-01f;
        // x^4 : -0xc.9d451p-11f
        const float erf_i1_c4=-6.1593432911e-03f;
        // x^5 : -0xc.143f5p-8f
        const float erf_i1_c5=-4.7183949500e-02f;
        // x^6 : +0xa.e7e45p-9f
        const float erf_i1_c6=+2.1300444379e-02f;
        // x^7 : +0xf.02551p-12f
        const float erf_i1_c7=+3.6643336061e-03f;
        // x^8 : -0xb.a7584p-11f
        const float erf_i1_c8=-5.6902784854e-03f;
        // x^9 : +0xb.511b8p-14f
        const float erf_i1_c9=+6.9072423503e-04f;
        // x^10 : +0xc.76818p-14f
        const float erf_i1_c10=+7.6067587361e-04f;
        // x^ : +0xap-3f
        const float erf_i1_x0=+1.2500000000e+00f;
        vf_type x_i1 = x - erf_i1_x0;
        vf_type x_i1_sqr = x_i1*x_i1;

        static const float c_i[]={
            erf_i1_c10,
            erf_i1_c9,
            erf_i1_c8,
            erf_i1_c7,
            erf_i1_c6,
            erf_i1_c5,
            erf_i1_c4,
            erf_i1_c3
        };
        vf_type y_i1= horner2(x_i1, x_i1_sqr, c_i);
        y_i1=horner(x_i1, y_i1, erf_i1_c2, erf_i1_c1)*x_i1;
        y_i1 += erf_i1_c0l;
        y_i1 += erf_i1_c0h;
        y = _T::sel(x_in_i1, y_i1, y);
    };

    vmf_type x_in_i2 = (x > erf_i2_left) & (x<=erf_i3_left);
    if (likely(any_of(x_in_i2))) {
        // [1.75, 3] : | p - f | <= 2^-32.15625
        // coefficients for erf_i2 generated by sollya
        // x^0 h: +0xf.fccbp-4f
        const float erf_i2_c0h=+9.9921703339e-01f;
        // x^0 l: +0xf.482d6p-29f
        const float erf_i2_c0l=+2.8464835822e-08f;
        // x^1 : +0x8.348cdp-11f
        const float erf_i2_c1=+4.0064812638e-03f;
        // x^2 : -0x9.be676p-10f
        const float erf_i2_c2=-9.5153953880e-03f;
        // x^3 : +0xe.0f54fp-10f
        const float erf_i2_c3=+1.3730361126e-02f;
        // x^4 : -0xd.72b8fp-10f
        const float erf_i2_c4=-1.3132943772e-02f;
        // x^5 : +0x8.8f7bfp-10f
        const float erf_i2_c5=+8.3598485216e-03f;
        // x^6 : -0xc.c4173p-12f
        const float erf_i2_c6=-3.1166940462e-03f;
        // x^7 : +0xe.49ec2p-17f
        const float erf_i2_c7=+1.0901458154e-04f;
        // x^8 : +0x9.ed063p-14f
        const float erf_i2_c8=+6.0582737206e-04f;
        // x^9 : -0x9.e2311p-15f
        const float erf_i2_c9=-3.0162234907e-04f;
        // x^10 : +0xf.ad2bdp-19f
        const float erf_i2_c10=+2.9900455047e-05f;
        // x^ : +0xep-3f
        // const float erf_i2_left=+1.7500000000e+00f;
        // x^ : +0x9.8p-2f
        const float erf_i2_x0=+2.3750000000e+00f;
        vf_type x_i2 = x - erf_i2_x0;
        vf_type x_i2_sqr= x_i2*x_i2;

        static const float c_i[]={
            erf_i2_c10,
            erf_i2_c9,
            erf_i2_c8,
            erf_i2_c7,
            erf_i2_c6,
            erf_i2_c5,
            erf_i2_c4,
            erf_i2_c3,
            erf_i2_c2,
            erf_i2_c1
        };
        vf_type y_i2= horner2(x_i2, x_i2_sqr, c_i)* x_i2;
        y_i2 += erf_i2_c0l;
        y_i2 += erf_i2_c0h;
        y = _T::sel(x_in_i2, y_i2, y);
    };

    vmf_type x_in_i3 = (x > erf_i3_left);
    if (likely(any_of(x_in_i3))) {
        // [3, 4] : | p - f | <= 2^-42.765625
        // coefficients for erf_i3 generated by sollya
        // x^0 h: +0xf.ffff4p-4f
        const float erf_i3_c0h=+9.9999928474e-01f;
        // x^0 l: -0xe.f2acbp-29f
        const float erf_i3_c0l=-2.7842721906e-08f;
        // x^1 : +0xb.52cbdp-21f
        const float erf_i3_c1=+5.3994285736e-06f;
        // x^2 : -0x9.e8715p-19f
        const float erf_i3_c2=-1.8897970222e-05f;
        // x^3 : +0xb.16648p-18f
        const float erf_i3_c3=+4.2295345338e-05f;
        // x^4 : -0x8.e0446p-17f
        const float erf_i3_c4=-6.7718836362e-05f;
        // x^5 : +0xa.c3812p-17f
        const float erf_i3_c5=+8.2120430307e-05f;
        // x^6 : -0xa.301d9p-17f
        const float erf_i3_c6=-7.7727898315e-05f;
        // x^7 : +0xf.3e57cp-18f
        const float erf_i3_c7=+5.8149438701e-05f;
        // x^8 : -0x9.02fa8p-18f
        const float erf_i3_c8=-3.4376658732e-05f;
        // x^9 : +0x8.25ba9p-19f
        const float erf_i3_c9=+1.5539890228e-05f;
        // x^10 : -0x8.ed1e3p-21f
        const float erf_i3_c10=-4.2563638090e-06f;
        // x^ : +0xep-2f
        const float erf_i3_x0=+3.5000000000e+00f;
        vf_type x_i3 = x - erf_i3_x0;
        vf_type x_i3_sqr= x_i3*x_i3;

        static const float c_i[]={
            erf_i3_c10,
            erf_i3_c9,
            erf_i3_c8,
            erf_i3_c7,
            erf_i3_c6,
            erf_i3_c5,
            erf_i3_c4,
            erf_i3_c3,
            erf_i3_c2,
            erf_i3_c1
        };
        vf_type y_i3= horner2(x_i3, x_i3_sqr, c_i)*x_i3;
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
    vf_type x= abs(xc);
    vmf_type x_le_0_75 = x <= 0.75f;
    vmf_type x_gt_0_75 = x > 0.75f;

    vf_type exl=0, exh=0;

    vf_type i0h=0, i0l=0, i123h=0, i123l=0;
    vf_type x2h;
    vf_type kf=0;
    bool any_of_x_gt_0_75=any_of(x_gt_0_75);
    if (likely(any_of_x_gt_0_75)) {
        vf_type x2l;
        if (d_real_traits<vf_type>::fma==true) {
            d_ops::mul12(x2h, x2l, x, -x);
        } else {
            d_ops::sqr12(x2h, x2l, x);
            x2h = -x2h;
            x2l = -x2l;
        }
        vf_type xrh, xrl;
        base_type::__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
        exh= base_type::__pow_exp_poly_k(xrh, xrl, &exl);
        x2h = -x2h;
    } else {
        x2h = x*x;
    }
    if (likely(any_of(x_le_0_75))) {
        // [0, 0.75] : | p - f | <= 2^-27.6328125
        // coefficients for erfc_i0 generated by sollya
        // x^0 : +0x8p-3f
        const float erfc_i0_c0=+1.0000000000e+00f;
        // x^1 : -0x9.06ebap-3f
        const float erfc_i0_c1=-1.1283791065e+00f;
        // x^3 : +0xc.0936cp-5f
        const float erfc_i0_c3=+3.7612473965e-01f;
        // x^5 : -0xe.70f3ep-7f
        const float erfc_i0_c5=-1.1282204092e-01f;
        // x^7 : +0xd.b7cd9p-9f
        const float erfc_i0_c7=+2.6792930439e-02f;
        // x^9 : -0xa.5600fp-11f
        const float erfc_i0_c9=-5.0468514673e-03f;
        // x^11 : +0xa.643d6p-14f
        const float erfc_i0_c11=+6.3425058033e-04f;

        static const float c_i0[]={
            erfc_i0_c11,
            erfc_i0_c9,
            erfc_i0_c7,
            erfc_i0_c5,
            erfc_i0_c3
        };
        i0h = horner(x2h, c_i0);
        horner_comp_quick(i0h, i0l, x2h, i0h, erfc_i0_c1);
        d_ops::mul122(i0h, i0l, x, i0h, i0l);
        d_ops::add122(i0h, i0l, erfc_i0_c0, i0h, i0l);
    }
    if (likely(any_of_x_gt_0_75)) {
        vmf_type x_gt_2_00 = x > 2.0f;
        vmf_type x_gt_4_00 = x > 4.0f;
        vmf_type x_in_i1 = x_gt_0_75 & (x <= 2.0f);
        vmf_type x_in_i2 = x_gt_2_00 & (x <= 4.0f);
        vmf_type x_in_i3 = x_gt_4_00;
        if (likely(any_of(x_in_i1))) {
            // [0.75, 2] : | p - f | <= 2^-31.25
            // coefficients for erfc_i1 generated by sollya
            // x^0 h: +0xe.414e8p-5f
            const float erfc_i1_c0h=+4.4547200203e-01f;
            // x^0 l: -0xb.468adp-30f
            const float erfc_i1_c0l=-1.0501179482e-08f;
            // x^1 : +0x8.27b47p-6f
            const float erfc_i1_c1=+1.2742339075e-01f;
            // x^2 : -0xc.00bf2p-7f
            const float erfc_i1_c2=-9.3772783875e-02f;
            // x^3 : +0xe.93af7p-8f
            const float erfc_i1_c3=+5.6940998882e-02f;
            // x^4 : -0xf.92b5p-9f
            const float erfc_i1_c4=-3.0416160822e-02f;
            // x^5 : +0xf.1c031p-10f
            const float erfc_i1_c5=+1.4755294658e-02f;
            // x^6 : -0xd.90c9fp-11f
            const float erfc_i1_c6=-6.6238190047e-03f;
            // x^7 : +0xb.6252cp-12f
            const float erfc_i1_c7=+2.7793152258e-03f;
            // x^8 : -0x9.023b8p-13f
            const float erfc_i1_c8=-1.0996973142e-03f;
            // x^9 : +0xd.d1d37p-15f
            const float erfc_i1_c9=+4.2174171540e-04f;
            // x^10 : -0x9.c1137p-16f
            const float erfc_i1_c10=-1.4883732365e-04f;
            // x^11 : +0x8.69d27p-18f
            const float erfc_i1_c11=+3.2094449125e-05f;
            // x^ : +0xcp-4f
            // const float erfc_i1_left=+7.5000000000e-01f;
            // x^ : +0x9.05p-3f
            const float erfc_i1_x0=+1.1274414062e+00f;

            vf_type x_i1 = x - erfc_i1_x0;
            vf_type i1h, i1l;
            vf_type x_i1_sqr= x_i1* x_i1;
            static const float c[]={
                erfc_i1_c11, erfc_i1_c10, erfc_i1_c9, erfc_i1_c8,
                erfc_i1_c7, erfc_i1_c6, erfc_i1_c5,  erfc_i1_c4
            };
            i1h = horner2(x_i1, x_i1_sqr, c);
            i1h = horner(x_i1,  i1h,
                         erfc_i1_c3,
                         erfc_i1_c2,
                         erfc_i1_c1);
            i1h *= x_i1;
            d_ops::add122cond(i1h, i1l, i1h, erfc_i1_c0h, erfc_i1_c0l);
            i123h= i1h;
            i123l= i1l;
        }
        if (likely(any_of(x_in_i2))) {
            // [2, 4] : | p - f | <= 2^-34.9375
            // coefficients for erfc_i2 generated by sollya
            // x^0 h: +0x8.785dp-4f
            const float erfc_i2_c0h=+5.2938556671e-01f;
            // x^0 l: +0x8.95a12p-29f
            const float erfc_i2_c0l=+1.5989858326e-08f;
            // x^1 : +0xb.9d9b6p-9f
            const float erfc_i2_c1=+2.2686820477e-02f;
            // x^2 : -0xa.e2e3p-10f
            const float erfc_i2_c2=-1.0631129146e-02f;
            // x^3 : +0x8.baacdp-11f
            const float erfc_i2_c3=+4.2623043992e-03f;
            // x^4 : -0xc.acde6p-13f
            const float erfc_i2_c4=-1.5472739469e-03f;
            // x^5 : +0x8.8e3e9p-14f
            const float erfc_i2_c5=+5.2219495410e-04f;
            // x^6 : -0xa.e61c3p-16f
            const float erfc_i2_c6=-1.6630352184e-04f;
            // x^7 : +0xd.42d67p-18f
            const float erfc_i2_c7=+5.0587022997e-05f;
            // x^8 : -0xf.a3328p-20f
            const float erfc_i2_c8=-1.4913071936e-05f;
            // x^9 : +0x8.bca49p-21f
            const float erfc_i2_c9=+4.1660719035e-06f;
            // x^10 : -0xf.b1d4fp-24f
            const float erfc_i2_c10=-9.3547436109e-07f;
            // x^11 : +0xf.166a4p-27f
            const float erfc_i2_c11=+1.1241107245e-07f;
            // x^ : +0x8p-2f
            // const float erfc_i2_left=+2.0000000000e+00f;
            // x^ : +0xa.66p-2f
            const float erfc_i2_x0=+2.5996093750e+00f;
            vf_type x_i2 = x - erfc_i2_x0;
            vf_type i2h, i2l;
            vf_type x_i2_sqr= x_i2* x_i2;
            static const float c[]={
                erfc_i2_c11, erfc_i2_c10, erfc_i2_c9, erfc_i2_c8,
                erfc_i2_c7, erfc_i2_c6, erfc_i2_c5,  erfc_i2_c4
            };
            i2h = horner2(x_i2, x_i2_sqr, c);
            i2h = horner(x_i2, i2h,
                         erfc_i2_c3,
                         erfc_i2_c2,
                         erfc_i2_c1);
            i2h *= x_i2;
            d_ops::add122cond(i2h, i2l, i2h, erfc_i2_c0h, erfc_i2_c0l);
            i123h = _T::sel(x_gt_2_00, i2h, i123h);
            i123l = _T::sel(x_gt_2_00, i2l, i123l);
        }
        vf_type inv_x, inv_x_l;
        d_ops::rcp12(inv_x, inv_x_l, x);
        if (likely(any_of(x_in_i3))) {
            // [9.9875159561634063720703125e-2, 0.25] : | p - f | <= 2^-32.734375
            // coefficients for erfc generated by sollya
            // x^0 h: +0x9.06efp-4f
            const float erfc_i3_c0h=+5.6419277191e-01f;
            // x^0 l: +0xd.b128ep-29f
            const float erfc_i3_c0l=+2.5503393175e-08f;
            // x^1 : -0x9.af0eap-16f
            const float erfc_i3_c1=-1.4776331955e-04f;
            // x^2 : -0x8.ef53ep-5f
            const float erfc_i3_c2=-2.7921479940e-01f;
            // x^3 : -0xf.ce21p-9f
            const float erfc_i3_c3=-3.0869513750e-02f;
            // x^4 : +0x9.e892dp-4f
            const float erfc_i3_c4=+6.1928063631e-01f;
            // x^5 : -0xb.a52afp-4f
            const float erfc_i3_c5=-7.2782415152e-01f;
            // x^6 : +0x8.c5fd2p-5f
            const float erfc_i3_c6=+2.7416855097e-01f;
            vf_type inv_x2= inv_x*inv_x;
            static const float c[]={
                erfc_i3_c6,
                erfc_i3_c5, erfc_i3_c4, erfc_i3_c3, erfc_i3_c2,
                erfc_i3_c1
            };
            vf_type i3h, i3l;
            i3h = horner2(inv_x, inv_x2, c);
            i3h *= inv_x;
            d_ops::add122cond(i3h, i3l, i3h, erfc_i3_c0h, erfc_i3_c0l);
            i123h = _T::sel(x_gt_4_00, i3h, i123h);
            i123l = _T::sel(x_gt_4_00, i3l, i123l);
        }
        // multiply with e^(-x^2)
        d_ops::mul22(i123h, i123l, i123h, i123l, exh, exl);
        // divide by x
        // divide by x
        vf_type rh, rl;
        // d_ops::div212(rh, rl, i123h, i123l, x);
        d_ops::mul22(rh, rl, i123h, i123l, inv_x, inv_x_l);
        dvf_type rs=base_type::__scale_exp_k(rh, rl, kf);
        i123h = rs[0];
        i123l = rs[1];
    }
    vmf_type x_lt_0_00 = xc < 0.0f;
    vf_type ih= _T::sel(x_le_0_75, i0h, i123h);
    if (likely(any_of(x_lt_0_00))) {
        vf_type il= _T::sel(x_le_0_75, i0l, i123l);
        vf_type nih, nil;
        d_ops::add122(nih, nil, 2.0f, -ih, -il);
        ih = _T::sel(x_lt_0_00, nih, ih);
    }
    return ih;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero)
{
    // G(z+1) = z * G(z)
    // G(z) * G(1-z) = pi/sin(pi*z)
    // with G(-z+1) = -z * G(z)
    // G(z) * -z * G(-z) = pi/sin(pi*z)
    // G(-z) = -pi/[sin(pi*z)*z * G(z)]
    // lanczos sum:
    vf_type xa=abs(x);
    using lanczos_ratfunc=lanczos_table_g_5_59172_N6;

    auto pq=lanczos_rational_at(xa,
                                lanczos_ratfunc::pdf,
                                lanczos_ratfunc::qf);
    vf_type sum = pq[0], sum_l= pq[1];
    // base of the Lanczos exponential
    vf_type base, base_l;
    d_ops::add122cond(base, base_l, xa,
                      lanczos_ratfunc::gm0_5f(),
                      lanczos_ratfunc::gm0_5f_l());
    vf_type zh, zl;
    d_ops::add12cond(zh, zl, xa,  -0.5);
    vf_type gh, gl;
    base_type::exp_k2(gh, gl, -base, -base_l);
    d_ops::mul22(gh, gl, gh, gl, sum, sum_l);
    if (any_of(x_lt_zero)) {
        dvf_type s;
        sinpi_cospi_k(xa, &s, nullptr);
        // vf_type r_n = -M_PI/(s * x0 * r);
        using ctbl = impl::d_real_constants<d_real<float>, float>;
        const dvf_type p=-ctbl::m_pi;
        // dvf_type q=s * (xa *dvf_type(gh, gl));
        dvf_type q;
        d_ops::mul122(q[0], q[1], xa, gh, gl);
        d_ops::mul22(q[0], q[1], q[0], q[1], s[0], s[1]);
        dvf_type g_n;
        d_ops::div22(g_n[0], g_n[1], p[0], p[1], q[0], q[1]);
        gh = _T::sel(x_lt_zero, g_n[0], gh);
        gl = _T::sel(x_lt_zero, g_n[1], gl);
        zh = _T::sel(x_lt_zero, -zh, zh);
        zl = _T::sel(x_lt_zero, -zl, zl);
    }
    auto p_sc=base_type::pow_k2(base, base_l, 0.5*zh, 0.5*zl);
    const dvf_type& powh= p_sc.first;
    d_ops::mul22(gh, gl, powh[0], powh[1], gh, gl);
    d_ops::mul22(gh, gl, powh[0], powh[1], gh, gl);
    const auto& sc=p_sc.second;
    gh *= sc.f0();
    gh *= sc.f1();
    gh *= sc.f0();
    gh *= sc.f1();
    gh = _T::sel(xa < 0x1p-24f, 1.0f/x, gh);
    return gh;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::dvf_type
cftal::math::spec_func_core<float, _T>::
__lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    // [1, 2] : | p - f | <= 2^-37.5625
    // coefficients for lngamma generated by sollya
    // x^0 h: +0xb.ebb41p-3f
    const float lngamma_i0_c0h=+1.4900895357e+00f;
    // x^0 l: -0xf.defcp-30f
    const float lngamma_i0_c0l=-1.4781051050e-08f;
    // x^1 h: -0xd.9075ep-2f
    const float lngamma_i0_c1h=-3.3910746574e+00f;
    // x^1 l: -0x9.48f64p-28f
    const float lngamma_i0_c1l=-3.4589348274e-08f;
    // x^2 h: +0xf.a3adfp-1f
    const float lngamma_i0_c2h=+7.8196864128e+00f;
    // x^2 l: -0xf.5d0cp-31f
    const float lngamma_i0_c2l=-7.1541705893e-09f;
    // x^3 : -0xd.c53fbp+0f
    const float lngamma_i0_c3=-1.3770503044e+01f;
    // x^4 : +0x9.21191p+1f
    const float lngamma_i0_c4=+1.8258577347e+01f;
    // x^5 : -0x9.34e94p+1f
    const float lngamma_i0_c5=-1.8413368225e+01f;
    // x^6 : +0xe.3b191p+0f
    const float lngamma_i0_c6=+1.4230851173e+01f;
    // x^7 : -0x8.6fd94p+0f
    const float lngamma_i0_c7=-8.4369087219e+00f;
    // x^8 : +0xf.3dd53p-2f
    const float lngamma_i0_c8=+3.8103835583e+00f;
    // x^9 : -0xa.4fabbp-3f
    const float lngamma_i0_c9=-1.2889016867e+00f;
    // x^10 : +0xa.20029p-5f
    const float lngamma_i0_c10=+3.1640747190e-01f;
    // x^11 : -0xd.a28ebp-8f
    const float lngamma_i0_c11=-5.3261678666e-02f;
    // x^12 : +0xb.4438dp-11f
    const float lngamma_i0_c12=+5.5012167431e-03f;
    // x^13 : -0x8.9e09ep-15f
    const float lngamma_i0_c13=-2.6298029115e-04f;
    const static float ci[]= {
        lngamma_i0_c13,
        lngamma_i0_c12,
        lngamma_i0_c11,
        lngamma_i0_c10,
        lngamma_i0_c9,
        lngamma_i0_c8,
        lngamma_i0_c7,
        lngamma_i0_c6,
        lngamma_i0_c5,
        lngamma_i0_c4,
        lngamma_i0_c3
    };
    vf_type ph, pl;
    d_ops::mul122(ph, pl, ci[0], xh, xl);
    const std::size_t N=std::distance(std::cbegin(ci), std::cend(ci));
#pragma GCC unroll 0
#pragma clang loop unroll(disable)
    for (std::size_t i=1; i<N; ++i) {
        d_ops::add122(ph, pl, ci[i], ph, pl);
        d_ops::mul22(ph, pl, xh, xl, ph, pl);
    }
    d_ops::add22(ph, pl, ph, pl, lngamma_i0_c2h, lngamma_i0_c2l);
    d_ops::mul22(ph, pl, xh, xl, ph, pl);
    d_ops::add22(ph, pl, ph, pl, lngamma_i0_c1h, lngamma_i0_c1l);
    d_ops::mul22(ph, pl, xh, xl, ph, pl);
    d_ops::add22(ph, pl, ph, pl, lngamma_i0_c0h, lngamma_i0_c0l);
    vf_type xm1h, xm1l;
    d_ops::add212(xm1h, xm1l, xh, xl, -1.0);
    vf_type xm2h, xm2l;
    d_ops::add122(xm2h, xm2l, -2.0, xh, xl);
    vf_type th, tl;
    d_ops::mul22(th, tl, xm1h, xm1l, xm2h, xm2l);
    d_ops::mul22(th, tl, ph, pl, th, tl);
    return dvf_type(th, tl);
}


template <typename _T>
typename cftal::math::spec_func_core<float, _T>::reduced_small_gamma_args
cftal::math::spec_func_core<float, _T>::
__lgamma_reduce_small_k(arg_t<vf_type> xc)
{
    dvf_type x=xc;
    dvf_type f0=vf_type(1.0f);
    vf_type f1(1.0f);
    vmf_type t;

    const float il=1.0f;
    const float ir=2.0f;

    if (any_of(t= x[0]>vf_type(ir))) {
        // x -= _T::sel(t, 1.0f, 0.0f);
        // dvf_type p= select(t, x, dvf_type(1.0f));
        x -= _T::sel(t, 1.0f, 0.0f);
        f0[0]=_T::sel(t, x[0], 1.0f);
        while (any_of(t= x[0]>vf_type(ir))) {
            // x -= _T::sel(t, 1.0f, 0.0f);
            // dvf_type p= select(t, x, dvf_type(1.0f));
            x -= _T::sel(t, 1.0f, 0.0f);
#if 0
            dvf_type p= select(t, x, dvf_type(1.0f));
            f0 *= p;
#else
            vf_type p= select(t, x[0], vf_type(1.0f));
            // f *= p;
            // d_ops::mul122(f0[0], f0[1], p, f0[0], f0[1]);
            // compensated product:
            vf_type pl;
            d_ops::mul12(f0[0], pl, f0[0], p);
            f0[1] = f0[1] * p + pl;
#endif
#if 0
            // avoid overflows in f0
            if (any_of(t=f0[0] > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                f0[1] *= h;
                f0[0] *= h;
                f1 *= _T::sel(t, 0x1p61f, 1.0f);
            }
#endif
        }
    }

    if (any_of(t= x[0]<vf_type(il))) {
        dvf_type q0(_T::sel(t, x[0], 1.0f), vf_type(0.0f));
        x += _T::sel(t, 1.0f, 0.0f);
        // see below
        while(any_of(t= x[0]<vf_type(-1.0f))) {
#if 0
            dvf_type q= select(t, x, dvf_type(1.0f));
            q0 *= q;
#else
            vf_type q= _T::sel(t, x[0], vf_type(1.0f));
            // q0 *= q;
            // d_ops::mul122(q0[0], q0[1], q, q0[0], q0[1]);
            vf_type pl;
            d_ops::mul12(q0[0], pl, q0[0], q);
            q0[1] = q0[1] * q + pl;
#endif
            x += _T::sel(t, 1.0f, 0.0f);
#if 0
            // avoid overflows in q0
            if (any_of(t=abs(q0[0]) > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                q0[1] *= h;
                q0[0] *= h;
                // we divide by f1
                f1 *= h;
            }
#endif
        }
        // the range between -1 and 1 must be handled more precise
        while(any_of(t= x[0]<vf_type(il))) {
            dvf_type q= select(t, x, dvf_type(1.0f));
            q0 *= q;
            x += _T::sel(t, 1.0f, 0.0f);
        }
        // f0 /= q0;
        f0 = d_ops::sloppy_div(f0, q0);
    }
    return reduced_small_gamma_args{x, f0};
}


template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
lgamma_k(arg_t<vf_type> xc, vi_type* signp)
{
    vf_type xa=abs(xc);
    constexpr const float x_tiny= 0x1p-25f;
    constexpr const float x_small_delta = 6.0f;
    constexpr const float x_small_left  = 1.0f-x_small_delta;
    constexpr const float x_small_right = 2.0f+x_small_delta;
    constexpr const float x_large= 0x1p25f;

    reduced_small_gamma_args sst;

    // the reflection implementation below works only if the
    // reflection for really tiny values delegated to __lgamma_small_k
    static_assert(x_small_left < - x_tiny, "constraint violated");
    vmf_type xa_in_small =
        ((xc >= x_small_left) & (xc <= x_small_right) & (xa >= x_tiny));

    vf_type base_h=xa, base_l=0.0f;
    if (any_of(xa_in_small)) {
        vf_type xs=_T::sel(xa_in_small, xc, 1.5f);
        sst = __lgamma_reduce_small_k(xs);
        dvf_type log_a=select(sst._f[0]>0, sst._f, -sst._f);
        base_h = _T::sel(xa_in_small, log_a[0], base_h);
        base_l = _T::sel(xa_in_small, log_a[1], base_l);
    }

    using lanczos_ratfunc = lanczos_table_g_5_59172_N6;
    vmf_type xa_in_lanczos =
        (((xc < x_small_left) | (xc > x_small_right)) & (xa < x_large));
    if (any_of(xa_in_lanczos)) {
        vf_type th, tl;
        d_ops::add122cond(th, tl, xa,
                          lanczos_ratfunc::gm0_5f(),
                          lanczos_ratfunc::gm0_5f_l());
        base_h= _T::sel(xa_in_lanczos, th, base_h);
        base_l= _T::sel(xa_in_lanczos, tl, base_l);
    }
    // lb contains log(xa+g-0.5) for xa_in_lanczos
    // log(xa) for xa > x_large | xa < x_tiny
    // log(f) for xa < x_small & xa >= tiny
    dvf_type lb= base_type::template
        __pow_log_k2<base_type::log_func::c_log_e,
                     base_type::result_prec::high>(base_h, base_l);

    vf_type lgh=0.0f, lgl=0.0f;
    vmf_type xa_in_large = (xa >= x_large);
    if (any_of(xa_in_large)) {
        // log(gamma(x)) = xa * (log(xa) - 1.0), xa >> 1
        vf_type th, tl;
        d_ops::add212(th, tl, lb[0], lb[1], -1.0f);
        d_ops::mul122(th, tl, xa, th, tl);
        lgh = _T::sel(xa_in_large, th, lgh);
        lgl = _T::sel(xa_in_large, tl, lgl);
    }
    if (any_of(xa_in_lanczos)) {
        // lanczos sum:
        auto pq=lanczos_rational_at(xa,
                                    lanczos_ratfunc::pdf,
                                    lanczos_ratfunc::qf);

        vf_type sum_h = pq[0], sum_l= pq[1];
        vf_type zh, zl;
        d_ops::add12cond(zh, zl, xa,  -0.5f);

        // g = z * log(base) + log(sum) - base;
        dvf_type ls=base_type::template
            __pow_log_k2<base_type::log_func::c_log_e,
                         base_type::result_prec::high>(sum_h, sum_l);
        vf_type th, tl;
        d_ops::mul22(th, tl, zh, zl, lb[0], lb[1]);
        d_ops::add22cond(th, tl, th, tl, -base_h, -base_l);
        d_ops::add22cond(th, tl, th, tl, ls[0], ls[1]);
        lgh = _T::sel(xa_in_lanczos, th, lgh);
        lgl = _T::sel(xa_in_lanczos, tl, lgl);
    }
    if (any_of(xa_in_small)) {
        dvf_type lg12=__lgamma_1_2_k(sst._xr[0], sst._xr[1]);
        vf_type th, tl;
        d_ops::add22cond(th, tl, lb[0], lb[1], lg12[0], lg12[1]);
        lgh = _T::sel(xa_in_small, th, lgh);
        lgl = _T::sel(xa_in_small, tl, lgl);
    }
    // xa_in_tiny:
    vmf_type xa_in_tiny= xa < x_tiny;
    lgh = _T::sel(xa_in_tiny, -lb[0], lgh);

    // reflection part
    vi_type sgn=1;
    vmf_type x_lt_0 = xc < 0.0f;
    if (any_of(x_lt_0)) {
        // tiny
        vmf_type t= x_lt_0 & xa_in_tiny;
        sgn = _T::sel(_T::vmf_to_vmi(t), -1, sgn);
        // small
        t = x_lt_0 & xa_in_small;
        if (any_of(t)) {
            vf_type sgn_g=copysign(vf_type(1.0f), sst._f[0]);
            vi_type si= _T::cvt_f_to_i(sgn_g);
            sgn=_T::sel(_T::vmf_to_vmi(t), si, sgn);
        }
        // lanczos
        t = x_lt_0 & xa_in_lanczos;
        if (any_of(t)) {
            // G(-z) = -pi/[sin(pi*z)*z * G(z)]
            dvf_type s;
            sinpi_cospi_k(xa, &s, nullptr);
            using ctbl = impl::d_real_constants<d_real<float>, float>;
            // log(G(-z)) = log(pi) - log(z) - log(abs(sin(pi*z))-log(G(z))
            //            = log(pi) - log(abs(sin(pi*z)*z) - log(G(z))
            //            = log(pi) - [log(abs(sin(pi*z)*z) + log(G(z))]
            dvf_type sa= select(s[0] < 0.0f, -s, s);
            d_ops::mul122(sa[0], sa[1], xa, sa[0], sa[1]);
            dvf_type lg_n=base_type::template
                __pow_log_k2<base_type::log_func::c_log_e,
                             base_type::result_prec::high>(sa[0], sa[1]);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             lg_n[0], lg_n[1],
                             lgh, lgl);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             ctbl::m_ln_pi[0], ctbl::m_ln_pi[1],
                             -lg_n[0], -lg_n[1]);
            lgh = _T::sel(t, lg_n[0], lgh);
            vmf_type s_lt_0 = (s[0] >= 0.0f) & t;
            vmi_type i_s_lt_0 = _T::vmf_to_vmi(s_lt_0);
            sgn = _T::sel(i_s_lt_0, -1, sgn);
        }
        // no large handling because xc is integer anyway
    }
    if (signp != nullptr)
        *signp = sgn;
    return lgh;
}

// Local Variables:
// mode: c++
// end:
#endif
