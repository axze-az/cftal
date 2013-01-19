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
		masked_vec<v4f32> operator()(const mask<v4f32>& m);
		~v4f32();
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

	class v2f64 : public impl::vec_base<double,2>::type {
	public:
		enum { N = 2 };
		typedef double element_type;
		typedef typename impl::vec_base<double, 2>::type
		base_type;
		element_type* operator()();
		const element_type* operator()() const;
		v2f64();
		v2f64(element_type r);
		v2f64(element_type r, bool broadcast);
		v2f64(element_type p00, element_type p01);
		v2f64(const v2f64& r);
		v2f64(v2f64&& r);
		// assignment from expr<op<v2f64>, _L, _R>
		template <template <class _V> class _OP, class _L, class _R>
		v2f64(const expr<_OP<v2f64>, _L, _R>& r);
		v2f64& operator=(element_type r);
		v2f64& operator=(const v2f64& r);
		v2f64& operator=(v2f64&& r);
		v2f64(const mem::addr_bcast<element_type>& r);
		v2f64(const mem::addr<element_type>& r);
		masked_vec<v2f64> operator()(const mask<v2f64>& m);
		~v2f64();
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
	v2f64 sqrt(const v2f64& a);

	v2f64 rint(const v2f64& a);
	v2f64 floor(const v2f64& a);
	v2f64 ceil(const v2f64& a);
	v2f64 trunc(const v2f64& a);

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
        return static_cast<element_type*>(base_type::vbegin());
}

inline
const emuvec::v2f64::element_type* emuvec::v2f64::begin() const
{
        return static_cast<const element_type*>(base_type::vbegin());
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

// Local variables:
// mode: c++
// end:
#endif
