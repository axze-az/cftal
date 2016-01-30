#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>

int main(int argc, char** argv)
{

    double t= 1.0;
    int e0;

    double m=std::frexp(t, &e0);

    int e1=std::ilogb(t);

    std::cout << std::scientific << std::setprecision(22);
    std::cout << m << "* 2^" << e0 << std::endl;
    std::cout << e1 << std::endl;

    return 0;
}
