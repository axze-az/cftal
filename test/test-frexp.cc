#include <cftal/vec.h>
#include <cftal/test/f32_f64.h>

namespace cftal {

    namespace test {
        template <class _FV, class _IV>
        bool check_frexp(typename _FV::value_type vp,
                         typename _FV::value_type vn);
    
        template <class _FV, class _IV>
        bool check_frexp_f64();

        template <class _FV, class _IV>
        bool check_frexp_f32();
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
    return rc;
}

template <class _FV, class _IV>
bool cftal::test::check_frexp_f64()
{
    // check zero
    double vp = make_double(0, 0, 0);
    check_frexp<_FV, _IV>(vp, -vp);
    vp = make_float(1, 0, 0);
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
    vp = make_float(1, 0, 0);
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

int main()
{
    int rc=true;
    rc &= cftal::test::check_frexp_f64<cftal::v2f64,
                                       cftal::v2s32>();
    rc &= cftal::test::check_frexp_f64<cftal::v4f64,
                                       cftal::v4s32>();
    rc &= cftal::test::check_frexp_f64<cftal::v8f64,
                                       cftal::v8s32>();                                       
    rc &= cftal::test::check_frexp_f32<cftal::v2f32,
                                       cftal::v2s32>();
    rc &= cftal::test::check_frexp_f32<cftal::v4f32,
                                       cftal::v4s32>();
    rc &= cftal::test::check_frexp_f32<cftal::v8f32,
                                       cftal::v8s32>();
    return rc=true ? 0 : 1;
}
