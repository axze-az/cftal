#if !defined (__CFTAL_X86_V4F64__)
#define __CFTAL_X86_V4F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/x86_perm.h> 
#include <cftal/x86_vreg.h>
#include <cftal/x86_v2f64.h>
#include <cftal/x86_ops_1.h>

#if !defined (__AVX__)
#error "urgh"
#endif

namespace cftal {

    template <>
    class vec<double, 4> : public x86::vreg<__m256d> {
    public:
        using base_type = x86::vreg<__m256d>;

        using value_type = double;
        using mask_value_type = double;
        using mask_type= vec<mask_value_type, 4>;

        using x86::vreg<__m256d>::vreg;
        vec() = default;
        // create vec{v,v,v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from vec<double, 8>
        vec(init_list<double> l);
        // allow construction from two halfes
        vec(const vec<double, 2>& lh, const vec<double, 2>& hh);
        
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<double, 4>, _L, _R>& r);
    };

    // load from memory, fills remaining elements with the last
    // one given
    vec<double, 4>
    load(const double* l, std::size_t s);

    void
    store(double* p, const vec<double, 4>& v);
    
    vec<double, 2>
    low_half(const vec<double, 4>& s);

    vec<double, 2>
    high_half(const vec<double, 4>& s);

    vec<double, 4> 
    select(const typename vec<double, 4>::mask_type& msk,
           const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

    bool
    all_signs(const vec<double, 4>& a);

    bool
    no_signs(const vec<double, 4>& a);

    bool
    both_signs(const vec<double, 4>& a);

    unsigned
    read_signs(const vec<double, 4>& b);
    
    vec<double, 4>
    sqrt(const vec<double, 4>& v);

    vec<double, 4>
    cbrt(vec<double, 4> v);

    v4f64 max(const v4f64& a, const v4f64& b);
    v4f64 min(const v4f64& a, const v4f64& b);
    v4f64 abs(const v4f64& a);
    v4f64 fabs(const v4f64& a);
    v4f64 sqrt(const v4f64& a);
    v4f64 cbrt(arg<v4f64>::type a);
    v4f64 hypot(const v4f64& a, const v4f64& b);
    
    v4f64 rsqrt(const v4f64& a);
    v4f64 native_rsqrt(const v4f64& a);

    namespace x86 {
        v4f64 round(const v4f64& v, rounding_mode::type m);
    }
    
    v4f64 rint(const v4f64& a);
    v4f64 floor(const v4f64& a);
    v4f64 ceil(const v4f64& a);
    v4f64 trunc(const v4f64& a);
    // returns (~a) & (b)
    v4f64 andnot(const v4f64& a, const v4f64& b);
    v4f64 copysign(const v4f64& x, const v4f64& y);
    v4f64 mulsign(const v4f64& x, const v4f64& y);
    v4f64 isinf(const v4f64& x);
    v4f64 isnan(const v4f64& x);
    v4f64 isfinite(const v4f64& x);

    v4f64 frexp(arg<v4f64>::type x, v4s32* e);
    // v4f64 pow2i(arg<v4s32>::type e);
    v4f64 ldexp(arg<v4f64>::type d, arg<v4s32>::type e);
    v4s32 ilogbp1(arg<v4f64>::type v);
    v4s32 ilogb(arg<v4f64>::type v);
    v4f64 atan2(arg<v4f64>::type y, arg<v4f64>::type x);
    v4f64 asin(arg<v4f64>::type d);
    v4f64 acos(arg<v4f64>::type d);

    v4f64 atan(arg<v4f64>::type d);
    std::pair<v4f64, v4f64> sincos(arg<v4f64>::type d);

    v4f64 exp(arg<v4f64>::type d);
    v4f64 expm1(arg<v4f64>::type d);
    v4f64 log(arg<v4f64>::type d);
    v4f64 pow(arg<v4f64>::type b, arg<v4f64>::type e);
    void sincos(arg<v4f64>::type d, v4f64* psin, v4f64* pcos);
    v4f64 sin(arg<v4f64>::type d);
    v4f64 cos(arg<v4f64>::type d);
    v4f64 tan(arg<v4f64>::type d);
    v4f64 cot(arg<v4f64>::type d);
    v4f64 atan2(arg<v4f64>::type x, arg<v4f64>::type y);
        
    void native_sincos(arg<v4f64>::type d, v4f64* psin, v4f64* pcos);
    v4f64 native_exp(arg<v4f64>::type d);
    v4f64 native_log(arg<v4f64>::type d);
    v4f64 native_sin(arg<v4f64>::type d);
    v4f64 native_cos(arg<v4f64>::type d);
    v4f64 native_tan(arg<v4f64>::type d);
    v4f64 native_cot(arg<v4f64>::type d);
    v4f64 cosh(arg<v4f64>::type d);
    v4f64 sinh(arg<v4f64>::type d);

    v4f64 pow(arg<v4f64>::type x, arg<v4f64>::type y);

    // a*b +c
    v4f64 fma(const v4f64& a, const v4f64& b, const v4f64& c);
    // a*b -c
    v4f64 fms(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) + c
    v4f64 nfma(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) - c
    v4f64 nfms(const v4f64& a, const v4f64& b, const v4f64& c);
    
    // a*b +c with rounding or not
    v4f64 mad(const v4f64& a, const v4f64& b, const v4f64& c);
    // -(a*b) +c with rounding or not
    v4f64 nmad(const v4f64& a, const v4f64& b, const v4f64& c);
    
    template <bool _P0, bool _P1, 
              bool _P2, bool _P3>
    vec<double, 4> 
    select(const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 4> 
    permute(const vec<double, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 4> 
    permute(const vec<double, 4>& s0, 
            const vec<double, 4>& s1);

    namespace op {

        template <>
        struct bit_not<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm256_xor_pd(a(), all_set());
            }
        };

        
        template <>
        struct lt<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmp_pd(a(), b(), _CMP_LT_OS);
            }
        };

        template <>
        struct le<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmp_pd(a(), b(), _CMP_LE_OS);
            }
        };

        template <>
        struct eq<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmp_pd(a(), b(), _CMP_EQ_OQ);
            }
        };

        template <>
        struct ne<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmp_pd(a(), b(), _CMP_UNORD_Q);
            }
        };

        template <>
        struct ge<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmp_pd(a(), b(), _CMP_GE_OS);
            }
        };

        template <>
        struct gt<double, 4> {
            using full_type = vec<double, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmp_pd(a(), b(), _CMP_GT_OS);
            }
        };

        template <>
        struct plus<double, 4> {
            using full_type = vec<double, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a) {
                const __m256d all_set = 
                    x86::const_v8u32<uint32_t(-1), uint32_t(-1),
                                     uint32_t(-1), uint32_t(-1),
                                     uint32_t(-1), uint32_t(-1),
                                     uint32_t(-1), uint32_t(-1)>::dv();
                    return _mm256_xor_pd(a(), all_set);
            }
        };

        template <>
        struct add<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_pd(a(), b());
            }
        };

        template <>
        struct sub<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_pd(a(), b());
            }
        };

        template <>
        struct mul<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_mul_pd(a(), b());
            }
        };

        template <>
        struct div<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_div_pd(a(), b());
            }
        };

