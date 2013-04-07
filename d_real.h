#if !defined (__CFTAL_D_REAL_H__)
#define __CFTAL_D_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/emuvec.h>
#include <cftal/x86vec.h>
#include <cmath>
#include <type_traits>

namespace cftal {

	template <class _T>
	_T fms(const _T& a, const _T& b, const _T& c) {
		return fma(a, b, -c);
	}

	template <typename _T>
	struct d_real_traits;

	template <typename _T>
	struct has_fma;

	// fma ?
	template <>
	struct has_fma<double> {
#if defined (FP_FAST_FMA) && (FP_FAST_FMA > 0)
		static constexpr bool fma = true;
#else
		static constexpr bool fma = false;
#endif
	};

	// fma ?
	template <>
	struct has_fma<float> {
#if defined (FP_FAST_FMAF) && (FP_FAST_FMAF > 0)
		static constexpr bool fma = true;
#else
		static constexpr bool fma = false;
#endif
	};

	template <>
	struct d_real_traits<double> : public has_fma<double> {
		constexpr d_real_traits<double>() = default;
		// result of a comparison operator
		typedef bool cmp_result_type;
		// 2^27 + 1
		static constexpr double split() { 
			return 134217729.0;
		}
		// 2^996 = 2^{1023-28+1}
		static constexpr double split_threshold() {
			return 6.69692879491417e+299;
		}
		// 2^-28
		static constexpr double split_scale_down() {
			return 3.7252902984619140625e-09;
		}
		// 2^28
		static constexpr double split_scale_up() {
			return 268435456.0;
		}
		// 
		static bool any(const cmp_result_type& b) { 
			return b; 
		}
		static double sel(const cmp_result_type& s,
				  const double& on_true,
				  const double& on_false) {
			return s ? on_true : on_false;
		}
	};

	template <>
	struct d_real_traits<float> : public has_fma<float> {
		constexpr d_real_traits<float>() = default;
		// result of a comparison operator
		typedef bool cmp_result_type;
		// 2^13 + 1
		static constexpr float split() {
			return 8193.0f;
		}
		// 2^115 = 2^{127-14+1}
		static constexpr float split_threshold() {
			return 4.15383749e+34f;
		}
		// 2^-14
		static constexpr double split_scale_down() {
			return 1.0f/16384.0f;
		}
		// 2^14
		static constexpr float split_scale_up() {
			return 16384.0f;
		}
		// fma ?
		static constexpr bool fma = false;
		// 
		static bool any(const cmp_result_type& b) { 
			return b; 
		}
		static float sel(const cmp_result_type& s,
				 const float& on_true,
				 const float& on_false) {
			return s ? on_true : on_false;
		}
	};


	template <typename _T> 
	class d_real {
		_T _h;
		_T _l;
	public:
		constexpr d_real(const _T& h, const _T& l) : _h(h), _l(l) {}
		constexpr d_real(const _T& h) : _h(h), _l(_T(0)) {}
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
	operator-(const d_real<_T>& a, const d_real<_T>& b);

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

	template <typename _T>
	d_real<_T> abs(const d_real<_T>& r);
	template <typename _T>
	d_real<_T> rint(const d_real<_T>& r);
	template <typename _T>
	d_real<_T> floor(const d_real<_T>& r);
	template <typename _T>
	d_real<_T> ceil(const d_real<_T>& r);
	template <typename _T>
	d_real<_T> trunc(const d_real<_T>& r);

	template <typename _T>
	d_real<_T> powi(const d_real<_T>& r, int e);

	d_real<double> str_to_d_double(const char* p, std::size_t n);
	d_real<double> str_to_d_double(const char* p);
	d_real<float> str_to_d_float(const char* p, std::size_t n);
	d_real<float> str_to_d_float(const char* p);

