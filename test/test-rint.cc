#include "cftal/test/of_fp_funcs.h"
#include <iomanip>

int main()
{
    using namespace cftal::test;
    std::cout << std::setprecision(18);
    std::cerr << std::setprecision(18);
    std::cout << "testing rint vXf64" << std::endl;
    exec_stats d_st(8);
    bool rd=of_fp_func_up_to<
        double, 8, check_rint<double> >::v(d_st);
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << d_st << std::endl;
    std::cout << "testing rint vXf32" << std::endl;
    exec_stats f_st(16);
    bool rf=of_fp_func_up_to<
        float, 16, check_rint<float> >::v(f_st);
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    std::cout << f_st << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
