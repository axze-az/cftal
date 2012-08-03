#include "mul_div.h"
#include <iostream>
#include <iomanip>

inline
cftal::uint32_t
cftal::impl::udiv_2by1_rcp_32::reciprocal_word_i(uint32_t d)
{
#define USE_DIV 0
#define USE_CPP 1
#define USE_ASM 2
#if defined (__i386__)
#define ALG USE_ASM
#else
#define ALG USE_CPP
#endif

#if USE_DIV==ALG
	return udiv_2by1_div_32::d(uint32_t(-1L), uint32_t(-1L)-d, d)._q0;
#endif
#if USE_CPP==ALG
	uint32_t v0 = _tbl[d>>22];
	uint32_t v0_v0 = v0*v0;
	uint32_t d21 = (d>>11) +1;
	uint64_t v0_v0_d21 = uint64_t(v0_v0) * d21;
	uint32_t v1 = (v0<<4) - (v0_v0_d21>>32) -1;
	// e fits into 32 bits.
	uint32_t d0 = d & 1;
	uint32_t nd0 = -d0;
	uint32_t d31 = (d>>1) + d0;
	
	uint32_t d0_v1_half = nd0 & (v1>>1);
	uint32_t v1_d31 = v1*d31;
	// this is e without 2^48
	uint32_t d0_v1_half_minus_v1_d31= d0_v1_half -v1_d31;
	
	uint32_t v1e_h = (uint64_t(d0_v1_half_minus_v1_d31)*v1)>>32;
	uint32_t v2 = (v1<<15) + (v1e_h>>1);

	uint64_t v2d= uint64_t(v2)*d;
	uint64_t dd(d | (uint64_t(d)<<32));
	v2d += dd;
	uint32_t v3 = v2 - uint32_t(v2d>>32);
	return v3;
#endif
#if USE_ASM==ALG 
	uint32_t v0 = _tbl[d>>22];
	uint32_t v0_v0 = v0*v0;
	uint32_t d21 = (d>>11) +1;
	uint32_t v0_v0_d21_l, v0_v0_d21_h;
	__asm__("mull %[d21] \n\t"
		: "=a"(v0_v0_d21_l), "=d"(v0_v0_d21_h)
		: [d21] "rm" (d21), "0"(v0_v0)
		: "cc");
	uint32_t v1 = (v0<<4) - v0_v0_d21_h -1;
	// e fits into 32 bits.
	// calculate d31, nd0
	uint32_t d31, nd0;
	__asm__ ("shr $1, %[d31] \n\t" // CF contains lowest bit
		 "sbb %[d0], %[d0] \n\t" // -1 if CF, 0 if not == -d0
		 "sub %[d0], %[d31] \n\t" // ceil(d/2)
		 : [d31] "=r"(d31), [d0] "=r"(nd0)
		 : "0" (d)
		 : "cc" );
	uint32_t d0_v1_half = nd0 & (v1>>1);
	uint32_t v1_d31 = v1*d31;
	// this is e without 2^48
	uint32_t d0_v1_half_minus_v1_d31= d0_v1_half -v1_d31;
	uint32_t v1e_h, v1e_l;
	__asm__("mull %[v1] \n\t"
		: "=a"(v1e_l), "=d"(v1e_h)
		: [v1] "rm"(v1), "0"(d0_v1_half_minus_v1_d31)
		: "cc");
	uint32_t v2 = (v1<<15) + (v1e_h>>1);
	uint32_t v2_d_h, v2_d_l;
	__asm__("mull %[v2] \n\t"
		: "=a"(v2_d_l), "=d"(v2_d_h)
		: [v2] "rm" (v2), "0"(d)
		: "cc");
	__asm__("add %[d], %[v2_d_l] \n\t"
		"adc %[d], %[v2_d_h] \n\t"
		 : [v2_d_l] "+r" (v2_d_l), [v2_d_h] "+r" (v2_d_h)
		: [d] "rm" (d)
		 : "cc");
	uint32_t v3 = v2 - v2_d_h;
	return v3;
#endif

#undef USE_DIV
#undef USE_CPP
#undef USE_ASM
#undef ALG
}

