#include "x86vec.h"
#include "emuvec.h"
#include "divisor.h"
#include "x86vec_test.h"
#include "bitops.h"
#include <functional>
#include <iomanip>

#if 0
void check_float()
{
        bool rc(true);
        __m128 a = x86vec::test::load_float(false);
        // __m128 b = x86vec::test::load_float(true);
        __m128 r;
        r = x86vec::perm_float<0, -1, 1, -1>(a);
        rc &= x86vec::test::check_float("perm1_float", r,
                                        x86vec::test::idx(0,-1,1,-1));
}

template <int _P0, int _P1, int _P2, int _P3>
void check_u32()
{
        bool rc(true);
        __m128i a = x86vec::test::load_u32(false);
        // __m128 b = x86vec::test::load_u32(true);
        __m128i r;
        r = x86vec::perm_u32<_P0, _P1, _P2, _P3>(a);
        rc &= x86vec::test::check_u32("perm1_u32", r,
                                      x86vec::test::idx(_P0,_P1,_P2,_P3));
}

void chk_u32_cases()
{
        check_u32< 0,-1, 1,-1>();
        check_u32< 2,-1, 3,-1>();
        check_u32<-1, 0,-1, 1>();
        check_u32<-1, 2,-1, 3>();
        check_u32< 0, 1,-1,-1>();
        check_u32< 2, 3,-1,-1>();
        check_u32<-1,-1, 0, 1>();
        check_u32<-1,-1, 2, 3>();


}
#endif

__m128i test_perm1_u16(__m128i a)
{
        return x86vec::perm_u16<0, 1, 2, 3, 7, 6, 5, 4>(a);
}


template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
void chk_u16()
{
        using namespace x86vec::test;

        bool rc(true);
        __m128i a = load_u16(false);
        // __m128 b = load_u16(true);
        __m128i r;
        r = x86vec::perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a);
        rc &= check_u16("perm1_u16", r,
                        idx(_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7));
}

void chk_u16_cases()
{
        using namespace x86vec::test;
        // copy
        chk_u16< 0, 1, 2, 3, 4, 5, 6, 7>();
        // lqdq
        chk_u16< 0, 1, 2, 3, 0, 1, 2, 3>();
        // ldq
        chk_u16< 0, 1, 0, 1, 2, 3, 2, 3>();
        // lwd
        chk_u16< 0, 0, 1, 1, 2, 2, 3, 3>();

        // copied from x86vec_perm.h
        chk_u16<-1,-1,-1,-1,-1,-1,-1,-1>();
        chk_u16< 0, 1, 2, 3, 4, 5, 6, 7>();
        chk_u16< 0, 0, 1, 1, 2, 2, 3, 3>();
        chk_u16< 4, 4, 5, 5, 6, 6, 7, 7>();
        chk_u16< 0, 1, 0, 1, 2, 3, 2, 3>();
        chk_u16< 4, 5, 4, 5, 6, 7, 6, 7>();
        chk_u16< 0, 1, 2, 3, 0, 1, 2, 3>();
        chk_u16< 4, 5, 6, 7, 4, 5, 6, 7>();
        chk_u16< 0,-1, 1,-1, 2,-1, 3,-1>();
        chk_u16< 4,-1, 5,-1, 6,-1, 7,-1>();
        chk_u16<-1, 0,-1, 1,-1, 2, -1, 3>();
        chk_u16<-1, 4,-1, 5,-1, 6, -1, 7>();

        // low/high shuffles
        chk_u16< 3, 2, 1, 0, 7, 6, 5, 4>();
        chk_u16<-1, 2,-1, 0, 7, 6, 6, 4>();
        chk_u16<-1, 2, 5, 1, 0, 0, 7, 1>();

        // low/high shifts
        chk_u16<7, 6, 5, 4, 3, 2, 1, 0>();
        // 32 bit perms
        chk_u16<6, 7, 4, 5, 2, 3, 0, 1>();
        // zero only
        chk_u16< 0, -1, 2, 3, 4, 5, -1, 7>();
#if 0
        chk_u16<8, 6, 5, 4, 3, 2, 1, 0>();
        chk_u16<8, -2, 5, 4, 3, 2, 1, 0>();
#endif
}

x86vec::v4u32 muluh(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return mulh(a, b);
}

x86vec::v4s32 mulsh(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return mulh(a, b);
}

void check_div_8(uint16_t ul, uint8_t v)
{
	using namespace cftal;
	typedef impl::udiv_2by1<uint8_t> div_type;

	std::pair<uint8_t, uint8_t> pq(
		div_type::d(ul, ul>>8, v, nullptr));
	uint16_t q((uint16_t(pq.second)<<8) |	pq.first);
	uint16_t q_ref = ul/v;
	if (q != q_ref) {
		std::cout << ul << " / " << uint16_t(v) << " = " << q
			  << " != " << q_ref << std::endl;
		std::exit(3);
	}
}

void check_div_8()
{
	for (int u=0x0; u< 0x10000; ++u) {
		if ((u & 0xFF) == 0xFF) {
			std::cout << u <<  '\r' << std::flush;
		}
		for (int v=1; v< 0x100; ++v) {
			check_div_8(u, v);
		}
	}
}

