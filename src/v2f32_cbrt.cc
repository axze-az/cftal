#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v2f32 cbrt(arg<v2f32>::type v)
        __attribute__((flatten));
}

cftal::v2f32
cftal::cbrt(arg<v2f32>::type v)
{
    using traits_t=cftal::math::func_traits<v2f32, v2s32>;
    using func_t=cftal::math::impl::nth_root<float, traits_t, 3>;
    return func_t::v<4>(v);
}
