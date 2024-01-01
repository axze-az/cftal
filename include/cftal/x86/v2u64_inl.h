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
#if !defined (__CFTAL_X86_V2U64_INL__)
#define __CFTAL_X86_V2U64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v2u64.h>
#include <cftal/x86/v2s64.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffffffffffffULL);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmplt_epu64_mask(a(), b());
#else
                return b > a;
#endif
            }
        };

        template <>
        struct le<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmple_epu64_mask(a(), b());
#else
                return ~(a > b);
#endif
            }
        };

        template <>
        struct eq<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpeq_epu64_mask(a(), b());
#else
		return x86::vpcmpeqq::v(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpneq_epu64_mask(a(), b());
#else
                return ~(a==b);
#endif
            }
        };

        template <>
        struct ge<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpge_epu64_mask(a(), b());
#else
                return ~(a < b);
#endif
            }
        };

        template <>
        struct gt<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpgt_epu64_mask(a(), b());
#else
#if defined (__SSE4_2__)
                const __m128i msk= _mm_set1_epi64x(sign_s64_msk::v.u64());
                __m128i ax= _mm_xor_si128(a(), msk);
                __m128i bx= _mm_xor_si128(b(), msk);
                __m128i r=_mm_cmpgt_epi64(ax, bx);
                return r;
#else
                // a > b: (a_h > b_h) || ((a_h == b_h) && (a_l > b_l))
                // c1 ---------^
                // c2 -------------------------^
                // c3 -----------------------------------------^
                const __m128i msk= _mm_set1_epi32(sign_s32_msk::v.u32());
                __m128i ax= _mm_xor_si128(a(), msk);
                __m128i bx= _mm_xor_si128(b(), msk);
                __m128i c2= _mm_cmpeq_epi32(a(), b());
                __m128i c1c3= _mm_cmpgt_epi32(ax, bx);
                // only elements 1, 3 are valid:
                __m128i c2_and_c3 =
                    _mm_and_si128(c2,
                                  x86::vpshufd<0, 0, 2, 2>::v(c1c3));
                // only elements 1, 3 are valid.
                __m128i r = _mm_or_si128(c1c3, c2_and_c3);
                r = x86::vpshufd< 1, 1, 3, 3>::v(r);
                return r;
