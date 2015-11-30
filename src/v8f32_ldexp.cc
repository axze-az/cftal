#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v8f32
    ldrexp(arg<v8f32>::type d, arg<v8s32>::type e)
        __attribute__((flatten));
}

cftal::v8f32
cftal::ldexp(arg<v8f32>::type d, arg<v8s32>::type e)
{
    using traits_t = math::func_traits<v8f32, v8s32>;
    using func_t = math::func<float, traits_t>;
    return func_t::ldexp(d, e);
}

