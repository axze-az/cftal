// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include "cftal/test/program.h"
#include "cftal/test/check_rcbrt.h"


int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<float> di[]={
        std::make_pair(-std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::max())
    };
    const int shifts[]={0};
    int r=program<check_rcbrt<float>, 16, 1, 0x8000>(argc,
                                                     argv,
                                                     mpfr_ext::rcbrt,
                                                     di,
                                                     shifts);
    return r;
#else
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> df=std::make_pair(-std::numeric_limits<float>::max(),
                                          std::numeric_limits<float>::max());
    auto usf=std::make_shared<ulp_stats>();
    exec_stats<_N> f_st;
    rc &= of_fp_func_up_to<
        float, _N, check_cbrt<float> >::v(f_st, df, speed_only,
                                          cmp_ulp<float>(ulp, usf),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *usf << std::endl;
    std::cout << f_st << std::endl;
    return rc==true ? 0 : 1;
#endif
}
