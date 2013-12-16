#if !defined (__EMUVEC_V4U32_INL_H__)
#define __EMUVEC_V4U32_INL_H__ 1

#include <algorithm>

// v4u32 implementation
inline
emuvec::v4u32::element_type* emuvec::v4u32::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4u32::element_type* emuvec::v4u32::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v4u32::element_type* emuvec::v4u32::operator()()
{
        return begin();
}

inline
const emuvec::v4u32::element_type* emuvec::v4u32::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v4u32&
emuvec::operator<<= (v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v4u32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

template <unsigned _P>
emuvec::v4u32&
emuvec::operator>>= (v4u32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v4u32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4u32::N);
        return a;
}

template <unsigned _P>
emuvec::v4u32
emuvec::operator<<(const v4u32& a, const const_u32< _P >& b)
{
        v4u32 r;
        const int val = b.val;
        impl::v_sl<v4u32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

template <unsigned _P>
emuvec::v4u32
emuvec::operator>> (const v4u32& a, const const_u32< _P >& b)
{
        v4u32 r;
        const int val = b.val;
        impl::v_sr<v4u32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4u32::N);
        return r;
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
emuvec::v4u32 emuvec::select(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::select_4<v4u32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4u32 emuvec::permute(const v4u32& a)
{
        v4u32 r;
        impl::perm1_4<v4u32::element_type, _P0, _P1, _P2, _P3>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4u32 emuvec::permute(const v4u32& a, const v4u32& b)
{
        v4u32 r;
        impl::perm2_4<v4u32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v4u32::element_type emuvec::extract(const v4u32& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v4u32 emuvec::insert(const v4u32& a, v4u32::element_type v)
{
        v4u32 r(a);
        r()[_I] =v;
        return r;
}

// v4u32 implementation
inline
emuvec::v4u32::v4u32(const v4s32& r) : base_type(r)
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
emuvec::v4u32& emuvec::v4u32::operator=(const v4s32& r)
{
        base_type::operator=(r);
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

inline
void emuvec::store(v4u32::element_type* p, const v4u32& v)
{
        impl::mem_cpy<sizeof(v4u32::element_type)*v4u32::N>::v(p, v());
}

#endif

