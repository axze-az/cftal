#if !defined (__X86VEC_FVEC_H__)
#define __X86VEC_FVEC_H__ 1

#include <cftal/x86vec_const.h>
#include <cftal/x86vec_vreg.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_ops_1.h>
#include <cftal/x86vec_ivec.h>
#include <cftal/mem_load.h>
#include <cftal/divisor.h>
#include <cftal/d_real.h>
#include <cfenv>

namespace x86vec {

        namespace impl {

                struct rounding_mode {
                        enum type {
                                nearest = 0x0,
                                downward = 0x1,
                                upward = 0x2,
                                towardzero = 0x3,
                                current = 0x4
                        };
                };

                /* int N;
                 * double x, y, coef[N+1], polevl[];
                 *
                 * y = polevl( x, coef, N );
                 *
                 *
                 *
                 * DESCRIPTION:
                 *
                 * Evaluates polynomial of degree N:
                 *
                 *                     2          N
                 * y  =  C  + C x + C x  +...+ C x
                 *        0    1     2          N
                 *
                 * Coefficients are stored in reverse order:
                 *
                 * coef[0] = C  , ..., coef[N] = C  .
                 *            N                   0
                 */
                template <unsigned _N, typename _T>
                _T polevl(_T x, const _T* coef);

                // same as above with C_N == 1.0
                template <unsigned _N, typename _T>
                _T p1evl(_T x, const _T* coef);

        }

	template <class _T>
	_T gather(const double* base, const v4s32& idx, int scale=1);
	template <class _T, class _IDX>
	_T gather(const float* base, const _IDX& idx, int scale=1);

        class v4f32 : public vreg<__m128> {
        public:
                typedef float element_type;
                typedef vreg<__m128> base_type;
                v4f32() = default;
                v4f32(vector_type r);
                v4f32(const base_type& r);
                v4f32(element_type p00, element_type p01,
                      element_type p02=0.0f, element_type p03=0.0f);
                // broadcast to all positions
                v4f32(element_type r);
                v4f32(element_type r, bool broadcast);
                // construction from expr<op<v4f32>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v4f32(const expr<_OP<v4f32>, _L, _R>& r);
                v4f32(const mem::addr_bcast<element_type>& r);
                v4f32(const mem::addr<element_type>& r);
                v4f32(const mem::aligned::addr<element_type>& r);
                v4f32(const mem::unaligned::addr<element_type>& r);
                using base_type::operator();
                masked_vec<v4f32> operator()(const mask<v4f32>& m);
        };

        inline
        const v4f32& eval(const v4f32& v) {
                return v;
        }

        namespace ops {

                template <>
                struct add<v4f32> : public def_vector_type<v4f32> {
                        static v4f32 v(const v4f32& a, const v4f32& b);
                };

                template <>
                struct sub<v4f32> : public def_vector_type<v4f32>{
                        static v4f32 v(const v4f32& a, const v4f32& b);
                };

                template <>
                struct mul<v4f32> : public def_vector_type<v4f32>{
                        static v4f32 v(const v4f32& a, const v4f32& b);
                };

                template <>
                struct div<v4f32> : public def_vector_type<v4f32>{
                        static v4f32 v(const v4f32& a, const v4f32& b);
                };

                // a * b + c
                template <>
                struct fma<v4f32> : public def_vector_type<v4f32>{
                        static v4f32 v(const v4f32& a, const v4f32& b,
                                       const v4f32& c);
                };

                // a * b - c
                template <>
                struct fms<v4f32> : public def_vector_type<v4f32>{
                        static v4f32 v(const v4f32& a, const v4f32& b,
                                       const v4f32& c);
                };

                // -(a * b) + c = c - a * b
                template <>
                struct fnma<v4f32> : public def_vector_type<v4f32>{
                        static v4f32 v(const v4f32& a, const v4f32& b,
                                       const v4f32& c);
                };
        }

        DEFINE_X86VEC_FP_OPERATORS(v4f32);

        v4f32& operator|= (v4f32& a, const v4f32& b);
        v4f32& operator&= (v4f32& a, const v4f32& b);
        v4f32& operator^= (v4f32& a, const v4f32& b);

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
	
