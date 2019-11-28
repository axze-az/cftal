//
// Copyright Axel Zeuner 2010-2019. Use, modification and
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

            template <typename _T, typename _TAG>
            struct mpfr_result {
                _T _res;
                int _mpfr_res;
            };

            struct f1_tag {};
            template <typename _T>
            using f1_mpfr_result = mpfr_result<_T, f1_tag>;

            // returns nullptr if nothing was found
            const f1_mpfr_result<double>*
            result(double a, f1_t f, f1_mpfr_result<double>& spc);
            // update the data base if f is cached
            void
            update(double a, f1_t f, const f1_mpfr_result<double>& r);
            // enable caching for f in func-name-f64.bin
            void
            use(f1_t f, const std::string& func_name, double v);

            // returns nullptr if nothing was found
            const f1_mpfr_result<float>*
            result(float a, f1_t f, f1_mpfr_result<float>& spc);
            // update the data base if f is cached
            void
            update(float a, f1_t f, const f1_mpfr_result<float>& r);
            // enable caching for f in func-name-f32.bin
            void
            use(f1_t f, const std::string& func_name, float v);

            struct f2_tag {};
            template <typename _T>
            using f2_mpfr_result = mpfr_result<_T, f2_tag>;

            // returns nullptr if nothing was found
            const f2_mpfr_result<double>*
            result(double a, double b, f2_t f,
                   f2_mpfr_result<double>& spc);
            // update the data base if f is cached
            void
            update(double a, double b, f2_t f,
                   const f2_mpfr_result<double>& r);
            // enable caching for f in func-name-f64_2.bin
            void
            use(f2_t f, const std::string& func_name, double v);

            // returns nullptr if nothing was found
            const f2_mpfr_result<float>*
            result(float a, float b, f2_t f,
                   f2_mpfr_result<float>& spc);
            // update the data base if f is cached
            void
            update(float a, float b, f2_t f,
                   const f2_mpfr_result<float>& r);
            // enable caching for f in func-name-f64_2.bin
            void
            use(f2_t f, const std::string& func_name, float v);

        }
    }
}

// local variables:
// mode: c++
// end:
#endif
