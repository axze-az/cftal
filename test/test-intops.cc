#include <cftal/test/intops.h>


bool all_tests_01()
{
        bool r(true);
        r &= cftal::test::check_signs();
        r &= cftal::test::check_popcnt();
        r &= cftal::test::check_div();
        return r;
}

int main(int argc, char** argv)
{
        return all_tests_01()==true ? 0 : 3;
}
