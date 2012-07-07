#include "fpvec.h"

vec::vec2d testf( const vec::vec2d& a, 
		  const vec::vec2d& b)
{

	vec::vec2d res(
		(a+b+ vec::vec2d(1,1)) *vec::vec2d(10,10) / vec::vec2d(2,2) );
	return res;
}

void daxpy( vec::vec2d* res, const vec::vec2d* x, const vec::vec2d* y,
	    double a, int n)
{
	const vec::vec2d _a(a,a);
	for ( int i = 0; i< n; ++i) {
		res[i] = _a * x[i] + y[i];
	}
}
