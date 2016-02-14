#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/d_real.h>
#include <cftal/vec_traits.h>


int main(int argc, char** argv)
{
    using namespace cftal;
    std::cout << std::scientific<< std::setprecision(22);
    v1f64 u(6.349540949350158986e-276), v(2.565091036874223535e+44);
    // v1f64 v(-4.412109017717083848e-283), u(-2.292371590037048002e-309);
    // v1f64 u(2.417695834957350489e-308), v(1.306809459378748165e-13);
    using traits_t=cftal::math::func_traits<v1f64,v1s32>;
    using func_t=cftal::math::func<double, traits_t>;
    d_real<v1f64> q=func_t::scaled_divide(u, v1f64(0), v, v1f64(0));

    std::cout << q.h() << " " << q.l() << std::endl;

    v1f64 a(2.417695834957350489e-308), b(1.306809459378748165e-13);
    v1f64 r=atan2(a, b);

    std::cout << std::scientific<< std::setprecision(22);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << r << std::endl;

    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
    return 0;
}
