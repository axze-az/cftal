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
#if !defined (__CFTAL_VEC_F32_H__)
#define __CFTAL_VEC_F32_H__ 1

#include <cftal/config.h>
#include <cftal/vec_spec.h>
#include <cftal/d_real.h>
#include <cftal/vec_d_real_traits_f32.h>
#include <cftal/vec_math_funcs.h>
#include <cmath>

#define V2F32_FUNCS 1
#if 1
#define V4F32_FUNCS                                                     \
    ((V4F32_SPECIALIZED>0) || ((V2F32_SPECIALIZED>0) && (V2S32_SPECIALIZED>0)))
#define V8F32_FUNCS                                                     \
    ((V8F32_SPECIALIZED>0) || ((V4F32_SPECIALIZED>0) && (V4S32_SPECIALIZED>0)))
#define V16F32_FUNCS                                                    \
    ((V16F32_SPECIALIZED>0) || ((V8F32_SPECIALIZED>0) && (V8S32_SPECIALIZED>0)))
#else
#define V4F32_FUNCS                                     \
    ((V4F32_SPECIALIZED>0) || ((V2F32_SPECIALIZED>0)))
#define V8F32_FUNCS                                     \
    ((V8F32_SPECIALIZED>0) || ((V4F32_SPECIALIZED>0)))
#define V16F32_FUNCS                                    \
    ((V16F32_SPECIALIZED>0) || ((V8F32_SPECIALIZED>0)))
#endif

#define V4F32_SLOW_SPEC_FUNCS                   \
    ((V4F32_SPECIALIZED>0))
#define V8F32_SLOW_SPEC_FUNCS                   \
    ((V8F32_SPECIALIZED>0))
#define V16F32_SLOW_SPEC_FUNCS                  \
    ((V16F32_SPECIALIZED>0))

namespace cftal {

    template <size_t _N>
    vec<float, _N>
    abs(const vec<float, _N>& v);

    // returns (~a) & (b)
    template <size_t _N>
    vec<float, _N>
    andnot(const vec<float, _N>& a, const vec<float, _N>& b);

    template <size_t _N>
    typename vec<float, _N>::mask_type
    signbit(const vec<float, _N>& v);

    template <size_t _N>
    vec<float, _N>
    copysign(const vec<float, _N>& x, const vec<float, _N>& y);

    template <size_t _N>
    vec<float, _N>
    copysign(const float& x, const vec<float, _N>& y);

    template <size_t _N>
    vec<float, _N>
    copysign(const vec<float, _N>& x, const float& y);

    template <size_t _N>
    vec<float, _N>
    mulsign(const vec<float, _N>& x, const vec<float, _N>& y);

    // return a*b +c with or without fma
    template <size_t _N>
    vec<float, _N>
    mad(const vec<float, _N>& a, const vec<float, _N>& b,
        const vec<float, _N>& c);

    // return -(a*b) +c = c - a * b with or without fma
    template <size_t _N>
    vec<float, _N>
    nmad(const vec<float, _N>& a, const vec<float, _N>& b,
         const vec<float, _N>& c);

    template <size_t _N>
    typename vec<float, _N>::mask_type
    iszero(const vec<float, _N>& v);

    template <size_t _N>
    typename vec<float, _N>::mask_type
    isinf(const vec<float, _N>& v);

    template <size_t _N>
    typename vec<float, _N>::mask_type
    isnan(const vec<float, _N>& v);

    template <size_t _N>
    typename vec<float, _N>::mask_type
    isfinite(const vec<float, _N>& v);

    // a*b +c
    template <size_t _N>
    vec<float, _N>
    fma(const vec<float, _N>& a, const vec<float, _N>& b,
        const vec<float, _N>& c);

    vec<float, 1>
    fma(const vec<float, 1>& a, const vec<float, 1>& b,
        const vec<float, 1>& c);

    // a*b -c
    template <size_t _N>
    vec<float, _N>
    fms(const vec<float, _N>& a, const vec<float, _N>& b,
        const vec<float, _N>& c);

    vec<float, 1>
    fms(const vec<float, 1>& a, const vec<float, 1>& b,
        const vec<float, 1>& c);
    // -(a*b) + c
    template <size_t _N>
    vec<float, _N>
    nfma(const vec<float, _N>& a, const vec<float, _N>& b,
         const vec<float, _N>& c);
    vec<float, 1>
    nfma(const vec<float, 1>& a, const vec<float, 1>& b,
         const vec<float, 1>& c);
    // -(a*b) - c
    template <size_t _N>
    vec<float, _N>
    nfms(const vec<float, _N>& a, const vec<float, _N>& b,
         const vec<float, _N>& c);
    vec<float, 1>
    nfms(const vec<float, 1>& a, const vec<float, 1>& b,
         const vec<float, 1>& c);

    // frexp
    template <size_t _N>
    vec<float, _N>
    frexp(const vec<float, _N>& a, vec<int32_t, _N>* e);

    vec<float, 1>
    frexp(arg_t<vec<float, 1> > a, vec<int32_t, 1>* e);

    // ldexp, 0 ulps
    template <size_t _N>
    vec<float, _N>
    ldexp(const vec<float, _N>& a, const vec<int32_t, _N>& e);

    vec<float, 1>
    ldexp(arg_t<vec<float, 1> > a, arg_t<vec<int32_t, 1> > e);

    // scalbn, ldexp alias
    template <size_t _N>
    vec<float, _N>
    scalbn(const vec<float, _N>& a, const vec<int32_t, _N>& e);

    // nextafter, 0 ulps
    template <size_t _N>
    vec<float, _N>
    nextafter(const vec<float, _N>& x, const vec<float, _N>& y);

    vec<float, 1>
    nextafter(arg_t<vec<float, 1> > x, arg_t<vec<float, 1> > y);

    // ilogb
    template <size_t _N>
    vec<int32_t, _N>
    ilogb(const vec<float, _N>& a);

    vec<int32_t, 1>
    ilogb(arg_t<vec<float, 1> > a);

    // rint, overloads are inline
    template <size_t _N>
    vec<float, _N>
    rint(const vec<float, _N>& v);

    vec<float, 1>
    rint(const vec<float, 1>& v);

    // floor, overloads are inline
    template <size_t _N>
    vec<float, _N>
    floor(const vec<float, _N>& v);

    vec<float, 1>
    floor(const vec<float, 1>& v);

    // ceil, overloads are inline
    template <size_t _N>
    vec<float, _N>
    ceil(const vec<float, _N>& v);

    vec<float, 1>
    ceil(const vec<float, 1>& v);

    // trunc, overloads are inline
    template <size_t _N>
    vec<float, _N>
    trunc(const vec<float, _N>& v);

    vec<float, 1>
    trunc(const vec<float, 1>& v);

    // sqrt, overloads are inline
    template <size_t _N>
    vec<float, _N>
    sqrt(const vec<float, _N>& v);

    vec<float, 1>
    sqrt(const vec<float, 1>& v);

    // rsqrt = 1/sqrt
    template <size_t _N>
    vec<float, _N>
    rsqrt(const vec<float, _N>& v);

    vec<float, 1>
    rsqrt(arg_t<vec<float, 1> > v);

