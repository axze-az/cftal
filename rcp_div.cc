#include <cftal/mul_div.h>
#include <cftal/x86vec_test.h>
#include <iostream>
#include <iomanip>

namespace cftal {

	namespace impl {

		class udiv_rcp_2by1_64 {
		public:
			static
			std::pair<uint64_t, uint64_t>
			d(uint64_t u0, uint64_t u1, uint64_t v, uint64_t* r);

			// we use only the high part of the table
			enum { TABLE_SIZE = 1<<9 };
			// private:
			static
			std::uint64_t reciprocal_word(std::uint64_t d);
			// 2 by division without overflow
			static
			std::uint64_t
			sd(uint64_t u0, uint64_t u1, uint64_t v,
			   uint64_t inv, uint64_t* r);
			static const uint16_t _tbl[TABLE_SIZE];
		};

		void print_rcp_64_table(std::ostream& s);
	}

	namespace test {
		bool udiv_64_one(std::uint64_t d);
		bool udiv_64();
	}
}

void
cftal::impl::print_rcp_64_table(std::ostream& s)
{
	const unsigned N = udiv_rcp_2by1_64::TABLE_SIZE;
	s << "const cftal::uint16_t\n"
	  << "cftal::impl::udiv_rcp_2by1_64::_tbl[TABLE_SIZE]={\n";
	const std::uint32_t d64 = (1<<19) - 3*(1<<8);
	// empty lower part of table
	s << "\t// empty lower part\n";
	for (std::uint32_t i=0; i<N/2; ++i) {
		s << "\t" << "0x000,";
		if (((i+1) & 7)==0)
			s << '\n';
	}
	s << "\t// required upper part\n";
	for (std::uint32_t i=N/2; i<N; ++i) {
		unsigned q(i==0 ? 0 : d64/i);
		s << "\t"
		  << "0x"
		  <<std::hex << std::setfill('0') << std::setw(3)
		  << q
		  << std::setfill(' ') << std::dec;
		if (i != N-1)
			s << ',';
		if (((i+1) & 7)==0)
			s << '\n';
		else
			s << ' ';
	}
	s << "};\n";
}

const cftal::uint16_t
cftal::impl::udiv_rcp_2by1_64::_tbl[TABLE_SIZE]={
	// empty lower part
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,	0x000,
	// required upper part
	0x7fd, 	0x7f5, 	0x7ed, 	0x7e5, 	0x7dd, 	0x7d5, 	0x7ce, 	0x7c6,
	0x7bf, 	0x7b7, 	0x7b0, 	0x7a8, 	0x7a1, 	0x79a, 	0x792, 	0x78b,
	0x784, 	0x77d, 	0x776, 	0x76f, 	0x768, 	0x761, 	0x75b, 	0x754,
	0x74d, 	0x747, 	0x740, 	0x739, 	0x733, 	0x72c, 	0x726, 	0x720,
	0x719, 	0x713, 	0x70d, 	0x707, 	0x700, 	0x6fa, 	0x6f4, 	0x6ee,
	0x6e8, 	0x6e2, 	0x6dc, 	0x6d6, 	0x6d1, 	0x6cb, 	0x6c5, 	0x6bf,
	0x6ba, 	0x6b4, 	0x6ae, 	0x6a9, 	0x6a3, 	0x69e, 	0x698, 	0x693,
	0x68d, 	0x688, 	0x683, 	0x67d, 	0x678, 	0x673, 	0x66e, 	0x669,
	0x664, 	0x65e, 	0x659, 	0x654, 	0x64f, 	0x64a, 	0x645, 	0x640,
	0x63c, 	0x637, 	0x632, 	0x62d, 	0x628, 	0x624, 	0x61f, 	0x61a,
	0x616, 	0x611, 	0x60c, 	0x608, 	0x603, 	0x5ff, 	0x5fa, 	0x5f6,
	0x5f1, 	0x5ed, 	0x5e9, 	0x5e4, 	0x5e0, 	0x5dc, 	0x5d7, 	0x5d3,
	0x5cf, 	0x5cb, 	0x5c6, 	0x5c2, 	0x5be, 	0x5ba, 	0x5b6, 	0x5b2,
	0x5ae, 	0x5aa, 	0x5a6, 	0x5a2, 	0x59e, 	0x59a, 	0x596, 	0x592,
	0x58e, 	0x58a, 	0x586, 	0x583, 	0x57f, 	0x57b, 	0x577, 	0x574,
	0x570, 	0x56c, 	0x568, 	0x565, 	0x561, 	0x55e, 	0x55a, 	0x556,
	0x553, 	0x54f, 	0x54c, 	0x548, 	0x545, 	0x541, 	0x53e, 	0x53a,
	0x537, 	0x534, 	0x530, 	0x52d, 	0x52a, 	0x526, 	0x523, 	0x520,
	0x51c, 	0x519, 	0x516, 	0x513, 	0x50f, 	0x50c, 	0x509, 	0x506,
	0x503, 	0x500, 	0x4fc, 	0x4f9, 	0x4f6, 	0x4f3, 	0x4f0, 	0x4ed,
	0x4ea, 	0x4e7, 	0x4e4, 	0x4e1, 	0x4de, 	0x4db, 	0x4d8, 	0x4d5,
	0x4d2, 	0x4cf, 	0x4cc, 	0x4ca, 	0x4c7, 	0x4c4, 	0x4c1, 	0x4be,
	0x4bb, 	0x4b9, 	0x4b6, 	0x4b3, 	0x4b0, 	0x4ad, 	0x4ab, 	0x4a8,
	0x4a5, 	0x4a3, 	0x4a0, 	0x49d, 	0x49b, 	0x498, 	0x495, 	0x493,
	0x490, 	0x48d, 	0x48b, 	0x488, 	0x486, 	0x483, 	0x481, 	0x47e,
	0x47c, 	0x479, 	0x477, 	0x474, 	0x472, 	0x46f, 	0x46d, 	0x46a,
	0x468, 	0x465, 	0x463, 	0x461, 	0x45e, 	0x45c, 	0x459, 	0x457,
	0x455, 	0x452, 	0x450, 	0x44e, 	0x44b, 	0x449, 	0x447, 	0x444,
	0x442, 	0x440, 	0x43e, 	0x43b, 	0x439, 	0x437, 	0x435, 	0x432,
	0x430, 	0x42e, 	0x42c, 	0x42a, 	0x428, 	0x425, 	0x423, 	0x421,
	0x41f, 	0x41d, 	0x41b, 	0x419, 	0x417, 	0x414, 	0x412, 	0x410,
	0x40e, 	0x40c, 	0x40a, 	0x408, 	0x406, 	0x404, 	0x402, 	0x400
};

