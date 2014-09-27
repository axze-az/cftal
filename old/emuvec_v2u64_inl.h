#if !defined (__EMUVEC_V2U64_INL_H__)
#define __EMUVEC_V2U64_INL_H__ 1

// v2u64 implementation
inline
emuvec::v2u64::element_type* emuvec::v2u64::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v2u64::element_type* emuvec::v2u64::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v2u64::element_type* emuvec::v2u64::operator()()
{
        return begin();
}

inline
const emuvec::v2u64::element_type* emuvec::v2u64::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v2u64&
emuvec::operator<<= (v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v2u64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

template <unsigned _P>
emuvec::v2u64&
emuvec::operator>>= (v2u64& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sr<v2u64::element_type> ot(val);
        impl::v_assign_op(a(), ot, v2u64::N);
        return a;
}

template <unsigned _P>
emuvec::v2u64
emuvec::operator<<(const v2u64& a, const const_u32< _P >& b)
{
        v2u64 r;
        const int val = b.val;
        impl::v_sl<v2u64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2u64::N);
        return r;
}

template <unsigned _P>
emuvec::v2u64
emuvec::operator>> (const v2u64& a, const const_u32< _P >& b)
{
        v2u64 r;
        const int val = b.val;
        impl::v_sr<v2u64::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v2u64::N);
        return r;
}

template < bool _P0, bool _P1>
emuvec::v2u64 emuvec::select(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::select_2<v2u64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1>
emuvec::v2u64 emuvec::permute(const v2u64& a)
{
        v2u64 r;
        impl::perm1_2<v2u64::element_type, _P0, _P1>::v(r(), a());
        return r;
}

template < int _P0, int _P1>
emuvec::v2u64 emuvec::permute(const v2u64& a, const v2u64& b)
{
        v2u64 r;
        impl::perm2_2<v2u64::element_type, _P0, _P1>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v2u64::element_type emuvec::extract(const v2u64& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v2u64 emuvec::insert(const v2u64& a, v2u64::element_type v)
{
        v2u64 r(a);
        r()[_I] =v;
        return r;
}

// v2u64 implementation
inline
emuvec::v2u64::v2u64(const v2s64& r) : base_type(r)
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
emuvec::v2u64& emuvec::v2u64::operator=(const v2s64& r)
{
        base_type::operator=(r);
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

inline
void emuvec::store(v2u64::element_type* p, const v2u64& v)
{
        impl::mem_cpy<sizeof(v2u64::element_type)*v2u64::N>::v(p, v());
}

#endif

