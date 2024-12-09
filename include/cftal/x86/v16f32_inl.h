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
#if !defined (__CFTAL_X86_V16F32_INL_H__)
#define __CFTAL_X86_V16F32_INL_H__ 1

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/math/misc.h>
#include <cftal/x86/v16f32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4f32.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one.f32());
                return _mm512_xor_ps(a(), all_set());
            }
        };

        template <>
        struct lt<vec<float, 16>> {
            using full_type = vec<float, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_ps_mask(a(), b(), _CMP_LT_OS);
            }
        };

        template <>
        struct le<vec<float, 16>> {
            using full_type = vec<float, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_ps_mask(a(), b(), _CMP_LE_OS);
            }
        };

        template <>
        struct eq<vec<float, 16>> {
            using full_type = vec<float, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_ps_mask(a(), b(), _CMP_EQ_OQ);
            }
        };

        template <>
        struct ne<vec<float, 16>> {
            using full_type = vec<float, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_ps_mask(a(), b(), _CMP_NEQ_UQ);
            }
        };

        template <>
        struct ge<vec<float, 16>> {
            using full_type = vec<float, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_ps_mask(a(), b(), _CMP_GE_OS);
            }
        };

        template <>
        struct gt<vec<float, 16>> {
            using full_type = vec<float, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmp_ps_mask(a(), b(), _CMP_GT_OS);
            }
        };

        template <>
        struct plus<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a) {
                const full_type msk(sign_f32_msk::v.f32());
                return _mm512_xor_ps(a(), msk());
            }
        };

        template <>
        struct add<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_add_ps(a(), b());
            }
        };

        template <>
        struct sub<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_sub_ps(a(), b());
            }
        };

        template <>
        struct mul<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_mul_ps(a(), b());
            }
        };

        template <>
        struct div<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_div_ps(a(), b());
            }
        };


        template <>
        struct fma<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA__)
                return _mm512_fmadd_ps(a(), b(), c());
#else
                return _mm512_add_ps(_mm512_mul_ps(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA__)
                return _mm512_fmsub_ps(a(), b(), c());
#else
                return _mm512_sub_ps(_mm512_mul_ps(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA__)
                return _mm512_fnmadd_ps(a(), b(), c());
#else
                return _mm512_sub_ps(c(), _mm512_mul_ps(a(), b()));
#endif
            }
        };

        template <>
        struct bit_or<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_or_ps(a(), b());
            }
        };

        template <>
        struct bit_and<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_and_ps(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<float, 16>> {
            using full_type = vec<float, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_xor_ps(a(), b());
            }
        };
    }

}

inline
cftal::vec<float, 16>::vec(float v)
    : base_type(_mm512_set1_ps(v))
{
}

