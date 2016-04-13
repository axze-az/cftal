#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_sqrt.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
    using namespace cftal::test;
    bool rc= true;
    func_domain<float> d=std::make_pair(-1.0e-38f,
                                        std::numeric_limits< float >::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(8);
    rc &= of_fp_func_up_to<
        float, 8, check_sqrt<float> >::v(st, d, cmp_ulp<float>(0, us));
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
