#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>

int main(int argc, char** argv)
{
    using namespace cftal;
    v2f64 a(3.880996418503809764e+02, -4.217746855610766374e+02);
    v2f64 r=exp(a);
    v2f64 re0(std::exp(3.880996418503809764e+02), std::exp(-4.217746855610766374e+02));

    std::cout << std::scientific<< std::setprecision(22);
    std::cout << a << std::endl;
    std::cout << r << std::endl;
    std::cout << re0 << std::endl;

    a = v2f64(1.0, 2.0);
    r = exp(a);
    v2f64 re1(std::exp(1.0), std::exp(2.0));
    std::cout << a << std::endl;
    std::cout << r << std::endl;
    std::cout << re1 << std::endl;
    return 0;
}
