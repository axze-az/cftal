//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F32_H__)
#define __CFTAL_MATH_SPEC_FUNC_CORE_F32_H__ 1

#include <cftal/config.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_wrapper_f32.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/lanczos.h>
#include <cftal/math/horner_idx.h>
#if  __CFTAL_CFG_USE_VF64_FOR_VF32__ > 0
#include <cftal/math/spec_func_core_f64.h>
#endif
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
            using vdf_type = typename _T::vdf_type;

            using d_ops= typename base_type::d_ops;
#if __CFTAL_CFG_USE_VF64_FOR_VF32__ > 0
            using f64_traits = typename _T::vhf_traits;
            using vhf_type = typename f64_traits::vf_type;
            using vmhf_type = typename f64_traits::vmf_type;
            using vi2_type = typename f64_traits::vi2_type;
            using vmi2_type = typename f64_traits::vmi2_type;

            using f64_core = spec_func_core<double, f64_traits>;
#endif

            using base_type::sinpi_cospi_k;
            static
            void
            sinpi_cospi_k(arg_t<vf_type> xc,
                          vdf_type* ps, vdf_type *pc);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_tbl_k(arg_t<vf_type> x);

            static
            vf_type
            tgamma_k(arg_t<vf_type> xc, arg_t<vmf_type> xc_lt_0);

#if __CFTAL_CFG_USE_VF64_FOR_VF32__>0
            // calculates lngamma for x in [1, 2]
            static
            vhf_type
            __lgamma_1_2_k(arg_t<vhf_type> x);

            // returns _xr in the range [1, 2]
            // returns _f (including sign)= (x+N)(x+_N-1)...(x-1)(x-2)
            // returns _inv_f as true if f must be inverted or false if not
            // lgamma(x) = lgamma(xr) * log(abs(_f))
            struct reduced_small_gamma_args_vhf {
                vhf_type _xr, _f;
                vmhf_type _inv_f;
                reduced_small_gamma_args_vhf() : _xr(), _f(), _inv_f() {}
                reduced_small_gamma_args_vhf(const vhf_type& xr,
                                             const vhf_type& f,
                                             const vmhf_type& inv_f)
                    : _xr(xr), _f(f), _inv_f(inv_f) {}
            };

            static
            reduced_small_gamma_args_vhf
            __lgamma_reduce_small_k(arg_t<vhf_type> x);
#endif
            // calculates lngamma for x in [1, 2]
            static
            vdf_type
            __lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates lngamma for x in [1, 2] using tables
            static
            vdf_type
            __lgamma_1_2_tbl_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // returns _xr in the range [1, 2]
            // returns _f (including sign)= (x+N)(x+_N-1)...(x-1)(x-2)
            // returns _inv_f as true if f must be inverted or false if not
            // lgamma(x) = lgamma(xr) +- log(abs(_f))
            struct reduced_small_gamma_args {
                vdf_type _xr, _f;
                vmf_type _inv_f;
                reduced_small_gamma_args() : _xr(), _f(), _inv_f() {}
                reduced_small_gamma_args(const vdf_type& xr,
                                         const vdf_type& f,
                                         const vmf_type& inv_f)
                    : _xr(xr), _f(f), _inv_f(inv_f) {};
            };
            static
            reduced_small_gamma_args
            __lgamma_reduce_small_k(arg_t<vf_type> x);

            static
            vf_type
            lgamma_k(arg_t<vf_type> xc, vi_type* signp);

            static
            vdf_type
            rsqrt12_k(arg_t<vf_type> xc);

            static
            void
            __check_tbl_idx(arg_t<vi_type> idx,
                            arg_t<vf_type> xb,
                            const float* t,
                            int32_t span);

            // handle small arguments up to ~64
            static
            vf_type
            __j01y01_small_tbl_k(arg_t<vf_type> xc,
                                 const float tb[j01y01_data<float>::ENTRIES],
                                 float max_small_x);

            static
            vi_type
            __reduce_trig_arg(vf_type& xrh, vf_type& xrm, vf_type& xrl,
                              arg_t<vf_type> x);

            static
            vi_type
            __reduce_trig_arg_tiny(vf_type& xrh, vf_type& xrl,
                                   arg_t<vf_type> xh,
                                   arg_t<vf_type> xl);

            // handle the interval [0, 4.75]
            static
            vf_type
            __y0_singular_k(arg_t<vf_type> xc);

            // xr2 square of reciprocal
            // xr reciprocal
            static
            vdf_type
            __j0y0_phase_corr_k(arg_t<vf_type> xr2h,
                                arg_t<vf_type> xr2l,
                                arg_t<vf_type> xrh,
                                arg_t<vf_type> xrl);

            // xr2 square of reciprocal
            static
            vdf_type
            __j0y0_amplitude_corr_k(arg_t<vf_type> xr2,
                                    arg_t<vf_type> xr2l);

            // handle the interval [0, 4.75]
            static
            vf_type
            __y1_singular_k(arg_t<vf_type> xc);

            // xr2 square of reciprocal
            // xr reciprocal
            static
            vdf_type
            __j1y1_phase_corr_k(arg_t<vf_type> xr2h,
                                arg_t<vf_type> xr2l,
                                arg_t<vf_type> xrh,
                                arg_t<vf_type> xrl);

            // xr2 square of reciprocal
            static
            vdf_type
            __j1y1_amplitude_corr_k(arg_t<vf_type> xr2,
                                    arg_t<vf_type> xr2l);


            // handle large arguments greater than ~128 to inf
            // calc_y01 select the calculation of y0/y1 or j0/j1
            // calc_j01 selects j0/y0 or j1/y1
            static
            vf_type
            __j01y01_large_phase_amplitude_k(arg_t<vf_type> xc,
                                             bool calc_y01,
                                             bool calc_jy1);

            static
            vf_type
            j0_k(arg_t<vf_type> xc);

            static
            vf_type
            j1_k(arg_t<vf_type> xc);

            static
            vf_type
            y0_k(arg_t<vf_type> xc);

            static
            vf_type
            y1_k(arg_t<vf_type> xc);
        };

    }
}

