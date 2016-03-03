#include <cftal/math_func.h>

int32_t
cftal::math::impl::__ieee754_rem_pio2(float x, float *y)
{
    double xd=static_cast<double>(x);
    double r[2];
    int32_t n=__ieee754_rem_pio2(xd, r);
    float h= static_cast<float>(r[0]);
    double hd= static_cast<double>(h);
    double hl= r[0] - hd;
    float l= static_cast<float>(hl);
    y[0] = h;
    y[1] = l;
    return n;
}
