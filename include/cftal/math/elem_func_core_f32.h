//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_ELEM_FUNC_CORE_F32_H__)
#define __CFTAL_MATH_ELEM_FUNC_CORE_F32_H__ 1

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
#include <cftal/math/elem_func.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/horner.h>
#include <cftal/math/misc.h>
#include <cftal/mem.h>

#include <iostream>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for float and different
        // traits
        template <typename _T>
        struct elem_func_core<float, _T> {

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using dvf_type = d_real<vf_type>;

            using d_ops=cftal::impl::d_real_ops<vf_type,
                                                d_real_traits<vf_type>::fma>;

            static
            vf_type
            pow2i(arg_t<vi_type> d);

            // nextafter without nan handling
            static
            vf_type
            nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc);

            // as frexp but without checking for 0, inf, nan
            static
            vi_type
            __frexp_k(vf_type& m, arg_t<vf_type> x);

            static
            vf_type
            frexp(arg_t<vf_type> vf, vi_type* vi);

            static
            vf_type
            ldexp(arg_t<vf_type> vf, arg_t<vi_type> vi);

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);

            static
            vi_type
            ilogb(arg_t<vf_type> vf);

            // calculates 1/sqrt(x)
            static
            vf_type
            rsqrt_k(arg_t<vf_type> x);

            // calculates x^(1/3)
            static
            vf_type
            cbrt_k(arg_t<vf_type> x);

            // calculates x^(1/12)
            static
            vf_type
            root12_k(arg_t<vf_type> x);

            // scaling function for exponential functions
            // returns y*2^k,
            // expects double(k) == kf
            static
            vf_type
            __scale_exp_k(arg_t<vf_type> y, arg_t<vf_type> kf,
                          arg_t<vi_type> k);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/2, log(2)/2], and the arguments
            // kf and k as argument for scale_exp_k
            // calculates %e^(xrh+xrl)*2^k - 1 if exp_m1 is true,
            // %e^(xrh+xrl)*2^k otherwise
            template <bool _EXP_M1>
            static
            vf_type
            __exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                    arg_t<vf_type> kf, arg_t<vi_type> k);

            // argument reduction for %e^x and %e^x-1
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/2, log(2)/2] for calling __exp_k
            // the return type must match the type of the k
            // argument of __exp_k
            static
            vi_type
            __reduce_exp_arg(vf_type& xrh,
                             vf_type& xrl,
                             vf_type& kf,
                             arg_t<vf_type> x);

            // argument reduction for %e^(xh+xl) and %e^(xh+xl)-1
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/2, log(2)/2] for calling __exp_k
            // the return type must match the type of the k
            // argument of __exp_k
            static
            vi_type
            __reduce_exp_arg(vf_type& xrh,
                             vf_type& xrl,
                             vf_type& kf,
                             arg_t<vf_type> xh,
                             arg_t<vf_type> xl);

            // calculates %e^x-1 if exp_m1 == true %e^x otherwise
            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            // calculates %e^(-x*x)
            static
            vf_type
            exp_mx2_k(arg_t<vf_type> x);

            // calculates %e^(x*x)
            static
            vf_type
            exp_px2_k(arg_t<vf_type> x);

            // calculates 2^x-1 if exp_m1 == true 2^x otherwise
            template <bool _EXP2_M1>
            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            // calculates 2^(-x*x)
            static
            vf_type
            exp2_mx2_k(arg_t<vf_type> x);

            // calculates 2^(x*x)
            static
            vf_type
            exp2_px2_k(arg_t<vf_type> x);

            // calculates 10^x-1 if exp_m1 == true 10^x otherwise
            template <bool _EXP10_M1>
            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            // calculates 10^(-x*x)
            static
            vf_type
            exp10_mx2_k(arg_t<vf_type> x);

            // calculates 10^(x*x)
            static
            vf_type
            exp10_px2_k(arg_t<vf_type> x);

            enum hyperbolic_func {
                c_sinh,
                c_cosh,
                c_tanh
            };

            template <hyperbolic_func _F>
            static
            vf_type
            hyperbolic_k(arg_t< vf_type > xc);

            static
            vf_type
            sinh_k(arg_t<vf_type> x);

            static
            vf_type
            cosh_k(arg_t<vf_type> x);

            static
            vf_type
            tanh_k(arg_t<vf_type> x);

            static
            vf_type
            old_sinh_k(arg_t<vf_type> x);

            static
            vf_type
            old_tanh_k(arg_t<vf_type> x);

            static
            vf_type
            old_cosh_k(arg_t<vf_type> x);

            // polynomial approximation of log(1+f) with
            // s = f/(2.0+f) and z = s*s;
            static
            vf_type
            log_k_poly(arg_t<vf_type> z);

            enum log_func {
                c_log_e,
                c_log_2,
                c_log_10
            };

            static
            vf_type
            log_k(arg_t<vf_type> x, log_func f=log_func::c_log_e);

            static
            vf_type
            log1p_k(arg_t<vf_type> x);

            static
            vf_type
            log2_k(arg_t<vf_type> x);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/2, log(2)/2], and the arguments
            // kf and k as argument for scale_exp_k
            // calculates %e^(xrh+xrl)*2^k
            static
            vf_type
            __pow_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vf_type> kf, arg_t<vi_type> k,
                        vf_type* exl=nullptr);

            static
            dvf_type
            __pow_log2_k(arg_t<vf_type> x);

            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y);

            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static
            std::pair<dvf_type, vi_type>
            reduce_trig_arg_k(arg_t<vf_type> x);

            // calculates sin(xh, xl) in [+0, pi/4]
            static
            vf_type
            __sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates cos(xh, xl) in [+0, pi/4]
            static
            vf_type
            __cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates tan(xh, xl) in [+0, pi/4] and
            // returns tan or -1/tan if q & 1
            static
            vf_type
            __tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl,
                    arg_t<vi_type> q);

            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tan_k(arg_t<vf_type> x);

            static
            vf_type
            atan_k(arg_t<vf_type> x);

            static
            vf_type
            atan2_k(arg_t<vf_type> y, arg_t<vf_type> x);

            static
            vf_type
            asin_k_poly(arg_t<vf_type> z2);

            static
            vf_type
            asin_k(arg_t<vf_type> x);

            static
            vf_type
            acos_k(arg_t<vf_type> x);

            static
            vf_type
            asinh_k(arg_t<vf_type> x);

            static
            vf_type
            acosh_k(arg_t<vf_type> x);

            static
            vf_type
            atanh_k(arg_t<vf_type> x);

        };
    }
}

template <typename _T>
inline
typename
cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
pow2i(arg_t<vi_type> vi)
{
    vi_type e(vi + vi_type(_T::bias));
    vf_type r(_T::insert_exp(e));
    vmi_type mi;
    vmf_type mf;
    mi= (vi < vi_type(_T::e_min));
    mf= _T::vmi_to_vmf(mi);
    r= _T::sel_zero_or_val(mf, r);
    mi= (vi > vi_type(_T::e_max));
    mf= _T::vmi_to_vmf(mi);
    vf_type inf(_T::pinf());
    r= _T::sel(mf, vf_type(inf), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc)
{
    vi_type ux=_T::as_int(xc);
    vi_type uy=_T::as_int(yc);
    vi_type ax= ux & not_sign_f32_msk::v.s32();
    vi_type ay= uy & not_sign_f32_msk::v.s32();
    vi_type ux_inc= ux + 1;
    vi_type ux_dec= ux - 1;
    // decrement required if ax > ay or (ux^uy & sgn) != 0
    vmi_type opp_sgn=
        vi_type((ux^uy) & sign_f32_msk::v.s32()) != vi_type(0);
    vi_type r= _T::sel((ax > ay) | opp_sgn, ux_dec, ux_inc);
    vi_type r0= _T::sel(ay == 0, uy, (uy & sign_f32_msk::v.s32()) | 1);
    r = _T::sel(ax == 0, r0, r);
    r = _T::sel(ux == uy, uy, r);
    vf_type rf=_T::as_float(r);
    return rf;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    vf_type xs=x;
    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();

    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    vi_type eo= _T::sel_val_or_zero(i_is_denom, vi_type(-25));
    // mantissa
    vi_type m=_T::as_int(xs);
    vi_type xe=((m>>23) & 0xff) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi_type nn= min(vi_type(4096), max(n, vi_type(-4096)));
    vi_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0xff normal result
    //     re >= 0xff inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

    // clear exponent bits from m
    m &= vi_type(~0x7f800000);

    // mantissa for normal results:
    vi_type mn= m | ((re & vi_type(0xff)) << 23);
    vf_type r= _T::as_float(mn);

    // overflow handling
    vmi_type i_is_inf = re > vi_type(0xfe);
    vmf_type f_is_inf = _T::vmi_to_vmf(i_is_inf);
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi_type i_is_near_z = re < vi_type (1);
    if (any_of(i_is_near_z)) {
        // create m*0x1.0p-126
        vi_type mu= m | vi_type(1<<23);
        vf_type r_u= _T::as_float(mu);
        // create a scaling factor
        vi_type ue= max(vi_type(re + (_T::bias()-1)), vi_type(1));
        vf_type s_u= _T::as_float(vi_type(ue << 23));
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi_to_vmf(i_is_near_z);
        r = _T::sel(f_is_near_z, r_u, r);
    }
    // handle special cases:
    r = _T::sel(isinf(x) | isnan(x) | (x==vf_type(0.0)),
                x, r);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__frexp_k(vf_type& m, arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    vi_type eo= _T::sel_val_or_zero(i_is_denom, vi_type(-25));
    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) & 0xff) + eo - vi_type(_T::bias()-1);
    // insert exponent
    i = (i & vi_type(0x807fffff)) | vi_type(0x7e<<23);
    m= _T::as_float(i);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vf_type xs=x;

    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();

    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    vi_type eo= _T::sel_val_or_zero(i_is_denom, vi_type(-25));

    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) & 0xff) + eo;

    // insert exponent
    i = (i & vi_type(0x807fffff)) | vi_type(0x7e<<23);
    // interpret as float
    vf_type frc(_T::as_float(i));
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    frc = _T::sel(f_inz, x, frc);
    if (ve != nullptr) {
        vmi_type i_inz=_T::vmf_to_vmi(f_inz);
        e -= vi_type(_T::bias()-1);
        e= _T::sel_zero_or_val(i_inz, e);
        *ve= e;
    }
    return frc;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
ilogbp1(arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-25), eo);
    // reinterpret as integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) & 0xff) + eo - vi_type(_T::bias()-1);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(ilogbp1(abs(d)) -1);
    vmf_type mf= d == 0.0f;
    vmi_type mi= _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(0x7fffffff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(FP_ILOGBNAN), e);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
