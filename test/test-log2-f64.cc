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
#include "cftal/test/check_log2.h"

int main(int argc, char** argv)
{
#if 1
    using namespace cftal::test;
    const func_domain<double> di[]={
        std::make_pair(0.0, std::numeric_limits< double >::max())
    };
    const int shifts[]={0};
    int r=program<check_log2<double>, 8, 1, 0x8000>(argc,
                                                    argv,
                                                    mpfr_log2,
                                                    di,
                                                    shifts);
    return r;
#else
    using namespace cftal::test;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/log2.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "log2.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);

        rc&= check_func_1<double, 1, check_log2<double> >(v, ulp, 0, false);
        rc&= check_func_1<double, 2, check_log2<double> >(v, ulp, 0, false);
        rc&= check_func_1<double, 4, check_log2<double> >(v, ulp, 0, false);
        rc&= check_func_1<double, 8, check_log2<double> >(v, ulp, 0, false);
    }
    func_domain<double> d=std::make_pair(0.0,
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        double, _N, check_log2<double> >::v(st, d, speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
