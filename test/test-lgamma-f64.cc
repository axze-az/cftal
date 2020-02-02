//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_lgamma.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    pgm_args ags=parse(argc, argv, 0x8000);
    if (ags._speed_only == false) {
        if (ags._use_cache==true) {
            mpfr_cache::use(mpfr_lgamma, "lgamma", 0.0);
        }
    }

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int ulp_pos=1;
    const int _N=8;
    bool rc=true;

    // func_domain<double> d=std::make_pair(-186.0, +172.0);
    // func_domain<double> d=std::make_pair(-0x1p-54, 0x1p-54);
    // func_domain<double> d=std::make_pair(-3.0, 3.0);
    // func_domain<double> d=std::make_pair(-186.0, 172.0);
    func_domain<double> d=std::make_pair(-0x1.0p54, 2.6e305);
    func_domain<double> d1=std::make_pair(0.0, 2.6e305);
    // func_domain<double> d=std::make_pair(-7.0, -1.0);
    // func_domain<double> d=std::make_pair(0x1p-54, 1.0);
    std::cout << "f64 testing lgamma" << std::endl;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    // test also some integral and integral-1/2 values
    std::vector<double> def_args=default_arguments<double>::values;
    for (std::size_t i=1; i<4097; ++i) {
        auto di=static_cast<double>(i);
        auto dih=di-0.5;
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args)) {
            def_args.push_back(di);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dih)==
            std::end(def_args)) {
            def_args.push_back(dih);
        }
        auto dip=std::nextafter(di, std::numeric_limits<double>::infinity());
        auto dihp=std::nextafter(dih, std::numeric_limits<double>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihp)==
            std::end(def_args)) {
            def_args.push_back(dihp);
        }
        auto dim=std::nextafter(di, -std::numeric_limits<double>::infinity());
        auto dihm=std::nextafter(dih, -std::numeric_limits<double>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dim)==
            std::end(def_args)) {
            def_args.push_back(dim);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihm)==
            std::end(def_args)) {
            def_args.push_back(dihm);
        }
    }

    using test_t=of_fp_func_up_to<double, _N, check_lgamma<double> >;
    rc &= test_t::v(st, d,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, double>(ulp, us),
                    ags._cnt >> 1,
                    def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    exec_stats<_N> stp;
    std::vector<double> p_def_args;
    std::copy_if(std::cbegin(def_args), std::cend(def_args),
                 std::back_inserter(p_def_args),
                 [](double v)->bool {
                     return v>=0.0;
                 });
    us = std::make_shared<ulp_stats>();
    rc &= test_t::v(stp, d1,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, double>(ulp_pos, us),
                    ags._cnt >> 1,
                    p_def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << stp << std::endl;
    return (rc == true) ? 0 : 1;
}

