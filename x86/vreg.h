#if !defined (__CFTAL_X86_VREG_H__)
#define __CFTAL_X86_VREG_H__ 1

#include <cftal/config.h>
#include <cftal/impl/vreg.h>

namespace cftal {

    namespace x86 {

        template <typename _T>
        struct arg { using type = _T; };
		using ::cftal::impl::vreg;
    }
}

// Local variables:
// mode: c++
// end:
#endif
