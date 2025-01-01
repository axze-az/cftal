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
#include "cftal/test/program.h"
#include "cftal/test/check_sinpicospi.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    using cftal::bf16_t;
    using cftal::operator ""_bf16;
    cpu_times_to_stdout tt;
    pgm_args ags=parse(argc, argv, 0x8000);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=32;

    bool rc=true;
    auto dp=std::make_pair(-0x1.5p25_bf16, 0x1.5p25_bf16);
    auto us_sin=std::make_shared<ulp_stats>();
    auto us_cos=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    struct cmp_ulp<std::pair<bf16_t, bf16_t> > cmp(ulp, us_sin, us_cos);
    rc &= of_fp_func_up_to<
        bf16_t, _N, check_sinpicospi<bf16_t> >::v(st, dp,
                                                  ags._speed_only,
                                                  ags._mt,
                                                  cmp,
                                                  ags._cnt);
    std::cout << "sinpi ulps: "
              << std::fixed << std::setprecision(4) << *us_sin << std::endl;
    std::cout << "cospi ulps: "
              << std::fixed << std::setprecision(4) << *us_cos << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
