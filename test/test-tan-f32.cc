#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_tan.h"
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
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
    }
    exec_stats st(_N);
    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_tan<float> >::v(st, dp, speed_only,
                                         cmp_ulp<float>(ulp, us),
                                         0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

    exec_stats st2(_N);
    auto dp2=std::make_pair(-0x1p6f, 0x1p6f);
    auto us2=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_tan<float> >::v(st2, dp2, speed_only,
                                         cmp_ulp<float>(ulp, us2),
                                         0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us2 << std::endl;
    std::cout << st2 << std::endl;
    return (rc == true) ? 0 : 1;
}
