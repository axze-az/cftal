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
#include "cftal/test/check_tgamma.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
    using cftal::f16_t;
    using cftal::operator""_f16;
    cpu_times_to_stdout tt;

    pgm_args ags=parse(argc, argv, 0x4000);
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=1;
    const int _N=32;
    bool rc=true;

    func_domain<f16_t> d=std::make_pair(-20.0_f16, +10.0_f16);
    std::cout << "testing tgamma" << std::endl;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;

    // test also some integral and integral-1/2 values
    std::vector<f16_t> def_args=default_arguments<f16_t>::values;
    for (std::size_t i=1; i<10; ++i) {
        using std::nextafter;
        auto di=static_cast<f16_t>(i);
        auto dih=di-0.5f;
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args)) {
            def_args.push_back(di);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dih)==
            std::end(def_args)) {
            def_args.push_back(dih);
        }
        auto dip=nextafter(di, std::numeric_limits<f16_t>::infinity());
        auto dihp=nextafter(dih, std::numeric_limits<f16_t>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihp)==
            std::end(def_args)) {
            def_args.push_back(dihp);
        }
        auto dim=nextafter(di, -std::numeric_limits<f16_t>::infinity());
        auto dihm=nextafter(dih, -std::numeric_limits<f16_t>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dim)==
            std::end(def_args)) {
            def_args.push_back(dim);
        }
        if (std::find(std::begin(def_args), std::end(def_args), dihm)==
            std::end(def_args)) {
            def_args.push_back(dihm);
        }
    }

    rc &= of_fp_func_up_to<
        f16_t, _N, check_tgamma<f16_t> >::v(st, d,
                                            ags._speed_only,
                                            ags._mt,
                                            cmp_ulp<f16_t>(ulp, us),
                                            ags._cnt,
                                            def_args);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
