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
x86vec::v4f32::v4f32(x86vec::v4f32::element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm_set1_ps(r) : _mm_set_ss(r))
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
        a = _mm_add_ps(a(), b());
        return a;
}

inline
x86vec::v4f32&
x86vec::operator-= (v4f32& a, const v4f32& b)
{
        a = _mm_sub_ps(a(), b());
        return a;
}

inline
x86vec::v4f32&
x86vec::operator*= (v4f32& a, const v4f32& b)
{
        a = _mm_mul_ps(a(), b());
        return a;
}

inline
x86vec::v4f32&
x86vec::operator/=(v4f32& a, const v4f32& b)
{
        a= _mm_div_ps(a(), b());
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
x86vec::v4f32 x86vec::operator+ (const v4f32& a, const v4f32& b)
{
        return _mm_add_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator- (const v4f32& a, const v4f32& b)
{
        return _mm_sub_ps(a(), b());
}

inline
x86vec::v4f32 x86vec::operator* (const v4f32& a, const v4f32& b)
{
        return _mm_mul_ps(a(), b());
}

inline
x86vec::v4f32
x86vec::operator/(const v4f32& a, const v4f32& b)
{
        return _mm_div_ps(a(), b());
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
