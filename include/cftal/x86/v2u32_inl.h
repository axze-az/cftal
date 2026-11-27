//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_X86_V2U32_INL_H__)
#define __CFTAL_X86_V2U32_INL_H__ 1

#include <cftal/config.h>

#if __CFTAL_CFG_USE_8_BYTE_VECS_ON_X86__ > 0

#include <cftal/types.h>
#include <cftal/x86/v2u32.h>
#include <cftal/x86/v4s32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_LT_OS & 7);
#else
                v2u32 ta(a ^ full_type(sign_s32_msk::v.u32()));
                v2u32 tb(b ^ full_type(sign_s32_msk::v.u32()));
                return _mm_cmpgt_epi32(tb(), ta());
#endif
            }
        };

        template <>
        struct le<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_LE_OS & 7);
#else
#if defined (__SSE4_1__)
                // a<= b: a == min(a, b);
                __m128i min_ab = _mm_min_epu32(b(), a());
                return _mm_cmpeq_epi32(a(), min_ab);
#else
                return ~(a > b);
#endif
#endif
            }
        };

        template <>
        struct eq<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_EQ_OQ & 7);
#else
                return _mm_cmpeq_epi32(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_UNORD_Q & 7);
#else
                return ~(a==b);
#endif
            }
        };

        template <>
        struct ge<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_GE_OS & 7);
#else
#if defined (__SSE4_1__)
                // a>= b: a == max(a, b);
                __m128i max_ab = _mm_max_epu32(b(), a());
                return _mm_cmpeq_epi32(a(), max_ab);
#else
                return ~(a < b);
#endif
#endif
            }
        };

        template <>
        struct gt<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_GT_OS & 7);
#else
                v2u32 ta(a ^ full_type(sign_s32_msk::v.u32()));
                v2u32 tb(b ^ full_type(sign_s32_msk::v.u32()));
                return _mm_cmpgt_epi32(ta(), tb());
