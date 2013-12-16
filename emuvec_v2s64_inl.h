#if !defined (__EMUVEC_V2S64_INL_H__)
#define __EMUVEC_V2S64_INL_H__ 1

#include <algorithm>

// v2s64 implementation
inline
emuvec::v2s64::element_type* emuvec::v2s64::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v2s64::element_type* emuvec::v2s64::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v2s64::element_type* emuvec::v2s64::operator()()
{
        return begin();
}

inline
const emuvec::v2s64::element_type* emuvec::v2s64::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v2s64&
emuvec::operator<<= (v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v2s64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

template <unsigned _P>
emuvec::v2s64&
emuvec::operator>>= (v2s64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v2s64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2s64::N);
        return a;
}

template <unsigned _P>
emuvec::v2s64
emuvec::operator<<(const v2s64& a, const const_u32< _P >& b)
{
        v2s64 r;
        const int val = b.val;
        impl::v_sl<v2s64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2s64::N);
        return r;
}

template <unsigned _P>
emuvec::v2s64
emuvec::operator>> (const v2s64& a, const const_u32< _P >& b)
{
        v2s64 r;
        const int val = b.val;
        impl::v_sr<v2s64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2s64::N);
        return r;
}

template < bool _P0, bool _P1 >
emuvec::v2s64 emuvec::select(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::select_2<v2s64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1 >
emuvec::v2s64 emuvec::permute(const v2s64& a)
{
        v2s64 r;
        impl::perm1_2<v2s64::element_type, _P0, _P1>::v(r(), a());
        return r;
}

template < int _P0, int _P1 >
emuvec::v2s64 emuvec::permute(const v2s64& a, const v2s64& b)
{
        v2s64 r;
        impl::perm2_2<v2s64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v2s64::element_type emuvec::extract(const v2s64& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v2s64 emuvec::insert(const v2s64& a, v2s64::element_type v)
{
        v2s64 r(a);
        r()[_I] =v;
        return r;
}

// v2s64 implementation
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

inline
void emuvec::store(v2s64::element_type* p, const v2s64& v)
{
        impl::mem_cpy<sizeof(v2s64::element_type)*v2s64::N>::v(p, v());
}

#endif

