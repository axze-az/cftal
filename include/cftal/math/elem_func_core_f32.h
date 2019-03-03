//
// Copyright Axel Zeuner 2010-2019. Use, modification and
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
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math/elem_func.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/func_data.h>
#include <cftal/math/misc.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/mem.h>

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
            using t_ops=cftal::impl::t_real_ops<vf_type>;

            enum result_prec {
                normal,
                medium,
                high
            };

            template <unsigned _U>
            static
            vf_type
            __fmod(arg_t<vf_type> v);

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
            ldexp_k(arg_t<vf_type> vf, arg_t<vi_type> vi);

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

            class scale_result {
                vf_type _f0;
                vf_type _f1;
            public:
                constexpr
                scale_result() = default;
                constexpr
                scale_result(const vf_type& s0, const vf_type& s1)
                    : _f0(s0), _f1(s1) {}
                constexpr const vf_type& f0() const { return _f0; }
                constexpr const vf_type& f1() const { return _f1; }
            };

            // returns 2^k = r.f0()* r.f1() to avoid over and underflows
            static
            scale_result
            __scale_exp_k(arg_t<vi_type> ki);

            // returns 2^k = r.f0()* r.f1() to avoid over and underflows
            static
            scale_result
            __scale_exp_k(arg_t<vf_type> k);

            // scaling function for exponential functions
            // returns y*2^k
            static
            vf_type
            __scale_exp_k(arg_t<vf_type> y, arg_t<vf_type> k);

            // scaling function for exponential functions
            // returns yh*2^k, yl*2^k
            static
            dvf_type
            __scale_exp_k(arg_t<vf_type> yh,
                          arg_t<vf_type> yl,
                          arg_t<vf_type> k);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/2, log(2)/2], and the argument
            // k as argument for __scale_exp_k
            // calculates %e^(xrh+xrl)*2^k - 1 if exp_m1 is true,
            // %e^(xrh+xrl)*2^k otherwise
            template <bool _EXP_M1>
            static
            vf_type
            __exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                    arg_t<vf_type> k);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/(2*N), log(2)/(2*N)], and the argument
            // idx is the table index
            // calculates %e^(xrh+xrl)*(2^idx/N)
            template <result_prec _P>
            static
            vf_type
            __exp_tbl_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vi_type> idx,
                        vf_type* expl=nullptr);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/(2*N), log(2)/(2*N)], and the argument
            // k as argument for __scale_exp_k
            // ki is the table index
            // calculates %e^(xrh+xrl)*(2^idx/N)*2^k
            static
            vf_type
            __exp_tbl_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vi_type> idx, arg_t<vi_type> ki,
                        vf_type* expl=nullptr);

            // argument reduction for %e^x and %e^x-1
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/2, log(2)/2] for calling __exp_k
            static
            void
            __reduce_exp_arg(vf_type& __restrict xrh,
                             vf_type& __restrict xrl,
                             vf_type& __restrict kf,
                             arg_t<vf_type> x);

            // argument reduction for %e^(xh+xl) and %e^(xh+xl)-1
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/2, log(2)/2] for calling __exp_k
            static
            void
            __reduce_exp_arg(vf_type& __restrict xrh,
                             vf_type& __restrict xrl,
                             vf_type& __restrict kf,
                             arg_t<vf_type> xh,
                             arg_t<vf_type> xl);

            // argument reduction for %e^(x)
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp_arg(vf_type& __restrict xrh,
                             vf_type& __restrict xrl,
                             vi_type& __restrict idx,
                             vi_type& __restrict ki,
                             arg_t<vf_type> x);

            // argument reduction for %e^(xh+xl)
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp_arg(vf_type& __restrict xrh,
                             vf_type& __restrict xrl,
                             vi_type& __restrict idx,
                             vi_type& __restrict ki,
                             arg_t<vf_type> xh,
                             arg_t<vf_type> xl);

            // calculates %e^x-1 if exp_m1 == true %e^x otherwise
            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            // calculates %e^(xh+xl) into eh, el
            static
            void
            exp_k2(vf_type& eh, vf_type& el,
                   arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates %e^(-x*x)
            static
            vf_type
            exp_mx2_k(arg_t<vf_type> x);

            // calculates %e^(x*x)
            static
            vf_type
            exp_px2_k(arg_t<vf_type> x);

            // argument reduction for 2^(x)
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp2_arg(vf_type& __restrict xrh,
                              vf_type& __restrict xrl,
                              vi_type& __restrict idx,
                              vi_type& __restrict ki,
                              arg_t<vf_type> x);

            // argument reduction for 2^(xh+xl)
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp2_arg(vf_type& __restrict xrh,
                              vf_type& __restrict xrl,
                              vi_type& __restrict idx,
                              vi_type& __restrict ki,
                              arg_t<vf_type> xh,
                              arg_t<vf_type> xl);

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

            // argument reduction for 10^(x)
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp10_arg(vf_type& __restrict xrh,
                               vf_type& __restrict xrl,
                               vi_type& __restrict idx,
                               vi_type& __restrict ki,
                               arg_t<vf_type> x);

            // argument reduction for 10^(xh+xl)
            // return 2^k * (xrh + xrl) with xrh in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp10_arg(vf_type& __restrict xrh,
                               vf_type& __restrict xrl,
                               vi_type& __restrict idx,
                               vi_type& __restrict ki,
                               arg_t<vf_type> xh,
                               arg_t<vf_type> xl);

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
            sinh_cosh_k(arg_t< vf_type > xc);

            static
            vf_type
            sinh_k(arg_t<vf_type> x);

            static
            vf_type
            cosh_k(arg_t<vf_type> x);

            static
            vf_type
            tanh_k(arg_t<vf_type> x);

            enum log_func {
                c_log_e,
                c_log_2,
                c_log_10
            };

            // return 2^k * 1/inv_c * (1 + xr*inv_c) = xc
            //        2^k * c * (1+xr/c) = xc
            // log_c_h + log_c_l = -log(inv_c),
            template <log_func _LFUNC>
            static
            void
            __reduce_log_arg(vf_type& xr,
                             vf_type& inv_c,
                             vf_type& log_c_h,
                             vf_type& log_c_l,
                             vf_type& kf,
                             arg_t<vf_type> x,
                             vi_type* k=nullptr);

            // standard log calculation
            template <log_func _LFUNC>
            static
            vf_type
            __log_tbl_k(arg_t<vf_type> xc);

            // calculates log/log2/log10
            //        2^k * c * (1+xr/c) = xc
            // (1 + xr/c) = r, rl
            // log_c_h, log_c_l = log(c)
            // with higher precision
            template <log_func _LFUNC, result_prec _P>
            static
            dvf_type
            __pow_log_tbl_k(arg_t<vf_type> r,
                            arg_t<vf_type> rl,
                            arg_t<vf_type> log_c_h,
                            arg_t<vf_type> log_c_l,
                            arg_t<vf_type> kf);

            // calculates log(xc) with higher precision
            template <log_func _LFUNC, result_prec _P>
            static
            dvf_type
            __pow_log_tbl_k(arg_t<vf_type> xc);

            // calculates log(xc+xcl) with higher precision
            template <log_func _LFUNC, result_prec _P>
            static
            dvf_type
            __pow_log_tbl_k2(arg_t<vf_type> xc, arg_t<vf_type> xcl);

            static
            void
            __reduce_log_arg(vf_type& xr,
                             vf_type& kf,
                             arg_t<vf_type> xc,
                             vi_type* pk=nullptr);

            // polynomial approximation of log(1+f) with
            // s = f/(2.0+f) and z = s*s, must be multiplied by
            // z later
            static
            vf_type
            __log_k_poly(arg_t<vf_type> z);

            template <log_func _F>
            static
            vf_type
            __log_k(arg_t<vf_type> x);

            static
            vf_type
            log1p_k(arg_t<vf_type> x);

            static
            vf_type
            log_k(arg_t<vf_type> x);

            static
            vf_type
            log2_k(arg_t<vf_type> x);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/2, log(2)/2],
            // calculates %e^(xrh+xrl)
            static
            vf_type
            __pow_exp_poly_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                             vf_type* exl=nullptr);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/2, log(2)/2], and the arguments
            // kf and k as argument for scale_exp_k
            // calculates %e^(xrh+xrl)*2^k
            static
            vf_type
            __pow_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vf_type> kf,
                        vf_type* exl=nullptr);

            // log worker with enhanced precision, inputs are
            // sh, sl = (xr-1)/(xr+1) and kf with x= xr*2^kf
            template <log_func _F, result_prec _P>
            static
            dvf_type
            __pow_log_k(arg_t<vf_type> sh, arg_t<vf_type> sl,
                        arg_t<vf_type> kf);

            // log with enhanced precision
            template <log_func _F, result_prec _P>
            static
            dvf_type
            __pow_log_k(arg_t<vf_type> x);

            // log with enhanced precision
            template <log_func _F, result_prec _P>
            static
            dvf_type
            __pow_log_k2(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculation of x^y
            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y);

            // returns (xh+xl)^(yh+yl) * 2^(-sc) as dvf_type in first,
            // sc in second
            using pow_k2_result = std::pair<dvf_type, scale_result>;
            static
            pow_k2_result
            pow_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
                   arg_t<vf_type> yh, arg_t<vf_type> yl);

            // argument reduction for all trigonometric functions,
            // reduction by %pi/2, the low bits of multiples of %pi/2
            // are returned in the value, the reduced argument is
            // stored into xrh and xrl
            static
            vi_type
            __reduce_trig_arg(vf_type& __restrict xrh,
                              vf_type& __restrict xrl,
                              arg_t<vf_type> x);

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
            __sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vi_type> q,
                        vf_type* s, vf_type* c);

            // core sine, cosine calculation with higher precision
            static
            void
            __sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vi_type> q,
                        dvf_type* ps, dvf_type* pc);

            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tan_k(arg_t<vf_type> x);

            // atan calculation for x in [0, 1]
            static
            dvf_type
            __atan_0_1_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

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

            static
            vf_type
            hypot_k(arg_t<vf_type> xc, arg_t<vf_type> yc);
        };
    }
}

