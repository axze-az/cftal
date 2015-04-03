#if !defined (__CFTAL_VEC_DOUBLE_N_H__)
#define __CFTAL_VEC_DOUBLE_N_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_1.h>
#include <cftal/d_real.h>
#include <cmath>

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

    template <std::size_t _N>
    vec<double, _N>
    rint(const vec<double, _N>& v);

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
    exp(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    native_exp(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    expm1(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    native_expm1(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    log(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    native_log(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    sinh(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    cosh(const vec<double, _N>& v);

    template <std::size_t _N>
    vec<double, _N>
    pow(const vec<double, _N>& x, const vec<double, _N>& y);

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


    namespace impl {
        // TODO: fma implementations
    }

    // specializations
    vec<double, 2> cbrt(arg<vec<double, 2> >::type v);
    vec<double, 2> frexp(arg<vec<double, 2> >::type v,
                         vec<int32_t, 4>* pi);
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
cftal::rint(const cftal::vec<double, _N>& v)
{
    return vec<double, _N>(rint(low_half(v)),
                           rint(high_half(v)));
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


// local variables:
// mode: c++
// end:
#endif
