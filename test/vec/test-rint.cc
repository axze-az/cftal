//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
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
