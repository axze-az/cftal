#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/expm1.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "expm1.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    bool rc= check_func_1<double, 2, check_expm1<double> >(v, 1, 0, false);
    rc &= check_func_1<double, 4, check_expm1<double> >(v, 1, 0, false);
    rc &= check_func_1<double, 8, check_expm1<double> >(v, 1, 0, false);

    func_domain<double> d=std::make_pair(-800.0, 710.0);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, 8, check_expm1<double> >::v(d, cmp_ulp<double>(1, us));
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    return (rc == true) ? 0 : 1;
}
