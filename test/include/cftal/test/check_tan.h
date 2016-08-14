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
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_tan, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::tan(a);
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
