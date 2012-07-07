#if !defined (__REAL_H__)
#error "Never include this file directly, use real.h"
#endif

#include <math.h>

namespace math {

	template <>
 	inline
        float pow<> ( const float& a, const float&  b) {
		return ::powf(a,b);
	}
	
	template <>
	inline
        double pow<> ( const double&  a, const double&  b) {
		return ::pow(a,b);
	}

	template <>
	inline
        long double pow<> ( const long double& a, const long double&  b) {
		return ::powl(a,b);
	}

	template <>
	inline
        float exp<> ( const float& a ) {
		return ::expf(a);
	}
	
	template <>
	inline
        double exp<> ( const double& a) {
		return ::exp(a);
	}

	template <>
	inline
        long double exp<> ( const long double& a ) {
		return ::expl(a);
	}

	template <>
	inline 
	bool infinity<>( const float& a) {
		return ::isinff(a);
	}

	template <>
	inline 
	bool infinity<>( const double& a) {
		return isinf(a);
	}

	template <>
	inline 
	bool infinity<>( const long double& a) {
		return ::isinfl(a);
	}

	template <>
	inline 
	bool nonumber<>( const float& a) {
		return isnanf(a);
	}

	template <>
	inline 
	bool nonumber<>( const double& a) {
		return isnan(a);
	}

	template <>
	inline 
	bool nonumber<>( const long double& a) {
		return isnanl(a);
	}

	template <typename I, bool checked>
	void real<I, checked>::check() const
	{
		if ( infinity( val_ ) )
			throw ex_overflow();
		if ( nonumber( val_ ) )
			throw ex_invalid_op();
	}

	template <typename I, bool checked>
	inline
	real<I,checked>::real() : val_(I(0)) {
	}
	
	template <typename I, bool checked>
	inline
	real<I,checked>::real(const float& r) : val_(r) {
	}

	template <typename I, bool checked>
	inline
	real<I,checked>::real(const double& r) : val_(r) {
	}

	template <typename I, bool checked>
	inline
	real<I,checked>::real(const long double& r) : val_(r) {
	}

	template <typename I, bool checked>
	inline
	I real<I, checked>::to_val() const {
		return val_;
	}

	template <typename I, bool checked>
	inline
	const I&  real<I, checked>::to_ref() const {
		return val_;
	}

	template <typename I,  bool checked>
	template <bool Other> 
	inline
	real<I,checked>::real(const real<I,Other> & r) : val_(r.to_ref()) {
	}

	template <typename I, bool checked>
	inline
	real<I,checked>::~real() throw () {
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	real<I,checked>& 
	real<I,checked>::operator=(const real<I,Other>& r) {
		if ( &r != this )
			val_= r.to_ref();
		return *this;
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline 
	real<I, checked>& 
	real<I, checked>::operator+=(const real<I,Other>& r) {
		val_ += r.to_ref();
		if ( checked == true )
			check();
		return *this;
	}
	
	template <typename I, bool checked>
	template <bool Other> 
	inline 
	real<I, checked>& 
	real<I, checked>::operator-=(const real<I,Other>& r) {
		val_ -= r.to_ref();
		if ( checked == true )
			check();
		return *this;
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline 
	real<I, checked>& 
	real<I, checked>::operator*=(const real<I,Other>& r) {
		val_ *= r.to_ref();
		if ( checked == true )
			check();
		return *this;
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline 
	real<I, checked>& 
	real<I, checked>::operator/=(const real<I,Other>& r) {
		if ( checked == true ) {
			const value_type zero(0);
			if ( r.to_ref() == zero  )
				throw ex_div_by_zero();
		}
		val_ /= r.to_ref();
		if ( checked == true )
			check();
		return *this;
	}

	template <typename I, bool checked>
	inline
	real<I, checked> real<I, checked>::operator+() const {
		return real(*this);
	}
	
	template <typename I, bool checked>
	inline
	real<I, checked> real<I, checked>::operator-() const {
		return real(-val_);
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	bool real<I, checked>::operator<(const real<I,Other>& r) const {
		return val_ < r.to_ref();
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	bool real<I, checked>::operator<=(const real<I,Other>& r) const {
		return val_ <= r.to_ref();
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	bool real<I, checked>::operator==(const real<I,Other>& r) const {
		return val_ == r.to_ref();
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	bool real<I, checked>::operator>=(const real<I,Other>& r) const {
		return val_ >= r.to_ref();
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	bool real<I, checked>::operator>(const real<I,Other>& r) const {
		return val_ > r.to_ref();
	}

	template <typename I, bool checked>
	template <bool Other> 
	inline
	bool real<I, checked>::operator!=(const real<I,Other>& r) const {
		return val_ != r.to_ref();
	}

	template <typename I, bool A, bool B, bool C>
	inline
	real<I, A> operator+( const real<I, B>& a, 
			      const real<I, C>& b) {
		return (real<I, A>(a)+=b);
	}

	template <typename I, bool A, bool B, bool C>
	inline
	real<I, A> operator-( const real<I, B>& a, 
			      const real<I, C>& b) {
		return (real<I, A>(a)-=b);
	}

	template <typename I, bool A, bool B, bool C>
	inline
	real<I, A> operator*( const real<I, B>& a, 
			      const real<I, C>& b) {
		return (real<I, A>(a)*=b);
	}

	template <typename I, bool A, bool B, bool C>
	inline
	real<I, A> operator/( const real<I, B>& a, 
			      const real<I, C>& b) {
		return (real<I, A>(a)/=b);
	}

	template <typename I, bool A, bool B, bool C>
	inline
	real<I, A> pow( const real<I, B>& a, 
			const real<I, C>& b) {
		real<I, A> ret( pow(a.to_ref(), b.to_ref()) );
		if ( A == true )
			ret.check();
		return ret;
	}

	template <typename I, bool A, bool B>
	inline
	real<I, A> exp( const real<I, B>& a) {
		real<I, A> ret(exp(a.to_ref()));
		if ( A == true )
			ret.check();
	}

	template <typename I, bool checked>
	inline
	bool infinity( const real<I, checked>& a) {
		return infinity( a.to_val());
	}

	template <typename I, bool checked>
	inline
	bool nonumber( const real<I, checked>& a) {
		return isnan( a.to_val());
	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
