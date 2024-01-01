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
#if !defined (__CFTAL_X86_V4S64_INL__)
#define __CFTAL_X86_V4S64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v4s64.h>
#include <cftal/x86/v4u64.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffffffffffffULL);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        template <>
        struct lt<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmplt_epi64_mask(a(), b());
#else
                return b > a;
#endif
            }
        };

        template <>
        struct le<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmple_epi64_mask(a(), b());
#else
                return ~(a > b);
#endif
            }
        };

        template <>
        struct eq<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpeq_epi64_mask(a(), b());
#else
                return _mm256_cmpeq_epi64(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpneq_epi64_mask(a(), b());
#else
                return ~(a == b);
#endif
            }
        };

        template <>
        struct ge<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpge_epi64_mask(a(), b());
#else
                return ~(a < b);
#endif
            }
        };

        template <>
        struct gt<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpgt_epi64_mask(a(), b());
#else
                return _mm256_cmpgt_epi64(a(), b());
#endif
            }
        };

        template <>
        struct plus<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm256_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s64::v(a(), b());
            }
        };

        template <>
        struct mod<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v4s64 q(a/b);
                v4s64 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int64_t, 4>>::v(
                    mul<vec<int64_t, 4>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int64_t, 4>>::v(
                    mul<vec<int64_t, 4>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int64_t, 4>>::v(
                    c, mul<vec<int64_t, 4>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsraq::v(a(), s);
            }
        };

#if defined (__AVX2__)
        template <>
        struct vshl<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvq::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<int64_t, 4>> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsravq::v(a(), s());
            }
        };
#endif

    }

}

inline
cftal::vec<cftal::int64_t, 4>::vec(const vec<uint64_t, 4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int64_t, 4>::vec(int64_t v)
    : base_type(_mm256_set_epi64x(v, v, v, v))
{
}

inline
cftal::vec<int64_t, 4>::
vec(const vec<int64_t, 2>& lh, const vec<int64_t, 2>& hh)
    : base_type(_mm256_inserti128_si256(as<__m256i>(lh()),hh(), 1))
{
}


inline
cftal::vec<cftal::int64_t, 4>::
vec(std::initializer_list<int64_t> l)
    : vec(mem<v4s64>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 4>::
vec(init_list<int64_t> l)
    : vec(mem<v4s64>::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int64_t, 4>::vec(const expr<_OP<vec<int64_t, 4> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int64_t, 4>
cftal::mem<cftal::vec<int64_t, 4> >::load(const int64_t* p, std::size_t s)
{
    __m256i v;
    switch (s) {
    default:
    case 4:
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
        break;
    case 3:
        v = _mm256_setr_epi64x(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_epi64x(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm256_setr_epi64x(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_set_epi64x(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int64_t, 4> >::store(int64_t* p,
                                           const vec<int64_t, 4>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::vec<int64_t, 2>
cftal::low_half(const cftal::vec<int64_t, 4>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<int64_t, 2>
cftal::high_half(const cftal::vec<int64_t, 4>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

template <cftal::size_t _I>
inline
cftal::int64_t
cftal::extract(const vec<int64_t, 4>& v)
{
    return x86::extract_u64<_I>(v());
}

inline
cftal::int64_t
cftal::extract(const vec<int64_t, 4>& v, size_t i)
{
    return x86::extract_u64(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<int64_t, 4>& v, const int64_t& vi)
{
    v= x86::insert_u64<_I>(v(), vi);
}

inline
void
cftal::insert(vec<int64_t, 4>& v, const int64_t& vi, size_t i)
{
    v= x86::insert_u64(v(), vi, i);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<int64_t, 4>::mask_type& v)
{
    return x86::all_of_s64(v());
}

inline
bool cftal::any_of(const vec<int64_t, 4>::mask_type& v)
{
    return x86::any_of_s64(v());
}

inline
bool cftal::none_of(const vec<int64_t, 4>::mask_type& v)
{
    return x86::none_of_s64(v());
}

inline
cftal::vec<cftal::bit, 4>
cftal::compress_mask(const vec<int64_t, 4>::mask_type& v)
{
    return x86::compress_mask_u64(v());
}

inline
cftal::vec<int64_t, 4>
cftal::expand_mask<cftal::vec<int64_t, 4> >::
from(const vec<bit, 4>& s)
{
    return x86::expand_mask_v4u64(s());
}

#endif

inline
cftal::v4s64 cftal::max(const v4s64& a, const v4s64& b)
{
    v4s64::mask_type _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v4s64 cftal::min(const v4s64& a, const v4s64& b)
{
    v4s64::mask_type _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v4s64 cftal::abs(const v4s64& a)
{
    v4s64 sgn= _mm256_cmpgt_epi64(_mm256_setzero_si256(), a());
    // invert where sgn < 0
    v4s64 inv = a ^ sgn;
    // add 1
    return inv - sgn;
}

inline
cftal::v4s64 cftal::select(const v4s64::mask_type& m,
                           const v4s64& on_true,
                           const v4s64& on_false)
{
    return x86::select_u64(m(), on_true(), on_false());
}

inline
cftal::v4s64
cftal::select_val_or_zero(const v4s64::mask_type& m,
                          const v4s64& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_and_si256(m(), on_true());
#else
    return _mm256_maskz_mov_epi64(m(), on_true());
#endif
}

inline
cftal::v4s64
cftal::select_zero_or_val(const v4s64::mask_type& m,
                          const v4s64& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_andnot_si256(m(), on_false());
#else
    return _mm256_maskz_mov_epi64(_knot_mask8(m()), on_false());
#endif
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::v4s64
cftal::select(const v4s64& a, const v4s64& b)
{
    return x86::select_u64<_I0, _I1, _I2, _I3>(a(), b());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4s64 cftal::permute(const v4s64& a)
{
    return x86::perm_v4u64<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4s64 cftal::permute(const v4s64& a, const v4s64& b)
{
    return x86::perm_v4u64<_I0, _I1, _I2, _I3>(a(), b());
}

inline
cftal::v4s64 cftal::permute(const v4s64& s, const v4s64& idx)
{
    return x86::permute_v4u64_v4s64(s(), idx());
}

inline
std::pair<cftal::v4s64, cftal::v4s64>
cftal::mul_lo_hi(const v4s64& x, const v4s64& y)
{
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v4u64, v4u64> ur(mul_lo_hi(v4u64(x), v4u64(y)));
    v4s64 xsgn_y= y >> 63;
    v4s64 xsgn_x= x >> 63;
    v4s64 x_and_xsgn_y = x & xsgn_y;
    v4s64 y_and_xsgn_x = y & xsgn_x;
    v4s64 ph= v4s64(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v4s64 pl= v4s64(ur.first);
    return std::make_pair(pl, ph);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4S64_INL__
