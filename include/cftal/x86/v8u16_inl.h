//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_X86_V8U16_INL__)
#define __CFTAL_X86_V8U16_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v8u16.h>
#include <cftal/x86/v8s16.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmplt_epu16_mask(a(), b());
#else
                v8u16 ta(a ^ full_type(sign_s16_msk::v.u16()));
                v8u16 tb(b ^ full_type(sign_s16_msk::v.u16()));
                return _mm_cmpgt_epi16(tb(), ta());
#endif
            }
        };

        template <>
        struct le<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmple_epu16_mask(a(), b());
#else
#if defined (__SSE4_1__)
                // a<= b: a == min(a, b);
                __m128i min_ab = _mm_min_epu16(b(), a());
                return _mm_cmpeq_epi16(a(), min_ab);
#else
                return ~(a > b);
#endif
#endif
            }
        };

        template <>
        struct eq<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpeq_epu16_mask(a(), b());
#else
                return _mm_cmpeq_epi16(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpneq_epu16_mask(a(), b());
#else
                return ~(a == b);
#endif
            }
        };

        template <>
        struct ge<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpge_epu16_mask(a(), b());
#else
#if defined (__SSE4_1__)
                // a>= b: a == max(a, b);
                __m128i max_ab = _mm_max_epu16(b(), a());
                return _mm_cmpeq_epi16(a(), max_ab);
#else
                return ~(a < b);
#endif
#endif
            }
        };

        template <>
        struct gt<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpgt_epu16_mask(a(), b());
#else
                v8u16 ta(a ^ full_type(sign_s16_msk::v.u16()));
                v8u16 tb(b ^ full_type(sign_s16_msk::v.u16()));
                return _mm_cmpgt_epi16(ta(), tb());
#endif
            }
        };

        template <>
        struct plus<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s16_msk::v.u16());
                return _mm_sign_epi16(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi16(zero(), a());
#endif
            }
        };

        template <>
        struct add<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi16(a(), b());
            }
        };

        template <>
        struct sub<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi16(a(), b());
            }
        };

        template <>
        struct mul<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullw::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u16::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v8u16 q(a/b);
                v8u16 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint16_t, 8>>::v(
                    mul<vec<uint16_t, 8>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint16_t, 8>>::v(
                    mul<vec<uint16_t, 8>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint16_t, 8>>::v(
                    c, mul<vec<uint16_t, 8>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi16(a(), s);
            }
        };

        template <>
        struct shr<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi16(a(), s);
            }
        };

