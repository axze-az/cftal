#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_asin.h"
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
    func_domain<float> d=std::make_pair(-1.000001f,
                                        +1.000001f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_asin<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          0x8000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << "stats: \n"
              << st;
    return (rc == true) ? 0 : 1;
}
