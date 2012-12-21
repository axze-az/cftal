#if !defined (__EMUVEC_MASK_H__)
#define __EMUVEC_MASK_H__ 1

#include <cftal/emuvec_expr.h>

namespace emuvec {

	// mask of a vector.
	template <class _V>
	class mask {
		_V _v;
	public:
		mask() = default;
		mask& operator=(const mask& r) = default;
		mask(const _V& x);
		const _V& operator()() const;
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
	};

}

template <class _V>
inline 
emuvec::mask<_V>::mask(const _V& x) : _v(x()) 
{
}

template <class _V>
inline 
const _V& emuvec::mask<_V>::operator()() const 
{
	return _v;
}

template <class _V>
inline
emuvec::masked_vec<_V>::masked_vec(_V& v, const mask<_V>& m)
	: _v(&v), _m(m)
{
}

template <class _V>
inline
_V& emuvec::masked_vec<_V>::operator=(const _V& r)
{
	_V& res= *_v;
	res = select(_m(), r, res);
	return res;
}

template <class _V>
template <template <class _X> class _OP, class _L, class _R>
inline
_V&
emuvec::masked_vec<_V>::operator=(const expr<_OP<_V>, _L, _R>& r)
{
	_V& res= *_v;
	typename _V::element_type* p= res();
	const _V& msk= _m();
	const typename _V::element_type* mp= msk();
	for (size_t i=0; i<_V::N; ++i)
		if (impl::lt_z(mp[i]))
			p[i] = eval(r, i);
	return res;
}

// Local variables:
// mode: c++
// end:
#endif
