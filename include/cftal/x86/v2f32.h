#if !defined (__CFTAL_X86_V2F32__)
#define __CFTAL_X86_V2F32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/constants.h>
#include <cftal/vec_float_n.h>
#include <cftal/x86/const.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/ops_1.h>
#include <cftal/x86/v4s32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/vreg.h>

namespace cftal {
    
    template <>
    class vec<float, 2> : public x86::vreg<uint64_t> {
    public:
        using base_type= x86::vreg<uint64_t>;

        using value_type = float;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = float;
#endif
        using mask_type= vec<mask_value_type, 2>;
        vec() = default;
        // create vec{v,v,v,v}
        vec(float v);
        vec(__m128 v);
        __m128 operator()() const;
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<float> l);
        // allow construction from vec<float, 8>
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
    struct mem< vec<float, 2> > {
        static
        vec<float, 2> load(const float* p, std::size_t n=2);
        static
        void store(float* p, const vec<float, 2>& v);
    };

    vec<float, 1>
    low_half(const vec<float, 2>& s);

    vec<float, 1>
    high_half(const vec<float, 2>& s);

#if !defined (__AVX512VL__)
    bool
    any_of(const vec<float, 2>::mask_type& s);

    bool
    all_of(const vec<float, 2>::mask_type& s);

    bool
    none_of(const vec<float, 2>::mask_type& s);
#endif

    template <std::size_t _I>
    float
    extract(const vec<float, 2>& s);
    
    vec<float, 2>
    select(const typename vec<float, 2>::mask_type& msk,
           const vec<float, 2>& on_true,
           const vec<float, 2>& on_false);

    unsigned
    read_signs(const vec<float, 2>& b);

    bool
    elements_equal(const v2f32& a);
    

    v2f32 max(const v2f32& a, const v2f32& b);
    v2f32 min(const v2f32& a, const v2f32& b);

    float max_element(const v2f32& v);
    float min_element(const v2f32& v);

    v2f32 abs(const v2f32& a);
    v2f32 fabs(const v2f32& a);
    v2f32 sqrt(const v2f32& a);
    v2f32 cbrt(arg<v2f32>::type a);
    v2f32 hypot(const v2f32& a, const v2f32& b);

    v2f32 rsqrt(const v2f32& a);
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

    namespace op {

