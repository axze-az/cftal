//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
        struct bit_not<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v16u8 ta(a ^ full_type(sign_s8_msk::v.u8ll()));
                v16u8 tb(b ^ full_type(sign_s8_msk::v.u8ll()));
                return _mm_cmpgt_epi8(tb(), ta());
            }
        };

        template <>
        struct le<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                // a<= b: a == min(a, b);
                __m128i min_ab = _mm_min_epu8(b(), a());
                return _mm_cmpeq_epi8(a(), min_ab);
            }
        };

        template <>
        struct eq<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_epi16(a(), b());
            }
        };

        template <>
        struct ne<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a == b);
            }
        };

        template <>
        struct ge<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                // a>= b: a == max(a, b);
                __m128i max_ab = _mm_max_epu8(b(), a());
                return _mm_cmpeq_epi8(a(), max_ab);
            }
        };

        template <>
        struct gt<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                v16u8 ta(a ^ full_type(sign_s8_msk::v.u8ll()));
                v16u8 tb(b ^ full_type(sign_s8_msk::v.u8ll()));
                return _mm_cmpgt_epi16(ta(), tb());
            }
        };

        template <>
        struct plus<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<uint8_t, 16> {
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
        struct add<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi8(a(), b());
            }
        };

        template <>
        struct sub<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi8(a(), b());
            }
        };

        template <>
        struct mul<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullb::v(a(), b());
            }
        };

        template <>
        struct div<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u8::v(a(), b());
            }
        };

        template <>
        struct mod<uint8_t, 16> {
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
        struct fma<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<uint8_t, 16>::v(
                    mul<uint8_t, 16>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<uint8_t, 16>::v(
                    mul<uint8_t, 16>::v(a , b), c);
            }
        };

        template <>
        struct fnma<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<uint8_t, 16>::v(
                    c, mul<uint8_t, 16>::v(a, b));

            }
        };

        template <>
        struct bit_or<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<uint8_t, 16> {
            using full_type = vec<uint8_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllb::v(a(), s);
            }
        };

        template <>
        struct shr<uint8_t, 16> {
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

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint8_t, 16>::vec(const expr<_OP<uint8_t, 16>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint8_t, 16>
cftal::mem<cftal::vec<uint8_t, 16> >::load(const uint8_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 16:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 15:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[9], p[10], p[11],
                          p[12], p[13], p[14], p[14]);
        break;
    case 14:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[9], p[10], p[11],
                          p[12], p[13], p[13], p[13]);
        break;
    case 13:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[9], p[10], p[11],
                          p[12], p[12], p[12], p[12]);
        break;
    case 12:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[9], p[10], p[11],
                          p[11], p[11], p[11], p[11]);
        break;
    case 11:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[9], p[10], p[10],
                          p[10], p[10], p[10], p[10]);
        break;
    case 10:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[9], p[9], p[9],
                          p[9], p[9], p[9], p[9]);
        break;
    case 9:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[8], p[8], p[8], p[8],
                          p[8], p[8], p[8], p[8]);
        break;
    case 8:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[7],
                          p[7], p[7], p[7], p[7],
                          p[7], p[7], p[7], p[7]);
        break;
    case 7:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[6], p[6],
                          p[6], p[6], p[6], p[6],
                          p[6], p[6], p[6], p[6]);
        break;
    case 6:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[5], p[5], p[5],
                          p[5], p[5], p[5], p[5],
                          p[5], p[5], p[5], p[5]);
        break;
    case 5:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[4], p[4], p[4], p[4],
                          p[4], p[4], p[4], p[4],
                          p[4], p[4], p[4], p[4]);
        break;
    case 4:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[3],                           
                          p[3], p[3], p[3], p[3],
                          p[3], p[3], p[3], p[3],
                          p[3], p[3], p[3], p[3]);
        break;
    case 3:
        v = _mm_setr_epi8(p[0], p[1], p[2], p[2],                           
                          p[2], p[2], p[2], p[2],
                          p[2], p[2], p[2], p[2],
                          p[2], p[2], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_epi8(p[0], p[1], p[1], p[1],                           
                          p[1], p[1], p[1], p[1],
                          p[1], p[1], p[1], p[1],
                          p[1], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm_setr_epi8(p[0], p[0], p[0], p[0],                           
                          p[0], p[0], p[0], p[0],
                          p[0], p[0], p[0], p[0],
                          p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_epi32(0, 0, 0, 0);
        break;        
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint8_t, 16> >::store(uint8_t* p,
                                            const vec<uint8_t, 16>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::vec<uint8_t, 8>
cftal::low_half(const vec<uint8_t, 16>& v)
{
    return as<vec<uint8_t,8> >(v);
}

inline
cftal::vec<uint8_t, 8>
cftal::high_half(const vec<uint8_t, 16>& v)
{
    vec<uint8_t, 16> h=permute<8, 9, 10, 11, 12, 13, 14, 15, 
                               0, 1, 2, 3, 4, 5, 6, 7>(v);
    return as<vec<uint8_t, 8> >(h);
}

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
    return x86::select_u16(m(), on_true(), on_false());
}

inline
cftal::v16u8
cftal::select_val_or_zero(const v16u8::mask_type& m,
                          const v16u8& on_true)
{
    return _mm_and_si128(m(), on_true());
}

inline
cftal::v16u8
cftal::select_zero_or_val(const v16u8::mask_type& m,
                          const v16u8& on_false)
{
    return _mm_andnot_si128(m(), on_false());
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
