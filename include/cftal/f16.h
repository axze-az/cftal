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

#if 0
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

        f16_t
        _cvt_f32_to_f16(f32_t f);

        f32_t
        _cvt_f16_to_f32(f16_t f);


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
    uint32_t t=as<uint32_t>(s);
    vec<uint32_t, 4> s2(t);
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
    uint64_t t=as<uint64_t>(s);
    vec<uint64_t, 2> s2(t);
    vec<f32_t, 4> r= _mm_cvtph_ps(s2());
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
