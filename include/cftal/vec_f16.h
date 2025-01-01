//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_VEC_F16_H__)
#define __CFTAL_VEC_F16_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
// this file should be included in vec_spec.h:
#include <cftal/vxf16.h>

#define V2F16_FUNCS 1
#define V4F16_FUNCS                                                     \
    ((V4F16_SPECIALIZED>0) || ((V2F16_SPECIALIZED>0) && (V2S16_SPECIALIZED>0)))
#define V8F16_FUNCS                                                     \
    ((V8F16_SPECIALIZED>0) || ((V4F16_SPECIALIZED>0) && (V4S16_SPECIALIZED>0)))
#define V16F16_FUNCS                                                    \
    ((V16F16_SPECIALIZED>0) || ((V8F16_SPECIALIZED>0) && (V8S16_SPECIALIZED>0)))

namespace cftal {

    using v1f16 = vec<f16_t, 1>;
    using v2f16 = vec<f16_t, 2>;
    using v4f16 = vec<f16_t, 4>;
    using v8f16 = vec<f16_t, 8>;
    using v16f16 = vec<f16_t, 16>;

    template <size_t _N>
    vec<f16_t, _N>
    ldexp(const vec<f16_t, _N>& a, const vec<int16_t, _N>& e);

    template <size_t _N>
    vec<f16_t, _N>
    scalbn(const vec<f16_t, _N>& a, const vec<int16_t, _N>& e);

    template <size_t _N>
    vec<f16_t, _N>
    frexp(const vec<f16_t, _N>& a, vec<int16_t, _N>* e);

    template <size_t _N>
    vec<f16_t, _N>
    nextafter(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y);

    template <size_t _N>
    vec<int16_t, _N>
    ilogb(const vec<f16_t, _N>& x);


