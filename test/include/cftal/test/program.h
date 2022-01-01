//
// Copyright (C) 2010-2022 Axel Zeuner
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
#if !defined (__CFTAL_TEST_PROGRAM_H__)
#define __CFTAL_TEST_PROGRAM_H__ 1

#include <cftal/config.h>
#include <cftal/test/of_math_funcs.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/mpfr_cache.h>
#include <cftal/test/cpu_times.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {

        struct pgm_args {
            // speed test only
            bool _speed_only;
            // multi thread
            bool _mt;
            // use cache
            bool _use_cache;
            // fast
            bool _fast;
            // slow
            bool _slow;
            // data directory
            std::string _data_dir;
            // the count of tests to perform
            std::size_t _cnt;
            pgm_args(std::size_t c=0x80000)
              : _speed_only(false), _mt(true),
                _use_cache(false), _fast(false),
                _slow(false),
                _data_dir("../test/data/"),
                _cnt(c) {}
        };

        std::ostream&
        operator<<(std::ostream& s, const pgm_args& ags);

        pgm_args
        parse(int argc, char** argv, std::size_t cnt);

        // f64 test program
        template <typename _CHECK,
                  std::size_t _N, int _ULP,
                  std::size_t _CNT,
                  std::size_t _M>
        int
        program(int argc, char** argv,
                call_mpfr::f1_t func,
                const func_domain<double> (&d)[_M],
                const int (&count_shift)[_M],
                bool table_check=true);

        // f32 test program
        template <typename _CHECK,
                  std::size_t _N, int _ULP,
                  std::size_t _CNT,
                  std::size_t _M>
        int
        program(int argc, char** argv,
                call_mpfr::f1_t func,
                const func_domain<float> (&d)[_M],
                const int (&count_shift)[_M]);
    }
}

template <typename _CHECK,
          std::size_t _N,int _ULP,
          std::size_t _CNT,
          std::size_t _M>
int
cftal::test::program(int argc, char** argv,
                     call_mpfr::f1_t func,
                     const func_domain<double> (&d)[_M],
                     const int (&count_shift)[_M],
                     bool table_check)
{
    cpu_times_to_stdout tt;
    pgm_args ags=parse(argc, argv, _CNT);
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    std::cout << "f64 test of " << _CHECK::fname()
              << ' ' << ags << std::endl;
    bool rc=true;
    using ftype = double;
    if (ags._speed_only == false){
        if (ags._use_cache==true) {
            mpfr_cache::use(func, _CHECK::fname(), ftype(0.0));
        }
        if (table_check) {
            try {
                std::string fname=_CHECK::fname();
                fname += ".testdata";
                std::string td_file=append_filename(ags._data_dir, fname);
                std::vector<func_arg_result<ftype> > v=
                    read_double_file(td_file, false);
                rc &= check_func_1<ftype, 1, _CHECK >(v, _ULP, 0, false);
                rc &= check_func_1<ftype, 2, _CHECK >(v, _ULP, 0, false);
                rc &= check_func_1<ftype, 4, _CHECK >(v, _ULP, 0, false);
                rc &= check_func_1<ftype, 8, _CHECK >(v, _ULP, 0, false);
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what() << std::endl;
            }
            catch (...) {
            }
        }
    }
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    for (std::size_t i=0; i<_M; ++i) {
        std::size_t cnt= ags._cnt;
        uint32_t sh=std::abs(count_shift[i]);
        if (count_shift[i] < 0) {
            cnt >>= sh;
        } else if (count_shift[i]>0) {
            cnt <<= sh;
        }
        rc &= of_fp_func_up_to<
            ftype, _N, _CHECK>::v(st, d[i],
                                  ags._speed_only,
                                  ags._mt,
                                  cmp_ulp<ftype>(_ULP, us),
                                  cnt);
    }
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

template <typename _CHECK,
          std::size_t _N,int _ULP,
          std::size_t _CNT,
          std::size_t _M>
int
cftal::test::program(int argc, char** argv,
                     call_mpfr::f1_t func,
                     const func_domain<float> (&d)[_M],
                     const int (&count_shift)[_M])
{
    cpu_times_to_stdout tt;
    pgm_args ags=parse(argc, argv, _CNT);
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    std::cout << "f32 test of " << _CHECK::fname()
              << ' ' << ags << std::endl;;
    bool rc=true;
    using ftype = float;
    if (ags._speed_only == false) {
        if (ags._use_cache==true) {
            mpfr_cache::use(func, _CHECK::fname(), ftype(0.0));
        }
    }
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    for (std::size_t i=0; i<_M; ++i) {
        std::size_t cnt= ags._cnt;
        uint32_t sh=std::abs(count_shift[i]);
        if (count_shift[i] < 0) {
            cnt >>= sh;
        } else if (count_shift[i]>0) {
            cnt <<= sh;
        }
        rc &= of_fp_func_up_to<
            ftype, _N, _CHECK>::v(st, d[i],
                                  ags._speed_only,
                                  ags._mt,
                                  cmp_ulp<ftype>(_ULP, us),
                                  cnt);
    }
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_PROGRAM_H__
