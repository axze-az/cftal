#if !defined (__X86VEC_V4F64_INL_H__)
#define __X86VEC_V4F64_INL_H__ 1

#if !defined (__X86VEC_FVEC_H__)
#include <cftal/x86vec_fvec.h>
#error "never use this file directly"
#endif

inline
x86vec::v4f64::v4f64(vector_type r) : base_type(r)
{
}

inline
x86vec::v4f64::v4f64(const base_type& r) : base_type(r)
{
}

inline
x86vec::v4f64::v4f64(element_type p00, element_type p01,
		     element_type p02, element_type p03)
        : base_type(_mm256_set_pd(p03, p02, p01, p00))
{
}

inline
x86vec::v4f64::v4f64(element_type r)
        : base_type(_mm256_set1_pd(r))
{
}

inline
x86vec::v4f64::v4f64(element_type r, bool broadcast)
        : base_type(broadcast ? 
		    _mm256_set1_pd(r) : 
		    _mm256_castpd128_pd256(_mm_set_sd(r)))
{
}

inline
x86vec::v4f64::v4f64(const v2f64&l)
        : base_type(impl::vinsertf128<1>::v(as<__m256d>(l()),
					    _mm_setzero_pd()))
{
}

inline
x86vec::v4f64::v4f64(const v2f64&l, const v2f64& h)
        : base_type(impl::vinsertf128<1>::v(as<__m256d>(l()),
					    h()))
{
}


template <template <class _V> class _OP, class _L, class _R>
inline
x86vec::v4f64::v4f64(const expr<_OP<v4f64>, _L, _R>& r)
	: base_type(eval(r)())
{
}

inline
x86vec::v4f64::v4f64(const mem::addr_bcast<element_type>& r)
        : base_type(_mm256_set1_pd(* (r())))
{
}

inline
x86vec::v4f64::v4f64(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<32>::ptr(r()) ?
                    _mm256_load_pd(r()) :
                    _mm256_loadu_pd(r()))
{
}

inline
x86vec::v4f64::v4f64(const mem::aligned::addr<element_type>& r)
        : base_type(_mm256_load_pd(r()))
{
}

inline
x86vec::v4f64::v4f64(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm256_loadu_pd(r()))
{
}

inline
x86vec::masked_vec<x86vec::v4f64>
x86vec::v4f64::operator()(const mask<v4f64>& m) 
{
	return masked_vec<v4f64>(*this, m);
}

inline
x86vec::v4f64
x86vec::ops::add<x86vec::v4f64>::v(const v4f64& a, const v4f64& b)
{
	return _mm256_add_pd(a(), b());
}

inline
x86vec::v4f64
x86vec::ops::sub<x86vec::v4f64>::v(const v4f64& a, const v4f64& b)
{
	return _mm256_sub_pd(a(), b());
}

inline
x86vec::v4f64
x86vec::ops::mul<x86vec::v4f64>::v(const v4f64& a, const v4f64& b)
{
	return _mm256_mul_pd(a(), b());
}

inline
x86vec::v4f64
x86vec::ops::div<x86vec::v4f64>::v(const v4f64& a, const v4f64& b)
{
	return _mm256_div_pd(a(), b());
}

inline
x86vec::v4f64 x86vec::ops::fma<x86vec::v4f64>::
v(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__) 
	return _mm256_macc_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fmadd_pd(a(), b(), c());
#else
	return _mm256_add_pd(_mm256_mul_pd(a(), b()), c());
#endif
}

inline
x86vec::v4f64 x86vec::ops::fms<x86vec::v4f64>::
v(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
	return _mm256_msub_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fmsub_pd(a(), b(), c());
#else
	return _mm256_sub_pd(_mm256_mul_pd(a(), b()), c());
#endif
}

inline
x86vec::v4f64 x86vec::ops::fnma<x86vec::v4f64>::
v(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
	return _mm256_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fnmadd_pd(a(), b(), c());
#else
	return _mm256_sub_pd(c(), _mm256_mul_pd(a(), b()));
#endif
}

