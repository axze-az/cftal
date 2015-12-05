#include <cftal/vec.h>
#include <cftal/d_int.h>
#include <cftal/d_real.h>
#include <cftal/mul_div.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/vec_traits.h>
#include <cftal/impl/vreg.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>


namespace cftal {
}

cftal::vec<float, 2>
do_mul_add(cftal::vec<float, 2> a,
           cftal::vec<float, 2> b, cftal::vec<float, 2> c)
{
    return (a * b + c) + (a + b * c);
}

cftal::vec<int32_t, 2>
do_mul_add(cftal::vec<int32_t, 2> a,
           cftal::vec<int32_t, 2> b, cftal::vec<int32_t, 2> c)
{
    return (a * b + c) + (a + b * c);
}

cftal::vec<int32_t, 2>
do_add(cftal::vec<int32_t, 2> a, cftal::vec<int32_t, 2> b)
{
    return a + b;
}

int main(int argc, char** argv)
{
    cftal::divisor<cftal::v4s32, int32_t> v4rr(3);
    cftal::v4s32 v4t=-7046431;
    cftal::v4s32 v4q=v4t/v4rr;
    std::cout << v4q << std::endl;

    using v1s32 = cftal::vec<int32_t, 1>;

    cftal::divisor<v1s32, int32_t> v1rr(3);
    v1s32 v1t=-7046431;
    v1s32 v1q=v1t/v1rr;
    std::cout << v1q << std::endl;


    cftal::divisor<cftal::v2s32, int32_t> rr(3);
    cftal::v2s32 t=-7046431;
    cftal::v2s32 q=t/rr;
    std::cout << q << std::endl;

    cftal::divisor<int32_t, int32_t> srr(3);
    int32_t st=-7046431;
    int32_t sq=st/srr;
    std::cout << sq << std::endl;
    return 0;
}
