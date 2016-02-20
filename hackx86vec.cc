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

    v1f64 a(2.417695834957350489e-308), b(1.306809459378748165e-13);
    v1f64 r=atan2(a, b);

    std::cout << std::scientific<< std::setprecision(22);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << r << std::endl;

    using vf_type = v1f64;
    const vf_type ln2d_hi = 0.693145751953125;
    const vf_type ln2d_lo = 1.42860682030941723212E-6;
    std::cout << std::hexfloat << ln2d_hi << std::endl;
    std::cout << ln2d_lo << std::scientific << std::endl;

    v1f64 l2h, l2l;

    const vec<double, 1> msk(
        const_u64<0x00000000U, 0xfffffff0U>::v._f64);
    l2h = v1f64(M_LN2) & msk;
    l2l = v1f64(M_LN2) - l2h;
    std::cout << std::hexfloat << l2h << std::endl;
    std::cout << l2l << std::scientific << std::endl;
    std::cout << l2h << std::endl;
    std::cout << l2l << std::scientific << std::endl;


    const float ln2f_hi  =  0.693359375f;
    const float ln2f_lo  = -2.12194440e-4f;
    std::cout << std::hexfloat << ln2f_hi << std::endl;
    std::cout << ln2f_lo << std::scientific << std::endl;
    
    v1f32 l2hf, l2lf;
    const vec<float, 1> mskf(
        const_u32<0xffffe000U>::v._f32);
    l2hf = v1f32(M_LN2) & mskf;
    l2lf = v1f32(M_LN2) - l2hf;
    std::cout << std::hexfloat << l2hf << std::endl;
    std::cout << l2lf << std::scientific << std::endl;
    std::cout << l2hf << std::endl;
    std::cout << l2lf << std::scientific << std::endl;
    
    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
    return 0;
}
