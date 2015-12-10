#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXf32" << std::endl;
    rc=cftal::test::of_ops_up_to<float, 16>::v();
    if (rc==false)
        std::cerr << "float test failed" << std::endl;
    return rc==true ? 0 : 1;
}

