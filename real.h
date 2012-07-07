#if !defined (__REAL_H__)
#define __REAL_H__ 1

#include <exception>
#include <cmath>

namespace math {

	class exception : public std::exception {
	public:
		virtual ~exception() throw()=0;
		virtual const char* what() const throw () =0;
	protected:
		exception();
	};

	class ex_div_by_zero : public exception {
	public:
		ex_div_by_zero();
		virtual ~ex_div_by_zero() throw();
		virtual const char* what() const throw ();
	private:
		static const char* reason_;
	};

	class ex_overflow : public exception {
	public:
		ex_overflow();
		virtual ~ex_overflow() throw();
		virtual const char* what() const throw();
	private:
		static const char* reason_;
	};

	class ex_invalid_op : public exception {
	public:
		ex_invalid_op();
		virtual ~ex_invalid_op() throw();
		virtual const char* what() const throw();
	private:
		static const char* reason_;
	};

	typedef float real4_t;
	typedef double real8_t;
	typedef long double real16_t;

	/* checked contains the checked real types */
	namespace checked {
		class real4_t;
		class real8_t;
		class real16_t;
	}
}

#include <real4.h>
#include <real8.h>
#include <real16.h>

#if !defined (__NO_REAL4_INLINES__)
#include <real4_inlines.h>
#endif
#if !defined (__NO_REAL8_INLINES__)
#include <real8_inlines.h>
#endif
#if !defined (__NO_REAL16_INLINES__)
#include <real16_inlines.h>
#endif

#include <realops.h>



/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
