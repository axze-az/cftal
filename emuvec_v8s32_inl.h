#if !defined (__EMUVEC_V8S32_INL_H__)
#define __EMUVEC_INL_V8S32_H__ 1

#include <algorithm>

// v8s32 implementation
inline
emuvec::v8s32::element_type* emuvec::v8s32::begin()
{
        return reinterpret_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v8s32::element_type* emuvec::v8s32::begin() const
{
        return reinterpret_cast<const element_type*>(base_type::vbegin());
}

inline
emuvec::v8s32::element_type* emuvec::v8s32::operator()()
{
        return begin();
}

inline
const emuvec::v8s32::element_type* emuvec::v8s32::operator()() const
{
        return begin();
}

template <unsigned _P>
emuvec::v8s32&
emuvec::operator<<= (v8s32& a, const const_u32< _P >& b)
{
        const int val = b.val;
        impl::v_sl<v8s32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v8s32::N);
        return a;
}

template <unsigned _P>
emuvec::v8s32&
emuvec::operator>>= (v8s32& a, const const_u32<_P>& b)
{
        const int val = b.val;
        impl::v_sr<v8s32::element_type> ot(val);
        impl::v_assign_op(a(), ot, v8s32::N);
        return a;
}

template <unsigned _P>
emuvec::v8s32
emuvec::operator<<(const v8s32& a, const const_u32< _P >& b)
{
        v8s32 r;
        const int val = b.val;
        impl::v_sl<v8s32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v8s32::N);
        return r;
}

template <unsigned _P>
emuvec::v8s32
emuvec::operator>> (const v8s32& a, const const_u32< _P >& b)
{
        v8s32 r;
        const int val = b.val;
        impl::v_sr<v8s32::element_type> ot(val);
        impl::v_bi_op(r(), a(), ot, v8s32::N);
        return r;
}

template < bool _P0, bool _P1, bool _P2, bool _P3,
           bool _P4, bool _P5, bool _P6, bool _P7 >
