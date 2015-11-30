#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v2f64
    ldexp(arg<v2f64>::type d, arg<v2s32>::type e)
        __attribute__((flatten));
}

cftal::v2f64
cftal::ldexp(arg<v2f64>::type d, arg<v2s32>::type e)
{
    using traits_t = math::func_traits<v2f64, v2s32>;
    using func_t = math::func<double, traits_t>;
    return func_t::ldexp(d, e);
}

