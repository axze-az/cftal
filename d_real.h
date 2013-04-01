#if !defined (__CFTAL_D_REAL_H__)
#define __CFTAL_D_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <type_traits>

namespace cftal {

	template <typename _T>
	struct d_real_traits;

	template <>
	struct d_real_traits<double> {
		// result of a comparison operator
		typedef bool cmp_result_type;
		// 2^27 + 1
		static constexpr double split = 
			134217729.0;
		// 2^996 = 2^1024-2^28
		static constexpr double split_threshold=
			6.69692879491417e+299;
		// 2^-28
		static constexpr double split_scale_down=
			3.7252902984619140625e-09;
		// 2^28
		static constexpr double split_scale_up=
			268435456.0;
		// fma ?
		static constexpr bool fma = false;
		// 
		static bool any(const cmp_result_type& b) { 
			return b; 
		}
	};


	template <typename _T> 
	class d_real {
		_T _h;
		_T _l;
	public:
		d_real(const _T& h, const _T& l) : _h(h), _l(l) {}
		d_real(const _T& h) : _h(h), _l(_T(0)) {}
		const _T& l() const { return _l; }
		_T& l() { return _l; }
		const _T& h() const { return _h; }
		_T& h() { return _h; }
	};

	namespace d_real_impl {
		
		template <typename _T>
		_T quick_two_sum(const _T& a, const _T& b, _T& e);
		
		template <typename _T>
		_T quick_two_diff(const _T& a, const _T& b, _T& e);
		
		template <typename _T>
		_T two_sum(const _T& a, const _T& b, _T& e);
		
		template <typename _T>
		_T two_diff(const _T& a, const _T& b, _T& e);

		template <typename _T>
		void split(const _T& a, _T& h, _T& l);

		template <typename _T>
		_T two_prod(const _T& a, const _T& b, _T& e);

		template <typename _T>
		_T two_sqr(const _T& a, _T& e);

		template <typename _T>
		d_real<_T> add(const _T& a, const _T& b);

		template <typename _T>
		d_real<_T> ieee_add(const d_real<_T>& a,
				    const d_real<_T>& b);

		template <typename _T>
		d_real<_T> sloppy_add(const d_real<_T>& a,
				    const d_real<_T>& b);

		template <typename _T>
		d_real<_T> sub(const _T& a, const _T& b);

		template <typename _T>
		d_real<_T> ieee_sub(const d_real<_T>& a,
				    const d_real<_T>& b);

		template <typename _T>
		d_real<_T> sloppy_sub(const d_real<_T>& a,
				    const d_real<_T>& b);

		template <typename _T>
		d_real<_T> mul(const _T& a, const _T& b);

		template <typename _T>
		d_real<_T> div(const _T& a, const _T& b);

		template <typename _T>
		d_real<_T> ieee_div(const d_real<_T>& a,
				    const d_real<_T>& b);

		template <typename _T>
		d_real<_T> sloppy_div(const d_real<_T>& a,
				      const d_real<_T>& b);
	}

