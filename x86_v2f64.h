#if !defined (__CFTAL_X86_V2F64__)
#define __CFTAL_X86_V2F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_perm.h> 
#include <cftal/x86_vreg.h>


namespace cftal {

    template <>
    class vec<double, 2> : public x86::vreg<__m128d> {
    public:
        using base_type = x86::vreg<__m128d>;

        using value_type = double;
        using mask_value_type = double;
        using mask_type= vec<mask_value_type, 2>;

        using base_type::base_type;
        vec() = default;
        // create vec{v,v,v,v}
        vec(double v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<double> l);
        // allow construction from vec<double, 8>
        vec(init_list<double> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<double, 2>, _L, _R>& r);
    };

    template <>
    struct mem< vec<double, 2> > {
        static
        vec<double, 2> load(const double* p, std::size_t n=1);
        static
        void store(double* p, const vec<double, 2>& v);
    };
    
    vec<double, 1>
    low_half(const vec<double, 2>& s);

    vec<double, 1>
    high_half(const vec<double, 2>& s);

    vec<double, 2> 
    select(const typename vec<double, 2>::mask_type& msk,
           const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    bool
    all_signs(const vec<double, 2>& a);

    bool
    no_signs(const vec<double, 2>& a);

    bool
    both_signs(const vec<double, 2>& a);

    unsigned
    read_signs(const vec<double, 2>& b);
    

    vec<double, 2>
    sqrt(const vec<double, 2>& v);

    vec<double, 2>
    cbrt(vec<double, 2> v);

    v2f64 max(const v2f64& a, const v2f64& b);
    v2f64 min(const v2f64& a, const v2f64& b);
    v2f64 abs(const v2f64& a);
    v2f64 fabs(const v2f64& a);
    v2f64 sqrt(const v2f64& a);
    v2f64 cbrt(arg<v2f64>::type a);
    v2f64 hypot(const v2f64& a, const v2f64& b);
    
    v2f64 rsqrt(const v2f64& a);
    v2f64 native_rsqrt(const v2f64& a);

    namespace x86 {
        v2f64 round(const v2f64& v, rounding_mode::type m);
    }
    
    v2f64 rint(const v2f64& a);
    v2f64 floor(const v2f64& a);
    v2f64 ceil(const v2f64& a);
    v2f64 trunc(const v2f64& a);
    // returns (~a) & (b)
    v2f64 andnot(const v2f64& a, const v2f64& b);
    v2f64 copysign(const v2f64& x, const v2f64& y);
    v2f64 mulsign(const v2f64& x, const v2f64& y);
    v2f64 isinf(const v2f64& x);
    v2f64 isnan(const v2f64& x);
    v2f64 isfinite(const v2f64& x);

    v2f64 frexp(arg<v2f64>::type x, v4s32* e);
    // v2f64 pow2i(arg<v4s32>::type e);
    v2f64 ldexp(arg<v2f64>::type d, arg<v4s32>::type e);
    v4s32 ilogbp1(arg<v2f64>::type v);
    v4s32 ilogb(arg<v2f64>::type v);
    v2f64 atan2(arg<v2f64>::type y, arg<v2f64>::type x);
    v2f64 asin(arg<v2f64>::type d);
    v2f64 acos(arg<v2f64>::type d);

    v2f64 atan(arg<v2f64>::type d);
    std::pair<v2f64, v2f64> sincos(arg<v2f64>::type d);

    v2f64 exp(arg<v2f64>::type d);
    v2f64 expm1(arg<v2f64>::type d);
    v2f64 log(arg<v2f64>::type d);
    v2f64 pow(arg<v2f64>::type b, arg<v2f64>::type e);
    void sincos(arg<v2f64>::type d, v2f64* psin, v2f64* pcos);
    v2f64 sin(arg<v2f64>::type d);
    v2f64 cos(arg<v2f64>::type d);
    v2f64 tan(arg<v2f64>::type d);
    v2f64 cot(arg<v2f64>::type d);
    v2f64 atan2(arg<v2f64>::type x, arg<v2f64>::type y);
        
    void native_sincos(arg<v2f64>::type d, v2f64* psin, v2f64* pcos);
    v2f64 native_exp(arg<v2f64>::type d);
    v2f64 native_log(arg<v2f64>::type d);
    v2f64 native_sin(arg<v2f64>::type d);
    v2f64 native_cos(arg<v2f64>::type d);
    v2f64 native_tan(arg<v2f64>::type d);
    v2f64 native_cot(arg<v2f64>::type d);
    v2f64 cosh(arg<v2f64>::type d);
    v2f64 sinh(arg<v2f64>::type d);

    v2f64 pow(arg<v2f64>::type x, arg<v2f64>::type y);

    // a*b +c
    v2f64 fma(const v2f64& a, const v2f64& b, const v2f64& c);
    // a*b -c
    v2f64 fms(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) + c
    v2f64 nfma(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) - c
    v2f64 nfms(const v2f64& a, const v2f64& b, const v2f64& c);
    
    // a*b +c with rounding or not
    v2f64 mad(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) +c with rounding or not
    v2f64 nmad(const v2f64& a, const v2f64& b, const v2f64& c);
    
    template <bool _P0, bool _P1, 
              bool _P2, bool _P3>
    vec<double, 2> 
    select(const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 2> 
    permute(const vec<double, 2>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<double, 2> 
    permute(const vec<double, 2>& s0, 
            const vec<double, 2>& s1);

    namespace op {

        template <>
        struct bit_not<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a) {
                const bytes8 all_ones{-1, -1};
                full_type all_set(all_ones._f64);
                return _mm_xor_pd(a(), all_set());
            }
        };

        
        template <>
        struct lt<double, 2> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmplt_pd(a(), b());
            }
        };

