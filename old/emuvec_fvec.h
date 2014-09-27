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
        v4f32 atan2(arg<v4f32>::type x, arg<v4f32>::type y);

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
        v2f64 atan2(arg<v2f64>::type x, arg<v2f64>::type y);
        
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


        class v4f64 : public impl::vec_base<double,4>::type {
        public:
                enum { N = 4 };
                typedef double element_type;
                typedef typename impl::vec_base<double, 4>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v4f64() = default;
                v4f64(element_type r);
                v4f64(element_type r, bool broadcast);
                v4f64(element_type p00, element_type p01,
		      element_type p02=0.0, element_type p03=0.0);
		v4f64(const v2f64& l, const v2f64& h);
                v4f64(const v4f64& r) = default;
                v4f64(v4f64&& r) = default;
                // assignment from expr<op<v4f64>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v4f64(const expr<_OP<v4f64>, _L, _R>& r);
                v4f64& operator=(element_type r);
                v4f64& operator=(const v4f64& r) = default;
                v4f64& operator=(v4f64&& r) = default;
                v4f64(const mem::addr_bcast<element_type>& r);
                v4f64(const mem::addr<element_type>& r);
                v4f64(const mem::aligned::addr<element_type>& r);
                v4f64(const mem::unaligned::addr<element_type>& r);
                masked_vec<v4f64> operator()(const mask<v4f64>& m);
        private:
                element_type* begin();
                const element_type* begin() const;
        };

        template <>
        struct expr_traits<v4f64> {
                typedef const v4f64& type;
        };
        
        inline
        const v4f64::element_type& eval(const v4f64& v, size_t i) {
                return v()[i];
        }

        DEFINE_EMUVEC_FP_OPERATORS(v4f64);

        v4f64& operator|= (v4f64& a, const v4f64& b);
        v4f64& operator&= (v4f64& a, const v4f64& b);
        v4f64& operator^= (v4f64& a, const v4f64& b);

        v4f64 operator++ (v4f64& a, int);
        v4f64& operator++(v4f64& a);
        v4f64 operator-- (v4f64& a, int);
        v4f64& operator--(v4f64& a);

        v4f64 operator-(const v4f64& a);
        const v4f64& operator+(const v4f64& a);
        v4f64 operator~(const v4f64& a);
        v4f64 operator!(const v4f64& a);

        v4f64 operator| (const v4f64& a, const v4f64& b);
        v4f64 operator|| (const v4f64& a, const v4f64& b);
        v4f64 operator& (const v4f64& a, const v4f64& b);
        v4f64 operator&& (const v4f64& a, const v4f64& b);
        v4f64 operator^(const v4f64& a, const v4f64& b);

        v4f64 operator< (const v4f64& a, const v4f64& b);
        v4f64 operator<= (const v4f64& a, const v4f64& b);
        v4f64 operator== (const v4f64& a, const v4f64& b);
        v4f64 operator!= (const v4f64& a, const v4f64& b);
        v4f64 operator>= (const v4f64& a, const v4f64& b);
        v4f64 operator> (const v4f64& a, const v4f64& b);

        v2f64 low_half(const v4f64& v);
        v2f64 high_half(const v4f64& v);

        // checks the signs
        bool all_signs(const v4f64& a);
        // checks the signs
        bool both_signs(const v4f64& a);
        // checks the signs
        bool no_signs(const v4f64& a);

        v4f64 max(const v4f64& a, const v4f64& b);
        v4f64 min(const v4f64& a, const v4f64& b);
        v4f64 abs(const v4f64& a);
        v4f64 fabs(const v4f64& a);
        v4f64 sqrt(const v4f64& a);
        v4f64 cbrt(arg<v4f64>::type a);

        v4f64 rint(const v4f64& a);
        v4f64 floor(const v4f64& a);
        v4f64 ceil(const v4f64& a);
        v4f64 trunc(const v4f64& a);

        v4f64 copysign(const v4f64& x, const v4f64& y);
        v4f64 mulsign(const v4f64& x, const v4f64& y);
        v4f64 isinf(const v4f64& x);
        v4f64 isnan(const v4f64& x);
        v4f64 isfinite(const v4f64& x);

        v4f64 frexp(arg<v4f64>::type x, v4s32* e);
        // v4f64 pow2i(arg<v4s32>::type e);
        v4f64 ldexp(arg<v4f64>::type d, arg<v4s32>::type e);
        v4s32 ilogbp1(arg<v4f64>::type v);
        v4s32 ilogb(arg<v4f64>::type v);
        v4f64 atan2(arg<v4f64>::type y, arg<v4f64>::type x);
        v4f64 asin(arg<v4f64>::type d);
        v4f64 acos(arg<v4f64>::type d);

        v4f64 atan(arg<v4f64>::type d);

        v4f64 exp(arg<v4f64>::type d);
        v4f64 expm1(arg<v4f64>::type d);
        v4f64 log(arg<v4f64>::type d);
        v4f64 pow(arg<v4f64>::type b, arg<v4f64>::type e);
        void sincos(arg<v4f64>::type d, v4f64* psin, v4f64* pcos);
        v4f64 sin(arg<v4f64>::type d);
        v4f64 cos(arg<v4f64>::type d);
        v4f64 tan(arg<v4f64>::type d);
        v4f64 cot(arg<v4f64>::type d);
        v4f64 atan2(arg<v4f64>::type x, arg<v4f64>::type y);
        
        void native_sincos(arg<v4f64>::type d, v4f64* psin, v4f64* pcos);
        v4f64 native_exp(arg<v4f64>::type d);
        v4f64 native_log(arg<v4f64>::type d);
        v4f64 native_sin(arg<v4f64>::type d);
        v4f64 native_cos(arg<v4f64>::type d);
        v4f64 native_tan(arg<v4f64>::type d);
        v4f64 native_cot(arg<v4f64>::type d);
        v4f64 cosh(arg<v4f64>::type d);
        v4f64 sinh(arg<v4f64>::type d);

        v4f64 pow(arg<v4f64>::type x, arg<v4f64>::type y);

        template <bool _P0, bool _P1, bool _P2, bool _P3>
        v4f64 select(const v4f64& a, const v4f64& b);
        v4f64 select(const v4f64& msk, const v4f64& on_true,
                     const v4f64& on_false);

        template <int _P0, int _P1, int _P2, int _P3>
        v4f64 permute(const v4f64& a);
        template <int _P0, int _P1, int _P2, int _P3>
        v4f64 permute(const v4f64& a, const v4f64& b);

        template <unsigned _I>
        v4f64 insert(const v4f64& a, typename v4f64::element_type v);
        template <unsigned _I>
        typename v4f64::element_type extract(const v4f64& a);

        void store(v4f64::element_type* p, const v4f64& r);

        class v8f32 : public impl::vec_base<float,4>::type {
        public:
                enum { N = 8 };
                typedef float element_type;
                typedef typename impl::vec_base<float,4>::type
                base_type;
                element_type* operator()();
                const element_type* operator()() const;
                v8f32() = default;
                v8f32(element_type r);
                v8f32(element_type r, bool broadcast);
                v8f32(element_type p00, element_type p01,
                      element_type p02, element_type p03,
		      element_type p04, element_type p05,
                      element_type p06, element_type p07);
                v8f32(const v8f32& r) = default;
                v8f32(v8f32&& r) = default;
                // assignment from expr<op<v8f32>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v8f32(const expr<_OP<v8f32>, _L, _R>& r);
                v8f32& operator=(element_type r);
                v8f32& operator=(const v8f32& r) = default;
                v8f32& operator=(v8f32&& r) = default;
                v8f32(const mem::addr_bcast<element_type>& r);
                v8f32(const mem::addr<element_type>& r);
                v8f32(const mem::aligned::addr<element_type>& r);
                v8f32(const mem::unaligned::addr<element_type>& r);
                masked_vec<v8f32> operator()(const mask<v8f32>& m);
        private:
		element_type* begin();
                const element_type* begin() const;
        };

        template <>
        struct expr_traits<v8f32> {
                typedef const v8f32& type;
        };
        
        inline
        const v8f32::element_type& eval(const v8f32& v, size_t i) {
                return v()[i];
        }

        DEFINE_EMUVEC_FP_OPERATORS(v8f32);

        v8f32& operator|= (v8f32& a, const v8f32& b);
        v8f32& operator&= (v8f32& a, const v8f32& b);
        v8f32& operator^= (v8f32& a, const v8f32& b);
        v8f32& operator+= (v8f32& a, const v8f32& b);
        v8f32& operator-= (v8f32& a, const v8f32& b);
        v8f32& operator*= (v8f32& a, const v8f32& b);
        v8f32& operator/= (v8f32& a, const v8f32& b);

        v8f32 operator++ (v8f32& a, int);
        v8f32& operator++(v8f32& a);
        v8f32 operator-- (v8f32& a, int);
        v8f32& operator--(v8f32& a);

        v8f32 operator-(const v8f32& a);
        const v8f32& operator+(const v8f32& a);
        v8f32 operator~(const v8f32& a);
        v8f32 operator!(const v8f32& a);

        v8f32 operator| (const v8f32& a, const v8f32& b);
        v8f32 operator|| (const v8f32& a, const v8f32& b);
        v8f32 operator& (const v8f32& a, const v8f32& b);
        v8f32 operator&& (const v8f32& a, const v8f32& b);
        v8f32 operator^(const v8f32& a, const v8f32& b);

        v8f32 operator< (const v8f32& a, const v8f32& b);
        v8f32 operator<= (const v8f32& a, const v8f32& b);
        v8f32 operator== (const v8f32& a, const v8f32& b);
        v8f32 operator!= (const v8f32& a, const v8f32& b);
        v8f32 operator>= (const v8f32& a, const v8f32& b);
        v8f32 operator> (const v8f32& a, const v8f32& b);

        // checks the signs
        bool all_signs(const v8f32& a);
        // checks the signs
        bool both_signs(const v8f32& a);
        // checks the signs
        bool no_signs(const v8f32& a);
        // read a mask of all signs
        unsigned read_signs(const v8f32& a);

        v8f32 max(const v8f32& a, const v8f32& b);
        v8f32 min(const v8f32& a, const v8f32& b);
        v8f32 abs(const v8f32& a);
        v8f32 fabs(const v8f32& a);
        v8f32 sqrt(const v8f32& a);
        v8f32 cbrt(arg<v8f32>::type a);
        
        v8f32 rcp(const v8f32& a);
        v8f32 native_rcp(const v8f32& a);
        v8f32 rsqrt(const v8f32& a);
        v8f32 native_rsqrt(const v8f32& a);

        v8f32 rint(const v8f32& a);
        v8f32 floor(const v8f32& a);
        v8f32 ceil(const v8f32& a);
        v8f32 trunc(const v8f32& a);
        // returns (~a) & (b)
        v8f32 andnot(const v8f32& a, const v8f32& b);
        v8f32 copysign(const v8f32& x, const v8f32& y);
        v8f32 mulsign(const v8f32& x, const v8f32& y);
        v8f32 isinf(const v8f32& x);
        v8f32 isnan(const v8f32& x);
        v8f32 isfinite(const v8f32& x);

        // v8f32 pow2if(arg<v4s32>::type e);
        v8f32 ldexp(arg<v8f32>::type d, arg<v8s32>::type e);
        v8f32 frexp(arg<v8f32>::type d, v8s32* e);
        v8s32 ilogbp1(arg<v8f32>::type v);
        v8s32 ilogb(arg<v8f32>::type v);

        v8f32 exp(arg<v8f32>::type d);
        v8f32 expm1(arg<v8f32>::type d);
        v8f32 cosh(arg<v8f32>::type d);
        v8f32 sinh(arg<v8f32>::type d);
        v8f32 log(arg<v8f32>::type d);
        v8f32 pow(arg<v8f32>::type b, arg<v8f32>::type e);

        void sincos(arg<v8f32>::type d, v8f32* psin, v8f32* pcos);
        v8f32 sin(arg<v8f32>::type d);
        v8f32 cos(arg<v8f32>::type d);
        v8f32 tan(arg<v8f32>::type d);
        v8f32 cot(arg<v8f32>::type d);
        v8f32 atan2(arg<v8f32>::type x, arg<v8f32>::type y);

        void native_sincos(arg<v8f32>::type d, 
                           v8f32* psin, v8f32* pcos);
        v8f32 native_sin(arg<v8f32>::type d);
        v8f32 native_cos(arg<v8f32>::type d);
        v8f32 native_tan(arg<v8f32>::type d);
        v8f32 native_cot(arg<v8f32>::type d);

        v8f32 native_exp(arg<v8f32>::type d);
        v8f32 native_log(arg<v8f32>::type d);

        template <bool _P0, bool _P1, bool _P2, bool _P3,
		  bool _P4, bool _P5, bool _P6, bool _P7>
        v8f32 select(const v8f32& a, const v8f32& b);
        v8f32 select(const v8f32& msk, const v8f32& on_true,
                     const v8f32& on_false);

        template <int _P0, int _P1, int _P2, int _P3,
		  int _P4, int _P5, int _P6, int _P7>
        v8f32 permute(const v8f32& a);
        template <int _P0, int _P1, int _P2, int _P3,
		  int _P4, int _P5, int _P6, int _P7>
        v8f32 permute(const v8f32& a, const v8f32& b);

        template <unsigned _I>
        v8f32 insert(const v8f32& a, typename v8f32::element_type v);
        template <unsigned _I>
        typename v8f32::element_type extract(const v8f32& a);

        void store(v8f32::element_type* p, const v8f32& r);

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
        typedef const_v4u32<0x00000000,0x7ff00000,
			    0x00000000,0x7ff00000> v_exp_v2f64_msk;
        typedef const_v4u32<0x80000000, 0x80000000,
                            0x80000000, 0x80000000> v_sign_v4f32_msk;

        // static constants consisting of 8 uint32_t
        template <uint32_t _P0, uint32_t _P1,
                  uint32_t _P2, uint32_t _P3,
		  uint32_t _P4, uint32_t _P5,
                  uint32_t _P6, uint32_t _P7>
        class const_v8u32 {
                union  alignas(32) u_t {
                        const uint32_t _u32[8];
                        const double _f64[4];
                        const float _f32[8];
                };
                static const u_t _msk;
                static const v8f32 _f32;
                static const v4f64 _f64;
        public:
                // static constexpr __m128i iv();
                static const v8f32& fv();
                static const v4f64& dv();
        };

        typedef const_v8u32<0x00000000, 0x80000000,
                            0x00000000, 0x80000000,
			    0x00000000, 0x80000000,
                            0x00000000, 0x80000000> v_sign_v4f64_msk;
        typedef const_v8u32<0x80000000, 0x80000000,
                            0x80000000, 0x80000000,
			    0x80000000, 0x80000000,
                            0x80000000, 0x80000000> v_sign_v8f32_msk;
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


