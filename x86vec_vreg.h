#if !defined (__X86VEC_VREG_H__)
#define __X86VEC_VREG_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cftal/x86vec_select.h>
#include <cftal/x86vec_ins_ext.h>
#include <cftal/x86vec_perm.h>
#include <cftal/x86vec_load.h>

namespace x86vec {

	template <typename _T>
	struct arg { typedef _T type; };

        // wrapper around a vector register type
        template <class _X>
        class vreg {
                _X _v;
        public:
                typedef _X vector_type;
                typedef void element_type;
                vreg() = default;
		vreg(_X x);
		vreg& operator=(const vreg& r) = default;
                _X operator()() const;
                _X& operator()();
        };

	// mask of a vector.
	template <class _V>
	class mask {
		_V _v;
	public:
		typedef typename _V::vector_type vector_type;
		mask() = default;
		mask& operator=(const mask& r) = default;
		mask(const _V& x);
		_V operator()() const;
	};

	// masked vector to allow something like v x;
	// x(mask) = ...
	template <class _V>
	class masked_vec {
		_V* _v;
		mask<_V> _m;
	public:
		masked_vec() = delete;
		masked_vec(_V& v, const mask<_V>& m);
		masked_vec& operator=(const masked_vec& r) = delete;
		_V& operator=(const _V& r);
		explicit operator _V() const;
	};

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

	// template <class _T>
	// _T eval(const _T& t) {
	// 	return t;
	// }

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
	// a*b +c 
	template <class _V, class _L1, class _R1, class _L2, class _R2>
	_V eval(const expr<ops::add<_V>, 
			   expr<ops::mul<_V>, _L1, _R1>,
			   expr<ops::mul<_V>, _L2, _R2> >& e) {
		return ops::fma<_V>::v(eval(e._l._l), eval(e._l._r), 
				       eval(e._r));
	}

	// a*b -c
	template <class _V>
	_V eval(const expr<ops::sub<_V>,
			   expr<ops::mul<_V>, _V, _V>,
			   _V>& e) {
		return ops::fms<_V>::v(e._l._l, e._l._r, e._r);
	}
	// -a*b +c = c- a* b;
	template <class _V>
	_V eval(const expr<ops::sub<_V>,
			   _V,
			   expr<ops::mul<_V>, _V, _V> >& e) {
		return ops::fnma<_V>::v(e._r._l, e._r._r, e._l);
	}
	
	template <class _OP, class _T>
	struct bi_op {
		const _T _a0;
		const _T _a1;
		constexpr bi_op(const _T& a0, const _T& a1);
	};

	template <class _OP, class _T>
	struct tri_op {
		const _T _a0;
		const _T _a1;
		const _T _a2;
		constexpr tri_op(const _T& a0, const _T& a1, const _T& a2);
	};
}

template <class _X>
inline
x86vec::vreg<_X>::vreg(_X x) : _v(x)
{
}

template <class _X>
inline
_X x86vec::vreg<_X>::operator()() const
{
        return _v;
}

template <class _X>
inline
_X& x86vec::vreg<_X>::operator()()
{
        return _v;
}

template <class _V>
inline 
x86vec::mask<_V>::mask(const _V& x) : _v(x()) 
{
}

template <class _V>
inline 
_V x86vec::mask<_V>::operator()() const 
{
	return _v;
}

template <class _V>
inline
x86vec::masked_vec<_V>::masked_vec(_V& v, const mask<_V>& m)
	: _v(&v), _m(m)
{
}

template <class _V>
inline
_V& x86vec::masked_vec<_V>::operator=(const _V& r)
{
	_V& res= *_v;
	res = select(_m(), r, res);
	return res;
}

template <class _V>
inline
x86vec::masked_vec<_V>::operator _V () const 
{
	return *_v;
}

template <class _OP, class _T>
inline
constexpr
x86vec::bi_op<_OP, _T>::bi_op(const _T& a0, const _T& a1)
	: _a0(a0), _a1(a1)
{
}

template <class _OP, class _T>
inline
constexpr
x86vec::tri_op<_OP, _T>::tri_op(const _T& a0, const _T& a1, const _T& a2)
	: _a0(a0), _a1(a1), _a2(a2)
{
}


// Local variables:
// mode: c++
// end:
#endif
