#if !defined (__X86VEC_V8U16_INL_H__)
#define __X86VEC_V8U16_INL_H__ 1

#if !defined (__X86VEC_IVEC_H__)
#error "never use this file directly"
#endif

inline
x86vec::v8u16::v8u16(vector_type r) : base_type(r)
{
}

inline
x86vec::v8u16::v8u16(const base_type& r) : base_type(r)
{
}

inline
x86vec::v8u16::v8u16(element_type p00, element_type p01,
                     element_type p02, element_type p03,
                     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type(_mm_set_epi16(p07, p06, p05, p04,
                                  p03, p02, p01, p00))
{
}

inline
x86vec::v8u16::v8u16(element_type r)
        : base_type(_mm_set1_epi16(r))
{
}

inline
x86vec::v8u16::v8u16(x86vec::v8u16::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_epi16(r) : _mm_cvtsi32_si128(r))
{
}

inline
x86vec::v8u16::v8u16(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_epi16(* (r())))
{
}

inline
x86vec::v8u16::v8u16(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_si128(m128i_ptr::make(r())) :
                    _mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v8u16::v8u16(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v8u16::v8u16(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_si128(m128i_ptr::make(r())))
{
}

inline
x86vec::v8u16&
x86vec::operator|= (v8u16& a, const v8u16& b)
{
        a = _mm_or_si128(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator&= (v8u16& a, const v8u16& b)
{
        a = _mm_and_si128(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator^= (v8u16& a, const v8u16& b)
{
        a = _mm_xor_si128(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator+= (v8u16& a, const v8u16& b)
{
        a = _mm_add_epi16(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator-= (v8u16& a, const v8u16& b)
{
        a = _mm_sub_epi16(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator*= (v8u16& a, const v8u16& b)
{
        a = _mm_mullo_epi16(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator/=(v8u16& a, const v8u16& b)
{
        a= impl::div_u16::v(a(), b());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator%=(v8u16& a, const v8u16& b)
{
        v8u16 q(a/b);
        a = cftal::remainder(a, b, q);
        return a;
}

template <unsigned _P>
inline
x86vec::v8u16&
x86vec::operator<<= (v8u16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsllw_const<val>::v(a());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator<<= (v8u16& a, uint32_t b)
{
        __m128i s = _mm_cvtsi32_si128(b);
        a = impl::vpsllw::v(a(), s);
        return a;
}

template <unsigned _P>
inline
x86vec::v8u16
x86vec::operator<< (const v8u16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsllw_const<val>::v(a());
}

inline
x86vec::v8u16
x86vec::operator<< (const v8u16& a, uint32_t b)
{
        __m128i s = _mm_cvtsi32_si128(b);
        return impl::vpsllw::v(a(), s);
}


template <unsigned _P>
inline
x86vec::v8u16&
x86vec::operator>>= (v8u16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        a = impl::vpsrlw_const<val>::v(a());
        return a;
}

inline
x86vec::v8u16&
x86vec::operator>>= (v8u16& a, uint32_t r)
{
        __m128i s = _mm_cvtsi32_si128(r);
        a = impl::vpsrlw::v(a(), s);
        return a;
}

template <unsigned _P>
inline
x86vec::v8u16
x86vec::operator>> (const v8u16& a, const const_u32< _P >& b)
{
        const int val = b.val;
        return impl::vpsrlw_const<val>::v(a());
}

inline
x86vec::v8u16
x86vec::operator>> (const v8u16& a, uint32_t r)
{
        __m128i s = _mm_cvtsi32_si128(r);
        return impl::vpsrlw::v(a(), s);
}


inline
x86vec::v8u16&
x86vec::operator++(v8u16& a)
{
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_add_epi16(a(), one);
        return a;
}

inline
x86vec::v8u16
x86vec::operator++ (v8u16& a, int)
{
        v8u16 t(a);
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_add_epi16(a(), one);
        return t;
}

inline
x86vec::v8u16&
x86vec::operator--(v8u16& a)
{
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_sub_epi16(a(), one);
        return a;
}

inline
x86vec::v8u16
x86vec::operator-- (v8u16& a, int)
{
        v8u16 t(a);
        const __m128i one = const8_u16< 1, 1, 1, 1, 1, 1, 1, 1>::iv();
        a = _mm_sub_epi16(a(), one);
        return a;
}

inline
x86vec::v8u16
x86vec::operator-(const v8u16& a)
{
        const __m128i zero = impl::make_zero_int::v();
        return _mm_sub_epi16(zero, a());
}

inline
const x86vec::v8u16&
x86vec::operator+(const v8u16& a)
{
	return a;
}

inline
x86vec::v8u16
x86vec::operator~(const v8u16& a)
{
        const __m128i all_set = const4_u32 < -1, -1, -1, -1 >::iv();
        return _mm_xor_si128(a(), all_set);
}

inline
x86vec::v8u16
x86vec::operator!(const v8u16& a)
{
        const __m128i msk = impl::make_zero_int::v();
        return _mm_cmpeq_epi16(a(), msk);
}

inline
x86vec::v8u16 x86vec::operator| (const v8u16& a, const v8u16& b)
{
        return _mm_or_si128(a(), b());
}

inline
x86vec::v8u16 x86vec::operator|| (const v8u16& a, const v8u16& b)
{
        return a | b;
}

inline
x86vec::v8u16 x86vec::operator& (const v8u16& a, const v8u16& b)
{
        return _mm_and_si128(a(), b());
}

inline
x86vec::v8u16 x86vec::operator&& (const v8u16& a, const v8u16& b)
{
        return a & b;
}

inline
x86vec::v8u16 x86vec::operator^(const v8u16& a, const v8u16& b)
{
        return _mm_xor_si128(a(), b());
}

inline
x86vec::v8u16 x86vec::operator+ (const v8u16& a, const v8u16& b)
{
        return _mm_add_epi16(a(), b());
}

inline
x86vec::v8u16 x86vec::operator- (const v8u16& a, const v8u16& b)
{
        return _mm_sub_epi16(a(), b());
}

inline
x86vec::v8u16 x86vec::operator* (const v8u16& a, const v8u16& b)
{
        return _mm_mullo_epi16(a(), b());
}

inline
x86vec::v8u16
x86vec::operator/(const v8u16& a, const v8u16& b)
{
        return impl::div_u16::v(a(), b());
}

inline
x86vec::v8u16
x86vec::operator%(const v8u16& a, const v8u16& b)
{
        return cftal::remainder(a, b, a/b);
}

inline
x86vec::v8u16 x86vec::operator< (const v8u16& a, const v8u16& b)
{
	v8u16 ta(a ^ v_sign_s16_msk::iv());
	v8u16 tb(b ^ v_sign_s16_msk::iv());
        return _mm_cmpgt_epi16(tb(), ta());
}

inline
x86vec::v8u16 x86vec::operator<= (const v8u16& a, const v8u16& b)
{
	return ~(b > a);
}

inline
x86vec::v8u16 x86vec::operator== (const v8u16& a, const v8u16& b)
{
        return _mm_cmpeq_epi16(a(), b());
}

inline
x86vec::v8u16 x86vec::operator!= (const v8u16& a, const v8u16& b)
{
        return ~(a == b);
}

inline
x86vec::v8u16 x86vec::operator>= (const v8u16& a, const v8u16& b)
{
	return ~(a < b);
}

inline
x86vec::v8u16 x86vec::operator> (const v8u16& a, const v8u16& b)
{
	v8u16 ta(a ^ v_sign_s16_msk::iv());
	v8u16 tb(b ^ v_sign_s16_msk::iv());
        return _mm_cmpgt_epi16(ta(), tb());
}

inline
x86vec::v8u16 x86vec::max(const v8u16& a, const v8u16& b)
{
#if defined (__SSE4_1__)
	return _mm_max_epu16(a(), b());
#else
	// add 0x8000
	__m128i a0= _mm_xor_si128(a(), v_sign_s16_msk::iv());           
	// add 0x8000
	__m128i b0= _mm_xor_si128(b(), v_sign_s16_msk::iv());       
	// signed max
	__m128i m0= _mm_max_epi16(a1,b1);               
	// sub 0x8000
	return  _mm_xor_si128(m0,v_sign_s16_msk::iv());
#endif
}

inline
x86vec::v8u16 x86vec::min(const v8u16& a, const v8u16& b)
{
#if defined (__SSE4_1__)
        return v8u16(_mm_min_epu16(a(), b()));
#else
	// add 0x8000
	__m128i a0= _mm_xor_si128(a(), v_sign_s16_msk::iv());           
	// add 0x8000
	__m128i b0= _mm_xor_si128(b(), v_sign_s16_msk::iv());       
	// signed min
	__m128i m0= _mm_min_epi16(a1,b1);               
	// sub 0x8000
	return  _mm_xor_si128(m0,v_sign_s16_msk::iv());
#endif
}

inline
x86vec::v8u16 x86vec::mulh(const v8u16& a, const v8u16& b)
{
	return _mm_mulhi_epu16(a(), b());
}

template < bool _P0, bool _P1, bool _P2, bool _P3,
	   bool _P4, bool _P5, bool _P6, bool _P7 >
inline
x86vec::v8u16 x86vec::select(const v8u16& a, const v8u16& b)
{
        return select_u16 <
		_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7 > (a(), b());
}

inline
x86vec::v8u16 x86vec::select(const v8u16& msk,
                             const v8u16& on_true,
                             const v8u16& on_false)
{
        return select(msk(), on_true(), on_false());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >
inline
x86vec::v8u16 x86vec::permute(const v8u16& a)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >
inline
x86vec::v8u16 x86vec::permute(const v8u16& a, const v8u16& b)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a(), b());
}

// Local variables:
// mode: c++
// end:
#endif
