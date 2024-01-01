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
    nextafter(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y);

    template <size_t _N>
    vec<f16_t, _N>
    sqrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    rsqrt(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    cbrt(const vec<f16_t, _N>& x);

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

    template <std::size_t _N>
    vec<f16_t, _N>
    pow(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y);

    template <std::size_t _N>
    vec<f16_t, _N>
    pow(const vec<f16_t, _N>& x, const vec<int16_t, _N>& y);

    template <std::size_t _N>
    vec<f16_t, _N>
    rootn(const vec<f16_t, _N>& x, const vec<int16_t, _N>& y);

    template <std::size_t _N>
    vec<f16_t, _N>
    sin(const vec<f16_t, _N>& x);

    template <std::size_t _N>
    vec<f16_t, _N>
    cos(const vec<f16_t, _N>& x);

    template <std::size_t _N>
    void
    sincos(const vec<f16_t, _N>& x,
           vec<f16_t, _N>* s, vec<f16_t, _N>* c);

    template <std::size_t _N>
    vec<f16_t, _N>
    tan(const vec<f16_t, _N>& x);

    template <std::size_t _N>
    vec<f16_t, _N>
    sinpi(const vec<f16_t, _N>& x);

    template <std::size_t _N>
    vec<f16_t, _N>
    cospi(const vec<f16_t, _N>& x);

    template <std::size_t _N>
    void
    sinpicospi(const vec<f16_t, _N>& x,
               vec<f16_t, _N>* s, vec<f16_t, _N>* c);

    template <std::size_t _N>
    vec<f16_t, _N>
    tanpi(const vec<f16_t, _N>& x);

// #if V1F16_FUNCS > 0
    vec<f16_t, 1>
    ldexp(arg_t<vec<f16_t, 1> > a, arg_t<vec<int16_t, 1> > e);

    vec<f16_t, 1>
    nextafter(arg_t<vec<f16_t, 1> > x, arg_t<vec<f16_t, 1> > y);

    vec<f16_t, 1>
    sqrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    rsqrt(arg_t<vec<f16_t, 1> > x);

    vec<f16_t, 1>
    cbrt(arg_t<vec<f16_t, 1> > x);

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

// #endif
#if V2F16_FUNCS>0

    vec<f16_t, 2>
    ldexp(arg_t<vec<f16_t, 2> > a, arg_t<vec<int16_t, 2> > e);

    vec<f16_t, 2>
    nextafter(arg_t<vec<f16_t, 2> > x, arg_t<vec<f16_t, 2> > y);

    vec<f16_t, 2>
    sqrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    rsqrt(arg_t<vec<f16_t, 2> > x);

    vec<f16_t, 2>
    cbrt(arg_t<vec<f16_t, 2> > x);

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
#endif

#if V4F16_FUNCS>0

    vec<f16_t, 4>
    ldexp(arg_t<vec<f16_t, 4> > a, arg_t<vec<int16_t, 4> > e);

    vec<f16_t, 4>
    nextafter(arg_t<vec<f16_t, 4> > x, arg_t<vec<f16_t, 4> > y);

    vec<f16_t, 4>
    sqrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    rsqrt(arg_t<vec<f16_t, 4> > x);

    vec<f16_t, 4>
    cbrt(arg_t<vec<f16_t, 4> > x);

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

#endif
#if V8F16_FUNCS>0

    vec<f16_t, 8>
    ldexp(arg_t<vec<f16_t, 8> > a, arg_t<vec<int16_t, 8> > e);

    vec<f16_t, 8>
    nextafter(arg_t<vec<f16_t, 8> > x, arg_t<vec<f16_t, 8> > y);

    vec<f16_t, 8>
    sqrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    rsqrt(arg_t<vec<f16_t, 8> > x);

    vec<f16_t, 8>
    cbrt(arg_t<vec<f16_t, 8> > x);

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

#endif
#if V16F16_FUNCS>0

    vec<f16_t, 16>
    ldexp(arg_t<vec<f16_t, 16> > a, arg_t<vec<int16_t, 16> > e);

    vec<f16_t, 16>
    nextafter(arg_t<vec<f16_t, 16> > x, arg_t<vec<f16_t, 16> > y);

    vec<f16_t, 16>
    sqrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    rsqrt(arg_t<vec<f16_t, 16> > x);

    vec<f16_t, 16>
    cbrt(arg_t<vec<f16_t, 16> > x);

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

#endif
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
ldexp(const vec<cftal::f16_t, _N>& v, const vec<cftal::int16_t, _N>& e)
{
    vec<f16_t, _N> r(ldexp(low_half(v), low_half(e)),
                     ldexp(high_half(v), low_half(e)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
nextafter(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(nextafter(low_half(x), low_half(y)),
                     nextafter(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sqrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sqrt(low_half(v)), sqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rsqrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(rsqrt(low_half(v)), rsqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cbrt(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cbrt(low_half(v)), cbrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::
hypot(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(hypot(low_half(x), low_half(y)),
                     hypot(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp(low_half(v)), exp(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::expm1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(expm1(low_half(v)), expm1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp2(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp2(low_half(v)), exp2(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp2m1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp2m1(low_half(v)), exp2m1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp10(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp10(low_half(v)), exp10(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::exp10m1(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(exp10m1(low_half(v)), exp10m1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sinh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sinh(low_half(v)), sinh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cosh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cosh(low_half(v)), cosh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tanh(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tanh(low_half(v)), tanh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log(low_half(v)), log(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log2(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log2(low_half(v)), log2(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log10(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log10(low_half(v)), log10(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::log1p(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(log1p(low_half(v)), log1p(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::pow(const vec<cftal::f16_t, _N>& x, const vec<cftal::f16_t, _N>& y)
{
    vec<f16_t, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::pow(const vec<cftal::f16_t, _N>& x, const vec<cftal::int16_t, _N>& y)
{
    vec<f16_t, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rootn(const vec<cftal::f16_t, _N>& x, const vec<cftal::int16_t, _N>& y)
{
    vec<f16_t, _N> r(rootn(low_half(x), low_half(y)),
                     rootn(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sin(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sin(low_half(v)), sin(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cos(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cos(low_half(v)), cos(high_half(v)));
    return r;
}

template <std::size_t _N>
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

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tan(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tan(low_half(v)), tan(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::sinpi(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(sinpi(low_half(v)), sinpi(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::cospi(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(cospi(low_half(v)), cospi(high_half(v)));
    return r;
}

template <std::size_t _N>
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

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::tanpi(const vec<cftal::f16_t, _N>& v)
{
    vec<f16_t, _N> r(tanpi(low_half(v)), tanpi(high_half(v)));
    return r;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_VEC_F16_H__
