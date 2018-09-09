//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_tgamma.h"
#include "cftal/test/mpfr_cache.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=12;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        mpfr_cache::use(mpfr_gamma, "tgamma", 0.0f);
    }
    func_domain<float> d=std::make_pair(-45.0f, +35.5f);
    std::cout << "testing tgamma" << std::endl;
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);

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

    rc &= of_fp_func_up_to<
        float, _N, check_tgamma<float> >::v(st, d, speed_only,
                                            cmp_ulp<float>(ulp, us),
                                            cnt,
                                            def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
