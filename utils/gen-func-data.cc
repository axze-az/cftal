// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include <cftal/constants.h>
#include <cftal/types.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/of_fp_funcs.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <cstdlib>
#include <mpfr.h>

namespace cftal {
    namespace test {

        using mpfr_func_1 =
            int (*)(mpfr_t, const mpfr_t, mpfr_rnd_t);

        void generate_func_1(std::ostream& s,
                             mpfr_func_1 f,
                             int rep_bits, std::size_t cnt,
                             func_domain<double> dom);

        using mpfr_func_2 =
            int(*)(mpfr_t, const mpfr_t, const mpfr_t, mpfr_rnd_t);

        void generate_func_2(std::ostream& s,
                             mpfr_func_2 f,
                             int rep_bits, std::size_t cnt);
    }
}

void
cftal::test::
generate_func_1(std::ostream& s, mpfr_func_1 f,
                int rep_bits, std::size_t cnt,
                func_domain<double> dom)
{
    mpfr_t mp_res, mp_res53, mp_res54, mp_input;

    mpfr_init2(mp_res,  53+rep_bits+1);
    mpfr_init2(mp_res53, 53);
    mpfr_init2(mp_res54, 54);
    mpfr_init2(mp_input, 53);

    // std::uniform_int_distribution<uint64_t> distribution;
    uniform_real_distribution<double> distribution(dom.first, dom.second);
    std::mt19937_64 rnd;

    while (cnt != 0) {
        bytes8 input(distribution(rnd));
        double d=input.f64();
        mpfr_set_d(mp_input, d, GMP_RNDN);
        f(mp_res, mp_input, GMP_RNDN);
        f(mp_res54, mp_input, GMP_RNDN);
        if(mpfr_cmp (mp_res54, mp_res)!=0)
            continue;
        // This is a difficult to round case.
        // first filter results equal to zero, infty, nan , 1.0
        bytes8 res(mpfr_get_d(mp_res, GMP_RNDN));
        if ((res.u32h() & 0x7ff00000u) == 0x7ff00000u)
            continue;
        if (res.f64() == 1.0)
            continue;
        if (res.f64() ==0.0)
            continue;
        f(mp_res53, mp_input, GMP_RNDN);
        if(mpfr_cmp (mp_res54, mp_res53)==0)
            continue;
        bytes8 r53(mpfr_get_d(mp_res53, GMP_RNDN));
        s << "N "
          << std::hex
          << std::setfill('0')
          << std::setw(8)
          << input.u32h()
          << ' '
          << std::setw(8)
          << input.u32l()
          << ' '
          << std::setw(8)
          << r53.u32h()
          << ' '
          << std::setw(8)
          << r53.u32l()
          << " # "
          << std::setprecision(18)
          << std::scientific
          << input.f64()
          // << " r: "
          // << r53._f64
          << std::endl;
        --cnt;
    }
    mpfr_clear(mp_res);
    mpfr_clear(mp_res53);
    mpfr_clear(mp_res54);
    mpfr_clear(mp_input);
}

void
cftal::test::
generate_func_2(std::ostream& s, mpfr_func_2 f,
                int rep_bits, std::size_t cnt)
{
    mpfr_t mp_res, mp_res53, mp_res54, mp_input0, mp_input1;

    mpfr_init2(mp_res,  53+rep_bits+1);
    mpfr_init2(mp_res53, 53);
    mpfr_init2(mp_res54, 54);
    mpfr_init2(mp_input0, 53);
    mpfr_init2(mp_input1, 53);

    std::uniform_int_distribution<uint64_t> distribution;
    std::mt19937_64 rnd;

    while (cnt != 0) {
        bytes8 input0(distribution(rnd));
        double d0=input0.f64();
        mpfr_set_d(mp_input0, d0, GMP_RNDN);
        bytes8 input1(distribution(rnd));
        double d1=input1.f64();
        mpfr_set_d(mp_input1, d1, GMP_RNDN);

        f(mp_res, mp_input0, mp_input1, GMP_RNDN);
        f(mp_res54, mp_input0, mp_input1, GMP_RNDN);
        if(mpfr_cmp (mp_res54, mp_res)!=0)
            continue;
        // This is a difficult to round case.
        // first filter results equal to zero, infty, nan , 1.0
        bytes8 res(mpfr_get_d(mp_res, GMP_RNDN));
        if ((res.u32h() & 0x7ff00000u) == 0x7ff00000u)
            continue;
        if (res.f64() == 1.0)
            continue;
        if (res.f64() ==0.0)
            continue;
        f(mp_res53, mp_input0, mp_input1, GMP_RNDN);
        if(mpfr_cmp (mp_res54, mp_res53)==0)
            continue;
        bytes8 r53(mpfr_get_d(mp_res53, GMP_RNDN));
        s << "N "
          << std::hex
          << std::setfill('0')
          << std::setw(8)
          << input0.u32h()
          << ' '
          << std::setw(8)
          << input0.u32l()
          << ' '
          << input1.u32h()
          << ' '
          << std::setw(8)
          << input1.u32l()
          << ' '
          << std::setw(8)
          << r53.u32h()
          << ' '
          << std::setw(8)
          << r53.u32l()
          << " # "
          << std::setprecision(18)
          << std::scientific
          << input0.f64()
          << ' '
          << input1.f64()
          << std::endl;
        --cnt;
    }
    mpfr_clear(mp_res);
    mpfr_clear(mp_res53);
    mpfr_clear(mp_res54);
    mpfr_clear(mp_input0);
    mpfr_clear(mp_input1);
}


