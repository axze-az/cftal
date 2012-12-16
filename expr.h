#if !defined (__CFTAL_EXPR_H__)
#define __CFTAL_EXPR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>

namespace cftal {

	namespace ops {

		template <class _V> struct add {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b) {
				return a + b;
			}
		};

		template <class _V> struct sub {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b) {
				return a - b;
			}
		};

		template <class _V> struct mul {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b) {
				return a * b;
			}
		};

		template <class _V> struct div {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b) {
				return a / b;
			}
		};

		// fma (a*b+c) implementation
		template <class _V> struct fma {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b, 
					      const element_type& c) {
				return add<_V>::v(mul<_V>::v(a,b), c);
			}
		};
		// fms (a*b-c) implementation
		template <class _V> struct fms {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b, 
					      const element_type& c) {
				return sub<_V>::v(mul<_V>::v(a,b), c);
			}
		};
		// fnma (c-a*b)= -a*b + c implementation
		template <class _V> struct fnma {
			typedef typename _V::element_type element_type;
			static element_type v(const element_type& a, 
					      const element_type& b, 
					      const element_type& c) {
				return sub<_V>::v(c, mul<_V>::v(a,b));
			}
		};


	}

	template <class _T>
	struct expr_traits {
		typedef const _T type;
	};

	template <class _OP, class _L, class _R>
	struct expr {
		typename expr_traits<_L>::type _l;
		typename expr_traits<_R>::type _r;
		constexpr expr(const _L& l, const _R& r) :
			_l(l), _r(r) {}
	};

	// allow scalars
	template <class _T>
	const _T& eval(const _T& v, size_t i) {
		static_cast<void>(i);
		return v;
	}

	template <class _OP, class _L, class _R>
	typename _OP::element_type 
	eval(const expr<_OP, _L, _R>& e, size_t i) {
		return _OP::v(eval(e._l, i), eval(e._r, i)); 
	}

	// a+ b*c 
	template <class _V, class _L1, class _L2, class _R2>
	typename _V::element_type
	eval(const expr<ops::add<_V>, 
			_L1, 
			expr<ops::mul<_V>, _L2, _R2> >& e,
	     size_t i) {
		return ops::fma<_V>::v(eval(e._r._l, i), eval(e._r._r, i), 
				       eval(e._l, i));
	}
	// a*b +c 
	template <class _V, class _L1, class _R1, class _R2>
	typename _V::element_type
	eval(const expr<ops::add<_V>, 
			expr<ops::mul<_V>, _L1, _R1>,
			_R2>& e,
	     size_t i) {
		return ops::fma<_V>::v(eval(e._l._l, i), eval(e._l._r, i), 
				       eval(e._r, i));
	}
	// a*b +c*d
	template <class _V, class _L1, class _R1, class _L2, class _R2>
	typename _V::element_type
	eval(const expr<ops::add<_V>, 
			expr<ops::mul<_V>, _L1, _R1>,
			expr<ops::mul<_V>, _L2, _R2> >& e,
	     size_t i) {
		return ops::fma<_V>::v(eval(e._l._l, i), eval(e._l._r, i), 
				       eval(e._r, i));
	}

	// a*b -c
	template <class _V, class _L1, class _R1, class _R2>
	typename _V::element_type
	eval(const expr<ops::sub<_V>,
			expr<ops::mul<_V>, _L1, _R1>,
			_R2>& e,
	     size_t i) {
		return ops::fms<_V>::v(eval(e._l._l,i), eval(e._l._r,i), 
				       eval(e._r, i));
	}
	// -a*b +c = c- a* b;
	template <class _V, class _L1, class _L2, class _R2>
	typename _V::element_type
	eval(const expr<ops::sub<_V>, 
	     _L1, 
	     expr< ops::mul<_V>, _L2, _R2> >&  e,
	     size_t i) {
		return ops::fnma<_V>::v(eval(e._r._l, i), eval(e._r._r, i), 
					eval(e._l, i));
	}

	// a*b - c*d
	template <class _V, class _L1, class _R1, class _L2, class _R2>
	typename _V::element_type
	eval(const expr<ops::sub<_V>, 
			expr<ops::mul<_V>, _L1, _R1>,
			expr<ops::mul<_V>, _L2, _R2> >& e, 
	     size_t i) {
		return ops::fms<_V>::v(eval(e._l._l, i), eval(e._l._r, i), 
				       eval(e._r, i));
	}

