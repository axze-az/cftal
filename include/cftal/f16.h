//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_F16_H__)
#define __CFTAL_F16_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec.h>


namespace cftal {

#if 1
    using f16_t = uint16_t;
    inline
    uint16_t read_bits(f16_t v) {
        return v;
    }
#else
    // a 16 bit floating point number used as storage format
    class f16_t {
    public:
        constexpr f16_t() : _f(0) {}
        constexpr explicit f16_t(uint16_t f) : _f(f) {}
        constexpr uint16_t operator()() const { return _f; }
    private:
        uint16_t _f;
    };

    inline
    uint16_t read_bits(f16_t v) {
        return v();
    }

    template <size_t _N>
    class vec<f16_t, _N> : public vec<uint16_t, _N> {
    public:
        using value_type = f16_t;
        using half_type = vec<f16_t, _N/2>;
        using base_type = vec<uint16_t, _N>;
        using mask_type = typename base_type::mask_type;
        using mask_value_type = typename base_type::mask_value_type;
        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;
        vec(const half_type& lh, const half_type& hh) :
            base_type(lh, hh) {}
        const half_type& lh() const {
            return static_cast<const half_type&>(base_type::lh());
        }
        const half_type& hh() const {
            return static_cast<const half_type&>(base_type::hh());
        }
        vec(f16_t v) : base_type(read_bits(v)) {}
        vec(const base_type& r) : base_type(r) {}
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<f16_t, _N>, _L, _R>& r) : vec(eval(r)) {}
    };

    template <>
    class vec<f16_t, 1> : public vec<uint16_t, 1> {
    public:
        using base_type = vec<uint16_t, 1>;
        using mask_type = typename vec<uint16_t, 1>::mask_type;
        using mask_value_type = typename vec<uint16_t, 1>::mask_value_type;
        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;
        vec(f16_t v) : base_type(read_bits(v)) {}
        f16_t operator()() const { return f16_t(base_type::operator()()); }
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<f16_t, 1>, _L, _R>& r) : vec(eval(r)) {}
    };

    template <size_t _N>
    struct arg< vec<f16_t, _N> > {
        using type = typename arg <vec<uint16_t, _N> >::type;
    };

    template <>
    struct mem< vec<f16_t, 1> > {
        static
        vec<f16_t, 1> load(const f16_t* p, std::size_t n=1) {
            return vec<f16_t, 1>(*p);
        }
        static
        void store(f16_t* p, const vec<f16_t, 1>& v) {
            *p = v();
        }
    };

    template <size_t _N>
    struct mem< vec<f16_t, _N> > {
        static
        vec<f16_t, _N> load(const f16_t* p, std::size_t n=_N) {
            using v_t= vec<uint16_t, _N>;
            v_t r(mem<typename v_t::base_type>::load(
                reinterpret_cast<const uint16_t*>(p), n));
            return r;
        }
        static
        void store(f16_t* p, const vec<f16_t, _N>& v) {
            using v_t = vec<f16_t, _N>;
            mem<typename v_t::base_type>::store(
                reinterpret_cast<uint16_t*>(p), v);
        }
    };

