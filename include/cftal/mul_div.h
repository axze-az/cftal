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
#if !defined (__CFTAL_MUL_DIV_H__)
#define __CFTAL_MUL_DIV_H__ 1

#include <cftal/config.h>
#include <cftal/bitops.h>
#include <cftal/select.h>
#include <cftal/type_traits.h>
#include <iosfwd>
#include <utility>

namespace cftal {

    // calculate the remainder from trunc(n/d)=q
    template <class _V>
    _V remainder(const _V& n, const _V& d, const _V& q);

    // return low part in first, high part in second of a*b
    template <class _T>
    std::enable_if_t<cftal::is_integral<_T>::value, std::pair<_T, _T> >
    mul_lo_hi(const _T& a, const _T& b);
    // return high part of a*b
    template <class _T>
    std::enable_if_t<cftal::is_integral<_T>::value, _T>
    mul_hi(const _T& a, const _T& b);

    namespace impl {

        template <class _U>
        struct umul_lo_hi {
            static_assert(is_integral<_U>::value, "_U must be integral");
            // returns low part in first, high part in second
            std::pair<_U, _U> operator()(const _U& a, const _U& b)
                const;
        };

        template <class _S>
        struct smul_lo_hi {
            static_assert(is_integral<_S>::value, "_S must be integral");
            // returns low part in first, high part in second
            std::pair<_S, _S> operator()(const _S& a, const _S& b)
                const;
        };

#if !defined (__NO_MUL_LO_HI_SPECIALIZATIONS__)
        // specializations for standard types.
        template <>
        struct umul_lo_hi<uint8_t> {
            std::pair<uint8_t, uint8_t>
            operator()(const uint8_t a, const uint8_t b)
                const {
                uint16_t p(uint16_t(a)*b);
                uint8_t l(p);
                uint8_t h(p>>8);
                return std::make_pair(l, h);
            }
        };

        template <>
        struct smul_lo_hi<int8_t> {
            std::pair<int8_t, int8_t>
            operator()(const int8_t a, const int8_t b)
                const {
                int16_t p(int16_t(a)*b);
                int8_t l(p);
                int8_t h(p>>8);
                return std::make_pair(l, h);
            }
        };

        template <>
        struct umul_lo_hi<uint16_t> {
            std::pair<uint16_t, uint16_t>
            operator()(const uint16_t a, const uint16_t b)
                const {
                uint32_t p(uint32_t(a)*b);
                uint16_t l(p);
                uint16_t h(p>>16);
                return std::make_pair(l, h);
            }
        };

        template <>
        struct smul_lo_hi<int16_t> {
            std::pair<int16_t, int16_t>
            operator()(const int16_t a, const int16_t b)
                const {
                int32_t p(int32_t(a)*b);
                int16_t l(p);
                int16_t h(p>>16);
                return std::make_pair(l, h);
            }
        };

        template <>
        struct umul_lo_hi<uint32_t> {
            std::pair<uint32_t, uint32_t>
            operator()(const uint32_t a, const uint32_t b)
                const {
                uint64_t p(uint64_t(a)*b);
                uint32_t l(p);
                uint32_t h(p>>32);
                return std::make_pair(l, h);
            }
        };

        template <>
        struct smul_lo_hi<int32_t> {
            std::pair<int32_t, int32_t>
            operator()(const int32_t a, const int32_t b)
                const {
                int64_t p(int64_t(a)*b);
                int32_t l(p);
                int32_t h(p>>32);
                return std::make_pair(l, h);
            }
        };

#if defined (__GNUC__) && /* !defined(__clang__) && */       \
    (defined (__LP64__) || defined (__x86_64__))
        template <>
        struct umul_lo_hi<uint64_t> {
            std::pair<uint64_t, uint64_t>
            operator()(const uint64_t a, const uint64_t b)
                const {
                typedef unsigned __int128 u128_t;
                u128_t p(u128_t(a)*b);
                uint64_t l(p);
                uint64_t h(p>>64);
                return std::make_pair(l, h);
            }
        };

        template <>
        struct smul_lo_hi<int64_t> {
            std::pair<int64_t, int64_t>
            operator()(const int64_t a, const int64_t b)
                const {
                typedef __int128 i128_t;
                i128_t p(i128_t(a)*b);
                int64_t l(p);
                int64_t h(p>>64);
                return std::make_pair(l, h);
            }
        };
#endif

#endif
    }

    namespace impl {