rsqrt_k(arg_t<vf_type> x)
{
#if 1
#if 1
    const float large = 0x1p64f;
    const float small = 0x1p-64f;
    const float rsqrt_large = 0x1p-32f;
    const float rsqrt_small = 0x1p32f;
    vmf_type x_large= x >= large;
    vmf_type x_small= x <= small;
    vf_type xr = _T::sel(x_large, x* small, x);
    vf_type s = _T::sel(x_large, rsqrt_large, 1.0);
    xr = _T::sel(x_small, x*large, xr);
    s = _T::sel(x_small, rsqrt_small, s);
    vf_type y = native_rsqrt(xr);
    vf_type yh, yl;
    d_ops::mul12(yh, yl, xr, y);
    d_ops::mul122(yh, yl, y, yh, yl);
    d_ops::add122(yh, yl, -1.0, yh, yl);
    y = y + (-0.5f*y)*yh;
    y *= s;
#else
    vf_type y= vf_type(1.0/sqrt(x));
    // y = y + 0.5* y * (vf_type(1) - d_ops::mul(x, y)*y).h();
    vf_type yh, yl;
    d_ops::mul12(yh, yl, x, y);
    d_ops::mul122(yh, yl, y, yh, yl);
    d_ops::add122(yh, yl, -1.0, yh, yl);
    y = y + (-0.5*y)*yh;
#endif
#else
    // m in [0.5, 1)
    vf_type mm0;
    auto e=__frexp_k(mm0, x);
    vi_type e1= e & 1;
    vmi_type msk = e1 == 1;
    // const divisor<vi_type, int32_t> idiv2(2);
    // vi_type e2= e / idiv2;
    // correction of the exponent only required for positve e
    // because of the signed division above
    // vi_type e2c= _T::sel(msk & vmi_type (e>0), e2+1, e2);
    vi_type e2 = e>>1;
    vi_type e2c= e2 + e1; // _T::sel(msk, e2+1, e2);
    vmf_type f_msk = _T::vmi_to_vmf(msk);
    mm0 = _T::sel(f_msk, mm0*0.5, mm0);
#if 0
    vf_type mm=native_rsqrt(mm0);
    mm = mm + 0.5* mm *
        (vf_type(1) - d_ops::mul(mm0, mm)*mm).h();
    vf_type t= _T::insert_exp(_T::bias()-e2c);
    // mm = ldexp_k(mm, -e2c);
    vf_type y= mm*t;
#else
#if 0
    // [0.25, 0.5] : | p - f | <= 2^-10.02734375
    // coefficients for rsqrt generated by sollya
    // x^0 : +0xe.bce4cp-2f
    const float rsqrt_i0_c0=+3.6844663620e+00f;
    // x^1 : -0xa.4b628p+0f
    const float rsqrt_i0_c1=-1.0294471741e+01f;
    // x^2 : +0x8.755f5p+1f
    const float rsqrt_i0_c2=+1.6916971207e+01f;
    // x^3 : -0xa.d2d0bp+0f
    const float rsqrt_i0_c3=-1.0823496819e+01f;
    // [0.5, 1] : | p - f | <= 2^-10.52734375
    // coefficients for rsqrt generated by sollya
    // x^0 : +0xa.6bd6ap-2f
    const float rsqrt_i1_c0=+2.6053109169e+00f;
    // x^1 : -0xe.8effp-2f
    const float rsqrt_i1_c1=-3.6396446228e+00f;
    // x^2 : +0xb.f64c5p-2f
    const float rsqrt_i1_c2=+2.9905254841e+00f;
    // x^3 : -0xf.4e86p-4f
    const float rsqrt_i1_c3=-9.5667076111e-01f;
    // x^ : +0x8p-4f
    const float rsqrt_i1_left=+5.0000000000e-01f;
    vf_type mm0sqr=mm0*mm0;
    vf_type mm0half=0.5f*mm0;
    vf_type mm_i0_o=horner(mm0sqr,
                           rsqrt_i0_c3,
                           rsqrt_i0_c1);
    vf_type mm_i0_e=horner(mm0sqr,
                           rsqrt_i0_c2,
                           rsqrt_i0_c0);
    vf_type mm_i1_o=horner(mm0sqr,
                           rsqrt_i1_c3,
                           rsqrt_i1_c1);
    vf_type mm_i1_e=horner(mm0sqr,
                           rsqrt_i1_c2,
                           rsqrt_i1_c0);
    vf_type mm_i0=horner(mm0, mm_i0_o, mm_i0_e);
    vf_type mm_i1=horner(mm0, mm_i1_o, mm_i1_e);
    vf_type mm = _T::sel(mm0 < rsqrt_i1_left, mm_i0, mm_i1);
    // mm = 0.5f *mm*(3.0f - vf_type(mm0 * mm) *mm);
    // mm = mm + 0.5f * mm * (1.0f - mm*mm*mm0);
    // mm= mm + mm * (0.5f - mm*mm*mm0half);
    mm = mm*(1.5f - vf_type(mm0half * mm) *mm);
#else
    // [0.25, 0.46875] : | p - f | <= 2^-7.7109375
    // coefficients for rsqrt generated by sollya
    // x^0 : +0xc.d6a17p-2f
    const float rsqrt_i0_c0=+3.2096002102e+00f;
    // x^1 : -0xc.4e6a9p-1f
    const float rsqrt_i0_c1=-6.1531567574e+00f;
    // x^2 : +0xa.5d871p-1f
    const float rsqrt_i0_c2=+5.1826710701e+00f;
    // [0.46875, 1] : | p - f | <= 2^-7.365234375
    // coefficients for rsqrt generated by sollya
    // x^0 : +0x9.159d5p-2f
    const float rsqrt_i1_c0=+2.2711079121e+00f;
    // x^1 : -0x8.a50f4p-2f
    const float rsqrt_i1_c1=-2.1611909866e+00f;
    // x^2 : +0xe.4ec4ap-4f
    const float rsqrt_i1_c2=+8.9423048496e-01f;
    // x^ : +0xfp-5f
    const float rsqrt_i1_left=+4.6875000000e-01f;
    vf_type mm0half = 0.5f*mm0;
    vf_type mm0s=mm0*mm0;
    vf_type mm_i0= horner(mm0,
                          rsqrt_i0_c1, rsqrt_i0_c0) + mm0s *rsqrt_i0_c2;
    vf_type mm_i1= horner(mm0,
                          rsqrt_i1_c1, rsqrt_i1_c0) + mm0s *rsqrt_i1_c2;
    vf_type mm = _T::sel(mm0 <= rsqrt_i1_left, mm_i0, mm_i1);
    vf_type z = mm * mm * mm0 - 1.0f;
    //mm = mm * horner(z, 3.0f/8.0f, -0.5f, 1.0f);
    vf_type mmz = mm * z;
    mm = mm + mmz * horner(z, 3.0f/8.0f, -0.5f);
#endif
#if 0
    mm = 0.5f * mm * (3.0f - mm0 * mm * mm);
    vf_type s= d_ops::xfma(mm, mm*mm0, -1.0f);
    mm = mm - mm * 0.5f * s;
#else
    // mm= mm + 0.5f * mm * (1.0f - mm*mm*mm0);
#if 1
    vf_type sh, sl;
    d_ops::sqr12(sh, sl, mm);
    d_ops::mul122(sh, sl, -mm0half, sh, sl);
    d_ops::add122(sh, sl, 0.5f, sh, sl);
    mm = mm +sh*mm;
#else
    dvf_type s=vf_type(1.0f) - d_ops::sqr(mm)*mm0;
    mm = mm + 0.5f*mm * s.h();
#endif
#endif
    vf_type t= _T::insert_exp(_T::bias()-e2c);
    // mm = ldexp_k(mm, -e2c);
    vf_type y= mm*t;
#endif
#endif
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);

    // reduce x into [2^-3, 1.0)
    const int32_t shift_1_3 = 9;
    const int32_t fac_1_3 = ((1<<shift_1_3)+2)/3;

    vf_type mm0;
    auto e=__frexp_k(mm0, xp);
    // do a division by 3
    // vi2_type e3 = (((e)*fac_1_3)>>shift_1_3) -(e>>31);
    // do a division by 3 rounded down
    const vi_type v_bias_3(3*_T::bias()), v_bias(_T::bias());
    vi_type e3_with_bias = (((e+v_bias_3)*fac_1_3)>>shift_1_3);
    vi_type e3 = e3_with_bias - v_bias;
    vi_type r = e - e3 - (e3<<1);

    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 3
    // 1    0.25    -2           -2
    // 2    0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
    vmi_type r_ne_z = r != 0;
    e3_with_bias=_T::sel(r_ne_z, e3_with_bias+1, e3_with_bias);

    // log_2(scale) = bias + (r-3) = bias - 3 + r
    const vi_type v_bias_plus_3(_T::bias()-3);
    vf_type scale = _T::insert_exp(v_bias_plus_3 + r);
    vmf_type f_r_ne_z = _T::vmi_to_vmf(r_ne_z);
    scale = _T::sel(f_r_ne_z, scale, 1.0);
    mm0 = mm0 * scale;

    // [0.125, 1] : | p - f | <= 2^-4.123046875
    // coefficients for cbrt generated by sollya
    // x^0 : +0xe.8050fp-5f
    const vf_type cbrt_c0=+4.5316359401e-01f;
    // x^1 : +0x9.aae0ap-4f
    const vf_type cbrt_c1=+6.0421812534e-01f;
    vf_type mm = horner(mm0,
                        cbrt_c1,
                        cbrt_c0);
    // 1st iteration
    mm = impl::root3::order3<float>(mm, mm0);
#if 1
    // round mm to 8 bits = int(24)/3
    mm = rint(vf_type(mm*0x1p8f))*0x1p-8f;
#else
    vi_type hw=_T::as_int(mm);
    // round mm to 8 bits (including the hidden one)
    // round up if the first bit truncated is set
    // hw += hw & 0x0008000;
    vi_type corr= hw & 0x000008000;
    // vi_type corr= hw & 0x0000e000;
    // vmi_type m=(vi_type(hw & 0x0001e000) != vi_type(0x00008000)) &
    //    (corr != vi_type(0));
    // corr= _T::sel(m, vi_type(0x00008000), vi_type(0));
    hw += corr;
    hw &= 0xffff0000;
    mm=_T::as_float(hw);
#endif
    // second iteration
    mm = impl::root3::order5<float>(mm, mm0);
    // no denormal results are possible
    // vf_type t= _T::insert_exp(_T::bias()+e3c);
    vf_type t= _T::insert_exp(e3_with_bias);
    mm *=t;
    mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
