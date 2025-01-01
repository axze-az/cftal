//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_D_INT_H__)
#define __CFTAL_D_INT_H__ 1

#include <cftal/config.h>
#include <cftal/mul_div.h>
#include <cftal/type_traits.h>

namespace cftal {

    // double unsigned integer
    template <typename _T>
    class duint {
        static_assert(is_unsigned<_T>::value, "_T must be unsigned");
    public:
        using type = _T;
        enum {
            N2 = sizeof(type) * 8,
            N = N2*2
        };
        constexpr duint() : _l(0), _h(0) {}
        constexpr duint(const type& vl) : _l(vl), _h(0) {}
        constexpr duint(const type& vl, const type& vh) : _l(vl), _h(vh) {}
        constexpr const type& l() const { return _l; }
        constexpr const type& uh() const { return _h; }
        void l(const type& v) { _l = v; }
        void uh(const type& v) { _h = v; }
        explicit operator _T() const { return _l; }
    private:
        type _l;
        type _h;
    };

    template <class _T>
    unsigned lzcnt(const duint<_T>& a);

    template <typename _T>
    duint<_T> operator~(const duint<_T>& a);
    template <typename _T>
    duint<_T> operator-(const duint<_T>& a);
    template <typename _T>
    const duint<_T>& operator+(const duint<_T>& a);
    template <typename _T>
    bool operator!(const duint<_T>& a);

    template <typename _T>
    duint<_T> operator++ (duint<_T>& a, int);
    template <typename _T>
    duint<_T>& operator++(duint<_T>& a);
    template <typename _T>
    duint<_T> operator-- (duint<_T>& a, int);
    template <typename _T>
    duint<_T>& operator--(duint<_T>& a);

