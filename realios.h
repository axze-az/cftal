#if !defined (__REALIOS_H__)
#define __REALIO_HS__ 1

#include <real.h>
#include <iosfwd>

namespace math {
	template <typename I>
	std::ostream& operator>>(std::ostream& o, const real<I>& r);

	template <typename I>
	std::istream& operator>>(std::istream& i, real<I>& r);
}

#include <realios.tcc>

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
