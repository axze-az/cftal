//
// Copyright (C) 2010-2024 Axel Zeuner
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
#include <cftal/d_real_traits_f32.h>
#include <cftal/std_types.h>
#include <cftal/math/elem_func.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/func_data.h>
#include <cftal/math/misc.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/payne_hanek.h>
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
            using vdf_type = typename _T::vdf_type;
            using d_ops=d_real_ops<vf_type,
                                   d_real_traits<vf_type>::fma>;

            enum result_prec {
                normal,
                medium,
                high
            };

            // call a scalar function on x
            template <typename _SCALAR_FUNC>
            static
            vf_type
            call_scalar_func(arg_t<vf_type> x, _SCALAR_FUNC f);

            // call a scalar function on x
            template <typename _SCALAR_FUNC>
            static
            vf_type
            call_scalar_func(arg_t<vf_type> x,
                             arg_t<vf_type> y,
                             _SCALAR_FUNC f);

            // unsigned integer __fmod
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


            template <int32_t _X>
            static
            vi_type
            __ilogb_plus(arg_t<vf_type> x);

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);

            static
            vi_type
            ilogb(arg_t<vf_type> vf);

            static
            vf_type
            rsqrt_k(arg_t<vf_type> x);

            // calculates x^(1/3)
            static
            vf_type
            cbrt_k(arg_t<vf_type> x);

            // calculates x^-(1/3)
            static
            vf_type
            rcbrt_k(arg_t<vf_type> x);

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
            __two_pow(arg_t<vi_type> ki);

            // returns 2^k = r.f0()* r.f1() to avoid over and underflows
            static
            scale_result
            __two_pow(arg_t<vf_type> k);

            // returns y*2^ki
            static
            vf_type
            __mul_two_pow(arg_t<vf_type> y, arg_t<vi_type> ki);

            // returns y*2^ki, yl*2^ki
            static
            vdf_type
            __mul_two_pow(arg_t<vf_type> y, arg_t<vf_type> yl,
                          arg_t<vi_type> ki);

            // scaling function for exponential functions
            // returns y*2^k
            static
            vf_type
            __mul_two_pow(arg_t<vf_type> y, arg_t<vf_type> k);

            // scaling function for exponential functions
            // returns yh*2^k, yl*2^k
            static
            vdf_type
            __mul_two_pow(arg_t<vf_type> yh,
                          arg_t<vf_type> yl,
                          arg_t<vf_type> k);

            // arguments are the reduced xrh, xrl in
            // [-log(2)/2, log(2)/2], and the argument
            // k as argument for __mul_two_pow
            // x_small marks the range where e^x-1 == xrh
            // calculates %e^(xrh+xrl)*2^k - 1 if exp_m1 is true,
            // %e^(xrh+xrl)*2^k otherwise
            template <bool _EXP_M1>
            static
            vf_type
            __exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                    arg_t<vf_type> k,
                    arg_t<vmf_type> x_small);

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
            // ki as argument for __mul_two_pow
            // idx is the table index
            // calculates %e^(xrh+xrl)*(2^idx/N)*2^ki
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
            exp_k2(vf_type& __restrict eh,
                   vf_type& __restrict el,
                   arg_t<vf_type> xh,
                   arg_t<vf_type> xl);

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

            // returns 1/(1+exp(-x))
            static
            vf_type
            sig_k(arg_t<vf_type> x);

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

            // return xr * 2^ki = xc
            static
            vi_type
            __reduce_log_arg(vf_type& __restrict xr,
                             arg_t<vf_type> xc);

            // argument reduction for table based logarithm
            static
            vi_type
            __reduce_log_arg(vf_type& __restrict xr,
                             vi_type& __restrict idx,
                             arg_t<vf_type> x);

            // polynomial approximation of log1p(r), r2=r*r
            static
            vf_type
            __log_poly_k_poly(arg_t<vf_type> r,
                              arg_t<vf_type> r2);

            static
            vf_type
            __log_poly_k(arg_t<vf_type> r);

            // calculates log
            //        2^k * c * (1+xr/c) = xc
            // (1 + xr/c) = r, rl
            // log_c_h, log_c_l = log(c)
            // with higher precision
            template <result_prec _P>
            static
            vdf_type
            __log_tbl_k2(arg_t<vf_type> r,
                         arg_t<vf_type> rl,
                         arg_t<vf_type> log_c_h,
                         arg_t<vf_type> log_c_l,
                         arg_t<vf_type> kf);

            // calculates log(xc+xcl) with higher precision
            template <result_prec _P>
            static
            vdf_type
            __log_tbl_k2(arg_t<vf_type> xc, arg_t<vf_type> xcl);

            // calculates log(xc) with higher precision
            static
            vdf_type
            __log_tbl_k12(arg_t<vf_type> xc);

            static
            vf_type
            __log1p_poly_k(arg_t<vf_type> x);

            static
            vf_type
            log1p_k(arg_t<vf_type> x);

            static
            vf_type
            log_k(arg_t<vf_type> x);

            static
            vf_type
            __mul_invln2_add_kf(arg_t<vf_type> lnh,
                                arg_t<vf_type> lnl,
                                arg_t<vf_type> kf);

            static
            vf_type
            log2_k(arg_t<vf_type> x);

            static
            vf_type
            log2p1_k(arg_t<vf_type> x);

            static
            vf_type
            __mul_invln10_add_kflg2(arg_t<vf_type> lnh,
                                    arg_t<vf_type> lnl,
                                    arg_t<vf_type> kf);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            static
            vf_type
            log10p1_k(arg_t<vf_type> x);

            // calculation of x^y
            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y);

            // returns (xh+xl)^(yh+yl) * 2^(sc) as vdf_type in first,
            // sc in second
            using pow_k2_result = std::pair<vdf_type, scale_result>;
            static
            pow_k2_result
            pow_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
                   arg_t<vf_type> yh, arg_t<vf_type> yl);

            // calculation of x^e or x^1/e
            template <bool _CALC_ROOT>
            static
            vf_type
            powi_k(arg_t<vf_type> x, arg_t<vi_type> e);

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
                        vdf_type* ps, vdf_type* pc);

            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tan_k(arg_t<vf_type> x);

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

            // tan(pi*x) calculation
            static
            vf_type
            tanpi_k(arg_t<vf_type> x);

            // atan calculation for x in [0, 1]
            static
            vdf_type
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
template <typename _SCALAR_FUNC>
inline
typename
cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
call_scalar_func(arg_t<vf_type> x, _SCALAR_FUNC f)
{
    using std::size;
    const std::size_t _N = size(x);
    vf_type r;
    for (std::size_t i=0; i<_N; ++i) {
        float xi=extract(x, i);
        float ri=f(xi);
        insert(r, ri, i);
    }
    return r;
}

template <typename _T>
template <typename _SCALAR_FUNC>
inline
typename
cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
call_scalar_func(arg_t<vf_type> x, arg_t<vf_type> y, _SCALAR_FUNC f)
{
    using std::size;
    const std::size_t _N = size(x);
    vf_type r;
    for (std::size_t i=0; i<_N; ++i) {
        float xi=extract(x, i);
        float yi=extract(y, i);
        float ri=f(xi, yi);
        insert(r, ri, i);
    }
    return r;
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
    vi_type r= _T::sel_vi((ax > ay) | opp_sgn, ux_dec, ux_inc);
    vi_type r0= _T::sel_vi(ay == 0, uy, (uy & sign_f32_msk::v.s32()) | 1);
    r = _T::sel_vi(ax == 0, r0, r);
    r = _T::sel_vi(ux == uy, uy, r);
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
    vmf_type is_denom= abs(x) < fc::min_normal();

    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    vi_type eo= _T::sel_val_or_zero_vi(i_is_denom, vi_type(-25));
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
    if (_T::any_of_vmi(i_is_near_z)) {
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
    r = _T::sel(isinf(x) | isnan(x) | (x==vf_type(0.0)), x, r);
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
    vmf_type is_denom= abs(x) < fc::min_normal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    const int32_t neg_bias_p_1=-_T::bias()+1;
    const int32_t neg_bias_p_1_m_25=neg_bias_p_1 - 25;
    vi_type e=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                         neg_bias_p_1_m_25, neg_bias_p_1);
    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    // exponent:
    e += ((i >> 23) & 0xff);
    const int32_t half=0x3f000000;
    const int32_t clear_exp_msk=0x807fffff;
    // insert exponent
    i &= clear_exp_msk;
    i |= half;
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
    vmf_type is_denom= abs(x) < fc::min_normal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    const int32_t neg_bias_p_1=-_T::bias()+1;
    const int32_t neg_bias_p_1_m_25=neg_bias_p_1 - 25;
    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    const int32_t half=0x3f000000;
    const int32_t clear_exp_msk=0x807fffff;
    // insert exponent
    vi_type mi = i & clear_exp_msk;
    mi |= half;
    vf_type m= _T::as_float(mi);
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    m = _T::sel(f_inz, x, m);
    if (ve != nullptr) {
        vi_type e=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                             neg_bias_p_1_m_25, neg_bias_p_1);
        // exponent:
        e += ((i >> 23) & 0xff);
        vmi_type i_inz=_T::vmf_to_vmi(f_inz);
        e = _T::sel_zero_or_val_vi(i_inz, e);
        *ve=e;
    }
    return m;
}

