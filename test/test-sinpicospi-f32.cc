//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_sinpicospi.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    cpu_times_to_stdout tt;
    pgm_args ags=parse(argc, argv, 0x8000);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;

    bool rc=true;
    auto dp=std::make_pair(-0x1.5p25f, 0x1.5p25f);
    auto us_sin=std::make_shared<ulp_stats>();
    auto us_cos=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    struct cmp_ulp<std::pair<float, float> > cmp(ulp, us_sin, us_cos);
    rc &= of_fp_func_up_to<
        float, _N, check_sinpicospi<float> >::v(st, dp,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp,
                                                ags._cnt);
    std::cout << "sinpi ulps: "
              << std::fixed << std::setprecision(4) << *us_sin << std::endl;
    std::cout << "cospi ulps: "
              << std::fixed << std::setprecision(4) << *us_cos << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
