//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/elem_func.h"
#include "cftal/math/elem_func_core_f64.h"
#include "cftal/math/elem_func_core_f32.h"
#include "cftal/math/impl_estrin.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>


/*
    floatn cos(floatn x);
    floatn exp(floatn x); +
    floatn exp2(floatn x); +
    floatn exp10(floatn x); +
    floatn log(floatn x); +
    floatn log2(floatn x); +
    floatn log10(floatn x); +
    floatn recip(floatn x);
    floatn rsqrt(floatn x);
    floatn sin(floatn x);
    floatn sqrt(floatn x);
    floatn tan(floatn x);
    floatn divide(floatn x, floatn y);
    floatn powr(floatn x, floatn y);
 */

#define EXP 1

namespace cftal {

    namespace math {
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct test_func : public elem_func_core< _FLOAT_T, _TRAITS_T> {
            using base_type = elem_func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = test_func<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;

            static vf_type func(arg_t<vf_type> vf);
        };

        template <typename _T>
        struct test_func<double, _T> : public elem_func_core<double, _T> {
            using base_type = elem_func_core<double, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<double, _T>;

            using d_ops = typename base_type::d_ops;

            // static vf_type func_k(arg_t<vf_type> vf);

            using base_type::ilogbp1_k;
            using base_type::ldexp_k;
            using base_type::pow_k;

            static
            vf_type
            erfc_k(arg_t<vf_type> xc);

            static
            vf_type
            erfc(arg_t<vf_type> xc);

        };

        template <typename _T>
        struct test_func<float, _T> : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<float, _T>;

            using d_ops = typename base_type::d_ops;

            using base_type::ilogbp1;
            using base_type::ldexp;
            using base_type::__reduce_exp_arg;
            using base_type::__scale_exp_k;
            using base_type::__exp_k;

        };
    }


    namespace test {

        template <typename _T>
        struct check_erfc {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::erfc(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_erfc, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::erfc(a);
            }
            static
            const char* fname() { return "erfc"; }
        };

    }
}