template <typename _T>
template <unsigned _U>
inline
typename
cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__fmod(arg_t<vf_type> v)
{
    constexpr const float sd=1.0f/_U;
    constexpr const float su=_U;
    constexpr const float nsu=-su;
    vf_type i= rint(vf_type(v*sd));
    vf_type r= i*nsu + v;
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
ldexp_k(arg_t<vf_type> x, arg_t<vi_type> n)
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
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    return ldexp_k(x, n);
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
    vf_type y= vf_type(1.0/sqrt(x));
    // y = y + 0.5* y * (vf_type(1) - d_ops::mul(x, y)*y)[0];
#if 1
    vf_type xyh, xyl;
    d_ops::mul12(xyh, xyl, x, y);
    vf_type th;
    if (d_real_traits<vf_type>::fma == true) {
        th = y * xyh - 1.0;
        th = y * xyl + th;
    } else {
        vf_type yxyh, yxyl;
        d_ops::mul12(yxyh, yxyl, y, xyh);
        vf_type tl;
        th = yxyh - 1.0;
        tl = yxyl + y*xyl;
        th += tl;
#if 0
        d_ops::muladd12(th, tl, -1.0, y, xyh);
        tl = y * xyl + tl;
        th += tl;
#endif
    }
    y = y + (-0.5*y) * th;
#else
    vf_type yh, yl;
    d_ops::mul12(yh, yl, x, y);
    d_ops::mul122(yh, yl, y, yh, yl);
    d_ops::add122(yh, yl, -1.0, yh, yl);
    y = y - (0.5*y)*yh;
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
    const float cbrt_c0=+4.5316359401e-01f;
    // x^1 : +0x9.aae0ap-4f
    const float cbrt_c1=+6.0421812534e-01f;
    vf_type mm = horner(mm0,
                        cbrt_c1,
                        cbrt_c0);
    // 1st iteration
    mm = impl::root3::order3<float>(mm, mm0);

    // round mm to 8 bits = int(24)/3
    mm = rint(vf_type(mm*0x1p8f))*0x1p-8f;
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
    vf_type mm_a= _T::sel(mm0 < 0x1p-9f, mm_i0, mm_i1);
    vf_type mm_b= _T::sel(mm0 < 0x1p-3f, mm_i2, mm_i3);
    vf_type mm= _T::sel(mm0 < 0x1p-6f, mm_a, mm_b);

    mm = impl::root12::householder4<float>(mm, mm0);
    vf_type t= _T::insert_exp(e12_with_bias);
    mm *=t;
    // mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::scale_result
cftal::math::elem_func_core<float, _T>::
__scale_exp_k(arg_t<vi_type> ki)
{
    vi_type kia= ki>>1;
    vi_type kib= ki - kia;
    vf_type rh= _T::insert_exp(_T::bias()+kia);
    vf_type rl= _T::insert_exp(_T::bias()+kib);
    return scale_result(rh, rl);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::scale_result
cftal::math::elem_func_core<float, _T>::
__scale_exp_k(arg_t<vf_type> k)
{
    return __scale_exp_k(_T::cvt_f_to_i(k));
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__scale_exp_k(arg_t<vf_type> ym, arg_t<vf_type> k)
{
    auto sc=__scale_exp_k(k);
    vf_type ys = (ym * sc.f0()) * sc.f1();
    return ys;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__scale_exp_k(arg_t<vf_type> yh, arg_t<vf_type> yl, arg_t<vf_type> k)
{
    auto sc = __scale_exp_k(k);
    vf_type ysh = (yh * sc.f0()) * sc.f1();
    vf_type ysl = (yl * sc.f0()) * sc.f1();
    return dvf_type(ysh, ysl);
}

template <typename _T>
template <bool _EXP_M1>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
        arg_t<vf_type> kf)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-32.609375
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3f
    const float exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    // const float exp_c1=+1.0000000000e+00f;
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

    vf_type x2= xrh*xrh;
    static const float ci[]={
        exp_c7, exp_c6, exp_c5, exp_c4, exp_c3
    };
    vf_type y= horner2(xrh, x2, ci);
    y=horner(xrh, y, exp_c2);
    vf_type ye;
#if 1
    d_ops::muladd12(y, ye, xrh, y, x2);
#else
    y = y* x2;
    d_ops::add12(y, ye, xrh, y);
#endif
    // calculate expm1 for correction term
    vf_type yl=y;
    // correction for errors in argument reduction
    vf_type yee= xrl + xrl * yl;
    yee += ye;
    d_ops::add12(y, ye, exp_c0, y);
    if (_EXP_M1 == false) {
        y += (yee+ye);
        y = __scale_exp_k(y, kf);
    } else {
        ye += yee;
        // 2^kf = 2*2^s ; s = kf/2
        vf_type scale = __scale_exp_k(vf_type(0.5f), kf);
        // e^x-1 = 2*(y * 2^s - 0.5)
        y  *= scale;
        vf_type t;
        d_ops::add12cond(y, t, -0.5f, y);
        ye = 2.0f * (ye * scale + t);
        y = 2.0f*y + ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel((abs(xrh) < 0x1p-25f) & (kf==0.0), xrh, y);
    }
    return y;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::result_prec _P>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__exp_tbl_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi_type> idx,
            vf_type* expl)
{
    // [-1.0830424726009368896484375e-2, 1.0830424726009368896484375e-2] : | p - f | <= 2^-32.65625
    // coefficients for exp generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8.0003dp-4f
    constexpr
    const float exp_c2=+5.0000363588e-01f;
    // x^3 : +0xa.aaac9p-6f
    constexpr
    const float exp_c3=+1.6666711867e-01f;

    auto lk=make_variable_lookup_table<float>(idx);
    const auto& tbl=exp_data<float>::_tbl;
    vf_type th=lk.from(tbl._2_pow_i_n_h);
    vf_type tl=lk.from(tbl._2_pow_i_n_l);
    static_assert(exp_c1==1.0f, "oops");

    vf_type x2=xrh*xrh;
    vf_type p= horner(xrh, exp_c3, exp_c2);

    vf_type y;

    if (_P == result_prec::high) {
        vf_type ye;
        d_ops::muladd12(y, ye, xrh, p, x2);
        vf_type yee= xrl + xrl * y;
        ye += yee;
        d_ops::mul22(y, ye, y, ye, th, tl);
        d_ops::add22(y, ye, th, tl, y, ye);
        if (expl != nullptr)
            *expl = ye;
    } else {
        vf_type eh=xrh + (xrl+x2*p);
        if (_P == result_prec::medium) {
            vf_type ye;
            d_ops::add12(y, ye, th, tl + th*eh);
            if (expl != nullptr)
                *expl = ye;
        } else if (_P == result_prec::normal) {
            y= th + (tl + th*eh);
            if (expl != nullptr)
                *expl = 0.0;
        }
    }
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__exp_tbl_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi_type> idx, arg_t<vi_type> ki,
            vf_type* expl)
{
    vf_type y;
    if (expl == nullptr) {
        y=__exp_tbl_k<result_prec::normal>(xrh, xrl, idx, expl);
        auto sc=__scale_exp_k(ki);
        y *= sc.f0();
        y *= sc.f1();
    } else {
        vf_type t;
        y=__exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &t);
        auto sc=__scale_exp_k(ki);
        y *= sc.f0();
        t *= sc.f0();
        y *= sc.f1();
        t *= sc.f1();
        *expl=t;
    }
    return y;
}

template <typename _T>
inline
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    kf = rint(vf_type(x * ctbl::m_1_ln2[0]));
#if 1
    // l1h=round(log(2), 24-9, RN);
    // l1l=log(2)-l1h;
    // write_coeff(l1h, "", "const float _ln2_h_cw", single);
    // write_coeff(l1l, "", "const float _ln2_l_cw", single);
    // x^ : +0xb.172p-4f
    const float _ln2_h_cw=+6.9314575195e-01f;
    // x^ : +0xb.fbe8ep-23f
    const float _ln2_l_cw=+1.4286067653e-06f;

    vf_type hi = x - kf * _ln2_h_cw;
    xrh = hi - kf * _ln2_l_cw;
    vf_type dx = hi-xrh;
    xrl = dx - kf * _ln2_l_cw;
#else
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    xrh = hi - kf * ctbl::m_ln2_cw[1];
    vf_type dx = hi-xrh;
    xrl = dx - kf * ctbl::m_ln2_cw[1];
#endif
}

template <typename _T>
inline
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> xh,
                 arg_t<vf_type> xl)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    kf = rint(vf_type(xh * ctbl::m_1_ln2[0]));
    vf_type neg_kfln2h, neg_kfln2l;
    d_ops::mul122(neg_kfln2h, neg_kfln2l,
                  kf, -ctbl::m_ln2[0], -ctbl::m_ln2[1]);
    d_ops::add22cond(xrh, xrl,
                     xh, xl,
                     neg_kfln2h, neg_kfln2l);
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vi_type& idx,
                 vi_type& k,
                 arg_t<vf_type> x)
{
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    const float _32_ln2=+4.6166240692e+01f;
    // x^ : +0xb.17p-9f
    const float _ln2_32_cw_h=+2.1659851074e-02f;
    // x^ : +0x8.5fdf4p-23f
    const float _ln2_32_cw_l=+9.9831822808e-07f;
    vf_type kf = rint(vf_type(x * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
    idx = ki & exp_data<float>::EXP_IDX_MASK;
    k = ki >> exp_data<float>::EXP_SHIFT;
    vf_type hi = x - kf * _ln2_32_cw_h;
    xrh = hi - kf * _ln2_32_cw_l;
    vf_type dx = hi-xrh;
    xrl = dx - kf * _ln2_32_cw_l;
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vi_type& idx,
                 vi_type& k,
                 arg_t<vf_type> xh,
                 arg_t<vf_type> xl)
{
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    const float _32_ln2=+4.6166240692e+01f;
   // x^ : +0xb.17218p-9f
    const float _ln2_32_h=+2.1660849452e-02f;
    // x^ : -0x8.2e308p-37f
    const float _ln2_32_l=-5.9520444129e-11f;
    vf_type kf = rint(vf_type(xh * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
    idx = ki & exp_data<float>::EXP_IDX_MASK;
    k = ki >> exp_data<float>::EXP_SHIFT;
    vf_type neg_kfln2h, neg_kfln2l;
    d_ops::mul122(neg_kfln2h, neg_kfln2l,
                  kf, -_ln2_32_h, -_ln2_32_l);
    d_ops::add22cond(xrh, xrl,
                     xh, xl,
                     neg_kfln2h, neg_kfln2l);
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl;
    vf_type y;
    if (_EXP_M1==false) {
#if 0
        vf_type kf;
        __reduce_exp_arg(xrh, xrl, kf, xc);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf);
#else
        vi_type idx, ki;
        __reduce_exp_arg(xrh, xrl, idx, ki, xc);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
#endif
    } else {
        vf_type kf;
        __reduce_exp_arg(xrh, xrl, kf, xc);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf);
    }
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
exp_k2(vf_type& eh, vf_type& el,
       arg_t<vf_type> xh, arg_t<vf_type> xl)
{
#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, xh, xl);
    eh=__exp_tbl_k(xrh, xrl, idx, ki, &el);
#else
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, xh, xl);
    eh= __pow_exp_k(xrh, xrl, kf, &el);
#endif
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
#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, x2h, x2l);
    vf_type y=__exp_tbl_k(xrh, xrl, idx, ki);
#else
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
#endif
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
    vf_type t= 0x1.01p-17f;
    x2h = _T::sel(border_case, x2h - t, x2h);
    x2l = _T::sel(border_case, x2l + t, x2l);

#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, x2h, x2l);
    vf_type y=__exp_tbl_k(xrh, xrl, idx, ki);
#else
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
#endif
    y= _T::sel(x2h >= fc_t::exp_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp2_arg(vf_type& xrh,
                  vf_type& xrl,
                  vi_type& idx,
                  vi_type& k,
                  arg_t<vf_type> x)
{
    static_assert(exp_data<float>::EXP_N == 32,
                  "exp_data<float>::EXP_N == 32 expected");
    constexpr const float _ND=exp_data<float>::EXP_N;
    constexpr const float _1_ND=1.0f/exp_data<float>::EXP_N;
    vf_type kf= rint(vf_type(x*_ND));
    vi_type ki=_T::cvt_f_to_i(kf);
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    vf_type xr= x- kf*_1_ND;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul12(xrh, xrl, xr, ctbl::m_ln2[0]);
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp2_arg(vf_type& xrh,
                  vf_type& xrl,
                  vi_type& idx,
                  vi_type& k,
                  arg_t<vf_type> xh,
                  arg_t<vf_type> xl)
{
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    constexpr const double _ND=exp_data<float>::EXP_N;
    constexpr const double _1_ND=1.0f/exp_data<float>::EXP_N;
    vf_type kf= rint(vf_type(xh*_ND));
    vi_type ki=_T::cvt_f_to_i(kf);
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    d_ops::add122cond(xrh, xrl, kf*(-_1_ND), xh, xl);
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul22(xrh, xrl, xrh, xrl,
                 ctbl::m_ln2[0], ctbl::m_ln2[1]);
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type y, kf, xrh, xrl;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
#if 1
    if (_EXP2_M1==false) {
        vi_type idx, ki;
        __reduce_exp2_arg(xrh, xrl, idx, ki, x);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
    } else {
        kf= rint(vf_type(x));
        vf_type xr = x - kf;
        // for exp2 mul12 would be sufficient
        d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
        y=__exp_k<_EXP2_M1>(xrh, xrl, kf);
    }
#else
    kf= rint(vf_type(x));
    vf_type xr = x - kf;
    // for exp2 mul12 would be sufficient
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    y=__exp_k<_EXP2_M1>(xrh, xrl, kf);
#endif
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
#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, x2h, x2l);
    vf_type y=__exp_tbl_k(xrh, xrl, idx, ki);
#else
    vf_type kf = rint(vf_type(x2h));
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, -kf, x2h, x2l);
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
#endif
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
#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, x2h, x2l);
    vf_type y=__exp_tbl_k(xrh, xrl, idx, ki);
#else
    vf_type kf = rint(vf_type(x2h));
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, -kf, x2h, x2l);
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
#endif
    using fc_t = math::func_constants<float>;
    y= _T::sel(x2h >= fc_t::exp2_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp10_arg(vf_type& xrh,
                   vf_type& xrl,
                   vi_type& idx,
                   vi_type& k,
                   arg_t<vf_type> x)
{
    static_assert(exp_data<float>::EXP_N == 32,
                  "exp_data<float>::EXP_N == 32 expected");
    const float _32_lg2=+1.0630169678e+02f;
    // x^ : +0x9.a2p-10f
    const float _lg2_32_cw_h=+9.4070434570e-03f;
    // x^ : +0x9.a84fcp-26f
    const float _lg2_32_cw_l=+1.4390747083e-07f;
    vf_type kf= rint(vf_type(x*_32_lg2));
    vi_type ki=_T::cvt_f_to_i(kf);
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    vf_type hi = x - kf * _lg2_32_cw_h;
    xrh = hi - kf * _lg2_32_cw_l;
    vf_type dx= hi-xrh;
    vf_type cr = dx- kf * _lg2_32_cw_l;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul12(xrh, xrl, xrh, ctbl::m_ln10[0]);
    xrl += cr * ctbl::m_ln10[0];
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_exp10_arg(vf_type& xrh,
                   vf_type& xrl,
                   vi_type& idx,
                   vi_type& k,
                   arg_t<vf_type> xh,
                   arg_t<vf_type> xl)
{
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    const float _32_lg2=+1.0630169678e+02f;
    // x^ : +0x9.a209bp-10f
    const float _lg2_32_h=+9.4071878120e-03f;
    // x^ : -0xf.6086p-35f
    const float _lg2_32_l=-4.4753090123e-10f;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xh*_32_lg2));
    vi_type ki=_T::cvt_f_to_i(kf);
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    vf_type kf_lg_2_32_h, kf_lg_2_32_l;
    d_ops::mul122(kf_lg_2_32_h, kf_lg_2_32_l,
                  kf, -_lg2_32_h, -_lg2_32_l);
    d_ops::add22cond(xrh, xrl,
                     xh, xl,
                     kf_lg_2_32_h, kf_lg_2_32_l);
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln10[0], ctbl::m_ln10[1]);
}

template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp10_k(arg_t<vf_type> x)
{
#if 1
    vf_type y, xrh, xrl;
    if (_EXP10_M1==false) {
        vi_type idx, ki;
        __reduce_exp10_arg(xrh, xrl, idx, ki, x);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
    } else {
        using ctbl = impl::d_real_constants<d_real<float>, float>;
        vf_type kf = rint(vf_type(x * ctbl::m_1_lg2[0]));
        vf_type hi = x - kf * ctbl::m_lg2_cw[0];
        vf_type xr = hi - kf * ctbl::m_lg2_cw[1];
        vf_type dx= (hi-xr);
        vf_type cr = dx-kf * ctbl::m_lg2_cw[1];
        // for exp10 mul12 would be sufficient
        d_ops::mul122(xrh, xrl, xr, ctbl::m_ln10[0], ctbl::m_ln10[1]);
        xrl += cr * ctbl::m_ln10[0];
        // do not normalize xrh, xrl
        // d_ops::add12(xrh, xrl, xrh, xrl);
        y=__exp_k<_EXP10_M1>(xrh, xrl, kf);
    }
    return y;
#else
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x * ctbl::m_1_lg2[0]));
    vf_type hi = x - kf * ctbl::m_lg2_cw[0];
    vf_type xr = hi - kf * ctbl::m_lg2_cw[1];
    vf_type dx= (hi-xr);
    vf_type cr = dx-kf * ctbl::m_lg2_cw[1];
    vf_type xrh, xrl;
    // for exp10 mul12 would be sufficient
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln10[0], ctbl::m_ln10[1]);
    xrl += cr * ctbl::m_ln10[0];
    // do not normalize xrh, xrl
    // d_ops::add12(xrh, xrl, xrh, xrl);
    vf_type y=__exp_k<_EXP10_M1>(xrh, xrl, kf);
    return y;
#endif
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
#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp10_arg(xrh, xrl, idx, ki, x2h, x2l);
    vf_type y=__exp_tbl_k(xrh, xrl, idx, ki);
#else
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x2h*ctbl::m_1_lg2[0]));
    vf_type neg_kfln10h, neg_kfln10l;
    d_ops::mul122(neg_kfln10h, neg_kfln10l,
                  kf, -ctbl::m_lg2[0], -ctbl::m_lg2[1]);
    vf_type xrh, xrl;
    d_ops::add22cond(xrh, xrl,
                     x2h, x2l,
                     neg_kfln10h, neg_kfln10l);
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln10[0], ctbl::m_ln10[1]);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
#endif
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
#if 1
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp10_arg(xrh, xrl, idx, ki, x2h, x2l);
    vf_type y=__exp_tbl_k(xrh, xrl, idx, ki);
