#if !defined (__EMUVEC_FVEC_H__)
#define __EMUVEC_FVEC_H__ 1

#include <cftal/config.h>
#include <cftal/mem_load.h>
#include <cftal/emuvec_impl.h>
#include <cftal/emuvec_impl_ops.h>
#include <cftal/emuvec_expr.h>
#include <cftal/emuvec_mask.h>
#include <algorithm>
#include <functional>

namespace emuvec {

        class v4f32 : public impl::vec_base<float,4>::type {
        public:
                enum { N = 4 };
                typedef float element_type;
                typedef typename impl::vec_base<float,4>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v4f32() = default;
                v4f32(element_type r);
                v4f32(element_type r, bool broadcast);
                v4f32(element_type p00, element_type p01,
                      element_type p02, element_type p03);
                v4f32(const v4f32& r) = default;
                v4f32(v4f32&& r) = default;
                // assignment from expr<op<v4f32>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v4f32(const expr<_OP<v4f32>, _L, _R>& r);
                v4f32& operator=(element_type r);
                v4f32& operator=(const v4f32& r) = default;
                v4f32& operator=(v4f32&& r) = default;
                v4f32(const mem::addr_bcast<element_type>& r);
                v4f32(const mem::addr<element_type>& r);
                v4f32(const mem::aligned::addr<element_type>& r);
                v4f32(const mem::unaligned::addr<element_type>& r);
                masked_vec<v4f32> operator()(const mask<v4f32>& m);
        private:
                element_type* begin();
                const element_type* begin() const;
        };

        template <>
        struct expr_traits<v4f32> {
                typedef const v4f32& type;
        };
        
        inline
        const v4f32::element_type& eval(const v4f32& v, size_t i) {
                return v()[i];
        }

        DEFINE_EMUVEC_FP_OPERATORS(v4f32);

        v4f32& operator|= (v4f32& a, const v4f32& b);
        v4f32& operator&= (v4f32& a, const v4f32& b);
        v4f32& operator^= (v4f32& a, const v4f32& b);
        v4f32& operator+= (v4f32& a, const v4f32& b);
        v4f32& operator-= (v4f32& a, const v4f32& b);
        v4f32& operator*= (v4f32& a, const v4f32& b);
        v4f32& operator/= (v4f32& a, const v4f32& b);

        v4f32 operator++ (v4f32& a, int);
        v4f32& operator++(v4f32& a);
        v4f32 operator-- (v4f32& a, int);
        v4f32& operator--(v4f32& a);

        v4f32 operator-(const v4f32& a);
        const v4f32& operator+(const v4f32& a);
        v4f32 operator~(const v4f32& a);
        v4f32 operator!(const v4f32& a);

        v4f32 operator| (const v4f32& a, const v4f32& b);
        v4f32 operator|| (const v4f32& a, const v4f32& b);
        v4f32 operator& (const v4f32& a, const v4f32& b);
        v4f32 operator&& (const v4f32& a, const v4f32& b);
        v4f32 operator^(const v4f32& a, const v4f32& b);

        v4f32 operator< (const v4f32& a, const v4f32& b);
        v4f32 operator<= (const v4f32& a, const v4f32& b);
        v4f32 operator== (const v4f32& a, const v4f32& b);
        v4f32 operator!= (const v4f32& a, const v4f32& b);
        v4f32 operator>= (const v4f32& a, const v4f32& b);
        v4f32 operator> (const v4f32& a, const v4f32& b);

        // checks the signs
        bool all_signs(const v4f32& a);
        // checks the signs
        bool both_signs(const v4f32& a);
        // checks the signs
        bool no_signs(const v4f32& a);
        // read a mask of all signs
        unsigned read_signs(const v4f32& a);

        v4f32 max(const v4f32& a, const v4f32& b);
        v4f32 min(const v4f32& a, const v4f32& b);
        v4f32 abs(const v4f32& a);
        v4f32 fabs(const v4f32& a);
        v4f32 sqrt(const v4f32& a);
        v4f32 cbrt(arg<v4f32>::type a);
        
        v4f32 rcp(const v4f32& a);
        v4f32 native_rcp(const v4f32& a);
        v4f32 rsqrt(const v4f32& a);
        v4f32 native_rsqrt(const v4f32& a);

