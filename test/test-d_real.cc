//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
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
