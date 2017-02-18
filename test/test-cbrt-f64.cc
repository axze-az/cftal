//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cmath>
#include <cftal/vec.h>
#include <cftal/math/func.h>
#include <cftal/math/misc.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/of_math_funcs.h>
#include <cftal/test/check_cbrt.h>
#include <limits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstring>

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
            v_d() { std::memset(_d, 0, sizeof(_d)); }
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

namespace cftal {
    double xcbrt(double x);

    template <typename _T, unsigned _N>
    _T nth_root_guess(_T x);

}

template <typename _T, unsigned _N>
_T
cftal::nth_root_guess(_T x)
{
    // a * 1 + b = 1
    // a * 2^(-_N) + b = 0.5
    // a = 1 - b
    // (1-b)*2^(-_N) + b = 0.5
    // 2^(-_N) - b * 2^(-_N) + b = 0.5
    // b (1-2^(-_N)) = 0.5 - 2^(-_N)
    // b= (0.5-2^(-_N))/(1-2^(-_N))
    const _T two_pow_n= _T(1 << _N);
    const _T two_pow_minus_n = _T(1.0)/two_pow_n;
    const _T b= (0.5-two_pow_minus_n)/(1-two_pow_minus_n);
    const _T a= 1.0 -b;
    return a * x + b;
}


double
cftal::xcbrt(double x)
{
    double xp=std::abs(x);
    int32_t e;
    // m in [0.5, 1)
    double m=std::frexp(xp, &e);
    divisor<int32_t, int32_t> idiv3(3);
    int32_t e3= e / idiv3;
    int32_t r3= remainder(e, 3, e3);
    // select r3c so that r3c [-2,-1,0]
    int32_t r3c= select(r3 > 0, r3-3, r3);
    int32_t e3c= select(r3 > 0, e3+1, e3);
    // mm in [0.125, 1) => m * 2 ^[-2,-1.0]
    double mm=std::ldexp(m, r3c);
    double mm0= mm;
    // intial guess:
    // a * 1 + b = 1
    // a * 0.125 + b = 0.5
    // a = 1 - b
    // (1-b)*0.125 + b = 0.5
    // 0.125 - b * 0.125 + b = 0.5
    // b (1-0.125) = 0.5 - 0.125
    // b= (0.5-0.125)/(1-0.125)
    // const double a= 0.571428571428571;
    // const double b= 0.428571428571429;
    const double b= (0.5-0.125)/(1-0.125);
    const double a= 1.0 -b;
    mm= a * mm + b;
    // newton raphson steps
    const uint32_t _N = 4;
    for (uint32_t i=0; i<_N; ++i) {
#if 1
        double ipow2= mm * mm;
        double en= mm0 - mm * ipow2;
        double den= 3* ipow2;
        mm = mm + en/den;
#else
        mm = (2.0/3.0) * mm + (1.0/3.0) * mm0 / (mm*mm);
#endif
    }
    // scale back
    double res=std::ldexp(mm, e3c);
    // restore sign
    res=std::copysign(res, x);
    return res;
}

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        std::cout << "f64 test\n"<<std::scientific;
        rc &= check_cbrt_f64(cftal::v1f64(), false);
        rc &= check_cbrt_f64(cftal::v2f64(), false);
        rc &= check_cbrt_f64(cftal::v4f64(), false);
        rc &= check_cbrt_f64(cftal::v8f64(), false);
    }
    func_domain<double> dd=std::make_pair(-std::numeric_limits<double>::max(),
                                          std::numeric_limits<double>::max());
    auto us=std::make_shared<ulp_stats>();
    exec_stats d_st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_cbrt<double> >::v(d_st, dd, speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << d_st << std::endl;
    return rc==true ? 0 : 1;
}