inline
cftal::uint32_t
cftal::impl::udiv_2by1_rcp_32::
sd_i(uint32_t u0, uint32_t u1, uint32_t d, uint32_t inv, uint32_t& rem)
{
	std::pair<uint32_t, uint32_t> p0(mul_lo_hi(u1, inv));
#if 1
	uint64_t q(p0.first | (uint64_t(p0.second)<<32));
	q+= uint64_t(u0 | (uint64_t(u1+1)<<32));
	uint32_t q0 = q;
	uint32_t q1 = q>>32;
#else
	uint32_t q0= p0.first + u0;
	uint32_t q1= p0.second + u1;
	if (q0 < u0)
		++q1;
	++q1;
#endif
	uint32_t r = u0 - q1*d;
#if 1
	uint32_t corr_q1= (r>q0) ? 1 : 0;
	uint32_t corr_r= (r>q0) ? d : 0;
	q1 -= corr_q1;
	r += corr_r;
#else
	if (r > q0) {
		--q1;
		r += d;
	}
#endif
	if (unlikely(r >= d)) {
		++q1;
		r -= d;
	}
	rem = r;
	return q1;
}

inline
cftal::impl::udiv_result<uint32_t>
cftal::impl::udiv_2by1_rcp_32::
d_i(uint32_t u0, uint32_t u1, uint32_t nv, uint32_t inv, unsigned l_z)
{
	unsigned neg_shift = 32 - l_z;
	uint32_t u2(0);
	if (likely(l_z)!=0) {
		uint64_t s2, s1, s0;
		uint64_t s0_s1((uint64_t(u1)<<32)|u0);
		s0_s1 <<= l_z;
		s0 = s0_s1;
		s1 = s0_s1>>32;
		s2 = u1 >> neg_shift;
		// store normalized values.
		u0 = s0;
		u1 = s1;
		u2 = s2;
	}
	uint32_t q1(0), q0(0), r(u1);
	if (u2 != 0 || u1>=nv) {
		q1=sd_i(u1, u2, nv, inv, r);
	}
	q0=sd_i(u0, r, nv, inv, r);
	if (l_z)
		r >>= l_z;
	return make_udiv_result(q0, q1, r);
}

cftal::uint32_t
cftal::impl::udiv_2by1_rcp_32::reciprocal_word(uint32_t d)
{
	return reciprocal_word_i(d);
}

cftal::impl::udiv_result<uint32_t>
cftal::impl::udiv_2by1_rcp_32::
d(uint32_t u0, uint32_t u1, uint32_t nv, uint32_t inv, unsigned l_z)
{
	return d_i(u0, u1, nv, inv, l_z);
}

cftal::impl::udiv_result<uint32_t>
cftal::impl::udiv_2by1_rcp_32::
d(uint32_t u0, uint32_t u1, uint32_t v)
{
#if 1
	if (v==0) 
		return make_udiv_result(u0, u1/v, u1);
#else
	if (v<2) {
		if (v==1)
			return make_udiv_result(u0, u1, 0);
		return make_udiv_result(u0, u1/v, u1);
	}
#endif
	unsigned l_z=lzcnt(v);
	v <<= l_z;
	uint32_t inv(reciprocal_word_i(v));
	return d_i(u0, u1, v, inv, l_z);
}

