//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_sincos.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
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
        // sin part
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/sin.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "sin.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);

        rc &= check_func_1<double, 1, check_sincos<double>::sin >(v, ulp,
                                                                  0, false);
        rc &= check_func_1<double, 2, check_sincos<double>::sin >(v, ulp,
                                                                  0, false);
        rc &= check_func_1<double, 4, check_sincos<double>::sin >(v, ulp,
                                                                  0, false);
        rc &= check_func_1<double, 8, check_sincos<double>::sin >(v, ulp,
                                                                  0, false);
        // cos part
        test_data_file=
            append_filename(test_data_dir, "../../test/data/cos.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "cos.testdata");
        }
        v=read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_sincos<double>::cos >(v, ulp,
                                                                  0, false);
        rc &= check_func_1<double, 2, check_sincos<double>::cos >(v, ulp,
                                                                  0, false);
        rc &= check_func_1<double, 4, check_sincos<double>::cos >(v, ulp,
                                                                  0, false);
        rc &= check_func_1<double, 8, check_sincos<double>::cos >(v, ulp,
                                                                  0, false);
    }
#if 1
    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
    auto us_sin=std::make_shared<ulp_stats>();
    auto us_cos=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    struct cmp_ulp<std::pair<double, double> > cmp(ulp, us_sin, us_cos);
    rc &= of_fp_func_up_to<
        double, _N, check_sincos<double> >::v(st, dp, speed_only, cmp, cnt);
    std::cout << "sin ulps: "
              << std::fixed << std::setprecision(4) << *us_sin << std::endl;
    std::cout << "cos ulps: "
              << std::fixed << std::setprecision(4) << *us_cos << std::endl;
    std::cout << st << std::endl;

    auto dp2=std::make_pair(-0x1p28, 0x1p28);
    auto us_sin2=std::make_shared<ulp_stats>();
    auto us_cos2=std::make_shared<ulp_stats>();
    exec_stats st2(_N);
    struct cmp_ulp<std::pair<double, double> > cmp2(ulp, us_sin2, us_cos2);
    rc &= of_fp_func_up_to<
        double, _N, check_sincos<double> >::v(st, dp2, speed_only, cmp2, cnt);
    std::cout << "sin ulps: "
              << std::fixed << std::setprecision(4) << *us_sin2 << std::endl;
    std::cout << "cos ulps: "
              << std::fixed << std::setprecision(4) << *us_cos2 << std::endl;
    std::cout << st << std::endl;
#else
    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_sincos<double>::sin >::v(st, dp, speed_only,
                                                   cmp_ulp<double>(ulp, us),
                                                   cnt);
    rc &= of_fp_func_up_to<
        double, _N, check_sincos<double>::cos >::v(st, dp, speed_only,
                                                   cmp_ulp<double>(ulp, us),
                                                   cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
#endif
    return (rc == true) ? 0 : 1;
}
