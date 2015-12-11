#include "cftal/test/dint8.h"

int main()
{
    std::cout << "dint<int8_t> signed check" << std::endl;
    cftal::test::check_duint_ops<int16_t, cftal::dint<int8_t> >();
    return 0;
}
