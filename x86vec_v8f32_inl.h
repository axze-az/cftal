#if !defined (__X86VEC_V8F32_INL_H__)
#define __X86VEC_V8F32_INL_H__ 1

#if !defined (__X86VEC_FVEC_H__)
#include <cftal/x86vec_fvec.h>
#error "never use this file directly"
#endif

#if !defined (__AVX__)

inline
x86vec::v8f32::v8f32(const v4f32& lh, const v4f32& hh)
	: _l(lh), _h(hh)
{
}

inline
x86vec::v8f32::v8f32(element_type p00, element_type p01,
                     element_type p02, element_type p03,
		     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : _l(p00, p01, p02, p03), _h(p04, p05, p06, p07)
{
}

inline
x86vec::v8f32::v8f32(element_type r)
        : _l(r), _h(r)
{
}

inline
x86vec::v8f32::v8f32(element_type r, bool broadcast)
        : _l(r, broadcast), _h( broadcast ? r : 0.0)
{
}

template <template <class _V> class _OP, class _L, class _R>
inline
x86vec::v8f32::v8f32(const expr<_OP<v8f32>, _L, _R>& r)
	: _l(low_half(eval(r))), _h(high_half(eval(r)))
{
}

inline
x86vec::v8f32::v8f32(const mem::addr_bcast<element_type>& r)
        : _l(r), _h(r)
{
}

inline
x86vec::v8f32::v8f32(const mem::addr<element_type>& r)
        : _l(r), _h(mem::addr<element_type>(r()+4))
{
}

inline
x86vec::v8f32::v8f32(const mem::aligned::addr<element_type>& r)
	: _l(r), _h(mem::aligned::addr<element_type>(r()+4))
{
}

inline
x86vec::v8f32::v8f32(const mem::unaligned::addr<element_type>& r)
	: _l(r), _h(mem::unaligned::addr<element_type>(r()+4))
{
}

inline
x86vec::masked_vec<x86vec::v8f32>
x86vec::v8f32::operator()(const mask<v8f32>& m) 
{
	return masked_vec<v8f32>(*this, m);
}

inline
x86vec::v8f32
x86vec::ops::add<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(al + bl, ah + bh);
}

inline
x86vec::v8f32
x86vec::ops::sub<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(al - bl, ah - bh);
}

inline
x86vec::v8f32
x86vec::ops::mul<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(al * bl, ah * bh);
}

inline
x86vec::v8f32
x86vec::ops::div<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(al / bl, ah / bh);
}

inline
x86vec::v8f32 x86vec::ops::fma<x86vec::v8f32>::
v(const v8f32& a, const v8f32& b, const v8f32& c)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	v4f32 cl = low_half(c);
	v4f32 ch = high_half(c);
	return v8f32(al * bl + cl, ah * bh *ch);
}

inline
x86vec::v8f32 x86vec::ops::fms<x86vec::v8f32>::
v(const v8f32& a, const v8f32& b, const v8f32& c)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	v4f32 cl = low_half(c);
	v4f32 ch = high_half(c);
	return v8f32(al * bl - cl, ah * bh - ch);
}

inline
x86vec::v8f32 x86vec::ops::fnma<x86vec::v8f32>::
v(const v8f32& a, const v8f32& b, const v8f32& c)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	v4f32 cl = low_half(c);
	v4f32 ch = high_half(c);
	return v8f32(cl - al * bl, ch - ah * bh);
}

inline
x86vec::v8f32&
x86vec::operator|= (v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	a = v8f32( al | bl, ah | bh);
        return a;
}

inline
x86vec::v8f32&
x86vec::operator&= (v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	a = v8f32( al & bl, ah & bh);
        return a;
}

inline
x86vec::v8f32&
x86vec::operator^= (v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	a = v8f32( al & bl, ah & bh);
        return a;
}

inline
x86vec::v8f32&
x86vec::operator++(v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	++al;
	++ah;
	a = v8f32(al, ah);
        return a;
}

inline
x86vec::v8f32
x86vec::operator++ (v8f32& a, int)
{
        v8f32 t(a);
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	++al;
	++ah;
	a = v8f32(al, ah);
        return t;
}

inline
x86vec::v8f32&
x86vec::operator--(v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	--al;
	--ah;
	a = v8f32(al, ah);
        return a;
}

