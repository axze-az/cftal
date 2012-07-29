#include <bitops.h>
#include <divisor.h>

namespace cftal {

	uint32_t sqrt(uint32_t x);
	uint64_t sqrt(uint64_t x);
}

namespace cftal {

	namespace impl {

		template <typename _U>
		struct sqrt {
			enum { N = sizeof(_U)*8 };
			static _U v(const _U& x);
		};
	}
}

template <typename _U>
_U cftal::impl::sqrt<_U>::v(const _U& x) 
{
	if (x<=_U(1))
		return x;
	unsigned s = N - (lzcnt(x-1)>>1);
	// g0 = 2^s
	_U g0 = _U(1)<<s;
	// g1 = (g0 + x/g0)/2
	_U g1 = (g0 + (x>>s)) >>1;
	while (g1 < g0) {
		g0 = g1;
		g1 = (g0 + (x/g0)) >>1;
	}
	return g0;
}

cftal::uint32_t
cftal::sqrt(uint32_t x)
{
	return impl::sqrt<uint32_t>::v(x);
}

cftal::uint64_t
cftal::sqrt(uint64_t x)
{
	return impl::sqrt<uint64_t>::v(x);
}
