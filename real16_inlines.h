
namespace math {
	namespace checked {

		inline 
		real16_t::value_type real16_t::val() const throw() {
			return value_;
		}

		inline
		const real16_t::value_type& real16_t::ref() const throw() {
			return value_;
		}

		inline
		real16_t::~real16_t() throw() {}

		inline 
		real16_t::real16_t() : value_(0.0L) {}

		inline
		real16_t::real16_t(int r) : value_(r) {}

		inline
		real16_t::real16_t(long int r) : value_(r) {}

		inline
		real16_t::real16_t(unsigned int r) : value_(r) {}

		inline 
		real16_t::real16_t( const real16_t& r) : value_(r.value_) {}

		inline
		real16_t::real16_t( const math::real16_t& r) : value_(r) {}

		inline
		real16_t::real16_t( const real8_t& r) : value_(r.val()) {}

		inline
		real16_t::real16_t( const math::real8_t& r) : value_(r) {}

		inline 
		real16_t::real16_t( const real4_t& r) : value_(r.val()) {}

		inline
		real16_t::real16_t( const math::real4_t& r) : value_(r) {}

		inline
		real16_t& real16_t::operator=( const real16_t& r ) {
			if ( &r != this )
				value_ = r.value_;
			return *this;
		}
		
		inline
		real16_t real16_t::operator-() const {
			return real16_t(-value_);
		}

		inline
		real16_t& real16_t::operator+=( const real16_t& r) {
			value_ += r.val();
			if ( !isfinite( value_))
				check_after_op_(  );
			return *this;
		}
		
		inline
		real16_t& real16_t::operator-=( const real16_t& r) {
			value_ -= r.val();
			if ( !isfinite( value_))
				check_after_op_(  );
			return *this;
		}

		inline
		real16_t& real16_t::operator*=( const real16_t& r) {
			value_ *= r.val();
			if ( !isfinite( value_))
				check_after_op_(  );
			return *this;
		}

		inline
		real16_t& real16_t::operator/=( const real16_t& r) {
			value_ /= r.val();
			if ( !isfinite( value_))
				check_after_div_( r );
			return *this;
		}

		inline
		bool operator>( const real16_t& a, const real16_t& b) {
			return a.val() > b.val();
		}

		inline
		bool operator>=( const real16_t& a, const real16_t& b) {
			return a.val() >= b.val();
		}

		inline
		bool operator==( const real16_t& a, const real16_t& b) {
			return a.val() == b.val();
		}

		inline
		bool operator<=( const real16_t& a, const real16_t& b) {
			return a.val() <= b.val();
		}

		inline
		bool operator<( const real16_t& a, const real16_t& b) {
			return a.val() < b.val();
		}

		inline
		bool operator!=( const real16_t& a, const real16_t& b) {
			return a.val() != b.val();
		}

		inline
		real16_t operator+( const real16_t& a, const real16_t& b) {
			return (real16_t(a)+=b);
		}

		inline
		real16_t operator-( const real16_t& a, const real16_t& b) {
			return (real16_t(a)-=b);
		}

		inline
		real16_t operator*( const real16_t& a, const real16_t& b) {
			return (real16_t(a)*=b);
		}

		inline
		real16_t operator/( const real16_t& a, const real16_t& b) {
			return (real16_t(a)/=b);
		}
	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
