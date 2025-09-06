//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_TEST_MPFR_CACHE_H__)
#define __CFTAL_TEST_MPFR_CACHE_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <iostream>
#include <cftal/test/call_mpfr.h>
#include <string>

namespace cftal {
    namespace test {
        namespace mpfr_cache {

            using call_mpfr::f_f_t;
            using call_mpfr::f_ff_t;
            using call_mpfr::fi_f_t;

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
            result(double a, f_f_t f, f1_mpfr_result<double>& spc);
            // update the data base if f is cached
            void
            update(double a, f_f_t f, const f1_mpfr_result<double>& r);
            // enable caching for f in func-name-f64.bin
            void
            use(f_f_t f, const std::string& func_name, double v);

            // returns nullptr if nothing was found
            const f1_mpfr_result<float>*
            result(float a, f_f_t f, f1_mpfr_result<float>& spc);
            // update the data base if f is cached
            void
            update(float a, f_f_t f, const f1_mpfr_result<float>& r);
            // enable caching for f in func-name-f32.bin
            void
            use(f_f_t f, const std::string& func_name, float v);

            struct f2_tag {};
            template <typename _T>
            using f2_mpfr_result = mpfr_result<_T, f2_tag>;

            // returns nullptr if nothing was found
            const f2_mpfr_result<double>*
            result(double a, double b, f_ff_t f,
                   f2_mpfr_result<double>& spc);
            // update the data base if f is cached
            void
            update(double a, double b, f_ff_t f,
                   const f2_mpfr_result<double>& r);
            // enable caching for f in func-name-f64_2.bin
            void
            use(f_ff_t f, const std::string& func_name, double v);

            // returns nullptr if nothing was found
            const f2_mpfr_result<float>*
            result(float a, float b, f_ff_t f,
                   f2_mpfr_result<float>& spc);
            // update the data base if f is cached
            void
            update(float a, float b, f_ff_t f,
                   const f2_mpfr_result<float>& r);
            // enable caching for f in func-name-f64_2.bin
            void
            use(f_ff_t f, const std::string& func_name, float v);

            struct f1i_tag {};
            template <typename _T>
            using f1i_mpfr_result = mpfr_result<_T, f1i_tag>;

            // returns nullptr if nothing was found
            const f1i_mpfr_result<std::pair<double, int32_t> >*
            result(double a, fi_f_t f,
                   f1i_mpfr_result<std::pair<double, int32_t> >& spc);
            // update the data base if f is cached
            void
            update(double a, fi_f_t f,
                   const f1i_mpfr_result<std::pair<double, int32_t> >& r);
            // enable caching for f in func-name-f64_2.bin
            void
            use(fi_f_t f, const std::string& func_name, double v);

            // returns nullptr if nothing was found
            const f1i_mpfr_result<std::pair<float, int32_t> >*
            result(float a, fi_f_t f,
                   f1i_mpfr_result<std::pair<float, int32_t> >& spc);
            // update the data base if f is cached
            void
            update(float a, fi_f_t f,
                   const f1i_mpfr_result<std::pair<float, int32_t> >& r);
            // enable caching for f in func-name-f64_2.bin
            void
            use(fi_f_t f, const std::string& func_name, float v);

        }
    }
}

// local variables:
// mode: c++
// end:
#endif