inline
x86vec::v8f32
x86vec::operator-- (v8f32& a, int)
{
        v8f32 t(a);
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	--al;
	--ah;
	a = v8f32(al, ah);
        return t;
}

inline
x86vec::v8f32
x86vec::operator-(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(-al, -ah);
}

inline
const x86vec::v8f32&
x86vec::operator+(const v8f32& a)
{
        return a;
}

inline
x86vec::v8f32
x86vec::operator~(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(~al, ~ah);
}

inline
x86vec::v8f32
x86vec::operator!(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(!al, !ah);
}

inline
x86vec::v8f32 x86vec::operator| (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al | bl, ah | bh);
}

inline
x86vec::v8f32 x86vec::operator|| (const v8f32& a, const v8f32& b)
{
        return a | b;
}

inline
x86vec::v8f32 x86vec::operator& (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al & bl, ah & bh);
}

inline
x86vec::v8f32 x86vec::operator&& (const v8f32& a, const v8f32& b)
{
        return a & b;
}

inline
x86vec::v8f32 x86vec::operator^(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al ^ bl, ah ^ bh);
}

inline
x86vec::v8f32 x86vec::operator< (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al < bl, ah < bh);
}

inline
x86vec::v8f32 x86vec::operator<= (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al <= bl, ah <= bh);
}

inline
x86vec::v8f32 x86vec::operator== (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al == bl, ah == bh);
}

inline
x86vec::v8f32 x86vec::operator!= (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al != bl, ah != bh);
}

inline
x86vec::v8f32 x86vec::operator>= (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al >= bl, ah >= bh);
}

inline
x86vec::v8f32 x86vec::operator> (const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32( al > bl, ah > bh);
}

inline
x86vec::v4f32 x86vec::low_half(const v8f32& v)
{
	return v._l;
}

inline
x86vec::v4f32 x86vec::high_half(const v8f32& v)
{
	return v._h;
}

inline
bool x86vec::all_signs(const v8f32& a)
{
	bool b0(all_signs(low_half(a)));
	bool b1(all_signs(high_half(a)));
	return b0 & b1;
}

inline
bool x86vec::both_signs(const v8f32& a)
{
	bool b0(both_signs(low_half(a)));
	bool b1(both_signs(high_half(a)));
	return b0 | b1;
}

inline
bool x86vec::no_signs(const v8f32& a)
{
	bool b0(no_signs(low_half(a)));
	bool b1(no_signs(high_half(a)));
	return b0 & b1;
}

inline
unsigned x86vec::read_signs(const v8f32& a)
{
	unsigned s0(read_signs(low_half(a)));
	unsigned s1(read_signs(high_half(a)));
	return (s1<<4)|s0;
}

inline
x86vec::v8f32 x86vec::max(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(max(al, bl), max(ah, bh));
}

inline
x86vec::v8f32 x86vec::min(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(min(al, bl), min(ah, bh));
}

inline
x86vec::v8f32 x86vec::abs(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(abs(al), abs(ah));
}

inline
x86vec::v8f32 x86vec::fabs(const v8f32& a)
{
	return abs(a);
}

inline
x86vec::v8f32 x86vec::sqrt(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(sqrt(al), sqrt(ah));
}

inline
x86vec::v8f32 
x86vec::rcp(const v8f32& a)
{
	return 1.0f/a;
}

inline
x86vec::v8f32
x86vec::native_rcp(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(native_rcp(al), native_rcp(ah));
}

inline
x86vec::v8f32
x86vec::rsqrt(const v8f32& a)
{
	return 1.0f/sqrt(a);
}

inline 
x86vec::v8f32
x86vec::native_rsqrt(const v8f32& a)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(native_rsqrt(al), native_rsqrt(ah));
}

inline
x86vec::v8f32 x86vec::impl::round(const v8f32& a, const rounding_mode::type m)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	return v8f32(round(al, m), round(ah, m));
}

inline
x86vec::v8f32 x86vec::rint(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::nearest);
}

inline
x86vec::v8f32 x86vec::floor(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::downward);
}

inline
x86vec::v8f32 x86vec::ceil(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::upward);
}

inline
x86vec::v8f32 x86vec::trunc(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::towardzero);
}

