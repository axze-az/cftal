//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_hypot.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    const int ulp2=1;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
    }

    func_domain<double> d=std::make_pair(-std::numeric_limits< double >::max(),
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_2_up_to<
        double, _N, check_hypot<double> >::v(st, d, d, speed_only,
                                           cmp_ulp<double>(ulp2, us),
                                           cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    st=exec_stats(_N);
    us=std::make_shared<ulp_stats>();
    func_domain<double> d1=std::make_pair(-1024.0, 1024.0);
    func_domain<double> d2=std::make_pair(-1024.0, 1024.0);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        double, _N, check_hypot<double> >::v(st, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);
    d1=std::make_pair(-10.0, 10.0);
    d2=std::make_pair(-10.0, 10.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_hypot<double> >::v(st, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);

    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
