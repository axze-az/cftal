//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include "cftal/test/check_lgamma.h"
#include <iostream>
#include <iomanip>


int main_lgamma(int argc, char** argv)
{
    using namespace cftal::test;

    pgm_args ags=parse(argc, argv, 0x8000);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1<<24;
    const int ulp_pos=2;
    const int _N=16;
    bool rc=true;

    // func_domain<float> d=std::make_pair(-186.0, +172.0);
    // func_domain<float> d=std::make_pair(0.0f, 4.1e36f);
    // func_domain<float> d=std::make_pair(0.0, 0x1p-53);
    func_domain<float> d=std::make_pair(-0x1p24f, 4.1e36f);
    func_domain<float> d1=std::make_pair(0.0f, 4.1e36f);
    std::cout << "testing lgamma" << std::endl;

    // test also all integral values
    std::vector<float> def_args=default_arguments<float>::values;
    for (std::size_t i=1; i<36; ++i) {
        auto di=static_cast<float>(i);
        if (std::find(std::begin(def_args), std::end(def_args), di)==
            std::end(def_args)) {
            def_args.push_back(di);
        }
        auto dip=std::nextafter(di, std::numeric_limits<float>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dip);
        }
        auto dim=std::nextafter(di, -std::numeric_limits<float>::infinity());
        if (std::find(std::begin(def_args), std::end(def_args), dip)==
            std::end(def_args)) {
            def_args.push_back(dim);
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
    rc &= test_t::v(stp, d1,
                    ags._speed_only,
                    ags._mt,
                    cmp_i_ulp<int32_t, float>(ulp_pos, us),
                    ags._cnt >> 1,
                    true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << stp << std::endl;

    return (rc == true) ? 0 : 1;
}

int main(int argc, char**argv)
{
#if 1
    int r=0;
    r |= main_lgamma(argc, argv);
    return r;
#else
    // creation of the f32 part of lanczos tables
    using namespace cftal::math;
    using lanczos_ratfunc=lanczos_table_g_5_59172_N6;
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
#endif
}
