#if !defined (__EMUVEC_INL_H__)
#define __X86VEC_V4F64_INL_H__ 1
#if 0

#if !defined (__EMUVEC_H__)
#include <cftal/emuvec.h>
#error "never use this file directly"
#endif
#include <algorithm>

// v8s16 implementation
inline
emuvec::v8s16::v8s16() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

inline
emuvec::v8s16::v8s16(const v8s16& r) : base_type(r)
{
}

inline
emuvec::v8s16::v8s16(v8s16&& r) : base_type(std::move(r))
{
}

inline
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

inline
emuvec::v8s16::v8s16(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v8s16::v8s16(v8s16::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(vbegin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

inline
emuvec::v8s16::v8s16(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v8s16::v8s16(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v8s16& emuvec::v8s16::operator=(const v8s16& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

inline
emuvec::v8s16& emuvec::v8s16::operator=(v8s16&& r)
{
        swap(r);
        return *this;
}

inline
emuvec::v8s16& emuvec::v8s16::operator=(v8s16::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

// inline
inline
emuvec::masked_vec<emuvec::v8s16>
emuvec::v8s16::operator()(const mask<v8s16>& m) 
{
        return masked_vec<v8s16>(*this, m);
}

inline
emuvec::v8s16::~v8s16()
{
}

inline
emuvec::v8s16&
emuvec::operator|= (v8s16& a, const v8s16& b)
{
        impl::v_or<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator&= (v8s16& a, const v8s16& b)
{
        impl::v_and<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator^= (v8s16& a, const v8s16& b)
{
        impl::v_xor<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator+= (v8s16& a, const v8s16& b)
{
        impl::v_add<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator-= (v8s16& a, const v8s16& b)
{
        impl::v_sub<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator*= (v8s16& a, const v8s16& b)
{
        impl::v_mul<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator/=(v8s16& a, const v8s16& b)
{
        impl::v_div<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator%=(v8s16& a, const v8s16& b)
{
        impl::v_irem<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s16::N);
        return a;
}

inline
emuvec::v8s16&
emuvec::operator<<= (v8s16& a, uint32_t b)
{
        impl::v_sl<v8s16::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

inline
emuvec::v8s16
emuvec::operator<< (const v8s16& a, uint32_t b)
{
        v8s16 r;
        impl::v_sl<v8s16::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8s16::N);
        return r;
}

inline
emuvec::v8s16&
emuvec::operator>>= (v8s16& a, uint32_t b)
{
        impl::v_sr<v8s16::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

inline
emuvec::v8s16
emuvec::operator>> (const v8s16& a, uint32_t b)
{
        v8s16 r;
        impl::v_sr<v8s16::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8s16::N);
        return r;
}

inline
emuvec::v8s16&
emuvec::operator++(v8s16& a)
{
        impl::v_inc<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

inline
emuvec::v8s16
emuvec::operator++ (v8s16& a, int)
{
        v8s16 t(a);
        impl::v_inc<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, v8s16::N);
        return t;
}

inline
emuvec::v8s16&
emuvec::operator--(v8s16& a)
{
        impl::v_dec<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, v8s16::N);
        return a;
}

inline
emuvec::v8s16
emuvec::operator-- (v8s16& a, int)
{
        v8s16 t(a);
        impl::v_dec<v8s16::element_type> ot;
        impl::v_assign_op(a(), ot, v8s16::N);
        return t;
}

inline
emuvec::v8s16
emuvec::operator-(const v8s16& a)
{
        v8s16 r;
        impl::v_neg<v8s16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s16::N);
        return r;
}

inline
const emuvec::v8s16&
emuvec::operator+(const v8s16& a)
{
        return a;
}

inline
emuvec::v8s16
emuvec::operator~(const v8s16& a)
{
        v8s16 r;
        impl::v_not<v8s16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s16::N);
        return r;
}

inline
emuvec::v8s16
emuvec::operator!(const v8s16& a)
{
        v8s16 r;
        impl::v_log_not<v8s16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator| (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_or<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator|| (const v8s16& a, const v8s16& b)
{
        return a | b;
}

inline
emuvec::v8s16 emuvec::operator& (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_and<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator&& (const v8s16& a, const v8s16& b)
{
        return a & b;
}

inline
emuvec::v8s16 emuvec::operator^(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_xor<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator+ (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_add<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator- (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_sub<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator* (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_mul<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16
emuvec::operator/(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_div<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16
emuvec::operator%(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_irem<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator< (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_lt<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator<= (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_le<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator== (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_eq<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator!= (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_ne<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator>= (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_ge<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::operator> (const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_gt<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::max(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_max<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::min(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_min<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::abs(const v8s16& a)
{
        v8s16 r;
        impl::v_abs<v8s16::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s16::N);
        return r;
}

inline
emuvec::v8s16 emuvec::mul_hi(const v8s16& a, const v8s16& b)
{
        v8s16 r;
        impl::v_mulhi<v8s16::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s16::N);
        return r;
}

inline
bool emuvec::no_signs(const v8s16& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v8s16::N));
        return sgns == 0;
}

inline
bool emuvec::all_signs(const v8s16& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v8s16::N));
        return sgns == 0xFF;

}

inline
bool emuvec::both_signs(const v8s16& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v8s16::N));
        return sgns != 0xFF && sgns != 0;
}

inline
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
inline
emuvec::v8u16::v8u16() : base_type()
{
}

inline
emuvec::v8u16::v8u16(const v8u16& r) : base_type(r)
{
}

inline
emuvec::v8u16::v8u16(const v8s16& r) : base_type(r)
{
}

inline
emuvec::v8u16::v8u16(v8u16&& r) : base_type(std::move(r))
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
emuvec::v8u16& emuvec::v8u16::operator=(const v8u16& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v8u16& emuvec::v8u16::operator=(const v8s16& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v8u16& emuvec::v8u16::operator=(v8u16&& r)
{
        base_type::operator=(std::move(r));
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
emuvec::v8u16::~v8u16()
{
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

// v4s32 implementation
inline
emuvec::v4s32::v4s32() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

inline
emuvec::v4s32::v4s32(const v4s32& r) : base_type(r)
{
}

inline
emuvec::v4s32::v4s32(v4s32&& r) : base_type(std::move(r))
{
}

inline
emuvec::v4s32::v4s32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01; p[2] = p02; p[3] = p03;
}

inline
emuvec::v4s32::v4s32(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v4s32::v4s32(v4s32::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(vbegin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

inline
emuvec::v4s32::v4s32(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v4s32::v4s32(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4s32::v4s32(const mem::aligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4s32::v4s32(const mem::unaligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4s32& emuvec::v4s32::operator=(const v4s32& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

inline
emuvec::v4s32& emuvec::v4s32::operator=(v4s32&& r)
{
        swap(r);
        return *this;
}

inline
emuvec::v4s32& emuvec::v4s32::operator=(v4s32::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

inline
emuvec::masked_vec<emuvec::v4s32>
emuvec::v4s32::operator()(const mask<v4s32>& m) 
{
        return masked_vec<v4s32>(*this, m);
}

inline
emuvec::v4s32::~v4s32()
{
}

inline
emuvec::v4s32&
emuvec::operator|= (v4s32& a, const v4s32& b)
{
        impl::v_or<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator&= (v4s32& a, const v4s32& b)
{
        impl::v_and<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator^= (v4s32& a, const v4s32& b)
{
        impl::v_xor<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator+= (v4s32& a, const v4s32& b)
{
        impl::v_add<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator-= (v4s32& a, const v4s32& b)
{
        impl::v_sub<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator*= (v4s32& a, const v4s32& b)
{
        impl::v_mul<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator/=(v4s32& a, const v4s32& b)
{
        impl::v_div<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator%=(v4s32& a, const v4s32& b)
{
        impl::v_irem<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4s32::N);
        return a;
}

inline
emuvec::v4s32&
emuvec::operator<<= (v4s32& a, uint32_t b)
{
        impl::v_sl<v4s32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

inline
emuvec::v4s32
emuvec::operator<< (const v4s32& a, uint32_t b)
{
        v4s32 r;
        impl::v_sl<v4s32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

inline
emuvec::v4s32&
emuvec::operator>>= (v4s32& a, uint32_t b)
{
        impl::v_sr<v4s32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

inline
emuvec::v4s32
emuvec::operator>> (const v4s32& a, uint32_t b)
{
        v4s32 r;
        impl::v_sr<v4s32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

inline
emuvec::v4s32&
emuvec::operator++(v4s32& a)
{
        impl::v_inc<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

inline
emuvec::v4s32
emuvec::operator++ (v4s32& a, int)
{
        v4s32 t(a);
        impl::v_inc<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return t;
}

inline
emuvec::v4s32&
emuvec::operator--(v4s32& a)
{
        impl::v_dec<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

inline
emuvec::v4s32
emuvec::operator-- (v4s32& a, int)
{
        v4s32 t(a);
        impl::v_dec<v4s32::element_type> ot;
        impl::v_assign_op(a(), ot, v4s32::N);
        return t;
}

inline
emuvec::v4s32
emuvec::operator-(const v4s32& a)
{
        v4s32 r;
        impl::v_neg<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

inline
const emuvec::v4s32&
emuvec::operator+(const v4s32& a)
{
        return a;
}

inline
emuvec::v4s32
emuvec::operator~(const v4s32& a)
{
        v4s32 r;
        impl::v_not<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

inline
emuvec::v4s32
emuvec::operator!(const v4s32& a)
{
        v4s32 r;
        impl::v_log_not<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator| (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_or<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator|| (const v4s32& a, const v4s32& b)
{
        return a | b;
}

inline
emuvec::v4s32 emuvec::operator& (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_and<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator&& (const v4s32& a, const v4s32& b)
{
        return a & b;
}

inline
emuvec::v4s32 emuvec::operator^(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_xor<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator+ (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_add<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator- (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_sub<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator* (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_mul<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32
emuvec::operator/(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_div<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32
emuvec::operator%(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_irem<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator< (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_lt<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator<= (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_le<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator== (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_eq<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator!= (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_ne<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator>= (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_ge<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::operator> (const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_gt<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::max(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_max<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::min(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_min<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::abs(const v4s32& a)
{
        v4s32 r;
        impl::v_abs<v4s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4s32::N);
        return r;
}

inline
emuvec::v4s32 emuvec::mul_hi(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::v_mulhi<v4s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4s32::N);
        return r;
}

inline
bool emuvec::no_signs(const v4s32& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v4s32::N));
        return sgns == 0;
}

inline
bool emuvec::all_signs(const v4s32& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v4s32::N));
        return sgns == 0x0f;

}

inline
bool emuvec::both_signs(const v4s32& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v4s32::N));
        return sgns != 0x0f && sgns != 0;
}

inline
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
inline
emuvec::v4u32::v4u32() : base_type()
{
}

inline
emuvec::v4u32::v4u32(const v4u32& r) : base_type(r)
{
}

inline
emuvec::v4u32::v4u32(const v4s32& r) : base_type(r)
{
}

inline
emuvec::v4u32::v4u32(v4u32&& r) : base_type(std::move(r))
{
}

inline
emuvec::v4u32::v4u32(v4s32&& r) : base_type(std::move(r))
{
}

inline
emuvec::v4u32::v4u32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type(p00, p01, p02, p03)
{
}

inline
emuvec::v4u32::v4u32(element_type r): base_type(r)
{
}

inline
emuvec::v4u32::v4u32(v4u32::element_type r, bool broadcast)
        : base_type(r, broadcast)
{
}

inline
emuvec::v4u32::v4u32(const mem::addr_bcast<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr_bcast<int32_t>&>(r))
{
}

inline
emuvec::v4u32::v4u32(const mem::addr<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr<int32_t>&>(r))
{
}

inline
emuvec::v4u32& emuvec::v4u32::operator=(const v4u32& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v4u32& emuvec::v4u32::operator=(const v4s32& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v4u32& emuvec::v4u32::operator=(v4u32&& r)
{
        base_type::operator=(std::move(r));
        return *this;
}

inline
emuvec::v4u32& emuvec::v4u32::operator=(v4s32&& r)
{
        base_type::operator=(std::move(r));
        return *this;
}

inline
emuvec::v4u32& emuvec::v4u32::operator=(element_type r)
{
        base_type::operator=(int32_t(r));
        return *this;
}

inline
emuvec::masked_vec<emuvec::v4u32>
emuvec::v4u32::operator()(const mask<v4u32>& m) 
{
        return masked_vec<v4u32>(*this, m);
}

inline
emuvec::v4u32::~v4u32()
{
}

inline
emuvec::v4u32&
emuvec::operator|= (v4u32& a, const v4u32& b)
{
        impl::v_or<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator&= (v4u32& a, const v4u32& b)
{
        impl::v_and<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator^= (v4u32& a, const v4u32& b)
{
        impl::v_xor<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator+= (v4u32& a, const v4u32& b)
{
        impl::v_add<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator-= (v4u32& a, const v4u32& b)
{
        impl::v_sub<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator*= (v4u32& a, const v4u32& b)
{
        impl::v_mul<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator/=(v4u32& a, const v4u32& b)
{
        impl::v_div<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator%=(v4u32& a, const v4u32& b)
{
        impl::v_irem<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4u32::N);
        return a;
}

inline
emuvec::v4u32&
emuvec::operator<<= (v4u32& a, uint32_t b)
{
        impl::v_sl<v4u32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

inline
emuvec::v4u32
emuvec::operator<< (const v4u32& a, uint32_t b)
{
        v4u32 r;
        impl::v_sl<v4u32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

inline
emuvec::v4u32&
emuvec::operator>>= (v4u32& a, uint32_t b)
{
        impl::v_sr<v4u32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

inline
emuvec::v4u32
emuvec::operator>> (const v4u32& a, uint32_t b)
{
        v4u32 r;
        impl::v_sr<v4u32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

inline
emuvec::v4u32&
emuvec::operator++(v4u32& a)
{
        impl::v_inc<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

inline
emuvec::v4u32
emuvec::operator++ (v4u32& a, int)
{
        v4u32 t(a);
        impl::v_inc<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return t;
}

inline
emuvec::v4u32&
emuvec::operator--(v4u32& a)
{
        impl::v_dec<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

inline
emuvec::v4u32
emuvec::operator-- (v4u32& a, int)
{
        v4u32 t(a);
        impl::v_dec<v4u32::element_type> ot;
        impl::v_assign_op(a(), ot, v4u32::N);
        return t;
}

inline
emuvec::v4u32
emuvec::operator-(const v4u32& a)
{
        v4u32 r;
        impl::v_neg<v4u32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4u32::N);
        return r;
}

inline
const emuvec::v4u32&
emuvec::operator+(const v4u32& a)
{
        return a;
}

inline
emuvec::v4u32
emuvec::operator~(const v4u32& a)
{
        v4u32 r;
        impl::v_not<v4u32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4u32::N);
        return r;
}

inline
emuvec::v4u32
emuvec::operator!(const v4u32& a)
{
        v4u32 r;
        impl::v_log_not<v4u32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator| (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_or<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator|| (const v4u32& a, const v4u32& b)
{
        return a | b;
}

inline
emuvec::v4u32 emuvec::operator& (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_and<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator&& (const v4u32& a, const v4u32& b)
{
        return a & b;
}

inline
emuvec::v4u32 emuvec::operator^(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_xor<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator+ (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_add<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator- (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_sub<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator* (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_mul<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32
emuvec::operator/(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_div<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32
emuvec::operator%(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_irem<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator< (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_lt<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator<= (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_le<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator== (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_eq<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator!= (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_ne<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator>= (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_ge<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::operator> (const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_gt<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::max(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_max<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::min(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_min<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
emuvec::v4u32 emuvec::mul_hi(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::v_mulhi<v4u32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4u32::N);
        return r;
}

inline
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


// v2s64 implementation
inline
emuvec::v2s64::v2s64() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

inline
emuvec::v2s64::v2s64(const v2s64& r) : base_type(r)
{
}

inline
emuvec::v2s64::v2s64(v2s64&& r) : base_type(std::move(r))
{
}

inline
emuvec::v2s64::v2s64(element_type p00, element_type p01)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01;
}

inline
emuvec::v2s64::v2s64(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v2s64::v2s64(v2s64::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(vbegin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

inline
emuvec::v2s64::v2s64(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v2s64::v2s64(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v2s64& emuvec::v2s64::operator=(const v2s64& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

inline
emuvec::v2s64& emuvec::v2s64::operator=(v2s64&& r)
{
        swap(r);
        return *this;
}

inline
emuvec::v2s64& emuvec::v2s64::operator=(v2s64::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

inline
emuvec::masked_vec<emuvec::v2s64>
emuvec::v2s64::operator()(const mask<v2s64>& m) 
{
        return masked_vec<v2s64>(*this, m);
}

inline
emuvec::v2s64::~v2s64()
{
}

inline
emuvec::v2s64&
emuvec::operator|= (v2s64& a, const v2s64& b)
{
        impl::v_or<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator&= (v2s64& a, const v2s64& b)
{
        impl::v_and<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator^= (v2s64& a, const v2s64& b)
{
        impl::v_xor<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator+= (v2s64& a, const v2s64& b)
{
        impl::v_add<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator-= (v2s64& a, const v2s64& b)
{
        impl::v_sub<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator*= (v2s64& a, const v2s64& b)
{
        impl::v_mul<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator/=(v2s64& a, const v2s64& b)
{
        impl::v_div<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator%=(v2s64& a, const v2s64& b)
{
        impl::v_irem<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2s64::N);
        return a;
}

inline
emuvec::v2s64&
emuvec::operator<<= (v2s64& a, uint64_t b)
{
        impl::v_sl<v2s64::element_type> ot(b);
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

inline
emuvec::v2s64
emuvec::operator<< (const v2s64& a, uint64_t b)
{
        v2s64 r;
        impl::v_sl<v2s64::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v2s64::N);
        return r;
}

inline
emuvec::v2s64&
emuvec::operator>>= (v2s64& a, uint64_t b)
{
        impl::v_sr<v2s64::element_type> ot(b);
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

inline
emuvec::v2s64
emuvec::operator>> (const v2s64& a, uint64_t b)
{
        v2s64 r;
        impl::v_sr<v2s64::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v2s64::N);
        return r;
}

inline
emuvec::v2s64&
emuvec::operator++(v2s64& a)
{
        impl::v_inc<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

inline
emuvec::v2s64
emuvec::operator++ (v2s64& a, int)
{
        v2s64 t(a);
        impl::v_inc<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, v2s64::N);
        return t;
}

inline
emuvec::v2s64&
emuvec::operator--(v2s64& a)
{
        impl::v_dec<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

inline
emuvec::v2s64
emuvec::operator-- (v2s64& a, int)
{
        v2s64 t(a);
        impl::v_dec<v2s64::element_type> ot;
        impl::v_assign_op(a(), ot, v2s64::N);
        return t;
}

inline
emuvec::v2s64
emuvec::operator-(const v2s64& a)
{
        v2s64 r;
        impl::v_neg<v2s64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2s64::N);
        return r;
}

inline
const emuvec::v2s64&
emuvec::operator+(const v2s64& a)
{
        return a;
}

inline
emuvec::v2s64
emuvec::operator~(const v2s64& a)
{
        v2s64 r;
        impl::v_not<v2s64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2s64::N);
        return r;
}

inline
emuvec::v2s64
emuvec::operator!(const v2s64& a)
{
        v2s64 r;
        impl::v_log_not<v2s64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator| (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_or<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator|| (const v2s64& a, const v2s64& b)
{
        return a | b;
}

inline
emuvec::v2s64 emuvec::operator& (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_and<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator&& (const v2s64& a, const v2s64& b)
{
        return a & b;
}

inline
emuvec::v2s64 emuvec::operator^(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_xor<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator+ (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_add<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator- (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_sub<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator* (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_mul<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64
emuvec::operator/(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_div<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64
emuvec::operator%(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_irem<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}


inline
emuvec::v2s64 emuvec::operator< (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_lt<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator<= (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_le<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator== (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_eq<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator!= (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_ne<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator>= (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_ge<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::operator> (const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_gt<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::max(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_max<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::min(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_min<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::abs(const v2s64& a)
{
        v2s64 r;
        impl::v_abs<v2s64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2s64::N);
        return r;
}

inline
emuvec::v2s64 emuvec::mul_hi(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::v_mulhi<v2s64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2s64::N);
        return r;
}

inline
bool emuvec::no_signs(const v2s64& a)
{
        uint64_t sgns(impl::get_signs_32(a(), v2s64::N));
        return sgns == 0;
}

inline
bool emuvec::all_signs(const v2s64& a)
{
        uint64_t sgns(impl::get_signs_32(a(), v2s64::N));
        return sgns == 0x0f;

}

inline
bool emuvec::both_signs(const v2s64& a)
{
        uint64_t sgns(impl::get_signs_32(a(), v2s64::N));
        return sgns != 0x0f && sgns != 0;
}

inline
emuvec::v2s64 emuvec::select(const v2s64& msk,
                             const v2s64& on_true,
                             const v2s64& on_false)
{
        v2s64 r;
        impl::select<v2s64::element_type>::v(r(),
                                             msk(), on_true(), on_false(),
                                             v2s64::N);
        return r;
}

// v2u64 implementation
inline
emuvec::v2u64::v2u64() : base_type()
{
}

inline
emuvec::v2u64::v2u64(const v2u64& r) : base_type(r)
{
}

inline
emuvec::v2u64::v2u64(const v2s64& r) : base_type(r)
{
}

inline
emuvec::v2u64::v2u64(v2u64&& r) : base_type(std::move(r))
{
}

inline
emuvec::v2u64::v2u64(v2s64&& r) : base_type(std::move(r))
{
}

inline
emuvec::v2u64::v2u64(element_type p00, element_type p01)
        : base_type(base_type::element_type(p00), 
                    base_type::element_type(p01))
{
}

inline
emuvec::v2u64::v2u64(element_type r): base_type(r)
{
}

inline
emuvec::v2u64::v2u64(v2u64::element_type r, bool broadcast)
        : base_type(r, broadcast)
{
}

inline
emuvec::v2u64::v2u64(const mem::addr_bcast<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr_bcast<int64_t>&>(r))
{
}

inline
emuvec::v2u64::v2u64(const mem::addr<element_type>& r)
        : base_type(reinterpret_cast<const mem::addr<int64_t>&>(r))
{
}

inline
emuvec::v2u64& emuvec::v2u64::operator=(const v2u64& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v2u64& emuvec::v2u64::operator=(const v2s64& r)
{
        base_type::operator=(r);
        return *this;
}

inline
emuvec::v2u64& emuvec::v2u64::operator=(v2u64&& r)
{
        base_type::operator=(std::move(r));
        return *this;
}

inline
emuvec::v2u64& emuvec::v2u64::operator=(v2s64&& r)
{
        base_type::operator=(std::move(r));
        return *this;
}

inline
emuvec::v2u64& emuvec::v2u64::operator=(element_type r)
{
        base_type::operator=(int64_t(r));
        return *this;
}

inline
emuvec::masked_vec<emuvec::v2u64>
emuvec::v2u64::operator()(const mask<v2u64>& m) 
{
        return masked_vec<v2u64>(*this, m);
}

inline
emuvec::v2u64::~v2u64()
{
}

inline
emuvec::v2u64&
emuvec::operator|= (v2u64& a, const v2u64& b)
{
        impl::v_or<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator&= (v2u64& a, const v2u64& b)
{
        impl::v_and<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator^= (v2u64& a, const v2u64& b)
{
        impl::v_xor<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator+= (v2u64& a, const v2u64& b)
{
        impl::v_add<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator-= (v2u64& a, const v2u64& b)
{
        impl::v_sub<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator*= (v2u64& a, const v2u64& b)
{
        impl::v_mul<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator/=(v2u64& a, const v2u64& b)
{
        impl::v_div<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator%=(v2u64& a, const v2u64& b)
{
        impl::v_irem<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2u64::N);
        return a;
}

inline
emuvec::v2u64&
emuvec::operator<<= (v2u64& a, uint64_t b)
{
        impl::v_sl<v2u64::element_type> ot(b);
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

inline
emuvec::v2u64
emuvec::operator<< (const v2u64& a, uint64_t b)
{
        v2u64 r;
        impl::v_sl<v2u64::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v2u64::N);
        return r;
}

inline
emuvec::v2u64&
emuvec::operator>>= (v2u64& a, uint64_t b)
{
        impl::v_sr<v2u64::element_type> ot(b);
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

inline
emuvec::v2u64
emuvec::operator>> (const v2u64& a, uint64_t b)
{
        v2u64 r;
        impl::v_sr<v2u64::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v2u64::N);
        return r;
}

inline
emuvec::v2u64&
emuvec::operator++(v2u64& a)
{
        impl::v_inc<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

inline
emuvec::v2u64
emuvec::operator++ (v2u64& a, int)
{
        v2u64 t(a);
        impl::v_inc<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, v2u64::N);
        return t;
}

inline
emuvec::v2u64&
emuvec::operator--(v2u64& a)
{
        impl::v_dec<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

inline
emuvec::v2u64
emuvec::operator-- (v2u64& a, int)
{
        v2u64 t(a);
        impl::v_dec<v2u64::element_type> ot;
        impl::v_assign_op(a(), ot, v2u64::N);
        return t;
}

inline
emuvec::v2u64
emuvec::operator-(const v2u64& a)
{
        v2u64 r;
        impl::v_neg<v2u64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2u64::N);
        return r;
}

inline
const emuvec::v2u64&
emuvec::operator+(const v2u64& a)
{
        return a;
}

inline
emuvec::v2u64
emuvec::operator~(const v2u64& a)
{
        v2u64 r;
        impl::v_not<v2u64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2u64::N);
        return r;
}

inline
emuvec::v2u64
emuvec::operator!(const v2u64& a)
{
        v2u64 r;
        impl::v_log_not<v2u64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator| (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_or<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator|| (const v2u64& a, const v2u64& b)
{
        return a | b;
}

inline
emuvec::v2u64 emuvec::operator& (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_and<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator&& (const v2u64& a, const v2u64& b)
{
        return a & b;
}

inline
emuvec::v2u64 emuvec::operator^(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_xor<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator+ (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_add<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator- (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_sub<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator* (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_mul<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64
emuvec::operator/(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_div<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64
emuvec::operator%(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_irem<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator< (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_lt<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator<= (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_le<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator== (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_eq<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator!= (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_ne<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator>= (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_ge<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::operator> (const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_gt<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::max(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_max<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::min(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_min<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::mul_hi(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::v_mulhi<v2u64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2u64::N);
        return r;
}

inline
emuvec::v2u64 emuvec::select(const v2u64& msk,
                             const v2u64& on_true,
                             const v2u64& on_false)
{
        v2u64 r;
        impl::select<v2u64::element_type>::v(r(),
                                             msk(), on_true(), on_false(),
                                             v2u64::N);
        return r;
}

// v4f32 implementation
inline
emuvec::v4f32::v4f32() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

inline
emuvec::v4f32::v4f32(const v4f32& r) : base_type(r)
{
}

inline
emuvec::v4f32::v4f32(v4f32&& r) : base_type(std::move(r))
{
}

inline
emuvec::v4f32::v4f32(element_type p00, element_type p01,
                     element_type p02, element_type p03)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01; p[2] = p02; p[3] = p03;
}

inline
emuvec::v4f32::v4f32(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v4f32::v4f32(v4f32::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(vbegin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

inline
emuvec::v4f32::v4f32(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v4f32::v4f32(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4f32::v4f32(const mem::aligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4f32::v4f32(const mem::unaligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4f32& emuvec::v4f32::operator=(const v4f32& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

inline
emuvec::v4f32& emuvec::v4f32::operator=(v4f32&& r)
{
        swap(r);
        return *this;
}

inline
emuvec::v4f32& emuvec::v4f32::operator=(v4f32::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

inline
emuvec::masked_vec<emuvec::v4f32>
emuvec::v4f32::operator()(const mask<v4f32>& m) 
{
        return masked_vec<v4f32>(*this, m);
}

inline
emuvec::v4f32::~v4f32()
{
}

inline
emuvec::v4f32&
emuvec::operator|= (v4f32& a, const v4f32& b)
{
        impl::v_f_or<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f32::N);
        return a;
}

inline
emuvec::v4f32&
emuvec::operator&= (v4f32& a, const v4f32& b)
{
        impl::v_f_and<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f32::N);
        return a;
}

inline
emuvec::v4f32&
emuvec::operator^= (v4f32& a, const v4f32& b)
{
        impl::v_f_xor<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f32::N);
        return a;
}

inline
emuvec::v4f32&
emuvec::operator++(v4f32& a)
{
        impl::v_inc<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, v4f32::N);
        return a;
}

inline
emuvec::v4f32
emuvec::operator++ (v4f32& a, int)
{
        v4f32 t(a);
        impl::v_inc<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, v4f32::N);
        return t;
}

inline
emuvec::v4f32&
emuvec::operator--(v4f32& a)
{
        impl::v_dec<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, v4f32::N);
        return a;
}

inline
emuvec::v4f32
emuvec::operator-- (v4f32& a, int)
{
        v4f32 t(a);
        impl::v_dec<v4f32::element_type> ot;
        impl::v_assign_op(a(), ot, v4f32::N);
        return t;
}

inline
emuvec::v4f32
emuvec::operator-(const v4f32& a)
{
        v4f32 t;
        impl::v_neg<v4f32::element_type> ot;
        impl::v_assign_op(t(), ot, v4f32::N);
        return t;
}

inline
const emuvec::v4f32&
emuvec::operator+(const v4f32& a)
{
        return a;
}

inline
emuvec::v4f32
emuvec::operator~(const v4f32& a)
{
        v4f32 t;
        impl::v_f_not<v4f32::element_type> ot;
        impl::v_assign_op(t(), ot, v4f32::N);
        return t;
}

inline
emuvec::v4f32
emuvec::operator!(const v4f32& a)
{
        v4f32 t;
        impl::v_log_not<v4f32::element_type> ot;
        impl::v_assign_op(t(), ot, v4f32::N);
        return t;
}

inline
emuvec::v4f32 emuvec::operator| (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_f_or<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator|| (const v4f32& a, const v4f32& b)
{
        return a | b;
}

inline
emuvec::v4f32 emuvec::operator& (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_f_and<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator&& (const v4f32& a, const v4f32& b)
{
        return a & b;
}

inline
emuvec::v4f32 emuvec::operator^(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_f_xor<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator< (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_lt<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator<= (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_le<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator== (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_eq<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator!= (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_ne<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator>= (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_ge<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::operator> (const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_ge<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
bool emuvec::all_signs(const v4f32& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v4f32::N));
        return sgn == 0x0f;
}

inline
bool emuvec::both_signs(const v4f32& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v4f32::N));
        return sgn != 0x0f && sgn != 0;
}

inline
bool emuvec::no_signs(const v4f32& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v4f32::N));
        return sgn == 0;
}

inline
emuvec::v4f32 emuvec::max(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_max<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::min(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::v_min<v4f32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::abs(const v4f32& a)
{
        v4f32 r;
        impl::v_abs<v4f32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::sqrt(const v4f32& a)
{
        v4f32 r;
        impl::v_sqrt<v4f32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::rint(const v4f32& a)
{
        v4f32 r;
        impl::v_rint<v4f32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::floor(const v4f32& a)
{
        v4f32 r;
        impl::v_floor<v4f32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::ceil(const v4f32& a)
{
        v4f32 r;
        impl::v_ceil<v4f32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::trunc(const v4f32& a)
{
        v4f32 r;
        impl::v_trunc<v4f32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f32::N);
        return r;
}

inline
emuvec::v4f32 emuvec::select(const v4f32& msk,
                             const v4f32& on_true,
                             const v4f32& on_false)
{
        v4f32 r;
        impl::select<v4f32::element_type>::v(r(), msk(), on_true(), on_false(),
                                             v4f32::N);
        return r;
}

// v2f64 implementation
inline
emuvec::v2f64::v2f64() : base_type()
{
        std::uninitialized_fill_n(begin(), N, 0);
}

inline
emuvec::v2f64::v2f64(const v2f64& r) : base_type(r)
{
}

inline
emuvec::v2f64::v2f64(v2f64&& r) : base_type(std::move(r))
{
}

inline
emuvec::v2f64::v2f64(element_type p00, element_type p01)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01;
}

inline
emuvec::v2f64::v2f64(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v2f64::v2f64(v2f64::element_type r, bool broadcast)
        : base_type()
{
        if (broadcast) {
                std::uninitialized_fill_n(begin(), N, r);
        } else {
                get_allocator().construct(vbegin(), r);
                std::uninitialized_fill_n(begin()+1, N-1, 0);
        }
}

inline
emuvec::v2f64::v2f64(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v2f64::v2f64(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v2f64::v2f64(const mem::aligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v2f64::v2f64(const mem::unaligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v2f64& emuvec::v2f64::operator=(const v2f64& r)
{
        if (&r != this)
                std::copy_n(r.begin(), N, begin());
        return *this;
}

inline
emuvec::v2f64& emuvec::v2f64::operator=(v2f64&& r)
{
        swap(r);
        return *this;
}

inline
emuvec::v2f64& emuvec::v2f64::operator=(v2f64::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

inline
emuvec::masked_vec<emuvec::v2f64>
emuvec::v2f64::operator()(const mask<v2f64>& m) 
{
        return masked_vec<v2f64>(*this, m);
}

inline
emuvec::v2f64::~v2f64()
{
}

inline
emuvec::v2f64&
emuvec::operator|= (v2f64& a, const v2f64& b)
{
        impl::v_f_or<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2f64::N);
        return a;
}

inline
emuvec::v2f64&
emuvec::operator&= (v2f64& a, const v2f64& b)
{
        impl::v_f_and<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2f64::N);
        return a;
}

inline
emuvec::v2f64&
emuvec::operator^= (v2f64& a, const v2f64& b)
{
        impl::v_f_xor<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v2f64::N);
        return a;
}

inline
emuvec::v2f64&
emuvec::operator++(v2f64& a)
{
        impl::v_inc<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, v2f64::N);
        return a;
}

inline
emuvec::v2f64
emuvec::operator++ (v2f64& a, int)
{
        v2f64 t(a);
        impl::v_inc<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, v2f64::N);
        return t;
}

inline
emuvec::v2f64&
emuvec::operator--(v2f64& a)
{
        impl::v_dec<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, v2f64::N);
        return a;
}

inline
emuvec::v2f64
emuvec::operator-- (v2f64& a, int)
{
        v2f64 t(a);
        impl::v_dec<v2f64::element_type> ot;
        impl::v_assign_op(a(), ot, v2f64::N);
        return t;
}

inline
emuvec::v2f64
emuvec::operator-(const v2f64& a)
{
        v2f64 t;
        impl::v_neg<v2f64::element_type> ot;
        impl::v_assign_op(t(), ot, v2f64::N);
        return t;
}

inline
const emuvec::v2f64&
emuvec::operator+(const v2f64& a)
{
        return a;
}

inline
emuvec::v2f64
emuvec::operator~(const v2f64& a)
{
        v2f64 t;
        impl::v_f_not<v2f64::element_type> ot;
        impl::v_assign_op(t(), ot, v2f64::N);
        return t;
}

inline
emuvec::v2f64
emuvec::operator!(const v2f64& a)
{
        v2f64 t;
        impl::v_log_not<v2f64::element_type> ot;
        impl::v_assign_op(t(), ot, v2f64::N);
        return t;
}

inline
emuvec::v2f64 emuvec::operator| (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_f_or<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator|| (const v2f64& a, const v2f64& b)
{
        return a | b;
}

inline
emuvec::v2f64 emuvec::operator& (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_f_and<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator&& (const v2f64& a, const v2f64& b)
{
        return a & b;
}

inline
emuvec::v2f64 emuvec::operator^(const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_f_xor<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator< (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_lt<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator<= (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_le<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator== (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_eq<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator!= (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_ne<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator>= (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_ge<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::operator> (const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_ge<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
bool emuvec::all_signs(const v2f64& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v2f64::N));
        return sgn == 0x03;
}

inline
bool emuvec::both_signs(const v2f64& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v2f64::N));
        return sgn != 0x03 && sgn != 0;
}


inline
bool emuvec::no_signs(const v2f64& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v2f64::N));
        return sgn == 0;
}

inline
emuvec::v2f64 emuvec::max(const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_max<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::min(const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_min<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::abs(const v2f64& a)
{
        v2f64 r;
        impl::v_abs<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::sqrt(const v2f64& a)
{
        v2f64 r;
        impl::v_sqrt<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::rint(const v2f64& a)
{
        v2f64 r;
        impl::v_rint<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::floor(const v2f64& a)
{
        v2f64 r;
        impl::v_floor<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::ceil(const v2f64& a)
{
        v2f64 r;
        impl::v_ceil<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::trunc(const v2f64& a)
{
        v2f64 r;
        impl::v_trunc<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::select(const v2f64& msk,
                             const v2f64& on_true,
                             const v2f64& on_false)
{
        v2f64 r;
        impl::select<v2f64::element_type>::v(r(), msk(), on_true(), on_false(),
                                             v2f64::N);
        return r;
}

// store.
inline
void emuvec::store(v8s16::element_type* p, const v8s16& v)
{
        impl::mem_cpy<sizeof(v8s16::element_type)*v8s16::N>::v(p, v());
}

inline
void emuvec::store(v8u16::element_type* p, const v8u16& v)
{
        impl::mem_cpy<sizeof(v8u16::element_type)*v8u16::N>::v(p, v());
}

inline
void emuvec::store(v4s32::element_type* p, const v4s32& v)
{
        impl::mem_cpy<sizeof(v4s32::element_type)*v4s32::N>::v(p, v());
}

inline
void emuvec::store(v4u32::element_type* p, const v4u32& v)
{
        impl::mem_cpy<sizeof(v4u32::element_type)*v4u32::N>::v(p, v());
}

inline
void emuvec::store(v4f32::element_type* p, const v4f32& v)
{
        impl::mem_cpy<sizeof(v4f32::element_type)*v4f32::N>::v(p, v());
}

inline
void emuvec::store(v2f64::element_type* p, const v2f64& v)
{
        impl::mem_cpy<sizeof(v2f64::element_type)*v2f64::N>::v(p, v());
}

#endif 
#endif
