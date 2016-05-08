#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/of_math_funcs.h>
#include <cftal/test/check_cbrt.h>
#include <limits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstring>


int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=0x8000;
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> df=std::make_pair(-std::numeric_limits<float>::max(),
                                          std::numeric_limits<float>::max());
    auto usf=std::make_shared<ulp_stats>();
    exec_stats f_st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_cbrt<float> >::v(f_st, df, speed_only,
                                          cmp_ulp<float>(ulp, usf),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *usf << std::endl;
    std::cout << f_st << std::endl;
    return rc==true ? 0 : 1;
}