inline
x86vec::v4f64&
x86vec::operator|= (v4f64& a, const v4f64& b)
{
        a = _mm256_or_pd(a(), b());
        return a;
}

inline
x86vec::v4f64&
x86vec::operator&= (v4f64& a, const v4f64& b)
{
        a = _mm256_and_pd(a(), b());
        return a;
}

inline
x86vec::v4f64&
x86vec::operator^= (v4f64& a, const v4f64& b)
{
        a = _mm256_xor_pd(a(), b());
        return a;
}


inline
x86vec::v4f64&
x86vec::operator++(v4f64& a)
{
        const __m256d one = _mm256_set1_pd(1.0);
        a = _mm256_add_pd(a(), one);
        return a;
}

inline
x86vec::v4f64
x86vec::operator++ (v4f64& a, int)
{
        v4f64 t(a);
        const __m256d one = _mm256_set1_pd(1.0);
        a = _mm256_add_pd(a(), one);
        return t;
}

inline
x86vec::v4f64&
x86vec::operator--(v4f64& a)
{
        const __m256d one = _mm256_set1_pd(1.0);
        a = _mm256_add_pd(a(), one);
        return a;
}

inline
x86vec::v4f64
x86vec::operator-- (v4f64& a, int)
{
        v4f64 t(a);
        const __m256d one = _mm256_set1_pd(1.0);
        a = _mm256_add_pd(a(), one);
        return t;
}

inline
x86vec::v4f64
x86vec::operator-(const v4f64& a)
{
	const __m256d msk= v_sign_v4f64_msk::dv();
        return _mm256_xor_pd(a(), msk);
}

inline
const x86vec::v4f64&
x86vec::operator+(const v4f64& a)
{
	return a;
}

inline
x86vec::v4f64
x86vec::operator~(const v4f64& a)
{
        const __m256d all_set = const_v8u32 < -1, -1, -1, -1,
					      -1, -1, -1, -1>::dv();
        return _mm256_xor_pd(a(), all_set);
}

inline
x86vec::v4f64
x86vec::operator!(const v4f64& a)
{
        const __m256d msk = impl::make_zero_v4f64::v();
        return _mm256_cmp_pd(a(), msk, _CMP_EQ_OQ);
}

inline
x86vec::v4f64 x86vec::operator| (const v4f64& a, const v4f64& b)
{
        return _mm256_or_pd(a(), b());
}

inline
x86vec::v4f64 x86vec::operator|| (const v4f64& a, const v4f64& b)
{
        return a | b;
}

inline
x86vec::v4f64 x86vec::operator& (const v4f64& a, const v4f64& b)
{
        return _mm256_and_pd(a(), b());
}

inline
x86vec::v4f64 x86vec::operator&& (const v4f64& a, const v4f64& b)
{
        return a & b;
}

inline
x86vec::v4f64 x86vec::operator^(const v4f64& a, const v4f64& b)
{
        return _mm256_xor_pd(a(), b());
}


inline
x86vec::v4f64 x86vec::operator< (const v4f64& a, const v4f64& b)
{
	return _mm256_cmp_pd(a(), b(), _CMP_LT_OS);
}

inline
x86vec::v4f64 x86vec::operator<= (const v4f64& a, const v4f64& b)
{
	return _mm256_cmp_pd(a(), b(), _CMP_LE_OS);
}

inline
x86vec::v4f64 x86vec::operator== (const v4f64& a, const v4f64& b)
{
        return _mm256_cmp_pd(a(), b(), _CMP_EQ_OQ);
}

inline
x86vec::v4f64 x86vec::operator!= (const v4f64& a, const v4f64& b)
{
        return _mm256_cmp_pd(a(), b(), _CMP_UNORD_Q);
}