	// comparison operators
	template <typename _T>
	typename d_real_traits<_T>::cmp_result_type 
	operator<(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	typename d_real_traits<_T>::cmp_result_type 
	operator<=(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	typename d_real_traits<_T>::cmp_result_type 
	operator==(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	typename d_real_traits<_T>::cmp_result_type 
	operator!=(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	typename d_real_traits<_T>::cmp_result_type 
	operator>(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	typename d_real_traits<_T>::cmp_result_type 
	operator>=(const d_real<_T>& a, const d_real<_T>& b);

	// unary minus
	template <typename _T>
	d_real<_T> 
	operator-(const d_real<_T>& a);
	// unary plus
	template <typename _T>
	const d_real<_T>& 
	operator+(const d_real<_T>& a);

	// addition
	template <typename _T>
	d_real<_T> 
	operator+(const _T& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>
	operator+(const d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T> 
	operator+(const d_real<_T>& a,  const d_real<_T>& b);

	template <typename _T>
	d_real<_T>&
	operator+=(d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>&
	operator+=(d_real<_T>& a, const d_real<_T>& b);

	// subtraction
	template <typename _T>
	d_real<_T> 
	operator-(const _T& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>
	operator-(const d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>
	operator+(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>&
	operator-=(d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>&
	operator-=(d_real<_T>& a, const d_real<_T>& b);

	// multiplication
	template <typename _T>
	d_real<_T>
	operator*(const _T& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>
	operator*(const d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>
	operator*(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>&
	operator*=(d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>&
	operator*=(d_real<_T>& a, const d_real<_T>& b);

	// division
	template <typename _T>
	d_real<_T>
	operator/(const d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>
	operator/(const _T& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T>
	operator/(const d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>&
	operator/=(d_real<_T>& a, const _T& b);

	template <typename _T>
	d_real<_T>&
	operator/=(d_real<_T>& a, const d_real<_T>& b);

	template <typename _T>
	d_real<_T> rcp(const d_real<_T>& r);

}

template <typename _T>
inline
_T 
cftal::d_real_impl::quick_two_sum(const _T& a, const _T& b, _T& err)
{
	_T s=a+b;
	err=b-(s-a);
	return s;
}

template <typename _T>
inline
_T 
cftal::d_real_impl::quick_two_diff(const _T& a, const _T& b, _T& err)
{
	_T s=a-b;
	err=(a-s)-b;
	return s;
}

template <typename _T>
inline
_T 
cftal::d_real_impl::two_sum(const _T& a, const _T& b, _T& err)
{
	_T s=a+b;
	_T bb=s-a;
	err=(a-(s-bb)) + (b -bb);
	return s;
}

template <typename _T>
inline
_T
cftal::d_real_impl::two_diff(const _T& a, const _T& b, _T& err)
{
	_T s=a-b;
	_T bb=s-a;
	err=(a-(s-bb))-(b+bb);
	return s;
}

template <typename _T>
inline
void 
cftal::d_real_impl::split(const _T& a0, _T& hi, _T& lo)
{
	_T temp;
	_T a=a0;
	if (d_real_traits<_T>::any(
		    a > d_real_traits<_T>::split_threshold) || 
	    d_real_traits<_T>::any(
		    a < -d_real_traits<_T>::split_threshold)) {
		a*=d_real_traits<_T>::split_scale_down;
		temp=d_real_traits<_T>::split*a;
		hi=temp-(temp-a);
		lo=a-hi;
		hi*=d_real_traits<_T>::split_scale_up;
		lo*=d_real_traits<_T>::split_scale_up;
	} else {
		temp=d_real_traits<_T>::split;
		hi=temp-(temp-a);
		lo=a-hi;
	}
}

template <typename _T>
inline
_T
cftal::d_real_impl::two_prod(const _T& a, const _T& b, _T& err)
{
	_T p=a*b;
	if (d_real_traits<_T>::fma) {
		err = fms(a, b, p);
	} else {
		_T a_h, a_l, b_h, b_l;
		split(a, a_h, a_l);
		split(b, b_h, b_l);
		err=((a_h*b_h-p)+a_h*b_l+a_l*b_h)+a_l*b_l;
	}
	return p;
}

template <typename _T>
inline
_T
cftal::d_real_impl::two_sqr(const _T& a)
{
	_T p=a*a;
	_T err;
	if (d_real_traits<_T>::fma) {
		err = fms(a, a, p);
	} else {
		_T a_h, a_l;
		split(a, a_h, a_l);
		err=((a_h*a_h-p)+2.0*a_h*a_l)+a_l*a_l;
	}
	return p;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::add(const _T& a, const _T& b)
{
	_T err, s= two_sum(a, b, err);
	return d_real<_T>(s, err);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::sub(const _T& a, const _T& b)
{
	_T err, s= two_diff(a, b, err);
	return d_real<_T>(s, err);
}


template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::ieee_add(const d_real<_T>& a, const d_real<_T>& b)
{
	_T s1, s2, t1, t2;
	s1 = two_sum(a.h(), b.h(), s2);
	t1 = two_sum(a.l(), b.l(), t2);
	s2+= t1;
	s1 = quick_two_sum(s1, s2, s2);
	s2+= t2;
	s1 = quick_two_sum(s1, s2, s2);
	return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::sloppy_add(const d_real<_T>& a, const d_real<_T>& b)
{
	_T s, e;
	s = two_sum(a.h(), b.h(), e);
	e+= (a.l() + b.l());
	s = quick_two_sum(s, e, e);
	return d_real<_T>(s, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::ieee_sub(const d_real<_T>& a, const d_real<_T>& b)
{
	_T s1, s2, t1, t2;
	s1 = two_diff(a.h(), b.h(), s2);
	t1 = two_diff(a.l(), b.l(), t2);
	s2+= t1;
	s1 = quick_two_sum(s1, s2, s2);
	s2+= t2;
	s1 = quick_two_sum(s1, s2, s2);
	return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::sloppy_sub(const d_real<_T>& a, const d_real<_T>& b)
{
	_T s, e;
	s = two_diff(a.h(), b.h(), e);
	e+= a.l();
	e-= b.l();
	s= quick_two_sum(s, e, e);
	return d_real<_T>(s, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::mul(const _T& a, const _T& b)
{
	_T p, e;
	p = two_prod(a, b, e);
	return d_real<_T>(p, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::div(const _T& a, const _T& b)
{
	_T q1, q2, p1, p2, s, e;
	q1 = a/b;
	/* a - q1 * b */
	p1 = two_prod(q1, b, p2);
	s = two_diff(a, p1, e);
	e-= p2;
	/* next approximation */
	q2= (s+e)/b;
	s = quick_two_sum(q1, q2, e);
	return d_real<_T>(s, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::ieee_div(const d_real<_T>& a, const d_real<_T>& b)
{
	_T q1, q2, q3;
	d_real<_T> r;
	q1 = a.h() / b.h();  /* approximate quotient */
	r = a - q1 * b;
	q2 = r.h() / b.h();
	r -= (q2 * b);
	q3 = r.h() / b.h();
	q1 = quick_two_sum(q1, q2, q2);
	r = d_real<_T>(q1, q2) + q3;
	return r;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::d_real_impl::sloppy_div(const d_real<_T>& a, const d_real<_T>& b)
{
	_T s1, s2, q1, q2;
	d_real<_T> r;
	/* approximate quotient */
	q1 = a.h() / b.h();  
	/* compute  this - q1 * dd */
	r = b * q1;
	s1 = two_diff(a.h(), r.h(), s2);
	s2 -= r.l();
	s2 += a.l();
	/* get next approximation */
	q2 = (s1 + s2) / b.h();
	/* renormalize */
	r.h() = quick_two_sum(q1, q2, r.l());
	return r;
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator<(const d_real<_T>& a, const d_real<_T>& b)
{
	return (a.h() < b.h()) ||
		((a.h()==b.h()) && a.l() < b.l());
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator<=(const d_real<_T>& a, const d_real<_T>& b)
{
	return (a.h() < b.h()) ||
		((a.h()==b.h()) && a.l() <= b.l());
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator==(const d_real<_T>& a, const d_real<_T>& b)
{
	return ((a.h()==b.h()) && (a.l() == b.l()));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator!=(const d_real<_T>& a, const d_real<_T>& b)
{
	return ((a.h()!=b.h()) || (a.l() != b.l()));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator>=(const d_real<_T>& a, const d_real<_T>& b)
{
	return ((a.h()>b.h()) || 
		((a.h()==b.h()) && (a.l() >= b.l())));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator>(const d_real<_T>& a, const d_real<_T>& b)
{
	return ((a.h()>b.h()) || 
		((a.h()==b.h()) && (a.l() > b.l())));
}


template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a)
{
	return d_real<_T>(-a.h(), -a.l());
}

template <typename _T>
inline
const cftal::d_real<_T>&
cftal::operator+(const d_real<_T>& a)
{
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const d_real<_T>& a, const _T& b)
{
	_T s1, s2;
	s1 = d_real_impl::two_sum(a.h(), b, s2);
	s2+= a.l();
	s1 = d_real_impl::quick_two_sum(s1, s2, s2);
	return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const _T& a, const d_real<_T>& b)
{
	return b + a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const d_real<_T>& a, const d_real<_T>& b)
{
	return d_real_impl::ieee_add(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator+=(d_real<_T>& a, const _T& b)
{
	a= a + b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator+=(d_real<_T>& a, const d_real<_T>& b)
{
	a= a + b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a, const _T& b)
{
	_T s1, s2;
	s1 = d_real_impl::two_diff(a.h(), b, s2);
	s2+= a.l();
	s1 = d_real_impl::quick_two_sum(s1, s2, s2);
	return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const _T& a, const d_real<_T>& b)
{
	_T s1, s2;
	s1 = d_real_impl::two_diff(a, b.h(), s2);
	s2-= b.l();
	s1 = d_real_impl::quick_two_sum(s1, s2, s2);
	return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a, const d_real<_T>& b)
{
	return d_real_impl::ieee_sub(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator-=(d_real<_T>& a, const _T& b)
{
	a= a - b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator-=(d_real<_T>& a, const d_real<_T>& b)
{
	a= a - b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const d_real<_T>& a, const _T& b)
{
	_T p1, p2;
	p1 = d_real_impl::two_prod(a.h(), b, p2);
	p2+= (a.l()*b);
	p1 = d_real_impl::quick_two_sum(p1, p2, p2);
	return d_real<_T>(p1, p2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const _T& a, const d_real<_T>& b)
{
	return b*a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const d_real<_T>& a, const d_real<_T>& b)
{
	_T p1, p2;
	p1 = d_real_impl::two_prod(a.h(), b.h(), p2);
	p2+= (a.h()*b.l() + a.l() * b.h());
	p1 = d_real_impl::quick_two_sum(p1, p2, p2);
	return d_real<_T>(p1, p2);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator*=(d_real<_T>& a, const _T& b)
{
	a= a * b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator*=(d_real<_T>& a, const d_real<_T>& b)
{
	a= a * b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const d_real<_T>& a, const _T& b)
{
	_T q1, q2, p1, p2, s, e;
	d_real<_T> r;
	/* approximate quotient. */
	q1 = a.h() / b;   
	/* Compute  this - q1 * d */
	p1 = d_real_impl::two_prod(q1, b, p2);
	s = d_real_impl::two_diff(a.h(), p1, e);
	e += a.l();
	e -= p2;
  	/* get next approximation. */
	q2 = (s + e) / b;
	/* renormalize */
	r.h() = d_real_impl::quick_two_sum(q1, q2, r.l());
	return r;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const _T& a, const d_real<_T>& b)
{
	return d_real_impl::ieee_div(d_real<_T>(a), b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const d_real<_T>& a, const d_real<_T>& b)
{
	return d_real_impl::ieee_div(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator/=(d_real<_T>& a, const _T& b)
{
	a= a / b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator/=(d_real<_T>& a, const d_real<_T>& b)
{
	a= a / b;
	return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::rcp(const d_real<_T>& a)
{
	return _T(1)/a;
}

// Local variables:
// mode: c++
// end:
#endif