#if defined (__AVX2__)
        template <>
        struct vshl<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvw::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<uint16_t, 8>> {
            using full_type = vec<uint16_t, 8>;
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
cftal::vec<cftal::uint16_t, 8>::vec(const vec<int16_t, 8>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint16_t, 8>::vec(uint16_t v)
    : base_type(_mm_setr_epi16(v, v, v, v, v, v, v, v))
{
}


inline
cftal::vec<cftal::uint16_t, 8>::
vec(std::initializer_list<uint16_t> l)
    : vec(mem<vec<uint16_t, 8> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint16_t, 8>::
vec(init_list<uint16_t> l)
    : vec(mem<vec<uint16_t, 8> >::load(l.begin(), l.size()))
{
}

#if 1
inline
cftal::vec<uint16_t, 8>::
vec(const vec<uint16_t, 4>& lh, const vec<uint16_t, 4>& hh)
    : base_type(
        _mm_set_epi64x(reinterpret_cast<const uint64_t&>(hh),
                       reinterpret_cast<const uint64_t&>(lh)))
{
}

#else
inline
cftal::vec<uint16_t, 8>::
vec(const vec<uint16_t, 4>& lh, const vec<uint16_t, 4>& hh)
    : vec(permute<0, 1, 2, 3, 8, 9, 10, 11>(as<vec<uint16_t, 8> >(lh),
                                            as<vec<uint16_t, 8> >(hh)))
{
}
#endif

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint16_t, 8>::vec(const expr<_OP<vec<uint16_t, 8> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint16_t, 8>
cftal::mem<cftal::vec<uint16_t, 8> >::load(const uint16_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 8:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 7:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[6], p[6]);
        break;
    case 6:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[5], p[5]);
        break;
    case 5:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[4], p[4], p[4], p[4]);
        break;
    case 4:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[3],
                           p[3], p[3], p[3], p[3]);
        break;
    case 3:
        v = _mm_setr_epi16(p[0], p[1], p[2], p[2],
                           p[2], p[2], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_epi16(p[0], p[1], p[1], p[1],
                           p[1], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm_setr_epi16(p[0], p[0], p[0], p[0],
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
cftal::mem<cftal::vec<uint16_t, 8> >::store(uint16_t* p,
                                            const vec<uint16_t, 8>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::vec<uint16_t, 4>
cftal::low_half(const vec<uint16_t, 8>& v)
{
    auto t=x86::extract_u64<0>(v());
    return as<vec<uint16_t,4> >(t);
}

inline
cftal::vec<uint16_t, 4>
cftal::high_half(const vec<uint16_t, 8>& v)
{
    auto t=x86::extract_u64<1>(v());
    return as<vec<uint16_t,4> >(t);
}

template <cftal::size_t _I>
inline
cftal::uint16_t
cftal::extract(const vec<uint16_t, 8>& v)
{
    return x86::extract_u16<_I>(v());
}

inline
cftal::uint16_t
cftal::extract(const vec<uint16_t, 8>& v, size_t i)
{
    return x86::extract_u16(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint16_t, 8>& v, const uint16_t& vi)
{
    v= x86::insert_u16<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint16_t, 8>& v, const uint16_t& vi, size_t i)
{
    v= x86::insert_u16(v(), vi, i);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
inline
bool cftal::all_of(const vec<uint16_t, 8>::mask_type& v)
{
    return x86::all_of_s16(v());
}

inline
bool cftal::any_of(const vec<uint16_t, 8>::mask_type& v)
{
    return x86::any_of_s16(v());
}

inline
bool cftal::none_of(const vec<uint16_t, 8>::mask_type& v)
{
    return x86::none_of_s16(v());
}

inline
cftal::vec<cftal::bit, 8>
cftal::compress_mask(const vec<uint16_t, 8>::mask_type& v)
{
    return x86::compress_mask_u16(v());
}

inline
cftal::vec<uint16_t, 8>
cftal::expand_mask<cftal::vec<uint16_t, 8> >::
from(const vec<bit, 8>& s)
{
    return x86::expand_mask_v8u16(s());
}
#endif

inline
cftal::v8u16 cftal::max(const v8u16& a, const v8u16& b)
{
#if defined (__SSE4_1__)
    return _mm_max_epu16(a(), b());
#else
    v8u16::mask_type _gt(a > b);
    return select(_gt, a, b);
#endif
}

inline
cftal::v8u16 cftal::min(const v8u16& a, const v8u16& b)
{
#if defined (__SSE4_1__)
    return _mm_min_epu16(a(), b());
#else
    v8u16::mask_type _lt(a < b);
    return select(_lt, a, b);
#endif
}

inline
cftal::v8u16 cftal::select(const v8u16::mask_type& m,
                           const v8u16& on_true,
                           const v8u16& on_false)
{
    return x86::select_u16(m(), on_true(), on_false());
}

inline
cftal::v8u16
cftal::select_val_or_zero(const v8u16::mask_type& m,
                          const v8u16& on_true)
{
#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi8(m(), on_true());
#endif
}

inline
cftal::v8u16
cftal::select_zero_or_val(const v8u16::mask_type& m,
                          const v8u16& on_false)
{
#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi8(_knot_mask8(m()), on_false());
#endif
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8u16 cftal::select(const v8u16& a, const v8u16& b)
{
    return x86::select_u16<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7> (a(), b());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8u16 cftal::permute(const v8u16& a)
{
    return x86::perm_v8u16<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8u16 cftal::permute(const v8u16& a, const v8u16& b)
{
    return x86::perm_v8u16<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a(), b());
}

inline
cftal::vec<uint16_t, 8>
cftal::permute(const vec<uint16_t, 8>& s, const vec<int16_t, 8>& idx)
{
    return x86::permute_v8u16_v8s16(s(), idx());
}

inline
std::pair<cftal::v8u16, cftal::v8u16>
cftal::mul_lo_hi(const v8u16& x, const v8u16& y)
{
    v8u16 l= x*y;
    v8u16 h= x86::vpmulhuw::v(x(), y());
    return std::make_pair(l, h);
}

inline
cftal::vec<cftal::uint16_t, 8>
cftal::sat_add(const vec<uint16_t, 8>& a, const vec<uint16_t, 8>& b)
{
    return _mm_adds_epu16(a(), b());
}

inline
cftal::vec<cftal::uint16_t, 8>
cftal::sat_sub(const vec<uint16_t, 8>& a, const vec<uint16_t, 8>& b)
{
    return _mm_subs_epu16(a(), b());
}

inline
cftal::vec<cftal::uint16_t, 8>
cftal::average(const vec<uint16_t, 8>& a, const vec<uint16_t, 8>& b)
{
    return x86::pavgw::v(a(), b());
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8U16_INL__