#else
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x2h*ctbl::m_1_lg2[0]));
    vf_type neg_kfln10h, neg_kfln10l;
    d_ops::mul122(neg_kfln10h, neg_kfln10l,
                  kf, -ctbl::m_lg2[0], -ctbl::m_lg2[1]);
    vf_type xrh, xrl;
    d_ops::add22cond(xrh, xrl,
                     x2h, x2l,
                     neg_kfln10h, neg_kfln10l);
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln10[0], ctbl::m_ln10[1]);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
#endif
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
sinh_cosh_k(arg_t<vf_type> xc)
{
    static_assert(_F != hyperbolic_func::c_tanh);

    vf_type x= abs(xc);
    vmf_type x_tiny;
    vf_type res= 0.0;
    // x^ : +0xb.17218p-6f
    constexpr
    const float sinh_i0_right=+1.7328679562e-01f;

    if (_F == hyperbolic_func::c_sinh) {
        x_tiny= x <= sinh_i0_right;
        if (any_of(x_tiny)) {
            // [0, 0.17328679561614990234375] : | p - f | <= 2^-34.921875
            // coefficients for sinh generated by sollya
            // x^1 : +0x8p-3f
            constexpr
            const float sinh_c1=+1.0000000000e+00f;
            // x^3 : +0xa.aaaa5p-6f
            constexpr
            const float sinh_c3=+1.6666658223e-01f;
            // x^5 : +0x8.8ac83p-10f
            constexpr
            const float sinh_c5=+8.3419112489e-03f;

            static_assert(sinh_c1==1.0f, "constraint violated");
            vf_type xs2=x*x;
            vf_type yt=horner(xs2, sinh_c5, sinh_c3)*xs2;
            yt= x + x*yt;
            res = _T::sel(x_tiny, yt, res);
        }
    }
    if (_F == hyperbolic_func::c_cosh || !all_of(x_tiny)) {
        vf_type xrh, xrl;
        vi_type k, idx;
        __reduce_exp_arg(xrh, xrl, idx, k, x);
        vi_type k0=k;

        // 1/2
        k -= 1;
        vf_type yh, yl;
        yh = __exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &yl);

        auto sc=__scale_exp_k(k);
        yh *= sc.f0();
        yh *= sc.f1();

        vmf_type x_medium;
        if (_F == hyperbolic_func::c_sinh)
            x_medium = (x > sinh_i0_right) & _T::vmi_to_vmf(k <14);
        else
            x_medium = _T::vmi_to_vmf(k <14);

        if (any_of(x_medium)) {
            // perform the scaling also for the low part
            yl *= sc.f0();
            yl *= sc.f1();

            vf_type nxrh, nxrl;
            vi_type nk, nidx;
            // base_type::__reduce_exp_arg(nxrh, nxrl, nidx, nk, -x);
            nxrh = -xrh;
            nxrl = -xrl;
            vi_type s=-((k0<<exp_data<float>::EXP_SHIFT)+idx);
            nk= s >> exp_data<float>::EXP_SHIFT;
            nidx= s & exp_data<float>::EXP_IDX_MASK;
            nk -= 1;

            vf_type nyh, nyl;
            nyh = __exp_tbl_k<result_prec::medium>(nxrh, nxrl, nidx, &nyl);
            // we know k < 14
            // auto nsc=__scale_exp_k(nk);
            // nyh *= nsc.f0();
            // nyl *= nsc.f0();
            // nyh *= nsc.f1();
            // nyl *= nsc.f1();
            vf_type nsc=_T::insert_exp(_T::bias() + nk);

            if (_F == hyperbolic_func::c_sinh)
                nsc = -nsc;

            nyh *= nsc;
            nyl *= nsc;

            vf_type zh, zl;
            d_ops::add22(zh, zl, yh, yl, nyh, nyl);
            yh = _T::sel(x_medium, zh, yh);
        }
        if (_F == hyperbolic_func::c_sinh) {
            res=_T::sel(x_tiny, res, yh);
        } else {
            res=yh;
        }
    }
    if (_F==hyperbolic_func::c_sinh) {
        res = copysign(res, xc);
    }
    return res;
}