#endif
            }
        };

        template <>
        struct plus<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v.u32());
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u32::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2u32 q=div<full_type>::v(a, b);
                v2u32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint32_t, 2>>::v(
                    mul<vec<uint32_t, 2>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint32_t, 2>>::v(
                    mul<vec<uint32_t, 2>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint32_t, 2>>::v(
                    c, mul<vec<uint32_t, 2>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };

        template <>
        struct vshl<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                // return _mm_sllv_epi32(a(), s());
                return x86::vpsllvd::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<uint32_t, 2>> {
            using full_type = vec<uint32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsrlvd::v(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::uint32_t, 2>::vec(__m128i v)
    : _v(v)
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(const vec<int32_t, 2>& v)
    : _v(v())
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(uint32_t v)
    : _v(v, v)
{
}

inline
cftal::vec<cftal::uint32_t, 2>::vec(vec<uint32_t, 1> l, vec<uint32_t, 1> h)
    : _v(_mm_setr_epi32(l(), h(), 0, 0))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::
vec(std::initializer_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint32_t, 2>::
vec(init_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 2> >::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint32_t, 2>::vec(const expr<_OP<vec<uint32_t, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint32_t, 2>
cftal::mem<cftal::vec<uint32_t, 2> >::load(const uint32_t* p, ssize_t s)
{
    __m128i v;
    if (s>=2) {
        v = _mm_setr_epi32(p[0], p[1], 0, 0);
    } else if (s==1) {
        v = _mm_loadu_si32(p);
    } else {
        v = _mm_setr_epi32(0, 0, 0, 0);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint32_t, 2> >::
store(uint32_t* p, const vec<uint32_t, 2>& v, ssize_t s)
{
    if (s>=2) {
        _mm_storeu_si64(p, v());
    } else if (s==1) {
        _mm_storeu_si32(p, v());
    }
}

inline
cftal::vec<uint32_t, 1>
cftal::low_half(const vec<uint32_t, 2>& v)
{
    auto t=x86::extract_u32<0>(v());
    return vec<uint32_t, 1>(t);
}

inline
cftal::vec<uint32_t, 1>
cftal::high_half(const vec<uint32_t, 2>& v)
{
    auto t=x86::extract_u32<1>(v());
    return vec<uint32_t, 1>(t);
}

template <cftal::size_t _I>
inline
cftal::uint32_t
cftal::extract(const vec<uint32_t, 2>& v)
{
    return x86::extract_u32<_I>(v());
}

inline
cftal::uint32_t
cftal::extract(const vec<uint32_t, 2>& v, size_t i)
{
    return x86::extract_u32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint32_t, 2>& v, const uint32_t& vi)
{
    v= x86::insert_u32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint32_t, 2>& v, const uint32_t& vi, size_t i)
{
    v= x86::insert_u32(v(), vi, i);
}


#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<uint32_t, 2>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<uint32_t, 2>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<uint32_t, 2>::mask_type& v)
{
    return x86::none_of_s32(v());
}

inline
cftal::vec<cftal::bit, 2>
cftal::compress_mask(const vec<uint32_t, 2>::mask_type& v)
{
    return x86::compress_mask_u32(v());
}

inline
cftal::vec<uint32_t, 2>
cftal::expand_mask<cftal::vec<uint32_t, 2> >::
from(const vec<bit, 2>& s)
{
    return x86::expand_mask_v4u32(s());
}

#endif

inline
cftal::v2u32 cftal::max(const v2u32& a, const v2u32& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epu32(a(), b());
#else
        v2u32 _gt(a > b);
        return select(_gt, a, b);
#endif
}

inline
cftal::v2u32 cftal::min(const v2u32& a, const v2u32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epu32(a(), b());
#else
        v2u32 _lt(a < b);
        return select(_lt, a, b);
#endif
}

inline
cftal::v2u32 cftal::select(const v2u32::mask_type& m,
                           const v2u32& on_true,
                           const v2u32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

inline
cftal::v2u32
cftal::select_val_or_zero(const v2u32::mask_type& m,
                          const v2u32& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi32(m(), on_true());
#endif
}

inline
cftal::v2u32
cftal::select_zero_or_val(const v2u32::mask_type& m,
                          const v2u32& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi32(_knot_mask8(m()), on_false());
#endif
}

template <bool _I0, bool _I1>
inline
cftal::v2u32 cftal::select(const v2u32& a, const v2u32& b)
{
    return x86::select_u32<_I0, _I1, false, false>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2u32 cftal::permute(const v2u32& a)
{
    return x86::perm_v4u32<_I0, _I1, 2, 3>(a());
}

template <int _I0, int _I1>
inline
cftal::v2u32 cftal::permute(const v2u32& a, const v2u32& b)
{
    v4s32 t(a, b);
    return x86::perm_v4u32<_I0, _I1, 2, 3>(t());
}

inline
cftal::v2u32 cftal::permute(const v2u32& s, const v2s32& idx)
{
    return x86::permute_v4u32_v4s32(s(), idx());
}

inline
std::pair<cftal::v2u32, cftal::v2u32>
cftal::mul_lo_hi(const v2u32& x, const v2u32& y)
{
    __m128i x4=x86::vpshufd<0, 0, 1, 1>::v(x());
    __m128i y4=x86::vpshufd<0, 0, 1, 1>::v(y());
    // p0l p0h p2l p2h
    __m128i p4= _mm_mul_epu32(x4, y4);
    __m128i l4= x86::vpshufd<0, 2, 0, 2>::v(p4);
    __m128i h4= x86::vpshufd<1, 3, 1, 3>::v(p4);
    v2s32 l(l4), h(h4);
    return std::make_pair(l, h);
}


#if defined (__AVX2__)
inline
cftal::impl::variable_vec_lookup_table<uint32_t, int32_t, 2>::
variable_vec_lookup_table(const vec<int32_t, 2>& idx)
    : _msk(idx)
{
}

inline
cftal::vec<cftal::uint32_t, 2>
cftal::impl::variable_vec_lookup_table<uint32_t, int32_t, 2>::
fromp(const uint32_t* tbl) const
{
    return _mm_i32gather_epi32(
        reinterpret_cast<const int*>(tbl), _msk(), sizeof(uint32_t));
}

#endif

#if defined (__SSSE3__)
inline
cftal::v2s32
cftal::impl::fixed_vec_lookup_table<4, uint32_t, int32_t, 2>::
setup_msk(const vec<int32_t, 2>& idx)
{
#if defined (__AVX__)
    return idx;
#else
    vec<int32_t, 2> idx4 = idx<<2;
    const __m128i u8u32 =
        x86::const_v16u8< 0, 0, 0, 0,  4,  4,  4,  4,
                          8, 8, 8, 8, 12, 12, 12, 12>::iv();
    __m128i m=_mm_shuffle_epi8(idx4(), u8u32);
    const __m128i offs=
        x86::const_v16u8< 0, 1, 2, 3, 0, 1, 2, 3,
                          0, 1, 2, 3, 0, 1, 2, 3>::iv();
    m = _mm_add_epi8(m, offs);
    return m;
#endif
}

inline
cftal::impl::fixed_vec_lookup_table<4, uint32_t, int32_t, 2>::
fixed_vec_lookup_table(const vec<int32_t, 2>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v2u32
cftal::impl::fixed_vec_lookup_table<4, uint32_t, int32_t, 2>::
fromp(const uint32_t* tbl) const
{
#if defined (__AVX__)
    vec<uint32_t, 2> r=mem<vec<uint32_t, 2> >::load(tbl, 2);
    r=_mm_castps_si128(_mm_permutevar_ps(_mm_castsi128_ps(r()), _msk()));
    return r;
#else
    vec<uint32_t, 2> r=mem<vec<uint32_t, 2> >::load(tbl, 2);
    __m128i ir = _mm_shuffle_epi8(r(), _msk());
    return ir;
#endif
}

#endif

#if defined (__AVX2__)
inline
cftal::impl::fixed_vec_lookup_table<8, uint32_t, int32_t, 2>::
fixed_vec_lookup_table(const vec<int32_t, 2>& idx)
    : _msk(idx)
{
}

inline
cftal::vec<uint32_t, 2>
cftal::impl::fixed_vec_lookup_table<8, uint32_t, int32_t, 2>::
fromp(const uint32_t* tbl) const
{
    __m256i m=_mm256_castsi128_si256(_msk());
    __m256i r=_mm256_loadu_epi32(tbl);
    r=_mm256_permutevar8x32_epi32(r, m);
    return _mm256_castsi256_si128(r);
}

inline
cftal::impl::fixed_vec_lookup_table<32, uint32_t, int32_t, 2>::
fixed_vec_lookup_table(const vec<int32_t, 2>& idx)
    : _msk(idx()),
      _idx_gt_7(_mm_cmpgt_epi32(idx(), _mm_set1_epi32(7))),
      _idx_gt_15(_mm_cmpgt_epi32(idx(), _mm_set1_epi32(15))),
      _idx_gt_23(_mm_cmpgt_epi32(idx(), _mm_set1_epi32(23)))
{
}

inline
cftal::v2u32
cftal::impl::fixed_vec_lookup_table<32, uint32_t, int32_t, 2>::
fromp(const uint32_t* tbl) const
{
    __m256i m=_mm256_castsi128_si256(_msk);
    __m256i r0, r1, r2, r3;
    if (__likely(is_aligned_to<32>(tbl))) {
        r0=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+0)), m);
        r1=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+8)), m);
        r2=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+16)), m);
        r3=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+24)), m);
    } else {
        r0=_mm256_loadu_epi32(tbl);
        r1=_mm256_loadu_epi32(tbl+8);
        r2=_mm256_loadu_epi32(tbl+16);
        r3=_mm256_loadu_epi32(tbl+24);
        r0=_mm256_permutevar8x32_epi32(r0, m);
        r1=_mm256_permutevar8x32_epi32(r1, m);
        r2=_mm256_permutevar8x32_epi32(r2, m);
        r3=_mm256_permutevar8x32_epi32(r3, m);
    }
    __m128i r0i=_mm256_castsi256_si128(r0);
    __m128i r1i=_mm256_castsi256_si128(r1);
    __m128i r2i=_mm256_castsi256_si128(r2);
    __m128i r3i=_mm256_castsi256_si128(r3);
    __m128i r01i=x86::select_u32(_idx_gt_7, r1i, r0i);
    __m128i r23i=x86::select_u32(_idx_gt_23, r3i, r2i);
    __m128i ri=x86::select_u32(_idx_gt_15, r23i, r01i);
    vec<uint32_t, 2> r(ri);
    return r;
}

#endif

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U32_INL_H__
