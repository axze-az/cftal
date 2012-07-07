#if !defined (__REAL16_H__)
#define __REAL16_H__ 1

namespace math {
	namespace checked {
		class real16_t {
		public:
			// underlying type
			typedef math::real16_t value_type;
			// Destructor
			~real16_t() throw();
			// convert to const math::real16_t&
			const value_type& ref() const throw() ;
			// convert to math::real16_t
			value_type val() const throw();
			// convert to const math::real8_t
			real8_t to_real8() const;
			// convert to const math::real4_t
			real4_t to_real4() const;
			// constructors
			real16_t();
			real16_t(int r);
			real16_t(long int r);
			real16_t(unsigned int r);
			real16_t(long unsigned int r);
			real16_t(const real16_t& r);
			real16_t(const math::real16_t& r);
			real16_t(const real8_t& r);
			real16_t(const math::real8_t& r);
			real16_t(const real4_t& r);
			real16_t(const math::real4_t& r);
			// Assignment operator
			real16_t& operator=(const real16_t& t);
			// unary minus
			real16_t operator-() const;
			// addition
			real16_t& operator+=( const real16_t& t );
			// subtraction
			real16_t& operator-=( const real16_t& t );
			// multiplication
			real16_t& operator*=( const real16_t& t );
			// division
			real16_t& operator/=( const real16_t& t );
		private:
			void check_after_op_( ) const;
			void check_after_op_( int fpclass) const;
			void check_after_div_( const real16_t& t ) const;
			void check_after_div_( int fpclass, 
					       const real16_t& t) const;
			value_type value_;
		};
		bool operator>(const real16_t& a, const real16_t& b);
		bool operator>=(const real16_t& a, const real16_t& b);
		bool operator==(const real16_t& a, const real16_t& b);
		bool operator<=(const real16_t& a, const real16_t& b);
		bool operator<(const real16_t& a, const real16_t& b);
		bool operator!=(const real16_t& a, const real16_t& b);

		real16_t operator+(const real16_t& a, const real16_t& b);
		real16_t operator-(const real16_t& a, const real16_t& b);
		real16_t operator*(const real16_t& a, const real16_t& b);
		real16_t operator/(const real16_t& a, const real16_t& b);
	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
