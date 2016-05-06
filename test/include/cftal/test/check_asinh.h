#if !defined(__CFTAL_TEST_CHECK_ASINH_H__)
#define __CFTAL_TEST_CHECK_ASINH_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_asinh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return asinh(a);
            }
            static
            _T
            r(const _T& a) {
                return call_mpfr::func(a, mpfr_asinh);
            }
            static
            _T
            s(const _T& a) {
                return std::asinh(a);
            }
            static
            const char* fname() { return "asinh"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
