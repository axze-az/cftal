#if !defined(__CFTAL_TEST_CHECK_TAN_H__)
#define __CFTAL_TEST_CHECK_TAN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {
        template <typename _T>
        struct check_tan {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return tan(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_tan);
#else
                return std::tan(a);
#endif
            }
            static
            const char* fname() { return "tan"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