        v4f32 rcp(const v4f32& a);
        v4f32 native_rcp(const v4f32& a);
        v4f32 rsqrt(const v4f32& a);
        v4f32 native_rsqrt(const v4f32& a);

        namespace impl {
                v4f32 round(const v4f32& a, const rounding_mode::type m);
        }
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

	void sincos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos);
	v4f32 sin(arg<v4f32>::type d);
        v4f32 cos(arg<v4f32>::type d);
        v4f32 tan(arg<v4f32>::type d);
	v4f32 cot(arg<v4f32>::type d);

	v4f32 native_sin(arg<v4f32>::type d);
        v4f32 native_cos(arg<v4f32>::type d);
        v4f32 native_tan(arg<v4f32>::type d);
	v4f32 native_cot(arg<v4f32>::type d);

        template < bool _P0, bool _P1, bool _P2, bool _P3>
        v4f32 select(const v4f32& a, const v4f32& b);
        v4f32 select(const v4f32& msk, const v4f32& on_true,
                     const v4f32& on_false);

        template < int _P0, int _P1, int _P2, int _P3 >
        v4f32 permute(const v4f32& a);
        template < int _P0, int _P1, int _P2, int _P3 >
        v4f32 permute(const v4f32& a, const v4f32& b);

        template <unsigned _I>
        v4f32 insert(const v4f32& a, typename v4f32::element_type v);
        template <unsigned _I>
        typename v4f32::element_type extract(const v4f32& a);

        v4f32::element_type hadd(const v4f32& a);
        v4f32 hadd_pairs(const v4f32& a, const v4f32& b);
        v4f32 hsub_pairs(const v4f32& a, const v4f32& b);
        v4f32 hmul_pairs(const v4f32& a, const v4f32& b);
        v4f32 hdiv_pairs(const v4f32& a, const v4f32& b);

        v4f32::element_type dot(const v4f32& a, const v4f32& b);

        class v2f64 : public vreg<__m128d> {
        public:
                typedef double element_type;
                typedef vreg<__m128d> base_type;
                v2f64() = default;
                v2f64(vector_type r);
                v2f64(const base_type& r);
                v2f64(element_type p00, element_type p01);
                // broadcast to all positions
                v2f64(element_type r);
                // construction from expr<op<v2f64>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v2f64(const expr<_OP<v2f64>, _L, _R>& r);
                v2f64(const mem::addr_bcast<element_type>& r);
                v2f64(const mem::addr<element_type>& r);
                v2f64(const mem::aligned::addr<element_type>& r);
                v2f64(const mem::unaligned::addr<element_type>& r);
                using base_type::operator();
                masked_vec<v2f64> operator()(const mask<v2f64>& m);
        };

        inline
        const v2f64& eval(const v2f64& v) {
                return v;
        }

        namespace ops {

                template <>
                struct add<v2f64> : public def_vector_type<v2f64> {
                        static v2f64 v(const v2f64& a, const v2f64& b);
                };

                template <>
                struct sub<v2f64> : public def_vector_type<v2f64>{
                        static v2f64 v(const v2f64& a, const v2f64& b);
                };

                template <>
                struct mul<v2f64> : public def_vector_type<v2f64>{
                        static v2f64 v(const v2f64& a, const v2f64& b);
                };

                template <>
                struct div<v2f64> : public def_vector_type<v2f64>{
                        static v2f64 v(const v2f64& a, const v2f64& b);
                };

                // a * b + c
                template <>
                struct fma<v2f64> : public def_vector_type<v2f64>{
                        static v2f64 v(const v2f64& a, const v2f64& b,
                                       const v2f64& c);
                };

                // a * b - c
                template <>
                struct fms<v2f64> : public def_vector_type<v2f64>{
                        static v2f64 v(const v2f64& a, const v2f64& b,
                                       const v2f64& c);
                };

                // -(a * b) + c = c - a * b
                template <>
                struct fnma<v2f64> : public def_vector_type<v2f64>{
                        static v2f64 v(const v2f64& a, const v2f64& b,
                                       const v2f64& c);
                };
        }

        DEFINE_X86VEC_FP_OPERATORS(v2f64);

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
	// return a mask of signs
	unsigned read_signs(const v2f64& a);

        v2f64 max(const v2f64& a, const v2f64& b);
        v2f64 min(const v2f64& a, const v2f64& b);
        v2f64 abs(const v2f64& a);
        v2f64 fabs(const v2f64& a);
        v2f64 sqrt(const v2f64& a);
	v2f64 cbrt(arg<v2f64>::type a);
	v2f64 hypot(const v2f64& a, const v2f64& b);

	v2f64 rsqrt(const v2f64& a);
	v2f64 native_rsqrt(const v2f64& a);

        namespace impl {
                v2f64 round(const v2f64& a, const rounding_mode::type m);
        }
        v2f64 rint(const v2f64& a);
        v2f64 floor(const v2f64& a);
        v2f64 ceil(const v2f64& a);
        v2f64 trunc(const v2f64& a);
        // returns (~a) & (b)
        v2f64 andnot(const v2f64& a, const v2f64& b);
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
        std::pair<v2f64, v2f64> sincos(arg<v2f64>::type d);

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
	v2f64 native_sin(arg<v2f64>::type d);
	v2f64 native_cos(arg<v2f64>::type d);
	v2f64 native_tan(arg<v2f64>::type d);
	v2f64 native_cot(arg<v2f64>::type d);
	v2f64 cosh(arg<v2f64>::type d);
	v2f64 sinh(arg<v2f64>::type d);

        v2f64 pow(arg<v2f64>::type x, arg<v2f64>::type y);

        namespace impl {
                // fma emulation (a*b +c), calculates correctly until
                // no internal overflow occurs
                v2f64 fma(arg<v2f64>::type a, arg<v2f64>::type b,
                          arg<v2f64>::type c);
        }
        // a*b +c
        v2f64 fma(const v2f64& a, const v2f64& b, const v2f64& c);
        // a*b -c
        v2f64 fms(const v2f64& a, const v2f64& b, const v2f64& c);
        // -(a*b) + c
        v2f64 nfma(const v2f64& a, const v2f64& b, const v2f64& c);
        // -(a*b) - c
        v2f64 nfms(const v2f64& a, const v2f64& b, const v2f64& c);

        // a*b +c with rounding or not
        v2f64 mad(const v2f64& a, const v2f64& b, const v2f64& c);
        // -(a*b) +c with rounding or not
        v2f64 nmad(const v2f64& a, const v2f64& b, const v2f64& c);

        template < bool _P0, bool _P1>
        v2f64 select(const v2f64& a, const v2f64& b);
        v2f64 select(const v2f64& msk, const v2f64& on_true,
                     const v2f64& on_false);

        template < int _P0, int _P1>
        v2f64 permute(const v2f64& a);
        template < int _P0, int _P1>
        v2f64 permute(const v2f64& a, const v2f64& b);

        template <unsigned _I>
        v2f64 insert(const v2f64& a, typename v2f64::element_type v);
        template <unsigned _I>
        typename v2f64::element_type extract(const v2f64& a);

        v2f64::element_type hadd(const v2f64& a);

