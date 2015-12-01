#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/test/f32_f64.h>
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {


        template <class _V>
        int check_cbrt_f64(const _V& v0, double x, bool verbose);

        template <class _V>
        bool check_cbrt_f64(const _V& v0, bool verbose);

    }
}

std::uint64_t as_uint64(double d)
{
    union u_d {
        double _d;
        int64_t _i;
    } t;
    t._d = d;
    return t._i;
}

template <class _V>
int cftal::test::check_cbrt_f64(const _V& v, double x, bool verbose)
{
    double r3(std::cbrt(x));
    _V vx(x);
    _V vr3(cbrt(vx));

    double p3(cftal::math::pow<3>(r3));
    _V vp3(cftal::math::pow<3>(vr3));

    if (!elements_equal(vr3) && !(std::isnan(r3) && all_of(isnan(vr3)))) {
        std::cout << "Invalid vector values for cbrt(" << x << ")\n";
        const int N=sizeof(_V)/sizeof(double);
        union v_d {
            _V _v;
            double _d[sizeof(_V)/sizeof(double)];
        };
        std::cout << std::setprecision(18);
        std::cout << "expected result: " << r3 << std::endl;
        v_d t;
        t._v = vx;
        std::cout << "argument vector\n";
        for (unsigned i=0; i<N; ++i) {            
            std::cout << t._d[i] << std::endl;
        }
        t._v = vr3;
        std::cout << "result vector\n";
        for (unsigned i=0; i<N; ++i) {
            std::cout << t._d[i] << std::endl;
        }
        std::cout << "back multiplication vector\n";
        t._v = vp3;
        for (unsigned i=0; i<N; ++i) {
            std::cout << t._d[i] << std::endl;
        }
        std::exit(3);
    }

    double vr3_0(extract<0>(vr3));
    double vp3_0(extract<0>(vp3));
    int rc(0);
    if (std::fabs(x - vp3_0) > std::fabs(x - p3)) {
        if (verbose==true) {
            std::cerr << "cbrt(" << x << ")= "
                    << vr3_0 << " != expected " << r3 << std::endl;
            std::cerr << vp3_0 << " " << p3 << std::endl;

            std::cerr << std::fabs(x - vp3_0) << " "
                    << std::fabs(x - p3)
                    << std::endl;
            std::cerr << std::hex
                    << std::setw(16 )
                    << as_uint64(vr3_0)
                    << ' '
                    << as_uint64(r3)
                    << std::dec
                    << std::endl;
        }
        rc = -1;
    } else if (std::fabs(x - vp3_0) < std::fabs(x - p3)) {
        rc = 1;
    }
    return rc;
}

template <class _V>
bool cftal::test::check_cbrt_f64(const _V& v, bool verbose)
{
    bool res(true);
    static_cast<void>(v);
    std::cerr << std::setprecision(19)
              << std::scientific;
    int r(0), e(0), f(0);
    int rc;
    for (int i=0; i<1000000; ++i) {
        double x(double(i)*0.01);

        rc=check_cbrt_f64(v, x, verbose);
        switch (rc) {
        case 0:
            ++e; break;
        case 1:
            ++r; break;
        case -1:
            ++f; break;
        }
        rc= check_cbrt_f64(v, -x, verbose);
        switch (rc) {
        case 0:
            ++e; break;
        case 1:
            ++r; break;
        case -1:
            ++f; break;
        }
    }
    rc = check_cbrt_f64(v, 1.0/0.0, verbose);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    rc = check_cbrt_f64(v, -1.0/0.0, verbose);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    rc = check_cbrt_f64(v, +0.0/0.0, verbose);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    rc = check_cbrt_f64(v, -0.0/0.0, verbose);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    std::cout << "r: " << r << " e: " << e << " f: " << f << std::endl;
    res = (r + e) > 10*f;
    return res;
}

int main(int argc, char** argv)
{
    bool rc=true;
    rc &= cftal::test::check_cbrt_f64(cftal::v2f64(), false);
    rc &= cftal::test::check_cbrt_f64(cftal::v4f64(), false);
    rc &= cftal::test::check_cbrt_f64(cftal::v8f64(), false);
    return rc==true ? 0 : 1;
}