#if 0
        template <>
        struct mod<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

        template <>
        struct fma<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__) 
                return _mm256_macc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fmadd_pd(a(), b(), c());
#else
                return _mm256_add_pd(_mm256_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
        return _mm256_msub_pd(a(), b(), c());
#elif defined (__FMA__)
        return _mm256_fmsub_pd(a(), b(), c());
#else
        return _mm256_sub_pd(_mm256_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm256_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm256_fnmadd_pd(a(), b(), c());
#else
                return _mm256_sub_pd(c(), _mm256_mul_pd(a(), b()));
#endif
            }
        };
        
        template <>
        struct bit_or<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_pd(a(), b());
            }
        };

        template <>
        struct bit_and<double, 4> {
            using full_type = vec<double, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_pd(a(), b());
            }
        };

        template <>
        struct bit_xor<double, 4> {
            using full_type = vec<double, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_pd(a(), b());
            }
        };

#if 0
        template <>
        struct shl<double, 4> {
            using full_type = vec<double, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<double, 4> {
            using full_type = vec<double, 4>;
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
cftal::vec<double, 4>::vec(double v)
    : base_type(_mm256_set1_pd(v))
{
}


inline
cftal::vec<double, 4>::
vec(std::initializer_list<double> l)
    : vec(load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 4>::
vec(init_list<double> l)
    : vec(load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 4>::
vec(const vec<double, 2>& lh, const vec<double, 2>& hh)
    : base_type(x86::impl::vinsertf128<1>::v(as<__m256d>(lh()),
                                             hh()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<double, 4>::vec(const expr<_OP<double, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<double, 4>
cftal::load(const double* p, std::size_t s)
{
    __m256d v;
    switch (s) {
    default:
    case 4:
        v = _mm256_loadu_pd(p);
        break;
    case 3:
        v = _mm256_setr_pd(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_pd(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm256_setr_pd(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_setr_pd(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::store(double* p, const vec<double, 4>& v)
{
    _mm256_storeu_pd(p, v());
}


inline
cftal::vec<double, 2>
cftal::low_half(const cftal::vec<double, 4>& v)
{
    return _mm256_castpd256_pd128(v());
}

inline
cftal::vec<double, 2>
cftal::high_half(const cftal::vec<double, 4>& v)
{
    return _mm256_extractf128_pd(v(), 1);
}

inline
cftal::v4f64 cftal::select(const v4f64::mask_type& m,
                           const v4f64& on_true,
                           const v4f64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}

inline
cftal::v4f64 cftal::abs(const v4f64& a)
{
    const __m256d msk= x86::v_not_sign_v4f64_msk::dv();
    return _mm256_and_pd(a(), msk);
}

inline
cftal::v4f64 cftal::andnot(const v4f64& a, const v4f64& b)
{
    return _mm256_andnot_pd(a(), b());

}

inline
cftal::vec<double, 4>
cftal::isnan(const v4f64& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

inline
cftal::vec<double, 4>
cftal::isinf(const v4f64& x)
{
    v4f64 absx(abs(x));
    return absx == v4f64(x86::v_exp_v4f64_msk::dv());
}


inline
cftal::v4f64 cftal::copysign(const v4f64& x, const v4f64& y)
{
    // return abs(x) * sgn(y)
    const v4f64 msk(x86::v_not_sign_v4f64_msk::dv());
    v4f64 abs_x(x & msk);
    v4f64 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v4f64 cftal::mulsign(const v4f64& x, const v4f64& y)
{
    const v4f64 msk(x86::v_sign_v4f64_msk::dv());
    v4f64 sgn_y = y & msk;
    return x ^ sgn_y;
}

inline
bool cftal::all_signs(const v4f64& a)
{
    return x86::all_signs_f64(a());
}

inline
bool cftal::both_signs(const v4f64& a)
{
    return both_signs_f64(a());
}

inline
bool cftal::no_signs(const v4f64& a)
{
    return no_signs_f64(a());
}

inline
unsigned cftal::read_signs(const v4f64& a)
{
    return read_signs_f64(a());
}


inline
cftal::v4f64 cftal::x86::round(const v4f64& a, const rounding_mode::type m)
{
    v4f64 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm256_round_pd(a(), 0);
        break;
    case rounding_mode::downward:
        r= _mm256_round_pd(a(), 1);
        break;
    case rounding_mode::upward:
        r= _mm256_round_pd(a(), 2);
        break;
    case rounding_mode::towardzero:
        r= _mm256_round_pd(a(), 3);
        break;
    case rounding_mode::current:
        r= _mm256_round_pd(a(), 4);
        break;
    }
    return r;
}

inline
cftal::v4f64 cftal::rint(const v4f64& a)
{
    return x86::round(a, x86::rounding_mode::nearest);
}

inline
cftal::v4f64 cftal::floor(const v4f64& a)
{
    return x86::round(a, x86::rounding_mode::downward);
}

inline
cftal::v4f64 cftal::ceil(const v4f64& a)
{
    return x86::round(a, x86::rounding_mode::upward);
}

inline
cftal::v4f64 cftal::trunc(const v4f64& a)
{
    return x86::round(a, x86::rounding_mode::towardzero);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F64__
