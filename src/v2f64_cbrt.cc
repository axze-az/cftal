#include "cftal/vec.h"
#include "cftal/vec_traits.h"

cftal::v2f64
cftal::cbrt(arg<v2f64>::type v)
{
    using traits_t=cftal::math::func_traits<v2f64, v2s32>;
    using func_t=cftal::math::impl::nth_root<double, traits_t, 3>;
    return func_t::v<6>(v);
}