#if defined (__AVX__)
        // 256 bit floating point types
        class v8f32 : public vreg<__m256> {
        public:
                typedef float element_type;
                typedef vreg<__m256> base_type;
                v8f32() = default;
                v8f32(vector_type r);
                v8f32(const base_type& r);
		v8f32(const v4f32& l, const v4f32& h);
                v8f32(element_type p00, element_type p01,
                      element_type p02=0.0f, element_type p03=0.0f,
		      element_type p04=0.0f, element_type p05=0.0f,
                      element_type p06=0.0f, element_type p07=0.0f);
                // broadcast to all positions
                v8f32(element_type r);
                v8f32(element_type r, bool broadcast);
                // construction from expr<op<v8f32>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v8f32(const expr<_OP<v8f32>, _L, _R>& r);
                v8f32(const mem::addr_bcast<element_type>& r);
                v8f32(const mem::addr<element_type>& r);
                v8f32(const mem::aligned::addr<element_type>& r);
                v8f32(const mem::unaligned::addr<element_type>& r);
                using base_type::operator();
                masked_vec<v8f32> operator()(const mask<v8f32>& m);
        };

        namespace ops {

                template <>
                struct add<v8f32> : public def_vector_type<v8f32> {
                        static v8f32 v(const v8f32& a, const v8f32& b);
                };

                template <>
                struct sub<v8f32> : public def_vector_type<v8f32>{
                        static v8f32 v(const v8f32& a, const v8f32& b);
                };

                template <>
                struct mul<v8f32> : public def_vector_type<v8f32>{
                        static v8f32 v(const v8f32& a, const v8f32& b);
                };

                template <>
                struct div<v8f32> : public def_vector_type<v8f32>{
                        static v8f32 v(const v8f32& a, const v8f32& b);
                };

                // a * b + c
                template <>
                struct fma<v8f32> : public def_vector_type<v8f32>{
                        static v8f32 v(const v8f32& a, const v8f32& b,
                                       const v8f32& c);
                };

                // a * b - c
                template <>
                struct fms<v8f32> : public def_vector_type<v8f32>{
                        static v8f32 v(const v8f32& a, const v8f32& b,
                                       const v8f32& c);
                };

                // -(a * b) + c = c - a * b
                template <>
                struct fnma<v8f32> : public def_vector_type<v8f32>{
                        static v8f32 v(const v8f32& a, const v8f32& b,
                                       const v8f32& c);
                };
        }

