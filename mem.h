#if !defined (__CFTAL_MEM_H__)
#define __CFTAL_MEM_H__ 1

#include <cftal/config.h>

namespace cftal {
    
    template <class _T>
    struct mem {
        static
        _T read_from(const _T* p) {
            return *p;
        }
        static
        void write_to(_T* p, const _T& v) {
            *p = v;
        }
    };
    
}
        

// Local variables:
// mode: c++
// end:
#endif
