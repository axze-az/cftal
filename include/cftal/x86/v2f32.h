//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_X86_V2F32__)
#define __CFTAL_X86_V2F32__ 1

#include <cftal/config.h>

#if X86_64_SPECIALIZE_V2F32 > 0

#include <cftal/types.h>
#include <cftal/vec_t_n.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2f64.h>
#include <cftal/x86/v4f64.h>
#include <cftal/x86/v4s32.h>

namespace cftal {

#define V2F32_SPECIALIZED 1

    template <>
    class vec<float, 2>  {
        union _rep {
            double _d;
            float _f[2];

            static
            double
            _castps_f64(__m128 f) {
#if defined (__clang__) /* || defined (__GNUC__) */
                return _mm_cvtsd_f64(_mm_castps_pd(f));
#else
                double r;
                __asm__ ("" : "=x" (r) : "0"(f));
                return r;
#endif
            }

            static
            __m128
            _castf64_ps(double d) {
#if defined (__clang__) /* || defined (__GNUC__) */
                return _mm_castpd_ps(_mm_setr_pd(d, 0.0));
#else
                __m128 r;
                __asm__ ("" : "=x" (r) : "0"(d));
                return r;
#endif
            }

            _rep() = default;
            constexpr
            _rep(double d) : _d(d) {}
            _rep(float l, float h) : _d(_castps_f64(
                _mm_setr_ps(l, h, l, h))) {}
        };
        _rep _v;
    public:
        using value_type = float;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 2>;

        __m128 operator()() const;
        vec() = default;
        vec(__m128 f);
        // create vec{v,v,v,v,....}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 1>& lh, const vec<float, 1>& hh);
         // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<float, 2>, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 2> > {
        using type = vec<float, 2>;
    };

    template <>
    struct is_vec_specialized<vec<float, 2> > : public std::true_type {};

    template <>
    struct mem< vec<float, 2> > {
        static
        vec<float, 2> load(const float* p, std::size_t n=4);
        static
        void store(float* p, const vec<float, 2>& v);
    };

    vec<float, 1>
    low_half(const vec<float, 2>& s);

    vec<float, 1>
    high_half(const vec<float, 2>& s);

    template <std::size_t _I>
    float
    extract(const vec<float, 2>& s);

    vec<float, 2>
    select(const vec<float, 2>::mask_type& msk,
           const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    vec<float, 2>
    select_val_or_zero(const vec<float, 2>::mask_type& msk,
                       const vec<float, 2>& on_true);

    vec<float, 2>
    select_zero_or_val(const vec<float, 2>::mask_type& msk,
                       const vec<float, 2>& on_false);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<float, 2>::mask_type& a);

    bool
    any_of(const vec<float, 2>::mask_type& a);

    bool
    none_of(const vec<float, 2>::mask_type& a);
#endif

    unsigned
    read_signs(const vec<float, 2>& b);

    bool
    elements_equal(const vec<float, 2>& v);

    v2f32 max(const v2f32& a, const v2f32& b);
    v2f32 min(const v2f32& a, const v2f32& b);
    v2f32 abs(const v2f32& a);
    v2f32 fabs(const v2f32& a);
    v2f32 sqrt(const v2f32& a);

    v2f32 native_rsqrt(const v2f32& a);

    namespace x86 {
        v2f32 round(const v2f32& v, rounding_mode::type m);
    }

    v2f32 rint(const v2f32& a);
    v2f32 floor(const v2f32& a);
    v2f32 ceil(const v2f32& a);
    v2f32 trunc(const v2f32& a);
    // returns (~a) & (b)
    v2f32 andnot(const v2f32& a, const v2f32& b);
    v2f32 copysign(const v2f32& x, const v2f32& y);
    v2f32 mulsign(const v2f32& x, const v2f32& y);
#if 0
    v2f32::mask_type isinf(const v2f32& x);
    v2f32::mask_type isnan(const v2f32& x);
    v2f32::mask_type isfinite(const v2f32& x);
#endif

    // a*b +c
    v2f32 fma(const v2f32& a, const v2f32& b, const v2f32& c);
    // a*b -c
    v2f32 fms(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) + c
    v2f32 nfma(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) - c
    v2f32 nfms(const v2f32& a, const v2f32& b, const v2f32& c);

#if 0
    // a*b +c with rounding or not
    v2f32 mad(const v2f32& a, const v2f32& b, const v2f32& c);
    // -(a*b) +c with rounding or not
    v2f32 nmad(const v2f32& a, const v2f32& b, const v2f32& c);
#endif

    template <bool _P0, bool _P1>
    vec<float, 2>
    select(const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<float, 2>
    permute(const vec<float, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<float, 2>
    permute(const vec<float, 2>& s0,
            const vec<float, 2>& s1);

    vec<float, 2>
    native_recip(const vec<float, 2>& b);

    vec<float, 2>
    native_recip(const vec<float, 2>& b);

    vec<float, 2>
    native_div(const vec<float, 2>& a, const vec<float, 2>& b);

    vec<float, 2>
    native_div(const vec<float, 2>& a, const vec<float, 2>& b);

}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F32__
