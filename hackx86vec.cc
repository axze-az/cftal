#include <cftal/d_int.h>
#include <cftal/mul_div.h>
#include <x86vec.h>
#include <x86vec_test.h>
#include <cstdint>
#include <iostream>
#include <iomanip>


void test_div()
{
	using namespace x86vec;
	using test::pr_v2u64;

	v2u64::element_type vi(9223372036854775808UL);
	v2u64 u(18441799355538036301UL, 3155565450790631795UL);
	v2u64 v(vi);
	divisor<v2u64, uint64_t> vd(vi);
	
	v2u64 q_div(u/v), r_div(u % v);
	v2u64 q_cdiv(u/vd), r_cdiv(u % vd); 

	v2u64 q_cmp_div(q_cdiv == q_div);
	v2u64 r_cmp_div(r_div == r_cdiv);

	if (!all_signs(q_cmp_div) || !all_signs(r_cmp_div)) {
		std::cout << "div " << std::endl
			  << pr_v2u64(u()) << " / "
			  << vi << std::endl
			  << "Q_DIV:  "
			  << pr_v2u64(q_div()) << std::endl
			  << "R_DIV:  "
			  << pr_v2u64(r_div()) << std::endl
			  << "Q_CDIV: "
			  << pr_v2u64(q_cdiv()) << std::endl
			  << "R_CDIV: "
			  << pr_v2u64(r_cdiv()) << std::endl;
	}
}

int main(int argc, char** argv)
{
	test_div();
        return 0;
}
