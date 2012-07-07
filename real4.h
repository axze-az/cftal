#if !defined (__REAL4_H__)
#define __REAL4_H__ 1

namespace math {
	namespace checked {
		class real4_t {
		public:
			// underlying type
			typedef math::real4_t value_type;
			// Destructor
			~real4_t() throw();
			// convert to const math::real4_t&
			const value_type& ref() const throw() ;
			// convert to math::real4_t
			value_type val() const throw() ;
			// constructors
			real4_t();
			real4_t(int r);
			real4_t(long int r);
			real4_t(unsigned int r);
			real4_t(long unsigned int r);
			real4_t(const real4_t& r);
			real4_t(const math::real4_t& r);
			// Assignment operator
			real4_t& operator=(const real4_t& t);
			// unary minus
			real4_t operator-() const;
			// addition
			real4_t& operator+=( const real4_t& t );
			// subtraction
			real4_t& operator-=( const real4_t& t );
			// multiplication
			real4_t& operator*=( const real4_t& t );
			// division
			real4_t& operator/=( const real4_t& t );
		private:
			void check_after_op_( ) const;
			void check_after_op_( int fpclass ) const;
			void check_after_div_( const real4_t& t ) const;
			void check_after_div_( int fpclass, 
					       const real4_t& t ) const;
			value_type value_;
		};
		bool operator>(const real4_t& a, const real4_t& b);
		bool operator>=(const real4_t& a, const real4_t& b);
		bool operator==(const real4_t& a, const real4_t& b);
		bool operator<=(const real4_t& a, const real4_t& b);
		bool operator<(const real4_t& a, const real4_t& b);
		bool operator!=(const real4_t& a, const real4_t& b);

		real4_t operator+(const real4_t& a, const real4_t& b);
		real4_t operator-(const real4_t& a, const real4_t& b);
		real4_t operator*(const real4_t& a, const real4_t& b);
		real4_t operator/(const real4_t& a, const real4_t& b);
	}
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
