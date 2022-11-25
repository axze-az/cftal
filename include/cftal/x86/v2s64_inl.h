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
#if !defined (__CFTAL_X86_V2S64_INL__)
#define __CFTAL_X86_V2S64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v2s64.h>
#include <cftal/x86/v2u64.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffffffffffffULL);
                return _mm_xor_si128(a(), all_set());
            }
        };

        template <>
        struct lt<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmplt_epi64_mask(a(), b());
#else
                return b > a;
#endif
            }
        };

        template <>
        struct le<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmple_epi64_mask(a(), b());
#else
                return ~(a > b);
#endif
            }
        };

        template <>
        struct eq<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpeq_epi64_mask(a(), b());
#else
		return x86::vpcmpeqq::v(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpneq_epi64_mask(a(), b());
#else
                return ~(a == b);
#endif
            }
        };

        template <>
        struct ge<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpge_epi64_mask(a(), b());
#else
                return ~(a < b);
#endif
            }
        };

        template <>
        struct gt<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmpgt_epi64_mask(a(), b());
#else
#if defined (__SSE4_2__)
                return _mm_cmpgt_epi64(a(), b());
#else
                // a > b : (a>=0 && b<0) || ((sgn(a) == sgn(b) && (b-a < 0)))
                // c1 --------^
                // c2 ---------------^
                // c3 -------------------------------^
                // c4 -------------------------------------------------^
                // sgn(a) == sgn(b) --> a ^ b == highest bit clear
                // b-a <0 == highest bit set
                // a >=0 == highest bit empty
                // b < 0 == highest bit set
                __m128i c4= _mm_sub_epi64(b(), a());
                __m128i c1_and_c2 = _mm_andnot_si128(a(), b());
                __m128i c3 = _mm_xor_si128(a(), b());
                __m128i c3_and_c4 = _mm_andnot_si128(c3, c4);
                __m128i r = _mm_or_si128(c1_and_c2, c3_and_c4);
                r = x86::vpsrad_const<31>::v(r);
                r = x86::vpshufd< 1, 1, 3, 3>::v(r);
                return r;
