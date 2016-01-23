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

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    bool rc= check_func_1<double, 2, check_tan<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_tan<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_tan<double> >(v, ulp, 0, false);

    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, 8, check_tan<double> >::v(dp, cmp_ulp<double>(ulp, us),
                                          0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    return (rc == true) ? 0 : 1;
}