    template <size_t _N>
    vec<f16_t, _N>
    rsqrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    cbrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    rcbrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    root12(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    hypot(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y);

    template <size_t _N>
    vec<f16_t, _N>
    exp(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    expm1(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    exp2(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    exp2m1(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    exp10(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    exp10m1(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    sinh(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    cosh(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    tanh(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    log(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    log2(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    log10(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    log1p(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    log2p1(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    log10p1(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    pow(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y);

    template <size_t _N>
    vec<f16_t, _N>
    pow(const vec<f16_t, _N>& x, const vec<int16_t, _N>& y);

    template <size_t _N>
    vec<f16_t, _N>
    rootn(const vec<f16_t, _N>& x, const vec<int16_t, _N>& y);

    template <size_t _N>
    vec<f16_t, _N>
    sin(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    cos(const vec<f16_t, _N>& x);

    template <size_t _N>
    void
    sincos(const vec<f16_t, _N>& x,
           vec<f16_t, _N>* s, vec<f16_t, _N>* c);

    template <size_t _N>
    vec<f16_t, _N>
    tan(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    sinpi(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    cospi(const vec<f16_t, _N>& x);

    template <size_t _N>
    void
    sinpicospi(const vec<f16_t, _N>& x,
               vec<f16_t, _N>* s, vec<f16_t, _N>* c);

    template <size_t _N>
    vec<f16_t, _N>
    tanpi(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    atan2(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y);

    template <size_t _N>
    vec<f16_t, _N>
    asin(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    acos(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    atan(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    asinh(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    acosh(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    atanh(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    erf(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    erfc(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    tgamma(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    lgamma(const vec<f16_t, _N>& x, vec<int16_t, _N>* signp);

    template <size_t _N>
    vec<f16_t, _N>
    j0(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    j1(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    y0(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    y1(const vec<f16_t, _N>& x);

    // exp_mx2, calculates $ e^{-x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<f16_t, _N>
    exp_mx2(const vec<f16_t, _N>& x);

    // exp_px2, calculates $ e^{+x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<f16_t, _N>
    exp_px2(const vec<f16_t, _N>& x);

    // exp2_mx2, calculates $ 2^{-x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<f16_t, _N>
    exp2_mx2(const vec<f16_t, _N>& x);

    // exp2_px2, calculates $ 2^{+x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<f16_t, _N>
    exp2_px2(const vec<f16_t, _N>& x);

    // exp10_mx2, calculates $ 10^{-x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<f16_t, _N>
    exp10_mx2(const vec<f16_t, _N>& x);

    // exp10_px2, calculates $ 10^{+x^2} $ these functions are exact to +-1 ulp
    template <size_t _N>
    vec<f16_t, _N>
    exp10_px2(const vec<f16_t, _N>& x);

    // logistic or sigmoid function
    // sig(x) = 1/(1+exp(-x))
    template <size_t _N>
    vec<f16_t, _N>
    sig(const vec<f16_t, _N>& x);

// #if V1F16_FUNCS > 0
    vec<f16_t, 1>
    ldexp(arg_t<vec<f16_t, 1> > a, arg_t<vec<int16_t, 1> > e);

    vec<f16_t, 1>
    frexp(arg_t<vec<f16_t, 1> > a, vec<int16_t, 1>* e);

    vec<f16_t, 1>
    nextafter(arg_t<vec<f16_t, 1> > x, arg_t<vec<f16_t, 1> > y);

    vec<int16_t, 1>
    ilogb(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    rsqrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    cbrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    rcbrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    root12(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    hypot(arg_t<vec<f16_t, 1> > x, arg_t<vec<f16_t, 1> > y);

    vec<f16_t, 1>
    exp(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    expm1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    exp2(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    exp2m1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    exp10(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    exp10m1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    sinh(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    cosh(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    tanh(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    log(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    log2(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    log10(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    log1p(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    log2p1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    log10p1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    pow(arg_t<vec<f16_t, 1> > x, arg_t<vec<f16_t, 1> > y);

    vec<f16_t, 1>
    pow(arg_t<vec<f16_t, 1> > x, arg_t<vec<int16_t, 1> > y);

    vec<f16_t, 1>
    rootn(arg_t<vec<f16_t, 1> > x, arg_t<vec<int16_t, 1> > y);

    vec<f16_t, 1>
    sin(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    cos(arg_t<vec<f16_t, 1> > x);

    void
    sincos(arg_t<vec<f16_t, 1> > x,
           vec<f16_t, 1>* s, vec<f16_t, 1>* c);

    vec<f16_t, 1>
    tan(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    sinpi(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    cospi(arg_t<vec<f16_t, 1> > x);

    void
    sinpicospi(arg_t<vec<f16_t, 1> > x,
               vec<f16_t, 1>* s, vec<f16_t, 1>* c);

    vec<f16_t, 1>
    tanpi(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    atan2(arg_t<vec<f16_t, 1> > x, arg_t<vec<f16_t, 1> > y);

    vec<f16_t, 1>
    asin(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    acos(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    atan(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    asinh(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    acosh(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    atanh(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    erf(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    erfc(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    tgamma(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    lgamma(arg_t<vec<f16_t, 1> > d, vec<int16_t, 1>* signp);

    vec<f16_t, 1>
    j0(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    j1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    y0(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    y1(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    exp_mx2(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    exp_px2(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    exp2_mx2(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    exp2_px2(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    exp10_mx2(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    exp10_px2(arg_t<vec<f16_t, 1> > d);

    vec<f16_t, 1>
    sig(arg_t<vec<f16_t, 1> > d);

// #endif
#if V2F16_FUNCS>0

    vec<f16_t, 2>
    ldexp(arg_t<vec<f16_t, 2> > a, arg_t<vec<int16_t, 2> > e);

    vec<f16_t, 2>
    frexp(arg_t<vec<f16_t, 2> > a, vec<int16_t, 2>* e);

    vec<f16_t, 2>
    nextafter(arg_t<vec<f16_t, 2> > x, arg_t<vec<f16_t, 2> > y);

    vec<int16_t, 2>
    ilogb(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    rsqrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    cbrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    rcbrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    root12(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    hypot(arg_t<vec<f16_t, 2> > x, arg_t<vec<f16_t, 2> > y);

    vec<f16_t, 2>
    exp(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    expm1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    exp2(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    exp2m1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    exp10(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    exp10m1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    sinh(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    cosh(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    tanh(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    log(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    log2(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    log10(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    log1p(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    log2p1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    log10p1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    pow(arg_t<vec<f16_t, 2> > x, arg_t<vec<f16_t, 2> > y);

    vec<f16_t, 2>
    pow(arg_t<vec<f16_t, 2> > x, arg_t<vec<int16_t, 2> > y);

    vec<f16_t, 2>
    rootn(arg_t<vec<f16_t, 2> > x, arg_t<vec<int16_t, 2> > y);

    vec<f16_t, 2>
    sin(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    cos(arg_t<vec<f16_t, 2> > x);

    void
    sincos(arg_t<vec<f16_t, 2> > x,
           vec<f16_t, 2>* s, vec<f16_t, 2>* c);

    vec<f16_t, 2>
    tan(arg_t<vec<f16_t, 2> > x);


    vec<f16_t, 2>
    sinpi(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    cospi(arg_t<vec<f16_t, 2> > x);

    void
    sinpicospi(arg_t<vec<f16_t, 2> > x,
               vec<f16_t, 2>* s, vec<f16_t, 2>* c);

    vec<f16_t, 2>
    tanpi(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    atan2(arg_t<vec<f16_t, 2> > x, arg_t<vec<f16_t, 2> > y);

    vec<f16_t, 2>
    asin(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    acos(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    atan(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    asinh(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    acosh(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    atanh(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    erf(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    erfc(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    tgamma(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    lgamma(arg_t<vec<f16_t, 2> > d, vec<int16_t, 2>* signp);

    vec<f16_t, 2>
    j0(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    j1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    y0(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    y1(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    exp_mx2(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    exp_px2(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    exp2_mx2(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    exp2_px2(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    exp10_mx2(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    exp10_px2(arg_t<vec<f16_t, 2> > d);

    vec<f16_t, 2>
    sig(arg_t<vec<f16_t, 2> > d);

#endif

#if V4F16_FUNCS>0

    vec<f16_t, 4>
    ldexp(arg_t<vec<f16_t, 4> > a, arg_t<vec<int16_t, 4> > e);

    vec<f16_t, 4>
    frexp(arg_t<vec<f16_t, 4> > a, vec<int16_t, 4>* e);

    vec<f16_t, 4>
    nextafter(arg_t<vec<f16_t, 4> > x, arg_t<vec<f16_t, 4> > y);

    vec<int16_t, 4>
    ilogb(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    rsqrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    cbrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    rcbrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    root12(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    hypot(arg_t<vec<f16_t, 4> > x, arg_t<vec<f16_t, 4> > y);

    vec<f16_t, 4>
    exp(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    expm1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    exp2(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    exp2m1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    exp10(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    exp10m1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    sinh(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    cosh(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    tanh(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    log(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    log2(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    log10(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    log1p(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    log2p1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    log10p1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    pow(arg_t<vec<f16_t, 4> > x, arg_t<vec<f16_t, 4> > y);

    vec<f16_t, 4>
    pow(arg_t<vec<f16_t, 4> > x, arg_t<vec<int16_t, 4> > y);

    vec<f16_t, 4>
    rootn(arg_t<vec<f16_t, 4> > x, arg_t<vec<int16_t, 4> > y);

    vec<f16_t, 4>
    sin(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    cos(arg_t<vec<f16_t, 4> > x);

    void
    sincos(arg_t<vec<f16_t, 4> > x,
           vec<f16_t, 4>* s, vec<f16_t, 4>* c);

    vec<f16_t, 4>
    tan(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    sinpi(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    cospi(arg_t<vec<f16_t, 4> > x);

    void
    sinpicospi(arg_t<vec<f16_t, 4> > x,
               vec<f16_t, 4>* s, vec<f16_t, 4>* c);

    vec<f16_t, 4>
    tanpi(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    atan2(arg_t<vec<f16_t, 4> > x, arg_t<vec<f16_t, 4> > y);

    vec<f16_t, 4>
    asin(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    acos(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    atan(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    asinh(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    acosh(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    atanh(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    erf(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    erfc(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    tgamma(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    lgamma(arg_t<vec<f16_t, 4> > d, vec<int16_t, 4>* signp);

    vec<f16_t, 4>
    j0(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    j1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    y0(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    y1(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    exp_mx2(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    exp_px2(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    exp2_mx2(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    exp2_px2(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    exp10_mx2(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    exp10_px2(arg_t<vec<f16_t, 4> > d);

    vec<f16_t, 4>
    sig(arg_t<vec<f16_t, 4> > d);

#endif
#if V8F16_FUNCS>0

    vec<f16_t, 8>
    ldexp(arg_t<vec<f16_t, 8> > a, arg_t<vec<int16_t, 8> > e);

    vec<f16_t, 8>
    frexp(arg_t<vec<f16_t, 8> > a, vec<int16_t, 8>* e);

    vec<f16_t, 8>
    nextafter(arg_t<vec<f16_t, 8> > x, arg_t<vec<f16_t, 8> > y);

    vec<int16_t, 8>
    ilogb(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    rsqrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    cbrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    rcbrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    root12(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    hypot(arg_t<vec<f16_t, 8> > x, arg_t<vec<f16_t, 8> > y);

    vec<f16_t, 8>
    exp(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    expm1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    exp2(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    exp2m1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    exp10(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    exp10m1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    sinh(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    cosh(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    tanh(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    log(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    log2(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    log10(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    log1p(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    log2p1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    log10p1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    pow(arg_t<vec<f16_t, 8> > x, arg_t<vec<f16_t, 8> > y);

    vec<f16_t, 8>
    pow(arg_t<vec<f16_t, 8> > x, arg_t<vec<int16_t, 8> > y);

    vec<f16_t, 8>
    rootn(arg_t<vec<f16_t, 8> > x, arg_t<vec<int16_t, 8> > y);

    vec<f16_t, 8>
    sin(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    cos(arg_t<vec<f16_t, 8> > x);

    void
    sincos(arg_t<vec<f16_t, 8> > x,
           vec<f16_t, 8>* s, vec<f16_t, 8>* c);

    vec<f16_t, 8>
    tan(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    sinpi(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    cospi(arg_t<vec<f16_t, 8> > x);

    void
    sinpicospi(arg_t<vec<f16_t, 8> > x,
               vec<f16_t, 8>* s, vec<f16_t, 8>* c);

    vec<f16_t, 8>
    tanpi(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    atan2(arg_t<vec<f16_t, 8> > x, arg_t<vec<f16_t, 8> > y);

    vec<f16_t, 8>
    asin(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    acos(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    atan(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    asinh(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    acosh(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    atanh(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    erf(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    erfc(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    tgamma(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    lgamma(arg_t<vec<f16_t, 8> > d, vec<int16_t, 8>* signp);

    vec<f16_t, 8>
    j0(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    j1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    y0(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    y1(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    exp_mx2(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    exp_px2(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    exp2_mx2(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    exp2_px2(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    exp10_mx2(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    exp10_px2(arg_t<vec<f16_t, 8> > d);

    vec<f16_t, 8>
    sig(arg_t<vec<f16_t, 8> > d);

#endif
#if V16F16_FUNCS>0

    vec<f16_t, 16>
    ldexp(arg_t<vec<f16_t, 16> > a, arg_t<vec<int16_t, 16> > e);

    vec<f16_t, 16>
    frexp(arg_t<vec<f16_t, 16> > a, vec<int16_t, 16>* e);

    vec<f16_t, 16>
    nextafter(arg_t<vec<f16_t, 16> > x, arg_t<vec<f16_t, 16> > y);

    vec<int16_t, 16>
    ilogb(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    rsqrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    cbrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    rcbrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    root12(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    hypot(arg_t<vec<f16_t, 16> > x, arg_t<vec<f16_t, 16> > y);

    vec<f16_t, 16>
    exp(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    expm1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    exp2(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    exp2m1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    exp10(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    exp10m1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    sinh(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    cosh(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    tanh(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    log(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    log2(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    log10(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    log1p(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    log2p1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    log10p1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    pow(arg_t<vec<f16_t, 16> > x, arg_t<vec<f16_t, 16> > y);

    vec<f16_t, 16>
    pow(arg_t<vec<f16_t, 16> > x, arg_t<vec<int16_t, 16> > y);

    vec<f16_t, 16>
    rootn(arg_t<vec<f16_t, 16> > x, arg_t<vec<int16_t, 16> > y);

    vec<f16_t, 16>
    sin(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    cos(arg_t<vec<f16_t, 16> > x);

    void
    sincos(arg_t<vec<f16_t, 16> > x,
           vec<f16_t, 16>* s, vec<f16_t, 16>* c);

    vec<f16_t, 16>
    tan(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    sinpi(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    cospi(arg_t<vec<f16_t, 16> > x);

    void
    sinpicospi(arg_t<vec<f16_t, 16> > x,
               vec<f16_t, 16>* s, vec<f16_t, 16>* c);

    vec<f16_t, 16>
    tanpi(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    atan2(arg_t<vec<f16_t, 16> > x, arg_t<vec<f16_t, 16> > y);

    vec<f16_t, 16>
    asin(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    acos(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    atan(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    asinh(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    acosh(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    atanh(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    erf(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    erfc(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    tgamma(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    lgamma(arg_t<vec<f16_t, 16> > d, vec<int16_t, 16>* signp);

    vec<f16_t, 16>
    j0(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    j1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    y0(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    y1(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    exp_mx2(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    exp_px2(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    exp2_mx2(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    exp2_px2(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    exp10_mx2(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    exp10_px2(arg_t<vec<f16_t, 16> > d);

    vec<f16_t, 16>
    sig(arg_t<vec<f16_t, 16> > d);

#endif
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
ldexp(const vec<cftal::f16_t, _N>& v, const vec<cftal::int16_t, _N>& e)
{
    vec<f16_t, _N> r(ldexp(low_half(v), low_half(e)),
                     ldexp(high_half(v), low_half(e)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
scalbn(const vec<cftal::f16_t, _N>& v, const vec<cftal::int16_t, _N>& e)
{
    return ldexp(v, e);
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::frexp(const vec<cftal::f16_t, _N>& a, vec<int16_t, _N>* e)
{
    vec<f16_t, _N> r;
    if (e != nullptr) {
        vec<int16_t, _N/2> el, eh;
        r=vec<f16_t, _N>(frexp(low_half(a), &el),
                         frexp(high_half(a), &eh));
        vec<int16_t, _N> er(el, eh);
        *e = er;
    } else {
        r=vec<f16_t, _N>(frexp(low_half(a), nullptr),
                         frexp(high_half(a), nullptr));
    }
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
nextafter(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(nextafter(low_half(x), low_half(y)),
                     nextafter(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::int16_t, _N>
cftal::ilogb(const vec<cftal::f16_t, _N>& v)
{
    vec<int16_t, _N> r(ilogb(low_half(v)), ilogb(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rsqrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(rsqrt(low_half(v)), rsqrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cbrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cbrt(low_half(v)), cbrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rcbrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(rcbrt(low_half(v)), rcbrt(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::root12(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(root12(low_half(v)), root12(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
hypot(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(hypot(low_half(x), low_half(y)),
                     hypot(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp(low_half(v)), exp(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::expm1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(expm1(low_half(v)), expm1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp2(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp2(low_half(v)), exp2(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp2m1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp2m1(low_half(v)), exp2m1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp10(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp10(low_half(v)), exp10(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp10m1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp10m1(low_half(v)), exp10m1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sinh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sinh(low_half(v)), sinh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cosh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cosh(low_half(v)), cosh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tanh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tanh(low_half(v)), tanh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log(low_half(v)), log(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log2(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log2(low_half(v)), log2(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log10(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log10(low_half(v)), log10(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log1p(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log1p(low_half(v)), log1p(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log2p1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log2p1(low_half(v)), log2p1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log10p1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log10p1(low_half(v)), log10p1(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::pow(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::pow(const vec<cftal::f16_t, _N>& x, const vec<cftal::int16_t, _N>& y)
{
    vec<f16_t, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rootn(const vec<cftal::f16_t, _N>& x, const vec<cftal::int16_t, _N>& y)
{
    vec<f16_t, _N> r(rootn(low_half(x), low_half(y)),
                     rootn(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sin(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sin(low_half(v)), sin(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cos(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cos(low_half(v)), cos(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
void
cftal::sincos(const vec<cftal::f16_t, _N>& v,
              vec<cftal::f16_t, _N>* s, vec<cftal::f16_t, _N>* c)
{
    if (s != nullptr && c != nullptr) {
        vec<f16_t, _N/2> sl, sh, cl, ch;
        sincos(low_half(v), &sl, &cl);
        sincos(high_half(v), &sh, &ch);
        *s= vec<f16_t, _N>(sl, sh);
        *c= vec<f16_t, _N>(cl, ch);
    } else if (s != nullptr) {
        *s = sin(v);
    } else if (c != nullptr) {
        *c = cos(v);
    }
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tan(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tan(low_half(v)), tan(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sinpi(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sinpi(low_half(v)), sinpi(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cospi(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cospi(low_half(v)), cospi(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
void
cftal::sinpicospi(const vec<cftal::f16_t, _N>& v,
                  vec<cftal::f16_t, _N>* s, vec<cftal::f16_t, _N>* c)
{
    if (s != nullptr && c != nullptr) {
        vec<f16_t, _N/2> sl, sh, cl, ch;
        sinpicospi(low_half(v), &sl, &cl);
        sinpicospi(high_half(v), &sh, &ch);
        *s= vec<f16_t, _N>(sl, sh);
        *c= vec<f16_t, _N>(cl, ch);
    } else if (s != nullptr) {
        *s = sinpi(v);
    } else if (c != nullptr) {
        *c = cospi(v);
    }
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tanpi(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tanpi(low_half(v)), tanpi(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::atan2(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(atan2(low_half(x), low_half(y)),
                     atan2(high_half(x), high_half(y)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::asin(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(asin(low_half(v)), asin(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::acos(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(acos(low_half(v)), acos(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::atan(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(atan(low_half(v)), atan(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::asinh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(asinh(low_half(v)), asinh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::acosh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(acosh(low_half(v)), acosh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::atanh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(atanh(low_half(v)), atanh(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::erf(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(erf(low_half(v)), erf(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::erfc(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(erfc(low_half(v)), erfc(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tgamma(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tgamma(low_half(v)), tgamma(high_half(v)));
    return r;
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::lgamma(const vec<cftal::f16_t, _N>& v, vec<int16_t, _N>* signp)
{
    vec<int16_t, _N/2> sl, sh;
    vec<f16_t, _N> r(lgamma(low_half(v), &sl),
                     lgamma(high_half(v), &sh));
    if (signp)
        *signp=vec<int16_t, _N>(sl, sh);
    return r;
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::j0(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(j0(low_half(x)),
                          j0(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::j1(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(j1(low_half(x)),
                          j1(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::y0(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(y0(low_half(x)),
                          y0(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::y1(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(y1(low_half(x)),
                          y1(high_half(x)));
}


template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::exp_mx2(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(exp_mx2(low_half(x)),
                          exp_mx2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::exp_px2(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(exp_px2(low_half(x)),
                          exp_px2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::exp2_mx2(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(exp2_mx2(low_half(x)),
                          exp2_mx2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::exp2_px2(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(exp2_px2(low_half(x)),
                          exp2_px2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::exp10_mx2(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(exp10_mx2(low_half(x)),
                          exp10_mx2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::exp10_px2(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(exp10_px2(low_half(x)),
                          exp10_px2(high_half(x)));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::sig(const vec<f16_t, _N>& x)
{
    return vec<f16_t, _N>(sig(low_half(x)),
                          sig(high_half(x)));
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_VEC_F16_H__
