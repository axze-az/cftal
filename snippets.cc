#include <x86vec.h>
#include <iostream>
#include <iomanip>

namespace x86vec {


	template <class _L, class _OP, class _R>
	struct expr_node {
		const _L* _l;
		const _R* _r;
		_OP _op;
	public:
		auto 
		eval() ->decltype(_OP::operator()(_L,_R)) const {
			return _op.eval(_l->eval(), _r->eval());
		}
	};

	template <class _L, class _R, class _OP>
	auto eval(const expr_node& r) 
	{
		
	}


	template <class _OP>
	class expr_node<v2f64, v2f64, _OP> {
		const v2f64* _l;
		const v2f64* _r;
		_OP _op;
	public:
		v2f64 eval() const {
			return _op.eval(*_l, *_r);
		}
	};

		
	template <class _T>
	struct add_op {
		
	};

	template <class _T>
	struct mul_op {
	};

	// 
	class expr {
	};

}

typedef unsigned __int128 u128_t;

u128_t sll(u128_t r, unsigned s)
{
	return r<<s;
}

cftal::uint128_t add1(const cftal::uint128_t& r)
{
	return r + 1;
}

cftal::uint128_t slli17(cftal::uint128_t r)
{
	return r<<128;
}

u128_t ssli17(u128_t r)
{
	return r<<17;
}

u128_t ssli96(u128_t r)
{
	return r<<96;
}

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


std::pair<x86vec::v2u64, x86vec::v2u64>
square(x86vec::v2u64 a)
{
	return wide_mul(a, a);
}

std::pair<x86vec::v2s64, x86vec::v2s64>
square(x86vec::v2s64 a)
{
	return wide_mul(a, a);
}

typedef unsigned long long u64b;
typedef __uint128_t u128b;

u64b rng_hash_128(u64b *s)
{
	u64b c = 7319936632422683419ULL;
	u64b x = s[1];
	u64b y = s[0];
	u128b xx;

	/* Increment 128bit LCG */
	s[0] += c;
	s[1] += (s[0] < c) + y;

	/* Default threaded option of xoring seed location */
	x ^= (u64b) s;

	/* Hash result */
	xx = (u128b)x * c;
	x = xx ^ y ^ (xx >> 64);
	xx = (u128b)x * c;
	return xx + y + (xx >> 64);
}

void test_div()
{
	using namespace x86vec;
	using test::pr_v2u64;

	v2u64::element_type vi(0UL);
	v2u64 u(3300917957719651597UL, 17331437524411346996UL);
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
