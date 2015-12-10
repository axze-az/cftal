#include "cftal/test/of_ops.h"

int main()
{
    bool rc=true;
    std::cout << "testing vXu64" << std::endl;
    rc=cftal::test::of_ops_up_to<uint64_t, 8>::v();
    if (rc==false)
        std::cerr << "unit64_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

