//
// Copyright (C) 2010-2023 Axel Zeuner
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
#include "cftal/test/program.h"
#include "cftal/test/check_asinh.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<double> di[]={
        std::make_pair(-std::numeric_limits<double>::max(),
                        std::numeric_limits<double>::max())
    };
    const int shifts[]= {
        0,
    };
    int r=program<check_asinh<double>, 8, 1, 0x8000>(argc,
                                                     argv,
                                                     mpfr_asinh,
                                                     di,
                                                     shifts);
    return r;
#else
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
#if 1
    func_domain<double> d=std::make_pair(
        -std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max());
#else
    func_domain<double> d=std::make_pair(M_SQRT2/2, 3.0);
                                         // std::numeric_limits<double>::max());
#endif
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        double, _N, check_asinh<double> >::v(st, d, speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
