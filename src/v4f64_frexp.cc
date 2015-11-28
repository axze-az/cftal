#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v4f64
    frexp(arg<v2f64>::type d, v4s32* pe)
        __attribute__((flatten));
}


cftal::v4f64
cftal::frexp(arg<v4f64>::type d, v4s32* pe)
{
    using traits_t = math::func_traits<v4f64, v4s32>;
    using func_t = math::func<double, traits_t>;
    return func_t::frexp(d, pe);
}

