//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_pow.h"
#include <iostream>
#include <iomanip>

// critical values during test a^b
// v1f64 a=1.293872646225411094e+00;  v1f64 b=-1.778789453749938048e+03;

int main(int argc, char** argv)
{
    using namespace cftal::test;

    const int ulp2=1;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/pow.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "pow.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, true);
        rc&= check_func_2<double, 1, check_pow<double> >(v, ulp, 0, false);
        rc&= check_func_2<double, 2, check_pow<double> >(v, ulp, 0, false);
        rc&= check_func_2<double, 4, check_pow<double> >(v, ulp, 0, false);
        rc&= check_func_2<double, 8, check_pow<double> >(v, ulp, 0, false);
    }

    func_domain<double> d=std::make_pair(-std::numeric_limits< double >::max(),
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d, d, speed_only,
                                           cmp_ulp<double>(ulp2, us),
                                           cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    exec_stats<_N> st1;
    us=std::make_shared<ulp_stats>();
    func_domain<double> d1=std::make_pair(0.0, 20.0);
    func_domain<double> d2=std::make_pair(-200.0, 200.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st1, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);
    d1=std::make_pair(0x1p-10, 200.0);
    d2=std::make_pair(-80.0, 80.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st1, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);

    d1=std::make_pair(0x1p-10, 5.0);
    d2=std::make_pair(-10.0, 10.0);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st1, d1, d2, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt, true);

    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st1 << std::endl;
    return (rc == true) ? 0 : 1;
}
