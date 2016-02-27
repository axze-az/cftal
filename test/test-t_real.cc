#include <cftal/test/x_real.h>
#include <functional>
#include <iomanip>
#include <random>

int main()
{
    std::cerr << std::setprecision(20);
#if 0
    using namespace cftal::test;
    std::cerr << "t_real<double>:\n";
    bool rd= cftal::test::check_x_real<cftal::t_real, double,
                                       mpfr_real<196> >::v();
    std::cerr << "t_real<float>:\n";
    bool rf= cftal::test::check_x_real<cftal::t_real, float,
                                       mpfr_real<128> >::v();
    bool r = rd == true && rf == true;
    return r == true ? 0 : 1;
#else
    return 0;
#endif
}
