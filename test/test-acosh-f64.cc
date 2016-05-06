#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_acosh.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=2;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    // std::cerr << std::hexfloat;
    // std::cout << std::hexfloat;
    if ((argc > 1) && (std::string(argv[1]) == "--speed"))
        speed_only=true;
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
        1, 2);
        // 1.54, std::numeric_limits<double>::max());
#endif
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_acosh<double> >::v(st, d,
                                             speed_only,
                                             cmp_ulp<double>(ulp, us),
                                             0x10000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
