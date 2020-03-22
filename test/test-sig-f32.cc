//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_sig.h"

int main(int argc, char** argv)
{
#if 0
    using namespace cftal::test;
    const func_domain<float> di[]={
        std::make_pair(-89.0f, +18.0f)
    };
    const int shifts[]={0};
    int r=program<check_sig<float>,
                  16, 1, 0x8000>(argc,
                                argv,
                                mpfr_ext::sig,
                                di,
                                shifts);
    return r;
#else
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    pgm_args ags=parse(argc, argv, 0x8000);

    const int ulp=1;
    const int _N=16;
    bool rc=true;

    using ftype = float;
    if (ags._speed_only == false) {
        if (ags._use_cache==true) {
            mpfr_cache::use(mpfr_ext::sig,
                            "sig", ftype(0.0));
        }
    }

    auto d = std::make_pair(-89.0f, +18.0f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_sig<ftype> >::v(st, d,
                                         ags._speed_only,
                                         ags._mt,
                                         cmp_ulp<ftype>(ulp, us),
                                         ags._cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}

