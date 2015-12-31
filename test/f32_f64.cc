#include "cftal/test/f32_f64.h"
#include <boost/math/special_functions.hpp>
#include <cmath>

double cftal::test::make_double(unsigned sgn, unsigned exp, uint64_t sig)
{
    uint64_t _sgn= uint64_t(sgn & 1) << 63;
    uint64_t _exp= uint64_t(exp & 0x7FF) << 52;
    uint64_t _sig= sig & 0x000fffffffffffffULL;
    union {
        uint64_t _u;
        double _d;
    } t;
    t._u = _sgn | _exp | _sig;
    return t._d;
}

float cftal::test::make_float(unsigned sgn, unsigned exp, uint32_t sig)
{
    uint32_t _sgn= uint64_t(sgn & 1) << 31;
    uint32_t _exp= uint64_t(exp & 0xFF) << 23;
    uint32_t _sig= sig & 0x007fffff;
    union {
        uint32_t _u;
        float _d;
    } t;
    t._u = _sgn | _exp | _sig;
    return t._d;
}

bool cftal::test::f_eq(double a, double b)
{
    return (a == b) || (std::isnan(a) && std::isnan(b));
}

bool cftal::test::f_eq(float a, float b)
{
    return (a == b) || (std::isnan(a) && std::isnan(b));
}

namespace {

    template <typename _T>
    bool cmp_ulp(_T a, _T b, uint32_t ulp)
    {
        bool r;
        if ((r=cftal::test::f_eq(a, b)) == false) {
            int32_t u=sizeof(_T)*8;
            try {
                u=boost::math::float_distance<_T>(a, b);
            }
            catch (...) {
            }
            if (std::abs(u) <= int32_t(ulp))
                r=true;
        }
        return r;
    }
}

bool cftal::test::f_eq_ulp(double a, double b, uint32_t ulp)
{
    return cmp_ulp(a, b, ulp);
}

bool cftal::test::f_eq_ulp(float a, float b, uint32_t ulp)
{
    return cmp_ulp(a, b, ulp);
}


