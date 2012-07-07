#include <x86vec.h>
#include <x86vec_test.h>

bool all_tests_00()
{
	bool r(true);
	r &= x86vec::test::check_select_f64();
	r &= x86vec::test::check_perm1_f64();
	r &= x86vec::test::check_perm2_f64();

	r &= x86vec::test::check_select_f32();
	r &= x86vec::test::check_perm1_f32();
	r &= x86vec::test::check_perm2_f32();

	r &= x86vec::test::check_select_u32();
	r &= x86vec::test::check_perm1_u32();
	r &= x86vec::test::check_perm2_u32();

	r &= x86vec::test::check_select_u64();
	r &= x86vec::test::check_perm1_u64();
	r &= x86vec::test::check_perm2_u64();

	r &= x86vec::test::check_select_u16();
	r &= x86vec::test::check_perm1_u16();
	r &= x86vec::test::check_perm2_u16();

	return r;
}

int main(int argc, char** argv)
{
	return all_tests_00() == true ? 0 : 3;
}
