//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V4F32__)
#define __CFTAL_X86_V4F32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec_float_n.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/v4s32.h>

namespace cftal {

    template <>
    class vec<float, 4> : public x86::vreg<__m128> {
    public:
        using base_type = x86::vreg<__m128>;

        using value_type = float;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using x86::vreg<__m128>::vreg;
        vec() = default;
        // create vec{v,v,v,v,....}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 2>& lh, const vec<float, 2>& hh);

        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<float, 4>, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 4> > {
        using type = vec<float, 4>;
    };

    template <>
    struct mem< vec<float, 4> > {
        static
        vec<float, 4> load(const float* p, std::size_t n=4);
        static
        void store(float* p, const vec<float, 4>& v);
    };

    vec<float, 2>
    low_half(const vec<float, 4>& s);

    vec<float, 2>
    high_half(const vec<float, 4>& s);

    template <std::size_t _I>
    float
    extract(const vec<float, 4>& s);

    vec<float, 4>
    select(const vec<float, 4>::mask_type& msk,
           const vec<float, 4>& on_true,
           const vec<float, 4>& on_false);

    vec<float, 4>
    select_val_or_zero(const vec<float, 4>::mask_type& msk,
                       const vec<float, 4>& on_true);

    vec<float, 4>
    select_zero_or_val(const vec<float, 4>::mask_type& msk,
                       const vec<float, 4>& on_false);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<float, 4>::mask_type& a);

    bool
    any_of(const vec<float, 4>::mask_type& a);

    bool
    none_of(const vec<float, 4>::mask_type& a);
#endif

    unsigned
    read_signs(const vec<float, 4>& b);

    bool
    elements_equal(const vec<float, 4>& v);

    v4f32 max(const v4f32& a, const v4f32& b);
    v4f32 min(const v4f32& a, const v4f32& b);
    v4f32 abs(const v4f32& a);
    v4f32 fabs(const v4f32& a);
    v4f32 sqrt(const v4f32& a);
    v4f32 hypot(const v4f32& a, const v4f32& b);

    v4f32 native_rsqrt(const v4f32& a);

    namespace x86 {
        v4f32 round(const v4f32& v, rounding_mode::type m);
    }

    v4f32 rint(const v4f32& a);
    v4f32 floor(const v4f32& a);
    v4f32 ceil(const v4f32& a);
    v4f32 trunc(const v4f32& a);
    // returns (~a) & (b)
    v4f32 andnot(const v4f32& a, const v4f32& b);
    v4f32 copysign(const v4f32& x, const v4f32& y);
    v4f32 mulsign(const v4f32& x, const v4f32& y);
#if 0
    v4f32::mask_type isinf(const v4f32& x);
    v4f32::mask_type isnan(const v4f32& x);
    v4f32::mask_type isfinite(const v4f32& x);
#endif

    // a*b +c
    v4f32 fma(const v4f32& a, const v4f32& b, const v4f32& c);
    // a*b -c
    v4f32 fms(const v4f32& a, const v4f32& b, const v4f32& c);
    // -(a*b) + c
    v4f32 nfma(const v4f32& a, const v4f32& b, const v4f32& c);
    // -(a*b) - c
    v4f32 nfms(const v4f32& a, const v4f32& b, const v4f32& c);

#if 0
    // a*b +c with rounding or not
    v4f32 mad(const v4f32& a, const v4f32& b, const v4f32& c);
    // -(a*b) +c with rounding or not
    v4f32 nmad(const v4f32& a, const v4f32& b, const v4f32& c);
#endif

    template <bool _P0, bool _P1,
              bool _P2, bool _P3>
    vec<float, 4>
    select(const vec<float, 4>& on_true,
           const vec<float, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<float, 4>
    permute(const vec<float, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<float, 4>
    permute(const vec<float, 4>& s0,
            const vec<float, 4>& s1);

    vec<float, 2>
    native_recip(const vec<float, 2>& b);

    vec<float, 4>
    native_recip(const vec<float, 4>& b);

    vec<float, 2>
    native_div(const vec<float, 2>& a, const vec<float, 2>& b);

    vec<float, 4>
    native_div(const vec<float, 4>& a, const vec<float, 4>& b);


    namespace op {

        template <>
        struct bit_not<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one.f32());
                return _mm_xor_ps(a(), all_set());
            }
        };


        template <>
        struct lt<float, 4> {
            using full_type = vec<float, 4>;
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
        struct le<float, 4> {
            using full_type = vec<float, 4>;
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
        struct eq<float, 4> {
            using full_type = vec<float, 4>;
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
        struct ne<float, 4> {
            using full_type = vec<float, 4>;
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
        struct ge<float, 4> {
            using full_type = vec<float, 4>;
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
        struct gt<float, 4> {
            using full_type = vec<float, 4>;
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
        struct plus<float, 4> {
            using full_type = vec<float, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type msk(sign_f32_msk::v.f32());
                return _mm_xor_ps(a(), msk());
            }
        };