inline
x86vec::v8f32 x86vec::andnot(const v8f32& x, const v8f32& y)
{
	v4f32 xl = low_half(x);
	v4f32 xh = high_half(x);
	v4f32 yl = low_half(y);
	v4f32 yh = high_half(y);
	return v8f32(andnot(xl, yl), andnot(xh, yh));

}

inline
x86vec::v8f32 x86vec::copysign(const v8f32& x, const v8f32& y)
{
	v4f32 xl = low_half(x);
	v4f32 xh = high_half(x);
	v4f32 yl = low_half(y);
	v4f32 yh = high_half(y);
	return v8f32(copysign(xl, yl), copysign(xh, yh));
}

inline
x86vec::v8f32 x86vec::mulsign(const v8f32& x, const v8f32& y)
{
	v4f32 xl = low_half(x);
	v4f32 xh = high_half(x);
	v4f32 yl = low_half(y);
	v4f32 yh = high_half(y);
	return v8f32(mulsign(xl, yl), mulsign(xh, yh));
}

inline
x86vec::v8f32 x86vec::isinf(const v8f32& x)
{
	v4f32 xl = low_half(x);
	v4f32 xh = high_half(x);
	return v8f32(isinf(xl), isinf(xh));
}

inline
x86vec::v8f32 x86vec::isnan(const v8f32& x)
{
	v4f32 xl = low_half(x);
	v4f32 xh = high_half(x);
	return v8f32(isnan(xl), isnan(xh));
}
inline
x86vec::v8f32 x86vec::isfinite(const v8f32& x)
{
	v4f32 xl = low_half(x);
	v4f32 xh = high_half(x);
	return v8f32(isfinite(xl), isfinite(xh));
}


template <bool _P0, bool _P1, bool _P2, bool _P3,
	  bool _P4, bool _P5, bool _P6, bool _P7>
inline
x86vec::v8f32 x86vec::select(const v8f32& a, const v8f32& b)
{
	v4f32 al = low_half(a);
	v4f32 ah = high_half(a);
	v4f32 bl = low_half(b);
	v4f32 bh = high_half(b);
	return v8f32(select<_P0, _P1, _P2, _P3>(al, bl),
		     select<_P4, _P5, _P6, _P7>(ah, bh));
}

inline
x86vec::v8f32 x86vec::select(const v8f32& msk,
                             const v8f32& on_true,
                             const v8f32& on_false)
{
	v4f32 msk_l = low_half(msk);
	v4f32 msk_h = high_half(msk);
	v4f32 on_true_l = low_half(on_true);
	v4f32 on_true_h = high_half(on_true);
	v4f32 on_false_l = low_half(on_false);
	v4f32 on_false_h = high_half(on_false);
	return v8f32(select(msk_l, on_true_l, on_false_l),
		     select(msk_h, on_true_h, on_false_h));
}

template <int _P0, int _P1, int _P2, int _P3,
	  int _P4, int _P5, int _P6, int _P7>
inline
x86vec::v8f32 x86vec::permute(const v8f32& a)
{
	v4f32 rl(permute<_P0, _P1, _P2, _P3>(low_half(a), 
					     high_half(a)));
	const int _PP4 = _P4 > 7 ? _P4 & 7 : _P4;
	const int _PP5 = _P5 > 7 ? _P5 & 7 : _P5;
	const int _PP6 = _P6 > 7 ? _P6 & 7 : _P6;
	const int _PP7 = _P7 > 7 ? _P7 & 7 : _P7;

	v4f32 rh(permute<_PP4, _PP5, _PP6, _PP7>(low_half(a), 
						 high_half(a)));
	return v8f32(rl, rh);
}

template <int _P0, int _P1, int _P2, int _P3,
	  int _P4, int _P5, int _P6, int _P7>
