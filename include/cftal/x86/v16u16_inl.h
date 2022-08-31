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
#if !defined (__CFTAL_X86_V16U16_INL__)
#define __CFTAL_X86_V16U16_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v16u16.h>
#include <cftal/x86/v16s16.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffff);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v16u16 ta(a ^ full_type(sign_s16_msk::v.u16l()));
                v16u16 tb(b ^ full_type(sign_s16_msk::v.u16l()));
                return _mm256_cmpgt_epi16(tb(), ta());
            }
        };

        template <>
        struct le<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a<= b: a == min(a, b);
                __m256i min_ab = _mm256_min_epu16(b(), a());
                return _mm256_cmpeq_epi16(a(), min_ab);
#else
                return ~(a > b);
#endif
            }
        };

        template <>
        struct eq<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpeq_epi16(a(), b());
            }
        };

        template <>
        struct ne<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a == b);
            }
        };

        template <>
        struct ge<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a>= b: a == max(a, b);
                __m256i max_ab = _mm256_max_epu16(b(), a());
                return _mm256_cmpeq_epi16(a(), max_ab);
#else
                return ~(a < b);
#endif
            }
        };

        template <>
        struct gt<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v16u16 ta(a ^ full_type(sign_s16_msk::v.u16l()));
                v16u16 tb(b ^ full_type(sign_s16_msk::v.u16l()));
                return _mm256_cmpgt_epi16(ta(), tb());
            }
        };

        template <>
        struct plus<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s16_msk::v.u16l());
                return _mm256_sign_epi16(a(), sgn());
#else
                const full_type zero(0);
                return _mm256_sub_epi16(zero(), a());
#endif
            }
        };

        template <>
        struct add<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi16(a(), b());
            }
        };

        template <>
        struct sub<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi16(a(), b());
            }
        };

        template <>
        struct mul<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullw::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u16::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v16u16 q(a/b);
                v16u16 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint16_t, 16>>::v(
                    mul<vec<uint16_t, 16>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint16_t, 16>>::v(
                    mul<vec<uint16_t, 16>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint16_t, 16>>::v(
                    c, mul<vec<uint16_t, 16>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_slli_epi16(a(), s);
            }
        };

        template <>
        struct shr<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_srli_epi16(a(), s);
            }
        };

#if defined (__AVX2__)
        template <>
        struct vshl<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvw::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<uint16_t, 16>> {
            using full_type = vec<uint16_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsrlvw::v(a(), s());
            }
        };
#endif

    }

}

