#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_exp.h"
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
    std::size_t cnt=update_cnt(0x8000);
    bool speed_only=false;
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    exec_stats st(_N);
    func_domain<float> d=std::make_pair(-104.0f, 89.0f);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp<float> >::v(st, d, speed_only,
                                         cmp_ulp<float>(ulp, us),
                                         cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
