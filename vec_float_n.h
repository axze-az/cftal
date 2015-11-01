#if !defined (__CFTAL_VEC_FLOAT_N_H__)
#define __CFTAL_VEC_FLOAT_N_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_1.h>
#include <cftal/d_real.h>
#include <cmath>
#if defined (__SSE__)
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

    template <std::size_t _N>
    vec<float, _N>
    rint(const vec<float, _N>& v);

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
    sin(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    native_sin(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    cos(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    native_cos(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    tan(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    native_tan(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    exp(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    native_exp(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    expm1(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    native_expm1(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    log(const vec<float, _N>& v);

    template <std::size_t _N>
    vec<float, _N>
    native_log(const vec<float, _N>& v);

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

    namespace impl {
        // TODO: fma implementations
    }

    v4f32 cbrt(arg<v4f32>::type a);
    v4f32 frexp(arg<v4f32>::type x, v4s32* e);
    // v4f32 pow2i(arg<v4s32>::type e);
    v4f32 ldexp(arg<v4f32>::type d, arg<v4s32>::type e);
    v4s32 ilogbp1(arg<v4f32>::type v);
    v4s32 ilogb(arg<v4f32>::type v);
    v4f32 atan2(arg<v4f32>::type y, arg<v4f32>::type x);
    v4f32 asin(arg<v4f32>::type d);
    v4f32 acos(arg<v4f32>::type d);

    v4f32 atan(arg<v4f32>::type d);
    std::pair<v4f32, v4f32> sincos(arg<v4f32>::type d);

    v4f32 exp(arg<v4f32>::type d);
    v4f32 expm1(arg<v4f32>::type d);
    v4f32 log(arg<v4f32>::type d);
    v4f32 pow(arg<v4f32>::type b, arg<v4f32>::type e);
    void sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
    v4f32 sin(arg<v4f32>::type d);
    v4f32 cos(arg<v4f32>::type d);
    v4f32 tan(arg<v4f32>::type d);
    v4f32 cot(arg<v4f32>::type d);
    v4f32 atan2(arg<v4f32>::type x, arg<v4f32>::type y);

    void native_sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
    v4f32 native_exp(arg<v4f32>::type d);
    v4f32 native_log(arg<v4f32>::type d);
    v4f32 native_sin(arg<v4f32>::type d);
    v4f32 native_cos(arg<v4f32>::type d);
    v4f32 native_tan(arg<v4f32>::type d);
    v4f32 native_cot(arg<v4f32>::type d);
    v4f32 cosh(arg<v4f32>::type d);
    v4f32 sinh(arg<v4f32>::type d);

    v4f32 pow(arg<v4f32>::type x, arg<v4f32>::type y);

    v8f32 cbrt(arg<v8f32>::type a);
    v8f32 frexp(arg<v8f32>::type x, v8s32* e);
    // v8f32 pow2i(arg<v4s32>::type e);
    v8f32 ldexp(arg<v8f32>::type d, arg<v8s32>::type e);
    v8s32 ilogbp1(arg<v8f32>::type v);
    v8s32 ilogb(arg<v8f32>::type v);
    v8f32 atan2(arg<v8f32>::type y, arg<v8f32>::type x);
    v8f32 asin(arg<v8f32>::type d);
    v8f32 acos(arg<v8f32>::type d);

    v8f32 atan(arg<v8f32>::type d);
    std::pair<v8f32, v8f32> sincos(arg<v8f32>::type d);

    v8f32 exp(arg<v8f32>::type d);
    v8f32 expm1(arg<v8f32>::type d);
    v8f32 log(arg<v8f32>::type d);
    v8f32 pow(arg<v8f32>::type b, arg<v8f32>::type e);
    void sincos(arg<v8f32>::type d, v8f32* psin, v8f32* pcos);
    v8f32 sin(arg<v8f32>::type d);
    v8f32 cos(arg<v8f32>::type d);
    v8f32 tan(arg<v8f32>::type d);
    v8f32 cot(arg<v8f32>::type d);
    v8f32 atan2(arg<v8f32>::type x, arg<v8f32>::type y);

    void native_sincos(arg<v8f32>::type d, v8f32* psin, v8f32* pcos);
    v8f32 native_exp(arg<v8f32>::type d);
    v8f32 native_log(arg<v8f32>::type d);
    v8f32 native_sin(arg<v8f32>::type d);
    v8f32 native_cos(arg<v8f32>::type d);
    v8f32 native_tan(arg<v8f32>::type d);
    v8f32 native_cot(arg<v8f32>::type d);
    v8f32 cosh(arg<v8f32>::type d);
    v8f32 sinh(arg<v8f32>::type d);

    v8f32 pow(arg<v8f32>::type x, arg<v8f32>::type y);
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::abs(const vec<float, _N>& v)
{
    const vec<float, _N> msk(not_sign_f32_msk::v._f32);
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
    const v_t msk(not_sign_f32_msk::v._f32);
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
    const v_t msk(sign_f32_msk::v._f32);
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
cftal::sin(const vec<float, _N>& v)
{
    vec<float, _N> r(sin(low_half(v)), sin(high_half(v)));
    return r;
}

template <std::size_t _N>
inline
cftal::vec<float, _N>
cftal::native_sin(const vec<float, _N>& v)
{
    vec<float, _N> r(native_sin(low_half(v)), native_sin(high_half(v)));
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
cftal::native_cos(const vec<float, _N>& v)
{
    vec<float, _N> r(native_cos(low_half(v)), native_cos(high_half(v)));
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
cftal::native_tan(const vec<float, _N>& v)
{
    vec<float, _N> r(native_tan(low_half(v)), native_tan(high_half(v)));
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
cftal::native_exp(const vec<float, _N>& v)
{
    vec<float, _N> r(native_exp(low_half(v)), native_exp(high_half(v)));
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
cftal::native_expm1(const vec<float, _N>& v)
{
    vec<float, _N> r(native_expm1(low_half(v)), native_expm1(high_half(v)));
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
cftal::native_log(const vec<float, _N>& v)
{
    vec<float, _N> r(native_log(low_half(v)), native_log(high_half(v)));
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
cftal::cosh(const vec<float, _N>& v)
{
    vec<float, _N> r(cosh(low_half(v)), cosh(high_half(v)));
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
    const vec<float, _N> vm(exp_f32_msk::v._f32);
    return absx == vm;
}

template <std::size_t _N>
inline
typename cftal::vec<float, _N>::mask_type
cftal::isfinite(const vec<float, _N>& x)
{
    return ~(isinf(x) | isnan(x));
}

// local variables:
// mode: c++
// end:
#endif
