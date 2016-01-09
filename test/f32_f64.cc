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

std::ostream&
cftal::test::operator<<(std::ostream& s, const ulp_stats& us)
{
    s << us._cnt << " cases, with delta: " << us._ulps
      << " rate: " << double(us._ulps)/double(us._cnt) << '\n';
    for (const auto& t : us._devs) {
        s << std::setw(4) << t.first << " "
          << std::setw(16) << t.second << '\n';
    }
    return s;
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
    bool cmp_ulp(_T a, _T b, uint32_t ulp, cftal::test::ulp_stats* us)
    {
        bool r;
        int32_t u=0;
        if ((r=cftal::test::f_eq(a, b)) == false) {
            u=sizeof(_T)*8;
            try {
                u=boost::math::float_distance<_T>(a, b);
            }
            catch (...) {
            }
            if ((u >= -int32_t(ulp)) && (u <= int32_t(ulp)))
                r=true;
        }
        if (us != nullptr)
            us->inc(u);
        return r;
    }
}

bool cftal::test::f_eq_ulp(double a, double b, uint32_t ulp, ulp_stats* us)
{
    return cmp_ulp(a, b, ulp, us);
}

bool cftal::test::f_eq_ulp(float a, float b, uint32_t ulp, ulp_stats* us)
{
    return cmp_ulp(a, b, ulp, us);
}


