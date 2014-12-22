#if !defined (__CFTAL_X86_V4F32__)
#define __CFTAL_X86_V4F32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_float_n.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_vreg.h>
#include <cftal/x86_v2f64.h>
#include <cftal/x86_v4s32.h>

namespace cftal {

    template <>
    class vec<float, 4> : public x86::vreg<__m128> {
    public:
        using base_type = x86::vreg<__m128>;

        using value_type = float;
        using mask_value_type = float;
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

#if 0    
    vec<float, 4>
    low_half(const vec<float, 4>& s);

    vec<float, 4>
    high_half(const vec<float, 4>& s);
#endif
    
    template <std::size_t _I>
    float
    extract(const vec<float, 4>& s);
    
    vec<float, 4>
    select(const typename vec<float, 4>::mask_type& msk,
           const vec<float, 4>& on_true,
           const vec<float, 4>& on_false);

    bool
    all_signs(const vec<float, 4>& a);

    bool
    no_signs(const vec<float, 4>& a);

    bool
    both_signs(const vec<float, 4>& a);

    unsigned
    read_signs(const vec<float, 4>& b);

    bool
    elements_equal(const vec<float, 4>& v);
    
    vec<float, 4>
    cbrt(vec<float, 4> v);

    v4f32 max(const v4f32& a, const v4f32& b);
    v4f32 min(const v4f32& a, const v4f32& b);
    v4f32 abs(const v4f32& a);
    v4f32 fabs(const v4f32& a);
    v4f32 sqrt(const v4f32& a);
    v4f32 cbrt(arg<v4f32>::type a);
    v4f32 hypot(const v4f32& a, const v4f32& b);

    v4f32 rsqrt(const v4f32& a);
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

    v4f32 frexp(arg<v4f32>::type x, v4s32* e);
    // v4f32 pow2i(arg<v4s32>::type e);
    v4f32 ldexp(arg<v4f32>::type d, arg<v4s32>::type e);
    v4s32 ilogbp1(arg<v4f32>::type v);
    v4s32 ilogb(arg<v4f32>::type v);
    v4f32 atan2(arg<v4f32>::type y, arg<v4f32>::type x);
    v4f32 asin(arg<v4f32>::type d);
    v4f32 acos(arg<v4f32>::type d);

    v4f32 atan(arg<v4f32>::type d);
    std::pair<v4f32, v4f32> sincos(arg<v4f32>::type d);

    v4f32 exp(arg<v4f32>::type d);
    v4f32 expm1(arg<v4f32>::type d);
    v4f32 log(arg<v4f32>::type d);
    v4f32 pow(arg<v4f32>::type b, arg<v4f32>::type e);
    void sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
    v4f32 sin(arg<v4f32>::type d);
    v4f32 cos(arg<v4f32>::type d);
    v4f32 tan(arg<v4f32>::type d);
    v4f32 cot(arg<v4f32>::type d);
    v4f32 atan2(arg<v4f32>::type x, arg<v4f32>::type y);

    void native_sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
    v4f32 native_exp(arg<v4f32>::type d);
    v4f32 native_log(arg<v4f32>::type d);
    v4f32 native_sin(arg<v4f32>::type d);
    v4f32 native_cos(arg<v4f32>::type d);
    v4f32 native_tan(arg<v4f32>::type d);
    v4f32 native_cot(arg<v4f32>::type d);
    v4f32 cosh(arg<v4f32>::type d);
    v4f32 sinh(arg<v4f32>::type d);

    v4f32 pow(arg<v4f32>::type x, arg<v4f32>::type y);

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

    namespace op {

        template <>
        struct bit_not<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a) {
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one._f32);
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
#if defined (__AVX__)                
                return _mm_cmp_ps(a(), b(), _CMP_LT_OS);
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
#if defined (__AVX__)                
                return _mm_cmp_ps(a(), b(), _CMP_LE_OS);
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
#if defined (__AVX__)                
                return _mm_cmp_ps(a(), b(), _CMP_EQ_OQ);
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
#if defined (__AVX__)                
                return _mm_cmp_ps(a(), b(), _CMP_UNORD_Q);
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
#if defined (__AVX__)                
                return _mm_cmp_ps(a(), b(), _CMP_GE_OS);
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
#if defined (__AVX__)                
                return _mm_cmp_ps(a(), b(), _CMP_GT_OS);
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
                constexpr const bytes4 all_one{-1};
                const full_type all_set(all_one._f32);
                return _mm_xor_ps(a(), all_set());
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

#if 0
        template <>
        struct mod<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

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

#if 0
        template <>
        struct shl<float, 4> {
            using full_type = vec<float, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<float, 4> {
            using full_type = vec<float, 4>;
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
    return x86::select(m(), on_true(), on_false());
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
    return x86::perm_f32<_P0, _P1, _P2, _P3>(a());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
cftal::v4f32 cftal::permute(const v4f32& a, const v4f32& b)
{
    return x86::perm_f32<_P0, _P1, _P2, _P3>(a(), b());
}

inline
cftal::v4f32 cftal::sqrt(const v4f32& a)
{
    return _mm_sqrt_ps(a());
}

inline
cftal::v4f32 cftal::abs(const v4f32& a)
{
    const v4f32 msk(not_sign_f32_msk::v._f32);
    return _mm_and_ps(a(), msk());
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
    const v4f32 msk(not_sign_f32_msk::v._f32);
    v4f32 abs_x(x & msk);
    v4f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v4f32 cftal::mulsign(const v4f32& x, const v4f32& y)
{
    const v4f32 msk(sign_f32_msk::v._f32);
    v4f32 sgn_y = y & msk;
    return x ^ sgn_y;
}

inline
bool cftal::all_signs(const v4f32& a)
{
    return x86::all_signs_f32(a());
}

inline
bool cftal::both_signs(const v4f32& a)
{
    return x86::both_signs_f32(a());
}

inline
bool cftal::no_signs(const v4f32& a)
{
    return x86::no_signs_f32(a());
}

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
    return all_signs(rv);
}

inline
cftal::v4f32 cftal::x86::round(const v4f32& a, const rounding_mode::type m)
{
    v4f32 r;
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
    return r;
}

inline
cftal::v4f32 cftal::rint(const v4f32& a)
{
    return x86::round(a, x86::rounding_mode::current);
}

inline
cftal::v4f32 cftal::floor(const v4f32& a)
{
    return x86::round(a, x86::rounding_mode::downward);
}

inline
cftal::v4f32 cftal::ceil(const v4f32& a)
{
    return x86::round(a, x86::rounding_mode::upward);
}

inline
cftal::v4f32 cftal::trunc(const v4f32& a)
{
    return x86::round(a, x86::rounding_mode::towardzero);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F32__
