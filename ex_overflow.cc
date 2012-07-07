#include "real.h"

namespace math {

	const char* ex_overflow::reason_="numerical overflow";

	ex_overflow::ex_overflow() : exception()
	{
	}

	ex_overflow::~ex_overflow() throw ()
	{
	}

	const char* ex_overflow::what() const throw()
	{
		return reason_;
	}
}