template <typename _T>
template <cftal::int32_t _X>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__ilogb_plus(arg_t<vf_type> x)
{
    vf_type xs=abs(x);
    using fc=func_constants<float>;
    vmf_type is_denom= xs < fc::min_normal();
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel_vi(i_is_denom, vi_type(-25), eo);
    // reinterpret as integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) /* & 0xff*/ ) + eo - vi_type(_T::bias()-_X);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
ilogbp1(arg_t<vf_type> d)
{
    return __ilogb_plus<1>(d);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(__ilogb_plus<0>(d));
    vmf_type mf= d == 0.0f;
    vmi_type mi= _T::vmf_to_vmi(mf);
    e = _T::sel_vi(mi, vi_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel_vi(mi, vi_type(0x7fffffff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel_vi(mi, vi_type(FP_ILOGBNAN), e);
    return e;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    constexpr
    const float one=1.0f;
    vf_type y= vf_type(one/sqrt(x));
#if 0
    // use this code if f32 should not produce any error in the tests if
    // your processor supports fma
    vf_type z = y*(y*x) - one;
    y = y + y*(z*horner(z, 3.0f/8.0f, -0.5f));
#endif
    y = impl::root_r2::order2<float, true>(y, x);
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
    // do a division by 3, round to - infinity:
    vi_type e3 = (((e)*fac_1_3)>>shift_1_3) /* -(e>>31) */;
    vi_type r = e - e3 - (e3<<1);
    // if we have a positive remainder we have to correct
    // the final exponent:
#if 1
    vmi_type r_gt_z = r > 0;
    vi_type e3c= e3 + _T::sel_val_or_zero_vi(r_gt_z, 1);
#else
    vi_type e3c= _T::sel_vi(r==-2, e3, e3);
    e3c=_T::sel_vi(r==-1, e3, e3c);
    e3c=_T::sel_vi(r==1, e3+1, e3c);
    e3c=_T::sel_vi(r==2, e3+1, e3c);
#endif
    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 3
    // 1    0.25    -2           -2
    // 2    0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
#if 1
    vi_type rc= r + _T::sel_val_or_zero_vi(r_gt_z, -3);
    vi_type rc_exp= rc << 23;
    // correction of the exponent of mm0:
    vi_type mm0i=_T::as_int(mm0) + rc_exp;
    mm0=_T::as_float(mm0i);
#else
    vf_type rf=_T::cvt_i_to_f(r);
    vf_type scale=_T::sel(rf==-2.0, 0.25, 1.0);
    scale=_T::sel(rf==-1.0, 0.5, scale);
    scale=_T::sel(rf==1.0, 0.25, scale);
    scale=_T::sel(rf==2.0, 0.5, scale);
    mm0 = mm0 * scale;
#endif
#if 1
    // [0.125, 1] : | p - f | <= 2^-11.82421875
    // coefficients for cbrt generated by sollya
    // x^0 : +0x8.e3f96p-5f
    constexpr
    const float cbrt_c0=+2.7782887220e-01f;
    // x^1 : +0x9.8ff06p-2f
    constexpr
    const float cbrt_c1=+2.3905653954e+00f;
    // x^2 : -0xc.74144p-1f
    constexpr
    const float cbrt_c2=-6.2267169952e+00f;
    // x^3 : +0xc.57311p+0f
    constexpr
    const float cbrt_c3=+1.2340592384e+01f;
    // x^4 : -0xe.c0162p+0f
    constexpr
    const float cbrt_c4=-1.4750337601e+01f;
    // x^5 : +0x9.7496p+0f
    constexpr
    const float cbrt_c5=+9.4554138184e+00f;
    // x^6 : -0x9.f353p-2f
    constexpr
    const float cbrt_c6=-2.4876213074e+00f;
    constexpr static const float ci[]={
        cbrt_c6,
        cbrt_c5, cbrt_c4, cbrt_c3,
        cbrt_c2, cbrt_c1, cbrt_c0
    };
    vf_type mm = horner2(mm0, vf_type(mm0*mm0), ci);
#else
    // [0.125, 1] : | p - f | <= 2^-4.123046875
    // coefficients for cbrt generated by sollya
    // x^0 : +0xe.8050fp-5f
    constexpr
    const float cbrt_c0=+4.5316359401e-01f;
    // x^1 : +0x9.aae0ap-4f
    constexpr
    const float cbrt_c1=+6.0421812534e-01f;
    vf_type mm = horner(mm0,
                        cbrt_c1,
                        cbrt_c0);
    // 1st iteration
    mm = impl::root_3::order3<float>(mm, mm0);
#endif
    // round mm to 8 bits = int(24/3)
    mm=round_to_nearest_even_last_bits<24-24/3>(mm);
    // second iteration
    mm = impl::root_3::order5<float>(mm, mm0);
    // no denormal results are possible
#if 1
    vi_type e3c_exp=(e3c<<23);
    vi_type mmi=_T::as_int(mm) + e3c_exp;
    mm=_T::as_float(mmi);
#else
    vf_type t= _T::insert_exp(_T::bias()+e3c);
    mm *=t;
#endif
    // mm = copysign(mm, xc);
    mm |= (xc & sign_f32_msk::v.f32());
    return mm;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
rcbrt_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);

    // reduce x into [2^-3, 1.0)
    const int32_t shift_1_3 = 9;
    const int32_t fac_1_3 = ((1<<shift_1_3)+2)/3;

    vf_type mm0;
    auto e=__frexp_k(mm0, xp);
    // do a division by 3, round to - infinity:
    vi_type e3 = (((e)*fac_1_3)>>shift_1_3) /* -(e>>31) */;
    vi_type r = e - e3 - (e3<<1);
    // if we have a positive remainder we have to correct
    // the final exponent:
#if 1
    vmi_type r_gt_z = r > 0;
    vi_type e3c= e3 + _T::sel_val_or_zero_vi(r_gt_z, 1);
#else
    vi_type e3c= _T::sel_vi(r==-2, e3, e3);
    e3c=_T::sel_vi(r==-1, e3, e3c);
    e3c=_T::sel_vi(r==1, e3+1, e3c);
    e3c=_T::sel_vi(r==2, e3+1, e3c);
#endif
    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 3
    // 1    0.25    -2           -2
    // 2    0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
#if 1
    vi_type rc= r + _T::sel_val_or_zero_vi(r_gt_z, -3);
    vi_type rc_exp= rc << 23;
    // correction of the exponent of mm0:
    vi_type mm0i=_T::as_int(mm0) + rc_exp;
    mm0=_T::as_float(mm0i);
#else
    vf_type rf=_T::cvt_i_to_f(r);
    vf_type scale=_T::sel(rf==-2.0, 0.25, 1.0);
    scale=_T::sel(rf==-1.0, 0.5, scale);
    scale=_T::sel(rf==1.0, 0.25, scale);
    scale=_T::sel(rf==2.0, 0.5, scale);
    mm0 = mm0 * scale;
#endif
    // [0.125, 1] : | p - f | <= 2^-9.76953125
    // coefficients for rcbrt generated by sollya
    // x^0 : +0xc.94d52p-2f
    constexpr
    const float rcbrt_c0=+3.1453442574e+00f;
    // x^1 : -0xf.03ca1p+0f
    constexpr
    const float rcbrt_c1=-1.5014801979e+01f;
    // x^2 : +0x8.12b8ep+3f
    constexpr
    const float rcbrt_c2=+6.4585067749e+01f;
    // x^3 : -0xa.eec72p+4f
    constexpr
    const float rcbrt_c3=-1.7492361450e+02f;
    // x^4 : +0x9.19d05p+5f
    constexpr
    const float rcbrt_c4=+2.9122671509e+02f;
    // x^5 : -0x9.06246p+5f
    constexpr
    const float rcbrt_c5=-2.8876776123e+02f;
    // x^6 : +0x9.c19c9p+4f
    constexpr
    const float rcbrt_c6=+1.5610072327e+02f;
    // x^7 : -0x8.d68b3p+2f
    constexpr
    const float rcbrt_c7=-3.5352245331e+01f;
    constexpr static const float ci[]={
        rcbrt_c7, rcbrt_c6,
        rcbrt_c5, rcbrt_c4, rcbrt_c3,
        rcbrt_c2, rcbrt_c1, rcbrt_c0
    };
    vf_type mm02=mm0*mm0;
    vf_type mm = horner2(mm0, mm02, ci);
    // round mm to 8 bits = int(24/3)
    mm=round_to_nearest_even_last_bits<24-24/3>(mm);
    // second iteration
    mm = impl::root_r3::order5<float>(mm, mm0);
    // no denormal results are possible
#if 1
    vi_type e3c_exp=(e3c<<23);
    vi_type mmi=_T::as_int(mm) - e3c_exp;
    mm=_T::as_float(mmi);
#else
    vf_type t= _T::insert_exp(_T::bias()-e3c);
    mm *=t;
#endif
    // mm = copysign(mm, xc);
    mm |= (xc & sign_f32_msk::v.f32());
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

    // do a division by 12, round to - infinity:
    vi_type e12= (e*fac_1_12)>>shift_1_12;
    // r is always in [0, 1, 11] because of the round down
    vi_type r = e - ((e12<<3) + (e12<<2));
    // vi_type r = e - e12 *12;
    // if we have a positive remainder we have to correct
    // the final exponent:
    vmi_type r_gt_z = r > 0;
    vi_type e12c= e12 + _T::sel_val_or_zero_vi(r_gt_z, 1);
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
    vi_type rc= r + _T::sel_val_or_zero_vi(r_gt_z, -12);
    vi_type rc_exp= rc << 23;
    // correction of the exponent of mm0:
    vi_type mm0i=_T::as_int(mm0) + rc_exp;
    mm0=_T::as_float(mm0i);
    // [2.44140625e-4, 1.953125e-3] : | p - f | <= 2^-8.08984375
    // coefficients for root12_i0 generated by sollya
    // x^0 : +0xf.3c1f4p-5f
    constexpr
    const float root12_i0_c0=+4.7608911991e-01f;
    // x^1 : +0xe.bf4cfp+3f
    constexpr
    const float root12_i0_c1=+1.1797814178e+02f;
    // x^2 : -0xe.cb641p+11f
    constexpr
    const float root12_i0_c2=-3.0299126953e+04f;
    constexpr
    static const float ci0[] = {
        root12_i0_c2, root12_i0_c1, root12_i0_c0
    };
    // [1.953125e-3, 1.5625e-2] : | p - f | <= 2^-7.83984375
    // coefficients for root12_i1 generated by sollya
    // x^0 : +0x9.0f06cp-4f
    constexpr
    const float root12_i1_c0=+5.6616854668e-01f;
    // x^1 : +0x8.c4cedp+1f
    constexpr
    const float root12_i1_c1=+1.7537561417e+01f;
    // x^2 : -0x8.cbff5p+6f
    constexpr
    const float root12_i1_c2=-5.6299932861e+02f;
    constexpr
    static const float ci1[] = {
        root12_i1_c2, root12_i1_c1, root12_i1_c0
    };
    // [1.5625e-2, 0.125] : | p - f | <= 2^-7.58984375
    // coefficients for root12_i2 generated by sollya
    // x^0 : +0xa.c5cd8p-4f
    constexpr
    const float root12_i2_c0=+6.7329168320e-01f;
    // x^1 : +0xa.6d8a8p-2f
    constexpr
    const float root12_i2_c1=+2.6069736481e+00f;
    // x^2 : -0xa.76173p+0f
    constexpr
    const float root12_i2_c2=-1.0461291313e+01f;
    constexpr
    static const float ci2[] = {
        root12_i2_c2, root12_i2_c1, root12_i2_c0
    };
    // [0.125, 1] : | p - f | <= 2^-7.33984375
    // coefficients for root12_i3 generated by sollya
    // x^0 : +0xc.cf994p-4f
    constexpr
    const float root12_i3_c0=+8.0068325996e-01f;
    // x^1 : +0xc.66a31p-5f
    constexpr
    const float root12_i3_c1=+3.8752892613e-01f;
    // x^2 : -0xc.70cddp-6f
    constexpr
    const float root12_i3_c2=-1.9438500702e-01f;
    constexpr
    static const float ci3[] = {
        root12_i3_c2, root12_i3_c1, root12_i3_c0
    };
    vf_type mm_i0 = horner(mm0, ci0);
    vf_type mm_i1 = horner(mm0, ci1);
    vf_type mm_i2 = horner(mm0, ci2);
    vf_type mm_i3 = horner(mm0, ci3);
    vf_type mm_a= _T::sel(mm0 < 0x1p-9f, mm_i0, mm_i1);
    vf_type mm_b= _T::sel(mm0 < 0x1p-3f, mm_i2, mm_i3);
    vf_type mm= _T::sel(mm0 < 0x1p-6f, mm_a, mm_b);

    mm = impl::root_12::householder4<float>(mm, mm0);
    vi_type e12c_exp=(e12c<<23);
    vi_type mmi=_T::as_int(mm) + e12c_exp;
    mm=_T::as_float(mmi);
    // mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::scale_result
cftal::math::elem_func_core<float, _T>::
__two_pow(arg_t<vi_type> ki)
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
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__mul_two_pow(arg_t<vf_type> y, arg_t<vi_type> k)
{
    vi_type ka= k >> 1;
    vi_type kb= k - ka;
    ka <<= 23;
    kb += _T::bias();
    kb <<= 23;
    vi_type yi=_T::as_int(y) + ka;
    vf_type s1=_T::as_float(kb);
    vf_type r=_T::as_float(yi) * s1;
    return r;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vdf_type
cftal::math::elem_func_core<float, _T>::
__mul_two_pow(arg_t<vf_type> y,  arg_t<vf_type> yl,
              arg_t<vi_type> k)
{
    // use floating point operations here because yl may underflow
    auto sc=__two_pow(k);
    vf_type rh= y*sc.f0();
    vf_type rl= yl*sc.f0();
    rh *= sc.f1();
    rl *= sc.f1();
    return vdf_type(rh, rl);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::scale_result
cftal::math::elem_func_core<float, _T>::
__two_pow(arg_t<vf_type> k)
{
    return __two_pow(_T::cvt_f_to_i(k));
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__mul_two_pow(arg_t<vf_type> ym, arg_t<vf_type> k)
{
    return __mul_two_pow(ym, _T::cvt_f_to_i(k));
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vdf_type
cftal::math::elem_func_core<float, _T>::
__mul_two_pow(arg_t<vf_type> yh, arg_t<vf_type> yl, arg_t<vf_type> k)
{
    return __mul_two_pow(yh, yl, _T::cvt_f_to_i(k));
}

template <typename _T>
template <bool _EXP_M1>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
        arg_t<vf_type> kf,
        arg_t<vmf_type> x_small)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-32.609375
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3f
    constexpr
    const float exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    constexpr
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8p-4f
    constexpr
    const float exp_c2=+5.0000000000e-01f;
    // x^3 : +0xa.aaaa9p-6f
    constexpr
    const float exp_c3=+1.6666664183e-01f;
    // x^4 : +0xa.aaa73p-8f
    constexpr
    const float exp_c4=+4.1666459292e-02f;
    // x^5 : +0x8.88ae5p-10f
    constexpr
    const float exp_c5=+8.3338962868e-03f;
    // x^6 : +0xb.6a77ep-13f
    constexpr
    const float exp_c6=+1.3935414609e-03f;
    // x^7 : +0xc.d3317p-16f
    constexpr
    const float exp_c7=+1.9569355936e-04f;
    static_assert(exp_c0 == 1.0f, "exp_c0 == 1.0f is expected");
    static_assert(exp_c1 == 1.0f, "exp_c1 == 1.0f is expected");
    static_assert(exp_c2 == 0.5f, "exp_c2 == 0.5f is expected");

    vf_type x2= xrh*xrh;
    constexpr
    static const float ci[]={
        exp_c7, exp_c6, exp_c5, exp_c4, exp_c3
    };

    vf_type p=horner2(xrh, x2, ci);
    vf_type y;
    // y = 1 + (xrh + xrl) + c2r2 + (x*x2*p) + xrl + xrl* expm1
    vf_type c2r=exp_c2*xrh; // exact because c2 == 0.5
    vf_type c2r2, e0;
    d_ops::mul12(c2r2, e0, c2r, xrh);
    vf_type e1;
    d_ops::add12(y, e1, c2r2, x2*(xrh*p));
    vf_type e2;
    d_ops::add12(y, e2, xrh, y);
    vf_type e3=xrl + xrl*y;
    vf_type e4;
    d_ops::add12(y, e4, exp_c0, y);
    // d_ops::add12(y, ye, y, e0+e1+e2+e3+e4);
    vf_type ye=e0+e1+e2+e3+e4;
    if (_EXP_M1 == false) {
        y += (ye);
        y = __mul_two_pow(y, kf);
    } else {
        // 2^kf = 2*2^s ; s = kf/2
        vf_type scale = __mul_two_pow(vf_type(0.5f), kf);
        // e^x-1 = 2*(y * 2^s - 0.5)
        y  *= scale;
        vf_type t;
        d_ops::add12cond(y, t, -0.5f, y);
        // ye = 2.0f * (ye * scale + t);
        ye = (ye * scale + t);
        ye += ye;
        y = 2.0f*y + ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel(x_small, xrh, y);
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
    static_assert(exp_c1==1.0f, "oops");

#if 1
    vf_type x2=xrh*xrh;
    vf_type p2=horner(xrh, exp_c3, exp_c2);
    vf_type xrlp=xrl+x2*p2;
#if defined (__tune_znver2__) || defined(__tune_znver3__) \
    || defined (__tune_znver4__)
    auto lk=make_fixed_lookup_table<exp_data<float>::EXP_N, float>(idx);
#else
    auto lk=make_variable_lookup_table<float>(idx);
#endif
    const auto& tbl=exp_data<float>::_tbl;
    vf_type tf=lk.from(tbl._2_pow_i_n_f);
    vf_type th=lk.from(tbl._2_pow_i_n_h);
    vf_type eh=xrh + (xrlp + (tf /*+ xrl * xrh*/ ));
    vf_type y;
    if (expl!=nullptr) {
        vf_type ye;
        d_ops::muladd12(y, ye, th, th, eh);
        *expl=ye;
    } else {
        if (d_real_traits<vf_type>::fma==true) {
            y= th + th*eh;
        } else {
#if 1
            y= th + th*eh;
#else
            // y = d_ops::xfma(th, eh, th);
            // we know |th| >= |th*eh|
            vf_type ehh, ehl;
            d_real_traits<vf_type>::split(eh, ehh, ehl);
            vf_type thh, thl;
            d_real_traits<vf_type>::split(th, thh, thl);
            vf_type hh= ehh* thh;
            vf_type hl= ehh* thl;
            vf_type lh= ehl* thh;
            vf_type ll= ehl* thl;
            vf_type yh, yl;
            d_ops::add12(yh, yl, th, hh);
            yl += ll + lh + hl;
            y = yh + yl;
#endif
        }
    }
    return y;
#else
    auto lk=make_variable_lookup_table<float>(idx);
    const auto& tbl=exp_data<float>::_tbl;
    vf_type tl=lk.from(tbl._2_pow_i_n_l);
    vf_type th=lk.from(tbl._2_pow_i_n_h);

    vf_type x2=xrh*xrh;
    vf_type p2=horner(xrh, exp_c3, exp_c2);
    vf_type xrlp=xrl+x2*p2;
    vf_type y;
    if (_P == result_prec::high) {
        vf_type eh, e0;
        d_ops::mul12(eh, e0, th, xrh);
        vf_type ye= e0 + th * xrlp;
        vf_type e2;
        d_ops::add12(y, e2, th, eh);
        ye= ye + tl + e2 + tl*xrh;
        if (expl != nullptr) {
            d_ops::add12(y, ye, y, ye);
            *expl = ye;
        } else {
            y+= ye;
        }
    } else {
        vf_type eh=xrh + xrlp;
        vf_type el=tl + tl*xrh;
        vf_type ye=el + th*eh;
        if (expl!=nullptr) {
            d_ops::add12(y, ye, th, ye);
            *expl=ye;
        } else {
            y= th + ye;
        }
    }
    return y;
#endif
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
        y=__exp_tbl_k<result_prec::normal>(xrh, xrl, idx, nullptr);
        y= __mul_two_pow(y, ki);
    } else {
        vf_type t;
        y=__exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &t);
        auto sc=__mul_two_pow(y, t, ki);
        y=sc[0];
        *expl=sc[1];
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
    // l1h=round(log(2), 24-9, RN);
    // l1l=log(2)-l1h;
    // write_coeff(l1h, "", "const float _ln2_h_cw", single);
    // write_coeff(l1l, "", "const float _ln2_l_cw", single);
    // x^ : +0xb.172p-4f
    constexpr
    const float _ln2_h_cw=+6.9314575195e-01f;
    // x^ : +0xb.fbe8ep-23f
    constexpr
    const float _ln2_l_cw=+1.4286067653e-06f;
    vf_type hi = x - kf * _ln2_h_cw;
    xrh = hi - kf * _ln2_l_cw;
    vf_type dx = hi-xrh;
    xrl = dx - kf * _ln2_l_cw;
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
    d_ops::unorm_mul122(neg_kfln2h, neg_kfln2l,
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
    constexpr
    const float _32_ln2=+4.6166240692e+01f;
    // x^ : +0xb.17p-9f
    constexpr
    const float _ln2_32_cw_h=+2.1659851074e-02f;
    // x^ : +0x8.5fdf4p-23f
    constexpr
    const float _ln2_32_cw_l=+9.9831822808e-07f;
#if 0
    vf_type kf = rint(vf_type(x * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type x32ln2=x*_32_ln2;
    vf_type kf= rint(x32ln2);
    vi_type ki=_T::cvt_f_to_i(x32ln2);
#endif
    idx = ki & int32_t(exp_data<float>::EXP_IDX_MASK);
    k = ki >> int32_t(exp_data<float>::EXP_SHIFT);
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
    constexpr
    const float _32_ln2=+4.6166240692e+01f;
   // x^ : +0xb.17218p-9f
    constexpr
    const float _ln2_32_h=+2.1660849452e-02f;
    // x^ : -0x8.2e308p-37f
    constexpr
    const float _ln2_32_l=-5.9520444129e-11f;
#if 0
    vf_type kf = rint(vf_type(xh * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xh32ln2=xh*_32_ln2;
    vf_type kf= rint(xh32ln2);
    vi_type ki=_T::cvt_f_to_i(xh32ln2);
#endif
    idx = ki & int32_t(exp_data<float>::EXP_IDX_MASK);
    k = ki >> int32_t(exp_data<float>::EXP_SHIFT);
    vf_type neg_kfln2h, neg_kfln2l;
    d_ops::unorm_mul122(neg_kfln2h, neg_kfln2l,
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
exp_k(arg_t<vf_type> x)
{
    vf_type xrh, xrl;
    vf_type y;
    if (_EXP_M1==false) {
#if 0
        vf_type kf;
        __reduce_exp_arg(xrh, xrl, kf, x);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf, vmf_type());
#else
        vi_type idx, ki;
        __reduce_exp_arg(xrh, xrl, idx, ki, x);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
#endif
    } else {
        vf_type kf;
        __reduce_exp_arg(xrh, xrl, kf, x);
        vmf_type x_small = abs(x) < 0x1p-24f;
        xrh = _T::sel(x_small, x, xrh);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf, x_small);
    }
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
exp_k2(vf_type& __restrict eh, vf_type& __restrict el,
       arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, xh, xl);
    eh=__exp_tbl_k(xrh, xrl, idx, ki, &el);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp_mx2_k(arg_t<vf_type> xc)
{
    vf_type y;
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
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
    vf_type y;
    using fc_t = math::func_constants<float>;
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);
    vmf_type border_case = (x2h == fc_t::exp_hi_inf()) &
        (x2l < 0.0);
    vf_type t= 0x1.01p-17f;
    x2h = _T::sel(border_case, x2h - t, x2h);
    x2l = _T::sel(border_case, x2l + t, x2l);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
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
    constexpr const float _1_ND=1.0f/float(exp_data<float>::EXP_N);
#if 0
    vf_type kf= rint(vf_type(x*_ND));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xnd=x*_ND;
    vf_type kf= rint(xnd);
    vi_type ki=_T::cvt_f_to_i(xnd);
#endif
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    vf_type xr= x- kf*_1_ND;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    // d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0]);
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
    constexpr const float _ND=exp_data<float>::EXP_N;
    constexpr const float _1_ND=1.0f/float(exp_data<float>::EXP_N);
#if 0
    vf_type kf= rint(vf_type(xh*_ND));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xhnd=xh*_ND;
    vf_type kf= rint(xhnd);
    vi_type ki=_T::cvt_f_to_i(xhnd);
#endif
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
    vf_type y;
    vf_type xrh, xrl;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    if (_EXP2_M1==false) {
        vi_type idx, ki;
        __reduce_exp2_arg(xrh, xrl, idx, ki, x);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
    } else {
        vf_type kf= rint(vf_type(x));
        vf_type xr = x - kf;
        const float x_small_v=0x1p-24f/ctbl::m_ln2[0];
        vmf_type x_small = abs(x) < x_small_v;
        xr = _T::sel(x_small, x*0x1p24f, xr);
        // for exp2 mul12 would be sufficient
        d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
        xrh = _T::sel(x_small, xrh*0x1p-24f, xrh);
        xrh = _T::sel(iszero(x), x, xrh);
        y=__exp_k<_EXP2_M1>(xrh, xrl, kf, x_small);
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp2_mx2_k(arg_t<vf_type> xc)
{
    vf_type y;
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
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
    vf_type y;
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
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
    constexpr
    const float _32_lg2=+1.0630169678e+02f;
    // x^ : +0x9.a2p-10f
    constexpr
    const float _lg2_32_cw_h=+9.4070434570e-03f;
    // x^ : +0x9.a84fcp-26f
    constexpr
    const float _lg2_32_cw_l=+1.4390747083e-07f;
#if 0
    vf_type kf= rint(vf_type(x*_32_lg2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type x32lg2=x*_32_lg2;
    vf_type kf= rint(x32lg2);
    vi_type ki=_T::cvt_f_to_i(x32lg2);
#endif
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    vf_type hi = x - kf * _lg2_32_cw_h;
    xrh = hi - kf * _lg2_32_cw_l;
    vf_type dx= hi-xrh;
    vf_type cr = dx- kf * _lg2_32_cw_l;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    d_ops::mul122(xrh, xrl, xrh, ctbl::m_ln10[0], ctbl::m_ln10[1]);
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
    constexpr
    const float _32_lg2=+1.0630169678e+02f;
    // x^ : +0x9.a209bp-10f
    constexpr
    const float _lg2_32_h=+9.4071878120e-03f;
    // x^ : -0xf.6086p-35f
    constexpr
    const float _lg2_32_l=-4.4753090123e-10f;
    using ctbl = impl::d_real_constants<d_real<float>, float>;
#if 0
    vf_type kf = rint(vf_type(xh*_32_lg2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xh32lg2=xh*_32_lg2;
    vf_type kf= rint(xh32lg2);
    vi_type ki=_T::cvt_f_to_i(xh32lg2);
#endif
    idx= ki & exp_data<float>::EXP_IDX_MASK;
    k= ki >> exp_data<float>::EXP_SHIFT;
    vf_type kf_lg_2_32_h, kf_lg_2_32_l;
    d_ops::unorm_mul122(kf_lg_2_32_h, kf_lg_2_32_l,
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
    vf_type y;
    vf_type xrh, xrl;
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
        const float x_small_v=0x1p-24f/ctbl::m_ln10[0];
        vmf_type x_small = abs(x) < x_small_v;
        xr = _T::sel(x_small, x*0x1p24f, xr);
        // for exp10 mul12 would be sufficient
        d_ops::mul122(xrh, xrl, xr, ctbl::m_ln10[0], ctbl::m_ln10[1]);
        xrl += cr * ctbl::m_ln10[0];
        // do not normalize xrh, xrl
        // d_ops::add12(xrh, xrl, xrh, xrl);
        xrh = _T::sel(x_small, xrh*0x1p-24f, xrh);
        xrh = _T::sel(iszero(x), x, xrh);
        y=__exp_k<_EXP10_M1>(xrh, xrl, kf, x_small);
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
exp10_mx2_k(arg_t<vf_type> xc)
{
    vf_type y;
    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp10_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
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
    vf_type y;
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp10_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
    using fc_t = math::func_constants<float>;
    y= _T::sel(x2h >= fc_t::exp10_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
sig_k(arg_t<vf_type> x)
{
    using fc= func_constants<float>;
    constexpr const float lgf_lo_eq_exp= fc::sig_le_eq_exp();
    vmf_type xm= x>lgf_lo_eq_exp;
    vf_type xe= _T::sel(xm, -x, x);
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, xe);
    vf_type el, eh=
        __exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &el);
    auto sc=__two_pow(ki);
    eh *= sc.f0();
    eh *= sc.f1();
    constexpr const float lgf_hi_one=  fc::sig_hi_one();
    vmf_type x_not_hi= x < lgf_hi_one;
    vf_type rh, rl;
    // avoid multiplication of subnormal numbers
    vmf_type avoid_sn= xm & x_not_hi;
    vf_type th=_T::sel_val_or_zero(avoid_sn, eh);
    vf_type tl=_T::sel_val_or_zero(avoid_sn, el);
    tl *= sc.f0();
    tl *= sc.f1();
    d_ops::add122cond(rh, rl, float(1.0), th, tl);
    d_ops::rcp21(rh, rh, rl);
    vf_type r = _T::sel(xm, rh, eh);
    r = _T::sel(x_not_hi, r, float(1.0));
    return r;
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
    vf_type res;
#if 1
    vmf_type x_small;
    // x^ : +0x8p-3f
    constexpr
    const float sinh_i0_right=+1.0000000000e+00f;
    if (_F == hyperbolic_func::c_sinh) {
        x_small= x <= sinh_i0_right;
        if (__unlikely(_T::any_of_vmf(x_small))) {
            // [0, 1] : | p - f | <= 2^-32.03125
            // coefficients for sinh generated by sollya
            // x^1 : +0x8p-3f
            constexpr
            const float sinh_c1=+1.0000000000e+00f;
            // x^3 : +0xa.aaaabp-6f
            constexpr
            const float sinh_c3=+1.6666667163e-01f;
            // x^5 : +0x8.88875p-10f
            constexpr
            const float sinh_c5=+8.3333151415e-03f;
            // x^7 : +0xd.00e11p-16f
            constexpr
            const float sinh_c7=+1.9841665926e-04f;
            // x^9 : +0xb.b3b8fp-22f
            constexpr
            const float sinh_c9=+2.7899839097e-06f;
            static_assert(sinh_c1==1.0, "constraint violated");

            constexpr
            static const float cs[]= {
                sinh_c9, sinh_c7, sinh_c5
            };
            vf_type xs2, xs2l;
            d_ops::sqr12(xs2, xs2l, x);
            vf_type p= horner2(xs2, vf_type(xs2*xs2), cs);
            vf_type yh, yl;
            horner_comp_quick(yh, yl, xs2, p, sinh_c3);
            d_ops::mul22(yh, yl, yh, yl, xs2, xs2l);
            d_ops::unorm_mul122(yh, yl, x, yh, yl);
            vf_type e1;
            d_ops::add12(yh, e1, x, yh);
            yl += e1;
            res= yh + yl;
        }
    }
    // x^ : +0x8p-3f
    constexpr
    const float cosh_i0_right=+1.0000000000e+00f;
    if (_F == hyperbolic_func::c_cosh) {
        x_small= x <= cosh_i0_right;
        if (__unlikely(_T::any_of_vmf(x_small))) {
            // [0, 1] : | p - f | <= 2^-35.4375
            // coefficients for cosh generated by sollya
            // x^0 : +0x8p-3f
            constexpr
            const float cosh_c0=+1.0000000000e+00f;
            // x^2 : +0x8p-4f
            constexpr
            const float cosh_c2=+5.0000000000e-01f;
            // x^4 : +0xa.aaaabp-8f
            constexpr
            const float cosh_c4=+4.1666667908e-02f;
            // x^6 : +0xb.60b38p-13f
            constexpr
            const float cosh_c6=+1.3888841495e-03f;
            // x^8 : +0xd.01653p-19f
            constexpr
            const float cosh_c8=+2.4805927751e-05f;
            // x^10 : +0x9.49cf6p-25f
            constexpr
            const float cosh_c10=+2.7681352321e-07f;

            static_assert(cosh_c0==1.0f, "constraint violated");
            static_assert(cosh_c2==0.5f, "constraint violated");

            vf_type xs2, xs2l;
            d_ops::sqr12(xs2, xs2l, x);
#if 0
            constexpr
            static const float cs[]= {
                cosh_c16, cosh_c14, cosh_c12, cosh_c10, cosh_c8,
                cosh_c6
            };
            vf_type xs4, xs4l;
            d_ops::sqr22(xs4, xs4l, xs2, xs2l);
            vf_type p=horner(xs2, cs);
            vf_type ph, pl;
            horner_comp_quick(ph, pl, xs2, p, cosh_c4);
            d_ops::unorm_mul22(ph, pl, ph, pl, xs4, xs4l);
#else
            // less precision and but faster
            constexpr
            static const float cs[]= {
                cosh_c10, cosh_c8, cosh_c6, cosh_c4
            };
            vf_type xs4, xs4l;
            d_ops::sqr22(xs4, xs4l, xs2, xs2l);
            vf_type p=horner(xs2, cs);
            vf_type ph, pl;
            d_ops::unorm_mul122(ph, pl, p, xs4, xs4l);
#endif
            vf_type cm1h=cosh_c2 * xs2;
            vf_type cm1l=cosh_c2 * xs2l;
            vf_type e1;
            d_ops::add12(cm1h, e1, cm1h, ph);
            vf_type e2;
            d_ops::add12(cm1h, e2, cm1h, pl);
            cm1l += (e1 + e2);
            vf_type yh, yl;
            d_ops::add12(yh, yl, cosh_c0, cm1h);
            yl += cm1l;
            res = yh + yl;
        }
    }
    if (__likely(!_T::all_of_vmf(x_small))) {
        vf_type xrh, xrl;
        vi_type k, idx;
        __reduce_exp_arg(xrh, xrl, idx, k, x);
        vi_type k0=k;
        // 1/2
        k -= 1;

        vf_type yh, yl;
        yh = __exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &yl);
        auto sc=__two_pow(k);
        yh *= sc.f0();
        yh *= sc.f1();
        // fpprec: 32
        // bfloat(rhs(solve(2^-30*%e^x=%e^(-x), x)[2]));
        constexpr const float
        x_medium_max = 1.0397207708399179641258481821873e1f;
        vmf_type x_medium= x <= x_medium_max;
        if (_F == hyperbolic_func::c_sinh)
            x_medium &= (x > sinh_i0_right);
        if (_F == hyperbolic_func::c_cosh)
            x_medium &= (x > cosh_i0_right);
        if (__likely(_T::any_of_vmf(x_medium))) {
            // perform the scaling also for the low part
            yl *= sc.f0();
            yl *= sc.f1();
#if 0
            // slower than the lookups
            vf_type nyh, nyl;
            float dv= _F == hyperbolic_func::c_sinh ? -0.25 : 0.25;
            d_ops::div122(nyh, nyl, dv, yh, yl);
            static_cast<void>(k0);
#else
            vf_type nxrh, nxrl;
            vi_type nk, nidx;
            // base_type::__reduce_exp_arg(nxrh, nxrl, nidx, nk, -x);
            nxrh = -xrh;
            nxrl = -xrl;
            vi_type s=-((k0<<exp_data<float>::EXP_SHIFT)+idx);
            nk = s >> exp_data<float>::EXP_SHIFT;
            nidx = s & exp_data<float>::EXP_IDX_MASK;

            nk -= 1;
            vf_type nyh, nyl;
            nyh = __exp_tbl_k<result_prec::medium>(nxrh, nxrl, nidx, &nyl);
            // we know k < 14
            // create the scaling factor, produce a negative sign
            // for sinh because we want to subtract %e^-x
            const int32_t bias_with_sgn=
                _F == hyperbolic_func::c_sinh ? _T::bias()+256 : _T::bias();
            vf_type nsc=_T::insert_exp(bias_with_sgn + nk);
            nyh *= nsc;
            nyl *= nsc;
#endif
            vf_type zh, zl;
            d_ops::add12(zh, zl, yh, nyh);
            zh += (zl + yl + nyl);
            yh = _T::sel(x_medium, zh, yh);
        }
        res=_T::sel(x_small, res, yh);
    }
    if (_F==hyperbolic_func::c_sinh) {
        res = copysign(res, xc);
    }
    return res;
#else
    vmf_type x_tiny;
    // x^ : +0xb.17218p-6f
    constexpr
    const float sinh_i0_right=+1.7328679562e-01f;

    if (_F == hyperbolic_func::c_sinh) {
        x_tiny= x <= sinh_i0_right;
        if (__unlikely(_T::any_of_vmf(x_tiny))) {
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
            res = yt;
        }
    }
    if (_F == hyperbolic_func::c_cosh || __likely(!_T::all_of_vmf(x_tiny))) {
        vf_type xrh, xrl;
        vi_type k, idx;
        __reduce_exp_arg(xrh, xrl, idx, k, x);
        vi_type k0=k;

        // 1/2
        k -= 1;
        vf_type yh, yl;
        yh = __exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &yl);

        auto sc=__two_pow(k);
        yh *= sc.f0();
        yh *= sc.f1();

        // fpprec: 32
        // bfloat(rhs(solve(2^-30*%e^x=%e^(-x), x)[2]));
        constexpr const float
        x_medium_max = 1.0397207708399179641258481821873e1;
        vmf_type x_medium= x <= x_medium_max;
        if (_F == hyperbolic_func::c_sinh)
            x_medium &= (x > sinh_i0_right);
        if (__likely(_T::any_of_vmf(x_medium))) {
            // perform the scaling also for the low part
            yl *= sc.f0();
            yl *= sc.f1();
#if 0
            // slower than the lookups
            vf_type nyh, nyl;
            float dv= _F == hyperbolic_func::c_sinh ? -0.25f : 0.25f;
            d_ops::div122(nyh, nyl, dv, yh, yl);
            static_cast<void>(k0);
#else
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
            // create the scaling factor, produce a negative sign
            // for sinh because we want to subtract %e^-x
            const int32_t bias_with_sgn=
                _F == hyperbolic_func::c_sinh ? _T::bias()+256 : _T::bias();
            vf_type nsc=_T::insert_exp(bias_with_sgn + nk);
            nyh *= nsc;
            nyl *= nsc;
#endif
            vf_type zh, zl;
            d_ops::add12(zh, zl, yh, nyh);
            zh += (zl + yl + nyl);
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
#endif
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
    if (__unlikely(_T::any_of_vmf(x_tiny))) {
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
    if (__likely(_T::any_of_vmf(x_medium))) {
        constexpr const float tmax=2.0*fc::tanh_one();
        vf_type xae=min(vf_type(xa+xa), vf_type(tmax));
        vf_type xrh, xrl;
        vi_type idx, ki;
        __reduce_exp_arg(xrh, xrl, idx, ki, xae);
        vf_type ex, exl;
        ex=__exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &exl);
        auto sc=_T::insert_exp(_T::bias() + ki);
        ex  *= sc;
        exl *= sc;

        vf_type exm1, exm1l;
        d_ops::add212(exm1, exm1l, ex, exl, -1.0f);
        vf_type exp1, exp1l;
        d_ops::add212(exp1, exp1l, ex, exl, 1.0f);
        vf_type tanh_h;
        d_ops::div21(tanh_h, exm1, exm1l, exp1, exp1l);
        tanh_x = _T::sel(x_medium, tanh_h, tanh_x);
    }
    tanh_x=copysign(tanh_x, xc);
    return tanh_x;
}


template <typename _T>
typename
cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_log_arg(vf_type& xr,
                 arg_t<vf_type> xc)
{
    // MSQRT2/2
    constexpr
    const bytes4 offs=0x3f3504f3;

    using fc = func_constants<float>;
    vmf_type is_denom=xc < fc::min_normal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                         vi_type(-25-_T::bias()),
                         vi_type(-_T::bias()));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    constexpr const int32_t delta=0x3f800000 - offs.s32();
    hx += delta;
    k += (hx>>23);
    hx = (hx&0x007fffff) + offs.s32();
    xr = _T::as_float(hx);
    return k;
}

template <typename _T>
inline
typename
cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_log_arg(vf_type& xr,
                 vi_type& idx,
                 arg_t<vf_type> xc)

{
    constexpr
    const bytes4 offs=0x3f340000;
    using fc = func_constants<float>;
    vmf_type is_denom=xc < fc::min_normal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                         vi_type(-25-_T::bias()),
                         vi_type(-_T::bias()));
    vi_type hx = _T::as_int(x);
    // reduce x into [offs, 2*offs]
    constexpr const int32_t delta=0x3f800000 - offs.s32();
    hx += delta;
    k += (hx>>23);
    vi_type m = (hx&0x007fffff);
    hx = m + offs.s32();
    idx=(m >> (23-pow_log_data<float>::LOG_SHIFT));
    xr = _T::as_float(hx);
    return k;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__log_poly_k_poly(arg_t<vf_type> r, arg_t<vf_type> r2)
{
    // [-0.292893230915069580078125, 0.4142135679721832275390625] : | p - f | <= 2^-31.90625
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_c1=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    constexpr
    const float log_c2=-5.0000000000e-01f;
    // x^3 : +0xa.aaaa3p-5f
    constexpr
    const float log_c3=+3.3333310485e-01f;
    // x^4 : -0x8.00002p-5f
    constexpr
    const float log_c4=-2.5000005960e-01f;
    // x^5 : +0xc.cd2a4p-6f
    constexpr
    const float log_c5=+2.0002228022e-01f;
    // x^6 : -0xa.aaebep-6f
    constexpr
    const float log_c6=-1.6668221354e-01f;
    // x^7 : +0x9.1974bp-6f
    constexpr
    const float log_c7=+1.4217869937e-01f;
    // x^8 : -0xf.dfab7p-7f
    constexpr
    const float log_c8=-1.2401335686e-01f;
    // x^9 : +0xf.39c7cp-7f
    constexpr
    const float log_c9=+1.1895081401e-01f;
    // x^10 : -0xe.fa013p-7f
    constexpr
    const float log_c10=-1.1700453609e-01f;
    // x^11 : +0x8.a773bp-7f
    constexpr
    const float log_c11=+6.7610226572e-02f;
    static_assert(log_c1==1.0f, "constraint violated");
    static_assert(log_c2==-0.5f, "constraint violated");
    constexpr
    static const float ci[]={
        log_c11, log_c10,
        log_c9, log_c8, log_c7, log_c6,
        log_c5, log_c4, log_c3
    };
#if 1
    vf_type p= horner2(r, r2, ci);
#else
    vf_type r4=r2*r2;
    vf_type p= horner4(r, r2, r4, ci);
#endif
    return p;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__log_poly_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0f;

    // log(x) = kf*ln2 + r + r2*c2 + r3*p
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type l, e;
    d_ops::add12(l, e, kf* ctbl::m_ln2_cw[0], r);
    constexpr const float log_c2 = -0.5f;
    e += log_c2*r2l;
    vf_type r2c2=log_c2 * r2;
    vf_type ei;
    d_ops::add12(l, ei, l, r2c2);
    e += ei;
    d_ops::add12(l, ei, l, kf*ctbl::m_ln2_cw[1]);
    e += ei;
#if 0
    d_ops::add12(l, ei, l, r2*(r*p));
    e += ei;
    vf_type ll=e;
#else
    vf_type ll=e + r2*(r*p);
#endif
    return l+ll;
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<float, _T>::vdf_type
cftal::math::elem_func_core<float, _T>::
__log_tbl_k2(arg_t<vf_type> r, arg_t<vf_type> rl,
             arg_t<vf_type> log_c_h, arg_t<vf_type> log_c_l,
             arg_t<vf_type> kf)
{
   // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-46.703125
    // coefficients for log_hp generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_hp_c1=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    constexpr
    const float log_hp_c2=-5.0000000000e-01f;
    // x^3 : +0xa.aaaabp-5f
    constexpr
    const float log_hp_c3=+3.3333334327e-01f;
    // x^4 : -0x8p-5f
    constexpr
    const float log_hp_c4=-2.5000000000e-01f;
    // x^5 : +0xc.cc8d7p-6f
    constexpr
    const float log_hp_c5=+1.9998489320e-01f;
    // x^6 : -0xa.ab18ep-6f
    constexpr
    const float log_hp_c6=-1.6669294238e-01f;
    static_assert(log_hp_c1 == 1.0f);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type ph, pl;
    if (_P == result_prec::high) {
        constexpr
        static const float ci[]={
            log_hp_c6, log_hp_c5, log_hp_c4, log_hp_c3
        };
        vf_type p=horner(r, ci);
        horner_comp_quick(ph, pl, r, p, log_hp_c2);
        d_ops::unorm_mul22(ph, pl, r, rl, ph, pl);
        d_ops::add122(ph, pl, log_hp_c1, ph, pl);
    } else {
        // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-34.875
        // coefficients for log generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float log_c1=+1.0000000000e+00f;
        // x^2 : -0x8p-4f
        constexpr
        const float log_c2=-5.0000000000e-01f;
        // x^3 : +0xa.abp-5f
        constexpr
        const float log_c3=+3.3337402344e-01f;
        // x^4 : -0x8.0048bp-5f
        constexpr
        const float log_c4=-2.5003466010e-01f;

        constexpr
        static const float ci[]={
            log_c4, log_c3, log_c2
        };
        vf_type p=horner(r, ci);
        d_ops::muladd12(ph, pl, log_c1, p, r);
    }
    vf_type lh, ll;
    d_ops::unorm_mul22(lh, ll, r, rl, ph, pl);
    vf_type kh, kl;
    d_ops::unorm_mul122(kh, kl, kf, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    d_ops::add22(lh, ll, log_c_h, log_c_l, lh, ll);
    // |kh, kl | >= log(2) or 0
    d_ops::add22(lh, ll, kh, kl, lh, ll);
    return vdf_type(lh, ll);
}

template <typename _T>
template <typename cftal::math::elem_func_core<float, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<float, _T>::vdf_type
cftal::math::elem_func_core<float, _T>::
__log_tbl_k2(arg_t<vf_type> xc, arg_t<vf_type> xcl)
{
    vf_type xrh, inv_c, log_c_h, log_c_l;
    vi_type idx;
    vi_type ki=__reduce_log_arg(xrh, idx, xc);
    auto lck=make_variable_lookup_table<float>(idx);
    const auto& tbl=pow_log_data<float>::_tbl;
    inv_c =lck.from(tbl._p_inv_c);
    log_c_h=lck.from(tbl._p_log_c_h);
    log_c_l=lck.from(tbl._p_log_c_l);
    auto sc=__two_pow(-ki);
    vf_type xrl = xcl * sc.f0() * sc.f1();
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r, rl;
    if (d_real_traits<vf_type>::fma == true) {
        r = xrh * inv_c - 1.0f;
        rl = xrl * inv_c;
    } else {
        vf_type xrhh, xrhl;
        d_real_traits<vf_type>::split(xrh, xrhh, xrhl);
        xrhh *= inv_c;
        xrhl *= inv_c;
        xrhh -= 1.0f;
        r = xrhh + xrhl;
        rl = xrl * inv_c;
    }
    d_ops::add12cond(r, rl, r, rl);
    return __log_tbl_k2<_P>(r, rl, log_c_h, log_c_l, kf);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vdf_type
cftal::math::elem_func_core<float, _T>::
__log_tbl_k12(arg_t<vf_type> xc)
{
    vf_type xr, inv_c, log_c_h, log_c_l;
    vi_type idx;
    vi_type ki=__reduce_log_arg(xr, idx, xc);
    auto lck=make_variable_lookup_table<float>(idx);
    const auto& tbl=pow_log_data<float>::_tbl;
    inv_c =lck.from(tbl._p_inv_c);
    log_c_h=lck.from(tbl._p_log_c_h);
    log_c_l=lck.from(tbl._p_log_c_l);
    vf_type kf=_T::cvt_i_to_f(ki);

    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type r;
    vf_type rh, rl;
    if (d_real_traits<vf_type>::fma == true) {
        r = xr * inv_c - 1.0f;
    } else {
        d_real_traits<vf_type>::split(xr, rh, rl);
        rh *= inv_c;
        rl *= inv_c;
        rh -= 1.0f;
        r = rh + rl;
    }
    // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-41.53125
    // coefficients for log_hp generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_hp_c1=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    constexpr
    const float log_hp_c2=-5.0000000000e-01f;
    // x^3 : +0xa.aaaabp-5f
    constexpr
    const float log_hp_c3=+3.3333334327e-01f;
    // x^4 : -0x8.004abp-5f
    constexpr
    const float log_hp_c4=-2.5003561378e-01f;
    // x^5 : +0xc.cc8a7p-6f
    constexpr
    const float log_hp_c5=+1.9998417795e-01f;
    static_assert(log_hp_c1 == 1.0f);
    static_assert(log_hp_c2 ==-0.5f);
    constexpr
    static const float ci[]={
        log_hp_c5, log_hp_c4, log_hp_c3
    };
    vf_type r2=r*r;
    vf_type p=horner2(r, r2, ci);

    // thanks to the glibc developers for the lesson:
    vf_type t1, t;
    d_ops::add12(t1, t, kf* ctbl::m_ln2_cw[0], log_c_h);
    vf_type t2= t1 + r;
    vf_type l1= kf* ctbl::m_ln2_cw[1] + t + log_c_l;
    // error of t2:
    vf_type l2= t1 - t2 + r;
    // exact because |log_c2| is a power of 2:
    vf_type ar=log_hp_c2 * r;
    vf_type ar2=r*ar;
    vf_type r3=r*r2;

    vf_type h, l3, l4;
    if (d_real_traits<vf_type>::fma == true) {
        h = t2 + ar2;
        // error of ar2
        l3 = ar* r - ar2;
        // error of h:
        l4 = t2 - h + ar2;
    } else {
        vf_type arh= log_hp_c2 * rh;
        vf_type arh2= rh * arh;
        h = t2+ arh2;
        l3 = rl* (ar + arh);
        l4 = t2 - h + arh2;
    }
    vf_type l=(l1+l2+l3+l4)+r3*p;
    vf_type lh= h + l;
    vf_type ll= h - lh + l;
    return vdf_type(lh, ll);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__log1p_poly_k(arg_t<vf_type> xc)
{
    vf_type x=xc;
    vf_type u=1.0f+xc;
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, u);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0f;

#if 1
    // log(x) = kf*ln2 + r + r2*c2 + r3*p
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type l, e;
    d_ops::add12(l, e, kf* ctbl::m_ln2_cw[0], r);
    constexpr const float log_c2 = -0.5f;
    e += log_c2*r2l;
    vf_type r2c2=log_c2 * r2;
    vf_type ei;
    d_ops::add12(l, ei, l, r2c2);
    e += ei;
    d_ops::add12(l, ei, l, kf*ctbl::m_ln2_cw[1]);
    e += ei;

    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-x), x-(u-1.0f));
    c_k_2 /= u;
    // vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    vf_type c = c_k_2;

    d_ops::add12(l, ei, l, c);
    e += ei;
    vf_type ll=e + r2*(r*p);
    return l+ll;
#else
    vf_type r2=r*r;
    vf_type p=__log_poly_k_poly(r, r2);
    p = horner(r, p, -0.5f);

    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-x), x-(u-1.0f));
    c_k_2 /= u;
    // vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    vf_type c = c_k_2;

    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type lh, ll;
    d_ops::add12(lh, ll, kf*ctbl::m_ln2_cw[0], r);
    lh+= p*r2+(c+(ll + kf * ctbl::m_ln2_cw[1]));
    return lh;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log1p_k(arg_t<vf_type> xc)
{
    return __log1p_poly_k(xc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log_k(arg_t<vf_type> xc)
{
    // return __log_tbl_k<log_func::c_log_e>(xc);
    return __log_poly_k(xc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__mul_invln2_add_kf(arg_t<vf_type> l,
                    arg_t<vf_type> ll,
                    arg_t<vf_type> kf)
{
    // x^ : +0xb.8bp-3f
    constexpr
    const float invln2hi=+1.4428710938e+00f;
    // x^ : -0xb.89ad4p-16f
    constexpr
    const float invln2lo=-1.7605285393e-04f;
    vf_type l0, l1;
    vf_type l2, l3;
    if (d_real_traits<vf_type>::fma==true) {
        l0 = l * invln2hi;
        vf_type l0_e= l*invln2hi-l0;
        l1 = l * invln2lo + l0_e;
        l2 = ll * invln2hi;
        vf_type l2_e= ll*invln2hi-l2;
        l3 = ll * invln2lo + l2_e;
    } else {
        d_real_traits<vf_type>::split(l, l0, l1);
        l0 = l0 * invln2hi;
        l1 = (l1 * invln2hi) + l* invln2lo;
        d_real_traits<vf_type>::split(ll, l2, l3);
        l2 = l2 * invln2hi;
        l3 = (l3 * invln2hi) + ll* invln2lo;
    }
    vf_type res, t;
    d_ops::add12(res, t, kf, l0);
    res += t +(l1+l2+l3);
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log2_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0f;

    // log2(x) = kf + (r + r2*c2 + r3*p)/ln2;
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    constexpr const float log_c2=-0.5f;
    vf_type l= log_c2*r2;
    vf_type ei;
    d_ops::add12(l, ei, r, l);
    vf_type ll=(ei + log_c2*r2l) + r2*(r*p);
    vf_type res=__mul_invln2_add_kf(l, ll, kf);
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log2p1_k(arg_t<vf_type> xc)
{
    vf_type u=1.0f+xc;
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, u);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0f;

    // log2p1(x) = kf + (r + r2*c2 + r3*p)/ln2
    vf_type abs_xc= abs(xc);
    vmf_type xc_near_zero=abs_xc < 0x1p-3f;
    r = _T::sel(xc_near_zero, xc, r);

    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);

    constexpr const float log_c2 = -0.5f;
    vf_type l, e;
    vf_type r2c2=log_c2 * r2;
    d_ops::add12(l, e, r, r2c2);
    e += log_c2*r2l;
    // assume y == xrh, x == xrl:
    // f(x) := log(1+y+x);
    // f(x) := log(1 + y + x)
    // taylor(f(x), x, 0, 1);
    //                      x
    // /T/   log(y + 1) + ----- + . . .
    ///                   y + 1
    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-xc), xc-(u-1.0f));
    c_k_2 /= u;
    // vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    vf_type c = _T::sel_zero_or_val(xc_near_zero, c_k_2);

    vf_type ei;
    d_ops::add12(l, ei, l, c);
    e += ei;
    vf_type ll=e + r2*(r*p);

    vmf_type xc_tiny= abs_xc <
        0x1p2f*func_constants<float>::min_normal();
    l = _T::sel(xc_tiny, xc*0x1p24f, l);
    ll = _T::sel_zero_or_val(xc_tiny, ll);
    vf_type res=__mul_invln2_add_kf(l, ll, kf);
    res = _T::sel(xc_tiny, res*0x1p-24f, res);
    res= _T::sel(iszero(xc), xc, res);

    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
__mul_invln10_add_kflg2(arg_t<vf_type> l,
                        arg_t<vf_type> ll,
                        arg_t<vf_type> kf)
{
    // x^ : +0xd.e6p-5f
    constexpr
    const float invln10hi=+4.3432617188e-01f;
    // x^ : -0x8.4ead9p-18f
    constexpr
    const float invln10lo=-3.1689971365e-05f;

    vf_type l0, l1;
    vf_type l2, l3;
    if (d_real_traits<vf_type>::fma==true) {
        l0 = l * invln10hi;
        vf_type l0_e= l*invln10hi-l0;
        l1 = l * invln10lo + l0_e;
        l2 = ll * invln10hi;
        vf_type l2_e= ll*invln10hi-l2;
        l3 = ll * invln10lo + l2_e;
    } else {
        d_real_traits<vf_type>::split(l, l0, l1);
        l0 = l0 * invln10hi;
        l1 = (l1 * invln10hi) + l* invln10lo;
        d_real_traits<vf_type>::split(ll, l2, l3);
        l2 = l2 * invln10hi;
        l3 = (l3 * invln10hi) + ll* invln10lo;
    }
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type res, t;
    d_ops::add12(res, t, kf*ctbl::m_lg2_cw[0], l0);
    res += (t +(l1+l2+l3)) + kf * ctbl::m_lg2_cw[1];
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log10_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0f;

    // log10(x) = kf*lg(2) + (r + r2*c2 + r3*p)/ln10;
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    constexpr const float log_c2=-0.5f;
    vf_type l= log_c2*r2;
    vf_type ei;
    d_ops::add12(l, ei, r, l);
    vf_type ll=(ei + log_c2*r2l) + r2*(r*p);
    vf_type res=__mul_invln10_add_kflg2(l, ll, kf);
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
log10p1_k(arg_t<vf_type> xc)
{
    vf_type u=1.0f+xc;
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, u);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0f;

    vf_type abs_xc=abs(xc);
    vmf_type xc_near_zero=abs_xc < 0x1p-3f;
    r = _T::sel(xc_near_zero, xc, r);

    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);

    constexpr const float log_c2 = -0.5f;
    vf_type l, e;
    vf_type r2c2=log_c2 * r2;
    d_ops::add12(l, e, r, r2c2);
    e += log_c2*r2l;
    // assume y == xrh, x == xrl:
    // f(x) := log(1+y+x);
    // f(x) := log(1 + y + x)
    // taylor(f(x), x, 0, 1);
    //                      x
    // /T/   log(y + 1) + ----- + . . .
    ///                   y + 1
    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-xc), xc-(u-1.0f));
    c_k_2 /= u;
    // vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    vf_type c = _T::sel_zero_or_val(xc_near_zero, c_k_2);

    vf_type ei;
    d_ops::add12(l, ei, l, c);
    e += ei;
    vf_type ll=e + r2*(r*p);

    vmf_type xc_tiny= abs_xc <
        0x1p2f*func_constants<float>::min_normal();
    l = _T::sel(xc_tiny, xc*0x1p24f, l);
    ll = _T::sel_zero_or_val(xc_tiny, ll);
    vf_type res =__mul_invln10_add_kflg2(l, ll, kf);
    res = _T::sel(xc_tiny, res*0x1p-24f, res);
    res= _T::sel(iszero(xc), xc, res);

    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type abs_x= abs(x);
    vdf_type lnx= __log_tbl_k12(abs_x);

    vdf_type ylnx;
    d_ops::mul122(ylnx[0], ylnx[1], y, lnx[0], lnx[1]);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, ylnx[0], ylnx[1]);
    vf_type res=__exp_tbl_k(xrh, xrl, idx, ki);

    using fc=func_constants<float>;
    const vf_type& dh = ylnx[0];
    const vf_type& dl = ylnx[1];
    constexpr
    const float exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(
        (dh < exp_lo_zero) | ((dh == exp_lo_zero) & (dl <= 0.0f)),
        res);
    constexpr
    const float exp_hi_inf= fc::exp_hi_inf();
    res = _T::sel(
        (dh > exp_hi_inf) | ((dh == exp_hi_inf) & (dl >= 0.0f)),
        _T::pinf(), res);
    // guess the result if the calculation failed
    vmf_type rnan=isnan(dh);
    vmf_type abs_x_lt_1 = abs_x < 1.0f;
    vmf_type y_gt_1 = y > 1.0f;
    res = _T::sel(rnan, _T::pinf(), res);
    res = _T::sel_zero_or_val(rnan &
                              ((abs_x_lt_1 & y_gt_1) |
                               ((~abs_x_lt_1) & (~y_gt_1))),
                              res);
    return res;
}

template <typename _T>
typename cftal::math::elem_func_core<float, _T>::pow_k2_result
cftal::math::elem_func_core<float, _T>::
pow_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
       arg_t<vf_type> yh, arg_t<vf_type> yl)
{
    vdf_type abs_x= select(xh > 0.0f, vdf_type(xh, xl), vdf_type(-xh, -xl));
    vdf_type lnx = __log_tbl_k2<result_prec::normal>(abs_x[0], abs_x[1]);
    vdf_type ylnx;
    d_ops::mul22(ylnx[0], ylnx[1], yh, yl, lnx[0], lnx[1]);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, ylnx[0], ylnx[1]);
    vf_type rl;
    vf_type rh=__exp_tbl_k<result_prec::medium>(xrh, xrl, idx, &rl);
    auto sc = __two_pow(ki);
    return std::make_pair(vdf_type(rh, rl), sc);
}

template <typename _T>
template <bool _CALC_ROOT>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
powi_k(arg_t<vf_type> x, arg_t<vi_type> e)
{
    vf_type abs_x= abs(x);
    vdf_type lnx= __log_tbl_k12(abs_x);
    vi_type eh=e & 0xffff0000, el= e - eh;
    vf_type yh=_T::cvt_i_to_f(eh);
    vf_type yl=_T::cvt_i_to_f(el);
    d_ops::add12(yh, yl, yh, yl);
    vdf_type ylnx;
    if (_CALC_ROOT==true) {
        vf_type rh, rl;
        d_ops::rcp2(rh, rl, yh, yl);
        d_ops::unorm_mul22(ylnx[0], ylnx[1], lnx[0], lnx[1], rh, rl);
    } else {
        d_ops::mul22(ylnx[0], ylnx[1], yh, yl, lnx[0], lnx[1]);
    }

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, ylnx[0], ylnx[1]);
    vf_type res=__exp_tbl_k(xrh, xrl, idx, ki);

    using fc=func_constants<float>;
    const vf_type& dh = ylnx[0];
    const vf_type& dl = ylnx[1];
    constexpr
    const float exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(
        (dh < exp_lo_zero) | ((dh == exp_lo_zero) & (dl <= 0.0f)),
        res);
    if (_CALC_ROOT==false) {
        constexpr
        const float exp_hi_inf= fc::exp_hi_inf();
        res = _T::sel(
            (dh > exp_hi_inf) | ((dh == exp_hi_inf) & (dl >= 0.0f)),
            _T::pinf(), res);
    }
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_trig_arg(vf_type& xrh, vf_type& xrl, arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    constexpr const float large_arg=0x1p18f;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);

    xrh = 0.0f;
    xrl = 0.0f;
    vi_type q=0;
    if (__likely(!_T::all_of_vmf(v_large_arg))) {
        vf_type x_2_pi=x* ctbl::m_2_pi[0];
        vf_type fn= rint(x_2_pi);
        // x^ : -0xc.90fdbp-3f
        constexpr
        const float m_pi_2_h=-1.5707963705e+00f;
        // x^ : +0xb.bbd2ep-28f
        constexpr
        const float_t m_pi_2_m=+4.3711388287e-08f;
        // x^ : +0xf.72cedp-53f
        constexpr
        const float m_pi_2_l=+1.7151245100e-15f;
        vf_type f0, f1, f2, f3, f4;
        d_ops::mul12(f0, f1, fn, m_pi_2_h);
        d_ops::mul12(f2, f3, fn, m_pi_2_m);
        f4 = fn * m_pi_2_l;
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
        q=_T::cvt_f_to_i(x_2_pi);
    }
    if (__unlikely(_T::any_of_vmf(v_large_arg))) {
#if 1
        vf_type xrhl, xrll;
        // mask out not required values to avoid subnormals
        vf_type xl=_T::sel_val_or_zero(v_large_arg, x);
        vi_type ql=payne_hanek_pi_over_2<float, _T>::rem(xrhl, xrll, xl);
        q = _T::sel_vi(_T::vmf_to_vmi(v_large_arg), ql, q);
        xrh = _T::sel(v_large_arg, xrhl, xrh);
        xrl = _T::sel(v_large_arg, xrll, xrl);
#else
        size_t N = size(x);
        for (size_t i=0; i<N; ++i) {
            typename vf_type::value_type xi=extract(x, i);
            if (large_arg < std::fabs(xi)) {
                float xrhi, xrli;
                typename vi_type::value_type qi=
                    payne_hanek_pi_over_2<float, void>::rem(xrhi, xrli, xi);
                insert(q, qi, i);
                insert(xrh, xrhi, i);
                insert(xrl, xrli, i);
            }
        }
#endif
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
    constexpr
    const float sin_c2=-1.6666667163e-01f;
    // x^4 : +0x8.888b2p-10f
    constexpr
    const float sin_c4=+8.3333719522e-03f;
    // x^6 : -0xd.02433p-16f
    constexpr
    const float sin_c6=-1.9849911041e-04f;
    // x^8 : +0xb.bf108p-22f
    constexpr
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
    constexpr
    const float cos_c4=+4.1666667908e-02f;
    // x^6 : -0xb.60beap-13f
    constexpr
    const float cos_c6=-1.3889048714e-03f;
    // x^8 : +0xd.07ad8p-19f
    constexpr
    const float cos_c8=+2.4852735805e-05f;
    // x^10 : -0xa.c7898p-25f
    constexpr
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
    constexpr
    const float tan_c1=+1.0000000000e+00f;
    // x^3 : +0xa.aaabp-5f
    constexpr
    const float tan_c3=+3.3333349228e-01f;
    // x^5 : +0x8.886dp-6f
    constexpr
    const float tan_c5=+1.3332676888e-01f;
    // x^7 : +0xd.d6c9cp-8f
    constexpr
    const float tan_c7=+5.4058656096e-02f;
    // x^9 : +0xa.e63c5p-9f
    constexpr
    const float tan_c9=+2.1287808195e-02f;
    // x^11 : +0xb.15241p-10f
    constexpr
    const float tan_c11=+1.0822833516e-02f;
    // x^13 : +0xd.b2701p-17f
    constexpr
    const float tan_c13=+1.0449998808e-04f;
    // x^15 : +0x8.f2db7p-11f
    constexpr
    const float tan_c15=+4.3694633059e-03f;
    vf_type xrh2;
    d_ops::sqr21(xrh2, xrh, xrl);
    vf_type xrh4=xrh2*xrh2;
    constexpr
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
    c = _T::sel(isnan(c), copysign(_T::pinf(), th), c);
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
            vdf_type* ps, vdf_type* pc)
{
    // [5.42101086242752217003726400434970855712890625e-20, 0.785398185253143310546875] : | p - f | <= 2^-35.609375
    // coefficients for sin generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float sin_c1=+1.0000000000e+00f;
    // x^3 : -0xa.aaaabp-6f
    constexpr
    const float sin_c3=-1.6666667163e-01f;
    // x^5 : +0x8.888eap-10f
    constexpr
    const float sin_c5=+8.3334241062e-03f;
    // x^7 : -0xd.0a96cp-16f
    constexpr
    const float sin_c7=-1.9899540348e-04f;
    // x^9 : +0x9.5a646p-21f
    constexpr
    const float sin_c9=+4.4599028115e-06f;
    // x^11 : -0x9.d9517p-22f
    constexpr
    const float sin_c11=-2.3481604785e-06f;
    // x^13 : +0xa.0f27cp-23f
    constexpr
    const float sin_c13=+1.1991501196e-06f;

   // [5.42101086242752217003726400434970855712890625e-20, 0.785398185253143310546875] : | p - f | <= 2^-37.953125
    // coefficients for cos generated by sollya
    // x^0 : +0x8p-3f
    constexpr
    const float cos_c0=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    constexpr
    const float cos_c2=-5.0000000000e-01f;
    // x^4 : +0xa.aaaabp-8f
    constexpr
    const float cos_c4=+4.1666667908e-02f;
    // x^6 : -0xb.60bcfp-13f
    constexpr
    const float cos_c6=-1.3889017282e-03f;
    // x^8 : +0xd.0720cp-19f
    constexpr
    const float cos_c8=+2.4848639441e-05f;
    // x^10 : -0xb.b518p-25f
    constexpr
    const float cos_c10=-3.4890763345e-07f;
    // x^12 : +0xb.aa0e2p-28f
    constexpr
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

    constexpr
    static const float c_cos[]={
        cos_c12, cos_c10, cos_c8
    };
    constexpr
    static const float c_sin[]={
        sin_c13, sin_c11, sin_c9
    };
    horner_n2(ch, sh, xxh, c_cos, c_sin);
    sh = horner(xxh, sh, sin_c7);

    vf_type cl;
    d_ops::muladd12(ch, cl, cos_c6, ch, xxh);
    d_ops::unorm_mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c4, ch, cl);
    d_ops::unorm_mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c2, ch, cl);
    d_ops::unorm_mul22(ch, cl, ch, cl, xxh, xxl);
    d_ops::add122(ch, cl, cos_c0, ch, cl);

    vf_type sl;
    d_ops::muladd12(sh, sl, sin_c5, sh, xxh);
    d_ops::unorm_mul22(sh, sl, sh, sl, xxh, xxl);
    d_ops::add122(sh, sl, sin_c3, sh, sl);
    d_ops::unorm_mul22(sh, sl, sh, sl, xxh, xxl);
    d_ops::add122(sh, sl, sin_c1, sh, sl);
    d_ops::mul22(sh, sl, sh, sl, xrh, xrl);

    // vmf_type xrh_eq_0 = xrh == 0.0f;
    // sh = _T::sel(xrh_eq_0, xrh, sh);
    // sl = _T::sel(xrh_eq_0, 0.0f, sl);
    vmf_type xrh_tiny = abs(xrh) < 0x1p-24f;
    sh = _T::sel(xrh_tiny, xrh, sh);
    sl = _T::sel(xrh_tiny, xrl, sl);

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
        *ps = vdf_type(rsh, rsl);
    }
    if (pc != nullptr) {
        vf_type rch(_T::sel(q_and_1_f, sh, ch));
        vf_type rcl(_T::sel(q_and_1_f, sl, cl));
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        rch = _T::sel(mt, -rch, rch);
        rcl = _T::sel(mt, -rcl, rcl);
        *pc= vdf_type(rch, rcl);
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
typename cftal::math::elem_func_core<float, _T>::vi_type
cftal::math::elem_func_core<float, _T>::
__reduce_trigpi_arg(vf_type& xrh, vf_type& xrl, arg_t<vf_type> xc)
{
    vf_type xt2=xc+xc;
    vf_type fh= rint(xt2);
    xrh = xc - 0.5f * fh;
    // no need for fmod<4>(fh) here because |int(fh)| < |max integer|
    vmf_type xrh_tiny= abs(xrh) <
        0x1p2f*func_constants<float>::min_normal();
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    xrh = _T::sel(xrh_tiny, xrh*0x1p24f, xrh);
    d_ops::mul122(xrh, xrl, xrh, ctbl::m_pi[0], ctbl::m_pi[1]);
    xrh = _T::sel(xrh_tiny, xrh*0x1p-24f, xrh);
    xrl = _T::sel(xrh_tiny, xrl*0x1p-24f, xrl);
    vi_type q= _T::cvt_f_to_i(xt2);
    return q;
}

template <typename _T>
void
cftal::math::elem_func_core<float, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type xrh, xrl;
    auto q=__reduce_trigpi_arg(xrh, xrl, xc);
    __sin_cos_k(xrh, xrl, q, ps, pc);
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
tanpi_k(arg_t<vf_type> xc)
{
    vf_type xrh, xrl;
    auto q= __reduce_trigpi_arg(xrh, xrl, xc);
    vf_type t=__tan_k(xrh, xrl, q);
    return t;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vdf_type
cftal::math::elem_func_core<float, _T>::
__atan_0_1_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    vf_type xrh=xh, xrl=xl;
    vf_type ah=0, al=0;
    constexpr
    const float atan_i1_left=+3.7500000000e-01f;
    vmf_type sel=(xrh < atan_i1_left) |
        ((xrh == atan_i1_left) & (xrl < 0.0f));
    if (_T::any_of_vmf(sel)) {
        // [0, 0.375] : | p - f | <= 2^-28.390625
        // coefficients for atan_0 generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float atan_i0_c1=+1.0000000000e+00f;
        // x^3 : -0xa.aaa6bp-5f
        constexpr
        const float atan_i0_c3=-3.3333143592e-01f;
        // x^5 : +0xc.caa35p-6f
        constexpr
        const float atan_i0_c5=+1.9986803830e-01f;
        // x^7 : -0x8.f4f96p-6f
        constexpr
        const float atan_i0_c7=-1.3995203376e-01f;
        // x^9 : +0xa.e26b5p-7f
        constexpr
        const float atan_i0_c9=+8.5034765303e-02f;
        static_assert(atan_i0_c1==1.0, "atan_i0_c1 must be 1.0");
        constexpr
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
    if (!_T::all_of_vmf(sel)) {
        // [0.375, 1] : | p - f | <= 2^-29.859375
        // coefficients for atan_i1 generated by sollya
        // x^0 h: +0x9.26382p-4f
        constexpr
        const float atan_i1_c0h=+5.7183086872e-01f;
        // x^0 l: +0xc.d2a47p-29f
        constexpr
        const float atan_i1_c0l=+2.3884366485e-08f;
        // x^1 : +0xb.5069ep-4f
        constexpr
        const float atan_i1_c1=+7.0713222027e-01f;
        // x^2 : -0xa.4c309p-5f
        constexpr
        const float atan_i1_c2=-3.2180050015e-01f;
        // x^3 : +0xe.a281bp-9f
        constexpr
        const float atan_i1_c3=+2.8583576903e-02f;
        // x^4 : +0xc.10e86p-7f
        constexpr
        const float atan_i1_c4=+9.4265982509e-02f;
        // x^5 : -0xa.5a50ap-7f
        constexpr
        const float atan_i1_c5=-8.0881193280e-02f;
        // x^6 : +0x8.ab094p-9f
        constexpr
        const float atan_i1_c6=+1.6929902136e-02f;
        // x^7 : +0xf.1ca54p-9f
        constexpr
        const float atan_i1_c7=+2.9515422881e-02f;
        // x^8 : -0x8.7ffe3p-8f
        constexpr
        const float atan_i1_c8=-3.3203016967e-02f;
        // x^9 : -0xc.2cba2p-13f
        constexpr
        const float atan_i1_c9=-1.4861712698e-03f;
        // x^10 : +0xc.8ec16p-9f
        constexpr
        const float atan_i1_c10=+2.4526637048e-02f;
        // x^ : +0xa.4cp-4f
        constexpr
        const float atan_i1_x0=+6.4355468750e-01f;
        constexpr
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
    return vdf_type(ah, al);
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
    if (_T::any_of_vmf(calc_at)) {
        vmf_type x_gt_1 = x>1.0f;
        vf_type t=x;
        if (_T::any_of_vmf(x_gt_1)) {
            t = _T::sel(x_gt_1, 1.0f/x, t);
        }
        auto dat = __atan_0_1_k(t, 0.0f);
        if (_T::any_of_vmf(x_gt_1)) {
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
    constexpr
    const float atan_c0=+3.3333334327e-01f;
    // x^2 : -0xc.cccffp-6f
    constexpr
    const float atan_c2=-2.0000074804e-01f;
    // x^4 : +0x9.24b9bp-6f
    constexpr
    const float atan_c4=+1.4286653697e-01f;
    // x^6 : -0xe.34345p-7f
    constexpr
    const float atan_c6=-1.1096815020e-01f;
    // x^8 : +0xb.2d878p-7f
    constexpr
    const float atan_c8=+8.7326943874e-02f;
    // x^10 : -0xd.5110fp-8f
    constexpr
    const float atan_c10=-5.2018221468e-02f;

    constexpr
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
    // atan(1/x) = M_PI_2 -atan(x) if x>0
    // ax=abs(x)
    // ay=abs(y)
    // calculate at = atan( min(ax, ay)/max(ax, ay) )
    // ay > ax: at = M_PI_2 - atan;
    vf_type ax=abs(x);
    vf_type ay=abs(y);
    vf_type p=min(ax, ay), q=max(ax, ay);

    constexpr const float x_y_small =
        d_real_traits<float>::scale_div_threshold();
    vf_type xrh, xrl;
    d_ops::div12(xrh, xrl, p, q);
    vmf_type s;
    if (_T::any_of_vmf(s= (ax < x_y_small) | (ay < x_y_small))) {
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
    if (_T::any_of_vmf(s = ay > ax)) {
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
    if (_T::any_of_vmf(s=y_lt_0 & x_lt_0)) {
        vf_type at_minus_pi_h, at_minus_pi_l;
        d_ops::add22(at_minus_pi_h, at_minus_pi_l,
                    -ctbl::m_pi[0], -ctbl::m_pi[1],
                    dat[0], dat[1]);
        at = _T::sel(s, at_minus_pi_h, at);
    }

    // y < 0, x>=0: atan2(y, x) =  -atan(y/x)
    at = _T::sel(y_lt_0 & (x_s>=0.0f), -dat[0], at);

    // y >= 0, x < 0: atan2(y, x) = PI - atan(y/x)
    if (_T::any_of_vmf(s= (y_s >=0.0f) & x_lt_0)) {
        vf_type pi_minus_at_h, pi_minus_at_l;
        d_ops::add22(pi_minus_at_h, pi_minus_at_l,
                    ctbl::m_pi[0], ctbl::m_pi[1],
                    -dat[0], -dat[1]);
        at = _T::sel(s, pi_minus_at_h, at);
    }
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
    constexpr
    const float asin_c0=+1.6666667163e-01f;
    // x^2 : +0x9.99946p-7f
    constexpr
    const float asin_c2=+7.4999377131e-02f;
    // x^4 : +0xb.6f31dp-8f
    constexpr
    const float asin_c4=+4.4665444642e-02f;
    // x^6 : +0xf.5f16fp-9f
    constexpr
    const float asin_c6=+3.0022351071e-02f;
    // x^8 : +0xc.f08a7p-9f
    constexpr
    const float asin_c8=+2.5272680447e-02f;
    // x^10 : +0xa.b0219p-11f
    constexpr
    const float asin_c10=+5.2187559195e-03f;
    // x^12 : +0x9.a0bp-8f
    constexpr
    const float asin_c12=+3.7608146667e-02f;

    constexpr
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
    // vi_type t=_T::as_int(s);
    // t &= 0xfffff000;
    // vf_type f=_T::as_float(t);
    vf_type f, fl;
    d_real_traits<vf_type>::split(s, f, fl);
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
    // vi_type t=_T::as_int(s);
    // t &= 0xfffff000;
    // vf_type df= _T::as_float(t);
    vf_type df, dfl;
    d_real_traits<vf_type>::split(s, df, dfl);
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

    vf_type y=0;
    vmf_type sel;

    constexpr
    const float asinh_i1_left=+7.0710676908e-01f;
    constexpr
    const float asinh_i1_right=+3.0000000000e+00f;
    if (_T::any_of_vmf(sel = x <= asinh_i1_left)) {
        // [0, 0.707106769084930419921875] : | p - f | <= 2^-32.234375
        // coefficients for asinh_i0 generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float asinh_i0_c1=+1.0000000000e+00f;
        // x^3 : -0xa.aaaa7p-6f
        constexpr
        const float asinh_i0_c3=-1.6666661203e-01f;
        // x^5 : +0x9.9981ap-7f
        constexpr
        const float asinh_i0_c5=+7.4997141957e-02f;
        // x^7 : -0xb.6a588p-8f
        constexpr
        const float asinh_i0_c7=-4.4591456652e-02f;
        // x^9 : +0xf.538eap-9f
        constexpr
        const float asinh_i0_c9=+2.9934365302e-02f;
        // x^11 : -0xa.597cap-9f
        constexpr
        const float asinh_i0_c11=-2.0213980228e-02f;
        // x^13 : +0xb.807cfp-10f
        constexpr
        const float asinh_i0_c13=+1.1232330464e-02f;
        // x^15 : -0xe.1b09dp-12f
        constexpr
        const float asinh_i0_c15=-3.4437545110e-03f;
        constexpr
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
    if (_T::any_of_vmf(sel = (x> asinh_i1_left) & (x<=asinh_i1_right))) {
        // [0.707106769084930419921875, 3] : | p - f | <= 2^-32.671875
        // coefficients for asinh_i1 generated by sollya
        // x^0 h: +0x9.e8325p-3f
        constexpr
        const float asinh_i1_c0h=+1.2383772135e+00f;
        // x^0 l: +0xc.1ed42p-28f
        constexpr
        const float asinh_i1_c0l=+4.5152098949e-08f;
        // x^1 : +0x8.8e742p-4f
        constexpr
        const float asinh_i1_c1=+5.3477871418e-01f;
        // x^2 : -0xf.77528p-7f
        constexpr
        const float asinh_i1_c2=-1.2082892656e-01f;
        // x^3 : +0xe.e793bp-9f
        constexpr
        const float asinh_i1_c3=+2.9110541567e-02f;
        // x^4 : -0xa.15eccp-11f
        constexpr
        const float asinh_i1_c4=-4.9246307462e-03f;
        // x^5 : -0xa.556a7p-14f
        constexpr
        const float asinh_i1_c5=-6.3071626937e-04f;
        // x^6 : +0x9.a7641p-13f
        constexpr
        const float asinh_i1_c6=+1.1784509989e-03f;
        // x^7 : -0xb.f56d9p-14f
        constexpr
        const float asinh_i1_c7=-7.2990130866e-04f;
        // x^8 : +0xa.7a9f1p-15f
        constexpr
        const float asinh_i1_c8=+3.1979338382e-04f;
        // x^9 : -0xc.e08b6p-17f
        constexpr
        const float asinh_i1_c9=-9.8244679975e-05f;
        // x^10 : +0xa.6279cp-20f
        constexpr
        const float asinh_i1_c10=+9.9035933090e-06f;
        // x^11 : +0xd.7e68fp-20f
        constexpr
        const float asinh_i1_c11=+1.2868679732e-05f;
        // x^12 : -0xc.daf99p-20f
        constexpr
        const float asinh_i1_c12=-1.2259836694e-05f;
        // x^13 : +0xd.ff83p-21f
        constexpr
        const float asinh_i1_c13=+6.6748107201e-06f;
        // x^14 : -0x9.4b8cap-22f
        constexpr
        const float asinh_i1_c14=-2.2161279958e-06f;
        // x^15 : +0xb.1a90ap-25f
        constexpr
        const float asinh_i1_c15=+3.3091811247e-07f;
        // x^ : +0xc.a4p-3f
        constexpr
        const float asinh_i1_x0=+1.5800781250e+00f;
        constexpr
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
    if (_T::any_of_vmf(sel = x > asinh_i1_right)) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vmf_type x_huge = x > 0x1p24f;
        vf_type add_2_log=_T::sel_val_or_zero(x_huge, ctbl::m_ln2[0]);
        // vf_type t= x*x;
        vf_type log_arg=_T::sel(x_huge,
                                x,
                                2.0f * x+ 1.0f/(sqrt(vf_type(x*x+1.0f))+x));
        vf_type yl= log_k(log_arg);
        yl += add_2_log;
        y = _T::sel(sel, yl, y);
    }
    // |x| < 2.0
    // vf_type log1p_arg= x+t/(1.0+sqrt(vf_type(1.0+t)));
    // vf_type ys= log1p_k(log1p_arg);
    y = copysign(y, xc);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
acosh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);

    vf_type y=0.0f;
    vmf_type sel;
    constexpr
    const float acosh_i1_left=+2.0000000000e+00f;
    constexpr
    const float acosh_i1_right=+3.5000000000e+00f;
    if (_T::any_of_vmf(sel = x <= acosh_i1_left)) {
        vf_type xm1h, xm1l;
        d_ops::add12(xm1h, xm1l, x, -1.0f);
        vf_type sqrt2xm1h, sqrt2xm1l;
        d_ops::sqrt2(sqrt2xm1h, sqrt2xm1l, xm1h+xm1h, xm1l+xm1l);
        // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]

        // [9.31322574615478515625e-10, 1] : | p - f | <= 2^-31.4921875
        // coefficients for acosh_i0 generated by sollya
        // x^0 : +0x8p-3f
        constexpr
        const float acosh_i0_c0=+1.0000000000e+00f;
        // x^1 : -0xa.aaaa7p-7f
        constexpr
        const float acosh_i0_c1=-8.3333306015e-02f;
        // x^2 : +0x9.9981ap-9f
        constexpr
        const float acosh_i0_c2=+1.8749285489e-02f;
        // x^3 : -0xb.6a588p-11f
        constexpr
        const float acosh_i0_c3=-5.5739320815e-03f;
        // x^4 : +0xf.538eap-13f
        constexpr
        const float acosh_i0_c4=+1.8708978314e-03f;
        // x^5 : -0xa.597cap-14f
        constexpr
        const float acosh_i0_c5=-6.3168688212e-04f;
        // x^6 : +0xb.807cfp-16f
        constexpr
        const float acosh_i0_c6=+1.7550516350e-04f;
        // x^7 : -0xe.1b09dp-19f
        constexpr
        const float acosh_i0_c7=-2.6904332117e-05f;
        constexpr
        static const float ci[]={
            acosh_i0_c7, acosh_i0_c6, acosh_i0_c5,
            acosh_i0_c4, acosh_i0_c3, acosh_i0_c2, acosh_i0_c1
        };
        vf_type ys=horner2(xm1h, vf_type(xm1h*xm1h), ci);
        vf_type ysl;
        horner_comp_quick(ys, ysl, xm1h, ys, acosh_i0_c0);
        vf_type t;
        d_ops::unorm_mul22(ys, t, ys, ysl, sqrt2xm1h, sqrt2xm1l);
        ys += t;
        y= _T::sel(sel, ys, y);
    }
    if (_T::any_of_vmf(sel= (x > acosh_i1_left) & (x<=acosh_i1_right))) {
        // [2, 3.5] : | p - f | <= 2^-28.4140625
        // coefficients for acosh_i1 generated by sollya
        // x^0 h: +0xc.f8a2dp-3f
        constexpr
        const float acosh_i1_c0h=+1.6214042902e+00f;
        // x^0 l: +0xa.cadafp-28f
        constexpr
        const float acosh_i1_c0l=+4.0204835017e-08f;
        // x^1 : +0xd.29695p-5f
        constexpr
        const float acosh_i1_c1=+4.1130509973e-01f;
        // x^2 : -0xb.b4feep-7f
        constexpr
        const float acosh_i1_c2=-9.1461047530e-02f;
        // x^3 : +0xe.e36ccp-9f
        constexpr
        const float acosh_i1_c3=+2.9078863561e-02f;
        // x^4 : -0xb.46dcbp-10f
        constexpr
        const float acosh_i1_c4=-1.1012504809e-02f;
        // x^5 : +0x9.841bfp-11f
        constexpr
        const float acosh_i1_c5=+4.6465094201e-03f;
        // x^6 : -0x8.82a3p-12f
        constexpr
        const float acosh_i1_c6=-2.0777098835e-03f;
        // x^7 : +0xf.d8561p-14f
        constexpr
        const float acosh_i1_c7=+9.6710590879e-04f;
        // x^8 : -0x8.fdab8p-14f
        constexpr
        const float acosh_i1_c8=-5.4876087233e-04f;
        // x^9 : +0xb.1cf4dp-15f
        constexpr
        const float acosh_i1_c9=+3.3914521919e-04f;
        // x^10 : -0xe.a7d25p-17f
        constexpr
        const float acosh_i1_c10=-1.1181299487e-04f;
        // x^ : +0xa.84p-2f
        constexpr
        const float acosh_i1_x0=+2.6289062500e+00f;
        constexpr
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
    if (_T::any_of_vmf(sel = x > acosh_i1_right)) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vmf_type x_huge = x > 0x1p24f;
        vf_type add_2_log=_T::sel_val_or_zero(x_huge, ctbl::m_ln2[0]);
        // vf_type t= x*x;
        vf_type log_arg=_T::sel(x_huge,
                                x,
                                2.0f*x - 1.0f/(x+sqrt(vf_type(x*x-1.0f))));
        vf_type yl= log_k(log_arg);
        yl += add_2_log;
        y= _T::sel(sel, yl, y);
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<float, _T>::vf_type
cftal::math::elem_func_core<float, _T>::
atanh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);

    vf_type y=0.0;
    vmf_type sel;
    constexpr
    const float atanh_i1_left=+5.0000000000e-01f;
    if (_T::any_of_vmf(sel= x <= atanh_i1_left)) {
        // [0, 0.5] : | p - f | <= 2^-30.328125
        // coefficients for atanh_i0 generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float atanh_i0_c1=+1.0000000000e+00f;
        // x^3 : +0xa.aaa9fp-5f
        constexpr
        const float atanh_i0_c3=+3.3333298564e-01f;
        // x^5 : +0xc.cd394p-6f
        constexpr
        const float atanh_i0_c5=+2.0002585649e-01f;
        // x^7 : +0x9.1a158p-6f
        constexpr
        const float atanh_i0_c7=+1.4221704006e-01f;
        // x^9 : +0xf.24e21p-7f
        constexpr
        const float atanh_i0_c9=+1.1831308156e-01f;
        // x^11 : +0xd.15382p-8f
        constexpr
        const float atanh_i0_c11=+5.1105029881e-02f;
        // x^13 : +0xb.54293p-6f
        constexpr
        const float atanh_i0_c13=+1.7701177299e-01f;
        constexpr
        static const float c[]={
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
    if (_T::any_of_vmf(sel = (x>atanh_i1_left) & (x<=0.75))) {
        // [0.5, 0.75] : | p - f | <= 2^-28.375
        // coefficients for atanh_i1 generated by sollya
        // x^0 h: +0xc.2c9c3p-4f
        constexpr
        const float atanh_i1_c0h=+7.6089113951e-01f;
        // x^0 l: +0x8.122cp-31f
        constexpr
        const float atanh_i1_c0l=+3.7583447465e-09f;
        // x^1 : +0xd.98efap-3f
        constexpr
        const float atanh_i1_c1=+1.6996757984e+00f;
        // x^2 : +0xe.d401fp-3f
        constexpr
        const float atanh_i1_c2=+1.8535193205e+00f;
        // x^3 : +0xe.a2p-2f
        constexpr
        const float atanh_i1_c3=+3.6582031250e+00f;
        // x^4 : +0xf.1f06cp-1f
        constexpr
        const float atanh_i1_c4=+7.5605983734e+00f;
        // x^5 : +0x8.6f797p+1f
        constexpr
        const float atanh_i1_c5=+1.6870893478e+01f;
        // x^6 : +0x9.b87c7p+2f
        constexpr
        const float atanh_i1_c6=+3.8882595062e+01f;
        // x^7 : +0xc.51332p+3f
        constexpr
        const float atanh_i1_c7=+9.8537490845e+01f;
        // x^8 : +0x8.8d5fcp+5f
        constexpr
        const float atanh_i1_c8=+2.7367175293e+02f;
        // x^9 : +0xf.10c64p+5f
        constexpr
        const float atanh_i1_c9=+4.8209680176e+02f;
        // x^ : +0x8p-4f
        // x^ : +0xa.44p-4f
        constexpr
        const float atanh_i1_x0=+6.4160156250e-01f;
        constexpr
        static const float c[]={
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
    if (_T::any_of_vmf(sel = x>0.75f)) {
        vf_type log1p_arg= 2.0f*(x/(1.0f-x));
        vf_type yl= 0.5f*log1p_k(log1p_arg);
        y = _T::sel(sel, yl, y);
    }
    y = copysign(y, xc);
    return y;
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
    scale = _T::sel(ma_small, 0x1p-80f, scale);
    factor= _T::sel(ma_small, 0x1p80f, factor);
    // avoid overflows
    vmf_type ma_large= ma > 0x1p60f;
    scale = _T::sel(ma_large, 0x1p80f, scale);
    factor= _T::sel(ma_large, 0x1p-80f, factor);
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
