//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_fp_funcs.h"
#include <iomanip>

int main()
{
    using namespace cftal::test;
    std::cout << std::setprecision(18);
    std::cerr << std::setprecision(18);
    std::cout << "testing trunc vXf64" << std::endl;

    const int _DN=8;
    const int _FN=16;
    exec_stats<_DN> d_st;

    bool rd=of_fp_func_up_to<
        double, _DN, cftal::test::check_trunc<double> >::v(d_st);
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << d_st << std::endl;
    std::cout << "testing trunc vXf32" << std::endl;

    exec_stats<_FN> f_st;
    bool rf=cftal::test::of_fp_func_up_to<
        float, _FN, cftal::test::check_trunc<float> >::v(f_st);
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    std::cout << f_st << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