inline
x86vec::v4f64 x86vec::operator>= (const v4f64& a, const v4f64& b)
{
	return _mm256_cmp_pd(a(), b(), _CMP_GE_OS);
}

inline
x86vec::v4f64 x86vec::operator> (const v4f64& a, const v4f64& b)
{
        return _mm256_cmp_pd(a(), b(), _CMP_GT_OS);
}

inline
x86vec::v2f64 x86vec::low_half(const v4f64& v)
{
	return _mm256_extractf128_pd(v(), 0);
}

inline
x86vec::v2f64 x86vec::high_half(const v4f64& v)
{
	return _mm256_extractf128_pd(v(), 1);
}

inline
bool x86vec::all_signs(const v4f64& a)
{
        return all_signs_f64(a());
}

inline
bool x86vec::both_signs(const v4f64& a)
{
        return both_signs_f64(a());
}

inline
bool x86vec::no_signs(const v4f64& a)
{
        return no_signs_f64(a());
}

inline
unsigned x86vec::read_signs(const v4f64& a)
{
        return read_signs_f64(a());
}

inline
x86vec::v4f64 x86vec::max(const v4f64& a, const v4f64& b)
{
	return _mm256_max_pd(a(), b());
}

inline
x86vec::v4f64 x86vec::min(const v4f64& a, const v4f64& b)
{
	return _mm256_max_pd(a(), b());
}

inline
x86vec::v4f64 x86vec::abs(const v4f64& a)
{
	const __m256d msk= v_not_sign_v4f64_msk::dv();
	return _mm256_and_pd(a(), msk);
}

inline
x86vec::v4f64 x86vec::fabs(const v4f64& a)
{
	const __m256d msk= v_not_sign_v4f64_msk::dv();
	return _mm256_and_pd(a(), msk);
}

inline
x86vec::v4f64 x86vec::sqrt(const v4f64& a)
{
	return _mm256_sqrt_pd(a());
}

inline
x86vec::v4f64 x86vec::hypot(const v4f64& a, const v4f64& b)
{
	v4f64 abs_a(fabs(a)), abs_b(fabs(b));
	v4f64 x(max(abs_a, abs_b)), y(min(abs_a, abs_b));
	v4f64 t(y/x);
	return x* sqrt(1.0 * t * t);
}

inline
x86vec::v4f64 x86vec::rsqrt(const v4f64& a)
{
	return 1.0/sqrt(a);
}

inline
x86vec::v4f64 x86vec::native_rsqrt(const v4f64& a)
{
	return rsqrt(a);
}

inline
x86vec::v4f64 x86vec::impl::round(const v4f64& a, const rounding_mode::type m)
{
	v4f64 r;
	switch (m) {
	case rounding_mode::nearest:
		r= _mm256_round_pd(a(), 0);
		break;
	case rounding_mode::downward:
		r= _mm256_round_pd(a(), 1);
		break;
	case rounding_mode::upward:
		r= _mm256_round_pd(a(), 2);
		break;
	case rounding_mode::towardzero:
		r= _mm256_round_pd(a(), 3);
		break;
	case rounding_mode::current:
		r= _mm256_round_pd(a(), 4);
		break;
	}
	return r;

}

inline
x86vec::v4f64 x86vec::rint(const v4f64& a)
{
	return impl::round(a, impl::rounding_mode::nearest);
}

inline
x86vec::v4f64 x86vec::floor(const v4f64& a)
{
	return impl::round(a, impl::rounding_mode::downward);
}

inline
x86vec::v4f64 x86vec::ceil(const v4f64& a)
{
	return impl::round(a, impl::rounding_mode::upward);
}

inline
x86vec::v4f64 x86vec::trunc(const v4f64& a)
{
	return impl::round(a, impl::rounding_mode::towardzero);
}

inline
x86vec::v4f64 x86vec::andnot(const v4f64& x, const v4f64& y)
{
	return _mm256_andnot_pd(x(), y());
}