template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
erfc_k(arg_t<vf_type> xc)
{
#if 0
    i=[1/6.0, 1/26.5];
    deg=25;
    f=exp(1/x*1/x)*1/x*erfc(1/x);
    // efl=chebyshevform(f, deg, i);
    // p=efl[0];
    b=[|0, ..., deg|];
    c= [|D, D...|];
    p=fpminimax(f, b, c, i, relative, floating);
    write_approx_prec(p, f, i);
    write_coeffs(p, "const double erfc_asymp_c", "erfc", b, c);
    plot(log(abs(p(x)-f(x))), i, postscriptfile, "erfc-i-n-f64");
    implementpoly(p, i, 0x1p-52, D, "erfc_i_n", "erfc_i_n.c");

   // [3.77358496189117431640625e-2, 0.16666667163372039794921875] : | p - f | <= 2^-101.6875
    // coefficients for erfc generated by sollya
    // x^0 : +0xe.041533479aap-69
    const double erfc_asymp_c0=+2.3743940317925883256152e-20;
    // x^1 : +0x9.06eba8214db68p-4
    const double erfc_asymp_c1=+5.6418958354775627928035e-01;
    // x^2 : +0xa.97f936d8ef2f8p-53
    const double erfc_asymp_c2=+1.1761310212006589757065e-15;
    // x^3 : -0x9.06eba82151bap-5
    const double erfc_asymp_c3=-2.8209479177399221505596e-01;
    // x^4 : +0x8.a3885e085f808p-40
    const double erfc_asymp_c4=+7.8569424204930442613894e-12;
    // x^5 : +0xd.8a617bf9b78e8p-5
    const double erfc_asymp_c5=+4.2314218725162949796825e-01;
    // x^6 : +0x8.fe4e213135a1p-29
    const double erfc_asymp_c6=+1.6751475006263012686794e-08;
    // x^7 : -0x8.767d37e15cbcp-3
    const double erfc_asymp_c7=-1.0578560224199389239175e+00;
    // x^8 : +0xf.be22be33c275p-20
    const double erfc_asymp_c8=+1.5013425479661801138125e-05;
    // x^9 : +0xe.cf01b9a9c5528p-2
    const double erfc_asymp_c9=+3.7021550187940470699743e+00;
    // x^10 : +0xd.2e891742a6ebp-11
    const double erfc_asymp_c10=+6.4364156936167118278069e-03;
    // x^11 : -0x8.61dca4ccaa028p+1
    const double erfc_asymp_c11=-1.6764546012815134901075e+01;
    // x^12 : +0xb.454b9ccff2c48p-3
    const double erfc_asymp_c12=+1.4088356257401264404194e+00;
    // x^13 : +0x9.69134ff61d73p+3
    const double erfc_asymp_c13=+7.5283607464497976025086e+01;
    // x^14 : +0xa.19f9ce4612f1p+4
    const double erfc_asymp_c14=+1.6162348773358013431789e+02;
    // x^15 : -0xf.4233242db54fp+7
    const double erfc_asymp_c15=-1.9530998853954147307377e+03;
    // x^16 : +0x9.6b57e8d304a8p+10
    const double erfc_asymp_c16=+9.6453735854669066611677e+03;
    // x^17 : -0xc.f456750c635d8p+12
    const double erfc_asymp_c17=-5.3061403576267381140497e+04;
    // x^18 : +0x8.ae077b19b089p+15
    const double erfc_asymp_c18=+2.8441974043037102092057e+05;
    // x^19 : -0x9.017e9855f6808p+17
    const double erfc_asymp_c19=-1.1804131901233794633299e+06;
    // x^20 : +0xd.c2c8c70103p+18
    const double erfc_asymp_c20=+3.6073311094367504119873e+06;
    // x^21 : -0xf.6e18b3fc71798p+19
    const double erfc_asymp_c21=-8.0897976245658276602626e+06;
    // x^22 : +0xc.87313a5a7581p+20
    const double erfc_asymp_c22=+1.3136659647084716707468e+07;
    // x^23 : -0xe.1ced01bed0a88p+20
    const double erfc_asymp_c23=-1.4798544109085710719228e+07;
    // x^24 : +0x9.f6b1d56944268p+20
    const double erfc_asymp_c24=+1.0447645338199758902192e+07;
    // x^25 : -0xd.628743c2912b8p+18
    const double erfc_asymp_c25=-3.5087650587504315190017e+06;
#endif
    // [3.77358496189117431640625e-2, 0.16666667163372039794921875] : | p - f | <= 2^-92.75
    // coefficients for erfc generated by sollya
    // x^0 : +0x9.06eba8214db68p-4
    const double erfc_asymp_c0=+5.6418958354775627928035e-01;
    // x^1 : +0xa.d309b817b8928p-52
    const double erfc_asymp_c1=+2.4034923055980369429805e-15;
    // x^2 : -0x9.06eba8215a488p-5
    const double erfc_asymp_c2=-2.8209479177423540940950e-01;
    // x^3 : +0x9.36cca8b4b7e38p-38
    const double erfc_asymp_c3=+3.3520556275564863958090e-11;
    // x^4 : +0xd.8a617aff9279p-5
    const double erfc_asymp_c4=+4.2314218543158610419397e-01;
    // x^5 : +0xf.039283c5bc488p-27
    const double erfc_asymp_c5=+1.1186267724223785066351e-07;
    // x^6 : -0x8.767f3c7ea87c8p-3
    const double erfc_asymp_c6=-1.0578598714974403183220e+00;
    // x^7 : +0x9.2331dbae4f078p-16
    const double erfc_asymp_c7=+1.3942687262978633168202e-04;
    // x^8 : +0xe.cba62b70a1688p-2
    const double erfc_asymp_c8=+3.6988760745519830841488e+00;
    // x^9 : +0x9.f92e7a744621p-7
    const double erfc_asymp_c9=+7.7916917602622454142036e-02;
    // x^10 : -0x9.088396194d2c8p+1
    const double erfc_asymp_c10=-1.8066515695909718175471e+01;
    // x^11 : +0xa.ae2a986491fa8p+1
    const double erfc_asymp_c11=+2.1360674904924923822591e+01;
    // x^12 : -0xb.719b78661a19p+4
    const double erfc_asymp_c12=-1.8310045661815235007452e+02;
    // x^13 : +0xb.b40e94d9ae8f8p+8
    const double erfc_asymp_c13=+2.9960569587756322107452e+03;
    // x^14 : -0xd.d1c3d8b8d87dp+11
    const double erfc_asymp_c14=-2.8302120205328777956311e+04;
    // x^15 : +0xd.3d2298ef926f8p+14
    const double erfc_asymp_c15=+2.1690464935139470617287e+05;
    // x^16 : -0xa.e47b13f91a558p+17
    const double erfc_asymp_c16=-1.4277021560395162086934e+06;
    // x^17 : +0xf.1ec48661b9108p+19
    const double erfc_asymp_c17=+7.9273321994290659204125e+06;
    // x^18 : -0x8.b38112da1ab88p+22
    const double erfc_asymp_c18=-3.6495428712992556393147e+07;
    // x^19 : +0x8.32d2ca9bb59dp+24
    const double erfc_asymp_c19=+1.3754849060823994874954e+08;
    // x^20 : -0xc.73a4b4b62ebd8p+25
    const double erfc_asymp_c20=-4.1781079342330139875412e+08;
    // x^21 : +0xe.e167c974e276p+26
    const double erfc_asymp_c21=+9.9861277382632207870483e+08;
    // x^22 : -0xd.797649555ce1p+27
    const double erfc_asymp_c22=-1.8085115626675877571106e+09;
    // x^23 : +0x8.affe34aa6d0f8p+28
    const double erfc_asymp_c23=+2.3320256746516261100769e+09;
    // x^24 : -0xe.34f5625090a9p+27
    const double erfc_asymp_c24=-1.9068137145176587104797e+09;
    // x^25 : +0xb.115f19ac59a2p+26
    const double erfc_asymp_c25=+7.4275133469297075271606e+08;
    vf_type ea, eal;
    vf_type inv_x=1.0/xc;
    ea=horner(inv_x,
                      erfc_asymp_c25,
                      erfc_asymp_c24,
                      erfc_asymp_c23,
                      erfc_asymp_c22,
                      erfc_asymp_c21,
                      erfc_asymp_c20,
                      erfc_asymp_c19,
                      erfc_asymp_c18,
                      erfc_asymp_c17,
                      erfc_asymp_c16,
                      erfc_asymp_c15,
                      erfc_asymp_c14,
                      erfc_asymp_c13,
                      erfc_asymp_c12,
                      erfc_asymp_c11,
                      erfc_asymp_c10,
                      erfc_asymp_c9,
                      erfc_asymp_c8,
                      erfc_asymp_c7,
                      erfc_asymp_c6,
                      erfc_asymp_c5,
                      erfc_asymp_c4,
                      erfc_asymp_c3,
                erfc_asymp_c2,
                erfc_asymp_c1,
                erfc_asymp_c0);

    vf_type x2h, x2l;
    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, xc, -xc);
    } else {
        d_ops::sqr12(x2h, x2l, xc);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type xrh, xrl, kf;
    auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
    vf_type exl, ex= base_type::__pow_exp_k(xrh, xrl, kf, k, &exl);
    d_ops::mul122(ea, eal, ea, ex, exl);
    dvf_type t(ea, eal);
    t = d_ops::sloppy_div(t, xc);
    return t.h()+t.l();
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
erfc(arg_t<vf_type> x)
{
    vf_type r=erfc_k(x);
    // using fc=func_constants<_FLOAT_T>;
    // r = _TRAITS_T::sel(x < -fc::erf_lt_one_fin, -1.0, r);
    // r = _TRAITS_T::sel(x > fc::erf_lt_one_fin, 1.0, r);
    r = _T::sel(x == 0, 1.0, r);
    r = _T::sel(isnan(x), x, r);
    return r;
}

int main_erfc(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=32;
    const int _N=8;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<double> d=std::make_pair(6.0, 26.75);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        double, _N, check_erfc<double> >::v(st, d, speed_only,
                                            cmp_ulp<double>(ulp, us),
                                            cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char**argv)
{
    int r=0;
    // r |= main_cosh(argc, argv);
    r |= main_erfc(argc, argv);
    // r |= main_tanh(argc, argv);
    return r;
}