    // cbrt, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    cbrt(const vec<float, _N>& v);

    vec<float, 1>
    cbrt(arg_t<vec<float, 1> > v);

    // rcbrt, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    rcbrt(const vec<float, _N>& v);

    vec<float, 1>
    rcbrt(arg_t<vec<float, 1> > v);

    // root12, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    root12(const vec<float, _N>& v);

    vec<float, 1>
    root12(arg_t<vec<float, 1> > v);

    // hypot, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    hypot(const vec<float, _N>& x, const vec<float, _N>& y);

    vec<float, 1>
    hypot(arg_t<vec<float, 1> > x, arg_t<vec<float, 1> > y);

    // exp, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp(const vec<float, _N>& v);

    vec<float, 1>
    exp(arg_t<vec<float, 1> > v);

    // expm1, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    expm1(const vec<float, _N>& v);

    vec<float, 1>
    expm1(arg_t<vec<float, 1> > v);

    // exp2, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp2(const vec<float, _N>& v);

    vec<float, 1>
    exp2(arg_t<vec<float, 1> > v);

    // exp2m1, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp2m1(const vec<float, _N>& v);

    vec<float, 1>
    exp2m1(arg_t<vec<float, 1> > v);

    // exp10, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp10(const vec<float, _N>& v);

    vec<float, 1>
    exp10(arg_t<vec<float, 1> > v);

    // exp10m1, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp10m1(const vec<float, _N>& v);

    vec<float, 1>
    exp10m1(arg_t<vec<float, 1> > v);

    // sinh, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    sinh(const vec<float, _N>& v);

    vec<float, 1>
    sinh(arg_t<vec<float, 1> > d);

    // cosh, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    cosh(const vec<float, _N>& v);

    vec<float, 1>
    cosh(arg_t<vec<float, 1> > d);

    // cosh, these functions are exact to XXX ulp
    template <size_t _N>
    vec<float, _N>
    tanh(const vec<float, _N>& v);

    vec<float, 1>
    tanh(arg_t<vec<float, 1> > d);

    // log, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    log(const vec<float, _N>& v);

    vec<float, 1>
    log(arg_t<vec<float, 1> > v);

    // log1p, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    log1p(const vec<float, _N>& v);

    vec<float, 1>
    log1p(arg_t<vec<float, 1> > v);

    // log10, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    log10(const vec<float, _N>& v);

    vec<float, 1>
    log10(arg_t<vec<float, 1> > v);

    // log10p1, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    log10p1(const vec<float, _N>& v);

    vec<float, 1>
    log10p1(arg_t<vec<float, 1> > v);

    // log2, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    log2(const vec<float, _N>& v);

    vec<float, 1>
    log2(arg_t<vec<float, 1> > v);

    // log2p1, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    log2p1(const vec<float, _N>& v);

    vec<float, 1>
    log2p1(arg_t<vec<float, 1> > v);

    // pow, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    pow(const vec<float, _N>& x, const vec<float, _N>& y);

    vec<float, 1>
    pow(arg_t<vec<float, 1> > x, arg_t<vec<float, 1> > y);

    // pow, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    pow(const vec<float, _N>& x, const vec<int32_t, _N>& y);

    vec<float, 1>
    pow(arg_t<vec<float, 1> > x, arg_t<vec<int32_t, 1> > y);

    // pow, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    rootn(const vec<float, _N>& x, const vec<int32_t, _N>& y);

    vec<float, 1>
    rootn(arg_t<vec<float, 1> > x, arg_t<vec<int32_t, 1> > y);

    // atan, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    atan(const vec<float, _N>& x);

    vec<float, 1>
    atan(arg_t<vec<float, 1> > d);

    // asin, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    asin(const vec<float, _N>& x);

    vec<float, 1>
    asin(arg_t<vec<float, 1> > d);

    // acos, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    acos(const vec<float, _N>& x);

    vec<float, 1>
    acos(arg_t<vec<float, 1> > d);

    // atan2, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    atan2(const vec<float, _N>& y, const vec<float, _N>& x);

    vec<float, 1>
    atan2(arg_t<vec<float, 1> > y, arg_t<vec<float, 1> > x);

    // sin, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    sin(const vec<float, _N>& v);

    vec<float, 1>
    sin(arg_t<vec<float, 1> > v);

    // cos, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    cos(const vec<float, _N>& v);

    vec<float, 1>
    cos(arg_t<vec<float, 1> > v);

    // sincos, these functions are exact to +-1 ulp
    template<size_t _N>
    void
    sincos(const vec<float, _N>& x,
           vec<float, _N>* s, vec<float, _N>* c);

    void
    sincos(arg_t<vec<float, 1> > x,
           vec<float, 1>* s, vec<float, 1>* c);

    // tan, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    tan(const vec<float, _N>& v);

    vec<float, 1>
    tan(arg_t<vec<float, 1> > v);

    // sin, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    sinpi(const vec<float, _N>& v);

    vec<float, 1>
    sinpi(arg_t<vec<float, 1> > v);

    // cos, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    cospi(const vec<float, _N>& v);

    vec<float, 1>
    cospi(arg_t<vec<float, 1> > v);

    // sincos, these functions are exact to +-1 ulp
    template<size_t _N>
    void
    sinpicospi(const vec<float, _N>& x,
               vec<float, _N>* s, vec<float, _N>* c);

    void
    sinpicospi(arg_t<vec<float, 1> > x,
               vec<float, 1>* s, vec<float, 1>* c);

    // tan, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    tanpi(const vec<float, _N>& v);

    vec<float, 1>
    tanpi(arg_t<vec<float, 1> > v);

    // asinh, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    asinh(const vec<float, _N>& x);

    vec<float, 1>
    asinh(arg_t<vec<float, 1> > d);

    // acosh, these functions are exact to +-2 ulp
    template <size_t _N>
    vec<float, _N>
    acosh(const vec<float, _N>& x);

    vec<float, 1>
    acosh(arg_t<vec<float, 1> > d);

    // atanh, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    atanh(const vec<float, _N>& x);

    vec<float, 1>
    atanh(arg_t<vec<float, 1> > d);

    // erf, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    erf(const vec<float, _N>& x);

    vec<float, 1>
    erf(arg_t<vec<float, 1> > d);

    // erfc, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    erfc(const vec<float, _N>& x);

    vec<float, 1>
    erfc(arg_t<vec<float, 1> > d);

    // tgamma, these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    tgamma(const vec<float, _N>& x);

    vec<float, 1>
    tgamma(arg_t<vec<float, 1> > d);

    // lgamma: these functions are exact to ??? ulp, perhaps to +-1
    // ulp for non negative arguments
    template <size_t _N>
    vec<float, _N>
    lgamma(const vec<float, _N>& x, vec<int32_t, _N>* signp);

    vec<float, 1>
    lgamma(arg_t<vec<float, 1> > d, vec<int32_t, 1>* signp);

    // j0
    template <size_t _N>
    vec<float, _N>
    j0(const vec<float, _N>& x);

    vec<float, 1>
    j0(arg_t<vec<float, 1> > x);

    // j1
    template <size_t _N>
    vec<float, _N>
    j1(const vec<float, _N>& x);