cftal::uint64_t
cftal::impl::udiv_rcp_2by1_64::reciprocal_word(uint64_t d)
{
#if 1
	return udiv_2by1<uint64_t>::d(uint64_t(-1L),
				      uint64_t(-1L)-d,
				      d, nullptr).
		first;
#else
	uint64_t inv, t0, t1;
	const uint16_t* tblptr= _tbl;
	__asm__ __volatile__(
		"mov %[rdi], %[rax] \n\t"
		"shr $55, %[rax] \n\t"
		"movzwl (%[rcx], %[rax], 2), %k[rcx] \n\t"
		// v1 = (v0 << 11) - (v0*v0*d40 >> 40) - 1
		"mov %[rdi], %[rsi] \n\t"
		"mov %k[rcx], %k[rax] \n\t"
		"imul %k[rcx], %k[rcx] \n\t"
		"shr $24, %[rsi] \n\t"
		"inc %[rsi] \n\t" // %[rsi] = d40
		"imul %[rsi], %[rcx] \n\t"
		"shr $40, %[rcx] \n\t"
		"sal $11, %k[rax] \n\t"
		"dec %k[rax] \n\t"
		"sub %k[rcx], %k[rax] \n\t" // %[rax] = v1
		
		// v2 = (v1 << 13) + (v1 * (2^60 - v1*d40) >> 47
		"movabs $0x1000000000000000, %[rcx] \n\t"
		"imul %[rax], %[rsi] \n\t"
		"sub %[rsi], %[rcx] \n\t"
		"imul %[rax], %[rcx] \n\t"
		"sal $13, %[rax] \n\t"
		"shr $47, %[rcx] \n\t"
		"add %[rax], %[rcx]  \n\t" // %[rcx] = v2
		
		// v3 = (v2 << 31) + 
		// (v2 * (2^96 - v2 * d63 + (v2>>1) & mask) >> 65
		"mov %[rdi], %[rsi] \n\t"
		"shr $1, %[rsi] \n\t" // d/2
		"sbb %[rax], %[rax] \n\t" // -d0 = -(d mod 2)
		"sub %[rax], %[rsi] \n\t" // d63 = ceil(d/2)
		"imul %[rcx], %[rsi] \n\t" // v2 * d63
		"and %[rcx], %[rax] \n\t" // v2 * d0
		"shr $1, %[rax] \n\t" // (v2>>1) * d0
		"sub %[rsi], %[rax] \n\t" // (v2>>1) * d0 - v2 * d63
		"mul %[rcx] \n\t"
		"sal $31, %[rcx] \n\t"
		"shr $1, %[rdx] \n\t"
		"add %[rdx], %[rcx] \n\t" // %[rcx] = v3
		
		"mov %[rdi], %[rax] \n\t"
		"mul %[rcx] \n\t"
		"add %[rdi], %[rax] \n\t"
		"mov %[rcx], %[rax] \n\t"
		"adc %[rdi], %[rdx] \n\t"
		"sub %[rdx], %[rax] \n\t"
		: [rax] "=&r" (inv), [rdx] "=&r" (t0), 
		  [rsi] "=&r" (t1), [rcx] "+&r" (tblptr)
		: [rdi] "rm" (d)
		: "cc");
	return inv;
#endif
}