        template <>
        struct bit_not<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a) {
                const bytes4 all_ones{-1};
                full_type all_set(all_ones._f32);
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
                return _mm_cmp_ps_mask(a(), b(), _CMP_UNORD_Q);
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
                const full_type neg_bits(sign_f32_msk::v._f32);
                return _mm_xor_ps(a(), neg_bits());
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

#if 0
        template <>
        struct mod<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };
#endif

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

#if 0
        template <>
        struct shl<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<float, 2> {
            using full_type = vec<float, 2>;
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
cftal::vec<float, 2>::vec(float v)
    : vec(_mm_set1_ps(v))
{
}

inline
cftal::vec<float, 2>::vec(__m128 v)
    : base_type(_mm_cvtsi128_si64(_mm_castps_si128(v)))
{       
}

inline
__m128
cftal::vec<float, 2>::operator()() const 
{
    uint64_t r=base_type::operator()();    
    return _mm_castsi128_ps(_mm_cvtsi64_si128(r));
}

inline
cftal::vec<float, 2>::
vec(std::initializer_list<float> l)
    : vec(mem<vec<float,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 2>::
vec(init_list<float> l)
    : vec(mem<vec<float,2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<float, 2>::
vec(const vec<float, 1>& l, const vec<float, 1>& h)
    : vec(_mm_setr_ps(l(), h(), 0.0f, 0.0f))
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
cftal::mem<cftal::vec<float, 2>>::load(const float* p, std::size_t s)
{
    __m128 v;
    switch (s) {
    default:
    case 2:
        v = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<const __m64*>(p));
        break;
    case 1:
        v = _mm_set1_ps(p[0]);
        break;
    case 0:
        v = _mm_setzero_ps();
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<float, 2>>::store(float* p, const vec<float, 2>& v)
{
    _mm_storel_pi(reinterpret_cast<__m64*>(p), v());
}

inline
cftal::vec<float, 1>
cftal::low_half(const v2f32& v)
{
    return vec<float, 1>(extract<0>(v));
}

inline
cftal::vec<float, 1>
cftal::high_half(const v2f32& v)
{
    return vec<float, 1>(extract<1>(v));
}

template <std::size_t _I>
float
cftal::extract(const vec<float, 2>& v)
{
    return x86::extract_f32<_I>(v());
}

inline
cftal::v2f32
cftal::select(const v2f32::mask_type& m,
              const v2f32& on_true, const v2f32& on_false)
{
    return x86::select(m(), on_true(), on_false());
}


inline
cftal::v2f32
cftal::max(const v2f32& a, const v2f32& b)
{
    return _mm_max_ps(a(), b());
}

inline
cftal::v2f32
cftal::min(const v2f32& a, const v2f32& b)
{
    return _mm_min_ps(a(), b());
}

inline
float
cftal::max_element(const v2f32& v)
{
    v2f32 vp=permute<1, 0>(v);
    v2f32 r=max(v, vp);
    return extract<0>(r);
}

inline
float
cftal::min_element(const v2f32& v)
{
    v2f32 vp=permute<1, 0>(v);
    v2f32 r=min(v, vp);
    return extract<0>(r);
}

inline
cftal::v2f32 cftal::sqrt(const v2f32& a)
{
    return _mm_sqrt_ps(a());
}

inline
cftal::v2f32 cftal::abs(const v2f32& a)
{
    const v2f32 msk(not_sign_f32_msk::v._f32);
    return _mm_and_ps(a(), msk());
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
#endif

inline
cftal::v2f32 cftal::copysign(const v2f32& x, const v2f32& y)
{
    // return abs(x) * sgn(y)
    const v2f32 msk(not_sign_f32_msk::v._f32);
    v2f32 abs_x(x & msk);
    v2f32 sgn_y(andnot(msk, y));
    return abs_x | sgn_y;
}

inline
cftal::v2f32 cftal::mulsign(const v2f32& x, const v2f32& y)
{
    const v2f32 msk(sign_f32_msk::v._f32);
    v2f32 sgn_y = y & msk;
    return x ^ sgn_y;
}

#if !defined (__AVX512VL__)
inline
bool
cftal::any_of(const vec<float, 2>::mask_type& s)
{
    return x86::read_signs_f32(s()) != 0;
}

inline
bool
cftal::all_of(const vec<float, 2>::mask_type& s)
{
    return x86::read_signs_f32(s()) == 0x3;
}
    
inline
bool
cftal::none_of(const vec<float, 2>::mask_type& s)
{
    return x86::read_signs_f32(s()) == 0;
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
cftal::v2f32 cftal::x86::round(const v2f32& a, const rounding_mode::type m)
{
    v2f32 r;
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
    const __m128 sgn_msk= v_sign_v4f32_msk::fv();
    // (127+23)<< 23 = 0x4B000000 = 2^23
    const __m128 magic= const_v4u32<0x4B000000, 0x4B000000,
                                    0x4B000000, 0x4B000000>::fv();
    __m128 sign = _mm_and_ps(a(), sgn_msk);
    __m128 sign_magic = _mm_or_ps(magic, sign);
    r= _mm_add_ps(a(), sign_magic);
    r = _mm_sub_ps(a(), sign_magic);
    if (mxcsr != rmxcsr)
        _mm_setcsr(mxcsr);
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

template <bool _I0, bool _I1>
inline
cftal::vec<float, 2>
cftal::select(const vec<float, 2>& l, const vec<float,2>& r)
{
    return x86::select_f32<_I0, _I1>(l(), r());
}

template <int _I0, int _I1>
inline
cftal::vec<float, 2>
cftal::permute(const vec<float, 2>& v)
{
    return x86::perm_v4f32<_I0, _I1, 2, 3>(v());
}

template <int _I0, int _I1>
inline
cftal::vec<float, 2>
cftal::permute(const vec<float, 2>& l, const vec<float, 2>& r)
{
    return x86::perm_v4f32<_I0, _I1, 2, 3>(l(), r());
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2F32__
