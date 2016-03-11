#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=1;
    int rc= true;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    // sin part
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/sin.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "sin.testdata");
    }
    std::vector<func_arg_result<float> > v=
        read_float_file(test_data_file, false);


    rc &= check_func_1<float, 1, check_sincos<float>::sin >(v,
                                                            ulp, 0, false);
    rc &= check_func_1<float, 2, check_sincos<float>::sin >(v, ulp, 0, false);
    rc &= check_func_1<float, 4, check_sincos<float>::sin >(v, ulp, 0, false);
    rc &= check_func_1<float, 8, check_sincos<float>::sin >(v, ulp, 0, false);

    // cos part
    test_data_file=
        append_filename(test_data_dir, "../../test/data/cos.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "cos.testdata");
    }
    v=read_float_file(test_data_file, false);

    rc &= check_func_1<float, 2, check_sincos<float>::cos >(v, ulp, 0, false);
    rc &= check_func_1<float, 4, check_sincos<float>::cos >(v, ulp, 0, false);
    rc &= check_func_1<float, 8, check_sincos<float>::cos >(v, ulp, 0, false);

#endif

    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, 8, check_sincos<float>::sin >::v(dp, cmp_ulp<float>(ulp, us),
                                                0x80000);
    rc &= of_fp_func_up_to<
        float, 8, check_sincos<float>::cos >::v(dp, cmp_ulp<float>(ulp, us),
                                                0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    return (rc == true) ? 0 : 1;
}