#define DEFINE_CFTAL_VEC_FP_OPERATORS(vx)				\
	/* operator +(V, V) */						\
	inline								\
	expr<ops::add<vx>, vx, vx>					\
	operator+(const vx& a, const vx& b) {				\
		return expr<ops::add<vx>, vx, vx>(a,b);			\
	}								\
	/* operator +(V, expr) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::add<vx>, vx, expr<_OP<vx>, _L, _R> >			\
	operator+(const vx& a, const expr<_OP<vx>, _L, _R>& b) {	\
		return expr<ops::add<vx>,				\
			    vx, expr<_OP<vx>, _L, _R> >(a, b);		\
	}								\
	/* operator +(expr, V) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::add<vx>, expr<_OP<vx>, _L, _R>, vx>			\
	operator+(const expr<_OP<vx>, _L, _R>& a, const vx& b) {	\
		return expr<ops::add<vx>,				\
			    expr<_OP<vx>, _L, _R>, vx>(a, b);		\
	}								\
	/* operator +(expr, expr)  */					\
	template <template <class _V> class _OP1, class _L1, class _R1,	\
		  template <class _V> class _OP2, class _L2, class _R2>	\
	inline								\
	expr<ops::add<vx>,						\
	     expr<_OP1<vx>, _L1, _R1>, expr<_OP2<vx>, _L2, _R2> >	\
	operator+(const expr<_OP1<vx>, _L1, _R1>& a,			\
		  const expr<_OP2<vx>, _L2, _R2>& b) {			\
		return expr<ops::add<vx>,				\
			    expr<_OP1<vx>, _L1, _R1>,			\
			    expr<_OP2<vx>, _L2, _R2> > (a, b);		\
	}								\
	/* operator += V */						\
	inline								\
	vx& operator+=(vx& a, const vx& r) {				\
		a = a + r;						\
		return a;						\
	}								\
	/* operator += expr */						\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	vx& operator+=(vx& a, const expr<_OP<vx>, _L, _R>& r) {		\
		a = a + r;						\
		return a;						\
	}								\
									\
	/* operator -(V, V) */						\
	inline								\
	expr<ops::sub<vx>, vx, vx>					\
	operator-(const vx& a, const vx& b) {				\
		return expr<ops::sub<vx>, vx, vx>(a,b);			\
	}								\
	/* operator -(V, expr) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::sub<vx>, vx, expr<_OP<vx>, _L, _R> >			\
	operator-(const vx& a, const expr<_OP<vx>, _L, _R>& b) {	\
		return expr<ops::sub<vx>,				\
			    vx, expr<_OP<vx>, _L, _R> >(a, b);		\
	}								\
	/* operator -(expr, V) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::sub<vx>, expr<_OP<vx>, _L, _R>, vx>			\
	operator-(const expr<_OP<vx>, _L, _R>& a, const vx& b) {	\
		return expr<ops::sub<vx>,				\
			    expr<_OP<vx>, _L, _R>, vx>(a, b);		\
	}								\
	/* operator -(expr, expr)  */					\
	template <template <class _V> class _OP1, class _L1, class _R1,	\
		  template <class _V> class _OP2, class _L2, class _R2>	\
	inline								\
	expr<ops::sub<vx>,						\
	     expr<_OP1<vx>, _L1, _R1>, expr<_OP2<vx>, _L2, _R2> >	\
	operator-(const expr<_OP1<vx>, _L1, _R1>& a,			\
		  const expr<_OP2<vx>, _L2, _R2>& b) {			\
		return expr<ops::sub<vx>,				\
			    expr<_OP1<vx>, _L1, _R1>,			\
			    expr<_OP2<vx>, _L2, _R2> > (a, b);		\
	}								\
	/* operator -= V */						\
	inline								\
	vx& operator-=(vx& a, const vx& r) {				\
		a = a - r;						\
		return a;						\
	}								\
	/* operator += expr */						\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	vx& operator-=(vx& a, const expr<_OP<vx>, _L, _R>& r) {		\
		a = a - r;						\
		return a;						\
	}								\
									\
	/* operator *(V, V) */						\
	inline								\
	expr<ops::mul<vx>, vx, vx>					\
	operator*(const vx& a, const vx& b) {				\
		return expr<ops::mul<vx>, vx, vx>(a,b);			\
	}								\
	/* operator *(V, expr) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::mul<vx>, vx, expr<_OP<vx>, _L, _R> >			\
	operator*(const vx& a, const expr<_OP<vx>, _L, _R>& b) {	\
		return expr<ops::mul<vx>,				\
			    vx, expr<_OP<vx>, _L, _R> >(a, b);		\
	}								\
	/* operator *(expr, V) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::mul<vx>, expr<_OP<vx>, _L, _R>, vx>			\
	operator*(const expr<_OP<vx>, _L, _R>& a, const vx& b) {	\
		return expr<ops::mul<vx>,				\
			    expr<_OP<vx>, _L, _R>, vx>(a, b);		\
	}								\
	/* operator *(expr, expr) */					\
	template <template <class _V> class _OP1, class _L1, class _R1,	\
		  template <class _V> class _OP2, class _L2, class _R2>	\
	inline								\
	expr<ops::mul<vx>,						\
	     expr<_OP1<vx>, _L1, _R1>, expr<_OP2<vx>, _L2, _R2> >	\
	operator*(const expr<_OP1<vx>, _L1, _R1>& a,			\
		  const expr<_OP2<vx>, _L2, _R2>& b) {			\
		return expr<ops::mul<vx>,				\
			    expr<_OP1<vx>, _L1, _R1>,			\
			    expr<_OP2<vx>, _L2, _R2> > (a, b);		\
	}								\
	/* operator *= V */						\
	inline								\
	vx& operator*=(vx& a, const vx& r) {				\
		a = a * r;						\
		return a;						\
	}								\
	/* operator *= expr */						\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	vx& operator*=(vx& a, const expr<_OP<vx>, _L, _R>& r) {		\
		a = a * r;						\
		return a;						\
	}								\
									\
	/* operator /(V, V) */						\
	inline								\
	expr<ops::div<vx>, vx, vx>					\
	operator/(const vx& a, const vx& b) {				\
		return expr<ops::div<vx>, vx, vx>(a,b);			\
	}								\
	/* operator /(V, expr)  */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::div<vx>, vx, expr<_OP<vx>, _L, _R> >			\
	operator/(const vx& a, const expr<_OP<vx>, _L, _R>& b) {	\
		return expr<ops::div<vx>,				\
			    vx, expr<_OP<vx>, _L, _R> >(a, b);		\
	}								\
	/* operator /(expr, V) */					\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	expr<ops::div<vx>, expr<_OP<vx>, _L, _R>, vx>			\
	operator/(const expr<_OP<vx>, _L, _R>& a, const vx& b) {	\
		return expr<ops::div<vx>,				\
			    expr<_OP<vx>, _L, _R>, vx>(a, b);		\
	}								\
	/* operator /(expr, expr) */					\
	template <template <class _V> class _OP1, class _L1, class _R1,	\
		  template <class _V> class _OP2, class _L2, class _R2>	\
	inline								\
	expr<ops::div<vx>,						\
	     expr<_OP1<vx>, _L1, _R1>, expr<_OP2<vx>, _L2, _R2> >	\
	operator/(const expr<_OP1<vx>, _L1, _R1>& a,			\
		  const expr<_OP2<vx>, _L2, _R2>& b) {			\
		return expr<ops::div<vx>,				\
			    expr<_OP1<vx>, _L1, _R1>,			\
			    expr<_OP2<vx>, _L2, _R2> > (a, b);		\
	}								\
	/* operator /= V */						\
	inline								\
	vx& operator/=(vx& a, const vx& r) {				\
		a = a / r;						\
		return a;						\
	}								\
	/* operator += expr */						\
	template <template <class _V> class _OP, class _L, class _R>	\
	inline								\
	vx& operator/=(vx& a, const expr<_OP<vx>, _L, _R>& r) {		\
		a = a / r;						\
		return a;						\
	}								\

}

// Local variables:
// mode: c++
// end:
#endif
