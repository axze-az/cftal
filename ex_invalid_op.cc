#include "real.h"

namespace math {

	const char* ex_invalid_op::reason_="invalid floating point operation";

	ex_invalid_op::ex_invalid_op() : exception()
	{
	}

	ex_invalid_op::~ex_invalid_op() throw ()
	{
	}

	const char* ex_invalid_op::what() const throw()
	{
		return reason_;
	}
}

