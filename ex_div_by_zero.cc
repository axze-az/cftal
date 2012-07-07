#include "real.h"

namespace math {

	const char* ex_div_by_zero::reason_="division by zero";

	ex_div_by_zero::ex_div_by_zero() : exception()
	{
	}

	ex_div_by_zero::~ex_div_by_zero() throw ()
	{
	}

	const char* ex_div_by_zero::what() const throw()
	{
		return reason_;
	}
}

