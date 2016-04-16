#if !defined(__CFTAL_TEST_CHECK_ACOSH_H__)
#define __CFTAL_TEST_CHECK_ACOSH_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_acosh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return acosh(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_acosh);
#else
                return std::acosh(a);
#endif
            }
            static
            const char* fname() { return "acosh"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