#endif
#endif
            }
        };

        template <>
        struct plus<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s64::v(a(), b());
            }
        };

        template <>
        struct mod<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2s64 q(a/b);
                v2s64 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int64_t, 2>>::v(
                    mul<vec<int64_t, 2>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int64_t, 2>>::v(
                    mul<vec<int64_t, 2>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int64_t, 2>>::v(
                    c, mul<vec<int64_t, 2>>::v(a, b));
            }
        };

        template <>
        struct bit_or<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsraq::v(a(), s);
            }
        };

        template <>
        struct vshl<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvq::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<int64_t, 2>> {
            using full_type = vec<int64_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsravq::v(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::int64_t, 2>::vec(const vec<uint64_t, 2>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int64_t, 2>::vec(int64_t v)
    : base_type(_mm_set_epi64x(v, v))
{
}


inline
cftal::vec<cftal::int64_t, 2>::
vec(std::initializer_list<int64_t> l)
    : vec(mem<v2s64>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 2>::
vec(init_list<int64_t> l)
    : vec(mem<v2s64>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 2>::
vec(const vec<int64_t, 1>& lh, const vec<int64_t, 1>& hh)
    : base_type(_mm_set_epi64x(hh(), lh()))
{
}


template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int64_t, 2>::vec(const expr<_OP<vec<int64_t, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int64_t, 2>
cftal::mem<cftal::vec<int64_t, 2> >::load(const int64_t* p, std::size_t s)
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
cftal::mem<cftal::vec<int64_t, 2> >::store(int64_t* p,
                                           const vec<int64_t, 2>& v)
{
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v());
}

inline
cftal::vec<int64_t, 1>
cftal::low_half(const vec<int64_t, 2>& v)
{
    return as<vec<int64_t,1> >(v);
}

inline
cftal::vec<int64_t, 1>
cftal::high_half(const vec<int64_t, 2>& v)
{
    return x86::extract_u64<1>(v());
}

template <cftal::size_t _I>
inline
cftal::int64_t
cftal::extract(const vec<int64_t, 2>& v)
{
    return x86::extract_u64<_I>(v());
}

inline
cftal::int64_t
cftal::extract(const vec<int64_t, 2>& v, size_t i)
{
    return x86::extract_u64(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<int64_t, 2>& v, const int64_t& vi)
{
    v= x86::insert_u64<_I>(v(), vi);
}

inline
void
cftal::insert(vec<int64_t, 2>& v, const int64_t& vi, size_t i)
{
    v= x86::insert_u64(v(), vi, i);
}

inline
cftal::v2s64 cftal::max(const v2s64& a, const v2s64& b)
{
    v2s64::mask_type _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v2s64 cftal::min(const v2s64& a, const v2s64& b)
{
    v2s64::mask_type _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v2s64
cftal::abs(const v2s64& a)
{
#if defined (__SSE4_2__)
    v2s64 sgn= _mm_cmpgt_epi64(_mm_setzero_si128(), a());
#else
    v2s64 sgn= _mm_srai_epi32(a(), 31);
    sgn = x86::vpshufd<1, 1, 3, 3>::v(sgn());
#endif
    v2s64 inv = a ^ sgn;
    // add 1
    return inv - sgn;
}

inline
cftal::v2s64 cftal::select(const v2s64::mask_type& m,
                           const v2s64& on_true,
                           const v2s64& on_false)
{
    return x86::select_u64(m(), on_true(), on_false());
}

inline
cftal::v2s64
cftal::select_val_or_zero(const v2s64::mask_type& m,
                          const v2s64& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_si128(m(), on_true());
#else
    return _mm_maskz_mov_epi64(m(), on_true());
#endif
}

inline
cftal::v2s64
cftal::select_zero_or_val(const v2s64::mask_type& m,
                          const v2s64& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_si128(m(), on_false());
#else
    return _mm_maskz_mov_epi64(_knot_mask8(m()), on_false());
#endif
}

template <bool _I0, bool _I1>
inline
cftal::v2s64
cftal::select(const v2s64& a, const v2s64& b)
{
    return x86::select_u64<_I0, _I1>(a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2s64 cftal::permute(const v2s64& a)
{
    return x86::perm_v2u64<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2s64 cftal::permute(const v2s64& a, const v2s64& b)
{
    return x86::perm_v2u64<_I0, _I1>(a(), b());
}

inline
cftal::v2s64 cftal::permute(const v2s64& s, const v2s64& idx)
{
    return x86::permute_v2u64_v2s64(s(), idx());
}

inline
std::pair<cftal::v2s64, cftal::v2s64>
cftal::mul_lo_hi(const v2s64& x, const v2s64& y)
{
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v2u64, v2u64> ur(mul_lo_hi(v2u64(x), v2u64(y)));
    v2s64 xsgn_y= y >> 63;
    v2s64 xsgn_x= x >> 63;
    v2s64 x_and_xsgn_y = x & xsgn_y;
    v2s64 y_and_xsgn_x = y & xsgn_x;
    v2s64 ph= v2s64(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v2s64 pl= v2s64(ur.first);
    return std::make_pair(pl, ph);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
inline
bool cftal::all_of(const vec<int64_t, 2>::mask_type& v)
{
    return x86::all_of_s64(v());
}

inline
bool cftal::any_of(const vec<int64_t, 2>::mask_type& v)
{
    return x86::any_of_s64(v());
}

inline
bool cftal::none_of(const vec<int64_t, 2>::mask_type& v)
{
    return x86::none_of_s64(v());
}

inline
cftal::vec<cftal::bit, 2>
cftal::compress_mask(const vec<int64_t, 2>::mask_type& v)
{
    return x86::compress_mask_u64(v());
}

inline
cftal::vec<int64_t, 2>
cftal::expand_mask<cftal::vec<int64_t, 2> >::
from(const vec<bit, 2>& s)
{
    return x86::expand_mask_v2u64(s());
}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S64_INL__