template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
cosh_k(arg_t<vf_type> x)
{
    return sinh_cosh_k<hyperbolic_func::c_cosh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
sinh_k(arg_t<vf_type> x)
{
    return sinh_cosh_k<hyperbolic_func::c_sinh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
tanh_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    using fc=func_constants<float>;
    vf_type tanh_x=1.0;
    // x^ : +0xb.17218p-9f
    constexpr
    const float tanh_i0_right=+2.1660849452e-02f;
    vmf_type x_tiny = xa <= tanh_i0_right;
    if (any_of(x_tiny)) {
        // [0, 2.166084945201873779296875e-2] : | p - f | <= 2^-33.125
        // coefficients for tanh generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float tanh_c1=+1.0000000000e+00f;
        // x^3 : -0xa.aa3d6p-5f
        constexpr
        const float tanh_c3=-3.3328121901e-01f;
        static_assert(tanh_c1==1.0f, "oops");
        vf_type x2=xa*xa;
        vf_type p= tanh_c3*x2;
        vf_type tt=xa+p*xa;
        tanh_x=_T::sel(x_tiny, tt, tanh_x);
    }
    vmf_type x_medium=(xa > tanh_i0_right) & (xa<fc::tanh_one());
    if (any_of(x_medium)) {
        vf_type xae=min(vf_type(2.0f*xa), vf_type(2.0f*fc::tanh_one()));
        vf_type xrh, xrl;
        vi_type idx, ki;
        __reduce_exp_arg(xrh, xrl, idx, ki, xae);
        vf_type ex, exl;
        ex=__exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &exl);
        auto sc=_T::insert_exp(_T::bias() + ki);
        ex  *= sc;
        exl *= sc;

        vf_type exm1, exm1l;
        d_ops::add122cond(exm1, exm1l, -1.0, ex, exl);
        vf_type exp1, exp1l;
        d_ops::add122cond(exp1, exp1l, 1.0, ex, exl);
        vf_type tanh_h, tanh_l;
        d_ops::div22(tanh_h, tanh_l, exm1, exm1l, exp1, exp1l);
        tanh_x = _T::sel(x_medium, tanh_h, tanh_x);
    }
    tanh_x=copysign(tanh_x, xc);
    return tanh_x;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _LFUNC>
inline
void
cftal::math::elem_func_core<float, _T>::
__reduce_log_arg(vf_type& xr,
                 vf_type& inv_c,
                 vf_type& log_c_h,
                 vf_type& log_c_l,
                 vf_type& kf,
                 arg_t<vf_type> xc,
                 vi_type* pk)

{
    constexpr
    const bytes4 offs=0x3f350000;
    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_val_or_zero(_T::vmf_to_vmi(is_denom), vi_type(-25));
    vi_type hx = _T::as_int(x);
    // reduce x into [offs, 2*offs]
    hx += (0x3f800000 - offs.s32());
    k += (hx>>23) - _T::bias();
    vi_type m = (hx&0x007fffff);
    hx = m + offs.s32();
    vi_type idx=(m >> (23-log_data<float>::LOG_SHIFT));
    xr = _T::as_float(hx);
    auto lck=make_variable_lookup_table<float>(idx);
    const auto& tbl=log_data<float>::_tbl;

    inv_c =lck.from(tbl._inv_c);
    switch (_LFUNC) {
    case log_func::c_log_e:
        log_c_h=lck.from(tbl._log_c_h);
        log_c_l=lck.from(tbl._log_c_l);
        break;
    case log_func::c_log_2:
        log_c_h=lck.from(tbl._log2_c_h);
        log_c_l=lck.from(tbl._log2_c_l);
        break;
    case log_func::c_log_10:
        log_c_h=lck.from(tbl._log10_c_h);
        log_c_l=lck.from(tbl._log10_c_l);
        break;
    }
    // log(z)= log(ck*(1+xr/ck))= log(ck) + log(1+xr/ck);
    // x^ : +0xe.f7d4bp-4f
    constexpr
    const float _one_m_delta=+9.3550556898e-01f;
    // x^ : +0x8.8415bp-3f
    constexpr
    const float _one_p_delta=+1.0644944906e+00f;
    // in this range we use the tables:
    vmf_type xr_not_near_one=(xr < _one_m_delta) |
        (xr > _one_p_delta);
    /* 1/c == 1 around 1*/
    inv_c = _T::sel(xr_not_near_one, inv_c, 1.0f);
    /* log_c_h, log_c_l = 0.0 around 1 */
    log_c_h = _T::sel_val_or_zero(xr_not_near_one, log_c_h);
    log_c_l = _T::sel_val_or_zero(xr_not_near_one, log_c_l);
    kf=_T::cvt_i_to_f(k);
    if (pk != nullptr)
        *pk = k;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__log_tbl_k(arg_t<vf_type> xc)
{
    vf_type xr, inv_c, log_c_h, log_c_l, kf;
    __reduce_log_arg<_LFUNC>(xr, inv_c, log_c_h, log_c_l, kf, xc);
    vf_type r;
    if (d_real_traits<vf_type>::fma == true) {
        r = xr * inv_c - 1.0f;
    } else {
        vf_type ph, pl;
        d_real_traits<vf_type>::split(xr, ph, pl);
        ph *= inv_c;
        pl *= inv_c;
        r = (ph - 1.0f) + pl;
    }
    // [-6.44944608211517333984375e-2, 6.44944608211517333984375e-2] : | p - f | <= 2^-35.15625
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_c1=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    constexpr
    const float log_c2=-5.0000000000e-01f;
    // x^3 : +0xa.aaa86p-5f
    constexpr
    const float log_c3=+3.3333224058e-01f;
    // x^4 : -0xf.fffb8p-6f
    constexpr
    const float log_c4=-2.4999892712e-01f;
    // x^5 : +0xc.da81ep-6f
    constexpr
    const float log_c5=+2.0083662868e-01f;
    // x^6 : -0xa.b72fbp-6f
    constexpr
    const float log_c6=-1.6743080318e-01f;
    static_assert(log_c1 == 1.0f);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    static const float ci[]={
        log_c6, log_c5, log_c4, log_c3, log_c2
    };
    vf_type lh;
    vf_type r2 = r * r;
    vf_type p=horner2(r, r2, ci);
    if (_LFUNC==log_func::c_log_e) {
        lh= p*r2 + r;
        lh += log_c_l;
        lh += kf * ctbl::m_ln2_cw[1];
        lh += log_c_h;
        lh += kf * ctbl::m_ln2_cw[0];
    } else if (_LFUNC==log_func::c_log_2) {
        // x^ : +0xb.8bp-3f
        constexpr
        const float invln2hi=+1.4428710938e+00f;
        // x^ : -0xb.89ad4p-16f
        constexpr
        const float invln2lo=-1.7605285393e-04f;
        vf_type r2p=p*r2;
        vf_type th, tl;
        vf_type rh, rl;
        if (d_real_traits<vf_type>::fma==true) {
            th = r2p * invln2hi;
            vf_type th_e= r2p*invln2hi-th;
            tl = r2p * invln2lo + th_e;
            rh = r * invln2hi;
            vf_type rh_e= r*invln2hi-rh;
            rl = r * invln2lo + rh_e;
        } else {
            d_real_traits<vf_type>::split(r2p, th, tl);
            th = th * invln2hi;
            tl = tl * invln2hi + (r2p* invln2lo);
            d_real_traits<vf_type>::split(r, rh, rl);
            rh = rh * invln2hi;
            rl = rl * invln2hi + (r* invln2lo);
        }
        lh = ((tl + rl) + th) + rh;

        lh += log_c_l;
        lh += log_c_h;
        lh += kf;
    } else if (_LFUNC==log_func::c_log_10) {
        // x^ : +0xd.e6p-5f
        constexpr
        const float invln10hi=+4.3432617188e-01f;
        // x^ : -0x8.4ead9p-18f
        constexpr
        const float invln10lo=-3.1689971365e-05f;
        vf_type r2p=p*r2;
        vf_type th, tl;
        vf_type rh, rl;
        if (d_real_traits<vf_type>::fma==true) {
            th = r2p * invln10hi;
            vf_type th_e= r2p*invln10hi-th;
            tl = r2p * invln10lo + th_e;
            rh = r * invln10hi;
            vf_type rh_e= r*invln10hi-rh;
            rl = r * invln10lo + rh_e;
        } else {
            d_real_traits<vf_type>::split(r2p, th, tl);
            th = th * invln10hi;
            tl = tl * invln10hi + (r2p* invln10lo);
            d_real_traits<vf_type>::split(r, rh, rl);
            rh = rh * invln10hi;
            rl = rl * invln10hi + (r* invln10lo);
        }
        lh = ((tl + rl) + th) + rh;
        lh += log_c_l;
        lh += kf * ctbl::m_lg2_cw[1];
        lh += log_c_h;
        lh += kf * ctbl::m_lg2_cw[0];
    }
    return lh;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _LFUNC,
          typename cftal::math::elem_func_core<float, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log_tbl_k(arg_t<vf_type> r, arg_t<vf_type> rl,
                arg_t<vf_type> log_c_h, arg_t<vf_type> log_c_l,
                arg_t<vf_type> kf)
{
    // [-6.44944608211517333984375e-2, 6.44944608211517333984375e-2] : | p - f | <= 2^-35.15625
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_c1=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    constexpr
    const float log_c2=-5.0000000000e-01f;
    // x^3 : +0xa.aaa86p-5f
    constexpr
    const float log_c3=+3.3333224058e-01f;
    // x^4 : -0xf.fffb8p-6f
    constexpr
    const float log_c4=-2.4999892712e-01f;
    // x^5 : +0xc.da81ep-6f
    constexpr
    const float log_c5=+2.0083662868e-01f;
    // x^6 : -0xa.b72fbp-6f
    constexpr
    const float log_c6=-1.6743080318e-01f;
    static_assert(log_c1 == 1.0f);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    static const float ci[]={
        log_c6, log_c5, log_c4, log_c3
    };
    vf_type p=horner(r, ci);
    vf_type ph, pl;
    horner_comp_quick(ph, pl, r, p, log_c2, log_c1);
    vf_type lh, ll;
    if (_LFUNC==log_func::c_log_e) {
        d_ops::mul22(lh, ll, r, rl, ph, pl);
        vf_type kh, kl;
        d_ops::mul122(kh, kl, kf, ctbl::m_ln2[0], ctbl::m_ln2[1]);
        d_ops::add22(lh, ll, log_c_h, log_c_l, lh, ll);
        // |kh, kl | >= log(2) or 0
        d_ops::add22(lh, ll, kh, kl, lh, ll);
    } else if (_LFUNC==log_func::c_log_2) {
        vf_type r2, r2l;
        d_ops::mul22(r2, r2l, r, rl,
                     ctbl::m_1_ln2[0], ctbl::m_1_ln2[1]);
        d_ops::mul22(lh, ll, r2, r2l, ph, pl);
        d_ops::add22(lh, ll, log_c_h, log_c_l, lh, ll);
        d_ops::add122(lh, ll, kf, lh, ll);
    } else if (_LFUNC==log_func::c_log_10) {
        vf_type r10, r10l;
        d_ops::mul22(r10, r10l, r, rl,
                     ctbl::m_1_ln10[0], ctbl::m_1_ln10[1]);
        vf_type kh, kl;
        d_ops::mul122(kh, kl, kf, ctbl::m_lg2[0], ctbl::m_lg2[1]);
        d_ops::mul22(lh, ll, r10, r10l, ph, pl);
        d_ops::add22(lh, ll, log_c_h, log_c_l, lh, ll);
        d_ops::add22(lh, ll, kh, kl, lh, ll);
    }
    return dvf_type(lh, ll);
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _LFUNC,
          typename cftal::math::elem_func_core<float, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log_tbl_k2(arg_t<vf_type> xc, arg_t<vf_type> xcl)
{
    vf_type xr, kf, inv_c, log_c_h, log_c_l;
    vi_type k;
    __reduce_log_arg<_LFUNC>(xr,
                             inv_c, log_c_h, log_c_l,
                             kf,
                             xc,
                             &k);
    vf_type xrl = ldexp_k(xcl, -k);
    vf_type lh;
    vf_type r, rl;
    d_ops::mul122(r, rl, inv_c, xr, xrl);
    d_ops::add122cond(r, rl, -1.0f, r, rl);
    return __pow_log_tbl_k<_LFUNC, _P>(r, rl, log_c_h, log_c_l, kf);
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _LFUNC,
          typename cftal::math::elem_func_core<float, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log_tbl_k(arg_t<vf_type> xc)
{
    vf_type xr, kf, inv_c, log_c_h, log_c_l;
    __reduce_log_arg<_LFUNC>(xr,
                             inv_c, log_c_h, log_c_l,
                             kf,
                             xc);

    vf_type r, rl;
    if (d_real_traits<vf_type>::fma == true) {
        d_ops::mul12(r, rl, xr, inv_c);
        d_ops::add122cond(r, rl, -1.0f, r, rl);
        // r = xr * inv_c - 1.0;
    } else {
        vf_type ph, pl;
        d_real_traits<vf_type>::split(xr, ph, pl);
        ph *= inv_c;
        pl *= inv_c;
        d_ops::add12(ph, pl, ph, pl);
        // r = (ph - 1.0f) + pl;
        d_ops::add122(r, rl, -1.0f, ph, pl);
    }
    return __pow_log_tbl_k<_LFUNC, _P>(r, rl, log_c_h, log_c_l, kf);
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__reduce_log_arg(vf_type& xr,
                 vf_type& kf,
                 arg_t<vf_type> xc,
                 vi_type* pk)
{
    // MSQRT2/2
    constexpr
    const bytes4 offs=0x3f3504f3;

    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_val_or_zero(_T::vmf_to_vmi(is_denom), vi_type(-25));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += (0x3f800000 - offs.s32());
    k += (hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + offs.s32();
    xr = _T::as_float(hx);
    kf = _T::cvt_i_to_f(k);
    if (pk != nullptr)
        *pk = k;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__log_k_poly(arg_t<vf_type> z)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-32.90625
    // coefficients for log generated by sollya
    // x^2 : +0xa.aaaabp-4f
    const float log_c2=+6.6666668653e-01f;
    // x^4 : +0xc.ccc36p-5f
    const float log_c4=+3.9999550581e-01f;
    // x^6 : +0x9.2610fp-5f
    const float log_c6=+2.8589674830e-01f;
    // x^8 : +0xe.72cb8p-6f
    const float log_c8=+2.2575652599e-01f;

    static const float ci[]={
        log_c8, log_c6, log_c4, log_c2
    };
    vf_type y=horner2(z, vf_type(z*z), ci);
    return y;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__log_k(arg_t<vf_type> xc)
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
    vf_type xr, kf;
    __reduce_log_arg(xr, kf, xc);


    vf_type f = xr - 1.0f;
    // vf_type s = f/(2.0f+f);
    vf_type s = f/(xr + 1.0f);
    vf_type z = s*s;
    vf_type hfsq = (0.5f *f)*f;

    // split of the polynomial reduces precision
    vf_type R = __log_k_poly(z);
    vf_type hfsqR= R*z + hfsq;
    vf_type res;
    if (_LFUNC == log_func::c_log_e) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vf_type log_x=s*(hfsqR);
        log_x += kf*ctbl::m_ln2_cw[1];
        log_x -= hfsq;
        log_x += f;
        log_x += kf*ctbl::m_ln2_cw[0];
        res = log_x;
    } else if (_LFUNC == log_func::c_log_10) {
        const float ivln10hi  =  4.3432617188e-01f; /* 0x3ede6000 */
        const float ivln10lo  = -3.1689971365e-05f; /* 0xb804ead9 */
        const float log10_2hi =  3.0102920532e-01f; /* 0x3e9a2080 */
        const float log10_2lo =  7.9034151668e-07f; /* 0x355427db */

        vf_type t = f - hfsq;
        vi_type it= _T::as_int(t);
        it &= vi_type(0xfffff000);
        vf_type hi= _T::as_float(it);
        vf_type lo= f - hi -hfsq + s * (hfsqR);

        vf_type val_hi = hi * ivln10hi;
        vf_type y = kf* log10_2hi;
        vf_type val_lo = kf * log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;

        vf_type w= y + val_hi;
        val_lo += (y - w) + val_hi;
        val_hi = w;

        vf_type log10_x = val_lo + val_hi;
        res =log10_x;
    } else if (_LFUNC == log_func::c_log_2) {
        const float ivln2hi =  1.4428710938e+00f; /* 0x3fb8b000 */
        const float ivln2lo = -1.7605285393e-04f; /* 0xb9389ad4 */

        vf_type t= f - hfsq;
        vi_type it= _T::as_int(t);
        it &= vi_type(0xfffff000);
        vf_type hi= _T::as_float(it);
        vf_type lo= f - hi - hfsq + s * (hfsqR);
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
    // MSQRT2/2
    constexpr
    const bytes4 offs=0x3f3504f3;

    vf_type x=xc;
    vf_type u= 1+xc;
    vi_type hu=_T::as_int(u);
    hu += (0x3f800000 - offs.s32());
    vi_type k=(hu >> 23) - _T::bias();
    vf_type kf= _T::cvt_i_to_f(k);
    /* reduce u into [sqrt(2)/2, sqrt(2)] */
    hu = (hu&0x007fffff) + offs.s32();
    vf_type nu = _T::as_float(hu);
    vf_type f= nu -1.0f;

    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-x), x-(u-1.0f));
    c_k_2 /= u;
    vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);

    // vf_type s = f/(2.0f+f);
    vf_type s = f/(nu + 1.0f);
    vf_type z = s*s;
    vf_type hfsq = 0.5f*f*f;
    vf_type R = __log_k_poly(z);
    vf_type hfsqR= R*z + hfsq;

    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type log1p_x= s*(hfsqR);
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
log_k(arg_t<vf_type> xc)
{
    // return __pow_log_k<log_func::c_log_e,
    //                    result_prec::normal>(xc)[0];
#if USE_TABLE_BASED_LOG>0
    return __log_tbl_k<log_func::c_log_e>(xc);
#else
    return __log_k<log_func::c_log_e>(xc);
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log2_k(arg_t<vf_type> xc)
{
    // return __pow_log_k<log_func::c_log_2>(xc)[0];
/*
 * Return the base 2 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log2(x) = (f - f*f/2 + r)/log(2) + k
 */
#if USE_TABLE_BASED_LOG>0
    return __log_tbl_k<log_func::c_log_2>(xc);
#else
    return __log_k<log_func::c_log_2>(xc);
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log10_k(arg_t<vf_type> xc)
{
    // return __pow_log_k<log_func::c_log_10>(xc)[0];
/*
 * Return the base 10 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log10(x) = (f - f*f/2 + r)/log(10) + k*log10(2)
 */
#if USE_TABLE_BASED_LOG>0
    return __log_tbl_k<log_func::c_log_10>(xc);
#else
    return __log_k<log_func::c_log_10>(xc);
#endif
}

template <typename _T>
__attribute__((always_inline))
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__pow_exp_poly_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                 vf_type* exl)
{

    // coefficients for pow_exp generated by sollya
    // x^0 : +0x8p-3f
    constexpr
    const float pow_exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    constexpr
    const float pow_exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    constexpr
    const float pow_exp_c2=+5.0000000000e-01f;
    // x^3 : +0xa.aaaabp-6f
    constexpr
    const float pow_exp_c3=+1.6666667163e-01f;
    // x^4 : +0xa.aaaacp-8f
    constexpr
    const float pow_exp_c4=+4.1666671634e-02f;
    // x^5 : +0x8.887f6p-10f
    constexpr
    const float pow_exp_c5=+8.3331968635e-03f;
    // x^6 : +0xb.6078p-13f
    constexpr
    const float pow_exp_c6=+1.3887733221e-03f;
    // x^7 : +0xd.13c49p-16f
    constexpr
    const float pow_exp_c7=+1.9954251184e-04f;
    // x^8 : +0xd.59c5dp-19f
    constexpr
    const float pow_exp_c8=+2.5464391001e-05f;
    vf_type xx= xrh*xrh;

    static const float ci[]={
        pow_exp_c8, pow_exp_c7, pow_exp_c6,
        pow_exp_c5, pow_exp_c4, pow_exp_c3
    };
    vf_type y=horner2(xrh, xx, ci);
    vf_type ye;
    horner_comp_quick(y, ye, xrh, y, pow_exp_c2, pow_exp_c1);
    // correction for errors in argument reduction
    vf_type yl=y+ye;
    horner_comp_quick_si(y, ye, xrh, y, ye, pow_exp_c0);
    vf_type yee= xrl + xrl*xrh*yl;
    ye += yee;
    if (exl==nullptr) {
        y += ye;
    } else {
        d_ops::add12(y, ye, y, ye);
        *exl= ye;
    }
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__pow_exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vf_type> kf,
            vf_type* exl)
{
    vf_type y=__pow_exp_poly_k(xrh, xrl, exl);
    auto sc= __scale_exp_k(kf);
    y = (y* sc.f0()) * sc.f1();
    if (exl != nullptr) {
        vf_type ye=*exl;
        *exl = (ye * sc.f0())* sc.f1();
    }
    return y;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _F,
          typename cftal::math::elem_func_core<float, _T>::result_prec _P>
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log_k(arg_t<vf_type> sh, arg_t<vf_type> sl, arg_t<vf_type> kf)
{
    dvf_type ds(sh, sl);
    dvf_type ds2=sqr(ds);
    vf_type s2= ds2[0];
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vf_type th, tl;
    if (_F == log_func::c_log_e) {
        d_ops::mul122(th, tl, kf,
                      ctbl::m_ln2[0], ctbl::m_ln2[1]);
    } else if (_F == log_func::c_log_2) {
        d_ops::mul22(th, tl, ds[0], ds[1],
                     ctbl::m_1_ln2[0], ctbl::m_1_ln2[1]);
    } else if (_F == log_func::c_log_10) {
        d_ops::mul22(th, tl, ds[0], ds[1],
                     ctbl::m_1_ln10[0], ctbl::m_1_ln10[1]);
    }

    vf_type s4=s2*s2;
    vf_type ph, pl;
    if (_P == result_prec::high) {
        // [0, 0.17157287895679473876953125] : | p - f | <= 2^-46.890625
        // coefficients for pow_log_hp generated by sollya
        // x^1 : +0x8p-2f
        const float pow_log_hp_c1=+2.0000000000e+00f;
        // x^3 h: +0xa.aaaabp-4f
        const float pow_log_hp_c3h=+6.6666668653e-01f;
        // x^3 l: -0xa.996c6p-29f
        const float pow_log_hp_c3l=-1.9742753210e-08f;
        // x^5 : +0xc.ccccbp-5f
        const float pow_log_hp_c5=+3.9999994636e-01f;
        // x^7 : +0x9.24a28p-5f
        const float pow_log_hp_c7=+2.8572201729e-01f;
        // x^9 : +0xe.30c59p-6f
        const float pow_log_hp_c9=+2.2172679007e-01f;
        // x^11 : +0xc.904ccp-6f
        const float pow_log_hp_c11=+1.9630736113e-01f;
        static const float ci[]= {
            pow_log_hp_c11,
            pow_log_hp_c9,  pow_log_hp_c7
        };
        vf_type p= horner(s2, ci);
        vf_type s2l=ds2[1];
        d_ops::mul122(ph, pl, p, s2, s2l);
        d_ops::add122(ph, pl, pow_log_hp_c5, ph, pl);
        d_ops::mul22(ph, pl, s2, s2l, ph, pl);
        d_ops::add22(ph, pl, pow_log_hp_c3h, pow_log_hp_c3l, ph, pl);
        d_ops::mul22(ph, pl, s2, s2l, ph, pl);
        d_ops::add122(ph, pl, pow_log_hp_c1, ph, pl);
    } else {
        // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-39.5
        // coefficients for pow_log generated by sollya
        // x^1 : +0x8p-2f
        const float pow_log_c1=+2.0000000000e+00f;
        // x^3 : +0xa.aaaabp-4f
        const float pow_log_c3=+6.6666668653e-01f;
        // x^5 : +0xc.ccc17p-5f
        const float pow_log_c5=+3.9999458194e-01f;
        // x^7 : +0x9.289dap-5f
        const float pow_log_c7=+2.8620797396e-01f;
        // x^9 : +0xd.09b1p-6f
        const float pow_log_c9=+2.0371651649e-01f;
        // x^11 : +0xd.d007bp-5f
        const float pow_log_c11=+4.3164429069e-01f;

        static const float ci[]= {
            pow_log_c11, pow_log_c9,
            pow_log_c7,  pow_log_c5
        };
        vf_type p= horner2(s2, s4, ci);
#if 0
        d_ops::muladd12(ph, pl, pow_log_c3, s2, p);
        vf_type s2l=ds2[1];
        d_ops::mul22(ph, pl, ph, pl, s2, s2l);
        d_ops::add122(ph, pl, pow_log_c1, ph, pl);
#else
        horner_comp_quick(ph, pl, s2, p, pow_log_c3, pow_log_c1);
#endif
    }
    if (_F == log_func::c_log_e) {
        d_ops::mul22(ph, pl, ds[0], ds[1], ph, pl);
        // |kf * ln(2)| >= ph, pl if kf !=0
        d_ops::add22(ph, pl, th, tl, ph, pl);
    } else if (_F == log_func::c_log_2) {
        d_ops::mul22(ph, pl, th, tl, ph, pl);
        // |kf| >= ph, pl if kf !=0
        d_ops::add122(ph, pl, kf, ph, pl);
    } else if (_F == log_func::c_log_10) {
        vf_type kfh, kfl;
        d_ops::mul122(kfh, kfl, kf, ctbl::m_lg2[0], ctbl::m_lg2[1]);
        d_ops::mul22(ph, pl, th, tl, ph, pl);
        // |kf * lg(2)| >= ph, pl if kf !=0
        d_ops::add22(ph, pl, kfh, kfl, ph, pl);
    }
    return dvf_type(ph, pl);
}


template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _F,
          typename cftal::math::elem_func_core<float, _T>::result_prec _P>
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log_k(arg_t<vf_type> xc)
{
#if 1
    vf_type xr, kf;
    __reduce_log_arg(xr, kf, xc);
#else
    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_val_or_zero(_T::vmf_to_vmi(is_denom), vi_type(-25));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += (0x3f800000 - 0x3f3504f3);
    k += (hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + 0x3f3504f3;
    vf_type xr = _T::as_float(hx);
    vf_type kf = _T::cvt_i_to_f(k);
#endif
    // brute force:
    vf_type ymh, yml;
    d_ops::add12cond(ymh, yml, xr, vf_type(-1.0f));
    vf_type yph, ypl;
    d_ops::add12cond(yph, ypl, xr, vf_type(+1.0f));
    vf_type qh, ql;
    d_ops::div22(qh, ql, ymh, yml, yph, ypl);

    return __pow_log_k<_F, _P>(qh, ql, kf);
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::log_func _F,
          typename cftal::math::elem_func_core<float, _T>::result_prec _P>
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__pow_log_k2(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
#if 1
    vf_type xrh, kf;
    vi_type k;
    __reduce_log_arg(xrh, kf, xh, &k);
    auto sc=__scale_exp_k(-k);
    vf_type xrl=(xl * sc.f0()) * sc.f1();
#else
    vf_type xrh;
    auto k=__frexp_k(xrh, xh);
    vf_type xrl=ldexp_k(xl, -k);

    vmf_type c= xrh < M_SQRT2*0.5f;
    vf_type kf = _T::cvt_i_to_f(k);
    xrh = _T::sel(c, xrh*2.0f, xrh);
    xrl = _T::sel(c, xrl*2.0f, xrl);
    kf = _T::sel(c, kf-1.0f, kf);
#endif
    vf_type ymh, yml;
    d_ops::add122cond(ymh, yml, -1.0f, xrh, xrl);
    vf_type yph, ypl;
    d_ops::add122cond(yph, ypl, +1.0f, xrh, xrl);
    vf_type qh, ql;
    d_ops::div22(qh, ql, ymh, yml, yph, ypl);
    return __pow_log_k<_F, _P>(qh, ql, kf);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type abs_x= abs(x);
#if USE_TABLE_BASED_LOG>0
    dvf_type ldx= __pow_log_tbl_k<log_func::c_log_2,
                                  result_prec::normal>(abs_x);
#else
    dvf_type ldx= __pow_log_k<log_func::c_log_2,
                              result_prec::normal>(abs_x);
#endif
    dvf_type yldx;
    // yldx = y*ldx;
    d_ops::mul122(yldx[0], yldx[1], y, ldx[0], ldx[1]);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, yldx[0], yldx[1]);
    vf_type res=__exp_tbl_k(xrh, xrl, idx, ki);

    using fc=func_constants<float>;
    const vf_type& d= yldx[0];
    const float exp2_hi_inf= fc::exp2_hi_inf();
    const float exp2_lo_zero= fc::exp2_lo_zero();
    res = _T::sel_zero_or_val(d <= exp2_lo_zero, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::pow_k2_result
cftal::math::elem_func_core<float, _T>::
pow_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
       arg_t<vf_type> yh, arg_t<vf_type> yl)
{
    dvf_type abs_x= select(xh > 0.0f, dvf_type(xh, xl), dvf_type(-xh, -xl));
#if USE_TABLE_BASED_LOG>0
    dvf_type ldx=__pow_log_tbl_k2<log_func::c_log_2,
                                  result_prec::normal>(abs_x[0], abs_x[1]);
#else
    dvf_type ldx=__pow_log_k2<log_func::c_log_2,
                              result_prec::normal>(abs_x[0], abs_x[1]);
#endif
    // yldx = y*ldx;
    dvf_type yldx;
    d_ops::mul22(yldx[0], yldx[1], yh, yl, ldx[0], ldx[1]);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, yldx[0], yldx[1]);
    vf_type rl;
    vf_type rh=__exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &rl);
    auto sc = __scale_exp_k(ki);
    return std::make_pair(dvf_type(rh, rl), sc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_trig_arg(vf_type& xrh, vf_type& xrl, arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type fn= rint(vf_type(x* ctbl::m_2_pi[0]));
    constexpr const float large_arg=0x1p18f;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);

    xrh = x;
    xrl = 0.0;
    if (likely(!all_of(v_large_arg))) {
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
        t = x + p0;
        xrh = t + p1;
        xrl = p1 - (xrh - t) + p2;
        // not required because int32_t is large enough
        // fn= _fmod<4>(fn);
    }
    vi_type q(_T::cvt_f_to_i(fn));
    if (unlikely(any_of(v_large_arg))) {
        // reduce the large arguments
        constexpr const std::size_t N=_T::NVF();
        constexpr const std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(float)) v_d {
            float _sc[N];
        } tf, d0_l, d0_h;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, x);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, xrl);
        mem<vf_type>::store(d0_h._sc, xrh);
        for (std::size_t i=0; i<N; ++i) {
            if (large_arg < std::fabs(tf._sc[i])) {
                float y[2];
                // ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                ti._sc[i]=impl::__kernel_rem_pio2(y, tf._sc[i]);
                d0_l._sc[i]= y[1];
                d0_h._sc[i]= y[0];
            }
        }
        xrh=mem<vf_type>::load(d0_h._sc, N);
        xrl=mem<vf_type>::load(d0_l._sc, N);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    return q;
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
    const float sin_c2=-1.6666667163e-01f;
    // x^4 : +0x8.888b2p-10f
    const float sin_c4=+8.3333719522e-03f;
    // x^6 : -0xd.02433p-16f
    const float sin_c6=-1.9849911041e-04f;
    // x^8 : +0xb.bf108p-22f
    const float sin_c8=+2.8005470085e-06f;
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
    const float cos_c4=+4.1666667908e-02f;
    // x^6 : -0xb.60beap-13f
    const float cos_c6=-1.3889048714e-03f;
    // x^8 : +0xd.07ad8p-19f
    const float cos_c8=+2.4852735805e-05f;
    // x^10 : -0xa.c7898p-25f
    const float cos_c10=-3.2125240068e-07f;
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
    vf_type xrh2;
    d_ops::sqr21(xrh2, xrh, xrl);
    vf_type xrh4=xrh2*xrh2;
    static const float ci[]={
        tan_c15, tan_c13, tan_c11, tan_c9,
        tan_c7, tan_c5, tan_c3
    };
    vf_type t= horner2(xrh2, xrh4, ci);
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
}

template <typename _T>
__attribute__((flatten))
void
cftal::math::elem_func_core<float, _T>::
__sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi_type> q,
            vf_type* ps, vf_type* pc)
{
    vf_type s = __sin_k(xrh, xrl);
    vf_type c = __cos_k(xrh, xrl);
    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));
    // swap sin/cos if q & 1
    // swap signs
    if (ps != nullptr) {
        vf_type rs(_T::sel(q_and_1_f, c, s));
        rs = _T::sel(q_and_2_f, -rs, rs);
        *ps = rs;
    }
    if (pc != nullptr) {
        vf_type rc(_T::sel(q_and_1_f, s, c));
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        rc = _T::sel(mt, -rc, rc);
        *pc= rc;
    }
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
__sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi_type> q,
            dvf_type* ps, dvf_type* pc)
{
    // [5.42101086242752217003726400434970855712890625e-20, 0.785398185253143310546875] : | p - f | <= 2^-35.609375
    // coefficients for sin generated by sollya
    // x^1 : +0x8p-3f
    const float sin_c1=+1.0000000000e+00f;
    // x^3 : -0xa.aaaabp-6f
    const float sin_c3=-1.6666667163e-01f;
    // x^5 : +0x8.888eap-10f
    const float sin_c5=+8.3334241062e-03f;
    // x^7 : -0xd.0a96cp-16f
    const float sin_c7=-1.9899540348e-04f;
    // x^9 : +0x9.5a646p-21f
    const float sin_c9=+4.4599028115e-06f;
    // x^11 : -0x9.d9517p-22f
    const float sin_c11=-2.3481604785e-06f;
    // x^13 : +0xa.0f27cp-23f
    const float sin_c13=+1.1991501196e-06f;

   // [5.42101086242752217003726400434970855712890625e-20, 0.785398185253143310546875] : | p - f | <= 2^-37.953125
    // coefficients for cos generated by sollya
    // x^0 : +0x8p-3f
    const float cos_c0=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    const float cos_c2=-5.0000000000e-01f;
    // x^4 : +0xa.aaaabp-8f
    const float cos_c4=+4.1666667908e-02f;
    // x^6 : -0xb.60bcfp-13f
    const float cos_c6=-1.3889017282e-03f;
    // x^8 : +0xd.0720cp-19f
    const float cos_c8=+2.4848639441e-05f;
    // x^10 : -0xb.b518p-25f
    const float cos_c10=-3.4890763345e-07f;
    // x^12 : +0xb.aa0e2p-28f
    const float cos_c12=+4.3452821785e-08f;

    // sin(x+xl) ~ sin(x) + cos(x)*xl
    // sin(x+xl) ~ x+s3*x^3+s5*x^5 + ... + cos(x)*xl
    //           = x+s3*x^3+s5*x^5 + ... + (1-x*x/2)*xl
    //           = x+s3*x^3+s5*x^5 + ... + xl - x^2*xl/2
    //           = x+s3^x^3+x^2*(s5*x^3+...) + xl - x^2*xl/2
    // with p= s5*x^3+ s7*x^5 + s9*x^7 + ...
    //           = s1*x+s3^x^3+x^2*(p-xl/2)+xl

    // cos(x+xl) ~ 1.0 - 0.5*x^2 + c4*x^4+c4*x5 + ...- sin(x)*xl
    //           ~ 1.0 - 0.5*x^2 + p - x*xl
    // to increase precision add and subtract 1-0.5*x^2:
    //           = (1-0.5*x^2)+(1.0-(1.0-0.5*x^2)-0.5*x^2) + (p-x*xl)
    //           =      w     +(1.0-      w)     -0.5*x^2  + (p-x*xl)

    vf_type ch, sh;
    vf_type xxh, xxl;
    d_ops::sqr22(xxh, xxl, xrh, xrl);

    static const float c_cos[]={
        cos_c12, cos_c10, cos_c8
    };
    static const float c_sin[]={
        sin_c13, sin_c11, sin_c9
    };
    horner_n2(ch, sh, xxh, c_cos, c_sin);
    sh = horner(xxh, sh, sin_c7);

    vf_type cl;
    d_ops::muladd12(ch, cl, cos_c6, ch, xxh);
    d_ops::mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c4, ch, cl);
    d_ops::mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c2, ch, cl);
    d_ops::mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c0, ch, cl);

    vf_type sl;
    d_ops::muladd12(sh, sl, sin_c5, sh, xxh);
    d_ops::mul22(sh, sl, sh, sl, xxh, xxl);
    d_ops::add122(sh, sl, sin_c3, sh, sl);
    d_ops::mul22(sh, sl, sh, sl, xxh, xxl);
    d_ops::add122(sh, sl, sin_c1, sh, sl);
    d_ops::mul22(sh, sl, sh, sl, xrh, xrl);

    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // swap sin/cos if q & 1
    // swap signs
    if (ps != nullptr) {
        vf_type rsh(_T::sel(q_and_1_f, ch, sh));
        vf_type rsl(_T::sel(q_and_1_f, cl, sl));
        rsh = _T::sel(q_and_2_f, -rsh, rsh);
        rsl = _T::sel(q_and_2_f, -rsl, rsl);
        *ps = dvf_type(rsh, rsl);
    }
    if (pc != nullptr) {
        vf_type rch(_T::sel(q_and_1_f, sh, ch));
        vf_type rcl(_T::sel(q_and_1_f, sl, cl));
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        rch = _T::sel(mt, -rch, rch);
        rcl = _T::sel(mt, -rcl, rcl);
        *pc= dvf_type(rch, rcl);
    }
}


