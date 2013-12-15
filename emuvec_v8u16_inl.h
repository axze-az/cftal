#if !defined (__EMUVEC_V8U16_INL_H__)
#define __EMUVEC_V8U16_INL_H__ 1

#include <algorithm>


// v8u16 implementation
inline
emuvec::v8u16::v8u16(const v8s16& r) : base_type(r)
{
}


inline
emuvec::v8u16::v8u16(v8s16&& r) : base_type(std::move(r))
{
}

inline
emuvec::v8u16::v8u16(element_type p00, element_type p01,
                     element_type p02, element_type p03,
                     element_type p04, element_type p05,
                     element_type p06, element_type p07)
        : base_type(p00, p01, p02, p03, p04, p05, p06, p07)
{
}

inline
emuvec::v8u16::v8u16(element_type r): base_type(r)
{
}

inline
emuvec::v8u16::v8u16(v8u16::element_type r, bool broadcast)
        : base_type(r, broadcast)
{
}

inline
emuvec::v8u16::v8u16(const mem::addr_bcast<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr_bcast<int16_t>&>(r))
{
}

inline
emuvec::v8u16::v8u16(const mem::addr<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr<int16_t>&>(r))
{
}

inline
emuvec::v8u16& emuvec::v8u16::operator=(const v8s16& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v8u16& emuvec::v8u16::operator=(v8s16&& r)
{
        base_type::operator=(std::move(r));
        return *this;
}

inline
emuvec::v8u16& emuvec::v8u16::operator=(element_type r)
{
        base_type::operator=(int16_t(r));
        return *this;
}

// inline
inline
emuvec::masked_vec<emuvec::v8u16>
emuvec::v8u16::operator()(const mask<v8u16>& m) 
{
        return masked_vec<v8u16>(*this, m);
}


inline
emuvec::v8u16&
emuvec::operator|= (v8u16& a, const v8u16& b)
{
        impl::v_or<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator&= (v8u16& a, const v8u16& b)
{
        impl::v_and<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator^= (v8u16& a, const v8u16& b)
{
        impl::v_xor<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator+= (v8u16& a, const v8u16& b)
{
        impl::v_add<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator-= (v8u16& a, const v8u16& b)
{
        impl::v_sub<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator*= (v8u16& a, const v8u16& b)
{
        impl::v_mul<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator/=(v8u16& a, const v8u16& b)
{
        impl::v_div<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator%=(v8u16& a, const v8u16& b)
{
        impl::v_irem<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8u16::N);
        return a;
}

inline
emuvec::v8u16&
emuvec::operator<<= (v8u16& a, uint32_t b)
{
        impl::v_sl<v8u16::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

inline
emuvec::v8u16
emuvec::operator<< (const v8u16& a, uint32_t b)
{
        v8u16 r;
        impl::v_sl<v8u16::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8u16::N);
        return r;
}

inline
emuvec::v8u16&
emuvec::operator>>= (v8u16& a, uint32_t b)
{
        impl::v_sr<v8u16::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

inline
emuvec::v8u16
emuvec::operator>> (const v8u16& a, uint32_t b)
{
        v8u16 r;
        impl::v_sr<v8u16::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8u16::N);
        return r;
}

inline
emuvec::v8u16&
emuvec::operator++(v8u16& a)
{
        impl::v_inc<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

inline
emuvec::v8u16
emuvec::operator++ (v8u16& a, int)
{
        v8u16 t(a);
        impl::v_inc<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return t;
}

inline
emuvec::v8u16&
emuvec::operator--(v8u16& a)
{
        impl::v_dec<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return a;
}

inline
emuvec::v8u16
emuvec::operator-- (v8u16& a, int)
{
        v8u16 t(a);
        impl::v_dec<v8u16::element_type> ot;
        impl::v_assign_op(a(), ot, v8u16::N);
        return t;
}

inline
emuvec::v8u16
emuvec::operator-(const v8u16& a)
{
        v8u16 r;
        impl::v_neg<v8u16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8u16::N);
        return r;
}

inline
const emuvec::v8u16&
emuvec::operator+(const v8u16& a)
{
        return a;
}

inline
emuvec::v8u16
emuvec::operator~(const v8u16& a)
{
        v8u16 r;
        impl::v_not<v8u16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8u16::N);
        return r;
}

inline
emuvec::v8u16
emuvec::operator!(const v8u16& a)
{
        v8u16 r;
        impl::v_log_not<v8u16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator| (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_or<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator|| (const v8u16& a, const v8u16& b)
{
        return a | b;
}

inline
emuvec::v8u16 emuvec::operator& (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_and<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator&& (const v8u16& a, const v8u16& b)
{
        return a & b;
}

inline
emuvec::v8u16 emuvec::operator^(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_xor<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator+ (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_add<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator- (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_sub<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator* (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_mul<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16
emuvec::operator/(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_div<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16
emuvec::operator%(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_irem<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}


inline
emuvec::v8u16 emuvec::operator< (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_lt<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator<= (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_le<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator== (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_eq<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator!= (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_ne<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator>= (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_ge<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::operator> (const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_gt<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::max(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_max<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::min(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_min<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
emuvec::v8u16 emuvec::mul_hi(const v8u16& a, const v8u16& b)
{
        v8u16 r;
        impl::v_mulhi<v8u16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8u16::N);
        return r;
}

inline
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

// store.
inline
void emuvec::store(v8u16::element_type* p, const v8u16& v)
{
        impl::mem_cpy<sizeof(v8u16::element_type)*v8u16::N>::v(p, v());
}

#endif

