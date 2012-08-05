#include "divisor.h"

extern bool check_d_int8();
extern bool check_rcp_div_64();
extern bool check_rcp_div_32();

bool all_tests_02()
{
	bool r(true);
	r &= check_d_int8();
	r &= cftal::test::div_u16();
	r &= cftal::test::div_s16();
	r &= cftal::test::div_u32();
	r &= cftal::test::div_s32();
	r &= check_rcp_div_64();
	r &= check_rcp_div_32();
	return r;
}

int main(int argc, char** argv)
{
	return all_tests_02()==true ? 0 : 3;
}
