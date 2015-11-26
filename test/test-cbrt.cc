#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/test/f32_f64.h>
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {

        template <class _FV, class _IV>
        bool check_frexp(typename _FV::value_type vp,
                         typename _FV::value_type vn);

        template <class _FV, class _IV>
        bool check_frexp_f64();

        template <class _FV, class _IV>
        bool check_frexp_f32();

        template <class _V>
        int check_cbrt_f64(const _V& v0, double x);

        template <class _V>
        bool check_cbrt_f64(const _V& v0);

    }
}


template <class _FV, class _IV>
bool cftal::test::check_frexp(typename _FV::value_type vp,
                              typename _FV::value_type vm)
{
    using real_type = typename _FV::value_type;

    const int FN=sizeof(_FV)/sizeof(real_type);
    union v_d {
        _FV _v;
        real_type _d[FN];
    };

    using int_type = typename _IV::value_type;
    const int IN=sizeof(_IV)/sizeof(int_type);
    union v_i {
        _IV _v;
        int_type _i[IN];
    };

    v_d arg;

    for (int i=0; i<FN; i+=2) {
        arg._d[i]= vp;
        arg._d[i+1] = vm;
    }

    real_type ref[FN];
    int_type e_ref[FN];

    for (int i=0; i<FN; ++i)
        ref[i] = std::frexp(arg._d[i], &e_ref[i]);

    v_d res;
    v_i e;
    res._v = frexp(arg._v, &e._v);

    bool rc(true);

    for (int i=0; i<FN; ++i) {
        real_type r_i= res._d[i];
        real_type ref_i = ref[i];
        int_type e_i= e._i[i];
        int_type ref_e_i= e_ref[i];
        if (!f_eq(r_i, ref_i) || e_i != ref_e_i) {
            std::cout << "frexp(" << arg._d[i] << ")="
                      << r_i << " exp= " << e_i
                      << std::endl
                      << "expect: "
                      << ref_i << " exp= " << ref_e_i
                      << std::endl;
            rc= false;
        }
    }
    if (!rc)
        std::exit(3);
    return true;
}

template <class _FV, class _IV>
bool cftal::test::check_frexp_f64()
{
    // check zero
    double vp = make_double(0, 0, 0);
    check_frexp<_FV, _IV>(vp, -vp);
    // check +- inf
    check_frexp<_FV, _IV>(make_double(0, 0x7FF, 0),
                          make_double(1, 0x7FF, 0));
    // check +-nan
    for (int i=0; i<53; ++i) {
        uint64_t sig= uint64_t(1) << i;
        check_frexp<_FV, _IV>(make_double(0, 0x7FF, sig),
                              make_double(1, 0x7FF, sig));
    }
    // denormals and normals
    for (int e=0; e<=0x7ff; ++e) {
        for (int i=0; i<52; ++i) {
            uint64_t sig= uint64_t(1) << i;
            vp = make_double(0, e, sig);
            check_frexp<_FV, _IV>(vp, -vp);
        }
    }
    return true;
}

template <class _FV, class _IV>
bool cftal::test::check_frexp_f32()
{
    // check zero
    float vp = make_float(0, 0, 0);
    check_frexp<_FV, _IV>(vp, -vp);
    // check +- inf
    check_frexp<_FV, _IV>(make_float(0, 0xFF, 0),
                          make_float(1, 0xFF, 0));
    // check +-nan
    for (int i=0; i<23; ++i) {
        uint64_t sig= uint64_t(1) << i;
        check_frexp<_FV, _IV>(make_float(0, 0x7FF, sig),
                              make_float(1, 0x7FF, sig));
    }
    // denormals and normals
    for (int e=0; e<=0x7ff; ++e) {
        for (int i=0; i<23; ++i) {
            uint32_t sig= uint32_t(1) << i;
            vp = make_float(0, e, sig);
            check_frexp<_FV, _IV>(vp, -vp);
        }
    }
    return true;
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
int cftal::test::check_cbrt_f64(const _V& v, double x)
{
    double r3(std::cbrt(x));
    _V vx(x);
    _V vr3(cbrt(vx));

    double p3(cftal::math::pow<3>(r3));
    _V vp3(cftal::math::pow<3>(vr3));

    if (!elements_equal(vr3)) {
        std::cerr << "Invalid vector values\n";
        std::cout << "Invalid vector values\n";
        const int N=sizeof(_V)/sizeof(double);
        union v_d {
            _V _v;
            double _d[sizeof(_V)/sizeof(double)];
        };
        std::cout << std::setprecision(18);
        std::cout << x << std::endl;
        std::cout << r3 << std::endl;
        v_d t;
        t._v = vx;
        for (unsigned i=0; i<N; ++i) {
            std::cout << t._d[i] << std::endl;
        }
        t._v = vr3;
        for (unsigned i=0; i<N; ++i) {
            std::cout << t._d[i] << std::endl;
        }

        t._v = vp3;
        for (unsigned i=0; i<N; ++i) {
            std::cout << t._d[i] << std::endl;
        }


        // std::exit(3);
    }

    double vr3_0(extract<0>(vr3));
    double vp3_0(extract<0>(vp3));
    int rc(0);
    if (std::fabs(x - vp3_0) > std::fabs(x - p3)) {
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
        rc = -1;
    } else if (std::fabs(x - vp3_0) < std::fabs(x - p3)) {
        rc = 1;
    }
    return rc;
}

template <class _V>
bool cftal::test::check_cbrt_f64(const _V& v)
{
    bool res(true);
    static_cast<void>(v);
    std::cerr << std::setprecision(19)
              << std::scientific;
    int r(0), e(0), f(0);
    int rc;
    for (int i=0; i<1000000; ++i) {
        double x(double(i)*0.01);

        rc=check_cbrt_f64(v, x);
        switch (rc) {
        case 0:
            ++e; break;
        case 1:
            ++r; break;
        case -1:
            ++f; break;
        }
        rc= check_cbrt_f64(v, -x);
        switch (rc) {
        case 0:
            ++e; break;
        case 1:
            ++r; break;
        case -1:
            ++f; break;
        }
    }
    rc = check_cbrt_f64(v, 1.0/0.0);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    rc = check_cbrt_f64(v, -1.0/0.0);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    rc = check_cbrt_f64(v, +0.0/0.0);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    rc = check_cbrt_f64(v, -0.0/0.0);
    switch (rc) {
    case 0:
        ++e; break;
    case 1:
        ++r; break;
    case -1:
        ++f; break;
    }
    std::cout << "r: " << r << " e: " << e << " f: " << f << std::endl;
    return res;
}


bool all_tests_04()
{
    cftal::test::check_frexp_f64<cftal::v2f64,
                                 cftal::v2s32>();
    cftal::test::check_frexp_f64<cftal::v4f64,
                                 cftal::v4s32>();
    cftal::test::check_frexp_f64<cftal::v4f32,
                                 cftal::v4s32>();
    cftal::test::check_frexp_f64<cftal::v8f32,
                                 cftal::v8s32>();
    cftal::test::check_cbrt_f64(cftal::v2f64());
    cftal::test::check_cbrt_f64(cftal::v4f64());
    return true;
}

int main(int argc, char** argv)
{
    return all_tests_04()==true ? 0 : 3;
}
