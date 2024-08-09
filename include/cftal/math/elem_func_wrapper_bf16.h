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
#if !defined (__CFTAL_MATH_ELEM_FUNC_WRAPPER_BF16_H__)
#define __CFTAL_MATH_ELEM_FUNC_WRAPPER_BF16_H__ 1

#include <cftal/config.h>
#include <cftal/vec_cvt.h>
#include <cftal/math/vec_func_traits_bf16.h>
#include <cftal/math/func_constants_bf16.h>
#include <cftal/math/elem_func_rndmant_core_f32_16.h>

namespace cftal {
    namespace math {
        // specialization of elem_func_wrapper for bf16_t and different
        // traits
        template <typename _T>
        struct elem_func_wrapper<cftal::bf16_t, _T> {
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmi_type = typename _T::vmi_type;
            using vmf_type = typename _T::vmf_type;

            using f32_traits = typename _T::vhf_traits;
            using f32_core = elem_func_rndmant_core<float, 16, f32_traits>;
            using vhf_type = typename f32_traits::vf_type;
            using vmhf_type = typename f32_traits::vmf_type;
            using vhi_type = typename f32_traits::vi_type;
            using vhmi_type = typename f32_traits::vmi_type;

            // nextafter without nan handling
            static
            vf_type
            nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc);

            static
            vf_type
            ldexp_k(arg_t<vf_type> vf, arg_t<vi_type> vi);

            static
            vf_type
            ldexp(arg_t<vf_type> vf, arg_t<vi_type> vi);

            static
            vf_type
            frexp(arg_t<vf_type> vf, vi_type* vi);

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

            static
            vf_type
            cbrt_k(arg_t<vf_type> x);

            static
            vf_type
            rcbrt_k(arg_t<vf_type> x);

            static
            vf_type
            root12_k(arg_t<vf_type> x);

            template <bool _EXP_M1>
            static
            vf_type
            exp_k(arg_t<vf_type> x);

            static
            vf_type
            exp_mx2_k(arg_t<vf_type> x);

            static
            vf_type
            exp_px2_k(arg_t<vf_type> x);


            template <bool _EXP2_M1>
            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            static
            vf_type
            exp2_mx2_k(arg_t<vf_type> x);

            static
            vf_type
            exp2_px2_k(arg_t<vf_type> x);

            template <bool _EXP10_M1>
            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            static
            vf_type
            exp10_mx2_k(arg_t<vf_type> x);

            static
            vf_type
            exp10_px2_k(arg_t<vf_type> x);

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
            sig_k(arg_t<vf_type> x);

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
            log2p1_k(arg_t<vf_type> x);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            static
            vf_type
            log10p1_k(arg_t<vf_type> x);

            static
            vf_type
            pow_k(arg_t<vf_type> x, arg_t<vf_type> y);

            template <bool _CALC_ROOT>
            static
            vf_type
            powi_k(arg_t<vf_type> x, arg_t<vi_type> e);

            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tan_k(arg_t<vf_type> x);

            // core sine, cosine calculation
            static
            void
            sinpi_cospi_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tanpi_k(arg_t<vf_type> x);

            static
            vf_type
            atan_k(arg_t<vf_type> x);

            static
            vf_type
            atan2_k(arg_t<vf_type> y, arg_t<vf_type> x);

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
    }
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
nextafter_k(arg_t<vf_type> xc, arg_t<vf_type> yc)
{
    vi_type ux=_T::as_int(xc);
    vi_type uy=_T::as_int(yc);
    vi_type ax= ux & not_sign_f32_msk::v.s16h();
    vi_type ay= uy & not_sign_f32_msk::v.s16h();
    vi_type ux_inc= ux + 1;
    vi_type ux_dec= ux - 1;
    // decrement required if ax > ay or (ux^uy & sgn) != 0
    vmi_type opp_sgn=
        vi_type((ux^uy) & sign_f32_msk::v.s16h()) != vi_type(0);
    vi_type r= _T::sel_vi((ax > ay) | opp_sgn, ux_dec, ux_inc);
    vi_type r0= _T::sel_vi(ay == 0, uy, (uy & sign_f32_msk::v.s16h()) | 1);
    r = _T::sel_vi(ax == 0, r0, r);
    r = _T::sel_vi(ux == uy, uy, r);
    vf_type rf=_T::as_float(r);
    return rf;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
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
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    return ldexp_k(x, n);
}


template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
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
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vi_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
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
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vi_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
ilogbp1(arg_t<vf_type> d)
{
    return __ilogb_plus<1>(d);
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vi_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
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
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::rsqrt_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
cbrt_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::cbrt_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
rcbrt_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::rcbrt_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
root12_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::root12_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
template <bool _EXP_M1>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template exp_k<_EXP_M1>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp_mx2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=-xd*xd;
    vhf_type yd=f32_core::template exp_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<bf16_t>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp_px2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=xd*xd;
    vhf_type yd=f32_core::template exp_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<bf16_t>;
    // NOT >= because of rounding:
    y= _T::sel(x2h > fc_t::exp_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <bool _EXP2_M1>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template exp2_k<_EXP2_M1>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp2_mx2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=-xd*xd;
    vf_type x2h=cvt<vf_type>(x2d);
    vhf_type yd=f32_core::template exp2_k<false>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<bf16_t>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp2_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp2_px2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=xd*xd;
    vhf_type yd=f32_core::template exp2_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<bf16_t>;
    y= _T::sel(x2h >= fc_t::exp2_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
template <bool _EXP10_M1>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp10_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template exp10_k<_EXP10_M1>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp10_mx2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=-xd*xd;
    vf_type x2h=cvt<vf_type>(x2d);
    vhf_type yd=f32_core::template exp10_k<false>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<bf16_t>;
    y= _T::sel_zero_or_val(x2h <= fc_t::exp10_lo_zero(), y);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
exp10_px2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type x2d=xd*xd;
    vhf_type yd=f32_core::template exp10_k<false>(x2d);
    vf_type x2h=cvt<vf_type>(x2d);
    vf_type y=cvt<vf_type>(yd);
    using fc_t = math::func_constants<bf16_t>;
    y= _T::sel(x2h >= fc_t::exp10_hi_inf(), _T::pinf(), y);
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__,__flatten__))
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
sinh_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=f32_core::template
        sinh_cosh_k<f32_core::hyperbolic_func::c_sinh>(xd);
    vf_type y=cvt<vf_type>(yd);
    y=_T::sel(isnan(x), x, y);
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__,__flatten__))
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
cosh_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=f32_core::template
        sinh_cosh_k<f32_core::hyperbolic_func::c_cosh>(xd);
    vf_type y=cvt<vf_type>(yd);
    y=_T::sel(isnan(x), x, y);
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
tanh_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=f32_core::tanh_k(xd);
    vf_type y=cvt<vf_type>(yd);
    y=_T::sel(isnan(x), x, y);
    return y;
}

