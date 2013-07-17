#include <x86vec.h>
#include <x86vec_test.h>

bool all_tests_00()
{
	bool r(true);
	r &= x86vec::test::check_select_v2f64();
	r &= x86vec::test::check_perm1_v2f64();
	r &= x86vec::test::check_perm2_v2f64();

	r &= x86vec::test::check_select_v4f32();
	r &= x86vec::test::check_perm1_v4f32();
	r &= x86vec::test::check_perm2_v4f32();

	r &= x86vec::test::check_select_v4u32();
	r &= x86vec::test::check_perm1_v4u32();
	r &= x86vec::test::check_perm2_v4u32();

	r &= x86vec::test::check_select_v2u64();
	r &= x86vec::test::check_perm1_v2u64();
	r &= x86vec::test::check_perm2_v2u64();

	r &= x86vec::test::check_select_v8u16();
	r &= x86vec::test::check_perm1_v8u16();
	r &= x86vec::test::check_perm2_v8u16();

	return r;
}

int main(int argc, char** argv)
{
	return all_tests_00() == true ? 0 : 3;
}
