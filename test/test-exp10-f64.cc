//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_exp10.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
#if 1
    const double exp10_lo_den_nom= -3.076526555685887842628290e+02;
    using namespace cftal::test;

    const func_domain<double> di[]={
        std::make_pair(-330.0, 310.0),
        // check the denormal result range
        std::make_pair(-330.0, exp10_lo_den_nom)
    };
    const int shifts[]= {
        0,
        -3
    };
    int r=program<check_exp10<double>, 8, 1, 0x8000>(argc,
                                                     argv,
                                                     mpfr_exp10,
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
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/exp10.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "exp10.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_exp10<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 2, check_exp10<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 4, check_exp10<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 8, check_exp10<double> >(v, ulp, 0, false);
    }
    func_domain<double> d=std::make_pair(-330.0, 310.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        double, _N, check_exp10<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt);
    // check the denormal result range
    const double exp10_lo_den_nom= -3.076526555685887842628290e+02;
    d= std::make_pair(-330, exp10_lo_den_nom);
    rc &= of_fp_func_up_to<
        double, _N, check_exp10<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt>>3);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