        template <class _U>
        struct udiv_result {
            _U _q0;
            _U _q1;
            _U _r;
            udiv_result(const _U& q0, const _U& q1, const _U& r)
                : _q0(q0), _q1(q1), _r(r) {
            }
        };

        template <class _U>
        udiv_result<_U>
        make_udiv_result(const _U& q0, const _U& q1, const _U& r)
        {
            static_assert(is_integral<_U>::value, "_U must be integral");
            return udiv_result<_U>(q0, q1, r);
        }


        template <class _U, class _UHALF=_U>
        class udiv_2by1_base {
        public:
            static_assert(is_integral<_U>::value, "_U must be integral");
            static
            udiv_result<_U>
            d(const _U& u0, const _U& u1, const _U& v);
        private:
            static _U
            g(const _U& uh, const _U& ul,  const _U& v, _U& r);
        };

        template <class _U, class _UHALF=_U>
        class udiv_2by1 : public udiv_2by1_base<_U, _UHALF> {
        };


#if !defined (__NO_UDIV_2BY1_SPECIALIZATIONS__)

        template <class _UHALF>
        class udiv_2by1<uint8_t, _UHALF> {
        public:
            static_assert(std::is_same<uint8_t, _UHALF>::value,
                          "test");
            static
            udiv_result<uint8_t>
            d(uint8_t u0, uint8_t u1, uint8_t v) {
                uint16_t u((uint16_t(u1)<<8)|u0);
                uint16_t q(u/v);
                uint8_t r(u%v);
                uint8_t q0(q), q1(q>>8);
                return make_udiv_result(q0, q1, r);
            }
        };

        template <class _UHALF>
        class udiv_2by1<uint16_t, _UHALF> {
        public:
            static
            udiv_result<uint16_t>
            d(uint16_t u0, uint16_t u1, uint16_t v) {
                uint32_t u((uint32_t(u1)<<16)|u0);
                uint32_t q(u/v);
                uint16_t r(u%v);
                uint16_t q0(q), q1(q>>16);
                return make_udiv_result(q0, q1, r);
            }
        };


        class udiv_2by1_div_32 {
        public:
            static
            udiv_result<uint32_t>
            d(uint32_t u0, uint32_t u1, uint32_t v) {
                uint64_t u((uint64_t(u1)<<32)|u0);
                uint64_t q(u/v);
                uint32_t r(u%v);
                uint32_t q0(q), q1(q>>32);
                return make_udiv_result(q0, q1, r);
            }
        };

        class udiv_2by1_rcp_32 {
        public:
            // divide u0 + u1 2^32 by v
            static
            udiv_result<uint32_t>
            d(uint32_t u0, uint32_t u1, uint32_t v);
            // calculate (<u0, u1> << l_z) / nv
            // nv is the normalized divisor (v << l_z)
            // inv is the result of reciprocal_word(nv)
            static
            udiv_result<uint32_t>
            d(uint32_t u0, uint32_t u1, uint32_t nv,
              uint32_t inv, unsigned l_z);
            // calculate the reciprocal word to d
            // d must be normalized.
            static
            std::uint32_t reciprocal_word(std::uint32_t d);
            // division of (normalized) <u0, u1> by
            // normalized d without overflow.
            static
            std::uint32_t
            sd(uint32_t u0, uint32_t u1, uint32_t v,
               uint32_t inv, uint32_t& r);
            // we use only the high part of the table
            enum { TABLE_SIZE = 1<<10 };
        private:
            // calculate the reciprocal word to d
            // d must be normalized.
            static
            std::uint32_t reciprocal_word_i(std::uint32_t d);
            // calculate (<u0, u1> << l_z) / nv
            // nv is the normalized divisor (v << l_z)
            // inv is the result of reciprocal_word(nv)
            static
            udiv_result<uint32_t>
            d_i(uint32_t u0, uint32_t u1, uint32_t nv,
                uint32_t inv, unsigned l_z);
            // division of (normalized) <u0, u1> by
            // normalized d without overflow.
            static
            std::uint32_t
            sd_i(uint32_t u0, uint32_t u1, uint32_t v,
                 uint32_t inv, uint32_t& r);
            static const uint16_t _tbl[TABLE_SIZE];
        };

        void print_rcp_32_table(std::ostream& s);

        template <class _UHALF>
        class udiv_2by1<uint32_t, _UHALF> : public udiv_2by1_div_32 {
        };


