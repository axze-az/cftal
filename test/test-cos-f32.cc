#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    bool rc= true;
    const int ulp = 1;
    const int _N = 8;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/cos.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "cos.testdata");
    }
    std::vector<func_arg_result<float> > v=
        read_float_file(test_data_file, false);


    rc &= check_func_1<float, 1, check_cos<float> >(v, ulp, 0, false);
    rc &= check_func_1<float, 2, check_cos<float> >(v, ulp, 0, false);
    rc &= check_func_1<float, 4, check_cos<float> >(v, ulp, 0, false);
    rc &= check_func_1<float, 8, check_cos<float> >(v, ulp, 0, false);
#endif
    exec_stats st(_N);
    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_cos<float> >::v(st, dp, cmp_ulp<float>(ulp, us),
                                         0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    exec_stats st2(_N);
    auto dp2=std::make_pair(-0x1p7f, 0x1p7f);
    auto us2=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_cos<float> >::v(st2, dp2,
                                         cmp_ulp<float>(ulp, us2),
                                         0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us2 << std::endl;
    std::cout << st2 << std::endl;
    return (rc == true) ? 0 : 1;
}
