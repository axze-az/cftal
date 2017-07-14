//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_DOUBLE_N_H__)
#define __CFTAL_VEC_DOUBLE_N_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_1.h>
#include <cftal/d_real.h>
#include <cmath>
#if defined (__ARM_NEON__) || defined (__ARM_NEON)
#include <cftal/arm/v2f64.h>
#endif
#if defined (__SSE2__)
#include <cftal/x86/v2f64.h>
#endif
#if defined (__AVX__)
#include <cftal/x86/v4f64.h>
#endif
#if defined (__AVX512F__)
#include <cftal/x86/v8f64.h>
#endif

namespace cftal {

    template <std::size_t _N>
    vec<double, _N>
    abs(const vec<double, _N>& v);

    // returns (~a) & (b)
    template <std::size_t _N>
    vec<double, _N>
    andnot(const vec<double, _N>& a, const vec<double, _N>& b);

    template <std::size_t _N>
    vec<double, _N>
    copysign(const vec<double, _N>& x, const vec<double, _N>& y);

    template <std::size_t _N>
    vec<double, _N>
    mulsign(const vec<double, _N>& x, const vec<double, _N>& y);

    // return a*b +c with or without fma
    template <std::size_t _N>
    vec<double, _N>
    mad(const vec<double, _N>& a, const vec<double, _N>& b,
        const vec<double, _N>& c);

    // return -(a*b) +c = c - a * b with or without fma
    template <std::size_t _N>
    vec<double, _N>
    nmad(const vec<double, _N>& a, const vec<double, _N>& b,
         const vec<double, _N>& c);

    template <std::size_t _N>
    typename vec<double, _N>::mask_type
    isinf(const vec<double, _N>& v);

    template <std::size_t _N>
    typename vec<double, _N>::mask_type
    isnan(const vec<double, _N>& v);

    template <std::size_t _N>
    typename vec<double, _N>::mask_type
    isfinite(const vec<double, _N>& v);

    // a*b +c
    template <std::size_t _N>
    vec<double, _N>
    fma(const vec<double, _N>& a, const vec<double, _N>& b,
        const vec<double, _N>& c);

    vec<double, 1>
    fma(const vec<double, 1>& a, const vec<double, 1>& b,
        const vec<double, 1>& c);
    // a*b -c
    template <std::size_t _N>
    vec<double, _N>
    fms(const vec<double, _N>& a, const vec<double, _N>& b,
        const vec<double, _N>& c);

    vec<double, 1>
    fms(const vec<double, 1>& a, const vec<double, 1>& b,
        const vec<double, 1>& c);

    // -(a*b) + c
    template <std::size_t _N>
    vec<double, _N>
    nfma(const vec<double, _N>& a, const vec<double, _N>& b,
         const vec<double, _N>& c);
    // -(a*b) - c
    template <std::size_t _N>
    vec<double, _N>
    nfms(const vec<double, _N>& a, const vec<double, _N>& b,
         const vec<double, _N>& c);

// TODO: --------------------------------------------------------------------
// TODO: test for the functions above

    // frexp
    template <std::size_t _N>
    vec<double, _N>
    frexp(const vec<double, _N>& a, vec<int32_t, _N>* e);

    vec<double, 1>
    frexp(arg_t<vec<double, 1> > a, vec<int32_t, 1>* e);

    vec<double, 2>
    frexp(arg_t<vec<double, 2> > x, vec<int32_t, 2>* e);

    vec<double, 4>
    frexp(arg_t<vec<double, 4> > x, vec<int32_t, 4>* e);

    vec<double, 8>
    frexp(arg_t<vec<double, 8> > x, vec<int32_t, 8>* e);

    // ldexp, 0 ulps
    template <std::size_t _N>
    vec<double, _N>
    ldexp(const vec<double, _N>& a, const vec<int32_t, _N>& e);

    vec<double, 1>
    ldexp(arg_t<vec<double, 1> > a, arg_t<vec<int32_t, 1> > e);

