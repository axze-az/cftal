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
#if !defined (__CFTAL_X86_V8S32_INL__)
#define __CFTAL_X86_V8S32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v8s32.h>
#include <cftal/x86/v8u32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffff);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        template <>
        struct lt<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmplt_epi32_mask(a(), b());
#else
                return _mm256_cmpgt_epi32(b(), a());
#endif
            }
        };

        template <>
        struct le<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmple_epi32_mask(a(), b());
#else
                // a <= b: a == min(a, b);
                __m256i min_ab = _mm256_min_epi32(b(), a());
                return _mm256_cmpeq_epi32(a(), min_ab);
#endif
            }
        };

        template <>
        struct eq<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpeq_epi32_mask(a(), b());
#else
                return _mm256_cmpeq_epi32(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpneq_epi32_mask(a(), b());
#else
                mask_type a_eq_b(eq<vec<int32_t, 8>>::v(a, b));
                return bit_not<vec<int32_t, 8>>::v(a_eq_b);
#endif
            }
        };

        template <>
        struct ge<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpge_epi32_mask(a(), b());
#else
                // a >= b: a == max(a, b);
                __m256i max_ab = _mm256_max_epi32(b(), a());
                return _mm256_cmpeq_epi32(a(), max_ab);
#endif
            }
        };

        template <>
        struct gt<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmpgt_epi32_mask(a(), b());
#else
                return _mm256_cmpgt_epi32(a(), b());
#endif
            }
        };

        template <>
        struct plus<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(sign_s32_msk::v.s32());
                return _mm256_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm256_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s32::v(a(), b());
            }
        };

        template <>
        struct mod<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v8s32 q(a/b);
                v8s32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<int32_t, 8>>::v(
                    mul<vec<int32_t, 8>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<int32_t, 8>>::v(
                    mul<vec<int32_t, 8>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<int32_t, 8>>::v(
                    c, mul<vec<int32_t, 8>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm256_srai_epi32(a(), s);
            }
        };
#if defined (__AVX2__)
        template <>
        struct vshl<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return _mm256_sllv_epi32(a(), s());
            }
        };

        template <>
        struct vshr<vec<int32_t, 8>> {
            using full_type = vec<int32_t, 8>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return _mm256_srav_epi32(a(), s());
            }
        };
#endif

    }

}

