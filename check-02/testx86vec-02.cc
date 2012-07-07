#include <x86vec.h>
#include <x86vec_test.h>
#include <bitops.h>

bool all_tests_02()
{
	bool r(true);
	r &= bitops::test::div_u16();
	r &= bitops::test::div_s16();
	r &= bitops::test::div_u32();
	r &= bitops::test::div_s32();
	return r;
}

int main(int argc, char** argv)
{
	return all_tests_02()==true ? 0 : 3;
}