    vec<double, 2>
    ldexp(arg_t<vec<double, 2> > a, arg_t<vec<int32_t, 2> > e);

    vec<double, 4>
    ldexp(arg_t<vec<double, 4> > a, arg_t<vec<int32_t, 4> > e);

    vec<double, 8>
    ldexp(arg_t<vec<double, 8> > a, arg_t<vec<int32_t, 8> > e);

    // ilogb
    template <std::size_t _N>
    vec<int32_t, _N>
    ilogb(const vec<double, _N>& a);

    vec<int32_t, 1>
    ilogb(arg_t<vec<double, 1> > a);

    vec<int32_t, 2>
    ilogb(arg_t<vec<double, 2> > a);

    vec<int32_t, 4>
    ilogb(arg_t<vec<double, 4> > a);

    vec<int32_t, 8>
    ilogb(arg_t<vec<double, 8> > a);

    // rint, specializations are inline
    template <std::size_t _N>
    vec<double, _N>
    rint(const vec<double, _N>& v);

    vec<double, 1>
    rint(const vec<double, 1>& v);

    // floor, specializations are inline
    template <std::size_t _N>
    vec<double, _N>
    floor(const vec<double, _N>& v);

    vec<double, 1>
    floor(const vec<double, 1>& v);

    // ceil, specializations are inline
    template <std::size_t _N>
    vec<double, _N>
    ceil(const vec<double, _N>& v);

    vec<double, 1>
    ceil(const vec<double, 1>& v);

    // trunc, specializations are inline
    template <std::size_t _N>
    vec<double, _N>
    trunc(const vec<double, _N>& v);

    vec<double, 1>
    trunc(const vec<double, 1>& v);

    // sqrt
    // specializations are inline
    template <std::size_t _N>
    vec<double, _N>
    sqrt(const vec<double, _N>& v);

    vec<double, 1>
    sqrt(const vec<double, 1>& v);

    // rsqrt = 1/sqrt
    template <std::size_t _N>
    vec<double, _N>
    rsqrt(const vec<double, _N>& v);

    vec<double, 1>
    rsqrt(arg_t<vec<double, 1> > v);

    vec<double, 2>
    rsqrt(arg_t<vec<double, 2> > v);

    vec<double, 4>
    rsqrt(arg_t<vec<double, 4> > v);

    vec<double, 8>
    rsqrt(arg_t<vec<double, 8> > v);

    // native rsqrt, defaults to 1/sqrt
    template <std::size_t _N>
    vec<double, _N>
    native_rsqrt(const vec<double, _N>& v);

    // cbrt, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    cbrt(const vec<double, _N>& v);

    vec<double, 1>
    cbrt(arg_t<vec<double, 1> > v);

    vec<double, 2>
    cbrt(arg_t<vec<double, 2> > v);

    vec<double, 4>
    cbrt(arg_t<vec<double, 4> > v);

    vec<double, 8>
    cbrt(arg_t<vec<double, 8> > v);

    // root12, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    root12(const vec<double, _N>& v);

    vec<double, 1>
    root12(arg_t<vec<double, 1> > v);

    vec<double, 2>
    root12(arg_t<vec<double, 2> > v);

    vec<double, 4>
    root12(arg_t<vec<double, 4> > v);

    vec<double, 8>
    root12(arg_t<vec<double, 8> > v);

    // exp, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp(const vec<double, _N>& v);

    vec<double, 1>
    exp(arg_t<vec<double, 1> > v);