template <typename _T>
__attribute__((flatten))
void
cftal::math::elem_func_core<float, _T>::
sin_cos_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type xrh, xrl;
    auto q= __reduce_trig_arg(xrh, xrl, xc);
    __sin_cos_k(xrh, xrl, q, ps, pc);
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
tan_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl;
    auto q= __reduce_trig_arg(xrh, xrl, xc);
    vf_type t=__tan_k(xrh, xrl, q);
    return t;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::dvf_type
cftal::math::elem_func_core<float, _T>::
__atan_0_1_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    vf_type xrh=xh, xrl=xl;
    vf_type ah=0, al=0;
    const float atan_i1_left=+3.7500000000e-01f;
    vmf_type sel=(xrh < atan_i1_left) |
        ((xrh == atan_i1_left) & (xrl < 0.0f));
    if (any_of(sel)) {
        // [0, 0.375] : | p - f | <= 2^-28.390625
        // coefficients for atan_0 generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float atan_i0_c1=+1.0000000000e+00f;
        // x^3 : -0xa.aaa6bp-5f
        const float atan_i0_c3=-3.3333143592e-01f;
        // x^5 : +0xc.caa35p-6f
        const float atan_i0_c5=+1.9986803830e-01f;
        // x^7 : -0x8.f4f96p-6f
        const float atan_i0_c7=-1.3995203376e-01f;
        // x^9 : +0xa.e26b5p-7f
        const float atan_i0_c9=+8.5034765303e-02f;
        static_assert(atan_i0_c1==1.0, "atan_i0_c1 must be 1.0");
        static const float ci[]={
            atan_i0_c9,
            atan_i0_c7, atan_i0_c5, atan_i0_c3
        };
        vf_type x2=xrh*xrh;
        vf_type y_i0_h=horner2(x2, vf_type(x2*x2), ci)*x2;
        vf_type y_i0_l;
        d_ops::muladd12(y_i0_h, y_i0_l, xrh, y_i0_h, xrh);
        d_ops::add212(y_i0_h, y_i0_l, y_i0_h, y_i0_l, xrl);
        ah = _T::sel_val_or_zero(sel, y_i0_h);
        al = _T::sel_val_or_zero(sel, y_i0_l);
    }
    if (!all_of(sel)) {
        // [0.375, 1] : | p - f | <= 2^-29.859375
        // coefficients for atan_i1 generated by sollya
        // x^0 h: +0x9.26382p-4f
        const float atan_i1_c0h=+5.7183086872e-01f;
        // x^0 l: +0xc.d2a47p-29f
        const float atan_i1_c0l=+2.3884366485e-08f;
        // x^1 : +0xb.5069ep-4f
        const float atan_i1_c1=+7.0713222027e-01f;
        // x^2 : -0xa.4c309p-5f
        const float atan_i1_c2=-3.2180050015e-01f;
        // x^3 : +0xe.a281bp-9f
        const float atan_i1_c3=+2.8583576903e-02f;
        // x^4 : +0xc.10e86p-7f
        const float atan_i1_c4=+9.4265982509e-02f;
        // x^5 : -0xa.5a50ap-7f
        const float atan_i1_c5=-8.0881193280e-02f;
        // x^6 : +0x8.ab094p-9f
        const float atan_i1_c6=+1.6929902136e-02f;
        // x^7 : +0xf.1ca54p-9f
        const float atan_i1_c7=+2.9515422881e-02f;
        // x^8 : -0x8.7ffe3p-8f
        const float atan_i1_c8=-3.3203016967e-02f;
        // x^9 : -0xc.2cba2p-13f
        const float atan_i1_c9=-1.4861712698e-03f;
        // x^10 : +0xc.8ec16p-9f
        const float atan_i1_c10=+2.4526637048e-02f;
        // x^ : +0xa.4cp-4f
        const float atan_i1_x0=+6.4355468750e-01f;
        static const float ci[]={
            atan_i1_c10, atan_i1_c9,
            atan_i1_c8, atan_i1_c7, atan_i1_c6, atan_i1_c5,
            atan_i1_c4, atan_i1_c3, atan_i1_c2
        };
        vf_type x_i1_h, x_i1_l;
        d_ops::add122cond(x_i1_h, x_i1_l, -atan_i1_x0, xrh, xrl);
        vf_type y_i1_h=horner2(x_i1_h, vf_type(x_i1_h*x_i1_h), ci);
        vf_type y_i1_l;
        horner_comp_quick(y_i1_h, y_i1_l, x_i1_h, y_i1_h,
                          atan_i1_c1, atan_i1_c0h);
        d_ops::add212(y_i1_h, y_i1_l, y_i1_h, y_i1_l, atan_i1_c0l);
        ah = _T::sel(sel, ah, y_i1_h);
        al = _T::sel(sel, al, y_i1_l);
    }
    return dvf_type(ah, al);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atan_k(arg_t<vf_type> xc)
{
#if 1
    // atan(1/x) = M_PI/2 - atan(x)
    vf_type x=abs(xc);
    using fc=func_constants<float>;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type at=ctbl::m_pi_2[0];
    vmf_type calc_at=x < fc::atan_equal_pi_2();
    if (any_of(calc_at)) {
        vmf_type x_gt_1 = x>1.0f;
        vf_type t=x;
        if (any_of(x_gt_1)) {
            t = _T::sel(x_gt_1, 1.0f/x, t);
        }
        auto dat = __atan_0_1_k(t, 0.0f);
        if (any_of(x_gt_1)) {
            vf_type th, tl;
            d_ops::add22(th, tl,
                        ctbl::m_pi_2[0], ctbl::m_pi_2[1],
                        -dat[0], -dat[1]);
            dat[0] = _T::sel(x_gt_1, th, dat[0]);
        }
        at = _T::sel(calc_at, dat[0], at);
    }
    at=copysign(at, xc);
    return at;
#else
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
    const float atan_c0=+3.3333334327e-01f;
    // x^2 : -0xc.cccffp-6f
    const float atan_c2=-2.0000074804e-01f;
    // x^4 : +0x9.24b9bp-6f
    const float atan_c4=+1.4286653697e-01f;
    // x^6 : -0xe.34345p-7f
    const float atan_c6=-1.1096815020e-01f;
    // x^8 : +0xb.2d878p-7f
    const float atan_c8=+8.7326943874e-02f;
    // x^10 : -0xd.5110fp-8f
    const float atan_c10=-5.2018221468e-02f;

    static const float ci[]={
        atan_c10,
        atan_c8,
        atan_c6,
        atan_c4,
        atan_c2,
        atan_c0
    };

    vf_type t2=t*t;
    vf_type p= t2 * horner2(t2, vf_type(t2*t2), ci);
    vf_type at=  atan_hi - (t * p - atan_lo - t);
    at = copysign(at, xc);
    return at;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atan2_k(arg_t<vf_type> y, arg_t<vf_type> x)
{
#if 1
    // atan(1/x) = M_PI_2 -atan(x) if x>0
    // ax=abs(x)
    // ay=abs(y)
    // calculate at = atan( min(ax, ay)/max(ax, ay) )
    // ay > ax: at = M_PI_2 - atan;
    vf_type ax=abs(x);
    vf_type ay=abs(y);
    vf_type p=min(ax, ay), q=max(ax, ay);

    const double x_y_small =
        d_real_traits<float>::scale_div_threshold();
    vf_type xrh, xrl;
    d_ops::div12(xrh, xrl, p, q);
    vmf_type s;
    if (any_of(s= (ax < x_y_small) | (ay < x_y_small))) {
        // divide p/q very carefully:
        vf_type mp;
        auto ep=__frexp_k(mp, p);
        vf_type mq;
        auto eq=__frexp_k(mq, q);
        vf_type t_xrh, t_xrl;
        d_ops::div12(t_xrh, t_xrl, mp, mq);
        auto de= ep - eq;
        t_xrh = ldexp_k(t_xrh, de);
        t_xrl = ldexp_k(t_xrl, de);
        xrh = _T::sel(s, t_xrh, xrh);
        xrl = _T::sel(s, t_xrl, xrl);
    }

    using ctbl=impl::d_real_constants<d_real<float>, float>;
    auto dat = __atan_0_1_k(xrh, xrl);
    if (any_of(s = ay > ax)) {
        vf_type th, tl;
        d_ops::add22(th, tl,
                    ctbl::m_pi_2[0], ctbl::m_pi_2[1],
                    -dat[0], -dat[1]);
        dat[0] = _T::sel(s, th, dat[0]);
        dat[1] = _T::sel(s, tl, dat[1]);
    }
    vf_type y_s = copysign(vf_type(1.0f), y);
    vf_type x_s = copysign(vf_type(1.0f), x);
    vmf_type y_lt_0 = y_s < 0.0f;
    vmf_type x_lt_0 = x_s < 0.0f;
    // default y>=0, x>=0,
    vf_type at=dat[0];

    // x < 0 & y <0: atan2(y, x) = atan(y/x) - PI
    if (any_of(s=y_lt_0 & x_lt_0)) {
        vf_type at_minus_pi_h, at_minus_pi_l;
        d_ops::add22(at_minus_pi_h, at_minus_pi_l,
                    -ctbl::m_pi[0], -ctbl::m_pi[1],
                    dat[0], dat[1]);
        at = _T::sel(s, at_minus_pi_h, at);
    }

    // y < 0, x>=0: atan2(y, x) =  -atan(y/x)
    at = _T::sel(y_lt_0 & (x_s>=0.0f), -dat[0], at);

    // y >= 0, x < 0: atan2(y, x) = PI - atan(y/x)
    if (any_of(s= (y_s >=0.0f) & x_lt_0)) {
        vf_type pi_minus_at_h, pi_minus_at_l;
        d_ops::add22(pi_minus_at_h, pi_minus_at_l,
                    ctbl::m_pi[0], ctbl::m_pi[1],
                    -dat[0], -dat[1]);
        at = _T::sel(s, pi_minus_at_h, at);
    }
#else
    vf_type yx=y/x;
    vf_type t=atan_k(abs(yx));
    vf_type y_s = copysign(vf_type(1.0f), y);
    vf_type x_s = copysign(vf_type(1.0f), x);

    vmf_type y_lt_0 = y_s < 0.0f;
    vmf_type x_lt_0 = x_s < 0.0f;
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    // default y>=0, x>=0,
    vf_type at= _T::sel(y_lt_0 & x_lt_0,
                        (t - ctbl::m_pi[1]) - ctbl::m_pi[0],
                        t);
    at = _T::sel(y_lt_0 & (x_s>=0), -t, at);
    at = _T::sel((y_s >=0) & x_lt_0,
                 ctbl::m_pi[0] - (t - ctbl::m_pi[1]),
                 at);
#endif
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
    const float asin_c0=+1.6666667163e-01f;
    // x^2 : +0x9.99946p-7f
    const float asin_c2=+7.4999377131e-02f;
    // x^4 : +0xb.6f31dp-8f
    const float asin_c4=+4.4665444642e-02f;
    // x^6 : +0xf.5f16fp-9f
    const float asin_c6=+3.0022351071e-02f;
    // x^8 : +0xc.f08a7p-9f
    const float asin_c8=+2.5272680447e-02f;
    // x^10 : +0xa.b0219p-11f
    const float asin_c10=+5.2187559195e-03f;
    // x^12 : +0x9.a0bp-8f
    const float asin_c12=+3.7608146667e-02f;

    static const float ci[]={
        asin_c12,
        asin_c10,
        asin_c8,
        asin_c6,
        asin_c4,
        asin_c2,
        asin_c0
    };
    vf_type r=x2*horner2(x2, vf_type(x2*x2), ci);
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
    // vf_type as = ctbl::m_pi_2[0] - (2*(s+s*r) - ctbl::m_pi_2[1]);
    // x in [0, 1]
    vi_type t=_T::as_int(s);
    t &= 0xfffff000;
    vf_type f=_T::as_float(t);
    vf_type c= (z-f*f)/(s+f);
    vf_type as1= 0.5f * ctbl::m_pi_2[0] -
                         (2.0f*s*r - (ctbl::m_pi_2[1] -2.0f *c) -
                          (0.5f*ctbl::m_pi_2[0]-2.0f*f));
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
    vf_type ac = ctbl::m_pi_2[0] - (x - (ctbl::m_pi_2[1]-x*r));
    // x in [-1.0, -0.5]
    vf_type wn = r*s - ctbl::m_pi_2[1];
    vf_type ac1= 2*(ctbl::m_pi_2[0] - (s+wn));
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
#if 1
    vf_type y=0;
    vmf_type sel;

    const float asinh_i1_left=+7.0710676908e-01f;
    const float asinh_i1_right=+3.0000000000e+00f;
    if (any_of(sel = x <= asinh_i1_left)) {
        // [0, 0.707106769084930419921875] : | p - f | <= 2^-32.234375
        // coefficients for asinh_i0 generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float asinh_i0_c1=+1.0000000000e+00f;
        // x^3 : -0xa.aaaa7p-6f
        const float asinh_i0_c3=-1.6666661203e-01f;
        // x^5 : +0x9.9981ap-7f
        const float asinh_i0_c5=+7.4997141957e-02f;
        // x^7 : -0xb.6a588p-8f
        const float asinh_i0_c7=-4.4591456652e-02f;
        // x^9 : +0xf.538eap-9f
        const float asinh_i0_c9=+2.9934365302e-02f;
        // x^11 : -0xa.597cap-9f
        const float asinh_i0_c11=-2.0213980228e-02f;
        // x^13 : +0xb.807cfp-10f
        const float asinh_i0_c13=+1.1232330464e-02f;
        // x^15 : -0xe.1b09dp-12f
        const float asinh_i0_c15=-3.4437545110e-03f;
        static const float ci[]={
            asinh_i0_c15,
            asinh_i0_c13, asinh_i0_c11, asinh_i0_c9,
            asinh_i0_c7, asinh_i0_c5, asinh_i0_c3
        };
        vf_type xx=x*x;
        static_assert(asinh_i0_c1==1.0, "asinh_i0_c1 must be 1.0");
        vf_type p=horner2(xx, vf_type(xx*xx), ci)*xx;
        vf_type ys=x+p*x;
        y = _T::sel(sel, ys, y);
    }
    if (any_of(sel = (x> asinh_i1_left) & (x<=asinh_i1_right))) {
        // [0.707106769084930419921875, 3] : | p - f | <= 2^-32.671875
        // coefficients for asinh_i1 generated by sollya
        // x^0 h: +0x9.e8325p-3f
        const float asinh_i1_c0h=+1.2383772135e+00f;
        // x^0 l: +0xc.1ed42p-28f
        const float asinh_i1_c0l=+4.5152098949e-08f;
        // x^1 : +0x8.8e742p-4f
        const float asinh_i1_c1=+5.3477871418e-01f;
        // x^2 : -0xf.77528p-7f
        const float asinh_i1_c2=-1.2082892656e-01f;
        // x^3 : +0xe.e793bp-9f
        const float asinh_i1_c3=+2.9110541567e-02f;
        // x^4 : -0xa.15eccp-11f
        const float asinh_i1_c4=-4.9246307462e-03f;
        // x^5 : -0xa.556a7p-14f
        const float asinh_i1_c5=-6.3071626937e-04f;
        // x^6 : +0x9.a7641p-13f
        const float asinh_i1_c6=+1.1784509989e-03f;
        // x^7 : -0xb.f56d9p-14f
        const float asinh_i1_c7=-7.2990130866e-04f;
        // x^8 : +0xa.7a9f1p-15f
        const float asinh_i1_c8=+3.1979338382e-04f;
        // x^9 : -0xc.e08b6p-17f
        const float asinh_i1_c9=-9.8244679975e-05f;
        // x^10 : +0xa.6279cp-20f
        const float asinh_i1_c10=+9.9035933090e-06f;
        // x^11 : +0xd.7e68fp-20f
        const float asinh_i1_c11=+1.2868679732e-05f;
        // x^12 : -0xc.daf99p-20f
        const float asinh_i1_c12=-1.2259836694e-05f;
        // x^13 : +0xd.ff83p-21f
        const float asinh_i1_c13=+6.6748107201e-06f;
        // x^14 : -0x9.4b8cap-22f
        const float asinh_i1_c14=-2.2161279958e-06f;
        // x^15 : +0xb.1a90ap-25f
        const float asinh_i1_c15=+3.3091811247e-07f;
        // x^ : +0xc.a4p-3f
        const float asinh_i1_x0=+1.5800781250e+00f;
        static const float c[]={
            asinh_i1_c15, asinh_i1_c14,
            asinh_i1_c13, asinh_i1_c12, asinh_i1_c11, asinh_i1_c10,
            asinh_i1_c9, asinh_i1_c8, asinh_i1_c7, asinh_i1_c6,
            asinh_i1_c5, asinh_i1_c4, asinh_i1_c3,
            asinh_i1_c2
        };
        vf_type x_i1 = x - asinh_i1_x0;
        vf_type y_i1 = horner2(x_i1, vf_type(x_i1*x_i1), c);
        vf_type ye;
        horner_comp_quick(y_i1, ye, x_i1, y_i1,
                          asinh_i1_c1,
                          asinh_i1_c0h);
        y_i1 += vf_type(ye+asinh_i1_c0l);
        y = _T::sel(sel, y_i1, y);
    }
    if (any_of(sel = x > asinh_i1_right)) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vmf_type x_huge = x > 0x1p24f;
        vf_type add_2_log=_T::sel_val_or_zero(x_huge, ctbl::m_ln2[0]);
        vf_type t= x*x;
        vf_type log_arg=_T::sel(x_huge,
                                x,
                                2.0f * x+ 1.0f/(sqrt(vf_type(t+1.0f))+x));
        vf_type yl= __log_k<log_func::c_log_e>(log_arg);
        yl += add_2_log;
        y = _T::sel(sel, yl, y);
    }
    // |x| < 2.0
    // vf_type log1p_arg= x+t/(1.0+sqrt(vf_type(1.0+t)));
    // vf_type ys= log1p_k(log1p_arg);
    y = copysign(y, xc);
    return y;
#else
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vmf_type x_gt_0x1p12 = x > 0x1p12;
    vf_type add_2_log=_T::sel_val_or_zero(x_gt_0x1p12, ctbl::m_ln2[0]);
    vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p12,
                            x,
                            2.0f * x+ 1.0f/(sqrt(vf_type(t+1.0f))+x));
    vf_type yl= __log_k<log_func::c_log_e>(log_arg);
    yl += add_2_log;
    // |x| < 2.0
    vf_type log1p_arg= x+t/(1.0f+sqrt(vf_type(1.0f+t)));
    vf_type ys= log1p_k(log1p_arg);

    // [3.4694469519536141888238489627838134765625e-18, 0.707106769084930419921875] : | p - f | <= 2^-31.4921875
    // coefficients for asinh generated by sollya
    // x^0 : +0x8p-3f
    const float asinh_c0=+1.0000000000e+00f;
    // x^2 : -0xa.aaaa7p-6f
    const float asinh_c2=-1.6666661203e-01f;
    // x^4 : +0x9.9981ap-7f
    const float asinh_c4=+7.4997141957e-02f;
    // x^6 : -0xb.6a588p-8f
    const float asinh_c6=-4.4591456652e-02f;
    // x^8 : +0xf.538eap-9f
    const float asinh_c8=+2.9934365302e-02f;
    // x^10 : -0xa.597cap-9f
    const float asinh_c10=-2.0213980228e-02f;
    // x^12 : +0xb.807cfp-10f
    const float asinh_c12=+1.1232330464e-02f;
    // x^14 : -0xe.1b09dp-12f
    const float asinh_c14=-3.4437545110e-03f;

    static const float ci[]={
        asinh_c14,
        asinh_c12,
        asinh_c10,
        asinh_c8,
        asinh_c6,
        asinh_c4,
    };
    vf_type yss= horner2(t, vf_type(t*t), ci);
    yss = x*horner(t, yss, asinh_c2, asinh_c0);
    ys = _T::sel(x<= M_SQRT2*0.5f, yss, ys);

    vf_type ash=_T::sel(x <= 2.0f, ys, yl);
    ash = copysign(ash, xc);
    return ash;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
