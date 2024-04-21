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
    vmf_type is_denom= abs(x) <= fc::max_denormal();
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
template <cftal::int16_t _X>
inline
typename cftal::math::elem_func_core<cftal::f16_t, _T>::vi_type
cftal::math::elem_func_core<cftal::f16_t, _T>::
__ilogb_plus(arg_t<vf_type> x)
{
    vf_type xs=abs(x);
    using fc=func_constants<f16_t>;
    vmf_type is_denom= xs <= fc::max_denormal();
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
    // use cftal::f16_ting point operations here because yl may underflow
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




// Local Variables:
// mode: c++
// end:
#endif
