#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXu16" << std::endl;
    rc=cftal::test::of_ops_up_to<uint16_t, 32>::v();
    if (rc==false)
        std::cerr << "uint16_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

