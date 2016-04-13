#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_pow.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/pow.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "pow.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, true);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    // std::cerr << std::hexfloat;
    const int ulp=1;
    const int _N=8;
    
    bool rc= check_func_2<double, 1, check_pow<double> >(v, ulp, 0, false);
    rc&= check_func_2<double, 2, check_pow<double> >(v, ulp, 0, false);
    rc&= check_func_2<double, 4, check_pow<double> >(v, ulp, 0, false);
    rc&= check_func_2<double, 8, check_pow<double> >(v, ulp, 0, false);

    func_domain<double> d=std::make_pair(-std::numeric_limits< double >::max(),
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d, d, cmp_ulp<double>(ulp, us),
                                           0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;

    func_domain<double> d1=std::make_pair(0.0, 20.0);
    func_domain<double> d2=std::make_pair(0.0, 100.0);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        double, _N, check_pow<double> >::v(st, d1, d2, cmp_ulp<double>(ulp, us),
                                           0x10000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
