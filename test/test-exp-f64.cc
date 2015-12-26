#include "cftal/test/of_math_funcs.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::string dn=cftal::test::dirname(argv[0]);
    std::cout << dn << std::endl;
    const std::string data_file="data/exp-test.txt";
    std::cout << cftal::test::append_filename(dn, data_file)
              << std::endl;
    std::cout << cftal::test::filename_from_argv(argv[0], data_file)
              << std::endl;
    return 0;
}
