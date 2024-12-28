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
#if !defined (__CFTAL_X86_V4U32_INL__)
#define __CFTAL_X86_V4U32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v4u32.h>
#include <cftal/x86/v4s32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_LT_OS & 7);
#else
                v4u32 ta(a ^ full_type(sign_s32_msk::v.u32()));
                v4u32 tb(b ^ full_type(sign_s32_msk::v.u32()));
                return _mm_cmpgt_epi32(tb(), ta());
#endif
            }
        };

        template <>
        struct le<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
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
        struct eq<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
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
        struct ne<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
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
        struct ge<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
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
        struct gt<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_epu32_mask(a(), b(), _CMP_GT_OS & 7);
#else
                v4u32 ta(a ^ full_type(sign_s32_msk::v.u32()));
                v4u32 tb(b ^ full_type(sign_s32_msk::v.u32()));
                return _mm_cmpgt_epi32(ta(), tb());
#endif
            }
        };

        template <>
        struct plus<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
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
        struct add<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u32::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v4u32 q=div<full_type>::v(a, b);
                v4u32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint32_t, 4>>::v(
                    mul<vec<uint32_t, 4>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint32_t, 4>>::v(
                    mul<vec<uint32_t, 4>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint32_t, 4>>::v(
                    c, mul<vec<uint32_t, 4>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };

        template <>
        struct vshl<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                // return _mm_sllv_epi32(a(), s());
                return x86::vpsllvd::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<uint32_t, 4>> {
            using full_type = vec<uint32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsrlvd::v(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::uint32_t, 4>::vec(const vec<int32_t,4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint32_t, 4>::vec(uint32_t v)
    : base_type(_mm_setr_epi32(v, v, v, v))
{
}

inline
cftal::vec<cftal::uint32_t, 4>::vec(vec<uint32_t, 2> l, vec<uint32_t, 2> h)
    : base_type(_mm_setr_epi32(low_half(l)(),
                               high_half(l)(),
                               low_half(h)(),
                               high_half(h)()))
{
}

inline
cftal::vec<cftal::uint32_t, 4>::
vec(std::initializer_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 4> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint32_t, 4>::
vec(init_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 4> >::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint32_t, 4>::vec(const expr<_OP<vec<uint32_t, 4> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint32_t, 4>
cftal::mem<cftal::vec<uint32_t, 4> >::load(const uint32_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 4:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 3:
        v = _mm_setr_epi32(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_epi32(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm_setr_epi32(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_epi32(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint32_t, 4> >::store(uint32_t* p,
                                            const vec<uint32_t, 4>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::vec<uint32_t, 2>
cftal::low_half(const vec<uint32_t, 4>& v)
{
    auto t=x86::extract_u64<0>(v());
    return as<vec<uint32_t, 2> >(t);
}

inline
cftal::vec<uint32_t, 2>
cftal::high_half(const vec<uint32_t, 4>& v)
{
    auto t=x86::extract_u64<1>(v());
    return as<vec<uint32_t, 2> >(t);
}

template <cftal::size_t _I>
inline
cftal::uint32_t
cftal::extract(const vec<uint32_t, 4>& v)
{
    return x86::extract_u32<_I>(v());
}

inline
cftal::uint32_t
cftal::extract(const vec<uint32_t, 4>& v, size_t i)
{
    return x86::extract_u32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint32_t, 4>& v, const uint32_t& vi)
{
    v= x86::insert_u32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint32_t, 4>& v, const uint32_t& vi, size_t i)
{
    v= x86::insert_u32(v(), vi, i);
}


#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<uint32_t, 4>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<uint32_t, 4>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<uint32_t, 4>::mask_type& v)
{
    return x86::none_of_s32(v());
}

inline
cftal::vec<cftal::bit, 4>
cftal::compress_mask(const vec<uint32_t, 4>::mask_type& v)
{
    return x86::compress_mask_u32(v());
}

inline
cftal::vec<uint32_t, 4>
cftal::expand_mask<cftal::vec<uint32_t, 4> >::
from(const vec<bit, 4>& s)
{
    return x86::expand_mask_v4u32(s());
}

#endif

inline
cftal::v4u32 cftal::max(const v4u32& a, const v4u32& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epu32(a(), b());
#else
        v4u32 _gt(a > b);
        return select(_gt, a, b);
#endif
}

inline
cftal::v4u32 cftal::min(const v4u32& a, const v4u32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epu32(a(), b());
#else
        v4u32 _lt(a < b);
        return select(_lt, a, b);
#endif
}

inline
cftal::v4u32 cftal::select(const v4u32::mask_type& m,
                           const v4u32& on_true,
                           const v4u32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

inline
cftal::v4u32
cftal::select_val_or_zero(const v4u32::mask_type& m,
                          const v4u32& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi32(m(), on_true());
#endif
}

inline
cftal::v4u32
cftal::select_zero_or_val(const v4u32::mask_type& m,
                          const v4u32& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi32(_knot_mask8(m()), on_false());
#endif
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::v4u32 cftal::select(const v4u32& a, const v4u32& b)
{
    return x86::select_u32<_I0, _I1, _I2, _I3>(a(), b());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4u32 cftal::permute(const v4u32& a)
{
    return x86::perm_v4u32<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4u32 cftal::permute(const v4u32& a, const v4u32& b)
{
    return x86::perm_v4u32<_I0, _I1, _I2, _I3>(a(), b());
}

inline
cftal::v4u32 cftal::permute(const v4u32& s, const v4s32& idx)
{
    return x86::permute_v4u32_v4s32(s(), idx());
}

inline
std::pair<cftal::v4u32, cftal::v4u32>
cftal::mul_lo_hi(const v4u32& x, const v4u32& y)
{
    // p0l p0h p2l p2h
    v4u32 e= _mm_mul_epu32(x(), y());
    // p1l p1h p3l p3h
    v4u32 o= _mm_mul_epu32(x86::vpshufd<1, 0, 3, 2>::v(x()),
                           x86::vpshufd<1, 0, 3, 2>::v(y()));
    // p0l p1l p0h p1h
    v4u32 t0= permute<0, 4, 1, 5>(e, o);
    // p2l p3l p2h p3h
    v4u32 t1= permute<2, 6, 3, 7>(e, o);
    // p0h p1h p2h p3h
    v4u32 h = permute<2, 3, 6, 7>(t0, t1);
    v4u32 l = permute<0, 1, 4, 5>(t0, t1);
    return std::make_pair(l, h);
}


#if defined (__AVX2__)
inline
cftal::impl::variable_vec_lookup_table<uint32_t, int32_t, 4>::
variable_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(idx)
{
}

inline
cftal::vec<cftal::uint32_t, 4>
cftal::impl::variable_vec_lookup_table<uint32_t, int32_t, 4>::
fromp(const uint32_t* tbl) const
{
    return _mm_i32gather_epi32(
        reinterpret_cast<const int*>(tbl), _msk(), sizeof(uint32_t));
}

#endif

#if defined (__SSSE3__)
inline
cftal::v4s32
cftal::impl::fixed_vec_lookup_table<4, uint32_t, int32_t, 4>::
setup_msk(const vec<int32_t, 4>& idx)
{
#if defined (__AVX__)
    return idx;
#else
    vec<int32_t, 4> idx4 = idx<<2;
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
cftal::impl::fixed_vec_lookup_table<4, uint32_t, int32_t, 4>::
fixed_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v4u32
cftal::impl::fixed_vec_lookup_table<4, uint32_t, int32_t, 4>::
fromp(const uint32_t* tbl) const
{
#if defined (__AVX__)
    vec<uint32_t, 4> r=mem<vec<uint32_t, 4> >::load(tbl, 4);
    r=_mm_castps_si128(_mm_permutevar_ps(_mm_castsi128_ps(r()), _msk()));
    return r;
#else
    vec<uint32_t, 4> r=mem<vec<uint32_t, 4> >::load(tbl, 4);
    __m128i ir = _mm_shuffle_epi8(r(), _msk());
    return ir;
#endif
}

#endif

#if defined (__AVX2__)
inline
cftal::impl::fixed_vec_lookup_table<8, uint32_t, int32_t, 4>::
fixed_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(idx)
{
}

inline
cftal::vec<uint32_t, 4>
cftal::impl::fixed_vec_lookup_table<8, uint32_t, int32_t, 4>::
fromp(const uint32_t* tbl) const
{
    __m256i m=_mm256_castsi128_si256(_msk());
    __m256i r=_mm256_loadu_epi32(tbl);
    r=_mm256_permutevar8x32_epi32(r, m);
    return _mm256_castsi256_si128(r);
}

inline
cftal::impl::fixed_vec_lookup_table<32, uint32_t, int32_t, 4>::
fixed_vec_lookup_table(const vec<int32_t, 4>& idx)
    : _msk(idx()),
      _idx_gt_7(_mm_cmpgt_epi32(idx(), _mm_set1_epi32(7))),
      _idx_gt_15(_mm_cmpgt_epi32(idx(), _mm_set1_epi32(15))),
      _idx_gt_23(_mm_cmpgt_epi32(idx(), _mm_set1_epi32(23)))
{
}

inline
cftal::v4u32
cftal::impl::fixed_vec_lookup_table<32, uint32_t, int32_t, 4>::
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
    vec<uint32_t, 4> r(ri);
    return r;
}

#endif



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4U32_INL__
