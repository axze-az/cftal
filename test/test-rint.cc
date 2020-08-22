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
    std::cout << "testing rint vXf64" << std::endl;
    const int DN=8;
    exec_stats<DN> d_st;
    bool rd=of_fp_func_up_to<
	    double, DN, check_rint<double> >::v(d_st);
    std::cout << d_st << std::endl;

    exec_stats<DN> st2;
    auto dp2=std::make_pair(-0x1p54, 0x1p54);
    rd &= of_fp_func_up_to<
	    double, DN, check_rint<double> >::v(st2, dp2);
    std::cout << st2 << std::endl;
    if (rd==false)
        std::cerr << "double test failed" << std::endl;

    std::cout << "testing rint vXf32" << std::endl;
    exec_stats<16> f_st;
    bool rf=of_fp_func_up_to<
        float, 16, check_rint<float> >::v(f_st);
    std::cout << f_st << std::endl;

    exec_stats<16> f_st2;
    auto f_dp2=std::make_pair(-0x1p24f, 0x1p24f);
    rf &= of_fp_func_up_to<
	    float, 16, check_rint<float> >::v(f_st2, f_dp2);

    std::cout << f_st2 << std::endl;
    if (rf==false)
        std::cerr << "float test failed" << std::endl;

    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