emuvec::v8s32 emuvec::select(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::select_8<v8s32::element_type, _P0, _P1, _P2, _P3,
                _P4, _P5, _P6, _P7>::v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3,
           int _P4, int _P5, int _P6, int _P7 >
emuvec::v8s32 emuvec::permute(const v8s32& a)
{
        v8s32 r;
        impl::perm1_8<v8s32::element_type, _P0, _P1, _P2, _P3,
                _P4, _P5, _P6, _P7>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3,
           int _P4, int _P5, int _P6, int _P7 >
emuvec::v8s32 emuvec::permute(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::perm2_8<v8s32::element_type, _P0, _P1, _P2, _P3,
                _P4, _P5, _P6, _P7>::v(r(), a(), b());
        return r;
}

template <unsigned _I>
emuvec::v8s32::element_type emuvec::extract(const v8s32& a)
{
        return a()[_I];
}

template <unsigned _I>
emuvec::v8s32 emuvec::insert(const v8s32& a, v8s32::element_type v)
{
        v8s32 r(a);
        r()[_I] =v;
        return r;
}

// v8s32 implementation
inline
emuvec::v8s32::v8s32(element_type p00, element_type p01,
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
emuvec::v8s32::v8s32(element_type r): base_type()
{
        std::uninitialized_fill_n(begin(), N, r);
}

inline
emuvec::v8s32::v8s32(v8s32::element_type r, bool broadcast)
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
emuvec::v8s32::v8s32(const mem::addr_bcast<element_type>& r)
        : base_type()
{
        std::uninitialized_fill_n(begin(), N, *r());
}

inline
emuvec::v8s32::v8s32(const mem::addr<element_type>& r)
        : base_type()
{
        std::uninitialized_copy_n(r(), N, begin());
}

inline
emuvec::v8s32& emuvec::v8s32::operator=(v8s32::element_type r)
{
        std::fill_n(begin(), N, r);
        return *this;
}

// inline
inline
emuvec::masked_vec<emuvec::v8s32>
emuvec::v8s32::operator()(const mask<v8s32>& m) 
{
        return masked_vec<v8s32>(*this, m);
}


inline
emuvec::v8s32&
emuvec::operator|= (v8s32& a, const v8s32& b)
{
        impl::v_or<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator&= (v8s32& a, const v8s32& b)
{
        impl::v_and<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator^= (v8s32& a, const v8s32& b)
{
        impl::v_xor<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator+= (v8s32& a, const v8s32& b)
{
        impl::v_add<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator-= (v8s32& a, const v8s32& b)
{
        impl::v_sub<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator*= (v8s32& a, const v8s32& b)
{
        impl::v_mul<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator/=(v8s32& a, const v8s32& b)
{
        impl::v_div<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator%=(v8s32& a, const v8s32& b)
{
        impl::v_irem<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, b(), v8s32::N);
        return a;
}

inline
emuvec::v8s32&
emuvec::operator<<= (v8s32& a, uint32_t b)
{
        impl::v_sl<v8s32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8s32::N);
        return a;
}

inline
emuvec::v8s32
emuvec::operator<< (const v8s32& a, uint32_t b)
{
        v8s32 r;
        impl::v_sl<v8s32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8s32::N);
        return r;
}

inline
emuvec::v8s32&
emuvec::operator>>= (v8s32& a, uint32_t b)
{
        impl::v_sr<v8s32::element_type> ot(b);
        impl::v_assign_op(a(), ot, v8s32::N);
        return a;
}

inline
emuvec::v8s32
emuvec::operator>> (const v8s32& a, uint32_t b)
{
        v8s32 r;
        impl::v_sr<v8s32::element_type> ot(b);
        impl::v_bi_op(r(), a(), ot, v8s32::N);
        return r;
}

inline
emuvec::v8s32&
emuvec::operator++(v8s32& a)
{
        impl::v_inc<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, v8s32::N);
        return a;
}

inline
emuvec::v8s32
emuvec::operator++ (v8s32& a, int)
{
        v8s32 t(a);
        impl::v_inc<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, v8s32::N);
        return t;
}

inline
emuvec::v8s32&
emuvec::operator--(v8s32& a)
{
        impl::v_dec<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, v8s32::N);
        return a;
}

inline
emuvec::v8s32
emuvec::operator-- (v8s32& a, int)
{
        v8s32 t(a);
        impl::v_dec<v8s32::element_type> ot;
        impl::v_assign_op(a(), ot, v8s32::N);
        return t;
}

inline
emuvec::v8s32
emuvec::operator-(const v8s32& a)
{
        v8s32 r;
        impl::v_neg<v8s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s32::N);
        return r;
}

inline
const emuvec::v8s32&
emuvec::operator+(const v8s32& a)
{
        return a;
}

inline
emuvec::v8s32
emuvec::operator~(const v8s32& a)
{
        v8s32 r;
        impl::v_not<v8s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s32::N);
        return r;
}

inline
emuvec::v8s32
emuvec::operator!(const v8s32& a)
{
        v8s32 r;
        impl::v_log_not<v8s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator| (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_or<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator|| (const v8s32& a, const v8s32& b)
{
        return a | b;
}

inline
emuvec::v8s32 emuvec::operator& (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_and<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator&& (const v8s32& a, const v8s32& b)
{
        return a & b;
}

inline
emuvec::v8s32 emuvec::operator^(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_xor<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator+ (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_add<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator- (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_sub<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator* (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_mul<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32
emuvec::operator/(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_div<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32
emuvec::operator%(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_irem<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator< (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_lt<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator<= (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_le<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator== (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_eq<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator!= (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_ne<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator>= (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_ge<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::operator> (const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_gt<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::max(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_max<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::min(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_min<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::abs(const v8s32& a)
{
        v8s32 r;
        impl::v_abs<v8s32::element_type> ot;
        impl::v_un_op(r(), ot, a(), v8s32::N);
        return r;
}

inline
emuvec::v8s32 emuvec::mul_hi(const v8s32& a, const v8s32& b)
{
        v8s32 r;
        impl::v_mulhi<v8s32::element_type> ot;
        impl::v_bi_op(r(), a(), ot, b(), v8s32::N);
        return r;
}

inline
bool emuvec::no_signs(const v8s32& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v8s32::N));
        return sgns == 0;
}

inline
bool emuvec::all_signs(const v8s32& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v8s32::N));
        return sgns == 0xFF;

}

inline
bool emuvec::both_signs(const v8s32& a)
{
        uint32_t sgns(impl::get_signs_32(a(), v8s32::N));
        return sgns != 0xFF && sgns != 0;
}

inline
emuvec::v8s32 emuvec::select(const v8s32& msk,
                             const v8s32& on_true,
                             const v8s32& on_false)
{
        v8s32 r;
        impl::select<v8s32::element_type>::v(r(),
                                             msk(), on_true(), on_false(),
                                             v8s32::N);
        return r;
}

// store.
inline
void emuvec::store(v8s32::element_type* p, const v8s32& v)
{
        impl::mem_cpy<sizeof(v8s32::element_type)*v8s32::N>::v(p, v());
}

#endif

