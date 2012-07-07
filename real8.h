#if !defined (__REAL8_H__)
#define __REAL8_H__ 1

namespace math {
	namespace checked {
		class real8_t {
		public:
			// underlying fp type
			typedef math::real8_t value_type;
			// Destructor
			~real8_t() throw();
			// convert to const math::real8_t&
			const value_type& ref() const throw();
			// convert to math::real8_t
			value_type val() const throw();
			// convert to real4_t
			real4_t to_real4() const;
			// constructors
			real8_t();
			real8_t(int r);
			real8_t(long int r);
			real8_t(unsigned int r);
			real8_t(long unsigned int r);
			real8_t(const real8_t& r);
			real8_t(const math::real8_t& r);
			real8_t(const real4_t& r);
			real8_t(const math::real4_t& r);
			// Assignment operator
			real8_t& operator=(const real8_t& t);
			// unary minus
			real8_t operator-() const;
			// addition
			real8_t& operator+=( const real8_t& t );
			// subtraction
			real8_t& operator-=( const real8_t& t );
			// multiplication
			real8_t& operator*=( const real8_t& t );
			// division
			real8_t& operator/=( const real8_t& t );

			void check_after_op_( ) const;
		private:
			void check_after_op_( ) const 
				__attribute__((noreturn));
			void check_after_op_( int fpclass ) const
				__attribute__((noreturn));
			void check_after_div_( const real8_t& t ) const
				__attribute__((noreturn));
			void check_after_div_( int fpclass,
					       const real8_t& t ) const
				__attribute__((noreturn));
			value_type value_;
		};
		bool operator>(const real8_t& a, const real8_t& b);
		bool operator>=(const real8_t& a, const real8_t& b);
		bool operator==(const real8_t& a, const real8_t& b);
		bool operator<=(const real8_t& a, const real8_t& b);
		bool operator<(const real8_t& a, const real8_t& b);
		bool operator!=(const real8_t& a, const real8_t& b);

		real8_t operator+(const real8_t& a, const real8_t& b);
		real8_t operator-(const real8_t& a, const real8_t& b);
		real8_t operator*(const real8_t& a, const real8_t& b);
		real8_t operator/(const real8_t& a, const real8_t& b);

		real8_t cos( const real8_t& a);
		real8_t sin( const real8_t& a);
		real8_t tan( const real8_t& a);
		real8_t cot( const real8_t& a);
		real8_t exp( const real8_t& a);
		real8_t pow( const real8_t& base, const real8_t& exponent);
		real8_t log( const real8_t& a);
	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
