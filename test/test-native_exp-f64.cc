#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;

    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/exp.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "exp.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    bool rc= check_func_1<double, 2, check_native_exp<double> >(v, 1, 0, false);
#if 0
    rc &= check_func_1<double, 4, check_native_exp<double> >(v, 1, 0, false);
    rc &= check_func_1<double, 8, check_native_exp<double> >(v, 1, 0, false);

    func_domain<double> d=std::make_pair(-800.0, 710.0);
    rc &= of_fp_func_up_to<
        double, 8, check_native_exp<double> >::v(d, cmp_ulp<double>(1));
#endif
    return (rc == true) ? 0 : 1;
}