        v4f32 rint(const v4f32& a);
        v4f32 floor(const v4f32& a);
        v4f32 ceil(const v4f32& a);
        v4f32 trunc(const v4f32& a);
        // returns (~a) & (b)
        v4f32 andnot(const v4f32& a, const v4f32& b);
        v4f32 copysign(const v4f32& x, const v4f32& y);
        v4f32 mulsign(const v4f32& x, const v4f32& y);
        v4f32 isinf(const v4f32& x);
        v4f32 isnan(const v4f32& x);
        v4f32 isfinite(const v4f32& x);

        v4f32 pow2if(arg<v4s32>::type e);
        v4f32 ldexp(arg<v4f32>::type d, arg<v4s32>::type e);
        v4f32 frexp(arg<v4f32>::type d, v4s32* e);
        v4s32 ilogbp1(arg<v4f32>::type v);
        v4s32 ilogb(arg<v4f32>::type v);

        v4f32 exp(arg<v4f32>::type d);
        v4f32 expm1(arg<v4f32>::type d);
        v4f32 cosh(arg<v4f32>::type d);
        v4f32 sinh(arg<v4f32>::type d);
        v4f32 log(arg<v4f32>::type d);
        v4f32 pow(arg<v4f32>::type b, arg<v4f32>::type e);

        void sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
        v4f32 sin(arg<v4f32>::type d);
        v4f32 cos(arg<v4f32>::type d);
        v4f32 tan(arg<v4f32>::type d);
        v4f32 cot(arg<v4f32>::type d);

        void native_sincos(arg<v4f32>::type d, 
                           v4f32* psin, v4f32* pcos);
        v4f32 native_sin(arg<v4f32>::type d);
        v4f32 native_cos(arg<v4f32>::type d);
        v4f32 native_tan(arg<v4f32>::type d);
        v4f32 native_cot(arg<v4f32>::type d);

        v4f32 native_exp(arg<v4f32>::type d);
        v4f32 native_log(arg<v4f32>::type d);

        template <bool _P0, bool _P1, bool _P2, bool _P3>
        v4f32 select(const v4f32& a, const v4f32& b);
        v4f32 select(const v4f32& msk, const v4f32& on_true,
                     const v4f32& on_false);

        template <int _P0, int _P1, int _P2, int _P3 >
        v4f32 permute(const v4f32& a);
        template <int _P0, int _P1, int _P2, int _P3 >
        v4f32 permute(const v4f32& a, const v4f32& b);

        template <unsigned _I>
        v4f32 insert(const v4f32& a, typename v4f32::element_type v);
        template <unsigned _I>
        typename v4f32::element_type extract(const v4f32& a);

        void store(v4f32::element_type* p, const v4f32& r);

        class v2f64 : public impl::vec_base<double,2>::type {
        public:
                enum { N = 2 };
                typedef double element_type;
                typedef typename impl::vec_base<double, 2>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v2f64() = default;
                v2f64(element_type r);
                v2f64(element_type r, bool broadcast);
                v2f64(element_type p00, element_type p01);
                v2f64(const v2f64& r) = default;
                v2f64(v2f64&& r) = default;
                // assignment from expr<op<v2f64>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v2f64(const expr<_OP<v2f64>, _L, _R>& r);
                v2f64& operator=(element_type r);
                v2f64& operator=(const v2f64& r) = default;
                v2f64& operator=(v2f64&& r) = default;
                v2f64(const mem::addr_bcast<element_type>& r);
                v2f64(const mem::addr<element_type>& r);
                v2f64(const mem::aligned::addr<element_type>& r);
                v2f64(const mem::unaligned::addr<element_type>& r);
                masked_vec<v2f64> operator()(const mask<v2f64>& m);
        private:
                element_type* begin();
                const element_type* begin() const;
        };

        template <>
        struct expr_traits<v2f64> {
                typedef const v2f64& type;
        };
        
        inline
        const v2f64::element_type& eval(const v2f64& v, size_t i) {
                return v()[i];
        }

        DEFINE_EMUVEC_FP_OPERATORS(v2f64);

        v2f64& operator|= (v2f64& a, const v2f64& b);
        v2f64& operator&= (v2f64& a, const v2f64& b);
        v2f64& operator^= (v2f64& a, const v2f64& b);

