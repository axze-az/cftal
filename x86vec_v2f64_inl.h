#if !defined (__X86VEC_V2F64_INL_H__)
#define __X86VEC_V2F64_INL_H__ 1

#if !defined (__X86VEC_FVEC_H__)
#include <cftal/x86vec_fvec.h>
#error "never use this file directly"
#endif

inline
x86vec::v2f64::v2f64(vector_type r) : base_type(r)
{
}

inline
x86vec::v2f64::v2f64(const base_type& r) : base_type(r)
{
}

inline
x86vec::v2f64::v2f64(element_type p00, element_type p01)
        : base_type(_mm_set_pd(p01, p00))
{
}

inline
x86vec::v2f64::v2f64(element_type r)
        : base_type(_mm_set1_pd(r))
{
}

inline
x86vec::v2f64::v2f64(x86vec::v2f64::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_pd(r) : _mm_set_sd(r))
{
}

inline
x86vec::v2f64::v2f64(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_pd(* (r())))
{
}

inline
x86vec::v2f64::v2f64(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_pd(r()) :
                    _mm_loadu_pd(r()))
{
}

inline
x86vec::v2f64::v2f64(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_pd(r()))
{
}

inline
x86vec::v2f64::v2f64(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_pd(r()))
{
}

inline
x86vec::v2f64&
x86vec::operator|= (v2f64& a, const v2f64& b)
{
        a = _mm_or_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator&= (v2f64& a, const v2f64& b)
{
        a = _mm_and_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator^= (v2f64& a, const v2f64& b)
{
        a = _mm_xor_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator+= (v2f64& a, const v2f64& b)
{
        a = _mm_add_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator-= (v2f64& a, const v2f64& b)
{
        a = _mm_sub_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator*= (v2f64& a, const v2f64& b)
{
        a = _mm_mul_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator/=(v2f64& a, const v2f64& b)
{
        a= _mm_div_pd(a(), b());
        return a;
}

inline
x86vec::v2f64&
x86vec::operator++(v2f64& a)
{
        const __m128d one = _mm_set1_pd(1.0);
        a = _mm_add_pd(a(), one);
        return a;
}

inline
x86vec::v2f64
x86vec::operator++ (v2f64& a, int)
{
        v2f64 t(a);
        const __m128d one = _mm_set1_pd(1.0);
        a = _mm_add_pd(a(), one);
        return t;
}

inline
x86vec::v2f64&
x86vec::operator--(v2f64& a)
{
        const __m128d one = _mm_set1_pd(1.0);
        a = _mm_add_pd(a(), one);
        return a;
}

inline
x86vec::v2f64
x86vec::operator-- (v2f64& a, int)
{
        v2f64 t(a);
        const __m128d one = _mm_set1_pd(1.0);
        a = _mm_add_pd(a(), one);
        return t;
}

inline
x86vec::v2f64
x86vec::operator-(const v2f64& a)
{
	const __m128d msk= v_sign_f64_msk::dv();
        return _mm_xor_pd(a(), msk);
}

inline
const x86vec::v2f64&
x86vec::operator+(const v2f64& a)
{
	return a;
}

inline
x86vec::v2f64
x86vec::operator~(const v2f64& a)
{
        const __m128d all_set = const4_u32 < -1, -1, -1, -1 >::dv();
        return _mm_xor_pd(a(), all_set);
}

inline
x86vec::v2f64
x86vec::operator!(const v2f64& a)
{
        const __m128d msk = impl::make_zero_f64::v();
        return _mm_cmpeq_pd(a(), msk);
}

inline
x86vec::v2f64 x86vec::operator| (const v2f64& a, const v2f64& b)
{
        return _mm_or_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator|| (const v2f64& a, const v2f64& b)
{
        return a | b;
}

inline
x86vec::v2f64 x86vec::operator& (const v2f64& a, const v2f64& b)
{
        return _mm_and_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator&& (const v2f64& a, const v2f64& b)
{
        return a & b;
}

inline
x86vec::v2f64 x86vec::operator^(const v2f64& a, const v2f64& b)
{
        return _mm_xor_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator+ (const v2f64& a, const v2f64& b)
{
        return _mm_add_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator- (const v2f64& a, const v2f64& b)
{
        return _mm_sub_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator* (const v2f64& a, const v2f64& b)
{
        return _mm_mul_pd(a(), b());
}

inline
x86vec::v2f64
x86vec::operator/(const v2f64& a, const v2f64& b)
{
        return _mm_div_pd(a(), b());
}


inline
x86vec::v2f64 x86vec::operator< (const v2f64& a, const v2f64& b)
{
	return _mm_cmplt_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator<= (const v2f64& a, const v2f64& b)
{
	return _mm_cmple_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator== (const v2f64& a, const v2f64& b)
{
        return _mm_cmpeq_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator!= (const v2f64& a, const v2f64& b)
{
        return _mm_cmpneq_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator>= (const v2f64& a, const v2f64& b)
{
	return _mm_cmpge_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::operator> (const v2f64& a, const v2f64& b)
{
        return _mm_cmpgt_pd(a(), b());
}

inline
bool x86vec::all_signs(const v2f64& a)
{
        return all_signs_f64(a());
}

inline
bool x86vec::both_signs(const v2f64& a)
{
        return both_signs_f64(a());
}

inline
bool x86vec::no_signs(const v2f64& a)
{
        return no_signs_f64(a());
}

inline
x86vec::v2f64 x86vec::max(const v2f64& a, const v2f64& b)
{
	return _mm_max_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::min(const v2f64& a, const v2f64& b)
{
	return _mm_max_pd(a(), b());
}

inline
x86vec::v2f64 x86vec::abs(const v2f64& a)
{
	const __m128d msk= v_not_sign_f64_msk::dv();
	return _mm_and_pd(a(), msk);
}

inline
x86vec::v2f64 x86vec::sqrt(const v2f64& a)
{
	return _mm_sqrt_pd(a());
}

inline
x86vec::v2f64 x86vec::round(const v2f64& a, const rounding_mode m)
{
#if defined (__SSE4_1__)
	switch (m) {
	case rounding_mode::nearest:
		return _mm_round_pd(a(), 0);
	case rounding_mode::downward:
		return _mm_round_pd(a(), 1);
	case rounding_mode::upward:
		return _mm_round_pd(a(), 2);
	case rounding_mode::towardzero:
		return _mm_round_pd(a(), 3);
	}
#else
	std::uint32_t mxcsr=_mm_getcsr();
	std::uint32_t rmxcsr(mxcsr);
	rmxcsr &= ~(3<<13);
	switch (m) {
	case rounding_mode::nearest: //0
		break;
	case rounding_mode::downward:
		rmxcsr |= (1<<13);
		break;
	case rounding_mode::upward:
		rmxcsr |= (2<<13);
		break;
	case rounding_mode::towardzero:
		rmxcsr |= (2<<13);
		break;
	}
	if (mxcsr != rmxcsr)
		_mm_setcsr(rmxcsr);
	const __m128d sgn_msk=v_sign_f64_msk::dv();
	// (1023+52)<<(52-32) 0x43300000 = 2^52
	const __m128d magic= const4_u32<0, 0x43300000, 0, 0x43300000>::dv();
	__m128d sign = _mm_and_pd(a(), sgn_msk);
	__m128d sign_magic = _mm_or_pd(magic, sign);
	__m128d res = _mm_add_ps(a(), sign_magic);
	res = _mm_sub_ps(a(), sign_magic);
	if (mxcsr != rmxcsr)
		_mm_setcsr(mxcsr);
	return res;
#endif
}

inline
x86vec::v2f64 x86vec::rint(const v2f64& a)
{
	return round(a, rounding_mode::nearest);
}

inline
x86vec::v2f64 x86vec::floor(const v2f64& a)
{
	return round(a, rounding_mode::downward);
}

inline
x86vec::v2f64 x86vec::ceil(const v2f64& a)
{
	return round(a, rounding_mode::upward);
}

inline
x86vec::v2f64 x86vec::trunc(const v2f64& a)
{
	return round(a, rounding_mode::towardzero);
}

template < bool _P0, bool _P1>
inline
x86vec::v2f64 x86vec::select(const v2f64& a, const v2f64& b)
{
        return select_f64 <_P0, _P1> (a(), b());
}

inline
x86vec::v2f64 x86vec::select(const v2f64& msk,
                             const v2f64& on_true,
                             const v2f64& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1>
inline
x86vec::v2f64 x86vec::permute(const v2f64& a)
{
        return perm_f64<_P0, _P1>(a());
}

template <int _P0, int _P1>
inline
x86vec::v2f64 x86vec::permute(const v2f64& a, const v2f64& b)
{
        return perm_f64<_P0, _P1>(a(), b());
}

template <unsigned _I>
inline
x86vec::v2f64 x86vec::insert(const v2f64& a, typename v2f64::element_type v)
{
	return insert_f64<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v2f64::element_type
x86vec::extract(const v2f64& a)
{
	return extract_f64<_I>(a());
}

// Local variables:
// mode: c++
// end:
#endif
