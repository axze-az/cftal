#include "cftal/vec.h"
#include "cftal/vec_traits.h"

namespace cftal {
    v8f64
    frexp(arg<v8f64>::type d, v8s32* pe)
        __attribute__((flatten));
}

cftal::v8f64
cftal::frexp(arg<v8f64>::type d, v8s32* pe)
{
    using traits_t = math::func_traits<v8f64, v8s32>;
    using func_t = math::func<double, traits_t>;
    return func_t::frexp(d, pe);
}