inline
x86vec::v8f32 x86vec::permute(const v8f32& a, const v8f32& b)
{
	using impl::pos_msk_8;
	using impl::zero_msk_8;
        // Combine all the indexes into a single bitfield, with 4 bits
        // for each
        const int m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
        // Mask to zero out negative indexes
        const int m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

        if ((m1 & 0x88888888 & m2) == 0) {
                // no elements from b
                return permute<_P0, _P1, _P2, _P3, 
			       _P4, _P5, _P6, _P7>(a);
        }
        if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
                // no elements from a
                return permute<_P0 & ~8, _P1 & ~8,
			       _P2 & ~8, _P3 & ~8,
			       _P4 & ~8, _P5 & ~8,
			       _P6 & ~8, _P7 & ~8>(b);
        }
        if (((m1 & ~0x88888888) ^ 0x76543210) == 0 && m2 == 0xFFFFFFFF) {
                // selecting without shuffling or zeroing
                const bool sm0 = _P0 < 8;
                const bool sm1 = _P1 < 8;
                const bool sm2 = _P2 < 8;
                const bool sm3 = _P3 < 8;
                const bool sm4 = _P4 < 8;
                const bool sm5 = _P5 < 8;
                const bool sm6 = _P6 < 8;
                const bool sm7 = _P7 < 8;
                return select<sm0, sm1, sm2, sm3,
			      sm4, sm5, sm6, sm7>(a, b);
        }

        // select all elements to clear or from 1st vector
        const int ma0 = _P0 < 8 ? _P0 : -1;
	const int ma1 = _P1 < 8 ? _P1 : -1;
	const int ma2 = _P2 < 8 ? _P2 : -1;
	const int ma3 = _P3 < 8 ? _P3 : -1;
        const int ma4 = _P4 < 8 ? _P4 : -1;
	const int ma5 = _P5 < 8 ? _P5 : -1;
	const int ma6 = _P6 < 8 ? _P6 : -1;
	const int ma7 = _P7 < 8 ? _P7 : -1;
	v8f32 a1 = permute<ma0, ma1, ma2, ma3,
			   ma4, ma5, ma6, ma7>(a);
	// select all elements from second vector
	const int mb0 = _P0 > 8 ? (_P0-8) : -1;
	const int mb1 = _P1 > 8 ? (_P1-8) : -1;
	const int mb2 = _P2 > 8 ? (_P2-8) : -1;
	const int mb3 = _P3 > 8 ? (_P3-8) : -1;
	const int mb4 = _P4 > 8 ? (_P4-8) : -1;
	const int mb5 = _P5 > 8 ? (_P5-8) : -1;
	const int mb6 = _P6 > 8 ? (_P6-8) : -1;
	const int mb7 = _P7 > 8 ? (_P7-8) : -1;
	v8f32 b1 = permute<mb0, mb1, mb2, mb3,
			   mb4, mb5, mb6, mb7>(b);
	return  a1 | b1;
}

template <unsigned _I>
inline
x86vec::v8f32 x86vec::insert(const v8f32& a, 
			     typename v8f32::element_type v)
{
	const bool low= _I < 4;
	v4s32 rl(low_half(a)), rh(high_half(a));
	if (_I < 4)
		rl = insert<_I>(rl, v);
	else
		rh = insert<_I&3>(rh, v);
	return v8s32(rl, rh);
}

template <unsigned _I>
inline
x86vec::v8f32::element_type
x86vec::extract(const v8f32& a)
{
	if (_I < 4)
		return extract<_I>(low_half(a));
	return extract<_I&3>(high_half(a));
}

inline
x86vec::v8f32::element_type
x86vec::hadd(const v8f32& a)
{
	v4f32 lh(low_half(a));
	v4f32 hh(high_half(a));
	v4f32 r(lh + hh);
	return hadd(r);
}

inline
x86vec::v8f32
x86vec::hadd_pairs(const v8f32& a, const v8f32& b)
{
	v8f32 lh(permute<0, 2, 4, 6, 8, 10, 12, 14>(a, b));
	v8f32 hh(permute<1, 3, 5, 7, 9, 11, 13, 15>(a, b));
	return lh + hh;
}

inline
x86vec::v8f32
x86vec::hsub_pairs(const v8f32& a, const v8f32& b)
{
	v8f32 lh(permute<0, 2, 4, 6, 8, 10, 12, 14>(a, b));
	v8f32 hh(permute<1, 3, 5, 7, 9, 11, 13, 15>(a, b));
	return lh - hh;
}

inline
x86vec::v8f32
x86vec::hmul_pairs(const v8f32& a, const v8f32& b)
{
	v8f32 lh(permute<0, 2, 4, 6, 8, 10, 12, 14>(a, b));
	v8f32 hh(permute<1, 3, 5, 7, 9, 11, 13, 15>(a, b));
	return lh * hh;
}