#if !defined (__AVX2__)
	// conversion helpers for avx
	namespace impl {
		template <>
		struct vector_traits<v8s32> {
			typedef v8s32 vector_type;
			static const vector_type& v(const v8s32& r) {
				return r;
			}
		};

		template <> 
		struct cast<v8s32, __m256> {
			static v8s32 v(const __m256& r) {
				__m128 h=_mm256_extractf128_ps(r, 1);
				__m128 l=cast<__m128, __m256>::v(r);
				__m128i il=cast<__m128i, __m128>::v(l);
				__m128i ih=cast<__m128i, __m128>::v(h);
				return v8s32(il, ih);
			}
		};

		template <> 
		struct cast<__m256, v8s32> {
			static __m256 v(const v8s32& r) {
				__m128i il= low_half(r)();
				__m128i ih= high_half(r)();
				__m128 fl=cast<__m128, __m128i>::v(il);
				__m128 fh=cast<__m128, __m128i>::v(ih);
				__m256 res=cast<__m256, __m128>::v(fl);
				res = _mm256_insertf128_ps(res, fh, 1);
				return res;
			}
		};
	}
#endif

        inline
        const v8f32& eval(const v8f32& v) {
                return v;
        }

        DEFINE_X86VEC_FP_OPERATORS(v8f32);

        v8f32& operator|= (v8f32& a, const v8f32& b);
        v8f32& operator&= (v8f32& a, const v8f32& b);
        v8f32& operator^= (v8f32& a, const v8f32& b);

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

	v4f32 low_half(const v8f32& v);
	v4f32 high_half(const v8f32& v);

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
	
        v8f32 rcp(const v8f32& a);
        v8f32 native_rcp(const v8f32& a);
        v8f32 rsqrt(const v8f32& a);
        v8f32 native_rsqrt(const v8f32& a);

        namespace impl {
                v8f32 round(const v8f32& a, const rounding_mode::type m);
        }
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

        v8f32 pow2if(arg<v8s32>::type e);
        v8f32 ldexp(arg<v8f32>::type d, arg<v8s32>::type e);
        v8f32 frexp(arg<v8f32>::type d, v8s32* e);
        v8s32 ilogbp1(arg<v8f32>::type v);
        v8s32 ilogb(arg<v8f32>::type v);

	void sincos(arg<v8f32>::type d, v8f32* psin, v8f32* pcos);
	v8f32 sin(arg<v8f32>::type d);
        v8f32 cos(arg<v8f32>::type d);
        v8f32 tan(arg<v8f32>::type d);
	v8f32 cot(arg<v8f32>::type d);

	v8f32 native_sin(arg<v8f32>::type d);
        v8f32 native_cos(arg<v8f32>::type d);
        v8f32 native_tan(arg<v8f32>::type d);
	v8f32 native_cot(arg<v8f32>::type d);

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

        v8f32::element_type hadd(const v8f32& a);
        v8f32 hadd_pairs(const v8f32& a, const v8f32& b);
        v8f32 hsub_pairs(const v8f32& a, const v8f32& b);
        v8f32 hmul_pairs(const v8f32& a, const v8f32& b);
        v8f32 hdiv_pairs(const v8f32& a, const v8f32& b);

        v8f32::element_type dot(const v8f32& a, const v8f32& b);

        class v4f64 : public vreg<__m256d> {
        public:
                typedef double element_type;
                typedef vreg<__m256d> base_type;
                v4f64() = default;
                v4f64(vector_type r);
                v4f64(const base_type& r);
                v4f64(element_type p00, element_type p01,
		      element_type p02=0.0, element_type p03=0.0);
		v4f64(const v2f64& l);
		v4f64(const v2f64& l, const v2f64& h);
                // broadcast to all positions
                v4f64(element_type r);
		v4f64(element_type r, bool broad_cast);
                // construction from expr<op<v4f64>, _L, _R>
                template <template <class _V> class _OP, class _L, class _R>
                v4f64(const expr<_OP<v4f64>, _L, _R>& r);
                v4f64(const mem::addr_bcast<element_type>& r);
                v4f64(const mem::addr<element_type>& r);
                v4f64(const mem::aligned::addr<element_type>& r);
                v4f64(const mem::unaligned::addr<element_type>& r);
                using base_type::operator();
                masked_vec<v4f64> operator()(const mask<v4f64>& m);
        };

        namespace ops {

                template <>
                struct add<v4f64> : public def_vector_type<v4f64> {
                        static v4f64 v(const v4f64& a, const v4f64& b);
                };

                template <>
                struct sub<v4f64> : public def_vector_type<v4f64>{
                        static v4f64 v(const v4f64& a, const v4f64& b);
                };

                template <>
                struct mul<v4f64> : public def_vector_type<v4f64>{
                        static v4f64 v(const v4f64& a, const v4f64& b);
                };

                template <>
                struct div<v4f64> : public def_vector_type<v4f64>{
                        static v4f64 v(const v4f64& a, const v4f64& b);
                };

                // a * b + c
                template <>
                struct fma<v4f64> : public def_vector_type<v4f64>{
                        static v4f64 v(const v4f64& a, const v4f64& b,
                                       const v4f64& c);
                };

                // a * b - c
                template <>
                struct fms<v4f64> : public def_vector_type<v4f64>{
                        static v4f64 v(const v4f64& a, const v4f64& b,
                                       const v4f64& c);
                };

                // -(a * b) + c = c - a * b
                template <>
                struct fnma<v4f64> : public def_vector_type<v4f64>{
                        static v4f64 v(const v4f64& a, const v4f64& b,
                                       const v4f64& c);
                };
        }

        inline
        const v4f64& eval(const v4f64& v) {
                return v;
        }

        DEFINE_X86VEC_FP_OPERATORS(v4f64);

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
	// return a mask of signs
	unsigned read_signs(const v4f64& a);

        v4f64 max(const v4f64& a, const v4f64& b);
        v4f64 min(const v4f64& a, const v4f64& b);
        v4f64 abs(const v4f64& a);
        v4f64 fabs(const v4f64& a);
        v4f64 sqrt(const v4f64& a);
	v4f64 cbrt(arg<v4f64>::type a);
	v4f64 hypot(const v4f64& a, const v4f64& b);

	v4f64 rsqrt(const v4f64& a);
	v4f64 native_rsqrt(const v4f64& a);

        namespace impl {
                v4f64 round(const v4f64& a, const rounding_mode::type m);
        }
        v4f64 rint(const v4f64& a);
        v4f64 floor(const v4f64& a);
        v4f64 ceil(const v4f64& a);
        v4f64 trunc(const v4f64& a);
        // returns (~a) & (b)
        v4f64 andnot(const v4f64& a, const v4f64& b);
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
        std::pair<v4f64, v4f64> sincos(arg<v4f64>::type d);

        v4f64 exp(arg<v4f64>::type d);
	v4f64 expm1(arg<v4f64>::type d);
        v4f64 log(arg<v4f64>::type d);
	v4f64 pow(arg<v4f64>::type b, arg<v4f64>::type e);
	void sincos(arg<v4f64>::type d, v4f64* psin, v4f64* pcos);
	v4f64 sin(arg<v4f64>::type d);
        v4f64 cos(arg<v4f64>::type d);
        v4f64 tan(arg<v4f64>::type d);
	v4f64 cot(arg<v4f64>::type d);
	
	void native_sincos(arg<v4f64>::type d, v4f64* psin, v4f64* pcos);
	v4f64 native_exp(arg<v4f64>::type d);
	v4f64 native_sin(arg<v4f64>::type d);
	v4f64 native_cos(arg<v4f64>::type d);
	v4f64 native_tan(arg<v4f64>::type d);
	v4f64 native_cot(arg<v4f64>::type d);
	v4f64 cosh(arg<v4f64>::type d);
	v4f64 sinh(arg<v4f64>::type d);

        v4f64 pow(arg<v4f64>::type x, arg<v4f64>::type y);

        namespace impl {
                // fma emulation (a*b +c), calculates correctly until
                // no internal overflow occurs
                v4f64 fma(arg<v4f64>::type a, arg<v4f64>::type b,
                          arg<v4f64>::type c);
        }
        // a*b +c
        v4f64 fma(const v4f64& a, const v4f64& b, const v4f64& c);
        // a*b -c
        v4f64 fms(const v4f64& a, const v4f64& b, const v4f64& c);
        // -(a*b) + c
        v4f64 nfma(const v4f64& a, const v4f64& b, const v4f64& c);
        // -(a*b) - c
        v4f64 nfms(const v4f64& a, const v4f64& b, const v4f64& c);

        // a*b +c with rounding or not
        v4f64 mad(const v4f64& a, const v4f64& b, const v4f64& c);
        // -(a*b) +c with rounding or not
        v4f64 nmad(const v4f64& a, const v4f64& b, const v4f64& c);

        template < bool _P0, bool _P1, bool _P2, bool _P3>
        v4f64 select(const v4f64& a, const v4f64& b);
        v4f64 select(const v4f64& msk, const v4f64& on_true,
                     const v4f64& on_false);

        template < int _P0, int _P1, int _P2, int _P3>
        v4f64 permute(const v4f64& a);
        template < int _P0, int _P1, int _P2, int _P3>
        v4f64 permute(const v4f64& a, const v4f64& b);

        template <unsigned _I>
        v4f64 insert(const v4f64& a, typename v4f64::element_type v);
        template <unsigned _I>
        typename v4f64::element_type extract(const v4f64& a);

        v4f64::element_type hadd(const v4f64& a);
