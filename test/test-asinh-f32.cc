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
#include "cftal/test/check_asinh.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<float> di[]={
        std::make_pair(-std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::max())
    };
    const int shifts[]={0};
    int r=program<check_asinh<float>, 16, 1, 0x8000>(argc,
                                                     argv,
                                                     mpfr_asinh,
                                                     di,
                                                     shifts);
    return r;
#else
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    cftal::v1f32 t=-2.834401250000000000e+06f;
    std::pair<float, float> rp, rn;
    float fp=call_mpfr::func(t(), mpfr_asinh, &rp);
    float fn=call_mpfr::func(-t(), mpfr_asinh, &rn);

    std::cout << fp << std::endl
              << rp.first << std::endl
              << rp.second << std::endl;
    std::cout << fn << std::endl
              << rn.first << std::endl
              << rn.second << std::endl;
#else
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(
        -std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        float, _N, check_asinh<float> >::v(st, d, speed_only,
                                           cmp_ulp<float>(ulp, us),
                                           cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
#endif
}
