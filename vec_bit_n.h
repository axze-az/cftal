#if !defined (__CFTAL_VEC_BIT_N_H__)
#define __CFTAL_VEC_BIT_N_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <type_traits>

namespace cftal {

    // a bit
    class bit {
    public:
        enum _b {
            _0 = 0,
            _1 = 1
        };
        bit() = default;
        bit(const bit&) = default;
        bit(bit&&) = default;
        bit& operator=(const bit&) = default;
        bit& operator=(bit&&) = default;
        bit(bool b) : _v(b ? _1 : _0) {}
        bit(uint32_t v) : _v (v ? _1: _0) {}
        uint32_t operator()() const { return uint32_t(_v); }
    private:
        _b _v;
    };

    // specialization of vec for bit masks
    template <std::size_t _N>
    class vec<bit, _N> {      
    public:
        using utype = typename
            std::conditional<(_N>32), uint64_t,
            typename std::conditional<(_N>16), uint32_t,
            typename std::conditional<(_N>8), uint16_t,
            uint8_t>::type >::type >::type;
        static constexpr const utype mask =
            (utype(vec<bit, _N/2>::mask) << _N/2) |
            utype(vec<bit, _N/2>::mask);
            // utype((uint64_t(1) << _N)-1);
        vec() = default;
        vec(const vec&) = default;
        vec(vec&&) = default;
        vec& operator=(const vec&) = default;
        vec& operator=(vec&&) = default;

        constexpr vec(const vec<bit, _N/2>& l, const vec<bit, _N/2>& h)
            : _v((utype(l())) |
                 ((utype(h()) << (_N/2)))) {}
        constexpr vec(utype v) : _v( v & mask) {}
        utype operator()() const { return _v; }
    private:
        utype _v;
    };

    // full specialization for length 1 required because vec<_T, 1>
    // and vec<bit, _N> are equal qualified for instantiation of
    // vec<bit, 1>
    template <>
    class vec<bit, 1> {
    public:
        using utype = uint8_t;
        static constexpr const utype mask = 1;
        vec() = default;
        vec(const vec&) = default;
        vec(vec&&) = default;
        vec& operator=(const vec&) = default;
        vec& operator=(vec&&) = default;
        constexpr vec(utype v) : _v( v & mask) {}
        utype operator()() const { return _v; }
    private:
        utype _v;
    };

    template <std::size_t _N>
    typename std::enable_if<(_N>1), vec<bit, _N/2> >::type
    low_half(const vec<bit, _N>& v);

    template <std::size_t _N>
    typename std::enable_if<(_N>1), vec<bit, _N/2> >::type
    high_half(const vec<bit, _N>& v);
    
    template <std::size_t _N>
    vec<bit, _N>
    operator==(const vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    vec<bit, _N>
    operator!=(const vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    vec<bit, _N>
    operator~(const vec<bit, _N>& a);
    
    template <std::size_t _N>
    vec<bit, _N>
    operator^(const vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    vec<bit, _N>&
    operator^=(vec<bit, _N>& a, const vec<bit, _N>& b);
    
    template <std::size_t _N>
    vec<bit, _N>
    operator|(const vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    vec<bit, _N>&
    operator|=(vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    vec<bit, _N>
    operator&(const vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    vec<bit, _N>&
    operator&=(vec<bit, _N>& a, const vec<bit, _N>& b);

    template <std::size_t _N>
    bool
    all_of(const vec<bit, _N>& a);

    template <std::size_t _N>
    bool
    any_of(const vec<bit, _N>& a);

    template <std::size_t _N>
    bool
    none_of(const vec<bit, _N>& a);
    
}

template <std::size_t _N>
inline
typename std::enable_if<(_N>1), cftal::vec<cftal::bit, _N/2> >::type
cftal::low_half(const vec<bit, _N>& v)
{
    return vec<bit, _N/2>(v());
}

template <std::size_t _N>
inline
typename std::enable_if<(_N>1), cftal::vec<cftal::bit, _N/2> >::type
cftal::high_half(const vec<bit, _N>& v)
{
    return vec<bit, _N/2>(v() >> (_N/2));
}
    
template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::operator==(const vec<bit, _N>& a, const vec<bit, _N>& b)
{
    // 1 0 --> 0
    // 0 1 --> 0
    // 1 1 --> 1
    // 0 0 --> 1
    // a&b | ~a & ~b == ~(a^b)
    return ~(a() ^ b());
}

template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::operator!=(const vec<bit, _N>& a, const vec<bit, _N>& b)
{
    return a() ^ b();
}

template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::operator~(const vec<bit, _N>& a)
{
    return ~a();
}
    
template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::operator^(const vec<bit, _N>& a, const vec<bit, _N>& b)
{
    return a() ^ b();
}

template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>&
cftal::operator^=(vec<bit, _N>& a, const vec<bit, _N>& b)
{
    a= a^b;
    return a;
}
    
template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::operator|(const vec<bit, _N>& a, const vec<bit, _N>& b)
{
    return a() | b();
}

template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>&
cftal::operator|=(vec<bit, _N>& a, const vec<bit, _N>& b)
{
    a = a|b;
    return a;
}

template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::operator&(const vec<bit, _N>& a, const vec<bit, _N>& b)
{
    return a() & b();
}

template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>&
cftal::operator&=(vec<bit, _N>& a, const vec<bit, _N>& b)
{
    a = a & b;
    return a;
}

template <std::size_t _N>
inline
bool
cftal::all_of(const vec<bit, _N>& a)
{
    return a() == vec<bit, _N>::mask;
}

template <std::size_t _N>
inline
bool
cftal::any_of(const vec<bit, _N>& a)
{
    return a() != 0;
}

template <std::size_t _N>
inline
bool
cftal::none_of(const vec<bit, _N>& a)
{
    return a() == 0;
}


// Local variables:
// mode: c++
// end:
#endif