        template <>
        struct add<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_ps(a(), b());
            }
        };

        template <>
        struct sub<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_ps(a(), b());
            }
        };

        template <>
        struct mul<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_mul_ps(a(), b());
            }
        };

        template <>
        struct div<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_div_ps(a(), b());
            }
        };

        template <>
        struct fma<float, 4> {
            using full_type = vec<float, 4>;
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
        struct fms<float, 4> {
            using full_type = vec<float, 4>;
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
        struct fnma<float, 4> {
            using full_type = vec<float, 4>;
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
        struct bit_or<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_ps(a(), b());
            }
        };

        template <>
        struct bit_and<float, 4> {
            using full_type = vec<float, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_ps(a(), b());
            }
        };

        template <>
        struct bit_xor<float, 4> {
            using full_type = vec<float, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_ps(a(), b());
            }
        };

    }

}

inline
cftal::vec<float, 4>::vec(float v)
    : base_type(_mm_set1_ps(v))
{
}

inline
cftal::vec<float, 4>::
vec(std::initializer_list<float> l)
    : vec(mem<vec<float, 4> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 4>::
vec(init_list<float> l)
    : vec(mem<vec<float, 4> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 4>::
vec(const vec<float, 2>& lh, const vec<float, 2>& hh)
    : vec{low_half(lh)(), high_half(lh)(),
        low_half(hh)(), high_half(hh)()}
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<float, 4>::vec(const expr<_OP<float, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<float, 4>
cftal::mem<cftal::vec<float, 4> >::load(const float* p, std::size_t s)
{
    __m128 v;
    switch (s) {
    default:
    case 4:
        v = _mm_loadu_ps(p);
        break;
    case 3:
        v = _mm_setr_ps(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_ps(p[0], p[1], p[1], p[1]);

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
cftal::mem<cftal::vec<float, 4>>::store(float* p, const vec<float, 4>& v)
{
    _mm_storeu_ps(p, v());
}

inline
cftal::vec<float, 2>
cftal::low_half(const vec<float, 4>& v)
{
    return vec<float, 2>{extract<0>(v), extract<1>(v)};
}

inline
cftal::vec<float, 2>
cftal::high_half(const vec<float, 4>& v)
{
    return vec<float, 2>{extract<2>(v), extract<3>(v)};
}

template <std::size_t _I>
float
cftal::extract(const vec<float, 4>& v)
{
    return x86::extract_f32<_I>(v());
}

inline
cftal::v4f32 cftal::select(const v4f32::mask_type& m,
                           const v4f32& on_true,
                           const v4f32& on_false)
{
    return x86::select_f32(m(), on_true(), on_false());
}

inline
cftal::v4f32
cftal::select_val_or_zero(const v4f32::mask_type& m,
                          const v4f32& on_true)
{
    return _mm_and_ps(m(), on_true());
}

inline
cftal::v4f32
cftal::select_zero_or_val(const v4f32::mask_type& m,
                          const v4f32& on_false)
{
    return _mm_andnot_ps(m(), on_false());
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
inline
cftal::v4f32 cftal::select(const v4f32& a, const v4f32& b)
{
    return x86::select_f32<_P0, _P1, _P2, _P3> (a(), b());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
cftal::v4f32 cftal::permute(const v4f32& a)
{
    return x86::perm_v4f32<_P0, _P1, _P2, _P3>(a());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
cftal::v4f32 cftal::permute(const v4f32& a, const v4f32& b)
{
    return x86::perm_v4f32<_P0, _P1, _P2, _P3>(a(), b());
}

inline
cftal::v4f32 cftal::sqrt(const v4f32& a)
{
    return _mm_sqrt_ps(a());
}

inline
cftal::v4f32 cftal::abs(const v4f32& a)
{
    const v4f32 msk(not_sign_f32_msk::v.f32());
    return _mm_and_ps(a(), msk());
}

inline
cftal::v4f32 cftal::min(const v4f32& a, const v4f32& b)
{
    return _mm_min_ps(a(), b());
}

inline
cftal::v4f32 cftal::max(const v4f32& a, const v4f32& b)
{
    return _mm_max_ps(a(), b());
}


inline
cftal::v4f32 cftal::andnot(const v4f32& a, const v4f32& b)
{
    return _mm_andnot_ps(a(), b());
}

inline
cftal::v4f32
cftal::fma(const v4f32& a, const v4f32& b, const v4f32& c)
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
cftal::v4f32
cftal::fms(const v4f32& a, const v4f32& b, const v4f32& c)
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
cftal::v4f32
cftal::nfma(const v4f32& a, const v4f32& b, const v4f32& c)
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
cftal::v4f32
cftal::nfms(const v4f32& a, const v4f32& b, const v4f32& c)
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
cftal::v4f32
cftal::mad(const v4f32& a, const v4f32& b, const v4f32& c)
{
    return a * b + c;
}

inline
cftal::v4f32
cftal::nmad(const v4f32& a, const v4f32& b, const v4f32& c)
{
    return c -(a * b);
}

inline
cftal::vec<float, 4>::mask_type
cftal::isnan(const v4f32& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

inline
cftal::vec<float, 4>::mask_type
cftal::isinf(const v4f32& x)
{
    v4f32 absx(abs(x));
    return absx == v4f32(exp_32_msk::v._f32);
}
#endif

inline
cftal::v4f32 cftal::copysign(const v4f32& x, const v4f32& y)
{
    // return abs(x) * sgn(y)
    const v4f32 msk(not_sign_f32_msk::v.f32());
    v4f32 abs_x(x & msk);
    v4f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v4f32 cftal::mulsign(const v4f32& x, const v4f32& y)
{
    const v4f32 msk(sign_f32_msk::v.f32());
    v4f32 sgn_y = y & msk;
    return x ^ sgn_y;
}

#if !defined (__AVX512VL__)
inline
bool cftal::all_of(const v4f32::mask_type& a)
{
    return x86::read_signs_f32(a()) == 0xf;
}

inline
bool cftal::any_of(const v4f32::mask_type& a)
{
    return x86::read_signs_f32(a()) != 0;
}

inline
bool cftal::none_of(const v4f32::mask_type& a)
{
    return x86::read_signs_f32(a()) == 0;
}
#endif

inline
unsigned cftal::read_signs(const v4f32& a)
{
    return x86::read_signs_f32(a());
}

inline
bool cftal::elements_equal(const v4f32& a)
{
    float t0= extract<0>(a);
    v4f32 cmp0(t0);
    v4f32::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v4f32
cftal::native_rsqrt(const v4f32& x)
{
    v4f32 y= _mm_rsqrt_ps(x());
    y = y + 0.5* y * (1- (x * y) * y);
    return y;
}

inline
cftal::v4f32 cftal::x86::round(const v4f32& a, const rounding_mode::type m)
{
    v4f32 r;
#if defined (__SSE4_1__)
    switch (m) {
    case rounding_mode::nearest:
        r= _mm_round_ps(a(), 0);
        break;
    case rounding_mode::downward:
        r= _mm_round_ps(a(), 1);
        break;
    case rounding_mode::upward:
        r= _mm_round_ps(a(), 2);
        break;
    case rounding_mode::towardzero:
        r= _mm_round_ps(a(), 3);
        break;
    case rounding_mode::current:
        r= _mm_round_ps(a(), 4);
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
    const v4f32 sgn_msk(sign_f32_msk::v._f32);
    // (127+23)<< 23 = 0x4B000000 = 2^23
    const __m128 magic= const_v4u32<0x4B000000, 0x4B000000,
                                    0x4B000000, 0x4B000000>::fv();
    __m128 sign = _mm_and_ps(a(), sgn_msk());
    __m128 sign_magic = _mm_or_ps(magic, sign);
    r= _mm_add_ps(a(), sign_magic);
    r = _mm_sub_ps(r(), sign_magic);
    if (mxcsr != rmxcsr)
        _mm_setcsr(mxcsr);
    r = select(abs(a) > v4f32(magic), a, r);
#endif
    return r;
}

inline
cftal::v4f32 cftal::rint(const v4f32& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v4f32 cftal::floor(const v4f32& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v4f32 cftal::ceil(const v4f32& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v4f32 cftal::trunc(const v4f32& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

inline
cftal::v2f32
cftal::native_recip(const v2f32& y)
{
    v4f32 y4(y, y);
    return low_half(native_recip(y4));
}

inline
cftal::v4f32
cftal::native_recip(const v4f32& a)
{
    v4f32 rcp=_mm_rcp_ps(a());
    rcp = rcp + rcp*(1-rcp*a);
    return rcp;
}

inline
cftal::v2f32
cftal::native_div(const v2f32& b, const v2f32& a)
{
    v4f32 b4(b, b);
    v4f32 a4(a, a);
    return low_half(native_div(b4, a4));
}

inline
cftal::v4f32
cftal::native_div(const v4f32& b, const v4f32& a)
{
    return native_recip(a) * b;
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F32__
