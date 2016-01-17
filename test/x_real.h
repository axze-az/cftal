#if !defined (__CFTAL_TEST_X_REAL_H__)
#define __CFTAL_TEST_X_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/call_mpfr.h>
#include <random>
#include <iostream>

namespace cftal {
    namespace test {
        template <template <typename _T> class _X,
                  typename _T,
                  class _R>
        class check_x_real {

            static
            _R make_ref(_X<_T> a);

            static
            bool
            check(_X<_T> res, _R expected, const char* msg);

            static
            bool
            ops(_X<_T> a0, _X<_T> a1);

            static bool ops();

        public:
            static bool v();
        };

        template <template <typename _T> class _X, typename _T>
        struct check_x_real_traits;

        template <>
        struct check_x_real_traits<d_real, double> {
            static
            constexpr double eps() {
                // return std::pow(2, -104);
                return std::ldexp(1.0, -105);
            }

            template <typename _D, typename _RND>
            static
            d_real<double> make_rnd(_D& d, _RND& rnd) {
                double h=d(rnd);
                double l=h*1e-16;
                mpfr_real<128> t=h;
                t += mpfr_real<128>(l);
                double hn= double(t);
                t -= mpfr_real<128>(hn);
                double ln= double(t);
                return d_real<double>(hn, ln);
            }

            constexpr static const bool check_div = true;
        };

        template <>
        struct check_x_real_traits<t_real, double> {
            static
            constexpr double eps() {
                // return std::pow(2, -152);
                return std::ldexp(1.0, -152);
            }

            template <typename _D, typename _RND>
            static
            t_real<double> make_rnd(_D& d, _RND& rnd) {
                double h=d(rnd);
                double m=h*1e-16;
                double l=m*1e-16;
                mpfr_real<192> t=h;
                t += mpfr_real<192>(m);
                t += mpfr_real<192>(l);
                double hn= double(t);
                t -= mpfr_real<192>(hn);
                double mn= double(t);
                t -= mpfr_real<192>(mn);
                double ln= double(t);
                return t_real<double>(hn, mn, ln);
            }

            constexpr static const bool check_div = false;
        };

        template <>
        struct check_x_real_traits<d_real, float> {
            static
            constexpr double eps() {
                // return std::pow(2, -44);
                return std::ldexp(2, -48);
            }
            template <typename _D, typename _RND>
            static
            d_real<float> make_rnd(_D& d, _RND& rnd) {
                float h=d(rnd);
                float l=h*1e-8;
                mpfr_real<64> t=h;
                t += mpfr_real<64>(l);
                float hn= float(t);
                t -= mpfr_real<64>(hn);
                float ln= float(t);
                return d_real<float>(hn, ln);
            }

            constexpr static const bool check_div = true;
        };

        template <>
        struct check_x_real_traits<t_real, float> {
            static
            constexpr double eps() {
                // return std::pow(2, -64);
                return std::ldexp(2, -72);
            }
            template <typename _D, typename _RND>
            static
            t_real<float> make_rnd(_D& d, _RND& rnd) {
                float h=d(rnd);
                float m=h*1e-8;
                float l=m*1e-8;
                mpfr_real<128> t=h;
                t += mpfr_real<128>(m);
                t += mpfr_real<128>(l);
                float hn= float(t);
                t -= mpfr_real<128>(hn);
                float mn= float(t);
                t -= mpfr_real<128>(mn);
                float ln= float(t);
                return t_real<float>(hn, mn, ln);
            }
            constexpr static const bool check_div = false;
        };

    }
}

template <template <typename _T> class _X, class _T, class _R>
_R
cftal::test::check_x_real<_X, _T, _R>::make_ref(_X<_T> a)
{
    _R r = a;
    // _R r= a.h();
    // r+=_R(a.l());
    return r;
}

