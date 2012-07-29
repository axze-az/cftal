#include <cftal/mul_div.h>
#include <cftal/x86vec_test.h>
#include <iostream>
#include <iomanip>

namespace cftal {

	namespace test {
		bool udiv_32_one(std::uint32_t d, uint64_t& ops,
				 uint64_t* timings);
		bool udiv_32();
	}
}

bool
cftal::test::udiv_32_one(uint32_t v, uint64_t& ops, uint64_t* timings)
{
	x86vec::test::cmwc_rng<uint32_t> rng(ops);
	uint64_t t0, t1, t2;
	const int N= 20000;
	for (int i=0; i<N; ++i) {
		uint32_t ul= rng.next();
		uint32_t uh= rng.next();
		
		t0 = rdtsc();
		impl::udiv_result<uint32_t> qr_ref(
			impl::udiv_2by1_div_32::d(ul, uh, v));
		t1 = rdtsc();
		impl::udiv_result<uint32_t> qr(
			impl::udiv_2by1_rcp_32::d(ul, uh, v));
		t2 = rdtsc();

		timings[0] += t1-t0;
		timings[1] += t2-t1;

		uint32_t r_ref= qr_ref._r;
		uint32_t q_ref_l=qr_ref._q0;
		uint32_t q_ref_h=qr_ref._q1;


		uint32_t r=qr._r;
		uint32_t q_l = qr._q0;
		uint32_t q_h = qr._q1;

		if (q_l != q_ref_l || q_h != q_ref_h || r != r_ref ) {
			std::cout << '\n'
				  << std::hex 
				  << "0x"
				  << std::setfill('0')
				  << uh << ':' 
				  << std::setw(8)
				  << ul 
				  << " / 0x"
				  << v 
				  << " = \n"
				  << "0x"
				  << q_h << ':' 
				  << std::setw(8)
				  << q_l
				  << " rem: "
				  << "0x"
				  << r
				  << " != (ref:)\n"
				  << "0x"
				  << q_ref_h << ':' 
				  << std::setw(8)
				  << q_ref_l
				  << " rem: "
				  << "0x"
				  << r_ref
				  << std::dec
				  << std::setfill(' ')
				  << "\n";
			
			return false;
		}
	}
	ops += N;
	return true;
}

bool
cftal::test::udiv_32()
{
#if 0
	std::pair<uint32_t, uint32_t> t(
		impl::udiv_2by1_rcp_32::d(
			0x15dcc1ff2bcdf918UL,
			0xffdfd58d2bbc61abUL,
			0xfe00ec8213f1d401UL, nullptr));
	std::cout << std::hex
		  << t.first
		  << ' ' 
		  << t.second
		  << std::dec 
		  << std::endl;
	//return udiv_32_one(1);
	return true;
#else
	bool rc(true);
	uint64_t ops(0), timings[2];
	timings[0] = timings[1] =0;
	rc &= udiv_32_one(1, ops, timings);
	if (!rc)
		return rc;
	rc &= udiv_32_one(-1L, ops, timings);
	if (!rc)
		return rc;
	x86vec::test::cmwc_rng<uint32_t> rng(42*42);
	const int N = 0x10000;
	divisor<double> dd(N);
	for (int i=2; (i< N) && (rc ==true) ; ++i) {
		uint32_t v= rng.next();
		std::cout << std::fixed << std::setprecision(4);
		if ((i & 0x3FF)==0x3FF) {
			std::cout << "udiv_rcp_32: " 
				  << std::setw(7)
				  << (double(i)*100)/ dd
				  << " %\r" << std::flush;
		}
		rc &= udiv_32_one(v, ops, timings);
		if (!rc)

			return rc;
	}
	std::cout << "udiv_rcp_32 passed without errors"
		  << std::endl;
	std::cout << "timing information\n"
		  << "div:     " << double(timings[0])/ops 
		  << '\n'
		  << "rcp_div: " << double(timings[1])/ops 
		  << std::endl;
	return true;
#endif
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		std::string argv1(argv[1]);
		if (argv1 == "--gen-tbl") {
			cftal::impl::print_rcp_32_table(std::cout);
			return 0;
		}
	}
	cftal::test::udiv_32();
	return 0;
}