acosh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
#if 1
    vf_type y=0.0f;
    vmf_type sel;
    const float acosh_i1_left=+2.0000000000e+00f;
    const float acosh_i1_right=+3.5000000000e+00f;
    if (any_of(sel = x <= acosh_i1_left)) {
        vf_type xm1h, xm1l;
        d_ops::add12(xm1h, xm1l, x, -1.0f);
        vf_type sqrt2xm1h, sqrt2xm1l;
        d_ops::sqrt2(sqrt2xm1h, sqrt2xm1l, 2.0f*xm1h, 2.0f*xm1l);
        // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]

        // [9.31322574615478515625e-10, 1] : | p - f | <= 2^-31.4921875
        // coefficients for acosh_i0 generated by sollya
        // x^0 : +0x8p-3f
        const float acosh_i0_c0=+1.0000000000e+00f;
        // x^1 : -0xa.aaaa7p-7f
        const float acosh_i0_c1=-8.3333306015e-02f;
        // x^2 : +0x9.9981ap-9f
        const float acosh_i0_c2=+1.8749285489e-02f;
        // x^3 : -0xb.6a588p-11f
        const float acosh_i0_c3=-5.5739320815e-03f;
        // x^4 : +0xf.538eap-13f
        const float acosh_i0_c4=+1.8708978314e-03f;
        // x^5 : -0xa.597cap-14f
        const float acosh_i0_c5=-6.3168688212e-04f;
        // x^6 : +0xb.807cfp-16f
        const float acosh_i0_c6=+1.7550516350e-04f;
        // x^7 : -0xe.1b09dp-19f
        const float acosh_i0_c7=-2.6904332117e-05f;
        static const float ci[]={
            acosh_i0_c7, acosh_i0_c6, acosh_i0_c5,
            acosh_i0_c4, acosh_i0_c3, acosh_i0_c2, acosh_i0_c1
        };
        vf_type ys=horner2(xm1h, vf_type(xm1h*xm1h), ci);
        vf_type ysl;
        horner_comp_quick(ys, ysl, xm1h, ys, acosh_i0_c0);
        vf_type t;
        d_ops::mul22(ys, t, ys, ysl, sqrt2xm1h, sqrt2xm1l);
        y= _T::sel(sel, ys, y);
    }
    if (any_of(sel= (x > acosh_i1_left) & (x<=acosh_i1_right))) {
        // [2, 3.5] : | p - f | <= 2^-28.4140625
        // coefficients for acosh_i1 generated by sollya
        // x^0 h: +0xc.f8a2dp-3f
        const float acosh_i1_c0h=+1.6214042902e+00f;
        // x^0 l: +0xa.cadafp-28f
        const float acosh_i1_c0l=+4.0204835017e-08f;
        // x^1 : +0xd.29695p-5f
        const float acosh_i1_c1=+4.1130509973e-01f;
        // x^2 : -0xb.b4feep-7f
        const float acosh_i1_c2=-9.1461047530e-02f;
        // x^3 : +0xe.e36ccp-9f
        const float acosh_i1_c3=+2.9078863561e-02f;
        // x^4 : -0xb.46dcbp-10f
        const float acosh_i1_c4=-1.1012504809e-02f;
        // x^5 : +0x9.841bfp-11f
        const float acosh_i1_c5=+4.6465094201e-03f;
        // x^6 : -0x8.82a3p-12f
        const float acosh_i1_c6=-2.0777098835e-03f;
        // x^7 : +0xf.d8561p-14f
        const float acosh_i1_c7=+9.6710590879e-04f;
        // x^8 : -0x8.fdab8p-14f
        const float acosh_i1_c8=-5.4876087233e-04f;
        // x^9 : +0xb.1cf4dp-15f
        const float acosh_i1_c9=+3.3914521919e-04f;
        // x^10 : -0xe.a7d25p-17f
        const float acosh_i1_c10=-1.1181299487e-04f;
        // x^ : +0xa.84p-2f
        const float acosh_i1_x0=+2.6289062500e+00f;
        static const float c[]={
            acosh_i1_c10, acosh_i1_c9, acosh_i1_c8, acosh_i1_c7,
            acosh_i1_c6, acosh_i1_c5, acosh_i1_c4, acosh_i1_c3,
            acosh_i1_c2, acosh_i1_c1
        };
        vf_type x_i1 = x - acosh_i1_x0;
        vf_type y_i1 = horner2(x_i1, vf_type(x_i1*x_i1), c);
        vf_type ye;
        horner_comp_quick(y_i1, ye, x_i1, y_i1, acosh_i1_c0h);
        y_i1 += vf_type(ye+acosh_i1_c0l);
        y = _T::sel(sel, y_i1, y);
    }
    if (any_of(sel = x > acosh_i1_right)) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vmf_type x_huge = x > 0x1p24f;
        vf_type add_2_log=_T::sel_val_or_zero(x_huge, ctbl::m_ln2[0]);
        // vf_type t= x*x;
        vf_type log_arg=_T::sel(x_huge,
                                x,
                                2.0f*x - 1.0f/(x+sqrt(vf_type(x*x-1.0f))));
        vf_type yl= __log_k<log_func::c_log_e>(log_arg);
        yl += add_2_log;
        y= _T::sel(sel, yl, y);
    }
    return y;
