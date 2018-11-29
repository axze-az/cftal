//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_sincos.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    pgm_args ags=parse(argc, argv, 0x8000);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    if (ags._speed_only==true) {
        ags._cnt *=8;
    } else {
        // sin part
        std::string test_data_file=
            append_filename(ags._data_dir, "sin.testdata");
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
            append_filename(ags._data_dir, "cos.testdata");
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

    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
    auto us_sin=std::make_shared<ulp_stats>();
    auto us_cos=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    struct cmp_ulp<std::pair<double, double> > cmp(ulp, us_sin, us_cos);
    rc &= of_fp_func_up_to<
        double, _N, check_sincos<double> >::v(st, dp,
                                              ags._speed_only,
                                              ags._mt,
                                              cmp,
                                              ags._cnt);
    std::cout << "sin ulps: "
              << std::fixed << std::setprecision(4) << *us_sin << std::endl;
    std::cout << "cos ulps: "
              << std::fixed << std::setprecision(4) << *us_cos << std::endl;
    std::cout << st << std::endl;

    auto dp2=std::make_pair(-0x1p45, 0x1p45);
    auto us_sin2=std::make_shared<ulp_stats>();
    auto us_cos2=std::make_shared<ulp_stats>();
    exec_stats<_N> st2;
    struct cmp_ulp<std::pair<double, double> > cmp2(ulp, us_sin2, us_cos2);
    rc &= of_fp_func_up_to<
        double, _N, check_sincos<double> >::v(st, dp2,
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