    template <typename _T>
    duint<_T> operator|(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator|(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator|(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator&(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator&(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator&(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator^(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator^(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator^(const _T& a, const duint<_T>& b);

    template <typename _T>
    bool operator&&(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator&&(const duint<_T>& a, const _T& b);
    template <typename _T>
    bool operator&&(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator+(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator+(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator+(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator-(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator-(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator-(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator*(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator*(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator*(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator/(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator/(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator/(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator%(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T> operator%(const duint<_T>& a, const _T& b);
    template <typename _T>
    duint<_T> operator%(const _T& a, const duint<_T>& b);

    template <typename _T>
    duint<_T> operator<<(const duint<_T>& a, unsigned s);
    template <typename _T>
    duint<_T> operator<<(const duint<_T>& a, int s);
    template <typename _T>
    duint<_T> operator>>(const duint<_T>& a, unsigned s);
    template <typename _T>
    duint<_T> operator>>(const duint<_T>& a, int s);

    template <typename _T>
    duint<_T>& operator|=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator|=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator&=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator&=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator^=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator^=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator+=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator+=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator-=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator-=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator*=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator*=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator/=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator/=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator%=(duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    duint<_T>& operator%=(duint<_T>& a, const _T& b);

    template <typename _T>
    duint<_T>& operator<<=(duint<_T>& a, unsigned s);
    template <typename _T>
    duint<_T>& operator<<=(duint<_T>& a, int s);
    template <typename _T>
    duint<_T>& operator>>=(duint<_T>& a, unsigned s);
    template <typename _T>
    duint<_T>& operator>>=(duint<_T>& a, int s);

    template <typename _T>
    bool operator<(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator<(const _T& a, const duint<_T>& b);
    template <typename _T>
    bool operator<(const duint<_T>& a, const _T& b);

    template <typename _T>
    bool operator<=(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator<=(const _T& a, const duint<_T>& b);
    template <typename _T>
    bool operator<=(const duint<_T>& a, const _T& b);

    template <typename _T>
    bool operator==(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator==(const _T& a, const duint<_T>& b);
    template <typename _T>
    bool operator==(const duint<_T>& a, const _T& b);

    template <typename _T>
    bool operator!=(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator!=(const _T& a, const duint<_T>& b);
    template <typename _T>
    bool operator!=(const duint<_T>& a, const _T& b);

    template <typename _T>
    bool operator>=(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator>=(const _T& a, const duint<_T>& b);
    template <typename _T>
    bool operator>=(const duint<_T>& a, const _T& b);

    template <typename _T>
    bool operator>(const duint<_T>& a, const duint<_T>& b);
    template <typename _T>
    bool operator>(const _T& a, const duint<_T>& b);
    template <typename _T>
    bool operator>(const duint<_T>& a, const _T& b);

    // double signed integer
    template <typename _T>
    class dint : public duint<typename std::make_unsigned<_T>::type> {
        static_assert(is_signed<_T>::value, "_T must be signed");
    public:
        using type = _T;
        using utype = typename std::make_unsigned<_T>::type;
        using base_type = duint<utype>;
        constexpr dint() : base_type() {}
        constexpr dint(const type& vl) :
            base_type(vl, vl < _T(0) ? ~_T(0) : _T(0)) { }
        constexpr dint(const utype& vl, const type& vh) : base_type(vl,vh) {}
        constexpr dint(const base_type& b) : base_type(b) { }
        // l is inherited from base_tpye.
        constexpr const type& sh() const {
            return reinterpret_cast<const type&>(base_type::uh());
            // const utype& _uh= base_type::uh();
            // const type* ph= reinterpret_cast<const type*>(&_uh);
            // return *ph;
        }
        explicit operator _T() const {
            return type(this->l());
        }
    };

    template <typename _T>
    dint<_T> operator~(const dint<_T>& a);
    template <typename _T>
    dint<_T> operator-(const dint<_T>& a);
    template <typename _T>
    const dint<_T>& operator+(const dint<_T>& a);
    template <typename _T>
    bool operator!(const dint<_T>& a);

    template <typename _T>
    dint<_T> operator++ (dint<_T>& a, int);
    template <typename _T>
    dint<_T>& operator++(dint<_T>& a);
    template <typename _T>
    dint<_T> operator-- (dint<_T>& a, int);
    template <typename _T>
    dint<_T>& operator--(dint<_T>& a);

    template <typename _T>
    dint<_T> operator|(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator|(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator|(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator&(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator&(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator&(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator^(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator^(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator^(const _T& a, const dint<_T>& b);

    template <typename _T>
    bool operator&&(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator&&(const dint<_T>& a, const _T& b);
    template <typename _T>
    bool operator&&(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator+(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator+(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator+(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator-(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator-(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator-(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator*(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator*(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator*(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator/(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator/(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator/(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator%(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T> operator%(const dint<_T>& a, const _T& b);
    template <typename _T>
    dint<_T> operator%(const _T& a, const dint<_T>& b);

    template <typename _T>
    dint<_T> operator<<(const dint<_T>& a, unsigned s);
    template <typename _T>
    dint<_T> operator<<(const dint<_T>& a, int s);
    template <typename _T>
    dint<_T> operator>>(const dint<_T>& a, unsigned s);
    template <typename _T>
    dint<_T> operator>>(const dint<_T>& a, int s);

    template <typename _T>
    dint<_T>& operator|=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator|=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator&=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator&=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator^=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator^=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator+=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator+=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator-=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator-=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator*=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator*=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator/=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator/=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator%=(dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    dint<_T>& operator%=(dint<_T>& a, const _T& b);

    template <typename _T>
    dint<_T>& operator<<=(dint<_T>& a, unsigned s);
    template <typename _T>
    dint<_T>& operator<<=(dint<_T>& a, int s);
    template <typename _T>
    dint<_T>& operator>>=(dint<_T>& a, unsigned s);
    template <typename _T>
    dint<_T>& operator>>=(dint<_T>& a, int s);

    template <typename _T>
    bool operator<(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator<(const _T& a, const dint<_T>& b);
    template <typename _T>
    bool operator<(const dint<_T>& a, const _T& b);

    template <typename _T>
    bool operator<=(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator<=(const _T& a, const dint<_T>& b);
    template <typename _T>
    bool operator<=(const dint<_T>& a, const _T& b);

    template <typename _T>
    bool operator==(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator==(const _T& a, const dint<_T>& b);
    template <typename _T>
    bool operator==(const dint<_T>& a, const _T& b);

    template <typename _T>
    bool operator!=(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator!=(const _T& a, const dint<_T>& b);
    template <typename _T>
    bool operator!=(const dint<_T>& a, const _T& b);

    template <typename _T>
    bool operator>=(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator>=(const _T& a, const dint<_T>& b);
    template <typename _T>
    bool operator>=(const dint<_T>& a, const _T& b);

    template <typename _T>
    bool operator>(const dint<_T>& a, const dint<_T>& b);
    template <typename _T>
    bool operator>(const _T& a, const dint<_T>& b);
    template <typename _T>
    bool operator>(const dint<_T>& a, const _T& b);

#if defined (__GNUC__) && defined (__x86_64__) && !defined (__clang__)
    duint<uint64_t> operator+(const duint<uint64_t>& a,
                              const duint<uint64_t>& b);
    duint<uint64_t> operator+(const duint<uint64_t>& a,
                              const uint64_t& b);
    duint<uint64_t> operator+(const uint64_t& a,
                              const duint<uint64_t>& b);

    duint<uint64_t> operator-(const duint<uint64_t>& a,
                              const duint<uint64_t>& b);
    duint<uint64_t> operator-(const duint<uint64_t>& a,
                              const uint64_t& b);
    duint<uint64_t> operator-(const uint64_t& a,
                              const duint<uint64_t>& b);

    duint<uint64_t> operator*(const duint<uint64_t>& a,
                              const duint<uint64_t>& b);
    duint<uint64_t> operator*(const duint<uint64_t>& a,
                              const uint64_t& b);
    duint<uint64_t> operator*(const uint64_t& a,
                              const duint<uint64_t>& b);
#endif

    template <class _T>
    struct is_signed<duint<_T> >
        : public is_signed<_T> { };
    template <class _T>
    struct is_unsigned<duint<_T> >
        : public is_unsigned<_T> { };
    template <class _T>
    struct make_signed<duint<_T> > {
        typedef dint<_T> type;
    };
    template <class _T>
    struct make_unsigned<duint<_T> > {
        typedef duint<_T> type;
    };
    template <class _T>
    struct is_integral<duint<_T> >
        : public is_integral<_T> {};

    template <class _T>
    struct is_signed<dint<_T> >
        : public is_signed<_T> { };
    template <class _T>
    struct is_unsigned<dint<_T> >
        : public is_unsigned<_T> { };
    template <class _T>
    struct make_signed<dint<_T> > {
        typedef dint<_T> type;
    };
    template <class _T>
    struct make_unsigned<dint<_T> > {
        typedef duint<_T> type;
    };
    template <class _T>
    struct is_integral<dint<_T> >
        : public is_integral<_T> {};
}

namespace cftal {

    namespace impl {

        template <class _T>
        struct sign {
            static
            bool get(const _T& a) {
                typename std::make_signed<_T>::type s(a);
                return s < 0 ? true : false;
            }
        };

        template <class _T>
        struct sign<duint<_T> > {
            static
            bool get(const duint<_T>& a) {
                return sign<_T>::get(a.uh());
            }
        };

        template <class _T>
        struct sign<dint<_T> > {
            static
            bool get(const dint<_T>& a) {
                return sign<_T>::get(a.uh());
            }
        };

        template <class _T>
        bool get_sign(const _T& a)
        {
            return sign<_T>::get(a);
        }
    }
}

// duint<_T> implementation
template <class _T>
unsigned cftal::lzcnt(const duint<_T>& a)
{
    unsigned res(a.uh() == 0 ?
                 lzcnt(a.l()) + duint<_T>::N2 :
                 lzcnt(a.uh()));
    return res;
}

template <typename _T>
cftal::duint<_T> cftal::operator~(const duint<_T>& a)
{
    return duint<_T>(~a.l(),~a.uh());
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const duint<_T>& a)
{
    return _T(0) - a;
}

template <typename _T>
const cftal::duint<_T>& cftal::operator+(const duint<_T>& a)
{
    return a;
}

template <typename _T>
bool cftal::operator!(const duint<_T>& a)
{
    return a != _T(0);
}

template <typename _T>
cftal::duint<_T>& cftal::operator++(duint<_T>& a)
{
    a= a+_T(1);
    return a;
}

template <typename _T>
cftal::duint<_T> cftal::operator++(duint<_T>& a, int)
{
    duint<_T> t(a);
    a = a + _T(1);
    return t;
}

template <typename _T>
cftal::duint<_T>& cftal::operator--(duint<_T>& a)
{
    a= a-_T(1);
    return a;
}

template <typename _T>
cftal::duint<_T> cftal::operator--(duint<_T>& a, int)
{
    duint<_T> t(a);
    a = a-_T(1);
    return t;
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const duint<_T>& a, const duint<_T>& b)
{
    typename duint<_T>::type rl= a.l() | b.l();
    typename duint<_T>::type rh= a.uh() | b.uh();
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const duint<_T>& a, const _T& b)
{
    typename duint<_T>::type rl= a.l() | b;
    typename duint<_T>::type rh= a.uh();
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator|(const _T& a, const duint<_T>& b)
{
    return b | a;
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const duint<_T>& a, const duint<_T>& b)
{
    typename duint<_T>::type rl= a.l() & b.l();
    typename duint<_T>::type rh= a.uh() & b.uh();
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const duint<_T>& a, const _T& b)
{
    typename duint<_T>::type rl= a.l() & b;
    typename duint<_T>::type rh= _T(0);
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator&(const _T& a, const duint<_T>& b)
{
    return b & a;
}

template <typename _T>
bool cftal::operator&&(const duint<_T>& a, const duint<_T>& b)
{
    return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const duint<_T>& a, const _T& b)
{
    return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const _T& a, const duint<_T>& b)
{
    return b && a;
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const duint<_T>& a, const duint<_T>& b)
{
    typename duint<_T>::type rl= a.l() ^ b.l();
    typename duint<_T>::type rh= a.uh() ^ b.uh();
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const duint<_T>& a, const _T& b)
{
    typename duint<_T>::type rl= a.l() ^ b;
    typename duint<_T>::type rh= a.uh() ^ _T(0);
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator^(const _T& a, const duint<_T>& b)
{
    return b ^ a;
}

template <typename _T>
cftal::duint<_T> cftal::operator+(const duint<_T>& a, const duint<_T>& b)
{
    typename duint<_T>::type rl= a.l() + b.l();
    typename duint<_T>::type rh= a.uh() + b.uh();
    rh += (rl < a.l() ? _T(1) : _T(0));
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator+(const duint<_T>& a, const _T& b)
{
    typename duint<_T>::type rl= a.l() + b;
    typename duint<_T>::type rh= a.uh();
    rh += (rl < a.l() ? _T(1) : _T(0));
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator+(const _T& a, const duint<_T>& b)
{
    return b+a;
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const duint<_T>& a, const duint<_T>& b)
{
    typename duint<_T>::type rl= a.l() - b.l();
    typename duint<_T>::type rh= a.uh() - b.uh();
    rh -= (a.l() < b.l() ? _T(1) : _T(0));
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const duint<_T>& a, const _T& b)
{
    typename duint<_T>::type rl= a.l() - b;
    typename duint<_T>::type rh= a.uh();
    rh -= (a.l() < b ? _T(1) : _T(0));
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator-(const _T& a, const duint<_T>& b)
{
    typename duint<_T>::type rl= a - b.l();
    typename duint<_T>::type rh= -b.uh();
    rh -= (a < b.l() ? _T(1) : _T(0));
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const duint<_T>& a, const duint<_T>& b)
{
    typedef typename duint<_T>::type type;
    typedef std::pair<type, type> pair_type;
    // [2^ 0, 2^N2 )
    pair_type al_bl(mul_lo_hi(a.l(), b.l()));
    // [2^(N2/2),  2^(N2*2/2) )
    type al_bh(a.l() * b.uh());
    type ah_bl(a.uh() * b.l());
    // shift al_bh and ah_bl right by 2^(N2/2)
    return duint<_T>(al_bl.first, al_bl.second+ al_bh + ah_bl);
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const duint<_T>& a, const _T& b)
{
    typedef typename duint<_T>::type type;
    typedef std::pair<type, type> pair_type;
    // [2^ 0, 2^N2 )
    pair_type al_b(mul_lo_hi(a.l(), b));
    // [2^(N2/2),  2^(N2*2/2) )
    type ah_b(a.uh() * b);
    // shift al_bh and ah_bl right by 2^(N2/2)
    return duint<_T>(al_b.first, al_b.second + ah_b);
}

template <typename _T>
cftal::duint<_T> cftal::operator*(const _T& a, const duint<_T>& b)
{
    return b* a;
}

template <typename _T>
cftal::duint<_T> cftal::operator/(const duint<_T>& a, const _T& b)
{
    typedef impl::udiv_2by1<_T, _T> div_type;
    impl::udiv_result<_T> qr(div_type::d(a.l(), a.uh(), b));
    return duint<_T>(qr._q0, qr._q1);
}

template <typename _T>
cftal::duint<_T> cftal::operator/(const duint<_T>& a, const duint<_T>& b)
{
    typedef impl::udiv_2by1<duint<_T>, _T> div_type;
    impl::udiv_result<duint<_T> > qr(div_type::d(a, duint<_T>(0), b));
    return qr._q0;
}

template <typename _T>
cftal::duint<_T> cftal::operator/(const _T& a, const duint<_T>& b)
{
    duint<_T> ad(a);
    return ad / b;
}

template <typename _T>
cftal::duint<_T> cftal::operator%(const duint<_T>& a, const _T& b)
{
    typedef impl::udiv_2by1<_T, _T> div_type;
    impl::udiv_result<_T> qr(div_type::d(a.l(), a.uh(), b));
    return duint<_T>(qr._r);
}

template <typename _T>
cftal::duint<_T> cftal::operator%(const duint<_T>& a, const duint<_T>& b)
{
    typedef impl::udiv_2by1<duint<_T>, _T> div_type;
    impl::udiv_result<duint<_T> > qr(div_type::d(a, duint<_T>(0), b));
    return qr._r;
}

template <typename _T>
cftal::duint<_T> cftal::operator%(const _T& a, const duint<_T>& b)
{
    return duint<_T>(a) % b;
}

template <typename _T>
cftal::duint<_T> cftal::operator<<(const duint<_T>& a, unsigned s)
{
    typename duint<_T>::type rl;
    typename duint<_T>::type rh;
    if (s >= duint<_T>::N) {
        rl = rh = _T(0);
    } else if ( s>= duint<_T>::N2 ) {
        rl = _T(0);
        unsigned ss=s-duint<_T>::N2;
        rh = a.l() << ss;
    } else {
        // s < N2
        unsigned sr=duint<_T>::N2-s;
        typename duint<_T>::type t=a.l() >> sr;
        rl = a.l() << s;
        rh = (a.uh() << s) | t;
    }
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator<<(const duint<_T>& a, int s)
{
    return a << unsigned(s);
}

template <typename _T>
cftal::duint<_T> cftal::operator>>(const duint<_T>& a, unsigned s)
{
    typename duint<_T>::type rl;
    typename duint<_T>::type rh;
    if (s >= duint<_T>::N) {
        rl = rh = _T(0);
    } else if ( s>= duint<_T>::N2 ) {
        rh = _T(0);
        unsigned ss= s- duint<_T>::N2;
        rl = a.uh() >> ss;
    } else {
        // s < N2
        unsigned sr=duint<_T>::N2-s;
        typename duint<_T>::type t =a.uh() << sr;
        rh = a.uh() >> s;
        rl = (a.l() >> s) | t;
    }
    return duint<_T>(rl, rh);
}

template <typename _T>
cftal::duint<_T> cftal::operator>>(const duint<_T>& a, int s)
{
    return a >> unsigned(s);
}

template <typename _T>
cftal::duint<_T>& cftal::operator|=(duint<_T>& a, const duint<_T>& b)
{
    a = a | b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator|=(duint<_T>& a, const _T& b)
{
    a = a | b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator&=(duint<_T>& a, const duint<_T>& b)
{
    a = a & b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator&=(duint<_T>& a, const _T& b)
{
    a = a & b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator^=(duint<_T>& a, const duint<_T>& b)
{
    a = a ^ b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator^=(duint<_T>& a, const _T& b)
{
    a = a ^ b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator+=(duint<_T>& a, const duint<_T>& b)
{
    a = a + b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator+=(duint<_T>& a, const _T& b)
{
    a = a + b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator-=(duint<_T>& a, const duint<_T>& b)
{
    a = a - b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator-=(duint<_T>& a, const _T& b)
{
    a = a - b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator*=(duint<_T>& a, const duint<_T>& b)
{
    a = a * b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator*=(duint<_T>& a, const _T& b)
{
    a = a * b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator/=(duint<_T>& a, const duint<_T>& b)
{
    a = a / b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator/=(duint<_T>& a, const _T& b)
{
    a = a / b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator%=(duint<_T>& a, const duint<_T>& b)
{
    a = a % b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator%=(duint<_T>& a, const _T& b)
{
    a = a % b;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator<<=(duint<_T>& a, unsigned s)
{
    a= a << s;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator<<=(duint<_T>& a, int s)
{
    a= a << s;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator>>=(duint<_T>& a, unsigned s)
{
    a= a >> s;
    return a;
}

template <typename _T>
cftal::duint<_T>& cftal::operator>>=(duint<_T>& a, int s)
{
    a= a >> s;
    return a;
}

template <typename _T>
bool cftal::operator<(const duint<_T>& a, const duint<_T>& b)
{
    // return impl::get_sign(a -b) !=0;
    return (a.uh()< b.uh()) || ((a.uh()==b.uh()) && (a.l() < b.l()));
}

template <typename _T>
bool cftal::operator<(const _T& a, const duint<_T>& b)
{
    return (b.uh()==_T(0)) && (a < b.l());
}

template <typename _T>
bool cftal::operator<(const duint<_T>& a, const _T& b)
{
    return (a.uh()==_T(0)) && (a.l() < b);
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const duint<_T>& b)
{
    return (a.uh()< b.uh()) || ((a.uh()==b.uh()) && (a.l() <= b.l()));
}

template <typename _T>
bool cftal::operator<=(const _T& a, const duint<_T>& b)
{
    return (b.uh()==_T(0)) && (a <= b.l());
}

template <typename _T>
bool cftal::operator<=(const duint<_T>& a, const _T& b)
{
    return (a.uh()==_T(0)) && (a.l() <= b);
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const duint<_T>& b)
{
    return (a.uh() == b.uh()) && (a.l() == b.l());
}

template <typename _T>
bool cftal::operator==(const _T& a, const duint<_T>& b)
{
    return (b.uh()==_T(0)) && (a == b.l());
}

template <typename _T>
bool cftal::operator==(const duint<_T>& a, const _T& b)
{
    return (a.uh()==_T(0)) && (a.l() == b);
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const duint<_T>& b)
{
    return (a.uh() != b.uh()) || (a.l() != b.l());
}

template <typename _T>
bool cftal::operator!=(const _T& a, const duint<_T>& b)
{
    return (b.uh()!=_T(0)) || (a != b.l());
}

template <typename _T>
bool cftal::operator!=(const duint<_T>& a, const _T& b)
{
    return (a.uh()!=_T(0)) || (a.l() != b);
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const duint<_T>& b)
{
    return (a.uh() > b.uh()) || ((a.uh()==b.uh()) && (a.l() >= b.l()));
}

template <typename _T>
bool cftal::operator>=(const _T& a, const duint<_T>& b)
{
    return (b.uh()==_T(0)) && (a >= b.l());
}

template <typename _T>
bool cftal::operator>=(const duint<_T>& a, const _T& b)
{
    return (a.uh()>_T(0)) || (a.l() >= b);
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const duint<_T>& b)
{
    return (a.uh() > b.uh()) || ((a.uh()==b.uh()) && (a.l() > b.l()));
}

template <typename _T>
bool cftal::operator>(const _T& a, const duint<_T>& b)
{
    return (b.uh()==_T(0)) && (a > b.l());
}

template <typename _T>
bool cftal::operator>(const duint<_T>& a, const _T& b)
{
    return (a.uh()>_T(0)) || (a.l() > b);
}

// dint<_T> implementation
template <typename _T>
cftal::dint<_T> cftal::operator~(const dint<_T>& a)
{
    return ~ static_cast<const typename dint<_T>::base_type &>(a);
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const dint<_T>& a)
{
    return - static_cast<const typename dint<_T>::base_type &>(a);
}

template <typename _T>
const cftal::dint<_T>& cftal::operator+(const dint<_T>& a)
{
    return a;
}

template <typename _T>
bool cftal::operator!(const dint<_T>& a)
{
    return ! static_cast<const typename dint<_T>::base_type &>(a);
}

template <typename _T>
cftal::dint<_T>& cftal::operator++(dint<_T>& a)
{
    a= a+_T(1);
    return a;
}

template <typename _T>
cftal::dint<_T> cftal::operator++ (dint<_T>& a, int)
{
    dint<_T> t(a);
    a = a + _T(1);
    return t;
}

template <typename _T>
cftal::dint<_T>& cftal::operator--(dint<_T>& a)
{
    a= a-_T(1);
    return a;
}

template <typename _T>
cftal::dint<_T> cftal::operator-- (dint<_T>& a, int)
{
    dint<_T> t(a);
    a = a-_T(1);
    return t;
}

template <typename _T>
cftal::dint<_T> cftal::operator|(const dint<_T>& a, const dint<_T>& b)
{
    typename dint<_T>::utype rl= a.l() | b.l();
    typename dint<_T>::type rh= a.sh() | b.sh();
    return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator|(const dint<_T>& a, const _T& b)
{
    typename dint<_T>::utype rl= a.l() | b;
    typename dint<_T>::utype rh= a.sh();
    return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator|(const _T& a, const dint<_T>& b)
{
    return b | a;
}

template <typename _T>
cftal::dint<_T> cftal::operator&(const dint<_T>& a, const dint<_T>& b)
{
    typename dint<_T>::utype rl= a.l() & b.l();
    typename dint<_T>::type rh= a.sh() & b.sh();
    return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator&(const dint<_T>& a, const _T& b)
{
    typename dint<_T>::utype rl= a.l() & b;
    typename dint<_T>::type rh= _T(0);
    return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator&(const _T& a, const dint<_T>& b)
{
    return b & a;
}

template <typename _T>
bool cftal::operator&&(const dint<_T>& a, const dint<_T>& b)
{
    return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const dint<_T>& a, const _T& b)
{
    return (a != _T(0)) && (b != _T(0));
}

template <typename _T>
bool cftal::operator&&(const _T& a, const dint<_T>& b)
{
    return b && a;
}

template <typename _T>
cftal::dint<_T> cftal::operator^(const dint<_T>& a, const dint<_T>& b)
{
    typename dint<_T>::utype rl= a.l() ^ b.l();
    typename dint<_T>::utype rh= a.uh() ^ b.uh();
    return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator^(const dint<_T>& a, const _T& b)
{
    typename dint<_T>::type rl= a.l() ^ b;
    typename dint<_T>::type rh= a.uh() ^ 0;
    return dint<_T>(rl, rh);
}

template <typename _T>
cftal::dint<_T> cftal::operator^(const _T& a, const dint<_T>& b)
{
    return b ^ a;
}


template <typename _T>
cftal::dint<_T> cftal::operator+(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    return static_cast<const du_t&>(a) +
        static_cast<const du_t&>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator+(const dint<_T>& a, const _T& b)
{
    return a + dint<_T>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator+(const _T& a, const dint<_T>& b)
{
    return dint<_T>(a) + b;
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    return static_cast<const du_t&>(a) -
        static_cast<const du_t&>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const dint<_T>& a, const _T& b)
{
    return a - dint<_T>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator-(const _T& a, const dint<_T>& b)
{
    return dint<_T>(a) + b;
}

template <typename _T>
cftal::dint<_T> cftal::operator*(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    return static_cast<const du_t&>(a) *
        static_cast<const du_t&>(b);
}

template <typename _T>
cftal::dint<_T> cftal::operator*(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename std::make_unsigned<_T>::type u_t;
    du_t p(static_cast<const du_t&>(a) *
           static_cast<const u_t&>(b));
    if (impl::get_sign(b))
        p.uh(p.uh() -a.l());
    return p;
}

template <typename _T>
cftal::dint<_T> cftal::operator*(const _T& a, const dint<_T>& b)
{
    return b* a;
}

template <typename _T>
cftal::dint<_T> cftal::operator/(const dint<_T>& a, const _T& b)
{
    bool flip_a(impl::get_sign(a)), flip_b(impl::get_sign(b));
    typedef typename std::make_unsigned<_T>::type u_t;
    typedef typename dint<_T>::base_type du_t;
    du_t ap(flip_a ? -a : a);
    u_t bp(flip_b ? -b : b);
    dint<_T> q(ap / bp);
    if (flip_a ^ flip_b)
        q = -q;
    return q;
}

template <typename _T>
cftal::dint<_T> cftal::operator/(const dint<_T>& a, const dint<_T>& b)
{
    bool flip_a(impl::get_sign(a)), flip_b(impl::get_sign(b));
    typedef typename dint<_T>::base_type du_t;
    du_t ap(flip_a ? -a : a);
    du_t bp(flip_b ? -b : b);
    dint<_T> q(ap / bp);
    if (flip_a ^ flip_b)
        q = -q;
    return q;
}

template <typename _T>
cftal::dint<_T> cftal::operator/(const _T& a, const dint<_T>& b)
{
    dint<_T> ad(a);
    return ad / b;
}

template <typename _T>
cftal::dint<_T> cftal::operator%(const dint<_T>& a, const _T& b)
{
    dint<_T> q(a/b);
    return remainder(a, dint<_T>(b), q);
}

template <typename _T>
cftal::dint<_T> cftal::operator%(const dint<_T>& a, const dint<_T>& b)
{
    dint<_T> q(a/b);
    return remainder(a, b, q);
}

template <typename _T>
cftal::dint<_T> cftal::operator%(const _T& a, const dint<_T>& b)
{
    dint<_T> ad(a), q(ad/b);
    return remainder(ad, b, q);
}

template <typename _T>
cftal::dint<_T> cftal::operator<<(const dint<_T>& a, unsigned s)
{
    typedef typename dint<_T>::base_type du_t;
    return static_cast<const du_t&>(a) << s;
}

template <typename _T>
cftal::dint<_T> cftal::operator<<(const dint<_T>& a, int s)
{
    return a << unsigned(s);
}

template <typename _T>
cftal::dint<_T> cftal::operator>>(const dint<_T>& a, unsigned s)
{
    // arithmetic shift from logical shift:
    typedef typename dint<_T>::base_type du_t;
    // typedef typename std::make_unsigned<_T>::type u_t;
    const du_t& au = static_cast<const du_t&>(a);
    du_t t(- (au >> (dint<_T>::N-1)));
    du_t a_xor_t(a^ t);
    du_t t1(a_xor_t >> s);
    return t1 ^ t;
}

template <typename _T>
cftal::dint<_T> cftal::operator>>(const dint<_T>& a, int s)
{
    return a >> unsigned(s);
}

template <typename _T>
cftal::dint<_T>& cftal::operator|=(dint<_T>& a, const dint<_T>& b)
{
    a = a | b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator|=(dint<_T>& a, const _T& b)
{
    a = a | b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator&=(dint<_T>& a, const dint<_T>& b)
{
    a = a & b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator&=(dint<_T>& a, const _T& b)
{
    a = a & b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator^=(dint<_T>& a, const dint<_T>& b)
{
    a = a ^ b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator^=(dint<_T>& a, const _T& b)
{
    a = a ^ b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator+=(dint<_T>& a, const dint<_T>& b)
{
    a = a + b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator+=(dint<_T>& a, const _T& b)
{
    a = a + b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator-=(dint<_T>& a, const dint<_T>& b)
{
    a = a - b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator-=(dint<_T>& a, const _T& b)
{
    a = a - b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator*=(dint<_T>& a, const dint<_T>& b)
{
    a = a * b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator*=(dint<_T>& a, const _T& b)
{
    a = a * b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator/=(dint<_T>& a, const dint<_T>& b)
{
    a = a / b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator/=(dint<_T>& a, const _T& b)
{
    a = a / b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator%=(dint<_T>& a, const dint<_T>& b)
{
    a = a % b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator%=(dint<_T>& a, const _T& b)
{
    a = a % b;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator<<=(dint<_T>& a, unsigned s)
{
    a= a << s;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator<<=(dint<_T>& a, int s)
{
    a= a << s;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator>>=(dint<_T>& a, unsigned s)
{
    a= a >> s;
    return a;
}

template <typename _T>
cftal::dint<_T>& cftal::operator>>=(dint<_T>& a, int s)
{
    a= a >> s;
    return a;
}

template <typename _T>
bool cftal::operator<(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    bool r(static_cast<const du_t&>(a) < static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<(const _T& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const u_t&>(a) < static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const du_t&>(a) < static_cast<const u_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<=(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    bool r(static_cast<const du_t&>(a) <= static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<=(const _T& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const u_t&>(a) <= static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator<=(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const du_t&>(a) <= static_cast<const u_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator==(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    // typedef typename dint<_T>::utype u_t;
    return static_cast<const du_t&>(a) == static_cast<const du_t&>(b);
}

template <typename _T>
bool cftal::operator==(const _T& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    return static_cast<const u_t&>(a) == static_cast<const du_t&>(b);
}

template <typename _T>
bool cftal::operator==(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    return static_cast<const du_t&>(a) == static_cast<const u_t&>(b);
}

template <typename _T>
bool cftal::operator!=(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    return static_cast<const du_t&>(a) != static_cast<const du_t&>(b);
}

template <typename _T>
bool cftal::operator!=(const _T& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    return static_cast<const u_t&>(a) != static_cast<const du_t&>(b);
}

template <typename _T>
bool cftal::operator!=(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    return static_cast<const du_t&>(a) != static_cast<const u_t&>(b);
}

template <typename _T>
bool cftal::operator>=(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    bool r(static_cast<const du_t&>(a) >= static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>=(const _T& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const u_t&>(a) >= static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>=(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const du_t&>(a) >= static_cast<const u_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>(const dint<_T>& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    bool r(static_cast<const du_t&>(a) > static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>(const _T& a, const dint<_T>& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const u_t&>(a) > static_cast<const du_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

template <typename _T>
bool cftal::operator>(const dint<_T>& a, const _T& b)
{
    typedef typename dint<_T>::base_type du_t;
    typedef typename dint<_T>::utype u_t;
    bool r(static_cast<const du_t&>(a) > static_cast<const u_t&>(b));
    return impl::get_sign(a) ^ impl::get_sign(b) ^ r;
}

#if defined (__GNUC__) && defined (__x86_64__) && !defined (__clang__)
// specialized implementations, but clang 3.7 miscompiles it
inline
cftal::duint<uint64_t>
cftal::operator+(const duint<uint64_t>& a, const duint<uint64_t>& b)
{
    uint64_t l, h;
    __asm__ ("addq %4, %0 \n\t"
             "adcq %5, %1 \n\t"
             : "=m,r"(l), "=m,r"(h)
             : "0,0"(a.l()), "1,1"(a.uh()), "re,g"(b.l()), "re,g"(b.uh())
             : "cc");
    return duint<uint64_t>(l, h);
}

inline
cftal::duint<uint64_t>
cftal::operator+(const duint<uint64_t>& a, const uint64_t& b)
{
    uint64_t l,h;
    __asm__ ("addq %4, %0 \n\t"
             "adcq %5, %1 \n\t"
             : "=m,r"(l), "=m,r"(h)
             : "0,0"(a.l()), "1,1"(a.uh()), "re,g"(b), "K,K"(0)
             : "cc");
    return duint<uint64_t>(l, h);
}

inline
cftal::duint<uint64_t>
cftal::operator+(const uint64_t& a, const duint<uint64_t>& b)
{
    return b +a;
}

inline
cftal::duint<uint64_t>
cftal::operator-(const duint<uint64_t>& a, const duint<uint64_t>& b)
{
    uint64_t l,h;
    __asm__ ("subq %4, %0 \n\t"
             "sbbq %5, %1 \n\t"
             : "=m,r"(l), "=m,r"(h)
             : "0,0"(a.l()), "1,1"(a.uh()), "re,g"(b.l()), "re,g"(b.uh())
             : "cc");
    return duint<uint64_t>(l, h);
}

inline
cftal::duint<uint64_t>
cftal::operator-(const duint<uint64_t>& a, const uint64_t& b)
{
    uint64_t l,h;
    __asm__ ("subq %4, %0 \n\t"
             "sbbq %5, %1 \n\t"
             : "=m,r"(l), "=m,r"(h)
             : "0,0"(a.l()), "1,1"(a.uh()), "re,g"(b), "K,K"(0)
             : "cc");
    return duint<uint64_t>(l, h);
}

inline
cftal::duint<uint64_t>
cftal::operator-(const uint64_t& a, const duint<uint64_t>& b)
{
    return duint<uint64_t>(a) - b;
}

inline
cftal::duint<uint64_t>
cftal::operator*(const duint<uint64_t>& a, const duint<uint64_t>& b)
{
    uint64_t l, h;
    uint64_t ah = a.uh();
    uint64_t bh= b.uh();
    __asm__ ("imulq %[bl], %[ah] \n\t"
             "imulq %[al], %[bh] \n\t"
             "mulq %[bl]\n\t"
             "addq %[bh], %[ah] \n\t"
             "addq %[ah], %[bl] \n\t"
             : [al] "=a"(l), [bl] "=d" (h),
               [ah] "+r" (ah), [bh] "+r" (bh)
             : "0"(a.l()), "1"(b.l())
             : "cc");
    return duint<uint64_t>(l, h);
}

inline
cftal::duint<uint64_t>
cftal::operator*(const duint<uint64_t>& a, const uint64_t& b)
{
    uint64_t l, h;
    uint64_t ah = a.uh();
    __asm__ ("imulq %[bl], %[ah] \n\t"
             "mulq %[bl]\n\t"
             "addq %[ah], %[bl] \n\t"
             : [al] "=a"(l), [bl] "=d" (h),
               [ah] "+r" (ah)
             : "0"(a.l()), "1"(b)
             : "cc");
    return duint<uint64_t>(l, h);
}

inline
cftal::duint<uint64_t>
cftal::operator*(const uint64_t& a, const duint<uint64_t>& b)
{
    return b * a;
}

#endif

// Local variables:
// mode: c++
// end:
#endif