#else
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vmf_type x_gt_0x1p12 = x > 0x1p12;
    vf_type add_2_log=_T::sel_val_or_zero(x_gt_0x1p12, ctbl::m_ln2[0]);
    // vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p12,
                            x,
                            2.0f*x - 1.0f/(x+sqrt(vf_type(x*x-1.0f))));
    vf_type yl= __log_k<log_func::c_log_e>(log_arg);
    yl += add_2_log;

    vf_type xm1l;
    vf_type xm1=d_ops::two_diff(x, vf_type(1), xm1l);
    dvf_type sqrt2xm1=sqrt(mul_pwr2(dvf_type(xm1, xm1l), vf_type(2)));
    // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]
    // [3.4694469519536141888238489627838134765625e-18, 1] : | p - f | <= 2^-33.984375
    // coefficients for acosh generated by sollya
    // x^0 : +0x8p-3f
    const float acosh_c0=+1.0000000000e+00f;
    // x^1 : -0xa.aaaaap-7f
    const float acosh_c1=-8.3333328366e-02f;
    // x^2 : +0x9.9995p-9f
    const float acosh_c2=+1.8749862909e-02f;
    // x^3 : -0xb.6cfaap-11f
    const float acosh_c3=-5.5789547041e-03f;
    // x^4 : +0xf.7ee77p-13f
    const float acosh_c4=+1.8915672554e-03f;
    // x^5 : -0xb.180dcp-14f
    const float acosh_c5=-6.7712157033e-04f;
    // x^6 : +0xf.188dp-16f
    const float acosh_c6=+2.3034517653e-04f;
    // x^7 : -0x8.051ffp-17f
    const float acosh_c7=-6.1187885876e-05f;
    // x^8 : +0x9.191f4p-20f
    const float acosh_c8=+8.6766558525e-06f;

    static const float ci[]={
        acosh_c8,
        acosh_c7,
        acosh_c6,
        acosh_c5,
        acosh_c4,
        acosh_c3,
        acosh_c2,
        acosh_c1,
        acosh_c0
    };
    vf_type ys=horner2(xm1, vf_type(xm1*xm1), ci);
    ys= (sqrt2xm1 * ys)[0];
    vf_type y= _T::sel(x < 2.0f, ys, yl);
    return y;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atanh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
