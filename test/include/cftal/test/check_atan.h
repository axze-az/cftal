#if !defined(__CFTAL_TEST_CHECK_ATAN_H__)
#define __CFTAL_TEST_CHECK_ATAN_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_atan {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return atan(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_atan, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_cosh);
            }
            static
            _T
            s(const _T& a) {
                return std::atan(a);
            }
            static
            const char* fname() { return "atan"; }
        };
    }
}

// local variables:
// mode: c++
// end:

#endif
