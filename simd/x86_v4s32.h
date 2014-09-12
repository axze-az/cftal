#if !defined (__CFTAL_SIMD_X86_V4S32__)
#define __CFTAL_SIMD_X86_V4S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <initializer_list>
#include <cftal/x86vec_intrin.h> // for now

namespace cftal {
        namespace simd {

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

                        vec(int32_t v);
                        vec(int32_t v, bool splat);
                        vec(__m128i v);
                        vec(const std::initializer_list<int32_t>& v);
                        __m128i operator()() const;

                        template <template <class _U, std::size_t _M>
                                  class _OP,
                                  class _L, class _R>
                        vec(const expr<_OP<int32_t, 4>, _L, _R>& r);
                private:
                        __m128i _v;
                };

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
                                        return _mm_sign_epi32(a(),            sgn());
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
}

inline
cftal::simd::vec<cftal::int32_t, 4>::vec(int32_t v)
        : _v(_mm_setr_epi32(v, v, v, v))
{
}

inline
cftal::simd::vec<cftal::int32_t, 4>::vec(int32_t v, bool splat)
        : _v(splat ?
             _mm_setr_epi32(v, v, v, v) :
             _mm_setr_epi32(v, 0, 0, 0))
{
}

inline
cftal::simd::vec<cftal::int32_t, 4>::vec(__m128i v)
        : _v(v)
{
}

inline
cftal::simd::vec<cftal::int32_t, 4>::
vec(const std::initializer_list<int32_t>& l)
        : _v(_mm_loadu_si128(reinterpret_cast<const __m128i*>(l.begin())))
{
        // static_assert(l.size() ==4,
        // "invalid initializer_list");
}

inline
__m128i
cftal::simd::vec<cftal::int32_t, 4>::operator()() const
{
        return _v;
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::simd::
vec<cftal::int32_t, 4>::vec(const expr<_OP<int32_t, 4>, _L, _R>& r)
        : vec(eval(r))
{
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V4S32__
