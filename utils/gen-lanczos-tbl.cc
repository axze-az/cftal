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
#include <iostream>
#include "cftal/math/lanczos.h"
#include <iomanip>


int main(int argc, char**argv)
{
    // creation of the f32 part of lanczos tables
    using namespace cftal::math;
    using lanczos_ratfunc=lanczos_table_g_4_35169_N5;
    std::cout << std::scientific;

    auto make_df32=[](double d) ->std::pair<float, float> {
        float dh=static_cast<float>(d);
        float dl=static_cast<float>(d-static_cast<double>(dh));
        return std::make_pair(dh, dl);
    };

    auto gm0_5= make_df32(lanczos_ratfunc::gm0_5());
    std::cout << "static constexpr\n"
              << "float gm0_5f() {\n"
              << "return "
              << std::setprecision(10) << gm0_5.first
              << "f;\n}\n";

    std::cout << "static constexpr\n"
              << "float gm0_5f_l() {\n"
              << "return "
              << std::setprecision(10) << gm0_5.second
              << "f;\n}\n";


    const std::size_t _P=std::cend(lanczos_ratfunc::pd)
        - std::cbegin(lanczos_ratfunc::pd);
    std::cout << "static constexpr\n"
              << "const d_real<float> pdf[]={\n"
              << std::scientific;
    for (std::size_t i=0; i<_P; ++i) {
        double d=lanczos_ratfunc::p[i];
        auto dp=make_df32(d);
        std::cout << "{ "
                  << std::setprecision(10) << dp.first << "f, "
                  << std::setprecision(10) << dp.second << "f }";
        if (i != _P-1)
            std::cout << ',';
        std::cout << '\n';
    }
    std::cout << "};\n";

    std::cout << "static constexpr\n"
              << "const d_real<float> pedf[]={\n"
              << std::scientific;
    for (std::size_t i=0; i<_P; ++i) {
        double d=lanczos_ratfunc::ped[i][0];
        auto dp=make_df32(d);
        std::cout << "{ "
                  << std::setprecision(10) << dp.first << "f, "
                  << std::setprecision(10) << dp.second << "f }";
        if (i != _P-1)
            std::cout << ',';
        std::cout << '\n';
    }
    std::cout << "};\n";

    const std::size_t _Q=std::cend(lanczos_ratfunc::q)
        - std::cbegin(lanczos_ratfunc::q);
    std::cout << "static constexpr\n"
              << "const float qf[]={\n"
              << std::scientific;
    for (std::size_t i=0; i<_Q; ++i) {
        double d=lanczos_ratfunc::q[i];
        auto dp=make_df32(d);
        if (dp.second != 0.0f) {
            std::cerr << "oops, table with too large coefficients\n";
        }
        std::cout << std::setprecision(10) << dp.first << "f";
        if (i != _P-1)
            std::cout << ',';
        std::cout << '\n';
    }
    std::cout << "};\n";
    return 0;
}
