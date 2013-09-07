#if !defined (__X86VEC_MASK_H__)
#define __X86VEC_MASK_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cftal/x86vec_expr.h>

namespace x86vec {

	// mask of a vector.
	template <class _V>
	class mask {
		_V _v;
	public:
		mask() = default;
		mask& operator=(const mask& r) = default;
		mask(const _V& x);
		_V operator()() const;
	};

	// masked vector to allow something like
	// x(mask) = rhs <--> select(mask, rhs, x)
	template <class _V>
	class masked_vec {
		_V* _v;
		mask<_V> _m;
	public:
		masked_vec() = delete;
		masked_vec(_V& v, const mask<_V>& m);
		masked_vec& operator=(const masked_vec& r) = delete;
		_V& operator=(const _V& r);
		template <template <class _VV> class _OP, class _L, class _R>
		_V& operator=(const expr<_OP<_V>, _L, _R>& r);
#if 0
		explicit operator _V() const;
#endif
	};

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
template <template <class _X> class _OP, class _L, class _R>
inline
_V&
x86vec::masked_vec<_V>::operator=(const expr<_OP<_V>, _L, _R>& r)
{
	_V r0(r);
	_V& res= *_v;
	res = select(_m(), r0, res);
	return res;
}

#if 0
template <class _V>
inline
x86vec::masked_vec<_V>::operator _V () const 
{
	return *_v;
}
#endif

// Local variables:
// mode: c++
// end:
#endif
