//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V8F32_INL_H__)
#define __CFTAL_X86_V8F32_INL_H__ 1

#if defined (__AVX__)
#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/x86/v8f32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4f32.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    namespace impl {
#if defined (__AVX2__)
        template <std::size_t _L>
        struct lookup<_L, int32_t, float, 8> {
            static
            vec<float, 8>
            v(const vec<int32_t, 8>& idx, const float* tbl) {
                return _mm256_i32gather_ps(tbl, idx(), sizeof(float));
            }
        };
#endif
    }

    namespace op {

        template <>
        struct bit_not<float, 8> {
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
        struct lt<float, 8> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_LT_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_LT_OS);
#endif
            }
        };

        template <>
        struct le<float, 8> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_LE_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_LE_OS);
#endif
            }
        };

        template <>
        struct eq<float, 8> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_EQ_OQ);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_EQ_OQ);
#endif
            }
        };

        template <>
        struct ne<float, 8> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_NEQ_UQ);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_NEQ_UQ);
#endif
            }
        };

        template <>
        struct ge<float, 8> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_GE_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_GE_OS);
#endif
            }
        };

        template <>
        struct gt<float, 8> {
            using full_type = vec<float, 8>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm256_cmp_ps_mask(a(), b(), _CMP_GT_OS);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_GT_OS);
#endif
            }
        };

        template <>
        struct plus<float, 8> {
            using full_type = vec<float, 8>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a) {
                const full_type msk(sign_f32_msk::v.f32());
                return _mm256_xor_ps(a(), msk());
            }
        };

        template <>
        struct add<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_ps(a(), b());
            }
        };

        template <>
        struct sub<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_ps(a(), b());
            }
        };

        template <>
        struct mul<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_mul_ps(a(), b());
            }
        };

        template <>
        struct div<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_div_ps(a(), b());
            }
        };

#if 0
        template <>
        struct mod<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

        template <>
        struct fma<float, 8> {
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
        struct fms<float, 8> {
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
        struct fnma<float, 8> {
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
        struct bit_or<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_ps(a(), b());
            }
        };

        template <>
        struct bit_and<float, 8> {
            using full_type = vec<float, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_ps(a(), b());
            }
        };

        template <>
        struct bit_xor<float, 8> {
            using full_type = vec<float, 8>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_ps(a(), b());
            }
        };

#if 0
        template <>
        struct shl<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };
#endif

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
    : base_type(x86::impl::vinsertf128<1>::v(as<__m256>(lh()),
                                             hh()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 8>::vec(const expr<_OP<float, 8>, _L, _R>& r)
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
        v = _mm256_setr_ps(p[0], p[0], p[0], p[0],
                           p[0], p[0], p[0], p[0]);
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

template <std::size_t _I>
float
cftal::extract(const vec<float, 8>& v)
{
    return x86::extract_f32<_I>(v());
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
    return _mm256_and_ps(m(), on_true());
}

inline
cftal::v8f32
cftal::select_zero_or_val(const v8f32::mask_type& m,
                          const v8f32& on_false)
{
    return _mm256_andnot_ps(m(), on_false());
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

#if 0
inline
cftal::v8f32
cftal::mad(const v8f32& a, const v8f32& b, const v8f32& c)
{
    return a * b + c;
}

inline
cftal::v8f32
cftal::nmad(const v8f32& a, const v8f32& b, const v8f32& c)
{
    return c -(a * b);
}

inline
cftal::vec<float, 8>::mask_type
cftal::isnan(const v8f32& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

inline
cftal::vec<float, 8>::mask_type
cftal::isinf(const v8f32& x)
{
    v8f32 absx(abs(x));
    return absx == v8f32(exp_32_msk::v._f32);
}
#endif

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

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const v8f32::mask_type& a)
{
    return x86::read_signs_f32(a()) == 0xff;
}

inline
bool cftal::any_of(const v8f32::mask_type& a)
{
    return x86::read_signs_f32(a()) != 0;
}

inline
bool cftal::none_of(const v8f32::mask_type& a)
{
    return x86::read_signs_f32(a()) == 0;
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
cftal::v8f32
cftal::native_rsqrt(const v8f32& x)
{
    v8f32 y= _mm256_rsqrt_ps(x());
    y = y + (0.5f*y) * (1.0f- y*(x * y));
    // y= 0.5f*y *(3.0f - y*(y*x));
    return y;
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

inline
cftal::v8f32
cftal::native_recip(const v8f32& a)
{
    v8f32 rcp=_mm256_rcp_ps(a());
    rcp = rcp + rcp*(1-rcp*a);
    return rcp;
}

inline
cftal::v8f32
cftal::native_div(const v8f32& b, const v8f32& a)
{
    return native_recip(a) * b;
}

#endif
// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F32_INL_H__
