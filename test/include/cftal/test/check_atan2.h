#if !defined(__CFTAL_TEST_CHECK_ATAN2_H__)
#define __CFTAL_TEST_CHECK_ATAN2_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {
        template <typename _T>

        struct check_atan2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return atan2(a, b);
            }
            static
            _T
            v(const _T& a, const _T& b) {
#if 0
                return call_mpfr::func(a, b, mpfr_atan2);
#else
                return std::atan2(a, b);
#endif
            }
            static
            const char* fname() { return "atan2"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
