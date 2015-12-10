#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXs64" << std::endl;
    rc=cftal::test::of_ops_up_to<int64_t, 8>::v();
    if (rc==false)
        std::cerr << "int64_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

