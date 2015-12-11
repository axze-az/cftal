#include "cftal/test/rcp_div.h"

int main()
{
    bool rc= cftal::test::rcp_div_u32();
    return rc == true ? 0 : 1;
}
