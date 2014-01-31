#if !defined (__EMUVEC_V2F64_INL_H__)
#define __EMUVEC_V2F64_INL_H__ 1

#include <algorithm>
// v2f64 implementation
inline
emuvec::v2f64::element_type* emuvec::v2f64::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v2f64::element_type* emuvec::v2f64::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v2f64::element_type* emuvec::v2f64::operator()()
{
        return begin();
}

inline
const emuvec::v2f64::element_type* emuvec::v2f64::operator()() const
{
        return begin();
}

template <template <class _V> class _OP, class _L, class _R>
inline
emuvec::v2f64::v2f64(const expr<_OP<v2f64>, _L, _R>& r)
        : base_type()
{
        element_type* p= begin();
        for (size_t i=0; i<N; ++i)
                p[i] = eval(r, i);
}

template < bool _P0, bool _P1>
emuvec::v2f64 emuvec::select(const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::select_2<v2f64::element_type, _P0, _P1>::v(r(), a(), b());
        return r;
}

template < int _P0, int _P1 >
emuvec::v2f64 emuvec::permute(const v2f64& a)
{
        v2f64 r;
        impl::perm1_2<v2f64::element_type, _P0, _P1>::v(r(), a());
        return r;
}

template <int _P0, int _P1 >
emuvec::v2f64 emuvec::permute(const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::perm2_2<v2f64::element_type, _P0, _P1>::v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v2f64::element_type emuvec::extract(const v2f64& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v2f64 emuvec::insert(const v2f64& a, v2f64::element_type v)
{
        v2f64 r(a);
        r()[_I] =v;
        return r;
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
        v2f64 t(a);
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
emuvec::v2f64 emuvec::isinf(const v2f64& a)
{
        v2f64 r;
        impl::v_isinf<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::isnan(const v2f64& a)
{
        v2f64 r;
        impl::v_isnan<v2f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::copysign(const v2f64& a, const v2f64& b)
{
        v2f64 r;
        impl::v_copysign<v2f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v2f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::mulsign(const v2f64& x, const v2f64& y)
{
        const v2f64 msk= v_sign_v2f64_msk::dv();
        v2f64 sgn_y = y & msk;
        return x ^ sgn_y;
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

inline
void emuvec::store(v2f64::element_type* p, const v2f64& v)
{
        impl::mem_cpy<sizeof(v2f64::element_type)*v2f64::N>::v(p, v());
}

#endif

