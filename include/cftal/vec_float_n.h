//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_FLOAT_N_H__)
#define __CFTAL_VEC_FLOAT_N_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_1.h>
#include <cftal/d_real.h>
#include <cftal/fenv.h>
#include <cmath>
#if defined (__ARM_NEON__) || defined (__ARM_NEON)
#include <cftal/arm/v2f32.h>
#endif
#if defined (__SSE2__)
#include <cftal/x86/v4f32.h>
#endif
#if defined (__AVX__)
#include <cftal/x86/v8f32.h>
#endif

namespace cftal {

    template <std::size_t _N>
    vec<float, _N>
    abs(const vec<float, _N>& v);

    // returns (~a) & (b)
    template <std::size_t _N>
    vec<float, _N>
    andnot(const vec<float, _N>& a, const vec<float, _N>& b);

    template <std::size_t _N>
    vec<float, _N>
    copysign(const vec<float, _N>& x, const vec<float, _N>& y);

    template <std::size_t _N>
    vec<float, _N>
    mulsign(const vec<float, _N>& x, const vec<float, _N>& y);

    // return a*b +c with or without fma
    template <std::size_t _N>
    vec<float, _N>
    mad(const vec<float, _N>& a, const vec<float, _N>& b,
        const vec<float, _N>& c);

    // return -(a*b) +c = c - a * b with or without fma
    template <std::size_t _N>
    vec<float, _N>
    nmad(const vec<float, _N>& a, const vec<float, _N>& b,
         const vec<float, _N>& c);


    template <std::size_t _N>
    vec<float, _N>
    cos(const vec<float, _N>& v);


