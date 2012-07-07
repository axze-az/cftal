#include <real.h>

#if !defined (X)
#define X double
#endif

/* Instantiate the templates: */
namespace math {
	template class real<X,true>;
	template class real<X,false>;

#define instantiate_op(Y,OP)					\
	template						\
	real< X, Y> operator OP ( const real<X,true>& a,	\
			         const real<X,true>& b);	\
	template						\
	real< X, Y> operator OP (const real<X,true>& a,		\
			       const real<X,false>& b);		\
	template						\
	real< X, Y> operator OP (const real<X,false>& a,	\
			         const real<X,true>& b);	\
	template						\
	real< X, Y> operator OP (const real<X,false>& a,	\
		  	       const real<X,false>& b)

	instantiate_op(true, + );
	instantiate_op(true, - );
	instantiate_op(true, * );
	instantiate_op(true, / );
	instantiate_op(false, + );
	instantiate_op(false, - );
	instantiate_op(false, * );
	instantiate_op(false, / );

// 	template 
// 	real<X> pow(const real<X>& a,
// 		    const real<X>& b);

// 	template 
// 	real<X> exp(const real<X>& a);

	template 
	bool infinity(const real<X,true>& a);
	template 
	bool infinity(const real<X,false>& a);

	template 
	bool nonumber(const real<X,true>& a);
	template 
	bool nonumber(const real<X,false>& a);
}