#endif


    // conversion of a f32 to a f16 value
    f16_t
    cvt_f32_to_f16(f32_t f);
    // conversion of a f16 value to a f32 value
    f32_t
    cvt_f16_to_f32(f16_t f);

    // conversion of a f16 vector to a f32 vector
    template <std::size_t _N>
    vec<f16_t, _N>
    cvt_f32_to_f16(const vec<f32_t, _N>& s);

    // conversion of a f16 vector to a f32 vector
    vec<f16_t, 1>
    cvt_f32_to_f16(const vec<f32_t, 1>& s);

    // conversion of a f16 vector to a f32 vector
    vec<f16_t, 2>
    cvt_f32_to_f16(const vec<f32_t, 2>& s);

    // conversion of a f16 vector to a f32 vector
    vec<f16_t, 4>
    cvt_f32_to_f16(const vec<f32_t, 4>& s);

    // conversion of a f16 vector to a f32 vector
    vec<f16_t, 8>
    cvt_f32_to_f16(const vec<f32_t, 8>& s);

    // conversion of a f32 vector to a f16 vector
    template <std::size_t _N>
    vec<f32_t, _N>
    cvt_f16_to_f32(const vec<f16_t, _N>& s);

    // conversion of a f32 vector to a f16 vector
    vec<f32_t, 1>
    cvt_f16_to_f32(const vec<f16_t, 1>& s);

    // conversion of a f32 vector to a f16 vector
    vec<f32_t, 2>
    cvt_f16_to_f32(const vec<f16_t, 2>& s);

    // conversion of a f32 vector to a f16 vector
    vec<f32_t, 4>
    cvt_f16_to_f32(const vec<f16_t, 4>& s);

    // conversion of a f32 vector to a f16 vector
    vec<f32_t, 8>
    cvt_f16_to_f32(const vec<f16_t, 8>& s);


#if 0
    // abs
    template <size_t _N>
    vec<f16_t, _N>
    abs(const vec<f16_t, _N>& a);

    // nan
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isnan(const vec<f16_t, _N>& a);

    // inf
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isinf(const vec<f16_t, _N>& a);

    // operator == for f16_t
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    operator==(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b);

    // operator != for f16_t
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    operator!=(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b);
#endif

    namespace impl {

        f16_t
        _cvt_f32_to_f16(f32_t f);

        f32_t
        _cvt_f16_to_f32(f16_t f);

        template <std::size_t _N>
        vec<f16_t, _N>
        _cvt_f32_to_f16(vec<f32_t, _N> s);

        template <std::size_t _N>
        vec<f32_t, _N>
        _cvt_f16_to_f32(vec<f16_t, _N> s);

    }
}

inline
cftal::f32_t
cftal::impl::_cvt_f16_to_f32(f16_t t)
{
    uint32_t tt= read_bits(t);
    const uint32_t exp_msk = 0x7c00 << 13;
    uint32_t r= (tt & 0x7fff) << 13;
    uint32_t s= (tt & 0x8000) << 16;
    uint32_t e= exp_msk & r;
    r += (127-15) << 23; // adust the exponent
    if (e == exp_msk) {
        // maximum exponent? inf/NaNs
        r += (128-16) << 23;
    } else if (e == 0) {
        // denormal numbers
        const f32_t magic = as<f32_t>(113 << 23);
        r += 1<<23;
        r = as<uint32_t>(as<f32_t>(r) - magic);
    }
    r |= s;
    return as<f32_t>(r);
}

inline
cftal::f16_t
cftal::impl::_cvt_f32_to_f16(f32_t ff)
{
    const f32_t inf= std::numeric_limits<float>::infinity();
    const uint32_t inf_u= as<uint32_t>(inf);
    const uint32_t max_f16_u = (127+16)<<23;
    const f32_t denom_magic= 0.5f;

    const uint32_t sgn_msk = 0x80000000u;

    uint32_t f=as<uint32_t>(ff);
    uint32_t s=(f & sgn_msk);
    f ^= s;
    s >>= 16;
    if (f >= max_f16_u) {
        f = f > inf_u ?
            0x7e00 /*| ((f & 0x7fffff)>>13)*/ : 0x7c00;
    } else {
        if (f < (113<<23)) {
            f = as<uint32_t>(as<f32_t>(f) + denom_magic);
            f = f - as<uint32_t>(denom_magic);
        } else {
            uint32_t mant_odd= (f>>13) & 1;
            f += (uint32_t(15-127)<<23)+ 0xfff;
            f += mant_odd;
            f >>=13;
        }
    }
    return f16_t(f|s);
}

