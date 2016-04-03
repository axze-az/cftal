#include "cftal/test/of_math_funcs.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=1;
    const int _N=8;
    bool rc= true;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_sin<float> >::v(st, dp, cmp_ulp<float>(ulp, us),
                                        0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;

    exec_stats st2(_N);
    auto dp2=std::make_pair(-0x1p7f, 0x1p7f);
    auto us2=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_sin<float> >::v(st2, dp2,
                                         cmp_ulp<float>(ulp, us2),
                                         0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us2 << std::endl;
    std::cout << st2 << std::endl;
    return (rc == true) ? 0 : 1;
}
