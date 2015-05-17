#if !defined (__CFTAL_X86_V2F64__)
#define __CFTAL_X86_V2F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_double_n.h>
#include <cftal/x86_ops_1.h>
#include <cftal/x86_v4s32.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_vreg.h>

namespace cftal {

    template <>
    class vec<double, 2> : public x86::vreg<__m128d> {
    public:
        using base_type= x86::vreg<__m128d>;

        using value_type = double;
        using mask_value_type = double;
        using mask_type= vec<mask_value_type, 2>;

        using x86::vreg<__m128d>::vreg;;
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
    struct arg< vec<double, 2> > {
        using type = vec<double, 2>;
    };

    template <>
    struct mem< vec<double, 2> > {
        static
        vec<double, 2> load(const double* p, std::size_t n=2);
        static
        void store(double* p, const vec<double, 2>& v);
    };

    vec<double, 1>
    low_half(const vec<double, 2>& s);

    vec<double, 1>
    high_half(const vec<double, 2>& s);

    bool
    any_of(const vec<double, 2>::mask_type& s);

    bool
    all_of(const vec<double, 2>::mask_type& s);
    
    bool
    none_of(const vec<double, 2>::mask_type& s);

    template <std::size_t _I>
    double
    extract(const vec<double, 2>& s);
    
