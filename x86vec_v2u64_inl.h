#if !defined (__X86VEC_V2U64_INL_H__)
#define __X86VEC_V2U64_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

inline
x86vec::v2u64::v2u64(vector_type r) : base_type(r)
{
}

inline
x86vec::v2u64::v2u64(const base_type& r) : base_type(r)
{
}

inline
x86vec::v2u64::v2u64(element_type p00, element_type p01)
        : base_type(_mm_set_epi64x(p01, p00))
{
}

inline
x86vec::v2u64::v2u64(element_type r)
        : base_type(_mm_set1_epi64x(r))
{
}

inline
x86vec::v2u64::v2u64(v2u64::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi64x(r) :
		    _mm_set_epi64x(0, r))
{
}

inline
x86vec::v2u64::v2u64(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi64x(*r()))
{
}

inline
x86vec::v2u64::v2u64(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_si128(m128i_ptr::make(r())) :
                    _mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v2u64::v2u64(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v2u64::v2u64(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v2u64&
x86vec::operator|= (v2u64& a, const v2u64& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator&= (v2u64& a, const v2u64& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator^= (v2u64& a, const v2u64& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator+= (v2u64& a, const v2u64& b)
{
        a = _mm_add_epi64(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator-= (v2u64& a, const v2u64& b)
{
        a = _mm_sub_epi64(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator*= (v2u64& a, const v2u64& b)
{
        a = impl::vpmullq::v(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator/=(v2u64& a, const v2u64& b)
{
        a= impl::div_u64::v(a(), b());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator%=(v2u64& a, const v2u64& b)
{
        v2u64 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v2u64&
x86vec::operator<<= (v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsllq_const<val>::v(a());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator<<= (v2u64& a, uint32_t b)
{
        a = impl::vpsllq::v(a(), b);
        return a;
}

template <unsigned _P>
inline
x86vec::v2u64
x86vec::operator<< (const v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsllq_const<val>::v(a());
}

inline
x86vec::v2u64
x86vec::operator<< (const v2u64& a, uint32_t b)
{
        return impl::vpsllq::v(a(), b);
}


template <unsigned _P>
inline
x86vec::v2u64&
x86vec::operator>>= (v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsrlq_const<val>::v(a());
        return a;
}

inline
x86vec::v2u64&
x86vec::operator>>= (v2u64& a, uint32_t r)
{
        a = impl::vpsrlq::v(a(), r);
        return a;
}

template <unsigned _P>
inline
x86vec::v2u64
x86vec::operator>> (const v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsrlq_const<val>::v(a());
}

inline
x86vec::v2u64
x86vec::operator>> (const v2u64& a, uint32_t r)
{
        return impl::vpsraq::v(a(), r);
}

inline
x86vec::v2u64&
x86vec::operator++(v2u64& a)
{
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_add_epi64(a(), one);
        return a;
}

inline
x86vec::v2u64
x86vec::operator++ (v2u64& a, int)
{
        v2u64 t(a);
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_add_epi64(a(), one);
        return t;
}

inline
x86vec::v2u64&
x86vec::operator--(v2u64& a)
{
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_sub_epi64(a(), one);
        return a;
}

inline
x86vec::v2u64
x86vec::operator-- (v2u64& a, int)
{
        v2u64 t(a);
        const __m128i one = const4_u32< 1, 0, 1, 0>::iv();
        a = _mm_sub_epi64(a(), one);
        return t;
}

inline
x86vec::v2u64
x86vec::operator-(const v2u64& a)
{
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi64(zero, a());
}

inline
const x86vec::v2u64&
x86vec::operator+(const v2u64& a)
{
	return a;
}

inline
x86vec::v2u64
x86vec::operator~(const v2u64& a)
{
        const __m128i all_set = const4_u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(a(), all_set);
}

inline
x86vec::v2u64
x86vec::operator!(const v2u64& a)
{
        const __m128i msk = impl::make_zero_int::v();
        return a == v2u64(msk);
}

inline
x86vec::v2u64 x86vec::operator| (const v2u64& a, const v2u64& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v2u64 x86vec::operator|| (const v2u64& a, const v2u64& b)
{
        return a | b;
}

inline
x86vec::v2u64 x86vec::operator& (const v2u64& a, const v2u64& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v2u64 x86vec::operator&& (const v2u64& a, const v2u64& b)
{
        return a & b;
}

inline
x86vec::v2u64 x86vec::operator^(const v2u64& a, const v2u64& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v2u64 x86vec::operator+ (const v2u64& a, const v2u64& b)
{
        return _mm_add_epi64(a(), b());
}

inline
x86vec::v2u64 x86vec::operator- (const v2u64& a, const v2u64& b)
{
        return _mm_sub_epi64(a(), b());
}

inline
x86vec::v2u64 x86vec::operator* (const v2u64& a, const v2u64& b)
{
        return impl::vpmullq::v(a(), b());
}

inline
x86vec::v2u64
x86vec::operator/(const v2u64& a, const v2u64& b)
{
        return impl::div_u64::v(a(), b());
}

inline
x86vec::v2u64
x86vec::operator%(const v2u64& a, const v2u64& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v2u64 x86vec::operator< (const v2u64& a, const v2u64& b)
{
	return b > a;
}

inline
x86vec::v2u64 x86vec::operator<= (const v2u64& a, const v2u64& b)
{
	return ~(b > a);
}

inline
x86vec::v2u64 x86vec::operator== (const v2u64& a, const v2u64& b)
{
#if defined (__SSE4_1__)
        return _mm_cmpeq_epi64(a(), b());
#else
	// a == b : a_h == b_h && a_l == b_l
	__m128i r= _mm_cmpeq_epi32(a(), b());
	__m128i c32s = impl::vpsllq_const<32>::v(r);
	r = _mm_and_si128(r, c32s);
	return impl::vpshufd<1, 1, 3, 3>::v(r);
#endif
}

inline
x86vec::v2u64 x86vec::operator!= (const v2u64& a, const v2u64& b)
{
        return ~(a == b);
}

inline
x86vec::v2u64 x86vec::operator>= (const v2u64& a, const v2u64& b)
{
        return ~(a < b);
}

inline
x86vec::v2u64 x86vec::operator> (const v2u64& a, const v2u64& b)
{
#if defined (__SSE4_2__)
	const __m128i msk= v_sign_s64_msk::iv();
	__m128i ax= _mm_xor_si128(a(), msk);
	__m128i bx= _mm_xor_si128(b(), msk);
        return _mm_cmpgt_epi64(ax, bx);
#else
	// a > b: (a_h > b_h) || ((a_h == b_h) && (a_l > b_l))
	// c1 ---------^ 
	// c2 -------------------------^
	// c3 -----------------------------------------^
	const __m128i msk = v_sign_s32_msk::iv();
	__m128i ax= _mm_xor_si128(a(), msk);
	__m128i bx= _mm_xor_si128(b(), msk);
	__m128i c2= _mm_cmpeq_epi32(a(), b());
	__m128i c1c3= _mm_cmpgt_epi32(ax, bx);
	// only elements 1, 3 are valid:
	__m128i c2_and_c3 = _mm_and_si128(c2, 
					  impl::vpshufd<0, 0, 2, 2>::v(c1c3));
	// only elements 1, 3 are valid.
	__m128i r = _mm_or_si128(c1c3, c2_and_c3);
	r = impl::vpshufd< 1, 1, 3, 3>::v(r);
	return r;
#endif
}

inline
x86vec::v2u64 x86vec::max(const v2u64& a, const v2u64& b)
{
	v2u64 _gt(a > b);
	return select(_gt, a, b);
}

inline
x86vec::v2u64 x86vec::min(const v2u64& a, const v2u64& b)
{
	v2u64 _lt(a < b);
	return select(_lt, a, b);
}

inline
x86vec::v2u64 x86vec::mulh(const v2u64& x, const v2u64& y)
{
	// TODO: implement me.
	return 0;
}

template < bool _P0, bool _P1>
inline
x86vec::v2u64 x86vec::select(const v2u64& a, const v2u64& b)
{
        return select_u64<_P0, _P1> (a(), b());
}

inline
x86vec::v2u64 x86vec::select(const v2u64& msk,
                             const v2u64& on_true,
                             const v2u64& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1>
inline
x86vec::v2u64 x86vec::permute(const v2u64& a)
{
        return perm_u64<_P0, _P1>(a());
}

template < int _P0, int _P1 >
inline
x86vec::v2u64 x86vec::permute(const v2u64& a, const v2u64& b)
{
        return perm_u64<_P0, _P1>(a(), b());
}

template <unsigned _I>
inline
x86vec::v2u64 x86vec::insert(const v2u64& a, typename v2u64::element_type v)
{
	return insert_u64<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v2u64::element_type
x86vec::extract(const v2u64& a)
{
	return extract_u64<_I>(a());
}

// Local variables:
// mode: c++
// end:
#endif
