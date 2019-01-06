//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_sinh.h"

int main(int argc, char** argv)
{
#if 1
    using namespace cftal::test;
    const func_domain<float> di[]={
        std::make_pair(-90.0f, 90.0f)
    };
    const int shifts[]={0};
    int r=program<check_sinh<float>, 16, 1, 0x8000>(argc,
                                                    argv,
                                                    mpfr_sinh,
                                                    di,
                                                    shifts);
    return r;
#else
    using namespace cftal::test;
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
    func_domain<float> d=std::make_pair(-90.0f, 90.0f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_sinh<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
