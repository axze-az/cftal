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
#if !defined (__CFTAL_X86_V8F32_INL_H__)
#define __CFTAL_X86_V8F32_INL_H__ 1

#if defined (__AVX__)
#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/math/misc.h>
#include <cftal/x86/v8f32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4f32.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one.f32());
                return _mm256_xor_ps(a(), all_set());
            }
        };

        template <>
        struct lt<vec<float, 8>> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_LT_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_LT_OS);
#endif
            }
        };

        template <>
        struct le<vec<float, 8>> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_LE_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_LE_OS);
#endif
            }
        };

        template <>
        struct eq<vec<float, 8>> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_EQ_OQ);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_EQ_OQ);
#endif
            }
        };

        template <>
        struct ne<vec<float, 8>> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_NEQ_UQ);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_NEQ_UQ);
#endif
            }
        };

        template <>
        struct ge<vec<float, 8>> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_GE_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_GE_OS);
#endif
            }
        };

        template <>
        struct gt<vec<float, 8>> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_GT_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_GT_OS);
#endif
            }
        };

        template <>
        struct plus<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type msk(sign_f32_msk::v.f32());
                return _mm256_xor_ps(a(), msk());
            }
        };

        template <>
        struct add<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_ps(a(), b());
            }
        };

        template <>
        struct sub<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_ps(a(), b());
            }
        };

        template <>
        struct mul<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_mul_ps(a(), b());
            }
        };

        template <>
        struct div<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_div_ps(a(), b());
            }
        };


        template <>
        struct fma<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_macc_ps(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fmadd_ps(a(), b(), c());
#else
                return _mm256_add_ps(_mm256_mul_ps(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_msub_ps(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fmsub_ps(a(), b(), c());
#else
                return _mm256_sub_ps(_mm256_mul_ps(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_nmacc_ps(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fnmadd_ps(a(), b(), c());
#else
                return _mm256_sub_ps(c(), _mm256_mul_ps(a(), b()));
#endif
            }
        };

        template <>
        struct bit_or<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_ps(a(), b());
            }
        };

        template <>
        struct bit_and<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_ps(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<float, 8>> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_ps(a(), b());
            }
        };
    }

}

inline
cftal::vec<float, 8>::vec(float v)
    : base_type(_mm256_set1_ps(v))
{
}

