#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/log2.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "log2.testdata");
    }
    std::vector<func_arg_result<float> > v=
        read_float_file(test_data_file, false);

    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    // std::cerr << std::hexfloat;
    bool rc= check_func_1<float, 2, check_log2<float> >(v, 1, 0, false);
    rc&= check_func_1<float, 4, check_log2<float> >(v, 1, 0, false);
    rc&= check_func_1<float, 8, check_log2<float> >(v, 1, 0, false);
#else
    bool rc=true;
#endif
    func_domain<float> d=std::make_pair(-0.0001,
                                         std::numeric_limits< float >::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, 8, check_log2<float> >::v(d, cmp_ulp<float>(1, us),
                                         0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    return (rc == true) ? 0 : 1;
}
