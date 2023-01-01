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
#if !defined (__CFTAL_TYPES_H__)
#define __CFTAL_TYPES_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/d_int.h>

namespace cftal {

    using uint128_t = duint<uint64_t>;
    using int128_t = dint<int64_t>;

    using uint256_t = duint<uint128_t>;
    using int256_t = dint<int128_t>;

}

// Local variables:
// mode: c++
// end:
#endif
