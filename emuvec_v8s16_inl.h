#if !defined (__EMUVEC_V8S16_INL_H__)
#define __EMUVEC_INL_V8S16_H__ 1

#include <algorithm>

// v8s16 implementation
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

// store.
inline
void emuvec::store(v8s16::element_type* p, const v8s16& v)
{
        impl::mem_cpy<sizeof(v8s16::element_type)*v8s16::N>::v(p, v());
}

#endif

