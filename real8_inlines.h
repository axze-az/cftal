#include <cmath>

namespace math {
	namespace checked {
		inline 
		real8_t::value_type real8_t::val() const throw () {
			return value_;
		}

		inline
		const real8_t::value_type& real8_t::ref() const throw () {
			return value_;
		}

		inline
		real8_t::~real8_t() throw() {}

		inline 
		real8_t::real8_t() : value_(0.0) {}

		inline
		real8_t::real8_t(int r) : value_(r) {}

		inline
		real8_t::real8_t(long int r) : value_(r) {}

		inline
		real8_t::real8_t(unsigned int r) : value_(r) {}

		inline
		real8_t::real8_t( const real8_t& r) : value_(r.value_) {}

		inline
		real8_t::real8_t( const math::real8_t& r) : value_(r) {}

		inline 
		real8_t::real8_t( const real4_t& r) : value_(r.val()) {}

		inline
		real8_t::real8_t( const math::real4_t& r) : value_(r) {}

		inline
		real8_t& real8_t::operator=( const real8_t& r ) {
			if ( &r != this )
				value_ = r.value_;
			return *this;
		}
		
		inline
		real8_t real8_t::operator-() const {
			return real8_t(-value_);
		}

		inline
		real8_t& real8_t::operator+=( const real8_t& r) {
			value_ += r.value_;
			if ( ! isfinite( value_ ))
				check_after_op_( );
			return *this;
		}
		
		inline
		real8_t& real8_t::operator-=( const real8_t& r) {
			value_ -= r.value_;
			if ( ! isfinite( value_ ))
				check_after_op_( );
			return *this;
		}

		inline
		real8_t& real8_t::operator*=( const real8_t& r) {
			value_ *= r.value_;
			if ( ! isfinite( value_ ))
				check_after_op_( );
			return *this;
		}

		inline
		real8_t& real8_t::operator/=( const real8_t& r) {
			value_ /= r.value_;
			if ( ! isfinite( value_ ))
				check_after_div_( r );
			return *this;
		}

		inline
		bool operator>( const real8_t& a, const real8_t& b) {
			return a.val() > b.val();
		}

		inline
		bool operator>=( const real8_t& a, const real8_t& b) {
			return a.val() >= b.val();
		}

		inline
		bool operator==( const real8_t& a, const real8_t& b) {
			return a.val() == b.val();
		}

		inline
		bool operator<=( const real8_t& a, const real8_t& b) {
			return a.val() <= b.val();
		}

		inline
		bool operator<( const real8_t& a, const real8_t& b) {
			return a.val() < b.val();
		}

		inline
		bool operator!=( const real8_t& a, const real8_t& b) {
			return a.val() != b.val();
		}

		inline
		real8_t operator+( const real8_t& a, const real8_t& b) {
			return (real8_t(a)+=b);
		}

		inline
		real8_t operator-( const real8_t& a, const real8_t& b) {
			return (real8_t(a)-=b);
		}

		inline
		real8_t operator*( const real8_t& a, const real8_t& b) {
			return (real8_t(a)*=b);
		}
		
		inline
		real8_t operator/( const real8_t& a, const real8_t& b) {
			return (real8_t(a)/=b);
		}
		
		inline
		real8_t sin( const real8_t& a) {
			real8_t::value_type ret( sin(a.value()));
			real8_t rc(ret);
			if ( !isfinite(ret)
			     rc.check_after_op_ ();
		}

	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
