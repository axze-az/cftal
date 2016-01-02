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
    vec<double, _N>
    sin(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    native_sin(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    cos(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    native_cos(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    tan(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    native_tan(const vec<double, _N>& v);


    template <std::size_t _N>
    vec<double, _N>
    native_exp(const vec<double, _N>& v);


    template <std::size_t _N>
    vec<double, _N>
    native_expm1(const vec<double, _N>& v);


    template <std::size_t _N>
    vec<double, _N>
    native_log(const vec<double, _N>& v);


    template <std::size_t _N>
    vec<double, _N>
    atan2(const vec<double, _N>& x, const vec<double, _N>& y);

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
    // a*b -c
    template <std::size_t _N>
    vec<double, _N>
    fms(const vec<double, _N>& a, const vec<double, _N>& b,
        const vec<double, _N>& c);
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
    frexp(const vec<double, 1>& a, vec<int32_t, 1>* e);

    vec<double, 2>
    frexp(arg<vec<double, 2> >::type x, vec<int32_t, 2>* e);

    vec<double, 4>
    frexp(arg<vec<double, 4> >::type x, vec<int32_t, 4>* e);

    vec<double, 8>
    frexp(arg<vec<double, 8> >::type x, vec<int32_t, 8>* e);

    // ldexp
    template <std::size_t _N>
    vec<double, _N>
    ldexp(const vec<double, _N>& a, const vec<int32_t, _N>& e);

    vec<double, 1>
    ldexp(const vec<double, 1>& a, const vec<int32_t, 1>& e);

    vec<double, 2>
    ldexp(arg<vec<double, 2> >::type a, arg<vec<int32_t, 2> >::type e);

    vec<double, 4>
    ldexp(arg<vec<double, 4> >::type a, arg<vec<int32_t, 4> >::type e);

    vec<double, 8>
    ldexp(arg<vec<double, 8> >::type a, arg<vec<int32_t, 8> >::type e);

    // ilogb
    template <std::size_t _N>
    vec<int32_t, _N>
    ilogb(const vec<double, _N>& a);

    vec<int32_t, 1>
    ilogb(const vec<double, 1>& a);

    vec<int32_t, 2>
    ilogb(arg<vec<double, 2> >::type a);

    vec<int32_t, 4>
    ilogb(arg<vec<double, 4> >::type a);

    vec<int32_t, 8>
    ilogb(arg<vec<double, 8> >::type a);

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

    // exp
    template <std::size_t _N>
    vec<double, _N>
    exp(const vec<double, _N>& v);

    vec<double, 1>
    exp(const vec<double, 1>& v);

    vec<double, 2>
    exp(arg<vec<double, 2> >::type d);

    vec<double, 4>
    exp(arg<vec<double, 4> >::type d);

    vec<double, 8>
    exp(arg<vec<double, 8> >::type d);

    // expm1
    template <std::size_t _N>
    vec<double, _N>
    expm1(const vec<double, _N>& v);

    vec<double, 1>
    expm1(const vec<double, 1>& v);

    vec<double, 2>
    expm1(arg<vec<double, 2> >::type d);

    vec<double, 4>
    expm1(arg<vec<double, 4> >::type d);

    vec<double, 8>
    expm1(arg<vec<double, 8> >::type d);

    // sinh
    template <std::size_t _N>
    vec<double, _N>
    sinh(const vec<double, _N>& v);

    vec<double, 1>
    sinh(const vec<double, 1>& d);

    vec<double, 2>
    sinh(arg<vec<double, 2> >::type d);

    vec<double, 4>
    sinh(arg<vec<double, 4> >::type d);

    vec<double, 8>
    sinh(arg<vec<double, 8> >::type d);
    
    // cosh
    template <std::size_t _N>
    vec<double, _N>
    cosh(const vec<double, _N>& v);

    vec<double, 1>
    cosh(const vec<double, 1>& d);

    vec<double, 2>
    cosh(arg<vec<double, 2> >::type d);

    vec<double, 4>
    cosh(arg<vec<double, 4> >::type d);

    vec<double, 8>
    cosh(arg<vec<double, 8> >::type d);

    // log
    template <std::size_t _N>
    vec<double, _N>
    log(const vec<double, _N>& v);

    vec<double, 1>
    log(const vec<double, 1>& v);

    vec<double, 2>
    log(arg<vec<double, 2> >::type d);

    vec<double, 4>
    log(arg<vec<double, 4> >::type d);

    vec<double, 8>
    log(arg<vec<double, 8> >::type d);

    // pow and specializations
    template <std::size_t _N>
    vec<double, _N>
    pow(const vec<double, _N>& x, const vec<double, _N>& y);

    vec<double, 1>
    pow(const vec<double, 1>& x, const vec<double, 1>& y);

    vec<double, 2>
    pow(arg<vec<double, 2> >::type b, arg<vec<double, 2> >::type e);

    vec<double, 4>
    pow(arg<vec<double, 4> >::type b, arg<vec<double, 4> >::type e);

    vec<double, 8>
    pow(arg<vec<double, 8> >::type b, arg<vec<double, 8> >::type e);

// TODO: --------------------------------------------------------------------
// TODO: test for the functions below
    // specializations vec<double, 2>
    vec<double, 2>
    cbrt(arg<vec<double, 2> >::type v);

    vec<int32_t, 2>
    ilogbp1(arg<vec<double, 2> >::type v);
    vec<double, 2>
    atan2(arg<vec<double, 2> >::type y, arg<vec<double, 2> >::type x);
    vec<double, 2>
    asin(arg<vec<double, 2> >::type d);
    vec<double, 2>
    acos(arg<vec<double, 2> >::type d);

    vec<double, 2>
    atan(arg<vec<double, 2> >::type d);
    std::pair<vec<double, 2> , vec<double, 2> >
    sincos(arg<vec<double, 2> >::type d);

    void
    sincos(arg<vec<double, 2> >::type d, vec<double, 2> * psin, vec<double, 2> * pcos);
    vec<double, 2>
    sin(arg<vec<double, 2> >::type d);
    vec<double, 2>
    cos(arg<vec<double, 2> >::type d);
    vec<double, 2>
    tan(arg<vec<double, 2> >::type d);
    vec<double, 2>
    cot(arg<vec<double, 2> >::type d);
    vec<double, 2>
    atan2(arg<vec<double, 2> >::type x, arg<vec<double, 2> >::type y);

    void
    native_sincos(arg<vec<double, 2> >::type d,
                  vec<double, 2> * psin, vec<double, 2> * pcos);
    vec<double, 2>
    native_exp(arg<vec<double, 2> >::type d);
    vec<double, 2>
    native_log(arg<vec<double, 2> >::type d);
    vec<double, 2>
    native_sin(arg<vec<double, 2> >::type d);
    vec<double, 2>
    native_cos(arg<vec<double, 2> >::type d);
    vec<double, 2>
    native_tan(arg<vec<double, 2> >::type d);
    vec<double, 2>
    native_cot(arg<vec<double, 2> >::type d);


    // specializations vec<double, 4>
    vec<double, 4>
    cbrt(arg<vec<double, 4> >::type v);
    vec<int32_t, 4>
    ilogbp1(arg<vec<double, 4> >::type v);
    vec<double, 4>
    atan2(arg<vec<double, 4> >::type y, arg<vec<double, 4> >::type x);
    vec<double, 4>
    asin(arg<vec<double, 4> >::type d);
    vec<double, 4>
    acos(arg<vec<double, 4> >::type d);

    vec<double, 4>
    atan(arg<vec<double, 4> >::type d);
    std::pair<vec<double, 4> , vec<double, 4> >
    sincos(arg<vec<double, 4> >::type d);

    void
    sincos(arg<vec<double, 4> >::type d, vec<double, 4> * psin, vec<double, 4> * pcos);
    vec<double, 4>
    sin(arg<vec<double, 4> >::type d);
    vec<double, 4>
    cos(arg<vec<double, 4> >::type d);
    vec<double, 4>
    tan(arg<vec<double, 4> >::type d);
    vec<double, 4>
    cot(arg<vec<double, 4> >::type d);
    vec<double, 4>
    atan2(arg<vec<double, 4> >::type x, arg<vec<double, 4> >::type y);

    void
    native_sincos(arg<vec<double, 4> >::type d,
                  vec<double, 4> * psin, vec<double, 4> * pcos);
    vec<double, 4>
    native_exp(arg<vec<double, 4> >::type d);
    vec<double, 4>
    native_log(arg<vec<double, 4> >::type d);
    vec<double, 4>
    native_sin(arg<vec<double, 4> >::type d);
    vec<double, 4>
    native_cos(arg<vec<double, 4> >::type d);
    vec<double, 4>
    native_tan(arg<vec<double, 4> >::type d);
    vec<double, 4>
    native_cot(arg<vec<double, 4> >::type d);

    // specializations vec<double, 8>
    vec<double, 8>
    cbrt(arg<vec<double, 8> >::type v);
    vec<int32_t, 8>
    ilogbp1(arg<vec<double, 8> >::type v);
    vec<double, 8>
    atan2(arg<vec<double, 8> >::type y, arg<vec<double, 8> >::type x);
    vec<double, 8>
    asin(arg<vec<double, 8> >::type d);
    vec<double, 8>
    acos(arg<vec<double, 8> >::type d);

    vec<double, 8>
    atan(arg<vec<double, 8> >::type d);
    std::pair<vec<double, 8> , vec<double, 8> >
    sincos(arg<vec<double, 8> >::type d);

    void
    sincos(arg<vec<double, 8> >::type d, vec<double, 8> * psin, vec<double, 8> * pcos);
    vec<double, 8>
    sin(arg<vec<double, 8> >::type d);
    vec<double, 8>
    cos(arg<vec<double, 8> >::type d);
    vec<double, 8>
    tan(arg<vec<double, 8> >::type d);
    vec<double, 8>
    cot(arg<vec<double, 8> >::type d);
    vec<double, 8>
    atan2(arg<vec<double, 8> >::type x, arg<vec<double, 8> >::type y);

    void
    native_sincos(arg<vec<double, 8> >::type d,
                  vec<double, 8> * psin, vec<double, 8> * pcos);
    vec<double, 8>
    native_exp(arg<vec<double, 8> >::type d);
    vec<double, 8>
    native_log(arg<vec<double, 8> >::type d);
    vec<double, 8>
    native_sin(arg<vec<double, 8> >::type d);
    vec<double, 8>
    native_cos(arg<vec<double, 8> >::type d);
    vec<double, 8>
    native_tan(arg<vec<double, 8> >::type d);
    vec<double, 8>
    native_cot(arg<vec<double, 8> >::type d);

    vec<double, 1>
    fma(arg<vec<double, 1> >::type a,
        arg<vec<double, 1> >::type b,
        arg<vec<double, 1> >::type c);

    vec<double, 1>
    fms(arg<vec<double, 1> >::type a,
        arg<vec<double, 1> >::type b,
        arg<vec<double, 1> >::type c);
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::abs(const vec<double, _N>& v)
{
    const vec<double, _N> msk(not_sign_f64_msk::v._f64);
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
    const v_t msk(not_sign_f64_msk::v._f64);
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
    const v_t msk(sign_f64_msk::v._f64);
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
cftal::native_sin(const vec<double, _N>& v)
{
    vec<double, _N> r(native_sin(low_half(v)), native_sin(high_half(v)));
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
cftal::vec<double, _N>
cftal::native_cos(const vec<double, _N>& v)
{
    vec<double, _N> r(native_cos(low_half(v)), native_cos(high_half(v)));
    return r;
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
cftal::native_tan(const vec<double, _N>& v)
{
    vec<double, _N> r(native_tan(low_half(v)), native_tan(high_half(v)));
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

inline
cftal::vec<double, 1>
cftal::exp(const vec<double, 1>& v)
{
    return vec<double, 1>(std::exp(v()));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::native_exp(const vec<double, _N>& v)
{
    vec<double, _N> r(native_exp(low_half(v)), native_exp(high_half(v)));
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

inline
cftal::vec<double, 1>
cftal::expm1(const vec<double, 1>& v)
{
    return vec<double, 1> (std::expm1(v()));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::native_expm1(const vec<double, _N>& v)
{
    vec<double, _N> r(native_expm1(low_half(v)), native_expm1(high_half(v)));
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

inline
cftal::vec<double, 1>
cftal::log(const vec<double, 1>& v)
{
    return vec<double, 1> (std::log(v()));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::native_log(const vec<double, _N>& v)
{
    vec<double, _N> r(native_log(low_half(v)), native_log(high_half(v)));
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

inline
cftal::vec<double, 1>
cftal::sinh(const vec<double, 1>& v)
{
    return vec<double, 1>(std::sinh(v()));
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::cosh(const vec<double, _N>& v)
{
    vec<double, _N> r(cosh(low_half(v)), cosh(high_half(v)));
    return r;
}

inline
cftal::vec<double, 1>
cftal::cosh(const vec<double, 1>& v)
{
    return vec<double, 1>(std::cosh(v()));
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

inline
cftal::vec<double, 1>
cftal::pow(const vec<double, 1>& x, const vec<double, 1>& y)
{
    return vec<double, 1>(std::pow(x(), y()));
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
    const vec<double, _N> vm(exp_f64_msk::v._f64);
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

inline
cftal::vec<double, 1>
cftal::frexp(const vec<double, 1>& a, vec<int32_t, 1>* e)
{
    int32_t es;
    double r= std::frexp(a(), &es);
    if (e != nullptr) {
        *e= vec<int32_t, 1>(es);
    }
    return vec<double, 1>(r);
}

template <std::size_t _N>
inline
cftal::vec<double, _N>
cftal::ldexp(const vec<double, _N>& a, const vec<int32_t, _N>& e)
{
    return vec<double, _N>(ldexp(low_half(a), low_half(e)),
                           ldexp(high_half(a), high_half(e)));
}

inline
cftal::vec<double, 1>
cftal::ldexp(const vec<double, 1>& a, const vec<int32_t, 1>& e)
{
    return vec<double, 1>(std::ldexp(a(), e()));
}

template <std::size_t _N>
inline
cftal::vec<int32_t, _N>
cftal::ilogb(const vec<double, _N>& a)
{
    return vec<double, _N>(ilogb(low_half(a)), ilogb(high_half(a)));
}

inline
cftal::vec<int32_t, 1>
cftal::ilogb(const vec<double, 1>& a)
{
    return vec<int32_t, 1>(std::ilogb(a()));
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

// local variables:
// mode: c++
// end:
#endif
