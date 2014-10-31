#if !defined (__CFTAL_X86_V4S32__)
#define __CFTAL_X86_V4S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_perm.h> 
#include <cftal/x86_vreg.h>

namespace cftal {

    template <>
    class vec<int32_t, 4> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;

        using value_type = int32_t;
        using mask_value_type = int32_t;
        using mask_type= vec<mask_value_type, 4>;

        using base_type::base_type;
        // create vec{v,v,v,v}
        vec(int32_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from vec<int32_t, 8>
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int32_t, 4>, _L, _R>& r);
    };

    template <bool _P0, bool _P1, 
              bool _P2, bool _P3>
    vec<int32_t, 4> select(const vec<int32_t, 4>::mask_type& msk,
                           const vec<int32_t, 4>& on_true,
                           const vec<int32_t, 4>& on_false);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<int32_t, 4> permute(const vec<int32_t, 4>& s);

    template <int32_t _P0, int32_t _P1,
              int32_t _P2, int32_t _P3>
    vec<int32_t, 4> permute(const vec<int32_t, 4>& s0, 
                            const vec<int32_t, 4>& s1);

    // load from memory, fills remaining elements with the last
    // one given
    vec<int32_t, 4>
    load(const int32_t* l, std::size_t s);

    namespace op {

        template <>
        struct bit_not<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm_xor_si128(a(), all_set());
            }
        };

        
        template <>
        struct lt<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_epi32(b(), a());
            }
        };

        template <>
        struct le<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a <= b: a == min(a, b);
                __m128i min_ab = _mm_min_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), min_ab);
#else
                mask_type b_gt_a(lt<int32_t, 4>::v(b(), a()));
                const mask_type all_set(uint32_t(-1));
                return _mm_xor_si128(b_gt_a(), all_set());
#endif
            }
        };

        template <>
        struct eq<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpeq_epi32(a(), b());
            }
        };

        template <>
        struct ne<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                mask_type a_eq_b(eq<int32_t, 4>::v(a, b));
                return bit_not<int32_t, 4>::v(a_eq_b);
            }
        };

        template <>
        struct ge<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if defined (__SSE4_1__)
                // a >= b: a == max(a, b);
                __m128i max_ab = _mm_max_epi32(b(), a());
                return _mm_cmpeq_epi32(a(), max_ab);
#else
                mask_type a_lt_b( lt<int32_t, 4>::v(a(), b()));
                return bit_not<int32_t, 4>::v(a_lt_b);
#endif
            }
        };

        template <>
        struct gt<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm_cmpgt_epi32(a(), b());
            }
        };

        template <>
        struct plus<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a) {
#if defined (__SSSE3__)
                const full_type sgn(0x80000000);
                return _mm_sign_epi32(a(), sgn());
#else
                const full_type zero(0);
                return _mm_sub_epi32(zero(), a());
#endif
            }
        };

        template <>
        struct add<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return full_type(a() * b());
                return _mm_mul_epi32(a(), b());
            }
        };

        template <>
        struct div<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() / b());
            }
        };

        template <>
        struct mod<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return full_type(a() % b());
            }
        };

        template <>
        struct fma<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int32_t, 4>::v(
                    mul<int32_t, 4>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int32_t, 4>::v(
                    mul<int32_t, 4>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int32_t, 4>::v(
                    c, mul<int32_t, 4>::v(a, b));
                                          
            }
        };
        
        template <>
        struct bit_or<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_or_si128(a(), b());
            }
        };

        template <>
        struct bit_and<int32_t, 4> {
            using full_type = vec<int32_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_and_si128(a(), b());
            }
        };

        template <>
        struct bit_xor<int32_t, 4> {
            using full_type = vec<int32_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm_xor_si128(a(), b());
            }
        };

        template <>
        struct shl<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<int32_t, 4> {
            using full_type = vec<int32_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm_srli_epi32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int32_t, 4>::vec(int32_t v)
    : base_type(_mm_setr_epi32(v, v, v, v))
{
}


inline
cftal::vec<cftal::int32_t, 4>::
vec(std::initializer_list<int32_t> l)
    : vec(load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 4>::
vec(init_list<int32_t> l)
    : vec(load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 4>::vec(const expr<_OP<int32_t, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 4>
cftal::load(const int32_t* p, std::size_t s)
{
    __m128i v;
    switch (s) {
    default:
    case 4:
        v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
        break;
    case 3:
        v = _mm_setr_epi32(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm_setr_epi32(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm_setr_epi32(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm_setr_epi32(0, 0, 0, 0);
        break;
    }
    return v;

}



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V4S32__
