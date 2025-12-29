//
// Copyright (C) 2010-2026 Axel Zeuner
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
    std::cout << "testing floor vXf64" << std::endl;

    exec_stats<8> d_st;
    bool rd=of_fp_func_up_to<
        double, 8, check_floor<double> >::v(d_st);
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << d_st << std::endl;

    std::cout << "testing floor vXf32" << std::endl;
    exec_stats<16> f_st;
    bool rf=of_fp_func_up_to<
        float, 16, check_floor<float> >::v(f_st);
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    std::cout << f_st << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
