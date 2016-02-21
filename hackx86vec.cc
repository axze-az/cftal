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
    v1f64 r=ldexp(v1f64(0x1.2352cf807b7dfp-503), v1s32(-1076));
    double rd=std::ldexp(0x1.2352cf807b7dfp-503, -1076);
    std::cout << std::setprecision(22);
    std::cout << std::hexfloat << r << std::endl;
    std::cout << std::hexfloat << rd << std::endl;
    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
    return 0;
}
