#include "emuvec.h"
#include <algorithm>

// v8s16 implementation
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

emuvec::v8s16 emuvec::select(const v8s16& msk,
                             const v8s16& on_true,
                             const v8s16& on_false)
{
	v8s16 r;
	impl::select<v8s16::element_type>::v(r(), 
					     msk(), on_true(), on_false(),
					     v8s16::N);
	return r;
}


// v8u16 implementation
emuvec::v8u16::v8u16() : base_type()
{
}

emuvec::v8u16::v8u16(const v8u16& r) : base_type(r)
{
}

emuvec::v8u16::v8u16(const v8s16& r) : base_type(r)
{
}

emuvec::v8u16::v8u16(v8u16&& r) : base_type(std::move(r))
{
}

emuvec::v8u16::v8u16(v8s16&& r) : base_type(std::move(r))
{
}

emuvec::v8u16::v8u16(element_type p00, element_type p01,
                     element_type p02, element_type p03,
                     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type(p00, p01, p02, p03, p04, p05, p06, p07)
{
}

emuvec::v8u16::v8u16(element_type r): base_type(r)
{
}

emuvec::v8u16::v8u16(v8u16::element_type r, bool broadcast)
        : base_type(r, broadcast)
{
}

emuvec::v8u16::v8u16(const mem::addr_bcast<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr_bcast<std::int16_t>&>(r))
{
}

emuvec::v8u16::v8u16(const mem::addr<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr<std::int16_t>&>(r))
{
}

emuvec::v8u16& emuvec::v8u16::operator=(const v8u16& r)
{
	base_type::operator=(r);
        return *this;
}

emuvec::v8u16& emuvec::v8u16::operator=(const v8s16& r)
{
	base_type::operator=(r);
        return *this;
}

emuvec::v8u16& emuvec::v8u16::operator=(v8u16&& r)
{
	base_type::operator=(std::move(r));
        return *this;
}

emuvec::v8u16& emuvec::v8u16::operator=(v8s16&& r)
{
	base_type::operator=(std::move(r));
        return *this;
}

emuvec::v8u16& emuvec::v8u16::operator=(element_type r)
{
	base_type::operator=(std::int16_t(r));
        return *this;
}

emuvec::v8u16&
emuvec::operator|= (v8u16& a, const v8u16& b)
{
        impl::v_or<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator&= (v8u16& a, const v8u16& b)
{
        impl::v_and<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator^= (v8u16& a, const v8u16& b)
{
        impl::v_xor<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator+= (v8u16& a, const v8u16& b)
{
        impl::v_add<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator-= (v8u16& a, const v8u16& b)
{
        impl::v_sub<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator*= (v8u16& a, const v8u16& b)
{
        impl::v_mul<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator/=(v8u16& a, const v8u16& b)
{
        impl::v_div<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator%=(v8u16& a, const v8u16& b)
{
        impl::v_irem<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

emuvec::v8u16&
emuvec::operator<<= (v8u16& a, uint32_t b)
{
        impl::v_sl<v8u16::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

emuvec::v8u16
emuvec::operator<< (const v8u16& a, uint32_t b)
{
        v8u16 r;
        impl::v_sl<v8u16::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8u16::N);
        return r;
}

emuvec::v8u16&
emuvec::operator>>= (v8u16& a, uint32_t b)
{
        impl::v_sr<v8u16::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

emuvec::v8u16
emuvec::operator>> (const v8u16& a, uint32_t b)
{
        v8u16 r;
        impl::v_sr<v8u16::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8u16::N);
        return r;
}

emuvec::v8u16&
emuvec::operator++(v8u16& a)
{
        impl::v_inc<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

emuvec::v8u16
emuvec::operator++ (v8u16& a, int)
{
        v8u16 t(a);
        impl::v_inc<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return t;
}

emuvec::v8u16&
emuvec::operator--(v8u16& a)
{
        impl::v_dec<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

emuvec::v8u16
emuvec::operator-- (v8u16& a, int)
{
        v8u16 t(a);
        impl::v_dec<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return t;
}

emuvec::v8u16
emuvec::operator-(const v8u16& a)
{
        v8u16 r;
        impl::v_neg<v8u16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8u16::N);
        return r;
}

const emuvec::v8u16&
emuvec::operator+(const v8u16& a)
{
        return a;
}

emuvec::v8u16
emuvec::operator~(const v8u16& a)
{
        v8u16 r;
        impl::v_not<v8u16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8u16::N);
        return r;
}

emuvec::v8u16
emuvec::operator!(const v8u16& a)
{
        v8u16 r;
        impl::v_log_not<v8u16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator| (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_or<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator|| (const v8u16& a, const v8u16& b)
{
        return a | b;
}

emuvec::v8u16 emuvec::operator& (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_and<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator&& (const v8u16& a, const v8u16& b)
{
        return a & b;
}

emuvec::v8u16 emuvec::operator^(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_xor<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator+ (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_add<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator- (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_sub<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator* (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_mul<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16
emuvec::operator/(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_div<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16
emuvec::operator%(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_irem<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}


emuvec::v8u16 emuvec::operator< (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_lt<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator<= (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_le<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator== (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_eq<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator!= (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_ne<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator>= (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_ge<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::operator> (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_gt<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::max(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_max<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::min(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_min<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::mulh(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_mulhi<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

emuvec::v8u16 emuvec::select(const v8u16& msk,
                             const v8u16& on_true,
                             const v8u16& on_false)
{
	v8u16 r;
	impl::select<v8u16::element_type>::v(r(), 
					     msk(), on_true(), on_false(),
					     v8u16::N);
	return r;
}

// v4s32 implementation
emuvec::v4s32::v4s32() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

emuvec::v4s32::v4s32(const v4s32& r) : base_type(r)
{
}

emuvec::v4s32::v4s32(v4s32&& r) : base_type(std::move(r))
{
}

emuvec::v4s32::v4s32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01; p[2] = p02; p[3] = p03;
}

emuvec::v4s32::v4s32(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

emuvec::v4s32::v4s32(v4s32::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(begin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

emuvec::v4s32::v4s32(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

emuvec::v4s32::v4s32(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

emuvec::v4s32& emuvec::v4s32::operator=(const v4s32& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

emuvec::v4s32& emuvec::v4s32::operator=(v4s32&& r)
{
        swap(r);
        return *this;
}

emuvec::v4s32& emuvec::v4s32::operator=(v4s32::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

emuvec::v4s32&
emuvec::operator|= (v4s32& a, const v4s32& b)
{
        impl::v_or<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator&= (v4s32& a, const v4s32& b)
{
        impl::v_and<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator^= (v4s32& a, const v4s32& b)
{
        impl::v_xor<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator+= (v4s32& a, const v4s32& b)
{
        impl::v_add<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator-= (v4s32& a, const v4s32& b)
{
        impl::v_sub<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator*= (v4s32& a, const v4s32& b)
{
        impl::v_mul<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator/=(v4s32& a, const v4s32& b)
{
        impl::v_div<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator%=(v4s32& a, const v4s32& b)
{
        impl::v_irem<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

emuvec::v4s32&
emuvec::operator<<= (v4s32& a, uint32_t b)
{
        impl::v_sl<v4s32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

emuvec::v4s32
emuvec::operator<< (const v4s32& a, uint32_t b)
{
        v4s32 r;
        impl::v_sl<v4s32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

emuvec::v4s32&
emuvec::operator>>= (v4s32& a, uint32_t b)
{
        impl::v_sr<v4s32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

emuvec::v4s32
emuvec::operator>> (const v4s32& a, uint32_t b)
{
        v4s32 r;
        impl::v_sr<v4s32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

emuvec::v4s32&
emuvec::operator++(v4s32& a)
{
        impl::v_inc<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

emuvec::v4s32
emuvec::operator++ (v4s32& a, int)
{
        v4s32 t(a);
        impl::v_inc<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return t;
}

emuvec::v4s32&
emuvec::operator--(v4s32& a)
{
        impl::v_dec<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

emuvec::v4s32
emuvec::operator-- (v4s32& a, int)
{
        v4s32 t(a);
        impl::v_dec<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return t;
}

emuvec::v4s32
emuvec::operator-(const v4s32& a)
{
        v4s32 r;
        impl::v_neg<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

const emuvec::v4s32&
emuvec::operator+(const v4s32& a)
{
        return a;
}

emuvec::v4s32
emuvec::operator~(const v4s32& a)
{
        v4s32 r;
        impl::v_not<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

emuvec::v4s32
emuvec::operator!(const v4s32& a)
{
        v4s32 r;
        impl::v_log_not<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator| (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_or<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator|| (const v4s32& a, const v4s32& b)
{
        return a | b;
}

emuvec::v4s32 emuvec::operator& (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_and<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator&& (const v4s32& a, const v4s32& b)
{
        return a & b;
}

emuvec::v4s32 emuvec::operator^(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_xor<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator+ (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_add<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator- (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_sub<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator* (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_mul<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32
emuvec::operator/(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_div<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32
emuvec::operator%(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_irem<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}


emuvec::v4s32 emuvec::operator< (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_lt<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator<= (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_le<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator== (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_eq<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator!= (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_ne<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator>= (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_ge<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::operator> (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_gt<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::max(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_max<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::min(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_min<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

emuvec::v4s32 emuvec::abs(const v4s32& a)
{
        v4s32 r;
        impl::v_abs<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}


emuvec::v4s32 emuvec::mulh(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_mulhi<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

bool emuvec::no_signs(const v4s32& a)
{
        std::uint32_t sgns(impl::get_signs_32(a(), v4s32::N));
        return sgns == 0;
}

bool emuvec::all_signs(const v4s32& a)
{
        std::uint32_t sgns(impl::get_signs_32(a(), v4s32::N));
        return sgns == 0xFF;

}

bool emuvec::both_signs(const v4s32& a)
{
        std::uint32_t sgns(impl::get_signs_32(a(), v4s32::N));
        return sgns != 0xFF && sgns != 0;
}

emuvec::v4s32 emuvec::select(const v4s32& msk,
                             const v4s32& on_true,
                             const v4s32& on_false)
{
	v4s32 r;
	impl::select<v4s32::element_type>::v(r(), 
					     msk(), on_true(), on_false(),
					     v4s32::N);
	return r;
}

// v4u32 implementation
emuvec::v4u32::v4u32() : base_type()
{
}

emuvec::v4u32::v4u32(const v4u32& r) : base_type(r)
{
}

emuvec::v4u32::v4u32(const v4s32& r) : base_type(r)
{
}

emuvec::v4u32::v4u32(v4u32&& r) : base_type(std::move(r))
{
}

emuvec::v4u32::v4u32(v4s32&& r) : base_type(std::move(r))
{
}

emuvec::v4u32::v4u32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type(p00, p01, p02, p03)
{
}

emuvec::v4u32::v4u32(element_type r): base_type(r)
{
}

emuvec::v4u32::v4u32(v4u32::element_type r, bool broadcast)
        : base_type(r, broadcast)
{
}

emuvec::v4u32::v4u32(const mem::addr_bcast<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr_bcast<std::int32_t>&>(r))
{
}

emuvec::v4u32::v4u32(const mem::addr<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr<std::int32_t>&>(r))
{
}

emuvec::v4u32& emuvec::v4u32::operator=(const v4u32& r)
{
	base_type::operator=(r);
        return *this;
}

emuvec::v4u32& emuvec::v4u32::operator=(const v4s32& r)
{
	base_type::operator=(r);
        return *this;
}

emuvec::v4u32& emuvec::v4u32::operator=(v4u32&& r)
{
	base_type::operator=(std::move(r));
        return *this;
}

emuvec::v4u32& emuvec::v4u32::operator=(v4s32&& r)
{
	base_type::operator=(std::move(r));
        return *this;
}

emuvec::v4u32& emuvec::v4u32::operator=(element_type r)
{
	base_type::operator=(std::int32_t(r));
        return *this;
}

emuvec::v4u32&
emuvec::operator|= (v4u32& a, const v4u32& b)
{
        impl::v_or<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator&= (v4u32& a, const v4u32& b)
{
        impl::v_and<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator^= (v4u32& a, const v4u32& b)
{
        impl::v_xor<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator+= (v4u32& a, const v4u32& b)
{
        impl::v_add<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator-= (v4u32& a, const v4u32& b)
{
        impl::v_sub<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator*= (v4u32& a, const v4u32& b)
{
        impl::v_mul<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator/=(v4u32& a, const v4u32& b)
{
        impl::v_div<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator%=(v4u32& a, const v4u32& b)
{
        impl::v_irem<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

emuvec::v4u32&
emuvec::operator<<= (v4u32& a, uint32_t b)
{
        impl::v_sl<v4u32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

emuvec::v4u32
emuvec::operator<< (const v4u32& a, uint32_t b)
{
        v4u32 r;
        impl::v_sl<v4u32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

emuvec::v4u32&
emuvec::operator>>= (v4u32& a, uint32_t b)
{
        impl::v_sr<v4u32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

emuvec::v4u32
emuvec::operator>> (const v4u32& a, uint32_t b)
{
        v4u32 r;
        impl::v_sr<v4u32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

emuvec::v4u32&
emuvec::operator++(v4u32& a)
{
        impl::v_inc<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

emuvec::v4u32
emuvec::operator++ (v4u32& a, int)
{
        v4u32 t(a);
        impl::v_inc<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return t;
}

emuvec::v4u32&
emuvec::operator--(v4u32& a)
{
        impl::v_dec<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

emuvec::v4u32
emuvec::operator-- (v4u32& a, int)
{
        v4u32 t(a);
        impl::v_dec<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return t;
}

emuvec::v4u32
emuvec::operator-(const v4u32& a)
{
        v4u32 r;
        impl::v_neg<v4u32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4u32::N);
        return r;
}

const emuvec::v4u32&
emuvec::operator+(const v4u32& a)
{
        return a;
}

emuvec::v4u32
emuvec::operator~(const v4u32& a)
{
        v4u32 r;
        impl::v_not<v4u32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4u32::N);
        return r;
}

emuvec::v4u32
emuvec::operator!(const v4u32& a)
{
        v4u32 r;
        impl::v_log_not<v4u32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator| (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_or<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator|| (const v4u32& a, const v4u32& b)
{
        return a | b;
}

emuvec::v4u32 emuvec::operator& (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_and<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator&& (const v4u32& a, const v4u32& b)
{
        return a & b;
}

emuvec::v4u32 emuvec::operator^(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_xor<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator+ (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_add<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator- (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_sub<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator* (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_mul<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32
emuvec::operator/(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_div<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32
emuvec::operator%(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_irem<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}


emuvec::v4u32 emuvec::operator< (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_lt<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator<= (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_le<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator== (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_eq<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator!= (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_ne<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator>= (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_ge<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::operator> (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_gt<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::max(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_max<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::min(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_min<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::mulh(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_mulhi<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

emuvec::v4u32 emuvec::select(const v4u32& msk,
                             const v4u32& on_true,
                             const v4u32& on_false)
{
	v4u32 r;
	impl::select<v4u32::element_type>::v(r(), 
					     msk(), on_true(), on_false(),
					     v4u32::N);
	return r;
}

// v4f32 implementation
emuvec::v4f32::v4f32() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

emuvec::v4f32::v4f32(const v4f32& r) : base_type(r)
{
}

emuvec::v4f32::v4f32(v4f32&& r) : base_type(std::move(r))
{
}

emuvec::v4f32::v4f32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01; p[2] = p02; p[3] = p03;
}

emuvec::v4f32::v4f32(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

emuvec::v4f32::v4f32(v4f32::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(begin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

emuvec::v4f32::v4f32(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

emuvec::v4f32::v4f32(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

emuvec::v4f32& emuvec::v4f32::operator=(const v4f32& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

emuvec::v4f32& emuvec::v4f32::operator=(v4f32&& r)
{
        swap(r);
        return *this;
}

emuvec::v4f32& emuvec::v4f32::operator=(v4f32::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

emuvec::v4f32&
emuvec::operator|= (v4f32& a, const v4f32& b)
{
        impl::v_f_or<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f32::N);
        return a;
}

#if 0

emuvec::v4f32&
emuvec::operator&= (v4f32& a, const v4f32& b)
{
        a = _mm_and_ps(a(), b());
        return a;
}


emuvec::v4f32&
emuvec::operator^= (v4f32& a, const v4f32& b)
{
        a = _mm_xor_ps(a(), b());
        return a;
}


emuvec::v4f32&
emuvec::operator+= (v4f32& a, const v4f32& b)
{
        a = _mm_add_ps(a(), b());
        return a;
}


emuvec::v4f32&
emuvec::operator-= (v4f32& a, const v4f32& b)
{
        a = _mm_sub_ps(a(), b());
        return a;
}


emuvec::v4f32&
emuvec::operator*= (v4f32& a, const v4f32& b)
{
        a = _mm_mul_ps(a(), b());
        return a;
}


emuvec::v4f32&
emuvec::operator/=(v4f32& a, const v4f32& b)
{
        a= _mm_div_ps(a(), b());
        return a;
}


emuvec::v4f32&
emuvec::operator++(v4f32& a)
{
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return a;
}


emuvec::v4f32
emuvec::operator++ (v4f32& a, int)
{
        v4f32 t(a);
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return t;
}


emuvec::v4f32&
emuvec::operator--(v4f32& a)
{
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return a;
}


emuvec::v4f32
emuvec::operator-- (v4f32& a, int)
{
        v4f32 t(a);
        const __m128 one = _mm_set1_ps(1.0f);
        a = _mm_add_ps(a(), one);
        return t;
}


emuvec::v4f32
emuvec::operator-(const v4f32& a)
{
        const __m128 msk= v_sign_f32_msk::fv();
        return _mm_xor_ps(a(), msk);
}


const emuvec::v4f32&
emuvec::operator+(const v4f32& a)
{
        return a;
}


emuvec::v4f32
emuvec::operator~(const v4f32& a)
{
        const __m128 all_set = const4_u32 < -1, -1, -1, -1 >::fv();
        return _mm_xor_ps(a(), all_set);
}


emuvec::v4f32
emuvec::operator!(const v4f32& a)
{
        const __m128 msk = impl::make_zero_f32::v();
        return _mm_cmpeq_ps(a(), msk);
}


emuvec::v4f32 emuvec::operator| (const v4f32& a, const v4f32& b)
{
        return _mm_or_ps(a(), b());
}


emuvec::v4f32 emuvec::operator|| (const v4f32& a, const v4f32& b)
{
        return a | b;
}


emuvec::v4f32 emuvec::operator& (const v4f32& a, const v4f32& b)
{
        return _mm_and_ps(a(), b());
}


emuvec::v4f32 emuvec::operator&& (const v4f32& a, const v4f32& b)
{
        return a & b;
}


emuvec::v4f32 emuvec::operator^(const v4f32& a, const v4f32& b)
{
        return _mm_xor_ps(a(), b());
}


emuvec::v4f32 emuvec::operator+ (const v4f32& a, const v4f32& b)
{
        return _mm_add_ps(a(), b());
}


emuvec::v4f32 emuvec::operator- (const v4f32& a, const v4f32& b)
{
        return _mm_sub_ps(a(), b());
}


emuvec::v4f32 emuvec::operator* (const v4f32& a, const v4f32& b)
{
        return _mm_mul_ps(a(), b());
}


emuvec::v4f32
emuvec::operator/(const v4f32& a, const v4f32& b)
{
        return _mm_div_ps(a(), b());
}



emuvec::v4f32 emuvec::operator< (const v4f32& a, const v4f32& b)
{
        return _mm_cmplt_ps(a(), b());
}


emuvec::v4f32 emuvec::operator<= (const v4f32& a, const v4f32& b)
{
        return _mm_cmple_ps(a(), b());
}


emuvec::v4f32 emuvec::operator== (const v4f32& a, const v4f32& b)
{
        return _mm_cmpeq_ps(a(), b());
}


emuvec::v4f32 emuvec::operator!= (const v4f32& a, const v4f32& b)
{
        return _mm_cmpneq_ps(a(), b());
}


emuvec::v4f32 emuvec::operator>= (const v4f32& a, const v4f32& b)
{
        return _mm_cmpge_ps(a(), b());
}


emuvec::v4f32 emuvec::operator> (const v4f32& a, const v4f32& b)
{
        return _mm_cmpgt_ps(a(), b());
}


bool emuvec::all_signs(const v4f32& a)
{
        return all_signs_f32(a());
}


bool emuvec::both_signs(const v4f32& a)
{
        return both_signs_f32(a());
}


bool emuvec::no_signs(const v4f32& a)
{
        return no_signs_f32(a());
}


emuvec::v4f32 emuvec::max(const v4f32& a, const v4f32& b)
{
        return _mm_max_ps(a(), b());
}


emuvec::v4f32 emuvec::min(const v4f32& a, const v4f32& b)
{
        return _mm_max_ps(a(), b());
}


emuvec::v4f32 emuvec::abs(const v4f32& a)
{
        const __m128 msk= v_not_sign_f32_msk::fv();
        return _mm_and_ps(a(), msk);
}


emuvec::v4f32 emuvec::sqrt(const v4f32& a)
{
        return _mm_sqrt_ps(a());
}


emuvec::v4f32 emuvec::impl::round(const v4f32& a, const rounding_mode::type m)
{
#if defined (__SSE4_1__)
        switch (m) {
        case rounding_mode::nearest:
                return _mm_round_ps(a(), 0);
        case rounding_mode::downward:
                return _mm_round_ps(a(), 1);
        case rounding_mode::upward:
                return _mm_round_ps(a(), 2);
        case rounding_mode::towardzero:
                return _mm_round_ps(a(), 3);
        }
#else
        std::uint32_t mxcsr=_mm_getcsr();
        std::uint32_t rmxcsr(mxcsr);
	rmxcsr &= ~(3<<13);
        switch (m) {
        case rounding_mode::nearest: // 0
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
        }
	if (mxcsr != rmxcsr)
		_mm_setcsr(rmxcsr);
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


emuvec::v4f32 emuvec::rint(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::nearest);
}


emuvec::v4f32 emuvec::floor(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::downward);
}


emuvec::v4f32 emuvec::ceil(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::upward);
}


emuvec::v4f32 emuvec::trunc(const v4f32& a)
{
	return impl::round(a, impl::rounding_mode::towardzero);
}

#if 0
template < bool _P0, bool _P1, bool _P2, bool _P3 >

emuvec::v4f32 emuvec::select(const v4f32& a, const v4f32& b)
{
        return select_f32 <_P0, _P1, _P2, _P3> (a(), b());
}


emuvec::v4f32 emuvec::select(const v4f32& msk,
                             const v4f32& on_true,
                             const v4f32& on_false)
{
        return select(msk(), on_true(), on_false());
}

template <int _P0, int _P1, int _P2, int _P3>

emuvec::v4f32 emuvec::permute(const v4f32& a)
{
        return perm_f32<_P0, _P1, _P2, _P3>(a());
}

template < int _P0, int _P1, int _P2, int _P3 >

emuvec::v4f32 emuvec::permute(const v4f32& a, const v4f32& b)
{
        return perm_f32<_P0, _P1, _P2, _P3>(a(), b());
}

template <unsigned _I>

emuvec::v4f32 emuvec::insert(const v4f32& a, typename v4f32::element_type v)
{
        return insert_f32<_I>(a(), v);
}

template <unsigned _I>

typename emuvec::v4f32::element_type
emuvec::extract(const v4f32& a)
{
        return extract_f32<_I>(a());
}
#endif
#endif

void catch_print_size() {
}