#if 1
    vf_type y=0.0;
    vmf_type sel;
    const float atanh_i1_left=+5.0000000000e-01f;
    if (any_of(sel= x <= atanh_i1_left)) {
        // [0, 0.5] : | p - f | <= 2^-30.328125
        // coefficients for atanh_i0 generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float atanh_i0_c1=+1.0000000000e+00f;
        // x^3 : +0xa.aaa9fp-5f
        const float atanh_i0_c3=+3.3333298564e-01f;
        // x^5 : +0xc.cd394p-6f
        const float atanh_i0_c5=+2.0002585649e-01f;
        // x^7 : +0x9.1a158p-6f
        const float atanh_i0_c7=+1.4221704006e-01f;
        // x^9 : +0xf.24e21p-7f
        const float atanh_i0_c9=+1.1831308156e-01f;
        // x^11 : +0xd.15382p-8f
        const float atanh_i0_c11=+5.1105029881e-02f;
        // x^13 : +0xb.54293p-6f
        const float atanh_i0_c13=+1.7701177299e-01f;
        static const double c[]={
            atanh_i0_c13,
            atanh_i0_c11, atanh_i0_c9,  atanh_i0_c7,
            atanh_i0_c5, atanh_i0_c3
        };
        vf_type xx=x*x;
        static_assert(atanh_i0_c1==1.0f, "atanh_i0_c1 must be 1.0");
        vf_type p=horner2(xx, vf_type(xx*xx), c)*xx;
        vf_type ys=x+p*x;
        y = _T::sel(sel, ys, y);
    }
    if (any_of(sel = (x>atanh_i1_left) & (x<=0.75))) {
        // [0.5, 0.75] : | p - f | <= 2^-28.375
        // coefficients for atanh_i1 generated by sollya
        // x^0 h: +0xc.2c9c3p-4f
        const float atanh_i1_c0h=+7.6089113951e-01f;
        // x^0 l: +0x8.122cp-31f
        const float atanh_i1_c0l=+3.7583447465e-09f;
        // x^1 : +0xd.98efap-3f
        const float atanh_i1_c1=+1.6996757984e+00f;
        // x^2 : +0xe.d401fp-3f
        const float atanh_i1_c2=+1.8535193205e+00f;
        // x^3 : +0xe.a2p-2f
        const float atanh_i1_c3=+3.6582031250e+00f;
        // x^4 : +0xf.1f06cp-1f
        const float atanh_i1_c4=+7.5605983734e+00f;
        // x^5 : +0x8.6f797p+1f
        const float atanh_i1_c5=+1.6870893478e+01f;
        // x^6 : +0x9.b87c7p+2f
        const float atanh_i1_c6=+3.8882595062e+01f;
        // x^7 : +0xc.51332p+3f
        const float atanh_i1_c7=+9.8537490845e+01f;
        // x^8 : +0x8.8d5fcp+5f
        const float atanh_i1_c8=+2.7367175293e+02f;
        // x^9 : +0xf.10c64p+5f
        const float atanh_i1_c9=+4.8209680176e+02f;
        // x^ : +0x8p-4f
        // x^ : +0xa.44p-4f
        const float atanh_i1_x0=+6.4160156250e-01f;
        static const double c[]={
            atanh_i1_c9, atanh_i1_c8, atanh_i1_c7, atanh_i1_c6,
            atanh_i1_c5, atanh_i1_c4, atanh_i1_c3, atanh_i1_c2,
            atanh_i1_c1
        };
        vf_type x_i1 = x - atanh_i1_x0;
        vf_type y_i1 = horner2(x_i1, vf_type(x_i1*x_i1), c);
        vf_type ye;
        horner_comp_quick(y_i1, ye, x_i1, y_i1, atanh_i1_c0h);
        y_i1 += vf_type(ye+atanh_i1_c0l);
        y = _T::sel(sel, y_i1, y);
    }
    if (any_of(sel = x>0.75f)) {
        vf_type log1p_arg= 2.0f*(x/(1.0f-x));
        vf_type yl= 0.5f*log1p_k(log1p_arg);
        y = _T::sel(sel, yl, y);
    }
    y = copysign(y, xc);
    return y;
#else
    // atanh(x) = x + 1/3*x^3 + 1/5*x^5
    //          = x + x^3/(3+x^2*Q)
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-24.3203125
    // coefficients for atanh generated by sollya
    // x^0 : -0xe.66666p-3f
    const float atanh_c0=-1.7999999523e+00f;
    // x^2 : -0xd.2a823p-6f
    const float atanh_c2=-2.0571951568e-01f;
    // x^4 : -0xd.6ffe8p-7f
    const float atanh_c4=-1.0498028994e-01f;
    // x^6 : -0x8.d7333p-7f
    const float atanh_c6=-6.9067381322e-02f;
    // x^8 : -0x8.cc5a3p-8f
    const float atanh_c8=-3.4368168563e-02f;
    // x^10 : -0x9.52b03p-7f
    const float atanh_c10=-7.2835944593e-02f;
    // x^12 : -0xc.30ebcp-13f
    const float atanh_c12=-1.4881710522e-03f;
    vf_type xx=x*x;
    static const float ci[]={
        atanh_c12,
        atanh_c10,
        atanh_c8,
        atanh_c6,
        atanh_c4,
        atanh_c2,
        atanh_c0
    };
    vf_type Q = horner2(xx, vf_type(xx*xx), ci);
    vf_type ys= x + x*xx/(3.0f + xx * Q);
    vf_type log1p_arg= 2.0f*(x/(1.0f-x));
    vf_type yl= 0.5f*log1p_k(log1p_arg);
    vf_type y=_T::sel(x<=0.5f, ys, yl);
    y = copysign(y, xc);
    return y;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
hypot_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type xa=abs(x);
    vf_type ya=abs(y);
    vf_type ma=max(xa, ya);
    vf_type mi=min(xa, ya);

    vf_type scale=1.0f;
    vf_type factor=1.0f;
    // avoid underflows
    vmf_type ma_small= ma < 0x1p-60f;
    scale = _T::sel(ma_small, 0x1p-70f, scale);
    factor= _T::sel(ma_small, 0x1p70f, factor);
    // avoid overflows
    vmf_type ma_large= ma > 0x1p60f;
    scale = _T::sel(ma_large, 0x1p70f, scale);
    factor= _T::sel(ma_large, 0x1p-70f, factor);
    ma *= factor;
    mi *= factor;

    vf_type smah, smal;
    d_ops::sqr12(smah, smal, ma);
    vf_type smih, smil;
    d_ops::sqr12(smih, smil, mi);
    vf_type sh, sl;
    d_ops::add22(sh, sl, smah, smal, smih, smil);
    vf_type r;
    d_ops::sqrt21(r, sh, sl);
    r *= scale;
    return r;
}


// Local Variables:
// mode: c++
// end:
#endif
