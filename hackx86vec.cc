#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>

int main(int argc, char** argv)
{
    using namespace cftal;
    v1f64 a(1), b(-1);
    v1f64 r=atan2(a, b);

    std::cout << std::scientific<< std::setprecision(22);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << r << std::endl;

    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
    return 0;
}
