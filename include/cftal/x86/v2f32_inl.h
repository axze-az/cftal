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
#if !defined (__CFTAL_X86_V2F32_INL_H__)
#define __CFTAL_X86_V2F32_INL_H__ 1

#include <cftal/config.h>

#if __CFTAL_CFG_USE_8_BYTE_VECS_ON_X86__> 0

#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/math/misc.h>
#include <cftal/vec_t_1.h>
#include <cftal/x86/v2f32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/v4s32.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one.f32());
                return _mm_xor_ps(a(), all_set());
            }
        };

        template <>
        struct lt<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_ps_mask(a(), b(), _CMP_LT_OS);
#else
                return _mm_cmplt_ps(a(), b());
#endif
            }
        };

        template <>
        struct le<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_ps_mask(a(), b(), _CMP_LE_OS);
#else
                return _mm_cmple_ps(a(), b());
#endif
            }
        };

        template <>
        struct eq<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_ps_mask(a(), b(), _CMP_EQ_OQ);
#else
                return _mm_cmpeq_ps(a(), b());
#endif
            }
        };

        template <>
        struct ne<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_ps_mask(a(), b(), _CMP_NEQ_UQ);
#else
                return _mm_cmpneq_ps(a(), b());
#endif
            }
        };

        template <>
        struct ge<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_ps_mask(a(), b(), _CMP_GE_OS);
#else
                return _mm_cmpge_ps(a(), b());
#endif

            }
        };

        template <>
        struct gt<vec<float, 2>> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
                return _mm_cmp_ps_mask(a(), b(), _CMP_GT_OS);
#else
                return _mm_cmpgt_ps(a(), b());
#endif
            }
        };

        template <>
        struct plus<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type msk(sign_f32_msk::v.f32());
                return _mm_xor_ps(a(), msk());
            }
        };

        template <>
        struct add<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_ps(a(), b());
            }
        };

        template <>
        struct sub<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_ps(a(), b());
            }
        };

        template <>
        struct mul<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_mul_ps(a(), b());
            }
        };

        template <>
        struct div<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_div_ps(a(), b());
            }
        };

        template <>
        struct fma<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm_macc_ps(a(), b(), c());
#elif defined (__FMA__)
                return _mm_fmadd_ps(a(), b(), c());
#else
                return _mm_add_ps(_mm_mul_ps(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm_msub_ps(a(), b(), c());
#elif defined (__FMA__)
                return _mm_fmsub_ps(a(), b(), c());
#else
                return _mm_sub_ps(_mm_mul_ps(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm_nmacc_ps(a(), b(), c());
#elif defined (__FMA__)
                return _mm_fnmadd_ps(a(), b(), c());
#else
                return _mm_sub_ps(c(), _mm_mul_ps(a(), b()));
#endif
            }
        };

        template <>
        struct bit_or<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_ps(a(), b());
            }
        };

        template <>
        struct bit_and<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_ps(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<float, 2>> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_ps(a(), b());
            }
        };

    }

}

inline
cftal::vec<float, 2>::vec(__m128 v)
    : _v(v)
{
}

inline
cftal::vec<float, 2>::vec(float v)
    : _v(_mm_set1_ps(v))
{
}

