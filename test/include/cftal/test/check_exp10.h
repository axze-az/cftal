#if !defined(__CFTAL_TEST_CHECK_EXP10_H__)
#define __CFTAL_TEST_CHECK_EXP10_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_exp10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp10(a);
            }

            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_exp10);
#else
                return ::exp10(a);
#endif
            }
            static
            const char* fname() { return "exp10"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
