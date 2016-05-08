#if !defined(__CFTAL_TEST_CHECK_NATIVE_COS_H__)
#define __CFTAL_TEST_CHECK_NATIVE_COS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_native_cos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_cos(a);
            }
            static
            _T
            r(const _T& a) {
                return call_mpfr::func(a, mpfr_cos);
            }
            static
            _T
            s(const _T& a) {
                return std::cos(a);
            }
            static
            const char* fname() { return "native_cos"; }
        };


    }
}

// local variables:
// mode: c++
// end:

#endif
