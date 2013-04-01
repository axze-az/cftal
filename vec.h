#if !defined (__CFTAL_VEC_H__)
#define __CFTAL_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/emuvec.h>
#include <cftal/x86vec.h>

namespace cftal {
#if defined (__amd64__) || defined (__i386__)
	namespace vec=x86vec;
#else
	namespace vec=emuvec;
#endif
}

// Local variables:
// mode: c++
// end:
#endif
