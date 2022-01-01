//
// Copyright (C) 2010-2022 Axel Zeuner
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
#include "cftal/test/check_root12.h"

int main(int argc, char** argv)
{
#if 1
    using namespace cftal::test;
    const func_domain<float> di[]={
        std::make_pair(0.0, std::numeric_limits<float>::max())
    };
    const int shifts[]={0};
    int r=program<check_root12<float>, 16, 1, 0x8000>(argc,
                                                      argv,
                                                      mpfr_ext::root12,
                                                      di,
                                                      shifts);
    return r;
#else
    using namespace cftal::test;
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
    func_domain<float> dd=std::make_pair(0.0,
                                          std::numeric_limits<float>::max());
    // dd=std::make_pair(0.125, 1.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> d_st;
    rc &= of_fp_func_up_to<
        float, _N, check_root12<float> >::v(d_st, dd, speed_only,
                                            cmp_ulp<float>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << d_st << std::endl;
    return rc==true ? 0 : 1;
#endif
}