        v2f64 operator++ (v2f64& a, int);
        v2f64& operator++(v2f64& a);
        v2f64 operator-- (v2f64& a, int);
        v2f64& operator--(v2f64& a);

        v2f64 operator-(const v2f64& a);
        const v2f64& operator+(const v2f64& a);
        v2f64 operator~(const v2f64& a);
        v2f64 operator!(const v2f64& a);

        v2f64 operator| (const v2f64& a, const v2f64& b);
        v2f64 operator|| (const v2f64& a, const v2f64& b);
        v2f64 operator& (const v2f64& a, const v2f64& b);
        v2f64 operator&& (const v2f64& a, const v2f64& b);
        v2f64 operator^(const v2f64& a, const v2f64& b);

        v2f64 operator< (const v2f64& a, const v2f64& b);
        v2f64 operator<= (const v2f64& a, const v2f64& b);
        v2f64 operator== (const v2f64& a, const v2f64& b);
        v2f64 operator!= (const v2f64& a, const v2f64& b);
        v2f64 operator>= (const v2f64& a, const v2f64& b);
        v2f64 operator> (const v2f64& a, const v2f64& b);

        // checks the signs
        bool all_signs(const v2f64& a);
        // checks the signs
        bool both_signs(const v2f64& a);
        // checks the signs
        bool no_signs(const v2f64& a);

        v2f64 max(const v2f64& a, const v2f64& b);
        v2f64 min(const v2f64& a, const v2f64& b);
        v2f64 abs(const v2f64& a);
        v2f64 fabs(const v2f64& a);
        v2f64 sqrt(const v2f64& a);
        v2f64 cbrt(arg<v2f64>::type a);

        v2f64 rint(const v2f64& a);
        v2f64 floor(const v2f64& a);
        v2f64 ceil(const v2f64& a);
        v2f64 trunc(const v2f64& a);

        v2f64 copysign(const v2f64& x, const v2f64& y);
        v2f64 mulsign(const v2f64& x, const v2f64& y);
        v2f64 isinf(const v2f64& x);
        v2f64 isnan(const v2f64& x);
        v2f64 isfinite(const v2f64& x);

        v2f64 frexp(arg<v2f64>::type x, v4s32* e);
        // v2f64 pow2i(arg<v4s32>::type e);
        v2f64 ldexp(arg<v2f64>::type d, arg<v4s32>::type e);
        v4s32 ilogbp1(arg<v2f64>::type v);
        v4s32 ilogb(arg<v2f64>::type v);
        v2f64 atan2(arg<v2f64>::type y, arg<v2f64>::type x);
        v2f64 asin(arg<v2f64>::type d);
        v2f64 acos(arg<v2f64>::type d);

        v2f64 atan(arg<v2f64>::type d);

        v2f64 exp(arg<v2f64>::type d);
        v2f64 expm1(arg<v2f64>::type d);
        v2f64 log(arg<v2f64>::type d);
        v2f64 pow(arg<v2f64>::type b, arg<v2f64>::type e);
        void sincos(arg<v2f64>::type d, v2f64* psin, v2f64* pcos);
        v2f64 sin(arg<v2f64>::type d);
        v2f64 cos(arg<v2f64>::type d);
        v2f64 tan(arg<v2f64>::type d);
        v2f64 cot(arg<v2f64>::type d);
        
        void native_sincos(arg<v2f64>::type d, v2f64* psin, v2f64* pcos);
        v2f64 native_exp(arg<v2f64>::type d);
        v2f64 native_log(arg<v2f64>::type d);
        v2f64 native_sin(arg<v2f64>::type d);
        v2f64 native_cos(arg<v2f64>::type d);
        v2f64 native_tan(arg<v2f64>::type d);
        v2f64 native_cot(arg<v2f64>::type d);
        v2f64 cosh(arg<v2f64>::type d);
        v2f64 sinh(arg<v2f64>::type d);

        v2f64 pow(arg<v2f64>::type x, arg<v2f64>::type y);

        template <bool _P0, bool _P1>
        v2f64 select(const v2f64& a, const v2f64& b);
        v2f64 select(const v2f64& msk, const v2f64& on_true,
                     const v2f64& on_false);