inline
cftal::vec<float, 16>::
vec(std::initializer_list<float> l)
    : vec(mem<vec<float, 16> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 16>::
vec(init_list<float> l)
    : vec(mem<vec<float, 16> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 16>::
vec(const vec<float, 8>& lh, const vec<float, 8>& hh)
    : base_type(_mm512_insertf32x8(as<__m512>(lh()), hh(), 1))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 16>::vec(const expr<_OP<vec<float, 16> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<float, 16>
cftal::mem<cftal::vec<float, 16> >::load(const float* p, std::size_t s)
{
    __m512 v;
    switch (s) {
    case 16:
        v = _mm512_loadu_ps(reinterpret_cast<const __m512i*>(p));
        break;
    case 0:
        v = _mm512_set1_ps(0.0f);
        break;
    default: {
            x86::vecunion<uint16_t, 16, __m512, __m512d, __m512i> st;
            std::uint32_t si=s & 15;
            float pi=p[0];
            st._s[0]=pi;
            for (uint32_t i=1; i<si; ++i) {
                pi=p[i];
                st._s[i]=pi;
            }
            for (uint32_t i=si; i<16; ++i) {
                st._s[i]=pi;
            }
            v=_mm512_loadu_ps(&st._vi);
            break;
    }}
    return v;
}

inline
void
cftal::mem<cftal::vec<float, 16>>::store(float* p, const vec<float, 16>& v)
{
    _mm512_storeu_ps(p, v());
}

inline
cftal::vec<float, 8>
cftal::low_half(const cftal::vec<float, 16>& v)
{
    return _mm512_castps512_ps256(v());
}

inline
cftal::vec<float, 8>
cftal::high_half(const cftal::vec<float, 16>& v)
{
    return _mm512_extractf32x8_ps(v(), 1);
}

template <cftal::size_t _I>
inline
float
cftal::extract(const vec<float, 16>& v)
{
    return x86::extract_f32<_I>(v());
}

inline
float
cftal::extract(const vec<float, 16>& v, size_t i)
{
    return x86::extract_f32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<float, 16>& v, const float& vi)
{
    v= x86::insert_f32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<float, 16>& v, const float& vi, size_t i)
{
    v= x86::insert_f32(v(), vi, i);
}

inline
cftal::v16f32
cftal::select(const v16f32::mask_type& m,
              const v16f32& on_true, const v16f32& on_false)
{
    return x86::select_f32(m(), on_true(), on_false());
}

inline
cftal::v16f32
cftal::select_val_or_zero(const v16f32::mask_type& m,
                          const v16f32& on_true)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm512_and_ps(m(), on_true());
#else
    return _mm512_maskz_mov_ps(m(), on_true());
#endif
}

inline
cftal::v16f32
cftal::select_zero_or_val(const v16f32::mask_type& m,
                          const v16f32& on_false)
{
#if !defined (__AVX512VL__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm512_andnot_ps(m(), on_false());
#else
    return _mm512_maskz_mov_ps(_knot_mask16(m()), on_false());
#endif
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline
cftal::v16f32 cftal::select(const v16f32& a, const v16f32& b)
{
    return x86::select_f32<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15> (a(), b());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16f32 cftal::permute(const v16f32& a)
{
    return x86::perm_v16f32<_P00, _P01, _P02, _P03,
                            _P04, _P05, _P06, _P07,
                            _P08, _P09, _P10, _P11,
                            _P12, _P13, _P14, _P15>(a());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16f32 cftal::permute(const v16f32& a, const v16f32& b)
{
    return x86::perm_v16f32<_P00, _P01, _P02, _P03,
                            _P04, _P05, _P06, _P07,
                            _P08, _P09, _P10, _P11,
                            _P12, _P13, _P14, _P15>(a(), b());
}

inline
cftal::v16f32 cftal::sqrt(const v16f32& a)
{
    return _mm512_sqrt_ps(a());
}

inline
cftal::v16f32 cftal::max(const v16f32& a, const v16f32& b)
{
    return _mm512_max_ps(a(), b());
}

inline
cftal::v16f32 cftal::min(const v16f32& a, const v16f32& b)
{
    return _mm512_min_ps(a(), b());
}


inline
cftal::v16f32 cftal::abs(const v16f32& a)
{
    const v16f32 msk(not_sign_f32_msk::v.f32());
    return _mm512_and_ps(a(), msk());
}

inline
cftal::v16f32 cftal::andnot(const v16f32& a, const v16f32& b)
{
    return _mm512_andnot_ps(a(), b());
}

inline
cftal::v16f32
cftal::fma(const v16f32& a, const v16f32& b, const v16f32& c)
{
#if defined (__FMA__)
    return _mm512_fmadd_ps(a(), b(), c());
#else
    // return impl::fma(a, b, c);
    return a * b + c;
#endif
}

inline
cftal::v16f32
cftal::fms(const v16f32& a, const v16f32& b, const v16f32& c)
{
#if defined (__FMA__)
    return _mm512_fmsub_ps(a(), b(), c());
#else
    // return impl::fma(a, b, -c);
    return a * b - c;
#endif
}

inline
cftal::v16f32
cftal::nfma(const v16f32& a, const v16f32& b, const v16f32& c)
{
#if defined (__FMA__)
    return _mm512_fnmadd_ps(a(), b(), c());
#else
    // return impl::fma(-a, b, c);
    return c - a*b;
#endif
}

inline
cftal::v16f32
cftal::nfms(const v16f32& a, const v16f32& b, const v16f32& c)
{
#if defined (__FMA__)
    return _mm512_fnmsub_ps(a(), b(), c());
#else
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
#endif
}

inline
cftal::v16f32 cftal::copysign(const v16f32& x, const v16f32& y)
{
    // return abs(x) * sgn(y)
    const v16f32 msk(not_sign_f32_msk::v.f32());
    v16f32 abs_x(x & msk);
    v16f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v16f32 cftal::mulsign(const v16f32& x, const v16f32& y)
{
    const v16f32 msk(sign_f32_msk::v.f32());
    v16f32 sgn_y = y & msk;
    return x ^ sgn_y;
}

inline
unsigned cftal::read_signs(const v16f32::mask_type& a)
{
    return x86::read_signs_f32(a());
}

inline
bool cftal::elements_equal(const v16f32& a)
{
    float t0= extract<0>(a);
    v16f32 cmp0(t0);
    v16f32::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v16f32 cftal::x86::round(const v16f32& a, const rounding_mode::type m)
{
    v16f32 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm512_roundscale_round_ps(a(), 0, 8);
        break;
    case rounding_mode::downward:
        r= _mm512_roundscale_round_ps(a(), 1, 8);
        break;
    case rounding_mode::upward:
        r= _mm512_roundscale_round_ps(a(), 2, 8);
        break;
    case rounding_mode::towardzero:
        r= _mm512_roundscale_round_ps(a(), 3, 8);
        break;
    case rounding_mode::current:
        r= _mm512_roundscale_round_ps(a(), 4, 8);
        break;
    }
    return r;
}

inline
cftal::v16f32 cftal::rint(const v16f32& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v16f32 cftal::floor(const v16f32& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v16f32 cftal::ceil(const v16f32& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v16f32 cftal::trunc(const v16f32& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

inline
cftal::v16f32
cftal::permute(const v16f32& s, const v16s32& idx)
{
    return x86::permute_v16f32_v16s32(s(), idx());
}

inline
cftal::variable_vec_lookup_table<float, int32_t, 16>::
variable_vec_lookup_table(const vec<int32_t, 16>& idx)
    : _msk(idx)
{
}

inline
cftal::v16f32
cftal::variable_vec_lookup_table<float, int32_t, 16>::
from(const float* tbl) const
{
    return x86::vgatherdps<__m512, __m512i>::v<sizeof(float)>(tbl, _msk());
}

inline
__m512i
cftal::impl::fixed_vec_lookup_table<4, float, int32_t, 16>::
setup_msk(const vec<int32_t, 16>& idx)
{
    return idx();
}

inline
cftal::impl::fixed_vec_lookup_table<4, float, int32_t, 16>::
fixed_vec_lookup_table(const vec<int32_t, 16>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v16f32
cftal::impl::fixed_vec_lookup_table<4, float, int32_t, 16>::
fromp(const float* tbl) const
{
    vec<float, 4> rh=mem<vec<float, 4> >::load(tbl, 4);
    __m512 r=_mm512_castps128_ps512(rh());
    r=_mm512_permutexvar_ps(_msk, r);
    return r;
}

inline
__m512i
cftal::impl::fixed_vec_lookup_table<8, float, int32_t, 16>::
setup_msk(const vec<int32_t, 16>& idx)
{
    return idx();
}

inline
cftal::impl::fixed_vec_lookup_table<8, float, int32_t, 16>::
fixed_vec_lookup_table(const vec<int32_t, 16>& idx)
    : _msk(setup_msk(idx))
{
}

inline
cftal::v16f32
cftal::impl::fixed_vec_lookup_table<8, float, int32_t, 16>::
fromp(const float* tbl) const
{
    vec<float, 16> r=mem<vec<float, 16> >::load(tbl, 16);
    r=_mm512_permutexvar_ps(_msk, r());
    return r;
}

inline
cftal::impl::fixed_vec_lookup_table<32, float, int32_t, 16>::
fixed_vec_lookup_table(const vec<int32_t, 16>& idx)
    : _msk(idx()),
      _idx_gt_15(_mm512_cmpgt_epi32_mask(idx(), _mm512_set1_epi32(15)))
{
}

inline
cftal::v16f32
cftal::impl::fixed_vec_lookup_table<32, float, int32_t, 16>::
fromp(const float* tbl) const
{
    vec<float, 16> r0=mem<vec<float, 16> >::load(tbl, 16);
    vec<float, 16> r1=mem<vec<float, 16> >::load(tbl+16, 16);
    r0=_mm512_permutexvar_ps(_msk, r0());
    r1=_mm512_permutexvar_ps(_msk, r1());
    vec<float, 16> r=x86::select_f32(_idx_gt_15, r1(), r0());
    return r;
}

#endif // __AVX512 ..
// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V16F32_INL_H__
