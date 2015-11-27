#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v8f32 cbrt(arg<v8f32>::type v)
        __attribute__((flatten));
}

cftal::v8f32
cftal::cbrt(arg<v8f32>::type v)
{
    using traits_t=cftal::math::func_traits<v8f32, v8s32>;
    using func_t=cftal::math::impl::nth_root<float, traits_t, 3>;
    return func_t::v<4>(v);
}
