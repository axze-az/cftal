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
            // x is the unreduced argument
            // calculates %e^(xrh+xrl)*2^k - 1 if exp_m1 is true,
            // %e^(xrh+xrl)*2^k otherwise
            template <bool _EXP_M1>
            static
            vf_type
            __exp_k(arg_t<vf_type> xrh, arg_t<vf_type> xrl,
                    arg_t<vf_type> k, arg_t<vf_type> x);

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
        arg_t<vf_type> kf, arg_t<vf_type> x)
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
        y = _T::sel((abs(x) < 0x1p-11_f16), x, y);
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
exp_k(arg_t<vf_type> xc)
{
    vf_type y;
    // float vector only code
    vf_type xrh, xrl;
    if (_EXP_M1==false) {
#if 0
        vf_type kf;
        __reduce_exp_arg(xrh, xrl, kf, xc);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf, xc);
#else
        vi_type idx, ki;
        __reduce_exp_arg(xrh, xrl, idx, ki, xc);
        y=__exp_tbl_k(xrh, xrl, idx, ki);
#endif
    } else {
        vf_type kf;
        __reduce_exp_arg(xrh, xrl, kf, xc);
        y=__exp_k<_EXP_M1>(xrh, xrl, kf, xc);
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


// Local Variables:
// mode: c++
// end:
#endif