    vec<float, 1>
    j1(arg_t<vec<float, 1> > x);

    // y0
    template <size_t _N>
    vec<float, _N>
    y0(const vec<float, _N>& x);

    vec<float, 1>
    y0(arg_t<vec<float, 1> > x);

    // y1
    template <size_t _N>
    vec<float, _N>
    y1(const vec<float, _N>& x);

    vec<float, 1>
    y1(arg_t<vec<float, 1> > x);

    // exp_mx2, calculates $ e^{-x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp_mx2(const vec<float, _N>& x);

    vec<float, 1>
    exp_mx2(arg_t<vec<float, 1> > d);

    // exp_px2, calculates $ e^{+x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp_px2(const vec<float, _N>& x);

    vec<float, 1>
    exp_px2(arg_t<vec<float, 1> > d);

    // exp2_mx2, calculates $ 2^{-x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp2_mx2(const vec<float, _N>& x);

    vec<float, 1>
    exp2_mx2(arg_t<vec<float, 1> > d);

    // exp2_px2, calculates $ 2^{+x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp2_px2(const vec<float, _N>& x);

    vec<float, 1>
    exp2_px2(arg_t<vec<float, 1> > d);

    // exp10_mx2, calculates $ 10^{-x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp10_mx2(const vec<float, _N>& x);

    vec<float, 1>
    exp10_mx2(arg_t<vec<float, 1> > d);

    // exp10_px2, calculates $ 10^{+x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<float, _N>
    exp10_px2(const vec<float, _N>& x);

    vec<float, 1>
    exp10_px2(arg_t<vec<float, 1> > d);

    // logistic or sigmoid function
    // sig(x) = 1/(1+exp(-x))
    template <size_t _N>
    vec<float, _N>
    sig(const vec<float, _N>& x);

    vec<float, 1>
    sig(arg_t<vec<float, 1> > x);

#if V2F32_FUNCS>0
    vec<float, 2>
    frexp(arg_t<vec<float, 2> > x, vec<int32_t, 2>* e);

    vec<float, 2>
    ldexp(arg_t<vec<float, 2> > a, arg_t<vec<int32_t, 2> > e);

    vec<float, 2>
    nextafter(arg_t<vec<float, 2> > x, arg_t<vec<float, 2> > y);

    vec<int32_t, 2>
    ilogb(arg_t<vec<float, 2> > a);

    vec<float, 2>
    rsqrt(arg_t<vec<float, 2> > v);

    vec<float, 2>
    cbrt(arg_t<vec<float, 2> > v);

    vec<float, 2>
    rcbrt(arg_t<vec<float, 2> > v);

    vec<float, 2>
    root12(arg_t<vec<float, 2> > v);

    vec<float, 2>
    hypot(arg_t<vec<float, 2> > x, arg_t<vec<float, 2> > y);

    vec<float, 2>
    exp(arg_t<vec<float, 2> > d);

