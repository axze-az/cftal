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
#if 1
    static const vf_type exp_mx2_c[28]= {
        // coefficients for exp_mx2 generated by sollya
        // exp(-0^2) * 0x1p64 : +0x8p+61
        +1.8446744073709551616000e+19,
        // exp(-1^2) * 0x1p64 : +0xb.c5ab1b16779cp+59
        +6.7861779012688855040000e+18,
        // exp(-2^2) * 0x1p64 : +0x9.60aadc109e7ap+55
        +3.3786390312696140800000e+17,
        // exp(-3^2) * 0x1p64 : +0x8.167912932a2dp+48
        +2.2765090721736130000000e+15,
        // exp(-4^2) * 0x1p64 : +0xf.1aaddd7742e58p+37
        +2.0759075673363620605469e+12,
        // exp(-5^2) * 0x1p64 : +0xf.451bd22fe197p+24
        +2.5618734618703597784042e+08,
        // exp(-6^2) * 0x1p64 : +0x8.5b61d7eef032p+9
        +4.2787644022629574465100e+03,
        // exp(-7^2) * 0x1p64 : +0x9.e74dcef3c7c28p-10
        +9.6714170039786748894750e-03,
        // exp(-8^2) * 0x1p64 : +0xc.b4ea3990f266p-32
        +2.9585089040578924999682e-09,
        // exp(-9^2) * 0x1p64 : +0x8.d35d756da7e88p-56
        +1.2248042603271035167064e-16,
        // exp(-10^2) * 0x1p64 : +0xd.460f8a7157ae8p-84
        +6.8623289464411634741726e-25,
        // exp(-11^2) * 0x1p64 : +0xa.ce9a6ec52a398p-114
        +5.2034023912599166757855e-34,
        // exp(-12^2) * 0x1p64 : +0x9.86bac991ccc6p-147
        +5.3396689014419052984427e-44,
        // exp(-13^2) * 0x1p64 : +0x9.1774b2fdfe8d8p-183
        +7.4157021960719279649668e-55,
        // exp(-14^2) * 0x1p64 : +0x9.64eb01c7ac688p-222
        +1.3938025972389352836150e-66,
        // exp(-15^2) * 0x1p64 : +0xa.826b922698e4p-264
        +3.5453677858214127316735e-79,
        // exp(-16^2) * 0x1p64 : +0xc.baacab56a74ep-309
        +1.2204847443797099313853e-92,
        // exp(-17^2) * 0x1p64 : +0x8.58a5c0fe328f8p-356
        +5.6860994659006915789175e-107,
        // exp(-18^2) * 0x1p64 : +0xb.d99513c3aa0d8p-407
        +3.5851521042313299768503e-122,
        // exp(-19^2) * 0x1p64 : +0x9.1b93a9791e608p-460
        +3.0592273650942492673237e-138,
        // exp(-20^2) * 0x1p64 : +0xf.286241e026e68p-517
        +3.5328643408332796279706e-155,
        // exp(-21^2) * 0x1p64 : +0xd.a7fe72bb96038p-576
        +5.5214507556250282903107e-173,
        // exp(-22^2) * 0x1p64 : +0xd.521abc9f1df7p-638
        +1.1678591865753221244567e-191,
        // exp(-23^2) * 0x1p64 : +0xe.115a694031de8p-703
        +3.3430186210371604076384e-211,
        // exp(-24^2) * 0x1p64 : +0x8.0ae5d103fed48p-770
        +1.2950846210555070014939e-231,
        // exp(-25^2) * 0x1p64 : +0x9.f4cb70097f71p-841
        +6.7899805925744216537816e-253,
        // exp(-26^2) * 0x1p64 : +0xd.58246e28376p-915
        +4.8178131857026396598073e-275,
        // exp(-27^2) * 0x1p64 : +0x9.ae9bfe3fc4abp-991
        +4.6263918584695643364672e-298,
    };
#else
    // this implementation produces +-1 ulp but is not
    // faithfully rounded    
    vf_type x2l, x2h=base_type::d_ops::two_prod(xc, xc, x2l);
    vf_type sx2h=-x2h;
    vf_type r= base_type::exp_k(sx2h, false);
    // f(x) := e^(x+y);
    // f(x) ~ e^x + e^x y + e^x/2 *y^2
    vf_type rt=r*0x1p104;
    x2l *= rt;
    rt -= x2l;
    r = rt*0x1p-104;
    using fc_t = math::func_constants<double>;
    r= _T::sel(sx2h <= fc_t::exp_lo_zero, vf_type(0), r);
    return r;
#endif
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
    const int _N=2;
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
}


int main(int argc, char** argv)
{
#if 1
    return exp_px2_main(argc, argv) & exp_mx2_main(argc, argv);
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
