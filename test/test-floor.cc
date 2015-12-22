#include "cftal/test/of_fp_funcs.h"

int main()
{
    std::cout << "testing floor vXf64" << std::endl;
    bool rd=cftal::test::of_fp_func_up_to<
        double, 8, cftal::test::check_floor<double> >::v();
    if (rd==false)
        std::cerr << "double test failed" << std::endl;
    std::cout << "testing floor vXf32" << std::endl;
    bool rf=cftal::test::of_fp_func_up_to<
        float, 16, cftal::test::check_floor<float> >::v();
    if (rf==false)
        std::cerr<< "float test failed" << std::endl;
    bool rc = rd && rf;
    return rc==true ? 0 : 1;
}
