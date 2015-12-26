#include <cftal/config.h>
#include <experimental/filesystem>
#include <string>
#include <iostream>

namespace cftal {
    namespace test {
        std::string
        dirname(const std::string& fn);
        std::string
        append_filename(const std::string& dn, const std::string& fn);
        std::string
        filename_from_argv(const char* argv0, const std::string& fn);
    }
}

std::string
cftal::test::dirname(const std::string& fn)
{
    using namespace std::experimental::filesystem;
    path pfn(fn);
    path dn(pfn.remove_filename());
    return dn;
}

std::string
cftal::test::append_filename(const std::string& dn, const std::string& fn)
{
    using namespace std::experimental::filesystem;
    path pdn(dn);
    path pfn(fn);
    path pnfn = pdn / pfn;
    return pnfn;
}

std::string
cftal::test::filename_from_argv(const char* argv, const std::string& fn)
{
    using namespace std::experimental::filesystem;
    path pargv(argv);
    path pdn(pargv.remove_filename());
    path pfn(fn);
    path pnfn= pdn / fn;
    return pnfn;
}


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
