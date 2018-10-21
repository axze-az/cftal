//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_ELEM_FUNC_CORE_F64_H__)
#define __CFTAL_MATH_ELEM_FUNC_CORE_F64_H__ 1

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
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/misc.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_estrin.h>
#include <cftal/math/impl_d_real_constants_f64.h>
#include <cftal/mem.h>

// #include <iostream>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for double and different
        // traits
        template <typename _T>
        struct elem_func_core<double, _T> {
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmli_type = typename _T::vmli_type;
            using vmi2_type = typename _T::vmi2_type;

            using dvf_type = d_real<vf_type>;

            using d_ops=cftal::impl::
                d_real_ops<vf_type, d_real_traits<vf_type>::fma>;

            using t_ops=cftal::impl::t_real_ops<vf_type>;


            enum result_prec {
                normal,
                high
            };

            static
            vf_type
            pow2i(arg_t<vi_type> vi);

            static
            vf_type
            ldexp_k(arg_t<vf_type> x, arg_t<vi2_type> e);

            static
            vf_type
            ldexp(arg_t<vf_type> x,
                  arg_t<vi_type> e);

            // nextafter without nan handling
            static
            vf_type
            nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc);

            // frexp_k without nan, inf, zero handling
            // the exponents are returned in the odd numbered
            // elements of the return value
            static
            vi2_type
            __frexp_k(vf_type& xr, arg_t<vf_type> x);

            // the exponents are returned in the odd numbered
            // elements of e
            static
            vf_type
            frexp_k(arg_t<vf_type> x, vi2_type* e);

            static
            vf_type
            frexp(arg_t<vf_type> x, vi_type* e);

            // the exponents are returned in the odd numbered
            // elements of e
            static
            vi2_type
            ilogbp1_k(arg_t<vf_type> x);

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);

            static
            vi_type
            ilogb(arg_t<vf_type> x);

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

            // calculates %e^x-1 if exp_m1 == true %e^x otherwise
            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            // calculates %e^(xh+xl) into eh and el
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

            template <log_func _F>
            static
            vf_type
            __log_k(arg_t<vf_type> x);

            static
            vf_type
            log_k(arg_t<vf_type> x);

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
            vi2_type
            __reduce_trig_arg(vf_type& __restrict xrh,
                              vf_type& __restrict xrl,
                              arg_t<vf_type> x);

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
                    arg_t<vi2_type> q);


            // core sine, cosine calculation
            static
            void
            __sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vi2_type> q,
                        vf_type* s, vf_type* c);
            // core sine, cosine calculation with higher precision
            static
            void
            __sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                        arg_t<vi2_type> q,
                        dvf_type* ps, dvf_type *pc);

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
            atan2_k(arg_t<vf_type> x, arg_t<vf_type> y);

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
            hypot_k(arg_t<vf_type> x, arg_t<vf_type> y);

        };

    } // end math
} // end cftal

