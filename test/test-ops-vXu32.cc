#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXu32" << std::endl;
    rc=cftal::test::of_ops_up_to<uint32_t, 16>::v();
    if (rc==false)
        std::cerr << "uint32_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

