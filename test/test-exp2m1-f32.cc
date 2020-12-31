//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_exp2m1.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<float> di[]={
        std::make_pair(-25.0f, 129.0f),
        std::make_pair(-0x1p-4, 0x1p-4)
    };
    const int shifts[]={
        0,
        -2
    };
    int r=program<check_exp2m1<float>, 16, 1, 0x8000>(argc,
                                                      argv,
                                                      mpfr_ext::exp2m1,
                                                      di,
                                                      shifts);
    return r;
#else
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    exec_stats<_N> st;
    func_domain<float> d=std::make_pair(-25.0f, 129.0f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp2m1<float> >::v(st, d, speed_only,
                                            cmp_ulp<float>(ulp, us),
                                            cnt);
    d=std::make_pair(-0x1p-4, 0x1p-4);
    rc &= of_fp_func_up_to<
        float, _N, check_exp2m1<float> >::v(st, d, speed_only,
                                            cmp_ulp<float>(ulp, us),
                                            cnt>>2);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
