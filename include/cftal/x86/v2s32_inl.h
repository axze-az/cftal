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
#if !defined (__CFTAL_X86_V2S32_INL_H__)
#define __CFTAL_X86_V2S32_INL_H__ 1

#include <cftal/config.h>

#if __CFTAL_CFG_USE_8_BYTE_VECS_ON_X86__> 0

#include <cftal/types.h>
#include <cftal/x86/v2s32.h>
#include <cftal/x86/v4u32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };


        template <>
        struct lt<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_LT_OS & 7);
#else
                return _mm_cmpgt_epi32(b(), a());
#endif
            }
        };

        template <>
        struct le<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_LE_OS & 7);
#else
#if defined (__SSE4_1__)
                // a <= b: a == min(a, b);
                __m128i min_ab = _mm_min_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), min_ab);
#else
                mask_type b_gt_a(lt<vec<int32_t, 2>>::v(b(), a()));
                const mask_type all_set(uint32_t(-1));
                return _mm_xor_si128(b_gt_a(), all_set());
#endif
#endif
            }
        };

        template <>
        struct eq<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_EQ_OQ & 7);
#else
                return _mm_cmpeq_epi32(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_UNORD_Q & 7);
#else
                mask_type a_eq_b(eq<vec<int32_t, 2>>::v(a, b));
                return bit_not<vec<int32_t, 2>>::v(a_eq_b);
#endif
            }
        };

        template <>
        struct ge<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_GE_OS & 7);
#else
#if defined (__SSE4_1__)
                // a >= b: a == max(a, b);
                __m128i max_ab = _mm_max_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), max_ab);
#else
                mask_type a_lt_b( lt<vec<int32_t, 2>>::v(a(), b()));
                return bit_not<vec<int32_t, 2>>::v(a_lt_b);
#endif
#endif
            }
        };

        template <>
        struct gt<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_epi32_mask(a(), b(), _CMP_GT_OS & 7);
#else
                return _mm_cmpgt_epi32(a(), b());
