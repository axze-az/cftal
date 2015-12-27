#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    std::string dn=cftal::test::dirname(argv[0]);
    std::cout << dn << std::endl;
    const std::string data_file="data/exp-test.txt";
    std::cout << cftal::test::append_filename(dn, data_file)
              << std::endl;
    std::cout << cftal::test::filename_from_argv(argv[0], data_file)
              << std::endl;

    std::string test_data_dir = cftal::test::dirname(argv[0]);
    if (argc > 1)
        test_data_dir = argv[1];
    const std::string test_data_file=
        cftal::test::append_filename(test_data_dir, "data/exp.testdata");
    std::vector<cftal::test::func_arg_result<double> > v=
        cftal::test::read_double_file(test_data_file, false);

    std::cout << v.size() << std::endl;
    std::cout << std::hexfloat << std::setprecision(20);
    for (const auto& vi : v) {
        std::cout << std::setw(24) << vi.arg0()
                  << ' '
                  << std::setw(24) << vi.res()
                  << std::endl;
    }

    return 0;
}
