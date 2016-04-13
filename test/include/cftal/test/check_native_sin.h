#if !defined(__CFTAL_TEST_CHECK_NATIVE_SIN_H__)
#define __CFTAL_TEST_CHECK_NATIVE_SIN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {
        template <typename _T>
        struct check_native_sin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_sin(a);
            }
            static
            _T
            v(const _T& a) {
                return std::sin(a);
            }
            static
            const char* fname() { return "native_sin"; }
        };

        template <>
        struct check_native_sin<float> {
            template <std::size_t _N>
            static
            vec<float, _N>
            v(const vec<float, _N>& a) {
                return native_sin(a);
            }
            static
            float
            v(const float& a) {
#if 0
                return call_mpfr::func(a, mpfr_sin);
#else
                return std::sin(a);
#endif
            }
            static
            const char* fname() { return "native_sin"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