        class udiv_2by1_rcp_64 {
        public:
            static
            udiv_result<uint64_t>
            d(uint64_t u0, uint64_t u1, uint64_t v);
            // calculate (<u0, u1> << l_z) / nv
            // nv is the normalized divisor (v << l_z)
            // inv is the result of reciprocal_word(nv)
            static
            udiv_result<uint64_t>
            d(uint64_t u0, uint64_t u1, uint64_t nv,
              uint64_t inv, unsigned l_z);
            // calculate the reciprocal word to d
            // d must be normalized.
            static
            std::uint64_t reciprocal_word(std::uint64_t d);
            // division of (normalized) <u0, u1> by
            // normalized d without overflow.
            static
            std::uint64_t
            sd(uint64_t u0, uint64_t u1, uint64_t v,
               uint64_t inv, uint64_t& r);
            // we use only the high part of the table
            enum { TABLE_SIZE = 1<<9 };
        private:
            // calculate the reciprocal word to d
            // d must be normalized.
            static
            std::uint64_t reciprocal_word_i(std::uint64_t d);
            // calculate (<u0, u1> << l_z) / nv
            // nv is the normalized divisor (v << l_z)
            // inv is the result of reciprocal_word(nv)
            static
            udiv_result<uint64_t>
            d_i(uint64_t u0, uint64_t u1, uint64_t nv,
                uint64_t inv, unsigned l_z);
            // division of (normalized) <u0, u1> by
            // normalized d without overflow.
            static
            std::uint64_t
            sd_i(uint64_t u0, uint64_t u1, uint64_t v,
                 uint64_t inv, uint64_t& r);

            static const uint16_t _tbl[TABLE_SIZE];
        };

        void print_rcp_64_table(std::ostream& s);


#if defined (__GNUC__) && (defined (__LP64__) || defined (__x86_64__))

        class udiv_2by1_div_64 {
        public:
            static
            udiv_result<uint64_t>
            d(uint64_t u0, uint64_t u1, uint64_t v) {
#if defined (__x86_64__)
                uint64_t q0, q1, r;
                if (u1>=v) {
                    __asm__("divq %4 \n\t"
                            : "=a"(q1), "=d"(r)
                            : "0"(u1), "1"(0), "rm"(v)
                            : "cc");
                    __asm__("divq %4 \n\t"
                            : "=a"(q0), "=d"(r)
                            : "0"(u0), "1"(r), "rm"(v)
                            : "cc");
                } else {
                    q1 =0;
                    __asm__("divq %4 \n\t"
                            : "=a"(q0), "=d"(r)
                            : "0"(u0), "1"(u1), "rm"(v)
                            : "cc");
                }
#else
                typedef unsigned __int128 u128_t;
                u128_t u((u128_t(u1)<<64)|u0);
                u128_t q(u/v);
                uint64_t r(u%v);
                uint64_t q0(q), q1(q>>64);
#endif
                return make_udiv_result(q0, q1, r);
            }
        };

        template <class _UHALF>
        class udiv_2by1<uint64_t, _UHALF> : public udiv_2by1_div_64 {
        };
#endif

#endif
    }
}


template <class _U>
std::pair<_U, _U>
cftal::impl::umul_lo_hi<_U>::operator()(const _U& a, const _U& b)
    const
{
    enum {
        N = sizeof(_U)* 8,
        N2 = N>>1
    };

    const _U N2MSK= (_U(1)<<N2)-_U(1);
    const _U MED_CARRY = _U(1) << N2;

    _U al = a & N2MSK;
    _U ah = a >> N2;
    _U bl = b & N2MSK;
    _U bh = b >> N2;

    _U al_bl = al * bl;
    _U al_bh = al * bh;
    _U ah_bl = ah * bl;
    _U ah_bh = ah * bh;

    _U med_sum = al_bh + ah_bl;
    _U l_add = med_sum << N2;
    _U h_add = med_sum >> N2;

    h_add |= select(med_sum < al_bh, MED_CARRY, _U(0));

    al_bl += l_add;
    _U l_carry= select(al_bl < l_add, _U(1), _U(0));

    ah_bh += l_carry;
    ah_bh += h_add;
    return std::make_pair(al_bl, ah_bh);
}

