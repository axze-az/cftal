#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v8f64
    ldexp(arg<v8f64>::type d, arg<v8s32>::type e)
        __attribute__((flatten));
}

cftal::v8f64
cftal::ldexp(arg<v8f64>::type d, arg<v8s32>::type e)
{
    using traits_t = math::func_traits<v8f64, v8s32>;
    using func_t = math::func<double, traits_t>;
    return func_t::ldexp(d, e);
}