template <typename _T>
inline
__attribute__((__always_inline__))
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
sig_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=f32_core::sig_k(xd);
    vf_type y=cvt<vf_type>(yd);
    return y;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
log_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template __log_k<f32_core::log_func::c_log_e>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
log1p_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template __log1p_k<f32_core::log_func::c_log_e>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
log2_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template __log_k<f32_core::log_func::c_log_2>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
log2p1_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template __log1p_k<f32_core::log_func::c_log_2>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
log10_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template __log_k<f32_core::log_func::c_log_10>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
log10p1_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::template __log1p_k<f32_core::log_func::c_log_10>(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
pow_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=cvt<vhf_type>(y);
    vhf_type ylnx;
    vhf_type rd=f32_core::pow_k(xd, yd, &ylnx);
    vf_type r=cvt<vf_type>(rd);
    using fc=func_constants<bf16_t>;
    const vf_type d= cvt<vf_type>(ylnx);
    constexpr
    const bf16_t exp_hi_inf= fc::exp_hi_inf();
    constexpr
    const bf16_t exp_lo_zero= fc::exp_lo_zero();
    r = _T::sel_zero_or_val(d <= exp_lo_zero, r);
    r = _T::sel(d > exp_hi_inf, _T::pinf(), r);
    return r;
}

template <typename _T>
template <bool _CALC_ROOT>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
powi_k(arg_t<vf_type> x, arg_t<vi_type> e)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhi_type ed=cvt<vhi_type>(e);
    vhf_type ylnx;
    vhf_type rd=f32_core::template powi_k<_CALC_ROOT>(xd, ed, &ylnx);
    vf_type r=cvt<vf_type>(rd);
    using fc=func_constants<bf16_t>;
    const vf_type d= cvt<vf_type>(ylnx);
    constexpr
    const bf16_t exp_hi_inf= fc::exp_hi_inf();
    constexpr
    const bf16_t exp_lo_zero= fc::exp_lo_zero();
    r = _T::sel_zero_or_val(d <= exp_lo_zero, r);
    r = _T::sel(d > exp_hi_inf, _T::pinf(), r);
    return r;
}

template <typename _T>
inline
void
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type sd, cd;
    vhf_type* ps= s != nullptr ? &sd : nullptr;
    vhf_type* pc= c != nullptr ? &cd : nullptr;
    f32_core::sin_cos_k(xd, ps, pc);
    if (s != nullptr) {
        *s = cvt<vf_type>(sd);
    }
    if (c != nullptr) {
        *c = cvt<vf_type>(cd);
    }
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
tan_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::tan_k(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
void
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
sinpi_cospi_k(arg_t<vf_type> x, vf_type* s, vf_type* c)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type sd, cd;
    vhf_type* ps= s != nullptr ? &sd : nullptr;
    vhf_type* pc= c != nullptr ? &cd : nullptr;
    f32_core::sinpi_cospi_k(xd, ps, pc);
    if (s != nullptr) {
        *s = cvt<vf_type>(sd);
    }
    if (c != nullptr) {
        *c = cvt<vf_type>(cd);
    }
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
tanpi_k(arg_t<vf_type> x)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type rd=f32_core::tanpi_k(xd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
atan_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::atan_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
atan2_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type yf=cvt<vhf_type>(y);
    vhf_type rf=f32_core::atan2_k(xf, yf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
asin_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::asin_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
acos_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::acos_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
asinh_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::asinh_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
acosh_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::acosh_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
atanh_k(arg_t<vf_type> x)
{
    vhf_type xf=cvt<vhf_type>(x);
    vhf_type rf=f32_core::atanh_k(xf);
    vf_type r=cvt<vf_type>(rf);
    return r;
}

template <typename _T>
inline
typename cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::vf_type
cftal::math::elem_func_wrapper<cftal::bf16_t, _T>::
hypot_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    vhf_type xd=cvt<vhf_type>(x);
    vhf_type yd=cvt<vhf_type>(y);
    vhf_type rd=f32_core::hypot_k(xd, yd);
    vf_type r=cvt<vf_type>(rd);
    return r;
}

#endif // __CFTAL_MATH_ELEM_FUNC_WRAPPER_B16_H__