template <typename _T>
inline
typename
cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
pow2i(arg_t<vi_type> vi)
{
    vi_type e(vi + vi_type(_T::bias()));
    vf_type r(_T::insert_exp(e));
    vmi_type mi;
    vmf_type mf;
    mi= (vi < vi_type(_T::e_min()));
    mf= _T::vmi_to_vmf(mi);
    r= _T::sel_zero_or_val(mf, r);
    mi= (vi > vi_type(_T::e_max()));
    mf= _T::vmi_to_vmf(mi);
    vf_type inf(_T::pinf());
    r= _T::sel(mf, vf_type(inf), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
ldexp_k(arg_t<vf_type> x, arg_t<vi2_type> n)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi2_type i_is_denom= _T::vmf_to_vmi2(is_denom);
    vi2_type eo= _T::sel_val_or_zero(i_is_denom, vi2_type(-54));
    // split mantissa
    vi2_type ml, mh;
    _T::extract_words(ml, mh, xs);
    vi2_type xe=((mh>>20) & _T::e_mask()) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi2_type nn= min(vi2_type(4096), max(n, vi2_type(-4096)));
    vi2_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0x7ff normal result
    //     re >= 0x7ff inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

    // clear exponent bits from mh
    mh &= vi2_type(~0x7ff00000);

    // high part of mantissa for normal results:
    vi2_type mhn= mh | ((re & vi2_type(_T::e_mask())) << 20);
    vf_type r= _T::combine_words(ml, mhn);

    // overflow handling
    vmi2_type i_is_inf = re > vi2_type(0x7fe);
    vmf_type f_is_inf = _T::vmi2_to_vmf(copy_odd_to_even(i_is_inf));
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi2_type i_is_near_z = copy_odd_to_even(vi2_type(re < vi2_type (1)));
    if (any_of(i_is_near_z)) {
        // create m*0x1.0p-1022
        vi2_type mhu= mh | vi2_type(1<<20);
        vf_type r_u= _T::combine_words(ml, mhu);
        // create a scaling factor, but avoid overflows
        vi2_type ue= max(vi2_type(re + (_T::bias()-1)), vi2_type(1));
        vf_type s_u= _T::insert_exp(ue);
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi2_to_vmf(i_is_near_z);
        r = _T::sel(f_is_near_z, r_u, r);
    }
    // handle special cases:
    r = _T::sel(isinf(x) | isnan(x) | (x==vf_type(0.0)),
                x, r);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    return ldexp_k(x, _T::vi_to_vi2(n));
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc)
{
    vli_type ux=_T::as_vli(xc);
    vli_type uy=_T::as_vli(yc);
    vli_type ax= ux & not_sign_f64_msk::v.s64();
    vli_type ay= uy & not_sign_f64_msk::v.s64();
    vli_type ux_inc= ux + 1;
    vli_type ux_dec= ux - 1;
    // decrement required if ax > ay or (ux^uy & sgn) != 0
    vmli_type opp_sgn=
        vli_type((ux^uy) & sign_f64_msk::v.s64()) != vli_type(0LL);
    vli_type r= _T::sel((ax > ay) | opp_sgn, ux_dec, ux_inc);
    vli_type r0= _T::sel(ay == 0, uy, (uy & sign_f64_msk::v.s64()) | 1LL);
    r = _T::sel(ax == 0, r0, r);
    r = _T::sel(ux == uy, uy, r);
    vf_type rf=_T::as_vf(r);
    return rf;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vi2_type
cftal::math::elem_func_core<double, _T>::
__frexp_k(vf_type& m, arg_t<vf_type> x)
{
    using fc = func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    vf_type xn=_T::sel(is_denom, x*0x1p54, x);
    vi2_type e=_T::sel_val_or_zero(_T::vmf_to_vmi2(is_denom), vi2_type(-54));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, xn);
    /* reduce x into [0.5, 1.0) */
    e +=  ((hx>>20) & _T::e_mask()) - (_T::bias()-1);
    hx = (hx&0x800fffff) | vi2_type(0x3fe00000);
    m = _T::combine_words(lx, hx);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
frexp_k(arg_t<vf_type> x, vi2_type* ve)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi2_type i_is_denom= _T::vmf_to_vmi2(is_denom);
    vi2_type eo= _T::sel_val_or_zero(i_is_denom, vi2_type(-54));
    // extract mantissa
    vi2_type lo_word, hi_word;
    _T::extract_words(lo_word, hi_word, xs);
    // exponent:
    vi2_type e=((hi_word >> 20) & _T::e_mask()) + eo;
    // insert exponent
    hi_word = (hi_word & vi2_type(0x800fffff)) | vi2_type(0x3fe00000);
    // combine low and high word
    vf_type frc(_T::combine_words(lo_word, hi_word));
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    frc = _T::sel(f_inz, x, frc);
    if (ve != nullptr) {
        // remove bias from e
        vmi2_type i_inz=_T::vmf_to_vmi2(f_inz);
        e -= vi2_type(_T::bias()-1);
        e= _T::sel_zero_or_val(i_inz, e);
        *ve= e;
    }
    return frc;
}


template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vi2_type e;
    vi2_type* pe = ve != nullptr ? &e : nullptr;
    vf_type r=frexp_k(x, pe);
    if (ve) {
        *ve=_T::vi2_odd_to_vi(e);
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vi2_type
cftal::math::elem_func_core<double, _T>::
ilogbp1_k(arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p54), xs);
    vmi2_type i_is_denom= _T::vmf_to_vmi2(is_denom);
    vi2_type eo= _T::sel_val_or_zero(i_is_denom, vi2_type(-54));
    // reinterpret as integer
    vi2_type hi_word, lo_word;
    _T::extract_words(lo_word, hi_word, xs);
    // exponent:
    vi2_type e=((hi_word >> 20) & _T::e_mask()) + eo - vi2_type(_T::bias()-1);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vi_type
cftal::math::elem_func_core<double, _T>::
ilogbp1(arg_t<vf_type> x)
{
    return _T::vi2_odd_to_vi(ilogbp1_k(x));
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vi_type
cftal::math::elem_func_core<double, _T>::
ilogb(arg_t<vf_type> d)
{
    vi2_type e(ilogbp1_k(d) - vi2_type(1));
    vmf_type mf= d == 0.0;
    vmi2_type mi= _T::vmf_to_vmi2(mf);
    e = _T::sel(mi, vi2_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi2(mf);
    e = _T::sel(mi, vi2_type(0x7fffffff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi2(mf);
    e = _T::sel(mi, vi2_type(FP_ILOGBNAN), e);
    return _T::vi2_odd_to_vi(e);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    vf_type y= vf_type(1.0/sqrt(x));
    // vf_type y= native_rsqrt(x);
    // y = y + 0.5* y * (vf_type(1) - d_ops::mul(x, y)*y)[0];
    vf_type yh, yl;
    d_ops::mul12(yh, yl, x, y);
    d_ops::mul122(yh, yl, y, yh, yl);
    d_ops::add122(yh, yl, -1.0, yh, yl);
    y = y + (-0.5*y)*yh;
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    // reduce x into [2^-3, 1.0)
    const int32_t shift_1_3 = 13;
    const int32_t fac_1_3 = ((1<<shift_1_3)+2)/3;

    vf_type xp=abs(xc);
    vf_type mm0;
    auto e=__frexp_k(mm0, xp);
    e=copy_odd_to_even(e);
    // do a division by 3
    // vi2_type e3 = (((e)*fac_1_3)>>shift_1_3) -(e>>31);
    // do a division by 3 rounded to - infinity
    const vi2_type v_bias_3(3*_T::bias()), v_bias(_T::bias());
    vi2_type e3_with_bias = (((e+v_bias_3)*fac_1_3)>>shift_1_3);
    vi2_type e3 =e3_with_bias - v_bias;
    // r is always in 0, 1, 2 because of the round down
    vi2_type r = e - e3 - (e3<<1);

    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 3
    // 1    0.25    -2           -2
    // 2    0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
    vmi2_type r_ne_z = r != 0;
    e3_with_bias=_T::sel(r_ne_z, e3_with_bias+1, e3_with_bias);
    // log_2(scale) = bias + (r-3) = bias - 3 + r
    const vi2_type v_bias_plus_3(_T::bias()-3);
    vf_type scale = _T::insert_exp(v_bias_plus_3 + r);
    vmf_type f_r_ne_z = _T::vmi2_to_vmf(r_ne_z);
    scale = _T::sel(f_r_ne_z, scale, 1.0);
    mm0 = mm0 * scale;
    // [0.125, 1] : | p - f | <= 2^-7.58203125
    // coefficients for cbrt generated by sollya
    // x^0 : +0xa.e82d45a6c55p-5
    const double cbrt_c0=+3.4084189990805136005747e-01;
    // x^1 : +0xb.aa37398d24be8p-3
    const double cbrt_c1=+1.4581131454657161317101e+00;
    // x^2 : -0xb.165ffaefafeap-3
    const double cbrt_c2=-1.3859252552410810110928e+00;
    // x^3 : +0x9.79975a0a1a7ap-4
    const double cbrt_c3=+5.9218535586992837593812e-01;
    vf_type mm = horner(mm0,
                        cbrt_c3,
                        cbrt_c2,
                        cbrt_c1,
                        cbrt_c0);
    // one step of order 3
    mm = impl::root3::order3<double>(mm, mm0);
    // round mm to 17 bits == int(53/3)
    mm = rint(vf_type(mm*0x1p17))*0x1p-17;
    mm = impl::root3::order5<double>(mm, mm0);
    // no denormal results are possible
    // vf_type t= _T::insert_exp(_T::bias()+e3c);
    vf_type t= _T::insert_exp(e3_with_bias);
    mm *=t;
    mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
root12_k(arg_t<vf_type> xc)
{
    // reduce x into [2^-12, 1.0)
    const int32_t shift_1_12= 0x11;
    const int32_t fac_1_12= 0x2aab;

    vf_type xp=abs(xc);
    vf_type mm0;
    auto e=__frexp_k(mm0, xp);
    e=copy_odd_to_even(e);
    // do a division by 12 rounded to - infinity
    const vi2_type v_bias_12(12*_T::bias()), v_bias(_T::bias());
    vi2_type e12_with_bias = (((e+v_bias_12)*fac_1_12)>>shift_1_12);
    vi2_type e12 =e12_with_bias - v_bias;
    // r is always in [0, 1, 11] because of the round down
    vi2_type r = e - e12 *12;

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
    vmi2_type r_ne_z = r != 0;
    e12_with_bias=_T::sel(r_ne_z, e12_with_bias+1, e12_with_bias);

    // log_2(scale) = bias + (r-12) = bias - 12 + r
    const vi2_type v_bias_plus_12(_T::bias()-12);
    vf_type scale = _T::insert_exp(v_bias_plus_12 + r);
    vmf_type f_r_ne_z = _T::vmi2_to_vmf(r_ne_z);
    scale = _T::sel(f_r_ne_z, scale, 1.0);
    mm0 = mm0 * scale;

    // [2.44140625e-4, 1.953125e-3] : | p - f | <= 2^-8.08984375
    // coefficients for root12_i0 generated by sollya
    // x^0 : +0xf.3c1f4011479p-5
    const double root12_i0_c0=+4.7608912003691905567848e-01;
    // x^1 : +0xe.bf4cf44871c7p+3
    const double root12_i0_c1=+1.1797814382695489143771e+02;
    // x^2 : -0xe.cb6420160acd8p+11
    const double root12_i0_c2=-3.0299128916760539141251e+04;
    // [1.953125e-3, 1.5625e-2] : | p - f | <= 2^-7.83984375
    // coefficients for root12_i1 generated by sollya
    // x^0 : +0x9.0f06c5f8c742p-4
    const double root12_i1_c0=+5.6616856892328870642928e-01;
    // x^1 : +0x8.c4cea29e557b8p+1
    const double root12_i1_c1=+1.7537556006728632240765e+01;
    // x^2 : -0x8.cbff08f4649ap+6
    const double root12_i1_c2=-5.6299905759681723793619e+02;
    // [1.5625e-2, 0.125] : | p - f | <= 2^-7.58984375
    // coefficients for root12_i2 generated by sollya
    // x^0 : +0xa.c5cd81f2ba9e8p-4
    const double root12_i2_c0=+6.7329169045448333807968e-01;
    // x^1 : +0xa.6d8a687f96ab8p-2
    const double root12_i2_c1=+2.6069732978700517200821e+00;
    // x^2 : -0xa.761706511613p+0
    const double root12_i2_c2=-1.0461288828655664673306e+01;
    // [0.125, 1] : | p - f | <= 2^-7.33984375
    // coefficients for root12_i3 generated by sollya
    // x^0 : +0xc.cf99425c810bp-4
    const double root12_i3_c0=+8.0068326876068129926978e-01;
    // x^1 : +0xc.66a30198caf7p-5
    const double root12_i3_c1=+3.8752889930614642377549e-01;
    // x^2 : -0xc.70cdb97a7ca1p-6
    const double root12_i3_c2=-1.9438498604899662192125e-01;
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
    vf_type mm_a= _T::sel(mm0 < 0x1p-9, mm_i0, mm_i1);
    vf_type mm_b= _T::sel(mm0 < 0x1p-3, mm_i2, mm_i3);
    vf_type mm= _T::sel(mm0 < 0x1p-6, mm_a, mm_b);

    // only one division and much parallelism
    mm = impl::root12::householder8<double>(mm, mm0);

    vf_type t= _T::insert_exp(e12_with_bias);
    mm *=t;
    // mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::scale_result
cftal::math::elem_func_core<double, _T>::
__scale_exp_k(arg_t<vf_type> k)
{
    vi_type ki= _T::cvt_f_to_i(k);
    vi_type kia= ki>>1;
    vi_type kib= ki - kia;
    vf_type rh= _T::insert_exp(_T::bias()+kia);
    vf_type rl= _T::insert_exp(_T::bias()+kib);
    return scale_result(rh, rl);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__scale_exp_k(arg_t<vf_type> ym, arg_t<vf_type> k)
{
    auto sc=__scale_exp_k(k);
    vf_type ys = (ym * sc.f0()) * sc.f1();
    return ys;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::dvf_type
cftal::math::elem_func_core<double, _T>::
__scale_exp_k(arg_t<vf_type> yh, arg_t<vf_type> yl, arg_t<vf_type> k)
{
    auto sc = __scale_exp_k(k);
    vf_type ysh = (yh * sc.f0()) * sc.f1();
    vf_type ysl = (yl * sc.f0()) * sc.f1();
    return dvf_type(ysh, ysl);
}

template <typename _T>
template <bool _EXP_M1>
__attribute__((always_inline))
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
        arg_t<vf_type> kf)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    const double exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    // const double exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const double exp_c2=+5.0000000000000000000000e-01;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const double exp_c3=+1.6666666666666665741481e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const double exp_c4=+4.1666666666666685170384e-02;
    // x^5 : +0x8.888888888961p-10
    const double exp_c5=+8.3333333333340843529502e-03;
    // x^6 : +0xb.60b60b60a81p-13
    const double exp_c6=+1.3888888888873365812238e-03;
    // x^7 : +0xd.00d00cfa88cc8p-16
    const double exp_c7=+1.9841269839039331096715e-04;
    // x^8 : +0xd.00d00d6b5b978p-19
    const double exp_c8=+2.4801587348902822885563e-05;
    // x^9 : +0xb.8ef1e87f81768p-22
    const double exp_c9=+2.7557322326013774747291e-06;
    // x^10 : +0x9.3f26623e02258p-25
    const double exp_c10=+2.7557252167692825528943e-07;
    // x^11 : +0xd.72da4d99dd1ep-29
    const double exp_c11=+2.5050050656120229688701e-08;
    // x^12 : +0x8.fc5bcb2f9dd7p-32
    const double exp_c12=+2.0921639307947297714762e-09;
    // x^13 : +0xb.675e3aadcbc88p-36
    const double exp_c13=+1.6594686274338619941159e-10;
    vf_type x2=xrh*xrh;

    static const double c[]={
        exp_c13, exp_c12, exp_c11, exp_c10, exp_c9,
        exp_c8, exp_c7, exp_c6, exp_c5, exp_c4,
        exp_c3, exp_c2
    };
    vf_type y=horner2(xrh, x2, c);
    y = y * x2;
    vf_type ye;
    d_ops::add12(y, ye, xrh, y);
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
        vf_type scale = __scale_exp_k(vf_type(0.5), kf);
        // e^x-1 = 2*(y * 2^s - 0.5)
        y  *= scale;
        vf_type t;
        d_ops::add12cond(y, t, -0.5, y);
        ye = 2.0 * (ye * scale + t);
        y = 2.0*y + ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel((abs(xrh) < 0x1p-54) & (kf==0.0), xrh, y);
    }
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__))
void
cftal::math::elem_func_core<double, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    kf = rint(vf_type(x * ctbl::m_1_ln2[0]));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    xrh = hi - kf * ctbl::m_ln2_cw[1];
    vf_type dx = hi-xrh;
    xrl = dx - kf * ctbl::m_ln2_cw[1];
}

template <typename _T>
inline
void
cftal::math::elem_func_core<double, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> xh,
                 arg_t<vf_type> xl)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    kf = rint(vf_type(xh * ctbl::m_1_ln2[0]));
    vf_type neg_kfln2h, neg_kfln2l;
    d_ops::mul122(neg_kfln2h, neg_kfln2l,
                  kf, -ctbl::m_ln2[0], -ctbl::m_ln2[1]);
    d_ops::add22cond(xrh, xrl,
                     xh, xl,
                     neg_kfln2h, neg_kfln2l);
}

template <typename _T>
template <bool _EXP_M1>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
exp_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, xc);
    vf_type y=__exp_k<_EXP_M1>(xrh, xrl, kf);
    return y;
}


template <typename _T>
void
cftal::math::elem_func_core<double, _T>::
exp_k2(vf_type& eh, vf_type& el,
       arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, xh, xl);
    eh= __pow_exp_k(xrh, xrl, kf, &el);
}


template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
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
    __reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
    using fc_t = math::func_constants<double>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
exp_px2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
    using fc_t = math::func_constants<double>;
    y= _T::sel(x2h >= fc_t::exp_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type kf= rint(vf_type(x));
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type xr = x - kf;
    vf_type xrh, xrl;
    // for exp2 mul12 would be sufficient
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type y=__exp_k<_EXP2_M1>(xrh, xrl, kf);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
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
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, vf_type(-kf), x2h, x2l);
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
    using fc_t = math::func_constants<double>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp2_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
