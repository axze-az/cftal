#if !defined(__CFTAL_TEST_CHECK_EXPM1_H__)
#define __CFTAL_TEST_CHECK_EXPM1_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_expm1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return expm1(a);
            }
            static
            _T
            v(const _T& a) {
                return std::expm1(a);
            }
            static
            const char* fname() { return "expm1"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
