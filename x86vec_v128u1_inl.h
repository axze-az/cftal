#if !defined (__X86VEC_V128U1_INL_H__)
#define __X86VEC_V128U1_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

inline
x86vec::v128u1::v128u1(__m128i v) : base_type(v)
{
}

inline
x86vec::v128u1::v128u1(const base_type& v) : base_type(v)
{
}

inline
x86vec::v128u1&
x86vec::operator|= (v128u1& a, const v128u1& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v128u1&
x86vec::operator&= (v128u1& a , const v128u1& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v128u1&
x86vec::operator^= (v128u1& a, const v128u1& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v128u1
x86vec::operator~(const v128u1& r)
{
        const __m128i msk = const_v4u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(r(), msk);
}

inline
x86vec::v128u1
x86vec::operator| (const v128u1& a, const v128u1& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v128u1
x86vec::operator|| (const v128u1& a, const v128u1& b)
{
        return a | b;
}

inline
x86vec::v128u1
x86vec::operator& (const v128u1& a, const v128u1& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v128u1
x86vec::operator&& (const v128u1& a, const v128u1& b)
{
        return a & b;
}

inline
x86vec::v128u1
x86vec::operator^(const v128u1& a, const v128u1& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v128u1
x86vec::andnot(const v128u1& a, const v128u1& b)
{
	return _mm_andnot_si128(a(), b());
}

inline
bool
x86vec::all(const v128u1& a)
{
        return all_bits(a());
}

inline
bool
x86vec::both(const v128u1& a)
{
        return both_bits(a());
}

inline
bool
x86vec::none(const v128u1& a)
{
        return no_bits(a());
}

// Local variables:
// mode: c++
// end:
#endif
