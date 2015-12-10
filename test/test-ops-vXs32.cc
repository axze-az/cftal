#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXs32" << std::endl;
    rc=cftal::test::of_ops_up_to<int32_t, 16>::v();
    if (rc==false)
        std::cerr << "int32_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

