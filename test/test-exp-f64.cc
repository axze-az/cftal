#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
#if 0
    std::string dn=cftal::test::dirname(argv[0]);
    std::cout << dn << std::endl;
    const std::string data_file="data/exp-test.txt";
    std::cout << cftal::test::append_filename(dn, data_file)
              << std::endl;
    std::cout << cftal::test::filename_from_argv(argv[0], data_file)
              << std::endl;
#endif
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

    std::cout << std::setprecision(18);
    std::cerr << std::setprecision(18);
    std::cerr << std::hexfloat;
    bool rc= check_func_1<double, 2, check_exp<double> >(v, 1);
    rc &= check_func_1<double, 4, check_exp<double> >(v, 1);
    rc &= check_func_1<double, 8, check_exp<double> >(v, 1);
#if 0
    std::cout << v.size() << std::endl;
    std::cout << std::hexfloat << std::setprecision(20);
    for (const auto& vi : v) {
        std::cout << std::setw(24) << vi.arg0()
                  << ' '
                  << std::setw(24) << vi.res()
                  << std::endl;
    }
#endif
    return (rc == true) ? 0 : 1;
}
