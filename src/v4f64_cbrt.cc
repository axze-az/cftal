#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v4f64 cbrt(arg<v4f64>::type v)
        __attribute__((flatten));
}

cftal::v4f64
cftal::cbrt(arg<v4f64>::type v)
{
    using traits_t=cftal::math::func_traits<v4f64, v4s32>;
    using func_t=cftal::math::impl::nth_root<double, traits_t, 3>;
    return func_t::v<5>(v);
}
