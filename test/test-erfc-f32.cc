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
#include "cftal/test/check_erfc.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const auto mx = 10.05f;
    const func_domain<float> di[]={
        std::make_pair(-mx, mx)
    };
    const int shifts[]={0};
    int r=program<check_erfc<float>, 16, 1, 0x8000>(argc,
                                                    argv,
                                                    mpfr_erfc,
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
    } else {
        mpfr_cache::use(mpfr_erfc, "erfc", 0.0f);
    }
    // func_domain<float> d=std::make_pair(0.0f, 0.75f);
    // func_domain<float> d=std::make_pair(0.75f, 2.00f);
    // func_domain<float> d=std::make_pair(2.00f, 4.00f);
    // func_domain<float> d=std::make_pair(4.00f, 10.05f);
    // auto mx = 9.194549560546875000000000e+00f;
    // mx = std::nextafter(mx, -1.0f);
    const auto mx = 10.05f;
    func_domain<float> d=std::make_pair(-mx, mx);
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        float, _N, check_erfc<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
