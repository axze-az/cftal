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
#if !defined (__CFTAL_D_REAL_TRAITS_H__)
#define __CFTAL_D_REAL_TRAITS_H__ 1

#include <cftal/config.h>

namespace cftal {

    // traits structure for d_real class
    template <typename _T>
    struct d_real_traits {};

    // helper call defining the existance of fused multiply and add
    template <typename _T>
    struct has_fma {
        static constexpr bool fma=false;
    };

}

// Local variables:
// mode: c++
// end:
#endif
