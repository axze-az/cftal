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
#if !defined (__CFTAL_MATH_ELEM_FUNC_LOPREC_CORE_F32_H__)
#define __CFTAL_MATH_ELEM_FUNC_LOPREC_CORE_F32_H__ 1

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
#include <cftal/as.h>
#include <cftal/std_types.h>
#include <cftal/math/elem_func.h>
#include <cftal/math/func_traits_f32_s32.h>
#include <cftal/math/func_data.h>
#include <cftal/math/misc.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/payne_hanek.h>
#include <cftal/mem.h>
#include <cftal/vec_t_n.h>

namespace cftal {
    namespace math {

        // specialization of elem_func_core for double and different
        // traits
        template <typename _T>
        struct elem_func_loprec_core<float, _T> {
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vdf_type = typename _T::vdf_type;

            using d_ops=d_real_ops<vf_type,
                                   d_real_traits<vf_type>::fma>;

            using f16_traits= typename _T::vlf_traits;
            using vlf_type = typename f16_traits::vf_type;
            using vmlf_type = typename f16_traits::vmf_type;

            // as frexp but without checking for 0, inf, nan
            static
            vi_type
            __frexp_k(vf_type& m, arg_t<vf_type> x);

            static
            vf_type
            rsqrt_k(arg_t<vf_type> x);

            static
            vf_type
            cbrt_k(arg_t<vf_type> x);

            // return y*2^k
            static
            vf_type
            __mul_two_pow(arg_t<vf_type> y,
                          arg_t<vi_type> k);

            // return y*2^rint(kf)
            static
            vf_type
            __mul_two_pow(arg_t<vf_type> y,
                          arg_t<vf_type> kf);

            // arguments are the reduced xr in
            // [-log(2)/2, log(2)/2], and the argument
            // k as argument for __mul_two_pow
            // x is the unreduced argument
            // calculates %e^(xrh)*2^k - 1 if exp_m1 is true,
            // %e^(xrh+xrl)*2^k otherwise
            template <bool _EXP_M1>
            static
            vf_type
            __exp_k(arg_t<vf_type> xr,
                    arg_t<vf_type> kfd, arg_t<vf_type> x);

            // calculates %e^xr for xr in [-log(2)/(2*N),
            // log(2)/(2*N)], idx is the table index
            static
            vf_type
            __exp_tbl_k(arg_t<vf_type> xr,
                        arg_t<vi_type> idx);
            // calculates 2^k*%e^xr for xr in [-log(2)/(2*N),
            // log(2)/(2*N)], idx is the table index,
            static
            vf_type
            __exp_tbl_k(arg_t<vf_type> xr,
                        arg_t<vi_type> idx,
                        arg_t<vi_type> k);

            // argument reduction for %e^(x)
            // return 2^k * (xr) with xr in
            // [-log(2)/2, log(2)/2] for calling __exp_k
            static
            void
            __reduce_exp_arg(vf_type& xr,
                             vf_type& kf,
                             arg_t<vf_type> x);

            // argument reduction for %e^(x)
            // return 2^k * (xr) with xr in
            // [-log(2)/(2*N), log(2)/(2*N)] for calling __exp_tbl_k
            static
            void
            __reduce_exp_arg(vf_type& xr,
                             vi_type& idx,
                             vi_type& k,
                             arg_t<vf_type> x);

            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            template <bool _EXP2_M1>
            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            template <bool _EXP2_M1>
            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            enum hyperbolic_func {
                c_sinh,
                c_cosh,
                c_tanh
            };

            template <hyperbolic_func _F>
            static
            vf_type
            sinh_cosh_k(arg_t<vf_type> xc);

            static
            vf_type
            tanh_k(arg_t<vf_type> xc);

            static
            vi_type
            __reduce_log_arg(vf_type& xr,
                             arg_t<vf_type> x);

            enum log_func {
                c_log_e,
                c_log_2,
                c_log_10
            };

            template <log_func _LFUNC>
            static
            vf_type
            __log_k(arg_t<vf_type> xc);

            template <log_func _LFUNC>
            static
            vf_type
            __log1p_k(arg_t<vf_type> xc);


            template <log_func _LFUNC>
            static
            vf_type
            __log_k12(arg_t<vf_type> xc);

            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y,
                  vf_type* p_ylnx=nullptr);

            template <bool _CALC_ROOT>
            static
            vf_type
            powi_k(arg_t<vf_type> x, arg_t<vi_type> e,
                  vf_type* p_ylnx=nullptr);


