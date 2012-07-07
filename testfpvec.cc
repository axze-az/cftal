#include <iostream>
#include "xmm_v2d.h"


xmm::v2d testf( const xmm::v2d& a, 
		  const xmm::v2d& b)
{

	xmm::v2d res(
		(a+b+ xmm::v2d(1,1)) *xmm::v2d(10,10) / xmm::v2d(2,2) );
	return res;
}

void daxpy( xmm::v2d* res, const xmm::v2d* x, const xmm::v2d* y,
	    double a, int n)
{
	const xmm::v2d _a(a,a);
	for ( int i = 0; i< n; ++i) {
		res[i] = _a * x[i] + y[i];
	}
}


int main()
{
	xmm::v2d res(1.0,2.0);
	xmm::v2d t1(1.0,2.0);
	res *= t1 * t1;
	daxpy(&res,&res,&t1,2.0,1);
	std::cout << res << std::endl;
	xmm::v2d res2( -res );
	std::cout << res2 << std::endl;
	xmm::v2d res3( -res2 );
	std::cout << res3 << std::endl;

	xmm::v2d a0(-1,0);
	std::cout << "a0: " << a0 << std::endl;
	xmm::v2d a1( fabs(a0) );
	std::cout << "a1: " << a1 << std::endl;
	xmm::v2d a2( -(a0-1) );
	std::cout << "a2: " << a2 << std::endl;

	xmm::v2d s0(1,2);
	xmm::v2d s1(sqrt(s0));
	xmm::v2d s2(sqrt(s1));
	std::cout << "s0: " << s0 << std::endl
		  << "s1: " << s1 << std::endl
		  << "s2: " << s2 << std::endl;

	return 0;
}