exp2_px2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);
    vf_type kf = rint(vf_type(x2h));
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, -kf, x2h, x2l);
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    d_ops::mul22(xrh, xrl, xrh, xrl, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type y= __exp_k<false>(xrh, xrl, kf);
    using fc_t = math::func_constants<double>;
    y= _T::sel(x2h >= fc_t::exp2_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
exp10_k(arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
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
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
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
    using ctbl = impl::d_real_constants<d_real<double>, double>;
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
    using fc_t = math::func_constants<double>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp10_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
exp10_px2_k(arg_t<vf_type> xc)
{
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);

    using ctbl = impl::d_real_constants<d_real<double>, double>;
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
    using fc_t = math::func_constants<double>;
    y= _T::sel(x2h >= fc_t::exp10_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <enum cftal::math::elem_func_core<double, _T>::hyperbolic_func _F>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
hyperbolic_k(arg_t<vf_type> xc)
{
    vf_type x= abs(xc);
    vf_type xrh, xrl, kf;
    __reduce_exp_arg(xrh, xrl, kf, x);
    vf_type scale=_T::sel(kf >= 1024, 2.0, 1.0);
    vi_type knh= _T::cvt_f_to_i(kf);
    vi2_type kn=_T::vi_to_vi2(knh);
    kn= _T::sel(kn>= 1024, kn-1, kn);

    // filter out large arguments for tanh
    vmf_type kf_le_35 = kf <= 35.0;
    bool any_of_kf_le_35 = any_of(kf_le_35);
    if (_F == hyperbolic_func::c_tanh) {
        if (unlikely(!any_of_kf_le_35)) {
            vf_type tanh_x = copysign(vf_type(1.0), xc);
            return tanh_x;
        }
    }
    // calculate 2^(k-1)
    vf_type two_pow_plus_k_minus_1 = _T::insert_exp((_T::bias()-1) + kn);
    // calculate sinh + cosh
    // [0, 0.3465735912322998046875] : | p - f | <= 2^-68.1875
    // coefficients for sinh generated by sollya
    // x^1 : +0x8p-3
    // const double sinh_c1=+1.0000000000000000000000e+00;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const double sinh_c3=+1.6666666666666665741481e-01;
    // x^5 : +0x8.888888888987p-10
    const double sinh_c5=+8.3333333333342161919344e-03;
    // x^7 : +0xd.00d00cf88266p-16
    const double sinh_c7=+1.9841269838319906034657e-04;
    // x^9 : +0xb.8ef1f23c3658p-22
    const double sinh_c9=+2.7557323709743886271627e-06;
    // x^11 : +0xd.72b2a27c563b8p-29
    const double sinh_c11=+2.5048923211833473960268e-08;
    // x^13 : +0xb.a1b17ee8523e8p-36
    const double sinh_c13=+1.6926226991841124453737e-10;

    // [0, 0.3465735912322998046875] : | p - f | <= 2^-69.96875
    // coefficients for cosh generated by sollya
    // x^0 : +0x8p-3
    const double cosh_c0=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const double cosh_c2=+5.0000000000000000000000e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const double cosh_c4=+4.1666666666666685170384e-02;
    // x^6 : +0xb.60b60b60a809p-13
    const double cosh_c6=+1.3888888888873335454577e-03;
    // x^8 : +0xd.00d00d6b984fp-19
    const double cosh_c8=+2.4801587349008149738488e-05;
    // x^10 : +0x9.3f26619515b2p-25
    const double cosh_c10=+2.7557252050478505757717e-07;
    // x^12 : +0x8.fc5cfb218889p-32
    const double cosh_c12=+2.0921681488787703832704e-09;

    vf_type xx= xrh*xrh;

    static const double cs[]= {
        sinh_c13,
        sinh_c11,
        sinh_c9,
        sinh_c7,
        sinh_c5,
        sinh_c3
    };
    static const double cc[]= {
        cosh_c12,
        cosh_c10,
        cosh_c8,
        cosh_c6,
        cosh_c4,
        cosh_c2
    };
    vf_type rsh, rch;
    horner_n2(rsh, rch, xx, cs, cc);

    vf_type rsh_h, rsh_l;
    rsh *= (xx*xrh);
    d_ops::add12(rsh_h, rsh_l, xrh, rsh);
    // horner_comp_quick(rsh_h, rsh_l, xx, rsh, sinh_c1);
    // d_ops::mul122(rsh_h, rsh_l, xrh, rsh_h, rsh_l);

    vf_type rch_h, rch_l;
    rch *= xx;
    d_ops::add12(rch_h, rch_l, cosh_c0, rch);
    // horner_comp_quick(rch_h, rch_l, xx, rch, cosh_c0);

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
    if (likely(any_of_kf_le_35)) {
        // calculate 2^(-k-1)
        vf_type two_pow_minus_k_minus_1 = _T::insert_exp((_T::bias()-1) - kn);
        two_pow_minus_k_minus_1= _T::sel_val_or_zero(kf_le_35,
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
        sinh_x = _T::sel(x < 0x1p-26, x, sinh_x);
        sinh_x = copysign(sinh_x, xc);
        r = sinh_x;
    }
    if (_F == hyperbolic_func::c_cosh) {
        vf_type cosh_x = cosh_h*scale;
        r = cosh_x;
    }
    if (_F == hyperbolic_func::c_tanh) {
        vf_type qh, ql;
        d_ops::div22(qh, ql, sinh_h, sinh_l, cosh_h, cosh_l);
        vf_type tanh_x=_T::sel(kf_le_35, qh, 1.0);
        tanh_x = _T::sel(x < 0x1p-26, x, tanh_x);
        tanh_x = copysign(tanh_x, xc);
        r = tanh_x;
    }
    return r;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
sinh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_sinh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
cosh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_cosh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
tanh_k(arg_t<vf_type> x)
{
    return hyperbolic_k<hyperbolic_func::c_tanh>(x);
}

template <typename _T>
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
log_k_poly(arg_t<vf_type> z)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-64.625
    // coefficients for log generated by sollya
    // x^2 : +0xa.aaaaaaaaaaaa8p-4
    const double log_c2=+6.6666666666666662965923e-01;
    // x^4 : +0xc.ccccccccceac8p-5
    const double log_c4=+4.0000000000005325739849e-01;
    // x^6 : +0x9.24924921770b8p-5
    const double log_c6=+2.8571428569168361155661e-01;
    // x^8 : +0xe.38e392e2fd49p-6
    const double log_c8=+2.2222222656633455750708e-01;
    // x^10 : +0xb.a2e6dba5baafp-6
    const double log_c10=+1.8181773614825663676342e-01;
    // x^12 : +0x9.d90aca733a8d8p-6
    const double log_c12=+1.5387220163840073516859e-01;
    // x^14 : +0x8.7a5091423103p-6
    const double log_c14=+1.3246549783140454392694e-01;
    // x^16 : +0x8.811edd68c1cb8p-6
    const double log_c16=+1.3288089391701582431260e-01;

    vf_type w = z*z;

    static const double ct1[]={
        log_c14,
        log_c10,
        log_c6,
        log_c2
    };
    static const double ct2[]={
        log_c16,
        log_c12,
        log_c8,
        log_c4
    };
    vf_type t1, t2;
    horner_n2(t1, t2, w, ct1, ct2);
    t1 *= z;
    vf_type y = t2*w + t1;
    return y;
}


template <typename _T>
template <typename cftal::math::elem_func_core<double, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__log_k(arg_t<vf_type> xc)
{
/* origin: FreeBSD /usr/src/lib/msun/src/e_log.c */
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

    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel_val_or_zero(_T::vmf_to_vmi2(is_denom), vi2_type(-54));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - _T::bias();
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);

    vf_type f = xr - 1.0;
    vf_type hfsq = (0.5*f)*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;

    vf_type R = log_k_poly(z);
    vf_type res;
    if (_LFUNC == log_func::c_log_e) {
        using ctbl=impl::d_real_constants<d_real<double>, double>;
        vf_type log_x=s*(hfsq+R);
        log_x += kf*ctbl::m_ln2_cw[1];
        log_x -= hfsq;
        log_x += f;
        log_x += kf*ctbl::m_ln2_cw[0];
        res = log_x;
    } else if (_LFUNC == log_func::c_log_10) {
        const double
            ivln10hi  = 4.34294481878168880939e-01; /* 0x3fdbcb7b, 0x15200000 */
        const double
            ivln10lo  = 2.50829467116452752298e-11; /* 0x3dbb9438, 0xca9aadd5 */
        const double
            log10_2hi = 3.01029995663611771306e-01; /* 0x3FD34413, 0x509F6000 */
        const double
            log10_2lo = 3.69423907715893078616e-13; /* 0x3D59FEF3, 0x11F12B36 */

        vf_type t = f - hfsq;
        vf_type hi= _T::clear_low_word(t);
        vf_type lo= f - hi -hfsq + s * (hfsq + R);

        vf_type val_hi = hi * ivln10hi;
        vf_type y = kf* log10_2hi;
        vf_type val_lo = kf * log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;

        vf_type w= y + val_hi;
        val_lo += (y - w) + val_hi;
        val_hi = w;

        vf_type log10_x = val_lo + val_hi;
        res =log10_x;
    } else /* if (func == log_func::c_log_2)*/ {
        const double
            ivln2hi = 1.44269504072144627571e+00; /* 0x3ff71547, 0x65200000 */
        const double
            ivln2lo = 1.67517131648865118353e-10; /* 0x3de705fc, 0x2eefa200 */

        vf_type t= f - hfsq;
        vf_type hi= _T::clear_low_word(t);
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
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
log1p_k(arg_t<vf_type> xc)
{
    // return nlog_k<c_log1p_e>(xc);
/* double log1p(double x)
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
    vi2_type lu, hu;
    _T::extract_words(lu, hu, u);
    hu += (0x3ff00000 - 0x3fe6a09e);
    vi2_type k=(hu >> 20) - _T::bias();
    vf_type kf= _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0), 1.0-(u-x), x-(u-1.0));
    c_k_2 /= u;
    vf_type c = _T::sel_val_or_zero(kf < vf_type(54.0), c_k_2);
    /* reduce u into [sqrt(2)/2, sqrt(2)] */
    hu = (hu&0x000fffff) + 0x3fe6a09e;
    vf_type nu = _T::combine_words(lu, hu);
    vf_type f= nu -1.0;

    vf_type hfsq = (0.5*f)*f;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;
    vf_type R = log_k_poly(z);

    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type log1p_x= s*(hfsq+R);
    log1p_x += kf*ctbl::m_ln2_cw[1] +c;
    log1p_x -= hfsq;
    log1p_x += f;
    log1p_x += kf*ctbl::m_ln2_cw[0];
    log1p_x= _T::sel(abs(x) < 0x1p-53, x, log1p_x);
    return log1p_x;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
log_k(arg_t<vf_type> xc)
{
    // return __pow_log_k<log_func::c_log_e,
    //                   result_prec::high>(xc)[0];
    return __log_k<log_func::c_log_e>(xc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
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
    return __log_k<log_func::c_log_2>(xc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
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
    return __log_k<log_func::c_log_10>(xc);
}

template <typename _T>
__attribute__((always_inline))
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__pow_exp_poly_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                 vf_type* exl)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    const double exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    const double exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const double exp_c2=+5.0000000000000000000000e-01;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const double exp_c3=+1.6666666666666665741481e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const double exp_c4=+4.1666666666666685170384e-02;
    // x^5 : +0x8.888888888961p-10
    const double exp_c5=+8.3333333333340843529502e-03;
    // x^6 : +0xb.60b60b60a81p-13
    const double exp_c6=+1.3888888888873365812238e-03;
    // x^7 : +0xd.00d00cfa88cc8p-16
    const double exp_c7=+1.9841269839039331096715e-04;
    // x^8 : +0xd.00d00d6b5b978p-19
    const double exp_c8=+2.4801587348902822885563e-05;
    // x^9 : +0xb.8ef1e87f81768p-22
    const double exp_c9=+2.7557322326013774747291e-06;
    // x^10 : +0x9.3f26623e02258p-25
    const double exp_c10=+2.7557252167692825528943e-07;
    // x^11 : +0xd.72da4d99dd1ep-29
    const double exp_c11=+2.5050050656120229688701e-08;
    // x^12 : +0x8.fc5bcb2f9dd7p-32
    const double exp_c12=+2.0921639307947297714762e-09;
    // x^13 : +0xb.675e3aadcbc88p-36
    const double exp_c13=+1.6594686274338619941159e-10;
    vf_type xx=xrh*xrh;

    static const double c[]= {
        exp_c13, exp_c12, exp_c11, exp_c10, exp_c9,
        exp_c8, exp_c7, exp_c6, exp_c5, exp_c4,
        exp_c3
    };
    vf_type y=horner2(xrh, xx, c);
    vf_type ye;
    horner_comp_quick(y, ye, xrh, y, exp_c2, exp_c1);
    // calculate expm1/xrh for correction term
    vf_type yl=y+ye;
    horner_comp_quick_si(y, ye, xrh, y, ye, exp_c0);
    vf_type yee= xrl + xrl * xrh * yl;
    ye += yee;
    if (exl==nullptr) {
        y += ye;
    } else {
        d_ops::add12(y, ye, y, ye);
        *exl = ye;
    }
    return y;
}

template <typename _T>
__attribute__((always_inline))
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
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
template <typename cftal::math::elem_func_core<double, _T>::log_func _F,
          typename cftal::math::elem_func_core<double, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<double, _T>::dvf_type
cftal::math::elem_func_core<double, _T>::
__pow_log_k(arg_t<vf_type> sh, arg_t<vf_type> sl, arg_t<vf_type> kf)
{
    dvf_type ds(sh, sl);
    dvf_type ds2=sqr(ds);
    vf_type s2= ds2[0];
    using ctbl = impl::d_real_constants<d_real<double>, double>;

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
    vf_type s2l=ds2[1];
    if (_P == result_prec::high) {
        // [0, 0.17157287895679473876953125] : | p - f | <= 2^-89.8125
        // coefficients for pow_log_hp generated by sollya
        // x^1 : +0x8p-2
        const double pow_log_hp_c1=+2.0000000000000000000000e+00;
        // x^3 h: +0xa.aaaaaaaaaaaa8p-4
        const double pow_log_hp_c3h=+6.6666666666666662965923e-01;
        // x^3 l: +0xa.aaab32cf2c8fp-58
        const double pow_log_hp_c3l=+3.7007462307803146546515e-17;
        // x^5 h: +0xc.cccccccccccdp-5
        const double pow_log_hp_c5h=+4.0000000000000002220446e-01;
        // x^5 l: -0xc.d5332786ce15p-59
        const double pow_log_hp_c5l=-2.2261379899555494748737e-17;
        // x^7 : +0x9.2492492492498p-5
        const double pow_log_hp_c7=+2.8571428571428575393654e-01;
        // x^9 : +0xe.38e38e38e2978p-6
        const double pow_log_hp_c9=+2.2222222222220852638763e-01;
        // x^11 : +0xb.a2e8ba2f4c478p-6
        const double pow_log_hp_c11=+1.8181818182091943891798e-01;
        // x^13 : +0x9.d89d897a52f8p-6
        const double pow_log_hp_c13=+1.5384615350312413895040e-01;
        // x^15 : +0x8.8888a6af4ed2p-6
        const double pow_log_hp_c15=+1.3333336141407159392003e-01;
        // x^17 : +0xf.0f0245e25efep-7
        const double pow_log_hp_c17=+1.1764553463284949108569e-01;
        // x^19 : +0xd.7b0afd07597bp-7
        const double pow_log_hp_c19=+1.0531747202794491946598e-01;
        // x^21 : +0xc.08df9f2aa0e78p-7
        const double pow_log_hp_c21=+9.4020798414255354891189e-02;
        // x^23 : +0xd.1a5719e2afe2p-7
        const double pow_log_hp_c23=+1.0236634029331442841126e-01;

        static const double c[]={
            pow_log_hp_c23, pow_log_hp_c21,
            pow_log_hp_c19, pow_log_hp_c17,
            pow_log_hp_c15, pow_log_hp_c13,
            pow_log_hp_c11, pow_log_hp_c9
        };
        vf_type p=horner2(s2, s4, c);

        d_ops::mul122(ph, pl, p, s2, s2l);
        d_ops::add122(ph, pl, pow_log_hp_c7,ph, pl);
        d_ops::mul22(ph, pl, s2, s2l, ph, pl);
        d_ops::add22(ph, pl, pow_log_hp_c5h, pow_log_hp_c5l, ph, pl);
        d_ops::mul22(ph, pl, s2, s2l, ph, pl);
        d_ops::add22(ph, pl, pow_log_hp_c3h, pow_log_hp_c3l, ph, pl);
        d_ops::mul22(ph, pl, s2, s2l, ph, pl);
        d_ops::add122(ph, pl, pow_log_hp_c1, ph, pl);
    } else if (_P == result_prec::normal) {
        // [0, 0.17157287895679473876953125] : | p - f | <= 2^-70.84375
        // coefficients for pow_log generated by sollya
        // x^1 : +0x8p-2
        const double pow_log_c1=+2.0000000000000000000000e+00;
        // x^3 : +0xa.aaaaaaaaaaaa8p-4
        const double pow_log_c3=+6.6666666666666662965923e-01;
        // x^5 : +0xc.cccccccccde78p-5
        const double pow_log_c5=+4.0000000000003138600491e-01;
        // x^7 : +0x9.2492492337668p-5
        const double pow_log_c7=+2.8571428570442664041096e-01;
        // x^9 : +0xe.38e38fe69c078p-6
        const double pow_log_c9=+2.2222222378553666000123e-01;
        // x^11 : +0xb.a2e82369f50d8p-6
        const double pow_log_c11=+1.8181804140461185759214e-01;
        // x^13 : +0x9.d8bcabeda57cp-6
        const double pow_log_c13=+1.5385357656358400468832e-01;
        // x^15 : +0x8.84d39be12c3ap-6
        const double pow_log_c15=+1.3310709211936322393655e-01;
        // x^17 : +0xf.83603792c34dp-7
        const double pow_log_c17=+1.2119677270450282535741e-01;
        // x^19 : +0xb.333e5bd067258p-7
        const double pow_log_c19=+8.7501330214586989231229e-02;

        static const double c[]= {
            pow_log_c19, pow_log_c17,
            pow_log_c15, pow_log_c13,
            pow_log_c11, pow_log_c9,
            pow_log_c7, pow_log_c5
        };
        vf_type p= horner2(s2, s4, c);
        p= s2* p;
        d_ops::add12(ph, pl, pow_log_c3, p);
        d_ops::mul22(ph, pl, s2, s2l, ph, pl);
        d_ops::add122(ph, pl, pow_log_c1, ph, pl);
        // this does not work :-(
        // horner_comp_quick(ph, pl, s2, p, pow_log_c3, pow_log_c1);
    }
    if (_F == log_func::c_log_e) {
        d_ops::mul22(ph, pl, ds[0], ds[1], ph, pl);
        d_ops::add22cond(ph, pl, th, tl, ph, pl);
    } else if (_F == log_func::c_log_2) {
        d_ops::mul22(ph, pl, th, tl, ph, pl);
        d_ops::add122cond(ph, pl, kf, ph, pl);
    } else if (_F == log_func::c_log_10) {
        vf_type kfh, kfl;
        d_ops::mul122(kfh, kfl, kf, ctbl::m_lg2[0], ctbl::m_lg2[1]);
        d_ops::mul22(ph, pl, th, tl, ph, pl);
        d_ops::add22cond(ph, pl, kfh, kfl, ph, pl);
    }
    return dvf_type(ph, pl);
}


template <typename _T>
template <typename cftal::math::elem_func_core<double, _T>::log_func _F,
          typename cftal::math::elem_func_core<double, _T>::result_prec _P>
typename cftal::math::elem_func_core<double, _T>::dvf_type
cftal::math::elem_func_core<double, _T>::
__pow_log_k(arg_t<vf_type> xc)
{
    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel_val_or_zero(_T::vmf_to_vmi2(is_denom), vi2_type(-54));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - _T::bias();
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    // brute force:
    vf_type ymh, yml;
    d_ops::add12cond(ymh, yml, xr, -1.0);
    vf_type yph, ypl;
    d_ops::add12cond(yph, ypl, xr, +1.0);
    vf_type qh, ql;
    d_ops::div22(qh, ql, ymh, yml, yph, ypl);
    return __pow_log_k<_F, _P>(qh, ql, kf);
}

template <typename _T>
template <typename cftal::math::elem_func_core<double, _T>::log_func _F,
          typename cftal::math::elem_func_core<double, _T>::result_prec _P>
typename cftal::math::elem_func_core<double, _T>::dvf_type
cftal::math::elem_func_core<double, _T>::
__pow_log_k2(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    vf_type xrh;
    auto k=__frexp_k(xrh, xh);
    vf_type xrl=ldexp_k(xl, -k);

    vmf_type c= xrh < M_SQRT2*0.5;
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));
    xrh = _T::sel(c, xrh*2.0, xrh);
    xrl = _T::sel(c, xrl*2.0, xrl);
    kf = _T::sel(c, kf-1.0, kf);

    vf_type ymh, yml;
    d_ops::add122cond(ymh, yml, -1.0, xrh, xrl);
    vf_type yph, ypl;
    d_ops::add122cond(yph, ypl, +1.0, xrh, xrl);
    vf_type qh, ql;
    d_ops::div22(qh, ql, ymh, yml, yph, ypl);
    return __pow_log_k<_F, _P>(qh, ql, kf);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type abs_x= abs(x);
    dvf_type ldx= __pow_log_k<log_func::c_log_2,
                              result_prec::normal>(abs_x);
    dvf_type yldx = y*ldx;
    vf_type kf= rint(vf_type(yldx[0]));
    dvf_type xrhl= yldx - kf;
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type xrh, xrl;
    d_ops::mul22(xrh, xrl, xrhl[0], xrhl[1],
                 ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type res=__pow_exp_k(xrh, xrl, kf);
    // std::cout << kf << std::endl;
    // std::cout << k << std::endl;
    using fc=func_constants<double>;
    const vf_type& d= yldx[0];
    const double exp2_hi_inf= fc::exp2_hi_inf();
    const double exp2_lo_zero= fc::exp2_lo_zero();
    res = _T::sel_zero_or_val(d <= exp2_lo_zero, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    // res = _T::sel(d == 0.0, 1.0, res);
    // res = _T::sel(d == 1.0, 2.0, res);
    return res;
}


template <typename _T>
typename cftal::math::elem_func_core<double, _T>::pow_k2_result
cftal::math::elem_func_core<double, _T>::
pow_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
       arg_t<vf_type> yh, arg_t<vf_type> yl)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    dvf_type abs_x= select(xh > 0.0, dvf_type(xh, xl), dvf_type(-xh, -xl));
    dvf_type ldx=__pow_log_k2<log_func::c_log_2,
                              result_prec::normal>(abs_x[0], abs_x[1]);
    dvf_type yldx = dvf_type(yh, yl)*ldx;
    vf_type kf= rint(vf_type(yldx[0]));
    dvf_type xrhl= yldx - kf;
    vf_type xrh, xrl;
    d_ops::mul22(xrh, xrl, xrhl[0], xrhl[1],
                 ctbl::m_ln2[0], ctbl::m_ln2[1]);
    vf_type rl, rh=__pow_exp_poly_k(xrh, xrl, &rl);
    auto sc = __scale_exp_k(kf);
    return std::make_pair(dvf_type(rh, rl), sc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vi2_type
cftal::math::elem_func_core<double, _T>::
__reduce_trig_arg(vf_type& xrh, vf_type& xrl, arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type fn= rint(vf_type(x* ctbl::m_2_pi[0]));

    const double large_arg=0x1p28;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);

    if (likely(!all_of(v_large_arg))) {
        const double m_pi_2_h=+1.5707963267948965579990e+00;
        const double m_pi_2_m=+6.1232339957367660358688e-17;
        const double m_pi_2_l=-1.4973849048591698329435e-33;
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
    } else {
        // keep the compiler silent
        xrh=x;
        xrl=0.0;
    }
    vi_type q(_T::cvt_f_to_i(fn));
    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(double)) v_d {
            double _sc[N];
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
                double y[2];
                // ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                ti._sc[i]=impl::__kernel_rem_pio2(y, tf._sc[i]);
                d0_l._sc[i]= y[1];
                d0_h._sc[i]= y[0];
            }
        }
        xrh = mem<vf_type>::load(d0_h._sc, N);
        xrl = mem<vf_type>::load(d0_l._sc, N);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    vi2_type q2=_T::vi_to_vi2(q);
    return q2;
}

template <typename _T>
inline
std::pair<typename cftal::math::elem_func_core<double, _T>::dvf_type,
          typename cftal::math::elem_func_core<double, _T>::vi_type>
cftal::math::elem_func_core<double, _T>::
reduce_trig_arg_k(arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    vf_type fn= rint(vf_type(x* ctbl::m_2_pi[0]));
    vf_type xrh, xrl;
    const double m_pi_2_h=+1.5707963267948965579990e+00;
    const double m_pi_2_m=+6.1232339957367660358688e-17;
    const double m_pi_2_l=-1.4973849048591698329435e-33;

    vf_type f0, f1, f2, f3, f4, f5;
    d_ops::mul12(f0, f1, fn, -m_pi_2_h);
    d_ops::mul12(f2, f3, fn, -m_pi_2_m);
    d_ops::mul12(f4, f5, fn, -m_pi_2_l);
    // normalize f0 - f5 into p0..p2
    vf_type p0, p1, p2, t;
    p0 = f0;
    d_ops::add12(p1, t, f1, f2);
    p2 = f4 + t + f3 + f5;
    d_ops::add12(p0, p1, p0, p1);
    d_ops::add12(p1, p2, p1, p2);
    t = x + p0;
    xrh = t + p1;
    xrl = p1 - (xrh - t) + p2;
    dvf_type d0(xrh, xrl);

    vi_type q(_T::cvt_f_to_i(fn));

    const double large_arg=0x1p28;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);
    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(double)) v_d {
            double _sc[N];
        } tf, d0_l, d0_h;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, x);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0[1]);
        mem<vf_type>::store(d0_h._sc, d0[0]);
        for (std::size_t i=0; i<N; ++i) {
            if (large_arg < std::fabs(tf._sc[i])) {
                double y[2];
                // ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                ti._sc[i]=impl::__kernel_rem_pio2(y, tf._sc[i]);
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
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-65.75
    // coefficients for sin generated by sollya
    // x^3 : -0xa.aaaaaaaaaaaa8p-6
    const double sin_c3=-1.6666666666666665741481e-01;
    // x^5 : +0x8.8888888888338p-10
    const double sin_c5=+8.3333333333330383146942e-03;
    // x^7 : -0xd.00d00cffd6618p-16
    const double sin_c7=-1.9841269840923354632854e-04;
    // x^9 : +0xb.8ef1d13ee1e78p-22
    const double sin_c9=+2.7557319021644065914860e-06;
    // x^11 : -0xd.732069828cf5p-29
    const double sin_c11=-2.5052043274294370345991e-08;
    // x^13 : +0xb.0711ea8fea688p-36
    const double sin_c13=+1.6047294965259665336204e-10;
    // x^15 : -0xb.7e01089ac32fp-44
    const double sin_c15=-6.5325612420449819354698e-13;
    // x^17 : -0xb.64eac061cb4bp-48
    const double sin_c17=-4.0480355151479898933826e-14;
    // sin(x+xl) ~ sin(x) + cos(x)*xl
    // sin(x+xl) ~ x+s3*x^3+s5*x^5 + ... + cos(x)*xl
    //           = x+s3*x^3+s5*x^5 + ... + (1-x*x/2)*xl
    //           = x+s3*x^3+s5*x^5 + ... + xl - x^2*xl/2
    //           = x+s3^x^3+x^2*(s5*x^3+...) + xl - x^2*xl/2
    // with p= s5*x^3+ s7*x^5 + s9*x^7 + ...
    //           = s1*x+s3^x^3+x^2*(p-xl/2)+xl
    vf_type x2=xh*xh;
    vf_type x3=x2*xh;

    vf_type x4=x2*x2;
    static const double c[]= {
        sin_c17, sin_c15, sin_c13, sin_c11, sin_c9, sin_c7, sin_c5
    };
    vf_type p=horner2(x2, x4, c)*x3;
    vf_type s= xh + (x3*sin_c3 + (x2*(p-xl*0.5) + xl));
    s = _T::sel(xh == 0.0, xh, s);
    return s;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.785398185253143310546875] : | p - f | <= 2^-68.5625
    // coefficients for cos generated by sollya
    // x^4 : +0xa.aaaaaaaaaaaa8p-8
    const double cos_c4=+4.1666666666666664353702e-02;
    // x^6 : -0xb.60b60b60b5a58p-13
    const double cos_c6=-1.3888888888888447064457e-03;
    // x^8 : +0xd.00d00d0013098p-19
    const double cos_c8=+2.4801587301259415111907e-05;
    // x^10 : -0x9.3f27db0aab07p-25
    const double cos_c10=-2.7557319100721175104631e-07;
    // x^12 : +0x8.f76bc25c94448p-32
    const double cos_c12=+2.0876731782420635499728e-09;
    // x^14 : -0xc.9bf5764d12da8p-40
    const double cos_c14=-1.1468013512615928202661e-11;
    // x^16 : +0xd.135bf90ffe23p-48
    const double cos_c16=+4.6453941653669631599764e-14;

    // cos(x+xl) ~ 1.0 - 0.5*x^2 + c4*x^4+c4*x5 + ...- sin(x)*xl
    //           ~ 1.0 - 0.5*x^2 + p - x*xl
    // to increase precision add and subtract 1-0.5*x^2:
    //           = (1-0.5*x^2)+(1.0-(1.0-0.5*x^2)-0.5*x^2) + (p-x*xl)
    //           =      w     +(1.0-      w)     -0.5*x^2  + (p-x*xl)
    vf_type x2=xh*xh;
    vf_type x4=x2*x2;
    static const double ci[]={
        cos_c16, cos_c14, cos_c12, cos_c10, cos_c8, cos_c6, cos_c4
    };
    vf_type p=horner2(x2, x4, ci);
    vf_type hx2=x2*0.5;
    vf_type w= 1.0 -hx2;
    vf_type c= w + (((1.0-w)-hx2) + (x4*p-xh*xl));
    return c;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
__tan_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl, arg_t<vi2_type> q)
{

    // [0, 0.785398185253143310546875] : | p - f | <= 2^-60.015625
    // coefficients for tan generated by sollya
    // x^1 : +0x8p-3
    const double tan_c1=+1.0000000000000000000000e+00;
    // x^3 : +0xa.aaaaaaaaaaafp-5
    const double tan_c3=+3.3333333333333381442998e-01;
    // x^5 : +0x8.888888888303p-6
    const double tan_c5=+1.3333333333325486647070e-01;
    // x^7 : +0xd.d0dd0dd5d757p-8
    const double tan_c7=+5.3968253972781141114545e-02;
    // x^9 : +0xb.327a42f229d78p-9
    const double tan_c9=+2.1869488403428224282399e-02;
    // x^11 : +0x9.1371d2c200e9p-10
    const double tan_c11=+8.8632378469818730304386e-03;
    // x^13 : +0xe.b69777df5eeep-12
    const double tan_c13=+3.5921017387960784555956e-03;
    // x^15 : +0xb.ed8904cc8f978p-13
    const double tan_c15=+1.4560390612973863385532e-03;
    // x^17 : +0x9.a604f13ca7ef8p-14
    const double tan_c17=+5.8889849328602392446869e-04;
    // x^19 : +0xf.f75d1024602b8p-16
    const double tan_c19=+2.4362585112802884082343e-04;
    // x^21 : +0xa.fed3d6f47fc08p-17
    const double tan_c21=+8.3888396582130708386583e-05;
    // x^23 : +0x8.bafbdd40b0c1p-17
    const double tan_c23=+6.6607709073967748996184e-05;
    // x^25 : -0xd.06204f8d6309p-19
    const double tan_c25=-2.4841176076767215654285e-05;
    // x^27 : +0xc.92b6d7155bcfp-18
    const double tan_c27=+4.7962579420398501034960e-05;
    // x^29 : -0xc.8c87bfcf6e0c8p-19
    const double tan_c29=-2.3935215700734370540765e-05;
    // x^31 : +0xa.31e5a50639158p-20
    const double tan_c31=+9.7226241578203219248977e-06;
    vf_type xrh2;
    d_ops::sqr21(xrh2, xrh, xrl);
    vf_type xrh4=xrh2*xrh2;
    vf_type xrh8=xrh4*xrh4;

    static const double cee[]={
        tan_c31,
        tan_c23,
        tan_c15
    };
    static const double ceo[]={
        tan_c27,
        tan_c19,
        tan_c11
    };
    vf_type ee, eo;
    horner_n2(ee, eo, xrh8, cee, ceo);

    static const double coe[]={
        tan_c29,
        tan_c21,
        tan_c13
    };
    static const double coo[]={
        tan_c25,
        tan_c17,
        tan_c9
    };
    vf_type oe, oo;
    horner_n2(oe, oo, xrh8, coe, coo);

    vf_type e=horner(xrh4, ee, eo, tan_c7);
    vf_type o=horner(xrh4, oe, oo, tan_c5);
    vf_type t=horner(xrh2, e, o, tan_c3);
    vf_type th, tl;
    horner_comp_quick(th, tl, xrh2, t, tan_c1);
    d_ops::mul22(th, tl, xrh, xrl, th, tl);
    vi2_type q1= q & 1;
    vmi2_type qm1= q1 == vi2_type(1);
    vmf_type fqm1= _T::vmi2_to_vmf(qm1);

    vf_type c;
    d_ops::rcp21(c, th, tl);
    th = _T::sel(fqm1, -c, th);
    return th;
}

template <typename _T>
inline
void
cftal::math::elem_func_core<double, _T>::
__sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi2_type> q,
            vf_type* ps, vf_type* pc)
{
#if 0
    vf_type s= __sin_k(xrh, xrl);
    vf_type c= __cos_k(xrh, xrl);
#else
    // [3.4694469519536141888238489627838134765625e-18, 0.785398185253143310546875] : | p - f | <= 2^-68.5625
    // coefficients for cos generated by sollya
    // x^4 : +0xa.aaaaaaaaaaaa8p-8
    const double cos_c4=+4.1666666666666664353702e-02;
    // x^6 : -0xb.60b60b60b5a58p-13
    const double cos_c6=-1.3888888888888447064457e-03;
    // x^8 : +0xd.00d00d0013098p-19
    const double cos_c8=+2.4801587301259415111907e-05;
    // x^10 : -0x9.3f27db0aab07p-25
    const double cos_c10=-2.7557319100721175104631e-07;
    // x^12 : +0x8.f76bc25c94448p-32
    const double cos_c12=+2.0876731782420635499728e-09;
    // x^14 : -0xc.9bf5764d12da8p-40
    const double cos_c14=-1.1468013512615928202661e-11;
    // x^16 : +0xd.135bf90ffe23p-48
    const double cos_c16=+4.6453941653669631599764e-14;
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-65.75
    // coefficients for sin generated by sollya
    // x^3 : -0xa.aaaaaaaaaaaa8p-6
    const double sin_c3=-1.6666666666666665741481e-01;
    // x^5 : +0x8.8888888888338p-10
    const double sin_c5=+8.3333333333330383146942e-03;
    // x^7 : -0xd.00d00cffd6618p-16
    const double sin_c7=-1.9841269840923354632854e-04;
    // x^9 : +0xb.8ef1d13ee1e78p-22
    const double sin_c9=+2.7557319021644065914860e-06;
    // x^11 : -0xd.732069828cf5p-29
    const double sin_c11=-2.5052043274294370345991e-08;
    // x^13 : +0xb.0711ea8fea688p-36
    const double sin_c13=+1.6047294965259665336204e-10;
    // x^15 : -0xb.7e01089ac32fp-44
    const double sin_c15=-6.5325612420449819354698e-13;
    // x^17 : -0xb.64eac061cb4bp-48
    const double sin_c17=-4.0480355151479898933826e-14;

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
    vf_type x2= xrh * xrh;
    vf_type x4= x2* x2;

    static const double c_sin_a[]= { sin_c17, sin_c13, sin_c9 };
    static const double c_sin_b[]= { sin_c15, sin_c11, sin_c7 };
    vf_type p_sin_a, p_sin_b;
    horner_n2(p_sin_a, p_sin_b, x4, c_sin_a, c_sin_b);
    vf_type x3= x2* xrh;

    static const double c_cos_a[]= { cos_c16, cos_c12, cos_c8 };
    static const double c_cos_b[]= { cos_c14, cos_c10, cos_c6 };
    vf_type p_cos_a, p_cos_b;
    horner_n2(p_cos_a, p_cos_b, x4, c_cos_a, c_cos_b);

    vf_type p_sin = horner(x2, p_sin_a, p_sin_b, sin_c5)* x3;
    vf_type p_cos = horner(x2, p_cos_a, p_cos_b, cos_c4);

    vf_type s= xrh + (x3*sin_c3 + (x2*(p_sin-xrl*0.5) + xrl));
    s = _T::sel(xrh == 0.0, xrh, s);
    vf_type hx2=x2*0.5;
    vf_type w= 1.0 -hx2;
    vf_type c= w + (((1.0-w)-hx2) + (x4*p_cos-xrh*xrl));
#endif
    vmi2_type q_and_2(vi2_type(q & vi2_type(2))==vi2_type(2));
    vmf_type q_and_2_f(_T::vmi2_to_vmf(q_and_2));
    vmi2_type q_and_1(vi2_type(q & vi2_type(1))==vi2_type(1));
    vmf_type q_and_1_f(_T::vmi2_to_vmf(q_and_1));
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
cftal::math::elem_func_core<double, _T>::
__sin_cos_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi2_type> q,
            dvf_type* ps, dvf_type* pc)
{
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-74.8125
    // coefficients for cos generated by sollya
    // x^0 : +0x8p-3
    const double cos_c0=+1.0000000000000000000000e+00;
    // x^2 : -0x8p-4
    const double cos_c2=-5.0000000000000000000000e-01;
    // x^4 h: +0xa.aaaaaaaaaaaa8p-8
    const double cos_c4h=+4.1666666666666664353702e-02;
    // x^4 l: +0xa.61064e00cc748p-62
    const double cos_c4l=+2.2505874013560704770729e-18;
    // x^6 : -0xb.60b60b60b6078p-13
    const double cos_c6=-1.3888888888888872071709e-03;
    // x^8 : +0xd.00d00d00c6p-19
    const double cos_c8=+2.4801587301569866239603e-05;
    // x^10 : -0x9.3f27dbaefe138p-25
    const double cos_c10=-2.7557319214744139428399e-07;
    // x^12 : +0x8.f76c64286586p-32
    const double cos_c12=+2.0876754236148643106523e-09;
    // x^14 : -0xc.9c98c138850ep-40
    const double cos_c14=-1.1470279653434290801974e-11;
    // x^16 : +0xd.55c18555f445p-48
    const double cos_c16=+4.7375380573980351719884e-14;

    // [0, 0.785398185253143310546875] : | p - f | <= 2^-77.09375
    // coefficients for sin generated by sollya
    // x^1 : +0x8p-3
    const double sin_c1=+1.0000000000000000000000e+00;
    // x^3 h: -0xa.aaaaaaaaaaaa8p-6
    const double sin_c3h=-1.6666666666666665741481e-01;
    // x^3 l: -0xa.a9b2b4d12c7ep-60
    const double sin_c3l=-9.2485768106366967659007e-18;
    // x^5 : +0x8.8888888888888p-10
    const double sin_c5=+8.3333333333333332176851e-03;
    // x^7 : -0xd.00d00d00cff2p-16
    const double sin_c7=-1.9841269841269694885338e-04;
    // x^9 : +0xb.8ef1d2ab39528p-22
    const double sin_c9=+2.7557319223894213899905e-06;
    // x^11 : -0xd.7322b3b10bc3p-29
    const double sin_c11=-2.5052108353527748850256e-08;
    // x^13 : +0xb.0922c0136462p-36
    const double sin_c13=+1.6059037439750684629749e-10;
    // x^15 : -0xd.73a6f9bca15p-44
    const double sin_c15=-7.6464440294670327735235e-13;
    // x^17 : +0xc.7a84b3e367b58p-52
    const double sin_c17=+2.7708030053329543554254e-15;

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

    static const double c_cos[]={
        cos_c16, cos_c14, cos_c12, cos_c10, cos_c8
    };
    static const double c_sin[]={
        sin_c17, sin_c15, sin_c13, sin_c11, sin_c9
    };
    horner_n2(ch, sh, xxh, c_cos, c_sin);
    ch *= xxh;
    sh = horner(xxh, sh, sin_c7)*xxh;

    vf_type cl;
    d_ops::add12(ch, cl, cos_c6, ch);
    d_ops::mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add22(ch, cl, cos_c4h, cos_c4l, ch, cl);
    d_ops::mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c2, ch, cl);
    d_ops::mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c0, ch, cl);

    vf_type sl;
    d_ops::add12(sh, sl, sin_c5, sh);
    d_ops::mul22(sh, sl, sh, sl, xxh, xxl);
    d_ops::add22(sh, sl, sin_c3h, sin_c3l, sh, sl);
    d_ops::mul22(sh, sl, sh, sl, xxh, xxl);
    d_ops::add122(sh, sl, sin_c1, sh, sl);
    d_ops::mul22(sh, sl, sh, sl, xrh, xrl);

    vmf_type xrh_eq_0 = xrh == 0.0;
    sh = _T::sel(xrh_eq_0, xrh, sh);
    sl = _T::sel(xrh_eq_0, 0.0, sl);

    vmi2_type q_and_2(vi2_type(q & vi2_type(2))==vi2_type(2));
    vmf_type q_and_2_f(_T::vmi2_to_vmf(q_and_2));
    vmi2_type q_and_1(vi2_type(q & vi2_type(1))==vi2_type(1));
    vmf_type q_and_1_f(_T::vmi2_to_vmf(q_and_1));

    // swap sin/cos if q & 1
    if (ps != nullptr) {
        vf_type rsh(_T::sel(q_and_1_f, ch, sh));
        vf_type rsl(_T::sel(q_and_1_f, cl, sl));
        // swap signs
        rsh = _T::sel(q_and_2_f, -rsh, rsh);
        rsl = _T::sel(q_and_2_f, -rsl, rsl);
        *ps = dvf_type(rsh, rsl);
    }
    if (pc != nullptr) {
        vf_type rch(_T::sel(q_and_1_f, sh, ch));
        vf_type rcl(_T::sel(q_and_1_f, sl, cl));
        // swap signs
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        rch = _T::sel(mt, -rch, rch);
        rcl = _T::sel(mt, -rcl, rcl);
        *pc= dvf_type(rch, rcl);
    }
}

