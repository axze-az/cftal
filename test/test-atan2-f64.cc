//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_atan2.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;

    pgm_args ags=parse(argc, argv, 0x8000);

    if (ags._speed_only) {
        ags._cnt *=8;
    }
    func_domain<double> d=std::make_pair(-std::numeric_limits< double >::max(),
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_2_up_to<
        double, _N, check_atan2<double> >::v(st, d, d,
                                             ags._speed_only,
                                             ags._mt,
                                             cmp_ulp<double>(ulp, us),
                                             ags._cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;

    func_domain<double> d1=std::make_pair(-100.0, 100.0);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        double, _N, check_atan2<double> >::v(st, d1, d1,
                                             ags._speed_only,
                                             ags._mt,
                                             cmp_ulp<double>(ulp, us),
                                             ags._cnt/2);
    func_domain<double> d2=std::make_pair(-2.0, 2.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_atan2<double> >::v(st, d2, d2,
                                             ags._speed_only,
                                             ags._mt,
                                             cmp_ulp<double>(ulp, us),
                                             ags._cnt/2);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
