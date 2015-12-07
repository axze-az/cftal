#if !defined (__CFTAL_X86_V2X32__)
#define __CFTAL_X86_V2X32__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {

    namespace x86 {
        namespace impl {

            union v2x32 {
                double _f64;
                float _f32[2];
                uint64_t _u64;
                int32_t _s32[2];
                uint32_t _u32[2];
                __m64 _m64;
                constexpr v2x32(double d0) : _f64{d0} {}
                constexpr v2x32(float f0, float f1) : _f32{f0, f1} {}
                constexpr v2x32(uint64_t u0) : _u64{u0} {}
                constexpr v2x32(uint32_t u0, uint32_t u1) : _u32{u0, u1} {}
                constexpr v2x32(int32_t s0, int32_t s1) : _s32{s0, s1} {}
            };

            // gcc produces terrible code with an underlying double
#define USE_FLOAT2_DOUBLE 0
#if USE_FLOAT2_DOUBLE
            using f32_pair_type = double;
#else
            using f32_pair_type = uint64_t;
#endif
            constexpr const v2x32 v2f32_div_hh{1.0f, 1.0f};

            inline
            __m128 unpack(f32_pair_type s) {
#if USE_FLOAT2_DOUBLE
                // make a copy of the low half to the high half
                // to avoid spurious divisions by 0 and other
                // exceptions
                __m128 t = _mm_castpd_ps(_mm_setr_pd(s, 0.0));
#else
                __m128 t = _mm_castsi128_ps(_mm_cvtsi64_si128(s));
#endif
                return t;
            }

            inline
            f32_pair_type pack(__m128 s) {
#if USE_FLOAT2_DOUBLE
                return _mm_cvtsd_f64(_mm_castps_pd(s));
#else
                return _mm_cvtsi128_si64(_mm_castps_si128(s));
#endif
            }

            inline
            f32_pair_type set(float l, float h) {
                v2x32 t(l, h);
#if USE_FLOAT2_DOUBLE
                return t._f64;
#else
                return t._u64;
#endif
            }

            inline
            f32_pair_type set1(float lh) {
                return set(lh, lh);
            }
#undef USE_FLOAT2_DOUBLE

            using s32_pair_type = uint64_t;
            using u32_pair_type = uint64_t;

            inline
            __m128i unpack_v2u32(s32_pair_type v) {
                return _mm_cvtsi64_si128(v);
            }

            inline
            s32_pair_type pack(__m128i v) {
                return _mm_cvtsi128_si64(v);
            }

            inline
            u32_pair_type set(uint32_t l, uint32_t h) {
                v2x32 t(l, h);
                return t._u64;
            }

            inline
            u32_pair_type set(uint32_t lh) {
                return set(lh, lh);
            }

            inline
            s32_pair_type set(int32_t l, int32_t h) {
                v2x32 t(l, h);
                return t._u64;
            }

            inline
            s32_pair_type set(int32_t lh) {
                return set(lh, lh);
            }

        }
    }
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2X32__
