#include <x86vec.h>
#include <iostream>
#include <iomanip>

typedef unsigned __int128 u128_t;

u128_t sll(u128_t r, unsigned s)
{
	return r<<s;
}

cftal::uint128_t sll(cftal::uint128_t r, unsigned s)
{
	return r<<s;
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

