#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/cos.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "cos.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    const int ulp = 1;
    const int _N=8;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    bool rc= true;
    rc &= check_func_1<double, 1, check_cos<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_cos<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_cos<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_cos<double> >(v, ulp, 0, false);

    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_cos<double> >::v(st, dp, cmp_ulp<double>(ulp, us),
                                           0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

    exec_stats st2(_N);
    auto dp2=std::make_pair(-0x1p20, 0x1p20);
    auto us2=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_cos<double> >::v(st2, dp2,
                                           cmp_ulp<double>(ulp, us2),
                                           0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us2 << std::endl;
    std::cout << st2 << std::endl;

    return (rc == true) ? 0 : 1;
}
