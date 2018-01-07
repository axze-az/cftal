//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_MPFR_CACHE_H__)
#define __CFTAL_TEST_MPFR_CACHE_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/test/call_mpfr.h>
#include <string>

namespace cftal {
    namespace test {
        namespace mpfr_cache {

            using call_mpfr::f1_t;
            using call_mpfr::f2_t;

            template <typename _T>
            struct mpfr_result {
                _T _res;
                int _mpfr_res;
            };

            // returns nullptr if nothing was found
            const mpfr_result<double>*
            result(double a, f1_t f, mpfr_result<double>& spc);
            // update the data base if f is cached
            void
            update(double a, f1_t f, const mpfr_result<double>& r);
            // enable caching for f in func-name-f64.bin
            void
            use(f1_t f, const std::string& func_name, double v);

            // returns nullptr if nothing was found
            const mpfr_result<float>*
            result(float a, f1_t f, mpfr_result<float>& spc);
            // update the data base if f is cached
            void
            update(float a, f1_t f, const mpfr_result<float>& r);
            // enable caching for f in func-name-f32.bin
            void
            use(f1_t f, const std::string& func_name, float v);

        }
    }
}

// local variables:
// mode: c++
// end:
#endif
