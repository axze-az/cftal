#if !defined (__X86VEC_V4F32_INL_H__)
#define __X86VEC_V4F32_INL_H__ 1

#if !defined (__X86VEC_FVEC_H__)
#include <cftal/x86vec_fvec.h>
#error "never use this file directly"
#endif

inline
x86vec::v4f32::v4f32(vector_type r) : base_type(r)
{
}

inline
x86vec::v4f32::v4f32(const base_type& r) : base_type(r)
{
}

inline
x86vec::v4f32::v4f32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type(_mm_set_ps(p03, p02, p01, p00))
{
}

inline
x86vec::v4f32::v4f32(element_type r)
        : base_type(_mm_set1_ps(r))
{
}

inline
x86vec::v4f32::v4f32(element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_ps(r) : _mm_set_ss(r))
{
}

template <template <class _V> class _OP, class _L, class _R>
inline
x86vec::v4f32::v4f32(const expr<_OP<v4f32>, _L, _R>& r)
	: base_type(eval(r)())
{
}

inline
x86vec::v4f32::v4f32(const mem::addr_bcast<element_type>& r)
        : base_type(_mm_set1_ps(* (r())))
{
}

inline
x86vec::v4f32::v4f32(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm_load_ps(r()) :
                    _mm_loadu_ps(r()))
{
}

inline
x86vec::v4f32::v4f32(const mem::aligned::addr<element_type>& r)
        : base_type(_mm_load_ps(r()))
{
}

inline
x86vec::v4f32::v4f32(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm_loadu_ps(r()))
{
}

inline
x86vec::masked_vec<x86vec::v4f32>
x86vec::v4f32::operator()(const mask<v4f32>& m) 
{
	return masked_vec<v4f32>(*this, m);
}

inline
x86vec::v4f32
x86vec::ops::add<x86vec::v4f32>::v(const v4f32& a, const v4f32& b)
{
	return _mm_add_ps(a(), b());
}

inline
x86vec::v4f32
x86vec::ops::sub<x86vec::v4f32>::v(const v4f32& a, const v4f32& b)
{
	return _mm_sub_ps(a(), b());
}

inline
x86vec::v4f32
x86vec::ops::mul<x86vec::v4f32>::v(const v4f32& a, const v4f32& b)
{
	return _mm_mul_ps(a(), b());
}

