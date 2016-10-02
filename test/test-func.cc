#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/elem_func.h"
#include "cftal/math/elem_func_core_f64.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>

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
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            // using vli_type = typename _T::vli_type;
            // using vi2_type = typename _T::vi2_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            // using vmi2_type = typename _T::vmi2_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef elem_func_core<double, _T> my_type;

            static vf_type func(arg_t<vf_type> vf);

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
#if 1 
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_erfc, &i);
                return std::make_tuple(v, i.first, i.second);                
#else
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp2(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
#endif
            }
            static
            _T
            s(const _T& a) {
                return std::erfc(a);
            }
            static
            const char* fname() { return "func"; }
        };



    }
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::func(arg_t<vf_type> xc)
{
#if 0
    const int _N=sizeof(vf_type)/sizeof(double);
    union t {
        double _d[_N];
        vf_type _v;
    } x, y;
    x._v= xc;
    for (int i=0; i<_N; ++i) {
        y._d[i]=boost::math::erfc(x._d[i]);
    }
    vf_type r=y._v;
    return r;
#else
    vf_type x=abs(xc);
    struct erfc_data {
        bool _calculated;
        vf_type _expmxx;
        vf_type _1_plus_2_x;
        vf_type _f;
        constexpr erfc_data() : _calculated(false),
                                _expmxx(0.0), _1_plus_2_x(0) {}
        void
        operator()(vf_type x) {
            if (_calculated == true)
                return;
            _expmxx = base_type::exp_mx2_k(x);
            // _1_plus_2_x= 1 + 2*x;
            _f = _expmxx;
        };
        vf_type
        operator()() const {
            return _f;
        }
    };

    erfc_data ef;

    auto i0=[x]()->vf_type {
        // [3.4694469519536141888238489627838134765625e-18, 0.75] : | p - f | <= 2^-60.71875
        // coefficients for erfc_i0 generated by sollya
        // x^0 : +0x8p-3
        const vf_type erfc_i0_c0=+1.0000000000000000000000e+00;
        // x^1 : -0x9.06eba8214db68p-3
        const vf_type erfc_i0_c1=-1.1283791670955125585607e+00;
        // x^3 : +0xc.093a3581bcdf8p-5
        const vf_type erfc_i0_c3=+3.7612638903183531757790e-01;
        // x^5 : -0xe.71790d020896p-7
        const vf_type erfc_i0_c5=-1.1283791670945636509416e-01;
        // x^7 : +0xd.c167189014758p-9
        const vf_type erfc_i0_c7=+2.6866170643224867448096e-02;
        // x^9 : -0xa.b2de67b63691p-11
        const vf_type erfc_i0_c9=-5.2239776039429159509853e-03;
        // x^11 : +0xe.016d76ef4a11p-14
        const vf_type erfc_i0_c11=+8.5483255292173967489211e-04;
        // x^13 : -0xf.cd1371bbf2558p-17
        const vf_type erfc_i0_c13=-1.2055265766965315976916e-04;
        // x^15 : +0xf.a609a2cfb581p-20
        const vf_type erfc_i0_c15=+1.4923653157630001249998e-05;
        // x^17 : -0xd.c6d41ecbe4bf8p-23
        const vf_type erfc_i0_c17=-1.6423075436226438355598e-06;
        // x^19 : +0xa.a8395922ecd18p-26
        const vf_type erfc_i0_c19=+1.5880353844048938806551e-07;
        // x^21 : -0xc.1a4926aa7611p-30
        const vf_type erfc_i0_c21=-1.1271497883150963258877e-08;
        vf_type xx= x*x;
        vf_type y_i0=impl::poly(xx,
                                erfc_i0_c21,
                                erfc_i0_c19,
                                erfc_i0_c17,
                                erfc_i0_c15,
                                erfc_i0_c13,
                                erfc_i0_c11,
                                erfc_i0_c9,
                                erfc_i0_c7,
                                erfc_i0_c5,
                                erfc_i0_c3);
        vf_type ye;
        impl::eft_poly(y_i0, ye, xx, y_i0,
                       erfc_i0_c1);
        impl::eft_poly_si(y_i0, ye, x, y_i0, ye,
                          erfc_i0_c0);
        y_i0 += ye;
        return y_i0;
    };
    auto i1=[x, &ef]()->vf_type {
    // [0.75, 1.625] : | p - f | <= 2^-55.09375
    // coefficients for erfc_i1 generated by sollya
    // x^0 h: +0xa.1130b17deeea8p-6
    const vf_type erfc_i1_c0h=+1.5729920705028513361334e-01;
    // x^0 l: -0xf.eb591d612bd78p-60
    const vf_type erfc_i1_c0l=-1.3807816464325810368603e-17;
    // x^1 : -0xd.488f84b7de16p-5
    const vf_type erfc_i1_c1=-4.1510749742059505074110e-01;
    // x^2 : +0xd.488f84b7de718p-5
    const vf_type erfc_i1_c2=+4.1510749742060520928177e-01;
    // x^3 : -0x8.db0a587a8f15p-6
    const vf_type erfc_i1_c3=-1.3836916580679431421075e-01;
    // x^4 : -0x8.db0a587b83fep-7
    const vf_type erfc_i1_c4=-6.9184582905137348429747e-02;
    // x^5 : +0x8.db0a5879ab44p-7
    const vf_type erfc_i1_c5=+6.9184582901778424179895e-02;
    // x^6 : -0x9.722d27c1b8bfp-11
    const vf_type erfc_i1_c6=-4.6123054273404778119483e-03;
    // x^7 : -0xf.84b7eea18108p-10
    const vf_type erfc_i1_c7=-1.5154718341706036044414e-02;
    // x^8 : +0x9.c889e52f31528p-11
    const vf_type erfc_i1_c8=+4.7770283762466380153566e-03;
    // x^9 : +0xf.718be3122d998p-13
    const vf_type erfc_i1_c9=+1.8851978462117279910365e-03;
    // x^10 : -0xa.0baea58d7518p-13
    const vf_type erfc_i1_c10=-1.2262736385496679492046e-03;
    // x^11 : -0xb.3a9e2a94811ap-17
    const vf_type erfc_i1_c11=-8.5670287526270355333430e-05;
    // x^12 : +0xd.201e7ab22627p-16
    const vf_type erfc_i1_c12=+2.0027870295588823734353e-04;
    // x^13 : -0x9.90ee0ff72732p-19
    const vf_type erfc_i1_c13=-1.8245949827978827557408e-05;
    // x^14 : -0xd.9dfbe1c36d308p-19
    const vf_type erfc_i1_c14=-2.5972604108049477967266e-05;
    // x^15 : +0x9.8ea388af838cp-20
    const vf_type erfc_i1_c15=+9.1144398018969352516169e-06;
    // x^16 : -0xc.5cc4b7f19cb9p-24
    const vf_type erfc_i1_c16=-7.3685507098203703418816e-07;
    // x^ : +0xcp-4
    const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
    // x^ : +0x8p-3
    const vf_type erfc_i1_x0=+1.0000000000000000000000e+00;
        vf_type xr= x - erfc_i1_x0;
        
        vf_type y_i1= impl::poly(xr,
                                 erfc_i1_c16,
                                 erfc_i1_c15,
                                 erfc_i1_c14,
                                 erfc_i1_c13,
                                 erfc_i1_c12,
                                 erfc_i1_c11,
                                 erfc_i1_c10,
                                 erfc_i1_c9,
                                 erfc_i1_c8,
                                 erfc_i1_c7,
                                 erfc_i1_c6,
                                 erfc_i1_c5,
                                 erfc_i1_c4);
        vf_type ye;
        impl::eft_poly(y_i1, ye, xr, y_i1, 
                                 erfc_i1_c3,
                       erfc_i1_c2,
                       erfc_i1_c1, 
                       erfc_i1_c0h);
        ye += erfc_i1_c0l;
        y_i1 += ye;
        return y_i1;
    };

    auto i2=[x, &ef]()->vf_type {
        // [1.875, 3.5] : | p - f | <= 2^-61.90625
        // coefficients for erfc_i2 generated by sollya
        // x^0 h: +0x8.33f40e9d72a2p-11
        const vf_type erfc_i2_c0h=+4.0053431472924540257541e-03;
        // x^0 l: +0x9.1bf1ccb7e27fp-66
        const vf_type erfc_i2_c0l=+1.2345211550514282013483e-19;
        // x^1 : -0x9.3155c4028323p-9
        const vf_type erfc_i2_c1=-1.7954521347979722489807e-02;
        // x^2 : +0x9.5a5d850dd558p-8
        const vf_type erfc_i2_c2=+3.6535115226646097674745e-02;
        // x^3 : -0xb.27ecea03b6c3p-8
        const vf_type erfc_i2_c3=-4.3577963955352891356476e-02;
        // x^4 : +0x8.3b98bb29e81p-8
        const vf_type erfc_i2_c4=+3.2159372038137457039397e-02;
        // x^5 : -0xd.6ac90b3e50af8p-10
        const vf_type erfc_i2_c5=-1.3102666198009314466044e-02;
        // x^6 : +0xa.35ad2d3e7b4c8p-15
        const vf_type erfc_i2_c6=+3.1157451529737753082375e-04;
        // x^7 : +0xc.09472a2fb1e18p-12
        const vf_type erfc_i2_c7=+2.9385356783504248089078e-03;
        // x^8 : -0xc.cb04aa156263p-13
        const vf_type erfc_i2_c8=-1.5616503812164047280964e-03;
        // x^9 : +0x8.d554b89e9eebp-16
        const vf_type erfc_i2_c9=+1.3478582752178444549226e-04;
        // x^10 : +0xe.997e807ca53p-16
        const vf_type erfc_i2_c10=+2.2277201104488591337782e-04;
        // x^11 : -0xd.b1840fc65e268p-17
        const vf_type erfc_i2_c11=-1.0447251396493544277778e-04;
        // x^12 : +0xd.f3f6787d9bd7p-23
        const vf_type erfc_i2_c12=+1.6633247845068352241307e-06;
        // x^13 : +0xe.f15ba81d24eap-20
        const vf_type erfc_i2_c13=+1.4250569172068282676556e-05;
        // x^14 : -0x9.4c5a96e14db1p-21
        const vf_type erfc_i2_c14=-4.4337545796250801339493e-06;
        // x^15 : -0xf.5bb28c6c21638p-25
        const vf_type erfc_i2_c15=-4.5770982457040160565004e-07;
        // x^16 : +0x8.ac7f217d817f8p-24
        const vf_type erfc_i2_c16=+5.1699965372001071763915e-07;
        // x^17 : +0x8.1109caca39b08p-28
        const vf_type erfc_i2_c17=+3.0050261565760021652852e-08;
        // x^18 : -0x8.ec44c6e3c9158p-26
        const vf_type erfc_i2_c18=-1.3296193558590645276267e-07;
        // x^19 : +0x8.b656c792ed678p-27
        const vf_type erfc_i2_c19=+6.4911407615191319781432e-08;
        // x^20 : -0x9.4699f6e92ba68p-29
        const vf_type erfc_i2_c20=-1.7277499310222299800160e-08;
        // x^21 : +0xc.07c3b7c2c7b3p-32
        const vf_type erfc_i2_c21=+2.8010295161204299998322e-09;
        // x^22 : -0x8.fb7eb0fccf6dp-35
        const vf_type erfc_i2_c22=-2.6142230218687706855659e-10;
        // x^23 : +0xb.e2b6c1ea60f08p-40
        const vf_type erfc_i2_c23=+1.0809891280474724393940e-11;
        // x^ : +0xfp-3
        const vf_type erfc_i2_left=+1.8750000000000000000000e+00;
        // x^ : +0x8.23b4fp-2
        const vf_type erfc_i2_x0=+2.0348699092864990234375e+00;

        vf_type x_i2 = x - erfc_i2_x0;
        vf_type y_i2= impl::poly(x_i2,
                                 erfc_i2_c23,
                                 erfc_i2_c22,
                                 erfc_i2_c21,
                                 erfc_i2_c20,
                                 erfc_i2_c19,
                                 erfc_i2_c18,
                                 erfc_i2_c17,
                                 erfc_i2_c16,
                                 erfc_i2_c15,
                                 erfc_i2_c14,
                                 erfc_i2_c13,
                                 erfc_i2_c12,
                                 erfc_i2_c11,
                                 erfc_i2_c10);
        vf_type ye;
        impl::eft_poly(y_i2, ye, x_i2, y_i2,
                       erfc_i2_c9,
                       erfc_i2_c8,
                       erfc_i2_c7,
                       erfc_i2_c6,
                       erfc_i2_c5,
                       erfc_i2_c4,
                       erfc_i2_c3,
                       erfc_i2_c2,
                       erfc_i2_c1,
                       erfc_i2_c0h);
        y_i2 += ye +erfc_i2_c0l;
        return y_i2;
    };

#if 0
    auto i4=[x, &expmxx]()->vf_type {
        // [16, 27.5] : | p - f | <= 2^-64.75
        // coefficients for erfc_i1 generated by sollya
        // x^0 h: +0xd.44648e2f65a78p-9
        const vf_type erfc_i1_c0h=+2.5912420612893168753166e-02;
        // x^0 l: -0xe.40dfcdad23fep-65
        const vf_type erfc_i1_c0l=-3.8633958687429383394176e-19;
        // x^1 : -0x9.bd3df45a7ae6p-13
        const vf_type erfc_i1_c1=-1.1888704346597498903715e-03;
        // x^2 : +0xe.48ac08cd2d85p-18
        const vf_type erfc_i1_c2=+5.4488659043608054827375e-05;
        // x^3 : -0xa.76b3295d48518p-22
        const vf_type erfc_i1_c3=-2.4947336408499828137202e-06;
        // x^4 : +0xf.507c925fbe178p-27
        const vf_type erfc_i1_c4=+1.1410117756138507899834e-07;
        // x^5 : -0xb.31fe4cf61153p-31
        const vf_type erfc_i1_c5=-5.2132115558101667806995e-09;
        // x^6 : +0x8.2cf5eac61e41p-35
        const vf_type erfc_i1_c6=+2.3794207363782838080994e-10;
        // x^7 : -0xb.edb7e5c3351dp-40
        const vf_type erfc_i1_c7=-1.0848986951998424797101e-11;
        // x^8 : +0x8.b176760bc7578p-44
        const vf_type erfc_i1_c8=+4.9415199459871791329908e-13;
        // x^9 : -0xc.a86218ecc0688p-49
        const vf_type erfc_i1_c9=-2.2484675182999015691024e-14;
        // x^10 : +0x9.34ab5f42f421p-53
        const vf_type erfc_i1_c10=+1.0220424430062766230130e-15;
        // x^11 : -0xd.607706e4fabb8p-58
        const vf_type erfc_i1_c11=-4.6410154215663817748747e-17;
        // x^12 : +0x9.b57b2d85e1f3p-62
        const vf_type erfc_i1_c12=+2.1052844351590252850989e-18;
        // x^13 : -0xe.132b35748f99p-67
        const vf_type erfc_i1_c13=-9.5375083591136594297948e-20;
        // x^14 : +0xa.3202142a56d48p-71
        const vf_type erfc_i1_c14=+4.3178962312698204272509e-21;
        // x^15 : -0xe.d8370544d48cp-76
        const vf_type erfc_i1_c15=-1.9646650679929372862725e-22;
        // x^16 : +0xa.b9bed46efd288p-80
        const vf_type erfc_i1_c16=+8.8719819760051011610255e-24;
        // x^17 : -0xe.5d9ec6bf3a6f8p-85
        const vf_type erfc_i1_c17=-3.7134474443742943181956e-25;
        // x^18 : +0xa.672576c192468p-89
        const vf_type erfc_i1_c18=+1.6806816281050232658047e-26;
        // x^19 : -0xb.6e79b86d56238p-93
        const vf_type erfc_i1_c19=-1.1542910443371632508712e-27;
        // x^20 : +0x8.2b85fb8aaa248p-97
        const vf_type erfc_i1_c20=+5.1560031829121269346255e-29;
        // x^ : +0x8p+1
        const vf_type erfc_i1_left=+1.6000000000000000000000e+01;
        // x^ : +0xa.ep+1
        const vf_type erfc_i1_x0=+2.1750000000000000000000e+01;
        vf_type xx=x-erfc_i1_x0;
        vf_type y_i1= impl::poly(xx,
                                 erfc_i1_c20,
                                 erfc_i1_c19,
                                 erfc_i1_c18,
                                 erfc_i1_c17,
                                 erfc_i1_c16,
                                 erfc_i1_c15,
                                 erfc_i1_c14,
                                 erfc_i1_c13,
                                 erfc_i1_c12,
                                 erfc_i1_c11,
                                 erfc_i1_c10,
                                 erfc_i1_c9,
                                 erfc_i1_c8,
                                 erfc_i1_c7,
                                 erfc_i1_c6,
                                 erfc_i1_c5,
                                 erfc_i1_c4,
                                 erfc_i1_c3,
                                 erfc_i1_c2,
                                 erfc_i1_c1);
        y_i1 *=xx;
        y_i1 +=erfc_i1_c0l;
        // y_i1 +=erfc_i1_c0h;
        if (expmxx.first == false) {
            expmxx.first =true;
            expmxx.second =expxx_k(x, -1.0);
        }
        y_i1 *= expmxx.second;
        return y_i1;
    };
#endif

    auto s01=[x, i0, i1]()->vf_type {
        // x^ : +0xcp-4
        const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
        vf_type r=select_branch(x < erfc_i1_left, i0, i1);
        return r;
    };

    auto s12=[x, s01, i2]()->vf_type {
        // x^ : +0xfp-3
        const vf_type erfc_i2_left=+1.6250000000000000000000e+00;
        vf_type r=select_branch(x < erfc_i2_left, s01, i2);
        return r;
    };

    vf_type y=s12();
    return y;
#endif
    
    return x;
}

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=256;
    const int _N=1;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = double;
    
    func_domain<ftype> d=std::make_pair(0.75, 1.625);
    // func_domain<float> d=std::make_pair(1.0, 27);
    // func_domain<float> d=std::make_pair(0.0, 1.0);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_func<ftype> >::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
