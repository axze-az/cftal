#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXf64" << std::endl;
    rc=cftal::test::of_ops_up_to<double, 8>::v();
    if (rc==false)
        std::cerr << "double test failed" << std::endl;
    return rc==true ? 0 : 1;
}

