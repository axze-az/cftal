#if !defined(__CFTAL_TEST_CHECK_SINCOS_H__)
#define __CFTAL_TEST_CHECK_SINCOS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_sincos {
            struct sin {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> s;
                    sincos(a, &s, nullptr);
                    return s;
                }
                static
                _T
                v(const _T& a) {
                    return std::sin(a);
                }
                static
                const char* fname() { return "sincos: sin"; }
            };

            struct cos {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> c;
                    sincos(a, nullptr, &c);
                    return c;
                }
                static
                _T
                v(const _T& a) {
                    return std::cos(a);
                }
                static
                const char* fname() { return "sincos: cos"; }
            };

        };

    }
}

// local variables:
// mode: c++
// end:

#endif
