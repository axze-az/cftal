#if !defined (__X86VEC_V4U32_INL_H__)
#define __X86VEC_V4U32_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

inline
x86vec::v4u32::v4u32(vector_type r) : base_type(r)
{
}

inline
x86vec::v4u32::v4u32(const base_type& r) : base_type(r)
{
}

inline
x86vec::v4u32::v4u32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type(_mm_set_epi32(p03, p02, p01, p00))
{
}

inline
x86vec::v4u32::v4u32(element_type r)
        : base_type(_mm_set1_epi16(r))
{
}

inline
x86vec::v4u32::v4u32(x86vec::v4u32::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi32(r) : _mm_cvtsi32_si128(r))
{
}

inline
x86vec::v4u32::v4u32(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi32(* (r())))
{
}

inline
x86vec::v4u32::v4u32(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_si128(m128i_ptr::make(r())) :
                    _mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v4u32::v4u32(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v4u32::v4u32(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v4u32&
x86vec::operator|= (v4u32& a, const v4u32& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator&= (v4u32& a, const v4u32& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator^= (v4u32& a, const v4u32& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator+= (v4u32& a, const v4u32& b)
{
        a = _mm_add_epi32(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator-= (v4u32& a, const v4u32& b)
{
        a = _mm_sub_epi32(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator*= (v4u32& a, const v4u32& b)
{
        a = impl::vpmulld::v(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator/=(v4u32& a, const v4u32& b)
{
        a= impl::div_u32::v(a(), b());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator%=(v4u32& a, const v4u32& b)
{
        v4u32 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v4u32&
x86vec::operator<<= (v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpslld_const<val>::v(a());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator<<= (v4u32& a, uint32_t b)
{
        __m128i s = _mm_cvtsi32_si128(b);
        a = impl::vpslld::v(a(), s);
        return a;
}

template <unsigned _P>
inline
x86vec::v4u32
x86vec::operator<< (const v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpslld_const<val>::v(a());
}

inline
x86vec::v4u32
x86vec::operator<< (const v4u32& a, uint32_t b)
{
        __m128i s = _mm_cvtsi32_si128(b);
        return impl::vpslld::v(a(), s);
}


template <unsigned _P>
inline
x86vec::v4u32&
x86vec::operator>>= (v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsrld_const<val>::v(a());
        return a;
}

inline
x86vec::v4u32&
x86vec::operator>>= (v4u32& a, uint32_t r)
{
        __m128i s = _mm_cvtsi32_si128(r);
        a = impl::vpsrld::v(a(), s);
        return a;
}

template <unsigned _P>
inline
x86vec::v4u32
x86vec::operator>> (const v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsrld_const<val>::v(a());
}

inline
x86vec::v4u32
x86vec::operator>> (const v4u32& a, uint32_t r)
{
        __m128i s = _mm_cvtsi32_si128(r);
        return impl::vpsrld::v(a(), s);
}


inline
x86vec::v4u32&
x86vec::operator++(v4u32& a)
{
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_add_epi32(a(), one);
        return a;
}

inline
x86vec::v4u32
x86vec::operator++ (v4u32& a, int)
{
        v4u32 t(a);
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_add_epi32(a(), one);
        return t;
}

inline
x86vec::v4u32&
x86vec::operator--(v4u32& a)
{
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_sub_epi32(a(), one);
        return a;
}

inline
x86vec::v4u32
x86vec::operator-- (v4u32& a, int)
{
        v4u32 t(a);
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_sub_epi32(a(), one);
        return a;
}

inline
x86vec::v4u32
x86vec::operator-(const v4u32& a)
{
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi32(zero, a());
}

inline
const x86vec::v4u32&
x86vec::operator+(const v4u32& a)
{
	return a;
}

inline
x86vec::v4u32
x86vec::operator~(const v4u32& a)
{
        const __m128i all_set = const4_u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(a(), all_set);
}

inline
x86vec::v4u32
x86vec::operator!(const v4u32& a)
{
        const __m128i msk = impl::make_zero_int::v();
        return _mm_cmpeq_epi32(a(), msk);
}

inline
x86vec::v4u32 x86vec::operator| (const v4u32& a, const v4u32& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v4u32 x86vec::operator|| (const v4u32& a, const v4u32& b)
{
        return a | b;
}

inline
x86vec::v4u32 x86vec::operator& (const v4u32& a, const v4u32& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v4u32 x86vec::operator&& (const v4u32& a, const v4u32& b)
{
        return a & b;
}

inline
x86vec::v4u32 x86vec::operator^(const v4u32& a, const v4u32& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v4u32 x86vec::operator+ (const v4u32& a, const v4u32& b)
{
        return _mm_add_epi32(a(), b());
}

inline
x86vec::v4u32 x86vec::operator- (const v4u32& a, const v4u32& b)
{
        return _mm_sub_epi32(a(), b());
}

inline
x86vec::v4u32 x86vec::operator* (const v4u32& a, const v4u32& b)
{
        return impl::vpmulld::v(a(), b());
}

inline
x86vec::v4u32
x86vec::operator/(const v4u32& a, const v4u32& b)
{
        return impl::div_u32::v(a(), b());
}

inline
x86vec::v4u32
x86vec::operator%(const v4u32& a, const v4u32& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v4u32 x86vec::operator< (const v4u32& a, const v4u32& b)
{
	v4u32 ta(a ^ v_sign_s32_msk::iv());
	v4u32 tb(b ^ v_sign_s32_msk::iv());
        return _mm_cmpgt_epi32(tb(), ta());
}

inline
x86vec::v4u32 x86vec::operator<= (const v4u32& a, const v4u32& b)
{
	return ~(b > a);
}

inline
x86vec::v4u32 x86vec::operator== (const v4u32& a, const v4u32& b)
{
        return _mm_cmpeq_epi32(a(), b());
}

inline
x86vec::v4u32 x86vec::operator!= (const v4u32& a, const v4u32& b)
{
        return ~(a == b);
}

inline
x86vec::v4u32 x86vec::operator>= (const v4u32& a, const v4u32& b)
{
	return ~(a < b);
}

inline
x86vec::v4u32 x86vec::operator> (const v4u32& a, const v4u32& b)
{
	v4u32 ta(a ^ v_sign_s32_msk::iv());
	v4u32 tb(b ^ v_sign_s32_msk::iv());
        return _mm_cmpgt_epi32(ta(), tb());
}

inline
x86vec::v4u32 x86vec::max(const v4u32& a, const v4u32& b)
{
#if defined (__SSE4_1__)
	return _mm_max_epu32(a(), b());
#else
	v4u32 _gt(a > b);
	return select(_gt, a, b);
#endif
}

inline
x86vec::v4u32 x86vec::min(const v4u32& a, const v4u32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epu32(a(), b());
#else
	v4u32 _lt(a < b);
	return select(_lt, a, b);
#endif
}

inline
x86vec::v4u32 x86vec::mulh(const v4u32& a, const v4u32& b)
{
	// return _mm_mulhi_epu32(a(), b());
	// 0, 2 at positions 1 3
	__m128i e= _mm_mul_epu32(a(), b());
	// 1, 3 at positions 1 3
	__m128i o= _mm_mul_epu32(_mm_srli_epi64(a(), 32),
				 _mm_srli_epi64(b(), 32));
	// 0, 2 at position 0, 2
	e = _mm_slli_epi64(e, 32);
#if defined (__SSE4_1__)
	return select_u32<1, 0, 1, 0>(e, o);
#else
	const __m128i msk = const4_u32<0, -1, 0, -1>::iv();
	o = _mm_and_si128(o, msk);
	return _mm_or_si128(e, o);
#endif
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
inline
x86vec::v4u32 x86vec::select(const v4u32& a, const v4u32& b)
{
        return select_u32 <_P0, _P1, _P2, _P3> (a(), b());
}

inline
x86vec::v4u32 x86vec::select(const v4u32& msk,
                             const v4u32& on_true,
                             const v4u32& on_false)
{
        return select(msk(), on_true(), on_false());
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
x86vec::v4u32 x86vec::permute(const v4u32& a)
{
        return perm_u32<_P0, _P1, _P2, _P3>(a());
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
x86vec::v4u32 x86vec::permute(const v4u32& a, const v4u32& b)
{
        return perm_u32<_P0, _P1, _P2, _P3>(a(), b());
}

// Local variables:
// mode: c++
// end:
#endif
