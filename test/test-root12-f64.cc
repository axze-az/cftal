//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_root12.h"

int main(int argc, char** argv)
{
#if 1
    using namespace cftal::test;
    const func_domain<double> di[]={
        std::make_pair(0.0, std::numeric_limits<double>::max())
    };
    const int shifts[]={0};
    int r=program<check_root12<double>, 8, 1, 0x8000>(argc,
                                                      argv,
                                                      mpfr_ext::root12,
                                                      di,
                                                      shifts);
    return r;
#else
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<double> dd=std::make_pair(0.0,
                                          std::numeric_limits<double>::max());
    // dd=std::make_pair(0.125, 1.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> d_st;
    rc &= of_fp_func_up_to<
        double, _N, check_root12<double> >::v(d_st, dd, speed_only,
                                              cmp_ulp<double>(ulp, us),
                                              cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << d_st << std::endl;
    return rc==true ? 0 : 1;
#endif
}
