//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MEM_H__)
#define __CFTAL_MEM_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {

    // mem: memory load/store abstraction
    template <class _T>
    struct mem {
        // load from memory
        static
        _T
        load(const _T* p, std::size_t s = 1) {
            static_cast<void>(s);
            return *p;
        }
        // store to memory
        static
        void
        store(_T* p, const _T& v) {
            *p = v;
        }
    };

}


// Local variables:
// mode: c++
// end:
#endif
