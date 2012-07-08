#if !defined (__EMUVEC_H__)
#define __EMUVEC_H__ 1

#include <cftal/heap_array.h>
#include <cftal/allocator.h>

namespace emuvec {

	template <typename _T, std::size_t _N>
	class vxy {
		typedef
		cftal::heap_array<_T, _N, cftal::cache_allocator<_T, _N> >
		vec_t;
		vec_t _v;
	public:
		template <typename _T, std::size_t>
		friend class ops;
	};

}
// Local variables:
// mode: c++
// end:
#endif
