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
#if !defined (__CFTAL_X86_V16U8_INL__)
#define __CFTAL_X86_V16U8_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v16u8.h>
#include <cftal/x86/v16s8.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmplt_epu8_mask(a(), b());
#else
                v16u8 ta(a ^ full_type(sign_s8_msk::v.u8ll()));
                v16u8 tb(b ^ full_type(sign_s8_msk::v.u8ll()));
                return _mm_cmpgt_epi8(tb(), ta());
#endif
            }
        };

        template <>
        struct le<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmple_epu8_mask(a(), b());
#else
                // a<= b: a == min(a, b);
                __m128i min_ab = _mm_min_epu8(b(), a());
                return _mm_cmpeq_epi8(a(), min_ab);
#endif
            }
        };

        template <>
        struct eq<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpeq_epu8_mask(a(), b());
#else
                return _mm_cmpeq_epi8(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpneq_epu8_mask(a(), b());
#else
                return ~(a == b);
#endif
            }
        };

        template <>
        struct ge<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpge_epu8_mask(a(), b());
#else
                // a>= b: a == max(a, b);
                __m128i max_ab = _mm_max_epu8(b(), a());
                return _mm_cmpeq_epi8(a(), max_ab);
#endif
            }
        };

        template <>
        struct gt<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpgt_epu8_mask(a(), b());
#else
                v16u8 ta(a ^ full_type(sign_s8_msk::v.u8ll()));
                v16u8 tb(b ^ full_type(sign_s8_msk::v.u8ll()));
                return _mm_cmpgt_epi8(ta(), tb());