        template <>
        struct le<double, 2> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmple_pd(a(), b());
            }
        };

        template <>
        struct eq<double, 2> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_pd(a(), b());
            }
        };

        template <>
        struct ne<double, 2> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpneq_pd(a(), b());
            }
        };

        template <>
        struct ge<double, 2> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpge_pd(a(), b());
            }
        };

        template <>
        struct gt<double, 2> {
            using full_type = vec<double, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_pd(a(), b());
            }
        };

        template <>
        struct plus<double, 2> {
            using full_type = vec<double, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a) {
                const bytes8 m1{-1, 1};
                const v2f64 all_set(m1._f64);
                return _mm_xor_pd(a(), all_set());
            }
        };

        template <>
        struct add<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_pd(a(), b());
            }
        };

        template <>
        struct sub<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_pd(a(), b());
            }
        };

        template <>
        struct mul<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_mul_pd(a(), b());
            }
        };

        template <>
        struct div<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_div_pd(a(), b());
            }
        };

#if 0
        template <>
        struct mod<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

        template <>
        struct fma<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__) 
                return _mm_macc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm_fmadd_pd(a(), b(), c());
#else
                return _mm_add_pd(_mm_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fms<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm_msub_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm_fmsub_pd(a(), b(), c());
#else
                return _mm_sub_pd(_mm_mul_pd(a(), b()), c());
#endif
            }
        };

        template <>
        struct fnma<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
#if defined (__FMA4__)
                return _mm_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
                return _mm_fnmadd_pd(a(), b(), c());
#else
                return _mm_sub_pd(c(), _mm_mul_pd(a(), b()));
#endif
            }
        };
        
        template <>
        struct bit_or<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_pd(a(), b());
            }
        };

        template <>
        struct bit_and<double, 2> {
            using full_type = vec<double, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_pd(a(), b());
            }
        };

        template <>
        struct bit_xor<double, 2> {
            using full_type = vec<double, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_pd(a(), b());
            }
        };

#if 0
        template <>
        struct shl<double, 2> {
            using full_type = vec<double, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<double, 2> {
            using full_type = vec<double, 2>;
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
cftal::vec<double, 2>::vec(double v)
    : base_type(_mm_set1_pd(v))
{
}


inline
cftal::vec<double, 2>::
vec(std::initializer_list<double> l)
    : vec(mem<vec<double,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<double, 2>::
vec(init_list<double> l)
    : vec(mem<vec<double,2> >::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<double, 2>::vec(const expr<_OP<double, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<double, 2>
cftal::mem<cftal::vec<double, 2>>::load(const double* p, std::size_t s)
{
    __m128d v;
    switch (s) {
    default:
    case 2:
        v = _mm_loadu_pd(p);
        break;
    case 1:
        v = _mm_setr_pd(p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_pd(0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<double, 2>>::store(double* p, const vec<double, 2>& v)
{
    _mm_storeu_pd(p, v());
}

inline
cftal::v2f64
cftal::select(const v2f64::mask_type& m,
              const v2f64& on_true, const v2f64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F64__