            static
            vi_type
            __reduce_trig_arg(vf_type& xr, arg_t<vf_type> x);

            static
            void
            __sin_cos_k(arg_t<vf_type> x, arg_t<vi_type> q,
                        vf_type* s, vf_type* c);

            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            static
            vf_type
            __tan_k(arg_t<vf_type> x, arg_t<vi_type> q);

            static
            vf_type
            tan_k(arg_t<vf_type> x);

            static
            vi_type
            __reduce_trigpi_arg(vf_type& __restrict xrh,
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
            vf_type
            __atan_0_1_k(arg_t<vf_type> x);

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
            hypot_k(arg_t<vf_type> xc, arg_t<vf_type> yc);

        };
    }
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vi_type
cftal::math::elem_func_loprec_core<float, _T>::
__frexp_k(vf_type& m , arg_t<vf_type> x)
{
    constexpr const int32_t neg_bias_p_1=-_T::bias()+1;
    // reinterpret a integer
    vi_type i=_T::as_int(x);
    // exponent:
    vi_type e = ((i >> 23) & 0xff) + neg_bias_p_1;
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
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    vf_type y=::cftal::native::rsqrt_11b(x);
    y = impl::root_r2::order2<float, false>(y, x);
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
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
    vmi_type r_gt_z = r > 0;
    vi_type e3c= e3 + _T::sel_val_or_zero_vi(r_gt_z, 1);
    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 3
    // 1    0.25    -2           -2
    // 2    0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
    vi_type rc= r + _T::sel_val_or_zero_vi(r_gt_z, -3);
    vi_type rc_exp= rc << 23;
    // correction of the exponent of mm0:
    vi_type mm0i=as<vi_type>(mm0) + rc_exp;
    mm0=as<vf_type>(mm0i);

    // [0.125, 1] : | p - f | <= 2^-5.97265625
    // coefficients for cbrt generated by sollya
    // x^0 : +0xc.3335fp-5f
    constexpr
    const float cbrt_c0=+3.8125130534e-01f;
    // x^1 : +0x8.94134p-3f
    constexpr
    const float cbrt_c1=+1.0723023415e+00f;
    // x^2 : -0xf.05d38p-5f
    constexpr
    const float cbrt_c2=-4.6946120262e-01f;
    constexpr static const float ci[]={
        cbrt_c2, cbrt_c1, cbrt_c0
    };
    vf_type mm = horner(mm0, ci);
    // round mm to 3 bits = int(11/3)
    // mm=round_to_nearest_even_last_bits<24-3>(mm);
    // iterate once
    mm = impl::root_3::order4<float>(mm, mm0);
    // no denormal results are possible
    vi_type e3c_exp=(e3c<<23);
    vi_type mmi=as<vi_type>(mm) + e3c_exp;
    mm=as<vf_type>(mmi);
    mm |= (xc & sign_f32_msk::v.f32());
    return mm;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__mul_two_pow(arg_t<vf_type> y, arg_t<vi_type> k)
{
    vi_type ep(k << 23);
    vi_type yi=as<vi_type>(y) + ep;
    vf_type ys = as<vf_type>(yi);
    return ys;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__mul_two_pow(arg_t<vf_type> y, arg_t<vf_type> kf)
{
    vi_type k=_T::cvt_f_to_i(kf);
    return __mul_two_pow(y, k);
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__exp_k(arg_t<vf_type> xrd, arg_t<vf_type> kfd,
        arg_t<vf_type> x)
{
    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-17.015625
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3f
    constexpr
    const float exp_c0=+1.0000000000e+00f;
    // x^1 : +0x8p-3f
    constexpr
    const float exp_c1=+1.0000000000e+00f;
    // x^2 : +0x8.0035ap-4f
    constexpr
    const float exp_c2=+5.0005114079e-01f;
    // x^3 : +0xa.b8e55p-6f
    constexpr
    const float exp_c3=+1.6753514111e-01f;
    // x^4 : +0xa.9130dp-8f
    constexpr
    const float exp_c4=+4.1277933866e-02f;
    static_assert(exp_c0 == 1.0f, "oops");
    static_assert(exp_c1 == 1.0f, "oops");

    constexpr
    static const float ci[]= {
        exp_c4, exp_c3, exp_c2
    };
    vf_type xrd2=xrd * xrd;
    vf_type yd= horner2(xrd, xrd2, ci)*xrd2 + xrd;
    yd+= exp_c0;
    yd=__mul_two_pow(yd, kfd);
    if (_EXP_M1 == true) {
        yd -= exp_c0;
        yd= _T::sel(abs(x) < 0x1.0p-11f, x, yd);
        // to reduce the number of differences to 910 at the cost of
        // assymmetric deviations:
        // yd= _T::sel(abs(x) < 0x1.68p-11f, x, yd);
    }
    return yd;
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__exp_tbl_k(arg_t<vf_type> xr, arg_t<vi_type> idx)
{
#if defined (__tune_znver2__) || defined(__tune_znver3__)
    auto lk=make_fixed_lookup_table<exp_data<float>::EXP_N, float>(idx);
#else
    auto lk=make_variable_lookup_table<float>(idx);
#endif
    const auto& tbl=exp_data<float>::_tbl;
    vf_type th=lk.from(tbl._2_pow_i_n_h);

    // [-1.0830424726009368896484375e-2, 1.0830424726009368896484375e-2] : | p - f | <= 2^-14.05078125
    // coefficients for exp generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float exp_c1=+1.0000000000e+00f;
    static_assert(exp_c1==1.0f, "oops");
    // vf_type x2=xr*xr;
    // vf_type p= horner(xr, exp_c3, exp_c2);
    // vf_type p= xr;
    // vf_type eh=xr + x2*p;
    vf_type eh=xr;
    vf_type yd=th + th*eh;
    return yd;
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__exp_tbl_k(arg_t<vf_type> xr, arg_t<vi_type> idx, arg_t<vi_type> ki)
{
    vf_type yd=__exp_tbl_k(xr, idx);
    return __mul_two_pow(yd, ki);
}

template <typename _T>
void
cftal::math::elem_func_loprec_core<float, _T>::
__reduce_exp_arg(vf_type& xr, vf_type& kf, arg_t<vf_type> xd)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    kf= rint(vf_type(xd * ctbl::m_1_ln2[0]));
    xr= xd - kf * ctbl::m_ln2[0];
}

template <typename _T>
void
cftal::math::elem_func_loprec_core<float, _T>::
__reduce_exp_arg(vf_type& xr, vi_type& idx, vi_type& k, arg_t<vf_type> xd)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    static_assert(exp_data<float>::EXP_N==32,
                 "exp_data<float>::EXP_N==32");
    // N
    const float _N=exp_data<float>::EXP_N;
    // N/ln(2)
    const float _32_ln2=_N * ctbl::m_1_ln2[0];
    // ln2/N;
    const float _ln2_32=ctbl::m_ln2[0] * (1.0/_N);
    vf_type kf= rint(vf_type(xd * _32_ln2));
    xr= xd - kf * _ln2_32;
    vi_type ki=cvt<vi_type>(kf);
    idx = ki & exp_data<float>::EXP_IDX_MASK;
    k = ki >> exp_data<float>::EXP_SHIFT;
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
exp_k(arg_t<vf_type> xc)
{
    vf_type yd;
    if (0 /*_EXP_M1==false*/) {
        vi_type idx, ki;
        vf_type xrd;
        __reduce_exp_arg(xrd, idx, ki, xc);
        yd=__exp_tbl_k(xrd, idx, ki);
    } else {
        vf_type xr, kf;
        __reduce_exp_arg(xr, kf, xc);
        yd=__exp_k<_EXP_M1>(xr, kf, xc);
    }
    return yd;
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
exp2_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type xd=xc*ctbl::m_ln2[0];
    vf_type yd=exp_k<_EXP2_M1>(xd);
    return yd;
}

template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
exp10_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type xd=xc*ctbl::m_ln10[0];
    vf_type yd=exp_k<_EXP10_M1>(xd);
    return yd;
}

template <typename _T>
template <enum cftal::math::elem_func_loprec_core<float, _T>::hyperbolic_func _F>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
sinh_cosh_k(arg_t<vf_type> xc)
{
    static_assert(_F != hyperbolic_func::c_tanh);

    vf_type x= abs(xc);
    vf_type xr;
    vmf_type x_small;
    vf_type res;

    // x^ : +0x8p-3f
    constexpr
    const float sinh_i0_right=+1.0000000000e+00f;
    if (_F == hyperbolic_func::c_sinh) {
        x_small= x <= sinh_i0_right;
        if (__likely(_T::any_of_vmf(x_small))) {
            // [0, 1] : | p - f | <= 2^-17.140625
            // coefficients for sinh generated by sollya
            // x^1 : +0x8.00031p-3f
            constexpr
            const float sinh_c1=+1.0000058413e+00f;
            // x^3 : +0xa.a8dd5p-6f
            constexpr
            const float sinh_c3=+1.6655667126e-01f;
            // x^5 : +0x8.d6c43p-10f
            constexpr
            const float sinh_c5=+8.6317686364e-03f;

            static const float ci[]={
                sinh_c5, sinh_c3, sinh_c1
            };
            vf_type xs2=x*x;
            vf_type yt=horner(xs2, ci)*x;
            res = yt;
        }
    }
    // x^ : +0x8p-3f
    constexpr
    const float cosh_i0_right=+1.0000000000e+00f;
    if (_F == hyperbolic_func::c_cosh) {
        x_small= x <= cosh_i0_right;
        if (__likely(_T::any_of_vmf(x_small))) {
            // [0, 1] : | p - f | <= 2^-21.9765625
            // coefficients for cosh generated by sollya
            // x^0 : +0xf.ffffdp-4f
            constexpr
            const float cosh_c0=+9.9999982119e-01f;
            // x^2 : +0x8.00061p-4f
            constexpr
            const float cosh_c2=+5.0000578165e-01f;
            // x^4 : +0xa.a8b33p-8f
            constexpr
            const float cosh_c4=+4.1636656970e-02f;
            // x^6 : +0xb.c7fc4p-13f
            constexpr
            const float cosh_c6=+1.4381338842e-03f;
            static const float ci[]={
                cosh_c6, cosh_c4, cosh_c2, cosh_c0
            };
            vf_type xs2=x*x;
            vf_type yt=horner(xs2, ci);
            res = yt;
        }
    }

    if (__likely(!_T::all_of_vmf(x_small))) {
        vf_type kf;
        __reduce_exp_arg(xr, kf, x);
        vf_type kf1=kf-1.0f;
        vf_type y = __exp_k<false>(xr, kf1, x);
        // fpprec: 32
        // bfloat(rhs(solve(2^-18*%e^x=%e^(-x), x)[2]));
        constexpr const float
        x_medium_max = 6.2383246250395077847550890931236e0;
        vmf_type x_medium= x <= x_medium_max;
        if (_F == hyperbolic_func::c_sinh)
            x_medium &= (x > sinh_i0_right);
        if (_F == hyperbolic_func::c_cosh)
            x_medium &= (x > cosh_i0_right);
        if (__likely(_T::any_of_vmf(x_medium))) {
            vf_type ny=0.25/y;
            vf_type z;
            if (_F == hyperbolic_func::c_sinh)
                z = y - ny;
            else
                z = y + ny;
            y= _T::sel(x_medium, z, y);
        }
        res=_T::sel(x_small, res, y);
    }
    if (_F==hyperbolic_func::c_sinh) {
        res = copysign(res, xc);
    }
    return res;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
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
        // [0, 2.166084945201873779296875e-2] : | p - f | <= 2^-18.1640625
        // coefficients for tanh generated by sollya
        // x^1 : +0x8p-3f
        constexpr
        const float tanh_c1=+1.0000000000e+00f;
        static_assert(tanh_c1==1.0f, "oops");
        tanh_x=_T::sel(x_tiny, xa, tanh_x);
    }
    vmf_type x_medium=(xa > tanh_i0_right) & (xa<fc::tanh_one());
    if (__likely(_T::any_of_vmf(x_medium))) {
        constexpr const float tmax=2.0*fc::tanh_one();
        vf_type xae=min(vf_type(xa+xa), vf_type(tmax));
        vf_type xr, kf;
        __reduce_exp_arg(xr, kf, xae);
        vf_type ex= __exp_k<false>(xr, kf, xae);

        vf_type exm1= ex - 1.0;
        vf_type exp1= ex + 1.0;
        vf_type tanh_m=exm1/exp1;
        tanh_x = _T::sel(x_medium, tanh_m, tanh_x);
    }
    tanh_x=copysign(tanh_x, xc);
    return tanh_x;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vi_type
cftal::math::elem_func_loprec_core<float, _T>::
__reduce_log_arg(vf_type& xr, arg_t<vf_type> xc)
{
    // MSQRT2/2
    constexpr
    const bytes4 offs=0x3f3504f3;
    vi_type hx = _T::as_int(xc);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    constexpr const int32_t delta=0x3f800000 - offs.s32();
    hx += delta;
    vi_type k=(hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + offs.s32();
    xr = _T::as_float(hx);
    return k;
}

template <typename _T>
template <typename
    cftal::math::elem_func_loprec_core<float, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__log_k(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type r;
    r = xr - 1.0;

    // [-0.292893230915069580078125, 0.41421353816986083984375] : | p - f | <= 2^-15.5390625
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_c1=+1.0000000000e+00f;
    // x^2 : -0xf.fc32dp-5f
    constexpr
    const float log_c2=-4.9953594804e-01f;
    // x^3 : +0xa.be1d1p-5f
    constexpr
    const float log_c3=+3.3570721745e-01f;
    // x^4 : -0x8.a322fp-5f
    constexpr
    const float log_c4=-2.6991412044e-01f;
    // x^5 : +0xb.6b004p-6f
    constexpr
    const float log_c5=+1.7840582132e-01f;
    // static_assert(log_c1 == 1.0f, "constraint violated");

    constexpr
    static const float ci[]={
        log_c5, log_c4, log_c3, log_c2, log_c1
    };
    vf_type r2=r*r;
    vf_type p=horner2(r, r2, ci);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type ll=r*p;
    vf_type lh;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    if (_LFUNC==log_func::c_log_e) {
        lh = (kf * ctbl::m_ln2[0]) + ll;
    } else if (_LFUNC==log_func::c_log_2) {
        lh = kf + ll * ctbl::m_1_ln2[0];
    } else if (_LFUNC==log_func::c_log_10) {
        lh = kf * ctbl::m_lg2[0] + ll * ctbl::m_1_ln10[0];
    }
    return lh;
}

template <typename _T>
template <typename
    cftal::math::elem_func_loprec_core<float, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__log1p_k(arg_t<vf_type> xc)
{
    vf_type xp1=xc + 1.0f;
    vf_type r= __log_k<_LFUNC>(xp1);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vmf_type xc_tiny= abs(xc)< 0x1.0p-11f;
    vf_type r_tiny;
    if (_LFUNC==log_func::c_log_e) {
        r_tiny=xc;
    } else if (_LFUNC==log_func::c_log_2) {
        r_tiny= xc * ctbl::m_1_ln2[0];
    } else if (_LFUNC==log_func::c_log_10) {
        r_tiny = xc * ctbl::m_1_ln10[0];
    }
    r = _T::sel(xc_tiny, r_tiny, r);
    return r;
}

template <typename _T>
template <typename
    cftal::math::elem_func_loprec_core<float, _T>::log_func _LFUNC>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__log_k12(arg_t<vf_type> xc)
{
    vf_type xr;
    vi_type ki=__reduce_log_arg(xr, xc);
    vf_type r;
    r = xr - 1.0;

    // [-0.292893230915069580078125, 0.41421353816986083984375] : | p - f | <= 2^-23.9375
    // coefficients for log generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float log_c1=+1.0000000000e+00f;
    // x^2 : -0x8.00036p-4f
    constexpr
    const float log_c2=-5.0000321865e-01f;
    // x^3 : +0xa.aac7ap-5f
    constexpr
    const float log_c3=+3.3334714174e-01f;
    // x^4 : -0xf.fb4bap-6f
    constexpr
    const float log_c4=-2.4971285462e-01f;
    // x^5 : +0xc.bd8dp-6f
    constexpr
    const float log_c5=+1.9906926155e-01f;
    // x^6 : -0xb.090b3p-6f
    constexpr
    const float log_c6=-1.7242698371e-01f;
    // x^7 : +0xa.5afp-6f
    constexpr
    const float log_c7=+1.6180038452e-01f;
    // x^8 : -0xc.e8156p-7f
    constexpr
    const float log_c8=-1.0083262622e-01f;

    static_assert(log_c1 == 1.0f, "constraint violated");

    static const float ci[]={
        log_c8, log_c7, log_c6, log_c5, log_c4, log_c3, log_c2
    };
    vf_type r2=r*r;
    vf_type p=horner2(r, r2, ci);
    vf_type kf=_T::cvt_i_to_f(ki);
    vf_type ll=r+r2*p;
    vf_type lh;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    if (_LFUNC==log_func::c_log_e) {
        lh = (kf * ctbl::m_ln2[0]) + ll;
    } else if (_LFUNC==log_func::c_log_2) {
        lh = kf + ll * ctbl::m_1_ln2[0];
    } else if (_LFUNC==log_func::c_log_10) {
        lh = kf * ctbl::m_lg2[0] + ll * ctbl::m_1_ln10[0];
    }
    return lh;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y, vf_type* p_ylnx)
{
    vf_type ylnx=y*__log_k12<log_func::c_log_e>(abs(x));
    if (p_ylnx != nullptr) {
        *p_ylnx = ylnx;
    }
#if 0
    vi_type idx, ki;
    vf_type xr;
    __reduce_exp_arg(xr, idx, ki, ylnx);
    vf_type r=__exp_tbl_k(xr, idx, ki);
#else
    vf_type xr, kf;
    __reduce_exp_arg(xr, kf, ylnx);
    vf_type r=__exp_k<false>(xr, kf, ylnx);
#endif
    return r;
}

template <typename _T>
template <bool _CALC_ROOT>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
powi_k(arg_t<vf_type> x, arg_t<vi_type> e, vf_type* p_ylnx)
{
    vf_type lnx=__log_k12<log_func::c_log_e>(abs(x));
    vf_type y=cvt<vf_type>(e);
    vf_type ylnx;
    if (_CALC_ROOT==true) {
        ylnx = lnx/y;
    } else {
        ylnx = lnx*y;
    }
    if (p_ylnx != nullptr) {
        *p_ylnx = ylnx;
    }
#if 0
    vi_type idx, ki;
    vf_type xr;
    __reduce_exp_arg(xr, idx, ki, ylnx);
    vf_type r=__exp_tbl_k(xr, idx, ki);
#else
    vf_type xr, kf;
    __reduce_exp_arg(xr, kf, ylnx);
    vf_type r=__exp_k<false>(xr, kf, ylnx);
#endif
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vi_type
cftal::math::elem_func_loprec_core<float, _T>::
__reduce_trig_arg(vf_type& xrh, arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type fn= rint(vf_type(x*ctbl::m_2_pi[0]));
    // conversion to double vectors does not make the code faster
    // seven bit chunks of %pi/2
    // x^ : +0xc.ap-3f
    constexpr
    const float pi_2_0=+1.5781250000e+00f;
    // x^ : -0xfp-11f
    constexpr
    const float pi_2_1=-7.3242187500e-03f;
    // x^ : -0x9.6p-21f
    constexpr
    const float pi_2_2=-4.4703483582e-06f;
    // x^ : +0x8.8p-29f
    constexpr
    const float pi_2_3=+1.5832483768e-08f;
    // x^ : +0x8.6p-37f
    constexpr
    const float pi_2_4=+6.0936145019e-11f;
    // x^ : -0xb.9ee5ap-46f
    constexpr
    const float pi_2_5=-1.6513995575e-13f;

    xrh = x + fn * -pi_2_0;
    xrh = xrh + fn * -pi_2_1;
    xrh = xrh + fn * -pi_2_2;
    xrh = xrh + fn * -pi_2_3;
    xrh = xrh + fn * -pi_2_4;
    xrh = xrh + fn * -pi_2_5;
    vi_type q=_T::cvt_f_to_i(fn);
    return q;
}

template <typename _T>
inline
void
cftal::math::elem_func_loprec_core<float, _T>::
__sin_cos_k(arg_t<vf_type> xr, arg_t<vi_type> q, vf_type* ps, vf_type* pc)
{
    vf_type xr2= xr*xr;
    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // [0, 0.785398185253143310546875] : | p - f | <= 2^-24
    // coefficients for cos_c generated by sollya
    // x^0 : +0xf.fffffp-4f
    constexpr
    const float cos_c0=+9.9999994040e-01f;
    // x^2 : -0xf.fffcp-5f
    constexpr
    const float cos_c2=-4.9999809265e-01f;
    // x^4 : +0xa.a9cbcp-8f
    constexpr
    const float cos_c4=+4.1653379798e-02f;
    // x^6 : -0xb.1dd56p-13f
    constexpr
    const float cos_c6=-1.3569991570e-03f;
    constexpr
    static const float cc[]={
        cos_c6, cos_c4,
        cos_c2, cos_c0
    };
    vf_type xr4=xr2*xr2;
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-28.578125
    // coefficients for sin generated by sollya
    // x^1 : +0x8p-3f
    constexpr
    const float sin_c1=+1.0000000000e+00f;
    // x^3 : -0xa.aaaa2p-6f
    constexpr
    const float sin_c3=-1.6666653752e-01f;
    // x^5 : +0x8.88373p-10f
    constexpr
    const float sin_c5=+8.3321211860e-03f;
    // x^7 : -0xc.c967cp-16f
    constexpr
    const float sin_c7=-1.9511015853e-04f;
    constexpr
    static const float cs[]={
        sin_c7,  sin_c5,
        sin_c3, sin_c1
    };
    // vf_type s= horner2(xr2, xr4, cs)*xr;
    vf_type s, c;
    horner2_n2(s, c, xr2, xr4, cs, cc);
    s *= xr;

    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        // vf_type fs = _T::sel(q_and_2_f, vf_type(-1.0), vf_type(1.0));
        // rs *= fs;
        *ps = _T::sel(q_and_2_f, -rs, rs);
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        // vf_type fc =  _T::sel(mt, vf_type(-1.0), vf_type(1.0));
        // rc *= fc;
        *pc= _T::sel(mt, -rc, rc);
    }
}

template <typename _T>
inline
void
cftal::math::elem_func_loprec_core<float, _T>::
sin_cos_k(arg_t<vf_type> x, vf_type* ps, vf_type* pc)
{
    vf_type xr;
    auto q= __reduce_trig_arg(xr, x);
    __sin_cos_k(xr, q, ps, pc);
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__tan_k(arg_t<vf_type> xr, arg_t<vi_type> q)
{
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-22.0703125
    // coefficients for tan generated by sollya
    // x^1 : +0xf.ffffcp-4f
    constexpr
    const float tan_c1=+9.9999976158e-01f;
    // x^3 : +0xa.aae29p-5f
    constexpr
    const float tan_c3=+3.3335998654e-01f;
    // x^5 : +0x8.8084bp-6f
    constexpr
    const float tan_c5=+1.3284413517e-01f;
    // x^7 : +0xe.a4ff9p-8f
    constexpr
    const float tan_c7=+5.7205174118e-02f;
    // x^9 : +0xc.ca68ep-10f
    constexpr
    const float tan_c9=+1.2490881607e-02f;
    // x^11 : +0xa.73bf1p-9f
    constexpr
    const float tan_c11=+2.0414324477e-02f;

    constexpr
    static const float ci[]={
        tan_c11, tan_c9,
        tan_c7, tan_c5, tan_c3, tan_c1
    };

    vf_type x2=xr*xr;
    vf_type x4=x2*x2;

    vf_type t = horner2(x2, x4, ci)*xr;
    vmi_type qm1= vi_type(q & vi_type(1)) == vi_type(1);
    vmf_type fqm1= _T::vmi_to_vmf(qm1);

    vf_type ct=-1.0f/t;
    t = _T::sel(fqm1, ct, t);
    return t;
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
tan_k(arg_t<vf_type> x)
{
    vf_type xr;
    auto q= __reduce_trig_arg(xr, x);
    return __tan_k(xr, q);
}

template <typename _T>
typename cftal::math::elem_func_loprec_core<float, _T>::vi_type
cftal::math::elem_func_loprec_core<float, _T>::
__reduce_trigpi_arg(vf_type& xr, arg_t<vf_type> xc)
{
    vf_type xt2=xc+xc;
    vf_type fh= rint(xt2);
    vf_type s = xc - 0.5f * fh;
    // no need for fmod<4>(fh) here because |int(fh)| < |max integer|
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    xr= s * ctbl::m_pi[0];
    vi_type q= _T::cvt_f_to_i(xt2);
    return q;
}

template <typename _T>
void
cftal::math::elem_func_loprec_core<float, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type xr;
    auto q=__reduce_trigpi_arg(xr, xc);
    __sin_cos_k(xr, q, ps, pc);
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
tanpi_k(arg_t<vf_type> xc)
{
    vf_type xr;
    auto q= __reduce_trigpi_arg(xr, xc);
    vf_type t=__tan_k(xr, q);
    return t;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
__atan_0_1_k(arg_t<vf_type> xr)
{
    vf_type a=0.0f;
    // x^ : +0xcp-5f
    constexpr
    const float atan_i1_left=+3.7500000000e-01f;
    vmf_type sel=(xr < atan_i1_left);
    if (_T::any_of_vmf(sel)) {
        // [0, 0.375] : | p - f | <= 2^-18.0390625
        // coefficients for atan_0 generated by sollya
        // x^1 : +0xf.fff53p-4f
        constexpr
        const float atan_i0_c1=+9.9998968840e-01f;
        // x^3 : -0xa.9f9bdp-5f
        constexpr
        const float atan_i0_c3=-3.3198347688e-01f;
        // x^5 : +0xb.1766ep-6f
        constexpr
        const float atan_i0_c5=+1.7330333591e-01f;
            constexpr
        static const float ci[]={
            atan_i0_c5, atan_i0_c3, atan_i0_c1
        };
        vf_type x2=xr*xr;
        vf_type y_i0=horner2(x2, vf_type(x2*x2), ci)*xr;
        a = _T::sel_val_or_zero(sel, y_i0);
    }
    if (!_T::all_of_vmf(sel)) {
        // [0.375, 1] : | p - f | <= 2^-20.3828125
        // coefficients for atan_i1 generated by sollya
        // x^0 : +0x9.26388p-4f
        constexpr
        const float atan_i1_c0=+5.7183122635e-01f;
        // x^1 : +0xb.50727p-4f
        constexpr
        const float atan_i1_c1=+7.0714038610e-01f;
        // x^2 : -0xa.4caffp-5f
        constexpr
        const float atan_i1_c2=-3.2186123729e-01f;
        // x^3 : +0xe.5b601p-9f
        constexpr
        const float atan_i1_c3=+2.8040887788e-02f;
        // x^4 : +0xc.4c4fep-7f
        constexpr
        const float atan_i1_c4=+9.6078857780e-02f;
        // x^5 : -0x9.4c81dp-7f
        constexpr
        const float atan_i1_c5=-7.2647310793e-02f;
        // x^ : +0xa.4cp-4f
        constexpr
        const float atan_i1_x0=+6.4355468750e-01f;

        constexpr
        static const float ci[]={
            atan_i1_c5, atan_i1_c4, atan_i1_c3, atan_i1_c2,
            atan_i1_c1, atan_i1_c0
        };
        vf_type x_i1=xr - atan_i1_x0;
        vf_type y_i1=horner2(x_i1, vf_type(x_i1*x_i1), ci);
        a = _T::sel(sel, a, y_i1);
    }
    return a;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
atan_k(arg_t<vf_type> xc)
{
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
            vf_type t=ctbl::m_pi_2[0] - dat;
            dat = _T::sel(x_gt_1, t, dat);
        }
        at = _T::sel(calc_at, dat, at);
    }
    at=copysign(at, xc);
    return at;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
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
    vf_type xr=p/q;
    vmf_type s;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    auto dat = __atan_0_1_k(xr);
    if (_T::any_of_vmf(s = ay > ax)) {
        vf_type t=ctbl::m_pi_2[0] - dat;
        dat = _T::sel(s, t, dat);
    }
    vf_type y_s = copysign(vf_type(1.0f), y);
    vf_type x_s = copysign(vf_type(1.0f), x);
    vmf_type y_lt_0 = y_s < 0.0f;
    vmf_type x_lt_0 = x_s < 0.0f;
    // default y>=0, x>=0,
    vf_type at=dat;

    // x < 0 & y <0: atan2(y, x) = atan(y/x) - PI
    if (_T::any_of_vmf(s=y_lt_0 & x_lt_0)) {
        vf_type at_minus_pi=dat -ctbl::m_pi[0];
        at = _T::sel(s, at_minus_pi, at);
    }

    // y < 0, x>=0: atan2(y, x) =  -atan(y/x)
    at = _T::sel(y_lt_0 & (x_s>=0.0f), -dat, at);

    // y >= 0, x < 0: atan2(y, x) = PI - atan(y/x)
    if (_T::any_of_vmf(s= (y_s >=0.0f) & x_lt_0)) {
        vf_type pi_minus_at=ctbl::m_pi[0] - dat;
        at = _T::sel(s, pi_minus_at, at);
    }
    return at;
}

template <typename _T>
inline
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
asin_k_poly(arg_t<vf_type> x2)
{
    // [3.4694469519536141888238489627838134765625e-18, 0.5] : | p - f | <= 2^-19.6171875
    // coefficients for asin generated by sollya
    // x^0 : +0xa.aaa61p-6f
    constexpr
    const vf_type asin_c0=+1.6666556895e-01f;
    // x^2 : +0x9.9e15p-7f
    constexpr
    const vf_type asin_c2=+7.5136780739e-02f;
    // x^4 : +0xa.c298cp-8f
    constexpr
    const vf_type asin_c4=+4.2031809688e-02f;
    // x^6 : +0xb.ab39ep-8f
    constexpr
    const vf_type asin_c6=+4.5581452549e-02f;
    constexpr

    static const float ci[]={
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
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
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
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
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
typename cftal::math::elem_func_loprec_core<float, _T>::vf_type
cftal::math::elem_func_loprec_core<float, _T>::
hypot_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vf_type x2=x*x;
    vf_type y2=y*y;
    vf_type r=sqrt(vf_type(x2+y2));
    return r;
}

#endif // __CFTAL_MATH_ELEM_FUNC_CORE_LOPREC_F32_H__