template <class _S>
std::pair<_S, _S>
cftal::impl::smul_lo_hi<_S>::operator()(const _S& x, const _S& y)
    const
{
    enum {
        N = sizeof(_S)* 8
    };
    typedef typename make_unsigned<_S>::type _U;
    _U xu(x);
    _U yu(y);
    umul_lo_hi<_U> m;
    std::pair<_U, _U> ur(m(xu, yu));
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    _S xsign_x = x >> (N-1);
    _S xsign_y = y >> (N-1);
    _S h = _S(ur.second) - (x & xsign_y) - (y & xsign_x);
    _S l = _S(ur.first);
    return std::make_pair(l, h);
}

template <class _U, class _UHALF>
cftal::impl::udiv_result<_U>
cftal::impl::udiv_2by1_base<_U, _UHALF>::
d(const _U& u0, const _U& u1, const _U& v)
{
    _U q1(0); _U q0(0);
    _U r(0);
    if (u1 >= v) {
        // j== 1
        q1= g(u1, 0, v, r);
        // j== 0
        q0= g(u0, r, v, r);
    } else {
        q0= g(u0, u1, v, r);
    }
    return make_udiv_result(q0, q1, r);
}

template <class _U, class _UHALF>
_U cftal::impl::udiv_2by1_base<_U, _UHALF>::
g(const _U& ul, const _U& uh, const _U& cv, _U& r)
{
    const unsigned N= sizeof(_U)*8;
    const unsigned N2= N>>1;
    // number base of the division
    const _U b= _U(1)<<N2;
    // mask out half of the bits of an _U
    const _U N2MSK= b - _U(1);
    // maximum possible u
    const _U U_MAX= ~_U(0);
    // Norm. divisor digits.
    _U un1, un0;
    // divisor digits.
    _UHALF vn1, vn0;
    // Quotient digits.
    _U q1, q0;
    // Dividend digit pairs.
    _U un32, un21, un10;
    // A remainder.
    _U rhat;
    // Shift amount for norm.
    unsigned s;
    _U v(cv);
    if (uh >= v) {
        // If overflow, set rem. to an impossible value,
        r = U_MAX;
        // and return the largest possible quotient.
        return U_MAX;
    }
    s = lzcnt(v);               // 0 <= s <= N-1.
    if (s>0) {
        // Normalize divisor.
        v = v << s;
    }
    vn1 = _UHALF(v >> N2);       // Break divisor up into
    vn0 = _UHALF(v & N2MSK);     // two half digits

    if (s>0) {
        // Shift dividend left.
        unsigned sr= N-s;
        _U un32_lb= ul >> sr;
        un32 = (uh << s) | un32_lb;
        un10 = ul << s;
    } else {
        un32 = uh;
        un10 = ul;
    }

    // Break right half of dividend into two digits.
    un1 = un10 >> N2;
    un0 = un10 & N2MSK;

    q1 = un32/vn1;            // Compute the first
    rhat = un32 - q1*vn1;     // quotient digit, q1.

    while (q1 >= b || q1*vn0 > b*rhat + un1) {
        q1 = q1 - _UHALF(1);
        rhat = rhat + vn1;
        if (rhat >= b)
            break;
    }

    un21 = un32*b + un1 - q1*v;  // Multiply and subtract.

    q0 = un21/vn1;            // Compute the second
    rhat = un21 - q0*vn1;     // quotient digit, q0.

    while (q0 >= b || q0*vn0 > b*rhat + un0) {
        q0 = q0 - _UHALF(1);
        rhat = rhat + vn1;
        if (rhat >= b)
            break;
    }
    // If remainder is wanted, return it.
    r = (un21*b + un0 - q0*v) >> s;
    return q1*b + q0;
}


template <class _V>
inline
_V cftal::remainder(const _V& n, const _V& d, const _V& q)
{
    _V p(d* q);
    return n - p;
}

template <class _T>
inline
std::enable_if_t<cftal::is_integral<_T>::value, std::pair<_T, _T> >
cftal::mul_lo_hi(const _T& x, const _T& y)
{
    static_assert(is_integral<_T>::value,
                  "_T must be an integral type");
    using mul_type = select_t<cftal::is_signed<_T>::value,
			      impl::smul_lo_hi<_T>,
			      impl::umul_lo_hi<_T> >;
    mul_type m;
    return m(x, y);
}

template <class _T>
inline
std::enable_if_t<cftal::is_integral<_T>::value, _T>
cftal::mul_hi(const _T& x, const _T& y)
{
    return mul_lo_hi(x, y).second;
}

// Local variables:
// mode: c++
// end:
#endif
