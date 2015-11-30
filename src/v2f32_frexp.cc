#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v2f32
    frexp(arg<v2f32>::type d, v2s32* pe)
        __attribute__((flatten));
}

cftal::v2f32
cftal::frexp(arg<v2f32>::type d, v2s32* pe)
{
    using traits_t = math::func_traits<v2f32, v2s32>;
    using func_t = math::func<float, traits_t>;
    return func_t::frexp(d, pe);
}