inline
x86vec::v8f32
x86vec::hdiv_pairs(const v8f32& a, const v8f32& b)
{
	v8f32 lh(permute<0, 2, 4, 6, 8, 10, 12, 14>(a, b));
	v8f32 hh(permute<1, 3, 5, 7, 9, 11, 13, 15>(a, b));
	return lh / hh;
}

inline
x86vec::v8f32::element_type
x86vec::dot(const v8f32& a, const v8f32& b)
{
	return hadd(a*b);
}

#else

inline
x86vec::v8f32::v8f32(vector_type r) : base_type(r)
{
}

inline
x86vec::v8f32::v8f32(const base_type& r) : base_type(r)
{
}

inline
x86vec::v8f32::v8f32(const v4f32& lh, const v4f32& hh)
	: base_type(_mm256_insertf128_ps(_mm256_castps128_ps256(lh()),
					 hh(), 1))
{
}

inline
x86vec::v8f32::v8f32(element_type p00, element_type p01,
                     element_type p02, element_type p03,
		     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type(_mm256_set_ps(p07, p06, p05, p04, p03, p02, p01, p00))
{
}

inline
x86vec::v8f32::v8f32(element_type r)
        : base_type(_mm256_set1_ps(r))
{
}

inline
x86vec::v8f32::v8f32(element_type r, bool broadcast)
        : base_type(broadcast ?
                    _mm256_set1_ps(r) : 
		    _mm256_set_ps(r, 0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, 0.0f, 0.0f))
{
}

template <template <class _V> class _OP, class _L, class _R>
inline
x86vec::v8f32::v8f32(const expr<_OP<v8f32>, _L, _R>& r)
	: base_type(eval(r)())
{
}

inline
x86vec::v8f32::v8f32(const mem::addr_bcast<element_type>& r)
        : base_type(_mm256_set1_ps(* (r())))
{
}

inline
x86vec::v8f32::v8f32(const mem::addr<element_type>& r)
        : base_type(is_aligned_to<16>::ptr(r()) ?
                    _mm256_load_ps(r()) :
                    _mm256_loadu_ps(r()))
{
}

inline
x86vec::v8f32::v8f32(const mem::aligned::addr<element_type>& r)
        : base_type(_mm256_load_ps(r()))
{
}

inline
x86vec::v8f32::v8f32(const mem::unaligned::addr<element_type>& r)
        : base_type(_mm256_loadu_ps(r()))
{
}

inline
x86vec::masked_vec<x86vec::v8f32>
x86vec::v8f32::operator()(const mask<v8f32>& m) 
{
	return masked_vec<v8f32>(*this, m);
}

inline
x86vec::v8f32
x86vec::ops::add<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	return _mm256_add_ps(a(), b());
}

inline
x86vec::v8f32
x86vec::ops::sub<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	return _mm256_sub_ps(a(), b());
}

inline
x86vec::v8f32
x86vec::ops::mul<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	return _mm256_mul_ps(a(), b());
}

inline
x86vec::v8f32
x86vec::ops::div<x86vec::v8f32>::v(const v8f32& a, const v8f32& b)
{
	return _mm256_div_ps(a(), b());
}

inline
x86vec::v8f32 x86vec::ops::fma<x86vec::v8f32>::
v(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__) 
	return _mm256_macc_ps(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fmadd_ps(a(), b(), c());
#else
	return _mm256_add_ps(_mm256_mul_ps(a(), b()), c());
#endif
}

inline
x86vec::v8f32 x86vec::ops::fms<x86vec::v8f32>::
v(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__)
	return _mm256_msub_ps(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fmsub_ps(a(), b(), c());
#else
	return _mm256_sub_ps(_mm256_mul_ps(a(), b()), c());
#endif
}

inline
x86vec::v8f32 x86vec::ops::fnma<x86vec::v8f32>::
v(const v8f32& a, const v8f32& b, const v8f32& c)
{
#if defined (__FMA4__)
	return _mm256_nmacc_ps(a(), b(), c());
#elif defined (__FMA__)
	return _mm256_fnmadd_ps(a(), b(), c());
#else
	return _mm256_sub_ps(c(), _mm256_mul_ps(a(), b()));
#endif
}

inline
x86vec::v8f32&
x86vec::operator|= (v8f32& a, const v8f32& b)
{
        a = _mm256_or_ps(a(), b());
        return a;
}

