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
#if !defined (__CFTAL_X86_V8S64_INL__)
#define __CFTAL_X86_V8S64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v8s64.h>
#include <cftal/x86/v8u64.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffffffffffffULL);
                return _mm512_xor_si512(a(), all_set());
            }
        };

        template <>
        struct lt<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmplt_epi64_mask(a(), b());
            }
        };

        template <>
        struct le<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmple_epi64_mask(a(), b());
            }
        };

        template <>
        struct eq<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpeq_epi64_mask(a(), b());
            }
        };

        template <>
        struct ne<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpneq_epi64_mask(a(), b());
            }
        };

        template <>
        struct ge<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpge_epi64_mask(a(), b());
            }
        };

        template <>
        struct gt<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpgt_epi64_mask(a(), b());
            }
        };

        template <>
        struct plus<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm512_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s64::v(a(), b());
            }
        };

        template <>
        struct mod<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v8s64 q(a/b);
                v8s64 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int64_t, 8>>::v(
                    mul<vec<int64_t, 8>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int64_t, 8>>::v(
                    mul<vec<int64_t, 8>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int64_t, 8>>::v(
                    c, mul<vec<int64_t, 8>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_or_si512(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_and_si512(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_xor_si512(a(), b());
            }
        };

        template <>
        struct shl<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::vpsraq::v(a(), s);
            }
        };

        template <>
        struct vshl<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsllvq::v(a(), s());
            }
        };

        template <>
        struct vshr<vec<int64_t, 8>> {
            using full_type = vec<int64_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return x86::vpsravq::v(a(), s());
            }
        };
    }
}

inline
cftal::vec<cftal::int64_t, 8>::vec(const vec<uint64_t, 8>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int64_t, 8>::vec(int64_t v)
    : base_type(_mm512_set1_epi64(v))
{
}

inline
cftal::vec<int64_t, 8>::
vec(const vec<int64_t, 4>& lh, const vec<int64_t, 4>& hh)
    : base_type(_mm512_inserti32x8(as<__m512i>(lh()),hh(), 1))
{
}


inline
cftal::vec<cftal::int64_t, 8>::
vec(std::initializer_list<int64_t> l)
    : vec(mem<v8s64>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 8>::
vec(init_list<int64_t> l)
    : vec(mem<v8s64>::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int64_t, 8>::vec(const expr<_OP<vec<int64_t, 8> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int64_t, 8>
cftal::mem<cftal::vec<int64_t, 8> >::load(const int64_t* p, ssize_t s)
{
    vec<int64_t, 8> v;
    if (s >= 8) {
        v = _mm512_loadu_si512(reinterpret_cast<const __m512i*>(p));
    } else if (s==1) {
        v = _mm512_castsi128_si512(_mm_loadu_si64(p));
    } else if (s>=2) {
        auto lh=mem<vec<int64_t, 4> >::load(p, s);
        ssize_t sh= s>=4 ? s-4 : 0;
        auto hh=mem<vec<int64_t, 4> >::load(p+4, sh);
        v = vec<int64_t, 8>(lh, hh);
    } else {
        v = _mm512_set1_epi64(0);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int64_t, 8> >::
store(int64_t* p, const vec<int64_t, 8>& v, ssize_t s)
{
    if (s>=8) {
        _mm512_storeu_si512(reinterpret_cast<__m512i*>(p), v());
    } else if (s>0) {
        mem<vec<int64_t, 4> >::store(p, low_half(v), s);
        if (s>4) {
            mem<vec<int64_t, 4> >::store(p+4, high_half(v), s-4);
        }
    }
}

inline
cftal::vec<int64_t, 4>
cftal::low_half(const cftal::vec<int64_t, 8>& v)
{
    return _mm512_castsi512_si256(v());
}

inline
cftal::vec<int64_t, 4>
cftal::high_half(const cftal::vec<int64_t, 8>& v)
{
    return _mm512_extracti64x4_epi64(v(), 1);
}

template <cftal::size_t _I>
inline
cftal::int64_t
cftal::extract(const vec<int64_t, 8>& v)
{
    return x86::extract_u64<_I>(v());
}

inline
cftal::int64_t
cftal::extract(const vec<int64_t, 8>& v, size_t i)
{
    return x86::extract_u64(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<int64_t, 8>& v, const int64_t& vi)
{
    v= x86::insert_u64<_I>(v(), vi);
}

inline
void
cftal::insert(vec<int64_t, 8>& v, const int64_t& vi, size_t i)
{
    v= x86::insert_u64(v(), vi, i);
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<int64_t, 8>::mask_type& v)
{
    return x86::all_of_s64(v());
}

inline
bool cftal::any_of(const vec<int64_t, 8>::mask_type& v)
{
    return x86::any_of_s64(v());
}

inline
bool cftal::none_of(const vec<int64_t, 8>::mask_type& v)
{
    return x86::none_of_s64(v());
}
#endif

inline
cftal::v8s64 cftal::max(const v8s64& a, const v8s64& b)
{
    v8s64::mask_type _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v8s64 cftal::min(const v8s64& a, const v8s64& b)
{
    v8s64::mask_type _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v8s64 cftal::abs(const v8s64& a)
{
    return _mm512_abs_epi64(a());
}

inline
cftal::v8s64 cftal::select(const v8s64::mask_type& m,
                           const v8s64& on_true,
                           const v8s64& on_false)
{
    return x86::select_u64(m(), on_true(), on_false());
}

inline
cftal::v8s64
cftal::select_val_or_zero(const v8s64::mask_type& m,
                          const v8s64& on_true)
{
    return _mm512_maskz_mov_epi64(m(), on_true());
}

inline
cftal::v8s64
cftal::select_zero_or_val(const v8s64::mask_type& m,
                          const v8s64& on_false)
{
    return _mm512_maskz_mov_epi64(_knot_mask8(m()), on_false());
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8s64
cftal::select(const v8s64& a, const v8s64& b)
{
    return x86::select_u64<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>(a(), b());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s64 cftal::permute(const v8s64& a)
{
    return x86::perm_v8u64<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s64 cftal::permute(const v8s64& a, const v8s64& b)
{
    return x86::perm_v8u64<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a(), b());
}

inline
cftal::v8s64
cftal::permute(const v8s64& s, const v8s64& idx)
{
    return x86::permute_v8u64_v8s64(s(), idx());
}

inline
std::pair<cftal::v8s64, cftal::v8s64>
cftal::mul_lo_hi(const v8s64& x, const v8s64& y)
{
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v8u64, v8u64> ur(mul_lo_hi(v8u64(x), v8u64(y)));
    v8s64 xsgn_y= y >> 63;
    v8s64 xsgn_x= x >> 63;
    v8s64 x_and_xsgn_y = x & xsgn_y;
    v8s64 y_and_xsgn_x = y & xsgn_x;
    v8s64 ph= v8s64(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v8s64 pl= v8s64(ur.first);
    return std::make_pair(pl, ph);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8S64_INL__
