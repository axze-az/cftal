#if !defined (__EMUVEC_V4F64_INL_H__)
#define __EMUVEC_V4F64_INL_H__ 1

#include <algorithm>
// v4f64 implementation
inline
emuvec::v4f64::element_type* emuvec::v4f64::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v4f64::element_type* emuvec::v4f64::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v4f64::element_type* emuvec::v4f64::operator()()
{
        return begin();
}

inline
const emuvec::v4f64::element_type* emuvec::v4f64::operator()() const
{
        return begin();
}

template <template <class _V> class _OP, class _L, class _R>
inline
emuvec::v4f64::v4f64(const expr<_OP<v4f64>, _L, _R>& r)
        : base_type()
{
        element_type* p= begin();
        for (size_t i=0; i<N; ++i)
                p[i] = eval(r, i);
}

template <bool _P0, bool _P1, bool _P2, bool _P3>
emuvec::v4f64 emuvec::select(const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::select_4<v4f64::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a(), b());
        return r;
}

template <int _P0, int _P1, int _P2, int _P3>
emuvec::v4f64 emuvec::permute(const v4f64& a)
{
        v4f64 r;
        impl::perm1_4<v4f64::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a());
        return r;
}

template <int _P0, int _P1, int _P2, int _P3>
emuvec::v4f64 emuvec::permute(const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::perm2_4<v4f64::element_type, _P0, _P1, _P2, _P3>::
		v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v4f64::element_type emuvec::extract(const v4f64& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v4f64 emuvec::insert(const v4f64& a, v4f64::element_type v)
{
        v4f64 r(a);
        r()[_I] =v;
        return r;
}

inline
emuvec::v4f64::v4f64(element_type p00, element_type p01,
		     element_type p02, element_type p03)
        : base_type()
{
        element_type* p= begin();
        p[0] = p00; p[1] = p01;
	p[2] = p02; p[3] = p03;
}

inline
emuvec::v4f64::v4f64(const v2f64& l, const v2f64& h)
	: base_type()
{
	const v2f64::element_type *p01 = l(), *p23 = h();
	element_type* p= begin();
	p[0] = p01[0]; p[1]= p01[1];
	p[2] = p23[0]; p[3]= p23[1];
}

inline
emuvec::v4f64::v4f64(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v4f64::v4f64(v4f64::element_type r, bool broadcast)
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
emuvec::v4f64::v4f64(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v4f64::v4f64(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4f64::v4f64(const mem::aligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4f64::v4f64(const mem::unaligned::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v4f64& emuvec::v4f64::operator=(v4f64::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

inline
emuvec::masked_vec<emuvec::v4f64>
emuvec::v4f64::operator()(const mask<v4f64>& m) 
{
        return masked_vec<v4f64>(*this, m);
}

inline
emuvec::v4f64&
emuvec::operator|= (v4f64& a, const v4f64& b)
{
        impl::v_f_or<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f64::N);
        return a;
}

inline
emuvec::v4f64&
emuvec::operator&= (v4f64& a, const v4f64& b)
{
        impl::v_f_and<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f64::N);
        return a;
}

inline
emuvec::v4f64&
emuvec::operator^= (v4f64& a, const v4f64& b)
{
        impl::v_f_xor<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v4f64::N);
        return a;
}

inline
emuvec::v4f64&
emuvec::operator++(v4f64& a)
{
        impl::v_inc<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, v4f64::N);
        return a;
}

inline
emuvec::v4f64
emuvec::operator++ (v4f64& a, int)
{
        v4f64 t(a);
        impl::v_inc<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, v4f64::N);
        return t;
}

inline
emuvec::v4f64&
emuvec::operator--(v4f64& a)
{
        impl::v_dec<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, v4f64::N);
        return a;
}

inline
emuvec::v4f64
emuvec::operator-- (v4f64& a, int)
{
        v4f64 t(a);
        impl::v_dec<v4f64::element_type> ot;
        impl::v_assign_op(a(), ot, v4f64::N);
        return t;
}

inline
emuvec::v4f64
emuvec::operator-(const v4f64& a)
{
        v4f64 t;
        impl::v_neg<v4f64::element_type> ot;
        impl::v_assign_op(t(), ot, v4f64::N);
        return t;
}

inline
const emuvec::v4f64&
emuvec::operator+(const v4f64& a)
{
        return a;
}

inline
emuvec::v4f64
emuvec::operator~(const v4f64& a)
{
        v4f64 t;
        impl::v_f_not<v4f64::element_type> ot;
        impl::v_assign_op(t(), ot, v4f64::N);
        return t;
}

inline
emuvec::v4f64
emuvec::operator!(const v4f64& a)
{
        v4f64 t;
        impl::v_log_not<v4f64::element_type> ot;
        impl::v_assign_op(t(), ot, v4f64::N);
        return t;
}

inline
emuvec::v4f64 emuvec::operator| (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_f_or<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator|| (const v4f64& a, const v4f64& b)
{
        return a | b;
}

inline
emuvec::v4f64 emuvec::operator& (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_f_and<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator&& (const v4f64& a, const v4f64& b)
{
        return a & b;
}

inline
emuvec::v4f64 emuvec::operator^(const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_f_xor<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator< (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_lt<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator<= (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_le<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator== (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_eq<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator!= (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_ne<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator>= (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_ge<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::operator> (const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_ge<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v2f64 emuvec::low_half(const v4f64& v)
{
	const v4f64::element_type* p=v();
	return v2f64(p[0], p[1]);
}

inline
emuvec::v2f64 emuvec::high_half(const v4f64& v)
{
	const v4f64::element_type* p=v();
	return v2f64(p[2], p[3]);
}

inline
bool emuvec::all_signs(const v4f64& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v4f64::N));
        return sgn == 0x03;
}

inline
bool emuvec::both_signs(const v4f64& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v4f64::N));
        return sgn != 0x03 && sgn != 0;
}


inline
bool emuvec::no_signs(const v4f64& a)
{
        uint32_t sgn(impl::get_signs_32(a(), v4f64::N));
        return sgn == 0;
}

inline
emuvec::v4f64 emuvec::max(const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_max<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::min(const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_min<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::abs(const v4f64& a)
{
        v4f64 r;
        impl::v_abs<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::sqrt(const v4f64& a)
{
        v4f64 r;
        impl::v_sqrt<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::rint(const v4f64& a)
{
        v4f64 r;
        impl::v_rint<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::floor(const v4f64& a)
{
        v4f64 r;
        impl::v_floor<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::ceil(const v4f64& a)
{
        v4f64 r;
        impl::v_ceil<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::trunc(const v4f64& a)
{
        v4f64 r;
        impl::v_trunc<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::isinf(const v4f64& a)
{
        v4f64 r;
        impl::v_isinf<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::isnan(const v4f64& a)
{
        v4f64 r;
        impl::v_isnan<v4f64::element_type> ot;
        impl::v_un_op(r(), ot, a(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::copysign(const v4f64& a, const v4f64& b)
{
        v4f64 r;
        impl::v_copysign<v4f64::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v4f64::N);
        return r;
}

inline
emuvec::v4f64 emuvec::mulsign(const v4f64& x, const v4f64& y)
{
        const v4f64 msk= v_sign_v4f64_msk::dv();
        v4f64 sgn_y = y & msk;
        return x ^ sgn_y;
}

inline
emuvec::v4f64 emuvec::select(const v4f64& msk,
                             const v4f64& on_true,
                             const v4f64& on_false)
{
        v4f64 r;
        impl::select<v4f64::element_type>::v(r(), msk(), on_true(), on_false(),
                                             v4f64::N);
        return r;
}

inline
void emuvec::store(v4f64::element_type* p, const v4f64& v)
{
        impl::mem_cpy<sizeof(v4f64::element_type)*v4f64::N>::v(p, v());
}

#endif

