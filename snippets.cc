#include <x86vec.h>
#include <iostream>
#include <iomanip>

typedef unsigned __int128 u128_t;

u128_t neg(u128_t r)
{
	return -r;
}

cftal::uint128_t neg(cftal::uint128_t r)
{
	return -r;
}

bool lt(u128_t a, u128_t b)
{
	return a < b;
}

bool lt(cftal::uint128_t a, cftal::uint128_t b)
{
	return a < b;
}


cftal::uint128_t sub(cftal::uint128_t a, cftal::uint128_t b)
{
	return a *b;
}

cftal::uint128_t sub(cftal::uint128_t a, std::uint64_t b)
{
	return a *b;
}

cftal::uint128_t sub(std::uint64_t a, cftal::uint128_t b)
{
	return a - b;
}

x86vec::v4u32 mul(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return a*b;
}

x86vec::v4s32 mul(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return a*b;
}

x86vec::v4u32 mulhi(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return mulh(a, b);
}

x86vec::v4s32 mulhi(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return mulh(a, b);
}

x86vec::v2u64 mul(x86vec::v2u64 a, x86vec::v2u64 b)
{
        return a*b;
}

x86vec::v2s64 mul(x86vec::v2s64 a, x86vec::v2s64 b)
{
        return a*b;
}

x86vec::v2u64 mulhi(x86vec::v2u64 a, x86vec::v2u64 b)
{
        return mulh(a,b);
}

x86vec::v2s64 mulhi(x86vec::v2s64 a, x86vec::v2s64 b)
{
        return mulh(a, b);
}

std::pair<x86vec::v2u64, x86vec::v2u64>
mulwide(x86vec::v2u64 a, x86vec::v2u64 b)
{
	return wide_mul(a, b);
}

std::pair<x86vec::v2s64, x86vec::v2s64>
mulwide(x86vec::v2s64 a, x86vec::v2s64 b)
{
	return wide_mul(a, b);
}

const unsigned d32 = (1<<24) - (1<<14) + (1<<9);

void generate_reciprocal_word_table_64(std::ostream& s)
{
	const unsigned N = 1<<9;
	s << "const cftal::uint16_t cftal::impl::recp_tbl_64["
	  << N/2 << "]={\n";
	const std::uint32_t d64 = (1<<19) - 3*(1<<8);
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
	s << "};";
}

namespace cftal {
	namespace impl {
		const unsigned INV64_TBL_CNT=256;
		extern const uint16_t recp_tbl_64[INV64_TBL_CNT]; 
		uint64_t reciprocal_word(uint64_t d);
	}
}

#if 0
/* inline */
std::uint64_t cftal::impl::reciprocal_word(uint64_t d)
{
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
}
#endif
