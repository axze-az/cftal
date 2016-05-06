#if !defined(__CFTAL_TEST_CHECK_POW_H__)
#define __CFTAL_TEST_CHECK_POW_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_pow {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return pow(a, b);
            }
            static
            _T
            r(const _T& a, const _T& b) {
                return call_mpfr::func(a, b, mpfr_pow);
            }
            static
            _T
            s(const _T& a, const _T& b) {
                return std::pow(a, b);
            }
            static
            const char* fname() { return "pow"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
