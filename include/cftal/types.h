//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