    template <std::size_t _N>
    vec<float, _N>
    tan(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    exp2(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    exp2m1(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    exp10(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    sinh(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    cosh(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    pow(const vec<float, _N>& x, const vec<float, _N>& y);

    template <std::size_t _N>
    vec<float, _N>
    atan2(const vec<float, _N>& x, const vec<float, _N>& y);

    template <std::size_t _N>
    typename vec<float, _N>::mask_type
    isinf(const vec<float, _N>& v);

    template <std::size_t _N>
    typename vec<float, _N>::mask_type
    isnan(const vec<float, _N>& v);

    template <std::size_t _N>
    typename vec<float, _N>::mask_type
    isfinite(const vec<float, _N>& v);

    // a*b +c
    template <std::size_t _N>
    vec<float, _N>
    fma(const vec<float, _N>& a, const vec<float, _N>& b,
        const vec<float, _N>& c);

    vec<float, 1>
    fma(const vec<float, 1>& a, const vec<float, 1>& b,
        const vec<float, 1>& c);

    // a*b -c
    template <std::size_t _N>
    vec<float, _N>
    fms(const vec<float, _N>& a, const vec<float, _N>& b,
        const vec<float, _N>& c);

    vec<float, 1>
    fms(const vec<float, 1>& a, const vec<float, 1>& b,
        const vec<float, 1>& c);
    // -(a*b) + c
    template <std::size_t _N>
    vec<float, _N>
    nfma(const vec<float, _N>& a, const vec<float, _N>& b,
         const vec<float, _N>& c);
    vec<float, 1>
    nfma(const vec<float, 1>& a, const vec<float, 1>& b,
         const vec<float, 1>& c);
    // -(a*b) - c
    template <std::size_t _N>
    vec<float, _N>
    nfms(const vec<float, _N>& a, const vec<float, _N>& b,
         const vec<float, _N>& c);
    vec<float, 1>
    nfms(const vec<float, 1>& a, const vec<float, 1>& b,
         const vec<float, 1>& c);

    // TODO: tests for the functions above
    template <std::size_t _N>
    vec<float, _N>
    frexp(const vec<float, _N>& a, vec<int32_t, _N>* e);

    vec<float, 1>
    frexp(arg<vec<float, 1> >::type a, vec<int32_t, 1>* e);

    vec<float, 2>
    frexp(arg<vec<float, 2> >::type a, vec<int32_t, 2>* e);

    vec<float, 4>
    frexp(arg<vec<float, 4> >::type x, vec<int32_t, 4>* e);

    vec<float, 8>
    frexp(arg<vec<float, 8> >::type x, vec<int32_t, 8>* e);

    vec<float, 16>
    frexp(arg<vec<float, 16> >::type x, vec<int32_t, 16>* e);

    // ldexp, +-0 ulp
    template <std::size_t _N>
    vec<float, _N>
    ldexp(const vec<float, _N>& a, const vec<int32_t, _N>& e);

    vec<float, 1>
    ldexp(arg<vec<float, 1> >::type a, arg<vec<int32_t, 1> >::type e);

    vec<float, 2>
    ldexp(arg<vec<float, 2> >::type a, arg<vec<int32_t, 2> >::type e);

    vec<float, 4>
    ldexp(arg<vec<float, 4> >::type a, arg<vec<int32_t, 4> >::type e);

    vec<float, 8>
    ldexp(arg<vec<float, 8> >::type a, arg<vec<int32_t, 8> >::type e);

    vec<float, 16>
    ldexp(arg<vec<float, 16> >::type a, arg<vec<int32_t, 16> >::type e);

    // nextafter, 0 ulps
    template <std::size_t _N>
    vec<float, _N>
    nextafter(const vec<float, _N>& x, const vec<float, _N>& y);

    vec<float, 1>
    nextafter(arg_t<vec<float, 1> > x, arg_t<vec<float, 1> > y);

    vec<float, 2>
    nextafter(arg_t<vec<float, 2> > b, arg_t<vec<float, 2> > e);

    vec<float, 4>
    nextafter(arg_t<vec<float, 4> > b, arg_t<vec<float, 4> > e);

    vec<float, 8>
    nextafter(arg_t<vec<float, 8> > b, arg_t<vec<float, 8> > e);

    vec<float, 16>
    nextafter(arg_t<vec<float, 16> > b, arg_t<vec<float, 16> > e);

    // ilogb
    template <std::size_t _N>
    vec<int32_t, _N>
    ilogb(const vec<float, _N>& a);

    vec<int32_t, 1>
    ilogb(arg<vec<float, 1> >::type a);

    vec<int32_t, 2>
    ilogb(arg<vec<float, 2> >::type a);

    vec<int32_t, 4>
    ilogb(arg<vec<float, 4> >::type a);

    vec<int32_t, 8>
    ilogb(arg<vec<float, 8> >::type a);

    vec<int32_t, 16>
    ilogb(arg<vec<float, 16> >::type a);

    // rint
    template <std::size_t _N>
    vec<float, _N>
    rint(const vec<float, _N>& v);

    vec<float, 1>
    rint(const vec<float, 1>& v);

    // floor
    template <std::size_t _N>
    vec<float, _N>
    floor(const vec<float, _N>& v);

    vec<float, 1>
    floor(const vec<float, 1>& v);

    // ceil
    template <std::size_t _N>
    vec<float, _N>
    ceil(const vec<float, _N>& v);

    vec<float, 1>
    ceil(const vec<float, 1>& v);

    // trunc
    template <std::size_t _N>
    vec<float, _N>
    trunc(const vec<float, _N>& v);

    vec<float, 1>
    trunc(const vec<float, 1>& v);

    // sqrt
    // overloads are inline
    template <std::size_t _N>
    vec<float, _N>
    sqrt(const vec<float, _N>& v);

    vec<float, 1>
    sqrt(const vec<float, 1>& v);

    // rsqrt
    template <std::size_t _N>
    vec<float, _N>
    rsqrt(const vec<float, _N>& v);

    vec<float, 1>
    rsqrt(arg_t<vec<float, 1> > v);

    vec<float, 2>
    rsqrt(arg_t<vec<float, 2> > v);

    vec<float, 4>
    rsqrt(arg_t<vec<float, 4> > v);

    vec<float, 8>
    rsqrt(arg_t<vec<float, 8> > v);

    vec<float, 16>
    rsqrt(arg_t<vec<float, 16> > v);

    // cbrt
    template <std::size_t _N>
    vec<float, _N>
    cbrt(const vec<float, _N>& v);

    vec<float, 1>
    cbrt(arg_t<vec<float, 1> > v);

    vec<float, 2>
    cbrt(arg_t<vec<float, 2> > v);

    vec<float, 4>
    cbrt(arg_t<vec<float, 4> > v);

    vec<float, 8>
    cbrt(arg_t<vec<float, 8> > v);

    vec<float, 16>
    cbrt(arg_t<vec<float, 16> > v);

    // root12
    template <std::size_t _N>
    vec<float, _N>
    root12(const vec<float, _N>& v);

    vec<float, 1>
    root12(arg_t<vec<float, 1> > v);

    vec<float, 2>
    root12(arg_t<vec<float, 2> > v);

    vec<float, 4>
    root12(arg_t<vec<float, 4> > v);

    vec<float, 8>
    root12(arg_t<vec<float, 8> > v);

    vec<float, 16>
    root12(arg_t<vec<float, 16> > v);

    // native rsqrt, defaults to 1/sqrt with vector length 1
    template <std::size_t _N>
    vec<float, _N>
    native_rsqrt(const vec<float, _N>& v);

    vec<float, 1>
    native_rsqrt(const vec<float, 1>& v);

    // exp: exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp(const vec<float, _N>& v);

    vec<float, 1>
    exp(arg<vec<float, 1> >::type v);

    v2f32
    exp(arg<v2f32>::type d);

    v4f32
    exp(arg<v4f32>::type d);

    v8f32
    exp(arg<v8f32>::type d);

    vec<float, 16>
    exp(arg<vec<float, 16> >::type d);

    // expm1, exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    expm1(const vec<float, _N>& v);

    vec<float, 1>
    expm1(arg<vec<float, 1> >::type v);

    v2f32
    expm1(arg<v2f32>::type d);

    v4f32
    expm1(arg<v4f32>::type d);

    v8f32
    expm1(arg<v8f32>::type d);

    vec<float, 16>
    expm1(arg<vec<float, 16> >::type d);

    // exp2, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp2(const vec<float, _N>& v);

    vec<float, 1>
    exp2(arg<vec<float, 1> >::type v);

    vec<float, 2>
    exp2(arg<vec<float, 2> >::type d);

    vec<float, 4>
    exp2(arg<vec<float, 4> >::type d);

    vec<float, 8>
    exp2(arg<vec<float, 8> >::type d);

    vec<float, 16>
    exp2(arg<vec<float, 16> >::type d);

    // exp2m1, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp2m1(const vec<float, _N>& v);

    vec<float, 1>
    exp2m1(arg<vec<float, 1> >::type v);

    vec<float, 2>
    exp2m1(arg<vec<float, 2> >::type d);

    vec<float, 4>
    exp2m1(arg<vec<float, 4> >::type d);

    vec<float, 8>
    exp2m1(arg<vec<float, 8> >::type d);

    vec<float, 16>
    exp2m1(arg<vec<float, 16> >::type d);

    // exp10, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp10(const vec<float, _N>& v);

    vec<float, 1>
    exp10(arg<vec<float, 1> >::type v);

    vec<float, 2>
    exp10(arg<vec<float, 2> >::type d);

    vec<float, 4>
    exp10(arg<vec<float, 4> >::type d);

    vec<float, 8>
    exp10(arg<vec<float, 8> >::type d);

    vec<float, 16>
    exp10(arg<vec<float, 16> >::type d);

    // exp10m1, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp10m1(const vec<float, _N>& v);

    vec<float, 1>
    exp10m1(arg<vec<float, 1> >::type v);

    vec<float, 2>
    exp10m1(arg<vec<float, 2> >::type d);

    vec<float, 4>
    exp10m1(arg<vec<float, 4> >::type d);

    vec<float, 8>
    exp10m1(arg<vec<float, 8> >::type d);

    vec<float, 16>
    exp10m1(arg<vec<float, 16> >::type d);

    // sinh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    sinh(const vec<float, _N>& v);

    vec<float, 1>
    sinh(arg<vec<float, 1> >::type d);

    vec<float, 2>
    sinh(arg<vec<float, 2> >::type d);

    vec<float, 4>
    sinh(arg<vec<float, 4> >::type d);

    vec<float, 8>
    sinh(arg<vec<float, 8> >::type d);

    vec<float, 16>
    sinh(arg<vec<float, 16> >::type d);

    // cosh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    cosh(const vec<float, _N>& v);

    vec<float, 1>
    cosh(arg<vec<float, 1> >::type d);

    vec<float, 2>
    cosh(arg<vec<float, 2> >::type d);

    vec<float, 4>
    cosh(arg<vec<float, 4> >::type d);

    vec<float, 8>
    cosh(arg<vec<float, 8> >::type d);

    vec<float, 16>
    cosh(arg<vec<float, 16> >::type d);

    // tanh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    tanh(const vec<float, _N>& v);

    vec<float, 1>
    tanh(arg<vec<float, 1> >::type d);

    vec<float, 2>
    tanh(arg<vec<float, 2> >::type d);

    vec<float, 4>
    tanh(arg<vec<float, 4> >::type d);

    vec<float, 8>
    tanh(arg<vec<float, 8> >::type d);

    vec<float, 16>
    tanh(arg<vec<float, 16> >::type d);

    // log: exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    log(const vec<float, _N>& v);

    vec<float, 1>
    log(arg<vec<float, 1> >::type v);

    v2f32
    log(arg_t<v2f32> d);

    v4f32
    log(arg_t<v4f32> d);

    v8f32
    log(arg_t<v8f32> d);

    vec<float, 16>
    log(arg<vec<float, 16> >::type d);

    // log: exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    log1p(const vec<float, _N>& v);

    vec<float, 1>
    log1p(arg_t<vec<float, 1> > v);

    vec<float, 2>
    log1p(arg_t<vec<float, 2> > d);

    vec<float, 4>
    log1p(arg_t<vec<float, 4> > d);

    vec<float, 8>
    log1p(arg_t<vec<float, 8> > d);

    vec<float, 16>
    log1p(arg<vec<float, 16> >::type d);

    template <std::size_t _N>
    vec<float, _N>
    log10(const vec<float, _N>& v);

    vec<float, 1>
    log10(arg_t<vec<float, 1> > v);

    vec<float, 2>
    log10(arg_t<vec<float, 2> > d);

    vec<float, 4>
    log10(arg_t<vec<float, 4> > d);

    vec<float, 8>
    log10(arg_t<vec<float, 8> > d);

    vec<float, 16>
    log10(arg<vec<float, 16> >::type d);

    template <std::size_t _N>
    vec<float, _N>
    log2(const vec<float, _N>& v);

    vec<float, 1>
    log2(arg_t<vec<float, 1> > v);

    vec<float, 2>
    log2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    log2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    log2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    log2(arg<vec<float, 16> >::type d);

    // asing, these functions are exact to +XXX ulp
    template <std::size_t _N>
    vec<float, _N>
    asinh(const vec<float, _N>& v);

    vec<float, 1>
    asinh(arg<vec<float, 1> >::type d);

    vec<float, 2>
    asinh(arg<vec<float, 2> >::type d);

    vec<float, 4>
    asinh(arg<vec<float, 4> >::type d);

    vec<float, 8>
    asinh(arg<vec<float, 8> >::type d);

    vec<float, 16>
    asinh(arg<vec<float, 16> >::type d);

    // acosh, these functions are exact to +-2 ulp
    template <std::size_t _N>
    vec<float, _N>
    acosh(const vec<float, _N>& x);

    vec<float, 1>
    acosh(arg_t<vec<float, 1> > d);

    vec<float, 2>
    acosh(arg_t<vec<float, 2> > d);

    vec<float, 4>
    acosh(arg_t<vec<float, 4> > d);

    vec<float, 8>
    acosh(arg_t<vec<float, 8> > d);

    vec<float, 16>
    acosh(arg<vec<float, 16> >::type d);

    // atanh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    atanh(const vec<float, _N>& x);

    vec<float, 1>
    atanh(arg_t<vec<float, 1> > d);

    vec<float, 2>
    atanh(arg_t<vec<float, 2> > d);

    vec<float, 4>
    atanh(arg_t<vec<float, 4> > d);

    vec<float, 8>
    atanh(arg_t<vec<float, 8> > d);

    vec<float, 16>
    atanh(arg<vec<float, 16> >::type d);

    // erf, these functions are exact to XXX ulp
    template <std::size_t _N>
    vec<float, _N>
    erf(const vec<float, _N>& x);

    vec<float, 1>
    erf(arg_t<vec<float, 1> > d);

    vec<float, 2>
    erf(arg_t<vec<float, 2> > d);

    vec<float, 4>
    erf(arg_t<vec<float, 4> > d);

    vec<float, 8>
    erf(arg_t<vec<float, 8> > d);

    vec<float, 16>
    erf(arg<vec<float, 16> >::type d);

    // erfc, these functions are exact to +-1 ulp, but not faithfully rounded
    template <std::size_t _N>
    vec<float, _N>
    erfc(const vec<float, _N>& x);

    vec<float, 1>
    erfc(arg_t<vec<float, 1> > d);

    vec<float, 2>
    erfc(arg_t<vec<float, 2> > d);

    vec<float, 4>
    erfc(arg_t<vec<float, 4> > d);

    vec<float, 8>
    erfc(arg_t<vec<float, 8> > d);

    vec<float, 16>
    erfc(arg_t<vec<float, 16> > d);

    // tgamma, these functions are exact to +-7 ulp
    template <std::size_t _N>
    vec<float, _N>
    tgamma(const vec<float, _N>& x);

    vec<float, 1>
    tgamma(arg_t<vec<float, 1> > d);

    vec<float, 2>
    tgamma(arg_t<vec<float, 2> > d);

    vec<float, 4>
    tgamma(arg_t<vec<float, 4> > d);

    vec<float, 8>
    tgamma(arg_t<vec<float, 8> > d);

    vec<float, 16>
    tgamma(arg_t<vec<float, 16> > d);

    // pow
    template <std::size_t _N>
    vec<float, _N>
    pow(const vec<float, _N>& x, const vec<float, _N>& y);

    vec<float, 1>
    pow(arg_t<vec<float, 1> > x, arg_t<vec<float, 1> > y);

    vec<float, 2>
    pow(arg<vec<float, 2> >::type b, arg<vec<float, 2> >::type e);

    vec<float, 4>
    pow(arg<vec<float, 4> >::type b, arg<vec<float, 4> >::type e);

    vec<float, 8>
    pow(arg<vec<float, 8> >::type b, arg<vec<float, 8> >::type e);

    vec<float, 16>
    pow(arg<vec<float, 16> >::type b, arg<vec<float, 16> >::type e);


// TODO: tests for the functions below
    template <std::size_t _N>
    vec<float, _N>
    sin(const vec<float, _N>& v);


    v2f32 frexp(arg<v2f32>::type x, v2s32* e);

    // v2f32 pow2i(arg<v2s32>::type e);
    v1s32 ilogbp1(arg<v1f32>::type v);
    v2s32 ilogbp1(arg<v2f32>::type v);

    // v2s32 ilogb(arg<v2f32>::type v);

    v1f32 atan2(arg<v1f32>::type y, arg<v1f32>::type x);
    v2f32 atan2(arg<v2f32>::type y, arg<v2f32>::type x);

    v1f32 asin(arg<v1f32>::type d);
    v2f32 asin(arg<v2f32>::type d);
    v1f32 acos(arg<v1f32>::type d);
    v2f32 acos(arg<v2f32>::type d);

    v1f32 atan(arg<v1f32>::type d);
    v2f32 atan(arg<v2f32>::type d);

    // std::pair<v2f32, v2f32> sincos(arg<v2f32>::type d);

    void sincos(arg<v1f32>::type d, v1f32* psin, v1f32* pcos);
    void sincos(arg<v2f32>::type d, v2f32* psin, v2f32* pcos);

    v1f32 sin(arg<v1f32>::type d);
    v2f32 sin(arg<v2f32>::type d);

    v1f32 cos(arg<v1f32>::type d);
    v2f32 cos(arg<v2f32>::type d);

    v1f32 tan(arg<v1f32>::type d);
    v2f32 tan(arg<v2f32>::type d);




    v4f32 frexp(arg<v4f32>::type x, v4s32* e);
    // v4f32 pow2i(arg<v4s32>::type e);
    v4s32 ilogbp1(arg<v4f32>::type v);
    v4s32 ilogb(arg<v4f32>::type v);
    v4f32 atan2(arg<v4f32>::type y, arg<v4f32>::type x);
    v4f32 asin(arg<v4f32>::type d);
    v4f32 acos(arg<v4f32>::type d);

    v4f32 atan(arg<v4f32>::type d);
    std::pair<v4f32, v4f32> sincos(arg<v4f32>::type d);

    void sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
    v4f32 sin(arg<v4f32>::type d);
    v4f32 cos(arg<v4f32>::type d);
    v4f32 tan(arg<v4f32>::type d);
    v4f32 atan2(arg<v4f32>::type x, arg<v4f32>::type y);


    v8f32 frexp(arg<v8f32>::type x, v8s32* e);
    // v8f32 pow2i(arg<v4s32>::type e);
    v8s32 ilogbp1(arg<v8f32>::type v);
    v16s32 ilogbp1(arg<v16f32>::type v);

    v8s32 ilogb(arg<v8f32>::type v);
    v8f32 atan2(arg<v8f32>::type y, arg<v8f32>::type x);
    v16f32 atan2(arg<v16f32>::type y, arg<v16f32>::type x);
    v8f32 asin(arg<v8f32>::type d);
    v16f32 asin(arg<v16f32>::type d);
    v8f32 acos(arg<v8f32>::type d);
    v16f32 acos(arg<v16f32>::type d);

    v8f32 atan(arg<v8f32>::type d);
    v16f32 atan(arg<v16f32>::type d);
    std::pair<v8f32, v8f32> sincos(arg<v8f32>::type d);

    void sincos(arg<v8f32>::type d, v8f32* psin, v8f32* pcos);
    void sincos(arg<v16f32>::type d, v16f32* psin, v16f32* pcos);
    v8f32 sin(arg<v8f32>::type d);
    v16f32 sin(arg<v16f32>::type d);
    v8f32 cos(arg<v8f32>::type d);
    v16f32 cos(arg<v16f32>::type d);
    v8f32 tan(arg<v8f32>::type d);
    v16f32 tan(arg<v16f32>::type d);
    v8f32 atan2(arg<v8f32>::type x, arg<v8f32>::type y);


    // exp_mx2, calculates $ e^{-x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp_mx2(const vec<float, _N>& x);

    vec<float, 1>
    exp_mx2(arg_t<vec<float, 1> > d);

    vec<float, 2>
    exp_mx2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    exp_mx2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    exp_mx2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    exp_mx2(arg_t<vec<float, 16> > d);

    // exp_px2, calculates $ e^{+x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp_px2(const vec<float, _N>& x);

    vec<float, 1>
    exp_px2(arg_t<vec<float, 1> > d);

    vec<float, 2>
    exp_px2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    exp_px2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    exp_px2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    exp_px2(arg_t<vec<float, 16> > d);

    // exp2_mx2, calculates $ 2^{-x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp2_mx2(const vec<float, _N>& x);

    vec<float, 1>
    exp2_mx2(arg_t<vec<float, 1> > d);

    vec<float, 2>
    exp2_mx2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    exp2_mx2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    exp2_mx2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    exp2_mx2(arg_t<vec<float, 16> > d);

    // exp2_px2, calculates $ 2^{+x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp2_px2(const vec<float, _N>& x);

    vec<float, 1>
    exp2_px2(arg_t<vec<float, 1> > d);

    vec<float, 2>
    exp2_px2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    exp2_px2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    exp2_px2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    exp2_px2(arg_t<vec<float, 16> > d);

    // exp10_mx2, calculates $ 10^{-x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp10_mx2(const vec<float, _N>& x);

    vec<float, 1>
    exp10_mx2(arg_t<vec<float, 1> > d);

    vec<float, 2>
    exp10_mx2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    exp10_mx2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    exp10_mx2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    exp10_mx2(arg_t<vec<float, 16> > d);

    // exp10_px2, calculates $ 10^{+x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<float, _N>
    exp10_px2(const vec<float, _N>& x);

    vec<float, 1>
    exp10_px2(arg_t<vec<float, 1> > d);

    vec<float, 2>
    exp10_px2(arg_t<vec<float, 2> > d);

    vec<float, 4>
    exp10_px2(arg_t<vec<float, 4> > d);

    vec<float, 8>
    exp10_px2(arg_t<vec<float, 8> > d);

    vec<float, 16>
    exp10_px2(arg_t<vec<float, 16> > d);

    // approximates 1/a
    template <std::size_t _N>
    vec<float, _N>
    native_recip(const vec<float, _N>& a);

    // approximates 1/a
    vec<float, 1>
    native_recip(const vec<float, 1>& b);

    // approximates a/b
    template <std::size_t _N>
    vec<float, _N>
    native_div(const vec<float, _N>& a, const vec<float, _N>& b);

    // approximates a/b
    vec<float, 1>
    native_div(const vec<float, 1>& a, const vec<float, 1>& b);

    // namespace for functions with reduced range and precision
    // similiar to opencl c++ 2.0
    namespace half_math {

        // for all functions below:
        // range: +- 2^16
        // precision: +-8 ulps

        template <std::size_t _N>
        vec<float, _N>
        cos(const vec<float, _N>& v);

        vec<float, 1>
        cos(arg_t<vec<float, 1> > v);

        vec<float, 2>
        cos(arg_t<vec<float, 2> > v);

        vec<float, 4>
        cos(arg_t<vec<float, 4> > v);

        vec<float, 8>
        cos(arg_t<vec<float, 8> > v);

        vec<float, 16>
        cos(arg_t<vec<float, 16> > v);

        template <std::size_t _N>
        vec<float, _N>
        divide(const vec<float, _N>& x, const vec<float, _N>& y);

        template <std::size_t _N>
        vec<float, _N>
        exp(const vec<float, _N>& v);

        vec<float, 1>
        exp(arg_t<vec<float, 1> > v);

        vec<float, 2>
        exp(arg_t<vec<float, 2> > v);

        vec<float, 4>
        exp(arg_t<vec<float, 4> > v);

        vec<float, 8>
        exp(arg_t<vec<float, 8> > v);

        vec<float, 16>
        exp(arg_t<vec<float, 16> > v);


        template <std::size_t _N>
        vec<float, _N>
        exp2(const vec<float, _N>& v);

        vec<float, 1>
        exp2(arg_t<vec<float, 1> > v);

        vec<float, 2>
        exp2(arg_t<vec<float, 2> > v);

        vec<float, 4>
        exp2(arg_t<vec<float, 4> > v);

        vec<float, 8>
        exp2(arg_t<vec<float, 8> > v);

        vec<float, 16>
        exp2(arg_t<vec<float, 16> > v);


        template <std::size_t _N>
        vec<float, _N>
        exp10(const vec<float, _N>& v);

        vec<float, 1>
        exp10(arg_t<vec<float, 1> > v);

        vec<float, 2>
        exp10(arg_t<vec<float, 2> > v);

        vec<float, 4>
        exp10(arg_t<vec<float, 4> > v);

        vec<float, 8>
        exp10(arg_t<vec<float, 8> > v);

        vec<float, 16>
        exp10(arg_t<vec<float, 16> > v);


        template <std::size_t _N>
        vec<float, _N>
        log(const vec<float, _N>& v);

        vec<float, 1>
        log(arg_t<vec<float, 1> > v);

        vec<float, 2>
        log(arg_t<vec<float, 2> > v);

        vec<float, 4>
        log(arg_t<vec<float, 4> > v);

        vec<float, 8>
        log(arg_t<vec<float, 8> > v);

        vec<float, 16>
        log(arg_t<vec<float, 16> > v);


        template <std::size_t _N>
        vec<float, _N>
        log2(const vec<float, _N>& v);

        vec<float, 1>
        log2(arg_t<vec<float, 1> > v);

        vec<float, 2>
        log2(arg_t<vec<float, 2> > v);

        vec<float, 4>
        log2(arg_t<vec<float, 4> > v);

        vec<float, 8>
        log2(arg_t<vec<float, 8> > v);

        vec<float, 16>
        log2(arg_t<vec<float, 16> > v);


        template <std::size_t _N>
        vec<float, _N>
        log10(const vec<float, _N>& v);

        vec<float, 1>
        log10(arg_t<vec<float, 1> > v);

        vec<float, 2>
        log10(arg_t<vec<float, 2> > v);

        vec<float, 4>
        log10(arg_t<vec<float, 4> > v);

        vec<float, 8>
        log10(arg_t<vec<float, 8> > v);

        vec<float, 16>
        log10(arg_t<vec<float, 16> > v);


#if 0
        template <std::size_t _N>
        vec<float, _N>
        powr(const vec<float, _N>& x, const vec<float, _N>& y);
#endif

        template <std::size_t _N>
        vec<float, _N>
        recip(const vec<float, _N>& v);

        template <std::size_t _N>
        vec<float, _N>
        rsqrt(const vec<float, _N>& v);

        vec<float, 1>
        rsqrt(arg_t<vec<float, 1> > v);

        vec<float, 2>
        rsqrt(arg_t<vec<float, 2> > v);

        vec<float, 4>
        rsqrt(arg_t<vec<float, 4> > v);

        vec<float, 8>
        rsqrt(arg_t<vec<float, 8> > v);

        vec<float, 16>
        rsqrt(arg_t<vec<float, 16> > v);


        template <std::size_t _N>
        vec<float, _N>
        sin(const vec<float, _N>& v);

        vec<float, 1>
        sin(arg_t<vec<float, 1> > v);

        vec<float, 2>
        sin(arg_t<vec<float, 2> > v);

        vec<float, 4>
        sin(arg_t<vec<float, 4> > v);

        vec<float, 8>
        sin(arg_t<vec<float, 8> > v);

        vec<float, 16>
        sin(arg_t<vec<float, 16> > v);

        template <std::size_t _N>
        vec<float, _N>
        sqrt(const vec<float, _N>& v);

        vec<float, 1>
        sqrt(arg_t<vec<float, 1> > v);

        vec<float, 2>
        sqrt(arg_t<vec<float, 2> > v);

        vec<float, 4>
        sqrt(arg_t<vec<float, 4> > v);

        vec<float, 8>
        sqrt(arg_t<vec<float, 8> > v);

        vec<float, 16>
        sqrt(arg_t<vec<float, 16> > v);

        template <std::size_t _N>
        vec<float, _N>
        tan(const vec<float, _N>& v);

        vec<float, 1>
        tan(arg_t<vec<float, 1> > v);

        vec<float, 2>
        tan(arg_t<vec<float, 2> > v);

        vec<float, 4>
        tan(arg_t<vec<float, 4> > v);

        vec<float, 8>
        tan(arg_t<vec<float, 8> > v);

        vec<float, 16>
        tan(arg_t<vec<float, 16> > v);

    };
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::abs(const vec<float, _N>& v)
{
    const vec<float, _N> msk(not_sign_f32_msk::v.f32());
    return v & msk;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::andnot(const vec<float, _N>& a, const vec<float, _N>& b)
{
    return vec<float, _N>((~a) & b);
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::copysign(const vec<float, _N>& x, const vec<float, _N>& y)
{
    // return abs(x) * sgn(y)
    using v_t = vec<float, _N>;
    const v_t msk(not_sign_f32_msk::v.f32());
    v_t abs_x(x & msk);
    v_t sgn_y(andnot(msk, y));
    return v_t(abs_x | sgn_y);
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::mulsign(const vec<float, _N>& x, const vec<float, _N>& y)
{
    using v_t = vec<float, _N>;
    const v_t msk(sign_f32_msk::v.f32());
    v_t sgn_y = y & msk;
    return v_t(x ^ sgn_y);
}


template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::mad(const vec<float, _N>& a, const vec<float, _N>& b,
           const vec<float, _N>& c)
{
    return a * b + c;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::nmad(const vec<float, _N>& a, const vec<float, _N>& b,
            const vec<float, _N>& c)
{
    return c - a * b;
}

template <std::size_t _N>
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

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::rsqrt(const vec<float, _N>& v)
{
    vec<float, _N> r(rsqrt(low_half(v)), rsqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::native_rsqrt(const vec<float, _N>& v)
{
    vec<float, _N> r(native_rsqrt(low_half(v)),
                     native_rsqrt(high_half(v)));
    return r;
}

inline
cftal::vec<float, 1>
cftal::native_rsqrt(const vec<float, 1>& x)
{
#if defined (__SSE__)
    v1f32 y= _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set1_ps(x())));
    y = y + (0.5f*y) * (1.0f- y*(x * y));
    // y= 0.5f*y *(3.0f - y*(y*x));
    return y;
#else
    vec<float, 1> r(1.0f/sqrt(v));
    return r;
#endif
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::cbrt(const vec<float, _N>& v)
{
    vec<float, _N> r(cbrt(low_half(v)), cbrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::root12(const vec<float, _N>& v)
{
    vec<float, _N> r(root12(low_half(v)), root12(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::sin(const vec<float, _N>& v)
{
    vec<float, _N> r(sin(low_half(v)), sin(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::cos(const vec<float, _N>& v)
{
    vec<float, _N> r(cos(low_half(v)), cos(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::tan(const vec<float, _N>& v)
{
    vec<float, _N> r(tan(low_half(v)), tan(high_half(v)));
    return r;
}


template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp(const vec<float, _N>& v)
{
    vec<float, _N> r(exp(low_half(v)), exp(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::expm1(const vec<float, _N>& v)
{
    vec<float, _N> r(expm1(low_half(v)), expm1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp2(const vec<float, _N>& v)
{
    vec<float, _N> r(exp2(low_half(v)), exp2(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp2m1(const vec<float, _N>& v)
{
    vec<float, _N> r(exp2m1(low_half(v)), exp2m1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp10(const vec<float, _N>& v)
{
    vec<float, _N> r(exp10(low_half(v)), exp10(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::exp10m1(const vec<float, _N>& v)
{
    vec<float, _N> r(exp10m1(low_half(v)), exp10m1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::log(const vec<float, _N>& v)
{
    vec<float, _N> r(log(low_half(v)), log(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::log1p(const vec<float, _N>& v)
{
    vec<float, _N> r(log1p(low_half(v)), log1p(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::log10(const vec<float, _N>& v)
{
    vec<float, _N> r(log10(low_half(v)), log10(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::log2(const vec<float, _N>& v)
{
    vec<float, _N> r(log2(low_half(v)), log2(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::sinh(const vec<float, _N>& v)
{
    vec<float, _N> r(sinh(low_half(v)), sinh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::asinh(const vec<float, _N>& v)
{
    vec<float, _N> r(asinh(low_half(v)), asinh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::acosh(const vec<float, _N>& v)
{
    vec<float, _N> r(acosh(low_half(v)), acosh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::atanh(const vec<float, _N>& v)
{
    vec<float, _N> r(atanh(low_half(v)), atanh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::erf(const vec<float, _N>& v)
{
    vec<float, _N> r(erf(low_half(v)), erf(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::erfc(const vec<float, _N>& v)
{
    vec<float, _N> r(erfc(low_half(v)), erfc(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::tgamma(const vec<float, _N>& v)
{
    vec<float, _N> r(tgamma(low_half(v)), tgamma(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::cosh(const vec<float, _N>& v)
{
    vec<float, _N> r(cosh(low_half(v)), cosh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::tanh(const vec<float, _N>& v)
{
    vec<float, _N> r(tanh(low_half(v)), tanh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::pow(const vec<float, _N>& x, const vec<float, _N>& y)
{
    vec<float, _N> r(pow(low_half(x), low_half(y)),
                     pow(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::atan2(const vec<float, _N>& x, const vec<float, _N>& y)
{
    vec<float, _N> r(atan2(low_half(x), low_half(y)),
                     atan2(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isnan(const vec<float, _N>& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

template <std::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isinf(const vec<float, _N>& x)
{
    vec<float, _N> absx(abs(x));
    const vec<float, _N> vm(exp_f32_msk::v.f32());
    return absx == vm;
}

template <std::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isfinite(const vec<float, _N>& x)
{
    return ~(isinf(x) | isnan(x));
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::fma(const vec<float, _N>& a, const vec<float, _N>& b,
           const vec<float, _N>& c)
{
    return vec<float, _N>(fma(low_half(a), low_half(b), low_half(c)),
                          fma(high_half(a), high_half(b), high_half(c)));
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::fms(const vec<float, _N>& a, const vec<float, _N>& b,
           const vec<float, _N>& c)
{
    return vec<float, _N>(fms(low_half(a), low_half(b), low_half(c)),
                          fms(high_half(a), high_half(b), high_half(c)));
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::nfma(const vec<float, _N>& a, const vec<float, _N>& b,
            const vec<float, _N>& c)
{
    return vec<float, _N>(nfma(low_half(a), low_half(b), low_half(c)),
                          nfma(high_half(a), high_half(b), high_half(c)));
}

template <std::size_t _N>
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

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::frexp(const vec<float, _N>& a, vec<int32_t, _N>* e)
{
    vec<int32_t, _N/2> el, eh;
    vec<float, _N> r(frexp(low_half(a), &el),
                     frexp(high_half(a), &eh));
    if (e != nullptr) {
        vec<int32_t, _N> er(el, eh);
        *e = er;
    }
    return r;
}


template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::ldexp(const vec<float, _N>& a, const vec<int32_t, _N>& e)
{
    return vec<float, _N>(ldexp(low_half(a), low_half(e)),
                          ldexp(high_half(a), high_half(e)));
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::nextafter(const vec<float, _N>& a, const vec<float, _N>& b)
{
    return vec<float, _N>(nextafter(low_half(a), low_half(b)),
                          nextafter(high_half(a), high_half(b)));
}

template <std::size_t _N>
inline
cftal::vec<int32_t, _N>
cftal::ilogb(const vec<float, _N>& a)
{
    return vec<float, _N>(ilogb(low_half(a)), ilogb(high_half(a)));
}


template <std::size_t _N>
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

template <std::size_t _N>
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

template <std::size_t _N>
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

template <std::size_t _N>
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

template <std::size_t _N>
cftal::vec<float, _N>
cftal::exp_mx2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp_mx2(low_half(x)),
                          exp_mx2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::exp_px2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp_px2(low_half(x)),
                          exp_px2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::exp2_mx2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp2_mx2(low_half(x)),
                          exp2_mx2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::exp2_px2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp2_px2(low_half(x)),
                          exp2_px2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::exp10_mx2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp10_mx2(low_half(x)),
                          exp10_mx2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::exp10_px2(const vec<float, _N>& x)
{
    return vec<float, _N>(exp10_px2(low_half(x)),
                          exp10_px2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::native_recip(const vec<float, _N>& b)
{
    vec<float, _N> r(native_recip(low_half(b)),
                     native_recip(high_half(b)));
    return r;
}

inline
cftal::vec<float, 1>
cftal::native_recip(const vec<float, 1>& a)
{
#if defined (__SSE__)
    v1f32 rcp=_mm_cvtss_f32(_mm_rcp_ss(_mm_set_ss(a())));
    rcp = rcp + rcp*(1-rcp*a);
    return rcp;
#else
    return 1.0f/a();
#endif
}


template <std::size_t _N>
cftal::vec<float, _N>
cftal::native_div(const vec<float, _N>& a, const vec<float, _N>& b)
{
    vec<float, _N> r(native_div(low_half(a), low_half(b)),
                     native_div(high_half(a), high_half(b)));
    return r;
}

inline
cftal::vec<float, 1>
cftal::native_div(const vec<float, 1>& b, const vec<float, 1>& a)
{
#if defined (__SSE__)
    return native_recip(a) * b;
#else
    return b / a;
#endif
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::
cos(const vec<float, _N>& v)
{
    vec<float, _N> r(cos(low_half(v)),
                     cos(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::
divide(const vec<float, _N>& x, const vec<float, _N>& y)
{
    return native_div(x, y);
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::exp(const vec<float, _N>& v)
{
    vec<float, _N> r(exp(low_half(v)),
                     exp(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::exp2(const vec<float, _N>& v)
{
    vec<float, _N> r(exp2(low_half(v)),
                     exp2(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::exp10(const vec<float, _N>& v)
{
    vec<float, _N> r(exp10(low_half(v)),
                     exp10(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::log(const vec<float, _N>& v)
{
    vec<float, _N> r(log(low_half(v)),
                     log(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::log2(const vec<float, _N>& v)
{
    vec<float, _N> r(log2(low_half(v)),
                     log2(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::log10(const vec<float, _N>& v)
{
    vec<float, _N> r(log10(low_half(v)),
                     log10(high_half(v)));
    return r;
}

#if 0
template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::
powr(const vec<float, _N>& x, const vec<float, _N>& y)
{
    vec<float, _N> r(powr(low_half(x), low_half(y)),
                     powr(high_half(x), high_half(y)));
    return r;
}
#endif

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::rsqrt(const vec<float, _N>& v)
{
    vec<float, _N> r(rsqrt(low_half(v)),
                     rsqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::sin(const vec<float, _N>& v)
{
    vec<float, _N> r(sin(low_half(v)),
                     sin(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::sqrt(const vec<float, _N>& v)
{
    // return cftal::sqrt(v);
    vec<float, _N> r(sqrt(low_half(v)),
                     sqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
cftal::vec<float, _N>
cftal::half_math::tan(const vec<float, _N>& v)
{
    vec<float, _N> r(tan(low_half(v)),
                     tan(high_half(v)));
    return r;
}


// local variables:
// mode: c++
// end:
#endif
