#include <cftal/mul_div.h>
#include <iostream>
#include <iomanip>

namespace cftal {

	namespace impl {

		class udiv_rcp_div_2by1_64 {
		public:
			static
			std::pair<uint64_t, uint64_t>
			d(uint64_t u0, uint64_t u1, uint64_t v, uint64_t* r);

			// we use only the high part of the table
			enum { TABLE_SIZE = 1<<9 };
		private:
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
}

void
cftal::impl::print_rcp_64_table(std::ostream& s)
{
	const unsigned N = udiv_rcp_div_2by1_64::TABLE_SIZE;
	s << "const cftal::uint16_t "
	  << "cftal::impl::udiv_rcp_div_2by1_64::_tbl[TABLE_SIZE]={\n";
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

cftal::uint64_t
cftal::impl::udiv_rcp_div_2by1_64::reciprocal_word(std::uint64_t d)
{
#if 0
	uint64_t d0 = d & 1;
	uint64_t d9 = (d>>55);
	uint64_t d40= (d>>24)+1;
	uint64_t d63= (d>>1);
	uint64_t v0 = recp_tbl_64[d9 & 255];
	uint64_t v1 = (1L<<11)*v0 - ((v0*v0*d40)>>40) -1;
	uint64_t v2 = (1L<<13)*v1 + ((v1*((1L<<60)*v1*d40))>>47);
	typedef duint<uint64_t> du_t;
	du_t e = (du_t(0, 0x100000000)) - du_t(v2)*d63;
	e+= d0 ? (v2>>1) : 0;
	uint64_t t0= (v2*e).uh()>>1;
	uint64_t v3 = (v2<<31) + t0;
	du_t t1 =(v3 + du_t(1,1))*d;
	uint64_t v4 = v3 - t1.uh();
	return v4;
#endif
	return -1;
}

cftal::uint64_t
cftal::impl::udiv_rcp_div_2by1_64::
sd(uint64_t u0, uint64_t u1, uint64_t d, uint64_t inv, uint64_t* rem)
{
	return 0;
}

std::pair<cftal::uint64_t, cftal::uint64_t>
cftal::impl::udiv_rcp_div_2by1_64::
d(uint64_t u0, uint64_t u1, uint64_t v, uint64_t* rem)
{
	unsigned l_z=lzcnt(v);
	// normalized values of v, u0, u1
	uint64_t nv, s1, s0;
	if (l_z == 0) {
		nv = v;
		s1 = u1;
		s0 = u0;
	} else {
		uint64_t u0r(u0 >> (64-l_z));
		nv = v << l_z;
		s1 = (u1 << l_z) | u0r;
		s0 = u0<<l_z;
	}
	uint64_t inv(reciprocal_word(nv));
	uint64_t q1(0);
	uint64_t q0(0);
	if (u1 >= v) {
		uint64_t s2(l_z ? u1 >> (64-l_z) : 0);
		uint64_t r;
		q1= sd(s1, s2, nv, inv, &r);
		// j== 0
		q0= sd(s0, r, nv, inv, rem);
	} else {
		q0= sd(s0, s1, nv, inv, rem);
	}
	return std::make_pair(q0, q1);
}


int main(int argc, char* argv[])
{
	if (argc > 1) {
		std::string argv1(argv[1]);
		if (argv1 == "--gen-tbl") {
			cftal::impl::print_rcp_64_table(std::cout);
		}
	}
	return 0;
}
