#if !defined (__X86VEC_LOAD_STORE_H__)
#define __X86VEC_LOAD_STORE_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cstdint>

namespace x86vec {

        template <unsigned _N>
        struct is_aligned_to {
                static const intptr_t val=_N;
                static bool ptr(const void* p) {
                        std::intptr_t t(reinterpret_cast<intptr_t>(p));
                        return (t & (_N-1))==0;
                }
        };

        template <class _D>
        struct ptr {
                template <class _S>
                static
                const _D* make(const _S* p) {
                        return reinterpret_cast<const _D*>(p);
                }
                template <class _S>
                static
                _D* make(_S* p) {
                        return reinterpret_cast<_D*>(p);
                }
        };

        struct m128_ptr : public ptr<__m128> {};
        struct m128d_ptr : public ptr<__m128> {};
        struct m128i_ptr : public ptr<__m128i> {};
#if defined (__AVX__)
        struct m256_ptr : public ptr<__m256> {};
        struct m256d_ptr : public ptr<__m256d> {};
#endif
#if defined (__AVX2__)
        struct m256i_ptr : public ptr<__m256i> {};
#endif
}

// Local variables:
// mode: c++
// end:
#endif
