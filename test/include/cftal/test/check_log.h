#if !defined(__CFTAL_TEST_CHECK_LOG_H__)
#define __CFTAL_TEST_CHECK_LOG_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {
        
        template <typename _T>
        struct check_log {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log(a);
            }
            static
            _T
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log, &i);
                return std::make_tuple(v, i.first, i.second);
                // return call_mpfr::func(a, mpfr_log);
            }
            static
            _T
            s(const _T& a) {
                return std::log(a);
            }
            static
            const char* fname() { return "log"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
