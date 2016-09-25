#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/common.h"
#include "cftal/math/func_f64.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include <tuple>
#include <iostream>
#include <iomanip>

namespace cftal {

    namespace math {
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct test_func : public func_core< _FLOAT_T, _TRAITS_T> {
            using base_type = func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = func_common<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;

            static vf_type func(arg_t<vf_type> vf);
        };

        template <typename _T>
        struct test_func<float, _T> : public func_core<float, _T> {
            using base_type = func_core<float, _T>;
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            // using vli_type = typename _T::vli_type;
            // using vi2_type = typename _T::vi2_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            // using vmi2_type = typename _T::vmi2_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef func_core<float, _T> my_type;

            static vf_type func(arg_t<vf_type> vf);

            // return exp(-x^2)
            static
            vf_type
            exp_mx2(arg_t<vf_type> x);

            // return exp(+x^2)
            static
            vf_type
            exp_px2(arg_t<vf_type> x);

            // return exp2(-x^2)
            static
            vf_type
            exp2_mx2(arg_t<vf_type> x);

            // return exp2(+x^2)
            static
            vf_type
            exp2_px2(arg_t<vf_type> x);

            // return exp10(-x^2)
            static
            vf_type
            exp10_mx2(arg_t<vf_type> x);

            // return exp10(+x^2)
            static
            vf_type
            exp10_px2(arg_t<vf_type> x);

        };
    }

    namespace test {

        template <typename _T>
        struct check_func {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::func(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp2(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp(-a*a);
            }
            static
            const char* fname() { return "func"; }
        };

        template <typename _T>
        struct check_exp10_mx2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::exp10_mx2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp10(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return ::exp10(-a*a);
            }
            static
            const char* fname() { return "exp10_mx2"; }
        };

        template <typename _T>
        struct check_exp10_px2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::exp10_px2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                // x = -x;
                mp_t mr;
                int mpres=mpfr_exp10(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return ::exp10(a*a);
            }
            static
            const char* fname() { return "exp10_px2"; }
        };

