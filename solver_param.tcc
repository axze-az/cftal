#include <ode.h>


namespace ode {

	template <typename C>
	solver_param<C>::solver_param( value_type x0, 
				       value_type xe, 
				       value_type h0,
				       const C& abserr, 
				       const C& relerr)
		: x0_(x0), xe_(xe), h0_(h0),
		  abserr_(abserr), relerr_(relerr)
	{
	}

	template <typename C>
	solver_param<C>::~solver_param()
	{
	}
	
	template <typename C>
	const typename solver_param<C>::value_type&
	solver_param<C>::x0() const
	{
		return x0_;
	}

	template <typename C>
	const typename solver_param<C>::value_type&
	solver_param<C>::xe() const
	{
		return xe_;
	}

	template <typename C>
	const typename solver_param<C>::value_type&
	solver_param<C>::h0() const
	{
		return h0_;
	}
 
	template <typename C>
	const C&
	solver_param<C>::abserr() const
	{
		return abserr_;
	}

	template <typename C>
	const C&
	solver_param<C>::relerr() const
	{
		return relerr_;
	}
}
/*
 * Local variables:
 * mode: c++
 * end:
 */