        template <int _P0, int _P1 >
        v2f64 permute(const v2f64& a);
        template <int _P0, int _P1 >
        v2f64 permute(const v2f64& a, const v2f64& b);

        template <unsigned _I>
        v2f64 insert(const v2f64& a, typename v2f64::element_type v);
        template <unsigned _I>
        typename v2f64::element_type extract(const v2f64& a);

        void store(v2f64::element_type* p, const v2f64& r);


        // static constants consisting of 4 uint32_t
        template <uint32_t _P0, uint32_t _P1,
                  uint32_t _P2, uint32_t _P3>
        class const_v4u32 {
                union  alignas(16) u_t {
                        const uint32_t _u32[4];
                        const double _f64[2];
                        const float _f32[4];
                };
                static const u_t _msk;
                static const v4f32 _f32;
                static const v2f64 _f64;
        public:
                // static constexpr __m128i iv();
                static const v4f32& fv();
                static const v2f64& dv();
        };

        typedef const_v4u32<0x00000000, 0x80000000,
                            0x00000000, 0x80000000> v_sign_v2f64_msk;
        typedef const_v4u32<0x80000000, 0x80000000,
                            0x80000000, 0x80000000> v_sign_v4f32_msk;
}

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3>
const typename emuvec::const_v4u32<_P0, _P1, _P2, _P3>::u_t 
emuvec::const_v4u32<_P0, _P1, _P2, _P3>::_msk={{
                _P0, _P1, _P2, _P3
        }
};

template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3>
const emuvec::v4f32
emuvec::const_v4u32<_P0, _P1, _P2, _P3>::_f32(_msk._f32[0],
                                              _msk._f32[1],
                                              _msk._f32[2],
                                              _msk._f32[3]);

template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3>
const emuvec::v2f64
emuvec::const_v4u32<_P0, _P1, _P2, _P3>::_f64(_msk._f64[0],
                                              _msk._f64[1]);

template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3>
inline
const emuvec::v4f32&
emuvec::const_v4u32<_P0, _P1, _P2, _P3>::fv()
{
        return _f32;
}

template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3>
inline
const emuvec::v2f64&
emuvec::const_v4u32<_P0, _P1, _P2, _P3>::dv()
{
        return _f64;
}

inline
emuvec::v4f32::element_type* emuvec::v4f32::begin()
{
        void* pp=__builtin_assume_aligned(base_type::vbegin(),16);
        element_type* p= static_cast<element_type*>(pp);
        return p;
}

inline
const emuvec::v4f32::element_type* emuvec::v4f32::begin() const
{
        const void* pp=__builtin_assume_aligned(base_type::vbegin(),16);
        const element_type* p= static_cast<const element_type*>(pp);
        return p;
}

inline
emuvec::v4f32::element_type* emuvec::v4f32::operator()()
{
        return begin();
}

inline
const emuvec::v4f32::element_type* emuvec::v4f32::operator()() const
{
        return begin();
}

template <template <class _V> class _OP, class _L, class _R>
inline
emuvec::v4f32::v4f32(const expr<_OP<v4f32>, _L, _R>& r)
        : base_type()
{
        element_type* p= begin();
        for (size_t i=0; i<N; ++i)
                p[i] = eval(r, i);
}


template < bool _P0, bool _P1, bool _P2, bool _P3 >
inline
emuvec::v4f32 emuvec::select(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::select_4<v4f32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
emuvec::v4f32 emuvec::permute(const v4f32& a)
{
        v4f32 r;
        impl::perm1_4<v4f32::element_type, _P0, _P1, _P2, _P3>::v(r(), a());
        return r;
}

template < int _P0, int _P1, int _P2, int _P3 >
inline
emuvec::v4f32 emuvec::permute(const v4f32& a, const v4f32& b)
{
        v4f32 r;
        impl::perm2_4<v4f32::element_type, _P0, _P1, _P2, _P3>::
                v(r(), a(), b());
        return r;
}

template <unsigned _I>
inline
emuvec::v4f32::element_type emuvec::extract(const v4f32& a)
{
        return a()[_I];
}

template <unsigned _I>
inline
emuvec::v4f32 emuvec::insert(const v4f32& a, v4f32::element_type v)
{
        v4f32 r(a);
        r()[_I] =v;
        return r;
}

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

// Local variables:
// mode: c++
// end:
#endif
