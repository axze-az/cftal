#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_native_expm1.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    bool rc = true;

    const int _N=8;
    const int ulp=1;
    exec_stats st(_N);
    func_domain<float> d=std::make_pair(-20.0f, 90.0f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_native_expm1<float> >::v(st, d,
                                                  cmp_ulp<float>(ulp, us));
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
