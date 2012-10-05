#if !defined (__X86VEC_V4S32_INL_H__)
#define __X86VEC_V4S32_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#include <cftal/x86vec_ivec.h>
#error "never use this file directly"
#endif

inline
x86vec::v4s32::v4s32(vector_type r) : base_type(r)
{
}

inline
x86vec::v4s32::v4s32(const base_type& r) : base_type(r)
{
}

inline
x86vec::v4s32::v4s32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type(_mm_set_epi32(p03, p02, p01, p00))
{
}

inline
x86vec::v4s32::v4s32(element_type r)
        : base_type(_mm_set1_epi32(r))
{
}

inline
x86vec::v4s32::v4s32(v4s32::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi32(r) :
		    _mm_set_epi32(0, 0, 0, r))
{
}

inline
x86vec::v4s32::v4s32(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi32(*r()))
{
}

inline
x86vec::v4s32::v4s32(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_si128(m128i_ptr::make(r())) :
                    _mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v4s32::v4s32(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v4s32::v4s32(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::masked_vec<x86vec::v4s32>
x86vec::v4s32::operator()(const mask<v4s32>& m) 
{
	return masked_vec<v4s32>(*this, m);
}

inline
x86vec::v4s32&
x86vec::operator|= (v4s32& a, const v4s32& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator&= (v4s32& a, const v4s32& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator^= (v4s32& a, const v4s32& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator+= (v4s32& a, const v4s32& b)
{
        a = _mm_add_epi32(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator-= (v4s32& a, const v4s32& b)
{
        a = _mm_sub_epi32(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator*= (v4s32& a, const v4s32& b)
{
        a = impl::vpmulld::v(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator/=(v4s32& a, const v4s32& b)
{
        a= impl::div_s32::v(a(), b());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator%=(v4s32& a, const v4s32& b)
{
        v4s32 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v4s32&
x86vec::operator<<= (v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpslld_const<val>::v(a());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator<<= (v4s32& a, uint32_t b)
{
        a = impl::vpslld::v(a(), b);
        return a;
}

template <unsigned _P>
inline
x86vec::v4s32
x86vec::operator<< (const v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpslld_const<val>::v(a());
}

inline
x86vec::v4s32
x86vec::operator<< (const v4s32& a, uint32_t b)
{
        return impl::vpslld::v(a(), b);
}


template <unsigned _P>
inline
x86vec::v4s32&
x86vec::operator>>= (v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsrad_const<val>::v(a());
        return a;
}

inline
x86vec::v4s32&
x86vec::operator>>= (v4s32& a, uint32_t r)
{
        a = impl::vpsrad::v(a(), r);
        return a;
}

template <unsigned _P>
inline
x86vec::v4s32
x86vec::operator>> (const v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsrad_const<val>::v(a());
}

inline
x86vec::v4s32
x86vec::operator>> (const v4s32& a, uint32_t r)
{
        return impl::vpsrad::v(a(), r);
}


inline
x86vec::v4s32&
x86vec::operator++(v4s32& a)
{
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_add_epi32(a(), one);
        return a;
}

inline
x86vec::v4s32
x86vec::operator++ (v4s32& a, int)
{
        v4s32 t(a);
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_add_epi32(a(), one);
        return t;
}

inline
x86vec::v4s32&
x86vec::operator--(v4s32& a)
{
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_sub_epi32(a(), one);
        return a;
}

inline
x86vec::v4s32
x86vec::operator-- (v4s32& a, int)
{
        v4s32 t(a);
        const __m128i one = const4_u32< 1, 1, 1, 1>::iv();
        a = _mm_sub_epi32(a(), one);
        return t;
}

inline
x86vec::v4s32
x86vec::operator-(const v4s32& a)
{
#if defined (__SSSE3__)
	const __m128i sgn_bits= v_sign_s32_msk::iv();
	return _mm_sign_epi32(a(), sgn_bits);
#else
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi32(zero, a());
#endif
}

inline
const x86vec::v4s32&
x86vec::operator+(const v4s32& a)
{
	return a;
}

inline
x86vec::v4s32
x86vec::operator~(const v4s32& a)
{
        const __m128i all_set = const4_u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(a(), all_set);
}

inline
x86vec::v4s32
x86vec::operator!(const v4s32& a)
{
        const __m128i msk = impl::make_zero_int::v();
        return _mm_cmpeq_epi32(a(), msk);
}

inline
x86vec::v4s32 x86vec::operator| (const v4s32& a, const v4s32& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v4s32 x86vec::operator|| (const v4s32& a, const v4s32& b)
{
        return a | b;
}

inline
x86vec::v4s32 x86vec::operator& (const v4s32& a, const v4s32& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v4s32 x86vec::operator&& (const v4s32& a, const v4s32& b)
{
        return a & b;
}

inline
x86vec::v4s32 x86vec::operator^(const v4s32& a, const v4s32& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v4s32 x86vec::operator+ (const v4s32& a, const v4s32& b)
{
        return _mm_add_epi32(a(), b());
}

inline
x86vec::v4s32 x86vec::operator- (const v4s32& a, const v4s32& b)
{
        return _mm_sub_epi32(a(), b());
}

inline
x86vec::v4s32 x86vec::operator* (const v4s32& a, const v4s32& b)
{
        return impl::vpmulld::v(a(), b());
}

inline
x86vec::v4s32
x86vec::operator/(const v4s32& a, const v4s32& b)
{
        return impl::div_s32::v(a(), b());
}

inline
x86vec::v4s32
x86vec::operator%(const v4s32& a, const v4s32& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v4s32 x86vec::operator< (const v4s32& a, const v4s32& b)
{
        return _mm_cmpgt_epi32(b(), a());
}

inline
x86vec::v4s32 x86vec::operator<= (const v4s32& a, const v4s32& b)
{
#if defined (__SSE4_1__)
	// a <= b: a == min(a, b);
	__m128i min_ab = _mm_min_epi32(b(), a());
	return _mm_cmpgt_epi32(a(), min_ab);
#else
	return ~(b > a);
#endif
}

inline
x86vec::v4s32 x86vec::operator== (const v4s32& a, const v4s32& b)
{
        return _mm_cmpeq_epi32(a(), b());
}

inline
x86vec::v4s32 x86vec::operator!= (const v4s32& a, const v4s32& b)
{
        return ~(a == b);
}

inline
x86vec::v4s32 x86vec::operator>= (const v4s32& a, const v4s32& b)
{
#if defined (__SSE4_1__)
	// a >= b: a == max(a, b);
	__m128i max_ab = _mm_max_epi32(b(), a());
	return _mm_cmpgt_epi32(a(), max_ab);
#else
        return ~(a < b);
#endif
}

inline
x86vec::v4s32 x86vec::operator> (const v4s32& a, const v4s32& b)
{
        return _mm_cmpgt_epi32(a(), b());
}

inline
bool x86vec::all_signs(const v4s32& a)
{
        return all_signs_s32(a());
}

inline
bool x86vec::both_signs(const v4s32& a)
{
        return both_signs_s32(a());
}

inline
bool x86vec::no_signs(const v4s32& a)
{
        return no_signs_s32(a());
}

inline
x86vec::v4s32 x86vec::max(const v4s32& a, const v4s32& b)
{
#if defined (__SSE4_1__)
        return _mm_max_epi32(a(), b());
#else
	v4s32 _gt(a > b);
	return select(_gt, a, b);
#endif
}

inline
x86vec::v4s32 x86vec::min(const v4s32& a, const v4s32& b)
{
#if defined (__SSE4_1__)
        return _mm_min_epi32(a(), b());
#else
	v4s32 _lt(a < b);
	return select(_lt, a, b);
#endif
}

inline
x86vec::v4s32 x86vec::abs(const v4s32& a)
{
#if defined (__SSSE3__)
        return _mm_abs_epi32(a());
#else
        v4s32 neg(impl::make_zero_int::v());
        neg -= a;
        return max(a, neg);
#endif
}

inline
x86vec::v4s32 x86vec::andnot(const v4s32& a, const v4s32& b)
{
	return _mm_andnot_si128(a(), b());
}

inline
x86vec::v4s32 x86vec::mul_hi(const v4s32& x, const v4s32& y)
{
	return impl::vpmulhd::v(x(), y());
}

inline
std::pair<x86vec::v4s32, x86vec::v4s32>
x86vec::mul_lo_hi(const v4s32& x, const v4s32& y)
{
#if defined (__SSE4_1__) 
	// p0l p0h p2l p2h
	v4s32 e= _mm_mul_epi32(x(), y());
	// p1l p1h p3l p3h
	v4s32 o= _mm_mul_epi32(impl::vpshufd<1, 0, 3, 2>::v(x()),
			       impl::vpshufd<1, 0, 3, 2>::v(y()));
	// p0l p1l p0h p1h
	v4s32 t0= permute<0, 4, 1, 5>(e, o);
	// p2l p3l p2h p3h
	v4s32 t1= permute<2, 6, 3, 7>(e, o);
	// p0h p1h p2h p3h
	v4s32 h = permute<2, 3, 6, 7>(t0, t1);
	v4s32 l = permute<0, 1, 4, 5>(t0, t1);
	return std::make_pair(l, h);
#else
	// muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
	// mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
	std::pair<v4u32, v4u32> ur(mul_lo_hi(v4u32(x), v4u32(y)));
	v4s32 xsgn_y= y >> const_shift::_31;
	v4s32 xsgn_x= x >> const_shift::_31;
	v4s32 x_and_xsgn_y = x & xsgn_y;
	v4s32 y_and_xsgn_x = y & xsgn_x;
	v4s32 sh = v4s32(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
	v4s32 sl = v4s32(ur.first);
	return std::make_pair(sl, sh);
#endif
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
inline
x86vec::v4s32 x86vec::select(const v4s32& a, const v4s32& b)
{
        return select_u32 <_P0, _P1, _P2, _P3> (a(), b());
}

inline
x86vec::v4s32 x86vec::select(const v4s32& msk,
                             const v4s32& on_true,
                             const v4s32& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
x86vec::v4s32 x86vec::permute(const v4s32& a)
{
        return perm_u32<_P0, _P1, _P2, _P3>(a());
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
x86vec::v4s32 x86vec::permute(const v4s32& a, const v4s32& b)
{
        return perm_u32<_P0, _P1, _P2, _P3>(a(), b());
}

template <unsigned _I>
inline
x86vec::v4s32 x86vec::insert(const v4s32& a, typename v4s32::element_type v)
{
	return insert_u32<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v4s32::element_type
x86vec::extract(const v4s32& a)
{
	return extract_u32<_I>(a());
}

// Local variables:
// mode: c++
// end:
#endif
