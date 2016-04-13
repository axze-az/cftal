#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_native_log.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=3;
    const int _N=8;
    

    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/log.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "log.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    // std::cerr << std::hexfloat;
    bool rc= check_func_1<double, 1,
                          check_native_log<double> >(v, ulp, 0, false);
    rc&= check_func_1<double, 2,
                      check_native_log<double> >(v, ulp, 0, false);
    rc&= check_func_1<double, 4,
                      check_native_log<double> >(v, ulp, 0, false);
    rc&= check_func_1<double, 8,
                      check_native_log<double> >(v, ulp, 0, false);

    exec_stats st(_N);
    func_domain<double> d=std::make_pair(0.0,
                                         std::numeric_limits< double >::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_native_log<double> >::v(st, d, cmp_ulp<double>(ulp, us));
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