#endif
}


template <unsigned _N, typename _T>
_T x86vec::impl::polevl(_T x, const _T* coef)
{
        const _T* p= coef;
        _T ans= *p++;
        int i= _N;
        do {
                ans = mad(ans, x,  *p);
                ++p;
        } while (--i);
        return ans;
}

template <unsigned _N, typename _T>
_T x86vec::impl::p1evl(_T x, const _T* coef)
{
        const _T* p= coef;
        _T ans= x* *p;
        ++p;
        int i= _N-1;
        do {
                ans = mad(ans, x, *p);
                ++p;
        } while (--i);
        return ans;
}

template <class _T>
inline
_T x86vec::gather(const double* base, const v4s32& idx, int scale)
{
	using vec_type = typename _T::vector_type;
	_T r(impl::vgatherdpd<vec_type>::v(base, idx(), scale));
	return r;
}


template <class _T, class _IDX>
inline
_T x86vec::gather(const double* base, const _IDX& idx, int scale)
{
	using vec_type = typename _T::vector_type;
	_T r(impl::vgatherdps<vec_type, _IDX>::v(base, idx, scale));
	return r;
}

#include <cftal/x86vec_v4f32_inl.h>
#include <cftal/x86vec_v2f64_inl.h>

#if defined (__AVX__)
#include <cftal/x86vec_v8f32_inl.h>
#include <cftal/x86vec_v4f64_inl.h>
#endif

// Local variables:
// mode: c++
// end:
#endif
