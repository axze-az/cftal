// 
// Copyright (C) 2010-2021 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include "cftal/test/program.h"
#include "cftal/test/check_acosh.h"

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 1
    const func_domain<double> di[]={
        std::make_pair(1.0, std::numeric_limits<double>::max())
    };
    const int shifts[]= {
        0
    };
    int r=program<check_acosh<double>, 8, 1, 0x8000>(argc,
                                                     argv,
                                                     mpfr_acosh,
                                                     di,
                                                     shifts);
    return r;
#else
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    // std::cerr << std::hexfloat;
    // std::cout << std::hexfloat;
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/acosh.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "acosh.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    rc &= check_func_1<double, 1, check_acosh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_acosh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_acosh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_acosh<double> >(v, ulp, 0, false);
#endif
#if 1
    func_domain<double> d=std::make_pair(
        1.0,
        std::numeric_limits<double>::max());
#else
    func_domain<double> d=std::make_pair(
        3.0, 12.0);
        // 1.54, std::numeric_limits<double>::max());
#endif
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        double, _N, check_acosh<double> >::v(st, d,
                                             speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