	d_real<double> operator "" _dd(const char* dd);
	d_real<float> operator "" _df(const char* df);
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
		    (a > d_real_traits<_T>::split_threshold()) || 
		    (a < -d_real_traits<_T>::split_threshold()))) {
		a*=d_real_traits<_T>::split_scale_down();
		temp=d_real_traits<_T>::split()*a;
		hi=temp-(temp-a);
		lo=a-hi;
		hi*=d_real_traits<_T>::split_scale_up();
		lo*=d_real_traits<_T>::split_scale_up();
	} else {
		temp=d_real_traits<_T>::split()*a;
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
cftal::d_real_impl::two_sqr(const _T& a, _T& err)
{
	_T p=a*a;
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
	d_real<_T> r(0);
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

template <typename _T>
inline
cftal::d_real<_T>
cftal::abs(const d_real<_T>& a)
{
	typename d_real_traits<_T>::cmp_result_type a_lt_z=
		a < d_real<_T>(0);
	d_real<_T> an(-a);
	_T hi_res = d_real_traits<_T>::sel( 
		a_lt_z, an.h(), a.h());
	_T lo_res = d_real_traits<_T>::sel(
		a_lt_z, an.l(), a.l());
	return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::rint(const d_real<_T>& a)
{
	_T hi= rint(a.h());
	_T lo;

	// if hi == a.h()
	_T lo_hi_int = rint(a.l());
	_T hi_hi_int = quick_two_sum(hi, lo_hi_int, lo_hi_int);

	// hi != a.h()
	_T lo_hi_no_int(0);
	_T hi_m1 = hi - 1.0;
	_T hi_hi_no_int = d_real_traits<_T>::sel(
		abs(hi - a.h())==_T(0.5) && a.l() < _T(0.0),
		hi_m1, hi);

	typename d_real_traits<_T>::cmp_result_type hi_eq_ah=
		hi == a.h();

	_T hi_res = d_real_traits<_T>::sel(
		hi_eq_ah, hi_hi_int, hi_hi_no_int);
	_T lo_res = d_real_traits<_T>::sel(
		hi_eq_ah, lo_hi_int, lo_hi_int);

	return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::floor(const d_real<_T>& a)
{
	_T hi = floor(a.h());
	_T lo(0);
	typename d_real_traits<_T>::cmp_result_type r=
		hi == a.h();
	_T lo_hi_int = floor(a.l());
	_T hi_hi_int = quick_two_sum(hi, lo_hi_int, lo_hi_int);

	_T hi_res = d_real_traits<_T>::sel(
		r, hi_hi_int, hi);
	_T lo_res = d_real_traits<_T>::sel(
		r, lo_hi_int, lo);
	return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::ceil(const d_real<_T>& a)
{
	_T hi = floor(a.h());
	_T lo(0);
	typename d_real_traits<_T>::cmp_result_type r=
		hi == a.h();
	_T lo_hi_int = ceil(a.l());
	_T hi_hi_int = quick_two_sum(hi, lo_hi_int, lo_hi_int);

	_T hi_res = d_real_traits<_T>::sel(
		r, hi_hi_int, hi);
	_T lo_res = d_real_traits<_T>::sel(
		r, lo_hi_int, lo);
	return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::trunc(const d_real<_T>& a)
{
	typename d_real_traits<_T>::cmp_result_type a_lt_z=
		a < d_real<_T>(0);
	d_real<_T> a_floor(floor(a));
	d_real<_T> a_ceil(ceil(a));
	_T hi_res= d_real_traits<_T>::sel(
		a_lt_z, a_ceil.h(), a_floor.h());
	_T lo_res= d_real_traits<_T>::sel(
		a_lt_z, a_ceil.l(), a_floor.l());
	return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::powi(const d_real<_T>& a, int e)
{
	d_real<_T> r = a;
	d_real<_T> s = 1.0;
	int np = std::abs(e);
	if (np > 1) {
		/* Use binary exponentiation */
		while (np > 0) {
			if ((np & 1) == 1) {
				s *= r;
			}
			np >>= 1;
			if (np > 0)
				r = r * r;
		}
	} else {
		s = r;
	}
	/* Compute the reciprocal if n is negative. */
	if (e < 0)
		s= (_T(1.0) / s);
	return s;
}


// Local variables:
// mode: c++
// end:
#endif
