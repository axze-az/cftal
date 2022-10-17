//
// Copyright (C) 2010-2022 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_VEC_BIT_N_H__)
#define __CFTAL_VEC_BIT_N_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/type_traits.h>
#include <iostream>

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
        bit(_b b) : _v(b != _0 ? _1 : _0) {}
        bit(bool b) : _v(b ? _1 : _0) {}
        // bit(uint32_t v) : _v (v ? _1: _0) {}
        constexpr uint32_t operator()() const { return uint32_t(_v); }
    private:
        _b _v;
    };

    std::ostream& operator<<(std::ostream& s, const bit& b);

    // specialization of vec for bit masks
    template <std::size_t _N>
    class vec<bit, _N> {
    public:
        static_assert(_N > 0 && _N <= 64, "_N must be element of [1, 64]]");
        using utype = typename
            std::conditional<(_N>32), uint64_t,
            typename std::conditional<(_N>16), uint32_t,
            typename std::conditional<(_N>8), uint16_t,
            uint8_t>::type >::type >::type;
        static constexpr const utype mask =
            (utype(vec<bit, _N/2>::mask) << _N/2) |
            utype(vec<bit, _N/2>::mask);
            // utype((uint64_t(1) << _N)-1);
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type = vec<mask_value_type, _N>;
        vec() = default;
        vec(const vec&) = default;
        vec(vec&&) = default;
        vec& operator=(const vec&) = default;
        vec& operator=(vec&&) = default;

        constexpr vec(const bit& v) : _v( v()!=0 ? mask : 0) {}
        constexpr vec(const vec<bit, _N/2>& l, const vec<bit, _N/2>& h)
            : _v((utype(l())) |
                 ((utype(h()) << (_N/2)))) {}
        constexpr vec(utype v) : _v( v & mask) {}
        utype operator()() const { return _v; }
    private:
        utype _v;
    };

    template <>
    struct is_vec_specialized<vec<bit, 64> > : public std::true_type {};
    template <>
    struct is_vec_specialized<vec<bit, 32> > : public std::true_type {};
    template <>
    struct is_vec_specialized<vec<bit, 16> > : public std::true_type {};
    template <>
    struct is_vec_specialized<vec<bit, 8> > : public std::true_type {};

    // full specialization for length 1 required because vec<_T, 1>
    // and vec<bit, _N> are equal qualified for instantiation of
    // vec<bit, 1>
    template <>
    class vec<bit, 1> {
    public:
        using utype = uint8_t;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type = vec<mask_value_type, 1>;
        static constexpr const utype mask = 1;

        vec() = default;
        vec(const vec&) = default;
        vec(vec&&) = default;
        vec& operator=(const vec&) = default;
        vec& operator=(vec&&) = default;
        constexpr vec(const bit& v) : _v( v()!=0 ? 1 : 0) {}
        constexpr vec(utype v) : _v( v & mask) {}
        utype operator()() const { return _v; }
    private:
        utype _v;
    };

    template <>
    struct is_vec_specialized<vec<bit, 1> > : public std::true_type {};

    template <>
    struct mem< vec<bit, 1> > {
        static
        vec<bit, 1> load(const bit* p, std::size_t n=1) {
            uint32_t ui=(*p)();
            return vec<bit, 1>(ui& 1);
        }
        static
        void store(bit* p, const vec<bit, 1>& v) {
            if (v())
                *p = bit::_1;
            else
                *p = bit::_0;
        }
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

    bool
    all_of(const vec<bit, 1>& a);

    bool
    any_of(const vec<bit, 1>& a);

    bool
    none_of(const vec<bit, 1>& a);

    template <std::size_t _N>
    vec<bit, _N>
    select(const vec<bit, _N>&  m,
           const vec<bit, _N>& on_true, const vec<bit, _N> on_false);

    std::ostream& operator<<(std::ostream& s, const vec<bit, 1>& v);
}

inline
std::ostream&
cftal::operator<<(std::ostream& s, const bit& b)
{
    uint32_t v=b();
    char c= v!=0 ? '1' : 0;
    s.put(c);
    return s;
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
    uint64_t r = a() | b();
    return r;
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

inline
bool
cftal::all_of(const vec<bit, 1>& a)
{
    return a() == vec<bit, 1>::mask;
}

inline
bool
cftal::any_of(const vec<bit, 1>& a)
{
    return a() != 0;
}

inline
bool
cftal::none_of(const vec<bit, 1>& a)
{
    return a() == 0;
}


template <std::size_t _N>
inline
cftal::vec<cftal::bit, _N>
cftal::
select(const vec<bit, _N>&  m,
       const vec<bit, _N>& on_true, const vec<bit, _N> on_false)
{
    return vec<bit, _N>(select(m(), on_true(), on_false()));
}

inline
std::ostream&
cftal::operator<<(std::ostream& s, const vec<bit, 1>& v)
{
    char c= v() != 0 ? '1' : '0';
    s.put(c);
    return s;
}


// Local variables:
// mode: c++
// end:
#endif