int main(int argc, char** argv)
{
    // const int rep_bits= 10;
    std::size_t cnt=1000;
    int rep_bits=10;

    cftal::test::mpfr_func_1 mpfr_func1 = nullptr;
    cftal::test::mpfr_func_2 mpfr_func2 = nullptr;

    struct fninfo {
        const char* fname;
        cftal::test::mpfr_func_1 _f1;
        cftal::test::mpfr_func_2 _f2;
        double _l;
        double _h;
    };

    static const struct fninfo g_func_info[] = {
        {
            "exp",        mpfr_exp,       nullptr,
            -712.0,     712.0
        }, {
            "expm1",      mpfr_expm1,     nullptr,
            -712.0,     712.0
        }, {
            "log",        mpfr_log,       nullptr,
            0.0,  std::numeric_limits<double>::max()
        }, {
            "sinh",       mpfr_sinh,      nullptr,
            -712.0,     712.0
        }, {
            "cosh",       mpfr_cosh,      nullptr,
            -712.0,     712.0
        }, {
            "exp2",       mpfr_exp2,      nullptr,
            -1026.0,    1026.0
        }, {
            "exp10",      mpfr_exp10,     nullptr,
            -330.0,     310.0
        }, {
            "cot",       mpfr_cot,      nullptr,
            -std::numeric_limits<double>::max(),
            std::numeric_limits<double>::max()
        }, {
            "cbrt",       mpfr_cbrt,      nullptr,
            -std::numeric_limits<double>::max(),
            std::numeric_limits<double>::max()
        }, {
            "sqrt",       mpfr_sqrt,      nullptr,
            0.0,  std::numeric_limits<double>::max()
        }, {
            "pow",        nullptr,        mpfr_pow,
            -std::numeric_limits<double>::max(),
            std::numeric_limits<double>::max()
        }
    };

    if (argc < 2 || argc > 4) {
        std::cerr << argv[0] << " func_name [rep_bits cnt]" << std::endl;
        return 3;
    }

    std::string fname=argv[1];
    cftal::test::func_domain<double> dom=
        std::make_pair(-std::numeric_limits< double >::max(),
                        std::numeric_limits<double>::max());
    for (const auto& fi : g_func_info) {
        if (fname == fi.fname) {
            if (fi._f1 != nullptr) {
                mpfr_func1 = fi._f1;
                dom = std::make_pair(fi._l, fi._h);
            } else if (fi._f2 != nullptr) {
                mpfr_func2 = fi._f2;
            }
            break;
        }
    }

    if (mpfr_func1 == nullptr && mpfr_func2 == nullptr) {
        std::cerr << "list of possible functions:\n";
        for (const auto& fi: g_func_info) {
            std::cerr << fi.fname << std::endl;
        }
        return 3;
    }


    if (argc > 2) {
        int irep_bits = std::strtol(argv[2], nullptr, 0);
        if (irep_bits <= 0) {
            std::cerr << argv[0] << " func_name [rep_bits cnt]" << std::endl;
            std::cerr << "rep_bits must be greater than 0" << std::endl;
            return 3;
        }
        rep_bits = irep_bits;
        if (argc > 3) {
            long cntl=std::strtol(argv[3], nullptr, 0);
            if (cntl <= 0) {
                std::cerr << argv[0] << " func_name rep_bits cnt" << std::endl;
                std::cerr << "cnt must be greater than 0" << std::endl;
                return 3;
            }
            cnt = cntl;
        }
    }

    std::cout << "# bad cases generated by " << argv[0] << '\n';
    std::cout << "# for " << fname <<  ' ' << rep_bits << ' ' << cnt << '\n';


    if (mpfr_func2 != nullptr) {
        cftal::test::generate_func_2(std::cout, mpfr_func2,
                                     rep_bits, cnt);
    } else if (mpfr_func1 != nullptr) {
        cftal::test::generate_func_1(std::cout, mpfr_func1,
                                    rep_bits, cnt, dom);
    }
    return 0;
}