namespace cftal {

	namespace test {

		template <class _T>
		struct div_half {
		};

		template <>
		struct div_half<uint16_t> 
			: public std::binary_function<uint16_t, 
						      uint16_t, 
						      uint16_t> {
			uint16_t operator()(uint16_t a, uint16_t b) 
				const {
				return a / (b & 0xFF);
			}
		};
		
		template <>
		struct div_half<duint<uint8_t> > 
			: public std::binary_function<duint<uint8_t>,
						      duint<uint8_t>,
						      duint<uint8_t> > {
			duint<uint8_t> operator()(const duint<uint8_t>& a,
						  const duint<uint8_t>& b)
				const {
				const uint8_t& l= b.l();
				return a / l;
			}
		};


		template <class _RES>
		void check_res(uint16_t u, uint16_t v, 
			       _RES res, _RES ref_res,
			       const char* msg) 
		{
			if (res != ref_res) {
				std::cout << std::hex
					  << u << ' ' << msg << ' ' 
					  << v << " = "
					  << res << " != (expected:) "
					  << ref_res
					  << std::dec
					  << std::endl;
				std::exit(3);
			}
		}

		template <template <class _U> class _OP>
		void check_bi_op(uint16_t u, uint16_t v, const char* msg)
		{
			
			duint<uint8_t> uu(u, u>>8);
			duint<uint8_t> vv(v, v>>8);
			_OP<uint16_t> op1;
			uint16_t r(op1(u, v));
			_OP<duint<uint8_t> > op2;
			duint<uint8_t> rr(op2(uu, vv));
			uint16_t res((uint16_t(rr.h())<<8)|rr.l());
			check_res(u, v, res, r, msg);
		}

		template <template <class _U> class _OP>
		void check_bi_op(const char* msg, uint32_t v0=0, 
				 uint32_t v1= 0x10000) 
		{
			for (uint32_t u=0; u<0x10000; ++u) {
				std::uint16_t tu= u;
				if (0x3FF==(u & 0x3FF)) {
					std::cout << msg << ' ' <<  u << '\r'
						  << std::flush;
				}
				for (uint32_t v=v0; v<v1; ++v) {
					std::uint16_t tv=v;
					check_bi_op<_OP>(tu, tv, msg);
				}
			}
			std::cout << msg << " passed\n";
		}

		template <template <class _U> class _OP>
		void check_cmp_op(uint16_t u, uint16_t v, const char* msg)
		{
			duint<uint8_t> uu(u, u>>8);
			duint<uint8_t> vv(v, v>>8);
			_OP<uint16_t> op1;
			bool r(op1(u, v));
			_OP<duint<uint8_t> > op2;
			bool res(op2(uu, vv));
			check_res(u, v, res, r, msg);
		}

		template <template <class _U> class _OP>
		void check_cmp_op(const char* msg, uint32_t v0=0) 
		{
			for (uint32_t u=0; u<0x10000; ++u) {
				std::uint16_t tu= u;
				if (0x3FF==(u & 0x3FF)) {
					std::cout << msg << ' ' <<  u << '\r'
						  << std::flush;
				}
				for (uint32_t v=v0; v<0x10000; ++v) {
					std::uint16_t tv=v;
					check_cmp_op<_OP>(tu, tv, msg);
				}
			}
			std::cout << msg << " passed\n";
		}

		
		void check_duint_ops()
		{
			check_bi_op<std::plus>("add");
			check_bi_op<std::minus>("sub");
			check_bi_op<std::multiplies>("mul");

			check_cmp_op<std::less>("<");
			check_cmp_op<std::less_equal>("<=");
			check_cmp_op<std::equal_to>("==");
			check_cmp_op<std::not_equal_to>("!=");
			check_cmp_op<std::greater_equal>(">=");
			check_cmp_op<std::greater>(">");
			check_bi_op<div_half>("div_half", 1, 255);
			check_bi_op<std::divides>("div", 1);
		}


		void check_div() 
		{
			duint<uint8_t> v(4) , u(1);
			duint<uint8_t> q(v/u);
			uint16_t res((uint16_t(q.h())<<8)|q.l());
			std::cout << res << std::endl;
		}
	}
}


void check_div_16(uint16_t u, uint16_t v)
{
	typedef cftal::duint<uint8_t> v_t;
	v_t vu(u, u>>8), vv(v, v>>8);
	v_t vq(vu / vv);
	uint16_t q((uint16_t(vq.h()) <<8) | vq.l());
	uint16_t q_ref = u/v;
	if (q != q_ref) {
		std::cout << u << " / " << uint16_t(v) << " = " << q
			  << " != " << q_ref << std::endl;
		std::exit(3);
	}
}

void check_div_16()
{
#if 1
	check_div_16(258, 257);
#else
	for (int u=0x0; u< 0x10000; ++u) {
		if ((u & 0xFF) == 0xFF) {
			std::cout << u <<  '\r' << std::flush;
		}
		for (int v=1; v< 0x10000; ++v) {
			check_div_16(u, v);
		}
	}
#endif
}


int main(int argc, char** argv)
{
	// cftal::test::check_div();
	cftal::test::check_duint_ops();
        return 0;
}
