//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V2F32_INL__)
#define __CFTAL_X86_V2F32_INL__ 1

#include <cftal/config.h>

#if X86_64_SPECIALIZE_V2F32 > 0

#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/x86/v2f32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/v4s32.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<float, 2> {
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
        struct lt<float, 2> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_ps_mask(a(), b(), _CMP_LT_OS);
#else
                return _mm_cmplt_ps(a(), b());
#endif
            }
        };

        template <>
        struct le<float, 2> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_ps_mask(a(), b(), _CMP_LE_OS);
#else
                return _mm_cmple_ps(a(), b());
#endif
            }
        };

        template <>
        struct eq<float, 2> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_ps_mask(a(), b(), _CMP_EQ_OQ);
#else
                return _mm_cmpeq_ps(a(), b());
#endif
            }
        };

        template <>
        struct ne<float, 2> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_ps_mask(a(), b(), _CMP_NEQ_UQ);
#else
                return _mm_cmpneq_ps(a(), b());
#endif
            }
        };

        template <>
        struct ge<float, 2> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_ps_mask(a(), b(), _CMP_GE_OS);
#else
                return _mm_cmpge_ps(a(), b());
#endif

            }
        };

        template <>
        struct gt<float, 2> {
            using full_type = vec<float, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__AVX512VL__)
                return _mm_cmp_ps_mask(a(), b(), _CMP_GT_OS);
#else
                return _mm_cmpgt_ps(a(), b());
#endif
            }
        };

        template <>
        struct plus<float, 2> {
            using full_type = vec<float, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a) {
                const full_type msk(sign_f32_msk::v.f32());
                return _mm_xor_ps(a(), msk());
            }
        };

        template <>
        struct add<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_ps(a(), b());
            }
        };

        template <>
        struct sub<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_ps(a(), b());
            }
        };

        template <>
        struct mul<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_mul_ps(a(), b());
            }
        };

        template <>
        struct div<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_div_ps(a(), b());
            }
        };

        template <>
        struct fma<float, 2> {
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
        struct fms<float, 2> {
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
        struct fnma<float, 2> {
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
        struct bit_or<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_ps(a(), b());
            }
        };

        template <>
        struct bit_and<float, 2> {
            using full_type = vec<float, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_ps(a(), b());
            }
        };

        template <>
        struct bit_xor<float, 2> {
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
    : _v(_rep::_castps_f64(v))
{
}

inline
__m128
cftal::vec<float, 2>::operator()() const
{
    return _rep::_castf64_ps(_v._d);
}

inline
cftal::vec<float, 2>::vec(float v)
    : _v(v, v)
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
    : _v(lh(), hh())
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 2>::vec(const expr<_OP<float, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<float, 2>
cftal::mem<cftal::vec<float, 2> >::load(const float* p, std::size_t s)
{
    __m128 v;
    switch (s) {
    default:
    case 2:
        v = _mm_setr_ps(p[0], p[1], p[0], p[1]);
        break;
    case 1:
        v = _mm_setr_ps(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_ps(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<float, 2>>::store(float* p, const vec<float, 2>& v)
{
    auto pd=reinterpret_cast<double*>(p);
    _mm_storel_pd(pd, _mm_castps_pd(v()));
}

inline
cftal::vec<float, 1>
cftal::low_half(const vec<float, 2>& v)
{
    return vec<float, 1>{extract<0>(v)};
}

inline
cftal::vec<float, 1>
cftal::high_half(const vec<float, 2>& v)
{
    return vec<float, 1>{extract<1>(v)};
}

template <std::size_t _I>
float
cftal::extract(const vec<float, 2>& v)
{
    return x86::extract_f32<_I>(v());
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
    return _mm_and_ps(m(), on_true());
}

inline
cftal::v2f32
cftal::select_zero_or_val(const v2f32::mask_type& m,
                          const v2f32& on_false)
{
    return _mm_andnot_ps(m(), on_false());
}

template <bool _P0, bool _P1>
inline
cftal::v2f32 cftal::select(const v2f32& a, const v2f32& b)
{
    return x86::select_f32<_P0, _P1, true, true> (a(), b());
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
    __m128 t=x86::impl::vshufps<0, 1, 0, 1>::v(a(), b());
    return x86::perm_v4f32<_P0, _P1, _P0, _P1>(t);
    // return x86::perm_v4f32<_P0, _P1, _P0, _P1>(a(), b());
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

#if 0
inline
cftal::v2f32
cftal::mad(const v2f32& a, const v2f32& b, const v2f32& c)
{
    return a * b + c;
}

inline
cftal::v2f32
cftal::nmad(const v2f32& a, const v2f32& b, const v2f32& c)
{
    return c -(a * b);
}

inline
cftal::vec<float, 2>::mask_type
cftal::isnan(const v2f32& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

inline
cftal::vec<float, 2>::mask_type
cftal::isinf(const v2f32& x)
{
    v2f32 absx(abs(x));
    return absx == v2f32(exp_32_msk::v._f32);
}
#endif

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

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const v2f32::mask_type& a)
{
    return (x86::read_signs_f32(a()) & 0x3) == 0x3;
}

inline
bool cftal::any_of(const v2f32::mask_type& a)
{
    return (x86::read_signs_f32(a()) & 0x3) != 0;
}

inline
bool cftal::none_of(const v2f32::mask_type& a)
{
    return (x86::read_signs_f32(a()) & 0x3) == 0;
}
#endif

inline
unsigned cftal::read_signs(const v2f32& a)
{
    return (x86::read_signs_f32(a()) & 0x3);
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
cftal::v2f32
cftal::native_rsqrt(const v2f32& x)
{
    v2f32 y= _mm_rsqrt_ps(x());
    y = y + (0.5f*y) * (1.0f- y*(x * y));
    // y= 0.5f*y *(3.0f - y*(y*x));
    return y;
}

inline
cftal::v2f32 cftal::x86::round(const v2f32& a, const rounding_mode::type m)
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
        if (unlikely(mxcsr != rmxcsr))
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

inline
cftal::v2f32
cftal::native_recip(const v2f32& a)
{
    v2f32 rcp=_mm_rcp_ps(a());
    rcp = rcp + rcp*(1-rcp*a);
    return rcp;
}

inline
cftal::v2f32
cftal::native_div(const v2f32& b, const v2f32& a)
{
    return native_recip(a) * b;
}
#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2f32_INL__
