#include <cftal/test/x_real.h>
#include <functional>
#include <iomanip>
#include <random>

int main()
{
    std::cerr << std::setprecision(20);

    using namespace cftal::test;
    std::cerr << "d_real<double>:\n";
#if 1
    bool rd= cftal::test::check_x_real<cftal::d_real, double,
                                       mpfr_real<128> >::v();
#else
    bool rd = true;
#endif
    std::cerr << "d_real<float>:\n";
    bool rf= cftal::test::check_x_real<cftal::d_real, float,
                                       mpfr_real<64> >::v();
    bool r = rd == true && rf == true;
    return r == true ? 0 : 1;
}
