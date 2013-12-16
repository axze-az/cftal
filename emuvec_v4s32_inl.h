#if !defined (__EMUVEC_V4S32_INL_H__)
#define __EMUVEC_V4S32_INL_H__ 1

#include <algorithm>

// v4s32 implementation
inline
emuvec::v4s32::element_type* emuvec::v4s32::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4s32::element_type* emuvec::v4s32::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v4s32::element_type* emuvec::v4s32::operator()()
{
        return begin();
}

inline
const emuvec::v4s32::element_type* emuvec::v4s32::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v4s32&
emuvec::operator<<= (v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v4s32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

template <unsigned _P>
emuvec::v4s32&
emuvec::operator>>= (v4s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v4s32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v4s32::N);
        return a;
}

template <unsigned _P>
emuvec::v4s32
emuvec::operator<<(const v4s32& a, const const_u32< _P >& b)
{
        v4s32 r;
        const int val = b.val;
        impl::v_sl<v4s32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

template <unsigned _P>
emuvec::v4s32
emuvec::operator>> (const v4s32& a, const const_u32< _P >& b)
{
        v4s32 r;
        const int val = b.val;
        impl::v_sr<v4s32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v4s32::N);
        return r;
}

template < bool _P0, bool _P1, bool _P2, bool _P3 >
emuvec::v4s32 emuvec::select(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::select_4<v4s32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4s32 emuvec::permute(const v4s32& a)
{
        v4s32 r;
        impl::perm1_4<v4s32::element_type, _P0, _P1, _P2, _P3>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
emuvec::v4s32 emuvec::permute(const v4s32& a, const v4s32& b)
{
        v4s32 r;
        impl::perm2_4<v4s32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v4s32::element_type emuvec::extract(const v4s32& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v4s32 emuvec::insert(const v4s32& a, v4s32::element_type v)
{
        v4s32 r(a);
        r()[_I] =v;
        return r;
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


inline
void emuvec::store(v4s32::element_type* p, const v4s32& v)
{
        impl::mem_cpy<sizeof(v4s32::element_type)*v4s32::N>::v(p, v());
}


#endif

