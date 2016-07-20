#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_cos.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::string test_data_dir = dirname(argv[0]);
        std::string test_data_file=
            append_filename(test_data_dir, "../../test/data/cos.testdata");
        if (argc > 1) {
            test_data_dir = argv[1];
            test_data_file = append_filename(test_data_dir, "cos.testdata");
        }
        std::vector<func_arg_result<double> > v=
            read_double_file(test_data_file, false);
        rc &= check_func_1<double, 1, check_cos<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 2, check_cos<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 4, check_cos<double> >(v, ulp, 0, false);
        rc &= check_func_1<double, 8, check_cos<double> >(v, ulp, 0, false);
    }
    auto dp=std::make_pair(-std::numeric_limits<double>::max(),
                           std::numeric_limits<double>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_cos<double> >::v(st, dp, speed_only,
                                           cmp_ulp<double>(ulp, us),
                                           cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

    exec_stats st2(_N);
    auto dp2=std::make_pair(-0x1p20, 0x1p20);
    auto us2=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_cos<double> >::v(st2, dp2, speed_only,
                                           cmp_ulp<double>(ulp, us2),
                                           cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us2 << std::endl;
    std::cout << st2 << std::endl;

    return (rc == true) ? 0 : 1;
}