template <typename _T>
inline
void
cftal::math::elem_func_core<double, _T>::
sin_cos_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type xrh, xrl;
    auto q= __reduce_trig_arg(xrh, xrl, xc);
    __sin_cos_k(xrh, xrl, q, ps, pc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
tan_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl;
    auto q= __reduce_trig_arg(xrh, xrl, xc);
    vf_type t=__tan_k(xrh, xrl, q);
    return t;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
atan_k(arg_t<vf_type> xc)
{
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
/* atan(x)
 * Method
 *   1. Reduce x to positive by atan(x) = -atan(-x).
 *   2. According to the integer k=4t+0.25 chopped, t=x, the argument
 *      is further reduced to one of the following intervals and the
 *      arctangent of t is evaluated by the corresponding formula:
 *
 *      [0,7/16]      atan(x) = t-t^3*(a1+t^2*(a2+...(a10+t^2*a11)...)
 *      [7/16,11/16]  atan(x) = atan(1/2) + atan( (t-0.5)/(1+t/2) )
 *      [11/16.19/16] atan(x) = atan( 1 ) + atan( (t-1)/(1+t) )
 *      [19/16,39/16] atan(x) = atan(3/2) + atan( (t-1.5)/(1+1.5t) )
 *      [39/16,INF]   atan(x) = atan(INF) + atan( -1/t )
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */
    /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
    const vf_type atan_0_5_hi = 4.63647609000806093515e-01;
    /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
    const vf_type atan_0_5_lo = 2.26987774529616870924e-17;
    /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
    const vf_type atan_1_0_hi = 7.85398163397448278999e-01;
    /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
    const vf_type atan_1_0_lo = 3.06161699786838301793e-17;
    /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
    const vf_type atan_1_5_hi = 9.82793723247329054082e-01;
    /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
    const vf_type atan_1_5_lo = 1.39033110312309984516e-17;
    /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
    const vf_type atan_inf_hi = 1.57079632679489655800e+00;
    /* atan(inf)lo 0x3C91A626, 0x33145C07 */
    const vf_type atan_inf_lo = 6.12323399573676603587e-17;

    vf_type x=abs(xc);
    // range reduction
    vmf_type r=x > 7.0/16;
    vf_type atan_hi= _T::sel_val_or_zero(r, atan_0_5_hi);
    vf_type atan_lo= _T::sel_val_or_zero(r, atan_0_5_lo);
    vf_type t=_T::sel(r, (2.0*x-1.0)/(2.0+x), x);
    r = x>11.0/16;
    atan_hi=_T::sel(r, atan_1_0_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_0_lo, atan_lo);
    t = _T::sel(r, (x-1.0)/(1.0+x), t);
    r = x>19.0/16;
    atan_hi=_T::sel(r, atan_1_5_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_5_lo, atan_lo);
    t = _T::sel(r, (x-1.5)/(1.0+1.5*x), t);
    r = x>39.0/16;
    atan_hi=_T::sel(r, atan_inf_hi, atan_hi);
    atan_lo=_T::sel(r, atan_inf_lo, atan_lo);
    t = _T::sel(r, -1.0/x, t);
    /* end of argument reduction */
    // [3.4694469519536141888238489627838134765625e-18, 0.4375] : | p - f | <= 2^-55.578125
    // coefficients for atan generated by sollya
    // x^0 : +0xa.aaaaaaaaaaaa8p-5
    const double atan_c0=+3.3333333333333331482962e-01;
    // x^2 : -0xc.cccccccccbecp-6
    const double atan_c2=-1.9999999999998752109320e-01;
    // x^4 : +0x9.24924923ecb9p-6
    const double atan_c4=+1.4285714285479006457891e-01;
    // x^6 : -0xe.38e38dcb8c098p-7
    const double atan_c6=-1.1111111091221941016283e-01;
    // x^8 : +0xb.a2e8a66330358p-7
    const double atan_c8=+9.0909081691621970722217e-02;
    // x^10 : -0x9.d89b5a3a9692p-7
    const double atan_c10=-7.6922816330967480613623e-02;
    // x^12 : +0x8.8860741c15338p-7
    const double atan_c12=+6.6661888784588549383692e-02;
    // x^14 : -0xf.0b35042500c3p-8
    const double atan_c14=-5.8764756690837180452824e-02;
    // x^16 : +0xd.59042ba8433ap-8
    const double atan_c16=+5.2139530809893225304918e-02;
    // x^18 : -0xb.798b2c169a4c8p-8
    const double atan_c18=-4.4823358787291663063446e-02;
    // x^20 : +0x8.6d95ca9f7d6ep-8
    const double atan_c20=+3.2922136276729324633195e-02;
    // x^22 : -0xe.efef0dee26fa8p-10
    const double atan_c22=-1.4587149834858851096819e-02;

    static const double ci[]={
        atan_c22, atan_c20, atan_c18, atan_c16,
        atan_c14, atan_c12, atan_c10, atan_c8,
        atan_c6, atan_c4, atan_c2, atan_c0
    };
    vf_type t2=t*t;
    vf_type p= t2 * horner2(t2, vf_type(t2*t2), ci);
    vf_type at=  atan_hi - (t * p - atan_lo - t);
    at = copysign(at, xc);
    return at;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
atan2_k(arg_t<vf_type> y, arg_t<vf_type> x)
{
    vf_type yx=y/x;
    vf_type t=atan_k(abs(yx));
    vf_type y_s = copysign(vf_type(1.0), y);
    vf_type x_s = copysign(vf_type(1.0), x);

    vmf_type y_lt_0 = y_s < 0.0;
    vmf_type x_lt_0 = x_s < 0.0;
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    // default y>=0, x>=0,
    vf_type at= _T::sel(y_lt_0 & x_lt_0,
                        (t - ctbl::m_pi[1]) - ctbl::m_pi[0],
                        t);
    at = _T::sel(y_lt_0 & (x_s>=0), -t, at);
    at = _T::sel((y_s >=0) & x_lt_0,
                 ctbl::m_pi[0] - (t - ctbl::m_pi[1]),
                 at);
    return at;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
asin_k_poly(arg_t<vf_type> x2)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-55.578125
    // coefficients for asin generated by sollya
    // x^0 : +0xa.aaaaaaaaaaabp-6
    const double asin_c0=+1.6666666666666668517038e-01;
    // x^2 : +0x9.9999999996e68p-7
    const double asin_c2=+7.4999999999980818121692e-02;
    // x^4 : +0xb.6db6db721cbep-8
    const double asin_c4=+4.4642857146857090056002e-02;
    // x^6 : +0xf.8e38e0a6d04ep-9
    const double asin_c6=+3.0381944106381383874371e-02;
    // x^8 : +0xb.745d97f1195dp-9
    const double asin_c8=+2.2372174069959817332975e-02;
    // x^10 : +0x8.e268dfce900c8p-9
    const double asin_c10=+1.7352368660141424122623e-02;
    // x^12 : +0xe.4e8e767a889f8p-10
    const double asin_c12=+1.3971544247973198202284e-02;
    // x^14 : +0xb.c066bfc3c65e8p-10
    const double asin_c14=+1.1476140455619060834480e-02;
    // x^16 : +0xa.96f869a145d7p-10
    const double asin_c16=+1.0341531226293412121242e-02;
    // x^18 : +0xb.0523e77b2d4f8p-11
    const double asin_c18=+5.3808980004733933041883e-03;
    // x^20 : +0x9.02efb2b82f72p-9
    const double asin_c20=+1.7600527349798236742551e-02;
    // x^22 : -0xf.83ec355b4bc98p-10
    const double asin_c22=-1.5151682621602968401020e-02;
    // x^24 : +0xe.d339866978be8p-9
    const double asin_c24=+2.8955266626085929965173e-02;

    static const double ci[]={
        asin_c24,
        asin_c22,
        asin_c20,
        asin_c18,
        asin_c16,
        asin_c14,
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
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
asin_k(arg_t<vf_type> xc)
{
/* asin(x)
 * Method :
 *      Since  asin(x) = x + x^3/6 + x^5*3/40 + x^7*15/336 + ...
 *      we approximate asin(x) on [0,0.5] by
 *              asin(x) = x + x*x^2*R(x^2)
 *      where
 *              R(x^2) is a rational approximation of (asin(x)-x)/x^3
 *      and its remez error is bounded by
 *              |(asin(x)-x)/x^3 - R(x^2)| < 2^(-58.75)
 *
 *      For x in [0.5,1]
 *              asin(x) = pi/2-2*asin(sqrt((1-x)/2))
 *      Let y = (1-x), z = y/2, s := sqrt(z), and pio2_hi+pio2_lo=pi/2;
 *      then for x>0.98
 *              asin(x) = pi/2 - 2*(s+s*z*R(z))
 *                      = pio2_hi - (2*(s+s*z*R(z)) - pio2_lo)
 *      For x<=0.98, let pio4_hi = pio2_hi/2, then
 *              f = hi part of s;
 *              c = sqrt(z) - f = (z-f*f)/(s+f)         ...f+c=sqrt(z)
 *      and
 *              asin(x) = pi/2 - 2*(s+s*z*R(z))
 *                      = pio4_hi+(pio4-2s)-(2s*z*R(z)-pio2_lo)
 *                      = pio4_hi+(pio4-2f)-(2s*z*R(z)-(pio2_lo+2c))
 *
 * Special cases:
 *      if x is NaN, return x itself;
 *      if |x|>1, return NaN with invalid signal.
 *
 */
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vmf_type x_lt_1_2= x<0.5;
    vf_type x2= x*x;
    vf_type z= (1-x)*0.5;
    vf_type s= sqrt(z);

    vf_type xr=_T::sel(x_lt_1_2, x2, z);
    vf_type r=asin_k_poly(xr);
    vf_type as0= x + x*r;
    // default: x>0.975
    // vf_type as = ctbl::m_pi_2[0] - (2*(s+s*r) - ctbl::m_pi_2[1]);
    // x in [0, 1]
    vf_type f=_T::clear_low_word(s);
    vf_type c= (z-f*f)/(s+f);
    vf_type as1= 0.5 * ctbl::m_pi_2[0] -
                         (2*s*r - (ctbl::m_pi_2[1] -2 *c) - (0.5*ctbl::m_pi_2[0]-2*f));
    vf_type as=_T::sel(x_lt_1_2, as0, as1);
    as = copysign(as, xc);
    return as;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
acos_k(arg_t<vf_type> xc)
{
/* acos(x)
 * Method :
 *      acos(x)  = pi/2 - asin(x)
 *      acos(-x) = pi/2 + asin(x)
 * For |x|<=0.5
 *      acos(x) = pi/2 - (x + x*x^2*R(x^2))     (see asin.c)
 * For x>0.5
 *      acos(x) = pi/2 - (pi/2 - 2asin(sqrt((1-x)/2)))
 *              = 2asin(sqrt((1-x)/2))
 *              = 2s + 2s*z*R(z)        ...z=(1-x)/2, s=sqrt(z)
 *              = 2f + (2c + 2s*z*R(z))
 *     where f=hi part of s, and c = (z-f*f)/(s+f) is the correction term
 *     for f so that f+c ~ sqrt(z).
 * For x<-0.5
 *      acos(x) = pi - 2asin(sqrt((1-|x|)/2))
 *              = pi - 0.5*(s+s*z*R(z)), where z=(1-|x|)/2,s=sqrt(z)
 *
 * Special cases:
 *      if x is NaN, return x itself;
 *      if |x|>1, return NaN with invalid signal.
 *
 * Function needed: sqrt
 */
    vf_type x= xc;

    vmf_type x_lt_m_1_2 = x < -0.5;
    vmf_type x_gt_1_2 = x>0.5;
    vmf_type abs_x_le_1_2 = abs(x) <= 0.5;

    vf_type z= _T::sel(x_lt_m_1_2, (1.0+x)*0.5, (1.0-x)*0.5);
    vf_type s= sqrt(z);
    vf_type x2=x*x;
    vf_type xr= _T::sel(abs_x_le_1_2, x2, z);
    vf_type r= asin_k_poly(xr);

    // x in [-0.5, 0.5]
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type ac = ctbl::m_pi_2[0] - (x - (ctbl::m_pi_2[1]-x*r));
    // x in [-1.0, -0.5]
    vf_type wn = r*s - ctbl::m_pi_2[1];
    vf_type ac1= 2*(ctbl::m_pi_2[0] - (s+wn));
    ac = _T::sel(x_lt_m_1_2, ac1, ac);
    // x in [0.5, 1.0]
    vf_type df= _T::clear_low_word(s);
    vf_type c= (z-df*df)/(s+df);
    vf_type wp= r*s+c;
    vf_type ac2=2*(df+wp);
    ac = _T::sel(x_gt_1_2, ac2, ac);
    return ac;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
asinh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    vmf_type x_gt_0x1p28 = x > 0x1p28;
    vf_type add_2_log=_T::sel_val_or_zero(x_gt_0x1p28, ctbl::m_ln2[0]);
    vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p28,
                            x,
                            2.0 * x+ 1.0/(sqrt(vf_type(t+1.0))+x));
    vf_type yl= __log_k<log_func::c_log_e>(log_arg);
    yl += add_2_log;
    // |x| < 2.0
    vf_type log1p_arg= x+t/(1.0+sqrt(vf_type(1.0+t)));
    vf_type ys= log1p_k(log1p_arg);

    // [3.4694469519536141888238489627838134765625e-18, 0.707106769084930419921875] : | p - f | <= 2^-56
    // coefficients for asinh generated by sollya
    // x^0 : +0x8p-3
    const double asinh_c0=+1.0000000000000000000000e+00;
    // x^2 : -0xa.aaaaaaaaaa1cp-6
    const double asinh_c2=-1.6666666666665874707576e-01;
    // x^4 : +0x9.99999998cd5p-7
    const double asinh_c4=+7.4999999998548450008684e-02;
    // x^6 : -0xb.6db6db0673fb8p-8
    const double asinh_c6=-4.4642857048941601838532e-02;
    // x^8 : +0xf.8e38c907b54dp-9
    const double asinh_c8=+3.0381941356476184490365e-02;
    // x^10 : -0xb.745b0f60c1bbp-9
    const double asinh_c10=-2.2372098567191987805725e-02;
    // x^12 : +0x8.e25c3a0e8df58p-9
    const double asinh_c12=+1.7351991736429466656189e-02;
    // x^14 : -0xe.4b05712b70068p-10
    const double asinh_c14=-1.3958058388070094038569e-02;
    // x^16 : +0xb.c91c2d4f668f8p-10
    const double asinh_c16=+1.1509361520302406264871e-02;
    // x^18 : -0x9.cc465ffb1bfa8p-10
    const double asinh_c18=-9.5683094102944985653858e-03;
    // x^20 : +0xf.da37011c56bap-11
    const double asinh_c20=+7.7404305662115320540995e-03;
    // x^22 : -0xb.a56203cc5b2cp-11
    const double asinh_c22=-5.6865365418566557464963e-03;
    // x^24 : +0xd.ecd9210d1e03p-12
    const double asinh_c24=+3.3997041326254721568811e-03;
    // x^26 : -0xb.7d7197c462c08p-13
    const double asinh_c26=-1.4025896654284721824096e-03;
    // x^28 : +0x9.73fd0c879255p-15
    const double asinh_c28=+2.8848510652019576736699e-04;

    static const double ci[]={
        asinh_c28,
        asinh_c26,
        asinh_c24,
        asinh_c22,
        asinh_c20,
        asinh_c18,
        asinh_c16,
        asinh_c14,
        asinh_c12,
        asinh_c10,
        asinh_c8,
        asinh_c6,
        asinh_c4,
        asinh_c2,
        asinh_c0
    };
    vf_type yss= x* horner2(t, vf_type(t*t), ci);

    ys = _T::sel(x<= M_SQRT2*0.5, yss, ys);

    vf_type ash=_T::sel(x <= 2.0, ys, yl);
    ash = copysign(ash, xc);
    return ash;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
acosh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    vmf_type x_gt_0x1p26 = x > 0x1p26;
    vf_type add_2_log=_T::sel_val_or_zero(x_gt_0x1p26, ctbl::m_ln2[0]);
    // vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p26,
                            x,
                            2.0*x - 1.0/(x+sqrt(vf_type(x*x-1))));
    vf_type yl= __log_k<log_func::c_log_e>(log_arg);
    yl += add_2_log;

    vf_type xm1l;
    vf_type xm1=d_ops::two_diff(x, vf_type(1), xm1l);
    dvf_type sqrt2xm1=sqrt(mul_pwr2(dvf_type(xm1, xm1l), vf_type(2)));
    // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]
    // [3.4694469519536141888238489627838134765625e-18, 1] : | p - f | <= 2^-62.75
    // coefficients for acosh generated by sollya
    // x^0 : +0x8p-3
    const double acosh_c0=+1.0000000000000000000000e+00;
    // x^1 : -0xa.aaaaaaaaaaa9p-7
    const double acosh_c1=-8.3333333333333287074041e-02;
    // x^2 : +0x9.99999999969dp-9
    const double acosh_c2=+1.8749999999994694521721e-02;
    // x^3 : -0xb.6db6db6bccc88p-11
    const double acosh_c3=-5.5803571426395063084791e-03;
    // x^4 : +0xf.8e38e2ed17b48p-13
    const double acosh_c4=+1.8988715231981984164072e-03;
    // x^5 : -0xb.745d07569c688p-14
    const double acosh_c5=-6.9912991362188804406880e-04;
    // x^6 : +0x8.e2751de7a3f1p-15
    const double acosh_c6=+2.7113646120568827852654e-04;
    // x^7 : -0xe.4cb4bce8dd5ep-17
    const double acosh_c7=-1.0909754060304648884058e-04;
    // x^8 : +0xb.d372715f209dp-18
    const double acosh_c8=+4.5112476384836415759134e-05;
    // x^9 : -0x9.fa0bf6aacc0ep-19
    const double acosh_c9=-1.9029131029489704750833e-05;
    // x^10 : +0x8.8081ba4f05f9p-20
    const double acosh_c10=+8.1081194769401966767567e-06;
    // x^11 : -0xe.55cbc4be4ec28p-22
    const double acosh_c11=-3.4177638318537515068880e-06;
    // x^12 : +0xb.72c013cb57d08p-23
    const double acosh_c12=+1.3647369584241793363111e-06;
    // x^13 : -0x8.0cd10a91b969p-24
    const double acosh_c13=-4.7982124786910910239706e-07;
    // x^14 : +0x8.f8c9d4867b86p-26
    const double acosh_c14=+1.3369068032649017936561e-07;
    // x^15 : -0xd.91588be74b8bp-29
    const double acosh_c15=-2.5271917436897211509152e-08;
    // x^16 : +0xa.262fe8ff68a98p-32
    const double acosh_c16=+2.3630374462414833615335e-09;

    static const double ci[]={
        acosh_c16,
        acosh_c15,
        acosh_c14,
        acosh_c13,
        acosh_c12,
        acosh_c11,
        acosh_c10,
        acosh_c9,
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
    vf_type y= _T::sel(x < 2.0, ys, yl);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
atanh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
#if 0
    vf_type xph, xpl, xmh, xml;
    d_ops::add12(xph, xpl, 1.0, x);
    d_ops::add12(xmh, xml, 1.0, -x);
    vf_type th, tl;
    // d_ops::rcp2(th, tl, xmh, xml);
    d_ops::div22(th, tl, xph, xpl, xmh, xml);
    auto a=__pow_log_k2<log_func::c_log_e,result_prec::normal>(th, tl);
    vf_type y=a[0]*0.5;
#else
#if 1
    // [0, 0.5] : | p - f | <= 2^-61.859375
    // coefficients for atanh_c generated by sollya
    // x^1 : +0x8p-3
    const double atanh_c1=+1.0000000000000000000000e+00;
    // x^3 : +0xa.aaaaaaaaaaa4p-5
    const double atanh_c3=+3.3333333333333259318465e-01;
    // x^5 : +0xc.ccccccccdc58p-6
    const double atanh_c5=+2.0000000000022088997298e-01;
    // x^7 : +0x9.2492491d76ecp-6
    const double atanh_c7=+1.4285714283128814194868e-01;
    // x^9 : +0xe.38e3919ca96e8p-7
    const double atanh_c9=+1.1111111268958091813364e-01;
    // x^11 : +0xb.a2e83dfdff6c8p-7
    const double atanh_c11=+9.0909033078783521575339e-02;
    // x^13 : +0x9.d8a9185816a18p-7
    const double atanh_c13=+7.6924454581036846856357e-02;
    // x^15 : +0x8.87cc9bf2a3c3p-7
    const double atanh_c15=+6.6644264360801924729216e-02;
    // x^17 : +0xf.1fd45f4a5e51p-8
    const double atanh_c17=+5.9079430832178717047931e-02;
    // x^19 : +0xc.f0cdb12cdbacp-8
    const double atanh_c19=+5.0549369579001079966218e-02;
    // x^21 : +0xf.481df260c0eap-8
    const double atanh_c21=+5.9694167780211110363453e-02;
    // x^23 : -0xb.afbc1a2999d08p-11
    const double atanh_c23=-5.7062812313234687403019e-03;
    // x^25 : +0xb.3d93b898d14a8p-6
    const double atanh_c25=+1.7563336398167864182973e-01;
    // x^27 : -0xc.999745775cb48p-6
    const double atanh_c27=-1.9687444480718888084603e-01;
    // x^29 : +0xf.74969aa1ddedp-6
    const double atanh_c29=+2.4149098492441006813536e-01;
    static const double c[]={
        atanh_c29, atanh_c27, atanh_c25,
        atanh_c23, atanh_c21, atanh_c19, atanh_c17,
        atanh_c15, atanh_c13, atanh_c11, atanh_c9,
        atanh_c7, atanh_c5, atanh_c3
    };
    static_cast<void>(atanh_c1);
    vf_type xx=x*x;
    vf_type p=horner2(xx, vf_type(xx*xx), c)*xx;
    vf_type ys=x+p*x;
#else
    // atanh(x) = x + 1/3*x^3 + 1/5*x^5
    //          = x + x^3/(3+x^2*Q)
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-54.3125
    // coefficients for atanh generated by sollya
    // x^0 : -0xe.6666666666668p-3
    const double atanh_c0=-1.8000000000000000444089e+00;
    // x^2 : -0xd.2a6c405d9c6a8p-6
    const double atanh_c2=-2.0571428571424257847333e-01;
    // x^4 : -0xd.7552366fea678p-7
    const double atanh_c4=-1.0514285715165104517776e-01;
    // x^6 : -0x8.914156cf95528p-7
    const double atanh_c6=-6.6932837856408314292089e-02;
    // x^8 : -0xc.2feccc796ed28p-8
    const double atanh_c8=-4.7606277389998376270430e-02;
    // x^10 : -0x9.454e5409eed38p-8
    const double atanh_c10=-3.6213775174412980717431e-02;
    // x^12 : -0xe.c38ee3a37e688p-9
    const double atanh_c12=-2.8835740363999221719249e-02;
    // x^14 : -0xc.0caa32fca509p-9
    const double atanh_c14=-2.3534125064836493301801e-02;
    // x^16 : -0xa.d819c51f48c4p-9
    const double atanh_c16=-2.1179967224854517882093e-02;
    // x^18 : -0xb.17d69a9ae9a5p-10
    const double atanh_c18=-1.0833123384807703121213e-02;
    // x^20 : -0x9.52ebeee6a1868p-8
    const double atanh_c20=-3.6421533418098041290367e-02;
    // x^22 : +0x8.20bf3feb67ac8p-8
    const double atanh_c22=+3.1749680619582228147113e-02;
    // x^24 : -0xf.5530a41a25ddp-8
    const double atanh_c24=-5.9893646301268657627936e-02;
    vf_type xx=x*x;
    static const double ci[]={
        atanh_c24,
        atanh_c22,
        atanh_c20,
        atanh_c18,
        atanh_c16,
        atanh_c14,
        atanh_c12,
        atanh_c10,
        atanh_c8,
        atanh_c6,
        atanh_c4,
        atanh_c2,
        atanh_c0
    };
    vf_type Q = horner2(xx, vf_type(xx*xx), ci);
    vf_type ys= x + x*xx/(3.0 + xx * Q);
#endif
    vf_type log1p_arg= 2*(x/(1-x));
    vf_type yl= 0.5*log1p_k(log1p_arg);
    vf_type y=_T::sel(x<=0.5, ys, yl);
#endif
    y = copysign(y, xc);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<double, _T>::vf_type
cftal::math::elem_func_core<double, _T>::
hypot_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type xa=abs(x);
    vf_type ya=abs(y);
    vf_type ma=max(xa, ya);
    vf_type mi=min(xa, ya);

    vf_type scale=1.0;
    vf_type factor=1.0;
    // avoid underflows
    vmf_type ma_small= ma < 0x1p-450;
    scale = _T::sel(ma_small, 0x1p-700, scale);
    factor= _T::sel(ma_small, 0x1p700, factor);
    // avoid overflows
    vmf_type ma_large= ma > 0x1p510;
    scale = _T::sel(ma_large, 0x1p700, scale);
    factor= _T::sel(ma_large, 0x1p-700, factor);
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