root12_k(arg_t<vf_type> xc)
{
    // reduce x into [2^-12, 1.0)
    const int32_t shift_1_12= 0x11;
    const int32_t fac_1_12= 0x2aab;

    vf_type xp=abs(xc);
    vf_type mm0;
    auto e=__frexp_k(mm0, xp);
    // do a division by 3
    // vi2_type e3 = (((e)*fac_1_3)>>shift_1_3) -(e>>31);
    // do a division by 3 rounded to - infinity
    const vi_type v_bias_12(12*_T::bias()), v_bias(_T::bias());
    vi_type e12_with_bias = (((e+v_bias_12)*fac_1_12)>>shift_1_12);
    vi_type e12 =e12_with_bias - v_bias;
    // r is always in [0, 1, 11] because of the round down
    vi_type r = e - e12 *12;

    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 12
    // 1    ...     -11          -11
    // 2            -10
    // 3            -9
    // 4            -8           ....
    // 5            -7
    // 6            -6
    // 7            -5
    // 8            -4
    // 9            -3
    // 10   0.25    -2           -2
    // 11   0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
    vmi_type r_ne_z = r != 0;
    e12_with_bias=_T::sel(r_ne_z, e12_with_bias+1, e12_with_bias);

    // log_2(scale) = bias + (r-12) = bias - 12 + r
    const vi_type v_bias_plus_12(_T::bias()-12);
    vf_type scale = _T::insert_exp(v_bias_plus_12 + r);
    vmf_type f_r_ne_z = _T::vmi_to_vmf(r_ne_z);
    scale = _T::sel(f_r_ne_z, scale, 1.0);
    mm0 = mm0 * scale;

    // [2.44140625e-4, 1.953125e-3] : | p - f | <= 2^-8.08984375
    // coefficients for root12_i0 generated by sollya
    // x^0 : +0xf.3c1f4p-5f
    const float root12_i0_c0=+4.7608911991e-01f;
    // x^1 : +0xe.bf4cfp+3f
    const float root12_i0_c1=+1.1797814178e+02f;
    // x^2 : -0xe.cb641p+11f
    const float root12_i0_c2=-3.0299126953e+04f;
    // [1.953125e-3, 1.5625e-2] : | p - f | <= 2^-7.83984375
    // coefficients for root12_i1 generated by sollya
    // x^0 : +0x9.0f06cp-4f
    const float root12_i1_c0=+5.6616854668e-01f;
    // x^1 : +0x8.c4cedp+1f
    const float root12_i1_c1=+1.7537561417e+01f;
    // x^2 : -0x8.cbff5p+6f
    const float root12_i1_c2=-5.6299932861e+02f;
    // [1.5625e-2, 0.125] : | p - f | <= 2^-7.58984375
    // coefficients for root12_i2 generated by sollya
    // x^0 : +0xa.c5cd8p-4f
    const float root12_i2_c0=+6.7329168320e-01f;
    // x^1 : +0xa.6d8a8p-2f
    const float root12_i2_c1=+2.6069736481e+00f;
    // x^2 : -0xa.76173p+0f
    const float root12_i2_c2=-1.0461291313e+01f;
    // [0.125, 1] : | p - f | <= 2^-7.33984375
    // coefficients for root12_i3 generated by sollya
    // x^0 : +0xc.cf994p-4f
    const float root12_i3_c0=+8.0068325996e-01f;
    // x^1 : +0xc.66a31p-5f
    const float root12_i3_c1=+3.8752892613e-01f;
    // x^2 : -0xc.70cddp-6f
    const float root12_i3_c2=-1.9438500702e-01f;
    vf_type mm_i0 = horner(mm0,
                           root12_i0_c2,
                           root12_i0_c1,
                           root12_i0_c0);
    vf_type mm_i1 = horner(mm0,
                           root12_i1_c2,
                           root12_i1_c1,
                           root12_i1_c0);
    vf_type mm_i2 = horner(mm0,
                           root12_i2_c2,
                           root12_i2_c1,
                           root12_i2_c0);
    vf_type mm_i3 = horner(mm0,
                           root12_i3_c2,
                           root12_i3_c1,
                           root12_i3_c0);
    vf_type mm= _T::sel(mm0 < 0x1p-3f, mm_i2, mm_i3);
    mm= _T::sel(mm0 < 0x1p-6f, mm_i1, mm);
    mm = _T::sel(mm0 < 0x1p-9f, mm_i0, mm);
#if 1
    mm = impl::root12::householder4<float>(mm, mm0);
#else
    mm = impl::root12::nr<float>(mm, mm0);
    mm = impl::root12::order3<float>(mm, mm0);
#endif
    vf_type t= _T::insert_exp(e12_with_bias);
    mm *=t;
    // mm = copysign(mm, xc);
    return mm;
}


template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__scale_exp_k(arg_t<vf_type> ym, arg_t<vf_type> kf, arg_t<vi_type> k)
{
#if 1
    // avoid subnormals
    vmi_type k_lt_m_125 = k < -125;
    vi_type ep = _T::sel(k_lt_m_125, k+64, k);
    vf_type two_pow_k= _T::insert_exp(_T::bias()+ep);
    // start scaling
    vf_type ys= ym * two_pow_k;
    // avoid overflows
    ys = _T::sel(kf >= vf_type(128),
                 ym * 2.0f * 0x1p127f,
                 ys);
    // correct subnormal results
    vmf_type kf_lt_m_125= _T::vmi_to_vmf(k_lt_m_125);
    ys = _T::sel(kf_lt_m_125, ys* 0x1p-64f, ys);
    return ys;
#else
    vi_type e_two_pow_k=_T::sel(k < vi_type(-125),
                                vi_type((_T::bias()+100)),
                                vi_type(_T::bias())) +k;
    vf_type two_pow_k= _T::insert_exp(e_two_pow_k);
    // kf == 128f or kf>=-125
    vf_type ymt=ym*two_pow_k;
    vf_type yt= _T::sel(kf == vf_type(128),
                        ym * 2.0f * 0x1p127f,
                        ymt);
    vf_type y = _T::sel(kf < vf_type(-125),
                        ymt*0x1p-100f, yt);
    return y;
#endif
}