template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3,
	  uint32_t _P4, uint32_t _P5,
	  uint32_t _P6, uint32_t _P7>
const typename emuvec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::u_t
emuvec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::_msk={{
                _P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7
        }
};


template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3,
	 uint32_t _P4, uint32_t _P5,
	 uint32_t _P6, uint32_t _P7>
const emuvec::v8f32
emuvec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::
_f32(_msk._f32[0],
     _msk._f32[1],
     _msk._f32[2],
     _msk._f32[3],
     _msk._f32[4],
     _msk._f32[5],
     _msk._f32[6],
     _msk._f32[7]);


template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3,
	 uint32_t _P4, uint32_t _P5,
	 uint32_t _P6, uint32_t _P7>
const emuvec::v4f64
emuvec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::
_f64(_msk._f64[0],
     _msk._f64[1],
     _msk._f64[2],
     _msk._f64[3]);


template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3,
	 uint32_t _P4, uint32_t _P5,
	 uint32_t _P6, uint32_t _P7>
inline
const emuvec::v8f32&
emuvec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::fv()
{
        return _f32;
}


template<uint32_t _P0, uint32_t _P1,
         uint32_t _P2, uint32_t _P3,
	 uint32_t _P4, uint32_t _P5,
	 uint32_t _P6, uint32_t _P7>
inline
const emuvec::v4f64&
emuvec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::dv()
{
        return _f64;
}



// Local variables:
// mode: c++
// end:
#endif
