#if !defined (__REALIOS_H__)
#error "Never include this file directly, use realio.h"
#endif

namespace math {

	template <typename I>
	inline
	std::ostream& operator>>(std::ostream& o, const real<I>& r) {
		o<<r.to_val();
		return o;
	}

	template <typename I>
	inline
	std::istream& operator>>(std::istream& i, real<I>& r)  {
		typename r::value_type t;
		i>>t;
		r=t;
		return i;
	}
}


/*
 * Local variables:
 * mode: c++
 * end:
 */