template <typename _T>
template <bool _EXP_M1>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
        arg_t<vf_type> kf, arg_t<vi_type> k)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-32.609375
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3f
    const float exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    const float exp_c2=+5.0000000000e-01f;
    // x^3 : +0xa.aaaa9p-6f
    const float exp_c3=+1.6666664183e-01f;
    // x^4 : +0xa.aaa73p-8f
    const float exp_c4=+4.1666459292e-02f;
    // x^5 : +0x8.88ae5p-10f
    const float exp_c5=+8.3338962868e-03f;
    // x^6 : +0xb.6a77ep-13f
    const float exp_c6=+1.3935414609e-03f;
    // x^7 : +0xc.d3317p-16f
    const float exp_c7=+1.9569355936e-04f;

    vf_type xx= xrh*xrh;
    vf_type i=horner(xx,
                     exp_c7,
                     exp_c5);
    vf_type j=horner(xx,
                     exp_c6,
                     exp_c4);
    vf_type y= horner(xrh, i, j, exp_c3, exp_c2);
    vf_type ye;
    if (_EXP_M1 == false) {
        y *= xrh;
        d_ops::add12(y, ye, exp_c1, y);
    } else {
        horner_comp_quick(y, ye, xrh, y, exp_c1);
    }
    // calculate expm1/xrh for correction term
    vf_type yl=y+ye;
    horner_comp_quick_si(y, ye, xrh, y, ye, exp_c0);
    // correction for errors in argument reduction
    vf_type yee= xrl + xrl*xrh*yl;
    ye += yee;
    if (_EXP_M1 == false) {
        y += ye;
        y = __scale_exp_k(y, kf, k);
    } else {
        // 2^kf = 2*2^s ; s = kf/2
        // e^x-1 = 2*(y * 2^s - 0.5)
        vf_type scale = __scale_exp_k(vf_type(0.5f), kf, k);
#if 1
        y  *= scale;
        vf_type t;
        d_ops::add12cond(y, t, -0.5, y);
        ye = 2.0*(ye * scale + t);
        y = 2.0*y + ye;
#else
        horner_comp_si(y, ye, scale, y, ye, vf_type(-0.5f));
        y *= 2;
        y  = y + 2*ye;
#endif
        // x small
        y = _T::sel((abs(xrh) < 0x1p-25f) & (kf==0.0), xrh, y);
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    kf = rint(vf_type(x * ctbl::m_1_ln2.h()));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    xrh = hi - kf * ctbl::m_ln2_cw[1];
    vi_type k= _T::cvt_f_to_i(kf);
    vf_type dx = hi-xrh;
    xrl = dx - kf * ctbl::m_ln2_cw[1];
    return k;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> xh,
                 arg_t<vf_type> xl)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    kf = rint(vf_type(xh * ctbl::m_1_ln2.h()));
    vf_type neg_kfln2h, neg_kfln2l;
    d_ops::mul122(neg_kfln2h, neg_kfln2l,
                  kf, -ctbl::m_ln2.h(), -ctbl::m_ln2.l());
    d_ops::add22cond(xrh, xrl,
                     xh, xl,
                     neg_kfln2h, neg_kfln2l);
    vi_type k= _T::cvt_f_to_i(kf);
    return k;
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl, kf;
    auto k=__reduce_exp_arg(xrh, xrl, kf, xc);
    vf_type y=__exp_k<_EXP_M1>(xrh, xrl, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp_mx2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type xrh, xrl, kf;
    auto k=__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type y= __exp_k<false>(xrh, xrl, kf, k);
    using fc_t = math::func_constants<float>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp_px2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);
    using fc_t = math::func_constants<float>;
    vmf_type border_case = (x2h == fc_t::exp_hi_inf()) &
        (x2l < 0.0);
    vf_type t= 0x1.02p-17f;
    x2h = _T::sel(border_case, x2h - t, x2h);
    x2l = _T::sel(border_case, x2l + t, x2l);

    vf_type xrh, xrl, kf;
    auto k=__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type y= __exp_k<false>(xrh, xrl, kf, k);
    y= _T::sel(x2h >= fc_t::exp_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type kf= rint(vf_type(x));
    vi_type k = _T::cvt_f_to_i(kf);
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type xr = x - kf;
    vf_type xrh, xrl;
    // for exp2 mul12 would be sufficient
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2.h(), ctbl::m_ln2.l());
    vf_type y=__exp_k<_EXP2_M1>(xrh, xrl, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp2_mx2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type kf = rint(vf_type(x2h));
    vi_type k = _T::cvt_f_to_i(kf);
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, -kf, x2h, x2l);
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln2.h(), ctbl::m_ln2.l());
    vf_type y= __exp_k<false>(xrh, xrl, kf, k);
    using fc_t = math::func_constants<float>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp2_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp2_px2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);
    vf_type kf = rint(vf_type(x2h));
    vi_type k = _T::cvt_f_to_i(kf);
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, -kf, x2h, x2l);
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln2.h(), ctbl::m_ln2.l());
    vf_type y= __exp_k<false>(xrh, xrl, kf, k);
    using fc_t = math::func_constants<float>;
    y= _T::sel(x2h >= fc_t::exp2_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp10_k(arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x * ctbl::m_1_lg2.h()));
    vf_type hi = x - kf * ctbl::m_lg2_cw[0];
    vf_type xr = hi - kf * ctbl::m_lg2_cw[1];
    vi_type k= _T::cvt_f_to_i(kf);
    vf_type dx= (hi-xr);
    vf_type cr = dx-kf * ctbl::m_lg2_cw[1];
    vf_type xrh, xrl;
    // for exp10 mul12 would be sufficient
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln10.h(), ctbl::m_ln10.l());
    xrl += cr * ctbl::m_ln10.h();
    // do not normalize xrh, xrl
    // d_ops::add12(xrh, xrl, xrh, xrl);
    vf_type y=__exp_k<_EXP10_M1>(xrh, xrl, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp10_mx2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x2h*ctbl::m_1_lg2.h()));
    vi_type k = _T::cvt_f_to_i(kf);
    vf_type neg_kfln10h, neg_kfln10l;
    d_ops::mul122(neg_kfln10h, neg_kfln10l,
                  kf, -ctbl::m_lg2.h(), -ctbl::m_lg2.l());
    vf_type xrh, xrl;
    d_ops::add22cond(xrh, xrl,
                     x2h, x2l,
                     neg_kfln10h, neg_kfln10l);
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln10.h(), ctbl::m_ln10.l());
    vf_type y= __exp_k<false>(xrh, xrl, kf, k);
    using fc_t = math::func_constants<float>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp10_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp10_px2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);

    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x2h*ctbl::m_1_lg2.h()));
    vi_type k = _T::cvt_f_to_i(kf);
    vf_type neg_kfln10h, neg_kfln10l;
    d_ops::mul122(neg_kfln10h, neg_kfln10l,
                  kf, -ctbl::m_lg2.h(), -ctbl::m_lg2.l());
    vf_type xrh, xrl;
    d_ops::add22cond(xrh, xrl,
                     x2h, x2l,
                     neg_kfln10h, neg_kfln10l);
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln10.h(), ctbl::m_ln10.l());
    vf_type y= __exp_k<false>(xrh, xrl, kf, k);
    using fc_t = math::func_constants<float>;
    y= _T::sel(x2h >= fc_t::exp10_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <enum cftal::math::elem_func_core<float, _T>::hyperbolic_func _F>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
hyperbolic_k(arg_t<vf_type> xc)
{
    vf_type x= abs(xc);
    vf_type xrh, xrl, kf;
    auto k= __reduce_exp_arg(xrh, xrl, kf, x);

    vf_type scale=_T::sel(kf >= 128, 2.0f, 1.0f);
    auto kn= _T::sel(k>= 128, k-1, k);

    // filter out large arguments for tanh
    vmf_type kf_le_13 = kf <= 13.0;
    bool any_of_kf_le_13 = any_of(kf_le_13);
    if (_F == hyperbolic_func::c_tanh) {
        if (!any_of_kf_le_13) {
            vf_type tanh_x = copysign(vf_type(1.0), xc);
            return tanh_x;
        }
    }
    // calculate 2^(k-1)
    vf_type two_pow_plus_k_minus_1 = _T::insert_exp((_T::bias()-1) + kn);
    // calculate sinh + cosh
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-36.71875
    // coefficients for sinh generated by sollya
    // x^1 : +0x8p-3f
    const float sinh_c1=+1.0000000000e+00f;
    // x^3 : +0xa.aaaabp-6f
    const float sinh_c3=+1.6666667163e-01f;
    // x^5 : +0x8.887fp-10f
    const float sinh_c5=+8.3331912756e-03f;
    // x^7 : +0xd.149ebp-16f
    const float sinh_c7=+1.9959329802e-04f;
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-33.171875
    // coefficients for cosh generated by sollya
    // x^0 : +0x8p-3f
    const float cosh_c0=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    const float cosh_c2=+5.0000000000e-01f;
    // x^4 : +0xa.aaa72p-8f
    const float cosh_c4=+4.1666455567e-02f;
    // x^6 : +0xb.6a8a3p-13f
    const float cosh_c6=+1.3935755705e-03f;

    vf_type xx= xrh*xrh;
    vf_type rsh= horner(xx,
                        sinh_c7,
                        sinh_c5,
                        sinh_c3);
    vf_type rsh_h, rsh_l;
    horner_comp_quick(rsh_h, rsh_l, xx, rsh, sinh_c1);
    d_ops::mul122(rsh_h, rsh_l, xrh, rsh_h, rsh_l);

    vf_type rch= horner(xx,
                        cosh_c6,
                        cosh_c4,
                        cosh_c2);
    vf_type rch_h, rch_l;
    horner_comp_quick(rch_h, rch_l, xx, rch, cosh_c0);

    // correction of argument reduction errors:
    // cosh(x+y) \approx cosh(y) + sinh(y) x
    // sinh(x+y) \approx sinh(y) + cosh(y) x
    vf_type rch_corr= rsh_h* xrl;
    vf_type rsh_corr= rch_h* xrl;
    rch_l += rch_corr;
    d_ops::add12(rch_h, rch_l, rch_h, rch_l);
    rsh_l += rsh_corr;
    d_ops::add12(rsh_h, rsh_l, rsh_h, rsh_l);

    // cosh(x + y) = cosh(x) cosh(y) + sinh(x)*sinh(y)
    // sinh(x + y) = sinh(x) cosh(y) + sinh(x)*cosh(y);
    // cosh(k * ln(2)) = 2^(k-1) + 2^(-k-1)
    // sinh(k * ln(2)) = 2^(k-1) - 2^(-k-1)

    vf_type two_pow_km1_rch_h = two_pow_plus_k_minus_1 * rch_h;
    vf_type two_pow_km1_rch_l = two_pow_plus_k_minus_1 * rch_l;

    vf_type two_pow_km1_rsh_h= two_pow_plus_k_minus_1 * rsh_h;
    vf_type two_pow_km1_rsh_l= two_pow_plus_k_minus_1 * rsh_l;

    vf_type cosh_h, cosh_l;
    // |rch| > |rsh|
    d_ops::add22(cosh_h,
                 cosh_l,
                 two_pow_km1_rch_h, two_pow_km1_rch_l,
                 two_pow_km1_rsh_h, two_pow_km1_rsh_l);
    vf_type sinh_h = cosh_h;
    vf_type sinh_l = cosh_l;

    const bool calc_sinh=_F == hyperbolic_func::c_sinh ||
        _F == hyperbolic_func::c_tanh;
    const bool calc_cosh=_F == hyperbolic_func::c_cosh ||
        _F == hyperbolic_func::c_tanh;

    // filter out small terms
    if (likely(any_of_kf_le_13)) {
        // calculate 2^(-k-1)
        vf_type two_pow_minus_k_minus_1 = _T::insert_exp((_T::bias()-1) - kn);
        two_pow_minus_k_minus_1= _T::sel_val_or_zero(kf_le_13,
                                                     two_pow_minus_k_minus_1);
        vf_type two_pow_mkm1_rch_h = two_pow_minus_k_minus_1 * rch_h;
        vf_type two_pow_mkm1_rch_l = two_pow_minus_k_minus_1 * rch_l;
        vf_type two_pow_mkm1_rsh_h = two_pow_minus_k_minus_1 * rsh_h;
        vf_type two_pow_mkm1_rsh_l = two_pow_minus_k_minus_1 * rsh_l;
        if (calc_sinh) {
            vf_type th, tl;
            // |rch| >  |rsh|
            d_ops::add22(th, tl,
                         -two_pow_mkm1_rch_h, -two_pow_mkm1_rch_l,
                         two_pow_mkm1_rsh_h, two_pow_mkm1_rsh_l);
            // k ==0 --> rch>=1, rsh>=0:
            //            (rch + rsh) * 2^(-1)  + (-rch + rsh) * 2^(-1)
            // otherwise: (rch + rsh) * 2^(k-1) + (-rch + rsh) * 2^(-k-1)
            d_ops::add22(sinh_h, sinh_l,
                         sinh_h, sinh_l,
                         th, tl);
        }
        if (calc_cosh) {
            vf_type th, tl;
            // |rch| >  |rsh|
            d_ops::add22(th, tl,
                         two_pow_mkm1_rch_h, two_pow_mkm1_rch_l,
                         -two_pow_mkm1_rsh_h, -two_pow_mkm1_rsh_l);
            // k ==0 --> rch>=1, rsh>=0:
            //            (rch + rsh) * 2^(-1)  + (rch - rsh) * 2^(-1)
            // otherwise: (rch + rsh) * 2^(k-1) + (rch - rsh) * 2^(-k-1)
            d_ops::add22(cosh_h, cosh_l,
                         cosh_h, cosh_l,
                         th, tl);
        }
    }
    vf_type r;
    if (_F == hyperbolic_func::c_sinh) {
        vf_type sinh_x = sinh_h*scale;
        sinh_x = _T::sel(x < 0x1p-13f, x, sinh_x);
        sinh_x = copysign(sinh_x, xc);
        r = sinh_x;
    }
    if (_F == hyperbolic_func::c_cosh) {
        vf_type cosh_x = cosh_h*scale;
        r = cosh_x;
    }
    if (_F == hyperbolic_func::c_tanh) {
        dvf_type s(sinh_h, sinh_l), c(cosh_h, cosh_l);
        dvf_type t=d_ops::sloppy_div(s, c);
        vf_type tanh_x=_T::sel(kf_le_13, t.h(), 1.0);
        tanh_x = _T::sel(x < 0x1p-13f, x, tanh_x);
        tanh_x = copysign(tanh_x, xc);
        r = tanh_x;
    }
    return r;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
cosh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_cosh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
sinh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_sinh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
tanh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_tanh>(x);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
old_sinh_k(arg_t<vf_type> xc)
{
    // for huge arguments:
    // sinh(x) = sgn(x) [e^y + ((e^v)/2 -1)e^y - (e^-v)/2)e^-y]
    // y= |x| -v
    // ln(2) <= v <= ln(3) for base 2
    // ln(2) <= v <= ln(2.125) for other bases
    // (e^v)/2 - 1 < 1/ß
    // chosing v=0.75 (2 bits set)
    // between 1 and overflow of expm(1):
    // sinh (x) = 1/2 (exp(x) - exp(-x))
    //          = (expm1(x) + (expm1(x)/(expm1(x)+1))/2;
    vf_type x = abs(xc);
    using fc=func_constants<float>;
    vmf_type x_huge = x >= fc::exp_hi_inf();
    // between 0 and 1
    // sinh(x) = x + x^3/Q(x^2)
    // [3.4694469519536141888238489627838134765625e-18, 1] : | p - f | <= 2^-26
    // coefficients for sinh generated by sollya
    // x^0 : +0xcp-1f
    const vf_type sinh_c0=+6.0000000000e+00f;
    // x^2 : -0x9.9999p-5f
    const vf_type sinh_c2=-2.9999971390e-01f;
    // x^4 : +0x8.0b43dp-10f
    const vf_type sinh_c4=+7.8554721549e-03f;
    // x^6 : -0x8.a845cp-16f
    const vf_type sinh_c6=-1.3210013276e-04f;
    vf_type x2=x*x;
    vf_type q=horner(x2,
                     sinh_c6,
                     sinh_c4,
                     sinh_c2,
                     sinh_c0);
    vf_type sinh_le_1 = x + (x*x2)/q;
    vf_type xr= _T::sel(x_huge, x - 0.75, x);
    vf_type em=exp_k<true>(xr);
    vf_type e= em+1;
    const vf_type e_v_2_m_1 = +5.8500006794930e-02f;
    const vf_type e_m_v_2 = +2.3618327081203e-01f;
    vf_type sinh_gt_1 = 0.5 * (em + em/e);
    vf_type sinh_huge = e + e_v_2_m_1 * e - e_m_v_2 / e;
    vf_type sinh_x = _T::sel(x<=1.0, sinh_le_1, sinh_gt_1);
    sinh_x = _T::sel(x_huge, sinh_huge, sinh_x);
    vf_type y = copysign(sinh_x, xc);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
old_cosh_k(arg_t<vf_type> xc)
{
    // for really large arguments:
    // cosh(x) = sgn(x) [e^y + ((e^v)/2 -1)e^y + (e^-v)/2)e^-y]
    // y= |x| -v
    // ln(2) <= v <= ln(3) for base 2
    // ln(2) <= v <= ln(2.125) for other bases
    // (e^v)/2 - 1 < 1/ß
    // chosing v=0.75 (2 bits set)
    // between log(2) and overflow of expm(1):
    // cosh (x) = 1/2 (exp(x) + exp(-x))
    //          = 1 + (expm1(x)/(expm1(x)+1))/2;
    vf_type x=abs(xc);
    using fc=func_constants<float>;
    vmf_type x_huge = x >= fc::exp_hi_inf();
    /*
      cosh(x) = 1 + x^2/2 + x^4/24 ...
      cosh(x)-1) = x^2*R
      R= f(x^2)
      cosh(x)-1)/(x^2)= R
    */
    // [3.4694469519536141888238489627838134765625e-18, 0.693147182464599609375] : | p - f | <= 2^-32.59375
    // coefficients for cosh generated by sollya
    // x^0 : +0x8p-4f
    const vf_type cosh_c0=+5.0000000000e-01f;
    // x^2 : +0xa.aaaacp-8f
    const vf_type cosh_c2=+4.1666671634e-02f;
    // x^4 : +0xb.6092p-13f
    const vf_type cosh_c4=+1.3888217509e-03f;
    // x^6 : +0xd.22546p-19f
    const vf_type cosh_c6=+2.5051307603e-05f;
    vf_type xx= x*x;
    vf_type cosh_le_ln2 = 1.0 + xx*horner(xx,
                                          cosh_c6,
                                          cosh_c4,
                                          cosh_c2,
                                          cosh_c0);
    vf_type xr= _T::sel(x_huge, x - 0.75, x);
    vf_type em=exp_k<true>(xr);
    vf_type e=em+1;
    const vf_type e_v_2_m_1 = +5.8500006794930e-02f;
    const vf_type e_m_v_2 = +2.3618327081203e-01f;
    vf_type cosh_gt_ln2 = 0.5 * (e + 1/e);
    vf_type cosh_huge = e + (e_v_2_m_1 * e - e_m_v_2 / e);
    vf_type cosh_x = _T::sel(x <= M_LN2, cosh_le_ln2, cosh_gt_ln2);
    cosh_x = _T::sel(x_huge, cosh_huge, cosh_x);
    return cosh_x;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
old_tanh_k(arg_t<vf_type> xc)
{
    /* tanh(x) = (exp(x) - exp(-x))/(exp(x) + exp(-x))
     *         = (exp(2*x) - 1)/(exp(2*x) - 1 + 2)
     *         = (1 - exp(-2*x))/(exp(-2*x) - 1 + 2)
     */
    vf_type x= abs(xc);
    // using fc=func_constants<double>;
    vmf_type x_gt_20 = x >= 20.0f;
    vf_type tanh_x_gt_20 = 1.0f;
    vf_type x2=2.0f*x;
    vf_type em= exp_k<false>(x2);
    vmf_type x_gt_ln_3_2= x > 0.5625f;
    // produce a faithfully rounded tanh:
    vf_type emp1l, emp1h=d_ops::quick_two_sum(em, vf_type(1.0f), emp1l);
    dvf_type emp1(emp1h, emp1l);
    vf_type tanh_x_gt_ln_3_2 = (vf_type(1.0f) - vf_type(2.0f)/emp1).h();
    // vf_type tanh_x_gt_ln_3_2 = 1.0f - 2.0f/(em1+2);
    // tanh(x) = sgn(x) * x - x^3/(3+ q(x^2));
    // [0, 0.5625] : | p - f | <= 2^-26.9921875
    // coefficients for tanh generated by sollya
    // x^2 : +0x9.9999ap-3f
    const vf_type tanh_c2=+1.2000000477e+00f;
    // x^4 : -0xb.b3f95p-11f
    const vf_type tanh_c4=-5.7143666781e-03f;
    // x^6 : +0x8.32abfp-15f
    const vf_type tanh_c6=+2.5018115412e-04f;
    const vf_type xx=x*x;
    vf_type q = horner(xx,
                       tanh_c6,
                       tanh_c4,
                       tanh_c2) *xx;
    vf_type tanh_x_small = x - x*xx/(3 + q);
    vf_type tanh_x = _T::sel(x_gt_ln_3_2, tanh_x_gt_ln_3_2, tanh_x_small);
    tanh_x = _T::sel(x_gt_20, tanh_x_gt_20, tanh_x);
    tanh_x= copysign(tanh_x, xc);
    return tanh_x;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log_k_poly(arg_t<vf_type> z)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-32.90625
    // coefficients for log generated by sollya
    // x^2 : +0xa.aaaabp-4f
    const vf_type log_c2=+6.6666668653e-01f;
    // x^4 : +0xc.ccc36p-5f
    const vf_type log_c4=+3.9999550581e-01f;
    // x^6 : +0x9.2610fp-5f
    const vf_type log_c6=+2.8589674830e-01f;
    // x^8 : +0xe.72cb8p-6f
    const vf_type log_c8=+2.2575652599e-01f;

    vf_type w = z*z;
    vf_type t1= z*horner(w,
                         log_c6,
                         log_c2);
    vf_type t2= horner(w,
                       log_c8,
                       log_c4);
    vf_type y= t2*w + t1;
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log_k(arg_t<vf_type> xc, log_func func)
{
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* log(x)
 * Return the logarithm of x
 *
 * Method :
 *   1. Argument Reduction: find k and f such that
 *                      x = 2^k * (1+f),
 *         where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *   2. Approximation of log(1+f).
 *      Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
 *               = 2s + 2/3 s**3 + 2/5 s**5 + .....,
 *               = 2s + s*R
 *      We use a special Remez algorithm on [0,0.1716] to generate
 *      a polynomial of degree 14 to approximate R The maximum error
 *      of this polynomial approximation is bounded by 2**-58.45. In
 *      other words,
 *                      2      4      6      8      10      12      14
 *          R(z) ~ Lg1*s +Lg2*s +Lg3*s +Lg4*s +Lg5*s  +Lg6*s  +Lg7*s
 *      (the values of Lg1 to Lg7 are listed in the program)
 *      and
 *          |      2          14          |     -58.45
 *          | Lg1*s +...+Lg7*s    -  R(z) | <= 2
 *          |                             |
 *      Note that 2s = f - s*f = f - hfsq + s*hfsq, where hfsq = f*f/2.
 *      In order to guarantee error in log below 1ulp, we compute log
 *      by
 *              log(1+f) = f - s*(f - R)        (if f is not too large)
 *              log(1+f) = f - (hfsq - s*(hfsq+R)).     (better accuracy)
 *
 *      3. Finally,  log(x) = k*ln2 + log(1+f).
 *                          = k*ln2_hi+(f-(hfsq-(s*(hfsq+R)+k*ln2_lo)))
 *         Here ln2 is split into two floating point number:
 *                      ln2_hi + ln2_lo,
 *         where n*ln2_hi is always exact for |n| < 2000.
 *
 * Special cases:
 *      log(x) is NaN with signal if x < 0 (including -INF) ;
 *      log(+INF) is +INF; log(0) is -INF with signal;
 *      log(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *      according to an error analysis, the error is always less than
 *      1 ulp (unit in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */
    // const vf_type ln2_hi = 6.93147180369123816490e-01;  /* 3fe62e42 fee00000 */
    // const vf_type ln2_lo = 1.90821492927058770002e-10;  /* 3dea39ef 35793c76 */

    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_val_or_zero(_T::vmf_to_vmi(is_denom), vi_type(-25));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3f800000 - 0x3f3504f3;;
    k += (hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + 0x3f3504f3;
    vf_type xr = _T::as_float(hx);

    vf_type f = xr - 1.0f;
    vf_type hfsq = (0.5f *f)*f;
    vf_type s = f/(2.0f+f);
    vf_type z = s*s;

    // split of the polynomial reduces precision
    vf_type R = log_k_poly(z);
    vf_type res;
    vf_type kf = _T::cvt_i_to_f(k);
    if (func == log_func::c_log_e) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vf_type log_x=s*(hfsq+R);
        log_x += kf*ctbl::m_ln2_cw[1];
        log_x -= hfsq;
        log_x += f;
        log_x += kf*ctbl::m_ln2_cw[0];
        res = log_x;
    } else if (func == log_func::c_log_10) {
        const vf_type ivln10hi  =  4.3432617188e-01f; /* 0x3ede6000 */
        const vf_type ivln10lo  = -3.1689971365e-05f; /* 0xb804ead9 */
        const vf_type log10_2hi =  3.0102920532e-01f; /* 0x3e9a2080 */
        const vf_type log10_2lo =  7.9034151668e-07f; /* 0x355427db */

        vf_type t = f - hfsq;
        vi_type it= _T::as_int(t);
        it &= vi_type(0xfffff000);
        vf_type hi= _T::as_float(it);
        vf_type lo= f - hi -hfsq + s * (hfsq + R);

        vf_type val_hi = hi * ivln10hi;
        vf_type y = kf* log10_2hi;
        vf_type val_lo = kf * log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;

        vf_type w= y + val_hi;
        val_lo += (y - w) + val_hi;
        val_hi = w;

        vf_type log10_x = val_lo + val_hi;
        res =log10_x;
    } else /* if (func == log_func::c_log_2) */ {
        const vf_type ivln2hi =  1.4428710938e+00f; /* 0x3fb8b000 */
        const vf_type ivln2lo = -1.7605285393e-04f; /* 0xb9389ad4 */

        vf_type t= f - hfsq;
        vi_type it= _T::as_int(t);
        it &= vi_type(0xfffff000);
        vf_type hi= _T::as_float(it);
        vf_type lo= f - hi - hfsq + s * (hfsq + R);
        vf_type val_hi = hi* ivln2hi;
        vf_type val_lo = (lo+hi)*ivln2lo + lo*ivln2hi;

        vf_type y= kf;
        vf_type w= y+ val_hi;
        val_lo += (y-w) + val_hi;
        val_hi = w;

        vf_type log2_x= val_lo + val_hi;
        res = log2_x;
    }
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log1p_k(arg_t<vf_type> xc)
{
/* float log1p(float x)
 * Return the natural logarithm of 1+x.
 *
 * Method :
 *   1. Argument Reduction: find k and f such that
 *                      1+x = 2^k * (1+f),
 *         where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *      Note. If k=0, then f=x is exact. However, if k!=0, then f
 *      may not be representable exactly. In that case, a correction
 *      term is need. Let u=1+x rounded. Let c = (1+x)-u, then
 *      log(1+x) - log(u) ~ c/u. Thus, we proceed to compute log(u),
 *      and add back the correction term c/u.
 *      (Note: when x > 2**53, one can simply return log(x))
 *
 *   2. Approximation of log(1+f): See log.c
 *
 *   3. Finally, log1p(x) = k*ln2 + log(1+f) + c/u. See log.c
 *
 * Special cases:
 *      log1p(x) is NaN with signal if x < -1 (including -INF) ;
 *      log1p(+INF) is +INF; log1p(-1) is -INF with signal;
 *      log1p(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *      according to an error analysis, the error is always less than
 *      1 ulp (unit in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 *
 * Note: Assuming log() return accurate answer, the following
 *       algorithm can be used to compute log1p(x) to within a few ULP:
 *
 *              u = 1+x;
 *              if(u==1.0) return x ; else
 *                         return log(u)*(x/(u-1.0));
 *
 *       See HP-15C Advanced Functions Handbook, p.193.
 */
    vf_type x=xc;
    vf_type u= 1+xc;
    vi_type hu=_T::as_int(u);
    hu += (0x3f800000 - 0x3f3504f3);
    vi_type k=(hu >> 23) - _T::bias();
    vf_type kf= _T::cvt_i_to_f(k);
    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-x), x-(u-1.0f));
    c_k_2 /= u;
    vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    /* reduce u into [sqrt(2)/2, sqrt(2)] */
    hu = (hu&0x007fffff) + 0x3f3504f3;
    vf_type nu = _T::as_float(hu);
    vf_type f= nu -1.0f;

    vf_type hfsq = 0.5f*f*f;
    vf_type s = f/(2.0f+f);
    vf_type z = s*s;
    vf_type R = log_k_poly(z);

    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type log1p_x= s*(hfsq+R);
    log1p_x += kf*ctbl::m_ln2_cw[1] +c;
    log1p_x -= hfsq;
    log1p_x += f;
    log1p_x += kf*ctbl::m_ln2_cw[0];
    log1p_x= _T::sel(abs(x) < 0x1p-24f, x, log1p_x);
    return log1p_x;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log2_k(arg_t<vf_type> xc)
{
/*
 * Return the base 2 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log2(x) = (f - f*f/2 + r)/log(2) + k
 */
    return log_k(xc, log_func::c_log_2);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log10_k(arg_t<vf_type> xc)
{
/*
 * Return the base 10 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log10(x) = (f - f*f/2 + r)/log(10) + k*log10(2)
 */
    return log_k(xc, log_func::c_log_10);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__pow_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vf_type> kf, arg_t<vi_type> k,
            vf_type* exl)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-32.609375
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3f
    const float exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    const float exp_c2=+5.0000000000e-01f;
    // x^3 : +0xa.aaaa9p-6f
    const float exp_c3=+1.6666664183e-01f;
    // x^4 : +0xa.aaa73p-8f
    const float exp_c4=+4.1666459292e-02f;
    // x^5 : +0x8.88ae5p-10f
    const float exp_c5=+8.3338962868e-03f;
    // x^6 : +0xb.6a77ep-13f
    const float exp_c6=+1.3935414609e-03f;
    // x^7 : +0xc.d3317p-16f
    const float exp_c7=+1.9569355936e-04f;

    vf_type xx= xrh*xrh;
    vf_type i=horner(xx,
                     exp_c7,
                     exp_c5);
    vf_type j=horner(xx,
                     exp_c6,
                     exp_c4);
    vf_type y= horner(xrh, i, j, exp_c3);
    vf_type ye;
    horner_comp_quick(y, ye, xrh, y, exp_c2, exp_c1);
    // correction for errors in argument reduction
    vf_type yl=y+ye;
    horner_comp_quick_si(y, ye, xrh, y, ye, exp_c0);
    vf_type yee= xrl + xrl*xrh*yl;
    ye += yee;
    if (exl==nullptr) {
        y += ye;
    } else {
        d_ops::add12(y, ye, y, ye);
        *exl= __scale_exp_k(ye, kf, k);
    }
    y = __scale_exp_k(y, kf, k);
    return y;
}


template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log2_k(arg_t<vf_type> xc)
{
    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_val_or_zero(_T::vmf_to_vmi(is_denom), vi_type(-25));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3f800000 - 0x3f3504f3;;
    k += (hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + 0x3f3504f3;
    vf_type xr = _T::as_float(hx);
    vf_type kf = _T::cvt_i_to_f(k);

    // brute force:
    dvf_type ym= d_ops::add(xr, vf_type(-1.0f));
    dvf_type yp= d_ops::add(xr, vf_type(+1.0f));
    dvf_type ds= d_ops::sloppy_div(ym, yp);

    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-39.5
    // coefficients for pow_log generated by sollya
    // x^1 : +0x8p-2f
    const vf_type pow_log_c1=+2.0000000000e+00f;
    // x^3 : +0xa.aaaabp-4f
    const vf_type pow_log_c3=+6.6666668653e-01f;
    // x^5 : +0xc.ccc17p-5f
    const vf_type pow_log_c5=+3.9999458194e-01f;
    // x^7 : +0x9.289dap-5f
    const vf_type pow_log_c7=+2.8620797396e-01f;
    // x^9 : +0xd.09b1p-6f
    const vf_type pow_log_c9=+2.0371651649e-01f;
    // x^11 : +0xd.d007bp-5f
    const vf_type pow_log_c11=+4.3164429069e-01f;
    vf_type s2= sqr(ds).h();
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type qh, ql;
    d_ops::mul22(qh, ql,
                 ctbl::m_1_ln2.h(), ctbl::m_1_ln2.l(),
                 ds.h(), ds.l());
#if 1
    vf_type s4=s2*s2;
    vf_type p1= horner(s4,
                       pow_log_c11,
                       pow_log_c7);
    vf_type p2= horner(s4,
                       pow_log_c9,
                       pow_log_c5);
    vf_type p= horner(s2, p1, p2);
#else
    vf_type p= horner(s2,
                      pow_log_c11,
                      pow_log_c9,
                      pow_log_c7,
                      pow_log_c5);
#endif
    vf_type ph, pl;
    horner_comp_quick(ph, pl, s2, p, pow_log_c3, pow_log_c1);
    d_ops::mul22(ph, pl, ph, pl, qh, ql);
    d_ops::add122cond(ph, pl, kf, ph, pl);
    dvf_type log2_x(ph, pl);
    return log2_x;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type abs_x= abs(x);
    dvf_type ldx= __pow_log2_k(abs_x);
    dvf_type yldx = y*ldx;
    vf_type kf= rint(vf_type(yldx.h()));
    dvf_type xrhl= yldx - kf;
    vf_type xrh, xrl;
    d_ops::mul22(xrh, xrl, xrhl.h(), xrhl.l(),
                 ctbl::m_ln2.h(), ctbl::m_ln2.l());
    vi_type k= _T::cvt_f_to_i(kf);
    vf_type res=__pow_exp_k(xrh, xrl, kf, k);
    // std::cout << kf << std::endl;
    // std::cout << k << std::endl;
    using fc=func_constants<float>;
    const vf_type& d= yldx.h();
    const vf_type exp2_hi_inf= fc::exp2_hi_inf();
    const vf_type exp2_lo_zero= fc::exp2_lo_zero();
    res = _T::sel_zero_or_val(d <= exp2_lo_zero, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0f, 1.0f, res);
    res = _T::sel(d == 1.0f, 2.0f, res);
    return res;
}

template <typename _T>
inline
std::pair<typename cftal::math::elem_func_core<float, _T>::dvf_type,
          typename cftal::math::elem_func_core<float, _T>::vi_type>
cftal::math::elem_func_core<float, _T>::
reduce_trig_arg_k(arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type fn= rint(vf_type(x* ctbl::m_2_pi.h()));
    vf_type xrh, xrl;
    const float m_pi_2_h=+1.5707963705063e+00f;
    const float m_pi_2_m=-4.3711388286738e-08f;
    const float m_pi_2_l=-1.7151245100059e-15f;
    vf_type th, tl;
    d_ops::mul12(th, tl, fn, -m_pi_2_h);
    d_ops::add122cond(xrh, xrl, x, th, tl);
    d_ops::mul12(th, tl, fn, -m_pi_2_m);
    d_ops::add22cond(xrh, xrl, xrh, xrl, th, tl);
    d_ops::mul12(th, tl, fn, -m_pi_2_l);
    d_ops::add22cond(xrh, xrl, xrh, xrl, th, tl);
    dvf_type d0(xrh, xrl);
    vi_type q(_T::cvt_f_to_i(fn));
    const float large_arg=0x1p18f;

    vmf_type v_large_arg= vf_type(large_arg) < abs(x);
    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(float)) v_d {
            float _sc[N];
        } tf, d0_l, d0_h;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, x);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0.l());
        mem<vf_type>::store(d0_h._sc, d0.h());
        for (std::size_t i=0; i<N; ++i) {
            if (large_arg < std::fabs(tf._sc[i])) {
                float y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                d0_l._sc[i]= y[1];
                d0_h._sc[i]= y[0];
            }
        }
        vf_type rh(mem<vf_type>::load(d0_h._sc, N));
        vf_type rl(mem<vf_type>::load(d0_l._sc, N));
        d0 = dvf_type(rh, rl);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    return std::make_pair(d0, q);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
/* __sin( x, y, iy)
 * kernel sin function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *      2. Callers must return sin(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization sin(x) ~ x for tiny x.
 *      3. sin(x) is approximated by a polynomial of degree 13 on
 *         [0,pi/4]
 *                               3            13
 *              sin(x) ~ x + S1*x + ... + S6*x
 *         where
 *
 *      |sin(x)         2     4     6     8     10     12  |     -58
 *      |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *      |  x                                               |
 *
 *      4. sin(x+y) = sin(x) + sin'(x')*y
 *                  ~ sin(x) + (1-x*x/2)*y
 *         For better accuracy, let
 *                   3      2      2      2      2
 *              r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *         then                   3    2
 *              sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */
    // [3.4694469519536141888238489627838134765625e-18, 0.785398185253143310546875] : | p - f | <= 2^-32.25
    // coefficients for sin generated by sollya
    // x^2 : -0xa.aaaabp-6f
    const vf_type sin_c2=-1.6666667163e-01f;
    // x^4 : +0x8.888b2p-10f
    const vf_type sin_c4=+8.3333719522e-03f;
    // x^6 : -0xd.02433p-16f
    const vf_type sin_c6=-1.9849911041e-04f;
    // x^8 : +0xb.bf108p-22f
    const vf_type sin_c8=+2.8005470085e-06f;
    vf_type z = xh*xh;
    // vf_type w = z*z;
    vf_type r = sin_c4 + z*(sin_c6 + z*sin_c8);
    vf_type v = z*xh;
    return xh - ((z*(0.5f*xl - v*r) - xl) - v*sin_c2);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
/*
 * __cos( x,  y )
 * kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since cos(-x) = cos(x), we need only to consider positive x.
 *      2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *      3. cos(x) is approximated by a polynomial of degree 14 on
 *         [0,pi/4]
 *                                       4            14
 *              cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *         where the remez error is
 *
 *      |              2     4     6     8     10    12     14 |     -58
 *      |cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 *      |                                                      |
 *
 *                     4     6     8     10    12     14
 *      4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *             cos(x) ~ 1 - x*x/2 + r
 *         since cos(x+y) ~ cos(x) - sin(x)*y
 *                        ~ cos(x) - x*y,
 *         a correction term is necessary in cos(x) and hence
 *              cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *         For better accuracy, rearrange to
 *              cos(x+y) ~ w + (tmp + (r-x*y))
 *         where w = 1 - x*x/2 and tmp is a tiny correction term
 *         (1 - x*x/2 == w + tmp exactly in infinite precision).
 *         The exactness of w + tmp in infinite precision depends on w
 *         and tmp having the same precision as x.  If they have extra
 *         precision due to compiler bugs, then the extra precision is
 *         only good provided it is retained in all terms of the final
 *         expression for cos().  Retention happens in all cases tested
 *         under FreeBSD, so don't pessimize things by forcibly clipping
 *         any extra precision in w.
 */
    // [3.4694469519536141888238489627838134765625e-18, 0.785398185253143310546875] : | p - f | <= 2^-33.78125
    // coefficients for cos generated by sollya
    // x^4 : +0xa.aaaabp-8f
    const vf_type cos_c4=+4.1666667908e-02f;
    // x^6 : -0xb.60beap-13f
    const vf_type cos_c6=-1.3889048714e-03f;
    // x^8 : +0xd.07ad8p-19f
    const vf_type cos_c8=+2.4852735805e-05f;
    // x^10 : -0xa.c7898p-25f
    const vf_type cos_c10=-3.2125240068e-07f;
    vf_type z  = xh*xh;
    // vf_type w  = z*z;
    vf_type r  = z*(cos_c4+z*(cos_c6+z*(cos_c8+z*cos_c10)));
    vf_type hz = 0.5f*z;
    vf_type w  = 1.0f-hz;
    return w + (((1.0f-w)-hz) + (z*r-xh*xl));
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__tan_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl, arg_t<vi_type> q)
{
#if 1
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-29.546875
    // coefficients for tan generated by sollya
    // x^1 : +0x8p-3f
    const float tan_c1=+1.0000000000e+00f;
    // x^3 : +0xa.aaabp-5f
    const float tan_c3=+3.3333349228e-01f;
    // x^5 : +0x8.886dp-6f
    const float tan_c5=+1.3332676888e-01f;
    // x^7 : +0xd.d6c9cp-8f
    const float tan_c7=+5.4058656096e-02f;
    // x^9 : +0xa.e63c5p-9f
    const float tan_c9=+2.1287808195e-02f;
    // x^11 : +0xb.15241p-10f
    const float tan_c11=+1.0822833516e-02f;
    // x^13 : +0xd.b2701p-17f
    const float tan_c13=+1.0449998808e-04f;
    // x^15 : +0x8.f2db7p-11f
    const float tan_c15=+4.3694633059e-03f;
    dvf_type dxr2=sqr(dvf_type(xrh, xrl));
    vf_type xrh2=dxr2.h();
    vf_type xrh4=xrh2*xrh2;
    vf_type e= horner(xrh4,
                      tan_c15,
                      tan_c11,
                      tan_c7);
    vf_type o= horner(xrh4,
                      tan_c13,
                      tan_c9,
                      tan_c5);
    vf_type t= horner(xrh2, e, o, tan_c3);
    vf_type th, tl;
    horner_comp_quick(th, tl, xrh2, t, tan_c1);
    d_ops::mul22(th, tl, xrh, xrl, th, tl);
    vi_type q1= q & 1;
    vmi_type qm1= q1 == vi_type(1);
    vmf_type fqm1= _T::vmi_to_vmf(qm1);

    vf_type c;
    d_ops::rcp21(c, th, tl);
    th = _T::sel(fqm1, -c, th);
    return th;
#else
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* tan(x)
 * Return tangent function of x.
 *
 * kernel function:
 *      __tan           ... tangent function on [-pi/4,pi/4]
 *      __rem_pio2      ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *      [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *      in [-pi/4 , +pi/4], and let n = k mod 4.
 *      We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *          0          S           C             T
 *          1          C          -S            -1/T
 *          2         -S          -C             T
 *          3         -C           S            -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *      TRIG(x) returns trig(x) nearly rounded
 */
/* __tan( x, y, k )
 * kernel tan function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input odd indicates whether tan (if odd = 0) or -1/tan (if odd = 1) is returned.
 *
 * Algorithm
 *      1. Since tan(-x) = -tan(x), we need only to consider positive x.
 *      2. Callers must return tan(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization tan(x) ~ x for tiny x.
 *      3. tan(x) is approximated by a odd polynomial of degree 27 on
 *         [0,0.67434]
 *                               3             27
 *              tan(x) ~ x + T1*x + ... + T13*x
 *         where
 *
 *              |tan(x)         2     4            26   |     -59.2
 *              |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
 *              |  x                                    |
 *
 *         Note: tan(x+y) = tan(x) + tan'(x)*y
 *                        ~ tan(x) + (1+x*x)*y
 *         Therefore, for better accuracy in computing tan(x+y), let
 *                   3      2      2       2       2
 *              r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
 *         then
 *                                  3    2
 *              tan(x+y) = x + (T1*x + (x *(r+y)+y))
 *
 *      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
 *              tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
 *                     = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
 */
    // [3.4694469519536141888238489627838134765625e-18, 0.673198401927947998046875] : | p - f | <= 2^-34.015625
    // coefficients for tan generated by sollya
    // x^2 : +0xa.aaaabp-5f
    const vf_type tan_c2=+3.3333334327e-01f;
    // x^4 : +0x8.88863p-6f
    const vf_type tan_c4=+1.3333277404e-01f;
    // x^6 : +0xd.d1a0fp-8f
    const vf_type tan_c6=+5.3979929537e-02f;
    // x^8 : +0xb.224d7p-9f
    const vf_type tan_c8=+2.1746082231e-02f;
    // x^10 : +0x9.d6476p-10f
    const vf_type tan_c10=+9.6064712852e-03f;
    // x^12 : +0xf.316f4p-14f
    const vf_type tan_c12=+9.2731346376e-04f;
    // x^14 : +0xe.89edp-11f
    const vf_type tan_c14=+7.0990100503e-03f;
    // x^16 : -0xc.37d89p-11f
    const vf_type tan_c16=-5.9658926912e-03f;
    // x^18 : +0xe.7d6fcp-12f
    const vf_type tan_c18=+3.5375943407e-03f;
    // make xrh positive
    vf_type sgn_x = copysign(vf_type(1.0f), xh);
    vmf_type x_is_neg = sgn_x < 0.0f;
    vf_type xrh = _T::sel(x_is_neg, -xh, xh);
    vf_type xrl = _T::sel(x_is_neg, -xl, xl);

    using ctbl = impl::d_real_constants<d_real<float>, float>;
    const vf_type large_arg=0.6731984257692414;
    vmf_type x_large= xrh > large_arg;
    // for xh in [6/7*pi/4, pi/4] we replace xh with pi/4 - xh

    dvf_type dxrl= dvf_type(ctbl::m_pi_4) - dvf_type(xrh, xrl);
    xrh = _T::sel(x_large, dxrl.h(), xrh);
    xrl = _T::sel(x_large, dxrl.l(), xrl);

    vf_type z = xrh*xrh;

    vf_type s= z * xrh;
    vf_type r = s* horner(z,
                          tan_c18,
                          tan_c16,
                          tan_c14,
                          tan_c12,
                          tan_c10,
                          tan_c8,
                          tan_c6,
                          tan_c4);
    r = tan_c2*s + (z *(r+xrl)+ xrl);
    vf_type txy= xrh + r;

    // tan(x+y) = (tan x + tan y)/(1 - tan(x) * tan(y))
    // tan(x-y) = (tan x - tan y)/(1 + tan(x) * tan(y))
    // because xr = pi/4-x --> tan(pi/4) = 1
    // tan(pi/4-x) = (1- tan(x))/(1 + tan(x))
    //             = 1 - 2*(tan(x) - (tan(x)^2)/(1+tan(x)))
    vi_type q1= q & 1;
    vmi_type qm1= q1 == vi_type(1);
    vmf_type fqm1= _T::vmi_to_vmf(qm1);

    // calculate the values for x large including the sign
    s = _T::sel(fqm1, vf_type(-1.0f), vf_type(1.0f));
    vf_type txyl = s - 2.0f*(xrh + (r - (txy*txy)/(s +txy)));
    txyl *= sgn_x;

    // calculate -1/tan: -1/(xrh +r) has an error to up to 2 ulp
    // use multiprecision arithmetic and one newton raphson step
    vi_type ti=_T::as_int(txy);
    ti &= 0xfffff000;
    vf_type w0 = _T::as_float(ti);
    vf_type w1 = r - (w0 -xrh);
    vf_type a = -1.0f/txy;
    ti= _T::as_int(a);
    ti &= 0xfffff000;
    vf_type a0 = _T::as_float(ti);
    vf_type inv_txy= a0 + a *(1.0f + a0*w0 + a0*w1);
    inv_txy= _T::sel(x_is_neg, -inv_txy, inv_txy);

    // restore the sign
    txy = copysign(txy, sgn_x);

    vf_type tt= _T::sel(fqm1, inv_txy, txy);
    tt = _T::sel(x_large, txyl, tt);
    return tt;
#endif
}

template <typename _T>
__attribute__((flatten))
void
cftal::math::elem_func_core<float, _T>::
sin_cos_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    std::pair<dvf_type, vi_type> rq=reduce_trig_arg_k(xc);
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;

    vf_type s = __sin_k(x.h(), x.l());
    vf_type c = __cos_k(x.h(), x.l());

    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        rs = _T::sel(q_and_2_f, -rs, rs);
        *ps = rs;
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        rc = _T::sel(mt, -rc, rc);
        *pc= rc;
    }
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
tan_k(arg_t<vf_type> xc)
{
    std::pair<dvf_type, vi_type> rq=reduce_trig_arg_k(xc);
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;
    vf_type t = __tan_k(x.h(), x.l(), q);
    return t;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atan_k(arg_t<vf_type> xc)
{
    const vf_type atan_0_5_hi=4.6364760399e-01; /* atan(0.5)hi 0x3eed6338 */
    const vf_type atan_0_5_lo=5.0121582440e-09; /* atan(0.5)lo 0x31ac3769 */
    const vf_type atan_1_0_hi=7.8539812565e-01; /* atan(1.0)hi 0x3f490fda */
    const vf_type atan_1_0_lo=3.7748947079e-08; /* atan(1.0)lo 0x33222168 */
    const vf_type atan_1_5_hi=9.8279368877e-01; /* atan(1.5)hi 0x3f7b985e */
    const vf_type atan_1_5_lo=3.4473217170e-08; /* atan(1.5)lo 0x33140fb4 */
    const vf_type atan_inf_hi=1.5707962513e+00; /* atan(inf)hi 0x3fc90fda */
    const vf_type atan_inf_lo=7.5497894159e-08; /* atan(inf)lo 0x33a22168 */

    vf_type x=abs(xc);
    // range reduction
    vmf_type r=x > 7.0/16;
    vf_type atan_hi= _T::sel_val_or_zero(r, atan_0_5_hi);
    vf_type atan_lo= _T::sel_val_or_zero(r, atan_0_5_lo);
    vf_type t=_T::sel(r, (2.0f*x-1.0f)/(2.0f+x), x);
    r = x>11.0f/16;
    atan_hi=_T::sel(r, atan_1_0_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_0_lo, atan_lo);
    t = _T::sel(r, (x-1.0f)/(1.0f+x), t);
    r = x>19.0f/16;
    atan_hi=_T::sel(r, atan_1_5_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_5_lo, atan_lo);
    t = _T::sel(r, (x-1.5f)/(1.0f+1.5f*x), t);
    r = x>39.0f/16;
    atan_hi=_T::sel(r, atan_inf_hi, atan_hi);
    atan_lo=_T::sel(r, atan_inf_lo, atan_lo);
    t = _T::sel(r, -1.0f/x, t);

    // [3.4694469519536141888238489627838134765625e-18, 0.4375] : | p - f | <= 2^-26.578125
    // coefficients for atan generated by sollya
    // x^0 : +0xa.aaaabp-5f
    const vf_type atan_c0=+3.3333334327e-01f;
    // x^2 : -0xc.cccffp-6f
    const vf_type atan_c2=-2.0000074804e-01f;
    // x^4 : +0x9.24b9bp-6f
    const vf_type atan_c4=+1.4286653697e-01f;
    // x^6 : -0xe.34345p-7f
    const vf_type atan_c6=-1.1096815020e-01f;
    // x^8 : +0xb.2d878p-7f
    const vf_type atan_c8=+8.7326943874e-02f;
    // x^10 : -0xd.5110fp-8f
    const vf_type atan_c10=-5.2018221468e-02f;

    vf_type t2=t*t;
    vf_type p= t2 * horner(t2,
                           atan_c10,
                           atan_c8,
                           atan_c6,
                           atan_c4,
                           atan_c2,
                           atan_c0);
    vf_type at=  atan_hi - (t * p - atan_lo - t);
    at = copysign(at, xc);
    return at;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atan2_k(arg_t<vf_type> y, arg_t<vf_type> x)
{
    vf_type yx=y/x;
    vf_type t=atan_k(abs(yx));
    vf_type y_s = copysign(vf_type(1.0f), y);
    vf_type x_s = copysign(vf_type(1.0f), x);

    vmf_type y_lt_0 = y_s < 0.0f;
    vmf_type x_lt_0 = x_s < 0.0f;
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    // default y>=0, x>=0,
    vf_type at= _T::sel(y_lt_0 & x_lt_0,
                        (t - ctbl::m_pi.l()) - ctbl::m_pi.h(),
                        t);
    at = _T::sel(y_lt_0 & (x_s>=0), -t, at);
    at = _T::sel((y_s >=0) & x_lt_0,
                 ctbl::m_pi.h() - (t - ctbl::m_pi.l()),
                 at);
    return at;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
asin_k_poly(arg_t<vf_type> x2)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-27.578125
    // coefficients for asin generated by sollya
    // x^0 : +0xa.aaaabp-6f
    const vf_type asin_c0=+1.6666667163e-01f;
    // x^2 : +0x9.99946p-7f
    const vf_type asin_c2=+7.4999377131e-02f;
    // x^4 : +0xb.6f31dp-8f
    const vf_type asin_c4=+4.4665444642e-02f;
    // x^6 : +0xf.5f16fp-9f
    const vf_type asin_c6=+3.0022351071e-02f;
    // x^8 : +0xc.f08a7p-9f
    const vf_type asin_c8=+2.5272680447e-02f;
    // x^10 : +0xa.b0219p-11f
    const vf_type asin_c10=+5.2187559195e-03f;
    // x^12 : +0x9.a0bp-8f
    const vf_type asin_c12=+3.7608146667e-02f;
    vf_type r=x2*horner(x2,
                        asin_c12,
                        asin_c10,
                        asin_c8,
                        asin_c6,
                        asin_c4,
                        asin_c2,
                        asin_c0);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
asin_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vmf_type x_lt_1_2= x<0.5f;
    vf_type x2= x*x;
    vf_type z= (1.0f-x)*0.5f;
    vf_type s= sqrt(z);

    vf_type xr=_T::sel(x_lt_1_2, x2, z);
    vf_type r=asin_k_poly(xr);
    vf_type as0= x + x*r;
    // default: x>0.975
    // vf_type as = ctbl::m_pi_2.h() - (2*(s+s*r) - ctbl::m_pi_2.l());
    // x in [0, 1]
    vi_type t=_T::as_int(s);
    t &= 0xfffff000;
    vf_type f=_T::as_float(t);
    vf_type c= (z-f*f)/(s+f);
    vf_type as1= 0.5f * ctbl::m_pi_2.h() -
                         (2.0f*s*r - (ctbl::m_pi_2.l() -2.0f *c) -
                          (0.5f*ctbl::m_pi_2.h()-2.0f*f));
    vf_type as=_T::sel(x_lt_1_2, as0, as1);
    as = copysign(as, xc);
    return as;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
acos_k(arg_t<vf_type> xc)
{
    vf_type x= xc;

    vmf_type x_lt_m_1_2 = x < -0.5f;
    vmf_type x_gt_1_2 = x>0.5f;
    vmf_type abs_x_le_1_2 = abs(x) <= 0.5f;

    vf_type z= _T::sel(x_lt_m_1_2, (1.0f+x)*0.5f, (1.0f-x)*0.5f);
    vf_type s= sqrt(z);
    vf_type x2=x*x;
    vf_type xr= _T::sel(abs_x_le_1_2, x2, z);
    vf_type r= asin_k_poly(xr);

    // x in [-0.5, 0.5]
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type ac = ctbl::m_pi_2.h() - (x - (ctbl::m_pi_2.l()-x*r));
    // x in [-1.0, -0.5]
    vf_type wn = r*s - ctbl::m_pi_2.l();
    vf_type ac1= 2*(ctbl::m_pi_2.h() - (s+wn));
    ac = _T::sel(x_lt_m_1_2, ac1, ac);
    // x in [0.5, 1.0]
    vi_type t=_T::as_int(s);
    t &= 0xfffff000;
    vf_type df= _T::as_float(t);
    vf_type c= (z-df*df)/(s+df);
    vf_type wp= r*s+c;
    vf_type ac2=2.0f*(df+wp);
    ac = _T::sel(x_gt_1_2, ac2, ac);
    return ac;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
asinh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vmf_type x_gt_0x1p12 = x > 0x1p12;
    vf_type add_2_log=_T::sel_val_or_zero(x_gt_0x1p12, ctbl::m_ln2.h());
    vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p12,
                            x,
                            2.0f * x+ 1.0f/(sqrt(vf_type(t+1.0f))+x));
    vf_type yl= log_k(log_arg, log_func::c_log_e);
    yl += add_2_log;
    // |x| < 2.0
    vf_type log1p_arg= x+t/(1.0f+sqrt(vf_type(1.0f+t)));
    vf_type ys= log1p_k(log1p_arg);

    // [3.4694469519536141888238489627838134765625e-18, 0.707106769084930419921875] : | p - f | <= 2^-31.4921875
    // coefficients for asinh generated by sollya
    // x^0 : +0x8p-3f
    const vf_type asinh_c0=+1.0000000000e+00f;
    // x^2 : -0xa.aaaa7p-6f
    const vf_type asinh_c2=-1.6666661203e-01f;
    // x^4 : +0x9.9981ap-7f
    const vf_type asinh_c4=+7.4997141957e-02f;
    // x^6 : -0xb.6a588p-8f
    const vf_type asinh_c6=-4.4591456652e-02f;
    // x^8 : +0xf.538eap-9f
    const vf_type asinh_c8=+2.9934365302e-02f;
    // x^10 : -0xa.597cap-9f
    const vf_type asinh_c10=-2.0213980228e-02f;
    // x^12 : +0xb.807cfp-10f
    const vf_type asinh_c12=+1.1232330464e-02f;
    // x^14 : -0xe.1b09dp-12f
    const vf_type asinh_c14=-3.4437545110e-03f;

    vf_type yss= x* horner(t,
                           asinh_c14,
                           asinh_c12,
                           asinh_c10,
                           asinh_c8,
                           asinh_c6,
                           asinh_c4,
                           asinh_c2,
                           asinh_c0);

    ys = _T::sel(x<= M_SQRT2*0.5f, yss, ys);

    vf_type ash=_T::sel(x <= 2.0f, ys, yl);
    ash = copysign(ash, xc);
    return ash;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
acosh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vmf_type x_gt_0x1p12 = x > 0x1p12;
    vf_type add_2_log=_T::sel_val_or_zero(x_gt_0x1p12, ctbl::m_ln2.h());
    // vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p12,
                            x,
                            2.0f*x - 1.0f/(x+sqrt(vf_type(x*x-1.0f))));
    vf_type yl= log_k(log_arg, log_func::c_log_e);
    yl += add_2_log;

    vf_type xm1l;
    vf_type xm1=d_ops::two_diff(x, vf_type(1), xm1l);
    dvf_type sqrt2xm1=sqrt(mul_pwr2(dvf_type(xm1, xm1l), vf_type(2)));
    // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]
    // [3.4694469519536141888238489627838134765625e-18, 1] : | p - f | <= 2^-33.984375
    // coefficients for acosh generated by sollya
    // x^0 : +0x8p-3f
    const vf_type acosh_c0=+1.0000000000e+00f;
    // x^1 : -0xa.aaaaap-7f
    const vf_type acosh_c1=-8.3333328366e-02f;
    // x^2 : +0x9.9995p-9f
    const vf_type acosh_c2=+1.8749862909e-02f;
    // x^3 : -0xb.6cfaap-11f
    const vf_type acosh_c3=-5.5789547041e-03f;
    // x^4 : +0xf.7ee77p-13f
    const vf_type acosh_c4=+1.8915672554e-03f;
    // x^5 : -0xb.180dcp-14f
    const vf_type acosh_c5=-6.7712157033e-04f;
    // x^6 : +0xf.188dp-16f
    const vf_type acosh_c6=+2.3034517653e-04f;
    // x^7 : -0x8.051ffp-17f
    const vf_type acosh_c7=-6.1187885876e-05f;
    // x^8 : +0x9.191f4p-20f
    const vf_type acosh_c8=+8.6766558525e-06f;
    vf_type ys=horner(xm1,
                      acosh_c8,
                      acosh_c7,
                      acosh_c6,
                      acosh_c5,
                      acosh_c4,
                      acosh_c3,
                      acosh_c2,
                      acosh_c1,
                      acosh_c0);
    ys= (sqrt2xm1 * ys).h();
    vf_type y= _T::sel(x < 2.0f, ys, yl);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atanh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);

    // atanh(x) = x + 1/3*x^3 + 1/5*x^5
    //          = x + x^3/(3+x^2*Q)
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-24.3203125
    // coefficients for atanh generated by sollya
    // x^0 : -0xe.66666p-3f
    const vf_type atanh_c0=-1.7999999523e+00f;
    // x^2 : -0xd.2a823p-6f
    const vf_type atanh_c2=-2.0571951568e-01f;
    // x^4 : -0xd.6ffe8p-7f
    const vf_type atanh_c4=-1.0498028994e-01f;
    // x^6 : -0x8.d7333p-7f
    const vf_type atanh_c6=-6.9067381322e-02f;
    // x^8 : -0x8.cc5a3p-8f
    const vf_type atanh_c8=-3.4368168563e-02f;
    // x^10 : -0x9.52b03p-7f
    const vf_type atanh_c10=-7.2835944593e-02f;
    // x^12 : -0xc.30ebcp-13f
    const vf_type atanh_c12=-1.4881710522e-03f;
    vf_type xx=x*x;
    vf_type Q = horner(xx,
                       atanh_c12,
                       atanh_c10,
                       atanh_c8,
                       atanh_c6,
                       atanh_c4,
                       atanh_c2,
                       atanh_c0);
    vf_type ys= x + x*xx/(3.0f + xx * Q);
    vf_type log1p_arg= 2.0f*(x/(1.0f-x));
    vf_type yl= 0.5f*log1p_k(log1p_arg);
    vf_type y=_T::sel(x<=0.5f, ys, yl);
    y = copysign(y, xc);
    return y;
}



// Local Variables:
// mode: c++
// end:
#endif
