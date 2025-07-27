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
#include "cftal/test/check_lgamma.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    using cftal::bf16_t;
    using cftal::operator""_bf16;
    cpu_times_to_stdout tt;

    pgm_args ags=parse(argc, argv, 0x4000);
    if (ags._speed_only == false) {
        if (ags._use_cache==true) {
            mpfr_cache::use(mpfr_lgamma, "lgamma", 0.0f);
        }
    }

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int ulp_pos=1;
    const int _N=TEST_BF16_VLEN;
    bool rc=true;

    // func_domain<bf16_t> d=std::make_pair(-186.0, +172.0);
    // func_domain<bf16_t> d=std::make_pair(0.0f, 4.1e36f);
    // func_domain<bf16_t> d=std::make_pair(-5.0f, 8.0f);
    // func_domain<bf16_t> d=std::make_pair(-8.0f, -5.0f);
    // func_domain<bf16_t> d=std::make_pair(0x1p25f, 4.1e36f);
    func_domain<bf16_t> d=std::make_pair(-0x1p24_bf16, 4.1e36_bf16);
    func_domain<bf16_t> d1=std::make_pair(0.0_bf16, 4.1e36_bf16);
    std::cout << "bf16 testing lgamma" << std::endl;

    // test also some integral and integral-1/2 values
    std::vector<bf16_t> def_args=default_arguments<bf16_t>::values;
    for (std::size_t i=1; i<1025; ++i) {
        using std::nextafter;
        auto di=static_cast<bf16_t>(i);
        auto dih=di-0.5_bf16;
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args)) {
            def_args.push_back(di);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dih)==
            std::end(def_args)) {
            def_args.push_back(dih);
        }
        auto dip=nextafter(di, std::numeric_limits<bf16_t>::infinity());
        auto dihp=nextafter(dih, std::numeric_limits<bf16_t>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihp)==
            std::end(def_args)) {
            def_args.push_back(dihp);
        }
        auto dim=nextafter(di, -std::numeric_limits<bf16_t>::infinity());
        auto dihm=nextafter(dih, -std::numeric_limits<bf16_t>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dim)==
            std::end(def_args)) {
            def_args.push_back(dim);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihm)==
            std::end(def_args)) {
            def_args.push_back(dihm);
        }
    }
    using test_t=of_fp_func_up_to<bf16_t, _N, check_lgamma<bf16_t, int16_t> >;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= test_t::v(st, d,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int16_t, bf16_t>(ulp, us),
                    ags._cnt >> 1,
                    def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;


    static_cast<void>(d1);
    static_cast<void>(ulp_pos);

    exec_stats<_N> stp;
    us = std::make_shared<ulp_stats>();
    std::vector<bf16_t> p_def_args;
    std::copy_if(std::cbegin(def_args), std::cend(def_args),
                 std::back_inserter(p_def_args),
                 [](bf16_t v)->bool {
                     return v>=0.0_bf16;
                 });
    rc &= test_t::v(stp, d1,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int16_t, bf16_t>(ulp_pos, us),
                    ags._cnt >> 1,
                    p_def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << stp << std::endl;
    return (rc == true) ? 0 : 1;
}