#endif
#endif

            }
        };

        template <>
        struct plus<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u64::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2u64 q(a/b);
                v2u64 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint64_t, 2>>::v(
                    mul<vec<uint64_t, 2>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint64_t, 2>>::v(
                    mul<vec<uint64_t, 2>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint64_t, 2>>::v(
                    c, mul<vec<uint64_t, 2>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsrlq::v(a(), s);
            }
        };

        template <>
        struct vshl<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvq::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<uint64_t, 2>> {
            using full_type = vec<uint64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsrlvq::v(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::uint64_t, 2>::vec(const vec<int64_t, 2>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint64_t, 2>::vec(uint64_t v)
    : base_type(_mm_set_epi64x(v, v))
{
}


inline
cftal::vec<cftal::uint64_t, 2>::
vec(std::initializer_list<uint64_t> l)
    : vec(mem<vec<uint64_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint64_t, 2>::
vec(init_list<uint64_t> l)
    : vec(mem<vec<uint64_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint64_t, 2>::
vec(const vec<uint64_t, 1>& lh, const vec<uint64_t, 1>& hh)
    : base_type(_mm_set_epi64x(hh(), lh()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint64_t, 2>::vec(const expr<_OP<vec<uint64_t, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint64_t, 2>
cftal::mem<cftal::vec<uint64_t, 2> >::load(const uint64_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 2:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 1:
        v = _mm_set_epi64x(p[0], p[0]);
        break;
    case 0:
        v = _mm_set_epi64x(0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint64_t, 2> >::store(uint64_t* p,
                                            const vec<uint64_t, 2>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::vec<uint64_t, 1>
cftal::low_half(const vec<uint64_t, 2>& v)
{
    return vec<uint64_t, 1>(extract<0>(v));
}

inline
cftal::vec<uint64_t, 1>
cftal::high_half(const vec<uint64_t, 2>& v)
{
    return vec<uint64_t, 1>(extract<1>(v));
}

template <cftal::size_t _I>
inline
cftal::uint64_t
cftal::extract(const vec<uint64_t, 2>& v)
{
    return x86::extract_u64<_I>(v());
}

inline
cftal::uint64_t
cftal::extract(const vec<uint64_t, 2>& v, size_t i)
{
    return x86::extract_u64(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint64_t, 2>& v, const uint64_t& vi)
{
    v= x86::insert_u64<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint64_t, 2>& v, const uint64_t& vi, size_t i)
{
    v= x86::insert_u64(v(), vi, i);
}

inline
cftal::v2u64 cftal::max(const v2u64& a, const v2u64& b)
{
    v2u64::mask_type _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v2u64 cftal::min(const v2u64& a, const v2u64& b)
{
    v2u64::mask_type _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v2u64 cftal::select(const v2u64::mask_type& m,
                           const v2u64& on_true,
                           const v2u64& on_false)
{
    return x86::select_u64(m(), on_true(), on_false());
}

inline
cftal::v2u64
cftal::select_val_or_zero(const v2u64::mask_type& m,
                          const v2u64& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi64(m(), on_true());
#endif
}

inline
cftal::v2u64
cftal::select_zero_or_val(const v2u64::mask_type& m,
                          const v2u64& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi64(_knot_mask8(m()), on_false());
#endif
}

template <bool _I0, bool _I1>
inline
cftal::v2u64 cftal::select(const v2u64& a, const v2u64& b)
{
    return x86::select_u64<_I0, _I1>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2u64 cftal::permute(const v2u64& a)
{
    return x86::perm_v2u64<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2u64 cftal::permute(const v2u64& a, const v2u64& b)
{
    return x86::perm_v2u64<_I0, _I1>(a(), b());
}

inline
cftal::v2u64 cftal::permute(const v2u64& s, const v2s64& idx)
{
    return x86::permute_v2u64_v2s64(s(), idx());
}

inline
std::pair<cftal::v2u64, cftal::v2u64>
cftal::mul_lo_hi(const v2u64& x, const v2u64& y)
{
    //         0         0 (xl_yl)_h  (xl_yl)_l
    //         0 (xh_yl)_h (xh_yl)_l          0
    //         0 (xl_yh)_h (xl_yh)_l          0
    // (xh_yh)_h (xh_yh)_l
    v2u64 xh = x >> 32;
    v2u64 yh = y >> 32;
    // 2^ 0
    v2u64 xl_yl= _mm_mul_epu32(x(), y());
    // 2^ 32
    v2u64 xl_yh= _mm_mul_epu32(x(), yh());
    v2u64 xh_yl= _mm_mul_epu32(xh(), y());
    // 2^ 64
    v2u64 xh_yh= _mm_mul_epu32(xh(), yh());
    // sum of 2^32
    v2u64 s32_95 = xl_yh + xh_yl;
    v2u64::mask_type carry_96 = s32_95 < xl_yh;
    //
    v2u64 s64_96 = s32_95 >> 32;
    v2u64 s32_63 = s32_95 << 32;
    // low part of the multiplication:
    xl_yl += s32_63;
    v2u64::mask_type neg_carry_64 = xl_yl < s32_63;
    v2u64 c96_msk(bytes8(0, 1).u64());

    s64_96 |= select(carry_96, c96_msk, v2u64(0));
    xh_yh -= select(neg_carry_64, v2u64(-1LL), v2u64(0));
    // high part of the multiplication:
    xh_yh += s64_96;
    return std::make_pair(xl_yl, xh_yh);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<uint64_t, 2>::mask_type& v)
{
    return x86::all_of_s64(v());
}

inline
bool cftal::any_of(const vec<uint64_t, 2>::mask_type& v)
{
    return x86::any_of_s64(v());
}

inline
bool cftal::none_of(const vec<uint64_t, 2>::mask_type& v)
{
    return x86::none_of_s64(v());
}

inline
cftal::vec<cftal::bit, 2>
cftal::compress_mask(const vec<uint64_t, 2>::mask_type& v)
{
    return x86::compress_mask_u64(v());
}

inline
cftal::vec<uint64_t, 2>
cftal::expand_mask<cftal::vec<uint64_t, 2> >::
from(const vec<bit, 2>& s)
{
    return x86::expand_mask_v2u64(s());
}

#endif


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U64_INL__
