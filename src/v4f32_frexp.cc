#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v4f32
    frexp(arg<v4f32>::type d, v4s32* pe)
        __attribute__((flatten));
}

cftal::v4f32
cftal::frexp(arg<v4f32>::type d, v4s32* pe)
{
    using traits_t = math::func_traits<v4f32, v4s32>;
    using func_t = math::func<float, traits_t>;
    return func_t::frexp(d, pe);
}