inline
x86vec::v8f32&
x86vec::operator&= (v8f32& a, const v8f32& b)
{
        a = _mm256_and_ps(a(), b());
        return a;
}

inline
x86vec::v8f32&
x86vec::operator^= (v8f32& a, const v8f32& b)
{
        a = _mm256_xor_ps(a(), b());
        return a;
}

inline
x86vec::v8f32&
x86vec::operator++(v8f32& a)
{
        const __m256 one = _mm256_set1_ps(1.0f);
        a = _mm256_add_ps(a(), one);
        return a;
}

inline
x86vec::v8f32
x86vec::operator++ (v8f32& a, int)
{
        v8f32 t(a);
        const __m256 one = _mm256_set1_ps(1.0f);
        a = _mm256_add_ps(a(), one);
        return t;
}

inline
x86vec::v8f32&
x86vec::operator--(v8f32& a)
{
        const __m256 one = _mm256_set1_ps(1.0f);
        a = _mm256_add_ps(a(), one);
        return a;
}

inline
x86vec::v8f32
x86vec::operator-- (v8f32& a, int)
{
        v8f32 t(a);
        const __m256 one = _mm256_set1_ps(1.0f);
        a = _mm256_add_ps(a(), one);
        return t;
}

inline
x86vec::v8f32
x86vec::operator-(const v8f32& a)
{
        const __m256 msk= v_sign_v8f32_msk::fv();
        return _mm256_xor_ps(a(), msk);
}

inline
const x86vec::v8f32&
x86vec::operator+(const v8f32& a)
{
        return a;
}

inline
x86vec::v8f32
x86vec::operator~(const v8f32& a)
{
        const __m256 all_set = const_v8u32<uint32_t(-1), uint32_t(-1),
					   uint32_t(-1), uint32_t(-1),
					   uint32_t(-1), uint32_t(-1),
					   uint32_t(-1), uint32_t(-1)>::fv();
        return _mm256_xor_ps(a(), all_set);
}

inline
x86vec::v8f32
x86vec::operator!(const v8f32& a)
{
        const __m256 msk = impl::make_zero_v8f32::v();
        return _mm256_cmp_ps(a(), msk, _CMP_EQ_OQ);
}

inline
x86vec::v8f32 x86vec::operator| (const v8f32& a, const v8f32& b)
{
        return _mm256_or_ps(a(), b());
}

inline
x86vec::v8f32 x86vec::operator|| (const v8f32& a, const v8f32& b)
{
        return a | b;
}

inline
x86vec::v8f32 x86vec::operator& (const v8f32& a, const v8f32& b)
{
        return _mm256_and_ps(a(), b());
}

inline
x86vec::v8f32 x86vec::operator&& (const v8f32& a, const v8f32& b)
{
        return a & b;
}

inline
x86vec::v8f32 x86vec::operator^(const v8f32& a, const v8f32& b)
{
        return _mm256_xor_ps(a(), b());
}

inline
x86vec::v8f32 x86vec::operator< (const v8f32& a, const v8f32& b)
{
        return _mm256_cmp_ps(a(), b(), _CMP_LT_OS);
}

inline
x86vec::v8f32 x86vec::operator<= (const v8f32& a, const v8f32& b)
{
        return _mm256_cmp_ps(a(), b(), _CMP_LE_OS);
}

inline
x86vec::v8f32 x86vec::operator== (const v8f32& a, const v8f32& b)
{
        return _mm256_cmp_ps(a(), b(), _CMP_EQ_OQ);
}

inline
x86vec::v8f32 x86vec::operator!= (const v8f32& a, const v8f32& b)
{
        return _mm256_cmp_ps(a(), b(), _CMP_UNORD_Q);
}

inline
x86vec::v8f32 x86vec::operator>= (const v8f32& a, const v8f32& b)
{
        return _mm256_cmp_ps(a(), b(), _CMP_GE_OS);
}

inline
x86vec::v8f32 x86vec::operator> (const v8f32& a, const v8f32& b)
{
        return _mm256_cmp_ps(a(), b(), _CMP_GT_OS);
}

inline
x86vec::v4f32 x86vec::low_half(const v8f32& v)
{
	return _mm256_castps256_ps128(v());
}

inline
x86vec::v4f32 x86vec::high_half(const v8f32& v)
{
	return _mm256_extractf128_ps(v(), 1);
}