const cftal::uint16_t
cftal::impl::udiv_2by1_rcp_32::_tbl[TABLE_SIZE]={
	// empty lower part
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	// required upper part
	0x7fe1, 0x7fa1, 0x7f61, 0x7f22, 0x7ee3, 0x7ea4, 0x7e65, 0x7e27,
	0x7de9, 0x7dab, 0x7d6d, 0x7d30, 0x7cf3, 0x7cb6, 0x7c79, 0x7c3d,
	0x7c00, 0x7bc4, 0x7b89, 0x7b4d, 0x7b12, 0x7ad7, 0x7a9c, 0x7a61,
	0x7a27, 0x79ec, 0x79b2, 0x7979, 0x793f, 0x7906, 0x78cc, 0x7894,
	0x785b, 0x7822, 0x77ea, 0x77b2, 0x777a, 0x7742, 0x770b, 0x76d3,
	0x769c, 0x7665, 0x762f, 0x75f8, 0x75c2, 0x758c, 0x7556, 0x7520,
	0x74ea, 0x74b5, 0x7480, 0x744b, 0x7416, 0x73e2, 0x73ad, 0x7379,
	0x7345, 0x7311, 0x72dd, 0x72aa, 0x7277, 0x7243, 0x7210, 0x71de,
	0x71ab, 0x7179, 0x7146, 0x7114, 0x70e2, 0x70b1, 0x707f, 0x704e,
	0x701c, 0x6feb, 0x6fba, 0x6f8a, 0x6f59, 0x6f29, 0x6ef9, 0x6ec8,
	0x6e99, 0x6e69, 0x6e39, 0x6e0a, 0x6ddb, 0x6dab, 0x6d7d, 0x6d4e,
	0x6d1f, 0x6cf1, 0x6cc2, 0x6c94, 0x6c66, 0x6c38, 0x6c0a, 0x6bdd,
	0x6bb0, 0x6b82, 0x6b55, 0x6b28, 0x6afb, 0x6acf, 0x6aa2, 0x6a76,
	0x6a49, 0x6a1d, 0x69f1, 0x69c6, 0x699a, 0x696e, 0x6943, 0x6918,
	0x68ed, 0x68c2, 0x6897, 0x686c, 0x6842, 0x6817, 0x67ed, 0x67c3,
	0x6799, 0x676f, 0x6745, 0x671b, 0x66f2, 0x66c8, 0x669f, 0x6676,
	0x664d, 0x6624, 0x65fc, 0x65d3, 0x65aa, 0x6582, 0x655a, 0x6532,
	0x650a, 0x64e2, 0x64ba, 0x6493, 0x646b, 0x6444, 0x641c, 0x63f5,
	0x63ce, 0x63a7, 0x6381, 0x635a, 0x6333, 0x630d, 0x62e7, 0x62c1,
	0x629a, 0x6275, 0x624f, 0x6229, 0x6203, 0x61de, 0x61b8, 0x6193,
	0x616e, 0x6149, 0x6124, 0x60ff, 0x60da, 0x60b6, 0x6091, 0x606d,
	0x6049, 0x6024, 0x6000, 0x5fdc, 0x5fb8, 0x5f95, 0x5f71, 0x5f4d,
	0x5f2a, 0x5f07, 0x5ee3, 0x5ec0, 0x5e9d, 0x5e7a, 0x5e57, 0x5e35,
	0x5e12, 0x5def, 0x5dcd, 0x5dab, 0x5d88, 0x5d66, 0x5d44, 0x5d22,
	0x5d00, 0x5cde, 0x5cbd, 0x5c9b, 0x5c7a, 0x5c58, 0x5c37, 0x5c16,
	0x5bf5, 0x5bd4, 0x5bb3, 0x5b92, 0x5b71, 0x5b51, 0x5b30, 0x5b10,
	0x5aef, 0x5acf, 0x5aaf, 0x5a8f, 0x5a6f, 0x5a4f, 0x5a2f, 0x5a0f,
	0x59ef, 0x59d0, 0x59b0, 0x5991, 0x5972, 0x5952, 0x5933, 0x5914,
	0x58f5, 0x58d6, 0x58b7, 0x5899, 0x587a, 0x585b, 0x583d, 0x581f,
	0x5800, 0x57e2, 0x57c4, 0x57a6, 0x5788, 0x576a, 0x574c, 0x572e,
	0x5711, 0x56f3, 0x56d5, 0x56b8, 0x569b, 0x567d, 0x5660, 0x5643,
	0x5626, 0x5609, 0x55ec, 0x55cf, 0x55b2, 0x5596, 0x5579, 0x555d,
	0x5540, 0x5524, 0x5507, 0x54eb, 0x54cf, 0x54b3, 0x5497, 0x547b,
	0x545f, 0x5443, 0x5428, 0x540c, 0x53f0, 0x53d5, 0x53b9, 0x539e,
	0x5383, 0x5368, 0x534c, 0x5331, 0x5316, 0x52fb, 0x52e0, 0x52c6,
	0x52ab, 0x5290, 0x5276, 0x525b, 0x5240, 0x5226, 0x520c, 0x51f1,
	0x51d7, 0x51bd, 0x51a3, 0x5189, 0x516f, 0x5155, 0x513b, 0x5121,
	0x5108, 0x50ee, 0x50d5, 0x50bb, 0x50a2, 0x5088, 0x506f, 0x5056,
	0x503c, 0x5023, 0x500a, 0x4ff1, 0x4fd8, 0x4fbf, 0x4fa6, 0x4f8e,
	0x4f75, 0x4f5c, 0x4f44, 0x4f2b, 0x4f13, 0x4efa, 0x4ee2, 0x4eca,
	0x4eb1, 0x4e99, 0x4e81, 0x4e69, 0x4e51, 0x4e39, 0x4e21, 0x4e09,
	0x4df1, 0x4dda, 0x4dc2, 0x4daa, 0x4d93, 0x4d7b, 0x4d64, 0x4d4d,
	0x4d35, 0x4d1e, 0x4d07, 0x4cf0, 0x4cd8, 0x4cc1, 0x4caa, 0x4c93,
	0x4c7d, 0x4c66, 0x4c4f, 0x4c38, 0x4c21, 0x4c0b, 0x4bf4, 0x4bde,
	0x4bc7, 0x4bb1, 0x4b9a, 0x4b84, 0x4b6e, 0x4b58, 0x4b41, 0x4b2b,
	0x4b15, 0x4aff, 0x4ae9, 0x4ad3, 0x4abd, 0x4aa8, 0x4a92, 0x4a7c,
	0x4a66, 0x4a51, 0x4a3b, 0x4a26, 0x4a10, 0x49fb, 0x49e5, 0x49d0,
	0x49bb, 0x49a6, 0x4990, 0x497b, 0x4966, 0x4951, 0x493c, 0x4927,
	0x4912, 0x48fe, 0x48e9, 0x48d4, 0x48bf, 0x48ab, 0x4896, 0x4881,
	0x486d, 0x4858, 0x4844, 0x482f, 0x481b, 0x4807, 0x47f3, 0x47de,
	0x47ca, 0x47b6, 0x47a2, 0x478e, 0x477a, 0x4766, 0x4752, 0x473e,
	0x472a, 0x4717, 0x4703, 0x46ef, 0x46db, 0x46c8, 0x46b4, 0x46a1,
	0x468d, 0x467a, 0x4666, 0x4653, 0x4640, 0x462c, 0x4619, 0x4606,
	0x45f3, 0x45e0, 0x45cd, 0x45ba, 0x45a7, 0x4594, 0x4581, 0x456e,
	0x455b, 0x4548, 0x4536, 0x4523, 0x4510, 0x44fe, 0x44eb, 0x44d8,
	0x44c6, 0x44b3, 0x44a1, 0x448f, 0x447c, 0x446a, 0x4458, 0x4445,
	0x4433, 0x4421, 0x440f, 0x43fd, 0x43eb, 0x43d9, 0x43c7, 0x43b5,
	0x43a3, 0x4391, 0x437f, 0x436d, 0x435c, 0x434a, 0x4338, 0x4327,
	0x4315, 0x4303, 0x42f2, 0x42e0, 0x42cf, 0x42bd, 0x42ac, 0x429b,
	0x4289, 0x4278, 0x4267, 0x4256, 0x4244, 0x4233, 0x4222, 0x4211,
	0x4200, 0x41ef, 0x41de, 0x41cd, 0x41bc, 0x41ab, 0x419a, 0x418a,
	0x4179, 0x4168, 0x4157, 0x4147, 0x4136, 0x4125, 0x4115, 0x4104,
	0x40f4, 0x40e3, 0x40d3, 0x40c2, 0x40b2, 0x40a2, 0x4091, 0x4081,
	0x4071, 0x4061, 0x4050, 0x4040, 0x4030, 0x4020, 0x4010, 0x4000
};

void
cftal::impl::print_rcp_32_table(std::ostream& s)
{
	const unsigned N = udiv_2by1_rcp_32::TABLE_SIZE;
	s << "const cftal::uint16_t\n"
	  << "cftal::impl::udiv_2by1_rcp_32::_tbl[TABLE_SIZE]={\n";
	const std::uint32_t d32 = (1<<24) - (1<<14) + (1<<9);
	// empty lower part of table
	// empty lower part of table
	s << "\t// empty lower part\n";
	for (uint32_t i=0; i<N/2; ++i) {
		if ((i & 7) == 0)
			s << "\t0x0000,";
		else 
			s <<  " 0x0000,";
		if (((i+1) & 7)==0)
			s << '\n';
	}
	s << "\t// required upper part\n";
	for (uint32_t i=N/2; i<N; ++i) {
		unsigned q(i==0 ? 0 : d32/i);
		if ((i & 7) == 0)
			s << '\t';
		else 
			s << ' ';
		s << "0x"
		  <<std::hex << std::setfill('0') << std::setw(4)
		  << q
		  << std::setfill(' ') << std::dec;
		if (i != N-1)
			s << ',';
		if (((i+1) & 7)==0)
			s << '\n';
	}
	s << "};\n";
}

