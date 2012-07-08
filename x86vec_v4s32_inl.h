#if !defined (__X86VEC_V4S32_INL_H__)
#define __X86VEC_V4S32_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
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
x86vec::v4s32::v4s32(x86vec::v4s32::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi32(r) : _mm_cvtsi32_si128(r))
{
}

inline
x86vec::v4s32::v4s32(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi32(* (r())))
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
        __m128i s = _mm_cvtsi32_si128(b);
        a = impl::vpslld::v(a(), s);
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
        __m128i s = _mm_cvtsi32_si128(b);
        return impl::vpslld::v(a(), s);
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
        __m128i s = _mm_cvtsi32_si128(r);
        a = impl::vpsrad::v(a(), s);
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
        __m128i s = _mm_cvtsi32_si128(r);
        return impl::vpsrad::v(a(), s);
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
        return a;
}

inline
x86vec::v4s32
x86vec::operator-(const v4s32& a)
{
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi32(zero, a());
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
	return ~(b > a);
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
        return ~(a < b);
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
        return _mm_max_epi32(a(), b());
}

inline
x86vec::v4s32 x86vec::min(const v4s32& a, const v4s32& b)
{
        return _mm_min_epi32(a(), b());
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
x86vec::v4s32 x86vec::mulh(const v4s32& x, const v4s32& y)
{
	// return _mm_mulhi_epi32(x(), y());
#if defined __SSE4_1__
	// 0, 2 at positions 1 3
	__m128i e= _mm_mul_epi32(x(), y());
	// 1, 3 at positions 1 3
	__m128i o= _mm_mul_epi32(_mm_srli_epi64(x(), 32),
				 _mm_srli_epi64(y(), 32));
	const __m128i msk = const4_u32<0, -1, 0, -1>::iv();
	e = _mm_slli_epi64(e, 32);
	o = _mm_and_si128(e, msk);
	return _mm_or_si128(e, o);
#else
	// muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
	// mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
	v4u32 m(mulh(v4u32(x), v4u32(y)));
	v4s32 xsgn_y(y >> const_shift::_31);
	v4s32 xsgn_x(x >> const_shift::_31);
	return v4s32(m) - (x & xsgn_y) - (y & xsgn_x);
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

// Local variables:
// mode: c++
// end:
#endif
