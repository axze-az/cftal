#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_log10.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    bool rc=true;
    const int ulp=1;
    const int _N=8;

    func_domain<float> d=std::make_pair(-0.0001,
                                         std::numeric_limits< float >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, 8, check_log10<float> >::v(st, d, cmp_ulp<float>(ulp, us),
                                          0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
