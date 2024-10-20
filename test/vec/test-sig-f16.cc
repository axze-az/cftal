//
// Copyright (C) 2010-2024 Axel Zeuner
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
#include "cftal/test/check_sig.h"

int main(int argc, char** argv)
{
    using cftal::f16_t;
    using cftal::operator""_f16;
#if 0
    using namespace cftal::test;
    const func_domain<f16_t> di[]={
        std::make_pair(-89.0f, +18.0f)
    };
    const int shifts[]={0};
    int r=program<check_sig<f16_t>,
                  32, 4, 0x8000>(argc,
				 argv,
				 mpfr_ext::sig,
				 di,
				 shifts);
    return r;
#else
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    pgm_args ags=parse(argc, argv, 0x4000);

    const int ulp=1;
    const int _N=32;
    bool rc=true;

    using ftype = f16_t;

    auto d = std::make_pair(-17.5_f16, +8.5_f16);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_sig<ftype> >::v(st, d,
                                         ags._speed_only,
                                         ags._mt,
                                         cmp_ulp<ftype>(ulp, us),
                                         ags._cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}

