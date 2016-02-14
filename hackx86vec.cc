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

    v1f64 a(2.417695834957350489e-308), b(1.306809459378748165e-13);
    v1f64 r=atan2(a, b);

    std::cout << std::scientific<< std::setprecision(22);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << r << std::endl;

    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
    return 0;
}
