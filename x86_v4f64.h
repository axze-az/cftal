#if !defined (__CFTAL_X86_V4F64__)
#define __CFTAL_X86_V4F64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_perm.h> 
#include <cftal/x86_vreg.h>
#include <cftal/x86_v2f64.h>

namespace cftal {

    template <>
    class vec<double, 4> : public x86::vreg<__m256d> {
    public:
        using base_type = x86::vreg<__m256d>;

        using value_type = double;
        using mask_value_type = double;
        using mask_type= vec<mask_value_type, 4>;

        using base_type::base_type;
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

    vec<double, 2>
    low_half(const vec<double, 4>& s);

    vec<double, 2>
    high_half(const vec<double, 4>& s);

    vec<double, 4> 
    select(const typename vec<double, 4>::mask_type& msk,
           const vec<double, 4>& on_true,
           const vec<double, 4>& on_false);

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



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4F64__