template <std::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::impl::_cvt_f32_to_f16(vec<f32_t, _N> ff)
{
    using f32vec = vec<f32_t, _N>;
    using i32vec = vec<int32_t, _N>;

    const f32vec inf=std::numeric_limits<float>::infinity();
    const i32vec inf_u= as<i32vec>(inf);
    const i32vec max_f16_u= (bias_f32+16) << exp_shift_f32;
    const f32vec denom_magic=0.5f;
    const i32vec denom_magic_u=as<i32vec>(denom_magic);

    i32vec f= as<i32vec>(ff);
    i32vec s= f & i32vec(sign_f32_msk::v.u32());
    f ^= s;
    // the signed shift does not matter because we truncate
    // the 16 higher bits anyway
    s >>= 16;

    // inf or nan handling
    auto inf_or_nan = f >= max_f16_u;
    i32vec r_nan = i32vec(0x7e00) /*| ((f & sig_f32_msk::v.u32()) >> 13)*/;
    i32vec r_inf = i32vec(0x7c00);
    i32vec r_inf_nan = select(f > inf_u, r_nan, r_inf);
    // denormal handling
    auto denom= f < i32vec(113<<23);
    f32vec f_denom = as<f32vec>(f);
    f_denom += denom_magic;
    i32vec r_denom= as<i32vec>(f_denom);
    r_denom -= denom_magic_u;
    // normal numbers
    i32vec mant_odd= (f>>13) & 1;
    const uint32_t offs=(uint32_t(15-bias_f32)<<23) +  0xfff;
    f += i32vec(offs);
    f += mant_odd;
    f >>= 13;
    // produce result
    i32vec r = select(denom, r_denom, f);
    r = select(inf_or_nan, r_inf_nan, r);
    r |= s;

    using u16vec2 = vec<uint16_t, 2*_N>;
    u16vec2 t=as<u16vec2>(r);
    auto rr=even_elements(t);

    return as<vec<f16_t, _N> >(rr);
}

template <std::size_t _N>
inline
cftal::vec<cftal::f32_t, _N>
cftal::impl::_cvt_f16_to_f32(vec<f16_t, _N> ff)
{
    using u32vec = vec<uint32_t, _N>;
    using u16vec = vec<int16_t, _N>;
    using u16vec2 = vec<int16_t, 2 * _N>;
    using f32vec = vec<f32_t, _N>;
    u16vec ffu16=as<u16vec>(ff);
    u16vec z=0;

    u16vec2 cc=combine_even_odd(ffu16, z);
    u32vec tt=as<u32vec>(cc);

    const u32vec exp_msk = 0x7c00 << 13;
    u32vec r= (tt & 0x7fff) << 13;
    u32vec s= (tt & 0x8000) << 16;
    u32vec e= exp_msk & r;
    r += (127-15) << 23; // adust the exponent

    u32vec r_inf_nan= r + ((128-16) << 23);

    const f32vec magic=as<f32_t>(113<<23);
    u32vec r_denom = r + (1<<23);
    f32vec f_denom = as<f32vec>(r_denom);
    f_denom -= magic;
    r_denom = as<u32vec>(f_denom);

    r = select(e== exp_msk, r_inf_nan, r);
    r = select(e== 0, r_denom, r);
    r |= s;
    return as<f32vec>(r);
}

inline
cftal::f32_t
cftal::cvt_f16_to_f32(f16_t t)
{
#if defined (__F16C__)
    return _cvtsh_ss(read_bits(t));
#else
    return impl::_cvt_f16_to_f32(t);
#endif
}

inline
cftal::f16_t
cftal::cvt_f32_to_f16(f32_t ff)
{
#if defined (__F16C__)
    return f16_t(_cvtss_sh(ff, 0));
#else
    return impl::_cvt_f32_to_f16(ff);
#endif
}


template <std::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::cvt_f32_to_f16(const vec<f32_t, _N>& s)
{
    vec<cftal::f16_t, _N/2> rl=cvt_f32_to_f16(low_half(s));
    vec<cftal::f16_t, _N/2> rh=cvt_f32_to_f16(high_half(s));
    return vec<cftal::f16_t, _N>(rl, rh);
}

