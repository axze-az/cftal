#if !defined (__CFTAL_MEM_H__)
#define __CFTAL_MEM_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {
    
    template <class _T>
    struct mem {
        static
        _T load(const _T* p, std::size_t s = 1) {
            return *p;
        }
        static
        void store(_T* p, const _T& v) {
            *p = v;
        }
    };
    
}
        

// Local variables:
// mode: c++
// end:
#endif
