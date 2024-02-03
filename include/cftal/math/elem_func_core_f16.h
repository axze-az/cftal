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

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);

            static
            vi_type
            ilogb(arg_t<vf_type> vf);

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
    vmf_type is_denom= abs(x) <= fc::max_denormal();

    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p12_f16), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    vi_type eo= _T::sel_val_or_zero_vi(i_is_denom, vi_type(-12));
    // mantissa
    vi_type m=_T::as_int(xs);
    vi_type xe=((m>>10) & 0x1f) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
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
#if 1
    return vi_type(0);
#else
    vf_type xs=x;
    using fc=func_constants<f16_t>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
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
    m= _T::as_f16_t(i);
    return e;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vf_type xs=x;
    using fc=func_constants<f16_t>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
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
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
ilogbp1(arg_t<vf_type> x)
{
#if 1
    return vi_type(0);
#else
    vf_type xs=x;
    using fc=func_constants<f16_t>;
    vmf_type is_denom= abs(x) <= fc::max_denormal();
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p25f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel_vi(i_is_denom, vi_type(-25), eo);
    // reinterpret as integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) & 0xff) + eo - vi_type(_T::bias()-1);
    return e;
#endif
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(ilogbp1(abs(d)) -1);
    vmf_type mf= d == 0.0_f16;
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
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
sqrt(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    vi_type idx=_T::as_int(xp);
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(f16_sqrt_data::tbl_zero());
    y=_T::sel(signbit(y), _T::nan(), y);
    y=_T::sel(iszero(xc), xc, y);
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
rsqrt_k(arg_t<vf_type> x)
{
    vf_type xp=abs(x);
    vi_type idx=_T::as_int(xp);
    auto lk=make_variable_lookup_table<f16_t>(idx);
    vf_type y=lk.from(f16_rsqrt_data::tbl_zero());
    // y=_T::sel(signbit(y), _T::nan(), y);
    // y=_T::sel(iszero(xc), xc, y);
    return y;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    return xc;
}

template <typename _T>
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
rcbrt_k(arg_t<vf_type> xc)
{
    return xc;
}

template <typename _T>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vf_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
hypot_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
#if 1
    return vf_type(0.0_f16);
#else
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
#endif
}


// Local Variables:
// mode: c++
// end:
#endif
