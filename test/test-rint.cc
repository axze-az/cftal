#include "cftal/test/of_fp_funcs.h"
#include <iomanip>

int main()
{
    std::cout << std::setprecision(18);
    std::cerr << std::setprecision(18);
    std::cout << "testing rint vXf64" << std::endl;
    bool rd=cftal::test::of_fp_func_up_to<
        double, 8, cftal::test::check_rint<double> >::v();
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << "testing rint vXf32" << std::endl;
    bool rf=cftal::test::of_fp_func_up_to<
        float, 16, cftal::test::check_rint<float> >::v();
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
