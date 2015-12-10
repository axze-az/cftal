#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    bool rt;
    std::cout << "testing vXf64" << std::endl;
    rt=cftal::test::of_ops_up_to<double, 8>::v();
    if (rt==false)
        std::cerr << "double test failed" << std::endl;
    rc &= rt;

    std::cout << "testing vXf32" << std::endl;
    rt=cftal::test::of_ops_up_to<float, 16>::v();
    if (rt==false)
        std::cerr<< "float test failed" << std::endl;
    rc &= rt;

    std::cout << "testing vXu64" << std::endl;
    rt=cftal::test::of_ops_up_to<uint64_t, 4>::v();
    if (rt==false)
        std::cerr<< "uint64_t test failed" << std::endl;
    rc &= rt;

    std::cout << "testing vXs64" << std::endl;
    rt=cftal::test::of_ops_up_to<int64_t, 4>::v();
    if (rt==false)
        std::cerr<< "int64_t test failed" << std::endl;
    rc &= rt;
    return rc==true ? 0 : 1;
}

