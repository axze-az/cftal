//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_X86_V32S8_INL__)
#define __CFTAL_X86_V32S8_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v32s8.h>
#include <cftal/x86/v32u8.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xff);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        template <>
        struct lt<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpgt_epi8(b(), a());
            }
        };

        template <>
        struct le<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                __m256i min_ab = _mm256_min_epi8(b(), a());
                return _mm256_cmpeq_epi8(a(), min_ab);
            }
        };

        template <>
        struct eq<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpeq_epi8(a(), b());
            }
        };

        template <>
        struct ne<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<vec<int8_t, 32>>::v(a, b));
                return bit_not<vec<int8_t, 32>>::v(a_eq_b);
            }
        };

        template <>
        struct ge<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                // a>= b: a == max(a, b);
                __m256i max_ab = _mm256_max_epi8(b(), a());
                return _mm256_cmpeq_epi8(a(), max_ab);
            }
        };

        template <>
        struct gt<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpgt_epi8(a(), b());
            }
        };

        template <>
        struct plus<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a) {
                const full_type sgn(0x80);
                return _mm256_sign_epi8(a(), sgn());
            }
        };

        template <>
        struct add<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi8(a(), b());
            }
        };

        template <>
        struct sub<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi8(a(), b());
            }
        };

        template <>
        struct mul<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullb::v(a(), b());
            }
        };

        template <>
        struct div<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s8::v(a(), b());
            }
        };

        template <>
        struct mod<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                full_type q(a/b);
                full_type r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int8_t, 32>>::v(
                    mul<vec<int8_t, 32>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int8_t, 32>>::v(
                    mul<vec<int8_t, 32>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int8_t, 32>>::v(
                    c, mul<vec<int8_t, 32>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllb::v(a(), s);
            }
        };

        template <>
        struct shr<vec<int8_t, 32>> {
            using full_type = vec<int8_t, 32>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsrab::v(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int8_t, 32>::vec(const vec<uint8_t, 32>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int8_t, 32>::vec(int8_t v)
    : base_type(_mm256_set1_epi8(v))
{
}

inline
cftal::vec<cftal::int8_t, 32>::
vec(std::initializer_list<int8_t> l)
    : vec(mem<v32s8>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int8_t, 32>::
vec(init_list<int8_t> l)
    : vec(mem<v32s8>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<int8_t, 32>::
vec(const vec<int8_t, 16>& lh, const vec<int8_t, 16>& hh)
    : base_type(_mm256_setr_m128i(lh(), hh()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int8_t, 32>::vec(const expr<_OP<vec<int8_t, 32> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int8_t, 32>
cftal::mem<cftal::vec<int8_t, 32> >::load(const int8_t* p, std::size_t s)
{
    __m256i v;
    switch (s) {
    case 32:
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
        break;
    case 0:
        v = _mm256_set1_epi32(0);
        break;
    default: {
            x86::vecunion<int8_t, 32, __m256, __m256d, __m256i> st;
            std::uint32_t si=s & 31;
            int8_t pi=p[0];
            st._s[0]=pi;
            for (uint32_t i=1; i<si; ++i) {
                pi=p[i];
                st._s[i]=pi;
            }
            for (uint32_t i=si; i<32; ++i) {
                st._s[i]=pi;
            }
            v=_mm256_loadu_si256(&st._vi);
            break;
    }}
    return v;
}

inline
void
cftal::mem<cftal::vec<int8_t, 32> >::store(int8_t* p,
                                           const vec<int8_t, 32>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::vec<int8_t, 16>
cftal::low_half(const vec<int8_t, 32>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<int8_t, 16>
cftal::high_half(const vec<int8_t, 32>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

template <cftal::size_t _I>
inline
cftal::int8_t
cftal::extract(const vec<int8_t, 32>& v)
{
    return x86::extract_u8<_I>(v());
}

inline
cftal::int8_t
cftal::extract(const vec<int8_t, 32>& v, size_t i)
{
    return x86::extract_u8(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<int8_t, 32>& v, const int8_t& vi)
{
    v = x86::insert_u8<_I>(v(), vi);
}

inline
void
cftal::insert(vec<int8_t, 32>& v, const int8_t& vi, size_t i)
{
    v = x86::insert_u8(v(), vi, i);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
inline
bool cftal::all_of(const vec<int8_t, 32>::mask_type& v)
{
    return x86::all_of_s8(v());
}

inline
bool cftal::any_of(const vec<int8_t, 32>::mask_type& v)
{
    return x86::any_of_s8(v());
}

inline
bool cftal::none_of(const vec<int8_t, 32>::mask_type& v)
{
    return x86::none_of_s8(v());
}

inline
cftal::vec<cftal::bit, 32>
cftal::compress_mask(const vec<int8_t, 32>::mask_type& v)
{
    return x86::compress_mask_u8(v());
}

inline
cftal::vec<int8_t, 32>
cftal::expand_mask<cftal::vec<int8_t, 32> >::
from(const vec<bit, 32>& s)
{
    return x86::expand_mask_v32u8(s());
}
#endif

inline
cftal::v32s8 cftal::max(const v32s8& a, const v32s8& b)
{
    return _mm256_max_epi8(a(), b());
}

inline
cftal::v32s8 cftal::min(const v32s8& a, const v32s8& b)
{
    return _mm256_min_epi8(a(), b());
}

inline
cftal::v32s8 cftal::abs(const v32s8& a)
{
    return _mm256_abs_epi8(a());
}

inline
cftal::v32s8 cftal::select(const v32s8::mask_type& m,
                           const v32s8& on_true,
                           const v32s8& on_false)
{
    return x86::select_u8(m(), on_true(), on_false());
}

inline
cftal::v32s8
cftal::select_val_or_zero(const v32s8::mask_type& m,
                          const v32s8& on_true)
{
    return _mm256_and_si256(m(), on_true());
}

inline
cftal::v32s8
cftal::select_zero_or_val(const v32s8::mask_type& m,
                          const v32s8& on_false)
{
    return _mm256_andnot_si256(m(), on_false());
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
	      bool _P04, bool _P05, bool _P06, bool _P07,
	      bool _P08, bool _P09, bool _P10, bool _P11,
	      bool _P12, bool _P13, bool _P14, bool _P15,
	      bool _P16, bool _P17, bool _P18, bool _P19,
	      bool _P20, bool _P21, bool _P22, bool _P23,
	      bool _P24, bool _P25, bool _P26, bool _P27,
	      bool _P28, bool _P29, bool _P30, bool _P31>
inline
cftal::v32s8 cftal::select(const v32s8& a, const v32s8& b)
{
    return x86::select_u8<_P00, _P01, _P02, _P03,
                          _P04, _P05, _P06, _P07,
                          _P08, _P09, _P10, _P11,
                          _P12, _P13, _P14, _P15,
                          _P16, _P17, _P18, _P19,
                          _P20, _P21, _P22, _P23,
                          _P24, _P25, _P26, _P27,
                          _P28, _P29, _P30, _P31>(a(), b());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15,
          int32_t _P16, int32_t _P17, int32_t _P18, int32_t _P19,
          int32_t _P20, int32_t _P21, int32_t _P22, int32_t _P23,
          int32_t _P24, int32_t _P25, int32_t _P26, int32_t _P27,
          int32_t _P28, int32_t _P29, int32_t _P30, int32_t _P31>
inline
cftal::v32s8 cftal::permute(const v32s8& a)
{
    return x86::perm_v32u8<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15,
                           _P16, _P17, _P18, _P19,
                           _P20, _P21, _P22, _P23,
                           _P24, _P25, _P26, _P27,
                           _P28, _P29, _P30, _P31>(a());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15,
          int32_t _P16, int32_t _P17, int32_t _P18, int32_t _P19,
          int32_t _P20, int32_t _P21, int32_t _P22, int32_t _P23,
          int32_t _P24, int32_t _P25, int32_t _P26, int32_t _P27,
          int32_t _P28, int32_t _P29, int32_t _P30, int32_t _P31>
inline
cftal::v32s8 cftal::permute(const v32s8& a, const v32s8& b)
{
    return x86::perm_v32u8<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15,
                           _P16, _P17, _P18, _P19,
                           _P20, _P21, _P22, _P23,
                           _P24, _P25, _P26, _P27,
                           _P28, _P29, _P30, _P31>(a(), b());
}

inline
std::pair<cftal::v32s8, cftal::v32s8>
cftal::mul_lo_hi(const v32s8& x, const v32s8& y)
{
    __m256i ox=_mm256_srai_epi16(x(), 8);
    __m256i oy=_mm256_srai_epi16(y(), 8);
    __m256i po=_mm256_mullo_epi16(ox, oy);

    const __m256i even_mask = x86::const_v32u8<0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00>::iv();
    __m256i ex=_mm256_srai_epi16(_mm256_slli_epi16(x(), 8), 8);
    __m256i ey=_mm256_srai_epi16(_mm256_slli_epi16(y(), 8), 8);
    __m256i pe=_mm256_mullo_epi16(ex, ey);
    // combine low part of the products
    __m256i pol=_mm256_slli_epi16(po, 8);
    __m256i pel=_mm256_and_si256(pe, even_mask);
    __m256i l=_mm256_or_si256(pol, pel);
    // combine high part of the products
    const __m256i odd_mask = x86::const_v32u8<0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff>::iv();
    __m256i poh=_mm256_and_si256(po, odd_mask);
    __m256i peh=_mm256_srli_epi16(pe, 8);
    __m256i h=_mm256_or_si256(poh, peh);
    return std::make_pair(l, h);
}

inline
cftal::vec<cftal::int8_t, 32>
cftal::sat_add(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b)
{
    return _mm256_adds_epi8(a(), b());
}

inline
cftal::vec<cftal::int8_t, 32>
cftal::sat_sub(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b)
{
    return _mm256_subs_epi8(a(), b());
}

inline
cftal::vec<cftal::int8_t, 32>
cftal::average(const vec<int8_t, 32>& a, const vec<int8_t, 32>& b)
{
    return x86::pavgsb::v(a(), b());
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V32S8_INL_H__
