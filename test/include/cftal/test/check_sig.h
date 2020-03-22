//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_SIG_H__)
#define __CFTAL_TEST_CHECK_SIG_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math/func_constants.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {


        template <typename _T>
        struct check_sig {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sig(a);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::sig, &i);
                return std::make_tuple(v, i.first, i.second);
            }

            static
            _T
            s(const _T& a) {
                using fc=cftal::math::func_constants<_T>;
                if (a >= fc::sig_hi_one()) {
                    return _T(1.0);
                }
                if (a < fc::sig_le_eq_exp()) {
                    return std::exp(a);
                }
                return _T(1.0)/(_T(2.0)+std::expm1(-a));
            }

            static
            const char* fname() { return "sig"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
