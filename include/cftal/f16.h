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
        constexpr uint16_t v() const { return _f; }
    private:
        uint16_t _f;
    };

    inline
    uint16_t read_bits(f16_t v) {
        return v.v();
    }

#if defined (__SSE2__)
    template <>
    class vec<f16_t, 8> : public vec<uint16_t, 8> {
    public:
        using base_type = vec<uint16_t, 8>;
        using mask_type = vec<uint16_t, 8>::mask_type;
        using mask_value_type = vec<uint16_t, 8>::mask_value_type;
        vec() = default;
        vec(const base_type& b) : base_type(b) {}
        vec(f16_t v) : base_type(read_bits(v)) {}
    };
    template <>
    struct arg< vec<f16_t, 8> > {
        using type = vec<f16_t, 8>;
    };

    template <>
    struct mem< vec<f16_t, 8> > {
        static
        vec<f16_t, 8> load(const f16_t* p, std::size_t n=8) {
            using v_t= vec<f16_t, 8>;
            v_t r(mem<v_t::base_type>::load(
                reinterpret_cast<const uint16_t*>(p), n));
            return r;
        }
        static
        void store(f16_t* p, const vec<int16_t, 8>& v) {
            using v_t = vec<f16_t, 8>;
            mem<v_t::base_type>::store(
                reinterpret_cast<uint16_t*>(p), v);
        }
    };
#endif

#endif

    // conversion of a f32 to a f16 value
    f16_t
    cvt_f32_to_f16(f32_t f);
    // conversion of a f16 value to a f16 value
    f32_t
    cvt_f16_to_f32(f16_t f);

    template <std::size_t _N>
    vec<f16_t, _N>
    cvt_f32_to_f16(const vec<f32_t, _N>& s);

    vec<f16_t, 1>
    cvt_f32_to_f16(const vec<f32_t, 1>& s);

    vec<f16_t, 2>
    cvt_f32_to_f16(const vec<f32_t, 2>& s);

    vec<f16_t, 4>
    cvt_f32_to_f16(const vec<f32_t, 4>& s);

    vec<f16_t, 8>
    cvt_f32_to_f16(const vec<f32_t, 8>& s);


    template <std::size_t _N>
    vec<f32_t, _N>
    cvt_f16_to_f32(const vec<f16_t, _N>& s);

    vec<f32_t, 1>
    cvt_f16_to_f32(const vec<f16_t, 1>& s);

    vec<f32_t, 2>
    cvt_f16_to_f32(const vec<f16_t, 2>& s);

    vec<f32_t, 4>
    cvt_f16_to_f32(const vec<f16_t, 4>& s);

    vec<f32_t, 8>
    cvt_f16_to_f32(const vec<f16_t, 8>& s);

    namespace impl {

        f16_t
        _cvt_f32_to_f16(f32_t f);

        f32_t
        _cvt_f16_to_f32(f16_t f);

        vec<f16_t, 1>
        _cvt_f32_to_f16(vec<f32_t, 1> s);

        vec<f16_t, 2>
        _cvt_f32_to_f16(vec<f32_t, 2> s);

        vec<f16_t, 4>
        _cvt_f32_to_f16(vec<f32_t, 4> s);

        vec<f16_t, 8>
        _cvt_f32_to_f16(vec<f32_t, 8> s);

        vec<f32_t, 1>
        _cvt_f16_to_f32(vec<f16_t, 1> s);

        vec<f32_t, 2>
        _cvt_f16_to_f32(vec<f16_t, 2> s);

        vec<f32_t, 4>
        _cvt_f16_to_f32(vec<f16_t, 4> s);

        vec<f32_t, 8>
        _cvt_f16_to_f32(vec<f16_t, 8> s);

    }
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
    const vec<uint16_t, 2> z0=0;
    vec<uint16_t, 2> s0=as<vec<uint16_t, 2> >(s);
    vec<uint16_t, 4> s1(s0, z0);
    const vec<uint16_t, 4> z1=0;
    v8u16 s2(s1, z1);
    vec<f32_t, 4> rr= _mm_cvtph_ps(s2());
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
    vec<uint16_t, 4> s0=as<vec<uint16_t, 4> >(s);
    const vec<uint16_t, 4> z0=0;
    v8u16 s1(s0, z0);
    vec<f32_t, 4> r= _mm_cvtph_ps(s1());
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
    v8u16 s0=as<v8u16>(s);
    vec<f32_t, 8> r= _mm256_cvtph_ps(s0());
#else
    vec<f32_t, 8> r= impl::_cvt_f16_to_f32(s);
#endif
    return r;
}


// Local variables:
// mode: c++
// end:
#endif
