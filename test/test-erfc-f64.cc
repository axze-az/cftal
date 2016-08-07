#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_erfc.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=128;
    const int _N=8;
    bool speed_only=false;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    bool rc= true;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *= 8;
    }
#if 0
    std::string test_data_dir = dirname(argv[0]);
    std::string test_data_file=
        append_filename(test_data_dir, "../../test/data/erf.testdata");
    if (argc > 1) {
        test_data_dir = argv[1];
        test_data_file = append_filename(test_data_dir, "erf.testdata");
    }
    std::vector<func_arg_result<double> > v=
        read_double_file(test_data_file, false);

    rc &= check_func_1<double, 1, check_erf<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 2, check_erf<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 4, check_erf<double> >(v, ulp, 0, false);
    rc &= check_func_1<double, 8, check_erf<double> >(v, ulp, 0, false);
#endif
    // mnewton(erfc(x)-erf(x), x, 0.46);
    func_domain<double> d=std::make_pair(3.5, 5.325);
    // func_domain<double> d=std::make_pair(1.875, 3.5);
    // func_domain<double> d=std::make_pair(0, 0.75);
    // func_domain<double> d=std::make_pair(-6.0, 27.7);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_erfc<double> >::v(st, d,
                                            speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