#endif
            }
        };

        template <>
        struct plus<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v.s32());
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s32::v(a(), b());
            }
        };

        template <>
        struct mod<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2s32 q=div<full_type>::v(a, b);
                v2s32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int32_t, 2>>::v(
                    mul<vec<int32_t, 2>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int32_t, 2>>::v(
                    mul<vec<int32_t, 2>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int32_t, 2>>::v(
                    c, mul<vec<int32_t, 2>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srai_epi32(a(), s);
            }
        };

        template <>
        struct vshl<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvd::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<int32_t, 2>> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsravd::v(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::int32_t, 2>::vec(__m128i v)
    : _v(v)
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(const vec<uint32_t, 2>& v)
    : _v(v())
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(int32_t v)
    : _v(_mm_setr_epi32(v, v, v, v))
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(vec<int32_t, 1> l, vec<int32_t, 1> h)
    : _v(_mm_setr_epi32(l(), h(), 0, 0))
{
}

inline
cftal::vec<cftal::int32_t, 2>::
vec(std::initializer_list<int32_t> l)
    : vec(mem<v2s32>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 2>::
vec(init_list<int32_t> l)
    : vec(mem<v2s32>::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 2>::vec(const expr<_OP<vec<int32_t, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 2>
cftal::mem<cftal::vec<int32_t, 2> >::load(const int32_t* p, ssize_t s)
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
cftal::mem<cftal::vec<int32_t, 2> >::
store(int32_t* p, const vec<int32_t, 2>& v, ssize_t s)
{
    if (s>=2) {
        _mm_storeu_si64(p, v());
    } else if (s==1) {
        _mm_storeu_si32(p, v());
    }
}

inline
cftal::vec<int32_t, 1>
cftal::low_half(const vec<int32_t, 2>& v)
{
    auto t=x86::extract_u32<0>(v());
    return vec<int32_t, 1>(t);
}

inline
cftal::vec<int32_t, 1>
cftal::high_half(const vec<int32_t, 2>& v)
{
    auto t=x86::extract_u32<1>(v());
    return vec<int32_t, 1>(t);
}

template <cftal::size_t _I>
inline
cftal::int32_t
cftal::extract(const vec<int32_t, 2>& v)
{
    return x86::extract_u32<_I>(v());
}

inline
cftal::int32_t
cftal::extract(const vec<int32_t, 2>& v, size_t i)
{
    return x86::extract_u32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<int32_t, 2>& v, const int32_t& vi)
{
    v= x86::insert_u32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<int32_t, 2>& v, const int32_t& vi, size_t i)
{
    v= x86::insert_u32(v(), vi, i);
}


#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<int32_t, 2>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<int32_t, 2>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<int32_t, 2>::mask_type& v)
{
    return x86::none_of_s32(v());
}

inline
cftal::vec<cftal::bit, 2>
cftal::compress_mask(const vec<int32_t, 2>::mask_type& v)
{
    return x86::compress_mask_u32(v());
}

inline
cftal::vec<int32_t, 2>
cftal::expand_mask<cftal::vec<int32_t, 2> >::
from(const vec<bit, 2>& s)
{
    return x86::expand_mask_v4u32(s());
}

#endif

inline
cftal::v2s32 cftal::max(const v2s32& a, const v2s32& b)
{
#if defined (__SSE4_1__)
    return _mm_max_epi32(a(), b());
#else
    v2s32 _gt(a > b);
    return select(_gt, a, b);
#endif
}

inline
cftal::v2s32 cftal::min(const v2s32& a, const v2s32& b)
{
#if defined (__SSE4_1__)
    return _mm_min_epi32(a(), b());
#else
    v2s32 _lt(a < b);
    return select(_lt, a, b);
#endif
}

inline
cftal::v2s32 cftal::abs(const v2s32& a)
{
#if defined (__SSSE3__)
    return _mm_sign_epi32(a(), a());
#else
    v2s32 sgn= a >> 31;
    // invert if negative
    v2s32 inv= a ^ sgn;
    // add 1
    return inv - sgn;
#endif
}

inline
cftal::v2s32 cftal::select(const v2s32::mask_type& m,
                           const v2s32& on_true,
                           const v2s32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

inline
cftal::v2s32
cftal::select_val_or_zero(const v2s32::mask_type& m,
                          const v2s32& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi32(m(), on_true());
#endif
}

inline
cftal::v2s32
cftal::select_zero_or_val(const v2s32::mask_type& m,
                          const v2s32& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi32(_knot_mask8(m()), on_false());
#endif
}

template <bool _I0, bool _I1>
inline
cftal::v2s32 cftal::select(const v2s32& a, const v2s32& b)
{
    return x86::select_u32<_I0, _I1, false, false>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2s32 cftal::permute(const v2s32& a)
{
    return x86::perm_v4u32<_I0, _I1, 2, 3>(a());
}

template <int _I0, int _I1>
inline
cftal::v2s32 cftal::permute(const v2s32& a, const v2s32& b)
{
    v4s32 t(a, b);
    return x86::perm_v4u32<_I0, _I1, 2, 3>(t());
}

inline
cftal::v2s32 cftal::permute(const v2s32& s, const v2s32& idx)
{
    return x86::permute_v4u32_v4s32(s(), idx());
}

inline
std::pair<cftal::v2s32, cftal::v2s32>
cftal::mul_lo_hi(const v2s32& x, const v2s32& y)
{
#if defined (__SSE4_1__)
    __m128i x4=x86::vpshufd<0, 0, 1, 1>::v(x());
    __m128i y4=x86::vpshufd<0, 0, 1, 1>::v(y());
    // p0l p0h p2l p2h
    __m128i p4= _mm_mul_epi32(x4, y4);
    __m128i l4= x86::vpshufd<0, 2, 0, 2>::v(p4);
    __m128i h4= x86::vpshufd<1, 3, 1, 3>::v(p4);
    v2s32 l(l4), h(h4);
    return std::make_pair(l, h);
#else
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v4u32, v4u32> ur(mul_lo_hi(v2u32(x), v2u32(y)));
    v2s32 xsgn_y= y >> 31; // x86::const_shift::_31;
    v2s32 xsgn_x= x >> 31; // x86::const_shift::_31;
    v2s32 x_and_xsgn_y = x & xsgn_y;
    v2s32 y_and_xsgn_x = y & xsgn_x;
    v2s32 sh = v2s32(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v2s32 sl = v2s32(ur.first);
    return std::make_pair(sl, sh);
#endif
}

#endif 
// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S32_INL_H__
