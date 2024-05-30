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
#if !defined (__CFTAL_MATH_ELEM_FUNC_CORE_F16_H__)
#define __CFTAL_MATH_ELEM_FUNC_CORE_F16_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f16.h>
#include <cftal/std_types.h>
#include <cftal/math/elem_func.h>
#include <cftal/math/func_traits_f16_s16.h>
#include <cftal/math/func_constants_f16.h>
#include <cftal/math/func_data.h>
#include <cftal/math/misc.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_d_real_constants_f16.h>
#include <cftal/math/f16_tables.h>
#include <cftal/mem.h>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for f16_t and different
        // traits
        template <typename _T>
        struct elem_func_core<f16_t, _T> {

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

            template <int16_t _X>
            static
            vi_type
            __ilogb_plus(arg_t<vf_type> x);

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);

            static
            vi_type
            ilogb(arg_t<vf_type> vf);

            template <typename _TBL>
            static
            vi_type
            cvt_to_index_4(arg_t<vf_type> x);

            template <typename _TBL>
            static
            vf_type
            lookup_from(arg_t<vf_type> x);

            static
            vf_type
            sqrt(arg_t<vf_type> x);

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

        };
    }
}

template <typename _T>
template <typename _SCALAR_FUNC>
inline
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
call_scalar_func(arg_t<vf_type> x, _SCALAR_FUNC f)
{
    using std::size;
    const std::size_t _N = size(x);
    vf_type r;
    for (std::size_t i=0; i<_N; ++i) {
        f16_t xi=extract(x, i);
        f16_t ri=f(xi);
        insert(r, ri, i);
    }
    return r;
}

template <typename _T>
template <typename _SCALAR_FUNC>
inline
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
call_scalar_func(arg_t<vf_type> x, arg_t<vf_type> y, _SCALAR_FUNC f)
{
    using std::size;
    const std::size_t _N = size(x);
    vf_type r;
    for (std::size_t i=0; i<_N; ++i) {
        f16_t xi=extract(x, i);
        f16_t yi=extract(y, i);
        f16_t ri=f(xi, yi);
        insert(r, ri, i);
    }
    return r;
}

template <typename _T>
template <unsigned _U>
inline
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__fmod(arg_t<vf_type> v)
{
    constexpr const f16_t sd=1.0_f16/_U;
    constexpr const f16_t su=_U;
    constexpr const f16_t nsu=-su;
    vf_type i= rint(vf_type(v*sd));
    vf_type r= i*nsu + v;
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc)
{
    vi_type ux=_T::as_int(xc);
    vi_type uy=_T::as_int(yc);
    vi_type ax= ux & not_sign_f16_msk::v.s16();
    vi_type ay= uy & not_sign_f16_msk::v.s16();
    vi_type ux_inc= ux + 1;
    vi_type ux_dec= ux - 1;
    // decrement required if ax > ay or (ux^uy & sgn) != 0
    vmi_type opp_sgn=
        vi_type((ux^uy) & sign_f16_msk::v.s16()) != vi_type(0);
    vi_type r= _T::sel_vi((ax > ay) | opp_sgn, ux_dec, ux_inc);
    vi_type r0= _T::sel_vi(ay == 0, uy, (uy & sign_f16_msk::v.s16()) | 1);
    r = _T::sel_vi(ax == 0, r0, r);
    r = _T::sel_vi(ux == uy, uy, r);
    vf_type rf=_T::as_float(r);
    return rf;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
ldexp_k(arg_t<vf_type> x, arg_t<vi_type> n)
{
    vf_type xs=x;
    using fc=func_constants<f16_t>;
    vmf_type is_denom= abs(x) < fc::min_normal();

    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p12_f16), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    vi_type eo= _T::sel_val_or_zero_vi(i_is_denom, vi_type(-12));
    // mantissa
    vi_type m=_T::as_int(xs);
    vi_type xe=((m>>10) & 0x1f) + eo;

    // determine the exponent of the result
    // clamp nn to [-256, 256]
    vi_type nn= min(vi_type(256), max(n, vi_type(-256)));
    vi_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0x1f normal result
    //     re >= 0x1f inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

    // clear exponent bits from m
    m &= vi_type(~0x7c00);

    // mantissa for normal results:
    vi_type mn= m | ((re & vi_type(0x1f)) << 10);
    vf_type r= _T::as_float(mn);

    // overflow handling
    vmi_type i_is_inf = re > vi_type(0x1e);
    vmf_type f_is_inf = _T::vmi_to_vmf(i_is_inf);
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi_type i_is_near_z = re < vi_type (1);
    if (_T::any_of_vmi(i_is_near_z)) {
        // create m*0x1.0p-14
        vi_type mu= m | vi_type(1<<10);
        vf_type r_u= _T::as_float(mu);
        // create a scaling factor
        vi_type ue= max(vi_type(re + (_T::bias()-1)), vi_type(1));
        vf_type s_u= _T::as_float(vi_type(ue << 10));
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi_to_vmf(i_is_near_z);
        r = _T::sel(f_is_near_z, r_u, r);
    }
    // handle special cases:
    r = _T::sel(isinf(x) | isnan(x) | iszero(x), x, r);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    return ldexp_k(x, n);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__frexp_k(vf_type& m, arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<f16_t>;
    vmf_type is_denom= abs(x) < fc::min_normal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p12_f16), xs);
    const int16_t neg_bias_p_1=-_T::bias()+1;
    const int16_t neg_bias_p_1_m_12=neg_bias_p_1 - 12;
    vi_type e=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                        neg_bias_p_1_m_12, neg_bias_p_1);;
    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    // exponent:
    e += ((i >> 10) & 0x1f);
    const int16_t half=0x3800;
    const int16_t clear_exp_msk=0x83ff;
    // insert exponent
    i &= clear_exp_msk;
    i |= half;
    m= _T::as_float(i);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vf_type xs=x;
    using fc=func_constants<f16_t>;
    vmf_type is_denom= abs(x) < fc::min_normal();
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p12_f16), xs);
    const int16_t neg_bias_p_1=-_T::bias()+1;
    const int16_t neg_bias_p_1_m_12=neg_bias_p_1 - 12;
    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    const int16_t half=0x3800;
    const int16_t clear_exp_msk=0x83ff;
    // insert exponent
    vi_type mi = i & clear_exp_msk;
    mi |= half;
    vf_type m= _T::as_float(mi);
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | iszero(x);
    m = _T::sel(f_inz, x, m);
    if (ve != nullptr) {
        vi_type e=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                             neg_bias_p_1_m_12, neg_bias_p_1);
        // exponent:
        e += ((i >> 10) & 0x1f);
        vmi_type i_inz=_T::vmf_to_vmi(f_inz);
        e = _T::sel_zero_or_val_vi(i_inz, e);
        *ve=e;
    }
    return m;
}

template <typename _T>
template <cftal::int16_t _X>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__ilogb_plus(arg_t<vf_type> x)
{
    vf_type xs=abs(x);
    using fc=func_constants<f16_t>;
    vmf_type is_denom= xs < fc::min_normal();
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p12_f16), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel_vi(i_is_denom, vi_type(-12), eo);
    // reinterpret as integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 10) /*& 0x1f*/) + eo - vi_type(_T::bias()-_X);
    return e;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
