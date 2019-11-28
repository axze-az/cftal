//
// Copyright Axel Zeuner 2010-2019. Use, modification and
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
            mpfr_cache::use(mpfr_lgamma, "lgamma", 0.0f);
        }
    }

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1<<24;
    const int ulp_pos=2;
    const int _N=16;
    bool rc=true;

    // func_domain<float> d=std::make_pair(-186.0, +172.0);
    // func_domain<float> d=std::make_pair(0.0f, 4.1e36f);
    // func_domain<float> d=std::make_pair(0.0, 0x1p-53);
    func_domain<float> d=std::make_pair(-0x1p24f, 4.1e36f);
    func_domain<float> d1=std::make_pair(0.0f, 4.1e36f);
    std::cout << "f32 testing lgamma" << std::endl;

    // test also all integral values
    std::vector<float> def_args=default_arguments<float>::values;
    for (std::size_t i=1; i<36; ++i) {
        auto di=static_cast<float>(i);
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args)) {
            def_args.push_back(di);
        }
        auto dip=std::nextafter(di, std::numeric_limits<float>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        auto dim=std::nextafter(di, -std::numeric_limits<float>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dim);
        }
    }
    using test_t=of_fp_func_up_to<float, _N, check_lgamma<float> >;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= test_t::v(st, d,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, float>(ulp, us),
                    ags._cnt >> 1,
                    def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

    static_cast<void>(d1);
    static_cast<void>(ulp_pos);

    exec_stats<_N> stp;
    us = std::make_shared<ulp_stats>();
    rc &= test_t::v(stp, d1,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, float>(ulp_pos, us),
                    ags._cnt >> 1,
                    true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << stp << std::endl;

    return (rc == true) ? 0 : 1;
}
