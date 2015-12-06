#include <cftal/test/intops.h>

int main(int argc, char** argv)
{
    bool rc= cftal::test::check_div_s32();
    return rc==true ? 0 : 1;
}
