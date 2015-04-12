#if !defined (__CFTAL_VEC_BIT_N_H__)
#define __CFTAL_VEC_BIT_N_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>
#include <type_traits>

namespace cftal {

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
    
    template <std::size_t _N>
    class vec<bit, _N> {      
        using utype = typename
            std::conditional<(_N>32), uint64_t,
            typename std::conditional<(_N>16), uint32_t,
            typename std::conditional<(_N>8), uint16_t,
            uint8_t>::type >::type >::type;
        utype _v;
    public:
        static constexpr const utype mask = _N-1; 
        vec() = default;
        vec(const vec&) = default;
        vec(vec&&) = default;
        vec& operator=(const vec&) = default;
        vec& operator=(vec&&) = default;

        template <typename _U>
        vec(const vec<_U, _N/2>& l, const vec<_U, _N/2>& h,
            typename std::enable_if<(_N>1), _U>::type* = nullptr) 
            : _v( (utype(l()) & ((_N/2)-1)) &
                  ((utype(h()) & ((_N/2)-1)) << _N/2)) {}
        template <typename _U>
        vec(const vec<_U, _N>& v) : _v(v()) {}
        vec(utype v) : _v( v & mask) {}
        utype operator()() const { return _v; }
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

// Local variables:
// mode: c++
// end:
#endif
