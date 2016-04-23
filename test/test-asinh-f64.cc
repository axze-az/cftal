#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_asinh.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/asinh.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "asinh.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    rc &= check_func_1<double, 1, check_asinh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_asinh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_asinh<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_asinh<double> >(v, ulp, 0, false);
#endif
#if 1
    func_domain<double> d=std::make_pair(
        -std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max());
#else
    func_domain<double> d=std::make_pair(
        -M_SQRT2/2,
        M_SQRT2/2);
#endif
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_asinh<double> >::v(st, d, cmp_ulp<double>(ulp, us),
                                             0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
