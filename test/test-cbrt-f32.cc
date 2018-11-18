//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_cbrt.h"


int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<float> di[]={
        std::make_pair(-std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::max())
    };
    const int shifts[]={0};
    int r=program<check_cbrt<float>, 16, 1, 0x8000>(argc,
                                                    argv,
                                                    mpfr_cbrt,
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
    func_domain<float> df=std::make_pair(-std::numeric_limits<float>::max(),
                                          std::numeric_limits<float>::max());
    auto usf=std::make_shared<ulp_stats>();
    exec_stats<_N> f_st;
    rc &= of_fp_func_up_to<
        float, _N, check_cbrt<float> >::v(f_st, df, speed_only,
                                          cmp_ulp<float>(ulp, usf),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *usf << std::endl;
    std::cout << f_st << std::endl;
    return rc==true ? 0 : 1;
#endif
}
