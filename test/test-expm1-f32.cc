#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/exp.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "exp.testdata");
    }
    std::vector<func_arg_result<double> > vd=
        read_double_file(test_data_file, false);
    std::vector<func_arg_result<float> > v;
    for (const auto& di : vd) {
        double a0 = di.arg0(), a1= di.arg1(), r=di.res();
        func_arg_result<float> fi(a0, a1, r);
        v.emplace_back(fi);
    }
    bool rc= check_func_1<float, 2, check_exp<float> >(v, 1, 0, false);
    // rc &= check_func_1<float, 4, check_exp<float> >(v, 1, 0, false);
    // rc &= check_func_1<float, 8, check_exp<float> >(v, 1, 0, false);
    if (rc)
        exit(1);
#else
    bool rc = true;
#endif
    func_domain<float> d=std::make_pair(-20.0f, 90.0f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, 8, check_expm1<float> >::v(d, cmp_ulp<float>(1, us));
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    return (rc == true) ? 0 : 1;
}
