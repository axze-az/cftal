#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math_common.h"
#include "cftal/math_func_f64.h"
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
        struct test_func<double, _T> : public func_core<double, _T> {
            using base_type = func_core<double, _T>;
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            using vmi2_type = typename _T::vmi2_type;
            
            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef func_core<double, _T> my_type;

            static vf_type func(arg_t<vf_type> vf);

            // return exp(-x^2)
            static
            vf_type
            exp_mx2(arg_t<vf_type> x);

            // return exp(+x^2)
            static
            vf_type
            exp_px2(arg_t<vf_type> x);
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
                using func_t=math::test_func<double, traits_t>;
                return func_t::func(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<128>;
                mp_t x=a;
                x *= x;
                // x = -x;
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
            const char* fname() { return "func"; }
        };

        template <typename _T>
        struct check_exp_px2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;   
                using func_t=math::test_func<double, traits_t>;
                return func_t::exp_px2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<128>;
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
                using func_t=math::test_func<double, traits_t>;
                return func_t::exp_mx2(a);
            }
            static
            auto
            r(const _T& a) {
                using mp_t=mpfr_real<128>;
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
                return std::exp(a*a);
            }
            static
            const char* fname() { return "exp_mx2"; }
        };
        
    }
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
func(arg_t<vf_type> xc)
{
    return exp_px2(xc);
}
    
template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
exp_mx2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded    
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type sx2h=-x2h;
    vf_type r= base_type::exp_k(sx2h, false);
    // f(x) := e^(x+y);
    // f(x) ~ e^x + e^x y + e^x/2 *y^2
    vf_type rt=r*0x1p256;
#if 0
    vf_type sx2l=-x2l;
    vf_type c= impl::poly(sx2l,
                          1.0/120,
                          1.0/24,
                          1.0/6,
                          1.0/2,
                          1.0) * sx2l * rt;
    // vf_type c= rt * base_type::exp_k(-x2l, true);
    rt += c;
#else
    x2l *= rt;
    rt -= x2l;
#endif
    r = rt*0x1p-256;
    using fc_t = math::func_constants<double>;
    r= _T::sel(sx2h <= fc_t::exp_lo_zero, vf_type(0), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
exp_px2(arg_t<vf_type> xc)
{
    // this implementation produces +-1 ulp but is not
    // faithfully rounded    
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type r= base_type::exp_k(x2h, false);
    // f(x) := e^(x+y);
    // f(x) ~ e^x + e^x y + e^x/2 *y^2
    x2l *= r;
    r += x2l;
    using fc_t = math::func_constants<double>;
    r= _T::sel(x2h >= fc_t::exp_hi_inf, _T::pinf(), r);
    return r;
}


int exp_px2_main(int argc, char** argv)
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
    }
    func_domain<double> d=std::make_pair(0.0, 26.65);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_exp_px2<double> >::v(st, d, speed_only,
                                               cmp_ulp<double>(ulp, us),
                                               cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int exp_mx2_main(int argc, char** argv)
{
#if 0
    using namespace cftal;
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    // for (int i=0; i<2*28; ++i) {
    v1f64 t=3.0;
    t *= 0.5;
    v1f64 d=check_exp_mx2<double>::v(t);
    double d0=std::get<0>(check_exp_mx2<double>::r(t()));
    std::cout << 1.5 << ' ' << d << std::endl;
    std::cout << 1.5 << ' ' << d0 << std::endl;
    // }
    return 0;
#else
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
    }
    func_domain<double> d=std::make_pair(0.0, 27.4);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_exp_mx2<double> >::v(st, d, speed_only,
                                               cmp_ulp<double>(ulp, us),
                                               cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}


int main(int argc, char** argv)
{
#if 1
    return /* exp_px2_main(argc, argv) & */ exp_mx2_main(argc, argv);
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
    func_domain<double> d=std::make_pair(0.0, 26.65);
    // func_domain<double> d=std::make_pair(1.0, 27);
    // func_domain<double> d=std::make_pair(0.0, 1.0);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        double, _N, check_exp_mx2<double> >::v(st, d, speed_only,
                                               cmp_ulp<double>(ulp, us),
                                               cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
#endif
}