    vec<double, 2>
    select(const typename vec<double, 2>::mask_type& msk,
           const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    unsigned
    read_signs(const vec<double, 2>& b);

    bool
    elements_equal(const v2f64& a);
    

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

    // a*b +c
    v2f64 fma(const v2f64& a, const v2f64& b, const v2f64& c);
    // a*b -c
    v2f64 fms(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) + c
    v2f64 nfma(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) - c
    v2f64 nfms(const v2f64& a, const v2f64& b, const v2f64& c);

#if 0    
    // a*b +c with rounding or not
    v2f64 mad(const v2f64& a, const v2f64& b, const v2f64& c);
    // -(a*b) +c with rounding or not
    v2f64 nmad(const v2f64& a, const v2f64& b, const v2f64& c);
#endif
    
    template <bool _P0, bool _P1>
    vec<double, 2>
    select(const vec<double, 2>& on_true,
           const vec<double, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<double, 2>
    permute(const vec<double, 2>& s);

    template <int32_t _P0, int32_t _P1>
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
cftal::vec<double, 1>
cftal::low_half(const v2f64& v)
{
    return vec<double, 1>(extract<0>(v));
}

inline
cftal::vec<double, 1>
cftal::high_half(const v2f64& v)
{
    return vec<double, 1>(extract<1>(v));
}

template <std::size_t _I>
double
cftal::extract(const vec<double, 2>& v)
{
    return x86::extract_f64<_I>(v());
}

inline
cftal::v2f64
cftal::select(const v2f64::mask_type& m,
              const v2f64& on_true, const v2f64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}

inline
cftal::v2f64 cftal::sqrt(const v2f64& a)
{
    return _mm_sqrt_pd(a());
}

inline
cftal::v2f64 cftal::abs(const v2f64& a)
{
    const v2f64 msk(not_sign_f64_msk::v._f64);
    return _mm_and_pd(a(), msk());
}

inline
cftal::v2f64 cftal::andnot(const v2f64& a, const v2f64& b)
{
    return _mm_andnot_pd(a(), b());
}

inline
cftal::v2f64
cftal::fma(const v2f64& a, const v2f64& b, const v2f64& c)
{
#if defined (__FMA4__)
    return _mm_macc_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fmadd_pd(a(), b(), c());
#else
    // return impl::fma(a, b, c);
    return a * b + c;
#endif
}

inline
cftal::v2f64
cftal::fms(const v2f64& a, const v2f64& b, const v2f64& c)
{
#if defined (__FMA4__)
    return _mm_msub_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fmsub_pd(a(), b(), c());
#else
    // return impl::fma(a, b, -c);
    return a * b - c;
#endif
}

inline
cftal::v2f64
cftal::nfma(const v2f64& a, const v2f64& b, const v2f64& c)
{
#if defined (__FMA4__)
    return _mm_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fnmadd_pd(a(), b(), c());
#else
    // return impl::fma(-a, b, c);
    return c - a*b;
#endif
}

inline
cftal::v2f64
cftal::nfms(const v2f64& a, const v2f64& b, const v2f64& c)
{
#if defined (__FMA4__)
    return _mm_nmsub_pd(a(), b(), c());
#elif defined (__FMA__)
    return _mm_fnmsub_pd(a(), b(), c());
#else
    // return impl::fma(-a, b, -c);
    return -(a*b) - c;
#endif
}

#if 0
inline
cftal::v2f64
cftal::mad(const v2f64& a, const v2f64& b, const v2f64& c)
{
    return a * b + c;
}

inline
cftal::v2f64
cftal::nmad(const v2f64& a, const v2f64& b, const v2f64& c)
{
    return c -(a * b);
}
#endif

inline
cftal::v2f64 cftal::copysign(const v2f64& x, const v2f64& y)
{
    // return abs(x) * sgn(y)
    const v2f64 msk(not_sign_f64_msk::v._f64);
    v2f64 abs_x(x & msk);
    v2f64 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v2f64 cftal::mulsign(const v2f64& x, const v2f64& y)
{
    const v2f64 msk(sign_f64_msk::v._f64);
    v2f64 sgn_y = y & msk;
    return x ^ sgn_y;
}

inline
bool
cftal::any_of(const vec<double, 2>::mask_type& s)
{
    return x86::read_signs_f64(s()) != 0;
}

inline
bool
cftal::all_of(const vec<double, 2>::mask_type& s)
{
    return x86::read_signs_f64(s()) == 0x3;
}
    
inline
bool
cftal::none_of(const vec<double, 2>::mask_type& s)
{
    return x86::read_signs_f64(s()) == 0;
}

inline
unsigned cftal::read_signs(const v2f64& a)
{
    return x86::read_signs_f64(a());
}

inline
bool cftal::elements_equal(const v2f64& a)
{
    double t0= extract<0>(a);
    v2f64 cmp0(t0);
    v2f64::mask_type rv(cmp0 == a);
    return all_of(rv);
}

inline
cftal::v2f64 cftal::x86::round(const v2f64& a, rounding_mode::type m)
{
#if defined (__SSE4_1__)
    v2f64 r;
    switch (m) {
    case rounding_mode::nearest:
        r= _mm_round_pd(a(), 0);
        break;
    case rounding_mode::downward:
        r= _mm_round_pd(a(), 1);
        break;
    case rounding_mode::upward:
        r= _mm_round_pd(a(), 2);
        break;
    case rounding_mode::towardzero:
        r= _mm_round_pd(a(), 3);
        break;
    case rounding_mode::current:
        r= _mm_round_pd(a(), 4);
        break;
    }
    return r;
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
    const v2f64 sgn_msk(sign_f64_msk::v._f64);
    // (1023+52)<<(52-32) 0x43300000 = 2^52
    const v2f64 magic(const_u64<0, 0x43300000>::v._f64);
    __m128d sign = _mm_and_pd(a(), sgn_msk());
    __m128d sign_magic = _mm_or_pd(magic(), sign);
    __m128d res = _mm_add_pd(a(), sign_magic);
    res = _mm_sub_pd(res, sign_magic);
    if (unlikely(mxcsr != rmxcsr))
        _mm_setcsr(mxcsr);
    return res;
#endif
}

inline
cftal::v2f64 cftal::rint(const v2f64& a)
{
    return x86::round(a, rounding_mode::current);
}

inline
cftal::v2f64 cftal::floor(const v2f64& a)
{
    return x86::round(a, rounding_mode::downward);
}

inline
cftal::v2f64 cftal::ceil(const v2f64& a)
{
    return x86::round(a, rounding_mode::upward);
}

inline
cftal::v2f64 cftal::trunc(const v2f64& a)
{
    return x86::round(a, rounding_mode::towardzero);
}

template <bool _I0, bool _I1>
inline
cftal::vec<double, 2>
cftal::select(const vec<double, 2>& l, const vec<double,2>& r)
{
    return x86::select_f64<_I0, _I1>(l(), r());
}

template <int _I0, int _I1>
inline
cftal::vec<double, 2>
cftal::permute(const vec<double, 2>& v)
{
    return x86::perm_f64<_I0, _I1>(v());
}


template <int _I0, int _I1>
inline
cftal::vec<double, 2>
cftal::permute(const vec<double, 2>& l, const vec<double, 2>& r)
{
    return x86::perm_f64<_I0, _I1>(l(), r());
}





// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F64__
