#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    bool rc=true;
    const int ulp=1;
    const int _N=8;

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/atan2.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "atan2.testdata");
    }
    std::vector<func_arg_result<float> > v=
        read_float_file(test_data_file, true);

    // std::cerr << std::hexfloat;
    rc&= check_func_2<float, 1, check_atan2<float> >(v, ulp, 0, false);
    rc&= check_func_2<float, 2, check_atan2<float> >(v, ulp, 0, false);
    rc&= check_func_2<float, 4, check_atan2<float> >(v, ulp, 0, false);
    rc&= check_func_2<float, 8, check_atan2<float> >(v, ulp, 0, false);
#endif
    exec_stats st(_N);
    func_domain<float> d=std::make_pair(-std::numeric_limits< float >::max(),
                                         std::numeric_limits< float >::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        float, _N, check_atan2<float> >::v(st, d, d, cmp_ulp<float>(ulp, us),
                                           0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;

    func_domain<float> d1=std::make_pair(0.0, 20.0);
    func_domain<float> d2=std::make_pair(0.0, 100.0);
    us= std::make_shared<ulp_stats>();
    rc &= of_fp_func_2_up_to<
        float, _N, check_atan2<float> >::v(st, d1, d2, cmp_ulp<float>(ulp, us),
                                           0x10000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
