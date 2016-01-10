#include <cftal/test/call_mpfr.h>

double
cftal::test::call_mpfr::func(double a, f1_t f)
{
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(r, 53);
    // mpfr_t ai, r;
    // mpfr_init2(ai, 53);
    // mpfr_init2(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    f(r, ai, GMP_RNDN);
    double dr=mpfr_get_d(r, GMP_RNDN);
    // mpfr_clear(ai);
    // mpfr_clear(r);
    return dr;
}

double
cftal::test::call_mpfr::func(double a, double b, f2_t f)
{
    MPFR_DECL_INIT(ai, 53);
    MPFR_DECL_INIT(bi, 53);
    MPFR_DECL_INIT(r, 53);
    // mpfr_t ai, bi, r;
    // mpfr_init2(ai, 53);
    // mpfr_init2(bi, 53);
    // mpfr_init2(r, 53);
    mpfr_set_d(ai, a, GMP_RNDN);
    mpfr_set_d(bi, b, GMP_RNDN);
    f(r, ai, bi, GMP_RNDN);
    double dr=mpfr_get_d(r, GMP_RNDN);
    // mpfr_clear(ai);
    // mpfr_clear(bi);
    // mpfr_clear(r);
    return dr;
}
