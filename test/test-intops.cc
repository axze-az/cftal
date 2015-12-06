#include <cftal/test/intops.h>

bool all_tests()
{
    bool r(true);
    r &= cftal::test::check_xxx_of();
    r &= cftal::test::check_popcnt();
    r &= cftal::test::check_bitrev();
    return r;
}

int main(int argc, char** argv)
{
    return all_tests()==true ? 0 : 3;
}
