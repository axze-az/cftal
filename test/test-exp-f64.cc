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

    const std::string test_data_file=
        cftal::test::append_filename(dn, "data/exp.testdata");

    std::vector<cftal::test::func_arg_result<double> > v=
        cftal::test::read_double_file(test_data_file, false);

    std::cout << std::hexfloat;
    for (const auto& vi : v) {
        std::cout << vi.arg0() << ' ' << vi.res() << std::endl;
    }

    return 0;
}
