#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>

int main(int argc, char** argv)
{
    using namespace cftal;
    v1f64 a(4.179377736134484375e+14), b(1.000000000000000000e+00);
    v1f64 r=atan2(a, b);

    std::cout << std::scientific<< std::setprecision(22);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << r << std::endl;

    return 0;
}