inline
cftal::vec<cftal::f16_t, 1>
cftal::cvt_f32_to_f16(const vec<f32_t, 1>& s)
{
#if defined (__F16C__)
    vec<f16_t, 1> r=f16_t(_cvtss_sh(s(), 0));
#else
    vec<f16_t, 1> r=impl::_cvt_f32_to_f16(s);
#endif
    return r;
}

inline
cftal::vec<cftal::f16_t, 2>
cftal::cvt_f32_to_f16(const vec<f32_t, 2>& s)
{
#if defined (__F16C__)
    v4f32 t(s, s);
    v4u32 rr=_mm_cvtps_ph(t(), 0);
    vec<f16_t, 2> r=as<vec<f16_t, 2> >(low_half(low_half(rr)));
#else
    vec<f16_t, 2> r=impl::_cvt_f32_to_f16(s);
#endif
    return r;
}

inline
cftal::vec<cftal::f16_t, 4>
cftal::cvt_f32_to_f16(const vec<f32_t, 4>& s)
{
#if defined (__F16C__)
    v4u32 rr=_mm_cvtps_ph(s(), 0);
    vec<f16_t, 4> r=as<vec<f16_t, 4> >(low_half(rr));
#else
    vec<f16_t, 4> r=impl::_cvt_f32_to_f16(s);
#endif
    return r;
}

inline
cftal::vec<cftal::f16_t, 8>
cftal::cvt_f32_to_f16(const vec<f32_t, 8>& s)
{
#if defined (__F16C__)
    v4u32 rr=_mm256_cvtps_ph(s(), 0);
    vec<f16_t, 8> r=as<vec<f16_t, 8> >(rr);
#else
    vec<f16_t, 8> r=impl::_cvt_f32_to_f16(s);
#endif
    return r;
}

template <std::size_t _N>
cftal::vec<cftal::f32_t, _N>
cftal::cvt_f16_to_f32(const vec<f16_t, _N>& s)
{
    vec<f32_t, _N/2> rl= cvt_f16_to_f32(low_half(s));
    vec<f32_t, _N/2> rh= cvt_f16_to_f32(high_half(s));
    return vec<f32_t, _N>(rl, rh);
}

inline
cftal::vec<cftal::f32_t, 1>
cftal::cvt_f16_to_f32(const vec<f16_t, 1>& s)
{
#if defined (__F16C__)
    vec<f32_t, 1> r= _cvtsh_ss(read_bits(s()));
#else
    vec<f32_t, 1> r= impl::_cvt_f16_to_f32(s);
#endif
    return r;
}


inline
cftal::vec<cftal::f32_t, 2>
cftal::cvt_f16_to_f32(const vec<f16_t, 2>& s)
{
#if defined (__F16C__)
    const uint32_t& t=reinterpret_cast<const uint32_t&>(s);
    __m128i s2=_mm_set_epi32(0, 0, 0, t);
    vec<f32_t, 4> rr= _mm_cvtph_ps(s2);
    vec<f32_t, 2> r= low_half(rr);
#else
    vec<f32_t, 2> r= impl::_cvt_f16_to_f32(s);
#endif
    return r;
}

inline
cftal::vec<cftal::f32_t, 4>
cftal::cvt_f16_to_f32(const vec<f16_t, 4>& s)
{
#if defined (__F16C__)
    const uint64_t& t=reinterpret_cast<const uint64_t&>(s);
    __m128i s2= _mm_set_epi64x(0, t);
    vec<f32_t, 4> r= _mm_cvtph_ps(s2);
#else
    vec<f32_t, 4> r= impl::_cvt_f16_to_f32(s);
#endif
    return r;
}

inline
cftal::vec<cftal::f32_t, 8>
cftal::cvt_f16_to_f32(const vec<f16_t, 8>& s)
{
#if defined (__F16C__)
    __m128i s0= s();
    vec<f32_t, 8> r= _mm256_cvtph_ps(s0);
#else
    vec<f32_t, 8> r= impl::_cvt_f16_to_f32(s);
#endif
    return r;
}


// Local variables:
// mode: c++
// end:
#endif
