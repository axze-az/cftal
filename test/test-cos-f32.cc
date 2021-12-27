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
#include "cftal/test/check_cos.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<float> di[]={
        std::make_pair(-std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::max())
    };
    const int shifts[]={0};
    int r=program<check_cos<float>, 16, 1, 0x8000>(argc,
                                                   argv,
                                                   mpfr_cos,
                                                   di,
                                                   shifts);
    const func_domain<float> di2[]={
        std::make_pair(-0x1p18f, 0x1p18f)
    };
    r |=program<check_cos<float>, 16, 1, 0x8000>(argc,
                                                 argv,
                                                 mpfr_cos,
                                                 di2,
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
    exec_stats<_N> st;
    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_cos<float> >::v(st, dp, speed_only,
                                         cmp_ulp<float>(ulp, us),
                                         cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    exec_stats<_N> st2;
    auto dp2=std::make_pair(-0x1p18f, 0x1p18f);
    auto us2=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_cos<float> >::v(st2, dp2, speed_only,
                                         cmp_ulp<float>(ulp, us2),
                                         cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us2 << std::endl;
    std::cout << st2 << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
