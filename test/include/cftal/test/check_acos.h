#if !defined(__CFTAL_TEST_CHECK_ACOS_H__)
#define __CFTAL_TEST_CHECK_ACOS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {
        
        template <typename _T>
        struct check_acos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return acos(a);
            }
            // reference
            static
            _T
            r(const _T& a) {
                return call_mpfr::func(a, mpfr_acos);
            }
            // speed test
            static
            _T
            s(const _T& a) {
                return std::acos(a);
            }
            static
            const char* fname() { return "acos"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
