#include "cftal/test/dint8.h"

int main()
{
    std::cout << "duint<uint8_t> unsigned check" << std::endl;
    cftal::test::check_duint_ops<uint16_t, cftal::duint<uint8_t> >();
    return 0;
}
