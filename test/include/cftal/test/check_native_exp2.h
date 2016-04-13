#if !defined(__CFTAL_TEST_CHECK_NATIVE_EXP2_H__)
#define __CFTAL_TEST_CHECK_NATIVE_EXP2_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_native_exp2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_exp2(a);
            }
            static
            _T
            v(const _T& a) {
#if 0
                return call_mpfr::func(a, mpfr_exp2);
#else
                return std::exp2(a);
#endif
            }
            static
            const char* fname() { return "exp2"; }
        };

        
    }
}

// local variables:
// mode: c++
// end:

#endif