inline
cftal::vec<float, 2>::
vec(std::initializer_list<float> l)
    : vec(mem<vec<float, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 2>::
vec(init_list<float> l)
    : vec(mem<vec<float, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 2>::
vec(const vec<float, 1>& lh, const vec<float, 1>& hh)
    : _v(_mm_setr_ps(lh(), hh(), 0.0f, 0.0f))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 2>::vec(const expr<_OP<vec<float, 2> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<float, 2>
cftal::mem<cftal::vec<float, 2> >::load(const float* p, ssize_t s)
{
    __m128 v;
    if (s>=2) {
        const double* dp=reinterpret_cast<const double*>(p);
        v = _mm_cvtpd_ps(_mm_load_sd(dp));
    } else if (s==1) {
        v = _mm_load_ss(p);
    } else {
        v = _mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<float, 2>>::
store(float* p, const vec<float, 2>& v, ssize_t s)
{
    if (s>=2) {
        auto pp=reinterpret_cast<__m64*>(p);
        _mm_storel_pi(pp, v());
    } else if (s==1) {
        _mm_store_ss(p, v());
    }
}

inline
cftal::vec<float, 1>
cftal::low_half(const vec<float, 2>& v)
{
    float f=extract<0>(v);
    return vec<float, 1>(f);
}

inline
cftal::vec<float, 1>
cftal::high_half(const vec<float, 2>& v)
{
    float f=extract<1>(v);
    return vec<float, 1>(f);
}

template <cftal::size_t _I>
inline
float
cftal::extract(const vec<float, 2>& v)
{
    return x86::extract_f32<_I>(v());
}

inline
float
cftal::extract(const vec<float, 2>& v, size_t i)
{
    return x86::extract_f32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<float, 2>& v, const float& vi)
{
    v= x86::insert_f32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<float, 2>& v, const float& vi, size_t i)
{
    v= x86::insert_f32(v(), vi, i);
}

inline
cftal::v2f32 cftal::select(const v2f32::mask_type& m,
                           const v2f32& on_true,
                           const v2f32& on_false)
{
    return x86::select_f32(m(), on_true(), on_false());
}

inline
cftal::v2f32
cftal::select_val_or_zero(const v2f32::mask_type& m,
                          const v2f32& on_true)
{
#if !defined (__AVX512F__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_and_ps(m(), on_true());
#else
    return _mm_maskz_mov_ps(m(), on_true());
#endif
}

inline
cftal::v2f32
cftal::select_zero_or_val(const v2f32::mask_type& m,
                          const v2f32& on_false)
{
#if !defined (__AVX512F__) || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
    return _mm_andnot_ps(m(), on_false());
#else
    return _mm_maskz_mov_ps(_knot_mask8(m()), on_false());
#endif
}

template <bool _P0, bool _P1>
inline
cftal::v2f32 cftal::select(const v2f32& a, const v2f32& b)
{
    return x86::select_f32<_P0, _P1, false, false> (a(), b());
}

template <int _P0, int _P1>
inline
cftal::v2f32 cftal::permute(const v2f32& a)
{
    return x86::perm_v4f32<_P0, _P1, 2, 3>(a());
}

template <int _P0, int _P1>
inline
cftal::v2f32 cftal::permute(const v2f32& a, const v2f32& b)
{
    v4f32 t(a, b);
    return x86::perm_v4f32<_P0, _P1, 2, 3>(t());
}

inline
cftal::v2f32
cftal::permute(const v2f32& s, const v2s32& idx)
{
    __m128i ii=_mm_setr_epi32(extract<0>(idx),
                              extract<1>(idx),
                              0, 0);
    return x86::permute_v4f32_v4s32(s(), ii);
}

inline
cftal::v2f32 cftal::sqrt(const v2f32& a)
{
    return _mm_sqrt_ps(a());
}

inline
cftal::v2f32 cftal::abs(const v2f32& a)
{
    const v2f32 msk(not_sign_f32_msk::v.f32());
    return _mm_and_ps(a(), msk());
}

inline
cftal::v2f32 cftal::min(const v2f32& a, const v2f32& b)
{
    return _mm_min_ps(a(), b());
}

inline
cftal::v2f32 cftal::max(const v2f32& a, const v2f32& b)
{
    return _mm_max_ps(a(), b());
}


inline
cftal::v2f32 cftal::andnot(const v2f32& a, const v2f32& b)
{
    return _mm_andnot_ps(a(), b());
}

inline
cftal::v2f32
cftal::fma(const v2f32& a, const v2f32& b, const v2f32& c)
{
#if defined (__FMA4__)
    return _mm_macc_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fmadd_ps(a(), b(), c());
#else
    // return impl::fma(a, b, c);
    return a * b + c;
#endif
}

inline
cftal::v2f32
cftal::fms(const v2f32& a, const v2f32& b, const v2f32& c)
{
#if defined (__FMA4__)
    return _mm_msub_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fmsub_ps(a(), b(), c());
#else
    // return impl::fma(a, b, -c);
    return a * b - c;
#endif
}

inline
cftal::v2f32
cftal::nfma(const v2f32& a, const v2f32& b, const v2f32& c)
{
#if defined (__FMA4__)
    return _mm_nmacc_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fnmadd_ps(a(), b(), c());
#else
    // return impl::fma(-a, b, c);
    return c - a*b;
#endif
}

inline
cftal::v2f32
cftal::nfms(const v2f32& a, const v2f32& b, const v2f32& c)
{
#if defined (__FMA4__)
    return _mm_nmsub_ps(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fnmsub_ps(a(), b(), c());
#else
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
#endif
}

inline
cftal::v2f32 cftal::copysign(const v2f32& x, const v2f32& y)
{
    // return abs(x) * sgn(y)
    const v2f32 msk(not_sign_f32_msk::v.f32());
    v2f32 abs_x(x & msk);
    v2f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v2f32 cftal::mulsign(const v2f32& x, const v2f32& y)
{
    const v2f32 msk(sign_f32_msk::v.f32());
    v2f32 sgn_y = y & msk;
    return x ^ sgn_y;
}

#if !defined (__AVX512VL__)  || (__CFTAL_CFG_ENABLE_AVX512__ == 0)
inline
bool cftal::all_of(const v2f32::mask_type& a)
{
    // return x86::all_of_f32(a());
    return (x86::compress_mask_f32(a()) & 0x03) == 0x03;
}

inline
bool cftal::any_of(const v2f32::mask_type& a)
{
    // return x86::any_of_f32(a());
    return (x86::compress_mask_f32(a()) & 0x03) != 0x00;
}

inline
bool cftal::none_of(const v2f32::mask_type& a)
{
    // return x86::none_of_f32(a());
    return (x86::compress_mask_f32(a()) & 0x03) != 0x00;
}

inline
cftal::vec<cftal::bit, 2>
cftal::compress_mask(const vec<float, 2>::mask_type& v)
{
    return x86::compress_mask_f32(v()) & 0x03;
}

inline
cftal::vec<float, 2>
cftal::expand_mask<cftal::vec<float, 2> >::
from(const vec<bit, 2>& s)
{
    return x86::expand_mask_v4f32(s());
}

#endif

inline
unsigned cftal::read_signs(const v2f32& a)
{
    return x86::read_signs_f32(a());
}

inline
bool cftal::elements_equal(const v2f32& a)
{
    float t0= extract<0>(a);
    v2f32 cmp0(t0);
    v2f32::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v2f32 cftal::x86::round(const v2f32& a, const rounding_mode m)
{
    v2f32 r;
#if defined (__SSE4_1__)
    switch (m) {
    case rounding_mode::nearest:
        r= _mm_round_ps(a(), 0+8);
        break;
    case rounding_mode::downward:
        r= _mm_round_ps(a(), 1+8);
        break;
    case rounding_mode::upward:
        r= _mm_round_ps(a(), 2+8);
        break;
    case rounding_mode::towardzero:
        r= _mm_round_ps(a(), 3+8);
        break;
    case rounding_mode::current:
        r= _mm_round_ps(a(), 4+8);
        break;
    }
#else
    uint32_t mxcsr=0;
    uint32_t rmxcsr=0;
    if (m != rounding_mode::current) {
        mxcsr = _mm_getcsr();
        rmxcsr= mxcsr;
        rmxcsr &= ~(3<<13);
        switch (m) {
        case rounding_mode::nearest: //0
            break;
        case rounding_mode::downward:
            rmxcsr |= (1<<13);
            break;
        case rounding_mode::upward:
            rmxcsr |= (2<<13);
            break;
        case rounding_mode::towardzero:
            rmxcsr |= (3<<13);
            break;
        default:
            break; // keep the compiler happy
        }
        if (__unlikely(mxcsr != rmxcsr))
            _mm_setcsr(rmxcsr);
    }
    const v2f32 sgn_msk(sign_f32_msk::v.f32());
    // (127+23)<< 23 = 0x4B000000 = 2^23
    const __m128 magic= const_v4u32<0x4B000000, 0x4B000000,
                                    0x4B000000, 0x4B000000>::fv();
    __m128 sign = _mm_and_ps(a(), sgn_msk());
    __m128 sign_magic = _mm_or_ps(magic, sign);
    r= _mm_add_ps(a(), sign_magic);
    r = _mm_sub_ps(r(), sign_magic);
    if (mxcsr != rmxcsr)
        _mm_setcsr(mxcsr);
    r = select(abs(a) > v2f32(magic), a, r);
#endif
    return r;
}

inline
cftal::v2f32 cftal::rint(const v2f32& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v2f32 cftal::floor(const v2f32& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v2f32 cftal::ceil(const v2f32& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v2f32 cftal::trunc(const v2f32& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

#endif
// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F32_INL_H__
