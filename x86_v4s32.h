#if !defined (__CFTAL_X86_V4S32__)
#define __CFTAL_X86_V4S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86vec_intrin.h> // for now

namespace cftal {

        template <>
        class vec<int32_t, 4> {
        public:
                using value_type = int32_t;
                using mask_value_type = int32_t;
                using mask_type= vec<mask_value_type, 4>;

                vec() = default;
                vec(const vec& r) = default;
                vec(vec&& r) = default;
                vec& operator=(const vec& r) = default;
                vec& operator=(vec&& r) = default;
                // create vec{v,v,v,v}
                vec(int32_t v);
                // create vec{v0, v1, v2, v3}
                // vec(int32_t v0, int32_t v1, int32_t v2=0, int32_t v3=0);
                vec(__m128i v);
                // constructor from std::initializer_list, fills remaining
                // elements with the last one given
                vec(std::initializer_list<int32_t> l);
                // allow construction from vec<int32_t, 8>
                vec(init_list<int32_t> l);

                __m128i operator()() const;

                template <template <class _U, std::size_t _M>
                          class _OP,
                          class _L, class _R>
                vec(const expr<_OP<int32_t, 4>, _L, _R>& r);
        private:
                __m128i _v;
        };

        // load from memory, fills remaining elements with the last
        // one given
        vec<int32_t, 4>
        load(const int32_t* l, std::size_t s);
        
        namespace op {

                template <>
                struct lt<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() < b());
                        }
                };

                template <>
                struct le<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() <= b());
                        }
                };

                template <>
                struct eq<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() == b());
                        }
                };

                template <>
                struct ne<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() != b());
                        }
                };

                template <>
                struct ge<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() >= b());
                        }
                };

                template <>
                struct gt<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        using mask_type = typename full_type::mask_type;
                        static
                        mask_type
                        v(const full_type& a, const full_type& b) {
                                return mask_type(a() > b());
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
                                return full_type(a() * b() - c());
                                // return full_type(std::fma(a(), b(), -c()));
                        }
                };

                template <>
                struct fnma<int32_t, 4> {
                        using full_type = vec<int32_t, 4>;
                        static
                        full_type
                        v(const full_type& a, const full_type& b,
                          const full_type& c) {
                                return full_type(c() - a() * b());
                                // return full_type(std::fma(-a(), b(), c()));
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
        : _v(_mm_setr_epi32(v, v, v, v))
{
}

#if 0
inline
cftal::vec<cftal::int32_t, 4>::
vec(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
        : _v(_mm_setr_epi32(v0, v1, v2, v3))
{
}
#endif

inline
cftal::vec<cftal::int32_t, 4>::vec(__m128i v)
        : _v(v)
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


inline
__m128i
cftal::vec<cftal::int32_t, 4>::operator()() const
{
        return _v;
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