inline
cftal::vec<cftal::int32_t, 8>::vec(const vec<uint32_t, 8>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int32_t, 8>::vec(int32_t v)
    : base_type(_mm256_set1_epi32(v))
{
}

inline
cftal::vec<cftal::int32_t, 8>::vec(const vec<int32_t, 4>& l,
                                   const vec<int32_t, 4>& h)
    : base_type(_mm256_inserti128_si256(
                    _mm256_castsi128_si256(l()), h(), 1))
{
}

inline
cftal::vec<cftal::int32_t, 8>::
vec(std::initializer_list<int32_t> l)
    : vec(mem<v8s32>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 8>::
vec(init_list<int32_t> l)
    : vec(mem<v8s32>::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 8>::vec(const expr<_OP<vec<int32_t, 8> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 8>
cftal::mem<cftal::vec<int32_t, 8> >::load(const int32_t* p, ssize_t s)
{
    vec<int32_t, 8> v;
    if (s >= 8) {
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
    } else if (s==1) {
        v = _mm256_castsi128_si256(_mm_loadu_si32(p));
    } else if (s>=2) {
        auto lh=mem<vec<int32_t, 4> >::load(p, s);
        ssize_t sh= s>=4 ? s-4 : 0;
        auto hh=mem<vec<int32_t, 4> >::load(p+4, sh);
        v = vec<int32_t, 8>(lh, hh);
    } else {
        v = _mm256_set1_epi32(0);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int32_t, 8> >::
store(int32_t* p, const vec<int32_t, 8>& v, ssize_t s)
{
    if (s>=8) {
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
    } else if (s>0) {
        mem<vec<int32_t, 4> >::store(p, low_half(v), s);
        if (s>4) {
            mem<vec<int32_t, 4> >::store(p+4, high_half(v), s-4);
        }
    }
}

inline
cftal::vec<int32_t, 4>
cftal::low_half(const cftal::vec<int32_t, 8>& v)
{
    return _mm256_castsi256_si128(v());
}

inline
cftal::vec<int32_t, 4>
cftal::high_half(const cftal::vec<int32_t, 8>& v)
{
    return _mm256_extracti128_si256(v(), 1);
}

template <cftal::size_t _I>
inline
cftal::int32_t
cftal::extract(const vec<int32_t, 8>& v)
{
    return x86::extract_u32<_I>(v());
}

inline
cftal::int32_t
cftal::extract(const vec<int32_t, 8>& v, size_t i)
{
    return x86::extract_u32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<int32_t, 8>& v, const int32_t& vi)
{
    v= x86::insert_u32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<int32_t, 8>& v, const int32_t& vi, size_t i)
{
    v= x86::insert_u32(v(), vi, i);
}


#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const vec<int32_t, 8>::mask_type& v)
{
    return x86::all_of_s32(v());
}

inline
bool cftal::any_of(const vec<int32_t, 8>::mask_type& v)
{
    return x86::any_of_s32(v());
}

inline
bool cftal::none_of(const vec<int32_t, 8>::mask_type& v)
{
    return x86::none_of_s32(v());
}

inline
cftal::vec<cftal::bit, 8>
cftal::compress_mask(const vec<int32_t, 8>::mask_type& v)
{
    return x86::compress_mask_u32(v());
}

inline
cftal::vec<int32_t, 8>
cftal::expand_mask<cftal::vec<int32_t, 8> >::
from(const vec<bit, 8>& s)
{
    return x86::expand_mask_v8u32(s());
}

#endif

inline
cftal::v8s32 cftal::max(const v8s32& a, const v8s32& b)
{
    return _mm256_max_epi32(a(), b());
}

inline
cftal::v8s32 cftal::min(const v8s32& a, const v8s32& b)
{
    return _mm256_min_epi32(a(), b());
}

inline
cftal::v8s32 cftal::abs(const v8s32& a)
{
    return _mm256_sign_epi32(a(), a());
}

inline
cftal::v8s32 cftal::select(const v8s32::mask_type& m,
                           const v8s32& on_true,
                           const v8s32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

inline
cftal::v8s32
cftal::select_val_or_zero(const v8s32::mask_type& m,
                          const v8s32& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_and_si256(m(), on_true());
#else
    return _mm256_maskz_mov_epi32(m(), on_true());
#endif
}

inline
cftal::v8s32
cftal::select_zero_or_val(const v8s32::mask_type& m,
                          const v8s32& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_andnot_si256(m(), on_false());
#else
    return _mm256_maskz_mov_epi32(_knot_mask8(m()), on_false());
#endif
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8s32 cftal::select(const v8s32& a, const v8s32& b)
{
    return x86::select_u32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7> (a(), b());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s32 cftal::permute(const v8s32& a)
{
    return x86::perm_v8u32<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a());
}

template <int _I0, int _I1, int _I2, int _I3,
          int _I4, int _I5, int _I6, int _I7>
inline
cftal::v8s32 cftal::permute(const v8s32& a, const v8s32& b)
{
    return x86::perm_v8u32<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(a(), b());
}

inline
cftal::v8s32 cftal::permute(const v8s32& s, const v8s32& idx)
{
    return x86::permute_v8u32_v8s32(s(), idx());
}

inline
std::pair<cftal::v8s32, cftal::v8s32>
cftal::mul_lo_hi(const v8s32& x, const v8s32& y)
{
    // p0l p0h p2l p2h p4l p4h p6l p6h
    v8s32 e= _mm256_mul_epi32(x(), y());
    // p1l p1h p3l p3h p5l p5h p7l p7h
    v8s32 o= _mm256_mul_epi32(
        x86::vpshufd<1, 0, 3, 2>::v(x()),
        x86::vpshufd<1, 0, 3, 2>::v(y()));
    // --------------------------------------
    v8s32 l= permute<0, 0+8,
                     2, 2+8,
                     4, 4+8,
                     6, 6+8>(e, o);
    v8s32 h= permute<1, 1+8,
                     3, 3+8,
                     5, 5+8,
                     7, 7+8>(e, o);
    return std::make_pair(l, h);
}

inline
cftal::impl::variable_vec_lookup_table<int32_t, int32_t, 8>::
variable_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(idx())
{
}

inline
cftal::v8s32
cftal::impl::variable_vec_lookup_table<int32_t, int32_t, 8>::
fromp(const int32_t* tbl) const
{
    return _mm256_i32gather_epi32(
        reinterpret_cast<const int*>(tbl), _msk, sizeof(int32_t));
}

inline
__m256i
cftal::impl::fixed_vec_lookup_table<4, int32_t, int32_t, 8>::
setup_msk(const vec<int32_t, 8>& idx)
{
    return idx();
}

inline
cftal::impl::fixed_vec_lookup_table<4, int32_t, int32_t, 8>::
fixed_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v8s32
cftal::impl::fixed_vec_lookup_table<4, int32_t, int32_t, 8>::
fromp(const int32_t* tbl) const
{
    vec<int32_t, 4> rh=mem<vec<int32_t, 4> >::load(tbl, 4);
    __m256i r=_mm256_castsi128_si256(rh());
    r=_mm256_permutevar8x32_epi32(r, _msk);
    return r;
}

inline
__m256i
cftal::impl::fixed_vec_lookup_table<8, int32_t, int32_t, 8>::
setup_msk(const vec<int32_t, 8>& idx)
{
    return idx();
}

inline
cftal::impl::fixed_vec_lookup_table<8, int32_t, int32_t, 8>::
fixed_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v8s32
cftal::impl::fixed_vec_lookup_table<8, int32_t, int32_t, 8>::
fromp(const int32_t* tbl) const
{
    v8s32 r;
    if (__likely(is_aligned_to<32>(tbl))) {
        r=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl)), _msk);
    } else {
        __m256i t=_mm256_loadu_epi32(tbl);
        r=_mm256_permutevar8x32_epi32(t, _msk);
    }
    return r;
}

inline
cftal::impl::fixed_vec_lookup_table<32, int32_t, int32_t, 8>::
fixed_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(idx()),
      _idx_gt_7(_mm256_cmpgt_epi32(idx(), _mm256_set1_epi32(7))),
      _idx_gt_15(_mm256_cmpgt_epi32(idx(), _mm256_set1_epi32(15))),
      _idx_gt_23(_mm256_cmpgt_epi32(idx(), _mm256_set1_epi32(23)))
{
}

inline
cftal::v8s32
cftal::impl::fixed_vec_lookup_table<32, int32_t, int32_t, 8>::
fromp(const int32_t* tbl) const
{
    v8s32 r0, r1, r2, r3;
    if (__likely(is_aligned_to<32>(tbl))) {
        r0=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+0)), _msk);
        r1=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+8)), _msk);
        r2=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+16)), _msk);
        r3=_mm256_permutevar8x32_epi32(
            *(reinterpret_cast<const __m256i*>(tbl+24)), _msk);
    } else {
        r0=mem<vec<int32_t, 8> >::load(tbl, 8);
        r1=mem<vec<int32_t, 8> >::load(tbl+8, 8);
        r2=mem<vec<int32_t, 8> >::load(tbl+16, 8);
        r3=mem<vec<int32_t, 8> >::load(tbl+24, 8);
        r0=_mm256_permutevar8x32_epi32(r0(), _msk);
        r1=_mm256_permutevar8x32_epi32(r1(), _msk);
        r2=_mm256_permutevar8x32_epi32(r2(), _msk);
        r3=_mm256_permutevar8x32_epi32(r3(), _msk);
    }
    __m256i r01i=x86::select_u32(_idx_gt_7, r1(), r0());
    __m256i r23i=x86::select_u32(_idx_gt_23, r3(), r2());
    __m256i ri=x86::select_u32(_idx_gt_15, r23i, r01i);
    vec<int32_t, 8> r(ri);
    return r;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8S32_INL__