template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::
check(_X<_T> res, _R expected, const char* msg)
{
    _R rs=make_ref(res);
    bool r=true;
    static const _R eps=check_x_real_traits<_X, _T>::eps();
    if (rel_err(rs, expected) > eps) {
        std::cerr << double(rs) << ' '  << double(expected) << ' '
                  << msg << std::endl;
        std::cerr << "rel_err: " << double(rel_err(rs, expected)) << std::endl;
        std::cerr << "abs_err:" << double(abs_err(rs, expected)) << std::endl;
        r = false;
    }
    return r;
}

template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::
ops(_X<_T> a0, _X<_T> b0)
{
    _R a = make_ref(a0);
    _R b = make_ref(b0);
    _R r;
    _X<_T> va=a0, vb=b0, vr;
    bool rc=true;

    r = -a;
    vr = -va;
    rc &= check(vr, r, "-a");

    r = +a;
    vr = +va;
    rc &= check(vr, r, "+a");

    r = a + b;
    vr = va + vb;
    rc &= check(vr, r, "a+b");

    r = a; r += b;
    vr = va; vr += vb;
    rc &= check(vr, r, "a+=b");

    r = a - b;
    vr = va - vb;
    rc &= check(vr, r, "a-b");

    r = a; r -= b;
    vr = va; vr -= vb;
    rc &= check(vr, r, "a-=b");

    r = a * b;
    vr = va * vb;
    rc &= check(vr, r, "a*b");

    r = a; r *= b;
    vr = va; vr *= vb;
    rc &= check(vr, r, "a*=b");

    if (check_x_real_traits<_X, _T>::check_div == true) {
        r = a / b;
        vr = va / vb;
        rc &= check(vr, r, "a/b");

        r = a; r /= b;
        vr = va; vr /= vb;
        rc &= check(vr, r, "a/=b");
    }

    r = std::max(a, b);
    vr = max(va, vb);
    rc &= check(vr, r, "max");

    r = std::min(a, b);
    vr = min(va, vb);
    rc &= check(vr, r, "min");

    r = a > _R(0) ? a : -a;
    vr = abs(va);
    rc &= check(vr, r, "abs");

    return rc;
}


template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::ops()
{
    static const _T operands[] = {
         _T(4), _T(2),
         _T(-4), _T(-2),
         _T(4), _T(0),
         _T(-4), _T(0),
         _T(0), _T(4),
         _T(0), _T(-4),
         _T(32), _T(21),
         _T(-32), _T(21),
         _T(32), _T(-21),
         _T(-32), _T(-21),
         _T(12), _T(-21),
         _T(-12), _T(21),
         _T(12), _T(21),
         _T(-12), _T(-21)
    };

    bool rc =true;
    for (auto b=std::begin(operands), e=std::end(operands); b!=e; b+=2) {
        rc &= ops(*b, *std::next(b));
        rc &= ops(*std::next(b), *b);
    }
    std::mt19937 rnd;
    std::uniform_real_distribution<_T>
        distrib(0, std::numeric_limits<_T>::max());
    const int64_t N0=0x1000ULL;
    const int64_t N=72*N0;
    for (int64_t i=0; i<N; ++i) {
        if ((i & (N0-1)) == (N0-1))
            std::cout << '.' << std::flush;
        _T ah, bh;
        ah = distrib(rnd);
        bh = distrib(rnd);
        _X<_T> va=check_x_real_traits<_X, _T>::make_rnd(distrib, rnd);
        _X<_T> vb=check_x_real_traits<_X, _T>::make_rnd(distrib, rnd);
        rc &= ops(va, vb);
        va = -ah;
        rc &= ops(va, vb);
        va = ah; vb= -bh;
        rc &= ops(va, vb);
        va = -ah;
        rc &= ops(va, vb);
    }
    std::cout << std::endl;
    if (rc == true) {
        std::cout << __func__ << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << " test failed " << std::endl;
    }
    return rc;
}

template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::v()
{
    return ops();
}


// Local variables:
// mode: c++
// end:
#endif