    vec<double, 2>
    exp(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp(arg_t<vec<double, 8> > d);

    // expm1, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    expm1(const vec<double, _N>& v);

    vec<double, 1>
    expm1(arg_t<vec<double, 1> > v);

    vec<double, 2>
    expm1(arg_t<vec<double, 2> > d);

    vec<double, 4>
    expm1(arg_t<vec<double, 4> > d);

    vec<double, 8>
    expm1(arg_t<vec<double, 8> > d);

    // exp2, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp2(const vec<double, _N>& v);

    vec<double, 1>
    exp2(arg_t<vec<double, 1> > v);

    vec<double, 2>
    exp2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp2(arg_t<vec<double, 8> > d);

    // exp2m1, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp2m1(const vec<double, _N>& v);

    vec<double, 1>
    exp2m1(arg_t<vec<double, 1> > v);

    vec<double, 2>
    exp2m1(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp2m1(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp2m1(arg_t<vec<double, 8> > d);

    // exp10, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp10(const vec<double, _N>& v);

    vec<double, 1>
    exp10(arg_t<vec<double, 1> > v);

    vec<double, 2>
    exp10(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp10(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp10(arg_t<vec<double, 8> > d);

    // exp10m1, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp10m1(const vec<double, _N>& v);

    vec<double, 1>
    exp10m1(arg_t<vec<double, 1> > v);

    vec<double, 2>
    exp10m1(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp10m1(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp10m1(arg_t<vec<double, 8> > d);

    // sinh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    sinh(const vec<double, _N>& v);

    vec<double, 1>
    sinh(arg_t<vec<double, 1> > d);

    vec<double, 2>
    sinh(arg_t<vec<double, 2> > d);

    vec<double, 4>
    sinh(arg_t<vec<double, 4> > d);

    vec<double, 8>
    sinh(arg_t<vec<double, 8> > d);

    // cosh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    cosh(const vec<double, _N>& v);

    vec<double, 1>
    cosh(arg_t<vec<double, 1> > d);

    vec<double, 2>
    cosh(arg_t<vec<double, 2> > d);

    vec<double, 4>
    cosh(arg_t<vec<double, 4> > d);

    vec<double, 8>
    cosh(arg_t<vec<double, 8> > d);

    // cosh, these functions are exact to XXX ulp
    template <std::size_t _N>
    vec<double, _N>
    tanh(const vec<double, _N>& v);

    vec<double, 1>
    tanh(arg_t<vec<double, 1> > d);

    vec<double, 2>
    tanh(arg_t<vec<double, 2> > d);

    vec<double, 4>
    tanh(arg_t<vec<double, 4> > d);

    vec<double, 8>
    tanh(arg_t<vec<double, 8> > d);

    // log, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    log(const vec<double, _N>& v);

    vec<double, 1>
    log(arg_t<vec<double, 1> > v);

    vec<double, 2>
    log(arg_t<vec<double, 2> > d);

    vec<double, 4>
    log(arg_t<vec<double, 4> > d);

    vec<double, 8>
    log(arg_t<vec<double, 8> > d);

    // log1p, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    log1p(const vec<double, _N>& v);

    vec<double, 1>
    log1p(arg_t<vec<double, 1> > v);

    vec<double, 2>
    log1p(arg_t<vec<double, 2> > d);

    vec<double, 4>
    log1p(arg_t<vec<double, 4> > d);

    vec<double, 8>
    log1p(arg_t<vec<double, 8> > d);

    // log10, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    log10(const vec<double, _N>& v);

    vec<double, 1>
    log10(arg_t<vec<double, 1> > v);

    vec<double, 2>
    log10(arg_t<vec<double, 2> > d);

    vec<double, 4>
    log10(arg_t<vec<double, 4> > d);

    vec<double, 8>
    log10(arg_t<vec<double, 8> > d);

    // log2, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    log2(const vec<double, _N>& v);

    vec<double, 1>
    log2(arg_t<vec<double, 1> > v);

    vec<double, 2>
    log2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    log2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    log2(arg_t<vec<double, 8> > d);

    // pow, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    pow(const vec<double, _N>& x, const vec<double, _N>& y);

    vec<double, 1>
    pow(arg_t<vec<double, 1> > x, arg_t<vec<double, 1> > y);

    vec<double, 2>
    pow(arg_t<vec<double, 2> > b, arg_t<vec<double, 2> > e);

    vec<double, 4>
    pow(arg_t<vec<double, 4> > b, arg_t<vec<double, 4> > e);

    vec<double, 8>
    pow(arg_t<vec<double, 8> > b, arg_t<vec<double, 8> > e);

    // atan, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    atan(const vec<double, _N>& x);

    vec<double, 1>
    atan(arg_t<vec<double, 1> > d);

    vec<double, 2>
    atan(arg_t<vec<double, 2> > d);

    vec<double, 4>
    atan(arg_t<vec<double, 4> > d);

    vec<double, 8>
    atan(arg_t<vec<double, 8> > d);

    // asin, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    asin(const vec<double, _N>& x);

    vec<double, 1>
    asin(arg_t<vec<double, 1> > d);

    vec<double, 2>
    asin(arg_t<vec<double, 2> > d);

    vec<double, 4>
    asin(arg_t<vec<double, 4> > d);

    vec<double, 8>
    asin(arg_t<vec<double, 8> > d);

    // acos, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    acos(const vec<double, _N>& x);

    vec<double, 1>
    acos(arg_t<vec<double, 1> > d);

    vec<double, 2>
    acos(arg_t<vec<double, 2> > d);

    vec<double, 4>
    acos(arg_t<vec<double, 4> > d);

    vec<double, 8>
    acos(arg_t<vec<double, 8> > d);

    // atan2, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    atan2(const vec<double, _N>& y, const vec<double, _N>& x);

    vec<double, 1>
    atan2(arg_t<vec<double, 1> > y, arg_t<vec<double, 1> > x);

    vec<double, 2>
    atan2(arg_t<vec<double, 2> > y, arg_t<vec<double, 2> > x);

    vec<double, 4>
    atan2(arg_t<vec<double, 4> > y, arg_t<vec<double, 4> > x);

    vec<double, 4>
    atan2(arg_t<vec<double, 4> > y, arg_t<vec<double, 4> > x);

    vec<double, 8>
    atan2(arg_t<vec<double, 8> > y, arg_t<vec<double, 8> > x);

    // sin, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    sin(const vec<double, _N>& v);

    vec<double, 1>
    sin(arg_t<vec<double, 1> > v);

    vec<double, 2>
    sin(arg_t<vec<double, 2> > d);

    vec<double, 4>
    sin(arg_t<vec<double, 4> > d);

    vec<double, 8>
    sin(arg_t<vec<double, 8> > d);

    // cos, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    cos(const vec<double, _N>& v);

    vec<double, 1>
    cos(arg_t<vec<double, 1> > v);

    vec<double, 2>
    cos(arg_t<vec<double, 2> > d);

    vec<double, 4>
    cos(arg_t<vec<double, 4> > d);

    vec<double, 8>
    cos(arg_t<vec<double, 8> > d);

    // sincos, these functions are exact to +-1 ulp
    template<std::size_t _N>
    void
    sincos(const vec<double, _N>& x,
           vec<double, _N>* s, vec<double, _N>* c);

    void
    sincos(arg_t<vec<double, 1> > x,
           vec<double, 1>* s, vec<double, 1>* c);

    void
    sincos(arg_t<vec<double, 2> > d,
           vec<double, 2> * psin, vec<double, 2> * pcos);

    void
    sincos(arg_t<vec<double, 4> > d,
           vec<double, 4> * psin, vec<double, 4> * pcos);

    void
    sincos(arg_t<vec<double, 8> > d,
           vec<double, 8> * psin, vec<double, 8> * pcos);

    // tan, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    tan(const vec<double, _N>& v);

    vec<double, 1>
    tan(arg_t<vec<double, 1> > v);

    vec<double, 2>
    tan(arg_t<vec<double, 2> > d);

    vec<double, 4>
    tan(arg_t<vec<double, 4> > d);

    vec<double, 8>
    tan(arg_t<vec<double, 8> > d);

    // asinh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    asinh(const vec<double, _N>& x);

    vec<double, 1>
    asinh(arg_t<vec<double, 1> > d);

    vec<double, 2>
    asinh(arg_t<vec<double, 2> > d);

    vec<double, 4>
    asinh(arg_t<vec<double, 4> > d);

    vec<double, 8>
    asinh(arg_t<vec<double, 8> > d);

    // acosh, these functions are exact to +-2 ulp
    template <std::size_t _N>
    vec<double, _N>
    acosh(const vec<double, _N>& x);

    vec<double, 1>
    acosh(arg_t<vec<double, 1> > d);

    vec<double, 2>
    acosh(arg_t<vec<double, 2> > d);

    vec<double, 4>
    acosh(arg_t<vec<double, 4> > d);

    vec<double, 8>
    acosh(arg_t<vec<double, 8> > d);

    // atanh, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    atanh(const vec<double, _N>& x);

    vec<double, 1>
    atanh(arg_t<vec<double, 1> > d);

    vec<double, 2>
    atanh(arg_t<vec<double, 2> > d);

    vec<double, 4>
    atanh(arg_t<vec<double, 4> > d);

    vec<double, 8>
    atanh(arg_t<vec<double, 8> > d);

    // erf, these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    erf(const vec<double, _N>& x);

    vec<double, 1>
    erf(arg_t<vec<double, 1> > d);

    vec<double, 2>
    erf(arg_t<vec<double, 2> > d);

    vec<double, 4>
    erf(arg_t<vec<double, 4> > d);

    vec<double, 8>
    erf(arg_t<vec<double, 8> > d);

#if 0
    // erfc, these functions are exact to XX ulp
    template <std::size_t _N>
    vec<double, _N>
    erfc(const vec<double, _N>& x);

    vec<double, 1>
    erfc(arg_t<vec<double, 1> > d);

    vec<double, 2>
    erfc(arg_t<vec<double, 2> > d);

    vec<double, 4>
    erfc(arg_t<vec<double, 4> > d);

    vec<double, 8>
    erfc(arg_t<vec<double, 8> > d);
#endif

// TODO: --------------------------------------------------------------------
// TODO: test for the functions below

    // specializations vec<double, 2>
    vec<int32_t, 1>
    ilogbp1(arg_t<vec<double, 1> > v);

    vec<int32_t, 2>
    ilogbp1(arg_t<vec<double, 2> > v);

    // specializations vec<double, 4>
    vec<int32_t, 4>
    ilogbp1(arg_t<vec<double, 4> > v);

    // specializations vec<double, 8>
    vec<int32_t, 8>
    ilogbp1(arg_t<vec<double, 8> > v);


    // exp_mx2, calculates $ e^{-x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp_mx2(const vec<double, _N>& x);

    vec<double, 1>
    exp_mx2(arg_t<vec<double, 1> > d);

    vec<double, 2>
    exp_mx2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp_mx2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp_mx2(arg_t<vec<double, 8> > d);

    // exp_px2, calculates $ e^{+x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp_px2(const vec<double, _N>& x);

    vec<double, 1>
    exp_px2(arg_t<vec<double, 1> > d);

    vec<double, 2>
    exp_px2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp_px2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp_px2(arg_t<vec<double, 8> > d);

    // exp2_mx2, calculates $ 2^{-x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp2_mx2(const vec<double, _N>& x);

    vec<double, 1>
    exp2_mx2(arg_t<vec<double, 1> > d);

    vec<double, 2>
    exp2_mx2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp2_mx2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp2_mx2(arg_t<vec<double, 8> > d);

    // exp2_px2, calculates $ 2^{+x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp2_px2(const vec<double, _N>& x);

    vec<double, 1>
    exp2_px2(arg_t<vec<double, 1> > d);

    vec<double, 2>
    exp2_px2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp2_px2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp2_px2(arg_t<vec<double, 8> > d);

    // exp10_mx2, calculates $ 10^{-x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp10_mx2(const vec<double, _N>& x);

    vec<double, 1>
    exp10_mx2(arg_t<vec<double, 1> > d);

    vec<double, 2>
    exp10_mx2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp10_mx2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp10_mx2(arg_t<vec<double, 8> > d);

    // exp10_px2, calculates $ 10^{+x^2} $ these functions are exact to +-1 ulp
    template <std::size_t _N>
    vec<double, _N>
    exp10_px2(const vec<double, _N>& x);

    vec<double, 1>
    exp10_px2(arg_t<vec<double, 1> > d);

    vec<double, 2>
    exp10_px2(arg_t<vec<double, 2> > d);

    vec<double, 4>
    exp10_px2(arg_t<vec<double, 4> > d);

    vec<double, 8>
    exp10_px2(arg_t<vec<double, 8> > d);
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::abs(const vec<double, _N>& v)
{
    const vec<double, _N> msk(not_sign_f64_msk::v.f64());
    return v & msk;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::andnot(const vec<double, _N>& a, const vec<double, _N>& b)
{
    return vec<double, _N>((~a) & b);
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::copysign(const vec<double, _N>& x, const vec<double, _N>& y)
{
    // return abs(x) * sgn(y)
    using v_t = vec<double, _N>;
    const v_t msk(not_sign_f64_msk::v.f64());
    v_t abs_x(x & msk);
    v_t sgn_y(andnot(msk, y));
    return v_t(abs_x | sgn_y);
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::mulsign(const vec<double, _N>& x, const vec<double, _N>& y)
{
    using v_t = vec<double, _N>;
    const v_t msk(sign_f64_msk::v.f64());
    v_t sgn_y = y & msk;
    return v_t(x ^ sgn_y);
}


template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::mad(const vec<double, _N>& a, const vec<double, _N>& b,
           const vec<double, _N>& c)
{
    return a * b + c;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::nmad(const vec<double, _N>& a, const vec<double, _N>& b,
            const vec<double, _N>& c)
{
    return c - a * b;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::sin(const vec<double, _N>& v)
{
    vec<double, _N> r(sin(low_half(v)), sin(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::cos(const vec<double, _N>& v)
{
    vec<double, _N> r(cos(low_half(v)), cos(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
void
cftal::sincos(const vec<double, _N>& v,
              vec<double, _N>* s, vec<double, _N>* c)
{
    if (s != nullptr && c != nullptr) {
        vec<double, _N/2> sl, sh, cl, ch;
        sincos(low_half(v), &sl, &cl);
        sincos(high_half(v), &sh, &ch);
        *s= vec<double, _N>(sl, sh);
        *c= vec<double, _N>(cl, ch);
    } else if (s != nullptr) {
        *s = sin(v);
    } else if (c != nullptr) {
        *c = cos(v);
    }
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::tan(const vec<double, _N>& v)
{
    vec<double, _N> r(tan(low_half(v)), tan(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::asinh(const vec<double, _N>& v)
{
    vec<double, _N> r(asinh(low_half(v)), asinh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::acosh(const vec<double, _N>& v)
{
    vec<double, _N> r(acosh(low_half(v)), acosh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::atanh(const vec<double, _N>& v)
{
    vec<double, _N> r(atanh(low_half(v)), atanh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::erf(const vec<double, _N>& v)
{
    vec<double, _N> r(erf(low_half(v)), erf(high_half(v)));
    return r;
}

#if 0
template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::erfc(const vec<double, _N>& v)
{
    vec<double, _N> r(erfc(low_half(v)), erfc(high_half(v)));
    return r;
}
#endif

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::sqrt(const vec<double, _N>& v)
{
    vec<double, _N> r(sqrt(low_half(v)), sqrt(high_half(v)));
    return r;
}

inline
cftal::vec<double, 1>
cftal::sqrt(const vec<double, 1>& v)
{
    return vec<double, 1>(std::sqrt(v()));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::rsqrt(const vec<double, _N>& v)
{
    vec<double, _N> r(rsqrt(low_half(v)), rsqrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::native_rsqrt(const vec<double, _N>& v)
{
    vec<double, _N> r(1.0/sqrt(v));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::cbrt(const vec<double, _N>& v)
{
    vec<double, _N> r(cbrt(low_half(v)), cbrt(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::root12(const vec<double, _N>& v)
{
    vec<double, _N> r(root12(low_half(v)), root12(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::exp(const vec<double, _N>& v)
{
    vec<double, _N> r(exp(low_half(v)), exp(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::expm1(const vec<double, _N>& v)
{
    vec<double, _N> r(expm1(low_half(v)), expm1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::exp2(const vec<double, _N>& v)
{
    vec<double, _N> r(exp2(low_half(v)), exp2(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::exp2m1(const vec<double, _N>& v)
{
    vec<double, _N> r(exp2m1(low_half(v)), exp2m1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::exp10(const vec<double, _N>& v)
{
    vec<double, _N> r(exp10(low_half(v)), exp10(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::exp10m1(const vec<double, _N>& v)
{
    vec<double, _N> r(exp10m1(low_half(v)), exp10m1(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::log(const vec<double, _N>& v)
{
    vec<double, _N> r(log(low_half(v)), log(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::log1p(const vec<double, _N>& v)
{
    vec<double, _N> r(log1p(low_half(v)), log1p(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::log10(const vec<double, _N>& v)
{
    vec<double, _N> r(log10(low_half(v)), log10(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::log2(const vec<double, _N>& v)
{
    vec<double, _N> r(log2(low_half(v)), log2(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::sinh(const vec<double, _N>& v)
{
    vec<double, _N> r(sinh(low_half(v)), sinh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::cosh(const vec<double, _N>& v)
{
    vec<double, _N> r(cosh(low_half(v)), cosh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::tanh(const vec<double, _N>& v)
{
    vec<double, _N> r(tanh(low_half(v)), tanh(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::pow(const vec<double, _N>& x, const vec<double, _N>& y)
{
    vec<double, _N> r(pow(low_half(x), low_half(y)),
                      pow(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::atan2(const vec<double, _N>& x, const vec<double, _N>& y)
{
    vec<double, _N> r(atan2(low_half(x), low_half(y)),
                      atan2(high_half(x), high_half(y)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::atan(const vec<double, _N>& x)
{
    vec<double, _N> r(atan(low_half(x)), atan(high_half(x)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::asin(const vec<double, _N>& x)
{
    vec<double, _N> r(asin(low_half(x)), asin(high_half(x)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::acos(const vec<double, _N>& x)
{
    vec<double, _N> r(acos(low_half(x)), acos(high_half(x)));
    return r;
}

template <std::size_t _N>
inline
typename cftal::vec<double, _N>::mask_type
cftal::isnan(const vec<double, _N>& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

template <std::size_t _N>
inline
typename cftal::vec<double, _N>::mask_type
cftal::isinf(const vec<double, _N>& x)
{
    vec<double, _N> absx(abs(x));
    const vec<double, _N> vm(exp_f64_msk::v.f64());
    return absx == vm;
}

template <std::size_t _N>
inline
typename cftal::vec<double, _N>::mask_type
cftal::isfinite(const vec<double, _N>& x)
{
    return ~(isinf(x) | isnan(x));
}


template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::fma(const vec<double, _N>& a, const vec<double, _N>& b,
           const vec<double, _N>& c)
{
    return vec<double, _N>(fma(low_half(a), low_half(b), low_half(c)),
                           fma(high_half(a), high_half(b), high_half(c)));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::fms(const vec<double, _N>& a, const vec<double, _N>& b,
           const vec<double, _N>& c)
{
    return vec<double, _N>(fms(low_half(a), low_half(b), low_half(c)),
                           fms(high_half(a), high_half(b), high_half(c)));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::nfma(const vec<double, _N>& a, const vec<double, _N>& b,
            const vec<double, _N>& c)
{
    return vec<double, _N>(nfma(low_half(a), low_half(b), low_half(c)),
                           nfma(high_half(a), high_half(b), high_half(c)));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::nfms(const vec<double, _N>& a, const vec<double, _N>& b,
            const vec<double, _N>& c)
{
    return vec<double, _N>(nfms(low_half(a), low_half(b), low_half(c)),
                           nfms(high_half(a), high_half(b), high_half(c)));
}

inline
cftal::vec<double, 1>
cftal::fma(const vec<double, 1>& a, const vec<double, 1>& b,
           const vec<double, 1>& c)
{
    return vec<double, 1>(::fma(a(), b(), c()));
}

inline
cftal::vec<double, 1>
cftal::fms(const vec<double, 1>& a, const vec<double, 1>& b,
           const vec<double, 1>& c)
{
    return vec<double, 1>(::fma(a(), b(), -c()));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::frexp(const vec<double, _N>& a, vec<int32_t, _N>* e)
{
    vec<int32_t, _N/2> el, eh;
    vec<double, _N> r(frexp(low_half(a), &el),
                      frexp(high_half(a), &eh));
    if (e != nullptr) {
        vec<int32_t, _N> er(el, eh);
        *e = er;
    }
    return r;
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::ldexp(const vec<double, _N>& a, const vec<int32_t, _N>& e)
{
    return vec<double, _N>(ldexp(low_half(a), low_half(e)),
                           ldexp(high_half(a), high_half(e)));
}

template <std::size_t _N>
inline
cftal::vec<int32_t, _N>
cftal::ilogb(const vec<double, _N>& a)
{
    return vec<double, _N>(ilogb(low_half(a)), ilogb(high_half(a)));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::rint(const cftal::vec<double, _N>& v)
{
    return vec<double, _N>(rint(low_half(v)),
                           rint(high_half(v)));
}

inline
cftal::vec<double, 1>
cftal::rint(const vec<double, 1>& v)
{
    return std::rint(v());
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::floor(const cftal::vec<double, _N>& v)
{
    return vec<double, _N>(floor(low_half(v)),
                           floor(high_half(v)));
}

inline
cftal::vec<double, 1>
cftal::floor(const vec<double, 1>& v)
{
    return std::floor(v());
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::ceil(const cftal::vec<double, _N>& v)
{
    return vec<double, _N>(ceil(low_half(v)),
                           ceil(high_half(v)));
}

inline
cftal::vec<double, 1>
cftal::ceil(const vec<double, 1>& v)
{
    return std::ceil(v());
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::trunc(const cftal::vec<double, _N>& v)
{
    return vec<double, _N>(trunc(low_half(v)),
                           trunc(high_half(v)));
}

inline
cftal::vec<double, 1>
cftal::trunc(const vec<double, 1>& v)
{
    return std::trunc(v());
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::exp_mx2(const vec<double, _N>& x)
{
    return vec<double, _N>(exp_mx2(low_half(x)),
                           exp_mx2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::exp_px2(const vec<double, _N>& x)
{
    return vec<double, _N>(exp_px2(low_half(x)),
                           exp_px2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::exp2_mx2(const vec<double, _N>& x)
{
    return vec<double, _N>(exp2_mx2(low_half(x)),
                           exp2_mx2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::exp2_px2(const vec<double, _N>& x)
{
    return vec<double, _N>(exp2_px2(low_half(x)),
                           exp2_px2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::exp10_mx2(const vec<double, _N>& x)
{
    return vec<double, _N>(exp10_mx2(low_half(x)),
                           exp10_mx2(high_half(x)));
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::exp10_px2(const vec<double, _N>& x)
{
    return vec<double, _N>(exp10_px2(low_half(x)),
                           exp10_px2(high_half(x)));
}


// local variables:
// mode: c++
// end:
#endif
