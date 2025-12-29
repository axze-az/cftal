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
#include "cftal/test/check_hypot.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    cpu_times_to_stdout tt;

    using cftal::f16_t;
    using cftal::operator""_f16;

    const int ulp2=1;
    const int ulp=1;
    const int _N=TEST_F16_VLEN;
    bool rc=true;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    pgm_args ags=parse(argc, argv, 0x4000);

    func_domain<f16_t> d=std::make_pair(-std::numeric_limits< f16_t >::max(),
                                         std::numeric_limits< f16_t >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_2_up_to<
        f16_t, _N, check_hypot<f16_t> >::v(st, d, d, ags._speed_only,
                                           ags._mt,
                                           cmp_ulp<f16_t>(ulp2, us),
                                           ags._cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    exec_stats<_N> st1;
    us=std::make_shared<ulp_stats>();
    func_domain<f16_t> d1=std::make_pair(-32.0_f16, 32.0_f16);
    func_domain<f16_t> d2=std::make_pair(-32.0_f16, 32.0_f16);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        f16_t, _N, check_hypot<f16_t> >::v(st1, d1, d2,
                                           ags._speed_only,
                                           ags._mt,
                                           cmp_ulp<f16_t>(ulp, us),
                                           ags._cnt, true);
    d1=std::make_pair(-4.0_f16, 4.0_f16);
    d2=std::make_pair(-4.0_f16, 4.0_f16);
    rc &= of_fp_func_2_up_to<
        f16_t, _N, check_hypot<f16_t> >::v(st1, d1, d2,
                                           ags._speed_only,
                                           ags._mt,
                                           cmp_ulp<f16_t>(ulp, us),
                                           ags._cnt, true);

    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st1 << std::endl;
    return (rc == true) ? 0 : 1;
}
