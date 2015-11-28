#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v8f32
    frexp(arg<v8f32>::type d, v8s32* pe)
        __attribute__((flatten));
}

cftal::v8f32
cftal::frexp(arg<v8f32>::type d, v8s32* pe)
{
    using traits_t = math::func_traits<v8f32, v8s32>;
    using func_t = math::func<float, traits_t>;
    return func_t::frexp(d, pe);
}

