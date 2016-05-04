#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_native_sin.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    bool rc=true;
    const int ulp=1;
    const int _N=8;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    exec_stats st(_N);
    auto dp=std::make_pair(-std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_native_sin<float> >::v(st, dp, cmp_ulp<float>(ulp, us),
                                                0x80000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