template <typename _T>
void
cftal::math::spec_func_core<float, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, vdf_type* ps, vdf_type* pc)
{
    vf_type xrh, xrl;
    auto q=base_type::__reduce_trigpi_arg(xrh, xrl, xc);
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
    if (__likely(_T::any_of_vmf(x_in_i0))) {
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
    if (__likely(_T::any_of_vmf(x_in_i1))) {
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
    if (__likely(_T::any_of_vmf(x_in_i2))) {
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
    if (__likely(_T::any_of_vmf(x_in_i3))) {
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
    vi_type k=0;
    bool any_of_x_gt_0_75=_T::any_of_vmf(x_gt_0_75);
    if (__likely(any_of_x_gt_0_75)) {
        vf_type x2l;
        if (d_real_traits<vf_type>::fma==true) {
            d_ops::mul12(x2h, x2l, x, -x);
        } else {
            d_ops::sqr12(x2h, x2l, x);
            x2h = -x2h;
            x2l = -x2l;
        }
        vf_type xrh, xrl;
        vi_type idx;
        base_type::__reduce_exp_arg(xrh, xrl, idx, k, x2h, x2l);
        exh=base_type::template
            __exp_tbl_k<base_type::result_prec::medium>(xrh, xrl, idx, &exl);
        x2h = -x2h;
    } else {
        x2h = x*x;
    }
    if (__likely(_T::any_of_vmf(x_le_0_75))) {
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
    if (__likely(any_of_x_gt_0_75)) {
        vmf_type x_gt_2_00 = x > 2.0f;
        vmf_type x_gt_4_00 = x > 4.0f;
        vmf_type x_in_i1 = x_gt_0_75 & (x <= 2.0f);
        vmf_type x_in_i2 = x_gt_2_00 & (x <= 4.0f);
        vmf_type x_in_i3 = x_gt_4_00;
        if (__likely(_T::any_of_vmf(x_in_i1))) {
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
        if (__likely(_T::any_of_vmf(x_in_i2))) {
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
        if (__likely(_T::any_of_vmf(x_in_i3))) {
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
        auto sc=base_type::__two_pow(k);
        rh *= sc.f0();
        rl *= sc.f0();
        rh *= sc.f1();
        rl *= sc.f1();
        i123h = rh;
        i123l = rl;
    }
    vmf_type x_lt_0_00 = xc < 0.0f;
    vf_type ih= _T::sel(x_le_0_75, i0h, i123h);
    if (__likely(_T::any_of_vmf(x_lt_0_00))) {
        vf_type il= _T::sel(x_le_0_75, i0l, i123l);
        vf_type nih, nil;
        d_ops::add122(nih, nil, 2.0f, -ih, -il);
        ih = _T::sel(x_lt_0_00, nih, ih);
    }
    return ih;
}

template <typename _T>
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
erfc_tbl_k(arg_t<vf_type> xc)
{
    // erfc(-x) = 2 - erfc(x)

    vf_type x= abs(xc);

    vf_type x2h, x2l;

    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, x, -x);
    } else {
        d_ops::sqr12(x2h, x2l, x);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type xrh, xrl;
    vi_type eidx, k;
    base_type::__reduce_exp_arg(xrh, xrl, eidx, k, x2h, x2l);

    using erfc_table=erfc_data<float>;
#if 0
    vf_type xi= rint(vf_type(x * erfc_table::SCALE));
    vf_type xi0= xi*erfc_table::INV_SCALE;
    vi_type idx= _T::cvt_f_to_i(xi);
#else
    vf_type xscale=x * erfc_table::SCALE;
    vf_type xi= rint(xscale);
    vi_type idx= _T::cvt_f_to_i(xscale);
    vf_type xi0= xi*erfc_table::INV_SCALE;
#endif
    idx = max(min(idx, vi_type(erfc_table::COUNT-1)), vi_type(0));

    vf_type exl, exh=base_type::template __exp_tbl_k<
        base_type::result_prec::medium>(xrh, xrl, eidx, &exl);

    // vi_type idxs = idx * (erfc_table::ENTRIES + 2) = idx * 7
    vi_type idx8= idx << 3;
    vi_type idxs = idx8 - idx;
    vf_type xr=x - xi0;
    vf_type xr2=xr*xr;
    auto lck=make_variable_lookup_table<float>(idxs);
    const float* pt=erfc_table::_tbl;
    vf_type i=horner2_idx<erfc_table::POLY_ORDER-1>(xr, xr2, lck, pt);
    vf_type c1=lck.from(pt+erfc_table::POLY_ORDER-1);
    i = horner(xr, i, c1);
    vf_type c0h=lck.from(pt+erfc_table::POLY_ORDER);
    vf_type c0l=lck.from(pt+erfc_table::POLY_ORDER+1);
    i *= xr;
    vf_type ih, il;
    d_ops::add212cond(ih, il, c0h, c0l, i);
    d_ops::mul22(ih, il, ih, il, exh, exl);
    auto sc=base_type::__two_pow(k);
    ih *= sc.f0();
    ih *= sc.f1();
    vmf_type x_lt_0_00 = xc < 0.0f;
    if (__likely(_T::any_of_vmf(x_lt_0_00))) {
        il *= sc.f0();
        il *= sc.f1();
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
    // using lanczos_ratfunc=lanczos_table_g_5_59172_N6;
    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
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
    d_ops::add12cond(zh, zl, xa,  -0.5f);
    vf_type gh, gl;
    base_type::exp_k2(gh, gl, -base, -base_l);
    d_ops::mul22(gh, gl, gh, gl, sum, sum_l);
    if (_T::any_of_vmf(x_lt_zero)) {
        vdf_type s;
        sinpi_cospi_k(xa, &s, nullptr);
        // vf_type r_n = -M_PI/(s * x0 * r);
        using ctbl = impl::d_real_constants<d_real<float>, float>;
        const vdf_type p=-ctbl::m_pi;
        // vdf_type q=s * (xa *vdf_type(gh, gl));
        vdf_type q;
        d_ops::mul122(q[0], q[1], xa, gh, gl);
        d_ops::mul22(q[0], q[1], q[0], q[1], s[0], s[1]);
        vdf_type g_n;
        d_ops::div22(g_n[0], g_n[1], p[0], p[1], q[0], q[1]);
        gh = _T::sel(x_lt_zero, g_n[0], gh);
        gl = _T::sel(x_lt_zero, g_n[1], gl);
        zh = _T::sel(x_lt_zero, -zh, zh);
        zl = _T::sel(x_lt_zero, -zl, zl);
    }
    auto p_sc=base_type::pow_k2(base, base_l, zh, zl);
    const vdf_type& powh= p_sc.first;
    d_ops::mul22(gh, gl, powh[0], powh[1], gh, gl);
    const auto& sc=p_sc.second;
    gh *= sc.f0();
    gh *= sc.f1();
    gh = _T::sel(xa < 0x1p-24f, 1.0f/x, gh);
    return gh;
}

#if __CFTAL_CFG_USE_VF64_FOR_VF32__>0
template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vhf_type
cftal::math::spec_func_core<float, _T>::
__lgamma_1_2_k(arg_t<vhf_type> x)
{
    // [1, 2] : | p - f | <= 2^-44.625
    // coefficients for lngamma generated by sollya
    // x^0 : +0xc.65fa47157d3p-3
    const double lngamma_i0_c0=+1.5497937730248381171805e+00;
    // x^1 : -0x8.0120723c45688p-1
    const double lngamma_i0_c1=-4.0022006701062347033826e+00;
    // x^2 : +0xa.b9220e753328p+0
    const double lngamma_i0_c2=+1.0723175910580863501309e+01;
    // x^3 : -0xb.21b402b99bb8p+1
    const double lngamma_i0_c3=-2.2263305988911668009678e+01;
    // x^4 : +0x8.d7189418c7bd8p+2
    const double lngamma_i0_c4=+3.5360875152778099561601e+01;
    // x^5 : -0xa.e1a2d09217d3p+2
    const double lngamma_i0_c5=-4.3525562422436721021768e+01;
    // x^6 : +0xa.8034c8c5ec3f8p+2
    const double lngamma_i0_c6=+4.2003221696170832899497e+01;
    // x^7 : -0xf.febafbf585048p+1
    const double lngamma_i0_c7=-3.1990081305391900201585e+01;
    // x^8 : +0x9.a03a8b3dcf95p+1
    const double lngamma_i0_c8=+1.9251786618405425599576e+01;
    // x^9 : -0x9.1cfe979a2427p+0
    const double lngamma_i0_c9=-9.1132597686120355717776e+00;
    // x^10 : +0xd.6ba1913f6079p-2
    const double lngamma_i0_c10=+3.3551085181171567128899e+00;
    // x^11 : -0xf.0f946b29879ap-4
    const double lngamma_i0_c11=-9.4130365238422664120321e-01;
    // x^12 : +0xc.7290f9838dc18p-6
    const double lngamma_i0_c12=+1.9449257246580139990577e-01;
    // x^13 : -0xe.499235246b9b8p-9
    const double lngamma_i0_c13=-2.7905053126423964154901e-02;
    // x^14 : +0xa.2c3621af382dp-12
    const double lngamma_i0_c14=+2.4835695757712663092609e-03;
    // x^15 : -0xd.89ad867d65478p-17
    const double lngamma_i0_c15=-1.0328524808293270754230e-04;
    static const double ci[]={
        lngamma_i0_c15,
        lngamma_i0_c14,
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
        lngamma_i0_c3,
        lngamma_i0_c2,
        lngamma_i0_c1,
        lngamma_i0_c0
    };
    vhf_type p=horner(x, ci);
    p= p * ((x-1.0) * (x-2.0));
    return p;
}

template <typename _T>
typename cftal::math::spec_func_core<float, _T>::reduced_small_gamma_args_vhf
cftal::math::spec_func_core<float, _T>::
__lgamma_reduce_small_k(arg_t<vhf_type> xc)
{
    vhf_type x=xc;
    vhf_type f0=1.0;
    const double il=1.0;
    const double ir=2.0;

    auto t= x>vhf_type(ir);

    if (_T::vhf_traits::any_of_vmf(t)) {
        x -= f64_traits::sel_val_or_zero(t, 1.0);
        f0= f64_traits::sel(t, x, 1.0);
        while (_T::vhf_traits::any_of_vmf(t= x>vhf_type(ir))) {
            x -= f64_traits::sel_val_or_zero(t, 1.0);
            f0 *= f64_traits::sel(t, x, vhf_type(1.0));
#if 0
            // avoid overflows in f0
            if (_T::any_of_vmf(t=f0[0] > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                f0[1] *= h;
                f0[0] *= h;
                f1 *= _T::sel(t, 0x1p61f, 1.0f);
            }
#endif
        }
    }
    t= x<vhf_type(il);
    vmhf_type inv_f=t;
    if (_T::vhf_traits::any_of_vmf(t)) {
        vhf_type& q0 = f0;
        q0=f64_traits::sel(t, x, q0);
        x += f64_traits::sel_val_or_zero(t, 1.0);
        while(_T::vhf_traits::any_of_vmf(t= x<vhf_type(il))) {
            q0 *= f64_traits::sel(t, x, 1.0);
            x += f64_traits::sel_val_or_zero(t, 1.0);
#if 0
            // avoid overflows in q0
            if (_T::vhf_traits::any_of_vmf(t=abs(q0[0]) > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                q0[1] *= h;
                q0[0] *= h;
                // we divide by f1
                f1 *= h;
            }
#endif
        }
        // f0 /= q0;
        // f0 = f0/q0;
    }
    return reduced_small_gamma_args_vhf{x, f0, inv_f};
}

#endif

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
__lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    // [1, 2] : | p - f | <= 2^-44.015625
    // coefficients for lngamma generated by sollya
    // x^0 h: +0xc.6534fp-3f
    const float lngamma_i0_c0h=+1.5494173765e+00f;
    // x^0 l: -0xd.65143p-28f
    const float lngamma_i0_c0l=-4.9899664845e-08f;
    // x^1 h: -0xf.fe3bp-2f
    const float lngamma_i0_c1h=-3.9982719421e+00f;
    // x^1 l: -0xe.211bep-27f
    const float lngamma_i0_c1l=-1.0527172378e-07f;
    // x^2 h: +0xa.b441fp+0f
    const float lngamma_i0_c2h=+1.0704131126e+01f;
    // x^2 l: -0xe.0975p-27f
    const float lngamma_i0_c2l=-1.0458336419e-07f;
    // x^3 h: -0xb.1a6bep+1f
    const float lngamma_i0_c3h=-2.2206417084e+01f;
    // x^3 l: -0xd.57df2p-24f
    const float lngamma_i0_c3l=-7.9531957908e-07f;
    // x^4 h: +0x8.cf9a2p+2f
    const float lngamma_i0_c4h=+3.5243782043e+01f;
    // x^4 l: -0xb.019d4p-25f
    const float lngamma_i0_c4l=-3.2801347061e-07f;
    // x^5 h: -0xa.d660ap+2f
    const float lngamma_i0_c5h=-4.3349647522e+01f;
    // x^5 l: +0xd.3affp-26f
    const float lngamma_i0_c5l=+1.9714912014e-07f;
    // x^6 h: +0xa.7373ep+2f
    const float lngamma_i0_c6h=+4.1803947449e+01f;
    // x^6 l: +0xa.7ce78p-23f
    const float lngamma_i0_c6l=+1.2502559912e-06f;
    // x^7 : -0xf.e88bep+1f
    const float lngamma_i0_c7=-3.1816768646e+01f;
    // x^8 : +0x9.914b2p+1f
    const float lngamma_i0_c8=+1.9135105133e+01f;
    // x^9 : -0x9.0d6d8p+0f
    const float lngamma_i0_c9=-9.0524520874e+00f;
    // x^10 : +0xd.52b7bp-2f
    const float lngamma_i0_c10=+3.3307788372e+00f;
    // x^11 : -0xe.f1847p-4f
    const float lngamma_i0_c11=-9.3396419287e-01f;
    // x^12 : +0xc.58176p-6f
    const float lngamma_i0_c12=+1.9287666678e-01f;
    // x^13 : -0xe.29712p-9f
    const float lngamma_i0_c13=-2.7659926564e-02f;
    // x^14 : +0xa.14307p-12f
    const float lngamma_i0_c14=+2.4606601801e-03f;
    // x^15 : -0xd.684f8p-17f
    const float lngamma_i0_c15=-1.0229082545e-04f;
    static const float ci[]={
        lngamma_i0_c15,
        lngamma_i0_c14,
        lngamma_i0_c13,
        lngamma_i0_c12,
        lngamma_i0_c11,
        lngamma_i0_c10,
        lngamma_i0_c9,
        lngamma_i0_c8,
        lngamma_i0_c7
    };
    constexpr
    const std::size_t N0=std::distance(std::cbegin(ci), std::cend(ci));
    const float* pci=ci;
    vf_type ph, pl;
    d_ops::unorm_mul122(ph, pl, pci[0], xh, xl);
#pragma clang unroll(1)
#pragma GCC unroll 1
    for (std::size_t i=1; i<N0; ++i) {
        d_ops::add122(ph, pl, pci[i], ph, pl);
        d_ops::unorm_mul22(ph, pl, xh, xl, ph, pl);
    }
    static const d_real<float> dci[]={
        {lngamma_i0_c6h, lngamma_i0_c6l},
        {lngamma_i0_c5h, lngamma_i0_c5l},
        {lngamma_i0_c4h, lngamma_i0_c4l},
        {lngamma_i0_c3h, lngamma_i0_c3l},
        {lngamma_i0_c2h, lngamma_i0_c2l},
        {lngamma_i0_c1h, lngamma_i0_c1l}
    };
    constexpr
    const std::size_t N1=std::distance(std::cbegin(dci), std::cend(dci));
    const d_real<float>* pdci=dci;
#pragma clang unroll(1)
#pragma GCC unroll 1
    for (std::size_t i=0; i<N1; ++i) {
        vf_type ch=mem<vf_type>::load(&(pdci[i][0]), 1);
        vf_type cl=mem<vf_type>::load(&(pdci[i][1]), 1);
        d_ops::add22(ph, pl, ch, cl, ph, pl);
        d_ops::unorm_mul22(ph, pl, xh, xl, ph, pl);
    }
    d_ops::add22(ph, pl, lngamma_i0_c0h, lngamma_i0_c0l, ph, pl);
    vf_type xm1h, xm1l;
    d_ops::add212(xm1h, xm1l, xh, xl, -1.0f);
    vf_type xm2h, xm2l;
    d_ops::add122(xm2h, xm2l, -2.0f, xh, xl);
    vf_type th, tl;
    d_ops::mul22(th, tl, xm1h, xm1l, xm2h, xm2l);
    d_ops::mul22(th, tl, ph, pl, th, tl);
    return vdf_type(th, tl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
__lgamma_1_2_tbl_k(arg_t<vf_type> xch, arg_t<vf_type> xcl)
{
    using lng_tbl=lngamma_data<float>;

    constexpr
    const float xi0=1.0f;
#if 0
    vf_type fidx=rint(vf_type((xch-xi0)*lng_tbl::SCALE));
    vf_type x0=xi0+fidx*lng_tbl::INV_SCALE;
    vi_type idx= _T::cvt_f_to_i(fidx);
#else
    vf_type dxscale=(xch-xi0)*lng_tbl::SCALE;
    vf_type fidx=rint(dxscale);
    vi_type idx= _T::cvt_f_to_i(dxscale);
    vf_type x0=xi0+fidx*lng_tbl::INV_SCALE;
#endif
    vf_type ph, pl, cih, cil;
    vi_type idxs = idx*lng_tbl::ELEMS_PER_INTERVAL;
    auto lck=make_variable_lookup_table<float>(idxs);

    vf_type xh, xl;
    d_ops::add122(xh, xl, -x0, xch, xcl);
    const float* pt=lng_tbl::_12_tbl;
    cih=lck.from(pt);
    d_ops::unorm_mul122(ph, pl, cih, xh, xl);
    for (int i=1; i<lng_tbl::ELEMS_PER_INTERVAL-lng_tbl::DD_COEFFS*2; ++i) {
        cih=lck.from(pt+i);
        d_ops::add122(ph, pl, cih, ph, pl);
        d_ops::unorm_mul22(ph, pl, ph, pl, xh, xl);
    }
    for (int i=lng_tbl::ELEMS_PER_INTERVAL-lng_tbl::DD_COEFFS*2;
         i<lng_tbl::ELEMS_PER_INTERVAL-2; i+=2) {
        cih=lck.from(pt+i);
        cil=lck.from(pt+i+1);
        d_ops::add22(ph, pl, cih, cil, ph, pl);
        d_ops::unorm_mul22(ph, pl, ph, pl, xh, xl);
    }
    cih=lck.from(pt+lng_tbl::ELEMS_PER_INTERVAL-2);
    cil=lck.from(pt+lng_tbl::ELEMS_PER_INTERVAL-1);
    // cih+cil >= ph+pl or have at least the same exponent
    // because it is the value in the middle of the interval
    d_ops::add22(ph, pl, cih, cil, ph, pl);
    return vdf_type(ph, pl);
}

template <typename _T>
typename cftal::math::spec_func_core<float, _T>::reduced_small_gamma_args
cftal::math::spec_func_core<float, _T>::
__lgamma_reduce_small_k(arg_t<vf_type> xc)
{
    vdf_type x=xc;
    vdf_type f0=vf_type(1.0f);
    // vf_type f1(1.0f);
    vmf_type t;

    const float il=1.0f;
    const float ir=2.0f;

    if (_T::any_of_vmf(t= x[0]>vf_type(ir))) {
        // x>= 2, if t
        x[0] += _T::sel_val_or_zero(t, -1.0f);
        f0[0]=_T::sel(t, x[0], f0[0]);
        while (_T::any_of_vmf(t= x[0]>vf_type(ir))) {
            // x>=2, if t
            x[0] += _T::sel_val_or_zero(t, -1.0f);
            vf_type p= _T::sel(t, x[0], vf_type(1.0f));
            d_ops::unorm_mul122(f0[0], f0[1], p, f0[0], f0[1]);
#if 0
            // avoid overflows in f0
            if (_T::any_of_vmf(t=f0[0] > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                f0[1] *= h;
                f0[0] *= h;
                f1 *= _T::sel(t, 0x1p61f, 1.0f);
            }
#endif
        }
    }

    t= x[0]<vf_type(il);
    vmf_type inv_f= t;
    if (_T::any_of_vmf(t)) {
        vdf_type& q0=f0;
        q0[0] = _T::sel(t, x[0], q0[0]);
        q0[1] = _T::sel_zero_or_val(t, q0[1]);
        // nothing known about x
        d_ops::add122cond(x[0], x[1],
                          _T::sel_val_or_zero(t, 1.0f),
                          x[0], x[1]);
        // see below
        while (_T::any_of_vmf(t= x[0]<vf_type(-1.0f))) {
            vf_type q= _T::sel(t, x[0], vf_type(1.0f));
            d_ops::mul122(q0[0], q0[1], q, q0[0], q0[1]);
            // works because we do not loose bits here
            // x < -1.0
            x[0] += _T::sel_val_or_zero(t, 1.0f);
#if 0
            // avoid overflows in q0
            if (_T::any_of_vmf(t=abs(q0[0]) > 0x1p60f)) {
                vf_type h=_T::sel(t, 0x1p-61f, 1.0f);
                q0[1] *= h;
                q0[0] *= h;
                // we divide by f1
                f1 *= h;
            }
#endif
        }
        // the range between -1 and 1 must be handled more precise
        if (_T::any_of_vmf(t= x[0]<vf_type(0.0f))) {
            vf_type qh= _T::sel(t, x[0], vf_type(1.0f));
            vf_type ql= _T::sel_val_or_zero(t, x[1]);
            d_ops::mul22(q0[0], q0[1], q0[0], q0[1], qh, ql);
            // |x| <= 1.0
            d_ops::add122(x[0], x[1],
                        _T::sel_val_or_zero(t, 1.0f),
                        x[0], x[1]);
        }
        if (_T::any_of_vmf(t= x[0]<vf_type(il))) {
            vf_type qh= _T::sel(t, x[0], vf_type(1.0f));
            vf_type ql= _T::sel_val_or_zero(t, x[1]);
            d_ops::mul22(q0[0], q0[1], q0[0], q0[1], qh, ql);
            // |x| <= 1.0
            d_ops::add122(x[0], x[1],
                        _T::sel_val_or_zero(t, 1.0f),
                        x[0], x[1]);
        }
        // f0 /= q0;
        // d_ops::div22(f0[0], f0[1], f0[0], f0[1], q0[0], q0[1]);
    }
    return reduced_small_gamma_args{x, f0, inv_f};
}


template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
lgamma_k(arg_t<vf_type> xc, vi_type* signp)
{
#if __CFTAL_CFG_USE_VF64_FOR_VF32__>0
    vhf_type x=cvt<vhf_type>(xc);
    vhf_type xa=abs(x);
    constexpr const float x_tiny= 0x1p-25;

    constexpr const double x_small_delta = 6.0;
    constexpr const double x_small_left  = 1.0-x_small_delta;
    constexpr const double x_small_right = 2.0+x_small_delta;
    constexpr const float x_large= 0x1p25;

    reduced_small_gamma_args_vhf sst;

    // the reflection implementation below works only if the
    // reflection for really tiny values is delegated to __lgamma_small_k
    static_assert(x_small_left < -x_tiny, "constraint violated");
    vmhf_type xa_in_small =
        ((x >= x_small_left) & (x <= x_small_right) & (xa >= x_tiny));

    vhf_type base=xa;
    if (_T::vhf_traits::any_of_vmf(xa_in_small)) {
        vhf_type xs=f64_traits::sel(xa_in_small, x, 1.5);
        sst = __lgamma_reduce_small_k(xs);
        vhf_type log_a=abs(sst._f);
        base = f64_traits::sel(xa_in_small, log_a, base);
    }
    // using lanczos_ratfunc = lanczos_table_g_5_59172_N6;
    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
    vmhf_type xa_in_lanczos =
        (((x < x_small_left) | (x > x_small_right)) & (xa < x_large));
    if (_T::vhf_traits::any_of_vmf(xa_in_lanczos)) {
        vhf_type t= xa + lanczos_ratfunc::gm0_5();
        base= f64_traits::sel(xa_in_lanczos, t, base);
    }
    // lb contains log(xa+g-0.5) for xa_in_lanczos
    // log(xa) for xa > x_large | xa < x_tiny
    // log(f) for xa < x_small & xa >= tiny
    vhf_type lb= f64_core::log_k(base);
    vhf_type lg=0.0;
    vmhf_type xa_in_large = (xa >= x_large);
    if (_T::vhf_traits::any_of_vmf(xa_in_large)) {
        // log(gamma(x)) = xa * (log(xa) - 1.0), xa >> 1
        vhf_type t=(lb -1.0)*xa;
        lg = f64_traits::sel(xa_in_large, t, lg);
    }
    if (_T::vhf_traits::any_of_vmf(xa_in_lanczos)) {
        // lanczos sum:
        auto pq=lanczos_rational_at(xa,
                                    lanczos_ratfunc::p,
                                    lanczos_ratfunc::q);
        vhf_type sum = pq;
        vhf_type z= xa - 0.5;
        // g = z * log(base) + log(sum) - base;
        vhf_type ls=f64_core::log_k(sum);
        vhf_type t= (z * lb) - base + ls;
        lg = f64_traits::sel(xa_in_lanczos, t, lg);
    }
    if (_T::vhf_traits::any_of_vmf(xa_in_small)) {
        vhf_type lg12=__lgamma_1_2_k(sst._xr);
        vhf_type slb= f64_traits::sel(sst._inv_f, -lb, lb);
        vhf_type t= lg12 + slb;
        lg = f64_traits::sel(xa_in_small, t, lg);
    }
    // xa_in_tiny:
    vmhf_type xa_in_tiny= xa < x_tiny;
    lg = _T::vhf_traits::sel(xa_in_tiny, -lb, lg);

    // reflection part
    vi_type sgn=1;
    vmhf_type x_lt_0 = x < 0.0;
    if (_T::vhf_traits::any_of_vmf(x_lt_0)) {
        // tiny
        vmhf_type t= x_lt_0 & xa_in_tiny;
        sgn = _T::sel_vi(f64_traits::vmf_to_vmi(t), -1, sgn);
        // small
        t = x_lt_0 & xa_in_small;
        if (_T::vhf_traits::any_of_vmf(t)) {
            vhf_type sgn_g=copysign(vhf_type(1.0), sst._f);
            vi_type si= f64_traits::cvt_f_to_i(sgn_g);
            sgn=_T::sel_vi(f64_traits::vmf_to_vmi(t), si, sgn);
        }
        // lanczos
        t = x_lt_0 & xa_in_lanczos;
        if (_T::vhf_traits::any_of_vmf(t)) {
            // G(-z) = -pi/[sin(pi*z)*z * G(z)]
            vhf_type s;
            f64_core::sinpi_cospi_k(xa, &s, nullptr);
            using ctbl = impl::d_real_constants<d_real<double>, double>;
            // log(G(-z)) = log(pi) - log(z) - log(abs(sin(pi*z))-log(G(z))
            //            = log(pi) - log(abs(sin(pi*z)*z) - log(G(z))
            //            = log(pi) - [log(abs(sin(pi*z)*z) + log(G(z))]
            vhf_type sa= abs(s);
            sa *= xa;
            vhf_type lg_n=f64_core::log_k(sa);
            lg_n += lg;
            lg_n = ctbl::m_ln_pi[0] - lg_n;
            lg = f64_traits::sel(t, lg_n, lg);
            vmhf_type s_lt_0 = (s >= 0.0) & t;
            vmi_type i_s_lt_0 = f64_traits::vmf_to_vmi(s_lt_0);
            sgn = _T::sel_vi(i_s_lt_0, -1, sgn);
        }
        // no large handling because xc is integer anyway
    }
    if (signp != nullptr)
        *signp = sgn;
    vf_type lgh=cvt<vf_type>(lg);
    return lgh;
#else
    vf_type xa=abs(xc);
    constexpr const float x_tiny= 0x1p-25f;
#if 1
    constexpr const float x_small_delta = 6.0f;
    constexpr const float x_small_left  = 1.0f-x_small_delta;
    constexpr const float x_small_right = 2.0f+x_small_delta;
#else
    constexpr const float x_small_left  = 1.0f-1.25f;
    constexpr const float x_small_right = 2.0f+1.0f;
#endif
    constexpr const float x_large= 0x1p25f;

    reduced_small_gamma_args sst;

    // the reflection implementation below works only if the
    // reflection for really tiny values is delegated to __lgamma_small_k
    static_assert(x_small_left < -x_tiny, "constraint violated");
    vmf_type xa_in_small =
        ((xc >= x_small_left) & (xc <= x_small_right) & (xa >= x_tiny));

    vf_type base_h=xa, base_l=0.0f;
    if (_T::any_of_vmf(xa_in_small)) {
        vf_type xs=_T::sel(xa_in_small, xc, 1.5f);
        sst = __lgamma_reduce_small_k(xs);
        vdf_type log_a=select(sst._f[0]>0, sst._f, -sst._f);
        base_h = _T::sel(xa_in_small, log_a[0], base_h);
        base_l = _T::sel(xa_in_small, log_a[1], base_l);
    }

    // using lanczos_ratfunc = lanczos_table_g_5_59172_N6;
    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
    vmf_type xa_in_lanczos =
        (((xc < x_small_left) | (xc > x_small_right)) & (xa < x_large));
    if (_T::any_of_vmf(xa_in_lanczos)) {
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
    vdf_type lb= base_type::template
        __log_tbl_k2<base_type::result_prec::high>(base_h, base_l);
    vf_type lgh=0.0f, lgl=0.0f;
    vmf_type xa_in_large = (xa >= x_large);
    if (_T::any_of_vmf(xa_in_large)) {
        // log(gamma(x)) = xa * (log(xa) - 1.0), xa >> 1
        vf_type th, tl;
        d_ops::add212(th, tl, lb[0], lb[1], -1.0f);
        d_ops::mul122(th, tl, xa, th, tl);
        lgh = _T::sel(xa_in_large, th, lgh);
        lgl = _T::sel(xa_in_large, tl, lgl);
    }
    if (_T::any_of_vmf(xa_in_lanczos)) {
        // lanczos sum:
        auto pq=lanczos_rational_at(xa,
                                    lanczos_ratfunc::pdf,
                                    lanczos_ratfunc::qf);

        vf_type sum_h = pq[0], sum_l= pq[1];
        vf_type zh, zl;
        d_ops::add12cond(zh, zl, xa,  -0.5f);

        // g = z * log(base) + log(sum) - base;
        vdf_type ls=base_type::template
            __log_tbl_k2<base_type::result_prec::high>(sum_h, sum_l);
        vf_type th, tl;
        d_ops::unorm_mul22(th, tl, zh, zl, lb[0], lb[1]);
        d_ops::add22cond(th, tl, th, tl, -base_h, -base_l);
        d_ops::add22cond(th, tl, th, tl, ls[0], ls[1]);
        lgh = _T::sel(xa_in_lanczos, th, lgh);
        lgl = _T::sel(xa_in_lanczos, tl, lgl);
    }
    if (_T::any_of_vmf(xa_in_small)) {
        vdf_type lg12=__lgamma_1_2_tbl_k(sst._xr[0], sst._xr[1]);
        vf_type th, tl;
        // log(1/lb) = -log(lb):
        th = _T::sel(sst._inv_f, -lb[0], lb[0]);
        tl = _T::sel(sst._inv_f, -lb[1], lb[1]);
        d_ops::add22cond(th, tl, th, tl, lg12[0], lg12[1]);
        lgh = _T::sel(xa_in_small, th, lgh);
        lgl = _T::sel(xa_in_small, tl, lgl);
    }
    // xa_in_tiny:
    vmf_type xa_in_tiny= xa < x_tiny;
    lgh = _T::sel(xa_in_tiny, -lb[0], lgh);

    // reflection part
    vi_type sgn=1;
    vmf_type x_lt_0 = xc < 0.0f;
    if (_T::any_of_vmf(x_lt_0)) {
        // tiny
        vmf_type t= x_lt_0 & xa_in_tiny;
        sgn = _T::sel_vi(_T::vmf_to_vmi(t), -1, sgn);
        // small
        t = x_lt_0 & xa_in_small;
        if (_T::any_of_vmf(t)) {
            vf_type sgn_g=copysign(vf_type(1.0f), sst._f[0]);
            vi_type si= _T::cvt_f_to_i(sgn_g);
            sgn=_T::sel_vi(_T::vmf_to_vmi(t), si, sgn);
        }
        // lanczos
        t = x_lt_0 & xa_in_lanczos;
        if (_T::any_of_vmf(t)) {
            // G(-z) = -pi/[sin(pi*z)*z * G(z)]
            vdf_type s;
            sinpi_cospi_k(xa, &s, nullptr);
            using ctbl = impl::d_real_constants<d_real<float>, float>;
            // log(G(-z)) = log(pi) - log(z) - log(abs(sin(pi*z))-log(G(z))
            //            = log(pi) - log(abs(sin(pi*z)*z) - log(G(z))
            //            = log(pi) - [log(abs(sin(pi*z)*z) + log(G(z))]
            vdf_type sa= select(s[0] < 0.0f, -s, s);
            d_ops::mul122(sa[0], sa[1], xa, sa[0], sa[1]);
            vdf_type lg_n=base_type::template
                __log_tbl_k2<base_type::result_prec::high>(sa[0], sa[1]);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             lg_n[0], lg_n[1],
                             lgh, lgl);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             ctbl::m_ln_pi[0], ctbl::m_ln_pi[1],
                             -lg_n[0], -lg_n[1]);
            lgh = _T::sel(t, lg_n[0], lgh);
            vmf_type s_lt_0 = (s[0] >= 0.0f) & t;
            vmi_type i_s_lt_0 = _T::vmf_to_vmi(s_lt_0);
            sgn = _T::sel_vi(i_s_lt_0, -1, sgn);
        }
        // no large handling because xc is integer anyway
    }
    if (signp != nullptr)
        *signp = sgn;
    return lgh;
#endif
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
rsqrt12_k(arg_t<vf_type> xc)
{
    vf_type y=1.0f/sqrt(xc);
    vf_type z=impl::root_r2::calc_z<float, true>(y, xc);
    vf_type d=-0.5f*z;
    vf_type yh, yl;
    d_ops::add12(yh, yl, y, y*d);
    // d_ops::muladd12(yh, yl, y, y, d);
    return vdf_type(yh, yl);
}

template <typename _T>
void
cftal::math::spec_func_core<float, _T>::
__check_tbl_idx(arg_t<vi_type> idx, arg_t<vf_type> xb,
                const float* t, int32_t span)
{
#if 1
    static_cast<void>(idx);
    static_cast<void>(xb);
    static_cast<void>(t);
    static_cast<void>(span);
#else
    for (uint32_t i=0; i<size(idx); ++i) {
        float xi=extract(xb, i);
        int32_t idxi=extract(idx, i);
        int32_t idxm1=idxi-span;
        if (float > 0) {
            float xl= t[idxm1];
            if (xl > xi) {
                std::cerr << std::setprecision(22) << xi
                          << " has too large idx " << idxi
                          << " xl= "
                          << xl << std::endl;
            }
        }
        float xr=t[idxi];
        if (xr < xi) {
            std::cerr << std::setprecision(22) << xi
                        << " has too small idx " << idxi
                        << " xr= "
                        << xr << std::endl;
        }
    }
#endif
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
__j01y01_small_tbl_k(arg_t<vf_type> xc,
                     const float tb[j01y01_data<float>::ENTRIES],
                     float max_small_x)
{
    using tbl_t=j01y01_data<float>;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type xb=min(xc, vf_type(max_small_x));
    vf_type xb_idx=xb*ctbl::m_2_pi[0];
    vi_type idx=cvt_rz<vi_type>(xb_idx);
    idx *= tbl_t::ELEMS;
    auto lk=make_variable_lookup_table<float>(idx);
    vf_type xr_i0=lk.from(tb);
    vi_type i0=idx;
    vi_type i1=idx+tbl_t::ELEMS;
    i1 = min(i1, vi_type(tbl_t::ELEMS*(tbl_t::INTERVALS-1)));
    vmf_type xb_in_i1= xb > xr_i0;
    vmi_type sel_i1 = _T::vmf_to_vmi(xb_in_i1);
    idx=_T::sel_vi(sel_i1, i1, i0);
    // and update the lookup table
    __check_tbl_idx(idx, xb, tb, tbl_t::ELEMS);
    lk=make_variable_lookup_table<float>(idx);
    // read the negative interval centers
    const vf_type x0h=lk.from(tb + tbl_t::NEG_X_OFFS_H);
    const vf_type x0m=lk.from(tb + tbl_t::NEG_X_OFFS_M);
    const vf_type x0l=lk.from(tb + tbl_t::NEG_X_OFFS_L);
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, xb, x0h, x0m);
    d_ops::add122cond(xrh, xrl, x0l, xrh, xrl);

    vf_type xr2=xrh*xrh;
    // produce a polynomial of order POLY_ORD-3
    vf_type p=horner2_idx<tbl_t::POLY_ORD-3>(
        xrh, xr2, lk, tb+tbl_t::NEG_X_OFFS_L+1);
    vf_type rh, rl;
    vf_type c3=lk.from(tb+tbl_t::C3);
    vf_type c2=lk.from(tb+tbl_t::C2);
    vf_type c1h=lk.from(tb+tbl_t::C1H);
    vf_type c1l=lk.from(tb+tbl_t::C1L);
    vf_type c0h=lk.from(tb+tbl_t::C0H);
    vf_type c0l=lk.from(tb+tbl_t::C0L);
    horner_comp_quick(rh, rl, xrh, p, c3, c2);
    horner_comp_quick_dpc_si(rh, rl, xrh, rh, rl, c1h, c1l);
    d_ops::unorm_mul22(rh, rl, rh, rl, xrh, xrl);
    d_ops::add22(rh, rl, c0h, c0l, rh, rl);
    return rh;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vi_type
cftal::math::spec_func_core<float, _T>::
__reduce_trig_arg(vf_type& xrh, vf_type& xrm, vf_type& xrl,
                  arg_t<vf_type> x)
{
#if 0
    return payne_hanek_pi_over_2<float, _T>::rem3(xrh, xrm, xrl, x);
#else
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    constexpr const float large_arg=0x1p18f;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);

    xrh = 0.0f;
    xrm = 0.0f;
    xrl = 0.0f;
    vi_type q=0;
    if (__likely(!_T::all_of_vmf(v_large_arg))) {
        vf_type x_2_pi=x* ctbl::m_2_pi[0];
        vf_type fn= rint(x_2_pi);
        constexpr const float m_pi_2_h=+1.5707963705063e+00f;
        constexpr const float m_pi_2_m=-4.3711388286738e-08f;
        constexpr const float m_pi_2_l=-1.7151245100059e-15f;
        vf_type f0, f1, f2, f3, f4;
        d_ops::mul12(f0, f1, fn, -m_pi_2_h);
        d_ops::mul12(f2, f3, fn, -m_pi_2_m);
        f4 = fn * -m_pi_2_l;
        // normalize f0 - f4 into p0..p2
        vf_type p0, p1, p2, t;
        p0 = f0;
        d_ops::add12(p1, t, f1, f2);
        p2 = f4 + t + f3;
        d_ops::add12(p0, p1, p0, p1);
        d_ops::add12(p1, p2, p1, p2);
        vf_type t0, t1, t2;
        using t_ops=t_real_ops<vf_type>;
        t_ops::add133cond(t0, t1, t2, x, p0, p1, p2);
        t_ops::renormalize3(xrh, xrm, xrl, t0, t1, t2);
        // fn = base_type::template __fmod<4>(fn);
        q=_T::cvt_f_to_i(fn);
    }
    if (_T::any_of_vmf(v_large_arg)) {
        // reduce the large arguments
        vf_type xrhl, xrml, xrll;
        // mask out not required values to avoid subnormals
        vf_type xl=_T::sel_val_or_zero(v_large_arg, x);
        vi_type ql=payne_hanek_pi_over_2<float, _T>::
            rem3(xrhl, xrml, xrll, xl);
        q = _T::sel_vi(_T::vmf_to_vmi(v_large_arg), ql, q);
        xrh = _T::sel(v_large_arg, xrhl, xrh);
        xrm = _T::sel(v_large_arg, xrml, xrm);
        xrl = _T::sel(v_large_arg, xrll, xrl);
    }
    return q;
#endif
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vi_type
cftal::math::spec_func_core<float, _T>::
__reduce_trig_arg_tiny(vf_type& xrh, vf_type& xrl,
                        arg_t<vf_type> x, arg_t<vf_type> xl)
{
    // x^ : +0xc.90fdbp-3f
    constexpr
    const float pi_2_0=+1.5707963705e+00f;
    // x^ : -0xb.bbd2ep-28f
    constexpr
    const float pi_2_1=-4.3711388287e-08f;
    // x^ : -0xf.72cedp-53f
    constexpr
    const float pi_2_2=-1.7151245100e-15f;
    constexpr
    static const float ci[]={
        -pi_2_0, -pi_2_1, -pi_2_2
    };
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type x_2_pi=x* ctbl::m_2_pi[0];
    vf_type fn= rint(x_2_pi);
    vf_type sh=x, sl=xl;
    for (auto b=std::cbegin(ci), e=std::cend(ci); b!=e; ++b) {
#if 1
        const float m_pi_2=*b;
        d_ops::add122cond(sh, sl, m_pi_2*fn, sh, sl);
#else
        vf_type th, tl;
        const float m_pi_2=*b;
        d_ops::mul12(th, tl, fn, m_pi_2);
        d_ops::add22cond(sh, sl, sh, sl, th, tl);
#endif
    }
    xrh = sh;
    xrl = sl;
    // works only up to 2^31
    vi_type q=_T::cvt_f_to_i(x_2_pi);
    return q;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
__y0_singular_k(arg_t<vf_type> xc)
{
    vf_type r;
    // x^ : +0xcp-4
    constexpr
    const float y0_i0_r=+7.5000000000e-01f;
    if (_T::any_of_vmf(xc < y0_i0_r)) {
        // x^ h: -0xe.d6d81p-7f
        constexpr
        const float log_half_plus_euler_gamma_h=-1.1593151838e-01f;
        // x^ l: +0xb.abe15p-32f
        constexpr
        const float log_half_plus_euler_gamma_l=+2.7174611450e-09f;
        // [6;6]
        // [2.93873587705571876992184134305561419454666389193021880377187926569604314863681793212890625e-39, 0.75] : | p - f | <= 2^-35.9375
        // coefficients for j0 generated by sollya
        // x^0 : +0x8p-3f
        constexpr
        const float j0z0=+1.0000000000e+00f;
        // x^2 : -0x8p-5f
        constexpr
        const float j0z2=-2.5000000000e-01f;
        // x^4 : +0xf.ffffcp-10f
        constexpr
        const float j0z4=+1.5624996275e-02f;
        // x^6 : -0xe.38a05p-15f
        constexpr
        const float j0z6=-4.3399646529e-04f;
        // x^8 : +0xe.0d003p-21f
        constexpr
        const float j0z8=+6.6999359660e-06f;
        // [6;6]
        // [2.93873587705571876992184134305561419454666389193021880377187926569604314863681793212890625e-39, 0.75] : | p - f | <= 2^-33.75
        // coefficients for y0_r generated by sollya
        // x^2 : +0x8p-5f
        constexpr
        const float y0r2=+2.5000000000e-01f;
        // x^4 : -0xb.ffffdp-9f
        constexpr
        const float y0r4=-2.3437494412e-02f;
        // x^6 : +0xd.093dfp-14f
        constexpr
        const float y0r6=+7.9566048225e-04f;
        // x^8 : -0xe.a2fb1p-20f
        constexpr
        const float y0r8=-1.3958590898e-05f;

        constexpr static const float j0coeffs[]={
            j0z8, j0z6, j0z4//, j0z2
        };
        vf_type x2=xc*xc;
        vf_type j0p=horner(x2, j0coeffs)/*x2*/;
        vf_type j0h, j0l;
        horner_comp_quick(j0h, j0l, x2, j0p, j0z2, j0z0);
        // d_ops::add12(j0h, j0l, j0z0, j0p);
        constexpr static const float y0rcoeffs[]={
            y0r8, y0r6, y0r4
        };
        vf_type y0rp=horner(x2, y0rcoeffs);
        vf_type y0rh, y0rl;
        horner_comp_quick(y0rh, y0rl, x2, y0rp, y0r2);
        d_ops::mul122(y0rh, y0rl, x2, y0rh, y0rl);
        vdf_type ln_x=base_type::__log_tbl_k12(xc);

        // y0(x) = 2/pi*(f(x) + (log(0.5*x) + euler_gamma) * j0(x));
        // y0(x) = 2/pi*(f(x) + (log(x) + log(0.5)+euler_gamma) * j0(x));
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vf_type y0h, y0l;
        // |log(3/4) ~ -0.28| > |log_half_plus_euler_gamma_h|
        d_ops::add22(y0h, y0l,
                     ln_x[0], ln_x[1],
                     log_half_plus_euler_gamma_h,
                     log_half_plus_euler_gamma_l);
        d_ops::unorm_mul22(y0h, y0l, j0h, j0l, y0h, y0l);
        d_ops::add22cond(y0h, y0l, y0rh, y0rl, y0h, y0l);
        d_ops::unorm_mul22(y0h, y0l, y0h, y0l, ctbl::m_2_pi[0], ctbl::m_2_pi[1]);
        r = y0h + y0l;
    }
    // x^ : +0xap-3f
    constexpr
    const float y0_i1_r=+1.2500000000e+00f;
    vmf_type msk=(xc >= y0_i0_r)  & (xc < y0_i1_r);
    if (_T::any_of_vmf(msk)) {
        // [0.75;1.25] [8;8]
        // shifted [-0.14357696473598480224609375;0.35642302036285400390625] [8;8]
        // [-0.14357696473598480224609375, 0.35642302036285400390625] : | p - f | <= 2^-33.6875
        // coefficients for y0_i1 generated by sollya
        // x^1 h: +0xe.121b9p-4f
        constexpr
        const float y0_i1_1h=+8.7942081690e-01f;
        // x^1 l: -0xf.95e24p-30f
        constexpr
        const float y0_i1_1l=-1.4515112667e-08f;
        // x^2 : -0xf.bf1c5p-5f
        constexpr
        const float y0_i1_2=-4.9207893014e-01f;
        // x^3 : +0xe.1d8ap-6f
        constexpr
        const float y0_i1_3=+2.2055292130e-01f;
        // x^4 : -0xe.78c6dp-6f
        constexpr
        const float y0_i1_4=-2.2612161934e-01f;
        // x^5 : +0xe.02ff8p-6f
        constexpr
        const float y0_i1_5=+2.1893298626e-01f;
        // x^6 : -0xd.1d145p-6f
        constexpr
        const float y0_i1_6=-2.0489986241e-01f;
        // x^7 : +0xc.b27p-6f
        constexpr
        const float y0_i1_7=+1.9839096069e-01f;
        // x^8 : -0xc.8853bp-6f
        constexpr
        const float y0_i1_8=-1.9582073390e-01f;
        // x^9 : +0xa.ff492p-6f
        constexpr
        const float y0_i1_9=+1.7183139920e-01f;
        // x^10 : -0xb.31079p-7f
        constexpr
        const float y0_i1_10=-8.7433762848e-02f;
        // x^ h: +0xe.4c176p-4f
        constexpr
        const float y0_i1_x0h=+8.9357697964e-01f;
        // x^ m: -0xe.57d03p-30f
        constexpr
        const float y0_i1_x0m=-1.3357978723e-08f;
        // x^ l: +0x8.f54e9p-55f
        constexpr
        const float y0_i1_x0l=+2.4864083066e-16f;

        constexpr static const float ci[]={
            y0_i1_10, y0_i1_9, y0_i1_8, y0_i1_7,
            y0_i1_6, y0_i1_5, y0_i1_4, y0_i1_3
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y0_i1_x0h, -y0_i1_x0m);
        d_ops::add122cond(xrh, xrl, -y0_i1_x0l, xrh, xrl);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i1_2);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i1_1h, y0_i1_1l);
        d_ops::unorm_mul22(ph, pl, ph, pl, xrh, xrl);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x8p-2f
    constexpr
    const float y0_i2_r=+2.0000000000e+00f;
    msk=(xc >= y0_i1_r)  & (xc < y0_i2_r);
    if (_T::any_of_vmf(msk)) {
        // [1.25;2] [7;7]
        // shifted [-0.375;0.375] [8;8]
        // [-0.375, 0.375] : | p - f | <= 2^-33.09375
        // coefficients for y0_i2 generated by sollya
        // x^0 h: +0xd.b9b15p-5f
        constexpr
        const float y0_i2_0h=+4.2891755700e-01f;
        // x^0 l: +0x8.23bcap-31f
        constexpr
        const float y0_i2_0l=+3.7902951888e-09f;
        // x^1 : +0xa.9d3dap-5f
        constexpr
        const float y0_i2_1=+3.3169442415e-01f;
        // x^2 : -0xa.20eb9p-5f
        constexpr
        const float y0_i2_2=-3.1651857495e-01f;
        // x^3 : +0xf.a8264p-9f
        constexpr
        const float y0_i2_3=+3.0579753220e-02f;
        // x^4 : -0x9.b9a0dp-11f
        constexpr
        const float y0_i2_4=-4.7485888936e-03f;
        // x^5 : +0xa.cd7fep-10f
        constexpr
        const float y0_i2_5=+1.0549543425e-02f;
        // x^6 : -0xb.fc4fp-11f
        constexpr
        const float y0_i2_6=-5.8523342013e-03f;
        // x^7 : +0xb.d5f04p-12f
        constexpr
        const float y0_i2_7=+2.8895745054e-03f;
        // x^8 : -0xe.89919p-13f
        constexpr
        const float y0_i2_8=-1.7745821970e-03f;
        // x^9 : +0x8.6e6a6p-13f
        constexpr
        const float y0_i2_9=+1.0292127263e-03f;
        // x^ : +0xdp-3f
        constexpr
        const float y0_i2_x0=+1.6250000000e+00f;
        constexpr static const float ci[]={
            y0_i2_9, y0_i2_8, y0_i2_7, y0_i2_6, y0_i2_5, y0_i2_4, y0_i2_3
        };
        vf_type xrh, xrl;
        d_ops::add12cond(xrh, xrl, xc, -y0_i2_x0);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i2_2, y0_i2_1);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i2_0h, y0_i2_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0xdp-2f
    constexpr
    const float y0_i3_r=+3.2500000000e+00f;
    msk=(xc >= y0_i2_r)  & (xc < y0_i3_r);
    if (_T::any_of_vmf(msk)) {
        // [2;3.25] [7;7]
        // shifted [-0.625;0.625] [8;8]
        // [-0.625, 0.625] : | p - f | <= 2^-32.296875
        // coefficients for y0_i3 generated by sollya
        // x^0 h: +0xf.3f718p-5f
        constexpr
        const float y0_i3_0h=+4.7649455070e-01f;
        // x^0 l: +0xc.32b36p-31f
        constexpr
        const float y0_i3_0l=+5.6801594539e-09f;
        // x^1 : -0xc.b3fdfp-6f
        constexpr
        const float y0_i3_1=-1.9848583639e-01f;
        // x^2 : -0xc.d4042p-6f
        constexpr
        const float y0_i3_2=-2.0044043660e-01f;
        // x^3 : +0xd.c1702p-8f
        constexpr
        const float y0_i3_3=+5.3732879460e-02f;
        // x^4 : +0xf.abd91p-11f
        constexpr
        const float y0_i3_4=+7.6519926079e-03f;
        // x^5 : -0x9.d6899p-13f
        constexpr
        const float y0_i3_5=-1.2009321945e-03f;
        // x^6 : -0x9.15a22p-14f
        constexpr
        const float y0_i3_6=-5.5447418708e-04f;
        // x^7 : +0x9.392cdp-16f
        constexpr
        const float y0_i3_7=+1.4073700004e-04f;
        // x^8 : -0x8.baa66p-18f
        constexpr
        const float y0_i3_8=-3.3298878407e-05f;
        // x^9 : +0xc.50bc1p-20f
        constexpr
        const float y0_i3_9=+1.1744851690e-05f;
        // x^ : +0xa.8p-2f
        constexpr
        const float y0_i3_x0=+2.6250000000e+00f;

        constexpr static const float ci[]={
            y0_i3_9, y0_i3_8, y0_i3_7, y0_i3_6, y0_i3_5, y0_i3_4, y0_i3_3
        };
        vf_type xrh, xrl;
        d_ops::add12cond(xrh, xrl, xc, -y0_i3_x0);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i3_2, y0_i3_1);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i3_0h, y0_i3_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x9.8p-1f
    constexpr
    const float y0_i4_r=+4.7500000000e+00f;
    msk=(xc >= y0_i3_r)  & (xc <= y0_i4_r);
    if (_T::any_of_vmf(msk)) {
        // [3.25;4.75] [7;7]
        // shifted [-0.70767843723297119140625;0.79232156276702880859375] [8;8]
        // [-0.70767843723297119140625, 0.79232156276702880859375] : | p - f | <= 2^-34.53125
        // coefficients for y0_i4 generated by sollya
        // x^1 h: -0xc.e1a13p-5f
        constexpr
        const float y0_i4_1h=-4.0254268050e-01f;
        // x^1 l: +0x9.5f9a5p-30f
        constexpr
        const float y0_i4_1l=+8.7297040707e-09f;
        // x^2 : +0xd.04e49p-8f
        constexpr
        const float y0_i4_2=+5.0855908543e-02f;
        // x^3 : +0xe.fb6adp-8f
        constexpr
        const float y0_i4_3=+5.8523822576e-02f;
        // x^4 : -0xe.08b68p-11f
        constexpr
        const float y0_i4_4=-6.8525560200e-03f;
        // x^5 : -0x8.f197cp-12f
        constexpr
        const float y0_i4_5=-2.1835258231e-03f;
        // x^6 : +0xc.cb9a6p-16f
        constexpr
        const float y0_i4_6=+1.9524115487e-04f;
        // x^7 : +0xd.5af4dp-18f
        constexpr
        const float y0_i4_7=+5.0946418924e-05f;
        // x^8 : -0xa.3d6dp-21f
        constexpr
        const float y0_i4_8=-4.8827860155e-06f;
        // x^9 : -0xa.50e3dp-25f
        constexpr
        const float y0_i4_9=-3.0744004675e-07f;
        // x^ h: +0xf.d4a9ap-2f
        constexpr
        const float y0_i4_x0h=+3.9576783180e+00f;
        // x^ m: +0xd.9856ap-27f
        constexpr
        const float y0_i4_x0m=+1.0129117811e-07f;
        // x^ l: -0x8.7c1acp-52f
        constexpr
        const float y0_i4_x0l=-1.8840003274e-15f;

        constexpr static const float ci[]={
            y0_i4_9, y0_i4_8, y0_i4_7, y0_i4_6, y0_i4_5, y0_i4_4, y0_i4_3
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y0_i4_x0h, -y0_i4_x0m);
        d_ops::add122cond(xrh, xrl, -y0_i4_x0l, xrh, xrl);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i4_2);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i4_1h, y0_i4_1l);
        d_ops::unorm_mul22(ph, pl, ph, pl, xrh, xrl);
        r = _T::sel(msk, ph+pl, r);
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
__j0y0_phase_corr_k(arg_t<vf_type> xr2h,
                    arg_t<vf_type> xr2l,
                    arg_t<vf_type> xrh,
                    arg_t<vf_type> xrl)
{
    constexpr
    const float a0_c1=-1.2500000000e-01f;
    constexpr
    const float a0_c3_h=+6.5104164183e-02f;
    constexpr
    const float a0_c3_l=+2.4835269397e-09f;
    constexpr
    const float a0_c5_h=-2.0957031846e-01f;
    constexpr
    const float a0_c5_l=+5.9604645664e-09f;
    constexpr
    const float a0_c7_h=+1.6380659342e+00f;
    constexpr
    const float a0_c7_l=-5.1089696029e-08f;
    constexpr
    const float a0_c9_h=-2.3475128174e+01f;
    constexpr
    const float a0_c9_l=+4.2385525489e-07f;
    constexpr
    const float a0_c11_h=+5.3564050293e+02f;
    constexpr
    const float a0_c11_l=+1.6580928786e-05f;
    constexpr
    const float a0_c13_h=-1.7837279297e+04f;
    constexpr
    const float a0_c13_l=-3.9207248483e-04f;
    constexpr
    const float a0_c15_h=+8.1673781250e+05f;
    constexpr
    const float a0_c15_l=+2.9691075906e-02f;

    static_cast<void>(a0_c3_l);
    static_cast<void>(a0_c5_l);
    static_cast<void>(a0_c7_l);
    static_cast<void>(a0_c9_l);
    static_cast<void>(a0_c11_h);
    static_cast<void>(a0_c11_l);
    static_cast<void>(a0_c13_h);
    static_cast<void>(a0_c13_l);
    static_cast<void>(a0_c15_h);
    static_cast<void>(a0_c15_l);
    constexpr const static float ci[]={
        /* a0_c15, a0_c13_h, a0_c11_h,*/ a0_c9_h, a0_c7_h, a0_c5_h
    };
    vf_type p=horner(xr2h, ci);
    vf_type ph, pl;
    horner_comp_quick_dpc_s0(ph, pl, xr2h, p, a0_c3_h, a0_c3_l);

    d_ops::mul22(ph, pl, xr2h, xr2l, ph, pl);
    d_ops::add122cond(ph, pl, a0_c1, ph, pl);
    d_ops::mul22(ph, pl, xrh, xrl, ph, pl);
    return vdf_type(ph, pl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
__j0y0_amplitude_corr_k(arg_t<vf_type> xr2h, arg_t<vf_type> xr2l)
{
    constexpr
    const float b0_c0=+1.0000000000e+00f;
    constexpr
    const float b0_c2=-6.2500000000e-02f;
    constexpr
    const float b0_c4=+1.0351562500e-01f;
    constexpr
    const float b0_c6=-5.4284667969e-01f;
    constexpr
    const float b0_c8=+5.8486995697e+00f;
    constexpr
    const float b0_c10=-1.0688679504e+02f;
    constexpr
    const float b0_c12=+2.9681428223e+03f;
    constexpr
    const float b0_c14=-1.1653847656e+05f;
    static_cast<void>(b0_c6);
    static_cast<void>(b0_c8);
    static_cast<void>(b0_c10);
    static_cast<void>(b0_c12);
    static_cast<void>(b0_c14);
    constexpr const static float ci[]={
        /* b0_c14, b0_c12, b0_c10, b0_c8,*/ b0_c6, b0_c4, b0_c2
    };
    vf_type beta=horner(xr2h, ci);
    static_cast<void>(xr2l);
    vf_type bh, bl;
    d_ops::mul122(bh, bl, beta, xr2h, xr2l);
    d_ops::add122(bh, bl, b0_c0, bh, bl);
    return vdf_type(bh, bl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
__y1_singular_k(arg_t<vf_type> xc)
{
    vf_type r=0;
    // x^ : +0xcp-4f
    constexpr
    const float y1_i0_r=+7.5000000000e-01f;
    if (_T::any_of_vmf(xc < y1_i0_r)) {
        // [6;6]
        // [0, 0.75] : | p - f | <= 2^-31.0625
        // coefficients for j1 generated by sollya
        // x^1 : +0x8p-4f
        constexpr
        const float j1z1=+5.0000000000e-01f;
        // x^3 : -0xf.ffffap-8f
        constexpr
        const float j1z3=-6.2499977648e-02f;
        // x^5 : +0xa.aa6a7p-12f
        constexpr
        const float j1z5=+2.6039273944e-03f;
        // x^7 : -0xe.07d37p-18f
        constexpr
        const float j1z7=-5.3522377129e-05f;
        // [6;7]
        // [0, 0.75] : | p - f | <= 2^-30.2265625
        // coefficients for y1_r generated by sollya
        // x^1 h: -0x9.dadbp-5f
        constexpr
        const float y1r1h=-3.0796575546e-01f;
        // x^1 l: -0x8.0b02p-33f
        constexpr
        const float y1r1l=-9.3632834819e-10f;
        // x^3 : +0xa.ed6cep-7f
        constexpr
        const float y1r3=+8.5370644927e-02f;
        // x^5 : -0x9.81819p-11f
        constexpr
        const float y1r5=-4.6415445395e-03f;
        // x^7 : +0xe.8497cp-17f
        constexpr
        const float y1r7=+1.1076309602e-04f;


        // y1(x) = 2/pi*(f(x) + (j1(x) * log(x) - 1/x));
        // y1(x) = 2/pi*(scale_down * f(x) +
        //               j1(x) * scale_down * log(x)
        //               -1,0/x/scale_down)*scale_up;
        // y1(x) = 2/pi*(scale_down * f(x) +
        //               j1(x) * scale_down * log(x)
        //               -1,0/(x*scale_up))*scale_up
        // scaling is required near zero to avoid nans
        // in the calculation of the sum
        const float scale_down=0x1p-25f;
        const float scale_up=0x1p25f;

        constexpr static const float j1coeffs[]={
            j1z7, j1z5
        };
        vf_type x2=xc*xc;
        vf_type j1p=horner(x2, j1coeffs);
        vf_type j1h, j1l;
        horner_comp_quick(j1h, j1l, x2, j1p, j1z3, j1z1);
        vf_type t;
        d_ops::mul12(j1h, t, j1h, xc);
        j1l= j1l*xc + t;

        constexpr static const float y1rcoeffs[]={
            y1r7, y1r5, y1r3
        };
        vf_type y1rp=horner(x2, y1rcoeffs);
        vf_type y1rh, y1rl;
        horner_comp_quick_dpc_s0(y1rh, y1rl, x2, y1rp, y1r1h, y1r1l);
        d_ops::mul122(y1rh, y1rl, xc, y1rh, y1rl);

        y1rh *= scale_down;
        y1rl *= scale_down;

        vdf_type ln_x=base_type::__log_tbl_k12(xc);
        ln_x[0] *=scale_down;
        ln_x[1] *=scale_down;

        vf_type y1h, y1l;
        vdf_type neg_inv_x;
        d_ops::rcp12(neg_inv_x[0], neg_inv_x[1], -(xc*scale_up));
        d_ops::unorm_mul22(y1h, y1l, j1h, j1l, ln_x[0], ln_x[1]);
        d_ops::add22cond(y1h, y1l, y1h, y1l, neg_inv_x[0], neg_inv_x[1]);
        d_ops::add22cond(y1h, y1l, y1h, y1l, y1rh, y1rl);
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        d_ops::unorm_mul22(y1h, y1l, y1h, y1l, ctbl::m_2_pi[0], ctbl::m_2_pi[1]);
        r = (y1h + y1l)*scale_up;
    }
    // x^ : +0xap-3f
    constexpr
    const float y1_i1_r=+1.2500000000e+00f;
    vmf_type msk=(xc >= y1_i0_r)  & (xc < y1_i1_r);
    if (_T::any_of_vmf(msk)) {
        // [0.75;1.25] [9;9]
        // shifted [-0.25;0.25] [9;9]
        // [-0.25, 0.25] : | p - f | <= 2^-29.6640625
        // coefficients for y1_i1 generated by sollya
        // x^0 h: -0xc.7fd9p-4f
        constexpr
        const float y1_i1_0h=-7.8121280670e-01f;
        // x^0 l: -0xf.a8622p-30f
        constexpr
        const float y1_i1_0l=-1.4582413499e-08f;
        // x^1 : +0xd.e9593p-4f
        constexpr
        const float y1_i1_1=+8.6946982145e-01f;
        // x^2 : -0xd.e9595p-5f
        constexpr
        const float y1_i1_2=-4.3473497033e-01f;
        // x^3 : +0x8.cdb43p-4f
        constexpr
        const float y1_i1_3=+5.5022066832e-01f;
        // x^4 : -0x9.f6756p-4f
        constexpr
        const float y1_i1_4=-6.2267053127e-01f;
        // x^5 : +0x9.fe4fp-4f
        constexpr
        const float y1_i1_5=+6.2458705902e-01f;
        // x^6 : -0xa.08558p-4f
        constexpr
        const float y1_i1_6=-6.2703466415e-01f;
        // x^7 : +0x9.e062fp-4f
        constexpr
        const float y1_i1_7=+6.1728185415e-01f;
        // x^8 : -0x9.d29d2p-4f
        constexpr
        const float y1_i1_8=-6.1391937733e-01f;
        // x^9 : +0xc.7f587p-4f
        constexpr
        const float y1_i1_9=+7.8109019995e-01f;
        // x^10 : -0xd.0c854p-4f
        constexpr
        const float y1_i1_10=-8.1555676460e-01f;
        // x^ : +0x8p-3f
        constexpr
        const float y1_i1_x0=+1.0000000000e+00f;

        constexpr static const float ci[]={
            y1_i1_10, y1_i1_9, y1_i1_8, y1_i1_7,
            y1_i1_6, y1_i1_5, y1_i1_4, y1_i1_3
        };
        // sterbenz lemma: subtraction is exact
        vf_type xrh=xc - y1_i1_x0;
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y1_i1_2, y1_i1_1);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y1_i1_0h, y1_i1_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x8p-2f
    constexpr
    const float y1_i2_r=+2.0000000000e+00f;
    msk=(xc >= y1_i1_r)  & (xc < y1_i2_r);
    if (_T::any_of_vmf(msk)) {
        // [1.25;2] [7;7]
        // shifted [-0.375;0.375] [9;9]
        // [-0.375, 0.375] : | p - f | <= 2^-32.453125
        // coefficients for y1_i2 generated by sollya
        // x^0 h: -0xa.9d3dap-5f
        constexpr
        const float y1_i2_0h=-3.3169442415e-01f;
        // x^0 l: +0xe.cc2bp-34f
        constexpr
        const float y1_i2_0l=+8.6132967425e-10f;
        // x^1 : +0xa.20ebap-4f
        constexpr
        const float y1_i2_1=+6.3303720951e-01f;
        // x^2 : -0xb.be1edp-7f
        constexpr
        const float y1_i2_2=-9.1739512980e-02f;
        // x^3 : +0x9.b8d9fp-9f
        constexpr
        const float y1_i2_3=+1.8988428637e-02f;
        // x^4 : -0xd.80113p-8f
        constexpr
        const float y1_i2_4=-5.2735399455e-02f;
        // x^5 : +0x9.07f0ap-8f
        constexpr
        const float y1_i2_5=+3.5277403891e-02f;
        // x^6 : -0xa.76ecp-9f
        constexpr
        const float y1_i2_6=-2.0438551903e-02f;
        // x^7 : +0xc.d185fp-10f
        constexpr
        const float y1_i2_7=+1.2518017553e-02f;
        // x^8 : -0xf.f241dp-11f
        constexpr
        const float y1_i2_8=-7.7862874605e-03f;
        // x^9 : +0xb.c42f1p-11f
        constexpr
        const float y1_i2_9=+5.7452847250e-03f;
        // x^10 : -0xe.9603cp-12f
        constexpr
        const float y1_i2_10=-3.5610338673e-03f;
        // x^ : +0xdp-3f
        constexpr
        const float y1_i2_x0=+1.6250000000e+00f;
        constexpr static const float ci[]={
            y1_i2_10, y1_i2_9, y1_i2_8, y1_i2_7,
            y1_i2_6, y1_i2_5, y1_i2_4, y1_i2_3
        };
        // sterbenz lemma: subtraction is exact
        vf_type xrh=xc - y1_i2_x0;
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y1_i2_2, y1_i2_1);
        horner_comp_dpc_si(ph, pl, xrh, ph, pl, y1_i2_0h, y1_i2_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0xdp-2f
    constexpr
    const float y1_i3_r=+3.2500000000e+00f;
    msk=(xc >= y1_i2_r)  & (xc < y1_i3_r);
    if (_T::any_of_vmf(msk)) {
        // [2;3.25] [7;7]
        // shifted [-0.1971413195133209228515625;1.05285871028900146484375] [9;9]
        // [-0.1971413195133209228515625, 1.05285871028900146484375] : | p - f | <= 2^-29.8671875
        // coefficients for y1_i3 generated by sollya
        // x^1 h: +0x8.55242p-4f
        constexpr
        const float y1_i3_1h=+5.2078640461e-01f;
        // x^1 l: +0xf.71d3cp-31f
        constexpr
        const float y1_i3_1l=+7.1919696865e-09f;
        // x^2 : -0xf.2b7bep-7f
        constexpr
        const float y1_i3_2=-1.1851452291e-01f;
        // x^3 : -0x8.69563p-8f
        constexpr
        const float y1_i3_3=-3.2857310027e-02f;
        // x^4 : -0x9.d45b8p-11f
        constexpr
        const float y1_i3_4=-4.7995708883e-03f;
        // x^5 : +0xf.34af9p-11f
        constexpr
        const float y1_i3_5=+7.4247089215e-03f;
        // x^6 : -0xa.869e2p-12f
        constexpr
        const float y1_i3_6=-2.5697876699e-03f;
        // x^7 : +0xf.b6befp-14f
        constexpr
        const float y1_i3_7=+9.5909734955e-04f;
        // x^8 : -0xa.7de95p-15f
        constexpr
        const float y1_i3_8=-3.2018558704e-04f;
        // x^9 : +0xe.3b5ddp-18f
        constexpr
        const float y1_i3_9=+5.4290390835e-05f;
        // x^ h: +0x8.c9df7p-2f
        constexpr
        const float y1_i3_x0h=+2.1971414089e+00f;
        // x^ m: -0xb.200dcp-27f
        constexpr
        const float y1_i3_x0m=-8.2889272335e-08f;
        // x^ l: +0xb.90b87p-53f
        constexpr
        const float y1_i3_x0l=+1.2840078215e-15f;
        constexpr static const float ci[]={
            y1_i3_9, y1_i3_8, y1_i3_7, y1_i3_6, y1_i3_5, y1_i3_4
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y1_i3_x0h, -y1_i3_x0m);
        d_ops::add122cond(xrh, xrl, -y1_i3_x0l, xrh, xrl);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y1_i3_3, y1_i3_2);
        horner_comp_dpc_si(ph, pl, xrh, ph, pl, y1_i3_1h, y1_i3_1l);
        d_ops::unorm_mul22(ph, pl, ph, pl, xrh, xrl);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x9.8p-1f
    constexpr
    const float y1_i4_r=+4.7500000000e+00f;
    msk=(xc >= y1_i3_r)  & (xc <= y1_i4_r);
    if (_T::any_of_vmf(msk)) {
        // [3.25;4.75] [8;8]
        // shifted [-0.4330228269100189208984375;1.06697714328765869140625] [7;8]
        // [-0.4330228269100189208984375, 1.06697714328765869140625] : | p - f | <= 2^-32.890625
        // coefficients for y1_i4 generated by sollya
        // x^0 h: +0xd.55dap-5f
        constexpr
        const float y1_i4_0h=+4.1672992706e-01f;
        // x^0 l: +0xa.0865p-33f
        constexpr
        const float y1_i4_0l=+1.1679706091e-09f;
        // x^1 : +0x8.ace9dp-29f
        constexpr
        const float y1_i4_1=+1.6159271254e-08f;
        // x^2 : -0xc.5a2dep-6f
        constexpr
        const float y1_i4_2=-1.9300410151e-01f;
        // x^3 : +0xf.0a383p-10f
        constexpr
        const float y1_i4_3=+1.4687421732e-02f;
        // x^4 : +0xc.62dd6p-10f
        constexpr
        const float y1_i4_4=+1.2095889077e-02f;
        // x^5 : -0x8.9a472p-14f
        constexpr
        const float y1_i4_5=-5.2506395150e-04f;
        // x^6 : -0xd.fef5cp-15f
        constexpr
        const float y1_i4_6=-4.2712211143e-04f;
        // x^7 : +0x9.2d22ap-18f
        constexpr
        const float y1_i4_7=+3.5004843085e-05f;
        // x^8 : +0xb.6eb6dp-23f
        constexpr
        const float y1_i4_8=+1.3628574607e-06f;
        // x^9 : +0xe.7d8d7p-25f
        constexpr
        const float y1_i4_9=+4.3184874698e-07f;
        // x^10 : -0xa.37781p-28f
        constexpr
        const float y1_i4_10=-3.8060083085e-08f;
        // x^ h: +0xe.bb6a5p-2f
        constexpr
        const float y1_i4_x0h=+3.6830227375e+00f;
        // x^ m: +0xa.6b7ccp-27f
        constexpr
        const float y1_i4_x0m=+7.7634098261e-08f;
        // x^ l: -0xd.71361p-52f
        constexpr
        const float y1_i4_x0l=-2.9847749113e-15f;

        constexpr static const float ci[]={
            y1_i4_10, y1_i4_9, y1_i4_8, y1_i4_7, y1_i4_6, y1_i4_5
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y1_i4_x0h, -y1_i4_x0m);
        d_ops::add122cond(xrh, xrl, -y1_i4_x0l, xrh, xrl);

        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp(ph, pl, xrh, p, y1_i4_4, y1_i4_3, y1_i4_2, y1_i4_1);
        d_ops::unorm_mul22(ph, pl, xrh, xrl, ph, pl);
        d_ops::add22(ph, pl, y1_i4_0h, y1_i4_0l, ph, pl);
        r = _T::sel(msk, ph, r);
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
__j1y1_phase_corr_k(arg_t<vf_type> xr2h,
                    arg_t<vf_type> xr2l,
                    arg_t<vf_type> xrh,
                    arg_t<vf_type> xrl)
{
    constexpr
    const float a1_c1=+3.7500000000e-01f;
    constexpr
    const float a1_c3=-1.6406250000e-01f;
    constexpr
    const float a1_c5_h=+3.7089842558e-01f;
    constexpr
    const float a1_c5_l=+1.1920929133e-08f;
    constexpr
    const float a1_c7_h=-2.3693978786e+00f;
    constexpr
    const float a1_c7_l=+3.4059798537e-08f;
    constexpr
    const float a1_c9=+3.0624011993e+01f;
    constexpr
    const float a1_c11_h=-6.5918524170e+02f;
    constexpr
    const float a1_c11_l=+1.9875440557e-05f;
    constexpr
    const float a1_c13_h=+2.1156314453e+04f;
    constexpr
    const float a1_c13_l=-4.0759719559e-04f;
    constexpr
    const float a1_c15_h=-9.4434662500e+05f;
    constexpr
    const float a1_c15_l=+1.5451945364e-02f;

    static_cast<void>(a1_c5_l);
    static_cast<void>(a1_c7_l);
    static_cast<void>(a1_c11_h);
    static_cast<void>(a1_c11_l);
    static_cast<void>(a1_c13_h);
    static_cast<void>(a1_c13_l);
    static_cast<void>(a1_c15_h);
    static_cast<void>(a1_c15_l);
    constexpr const static float ci[]={
        /* a1_c15_h, a1_c13_h, a1_c11_h,*/ a1_c9, a1_c7_h, a1_c5_h
    };
    vf_type p=horner(xr2h, ci);
    vf_type ph, pl;
    horner_comp_quick(ph, pl, xr2h, p, a1_c3);

    d_ops::mul22(ph, pl, xr2h, xr2l, ph, pl);
    d_ops::add122(ph, pl, a1_c1, ph, pl);
    d_ops::mul22(ph, pl, xrh, xrl, ph, pl);
    return vdf_type(ph, pl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vdf_type
cftal::math::spec_func_core<float, _T>::
__j1y1_amplitude_corr_k(arg_t<vf_type> xr2h, arg_t<vf_type> xr2l)
{
    constexpr
    const float b1_c0=+1.0000000000e+00f;
    constexpr
    const float b1_c2=+1.8750000000e-01f;
    constexpr
    const float b1_c4=-1.9335937500e-01f;
    constexpr
    const float b1_c6=+8.0529785156e-01f;
    constexpr
    const float b1_c8=-7.7399539948e+00f;
    constexpr
    const float b1_c10=+1.3276182556e+02f;
    constexpr
    const float b1_c12=-3.5433037109e+03f;
    constexpr
    const float b1_c14=+1.3539423438e+05f;
    static_cast<void>(b1_c6);
    static_cast<void>(b1_c8);
    static_cast<void>(b1_c10);
    static_cast<void>(b1_c12);
    static_cast<void>(b1_c14);
    constexpr const static float ci[]={
        /* b1_c14, b1_c12, b1_c10, b1_c8,*/ b1_c6, b1_c4, b1_c2
    };
    vf_type beta=horner(xr2h, ci);
    static_cast<void>(xr2l);
    vf_type bh, bl;
    d_ops::mul122(bh, bl, beta, xr2h, xr2l);
    d_ops::add122(bh, bl, b1_c0, bh, bl);
    return vdf_type(bh, bl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
__j01y01_large_phase_amplitude_k(arg_t<vf_type> xc,
                                 bool calc_yn,
                                 bool calc_jy1)
{
    scoped_ftz_daz_mode ftz_mode;

    vf_type rec_x_h, rec_x_l;
    d_ops::div12(rec_x_h, rec_x_l, 1.0, xc);
    vf_type xr2h, xr2l;
    d_ops::sqr22(xr2h, xr2l, rec_x_h, rec_x_l);

    // x^ h: +0xc.c422ap-4f
    constexpr
    const float sqrt_two_over_pi_h=+7.9788458347e-01f;
    // x^ l: -0xc.2bc9bp-29f
    constexpr
    const float sqrt_two_over_pi_l=-2.2670340272e-08f;
    // select amplitude correction for j0/y0 or j1/y1
    vdf_type amp_cor= calc_jy1 == false ?
        __j0y0_amplitude_corr_k(xr2h, xr2l) :
        __j1y1_amplitude_corr_k(xr2h, xr2l);
    auto rsqrt_xc=rsqrt12_k(xc);
    vf_type amph, ampl;
    d_ops::mul22(amph, ampl,
                 amp_cor[0], amp_cor[1], rsqrt_xc[0], rsqrt_xc[1]);
    d_ops::mul22(amph, ampl, amph, ampl,
                 sqrt_two_over_pi_h, sqrt_two_over_pi_l);

    vf_type xrh, xrm, xrl;
    vi_type q=__reduce_trig_arg(xrh, xrm, xrl, xc);
    vf_type xsh, xsl;
    // x^ : +0xc.90fdbp-4f
    constexpr
    const float pi_4_0=+7.8539818525e-01f;
    // x^ : -0xb.bbd2ep-29f
    constexpr
    const float pi_4_1=-2.1855694143e-08f;
    // x^ : -0xf.72cedp-54f
    constexpr
    const float pi_4_2=-8.5756225500e-16f;
    using t_ops=t_real_ops<vf_type>;
    // if x >= 0 subtract pi/4
    // if x < 0 add pi/4 and subtract -1 from q
    vmf_type is_x_lt_z = xrh < 0.0;
    vmi_type i_is_x_lt_z = _T::vmf_to_vmi(is_x_lt_z);
    vf_type d0=_T::sel(is_x_lt_z, pi_4_0, -pi_4_0);
    vf_type d1=_T::sel(is_x_lt_z, pi_4_1, -pi_4_1);
    vf_type d2=_T::sel(is_x_lt_z, pi_4_2, -pi_4_2);
    q = _T::sel_vi(i_is_x_lt_z, q - 1, q);
    t_ops::add33cond(xrh, xrm, xrl,
                     xrh, xrm, xrl,
                     d0, d1, d2);
    // select phase  correction for j0/y0 or j1/y1
    vdf_type phase_cor= calc_jy1 == false ?
        __j0y0_phase_corr_k(xr2h, xr2l, rec_x_h, rec_x_l) :
        __j1y1_phase_corr_k(xr2h, xr2l, rec_x_h, rec_x_l);
    t_ops::add233cond(xrh, xrm, xrl, phase_cor[0], phase_cor[1],
                      xrh, xrm, xrl);
    t_ops::renormalize32(xsh, xsl, xrh, xrm, xrl);
    // perform argument reduction on xsh, xsl again
    vf_type xh, xl;
    auto q2=__reduce_trig_arg_tiny(xh, xl, xsh, xsl);
    if (calc_jy1 == false) {
        q2 += q;
    } else {
        // -1 for the subtraction of only pi/4 above, i.e. q2 is 1 too large
        q2 += q-1;
    }
    // q2 &= 3;

    vdf_type phase;
    // select sinus or cosinus for y0/1 or j0/1 calculation
    vdf_type* psin = calc_yn ? &phase : nullptr;
    vdf_type* pcos = calc_yn ? nullptr : &phase;
    base_type::__sin_cos_k(xh, xl, q2, psin, pcos);

    vf_type rh, rl;
    d_ops::mul22(rh, rl, phase[0], phase[1], amph, ampl);
    return rh;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
j0_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const float small_threshold=j01y01_data<float>::_max_small_j0;
    const vmf_type xa_small = xa <= small_threshold;
    bool any_small;
    if ((any_small=_T::any_of_vmf(xa_small))==true) {
        r= __j01y01_small_tbl_k(xa,
                                j01y01_data<float>::_j0_coeffs,
                                j01y01_data<float>::_max_small_j0);
    }
    if (!_T::all_of_vmf(xa_small)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, false, false);
        if (any_small) {
            r = _T::sel(xa_small, r, rl);
        } else {
            r = rl;
        }
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
j1_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const float small_threshold=j01y01_data<float>::_max_small_j1;
    const vmf_type xa_small = xa <= small_threshold;
    bool any_small;
    if ((any_small=_T::any_of_vmf(xa_small))==true) {
        r= __j01y01_small_tbl_k(xa,
                                j01y01_data<float>::_j1_coeffs,
                                j01y01_data<float>::_max_small_j1);
    }
    if (!_T::all_of_vmf(xa_small)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, false, true);
        if (any_small) {
            r = _T::sel(xa_small, r, rl);
        } else {
            r = rl;
        }
    }
    r = mulsign(r, xc);
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
y0_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const float small_threshold=j01y01_data<float>::_max_small_y0;
    const float singular_threshold=4.75f;
    bool select_required=false;
    if (_T::any_of_vmf(xa <= singular_threshold)==true) {
        r=__y0_singular_k(xa);
        select_required=true;
    }
    vmf_type msk_xa_small=(xa > singular_threshold) &
                          (xa <= small_threshold);
    if (_T::any_of_vmf(msk_xa_small)==true) {
        vf_type rs= __j01y01_small_tbl_k(xa,
                                         j01y01_data<float>::_y0_coeffs,
                                         j01y01_data<float>::_max_small_y0);
        if (select_required==false) {
            r=rs;
            select_required=true;
        } else {
            r=_T::sel(msk_xa_small, rs, r);
        }
    }
    vmf_type msk_xa_large= xa > small_threshold;
    if (_T::any_of_vmf(msk_xa_large)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, true, false);
        if (select_required==false) {
            r = rl;
        } else {
            r = _T::sel(msk_xa_large, rl, r);
        }
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<float, _T>::vf_type
cftal::math::spec_func_core<float, _T>::
y1_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const float small_threshold=j01y01_data<float>::_max_small_y1;
    const float singular_threshold=4.75f;
    bool select_required=false;
    if (_T::any_of_vmf(xa <= singular_threshold)==true) {
        r=__y1_singular_k(xa);
        select_required=true;
    }
    vmf_type msk_xa_small=(xa > singular_threshold) &
                          (xa <= small_threshold);
    if (_T::any_of_vmf(msk_xa_small)==true) {
        vf_type rs= __j01y01_small_tbl_k(xa,
                                         j01y01_data<float>::_y1_coeffs,
                                         j01y01_data<float>::_max_small_y1);
        if (select_required==false) {
            r=rs;
            select_required=true;
        } else {
            r=_T::sel(msk_xa_small, rs, r);
        }
    }
    vmf_type msk_xa_large= xa > small_threshold;
    if (_T::any_of_vmf(msk_xa_large)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, true, true);
        if (select_required==false) {
            r = rl;
        } else {
            r = _T::sel(msk_xa_large, rl, r);
        }
    }
    return r;
}

// Local Variables:
// mode: c++
// end:
#endif
