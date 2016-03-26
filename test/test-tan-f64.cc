#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/tan.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "tan.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    const int ulp=1;
    const int _N=8;
    bool rc = true;

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0    
    rc &= check_func_1<double, 1, check_tan<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_tan<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_tan<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_tan<double> >(v, ulp, 0, false);
#endif
#if 1
    auto dp=std::make_pair(0.0, 0.62);
#else
    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
#endif    
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_tan<double> >::v(st, dp, cmp_ulp<double>(ulp, us),
                                           0x4000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