inline
bool x86vec::all_signs(const v8f32& a)
{
        return all_signs_f32(a());
}

inline
bool x86vec::both_signs(const v8f32& a)
{
        return both_signs_f32(a());
}

inline
bool x86vec::no_signs(const v8f32& a)
{
        return no_signs_f32(a());
}

inline
unsigned x86vec::read_signs(const v8f32& a)
{
        return read_signs_f32(a());
}

inline
x86vec::v8f32 x86vec::max(const v8f32& a, const v8f32& b)
{
        return _mm256_max_ps(a(), b());
}

inline
x86vec::v8f32 x86vec::min(const v8f32& a, const v8f32& b)
{
        return _mm256_min_ps(a(), b());
}

inline
x86vec::v8f32 x86vec::abs(const v8f32& a)
{
        const __m256 msk= v_not_sign_v8f32_msk::fv();
        return _mm256_and_ps(a(), msk);
}

inline
x86vec::v8f32 x86vec::fabs(const v8f32& a)
{
        const __m256 msk= v_not_sign_v8f32_msk::fv();
        return _mm256_and_ps(a(), msk);
}

inline
x86vec::v8f32 x86vec::sqrt(const v8f32& a)
{
        return _mm256_sqrt_ps(a());
}

inline
x86vec::v8f32 
x86vec::rcp(const v8f32& a)
{
	return 1.0f/a;
}

inline
x86vec::v8f32
x86vec::native_rcp(const v8f32& a)
{
	// return rcp(a);
	v8f32 x0(_mm256_rcp_ps(a()));
	return (x0+x0) - ((x0*a) * x0);
}

inline
x86vec::v8f32
x86vec::rsqrt(const v8f32& a)
{
	return 1.0f/sqrt(a);
}

inline 
x86vec::v8f32
x86vec::native_rsqrt(const v8f32& a)
{
#if 0
	v4u32 u(as<v4u32>(a));
	const v4u32 magic(0xBE6EB50C);
	u = (magic - u) >> 1;
	v8f32 x0(as<v8f32>(u));
	v8f32 x1(0.5f * x0 * (3.0f - (a * x0) * x0));
	return x1;
#else
	// return rsqrt(a);
	v8f32 x0(_mm256_rsqrt_ps(a()));
	return (0.5f * x0) *(3.0f - (a*x0)* x0);
#endif
}

inline
x86vec::v8f32 x86vec::impl::round(const v8f32& a, const rounding_mode::type m)
{
#if defined (__SSE4_1__)
	v8f32 r;
        switch (m) {
        case rounding_mode::nearest:
                r= _mm256_round_ps(a(), 0);
		break;
        case rounding_mode::downward:
                r= _mm256_round_ps(a(), 1);
		break;
        case rounding_mode::upward:
                r= _mm256_round_ps(a(), 2);
		break;
        case rounding_mode::towardzero:
                r= _mm256_round_ps(a(), 3);
		break;
        case rounding_mode::current:
                r= _mm256_round_ps(a(), 4);
		break;
        }
	return r;
#else
	uint32_t mxcsr=0;
	uint32_t rmxcsr=0;
	if (m != rounding_mode::current) {
		mxcsr = _mm256_getcsr();
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
			_mm256_setcsr(rmxcsr);
	}
        const __m256 sgn_msk= v_sign_v8f32_msk::fv();
	// (127+23)<< 23 = 0x4B000000 = 2^23
        const __m256 magic= const_v4u32<0x4B000000, 0x4B000000,
                                       0x4B000000, 0x4B000000>::fv();
        __m256 sign = _mm256_and_ps(a(), sgn_msk);
        __m256 sign_magic = _mm256_or_ps(magic, sign);
	__m256 res= _mm256_add_ps(a(), sign_magic);
	res = _mm256_sub_ps(a(), sign_magic);
	if (mxcsr != rmxcsr)
		_mm256_setcsr(mxcsr);
	return res;
#endif
}

inline
x86vec::v8f32 x86vec::rint(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::nearest);
}

inline
x86vec::v8f32 x86vec::floor(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::downward);
}

inline
x86vec::v8f32 x86vec::ceil(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::upward);
}

inline
x86vec::v8f32 x86vec::trunc(const v8f32& a)
{
	return impl::round(a, impl::rounding_mode::towardzero);
}

