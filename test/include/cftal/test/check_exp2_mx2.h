//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_EXP2_MX2_H__)
#define __CFTAL_TEST_CHECK_EXP2_MX2_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_exp2_mx2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp2_mx2(a);
            }
            static
            auto
            r(const _T& a) {
#if 1
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::exp2_mx2, &i);
                return std::make_tuple(v, i.first, i.second);
#else
                const std::size_t _N=sizeof(_T)*8;
                using mp_t=mpfr_real<2*_N>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp2(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
#endif
            }
            static
            _T
            s(const _T& a) {
                return std::exp2(-a*a);
            }
            static
            const char* fname() { return "exp2_mx2"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
