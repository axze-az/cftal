
namespace math {
	namespace checked {
		inline 
		real4_t::value_type real4_t::val() const throw() {
			return value_;
		}

		inline
		const real4_t::value_type& real4_t::ref() const throw () {
			return value_;
		}

		inline
		real4_t::~real4_t() throw() {}

		inline 
		real4_t::real4_t() : value_(0.0f) {}

		inline
		real4_t::real4_t(int r) : value_(r) {}

		inline
		real4_t::real4_t(long int r) : value_(r) {}

		inline
		real4_t::real4_t(unsigned int r) : value_(r) {}

		inline
		real4_t::real4_t( const real4_t& r) : value_(r.value_) {}

		inline
		real4_t::real4_t( const math::real4_t& r) : value_(r) {}

		inline
		real4_t& real4_t::operator=( const real4_t& r ) {
			if ( &r != this )
				value_ = r.value_;
			return *this;
		}
		
		inline
		real4_t real4_t::operator-() const {
			return real4_t(-value_);
		}

		inline
		real4_t& real4_t::operator+=( const real4_t& r) {
			value_ += r.value_;
			if ( !isfinite( value_))
				check_after_op_( );
			return *this;
		}
		
		inline
		real4_t& real4_t::operator-=( const real4_t& r) {
			value_ -= r.value_;
			if ( !isfinite( value_ ))
				check_after_op_( );
			return *this;
		}
		inline
		real4_t& real4_t::operator*=( const real4_t& r) {
			value_ *= r.value_;
			if ( !isfinite( value_))
				check_after_op_( );
			return *this;
		}

		inline
		real4_t& real4_t::operator/=( const real4_t& r) {
			value_ /= r.value_;
			if ( !isfinite( value_))
				check_after_div_( r );
			return *this;
		}

		inline
		bool operator>( const real4_t& a, const real4_t& b) {
			return a.val() > b.val();
		}

		inline
		bool operator>=( const real4_t& a, const real4_t& b) {
			return a.val() >= b.val();
		}

		inline
		bool operator==( const real4_t& a, const real4_t& b) {
			return a.val() == b.val();
		}

		inline
		bool operator<=( const real4_t& a, const real4_t& b) {
			return a.val() <= b.val();
		}

		inline
		bool operator<( const real4_t& a, const real4_t& b) {
			return a.val() < b.val();
		}

		inline
		bool operator!=( const real4_t& a, const real4_t& b) {
			return a.val() != b.val();
		}

		inline
		real4_t operator+( const real4_t& a, const real4_t& b) {
			return (real4_t(a)+=b);
		}

		inline
		real4_t operator-( const real4_t& a, const real4_t& b) {
			return (real4_t(a)-=b);
		}

		inline
		real4_t operator*( const real4_t& a, const real4_t& b) {
			return (real4_t(a)*=b);
		}
		
		inline
		real4_t operator/( const real4_t& a, const real4_t& b) {
			return (real4_t(a)/=b);
		}
	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
