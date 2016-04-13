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
            v(const _T& a, const _T& b) {
#if 1
                return call_mpfr::func(a, b, mpfr_pow);
#else
                return std::pow(a, b);
#endif

            }
            static
            const char* fname() { return "pow"; }
        };

        template <>
        struct check_pow<double> {
            template <std::size_t _N>
            static
            vec<double, _N>
            v(const vec<double, _N>& a, const vec<double, _N>& b) {
                return pow(a, b);
            }
            static
            double
            v(const double& a, const double& b) {
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
