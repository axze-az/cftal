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
