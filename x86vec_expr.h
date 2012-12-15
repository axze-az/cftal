#if !defined (__X86VEC_EXPR_H__)
#define __X86VEC_EXPR_H__ 1

#include <cftal/x86vec_intrin.h>

namespace x86vec {

	namespace ops {

		template <class _V> struct def_vector_type {
			typedef _V vector_type;
		};

		template <class _V> struct add {};
		template <class _V> struct sub {};
		template <class _V> struct mul {};
		template <class _V> struct div {};

		// fma (a*b+c) implementation
		template <class _V> struct fma : public def_vector_type<_V> {
			static _V v(const _V& a, const _V& b, const _V& c) {
				return add<_V>::v(mul<_V>::v(a,b), c);
			}
		};
		// fms (a*b-c) implementation
		template <class _V> struct fms : public def_vector_type<_V> {
			static _V v(const _V& a, const _V& b, const _V& c) {
				return sub<_V>::v(mul<_V>::v(a,b), c);
			}
		};
		// fnma (c-a*b)= -a*b + c implementation
		template <class _V> struct fnma : public def_vector_type<_V> {
			static _V v(const _V& a, const _V& b, const _V& c) {
				return sub<_V>::v(c, mul<_V>::v(a,b));
			}
		};
	}

	template <class _OP, class _L, class _R>
	struct expr {
		const _L _l;
		const _R _r;
		constexpr expr(const _L& l, const _R& r) :
			_l(l), _r(r) {}
	};

	template <class _OP, class _L, class _R>
	typename _OP::vector_type 
	eval(const expr<_OP, _L, _R>& e) {
		return _OP::v(eval(e._l), eval(e._r)); 
	}

	// a+ b*c 
	template <class _V, class _L1, class _L2, class _R2>
	_V eval(const expr<ops::add<_V>, 
			   _L1, 
			   expr<ops::mul<_V>, _L2, _R2> >& e) {
		return ops::fma<_V>::v(eval(e._r._l), eval(e._r._r), 
				       eval(e._l));
	}
	// a*b +c 
	template <class _V, class _L1, class _R1, class _R2>
	_V eval(const expr<ops::add<_V>, 
			   expr<ops::mul<_V>, _L1, _R1>,
			   _R2>& e) {
		return ops::fma<_V>::v(eval(e._l._l), eval(e._l._r), 
				       eval(e._r));
	}
	// a*b +c*d
	template <class _V, class _L1, class _R1, class _L2, class _R2>
	_V eval(const expr<ops::add<_V>, 
			   expr<ops::mul<_V>, _L1, _R1>,
			   expr<ops::mul<_V>, _L2, _R2> >& e) {
		return ops::fma<_V>::v(eval(e._l._l), eval(e._l._r), 
				       eval(e._r));
	}

	// a*b -c
	template <class _V, class _L1, class _R1, class _R2>
	_V eval(const expr<ops::sub<_V>,
			   expr<ops::mul<_V>, _L1, _R1>,
			   _R2>& e) {
		return ops::fms<_V>::v(e._l._l, e._l._r, e._r);
	}
	// -a*b +c = c- a* b;
	template <class _V, class _L1, class _L2, class _R2>
	_V eval(const expr<ops::sub<_V>,
			   _L1,
			   expr<ops::mul<_V>, _L2, _R2> >& e) {
		return ops::fnma<_V>::v(e._r._l, e._r._r, e._l);
	}

	// a*b - c*d
	template <class _V, class _L1, class _R1, class _L2, class _R2>
	_V eval(const expr<ops::sub<_V>, 
			   expr<ops::mul<_V>, _L1, _R1>,
			   expr<ops::mul<_V>, _L2, _R2> >& e) {
		return ops::fms<_V>::v(eval(e._l._l), eval(e._l._r), 
				       eval(e._r));
	}

}

#endif
