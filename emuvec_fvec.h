#if !defined (__EMUVEC_FVEC_H__)
#define __EMUVEC_FVEC_H__ 1

#include <cftal/config.h>
#include <cftal/emuvec_impl.h>
#include <cftal/emuvec_impl_ops.h>
#include <cftal/emuvec_expr.h>
#include <algorithm>

namespace emuvec {

	class v4f32 : public impl::vec_base<float,4>::type {
	public:
		enum { N = 4 };
		typedef float element_type;
		typedef typename impl::vec_base<float,4>::type
		base_type;
		element_type* operator()();
		const element_type* operator()() const;
		v4f32();
		v4f32(element_type r);
		v4f32(element_type r, bool broadcast);
		v4f32(element_type p00, element_type p01,
		      element_type p02, element_type p03);
		v4f32(const v4f32& r);
		v4f32(v4f32&& r);
		// assignment from expr<op<v4f32>, _L, _R>
		template <template <class _V> class _OP, class _L, class _R>
		v4f32(const expr<_OP<v4f32>, _L, _R>& r);
		v4f32& operator=(element_type r);
		v4f32& operator=(const v4f32& r);
		v4f32& operator=(v4f32&& r);
		v4f32(const mem::addr_bcast<element_type>& r);
		v4f32(const mem::addr<element_type>& r);
		~v4f32();
	private:
		element_type* begin();
		const element_type* begin() const;
	};


	template <>
	struct expr_traits<emuvec::v4f32> {
		typedef const emuvec::v4f32& type;
	};
	
	inline
	const v4f32::element_type& eval(const v4f32& v, size_t i) {
		return v()[i];
	}

	DEFINE_CFTAL_VEC_FP_OPERATORS(v4f32);

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

	v4f32 max(const v4f32& a, const v4f32& b);
	v4f32 min(const v4f32& a, const v4f32& b);
	v4f32 abs(const v4f32& a);
	v4f32 sqrt(const v4f32& a);

	v4f32 rint(const v4f32& a);
	v4f32 floor(const v4f32& a);
	v4f32 ceil(const v4f32& a);
	v4f32 trunc(const v4f32& a);

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

// Local variables:
// mode: c++
// end:
#endif
