#if !defined (__OPERATORS_H__)
#define __OPERATORS_H__ 1

#include <cftal/bitops.h>
#if defined (__i386__) || defined (__x86_64__)
#include <cftal/x86vec.h>
#else
#include <cftal/emuvec.h>
#endif
// classes, functions, templates, algorithms library
namespace cftal {
	
        // a = b
        // a = rvalue
        // a += b
        // a -= b
        // a *= b
        // a /= b
        // a %= b
        // a &= b
        // a |= b
        // a ^= b
        // a <<= b
        // a >>= b

	// ++a
	// --a
	// a++
	// a--


	// +a
	// -a
	// a + b
	// a - b
	// a * b
	// a / b
	// a % b
	// ~a
	// a & b
	// a | b
	// a ^ b
	// a << b
	// a >> b

	// !a
	// a && b
	// a || b
	
	// a == b
	// a != b
	// a < b
	// a > b
	// a <= b
	// a >= b
	
	// a[b]
	// *a
	// &a
	// a->b
	// a.b
	// a->*b
	// a.*b
	
	// a(...)
	// a, b
	// (type) a
	// ? :
}
// Local variables:
// mode: c++
// end:
#endif