inline
cftal::vec<cftal::uint16_t, 16>::vec(const vec<int16_t, 16>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint16_t, 16>::vec(uint16_t v)
    : base_type(_mm256_set1_epi16(v))
{
}

inline
cftal::vec<cftal::uint16_t, 16>::
vec(std::initializer_list<uint16_t> l)
    : vec(mem<vec<uint16_t, 16> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint16_t, 16>::
vec(init_list<uint16_t> l)
    : vec(mem<vec<uint16_t, 16> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<uint16_t, 16>::
vec(const vec<uint16_t, 8>& lh, const vec<uint16_t, 8>& hh)
    : base_type(_mm256_setr_m128i(lh(), hh()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint16_t, 16>::vec(const expr<_OP<vec<uint16_t, 16> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint16_t, 16>
cftal::mem<cftal::vec<uint16_t, 16> >::load(const uint16_t* p, std::size_t s)
{
    __m256i v;
    switch (s) {
    case 16:
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
        break;
    case 0:
        v = _mm256_set1_epi32(0);
        break;
    default: {
            x86::vecunion<uint16_t, 16, __m256, __m256d, __m256i> st;
            std::uint32_t si=s & 15;
            uint16_t pi=p[0];
            st._s[0]=pi;
            for (uint32_t i=1; i<si; ++i) {
                pi=p[i];
                st._s[i]=pi;
            }
            for (uint32_t i=si; i<16; ++i) {
                st._s[i]=pi;
            }
            v=_mm256_loadu_si256(&st._vi);
            break;
    }}
    return v;
}

inline
void
cftal::mem<cftal::vec<uint16_t, 16> >::store(uint16_t* p,
                                             const vec<uint16_t, 16>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::vec<uint16_t, 8>
cftal::low_half(const vec<uint16_t, 16>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<uint16_t, 8>
cftal::high_half(const vec<uint16_t, 16>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

template <cftal::size_t _I>
inline
cftal::uint16_t
cftal::extract(const vec<uint16_t, 16>& v)
{
    return x86::extract_u16<_I>(v());
}

inline
cftal::uint16_t
cftal::extract(const vec<uint16_t, 16>& v, size_t i)
{
    return x86::extract_u16(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint16_t, 16>& v, const uint16_t& vi)
{
    v= x86::insert_u16<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint16_t, 16>& v, const uint16_t& vi, size_t i)
{
    v= x86::insert_u16(v(), vi, i);
}

inline
bool cftal::all_of(const vec<uint16_t, 16>::mask_type& v)
{
    return x86::all_of_s16(v());
}

inline
bool cftal::any_of(const vec<uint16_t, 16>::mask_type& v)
{
    return x86::any_of_s16(v());
}

inline
bool cftal::none_of(const vec<uint16_t, 16>::mask_type& v)
{
    return x86::none_of_s16(v());
}

inline
cftal::v16u16 cftal::max(const v16u16& a, const v16u16& b)
{
#if defined (__SSE4_1__)
    return _mm256_max_epu16(a(), b());
#else
    v16u16::mask_type _gt(a > b);
    return select(_gt, a, b);
#endif
}

inline
cftal::v16u16 cftal::min(const v16u16& a, const v16u16& b)
{
#if defined (__SSE4_1__)
    return _mm256_min_epu16(a(), b());
#else
    v16u16::mask_type _lt(a < b);
    return select(_lt, a, b);
#endif
}

inline
cftal::v16u16 cftal::select(const v16u16::mask_type& m,
                           const v16u16& on_true,
                           const v16u16& on_false)
{
    return x86::select_u16(m(), on_true(), on_false());
}

inline
cftal::v16u16
cftal::select_val_or_zero(const v16u16::mask_type& m,
                          const v16u16& on_true)
{
    return _mm256_and_si256(m(), on_true());
}

inline
cftal::v16u16
cftal::select_zero_or_val(const v16u16::mask_type& m,
                          const v16u16& on_false)
{
    return _mm256_andnot_si256(m(), on_false());
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline
cftal::v16u16 cftal::select(const v16u16& a, const v16u16& b)
{
    return x86::select_u16<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15> (a(), b());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16u16 cftal::permute(const v16u16& a)
{
    return x86::perm_v16u16<_P00, _P01, _P02, _P03,
                            _P04, _P05, _P06, _P07,
                            _P08, _P09, _P10, _P11,
                            _P12, _P13, _P14, _P15>(a());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16u16 cftal::permute(const v16u16& a, const v16u16& b)
{
    return x86::perm_v16u16<_P00, _P01, _P02, _P03,
                            _P04, _P05, _P06, _P07,
                            _P08, _P09, _P10, _P11,
                            _P12, _P13, _P14, _P15>(a(), b());
}

inline
std::pair<cftal::v16u16, cftal::v16u16>
cftal::mul_lo_hi(const v16u16& x, const v16u16& y)
{
    v16u16 l= x*y;
    v16u16 h= x86::vpmulhuw::v(x(), y());
    return std::make_pair(l, h);
}

inline
cftal::vec<cftal::uint16_t, 16>
cftal::sat_add(const vec<uint16_t, 16>& a, const vec<uint16_t, 16>& b)
{
    return _mm256_adds_epu16(a(), b());
}

inline
cftal::vec<cftal::uint16_t, 16>
cftal::sat_sub(const vec<uint16_t, 16>& a, const vec<uint16_t, 16>& b)
{
    return _mm256_subs_epu16(a(), b());
}

inline
cftal::vec<cftal::uint16_t, 16>
cftal::average(const vec<uint16_t, 16>& a, const vec<uint16_t, 16>& b)
{
    return x86::pavgw::v(a(), b());
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V16U16_INL__