    vec<float, 2>
    expm1(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp2m1(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp10(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp10m1(arg_t<vec<float, 2> > d);

    vec<float, 2>
    sinh(arg_t<vec<float, 2> > d);

    vec<float, 2>
    cosh(arg_t<vec<float, 2> > d);

    vec<float, 2>
    tanh(arg_t<vec<float, 2> > d);

    vec<float, 2>
    log(arg_t<vec<float, 2> > d);

    vec<float, 2>
    log1p(arg_t<vec<float, 2> > d);

    vec<float, 2>
    log10(arg_t<vec<float, 2> > d);

    vec<float, 2>
    log10p1(arg_t<vec<float, 2> > d);

    vec<float, 2>
    log2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    log2p1(arg_t<vec<float, 2> > d);

    vec<float, 2>
    pow(arg_t<vec<float, 2> > b, arg_t<vec<float, 2> > e);

    vec<float, 2>
    pow(arg_t<vec<float, 2> > b, arg_t<vec<int32_t, 2> > e);

    vec<float, 2>
    rootn(arg_t<vec<float, 2> > b, arg_t<vec<int32_t, 2> > n);

    vec<float, 2>
    atan(arg_t<vec<float, 2> > d);

    vec<float, 2>
    asin(arg_t<vec<float, 2> > d);

    vec<float, 2>
    acos(arg_t<vec<float, 2> > d);

    vec<float, 2>
    atan2(arg_t<vec<float, 2> > y, arg_t<vec<float, 2> > x);

    vec<float, 2>
    sin(arg_t<vec<float, 2> > d);

    vec<float, 2>
    cos(arg_t<vec<float, 2> > d);

    void
    sincos(arg_t<vec<float, 2> > d,
           vec<float, 2> * psin, vec<float, 2> * pcos);

    vec<float, 2>
    tan(arg_t<vec<float, 2> > d);

    vec<float, 2>
    sinpi(arg_t<vec<float, 2> > d);

    vec<float, 2>
    cospi(arg_t<vec<float, 2> > d);

    void
    sinpicospi(arg_t<vec<float, 2> > d,
               vec<float, 2> * psin, vec<float, 2> * pcos);

    vec<float, 2>
    tanpi(arg_t<vec<float, 2> > d);

    vec<float, 2>
    asinh(arg_t<vec<float, 2> > d);

    vec<float, 2>
    acosh(arg_t<vec<float, 2> > d);

    vec<float, 2>
    atanh(arg_t<vec<float, 2> > d);

    vec<float, 2>
    erf(arg_t<vec<float, 2> > d);

    vec<float, 2>
    erfc(arg_t<vec<float, 2> > d);

    vec<float, 2>
    tgamma(arg_t<vec<float, 2> > d);

    vec<float, 2>
    lgamma(arg_t<vec<float, 2> > d, vec<int32_t, 2>* signp);

    vec<float, 2>
    j0(arg_t<vec<float, 2> > x);

    vec<float, 2>
    j1(arg_t<vec<float, 2> > x);

    vec<float, 2>
    y0(arg_t<vec<float, 2> > x);

    vec<float, 2>
    y1(arg_t<vec<float, 2> > x);

    vec<float, 2>
    exp_mx2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp_px2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp2_mx2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp2_px2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp10_mx2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    exp10_px2(arg_t<vec<float, 2> > d);

    vec<float, 2>
    sig(arg_t<vec<float, 2> > x);

#endif

#if V4F32_FUNCS>0
    vec<float, 4>
    frexp(arg_t<vec<float, 4> > x, vec<int32_t, 4>* e);

    vec<float, 4>
    ldexp(arg_t<vec<float, 4> > a, arg_t<vec<int32_t, 4> > e);

    vec<float, 4>
    nextafter(arg_t<vec<float, 4> > x, arg_t<vec<float, 4> > y);

    vec<int32_t, 4>
    ilogb(arg_t<vec<float, 4> > a);

    vec<float, 4>
    rsqrt(arg_t<vec<float, 4> > v);

    vec<float, 4>
    cbrt(arg_t<vec<float, 4> > v);

    vec<float, 4>
    rcbrt(arg_t<vec<float, 4> > v);

    vec<float, 4>
    root12(arg_t<vec<float, 4> > v);

    vec<float, 4>
    hypot(arg_t<vec<float, 4> > x, arg_t<vec<float, 4> > y);

    vec<float, 4>
    exp(arg_t<vec<float, 4> > d);

    vec<float, 4>
    expm1(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp2m1(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp10(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp10m1(arg_t<vec<float, 4> > d);

    vec<float, 4>
    sinh(arg_t<vec<float, 4> > d);

    vec<float, 4>
    cosh(arg_t<vec<float, 4> > d);

    vec<float, 4>
    tanh(arg_t<vec<float, 4> > d);

    vec<float, 4>
    log(arg_t<vec<float, 4> > d);

    vec<float, 4>
    log1p(arg_t<vec<float, 4> > d);

    vec<float, 4>
    log10(arg_t<vec<float, 4> > d);

    vec<float, 4>
    log10p1(arg_t<vec<float, 4> > d);

    vec<float, 4>
    log2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    log2p1(arg_t<vec<float, 4> > d);

    vec<float, 4>
    pow(arg_t<vec<float, 4> > b, arg_t<vec<float, 4> > e);

    vec<float, 4>
    pow(arg_t<vec<float, 4> > b, arg_t<vec<int32_t, 4> > e);

    vec<float, 4>
    rootn(arg_t<vec<float, 4> > b, arg_t<vec<int32_t, 4> > n);

    vec<float, 4>
    atan(arg_t<vec<float, 4> > d);

    vec<float, 4>
    asin(arg_t<vec<float, 4> > d);

    vec<float, 4>
    acos(arg_t<vec<float, 4> > d);

    vec<float, 4>
    atan2(arg_t<vec<float, 4> > y, arg_t<vec<float, 4> > x);

    vec<float, 4>
    sin(arg_t<vec<float, 4> > d);

    vec<float, 4>
    cos(arg_t<vec<float, 4> > d);

    void
    sincos(arg_t<vec<float, 4> > d,
           vec<float, 4> * psin, vec<float, 4> * pcos);

    vec<float, 4>
    tan(arg_t<vec<float, 4> > d);

    vec<float, 4>
    sinpi(arg_t<vec<float, 4> > d);

    vec<float, 4>
    cospi(arg_t<vec<float, 4> > d);

    void
    sinpicospi(arg_t<vec<float, 4> > d,
               vec<float, 4> * psin, vec<float, 4> * pcos);

    vec<float, 4>
    tanpi(arg_t<vec<float, 4> > d);

    vec<float, 4>
    asinh(arg_t<vec<float, 4> > d);

    vec<float, 4>
    acosh(arg_t<vec<float, 4> > d);

    vec<float, 4>
    atanh(arg_t<vec<float, 4> > d);

    vec<float, 4>
    erf(arg_t<vec<float, 4> > d);

    vec<float, 4>
    erfc(arg_t<vec<float, 4> > d);

#if V4F32_SLOW_SPEC_FUNCS>0
    vec<float, 4>
    tgamma(arg_t<vec<float, 4> > d);

    vec<float, 4>
    lgamma(arg_t<vec<float, 4> > d, vec<int32_t, 4>* signp);
#endif

    vec<float, 4>
    j0(arg_t<vec<float, 4> > x);

    vec<float, 4>
    j1(arg_t<vec<float, 4> > x);

    vec<float, 4>
    y0(arg_t<vec<float, 4> > x);

    vec<float, 4>
    y1(arg_t<vec<float, 4> > x);

    vec<float, 4>
    exp_mx2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp_px2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp2_mx2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp2_px2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp10_mx2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    exp10_px2(arg_t<vec<float, 4> > d);

    vec<float, 4>
    sig(arg_t<vec<float, 4> > x);

#endif

#if V8F32_FUNCS>0
    vec<float, 8>
    frexp(arg_t<vec<float, 8> > x, vec<int32_t, 8>* e);

    vec<float, 8>
    ldexp(arg_t<vec<float, 8> > a, arg_t<vec<int32_t, 8> > e);

    vec<float, 8>
    nextafter(arg_t<vec<float, 8> > x, arg_t<vec<float, 8> > y);

    vec<int32_t, 8>
    ilogb(arg_t<vec<float, 8> > a);

    vec<float, 8>
    rsqrt(arg_t<vec<float, 8> > v);

    vec<float, 8>
    cbrt(arg_t<vec<float, 8> > v);

    vec<float, 8>
    rcbrt(arg_t<vec<float, 8> > v);

    vec<float, 8>
    root12(arg_t<vec<float, 8> > v);

    vec<float, 8>
    hypot(arg_t<vec<float, 8> > x, arg_t<vec<float, 8> > y);

    vec<float, 8>
    exp(arg_t<vec<float, 8> > d);

    vec<float, 8>
    expm1(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp2m1(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp10(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp10m1(arg_t<vec<float, 8> > d);

    vec<float, 8>
    sinh(arg_t<vec<float, 8> > d);

    vec<float, 8>
    cosh(arg_t<vec<float, 8> > d);

    vec<float, 8>
    tanh(arg_t<vec<float, 8> > d);

    vec<float, 8>
    log(arg_t<vec<float, 8> > d);

    vec<float, 8>
    log1p(arg_t<vec<float, 8> > d);

    vec<float, 8>
    log10(arg_t<vec<float, 8> > d);

    vec<float, 8>
    log10p1(arg_t<vec<float, 8> > d);

    vec<float, 8>
    log2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    log2p1(arg_t<vec<float, 8> > d);

    vec<float, 8>
    pow(arg_t<vec<float, 8> > b, arg_t<vec<float, 8> > e);

    vec<float, 8>
    pow(arg_t<vec<float, 8> > b, arg_t<vec<int32_t, 8> > e);

    vec<float, 8>
    rootn(arg_t<vec<float, 8> > b, arg_t<vec<int32_t, 8> > n);

    vec<float, 8>
    atan(arg_t<vec<float, 8> > d);

    vec<float, 8>
    asin(arg_t<vec<float, 8> > d);

    vec<float, 8>
    acos(arg_t<vec<float, 8> > d);

    vec<float, 8>
    atan2(arg_t<vec<float, 8> > y, arg_t<vec<float, 8> > x);

    vec<float, 8>
    sin(arg_t<vec<float, 8> > d);

    vec<float, 8>
    cos(arg_t<vec<float, 8> > d);

    void
    sincos(arg_t<vec<float, 8> > d,
           vec<float, 8> * psin, vec<float, 8> * pcos);

    vec<float, 8>
    tan(arg_t<vec<float, 8> > d);

    vec<float, 8>
    sinpi(arg_t<vec<float, 8> > d);

    vec<float, 8>
    cospi(arg_t<vec<float, 8> > d);

    void
    sinpicospi(arg_t<vec<float, 8> > d,
               vec<float, 8> * psin, vec<float, 8> * pcos);

    vec<float, 8>
    tanpi(arg_t<vec<float, 8> > d);

    vec<float, 8>
    asinh(arg_t<vec<float, 8> > d);

    vec<float, 8>
    acosh(arg_t<vec<float, 8> > d);

    vec<float, 8>
    atanh(arg_t<vec<float, 8> > d);

    vec<float, 8>
    erf(arg_t<vec<float, 8> > d);

    vec<float, 8>
    erfc(arg_t<vec<float, 8> > d);

#if V8F32_SLOW_SPEC_FUNCS>0
    vec<float, 8>
    tgamma(arg_t<vec<float, 8> > d);

    vec<float, 8>
    lgamma(arg_t<vec<float, 8> > d, vec<int32_t, 8>* signp);
#endif

    vec<float, 8>
    j0(arg_t<vec<float, 8> > x);

    vec<float, 8>
    j1(arg_t<vec<float, 8> > x);

    vec<float, 8>
    y0(arg_t<vec<float, 8> > x);

    vec<float, 8>
    y1(arg_t<vec<float, 8> > x);

    vec<float, 8>
    exp_mx2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp_px2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp2_mx2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp2_px2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp10_mx2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    exp10_px2(arg_t<vec<float, 8> > d);

    vec<float, 8>
    sig(arg_t<vec<float, 8> > x);

#endif
#if V16F32_FUNCS>0
    vec<float, 16>
    frexp(arg_t<vec<float, 16> > x, vec<int32_t, 16>* e);

    vec<float, 16>
    ldexp(arg_t<vec<float, 16> > a, arg_t<vec<int32_t, 16> > e);

    vec<float, 16>
    nextafter(arg_t<vec<float, 16> > x, arg_t<vec<float, 16> > y);

    vec<int32_t, 16>
    ilogb(arg_t<vec<float, 16> > a);

    vec<float, 16>
    rsqrt(arg_t<vec<float, 16> > v);

    vec<float, 16>
    cbrt(arg_t<vec<float, 16> > v);

    vec<float, 16>
    rcbrt(arg_t<vec<float, 16> > v);

    vec<float, 16>
    root12(arg_t<vec<float, 16> > v);

    vec<float, 16>
    hypot(arg_t<vec<float, 16> > x, arg_t<vec<float, 16> > y);

    vec<float, 16>
    exp(arg_t<vec<float, 16> > d);

    vec<float, 16>
    expm1(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp2m1(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp10(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp10m1(arg_t<vec<float, 16> > d);

    vec<float, 16>
    sinh(arg_t<vec<float, 16> > d);

    vec<float, 16>
    cosh(arg_t<vec<float, 16> > d);

    vec<float, 16>
    tanh(arg_t<vec<float, 16> > d);

    vec<float, 16>
    log(arg_t<vec<float, 16> > d);

    vec<float, 16>
    log1p(arg_t<vec<float, 16> > d);

    vec<float, 16>
    log10(arg_t<vec<float, 16> > d);

    vec<float, 16>
    log10p1(arg_t<vec<float, 16> > d);

    vec<float, 16>
    log2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    log2p1(arg_t<vec<float, 16> > d);

    vec<float, 16>
    pow(arg_t<vec<float, 16> > b, arg_t<vec<float, 16> > e);

    vec<float, 16>
    pow(arg_t<vec<float, 16> > b, arg_t<vec<int32_t, 16> > e);

    vec<float, 16>
    rootn(arg_t<vec<float, 16> > b, arg_t<vec<int32_t, 16> > n);

    vec<float, 16>
    atan(arg_t<vec<float, 16> > d);

    vec<float, 16>
    asin(arg_t<vec<float, 16> > d);

    vec<float, 16>
    acos(arg_t<vec<float, 16> > d);

    vec<float, 16>
    atan2(arg_t<vec<float, 16> > y, arg_t<vec<float, 16> > x);

    vec<float, 16>
    sin(arg_t<vec<float, 16> > d);

    vec<float, 16>
    cos(arg_t<vec<float, 16> > d);

    void
    sincos(arg_t<vec<float, 16> > d,
           vec<float, 16> * psin, vec<float, 16> * pcos);

    vec<float, 16>
    tan(arg_t<vec<float, 16> > d);

    vec<float, 16>
    sinpi(arg_t<vec<float, 16> > d);

    vec<float, 16>
    cospi(arg_t<vec<float, 16> > d);

    void
    sinpicospi(arg_t<vec<float, 16> > d,
               vec<float, 16> * psin, vec<float, 16> * pcos);

    vec<float, 16>
    tanpi(arg_t<vec<float, 16> > d);

    vec<float, 16>
    asinh(arg_t<vec<float, 16> > d);

    vec<float, 16>
    acosh(arg_t<vec<float, 16> > d);

    vec<float, 16>
    atanh(arg_t<vec<float, 16> > d);

    vec<float, 16>
    erf(arg_t<vec<float, 16> > d);

    vec<float, 16>
    erfc(arg_t<vec<float, 16> > d);

#if V16F32_SLOW_SPEC_FUNCS>0
    vec<float, 16>
    tgamma(arg_t<vec<float, 16> > d);

    vec<float, 16>
    lgamma(arg_t<vec<float, 16> > d, vec<int32_t, 16>* signp);
#endif
    vec<float, 16>
    j0(arg_t<vec<float, 16> > x);

    vec<float, 16>
    j1(arg_t<vec<float, 16> > x);

    vec<float, 16>
    y0(arg_t<vec<float, 16> > x);

    vec<float, 16>
    y1(arg_t<vec<float, 16> > x);

    vec<float, 16>
    exp_mx2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp_px2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp2_mx2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp2_px2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp10_mx2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    exp10_px2(arg_t<vec<float, 16> > d);

    vec<float, 16>
    sig(arg_t<vec<float, 16> > x);

#endif

    namespace native {
#if defined (__SSE__)
        vec<float, 1>
        rsqrt_11b(const vec<float, 1>& x);

        vec<float, 2>
        rsqrt_11b(const vec<float, 2>& x);

        vec<float, 4>
        rsqrt_11b(const vec<float, 4>& x);
#if defined (__AVX__)
        vec<float, 8>
        rsqrt_11b(const vec<float, 8>& x);
#endif
#endif

        template <size_t _N>
        vec<float, _N>
        rsqrt_11b(const vec<float, _N>& x);
    }

    // namespace for functions with reduced range and precision
    // similiar to opencl c++ 2.0
    namespace half_math {

        // for all functions below:
        // range: +- 2^16
        // precision: +-8 ulps

        template <size_t _N>
        vec<float, _N>
        cos(const vec<float, _N>& v);

        vec<float, 1>
        cos(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        divide(const vec<float, _N>& x, const vec<float, _N>& y);

        template <size_t _N>
        vec<float, _N>
        exp(const vec<float, _N>& v);

        vec<float, 1>
        exp(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        exp2(const vec<float, _N>& v);

        vec<float, 1>
        exp2(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        exp10(const vec<float, _N>& v);

        vec<float, 1>
        exp10(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        log(const vec<float, _N>& v);

        vec<float, 1>
        log(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        log2(const vec<float, _N>& v);

        vec<float, 1>
        log2(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        log10(const vec<float, _N>& v);

        vec<float, 1>
        log10(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        recip(const vec<float, _N>& v);

        template <size_t _N>
        vec<float, _N>
        rsqrt(const vec<float, _N>& v);

        vec<float, 1>
        rsqrt(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        sin(const vec<float, _N>& v);

        vec<float, 1>
        sin(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        sqrt(const vec<float, _N>& v);

        vec<float, 1>
        sqrt(arg_t<vec<float, 1> > v);

        template <size_t _N>
        vec<float, _N>
        tan(const vec<float, _N>& v);

        vec<float, 1>
        tan(arg_t<vec<float, 1> > v);

#if V2F32_FUNCS>0
        vec<float, 2>
        cos(arg_t<vec<float, 2> > v);

        vec<float, 2>
        exp(arg_t<vec<float, 2> > v);

        vec<float, 2>
        exp2(arg_t<vec<float, 2> > v);

        vec<float, 2>
        exp10(arg_t<vec<float, 2> > v);

        vec<float, 2>
        log(arg_t<vec<float, 2> > v);

        vec<float, 2>
        log2(arg_t<vec<float, 2> > v);

        vec<float, 2>
        log10(arg_t<vec<float, 2> > v);

        vec<float, 2>
        rsqrt(arg_t<vec<float, 2> > v);

        vec<float, 2>
        sin(arg_t<vec<float, 2> > v);

        vec<float, 2>
        sqrt(arg_t<vec<float, 2> > v);

        vec<float, 2>
        tan(arg_t<vec<float, 2> > v);
#endif
#if V4F32_FUNCS>0
        vec<float, 4>
        cos(arg_t<vec<float, 4> > v);

        vec<float, 4>
        exp(arg_t<vec<float, 4> > v);

        vec<float, 4>
        exp2(arg_t<vec<float, 4> > v);

        vec<float, 4>
        exp10(arg_t<vec<float, 4> > v);

        vec<float, 4>
        log(arg_t<vec<float, 4> > v);

        vec<float, 4>
        log2(arg_t<vec<float, 4> > v);

        vec<float, 4>
        log10(arg_t<vec<float, 4> > v);

        vec<float, 4>
        rsqrt(arg_t<vec<float, 4> > v);

        vec<float, 4>
        sin(arg_t<vec<float, 4> > v);

        vec<float, 4>
        sqrt(arg_t<vec<float, 4> > v);

        vec<float, 4>
        tan(arg_t<vec<float, 4> > v);
#endif
#if V8F32_FUNCS>0
        vec<float, 8>
        cos(arg_t<vec<float, 8> > v);

        vec<float, 8>
        exp(arg_t<vec<float, 8> > v);

        vec<float, 8>
        exp2(arg_t<vec<float, 8> > v);

        vec<float, 8>
        exp10(arg_t<vec<float, 8> > v);

        vec<float, 8>
        log(arg_t<vec<float, 8> > v);

        vec<float, 8>
        log2(arg_t<vec<float, 8> > v);

        vec<float, 8>
        log10(arg_t<vec<float, 8> > v);

        vec<float, 8>
        rsqrt(arg_t<vec<float, 8> > v);

        vec<float, 8>
        sin(arg_t<vec<float, 8> > v);

        vec<float, 8>
        sqrt(arg_t<vec<float, 8> > v);

        vec<float, 8>
        tan(arg_t<vec<float, 8> > v);
#endif
#if V16F32_FUNCS>0
        vec<float, 16>
        cos(arg_t<vec<float, 16> > v);

        vec<float, 16>
        exp(arg_t<vec<float, 16> > v);

        vec<float, 16>
        exp2(arg_t<vec<float, 16> > v);

        vec<float, 16>
        exp10(arg_t<vec<float, 16> > v);

        vec<float, 16>
        log(arg_t<vec<float, 16> > v);

        vec<float, 16>
        log2(arg_t<vec<float, 16> > v);

        vec<float, 16>
        log10(arg_t<vec<float, 16> > v);

        vec<float, 16>
        rsqrt(arg_t<vec<float, 16> > v);

        vec<float, 16>
        sin(arg_t<vec<float, 16> > v);

        vec<float, 16>
        sqrt(arg_t<vec<float, 16> > v);

        vec<float, 16>
        tan(arg_t<vec<float, 16> > v);
#endif

    };
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::abs(const vec<float, _N>& v)
{
    const float msk=not_sign_f32_msk::v.f32();
    return v & msk;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::andnot(const vec<float, _N>& a, const vec<float, _N>& b)
{
    return vec<float, _N>((~a) & b);
}

template <cftal::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::signbit(const vec<float, _N>& x)
{
    using vf_type = vec<float, _N>;
    using vi_type = vec<int32_t, _N>;
    vi_type xi=as<vi_type>(x);
    typename vi_type::mask_type ri= xi < vi_type(0);
    return as<typename vf_type::mask_type>(ri);
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::copysign(const vec<float, _N>& x, const vec<float, _N>& y)
{
    // return abs(x) * sgn(y)
    using v_t = vec<float, _N>;
#if 1
    const float abs_msk=not_sign_f32_msk::v.f32();
    v_t abs_x=x & abs_msk;
    const float sgn_msk=sign_f32_msk::v.f32();
    v_t sgn_y=y & sgn_msk;
#else
    const float msk=not_sign_f32_msk::v.f32();
    v_t abs_x(x & msk);
    v_t sgn_y(andnot(v_t(msk), y));
#endif
    return v_t(abs_x | sgn_y);
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::copysign(const float& x, const vec<float, _N>& y)
{
    return copysign(vec<float, _N>(x), y);
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::copysign(const vec<float, _N>& x, const float& y)
{
    return copysign(x, vec<float, _N>(y));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::mulsign(const vec<float, _N>& x, const vec<float, _N>& y)
{
    using v_t = vec<float, _N>;
    const float msk=sign_f32_msk::v.f32();
    v_t sgn_y = y & msk;
    return v_t(x ^ sgn_y);
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::mad(const vec<float, _N>& a, const vec<float, _N>& b,
           const vec<float, _N>& c)
{
    return a * b + c;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::nmad(const vec<float, _N>& a, const vec<float, _N>& b,
            const vec<float, _N>& c)
{
    return c - a * b;
}

template <cftal::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::iszero(const vec<float, _N>& x)
{
    return x == 0.0f;
}

template <cftal::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isinf(const vec<float, _N>& x)
{
    vec<float, _N> absx(abs(x));
    const float vm=exp_f32_msk::v.f32();
    return absx == vm;
}

template <cftal::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isnan(const vec<float, _N>& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

template <cftal::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isfinite(const vec<float, _N>& x)
{
    // uses the fact that nan < x returns false
    vec<float, _N> absx(abs(x));
    const float vm=exp_f32_msk::v.f32();
    return absx < vm;
    // return ~(isinf(x) | isnan(x));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::fma(const vec<float, _N>& a, const vec<float, _N>& b,
           const vec<float, _N>& c)
{
    return vec<float, _N>(fma(low_half(a), low_half(b), low_half(c)),
                          fma(high_half(a), high_half(b), high_half(c)));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::fms(const vec<float, _N>& a, const vec<float, _N>& b,
           const vec<float, _N>& c)
{
    return vec<float, _N>(fms(low_half(a), low_half(b), low_half(c)),
                          fms(high_half(a), high_half(b), high_half(c)));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::nfma(const vec<float, _N>& a, const vec<float, _N>& b,
            const vec<float, _N>& c)
{
    return vec<float, _N>(nfma(low_half(a), low_half(b), low_half(c)),
                          nfma(high_half(a), high_half(b), high_half(c)));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::nfms(const vec<float, _N>& a, const vec<float, _N>& b,
            const vec<float, _N>& c)
{
    return vec<float, _N>(nfms(low_half(a), low_half(b), low_half(c)),
                          nfms(high_half(a), high_half(b), high_half(c)));
}

inline
cftal::vec<float, 1>
cftal::fma(const vec<float, 1>& a, const vec<float, 1>& b,
           const vec<float, 1>& c)
{
    return vec<float, 1>(fmaf(a(), b(), c()));
}

inline
cftal::vec<float, 1>
cftal::fms(const vec<float, 1>& a, const vec<float, 1>& b,
           const vec<float, 1>& c)
{
    return vec<float, 1>(fmaf(a(), b(), -c()));
}

inline
cftal::vec<float, 1>
cftal::nfma(const vec<float, 1>& a, const vec<float, 1>& b,
            const vec<float, 1>& c)
{
    return vec<float, 1>(fmaf(-a(), b(), c()));
}

inline
cftal::vec<float, 1>
cftal::nfms(const vec<float, 1>& a, const vec<float, 1>& b,
            const vec<float, 1>& c)
{
    return vec<float, 1>(fmaf(-a(), b(), -c()));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::sin(const vec<float, _N>& v)
{
    vec<float, _N> r(sin(low_half(v)), sin(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::cos(const vec<float, _N>& v)
{
    vec<float, _N> r(cos(low_half(v)), cos(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
void
cftal::sincos(const vec<float, _N>& v,
              vec<float, _N>* s, vec<float, _N>* c)
{
    if (s != nullptr && c != nullptr) {
        vec<float, _N/2> sl, sh, cl, ch;
        sincos(low_half(v), &sl, &cl);
        sincos(high_half(v), &sh, &ch);
        *s= vec<float, _N>(sl, sh);
        *c= vec<float, _N>(cl, ch);
    } else if (s != nullptr) {
        *s = sin(v);
    } else if (c != nullptr) {
        *c = cos(v);
    }
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::tan(const vec<float, _N>& v)
{
    vec<float, _N> r(tan(low_half(v)), tan(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::sinpi(const vec<float, _N>& v)
{
    vec<float, _N> r(sinpi(low_half(v)), sinpi(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::cospi(const vec<float, _N>& v)
{
    vec<float, _N> r(cospi(low_half(v)), cospi(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
void
cftal::sinpicospi(const vec<float, _N>& v,
                  vec<float, _N>* s, vec<float, _N>* c)
{
    if (s != nullptr && c != nullptr) {
        vec<float, _N/2> sl, sh, cl, ch;
        sinpicospi(low_half(v), &sl, &cl);
        sinpicospi(high_half(v), &sh, &ch);
        *s= vec<float, _N>(sl, sh);
        *c= vec<float, _N>(cl, ch);
    } else if (s != nullptr) {
        *s = sinpi(v);
    } else if (c != nullptr) {
        *c = cospi(v);
    }
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::tanpi(const vec<float, _N>& v)
{
    vec<float, _N> r(tanpi(low_half(v)), tanpi(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::asinh(const vec<float, _N>& v)
{
    vec<float, _N> r(asinh(low_half(v)), asinh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::acosh(const vec<float, _N>& v)
{
    vec<float, _N> r(acosh(low_half(v)), acosh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::atanh(const vec<float, _N>& v)
{
    vec<float, _N> r(atanh(low_half(v)), atanh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::erf(const vec<float, _N>& v)
{
    vec<float, _N> r(erf(low_half(v)), erf(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::erfc(const vec<float, _N>& v)
{
    vec<float, _N> r(erfc(low_half(v)), erfc(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::tgamma(const vec<float, _N>& v)
{
    vec<float, _N> r(tgamma(low_half(v)), tgamma(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::lgamma(const vec<float, _N>& v, vec<int32_t, _N>* signp)
{
    vec<int32_t, _N/2> sl, sh;
    vec<float, _N> r(lgamma(low_half(v), &sl), lgamma(high_half(v), &sh));
    if (signp)
        *signp=vec<int32_t, _N>(sl, sh);
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::j0(const vec<float, _N>& x)
{
    vec<float, _N> r(j0(low_half(x)), j0(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::j1(const vec<float, _N>& x)
{
    vec<float, _N> r(j1(low_half(x)), j1(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::y0(const vec<float, _N>& x)
{
    vec<float, _N> r(y0(low_half(x)), y0(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::y1(const vec<float, _N>& x)
{
    vec<float, _N> r(y1(low_half(x)), y1(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::sqrt(const vec<float, _N>& v)
{
    vec<float, _N> r(sqrt(low_half(v)), sqrt(high_half(v)));
    return r;
}

inline
cftal::vec<float, 1>
cftal::sqrt(const vec<float, 1>& v)
{
    return vec<float, 1>(std::sqrt(v()));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::rsqrt(const vec<float, _N>& v)
{
    vec<float, _N> r(rsqrt(low_half(v)), rsqrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::cbrt(const vec<float, _N>& v)
{
    vec<float, _N> r(cbrt(low_half(v)), cbrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::rcbrt(const vec<float, _N>& v)
{
    vec<float, _N> r(rcbrt(low_half(v)), rcbrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::root12(const vec<float, _N>& v)
{
    vec<float, _N> r(root12(low_half(v)), root12(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::hypot(const vec<float, _N>& x, const vec<float, _N>& y)
{
    vec<float, _N> r(hypot(low_half(x), low_half(y)),
                     hypot(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp(const vec<float, _N>& v)
{
    vec<float, _N> r(exp(low_half(v)), exp(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::expm1(const vec<float, _N>& v)
{
    vec<float, _N> r(expm1(low_half(v)), expm1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp2(const vec<float, _N>& v)
{
    vec<float, _N> r(exp2(low_half(v)), exp2(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp2m1(const vec<float, _N>& v)
{
    vec<float, _N> r(exp2m1(low_half(v)), exp2m1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp10(const vec<float, _N>& v)
{
    vec<float, _N> r(exp10(low_half(v)), exp10(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp10m1(const vec<float, _N>& v)
{
    vec<float, _N> r(exp10m1(low_half(v)), exp10m1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::log(const vec<float, _N>& v)
{
    vec<float, _N> r(log(low_half(v)), log(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::log1p(const vec<float, _N>& v)
{
    vec<float, _N> r(log1p(low_half(v)), log1p(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::log10(const vec<float, _N>& v)
{
    vec<float, _N> r(log10(low_half(v)), log10(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::log10p1(const vec<float, _N>& v)
{
    vec<float, _N> r(log10p1(low_half(v)), log10p1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::log2(const vec<float, _N>& v)
{
    vec<float, _N> r(log2(low_half(v)), log2(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::log2p1(const vec<float, _N>& v)
{
    vec<float, _N> r(log2p1(low_half(v)), log2p1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::sinh(const vec<float, _N>& v)
{
    vec<float, _N> r(sinh(low_half(v)), sinh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::cosh(const vec<float, _N>& v)
{
    vec<float, _N> r(cosh(low_half(v)), cosh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::tanh(const vec<float, _N>& v)
{
    vec<float, _N> r(tanh(low_half(v)), tanh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::pow(const vec<float, _N>& x, const vec<float, _N>& y)
{
    vec<float, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::pow(const vec<float, _N>& x, const vec<int32_t, _N>& y)
{
    vec<float, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::rootn(const vec<float, _N>& x, const vec<int32_t, _N>& y)
{
    vec<float, _N> r(rootn(low_half(x), low_half(y)),
                     rootn(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::atan2(const vec<float, _N>& x, const vec<float, _N>& y)
{
    vec<float, _N> r(atan2(low_half(x), low_half(y)),
                     atan2(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::atan(const vec<float, _N>& x)
{
    vec<float, _N> r(atan(low_half(x)), atan(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::asin(const vec<float, _N>& x)
{
    vec<float, _N> r(asin(low_half(x)), asin(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::acos(const vec<float, _N>& x)
{
    vec<float, _N> r(acos(low_half(x)), acos(high_half(x)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::frexp(const vec<float, _N>& a, vec<int32_t, _N>* e)
{
    vec<float, _N> r;
    if (e != nullptr) {
	vec<int32_t, _N/2> el, eh;
	r=vec<float, _N>(frexp(low_half(a), &el),
			 frexp(high_half(a), &eh));
        vec<int32_t, _N> er(el, eh);
        *e = er;
    } else {
	r=vec<float, _N>(frexp(low_half(a), nullptr),
			 frexp(high_half(a), nullptr));
    }
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::ldexp(const vec<float, _N>& a, const vec<int32_t, _N>& e)
{
    return vec<float, _N>(ldexp(low_half(a), low_half(e)),
                          ldexp(high_half(a), high_half(e)));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::scalbn(const vec<float, _N>& a, const vec<int32_t, _N>& e)
{
    return ldexp(a, e);
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::nextafter(const vec<float, _N>& a, const vec<float, _N>& b)
{
    return vec<float, _N>(nextafter(low_half(a), low_half(b)),
                          nextafter(high_half(a), high_half(b)));
}

template <cftal::size_t _N>
inline
cftal::vec<int32_t, _N>
cftal::ilogb(const vec<float, _N>& a)
{
    return vec<int32_t, _N>(ilogb(low_half(a)), ilogb(high_half(a)));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::rint(const cftal::vec<float, _N>& v)
{
    return vec<float, _N>(rint(low_half(v)),
                          rint(high_half(v)));
}

inline
cftal::vec<float, 1>
cftal::rint(const vec<float, 1>& v)
{
    return std::rint(v());
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::floor(const cftal::vec<float, _N>& v)
{
    return vec<float, _N>(floor(low_half(v)),
                          floor(high_half(v)));
}

inline
cftal::vec<float, 1>
cftal::floor(const vec<float, 1>& v)
{
    return std::floor(v());
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::ceil(const cftal::vec<float, _N>& v)
{
    return vec<float, _N>(ceil(low_half(v)),
                          ceil(high_half(v)));
}

inline
cftal::vec<float, 1>
cftal::ceil(const vec<float, 1>& v)
{
    return std::ceil(v());
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::trunc(const cftal::vec<float, _N>& v)
{
    return vec<float, _N>(trunc(low_half(v)),
                          trunc(high_half(v)));
}

inline
cftal::vec<float, 1>
cftal::trunc(const vec<float, 1>& v)
{
    return std::trunc(v());
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::exp_mx2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp_mx2(low_half(x)),
                          exp_mx2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::exp_px2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp_px2(low_half(x)),
                          exp_px2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::exp2_mx2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp2_mx2(low_half(x)),
                          exp2_mx2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::exp2_px2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp2_px2(low_half(x)),
                          exp2_px2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::exp10_mx2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp10_mx2(low_half(x)),
                          exp10_mx2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::exp10_px2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp10_px2(low_half(x)),
                          exp10_px2(high_half(x)));
}

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::sig(const vec<float, _N>& x)
{
    vec<float, _N> r(sig(low_half(x)),
                     sig(high_half(x)));
    return r;
}

#if defined(__SSE__)
inline
cftal::vec<float, 1>
cftal::native::rsqrt_11b(const vec<float, 1>& x)
{
    return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set1_ps(x())));
}

inline
cftal::vec<float, 2>
cftal::native::rsqrt_11b(const vec<float, 2>& x)
{
    vec<float, 4> xx(x, x);
    vec<float, 4> y =_mm_rsqrt_ps(xx());
    return low_half(y);
}

inline
cftal::vec<float, 4>
cftal::native::rsqrt_11b(const vec<float, 4>& x)
{
    return _mm_rsqrt_ps(x());
}

#if defined (__AVX__)
inline
cftal::vec<float, 8>
cftal::native::rsqrt_11b(const vec<float, 8>& x)
{
    return _mm256_rsqrt_ps(x());
}
#endif
#endif // __SSE__

template <cftal::size_t _N>
inline
cftal::vec<float, _N>
cftal::native::rsqrt_11b(const vec<float, _N>& x)
{
#if defined (__SSE__)
    return vec<float, _N>(rsqrt_11b(low_half(x)),
			  rsqrt_11b(high_half(x)));
#else
    using vf_type = vec<float, _N>;
    using vi_type = vec<int32_t, _N>;
    vi_type m=as<vi_type>(x);
    const vi_type magic = 0x5f3759df;
    vi_type mi= magic - (m >> 1);
    vf_type y=as<vf_type>(mi);
    // bits in [1.0, 4.0)
    // X * 3 * 2 = 23 (faithful) X ~ 3.8
    // y = math::impl::root_r2::order3<_T, false>(y, x);
    // y = math::impl::root_r2::order2<_T, true/false>(y, x);
    y = math::impl::root_r2::order3<float, false>(y, x);
    return y;
#endif
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::
cos(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::cos(low_half(v)),
                     half_math::cos(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::
divide(const vec<float, _N>& x, const vec<float, _N>& y)
{
    return x/y;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::exp(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::exp(low_half(v)),
                     half_math::exp(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::exp2(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::exp2(low_half(v)),
                     half_math::exp2(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::exp10(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::exp10(low_half(v)),
                     half_math::exp10(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::log(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::log(low_half(v)),
                     half_math::log(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::log2(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::log2(low_half(v)),
                     half_math::log2(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::log10(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::log10(low_half(v)),
                     half_math::log10(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::rsqrt(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::rsqrt(low_half(v)),
                     half_math::rsqrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::sin(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::sin(low_half(v)),
                     half_math::sin(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::sqrt(const vec<float, _N>& v)
{
    // return cftal::sqrt(v);
    vec<float, _N> r(half_math::sqrt(low_half(v)),
                     half_math::sqrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
cftal::vec<float, _N>
cftal::half_math::tan(const vec<float, _N>& v)
{
    vec<float, _N> r(half_math::tan(low_half(v)),
                     half_math::tan(high_half(v)));
    return r;
}


// local variables:
// mode: c++
// end:
#endif
