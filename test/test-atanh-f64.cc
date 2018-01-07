//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_atanh.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/atanh.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "atanh.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    rc &= check_func_1<double, 1, check_atanh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_atanh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_atanh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_atanh<double> >(v, ulp, 0, false);
#endif
    func_domain<double> d=std::make_pair(-1.0, 1.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_atanh<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
