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
#include "cftal/test/mpfr_cache.h"
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
            erfc_k_0(arg_t<vf_type> xc);

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
    // erfc(-x) = 2 - erfc(x)

    vf_type x= abs(xc);
    vmf_type x_le_0_75 = x <= 0.75;
    vmf_type x_gt_0_75 = x > 0.75;
    vmf_type x_gt_2_75 = x > 2.75;
    vmf_type x_gt_6_00 = x > 6.0;

    vmf_type x_in_i1 = x_gt_0_75 & (x <= 2.75);
    vmf_type x_in_i2 = x_gt_2_75 & (x <= 6.0);
    // vmf_type x_in_i12 = x_in_i1 | x_in_i2;
    vmf_type x_in_i3 = x_gt_6_00;

    vf_type exl=0, exh=0;

    vf_type i0h=0, i0l=0, i123h=0, i123l=0;
    vf_type x2h;
    if (any_of(x_gt_0_75)) {
        vf_type x2l;
        if (d_real_traits<vf_type>::fma==true) {
            d_ops::mul12(x2h, x2l, x, -x);
        } else {
            d_ops::sqr12(x2h, x2l, x);
            x2h = -x2h;
            x2l = -x2l;
        }
        vf_type xrh, xrl, kf;
        auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
        exh= base_type::__pow_exp_k(xrh, xrl, kf, k, &exl);
        x2h = -x2h;
    } else {
        x2h = x*x;
    }
    if (any_of(x_le_0_75)) {
        // [0, 0.75] : | p - f | <= 2^-60.390625
        // coefficients for erfc_i0 generated by sollya
        // x^0 : +0x8p-3
        const double erfc_i0_c0=+1.0000000000000000000000e+00;
        // x^1 : -0x9.06eba8214db68p-3
        const double erfc_i0_c1=-1.1283791670955125585607e+00;
        // x^3 : +0xc.093a3581bce68p-5
        const double erfc_i0_c3=+3.7612638903183609473402e-01;
        // x^5 : -0xe.71790d020f3d8p-7
        const double erfc_i0_c5=-1.1283791670950364671722e-01;
        // x^7 : +0xd.c16718928048p-9
        const double erfc_i0_c7=+2.6866170644325892968851e-02;
        // x^9 : -0xa.b2de682cab02p-11
        const double erfc_i0_c9=-5.2239776174096731742313e-03;
        // x^11 : +0xe.016d91f9d4358p-14
        const double erfc_i0_c11=+8.5483265129694446706615e-04;
        // x^13 : -0xf.cd175e0e4e63p-17
        const double erfc_i0_c13=-1.2055311438229345476734e-04;
        // x^15 : +0xf.a668a8978d9c8p-20
        const double erfc_i0_c15=+1.4925035918168110094070e-05;
        // x^17 : -0xd.ccaced61432dp-23
        const double erfc_i0_c17=-1.6450302196342027448580e-06;
        // x^19 : +0xa.e1fcd27acc17p-26
        const double erfc_i0_c19=+1.6216582075372502191930e-07;
        // x^21 : -0xe.a495e1208ac98p-30
        const double erfc_i0_c21=-1.3637274483397783432589e-08;
        // x^23 : +0xc.6f15790af88ap-34
        const double erfc_i0_c23=+7.2374948063438535431235e-10;

        i0h = horner(x2h,
                     erfc_i0_c23,
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
        horner_comp_quick(i0h, i0l, x2h, i0h, erfc_i0_c1);
        d_ops::mul122(i0h, i0l, x, i0h, i0l);
        d_ops::add122(i0h, i0l, erfc_i0_c0, i0h, i0l);
    }
    if (any_of(x_gt_0_75)) {
        vf_type i1h=0, i1l=0, i2h=0, i2l=0, i3h=0, i3l=0;
        if (any_of(x_in_i1)) {
            // [0.75, 2.75] : | p - f | <= 2^-59.140625
            // coefficients for erfc_i1 generated by sollya
            // x^0 h: +0xe.9ab8ed1eb334p-5
            const vf_type erfc_i1_c0h=+4.5638700783238173031009e-01;
            // x^0 l: +0xa.d84458027608p-60
            const vf_type erfc_i1_c0l=+9.4063583688085847229697e-18;
            // x^1 : +0xe.491a04c8c74cp-7
            const vf_type erfc_i1_c1=+1.1160588487251243972054e-01;
            // x^2 : -0xa.2f2e2cef14d4p-7
            const vf_type erfc_i1_c2=-7.9564830723177437654670e-02;
            // x^3 : +0xc.04e45b228aecp-8
            const vf_type erfc_i1_c3=+4.6949646234263731070513e-02;
            // x^4 : -0xc.81f3181aaca28p-9
            const vf_type erfc_i1_c4=-2.4428936664969275877057e-02;
            // x^5 : +0xb.d768c57589a98p-10
            const vf_type erfc_i1_c5=+1.1563908626507723650945e-02;
            // x^6 : -0xa.63b9b4a1478e8p-11
            const vf_type erfc_i1_c6=-5.0730236290837090254446e-03;
            // x^7 : +0x8.8d49ff8862c7p-12
            const vf_type erfc_i1_c7=+2.0878687432960901446122e-03;
            // x^8 : -0xd.52c57361f90b8p-14
            const vf_type erfc_i1_c8=-8.1319124504336786751074e-04;
            // x^9 : +0x9.e2cbf3c4e126p-15
            const vf_type erfc_i1_c9=+3.0169447521813798178403e-04;
            // x^10 : -0xe.0bb151c7a8528p-17
            const vf_type erfc_i1_c10=-1.0715999168492641908674e-04;
            // x^11 : +0x9.977b7170369bp-18
            const vf_type erfc_i1_c11=+3.6589536066079111453590e-05;
            // x^12 : -0xc.a2ab8ebd56438p-20
            const vf_type erfc_i1_c12=-1.2050085316536611183716e-05;
            // x^13 : +0x8.0ccdcd4bed6b8p-21
            const vf_type erfc_i1_c13=+3.8385464136067494822307e-06;
            // x^14 : -0x9.f2c8b4ede0f7p-23
            const vf_type erfc_i1_c14=-1.1859387209455998480028e-06;
            // x^15 : +0xb.f40aca445959p-25
            const vf_type erfc_i1_c15=+3.5623579156227751425936e-07;
            // x^16 : -0xd.ee6cf0d2c7e4p-27
            const vf_type erfc_i1_c16=-1.0379664453424312714811e-07;
            // x^17 : +0xf.68af910b030dp-29
            const vf_type erfc_i1_c17=+2.8701366732499267312170e-08;
            // x^18 : -0xf.378a81de6765p-31
            const vf_type erfc_i1_c18=-7.0859478803687918441900e-09;
            // x^19 : +0xc.09f239228b7b8p-33
            const vf_type erfc_i1_c19=+1.4015068628896234563066e-09;
            // x^20 : -0xc.ee9ba8cd582ap-36
            const vf_type erfc_i1_c20=-1.8818627975554374952333e-10;
            // x^21 : +0xd.a3aa20852e5p-40
            const vf_type erfc_i1_c21=+1.2404884439545507477160e-11;
            // x^ : +0xcp-4
            // const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
            // x^ : +0x9.c061p-3
            const vf_type erfc_i1_x0=+1.2189350128173828125000e+00;
            vf_type x_i1 = x - erfc_i1_x0;
#if 1
            vf_type x_i1_sqr= x_i1* x_i1;
            vf_type e= horner(x_i1_sqr,
                              erfc_i1_c21,
                              erfc_i1_c19,
                              erfc_i1_c17,
                              erfc_i1_c15,
                              erfc_i1_c13,
                              erfc_i1_c11,
                              erfc_i1_c9);
            vf_type o= horner(x_i1_sqr,
                              erfc_i1_c20,
                              erfc_i1_c18,
                              erfc_i1_c16,
                              erfc_i1_c14,
                              erfc_i1_c12,
                              erfc_i1_c10,
                              erfc_i1_c8);
            i1h = horner(x_i1, e, o,
                         erfc_i1_c7, erfc_i1_c6,
                         erfc_i1_c5, erfc_i1_c4,
                         erfc_i1_c3, erfc_i1_c2, erfc_i1_c1);
#else
            i1h = horner(x_i1, 
                         erfc_i1_c21,
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
#endif
            i1h *= x_i1;
            d_ops::add122cond(i1h, i1l, i1h, erfc_i1_c0h, erfc_i1_c0l);
        }
        if (any_of(x_in_i2)) {
            // [2.75, 6] : | p - f | <= 2^-60.78125
            // coefficients for erfc_i2 generated by sollya
            // x^0 h: +0x8.b6be4ee0e3cf8p-4
            const vf_type erfc_i2_c0h=+5.4461508571533900902040e-01;
            // x^0 l: -0xf.671435e10336p-60
            const vf_type erfc_i2_c0l=-1.3359671127367542122339e-17;
            // x^1 : +0xa.16d74869fa14p-10
            const vf_type erfc_i2_c1=+9.8527563045483629311505e-03;
            // x^2 : -0xe.d301c034b6d9p-12
            const vf_type erfc_i2_c2=-3.6192005530161991747051e-03;
            // x^3 : +0x9.6ff24eeab773p-13
            const vf_type erfc_i2_c3=+1.1520130713824016342739e-03;
            // x^4 : -0xa.ffdc08a0d9bd8p-15
            const vf_type erfc_i2_c4=-3.3567661126348403250949e-04;
            // x^5 : +0xc.08d7ee8566bap-17
            const vf_type erfc_i2_c5=+9.1816290715132132822102e-05;
            // x^6 : -0xc.887d80312e89p-19
            const vf_type erfc_i2_c6=-2.3905115107495057615462e-05;
            // x^7 : +0xc.883cc02440b08p-21
            const vf_type erfc_i2_c7=+5.9758076571828292662702e-06;
            // x^8 : -0xc.1a3be6d993c6p-23
            const vf_type erfc_i2_c8=-1.4427276287414592112544e-06;
            // x^9 : +0xb.55dd7bd65fcp-25
            const vf_type erfc_i2_c9=+3.3782156776389365591615e-07;
            // x^10 : -0xa.5477bd400695p-27
            const vf_type erfc_i2_c10=-7.6964140505220350364034e-08;
            // x^11 : +0x9.2e98812edf9dp-29
            const vf_type erfc_i2_c11=+1.7102834835369625553510e-08;
            // x^12 : -0xf.f3fc9d2840758p-32
            const vf_type erfc_i2_c12=-3.7143643321806636143601e-09;
            // x^13 : +0xd.90ea70083d63p-34
            const vf_type erfc_i2_c13=+7.8964962357884016169953e-10;
            // x^14 : -0xb.5034a2ead7708p-36
            const vf_type erfc_i2_c14=-1.6463022864863182286291e-10;
            // x^15 : +0x9.48326e811c72p-38
            const vf_type erfc_i2_c15=+3.3767790322690686244921e-11;
            // x^16 : -0xf.008d0c171947p-41
            const vf_type erfc_i2_c16=-6.8221889750437386369149e-12;
            // x^17 : +0xb.b4c57a7769f08p-43
            const vf_type erfc_i2_c17=+1.3308338431005692045565e-12;
            // x^18 : -0x8.3d69a3d340728p-45
            const vf_type erfc_i2_c18=-2.3419184991537750722353e-13;
            // x^19 : +0x9.44ce323295aap-48
            const vf_type erfc_i2_c19=+3.2929290592266954093199e-14;
            // x^20 : -0xd.fddde3facf0bp-52
            const vf_type erfc_i2_c20=-3.1067741781483397623413e-15;
            // x^21 : +0xa.3910a3ae7e2p-56
            const vf_type erfc_i2_c21=+1.4187137779577336243611e-16;
            // x^ : +0xbp-2
            // const vf_type erfc_i2_left=+2.7500000000000000000000e+00;
            // x^ : +0xe.6c9f6p-2
            const vf_type erfc_i2_x0=+3.6060767173767089843750e+00;
            vf_type x_i2 = x - erfc_i2_x0;
#if 1
            vf_type x_i2_sqr= x_i2* x_i2;
            vf_type e= horner(x_i2_sqr,
                              erfc_i2_c21,
                              erfc_i2_c19,
                              erfc_i2_c17,
                              erfc_i2_c15,
                              erfc_i2_c13,
                              erfc_i2_c11,
                              erfc_i2_c9,
                              erfc_i2_c7,
                              erfc_i2_c5,
                              erfc_i2_c3);
            vf_type o= horner(x_i2_sqr,
                              erfc_i2_c20,
                              erfc_i2_c18,
                              erfc_i2_c16,
                              erfc_i2_c14,
                              erfc_i2_c12,
                              erfc_i2_c10,
                              erfc_i2_c8,
                              erfc_i2_c6,
                              erfc_i2_c4,
                              erfc_i2_c2);
            i2h = horner(x_i2, e, o, erfc_i2_c1);
#else
            i2h = horner(x_i2, 
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
                         erfc_i2_c10,
                         erfc_i2_c9,
                         erfc_i2_c8,
                         erfc_i2_c7,
                         erfc_i2_c6,
                         erfc_i2_c5,
                         erfc_i2_c4,
                         erfc_i2_c3,
                         erfc_i2_c2,
                         erfc_i2_c1);
#endif
            i2h *= x_i2;
            d_ops::add122cond(i2h, i2l, i2h, erfc_i2_c0h, erfc_i2_c0l);
        }
        if (any_of(x_in_i3)) {
            // [3.6697246134281158447265625e-2, 0.16666667163372039794921875] : | p - f | <= 2^-92.125
            // coefficients for erfc generated by sollya
            // x^0 : +0x9.06eba8214db68p-4
            const double erfc_i3_c0=+5.6418958354775627928035e-01;
            // x^1 : +0xa.f92535989c79p-52
            const double erfc_i3_c1=+2.4365451922245938660534e-15;
            // x^2 : -0x9.06eba8215aap-5
            const double erfc_i3_c2=-2.8209479177424512386096e-01;
            // x^3 : +0x9.95dd9557213bp-38
            const double erfc_i3_c3=+3.4871526963839179975749e-11;
            // x^4 : +0xd.8a617aef4f97p-5
            const double erfc_i3_c4=+4.2314218531326985850427e-01;
            // x^5 : +0xf.ff517b44d421p-27
            const double erfc_i3_c5=+1.1918944909655141650019e-07;
            // x^6 : -0x8.767f6a5356d1p-3
            const double erfc_i3_c6=-1.0578602129633982720236e+00;
            // x^7 : +0x9.f403d11a91298p-16
            const double erfc_i3_c7=+1.5187352355840402925134e-04;
            // x^8 : +0xe.cb46be56c001p-2
            const double erfc_i3_c8=+3.6985120525787360534764e+00;
            // x^9 : +0xb.16181dfe9c908p-7
            const double erfc_i3_c9=+8.6611761709012316523548e-02;
            // x^10 : -0x9.1e7f2b6dc93a8p+1
            const double erfc_i3_c10=-1.8238255909544438537750e+01;
            // x^11 : +0xc.185e70965c288p+1
            const double erfc_i3_c11=+2.4190382073801007578595e+01;
            // x^12 : -0xd.e384db7ff99f8p+4
            const double erfc_i3_c12=-2.2221993589391965429058e+02;
            // x^13 : +0xd.7b5d7b665fe7p+8
            const double erfc_i3_c13=+3.4513651641830574590131e+03;
            // x^14 : -0x8.0013b33a31c48p+12
            const double erfc_i3_c14=-3.2769231256670384027530e+04;
            // x^15 : +0xf.7df0afac028ep+14
            const double erfc_i3_c15=+2.5382017155460349749774e+05;
            // x^16 : -0xc.d8dd1176d6d2p+17
            const double erfc_i3_c16=-1.6838981364391827955842e+06;
            // x^17 : +0x8.f9fc5603a2518p+20
            const double erfc_i3_c17=+9.4125493758872207254171e+06;
            // x^18 : -0xa.66ddd2a2f023p+22
            const double erfc_i3_c18=-4.3628404659119173884392e+07;
            // x^19 : +0x9.deafb38cd5c6p+24
            const double erfc_i3_c19=+1.6558891555013692378998e+08;
            // x^20 : -0xf.18369669d6f98p+25
            const double erfc_i3_c20=-5.0649015682687300443649e+08;
            // x^21 : +0x9.145a63c860018p+27
            const double erfc_i3_c21=+1.2186304302617194652557e+09;
            // x^22 : -0x8.45df7864a3c3p+28
            const double erfc_i3_c22=-2.2207507262899808883667e+09;
            // x^23 : +0xa.bad0fb0fef79p+28
            const double erfc_i3_c23=+2.8802456809959650039673e+09;
            // x^24 : -0x8.d2241011fd07p+28
            const double erfc_i3_c24=-2.3678323211242742538452e+09;
            // x^25 : +0xd.d03fb0fdd546p+26
            const double erfc_i3_c25=+9.2700640396614217758179e+08;
            vf_type inv_x=1.0/x;
            vf_type inv_x2= inv_x*inv_x;
            vf_type e=horner(inv_x2,
                             erfc_i3_c25,
                             erfc_i3_c23,
                             erfc_i3_c21,
                             erfc_i3_c19,
                             erfc_i3_c17,
                             erfc_i3_c15,
                             erfc_i3_c13,
                             erfc_i3_c11,
                             erfc_i3_c9,
                             erfc_i3_c7,
                             erfc_i3_c5,
                             erfc_i3_c3);
            vf_type o=horner(inv_x2,
                             erfc_i3_c24,
                             erfc_i3_c22,
                             erfc_i3_c20,
                             erfc_i3_c18,
                             erfc_i3_c16,
                             erfc_i3_c14,
                             erfc_i3_c12,
                             erfc_i3_c10,
                             erfc_i3_c8,
                             erfc_i3_c6,
                             erfc_i3_c4,
                             erfc_i3_c2);
            i3h = horner(inv_x, e, o, erfc_i3_c1);
            i3h *= inv_x;
            d_ops::add12cond(i3h, i3l, i3h, erfc_i3_c0);
        }
        i123h = _T::sel(x_gt_2_75, i2h, i1h);
        i123l = _T::sel(x_gt_2_75, i2l, i1l);
        i123h = _T::sel(x_gt_6_00, i3h, i123h);
        i123l = _T::sel(x_gt_6_00, i3l, i123l);
        // multiply with e^(-x^2)
        d_ops::mul22(i123h, i123l, i123h, i123l, exh, exl);
        // divide by x
        dvf_type t(i123h, i123l);
        dvf_type r = d_ops::sloppy_div(t, x);
        i123h = r.h();
        i123l = r.l();
    }
    vmf_type x_lt_0_00 = xc < 0.0;
    vf_type ih= _T::sel(x_le_0_75, i0h, i123h);
    if (any_of(x_lt_0_00)) {
        vf_type il= _T::sel(x_le_0_75, i0l, i123l);
        vf_type nih, nil;
        d_ops::add122cond(nih, nil, 2.0, -ih, -il);
        ih = _T::sel(x_lt_0_00, nih, ih);
    }
    return ih;
}

template <typename _T>
inline
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::
erfc_k_0(arg_t<vf_type> xc)
{
    // erfc(-x) = 2 - erfc(x)

    vf_type x= abs(xc);
    vmf_type x_le_0_75 = x <= 0.75;
    vmf_type x_gt_0_75 = x > 0.75;
    vmf_type x_gt_2_75 = x > 2.75;
    vmf_type x_gt_6_00 = x > 6.0;

    vmf_type x_in_i1 = x_gt_0_75 & (x <= 2.75);
    vmf_type x_in_i2 = x_gt_2_75 & (x <= 6.0);
    // vmf_type x_in_i12 = x_in_i1 | x_in_i2;
    vmf_type x_in_i3 = x_gt_6_00;

    vf_type exl=0, exh=0;

    vf_type i0h=0, i0l=0, i123h=0, i123l=0;
    vf_type x2h;
    if (any_of(x_gt_0_75)) {
        vf_type x2l;
        if (d_real_traits<vf_type>::fma==true) {
            d_ops::mul12(x2h, x2l, x, -x);
        } else {
            d_ops::sqr12(x2h, x2l, x);
            x2h = -x2h;
            x2l = -x2l;
        }
        vf_type xrh, xrl, kf;
        auto k=base_type::__reduce_exp_arg(xrh, xrl, kf, x2h, x2l);
        exh= base_type::__pow_exp_k(xrh, xrl, kf, k, &exl);
        x2h = -x2h;
    } else {
        x2h = x*x;
    }
    if (any_of(x_le_0_75)) {
        // [0, 0.75] : | p - f | <= 2^-60.390625
        // coefficients for erfc_i0 generated by sollya
        // x^0 : +0x8p-3
        const double erfc_i0_c0=+1.0000000000000000000000e+00;
        // x^1 : -0x9.06eba8214db68p-3
        const double erfc_i0_c1=-1.1283791670955125585607e+00;
        // x^3 : +0xc.093a3581bce68p-5
        const double erfc_i0_c3=+3.7612638903183609473402e-01;
        // x^5 : -0xe.71790d020f3d8p-7
        const double erfc_i0_c5=-1.1283791670950364671722e-01;
        // x^7 : +0xd.c16718928048p-9
        const double erfc_i0_c7=+2.6866170644325892968851e-02;
        // x^9 : -0xa.b2de682cab02p-11
        const double erfc_i0_c9=-5.2239776174096731742313e-03;
        // x^11 : +0xe.016d91f9d4358p-14
        const double erfc_i0_c11=+8.5483265129694446706615e-04;
        // x^13 : -0xf.cd175e0e4e63p-17
        const double erfc_i0_c13=-1.2055311438229345476734e-04;
        // x^15 : +0xf.a668a8978d9c8p-20
        const double erfc_i0_c15=+1.4925035918168110094070e-05;
        // x^17 : -0xd.ccaced61432dp-23
        const double erfc_i0_c17=-1.6450302196342027448580e-06;
        // x^19 : +0xa.e1fcd27acc17p-26
        const double erfc_i0_c19=+1.6216582075372502191930e-07;
        // x^21 : -0xe.a495e1208ac98p-30
        const double erfc_i0_c21=-1.3637274483397783432589e-08;
        // x^23 : +0xc.6f15790af88ap-34
        const double erfc_i0_c23=+7.2374948063438535431235e-10;

        i0h = horner(x2h,
                     erfc_i0_c23,
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
        horner_comp_quick(i0h, i0l, x2h, i0h, erfc_i0_c1);
        d_ops::mul122(i0h, i0l, x, i0h, i0l);
        d_ops::add122(i0h, i0l, erfc_i0_c0, i0h, i0l);
    }
    if (any_of(x_gt_0_75)) {
        vf_type i1h=0, i1l=0, i2h=0, i2l=0, i3h=0, i3l=0;
        if (any_of(x_in_i1)) {
            // [0.75, 2.75] : | p - f | <= 2^-59.140625
            // coefficients for erfc_i1 generated by sollya
            // x^0 h: +0xe.9ab8ed1eb334p-5
            const vf_type erfc_i1_c0h=+4.5638700783238173031009e-01;
            // x^0 l: +0xa.d84458027608p-60
            const vf_type erfc_i1_c0l=+9.4063583688085847229697e-18;
            // x^1 : +0xe.491a04c8c74cp-7
            const vf_type erfc_i1_c1=+1.1160588487251243972054e-01;
            // x^2 : -0xa.2f2e2cef14d4p-7
            const vf_type erfc_i1_c2=-7.9564830723177437654670e-02;
            // x^3 : +0xc.04e45b228aecp-8
            const vf_type erfc_i1_c3=+4.6949646234263731070513e-02;
            // x^4 : -0xc.81f3181aaca28p-9
            const vf_type erfc_i1_c4=-2.4428936664969275877057e-02;
            // x^5 : +0xb.d768c57589a98p-10
            const vf_type erfc_i1_c5=+1.1563908626507723650945e-02;
            // x^6 : -0xa.63b9b4a1478e8p-11
            const vf_type erfc_i1_c6=-5.0730236290837090254446e-03;
            // x^7 : +0x8.8d49ff8862c7p-12
            const vf_type erfc_i1_c7=+2.0878687432960901446122e-03;
            // x^8 : -0xd.52c57361f90b8p-14
            const vf_type erfc_i1_c8=-8.1319124504336786751074e-04;
            // x^9 : +0x9.e2cbf3c4e126p-15
            const vf_type erfc_i1_c9=+3.0169447521813798178403e-04;
            // x^10 : -0xe.0bb151c7a8528p-17
            const vf_type erfc_i1_c10=-1.0715999168492641908674e-04;
            // x^11 : +0x9.977b7170369bp-18
            const vf_type erfc_i1_c11=+3.6589536066079111453590e-05;
            // x^12 : -0xc.a2ab8ebd56438p-20
            const vf_type erfc_i1_c12=-1.2050085316536611183716e-05;
            // x^13 : +0x8.0ccdcd4bed6b8p-21
            const vf_type erfc_i1_c13=+3.8385464136067494822307e-06;
            // x^14 : -0x9.f2c8b4ede0f7p-23
            const vf_type erfc_i1_c14=-1.1859387209455998480028e-06;
            // x^15 : +0xb.f40aca445959p-25
            const vf_type erfc_i1_c15=+3.5623579156227751425936e-07;
            // x^16 : -0xd.ee6cf0d2c7e4p-27
            const vf_type erfc_i1_c16=-1.0379664453424312714811e-07;
            // x^17 : +0xf.68af910b030dp-29
            const vf_type erfc_i1_c17=+2.8701366732499267312170e-08;
            // x^18 : -0xf.378a81de6765p-31
            const vf_type erfc_i1_c18=-7.0859478803687918441900e-09;
            // x^19 : +0xc.09f239228b7b8p-33
            const vf_type erfc_i1_c19=+1.4015068628896234563066e-09;
            // x^20 : -0xc.ee9ba8cd582ap-36
            const vf_type erfc_i1_c20=-1.8818627975554374952333e-10;
            // x^21 : +0xd.a3aa20852e5p-40
            const vf_type erfc_i1_c21=+1.2404884439545507477160e-11;
            // x^ : +0xcp-4
            // const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
            // x^ : +0x9.c061p-3
            const vf_type erfc_i1_x0=+1.2189350128173828125000e+00;
            vf_type x_i1 = x - erfc_i1_x0;
#if 1
            vf_type x_i1_sqr= x_i1* x_i1;
            vf_type e= horner(x_i1_sqr,
                              erfc_i1_c21,
                              erfc_i1_c19,
                              erfc_i1_c17,
                              erfc_i1_c15,
                              erfc_i1_c13,
                              erfc_i1_c11,
                              erfc_i1_c9);
            vf_type o= horner(x_i1_sqr,
                              erfc_i1_c20,
                              erfc_i1_c18,
                              erfc_i1_c16,
                              erfc_i1_c14,
                              erfc_i1_c12,
                              erfc_i1_c10,
                              erfc_i1_c8);
            i1h = horner(x_i1, e, o,
                         erfc_i1_c7, erfc_i1_c6,
                         erfc_i1_c5, erfc_i1_c4,
                         erfc_i1_c3, erfc_i1_c2, erfc_i1_c1);
#else
            i1h = horner(x_i1, 
                         erfc_i1_c21,
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
#endif
            i1h *= x_i1;
            d_ops::add122cond(i1h, i1l, i1h, erfc_i1_c0h, erfc_i1_c0l);
        }
        if (any_of(x_in_i2)) {
            // [2.75, 6] : | p - f | <= 2^-60.78125
            // coefficients for erfc_i2 generated by sollya
            // x^0 h: +0x8.b6be4ee0e3cf8p-4
            const vf_type erfc_i2_c0h=+5.4461508571533900902040e-01;
            // x^0 l: -0xf.671435e10336p-60
            const vf_type erfc_i2_c0l=-1.3359671127367542122339e-17;
            // x^1 : +0xa.16d74869fa14p-10
            const vf_type erfc_i2_c1=+9.8527563045483629311505e-03;
            // x^2 : -0xe.d301c034b6d9p-12
            const vf_type erfc_i2_c2=-3.6192005530161991747051e-03;
            // x^3 : +0x9.6ff24eeab773p-13
            const vf_type erfc_i2_c3=+1.1520130713824016342739e-03;
            // x^4 : -0xa.ffdc08a0d9bd8p-15
            const vf_type erfc_i2_c4=-3.3567661126348403250949e-04;
            // x^5 : +0xc.08d7ee8566bap-17
            const vf_type erfc_i2_c5=+9.1816290715132132822102e-05;
            // x^6 : -0xc.887d80312e89p-19
            const vf_type erfc_i2_c6=-2.3905115107495057615462e-05;
            // x^7 : +0xc.883cc02440b08p-21
            const vf_type erfc_i2_c7=+5.9758076571828292662702e-06;
            // x^8 : -0xc.1a3be6d993c6p-23
            const vf_type erfc_i2_c8=-1.4427276287414592112544e-06;
            // x^9 : +0xb.55dd7bd65fcp-25
            const vf_type erfc_i2_c9=+3.3782156776389365591615e-07;
            // x^10 : -0xa.5477bd400695p-27
            const vf_type erfc_i2_c10=-7.6964140505220350364034e-08;
            // x^11 : +0x9.2e98812edf9dp-29
            const vf_type erfc_i2_c11=+1.7102834835369625553510e-08;
            // x^12 : -0xf.f3fc9d2840758p-32
            const vf_type erfc_i2_c12=-3.7143643321806636143601e-09;
            // x^13 : +0xd.90ea70083d63p-34
            const vf_type erfc_i2_c13=+7.8964962357884016169953e-10;
            // x^14 : -0xb.5034a2ead7708p-36
            const vf_type erfc_i2_c14=-1.6463022864863182286291e-10;
            // x^15 : +0x9.48326e811c72p-38
            const vf_type erfc_i2_c15=+3.3767790322690686244921e-11;
            // x^16 : -0xf.008d0c171947p-41
            const vf_type erfc_i2_c16=-6.8221889750437386369149e-12;
            // x^17 : +0xb.b4c57a7769f08p-43
            const vf_type erfc_i2_c17=+1.3308338431005692045565e-12;
            // x^18 : -0x8.3d69a3d340728p-45
            const vf_type erfc_i2_c18=-2.3419184991537750722353e-13;
            // x^19 : +0x9.44ce323295aap-48
            const vf_type erfc_i2_c19=+3.2929290592266954093199e-14;
            // x^20 : -0xd.fddde3facf0bp-52
            const vf_type erfc_i2_c20=-3.1067741781483397623413e-15;
            // x^21 : +0xa.3910a3ae7e2p-56
            const vf_type erfc_i2_c21=+1.4187137779577336243611e-16;
            // x^ : +0xbp-2
            // const vf_type erfc_i2_left=+2.7500000000000000000000e+00;
            // x^ : +0xe.6c9f6p-2
            const vf_type erfc_i2_x0=+3.6060767173767089843750e+00;
            vf_type x_i2 = x - erfc_i2_x0;
#if 1
            vf_type x_i2_sqr= x_i2* x_i2;
            vf_type e= horner(x_i2_sqr,
                              erfc_i2_c21,
                              erfc_i2_c19,
                              erfc_i2_c17,
                              erfc_i2_c15,
                              erfc_i2_c13,
                              erfc_i2_c11,
                              erfc_i2_c9,
                              erfc_i2_c7,
                              erfc_i2_c5,
                              erfc_i2_c3);
            vf_type o= horner(x_i2_sqr,
                              erfc_i2_c20,
                              erfc_i2_c18,
                              erfc_i2_c16,
                              erfc_i2_c14,
                              erfc_i2_c12,
                              erfc_i2_c10,
                              erfc_i2_c8,
                              erfc_i2_c6,
                              erfc_i2_c4,
                              erfc_i2_c2);
            i2h = horner(x_i2, e, o, erfc_i2_c1);
#else
            i2h = horner(x_i2, 
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
                         erfc_i2_c10,
                         erfc_i2_c9,
                         erfc_i2_c8,
                         erfc_i2_c7,
                         erfc_i2_c6,
                         erfc_i2_c5,
                         erfc_i2_c4,
                         erfc_i2_c3,
                         erfc_i2_c2,
                         erfc_i2_c1);
#endif
            i2h *= x_i2;
            d_ops::add122cond(i2h, i2l, i2h, erfc_i2_c0h, erfc_i2_c0l);
        }
        if (any_of(x_in_i3)) {
            // [3.6697246134281158447265625e-2, 0.16666667163372039794921875] : | p - f | <= 2^-92.125
            // coefficients for erfc generated by sollya
            // x^0 : +0x9.06eba8214db68p-4
            const double erfc_i3_c0=+5.6418958354775627928035e-01;
            // x^1 : +0xa.f92535989c79p-52
            const double erfc_i3_c1=+2.4365451922245938660534e-15;
            // x^2 : -0x9.06eba8215aap-5
            const double erfc_i3_c2=-2.8209479177424512386096e-01;
            // x^3 : +0x9.95dd9557213bp-38
            const double erfc_i3_c3=+3.4871526963839179975749e-11;
            // x^4 : +0xd.8a617aef4f97p-5
            const double erfc_i3_c4=+4.2314218531326985850427e-01;
            // x^5 : +0xf.ff517b44d421p-27
            const double erfc_i3_c5=+1.1918944909655141650019e-07;
            // x^6 : -0x8.767f6a5356d1p-3
            const double erfc_i3_c6=-1.0578602129633982720236e+00;
            // x^7 : +0x9.f403d11a91298p-16
            const double erfc_i3_c7=+1.5187352355840402925134e-04;
            // x^8 : +0xe.cb46be56c001p-2
            const double erfc_i3_c8=+3.6985120525787360534764e+00;
            // x^9 : +0xb.16181dfe9c908p-7
            const double erfc_i3_c9=+8.6611761709012316523548e-02;
            // x^10 : -0x9.1e7f2b6dc93a8p+1
            const double erfc_i3_c10=-1.8238255909544438537750e+01;
            // x^11 : +0xc.185e70965c288p+1
            const double erfc_i3_c11=+2.4190382073801007578595e+01;
            // x^12 : -0xd.e384db7ff99f8p+4
            const double erfc_i3_c12=-2.2221993589391965429058e+02;
            // x^13 : +0xd.7b5d7b665fe7p+8
            const double erfc_i3_c13=+3.4513651641830574590131e+03;
            // x^14 : -0x8.0013b33a31c48p+12
            const double erfc_i3_c14=-3.2769231256670384027530e+04;
            // x^15 : +0xf.7df0afac028ep+14
            const double erfc_i3_c15=+2.5382017155460349749774e+05;
            // x^16 : -0xc.d8dd1176d6d2p+17
            const double erfc_i3_c16=-1.6838981364391827955842e+06;
            // x^17 : +0x8.f9fc5603a2518p+20
            const double erfc_i3_c17=+9.4125493758872207254171e+06;
            // x^18 : -0xa.66ddd2a2f023p+22
            const double erfc_i3_c18=-4.3628404659119173884392e+07;
            // x^19 : +0x9.deafb38cd5c6p+24
            const double erfc_i3_c19=+1.6558891555013692378998e+08;
            // x^20 : -0xf.18369669d6f98p+25
            const double erfc_i3_c20=-5.0649015682687300443649e+08;
            // x^21 : +0x9.145a63c860018p+27
            const double erfc_i3_c21=+1.2186304302617194652557e+09;
            // x^22 : -0x8.45df7864a3c3p+28
            const double erfc_i3_c22=-2.2207507262899808883667e+09;
            // x^23 : +0xa.bad0fb0fef79p+28
            const double erfc_i3_c23=+2.8802456809959650039673e+09;
            // x^24 : -0x8.d2241011fd07p+28
            const double erfc_i3_c24=-2.3678323211242742538452e+09;
            // x^25 : +0xd.d03fb0fdd546p+26
            const double erfc_i3_c25=+9.2700640396614217758179e+08;
            vf_type inv_x=1.0/x;
            vf_type inv_x2= inv_x*inv_x;
            vf_type e=horner(inv_x2,
                             erfc_i3_c25,
                             erfc_i3_c23,
                             erfc_i3_c21,
                             erfc_i3_c19,
                             erfc_i3_c17,
                             erfc_i3_c15,
                             erfc_i3_c13,
                             erfc_i3_c11,
                             erfc_i3_c9,
                             erfc_i3_c7,
                             erfc_i3_c5);
            vf_type o=horner(inv_x2,
                             erfc_i3_c24,
                             erfc_i3_c22,
                             erfc_i3_c20,
                             erfc_i3_c18,
                             erfc_i3_c16,
                             erfc_i3_c14,
                             erfc_i3_c12,
                             erfc_i3_c10,
                             erfc_i3_c8,
                             erfc_i3_c6,
                             erfc_i3_c4);
            i3h = horner(inv_x, e, o, erfc_i3_c3, erfc_i3_c2, erfc_i3_c1);
            horner_comp(i3h, i3l, inv_x, i3h, erfc_i3_c0);
        }
        i123h = _T::sel(x_gt_2_75, i2h, i1h);
        i123l = _T::sel(x_gt_2_75, i2l, i1l);
        i123h = _T::sel(x_gt_6_00, i3h, i123h);
        i123l = _T::sel(x_gt_6_00, i3l, i123l);
        // multiply with e^(-x^2)
        d_ops::mul22(i123h, i123l, i123h, i123l, exh, exl);
        // divide by x
        dvf_type t(i123h, i123l);
        dvf_type r = d_ops::sloppy_div(t, x);
        i123h = r.h();
        i123l = r.l();
    }
    vmf_type x_lt_0_00 = xc < 0.0;
    vf_type ih= _T::sel(x_le_0_75, i0h, i123h);
    if (any_of(x_lt_0_00)) {
        vf_type il= _T::sel(x_le_0_75, i0l, i123l);
        vf_type nih, nil;
        d_ops::add122cond(nih, nil, 2.0, -ih, -il);
        ih = _T::sel(x_lt_0_00, nih, ih);
    }
    return ih;
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
    } else {
        mpfr_cache::use(mpfr_erfc, "erfc", 0.0);
    }
    // func_domain<double> d=std::make_pair(6, 27.25);
    // func_domain<double> d=std::make_pair(-0.75, 0.75);
    // func_domain<double> d=std::make_pair(0.75, 2.75);
    // func_domain<double> d=std::make_pair(2.75, 6.0);
    func_domain<double> d=std::make_pair(-27.25, 27.25);
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
