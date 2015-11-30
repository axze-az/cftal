#if !defined (__CFTAL_X86_V8F32_H__)
#define __CFTAL_X86_V8F32_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec_float_n.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v4f32.h>
#include <cftal/x86/ops_1.h>

namespace cftal {

    template <>
    class vec<float, 8> : public x86::vreg<__m256> {
    public:
        using base_type = x86::vreg<__m256>;

        using value_type = float;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 8>;

        using x86::vreg<__m256>::vreg;
        vec() = default;
        // create vec{v,v,v,v,....}
        vec(float v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 16>
        vec(init_list<float> l);
        // allow construction from two halfes
        vec(const vec<float, 4>& lh, const vec<float, 4>& hh);

        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<float, 8>, _L, _R>& r);
    };

    template <>
    struct arg< vec<float, 8> > {
        using type = vec<float, 8>;
    };

    template <>
    struct mem< vec<float, 8> > {
        static
        vec<float, 8> load(const float* p, std::size_t n=8);
        static
        void store(float* p, const vec<float, 8>& v);
    };

    vec<float, 4>
    low_half(const vec<float, 8>& s);

    vec<float, 4>
    high_half(const vec<float, 8>& s);

    template <std::size_t _I>
    float
    extract(const vec<float, 8>& s);
    
    vec<float, 8>
    select(const typename vec<float, 8>::mask_type& msk,
           const vec<float, 8>& on_true,
           const vec<float, 8>& on_false);

#if !defined (__AVX512VL__)    
    bool
    all_of(const vec<float, 8>::mask_type& a);

    bool
    any_of(const vec<float, 8>::mask_type& a);

    bool
    none_of(const vec<float, 8>::mask_type& a);
#endif
    
    unsigned
    read_signs(const vec<float, 8>& b);

    bool
    elements_equal(const vec<float, 8>& v);
    
    vec<float, 8>
    cbrt(vec<float, 8> v);

    v8f32 max(const v8f32& a, const v8f32& b);
    v8f32 min(const v8f32& a, const v8f32& b);
    v8f32 abs(const v8f32& a);
    v8f32 fabs(const v8f32& a);
    v8f32 sqrt(const v8f32& a);
    v8f32 hypot(const v8f32& a, const v8f32& b);

    v8f32 rsqrt(const v8f32& a);
    v8f32 native_rsqrt(const v8f32& a);

    namespace x86 {
        v8f32 round(const v8f32& v, rounding_mode::type m);
    }

    v8f32 rint(const v8f32& a);
    v8f32 floor(const v8f32& a);
    v8f32 ceil(const v8f32& a);
    v8f32 trunc(const v8f32& a);
    // returns (~a) & (b)
    v8f32 andnot(const v8f32& a, const v8f32& b);
    v8f32 copysign(const v8f32& x, const v8f32& y);
    v8f32 mulsign(const v8f32& x, const v8f32& y);
#if 0
    v8f32::mask_type isinf(const v8f32& x);
    v8f32::mask_type isnan(const v8f32& x);
    v8f32::mask_type isfinite(const v8f32& x);
#endif


    // a*b +c
    v8f32 fma(const v8f32& a, const v8f32& b, const v8f32& c);
    // a*b -c
    v8f32 fms(const v8f32& a, const v8f32& b, const v8f32& c);
    // -(a*b) + c
    v8f32 nfma(const v8f32& a, const v8f32& b, const v8f32& c);
    // -(a*b) - c
    v8f32 nfms(const v8f32& a, const v8f32& b, const v8f32& c);

#if 0    
    // a*b +c with rounding or not
    v8f32 mad(const v8f32& a, const v8f32& b, const v8f32& c);
    // -(a*b) +c with rounding or not
    v8f32 nmad(const v8f32& a, const v8f32& b, const v8f32& c);
#endif
    
    template <bool _P0, bool _P1,
              bool _P2, bool _P3,
              bool _P4, bool _P5,
              bool _P6, bool _P7>
    vec<float, 8>
    select(const vec<float, 8>& on_true,
           const vec<float, 8>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5,
              int32_t _P6, int32_t _P7>
    vec<float, 8>
    permute(const vec<float, 8>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3,
              int32_t _P4, int32_t _P5,
              int32_t _P6, int32_t _P7>
    vec<float, 8>
    permute(const vec<float, 8>& s0,
            const vec<float, 8>& s1);

    namespace op {

        template <>
        struct bit_not<float, 8> {
            using full_type = vec<float, 8>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one._f32);
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
                return _mm256_cmp_ps_mask(a(), b(), _CMP_UNORD_Q);
#else
                return _mm256_cmp_ps(a(), b(), _CMP_UNORD_Q);
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
                const full_type msk(sign_f32_msk::v._f32);
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
cftal::v8f32 cftal::select(const v8f32::mask_type& m,
                           const v8f32& on_true,
                           const v8f32& on_false)
{
    return x86::select(m(), on_true(), on_false());
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
    return x86::perm_f32<_P0, _P1, _P2, _P3,
                         _P4, _P5, _P6, _P7>(a());
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
cftal::v8f32 cftal::permute(const v8f32& a, const v8f32& b)
{
    return x86::perm_f32<_P0, _P1, _P2, _P3,
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
    const v8f32 msk(not_sign_f32_msk::v._f32);
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
    const v8f32 msk(not_sign_f32_msk::v._f32);
    v8f32 abs_x(x & msk);
    v8f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v8f32 cftal::mulsign(const v8f32& x, const v8f32& y)
{
    const v8f32 msk(sign_f32_msk::v._f32);
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
cftal::v8f32 cftal::x86::round(const v8f32& a, const rounding_mode::type m)
{
    v8f32 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm256_round_ps(a(), 0);
        break;
    case rounding_mode::downward:
        r= _mm256_round_ps(a(), 1);
        break;
    case rounding_mode::upward:
        r= _mm256_round_ps(a(), 2);
        break;
    case rounding_mode::towardzero:
        r= _mm256_round_ps(a(), 3);
        break;
    case rounding_mode::current:
        r= _mm256_round_ps(a(), 4);
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

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V8F32__
