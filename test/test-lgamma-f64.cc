//
// Copyright Axel Zeuner 2010-2018. Use, modification and
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

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1<<24;
    const int ulp_pos=2;
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
    std::cout << "testing lgamma" << std::endl;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    // test also all integral values
    std::vector<double> def_args=default_arguments<double>::values;
    for (std::size_t i=1; i<256; ++i) {
        auto di=static_cast<double>(i);
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args))
            def_args.push_back(di);
        auto dip=std::nextafter(di, std::numeric_limits<double>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        auto dim=std::nextafter(di, -std::numeric_limits<double>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dim);
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
    us = std::make_shared<ulp_stats>();
    rc &= test_t::v(stp, d1,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, double>(ulp_pos, us),
                    ags._cnt >> 1,
                    true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << stp << std::endl;
    return (rc == true) ? 0 : 1;
}

