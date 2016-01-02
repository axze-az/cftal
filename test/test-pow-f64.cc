#include "cftal/test/of_math_funcs.h"
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
    bool rc= check_func_2<double, 2, check_pow<double> >(v, 1, 0, false);
    rc&= check_func_2<double, 4, check_pow<double> >(v, 1, 0, false);
    rc&= check_func_2<double, 8, check_pow<double> >(v, 1, 0, false);

#if 0
    func_domain<double> d=std::make_pair(-0.0001,
                                         std::numeric_limits< double >::max());
    rc &= of_fp_func_up_to<
        double, 8, check_log<double> >::v(d, cmp_ulp<double>(1));
#endif
    return (rc == true) ? 0 : 1;
}
