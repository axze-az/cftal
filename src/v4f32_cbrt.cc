#include "cftal/vec.h"
#include "cftal/vec_traits.h"

cftal::v4f32
cftal::cbrt(arg<v4f32>::type v)
{
    using traits_t=cftal::math::func_traits<v4f32, v4s32>;
    using func_t=cftal::math::impl::nth_root<float, traits_t, 3>;
    return func_t::v<4>(v);
}