cftal::uint64_t
cftal::impl::udiv_rcp_2by1_64::
sd(uint64_t u0, uint64_t u1, uint64_t d, uint64_t inv, uint64_t* rem)
{
	std::pair<uint64_t, uint64_t> p0(wide_mul(u1, inv));
	uint64_t q0= p0.first + u0;
	uint64_t q1= p0.second + u1;
	if (q0 < u0)
		++q1;
	++q1;
	uint64_t r = u0 - q1*d;
	if (r > q0) {
		--q1;
		r += d;
	}
	if (r >= d) {
		++q1;
		r -= d;
	}
	if (rem)
		*rem = r;
	return q1;
}

std::pair<cftal::uint64_t, cftal::uint64_t>
cftal::impl::udiv_rcp_2by1_64::
d(uint64_t u0, uint64_t u1, uint64_t v, uint64_t* rem)
{
	if (v==0)
		return std::make_pair(u0, u1/v);
#if 0
	if (v==1) {
		if (rem)
			*rem = 0;
		return std::make_pair(u0, u1);
	}
#endif
	unsigned l_z=lzcnt(v);
	// normalized values of v, u0, u1
	uint64_t nv, s2, s1, s0;
	unsigned neg_shift = 64 - l_z;
	if (l_z == 0) {
		nv = v;
		s1 = u1;
		s0 = u0;
		s2 = 0;
	} else {
		uint64_t u01(u0 >> neg_shift);
		nv = v  << l_z;
		s0 = u0 << l_z;
		s1 = u1 << l_z;
		s1 |= u01;
		s2 = u1 >> neg_shift;
	}
	uint64_t inv(reciprocal_word(nv));
	uint64_t q1(0), q0(0), r(s1);
	if (s2 != 0 || s1>=nv) {
		q1=sd(s1, s2, nv, inv, &r);
	}
	q0=sd(s0, r, nv, inv, &r);
	if (rem)
		*rem = l_z ? r >> l_z : r;
	return std::make_pair(q0, q1);
}

bool
cftal::test::udiv_64_one(std::uint64_t v)
{
	x86vec::test::cmwc_rng<uint64_t> rng(42);
	for (int i=0; i<20000; ++i) {
		uint64_t ul= rng.next();
		uint64_t uh= rng.next();
		
		typedef unsigned __int128 u128_t;

		uint64_t r_ref=0;
		std::pair<uint64_t, uint64_t> pq_ref(
			impl::udiv_2by1<uint64_t>::d(ul, uh, v, &r_ref));
		
		uint64_t q_ref_l=pq_ref.first;
		uint64_t q_ref_h=pq_ref.second;

		uint64_t r=0;
		std::pair<uint64_t, uint64_t> pq(
			impl::udiv_rcp_2by1_64::d(ul, uh, v, &r));

		uint64_t q_l = pq.first;
		uint64_t q_h = pq.second;

		if (q_l != q_ref_l || q_h != q_ref_h || r != r_ref ) {
			std::cout << '\n'
				  << std::hex 
				  << "0x"
				  << std::setfill('0')
				  << uh << ':' 
				  << std::setw(16)
				  << ul 
				  << " / 0x"
				  << v 
				  << " = \n"
				  << "0x"
				  << q_h << ':' 
				  << std::setw(16)
				  << q_l
				  << " rem: "
				  << "0x"
				  << r
				  << " != (ref:)\n"
				  << "0x"
				  << q_ref_h << ':' 
				  << std::setw(16)
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
	return true;
}

bool
cftal::test::udiv_64()
{
#if 0
	std::pair<uint64_t, uint64_t> t(
		impl::udiv_rcp_2by1_64::d(
			0x15dcc1ff2bcdf918UL,
			0xffdfd58d2bbc61abUL,
			0xfe00ec8213f1d401UL, nullptr));
	std::cout << std::hex
		  << t.first
		  << ' ' 
		  << t.second
		  << std::dec 
		  << std::endl;
	//return udiv_64_one(1);
	return true;
#else
	bool rc(true);
	rc &= udiv_64_one(1);
	if (!rc)
		return rc;
	rc &= udiv_64_one(-1L);
	if (!rc)
		return rc;
	x86vec::test::cmwc_rng<uint64_t> rng(42*42);
	const int N = 0x100000;
	divisor<double> dd(N);
	for (int i=2; (i< N) && (rc ==true) ; ++i) {
		uint64_t v= rng.next();
		if ((i & 0x1FF)==0x1FF) {
			std::cout << "udiv_rcp_64: " 
				  << std::setw(8)
				  << (double(i)*100)/ dd
				  << '\r' << std::flush;
		}
		rc &= udiv_64_one(v);
		if (!rc)

			return rc;
	}
	std::cout << "udiv_rcp_64 passed without errors"
		  << std::endl;
	return true;
#endif
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		std::string argv1(argv[1]);
		if (argv1 == "--gen-tbl") {
			cftal::impl::print_rcp_64_table(std::cout);
		}
	}
	cftal::test::udiv_64();
	return 0;
}
