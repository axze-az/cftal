//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_tgamma.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;

    pgm_args ags=parse(argc, argv, 0x8000);
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    if (ags._speed_only == false) {
        if (ags._use_cache==true) {
            mpfr_cache::use(mpfr_gamma, "tgamma", 0.0);
        }
    }
    const int ulp=12;
    const int _N=8;
    bool rc=true;

    func_domain<double> d=std::make_pair(-186.0, +172.0);
    std::cout << "testing tgamma" << std::endl;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;

    // test also some integral and integral-1/2 values
    std::vector<double> def_args=default_arguments<double>::values;
    for (std::size_t i=1; i<173; ++i) {
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
    rc &= of_fp_func_up_to<
        double, _N, check_tgamma<double> >::v(st, d,
                                              ags._speed_only,
                                              ags._mt,
                                              cmp_ulp<double>(ulp, us),
                                              ags._cnt,
                                              def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

