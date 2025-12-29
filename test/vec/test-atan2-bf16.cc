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
#include "cftal/test/program.h"
#include "cftal/test/check_atan2.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    cpu_times_to_stdout tt;
    using cftal::bf16_t;
    using cftal::operator ""_bf16;

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=TEST_BF16_VLEN;
    bool rc=true;

    pgm_args ags=parse(argc, argv, 0x4000);
    exec_stats<_N> st;
    func_domain<bf16_t> d=std::make_pair(-std::numeric_limits< bf16_t >::max(),
                                         std::numeric_limits< bf16_t >::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        bf16_t, _N, check_atan2<bf16_t> >::v(st, d, d,
                                             ags._speed_only,
                                             ags._mt,
                                             cmp_ulp<bf16_t>(ulp, us),
                                             ags._cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;

    func_domain<bf16_t> d1=std::make_pair(-100.0_bf16, 100.0_bf16);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        bf16_t, _N, check_atan2<bf16_t> >::v(st, d1, d1,
                                             ags._speed_only,
                                             ags._mt,
                                             cmp_ulp<bf16_t>(ulp, us),
                                             ags._cnt/2);
    func_domain<bf16_t> d2=std::make_pair(-20.0_bf16, 20.0_bf16);
    rc &= of_fp_func_2_up_to<
        bf16_t, _N, check_atan2<bf16_t> >::v(st, d2, d2,
                                             ags._speed_only,
                                             ags._mt,
                                             cmp_ulp<bf16_t>(ulp, us),
                                             ags._cnt/2);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
