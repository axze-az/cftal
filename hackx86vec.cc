#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/d_real.h>
#include <cftal/vec_traits.h>


int main(int argc, char** argv)
{
    using namespace cftal;
    std::cout << std::hex;
    double t=0x1p51-1.0;
    std::cout << bytes8(t)._u64 << std::endl;
    double t1=t+0x1p52+0x1p51;
    std::cout << bytes8(t1)._u64 << std::endl;
    std::cout << bytes8(t1)._u32[0] << std::endl;
    double t2=-t+0x1p52+0x1p51;
    std::cout << bytes8(t2)._u64 << std::endl;
    std::cout << bytes8(t2)._u32[0] << std::endl;
    
    
    // v1f32 r=ldexp(v1f32(0x1.2352cf807b7dfp-503), v1s32(-1076));
    // double rd=std::ldexp(0x1.2352cf807b7dfp-503, -1076);
    // v1f32 r=ldexp(v1f32(0x1.a2e184p-127f), v1s32(-22));
    // float rd=std::ldexp(0x1.a2e184p-127f, -22);
    v1f32 r=ldexp(v1f32(0x1.0p-127f), v1s32(-1));
    float rd=std::ldexp(0x1.0p-127f, -1);
    // v1f64 r=ldexp(v1f64(0x1.a2e184p-1023), v1s32(+1023-1075));
    // double rd=std::ldexp(0x1.a2e184p-1023, +1023-1075);
    std::cout << std::setprecision(22);
    std::cout << std::hexfloat << r << std::endl;
    std::cout << std::hexfloat << rd << std::endl;
    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
    return 0;
}
