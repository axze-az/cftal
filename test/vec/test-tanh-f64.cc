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
#include "cftal/test/check_tanh.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
#if 1
    using namespace cftal::test;
    int r=program<check_tanh<double>, 8, 1, 0x8000>(
        argc,
        argv,
        mpfr_tanh,
        domain_tanh<double>::domains,
        domain_tanh<double>::shifts);
    return r;
#else

    using namespace cftal::test;
    const int ulp=1;
    const int _N=8;
    bool speed_only=false;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    bool rc= true;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *= 8;
    }
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/tanh.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "tanh.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    rc &= check_func_1<double, 1, check_tanh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_tanh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_tanh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_tanh<double> >(v, ulp, 0, false);
#endif
    func_domain<double> d=std::make_pair(-36.0, 36.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        double, _N, check_tanh<double> >::v(st, d,
                                            speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