#endif
            }
        };

        template <>
        struct plus<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s8_msk::v.u8ll());
                return _mm_sign_epi8(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi8(zero(), a());
#endif
            }
        };

        template <>
        struct add<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi8(a(), b());
            }
        };

        template <>
        struct sub<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi8(a(), b());
            }
        };

        template <>
        struct mul<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullb::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u8::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v16u8 q(a/b);
                v16u8 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint8_t, 16>>::v(
                    mul<vec<uint8_t, 16>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint8_t, 16>>::v(
                    mul<vec<uint8_t, 16>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint8_t, 16>>::v(
                    c, mul<vec<uint8_t, 16>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllb::v(a(), s);
            }
        };

        template <>
        struct shr<vec<uint8_t, 16>> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsrlb::v(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::uint8_t, 16>::vec(const vec<int8_t, 16>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint8_t, 16>::vec(uint8_t v)
    : base_type(_mm_setr_epi8(v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v))
{
}


inline
cftal::vec<cftal::uint8_t, 16>::
vec(std::initializer_list<uint8_t> l)
    : vec(mem<vec<uint8_t, 16> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint8_t, 16>::
vec(init_list<uint8_t> l)
    : vec(mem<vec<uint8_t, 16> >::load(l.begin(), l.size()))
{
}

#if 1
inline
cftal::vec<uint8_t, 16>::
vec(const vec<uint8_t, 8>& lh, const vec<uint8_t, 8>& hh)
    : base_type(
        _mm_set_epi64x(reinterpret_cast<const uint64_t&>(hh),
                       reinterpret_cast<const uint64_t&>(lh)))
{
}

#else
inline
cftal::vec<uint8_t, 16>::
vec(const vec<uint8_t, 4>& lh, const vec<uint8_t, 4>& hh)
    : vec(permute<0, 1, 2, 3, 16, 9, 10, 11>(as<vec<uint8_t, 16> >(lh),
                                            as<vec<uint8_t, 16> >(hh)))
{
}
#endif

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint8_t, 16>::vec(const expr<_OP<vec<uint8_t, 16> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint8_t, 16>
cftal::mem<cftal::vec<uint8_t, 16> >::load(const uint8_t* p, ssize_t s)
{
    vec<uint8_t, 16> v;
    if (s>=16) {
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
    } else if (s==8) {
        uint32_t l64=*reinterpret_cast<const uint64_t*>(p);
        v = _mm_cvtsi64_si128(l64);
    } else if (s==4) {
        uint32_t l32=*reinterpret_cast<const uint32_t*>(p);
        v = _mm_cvtsi32_si128(l32);
    } else if (s==2) {
        uint16_t l16=*reinterpret_cast<const uint16_t*>(p);
        uint32_t l32=l16;
        v = _mm_cvtsi32_si128(l32);
    } else if (s==1) {
        uint8_t l8=*p;
        uint32_t l32=l8;
        v = _mm_cvtsi32_si128(l32);
    } else if (s==0) {
        v = _mm_setr_epi32(0, 0, 0, 0);
    } else {
        auto lh=mem<vec<uint8_t, 8> >::load(p, s);
        ssize_t sh= s>=8 ? s-8 : 0;
        auto hh=mem<vec<uint8_t, 8> >::load(p+8, sh);
        v = vec<uint8_t, 16>(lh, hh);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint8_t, 16> >::
store(uint8_t* p, const vec<uint8_t, 16>& v, ssize_t s)
{
    if (s>=16) {
        _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
    } else if (s==8) {
        _mm_storeu_si64(p, v());
    } else if (s==4) {
        _mm_storeu_si32(p, v());
    } else if (s==2) {
        _mm_storeu_si16(p, v());
    } else if (s==1) {
        uint32_t t=_mm_cvtsi128_si32(v()) & 0xff;
        *p=t;
    } else if (s!=0) {
        mem<vec<uint8_t, 8> >::store(p, s);
        ssize_t sh= s>=8 ? s-8 : 0;
        mem<vec<uint8_t, 8> >::store(p+8, sh);
    }
}

inline
cftal::vec<uint8_t, 8>
cftal::low_half(const vec<uint8_t, 16>& v)
{
    auto t=x86::extract_u64<0>(v());
    return as<vec<uint8_t, 8> >(t);
}

inline
cftal::vec<uint8_t, 8>
cftal::high_half(const vec<uint8_t, 16>& v)
{
    auto t=x86::extract_u64<1>(v());
    return as<vec<uint8_t, 8> >(t);
}

template <cftal::size_t _I>
inline
cftal::uint8_t
cftal::extract(const vec<uint8_t, 16>& v)
{
    return x86::extract_u8<_I>(v());
}

inline
cftal::uint8_t
cftal::extract(const vec<uint8_t, 16>& v, size_t i)
{
    return x86::extract_u8(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint8_t, 16>& v, const uint8_t& vi)
{
    v = x86::insert_u8<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint8_t, 16>& v, const uint8_t& vi, size_t i)
{
    v = x86::insert_u8(v(), vi, i);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
inline
bool cftal::all_of(const vec<uint8_t, 16>::mask_type& v)
{
    return x86::all_of_s8(v());
}

inline
bool cftal::any_of(const vec<uint8_t, 16>::mask_type& v)
{
    return x86::any_of_s8(v());
}

inline
bool cftal::none_of(const vec<uint8_t, 16>::mask_type& v)
{
    return x86::none_of_s8(v());
}

inline
cftal::vec<cftal::bit, 16>
cftal::compress_mask(const vec<uint8_t, 16>::mask_type& v)
{
    return x86::compress_mask_u8(v());
}

inline
cftal::vec<cftal::uint8_t, 16>
cftal::expand_mask<cftal::vec<uint8_t, 16> >::
from(const vec<bit, 16>& s)
{
    return x86::expand_mask_v16u8(s());
}
#endif

inline
cftal::v16u8 cftal::max(const v16u8& a, const v16u8& b)
{
    return _mm_max_epu8(a(), b());
}

inline
cftal::v16u8 cftal::min(const v16u8& a, const v16u8& b)
{
    return _mm_min_epu8(a(), b());
}

inline
cftal::v16u8 cftal::select(const v16u8::mask_type& m,
                           const v16u8& on_true,
                           const v16u8& on_false)
{
    return x86::select_u8(m(), on_true(), on_false());
}

inline
cftal::v16u8
cftal::select_val_or_zero(const v16u8::mask_type& m,
                          const v16u8& on_true)
{
#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi8(m(), on_true());
#endif
}

inline
cftal::v16u8
cftal::select_zero_or_val(const v16u8::mask_type& m,
                          const v16u8& on_false)
{
#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi8(_knot_mask16(m()), on_false());
#endif
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline
cftal::v16u8 cftal::select(const v16u8& a, const v16u8& b)
{
    return x86::select_u8<_P00, _P01, _P02, _P03,
                          _P04, _P05, _P06, _P07,
                          _P08, _P09, _P10, _P11,
                          _P12, _P13, _P14, _P15> (a(), b());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16u8 cftal::permute(const v16u8& a)
{
    return x86::perm_v16u8<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15>(a());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16u8 cftal::permute(const v16u8& a, const v16u8& b)
{
    return x86::perm_v16u8<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15>(a(), b());
}

inline
cftal::vec<uint8_t, 16>
cftal::permute(const vec<uint8_t, 16>& s, const vec<int8_t, 16>& idx)
{
    return x86::permute_v16u8_v16s8(s(), idx());
}

inline
std::pair<cftal::v16u8, cftal::v16u8>
cftal::mul_lo_hi(const v16u8& x, const v16u8& y)
{
    __m128i ox=_mm_srli_epi16(x(), 8);
    __m128i oy=_mm_srli_epi16(y(), 8);
    __m128i po=_mm_mullo_epi16(ox, oy);

    const __m128i even_mask = x86::const_v16u8<0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00,
                                               0xff, 0x00, 0xff, 0x00>::iv();
    __m128i ex=_mm_and_si128(x(), even_mask);
    __m128i ey=_mm_and_si128(y(), even_mask);
    __m128i pe=_mm_mullo_epi16(ex, ey);
    // combine low part of the products
    __m128i pol=_mm_slli_epi16(po, 8);
    __m128i pel=_mm_and_si128(pe, even_mask);
    __m128i l=_mm_or_si128(pol, pel);
    // combine high part of the products
    const __m128i odd_mask = x86::const_v16u8<0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff,
                                              0x00, 0xff, 0x00, 0xff>::iv();
    __m128i poh=_mm_and_si128(po, odd_mask);
    __m128i peh=_mm_srli_epi16(pe, 8);
    __m128i h=_mm_or_si128(poh, peh);
    return std::make_pair(l, h);
}

inline
cftal::vec<cftal::uint8_t, 16>
cftal::sat_add(const vec<uint8_t, 16>& a, const vec<uint8_t, 16>& b)
{
    return _mm_adds_epu8(a(), b());
}

inline
cftal::vec<cftal::uint8_t, 16>
cftal::sat_sub(const vec<uint8_t, 16>& a, const vec<uint8_t, 16>& b)
{
    return _mm_subs_epu8(a(), b());
}

inline
cftal::vec<cftal::uint8_t, 16>
cftal::average(const vec<uint8_t, 16>& a, const vec<uint8_t, 16>& b)
{
    return x86::pavgb::v(a(), b());
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8U16_INL__
