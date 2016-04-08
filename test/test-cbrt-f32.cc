#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/of_math_funcs.h>
#include <limits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstring>


int main(int argc, char** argv)
{
    bool rc=true;
    using namespace cftal::test;
    const int ulp=6;
    const int _N=8;

    std::cout << "f32 test\n"<<std::scientific;
    func_domain<float> df=std::make_pair(-std::numeric_limits<float>::max(),
                                          std::numeric_limits<float>::max());
    auto usf=std::make_shared<ulp_stats>();
    exec_stats f_st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_cbrt<float> >::v(f_st, df, cmp_ulp<float>(ulp, usf),
                                           0x20000);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *usf << std::endl;
    std::cout << f_st << std::endl;
    return rc==true ? 0 : 1;
}