inline
x86vec::v4f32
x86vec::ops::div<x86vec::v4f32>::v(const v4f32& a, const v4f32& b)
{
	return _mm_div_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::ops::fma<x86vec::v4f32>::
v(const v4f32& a, const v4f32& b, const v4f32& c)
{
#if defined (__FMA4__) 
	return _mm_macc_ps(a(), b(), c());
#elif defined (__FMA__)
	return _mm_fmadd_ps(a(), b(), c());
#else
	return _mm_add_ps(_mm_mul_ps(a(), b()), c());
#endif
}

inline
x86vec::v4f32 x86vec::ops::fms<x86vec::v4f32>::
v(const v4f32& a, const v4f32& b, const v4f32& c)
{
#if defined (__FMA4__)
	return _mm_msub_ps(a(), b(), c());
#elif defined (__FMA__)
	return _mm_fmsub_ps(a(), b(), c());
#else
	return _mm_sub_ps(_mm_mul_ps(a(), b()), c());
#endif
}

inline
x86vec::v4f32 x86vec::ops::fnma<x86vec::v4f32>::
v(const v4f32& a, const v4f32& b, const v4f32& c)
{
#if defined (__FMA4__)
	return _mm_nmacc_ps(a(), b(), c());
#elif defined (__FMA__)
	return _mm_fnmadd_ps(a(), b(), c());
#else
	return _mm_sub_ps(c(), _mm_mul_ps(a(), b()));
#endif
}

inline
x86vec::v4f32&
x86vec::operator|= (v4f32& a, const v4f32& b)
{
        a = _mm_or_ps(a(), b());
        return a;
}

inline
x86vec::v4f32&
x86vec::operator&= (v4f32& a, const v4f32& b)
{
        a = _mm_and_ps(a(), b());
        return a;
}

inline
x86vec::v4f32&
x86vec::operator^= (v4f32& a, const v4f32& b)
{
        a = _mm_xor_ps(a(), b());
        return a;
}

inline
x86vec::v4f32&
x86vec::operator+= (v4f32& a, const v4f32& b)
{
        a = a + b;
        return a;
}

inline
x86vec::v4f32&
x86vec::operator-= (v4f32& a, const v4f32& b)
{
        a = a - b;
        return a;
}

inline
x86vec::v4f32&
x86vec::operator*= (v4f32& a, const v4f32& b)
{
        a = a * b;
        return a;
}

inline
x86vec::v4f32&
x86vec::operator/=(v4f32& a, const v4f32& b)
{
        a= a / b;
        return a;
}

inline
x86vec::v4f32&
x86vec::operator++(v4f32& a)
{
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return a;
}

inline
x86vec::v4f32
x86vec::operator++ (v4f32& a, int)
{
        v4f32 t(a);
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return t;
}

inline
x86vec::v4f32&
x86vec::operator--(v4f32& a)
{
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return a;
}

inline
x86vec::v4f32
x86vec::operator-- (v4f32& a, int)
{
        v4f32 t(a);
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return t;
}

inline
x86vec::v4f32
x86vec::operator-(const v4f32& a)
{
        const __m128 msk= v_sign_f32_msk::fv();
        return _mm_xor_ps(a(), msk);
}

inline
const x86vec::v4f32&
x86vec::operator+(const v4f32& a)
{
        return a;
}

inline
x86vec::v4f32
x86vec::operator~(const v4f32& a)
{
        const __m128 all_set = const4_u32 < -1, -1, -1, -1 >::fv();
        return _mm_xor_ps(a(), all_set);
}

inline
x86vec::v4f32
x86vec::operator!(const v4f32& a)
{
        const __m128 msk = impl::make_zero_f32::v();
        return _mm_cmpeq_ps(a(), msk);
}

inline
x86vec::v4f32 x86vec::operator| (const v4f32& a, const v4f32& b)
{
        return _mm_or_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator|| (const v4f32& a, const v4f32& b)
{
        return a | b;
}

inline
x86vec::v4f32 x86vec::operator& (const v4f32& a, const v4f32& b)
{
        return _mm_and_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator&& (const v4f32& a, const v4f32& b)
{
        return a & b;
}

inline
x86vec::v4f32 x86vec::operator^(const v4f32& a, const v4f32& b)
{
        return _mm_xor_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator< (const v4f32& a, const v4f32& b)
{
        return _mm_cmplt_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator<= (const v4f32& a, const v4f32& b)
{
        return _mm_cmple_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator== (const v4f32& a, const v4f32& b)
{
        return _mm_cmpeq_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator!= (const v4f32& a, const v4f32& b)
{
        return _mm_cmpneq_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator>= (const v4f32& a, const v4f32& b)
{
        return _mm_cmpge_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator> (const v4f32& a, const v4f32& b)
{
        return _mm_cmpgt_ps(a(), b());
}

inline
bool x86vec::all_signs(const v4f32& a)
{
        return all_signs_f32(a());
}

inline
bool x86vec::both_signs(const v4f32& a)
{
        return both_signs_f32(a());
}

inline
bool x86vec::no_signs(const v4f32& a)
{
        return no_signs_f32(a());
}

inline
x86vec::v4f32 x86vec::max(const v4f32& a, const v4f32& b)
{
        return _mm_max_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::min(const v4f32& a, const v4f32& b)
{
        return _mm_max_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::abs(const v4f32& a)
{
        const __m128 msk= v_not_sign_f32_msk::fv();
        return _mm_and_ps(a(), msk);
}

inline
x86vec::v4f32 x86vec::sqrt(const v4f32& a)
{
        return _mm_sqrt_ps(a());
}

inline
x86vec::v4f32 x86vec::impl::round(const v4f32& a, const rounding_mode::type m)
{
#if defined (__SSE4_1__)
	v4f32 r;
        switch (m) {
        case rounding_mode::nearest:
                r= _mm_round_ps(a(), 0);
		break;
        case rounding_mode::downward:
                r= _mm_round_ps(a(), 1);
		break;
        case rounding_mode::upward:
                r= _mm_round_ps(a(), 2);
		break;
        case rounding_mode::towardzero:
                r= _mm_round_ps(a(), 3);
		break;
        case rounding_mode::current:
                r= _mm_round_ps(a(), 4);
		break;
        }
	return r;
#else
	uint32_t mxcsr=0;
	uint32_t rmxcsr=0;
	if (m != rounding_mode::current) {
		mxcsr = _mm_getcsr();
		rmxcsr= mxcsr;
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
			rmxcsr |= (3<<13);
			break;
		default:
			break; // keep the compiler happy
		}
		if (unlikely(mxcsr != rmxcsr))
			_mm_setcsr(rmxcsr);
	}
        const __m128 sgn_msk= v_sign_f32_msk::fv();
	// (127+23)<< 23 = 0x4B000000 = 2^23
        const __m128 magic= const4_u32<0x4B000000, 0x4B000000,
                                       0x4B000000, 0x4B000000>::fv();
        __m128 sign = _mm_and_ps(a(), sgn_msk);
        __m128 sign_magic = _mm_or_ps(magic, sign);
	__m128 res= _mm_add_ps(a(), sign_magic);
	res = _mm_sub_ps(a(), sign_magic);
	if (mxcsr != rmxcsr)
		_mm_setcsr(mxcsr);
	return res;
#endif
}

inline
x86vec::v4f32 x86vec::rint(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::nearest);
}

inline
x86vec::v4f32 x86vec::floor(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::downward);
}

inline
x86vec::v4f32 x86vec::ceil(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::upward);
}

inline
x86vec::v4f32 x86vec::trunc(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::towardzero);
}

inline
x86vec::v4f32 x86vec::andnot(const v4f32& x, const v4f32& y)
{
	return _mm_andnot_ps(x(), y());
}

inline
x86vec::v4f32 x86vec::copysign(const v4f32& x, const v4f32& y)
{
	// return abs(x) * sgn(y)
	const v4f32 msk(v_not_sign_f32_msk::fv());
	v4f32 abs_x(x & msk);
	v4f32 sgn_y(andnot(msk, y));
	return abs_x | sgn_y;
}

inline
x86vec::v4f32 x86vec::mulsign(const v4f32& x, const v4f32& y)
{
	const v4f32 msk= v_sign_f32_msk::fv();
	v4f32 sgn_y = y & msk;
	return x ^ sgn_y;
}

inline
x86vec::v4f32 x86vec::isinf(const v4f32& x)
{
	// exponent = 0xFF and significand ==0
	v4f32 absx(abs(x));
	return absx == v_exp_f32_msk::fv();
}

inline
x86vec::v4f32 x86vec::isnan(const v4f32& x)
{
	// exponent = 0xff and significand !=0
	// x == x if x != NAN
	// x != x if x == NAN
	return x != x;
}
inline
x86vec::v4f32 x86vec::isfinite(const v4f32& x)
{
	// exponent != 0xFF
	v4u32 xi(as<v4u32>(x));
	const v4u32 msk=v_exp_f32_msk::iv();
	v4u32 res((xi & msk) != msk);
	return as<v4f32>(res);
}


template < bool _P0, bool _P1, bool _P2, bool _P3 >
inline
x86vec::v4f32 x86vec::select(const v4f32& a, const v4f32& b)
{
        return select_f32 <_P0, _P1, _P2, _P3> (a(), b());
}

inline
x86vec::v4f32 x86vec::select(const v4f32& msk,
                             const v4f32& on_true,
                             const v4f32& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1, int _P2, int _P3>
inline
x86vec::v4f32 x86vec::permute(const v4f32& a)
{
        return perm_f32<_P0, _P1, _P2, _P3>(a());
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
x86vec::v4f32 x86vec::permute(const v4f32& a, const v4f32& b)
{
        return perm_f32<_P0, _P1, _P2, _P3>(a(), b());
}

template <unsigned _I>
inline
x86vec::v4f32 x86vec::insert(const v4f32& a, typename v4f32::element_type v)
{
        return insert_f32<_I>(a(), v);
}

template <unsigned _I>
inline
typename x86vec::v4f32::element_type
x86vec::extract(const v4f32& a)
{
        return extract_f32<_I>(a());
}

// Local variables:
// mode: c++
// end:
#endif
