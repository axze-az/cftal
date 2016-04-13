#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_log.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    const int _N=8;
    const int ulp=1;

    bool rc=true;

    exec_stats st(_N);
    func_domain<float> d=std::make_pair(-0.0001,
                                         std::numeric_limits< float >::max());
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_log<float> >::v(st, d, cmp_ulp<float>(ulp, us));
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
