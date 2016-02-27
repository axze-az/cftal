#if !defined (__CFTAL_VEC_CAST_H__)
#define __CFTAL_VEC_CAST_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/x86/cast.h>

namespace cftal {

    namespace impl {
#if defined (__SSE2__)

        template <>
        struct cast<v2f64, v4s32> {
            static
            v2f64 v(const v4s32& s) {
                return v2f64(as<__m128d>(s()));
            }
        };

        template <>
        struct cast<v2f64, v4u32> {
            static
            v2f64 v(const v4s32& s) {
                return v2f64(as<__m128d>(s()));
            }
        };
#endif
#if defined (__AVX__)
#if !defined (__AVX2__)
        template <>
        struct cast<v4f64, v8s32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(as<v2f64>(low_half(s)),
                             as<v2f64>(high_half(s)));
            }
        };

        template <>
        struct cast<v4f64, v8u32> {
            static
            v4f64 v(const v4u32& s) {
                return v4f64(as<v2f64>(low_half(s)),
                             as<v2f64>(high_half(s)));
            }
        };
#else
        template <>
        struct cast<v4f64, v8s32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(as<__m256d>(s()));
            }
        };

        template <>
        struct cast<v4f64, v8u32> {
            static
            v4f64 v(const v8s32& s) {
                return v4f64(as<__m256d>(s()));
            }
        };

#endif
#endif
    }

}


// Local variables:
// mode: c++
// end:
#endif