        template <typename _T>
        struct check_exp2_mx2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::exp2_mx2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp2(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp2(-a*a);
            }
            static
            const char* fname() { return "exp2_mx2"; }
        };

        template <typename _T>
        struct check_exp2_px2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::exp2_px2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                // x = -x;
                mp_t mr;
                int mpres=mpfr_exp2(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp2(a*a);
            }
            static
            const char* fname() { return "exp2_px2"; }
        };


        template <typename _T>
        struct check_exp_px2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::exp_px2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                mp_t mr;
                int mpres=mpfr_exp(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp(a*a);
            }
            static
            const char* fname() { return "exp_px2"; }
        };

        template <typename _T>
        struct check_exp_mx2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::exp_mx2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp(-a*a);
            }
            static
            const char* fname() { return "exp_mx2"; }
        };

    }
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
exp2_mx2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type sx2h=-x2h;
    vf_type r= base_type::exp2_k(sx2h);
    // f(x) := 2^(x+y);
    // f(x) ~ 2^x + 2^x log(2) y
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type rt=r*0x1p48f;
    x2l *= rt;
    x2l *= ctbl::m_ln2.h();
    rt -= x2l;
    r = rt*0x1p-48f;
    using fc_t = math::func_constants<float>;
    r= _T::sel(sx2h <= fc_t::exp2_lo_zero, vf_type(0), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
exp2_px2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type r= base_type::exp2_k(x2h);
    // f(x) := 2^(x+y);
    // f(x) ~ 2^x + 2^x log(2) y
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    x2l *= r;
    x2l *= ctbl::m_ln2.h();
    r += x2l;
    using fc_t = math::func_constants<float>;
    r= _T::sel(x2h >= fc_t::exp2_hi_inf, _T::pinf(), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
exp10_mx2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type sx2h=-x2h;
    vf_type r= base_type::exp10_k(sx2h);
    // f(x) := 10^(x+y);
    // f(x) ~ 10^x + 10^x log(10) y + 1/2 * log(10)*log(10)*10^x y^2
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    const vf_type ln10c=-ctbl::m_ln10.h();
#if 1
    // std::cout << r << std::endl;
    // std::cout << x2l << std::endl;
    // std::cout << base_type::exp10_k(-x2l) << std::endl;
    vf_type rt=r ;// * 0x1p0f;
    vf_type xs=x2l*ln10c;
#if 1
    vf_type e10l = xs;
#else
    vf_type e10l= impl::poly(xs,
                             // 1.0f/720.0f,
                             // 1.0f/120.0f,
                             // 1.0f/24.0f,
                             // 1.0f/6.0f,
                             // 1.0f/2.0f,
                             1.0f) *xs;
#endif
    // std::cout << e10l << std::endl;
    rt += rt*e10l;
    r = rt; //*0x1p-0f;
#else
    vf_type rt=r*0x1p48f;
    x2l *= rt;
    x2l *= ln10c;
    rt -= x2l;
    r = rt*0x1p-48f;
#endif
    using fc_t = math::func_constants<float>;
    r= _T::sel(sx2h <= fc_t::exp10_lo_zero, vf_type(0), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
exp10_px2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type r= base_type::exp10_k(x2h);
    // f(x) := 2^(x+y);
    // f(x) ~ 2^x + 2^x log(2) y
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    x2l *= r;
    x2l *= ctbl::m_ln10.h();
    r += x2l;
    using fc_t = math::func_constants<float>;
    r= _T::sel(x2h >= fc_t::exp10_hi_inf, _T::pinf(), r);
    return r;
}


template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
exp_mx2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type sx2h=-x2h;
    vf_type r= base_type::exp_k(sx2h, false);
    // f(x) := e^(x+y);
    // f(x) ~ e^x + e^x y + e^x/2 *y^2
#if 1
    r -= x2l*r;
#else
    vf_type rt=r*0x1p48f;
    x2l *= rt;
    rt -= x2l;
    r = rt*0x1p-48f;
#endif
    using fc_t = math::func_constants<float>;
    r= _T::sel(sx2h <= fc_t::exp_lo_zero, vf_type(0), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
exp_px2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);

    // std::cout << x2h << std::endl;
    // std::cout << x2l << std::endl;
    using fc_t = math::func_constants<float>;
#if 1
    vmf_type border_case = (x2h == fc_t::exp_hi_inf) &
        (x2l < 0.0);
    // if (any_of(border_case))
    //    std::cout << xc << std::endl;
    vf_type t= 0x1.02p-17;
    x2h = _T::sel(border_case, x2h - t, x2h);
    x2l = _T::sel(border_case, x2l + t, x2l);
    // x2h = _T::sel(border_case, x2h + 2*x2l, x2h);
    // x2l = _T::sel(border_case, -1.88 *x2l, x2l);
#endif
    // std::cout << x2h << std::endl;
    // std::cout << x2l << std::endl;

    vf_type r= base_type::exp_k(x2h, false);
    // f(x) := e^(x+y);
    // f(x) ~ e^x + e^x y + e^x/2 *y^2
    vf_type rt= r*0x1p-48f;
    x2l *= rt;
    rt += x2l;
    r = rt*0x1p48f;
    // std::cout << r << std::endl;
    // std::cout << fc_t::exp_hi_inf << std::endl;
    r= _T::sel(x2h >= fc_t::exp_hi_inf, _T::pinf(), r);
    return r;
}

int exp_px2_main(int argc, char** argv)
{
#if 0
    using namespace cftal;
    using namespace cftal::test;
#if 0
    using traits_t=math::func_traits<vec<float, 1>,
                                     vec<int32_t, 1> >;
    using func_t=math::test_func<float, traits_t>;
#endif
    // return func_t::func(a);
    std::cout << std::setprecision(18)
              << std::hexfloat;
    v1f32 t=9.419280052185058594e+00f;
    v1f32 l=check_exp_px2<float>::v(t);
    auto r=check_exp_px2<float>::r(t());
    std::cout << l << std::endl;
    std::cout << std::get<0>(r) << std::endl;
    return 0;
#else
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=2;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x10000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(0.0, 9.5);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp_px2<float> >::v(st, d, speed_only,
                                             cmp_ulp<float>(ulp, us),
                                             cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}

int exp_mx2_main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x10000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(0.0, 10.2);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp_mx2<float> >::v(st, d, speed_only,
                                               cmp_ulp<float>(ulp, us),
                                               cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int exp2_mx2_main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x10000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(0.0, 12.3);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp2_mx2<float> >::v(st, d, speed_only,
                                                cmp_ulp<float>(ulp, us),
                                                cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int exp2_px2_main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x10000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(0, 11.4);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp2_px2<float> >::v(st, d, speed_only,
                                                cmp_ulp<float>(ulp, us),
                                                cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int exp10_mx2_main(int argc, char** argv)
{
#if 0
    using namespace cftal;
    using namespace cftal::test;
    // return func_t::func(a);
    std::cout << std::setprecision(18)
              << std::hexfloat;
    v1f32 t=6.173537731170654297e+00;
    v1f32 l=check_exp10_mx2<float>::v(t);
    auto r=check_exp10_mx2<float>::r(t());
    std::cout << l << std::endl;
    std::cout << std::get<0>(r) << std::endl;
    return 0;
#else
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x10000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(6.7, 6.8);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp10_mx2<float> >::v(st, d, speed_only,
                                                 cmp_ulp<float>(ulp, us),
                                                 cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}

int exp10_px2_main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x10000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(0, 6.3);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_exp10_px2<float> >::v(st, d, speed_only,
                                                cmp_ulp<float>(ulp, us),
                                                cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}



int main(int argc, char** argv)
{
#if 1
    return
        // exp10_px2_main(argc, argv) +
        // exp10_mx2_main(argc, argv) + // fails
        // exp2_px2_main(argc, argv) +
        // exp2_mx2_main(argc, argv) +
        // exp_px2_main(argc, argv) +
        exp_mx2_main(argc, argv) +
        0;
#else
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=2;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(32.5, 33.0);
    // func_domain<float> d=std::make_pair(1.0, 27);
    // func_domain<float> d=std::make_pair(0.0, 1.0);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        float, _N, check_func<float> >::v(st, d, speed_only,
                                            cmp_ulp<float>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
