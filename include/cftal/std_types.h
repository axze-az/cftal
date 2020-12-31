//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_STD_TYPES_H__)
#define __CFTAL_STD_TYPES_H__

#include <cftal/config.h>
#include <cstdint>

namespace cftal {

    using std::uint8_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::uint64_t;

    using std::int8_t;
    using std::int16_t;
    using std::int32_t;
    using std::int64_t;

    using f32_t = float;
    using f64_t = double;

    using std::size_t;
    using std::ptrdiff_t;
    using ssize_t = ptrdiff_t;
}

// Local variables:
// mode: c++
// end:
#endif