inline
x86vec::v8f32 x86vec::andnot(const v8f32& x, const v8f32& y)
{
	return _mm256_andnot_ps(x(), y());
}

inline
x86vec::v8f32 x86vec::copysign(const v8f32& x, const v8f32& y)
{
	// return abs(x) * sgn(y)
	const v8f32 msk(v_not_sign_v8f32_msk::fv());
	v8f32 abs_x(x & msk);
	v8f32 sgn_y(andnot(msk, y));
	return abs_x | sgn_y;
}

inline
x86vec::v8f32 x86vec::mulsign(const v8f32& x, const v8f32& y)
{
	const v8f32 msk= v_sign_v8f32_msk::fv();
	v8f32 sgn_y = y & msk;
	return x ^ sgn_y;
}

inline
x86vec::v8f32 x86vec::isinf(const v8f32& x)
{
	// exponent = 0xFF and significand ==0
	v8f32 absx(abs(x));
	return absx == v_exp_v8f32_msk::fv();
}

inline
x86vec::v8f32 x86vec::isnan(const v8f32& x)
{
	// exponent = 0xff and significand !=0
	// x == x if x != NAN
	// x != x if x == NAN
	return x != x;
}
inline
x86vec::v8f32 x86vec::isfinite(const v8f32& x)
{
	return ~(isinf(x) | isnan(x));
}


template <bool _P0, bool _P1, bool _P2, bool _P3,
	  bool _P4, bool _P5, bool _P6, bool _P7>
inline
x86vec::v8f32 x86vec::select(const v8f32& a, const v8f32& b)
{
        return select_f32<_P0, _P1, _P2, _P3,
			  _P4, _P5, _P6, _P7> (a(), b());
}

inline
x86vec::v8f32 x86vec::select(const v8f32& msk,
                             const v8f32& on_true,
                             const v8f32& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1, int _P2, int _P3,
	  int _P4, int _P5, int _P6, int _P7>
inline
x86vec::v8f32 x86vec::permute(const v8f32& a)
{
        return perm_f32<_P0, _P1, _P2, _P3,
			_P4, _P5, _P6, _P7>(a());
}

template <int _P0, int _P1, int _P2, int _P3,
	  int _P4, int _P5, int _P6, int _P7>
inline
x86vec::v8f32 x86vec::permute(const v8f32& a, const v8f32& b)
{
        return perm_f32<_P0, _P1, _P2, _P3,
			_P4, _P5, _P6, _P7>(a(), b());
}

template <unsigned _I>
inline
x86vec::v8f32 x86vec::insert(const v8f32& a, 
			     typename v8f32::element_type v)
{
        return insert_f32<_I>(a(), v);
}

template <unsigned _I>
inline
x86vec::v8f32::element_type
x86vec::extract(const v8f32& a)
{
        return extract_f32<_I>(a());
}

inline
x86vec::v8f32::element_type
x86vec::hadd(const v8f32& a)
{
	v4f32 lh(low_half(a));
	v4f32 hh(high_half(a));
	v4f32 r(lh + hh);
	return hadd(r);
}

inline
x86vec::v8f32
x86vec::hadd_pairs(const v8f32& a, const v8f32& b)
{
	return _mm256_hadd_ps(a(), b());
}

inline
x86vec::v8f32
x86vec::hsub_pairs(const v8f32& a, const v8f32& b)
{
	return _mm256_hsub_ps(a(), b());
}

inline
x86vec::v8f32
x86vec::hmul_pairs(const v8f32& a, const v8f32& b)
{
	v8f32 lh(permute<0, 2, 4, 6, 8, 10, 12, 14>(a, b));
	v8f32 hh(permute<1, 3, 5, 7, 9, 11, 13, 15>(a, b));
	return lh * hh;
}

inline
x86vec::v8f32
x86vec::hdiv_pairs(const v8f32& a, const v8f32& b)
{
	v8f32 lh(permute<0, 2, 4, 6, 8, 10, 12, 14>(a, b));
	v8f32 hh(permute<1, 3, 5, 7, 9, 11, 13, 15>(a, b));
	return lh / hh;
}


inline
x86vec::v8f32::element_type
x86vec::dot(const v8f32& a, const v8f32& b)
{
	return hadd(a*b);
}

#endif // __AVX__

// Local variables:
// mode: c++
// end:
#endif
