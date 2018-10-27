//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_asinh.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    cftal::v1f32 t=-2.834401250000000000e+06f;
    std::pair<float, float> rp, rn;
    float fp=call_mpfr::func(t(), mpfr_asinh, &rp);
    float fn=call_mpfr::func(-t(), mpfr_asinh, &rn);

    std::cout << fp << std::endl
              << rp.first << std::endl
              << rp.second << std::endl;
    std::cout << fn << std::endl
              << rn.first << std::endl
              << rn.second << std::endl;
#else
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(
        -std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_asinh<float> >::v(st, d, speed_only,
                                           cmp_ulp<float>(ulp, us),
                                           cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
