#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v4f64
    ldexp(arg<v4f64>::type d, arg<v4s32>::type e)
        __attribute__((flatten));
}

cftal::v4f64
cftal::ldexp(arg<v4f64>::type d, arg<v4s32>::type e)
{
    using traits_t = math::func_traits<v4f64, v4s32>;
    using func_t = math::func<double, traits_t>;
    return func_t::ldexp(d, e);
}

