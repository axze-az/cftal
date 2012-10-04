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

// Local variables:
// mode: c++
// end:
#endif
