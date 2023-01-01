//
// Copyright (C) 2010-2023 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
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