inline
x86vec::v4f64 x86vec::copysign(const v4f64& x, const v4f64& y)
{
	// return abs(x) * sgn(y)
	const v4f64 msk(v_not_sign_f64_msk::dv());
	v4f64 abs_x(x & msk);
	v4f64 sgn_y(andnot(msk, y));
	return abs_x | sgn_y;
}

inline
x86vec::v4f64 x86vec::mulsign(const v4f64& x, const v4f64& y)
{
	const v4f64 msk= v_sign_v4f64_msk::dv();
	v4f64 sgn_y = y & msk;
	return x ^ sgn_y;
}


inline
x86vec::v4f64 x86vec::isinf(const v4f64& x)
{
	// exponent = 0x7FF and significand ==0
	v4f64 absx(abs(x));
	return absx== v_exp_v4f64_msk::dv();
}

inline
x86vec::v4f64 x86vec::isnan(const v4f64& x)
{
	// exponent = 0x7FF and significand !=0
	// x != x  if x == NAN
	return x != x;
}

inline
x86vec::v4f64 x86vec::isfinite(const v4f64& x)
{
	return ~(isinf(x) | isnan(x));
}

inline
x86vec::v4f64 x86vec::fma(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
	return _mm256_macc_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fmadd_pd(a(), b(), c());
#else
	return impl::fma(a, b, c);
#endif	
}

inline
x86vec::v4f64 x86vec::fms(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
	return _mm256_msub_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fmsub_pd(a(), b(), c());
#else
	return impl::fma(a, b, -c);
#endif	
}

inline
x86vec::v4f64 x86vec::nfma(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
	return _mm256_nmacc_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fnmadd_pd(a(), b(), c());
#else
	return impl::fma(-a, b, c);
#endif	
}

inline
x86vec::v4f64 x86vec::nfms(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if defined (__FMA4__)
	return _mm256_nmsub_pd(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fnmsub_pd(a(), b(), c());
#else
	return impl::fma(-a, b, -c);
#endif	
}

inline
x86vec::v4f64 x86vec::mad(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if 1
	return a * b + c;
#else
#if defined (__FMA4__) || defined (__FMA__)
	return fma(a, b, c);
#else
	return a * b + c;
#endif
#endif
}

inline
x86vec::v4f64 x86vec::nmad(const v4f64& a, const v4f64& b, const v4f64& c)
{
#if 1
	return -(a * b) + c;
#else
#if defined (__FMA4__) || defined (__FMA__)
	return nfma(a, b, c);
#else
	return -(a * b) + c;
#endif
#endif
}

template < bool _P0, bool _P1, bool _P2, bool _P3>
inline
x86vec::v4f64 x86vec::select(const v4f64& a, const v4f64& b)
{
        return select_f64 <_P0, _P1, _P2, _P3> (a(), b());
}

inline
x86vec::v4f64 x86vec::select(const v4f64& msk,
                             const v4f64& on_true,
                             const v4f64& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
x86vec::v4f64 x86vec::permute(const v4f64& a)
{
        return perm_f64<_P0, _P1, _P2, _P3>(a());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
x86vec::v4f64 x86vec::permute(const v4f64& a, const v4f64& b)
{
        return perm_f64<_P0, _P1, _P2, _P3>(a(), b());
}

template <unsigned _I>
inline
x86vec::v4f64 x86vec::insert(const v4f64& a, typename v4f64::element_type v)
{
	return insert_f64<_I>(a(), v);
}

template <unsigned _I>
inline
x86vec::v4f64::element_type
x86vec::extract(const v4f64& a)
{
	return extract_f64<_I>(a());
}

#if 0
inline
x86vec::v4f64::element_type
x86vec::hadd(const v4f64& a)
{
	v4f64 t(a + permute<1,0>(a));
	v4f64::element_type r(extract<0>(t));
	return r;
}
#endif

// Local variables:
// mode: c++
// end:
#endif
