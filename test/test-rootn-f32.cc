//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_rootn.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    const int ulp3=1;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    pgm_args ags=parse(argc, argv, 0x8000);


    func_domain<float> da=std::make_pair(-std::numeric_limits<float>::max(),
                                         std::numeric_limits<float>::max());
    func_domain<int32_t> db=
        std::make_pair(double(std::numeric_limits<int32_t>::min()),
                       double(std::numeric_limits<int32_t>::max()));
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_2_up_to<
        float, _N, check_rootn<float>, float, int32_t>::
            v(st, da, db, ags._speed_only, ags._mt,
              cmp_ulp<float>(ulp3, us), ags._cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    exec_stats<_N> st1;
    us=std::make_shared<ulp_stats>();
    func_domain<float> d1=std::make_pair(0.0f, 30.0f);
    func_domain<int32_t> d2=std::make_pair(-20, 20);
    rc &= of_fp_func_2_up_to<
        float, _N, check_rootn<float>, float, int32_t>::
            v(st1, d1, d2, ags._speed_only,
              ags._mt, cmp_ulp<float>(ulp, us), ags._cnt, true);
    d1=std::make_pair(0x1p-10f, 5.0f);
    d2=std::make_pair(-10, 10);
    rc &= of_fp_func_2_up_to<
        float, _N, check_rootn<float>, float, int32_t>::
            v(st1, d1, d2, ags._speed_only,
              ags._mt, cmp_ulp<float>(ulp, us), ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st1 << std::endl;
    return (rc == true) ? 0 : 1;
}
