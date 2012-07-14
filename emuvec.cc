#include "emuvec.h"
#include <algorithm>

emuvec::v8s16::v8s16() : base_type()
{
	std::uninitialized_fill_n(begin(), N, 0);
}

emuvec::v8s16::v8s16(const v8s16& r) : base_type(r)
{
}

emuvec::v8s16::v8s16(v8s16&& r) : base_type(std::move(r))
{
}

emuvec::v8s16::v8s16(element_type p00, element_type p01,
                     element_type p02, element_type p03,
                     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type()
{
	element_type* p= begin();
	p[0] = p00; p[1] = p01; p[2] = p02; p[3] = p03;
	p[4] = p04; p[5] = p05; p[6] = p06; p[7] = p07;
}

emuvec::v8s16::v8s16(element_type r): base_type()
{
	std::uninitialized_fill_n(begin(), N, r);
}

emuvec::v8s16::v8s16(v8s16::element_type r, bool broadcast)
        : base_type()
{
	if (broadcast) {
		std::uninitialized_fill_n(begin(), N, r);
	} else {
		get_allocator().construct(begin(), r);
		std::uninitialized_fill_n(begin()+1, N-1, 0);
	}
}

emuvec::v8s16::v8s16(const mem::addr_bcast<element_type>& r)
        : base_type()
{
	std::uninitialized_fill_n(begin(), N, *r());
}

emuvec::v8s16::v8s16(const mem::addr<element_type>& r)
        : base_type()
{
	std::uninitialized_copy_n(r(), N, begin());
}

emuvec::v8s16& emuvec::v8s16::operator=(const v8s16& r)
{
	if (&r != this)
		std::copy_n(r.begin(), N, begin());
	return *this;
}

emuvec::v8s16& emuvec::v8s16::operator=(v8s16&& r)
{
	swap(r);
	return *this;
}

emuvec::v8s16& emuvec::v8s16::operator=(v8s16::element_type r)
{
	std::fill_n(begin(), N, r);
	return *this;
}

emuvec::v8s16&
emuvec::operator|= (v8s16& a, const v8s16& b)
{
	impl::v_or<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator&= (v8s16& a, const v8s16& b)
{
	impl::v_and<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator^= (v8s16& a, const v8s16& b)
{
	impl::v_xor<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator+= (v8s16& a, const v8s16& b)
{
	impl::v_add<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator-= (v8s16& a, const v8s16& b)
{
	impl::v_sub<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator*= (v8s16& a, const v8s16& b)
{
	impl::v_mul<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator/=(v8s16& a, const v8s16& b)
{
	impl::v_div<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator%=(v8s16& a, const v8s16& b)
{
	impl::v_irem<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, b(), v8s16::N);
	return a;
}

emuvec::v8s16&
emuvec::operator<<= (v8s16& a, uint32_t b)
{
	impl::v_sl<v8s16::element_type> ot(b);
	impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

emuvec::v8s16
emuvec::operator<< (const v8s16& a, uint32_t b)
{
	v8s16 r;
	impl::v_sl<v8s16::element_type> ot(b);
	impl::v_bi_op(r(), a(), ot, v8s16::N);
	return r;
}

emuvec::v8s16&
emuvec::operator>>= (v8s16& a, uint32_t b)
{
	impl::v_sr<v8s16::element_type> ot(b);
	impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

emuvec::v8s16
emuvec::operator>> (const v8s16& a, uint32_t b)
{
	v8s16 r;
	impl::v_sr<v8s16::element_type> ot(b);
	impl::v_bi_op(r(), a(), ot, v8s16::N);
	return r;
}

emuvec::v8s16&
emuvec::operator++(v8s16& a)
{
	impl::v_inc<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
	return a;
}

emuvec::v8s16
emuvec::operator++ (v8s16& a, int)
{
	v8s16 t(a);
	impl::v_inc<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
        return t;
}

emuvec::v8s16&
emuvec::operator--(v8s16& a)
{
	impl::v_dec<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
	return a;
}

emuvec::v8s16
emuvec::operator-- (v8s16& a, int)
{
	v8s16 t(a);
	impl::v_dec<v8s16::element_type> ot;
	impl::v_assign_op(a(), ot, v8s16::N);
        return t;
}

emuvec::v8s16
emuvec::operator-(const v8s16& a)
{
	v8s16 r;
	impl::v_neg<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}

const emuvec::v8s16&
emuvec::operator+(const v8s16& a)
{
	return a;
}

emuvec::v8s16
emuvec::operator~(const v8s16& a)
{
	v8s16 r;
	impl::v_not<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}

emuvec::v8s16
emuvec::operator!(const v8s16& a)
{
	v8s16 r;
	impl::v_log_not<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator| (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_or<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator|| (const v8s16& a, const v8s16& b)
{
        return a | b;
}

emuvec::v8s16 emuvec::operator& (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_and<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator&& (const v8s16& a, const v8s16& b)
{
        return a & b;
}

emuvec::v8s16 emuvec::operator^(const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_xor<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator+ (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_add<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator- (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_sub<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator* (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_mul<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16
emuvec::operator/(const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_div<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16
emuvec::operator%(const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_irem<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}


emuvec::v8s16 emuvec::operator< (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_lt<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator<= (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_le<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator== (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_eq<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator!= (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_ne<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator>= (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_ge<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::operator> (const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_gt<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::max(const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_max<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::min(const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_min<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

emuvec::v8s16 emuvec::abs(const v8s16& a)
{
	v8s16 r;
	impl::v_abs<v8s16::element_type> ot;
	impl::v_un_op(r(), ot, a(), v8s16::N);
	return r;
}


emuvec::v8s16 emuvec::mulh(const v8s16& a, const v8s16& b)
{
	v8s16 r;
	impl::v_mulhi<v8s16::element_type> ot;
	impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
	return r;
}

bool emuvec::no_signs(const v8s16& a)
{
	std::uint32_t sgns(impl::get_signs_32(a(), v8s16::N));
	return sgns == 0;
}

bool emuvec::all_signs(const v8s16& a)
{
	std::uint32_t sgns(impl::get_signs_32(a(), v8s16::N));
	return sgns == 0xFF;

}

bool emuvec::both_signs(const v8s16& a)
{
	std::uint32_t sgns(impl::get_signs_32(a(), v8s16::N));
	return sgns != 0xFF && sgns != 0;
}

#if 0
template < bool _P0, bool _P1, bool _P2, bool _P3,
	   bool _P4, bool _P5, bool _P6, bool _P7 >

emuvec::v8s16 emuvec::select(const v8s16& a, const v8s16& b)
{
        return select_u16 <
		_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7 > (a(), b());
}


emuvec::v8s16 emuvec::select(const v8s16& msk,
                             const v8s16& on_true,
                             const v8s16& on_false)
{
        return select(msk(), on_true(), on_false());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >

emuvec::v8s16 emuvec::permute(const v8s16& a)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a());
}

template < int _P0, int _P1, int _P2, int _P3,
	   int _P4, int _P5, int _P6, int _P7 >

emuvec::v8s16 emuvec::permute(const v8s16& a, const v8s16& b)
{
        return perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a(), b());
}

template <unsigned _I>

emuvec::v8s16 emuvec::insert(const v8s16& a, typename v8s16::element_type v)
{
	return insert_u16<_I>(a(), v);
}

template <unsigned _I>
typename emuvec::v8s16::element_type
emuvec::extract(const v8s16& a)
{
	return extract_u16<_I>(a());
}

#endif

void catch_print_size() {}