ilogbp1(arg_t<vf_type> x)
{
    return __ilogb_plus<1>(x);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(__ilogb_plus<0>(d));
    vmf_type mf= d == 0.0_f16;
    vmi_type mi= _T::vmf_to_vmi(mf);
    e = _T::sel_vi(mi, vi_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel_vi(mi, vi_type(0x7fff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel_vi(mi, vi_type(FP_ILOGBNAN), e);
    return e;
}

template <typename _T>
template <typename _TBL>
inline
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
cvt_to_index_4(arg_t<vf_type> x)
{
    vi_type idx;
    if (_TBL::zero_offset == 0) {
        vf_type ax=abs(x);
        idx=_T::as_int(ax);
    } else {
        vmi_type ltz=_T::vmf_to_vmi(signbit(x));
        vi_type i=_T::as_int(x);
        const int16_t nmsk=0x7fff;
        vi_type nidx= i^nmsk; // or nmsk - i;
        idx=_T::sel_vi(ltz, nidx, i);
        const vi_type min_idx(static_cast<int16_t>(_TBL::min_offset));
        idx=max(idx, min_idx);
    }
    const vi_type max_idx(static_cast<int16_t>(_TBL::max_offset-1));
    idx=min(idx, max_idx);
    return idx;
}

template <typename _T>
template <typename _TBL>
inline
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
lookup_from(arg_t<vf_type> x)
{
    vi_type idx=cvt_to_index_4<_TBL>(x);
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(_TBL::tbl_zero());
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
sqrt(arg_t<vf_type> xc)
{
    vf_type y=lookup_from<f16_sqrt_data>(xc);
    y=_T::sel(signbit(xc), _T::nan(), y);
    y=_T::sel(iszero(xc), xc, y);
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    vf_type y=lookup_from<f16_rsqrt_data>(x);
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);

    // reduce x into [2^-3, 1.0)
    const int32_t shift_1_3 = 7;
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
    vi_type rc_exp= rc << 10;
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
    const f16_t cbrt_c0=+2.7782887220e-01f;
    // x^1 : +0x9.8ff06p-2f
    constexpr
    const f16_t cbrt_c1=+2.3905653954e+00f;
    // x^2 : -0xc.74144p-1f
    constexpr
    const f16_t cbrt_c2=-6.2267169952e+00f;
    // x^3 : +0xc.57311p+0f
    constexpr
    const f16_t cbrt_c3=+1.2340592384e+01f;
    // x^4 : -0xe.c0162p+0f
    constexpr
    const f16_t cbrt_c4=-1.4750337601e+01f;
    // x^5 : +0x9.7496p+0f
    constexpr
    const f16_t cbrt_c5=+9.4554138184e+00f;
    // x^6 : -0x9.f353p-2f
    constexpr
    const f16_t cbrt_c6=-2.4876213074e+00f;
    constexpr static const f16_t ci[]={
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
    const f16_t cbrt_c0=+4.5316359401e-01f;
    // x^1 : +0x9.aae0ap-4f
    constexpr
    const f16_t cbrt_c1=+6.0421812534e-01f;
    vf_type mm = horner(mm0,
                        cbrt_c1,
                        cbrt_c0);
    // 1st iteration
    mm = impl::root_3::order3<f16_t>(mm, mm0);
#endif
    // round mm to 3 bits = int(11/3)
    mm=round_to_nearest_even_last_bits<11-11/3>(mm);
    // second iteration
    mm = impl::root_3::order5<f16_t>(mm, mm0);
    // no denormal results are possible
#if 1
    vi_type e3c_exp=(e3c<<10);
    vi_type mmi=_T::as_int(mm) + e3c_exp;
    mm=_T::as_float(mmi);
#else
    vf_type t= _T::insert_exp(_T::bias()+e3c);
    mm *=t;
#endif
    // mm = copysign(mm, xc);
    mm |= (xc & as<f16_t>(sign_f16_msk::v.u16()));
    return mm;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
rcbrt_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);

    // reduce x into [2^-3, 1.0)
    const int32_t shift_1_3 = 7;
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
    vi_type rc_exp= rc << 10;
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
    const f16_t rcbrt_c0=+3.1453442574e+00f;
    // x^1 : -0xf.03ca1p+0f
    constexpr
    const f16_t rcbrt_c1=-1.5014801979e+01f;
    // x^2 : +0x8.12b8ep+3f
    constexpr
    const f16_t rcbrt_c2=+6.4585067749e+01f;
    // x^3 : -0xa.eec72p+4f
    constexpr
    const f16_t rcbrt_c3=-1.7492361450e+02f;
    // x^4 : +0x9.19d05p+5f
    constexpr
    const f16_t rcbrt_c4=+2.9122671509e+02f;
    // x^5 : -0x9.06246p+5f
    constexpr
    const f16_t rcbrt_c5=-2.8876776123e+02f;
    // x^6 : +0x9.c19c9p+4f
    constexpr
    const f16_t rcbrt_c6=+1.5610072327e+02f;
    // x^7 : -0x8.d68b3p+2f
    constexpr
    const f16_t rcbrt_c7=-3.5352245331e+01f;
    constexpr static const f16_t ci[]={
        rcbrt_c7, rcbrt_c6,
        rcbrt_c5, rcbrt_c4, rcbrt_c3,
        rcbrt_c2, rcbrt_c1, rcbrt_c0
    };
    vf_type mm02=mm0*mm0;
    vf_type mm = horner2(mm0, mm02, ci);
    // round mm to 8 bits = int(24/3)
    mm=round_to_nearest_even_last_bits<11-11/3>(mm);
    // second iteration
    mm = impl::root_r3::order5<f16_t>(mm, mm0);
    // no denormal results are possible
#if 1
    vi_type e3c_exp=(e3c<<10);
    vi_type mmi=_T::as_int(mm) - e3c_exp;
    mm=_T::as_float(mmi);
#else
    vf_type t= _T::insert_exp(_T::bias()-e3c);
    mm *=t;
#endif
    // mm = copysign(mm, xc);
    mm |= (xc & as<f16_t>(sign_f16_msk::v.u16()));
    return mm;
}


template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
root12_k(arg_t<vf_type> xc)
{
    // reduce x into [2^-12, 1.0)
    const int32_t shift_1_12= 0xb;
    const int32_t fac_1_12= 0xab;

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
    vi_type rc_exp= rc << 10;
    // correction of the exponent of mm0:
    vi_type mm0i=_T::as_int(mm0) + rc_exp;
    mm0=_T::as_float(mm0i);
    // [2.44140625e-4, 1.953125e-3] : | p - f | <= 2^-8.08984375
    // coefficients for root12_i0 generated by sollya
    // x^0 : +0xf.3c1f4p-5f
    constexpr
    const f16_t root12_i0_c0=+4.7608911991e-01f;
    // x^1 : +0xe.bf4cfp+3f
    constexpr
    const f16_t root12_i0_c1=+1.1797814178e+02f;
    // x^2 : -0xe.cb641p+11f
    constexpr
    const f16_t root12_i0_c2=-3.0299126953e+04f;
    constexpr
    static const f16_t ci0[] = {
        root12_i0_c2, root12_i0_c1, root12_i0_c0
    };
    // [1.953125e-3, 1.5625e-2] : | p - f | <= 2^-7.83984375
    // coefficients for root12_i1 generated by sollya
    // x^0 : +0x9.0f06cp-4f
    constexpr
    const f16_t root12_i1_c0=+5.6616854668e-01f;
    // x^1 : +0x8.c4cedp+1f
    constexpr
    const f16_t root12_i1_c1=+1.7537561417e+01f;
    // x^2 : -0x8.cbff5p+6f
    constexpr
    const f16_t root12_i1_c2=-5.6299932861e+02f;
    constexpr
    static const f16_t ci1[] = {
        root12_i1_c2, root12_i1_c1, root12_i1_c0
    };
    // [1.5625e-2, 0.125] : | p - f | <= 2^-7.58984375
    // coefficients for root12_i2 generated by sollya
    // x^0 : +0xa.c5cd8p-4f
    constexpr
    const f16_t root12_i2_c0=+6.7329168320e-01f;
    // x^1 : +0xa.6d8a8p-2f
    constexpr
    const f16_t root12_i2_c1=+2.6069736481e+00f;
    // x^2 : -0xa.76173p+0f
    constexpr
    const f16_t root12_i2_c2=-1.0461291313e+01f;
    constexpr
    static const f16_t ci2[] = {
        root12_i2_c2, root12_i2_c1, root12_i2_c0
    };
    // [0.125, 1] : | p - f | <= 2^-7.33984375
    // coefficients for root12_i3 generated by sollya
    // x^0 : +0xc.cf994p-4f
    constexpr
    const f16_t root12_i3_c0=+8.0068325996e-01f;
    // x^1 : +0xc.66a31p-5f
    constexpr
    const f16_t root12_i3_c1=+3.8752892613e-01f;
    // x^2 : -0xc.70cddp-6f
    constexpr
    const f16_t root12_i3_c2=-1.9438500702e-01f;
    constexpr
    static const f16_t ci3[] = {
        root12_i3_c2, root12_i3_c1, root12_i3_c0
    };
    vf_type mm_i0 = horner(mm0, ci0);
    vf_type mm_i1 = horner(mm0, ci1);
    vf_type mm_i2 = horner(mm0, ci2);
    vf_type mm_i3 = horner(mm0, ci3);
    vf_type mm_a= _T::sel(mm0 < 0x1p-9f, mm_i0, mm_i1);
    vf_type mm_b= _T::sel(mm0 < 0x1p-3f, mm_i2, mm_i3);
    vf_type mm= _T::sel(mm0 < 0x1p-6f, mm_a, mm_b);

    mm = impl::root_12::householder4<f16_t>(mm, mm0);
    vi_type e12c_exp=(e12c<<10);
    vi_type mmi=_T::as_int(mm) + e12c_exp;
    mm=_T::as_float(mmi);
    // mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::scale_result
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__mul_two_pow(arg_t<vf_type> y, arg_t<vi_type> k)
{
    vi_type ka= k >> 1;
    vi_type kb= k - ka;
    ka <<= 10;
    kb += _T::bias();
    kb <<= 10;
    vi_type yi=_T::as_int(y) + ka;
    vf_type s1=_T::as_float(kb);
    vf_type r=_T::as_float(yi) * s1;
    return r;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vdf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__mul_two_pow(arg_t<vf_type> y,  arg_t<vf_type> yl,
              arg_t<vi_type> k)
{
    // use f16_ting point operations here because yl may underflow
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::scale_result
cftal::math::elem_func_core<cftal::f16_t, _T>::
__two_pow(arg_t<vf_type> k)
{
    return __two_pow(_T::cvt_f_to_i(k));
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__mul_two_pow(arg_t<vf_type> ym, arg_t<vf_type> k)
{
    return __mul_two_pow(ym, _T::cvt_f_to_i(k));
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vdf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__mul_two_pow(arg_t<vf_type> yh, arg_t<vf_type> yl, arg_t<vf_type> k)
{
    return __mul_two_pow(yh, yl, _T::cvt_f_to_i(k));
}

template <typename _T>
template <bool _EXP_M1>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
        arg_t<vf_type> kf,
        arg_t<vmf_type> x_small)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-16.5390625
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3_f16
    constexpr
    const f16_t exp_c0=+1.00000e+00_f16;
    // x^1 : +0x8p-3_f16
    constexpr
    const f16_t exp_c1=+1.00000e+00_f16;
    // x^2 : +0x8p-4_f16
    constexpr
    const f16_t exp_c2=+5.00000e-01_f16;
    // x^3 : +0xa.b8p-6_f16
    constexpr
    const f16_t exp_c3=+1.67480e-01_f16;
    // x^4 : +0xa.aap-8_f16
    constexpr
    const f16_t exp_c4=+4.16565e-02_f16;
    static_assert(exp_c0 == 1.0_f16, "exp_c0 == 1.0_f16 is expected");
    static_assert(exp_c1 == 1.0_f16, "exp_c1 == 1.0_f16 is expected");
    static_assert(exp_c2 == 0.5_f16, "exp_c2 == 0.5_f16 is expected");

    vf_type x2= xrh*xrh;
    constexpr
    static const f16_t ci[]={
        exp_c4, exp_c3
    };

    vf_type p=horner(xrh, ci);
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
        vf_type scale = __mul_two_pow(vf_type(0.5_f16), kf);
        // e^x-1 = 2*(y * 2^s - 0.5)
        y  *= scale;
        vf_type t;
        d_ops::add12cond(y, t, -0.5_f16, y);
        // ye = 2.0f * (ye * scale + t);
        ye = (ye * scale + t);
        ye += ye;
        y = 2.0_f16*y + ye;
        // x small, required for handling of subnormal numbers
        y = _T::sel(x_small, xrh, y);
    }
    return y;
}

template <typename _T>
template <typename cftal::math::elem_func_core<cftal::f16_t, _T>::result_prec _P>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__exp_tbl_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
            arg_t<vi_type> idx,
            vf_type* expl)
{
    // [-1.0830424726009368896484375e-2, 1.0830424726009368896484375e-2] : | p - f | <= 2^-22.1640625
    // coefficients for exp generated by sollya
    // x^1 : +0x8p-3_f16
    constexpr
    const f16_t exp_c1=+1.00000e+00_f16;
    // x^2 : +0x8p-4_f16
    constexpr
    const f16_t exp_c2=+5.00000e-01_f16;
    static_assert(exp_c1==1.0_f16, "oops");

#if 1
    vf_type x2=xrh*xrh;
    // vf_type p2=horner(xrh, exp_c3, exp_c2);
    vf_type xrlp=xrl +x2*exp_c2;
#if 1
    auto lk=make_fixed_lookup_table<exp_data<f16_t>::EXP_N, f16_t>(idx);
#else
    auto lk=make_variable_lookup_table<f16_t>(idx);
#endif
    const auto& tbl=exp_data<f16_t>::_tbl;
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
            y= th + th*eh;
        }
    }
    return y;
#else
    auto lk=make_variable_lookup_table<f16_t>(idx);
    const auto& tbl=exp_data<f16_t>::_tbl;
    vf_type tl=lk.from(tbl._2_pow_i_n_l);
    vf_type th=lk.from(tbl._2_pow_i_n_h);

    vf_type x2=xrh*xrh;
    // vf_type p2=horner(xrh, exp_c3, exp_c2);
    vf_type xrlp=xrl +x2*exp_c2;
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
    kf = rint(vf_type(x * ctbl::m_1_ln2[0]));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    xrh = hi - kf * ctbl::m_ln2_cw[1];
    vf_type dx = hi-xrh;
    xrl = dx - kf * ctbl::m_ln2_cw[1];
}

template <typename _T>
inline
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vf_type& kf,
                 arg_t<vf_type> xh,
                 arg_t<vf_type> xl)
{
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
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
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vi_type& idx,
                 vi_type& k,
                 arg_t<vf_type> x)
{
    static_assert(exp_data<f16_t>::EXP_N==32,
                 "exp_data<f16_t>::EXP_N==32");
    // x^ : +0xb.8ap+2_f16
    constexpr
    const f16_t _32_ln2=+4.61562e+01_f16;
    // x^ : +0xbp-9_f16
    constexpr
    const f16_t _ln2_32_cw_h=+2.14844e-02_f16;
    // x^ : +0xb.9p-16_f16
    constexpr
    const f16_t _ln2_32_cw_l=+1.76430e-04_f16;
#if 1
    vf_type kf = rint(vf_type(x * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type x32ln2=x*_32_ln2;
    vf_type kf= rint(x32ln2);
    vi_type ki=_T::cvt_f_to_i(x32ln2);
#endif
    idx = ki & int16_t(exp_data<f16_t>::EXP_IDX_MASK);
    k = ki >> int16_t(exp_data<f16_t>::EXP_SHIFT);
    vf_type hi = x - kf * _ln2_32_cw_h;
    xrh = hi - kf * _ln2_32_cw_l;
    vf_type dx = hi-xrh;
    xrl = dx - kf * _ln2_32_cw_l;
}

template <typename _T>
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp_arg(vf_type& xrh,
                 vf_type& xrl,
                 vi_type& idx,
                 vi_type& k,
                 arg_t<vf_type> xh,
                 arg_t<vf_type> xl)
{
    static_assert(exp_data<f16_t>::EXP_N==32,
                 "exp_data<16_t>::EXP_N==32");
    // x^ : +0xb.8ap+2_f16
    constexpr
    const f16_t _32_ln2=+4.61562e+01_f16;
    // x^ : +0xb.18p-9_f16
    constexpr
    const f16_t _ln2_32_h=+2.16675e-02_f16;
    // x^ : -0xd.ep-21_f16
    constexpr
    const f16_t _ln2_32_l=-6.61612e-06_f16;
#if 1
    vf_type kf = rint(vf_type(xh * _32_ln2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xh32ln2=xh*_32_ln2;
    vf_type kf= rint(xh32ln2);
    vi_type ki=_T::cvt_f_to_i(xh32ln2);
#endif
    idx = ki & int32_t(exp_data<f16_t>::EXP_IDX_MASK);
    k = ki >> int32_t(exp_data<f16_t>::EXP_SHIFT);
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
        vmf_type x_small = abs(x) < 0x1p-11_f16;
        xrh = _T::sel(x_small, x, xrh);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf, x_small);
    }
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
    using fc_t = math::func_constants<f16_t>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
exp_px2_k(arg_t<vf_type> xc)
{
    vf_type y;
    using fc_t = math::func_constants<f16_t>;
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);
#if 0
    vmf_type border_case = (x2h == fc_t::exp_hi_inf()) &
        (x2l < 0.0);
    vf_type t= 0x1.01p-17f;
    x2h = _T::sel(border_case, x2h - t, x2h);
    x2l = _T::sel(border_case, x2l + t, x2l);
#endif
    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
    y= _T::sel(x2h >= fc_t::exp_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp2_arg(vf_type& xrh,
                  vf_type& xrl,
                  vi_type& idx,
                  vi_type& k,
                  arg_t<vf_type> x)
{
    static_assert(exp_data<f16_t>::EXP_N == 32,
                  "exp_data<f16_t>::EXP_N == 32 expected");
    constexpr const f16_t _ND=exp_data<f16_t>::EXP_N;
    constexpr const f16_t _1_ND=f16_t(1.0f/float(exp_data<f16_t>::EXP_N));
#if 1
    vf_type kf= rint(vf_type(x*_ND));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xnd=x*_ND;
    vf_type kf= rint(xnd);
    vi_type ki=_T::cvt_f_to_i(xnd);
#endif
    idx= ki & exp_data<f16_t>::EXP_IDX_MASK;
    k= ki >> exp_data<f16_t>::EXP_SHIFT;
    vf_type xr= x- kf*_1_ND;
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
    d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
    // d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0]);
}

template <typename _T>
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp2_arg(vf_type& xrh,
                  vf_type& xrl,
                  vi_type& idx,
                  vi_type& k,
                  arg_t<vf_type> xh,
                  arg_t<vf_type> xl)
{
    static_assert(exp_data<f16_t>::EXP_N==32,
                 "exp_data<f16_t>::EXP_N==32");
    constexpr const f16_t _ND=exp_data<f16_t>::EXP_N;
    constexpr const f16_t _1_ND=f16_t(1.0f/float(exp_data<f16_t>::EXP_N));
#if 1
    vf_type kf= rint(vf_type(xh*_ND));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xhnd=xh*_ND;
    vf_type kf= rint(xhnd);
    vi_type ki=_T::cvt_f_to_i(xhnd);
#endif
    idx= ki & exp_data<f16_t>::EXP_IDX_MASK;
    k= ki >> exp_data<f16_t>::EXP_SHIFT;
    d_ops::add122cond(xrh, xrl, kf*(-_1_ND), xh, xl);
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
    d_ops::mul22(xrh, xrl, xrh, xrl,
                 ctbl::m_ln2[0], ctbl::m_ln2[1]);
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type y;
    vf_type xrh, xrl;
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
    if (_EXP2_M1==false) {
        vi_type idx, ki;
        __reduce_exp2_arg(xrh, xrl, idx, ki, x);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
    } else {
        vf_type kf= rint(vf_type(x));
        vf_type xr = x - kf;
        const f16_t x_small_v=0x1p-11_f16/ctbl::m_ln2[0];
        vmf_type x_small = abs(x) < x_small_v;
        xr = _T::sel(x_small, x*0x1p11_f16, xr);
        // for exp2 mul12 would be sufficient
        d_ops::mul122(xrh, xrl, xr, ctbl::m_ln2[0], ctbl::m_ln2[1]);
        xrh = _T::sel(x_small, xrh*0x1p-11_f16, xrh);
        xrh=_T::sel(iszero(x), x, xrh);
        y=__exp_k<_EXP2_M1>(xrh, xrl, kf, x_small);
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
    using fc_t = math::func_constants<f16_t>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp2_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
exp2_px2_k(arg_t<vf_type> xc)
{
    vf_type y;
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp2_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
    using fc_t = math::func_constants<f16_t>;
    y= _T::sel(x2h >= fc_t::exp2_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp10_arg(vf_type& xrh,
                   vf_type& xrl,
                   vi_type& idx,
                   vi_type& k,
                   arg_t<vf_type> x)
{
    static_assert(exp_data<f16_t>::EXP_N == 32,
                  "exp_data<f16_t>::EXP_N == 32 expected");
    // x^ : +0xd.4ap+3_f16
    constexpr
    const f16_t _32_lg2=+1.06312e+02_f16;
    // x^ : +0xap-10_f16
    constexpr
    const f16_t _lg2_32_cw_h=+9.76562e-03_f16;
    // x^ : -0xb.bep-15_f16
    constexpr
    const f16_t _lg2_32_cw_l=-3.58343e-04_f16;
#if 1
    vf_type kf= rint(vf_type(x*_32_lg2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type x32lg2=x*_32_lg2;
    vf_type kf= rint(x32lg2);
    vi_type ki=_T::cvt_f_to_i(x32lg2);
#endif
    idx= ki & int16_t(exp_data<f16_t>::EXP_IDX_MASK);
    k= ki >> int16_t(exp_data<f16_t>::EXP_SHIFT);
    vf_type hi = x - kf * _lg2_32_cw_h;
    xrh = hi - kf * _lg2_32_cw_l;
    vf_type dx= hi-xrh;
    vf_type cr = dx- kf * _lg2_32_cw_l;
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
    d_ops::mul122(xrh, xrl, xrh, ctbl::m_ln10[0], ctbl::m_ln10[1]);
    xrl += cr * ctbl::m_ln10[0];
}

template <typename _T>
void
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_exp10_arg(vf_type& xrh,
                   vf_type& xrl,
                   vi_type& idx,
                   vi_type& k,
                   arg_t<vf_type> xh,
                   arg_t<vf_type> xl)
{
    static_assert(exp_data<f16_t>::EXP_N==32,
                 "exp_data<f16_t>::EXP_N==32");
    // x^ : +0xd.4ap+3_f16
    constexpr
    const f16_t _32_lg2=+1.06312e+02_f16;
    // x^ : +0x9.a2p-10_f16
    constexpr
    const f16_t _lg2_32_h=+9.40704e-03_f16;
    // x^ : +0x8p-26_f16
    constexpr
    const f16_t _lg2_32_l=+1.19209e-07_f16;
    using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
#if 1
    vf_type kf = rint(vf_type(xh*_32_lg2));
    vi_type ki=_T::cvt_f_to_i(kf);
#else
    vf_type xh32lg2=xh*_32_lg2;
    vf_type kf= rint(xh32lg2);
    vi_type ki=_T::cvt_f_to_i(xh32lg2);
#endif
    idx= ki & int16_t(exp_data<f16_t>::EXP_IDX_MASK);
    k= ki >> int16_t(exp_data<f16_t>::EXP_SHIFT);
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
exp10_k(arg_t<vf_type> x)
{
    vf_type y;
    vf_type xrh, xrl;
    if (_EXP10_M1==false) {
        vi_type idx, ki;
        __reduce_exp10_arg(xrh, xrl, idx, ki, x);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
    } else {
        using ctbl = impl::d_real_constants<d_real<f16_t>, f16_t>;
        vf_type kf = rint(vf_type(x * ctbl::m_1_lg2[0]));
        vf_type hi = x - kf * ctbl::m_lg2_cw[0];
        vf_type xr = hi - kf * ctbl::m_lg2_cw[1];
        vf_type dx= (hi-xr);
        vf_type cr = dx-kf * ctbl::m_lg2_cw[1];
        const f16_t x_small_v=0x1p-11_f16/ctbl::m_ln10[0];
        vmf_type x_small = abs(x) < x_small_v;
        xr = _T::sel(x_small, x*0x1p11_f16, xr);
        // for exp10 mul12 would be sufficient
        d_ops::mul122(xrh, xrl, xr, ctbl::m_ln10[0], ctbl::m_ln10[1]);
        xrl += cr * ctbl::m_ln10[0];
        // do not normalize xrh, xrl
        // d_ops::add12(xrh, xrl, xrh, xrl);
        xrh = _T::sel(x_small, xrh*0x1p-11_f16, xrh);
        xrh = _T::sel(iszero(x), x, xrh);
        y=__exp_k<_EXP10_M1>(xrh, xrl, kf, x_small);
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
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
    using fc_t = math::func_constants<f16_t>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp10_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
exp10_px2_k(arg_t<vf_type> xc)
{
    vf_type y;
    vf_type x2h, x2l;
    d_ops::sqr12(x2h, x2l, xc);

    vf_type xrh, xrl;
    vi_type idx, ki;
    __reduce_exp10_arg(xrh, xrl, idx, ki, x2h, x2l);
    y=__exp_tbl_k(xrh, xrl, idx, ki);
    using fc_t = math::func_constants<f16_t>;
    y= _T::sel(x2h >= fc_t::exp10_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
sig_k(arg_t<vf_type> x)
{
    using fc= func_constants<f16_t>;
    constexpr const f16_t lgf_lo_eq_exp= fc::sig_le_eq_exp();
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
    constexpr const f16_t lgf_hi_one=  fc::sig_hi_one();
    vmf_type x_not_hi= x < lgf_hi_one;
    vf_type rh, rl;
    // avoid multiplication of subnormal numbers
    vmf_type avoid_sn= xm & x_not_hi;
    vf_type th=_T::sel_val_or_zero(avoid_sn, eh);
    vf_type tl=_T::sel_val_or_zero(avoid_sn, el);
    tl *= sc.f0();
    tl *= sc.f1();
    d_ops::add122cond(rh, rl, f16_t(1.0), th, tl);
    d_ops::rcp21(rh, rh, rl);
    vf_type r = _T::sel(xm, rh, eh);
    r = _T::sel(x_not_hi, r, f16_t(1.0));
    return r;
}

template <typename _T>
template <enum cftal::math::elem_func_core<cftal::f16_t, _T>::hyperbolic_func _F>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
sinh_cosh_k(arg_t<vf_type> xc)
{
    static_assert(_F != hyperbolic_func::c_tanh);

    vf_type x= abs(xc);
    vf_type res;
#if 1
    vmf_type x_small;
    // x^ : +0x8p-3_f16
    constexpr
    const f16_t sinh_i0_right=+1.00000e+00_f16;
    if (_F == hyperbolic_func::c_sinh) {
        x_small= x <= sinh_i0_right;
        if (__unlikely(_T::any_of_vmf(x_small))) {
            // [0, 1] : | p - f | <= 2^-16.015625
            // coefficients for sinh generated by sollya
            // x^1 : +0x8p-3_f16
            constexpr
            const f16_t sinh_c1=+1.00000e+00_f16;
            // x^3 : +0xa.aap-6_f16
            constexpr
            const f16_t sinh_c3=+1.66626e-01_f16;
            // x^5 : +0x8.c4p-10_f16
            constexpr
            const f16_t sinh_c5=+8.56018e-03_f16;
            static_assert(sinh_c1==1.0_f16, "constraint violated");

            constexpr
            static const f16_t cs[]= {
                sinh_c5, sinh_c3
            };
            vf_type x2=x*x;
            res = x + x*(x2*horner(x2, cs));
        }
    }
    // x^ : +0x8p-3_f16
    constexpr
    const f16_t cosh_i0_right=+1.00000e+00_f16;
    if (_F == hyperbolic_func::c_cosh) {
        x_small= x <= cosh_i0_right;
        if (__unlikely(_T::any_of_vmf(x_small))) {
            // [0, 1] : | p - f | <= 2^-13.58203125
            // coefficients for cosh generated by sollya
            // x^0 : +0x8p-3_f16
            constexpr
            const f16_t cosh_c0=+1.00000e+00_f16;
            // x^2 : +0xf.fcp-5_f16
            constexpr
            const f16_t cosh_c2=+4.99512e-01_f16;
            // x^4 : +0xb.22p-8_f16
            constexpr
            const f16_t cosh_c4=+4.34875e-02_f16;


            constexpr
            static const f16_t cs[]= {
                cosh_c4, cosh_c2, cosh_c0
            };
            vf_type x2=x*x;
            res = horner(x2, cs);
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
        // fpprec: 32;
        // bfloat(rhs(solve(2^-14*%e^x=%e^(-x), x)[2]));
        constexpr const f16_t
        x_medium_max = 4.8520302639196171659206248502072e0_f16;
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
            f16_t dv= _F == hyperbolic_func::c_sinh ? -0.25 : 0.25;
            d_ops::div122(nyh, nyl, dv, yh, yl);
            static_cast<void>(k0);
#else
            vf_type nxrh, nxrl;
            vi_type nk, nidx;
            // base_type::__reduce_exp_arg(nxrh, nxrl, nidx, nk, -x);
            nxrh = -xrh;
            nxrl = -xrl;
            vi_type s=-((k0<<int16_t(exp_data<f16_t>::EXP_SHIFT))+idx);
            nk = s >> int16_t(exp_data<f16_t>::EXP_SHIFT);
            nidx = s & int16_t(exp_data<f16_t>::EXP_IDX_MASK);

            nk -= 1;
            vf_type nyh, nyl;
            nyh = __exp_tbl_k<result_prec::medium>(nxrh, nxrl, nidx, &nyl);
            // we know k < 14
            // create the scaling factor, produce a negative sign
            // for sinh because we want to subtract %e^-x
            const int16_t bias_with_sgn=
                _F == hyperbolic_func::c_sinh ? _T::bias()+32 : _T::bias();
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
    const f16_t sinh_i0_right=+1.7328679562e-01f;

    if (_F == hyperbolic_func::c_sinh) {
        x_tiny= x <= sinh_i0_right;
        if (__unlikely(_T::any_of_vmf(x_tiny))) {
            // [0, 0.17328679561614990234375] : | p - f | <= 2^-34.921875
            // coefficients for sinh generated by sollya
            // x^1 : +0x8p-3f
            constexpr
            const f16_t sinh_c1=+1.0000000000e+00f;
            // x^3 : +0xa.aaaa5p-6f
            constexpr
            const f16_t sinh_c3=+1.6666658223e-01f;
            // x^5 : +0x8.8ac83p-10f
            constexpr
            const f16_t sinh_c5=+8.3419112489e-03f;

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

        // fpprec: 32;
        // bfloat(rhs(solve(2^-14*%e^x=%e^(-x), x)[2]));
        constexpr const f16_t
        x_medium_max = 4.8520302639196171659206248502072e0_f16;
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
            f16_t dv= _F == hyperbolic_func::c_sinh ? -0.25f : 0.25f;
            d_ops::div122(nyh, nyl, dv, yh, yl);
            static_cast<void>(k0);
#else
            vf_type nxrh, nxrl;
            vi_type nk, nidx;
            // base_type::__reduce_exp_arg(nxrh, nxrl, nidx, nk, -x);
            nxrh = -xrh;
            nxrl = -xrl;
            vi_type s=-((k0<<exp_data<f16_t>::EXP_SHIFT)+idx);
            nk= s >> exp_data<f16_t>::EXP_SHIFT;
            nidx= s & exp_data<f16_t>::EXP_IDX_MASK;
            nk -= 1;

            vf_type nyh, nyl;
            nyh = __exp_tbl_k<result_prec::medium>(nxrh, nxrl, nidx, &nyl);
            // we know k < 14
            // create the scaling factor, produce a negative sign
            // for sinh because we want to subtract %e^-x
            const int32_t bias_with_sgn=
                _F == hyperbolic_func::c_sinh ? _T::bias()+32 : _T::bias();
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
cosh_k(arg_t<vf_type> x)
{
    return sinh_cosh_k<hyperbolic_func::c_cosh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
sinh_k(arg_t<vf_type> x)
{
    return sinh_cosh_k<hyperbolic_func::c_sinh>(x);
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
tanh_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    using fc=func_constants<f16_t>;
    vf_type tanh_x=1.0_f16;
    // x^ : +0xb.18p-9_f16
    constexpr
    const f16_t tanh_i0_right=+2.16675e-02_f16;
    vmf_type x_tiny = xa <= tanh_i0_right;
    if (__unlikely(_T::any_of_vmf(x_tiny))) {
        // [0, 2.166084945201873779296875e-2] : | p - f | <= 2^-18.1640625
        // coefficients for tanh generated by sollya
        // x^1 : +0x8p-3_f16
        constexpr
        const f16_t tanh_c1=+1.00000e+00_f16;
        static_assert(tanh_c1==1.0_f16, "oops");
        tanh_x=_T::sel(x_tiny, xa, tanh_x);
    }
    vmf_type x_medium=(xa > tanh_i0_right) & (xa<fc::tanh_one());
    if (__likely(_T::any_of_vmf(x_medium))) {
        const f16_t tmax=2.0f*fc::tanh_one();
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
        d_ops::add212(exm1, exm1l, ex, exl, -1.0_f16);
        vf_type exp1, exp1l;
        d_ops::add212(exp1, exp1l, ex, exl, 1.0_f16);
        vf_type tanh_h;
        d_ops::div21(tanh_h, exm1, exm1l, exp1, exp1l);
        tanh_x = _T::sel(x_medium, tanh_h, tanh_x);
    }
    tanh_x=copysign(tanh_x, xc);
    return tanh_x;
}

template <typename _T>
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_log_arg(vf_type& xr,
                 arg_t<vf_type> xc)
{
    // MSQRT2/2
    constexpr
    const bytes2 offs=as<int16_t>(7.07031e-01_f16);

    using fc = func_constants<f16_t>;
    vmf_type is_denom=xc < fc::min_normal();
    vf_type x=_T::sel(is_denom, xc*0x1p12f, xc);
    vi_type k=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                         vi_type(-12-_T::bias()),
                         vi_type(-_T::bias()));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    constexpr const int16_t delta=as<int16_t>(1.0_f16) - offs.s16();
    hx += delta;
    k += (hx>>10);
    hx = (hx & sig_f16_msk::v.s16()) + offs.s16();
    xr = _T::as_float(hx);
    return k;
}

template <typename _T>
inline
typename
cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__reduce_log_arg(vf_type& xr,
                 vi_type& idx,
                 arg_t<vf_type> xc)

{
    // MSQRT2/2
    constexpr
    const bytes2 offs=as<int16_t>(7.07031e-01_f16);
    using fc = func_constants<f16_t>;
    vmf_type is_denom=xc < fc::min_normal();
    vf_type x=_T::sel(is_denom, xc*0x1p12f, xc);
    vi_type k=_T::sel_vi(_T::vmf_to_vmi(is_denom),
                         vi_type(-12-_T::bias()),
                         vi_type(-_T::bias()));
    vi_type hx = _T::as_int(x);
    // reduce x into [offs, 2*offs]
    constexpr const int16_t delta=as<int16_t>(1.0_f16) - offs.s16();
    hx += delta;
    k += (hx>>10);
    vi_type m = (hx&0x03ff);
    hx = m + offs.s16();
    idx=(m >> (10-pow_log_data<f16_t>::LOG_SHIFT));
    xr = _T::as_float(hx);
    return k;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__log_poly_k_poly(arg_t<vf_type> r, arg_t<vf_type> r2)
{
    // [-0.29296875, 0.4140625] : | p - f | <= 2^-17.9375
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3_f16
    constexpr
    const f16_t log_c1=+1.00000e+00_f16;
    // x^2 : -0x8p-4_f16
    constexpr
    const f16_t log_c2=-5.00000e-01_f16;
    // x^3 : +0xa.a6p-5_f16
    constexpr
    const f16_t log_c3=+3.32764e-01_f16;
    // x^4 : -0x8.14p-5_f16
    constexpr
    const f16_t log_c4=-2.52441e-01_f16;
    // x^5 : +0xep-6_f16
    constexpr
    const f16_t log_c5=+2.18750e-01_f16;
    // x^6 : -0x9.68p-6_f16
    constexpr
    const f16_t log_c6=-1.46973e-01_f16;
    static_assert(log_c1==1.0_f16, "constraint violated");
    static_assert(log_c2==-0.5_f16, "constraint violated");
    constexpr
    static const f16_t ci[]={
        log_c6, log_c5, log_c4, log_c3
    };
    vf_type p= horner2(r, r2, ci);
    return p;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__log_poly_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0_f16;

    // log(x) = kf*ln2 + r + r2*c2 + r3*p
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    using ctbl=impl::d_real_constants<d_real<f16_t>, f16_t>;
    vf_type l, e;
    d_ops::add12(l, e, kf* ctbl::m_ln2_cw[0], r);
    constexpr const f16_t log_c2 = -0.5_f16;
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
template <typename cftal::math::elem_func_core<cftal::f16_t, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vdf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__log_tbl_k2(arg_t<vf_type> r, arg_t<vf_type> rl,
             arg_t<vf_type> log_c_h, arg_t<vf_type> log_c_l,
             arg_t<vf_type> kf)
{
    // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-25.9453125
    // coefficients for log_hp generated by sollya
    // x^1 : +0x8p-3_f16
    constexpr
    const f16_t log_hp_c1=+1.00000e+00_f16;
    // x^2 : -0x8p-4_f16
    constexpr
    const f16_t log_hp_c2=-5.00000e-01_f16;
    // x^3 : +0xa.aap-5_f16
    constexpr
    const f16_t log_hp_c3=+3.33252e-01_f16;
    static_assert(log_hp_c1 == 1.0f);
    using ctbl=impl::d_real_constants<d_real<f16_t>, f16_t>;
    vf_type ph, pl;
    if (_P == result_prec::high) {
        vf_type p=log_hp_c3;
        horner_comp_quick(ph, pl, r, p, log_hp_c2);
        d_ops::unorm_mul22(ph, pl, r, rl, ph, pl);
        d_ops::add122(ph, pl, log_hp_c1, ph, pl);
    } else {
        // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-19.5625
        // coefficients for log generated by sollya
        // x^1 : +0x8p-3_f16
        constexpr
        const f16_t log_c1=+1.00000e+00_f16;
        // x^2 : -0x8p-4_f16
        constexpr
        const f16_t log_c2=-5.00000e-01_f16;
        vf_type p=log_c2;
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
template <typename cftal::math::elem_func_core<cftal::f16_t, _T>::result_prec _P>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vdf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__log_tbl_k2(arg_t<vf_type> xc, arg_t<vf_type> xcl)
{
    vf_type xrh, inv_c, log_c_h, log_c_l;
    vi_type idx;
    vi_type ki=__reduce_log_arg(xrh, idx, xc);
    auto lck=make_variable_lookup_table<f16_t>(idx);
    const auto& tbl=pow_log_data<f16_t>::_tbl;
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

#define FORCE_FMA 0
template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vdf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__log_tbl_k12(arg_t<vf_type> xc)
{
    vf_type xr, inv_c, log_c_h, log_c_l;
    vi_type idx;
    vi_type ki=__reduce_log_arg(xr, idx, xc);
    auto lck=make_variable_lookup_table<f16_t>(idx);
    const auto& tbl=pow_log_data<f16_t>::_tbl;
    inv_c =lck.from(tbl._p_inv_c);
    log_c_h=lck.from(tbl._p_log_c_h);
    log_c_l=lck.from(tbl._p_log_c_l);
    vf_type kf=_T::cvt_i_to_f(ki);

    using ctbl=impl::d_real_constants<d_real<f16_t>, f16_t>;
    vf_type r;
    vf_type rh, rl;
    if (FORCE_FMA || d_real_traits<vf_type>::fma == true) {
        r = xr * inv_c - 1.0_f16;
    } else {
        // because our invc contains to much bits we have to use mul12 here
#if 1
        d_ops::mul12(rh, rl, xr, inv_c);
        rh -= 1.0_f16;
        r = rh + rl;
#else
        d_real_traits<vf_type>::split(xr, rh, rl);
        rh *= inv_c;
        rl *= inv_c;
        rh -= 1.0_f16;
        r = rh + rl;
#endif
    }
    // [-1.5625e-2, 1.5625e-2] : | p - f | <= 2^-25.9453125
    // coefficients for log_hp generated by sollya
    // x^1 : +0x8p-3_f16
    constexpr
    const f16_t log_hp_c1=+1.00000e+00_f16;
    // x^2 : -0x8p-4_f16
    constexpr
    const f16_t log_hp_c2=-5.00000e-01_f16;
    // x^3 : +0xa.aap-5_f16
    constexpr
    const f16_t log_hp_c3=+3.33252e-01_f16;
    static_assert(log_hp_c1 == 1.0_f16);
    static_assert(log_hp_c2 ==-0.5_f16);
    vf_type r2=r*r;
    vf_type p=log_hp_c3;

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
    if (FORCE_FMA || d_real_traits<vf_type>::fma == true) {
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__log1p_poly_k(arg_t<vf_type> xc)
{
    vf_type x=xc;
    vf_type u=1.0_f16+xc;
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, u);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0_f16;

#if 1
    // log(x) = kf*ln2 + r + r2*c2 + r3*p
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    using ctbl=impl::d_real_constants<d_real<f16_t>, f16_t>;
    vf_type l, e;
    d_ops::add12(l, e, kf* ctbl::m_ln2_cw[0], r);
    constexpr const f16_t log_c2 = -0.5_f16;
    e += log_c2*r2l;
    vf_type r2c2=log_c2 * r2;
    vf_type ei;
    d_ops::add12(l, ei, l, r2c2);
    e += ei;
    d_ops::add12(l, ei, l, kf*ctbl::m_ln2_cw[1]);
    e += ei;

    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0_f16),
                            1.0_f16-(u-x), x-(u-1.0_f16));
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

    using ctbl=impl::d_real_constants<d_real<f16_t>, f16_t>;
    vf_type lh, ll;
    d_ops::add12(lh, ll, kf*ctbl::m_ln2_cw[0], r);
    lh+= p*r2+(c+(ll + kf * ctbl::m_ln2_cw[1]));
    return lh;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
log1p_k(arg_t<vf_type> xc)
{
    return __log1p_poly_k(xc);
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
log_k(arg_t<vf_type> xc)
{
#if 1
    return __log_poly_k(xc);
#else
    auto t=__log_tbl_k12(xc);
    return t[0]+t[1];
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__mul_invln2_add_kf(arg_t<vf_type> l,
                    arg_t<vf_type> ll,
                    arg_t<vf_type> kf)
{
    // x^ : +0xb.8p-3_f16
    constexpr
    const f16_t invln2hi=+1.43750e+00_f16;
    // x^ : +0xa.a4p-11_f16
    constexpr
    const f16_t invln2lo=+5.19562e-03_f16;
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
log2_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0_f16;

    // log2(x) = kf + (r + r2*c2 + r3*p)/ln2;
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    constexpr const f16_t log_c2=-0.5_f16;
    vf_type l= log_c2*r2;
    vf_type ei;
    d_ops::add12(l, ei, r, l);
    vf_type ll=(ei + log_c2*r2l) + r2*(r*p);
    vf_type res=__mul_invln2_add_kf(l, ll, kf);
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
log2p1_k(arg_t<vf_type> xc)
{
    vf_type u=1.0_f16+xc;
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, u);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0_f16;

    // log2p1(x) = kf + (r + r2*c2 + r3*p)/ln2
    vf_type abs_xc= abs(xc);
    vmf_type xc_near_zero=abs_xc < 0x1p-3_f16;
    r = _T::sel(xc_near_zero, xc, r);

    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);

    constexpr const f16_t log_c2 = -0.5f;
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
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0_f16),
                            1.0_f16-(u-xc), xc-(u-1.0_f16));
    c_k_2 /= u;
    // vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    vf_type c = _T::sel_zero_or_val(xc_near_zero, c_k_2);

    vf_type ei;
    d_ops::add12(l, ei, l, c);
    e += ei;
    vf_type ll=e + r2*(r*p);

    vmf_type xc_tiny= abs_xc <
        0x1p2_f16*func_constants<f16_t>::min_normal();
        // 0x1p-11_f16;
    l = _T::sel(xc_tiny, xc*0x1p11_f16, l);
    ll = _T::sel_zero_or_val(xc_tiny, ll);
    vf_type res=__mul_invln2_add_kf(l, ll, kf);
    res = _T::sel(xc_tiny, res*0x1p-11_f16, res);
    res= _T::sel(iszero(xc), xc, res);
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__mul_invln10_add_kflg2(arg_t<vf_type> l,
                        arg_t<vf_type> ll,
                        arg_t<vf_type> kf)
{
    // x^ : +0xd.cp-5_f16
    constexpr
    const f16_t invln10hi=+4.29688e-01_f16;
    // x^ : +0x9.7p-11_f16
    constexpr
    const f16_t invln10lo=+4.60815e-03_f16;

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
    using ctbl=impl::d_real_constants<d_real<f16_t>, f16_t>;
    vf_type res, t;
    d_ops::add12(res, t, kf*ctbl::m_lg2_cw[0], l0);
    res += (t +(l1+l2+l3)) + kf * ctbl::m_lg2_cw[1];
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
log10_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0_f16;

    // log10(x) = kf*lg(2) + (r + r2*c2 + r3*p)/ln10;
    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);
    constexpr const f16_t log_c2=-0.5_f16;
    vf_type l= log_c2*r2;
    vf_type ei;
    d_ops::add12(l, ei, r, l);
    vf_type ll=(ei + log_c2*r2l) + r2*(r*p);
    vf_type res=__mul_invln10_add_kflg2(l, ll, kf);
    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
log10p1_k(arg_t<vf_type> xc)
{
    vf_type u=1.0_f16+xc;
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, u);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type r=xr-1.0_f16;

    vf_type abs_xc=abs(xc);
    vmf_type xc_near_zero=abs_xc < 0x1p-3_f16;
    r = _T::sel(xc_near_zero, xc, r);

    vf_type r2, r2l;
    d_ops::sqr12(r2, r2l, r);
    vf_type p= __log_poly_k_poly(r, r2);

    constexpr const f16_t log_c2 = -0.5_f16;
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
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0_f16),
                            1.0_f16-(u-xc), xc-(u-1.0_f16));
    c_k_2 /= u;
    // vf_type c = _T::sel_val_or_zero(kf < vf_type(25.0f), c_k_2);
    vf_type c = _T::sel_zero_or_val(xc_near_zero, c_k_2);

    vf_type ei;
    d_ops::add12(l, ei, l, c);
    e += ei;
    vf_type ll=e + r2*(r*p);

    vmf_type xc_tiny= abs_xc <
        // 0x1.0p3_f16*func_constants<f16_t>::min_normal();
        0x1p-11_f16;
    l = _T::sel(xc_tiny, xc*0x1p11_f16, l);
    ll = _T::sel_zero_or_val(xc_tiny, ll);
    vf_type res =__mul_invln10_add_kflg2(l, ll, kf);
    res = _T::sel(xc_tiny, res*0x1p-11_f16, res);
    res= _T::sel(iszero(xc), xc, res);

    return res;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
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

    using fc=func_constants<f16_t>;
    const vf_type& dh = ylnx[0];
    const vf_type& dl = ylnx[1];
    constexpr
    const f16_t exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(
        (dh < exp_lo_zero) | ((dh == exp_lo_zero) & (dl <= 0.0_f16)),
        res);
    constexpr
    const f16_t exp_hi_inf= fc::exp_hi_inf();
    res = _T::sel(
        (dh > exp_hi_inf) | ((dh == exp_hi_inf) & (dl >= 0.0_f16)),
        _T::pinf(), res);
    // guess the result if the calculation failed
    vmf_type rnan=isnan(dh);
    vmf_type abs_x_lt_1 = abs_x < 1.0_f16;
    vmf_type y_gt_1 = y > 1.0_f16;
    res = _T::sel(rnan, _T::pinf(), res);
    res = _T::sel_zero_or_val(rnan &
                              ((abs_x_lt_1 & y_gt_1) |
                               ((~abs_x_lt_1) & (~y_gt_1))),
                              res);
    return res;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::pow_k2_result
cftal::math::elem_func_core<cftal::f16_t, _T>::
pow_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
       arg_t<vf_type> yh, arg_t<vf_type> yl)
{
    vdf_type abs_x= select(xh > 0.0_f16,
                           vdf_type(xh, xl), vdf_type(-xh, -xl));
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
powi_k(arg_t<vf_type> x, arg_t<vi_type> e)
{
    vf_type abs_x= abs(x);
    vdf_type lnx= __log_tbl_k12(abs_x);
    vi_type eh=e & 0xff00, el= e - eh;
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

    using fc=func_constants<f16_t>;
    const vf_type& dh = ylnx[0];
    const vf_type& dl = ylnx[1];
    constexpr
    const f16_t exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel_zero_or_val(
        (dh < exp_lo_zero) | ((dh == exp_lo_zero) & (dl <= 0.0_f16)),
        res);
    if (_CALC_ROOT==false) {
        constexpr
        const f16_t exp_hi_inf= fc::exp_hi_inf();
        res = _T::sel(
            (dh > exp_hi_inf) | ((dh == exp_hi_inf) & (dl >= 0.0_f16)),
            _T::pinf(), res);
    }
    // guess the result if the calculation failed, because 16 bit integers
    // are really large compared to fp16
    if (_CALC_ROOT==false) {
        vmf_type rnan=isnan(dh);
        vmf_type abs_x_lt_1 = abs_x < 1.0_f16;
        vmf_type y_gt_1 = _T::vmi_to_vmf(e > 1.0);
        res = _T::sel(rnan, _T::pinf(), res);
        res = _T::sel_zero_or_val(rnan &
                                ((abs_x_lt_1 & y_gt_1) |
                                ((~abs_x_lt_1) & (~y_gt_1))),
                                res);
    }
    return res;
}

// Local Variables:
// mode: c++
// end:
#endif
