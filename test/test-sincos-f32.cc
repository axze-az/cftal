//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_sincos.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    pgm_args ags=parse(argc, argv, 0x8000);


    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;

    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us_sin=std::make_shared<ulp_stats>();
    auto us_cos=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    struct cmp_ulp<std::pair<float, float> > cmp(ulp, us_sin, us_cos);
    rc &= of_fp_func_up_to<
        float, _N, check_sincos<float> >::v(st, dp,
                                            ags._speed_only,
                                            ags._mt,
                                            cmp,
                                            ags._cnt);
    std::cout << "sin ulps: "
              << std::fixed << std::setprecision(4) << *us_sin << std::endl;
    std::cout << "cos ulps: "
              << std::fixed << std::setprecision(4) << *us_cos << std::endl;
    std::cout << st << std::endl;

    auto dp2=std::make_pair(-0x1p18f, 0x1p18f);
    auto us_sin2=std::make_shared<ulp_stats>();
    auto us_cos2=std::make_shared<ulp_stats>();
    exec_stats<_N> st2;
    struct cmp_ulp<std::pair<float, float> > cmp2(ulp, us_sin2, us_cos2);
    rc &= of_fp_func_up_to<
        float, _N, check_sincos<float> >::v(st, dp2,
                                            ags._speed_only,
                                            ags._mt,
                                            cmp2,
                                            ags._cnt);
    std::cout << "sin ulps: "
              << std::fixed << std::setprecision(4) << *us_sin2 << std::endl;
    std::cout << "cos ulps: "
              << std::fixed << std::setprecision(4) << *us_cos2 << std::endl;
    std::cout << st << std::endl;

    return (rc == true) ? 0 : 1;
}
