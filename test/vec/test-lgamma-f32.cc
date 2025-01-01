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
    cpu_times_to_stdout tt;

    pgm_args ags=parse(argc, argv, 0x8000);
    if (ags._speed_only == false) {
        if (ags._use_cache==true) {
            mpfr_cache::use(mpfr_lgamma, "lgamma", 0.0f);
        }
    }

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int ulp_pos=1;
    const int _N=16;
    bool rc=true;

    // func_domain<float> d=std::make_pair(-186.0, +172.0);
    // func_domain<float> d=std::make_pair(0.0f, 4.1e36f);
    // func_domain<float> d=std::make_pair(-5.0f, 8.0f);
    // func_domain<float> d=std::make_pair(-8.0f, -5.0f);
    // func_domain<float> d=std::make_pair(0x1p25f, 4.1e36f);
    func_domain<float> d=std::make_pair(-0x1p24f, 4.1e36f);
    func_domain<float> d1=std::make_pair(0.0f, 4.1e36f);
    std::cout << "f32 testing lgamma" << std::endl;

    // test also some integral and integral-1/2 values
    std::vector<float> def_args=default_arguments<float>::values;
    for (std::size_t i=1; i<1025; ++i) {
        auto di=static_cast<float>(i);
        auto dih=di-0.5f;
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args)) {
            def_args.push_back(di);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dih)==
            std::end(def_args)) {
            def_args.push_back(dih);
        }
        auto dip=std::nextafter(di, std::numeric_limits<float>::infinity());
        auto dihp=std::nextafter(dih, std::numeric_limits<float>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihp)==
            std::end(def_args)) {
            def_args.push_back(dihp);
        }
        auto dim=std::nextafter(di, -std::numeric_limits<float>::infinity());
        auto dihm=std::nextafter(dih, -std::numeric_limits<float>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dim)==
            std::end(def_args)) {
            def_args.push_back(dim);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihm)==
            std::end(def_args)) {
            def_args.push_back(dihm);
        }
    }
    using test_t=of_fp_func_up_to<float, _N, check_lgamma<float> >;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= test_t::v(st, d,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, float>(ulp, us),
                    ags._cnt >> 1,
                    def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;


    static_cast<void>(d1);
    static_cast<void>(ulp_pos);

    exec_stats<_N> stp;
    us = std::make_shared<ulp_stats>();
    std::vector<float> p_def_args;
    std::copy_if(std::cbegin(def_args), std::cend(def_args),
                 std::back_inserter(p_def_args),
                 [](float v)->bool {
                     return v>=0.0f;
                 });
    rc &= test_t::v(stp, d1,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, float>(ulp_pos, us),
                    ags._cnt >> 1,
                    p_def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << stp << std::endl;
    return (rc == true) ? 0 : 1;
}
