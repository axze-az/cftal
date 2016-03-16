#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    bool rc= true;
    const int ulp = 5;
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


    rc &= check_func_1<float, 1, check_native_cos<float> >(v, ulp, 0, false);
    rc &= check_func_1<float, 2, check_native_cos<float> >(v, ulp, 0, false);
    rc &= check_func_1<float, 4, check_native_cos<float> >(v, ulp, 0, false);
    rc &= check_func_1<float, 8, check_native_cos<float> >(v, ulp, 0, false);
#endif
    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, 8, check_native_cos<float> >::v(dp, cmp_ulp<float>(ulp, us),
                                               0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    return (rc == true) ? 0 : 1;
}
