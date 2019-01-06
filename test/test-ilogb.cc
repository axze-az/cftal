//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/vec.h>
#include <cftal/test/f32_f64.h>
#include <cstring>
#include <iomanip>

namespace cftal {

    namespace test {
        template <class _FV, class _IV>
        bool check_ilogb(typename _FV::value_type vp,
                         typename _FV::value_type vn);

        template <class _FV, class _IV>
        bool check_ilogb_f64();

        template <class _FV, class _IV>
        bool check_ilogb_f32();
    }

}

template <class _FV, class _IV>
bool cftal::test::check_ilogb(typename _FV::value_type vp,
                              typename _FV::value_type vm)
{
    using real_type = typename _FV::value_type;

    const int FN=sizeof(_FV)/sizeof(real_type);
    union v_d {
        _FV _v;
        real_type _d[FN];
        v_d() { std::memset(_d, 0, sizeof(_d)); }
    };

    using int_type = typename _IV::value_type;
    const int IN=sizeof(_IV)/sizeof(int_type);
    union v_i {
        _IV _v;
        int_type _i[IN];
        v_i() { std::memset(_i, 0, sizeof(_i)); }
    };

    v_d arg;

    for (int i=0; i<FN; i+=2) {
        arg._d[i]= vp;
        arg._d[i+1] = vm;
    }

    int_type e_ref[FN];

    for (int i=0; i<FN; ++i)
        e_ref[i] = std::ilogb(arg._d[i]);

    v_i e;
    e._v = ilogb(arg._v);

    bool rc(true);

    for (int i=0; i<FN; ++i) {
        int_type e_i= e._i[i];
        int_type ref_e_i= e_ref[i];
        if (e_i != ref_e_i) {
            std::cout << "ilogb(" << arg._d[i] << ")= "
                      << e_i
                      << std::endl
                      << "expect: "
                      << ref_e_i
                      << std::endl;
            rc= false;
        }
    }
#if 0
    if (!rc)
        std::exit(3);
#endif
    return rc;
}

template <class _FV, class _IV>
bool cftal::test::check_ilogb_f64()
{
    bool rc=true;
    // check zero
    double vp = make_double(0, 0, 0);
    rc &= check_ilogb<_FV, _IV>(vp, -vp);
    vp = make_double(1, 0, 0);
    rc &= check_ilogb<_FV, _IV>(vp, -vp);
    // check +- inf
    rc &= check_ilogb<_FV, _IV>(make_double(0, 0x7FF, 0),
                                make_double(1, 0x7FF, 0));
    // check +-nan
    for (int i=0; i<53; ++i) {
        uint64_t sig= uint64_t(1) << i;
        rc &= check_ilogb<_FV, _IV>(make_double(0, 0x7FF, sig),
                                    make_double(1, 0x7FF, sig));
    }
    // denormals and normals
    for (int e=0; e<=0x7ff; ++e) {
        for (int i=0; i<52; ++i) {
            uint64_t sig= uint64_t(1) << i;
            vp = make_double(0, e, sig);
            rc &= check_ilogb<_FV, _IV>(vp, -vp);
        }
    }
    return rc;
}

template <class _FV, class _IV>
bool cftal::test::check_ilogb_f32()
{
    bool rc= true;
    // check zero
    float vp = make_float(0, 0, 0);
    rc &= check_ilogb<_FV, _IV>(vp, -vp);
    vp = make_float(1, 0, 0);
    rc &= check_ilogb<_FV, _IV>(vp, -vp);
    // check +- inf
    rc &= check_ilogb<_FV, _IV>(make_float(0, 0xFF, 0),
                                make_float(1, 0xFF, 0));
    // check +-nan
    for (int i=0; i<23; ++i) {
        uint64_t sig= uint64_t(1) << i;
        rc &= check_ilogb<_FV, _IV>(make_float(0, 0x7FF, sig),
                                    make_float(1, 0x7FF, sig));
    }
    // denormals and normals
    for (int e=0; e<=0x7ff; ++e) {
        for (int i=0; i<23; ++i) {
            uint32_t sig= uint32_t(1) << i;
            vp = make_float(0, e, sig);
            rc &=  check_ilogb<_FV, _IV>(vp, -vp);
        }
    }
    return rc;
}

int main()
{
    int rc=true;
    std::cout << std::setprecision(20);
    std::cout << "testing ilogb v2f64" << std::endl;
    rc &= cftal::test::check_ilogb_f64<cftal::v2f64,
                                       cftal::v2s32>();
    std::cout << "testing ilogb v4f64" << std::endl;
    rc &= cftal::test::check_ilogb_f64<cftal::v4f64,
                                       cftal::v4s32>();
    std::cout << "testing ilogb v8f64" << std::endl;
    rc &= cftal::test::check_ilogb_f64<cftal::v8f64,
                                       cftal::v8s32>();
#if 0
    std::cout << "testing ilogb v2f32" << std::endl;
    rc &= cftal::test::check_ilogb_f32<cftal::v2f32,
                                       cftal::v2s32>();
#endif
    std::cout << "testing ilogb v4f32" << std::endl;
    rc &= cftal::test::check_ilogb_f32<cftal::v4f32,
                                       cftal::v4s32>();
    std::cout << "testing ilogb v8f32" << std::endl;
    rc &= cftal::test::check_ilogb_f32<cftal::v8f32,
                                       cftal::v8s32>();
    return rc==true ? 0 : 1;
}