inline
cftal::vec<float, 8>::
vec(std::initializer_list<float> l)
    : vec(mem<vec<float, 8> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 8>::
vec(init_list<float> l)
    : vec(mem<vec<float, 8> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 8>::
vec(const vec<float, 4>& lh, const vec<float, 4>& hh)
    : base_type(x86::vinsertf128<1>::v(as<__m256>(lh()),
                                             hh()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 8>::vec(const expr<_OP<vec<float, 8> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<float, 8>
cftal::mem<cftal::vec<float, 8> >::load(const float* p, std::size_t s)
{
    __m256 v;
    switch (s) {
    default:
    case 8:
        v = _mm256_loadu_ps(p);
        break;
    case 7:
        v = _mm256_setr_ps(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[6], p[6]);
        break;
    case 6:
        v = _mm256_setr_ps(p[0], p[1], p[2], p[3],
                           p[4], p[5], p[5], p[5]);
        break;
    case 5:
        v = _mm256_setr_ps(p[0], p[1], p[2], p[3],
                           p[4], p[4], p[4], p[4]);
        break;
    case 4:
        v = _mm256_setr_ps(p[0], p[1], p[2], p[3],
                           p[3], p[3], p[3], p[3]);
        break;
    case 3:
        v = _mm256_setr_ps(p[0], p[1], p[2], p[2],
                           p[2], p[2], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_ps(p[0], p[1], p[1], p[1],
                           p[1], p[1], p[1], p[1]);

        break;
    case 1:
        v = _mm256_broadcast_ss(p);
        // v = _mm256_setr_ps(p[0], p[0], p[0], p[0],
        //                    p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_setr_ps(0.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<float, 8>>::store(float* p, const vec<float, 8>& v)
{
    _mm256_storeu_ps(p, v());
}

inline
cftal::vec<float, 4>
cftal::low_half(const cftal::vec<float, 8>& v)
{
    return _mm256_castps256_ps128(v());
}

inline
cftal::vec<float, 4>
cftal::high_half(const cftal::vec<float, 8>& v)
{
    return _mm256_extractf128_ps(v(), 1);
}

template <cftal::size_t _I>
inline
float
cftal::extract(const vec<float, 8>& v)
{
    return x86::extract_f32<_I>(v());
}

inline
float
cftal::extract(const vec<float, 8>& v, size_t i)
{
    return x86::extract_f32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<float, 8>& v, const float& vi)
{
    v= x86::insert_f32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<float, 8>& v, const float& vi, size_t i)
{
    v= x86::insert_f32(v(), vi, i);
}

inline
cftal::v8f32
cftal::select(const v8f32::mask_type& m,
              const v8f32& on_true, const v8f32& on_false)
{
    return x86::select_f32(m(), on_true(), on_false());
}

inline
cftal::v8f32
cftal::select_val_or_zero(const v8f32::mask_type& m,
                          const v8f32& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_and_ps(m(), on_true());
#else
    return _mm256_maskz_mov_ps(m(), on_true());
#endif
}

inline
cftal::v8f32
cftal::select_zero_or_val(const v8f32::mask_type& m,
                          const v8f32& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm256_andnot_ps(m(), on_false());
#else
    return _mm256_maskz_mov_ps(_knot_mask8(m()), on_false());
#endif
}

template <bool _P0, bool _P1, bool _P2, bool _P3,
          bool _P4, bool _P5, bool _P6, bool _P7>
inline
cftal::v8f32 cftal::select(const v8f32& a, const v8f32& b)
{
    return x86::select_f32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7> (a(), b());
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
cftal::v8f32 cftal::permute(const v8f32& a)
{
    return x86::perm_v8f32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>(a());
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
cftal::v8f32 cftal::permute(const v8f32& a, const v8f32& b)
{
    return x86::perm_v8f32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>(a(), b());
}

#if defined (__AVX2__)
inline
cftal::v8f32
cftal::permute(const v8f32& s, const v8s32& idx)
{
    return x86::permute_v8f32_v8s32(s(), idx());
}
#endif

inline
cftal::v8f32 cftal::sqrt(const v8f32& a)
{
    return _mm256_sqrt_ps(a());
}

inline
cftal::v8f32 cftal::max(const v8f32& a, const v8f32& b)
{
    return _mm256_max_ps(a(), b());
}

inline
cftal::v8f32 cftal::min(const v8f32& a, const v8f32& b)
{
    return _mm256_min_ps(a(), b());
}


inline
cftal::v8f32 cftal::abs(const v8f32& a)
{
    const v8f32 msk(not_sign_f32_msk::v.f32());
    return _mm256_and_ps(a(), msk());
}

inline
cftal::v8f32 cftal::andnot(const v8f32& a, const v8f32& b)
{
    return _mm256_andnot_ps(a(), b());
}

inline
cftal::v8f32
cftal::fma(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__)
    return _mm256_macc_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fmadd_ps(a(), b(), c());
#else
    // return impl::fma(a, b, c);
    return a * b + c;
#endif
}

inline
cftal::v8f32
cftal::fms(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__)
    return _mm256_msub_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fmsub_ps(a(), b(), c());
#else
    // return impl::fma(a, b, -c);
    return a * b - c;
#endif
}

inline
cftal::v8f32
cftal::nfma(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__)
    return _mm256_nmacc_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fnmadd_ps(a(), b(), c());
#else
    // return impl::fma(-a, b, c);
    return c - a*b;
#endif
}

inline
cftal::v8f32
cftal::nfms(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__)
    return _mm256_nmsub_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm256_fnmsub_ps(a(), b(), c());
#else
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
#endif
}

inline
cftal::v8f32 cftal::copysign(const v8f32& x, const v8f32& y)
{
    // return abs(x) * sgn(y)
    const v8f32 msk(not_sign_f32_msk::v.f32());
    v8f32 abs_x(x & msk);
    v8f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v8f32 cftal::mulsign(const v8f32& x, const v8f32& y)
{
    const v8f32 msk(sign_f32_msk::v.f32());
    v8f32 sgn_y = y & msk;
    return x ^ sgn_y;
}

#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__==0)
inline
bool cftal::all_of(const v8f32::mask_type& a)
{
    return x86::all_of_f32(a());
}

inline
bool cftal::any_of(const v8f32::mask_type& a)
{
    return x86::any_of_f32(a());
}

inline
bool cftal::none_of(const v8f32::mask_type& a)
{
    return x86::any_of_f32(a());
}

inline
cftal::vec<cftal::bit, 8>
cftal::compress_mask(const vec<float, 8>::mask_type& v)
{
    return x86::compress_mask_f32(v());
}

inline
cftal::vec<float, 8>
cftal::expand_mask<cftal::vec<float, 8> >::
from(const vec<bit, 8>& s)
{
    return x86::expand_mask_v8f32(s());
}

#endif

inline
unsigned cftal::read_signs(const v8f32& a)
{
    return x86::read_signs_f32(a());
}

inline
bool cftal::elements_equal(const v8f32& a)
{
    float t0= extract<0>(a);
    v8f32 cmp0(t0);
    v8f32::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v8f32 cftal::x86::round(const v8f32& a, const rounding_mode::type m)
{
    v8f32 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm256_round_ps(a(), 0+8);
        break;
    case rounding_mode::downward:
        r= _mm256_round_ps(a(), 1+8);
        break;
    case rounding_mode::upward:
        r= _mm256_round_ps(a(), 2+8);
        break;
    case rounding_mode::towardzero:
        r= _mm256_round_ps(a(), 3+8);
        break;
    case rounding_mode::current:
        r= _mm256_round_ps(a(), 4+8);
        break;
    }
    return r;
}

inline
cftal::v8f32 cftal::rint(const v8f32& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v8f32 cftal::floor(const v8f32& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v8f32 cftal::ceil(const v8f32& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v8f32 cftal::trunc(const v8f32& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

#if defined (__AVX2__)
inline
cftal::variable_vec_lookup_table<float, int32_t, 8>::
variable_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(idx)
{
}

inline
cftal::v8f32
cftal::variable_vec_lookup_table<float, int32_t, 8>::
from(const float* tbl) const
{
    return _mm256_i32gather_ps(tbl, _msk(), sizeof(float));
}
#endif

inline
__m256i
cftal::impl::fixed_vec_lookup_table<4, float, int32_t, 8>::
setup_msk(const vec<int32_t, 8>& idx)
{
#if defined (__AVX2__)
    return idx();
#else
    __m256i i=_mm256_setr_m128i(low_half(idx)(), high_half(idx)());
    return i;
#endif
}

inline
cftal::impl::fixed_vec_lookup_table<4, float, int32_t, 8>::
fixed_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v8f32
cftal::impl::fixed_vec_lookup_table<4, float, int32_t, 8>::
fromp(const float* tbl) const
{
#if defined (__AVX2__)
    vec<float, 4> rh=mem<vec<float, 4> >::load(tbl, 4);
    __m256 r=_mm256_castps128_ps256(rh());
    r=_mm256_permutevar8x32_ps(r, _msk);
#else
    vec<float, 8> r=_mm256_broadcast_ps(
        reinterpret_cast<const __m128*>(tbl));
    r=_mm256_permutevar_ps(r(), _msk);
#endif
    return r;
}

#if defined (__AVX2__)
inline
__m256i
cftal::impl::fixed_vec_lookup_table<8, float, int32_t, 8>::
setup_msk(const vec<int32_t, 8>& idx)
{
    return idx();
}

inline
cftal::impl::fixed_vec_lookup_table<8, float, int32_t, 8>::
fixed_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v8f32
cftal::impl::fixed_vec_lookup_table<8, float, int32_t, 8>::
fromp(const float* tbl) const
{
    vec<float, 8> r=mem<vec<float, 8> >::load(tbl, 8);
    r=_mm256_permutevar8x32_ps(r(), _msk);
    return r;
}

inline
cftal::impl::fixed_vec_lookup_table<32, float, int32_t, 8>::
fixed_vec_lookup_table(const vec<int32_t, 8>& idx)
    : _msk(idx()),
      _idx_gt_7(_mm256_cmpgt_epi32(idx(), _mm256_set1_epi32(7))),
      _idx_gt_15(_mm256_cmpgt_epi32(idx(), _mm256_set1_epi32(15))),
      _idx_gt_23(_mm256_cmpgt_epi32(idx(), _mm256_set1_epi32(23)))
{
}

inline
cftal::v8f32
cftal::impl::fixed_vec_lookup_table<32, float, int32_t, 8>::
fromp(const float* tbl) const
{
    vec<float, 8> r0=mem<vec<float, 8> >::load(tbl, 8);
    vec<float, 8> r1=mem<vec<float, 8> >::load(tbl+8, 8);
    vec<float, 8> r2=mem<vec<float, 8> >::load(tbl+16, 8);
    vec<float, 8> r3=mem<vec<float, 8> >::load(tbl+24, 8);
    r0=_mm256_permutevar8x32_ps(r0(), _msk);
    r1=_mm256_permutevar8x32_ps(r1(), _msk);
    r2=_mm256_permutevar8x32_ps(r2(), _msk);
    r3=_mm256_permutevar8x32_ps(r3(), _msk);
    __m256i r0i=_mm256_castps_si256(r0());
    __m256i r1i=_mm256_castps_si256(r1());
    __m256i r2i=_mm256_castps_si256(r2());
    __m256i r3i=_mm256_castps_si256(r3());

    __m256i r01i=x86::select_u32(_idx_gt_7, r1i, r0i);
    __m256i r23i=x86::select_u32(_idx_gt_23, r3i, r2i);
    __m256i ri=x86::select_u32(_idx_gt_15, r23i, r01i);
    vec<float, 8> r(_mm256_castsi256_ps(ri));
    return r;
}

#endif

#endif
// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F32_INL_H__
