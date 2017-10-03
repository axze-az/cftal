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
    vmf_type x_gt_3_00 = x > 3.0;
    vmf_type x_gt_6_00 = x > 6.0;

    vmf_type x_in_i1 = x_gt_0_75 & (x <= 3.0);
    vmf_type x_in_i2 = x_gt_3_00 & (x <= 6.0);
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
            // [0.75, 3] : | p - f | <= 2^-68.1875
            // coefficients for erfc generated by sollya
            // x^0 : +0xa.0e34a706ea15p-31
            const double erfc_i1_c0=+4.6824528428804165308176e-09;
            // x^1 : +0xf.ffffe9a843adp-4
            const double erfc_i1_c1=+9.9999991676689181652193e-01;
            // x^2 : -0x9.06eb49655fd38p-3
            const double erfc_i1_c2=-1.1283784612714755635210e+00;
            // x^3 : +0xf.fffc03419156p-4
            const double erfc_i1_c3=+9.9999619743274115180043e-01;
            // x^4 : -0xc.092ae033633d8p-4
            const double erfc_i1_c4=-7.5223815515910474882588e-01;
            // x^5 : +0xf.ffa65455f7558p-5
            const double erfc_i1_c5=+4.9995724174344030599215e-01;
            // x^6 : -0x9.a02bf8558791p-5
            const double erfc_i1_c6=-3.0080221655610916986490e-01;
            // x^7 : +0xa.a79f39af9ea9p-6
            const double erfc_i1_c7=+1.6648083337211488919039e-01;
            // x^8 : -0xa.f7a52a9e2ebc8p-7
            const double erfc_i1_c8=-8.5682531175157353175997e-02;
            // x^9 : +0xa.91e1b5ca36c18p-8
            const double erfc_i1_c9=+4.1288477785395925889755e-02;
            // x^10 : -0x9.91095a08c045p-9
            const double erfc_i1_c10=-1.8684665909291221785882e-02;
            // x^11 : +0x8.1fa2756a3e4fp-10
            const double erfc_i1_c11=+7.9331764378010559413124e-03;
            // x^12 : -0xc.e138ef349603p-12
            const double erfc_i1_c12=-3.1444763183450267704511e-03;
            // x^13 : +0x9.732df768145cp-13
            const double erfc_i1_c13=+1.1535547048447235968238e-03;
            // x^14 : -0xc.b0166fdf22e68p-15
            const double erfc_i1_c14=-3.8720222050256104502977e-04;
            // x^15 : +0xf.615973ad03658p-17
            const double erfc_i1_c15=+1.1734215680727769551533e-04;
            // x^16 : -0x8.4b9148f6ba5p-18
            const double erfc_i1_c16=-3.1643621915413951486973e-05;
            // x^17 : +0xf.ae21c7b142908p-21
            const double erfc_i1_c17=+7.4769034112143214926304e-06;
            // x^18 : -0xc.c504e805eb3ap-23
            const double erfc_i1_c18=-1.5222556727900419737344e-06;
            // x^19 : +0x8.cac77742f0bcp-25
            const double erfc_i1_c19=+2.6202518068438574347606e-07;
            // x^20 : -0xa.0126db7d9df38p-28
            const double erfc_i1_c20=-3.7269663686488073398321e-08;
            // x^21 : +0x9.21ec4867310ap-31
            const double erfc_i1_c21=+4.2526571265325559731560e-09;
            // x^22 : -0xc.d46e6ea3d011p-35
            const double erfc_i1_c22=-3.7339661682049134113624e-10;
            // x^23 : +0xc.ff766f5f025dp-39
            const double erfc_i1_c23=+2.3643044051543266700269e-11;
            // x^24 : -0x8.70e663150356p-43
            const double erfc_i1_c24=-9.5963235108191444145232e-13;
            // x^25 : +0xa.8b506c08ea37p-49
            const double erfc_i1_c25=+1.8730254489622485271535e-14;
#if 1
            i1h = horner(x,
                             erfc_i1_c25,
                             erfc_i1_c24);
            horner_comp(i1h, i1l, x,
                            i1h,
                             erfc_i1_c23,
                             erfc_i1_c22,
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
                             erfc_i1_c2, erfc_i1_c1, erfc_i1_c0);
#else
            vf_type e=horner(x2h,
                             erfc_i1_c25,
                             erfc_i1_c23,
                             erfc_i1_c21,
                             erfc_i1_c19,
                             erfc_i1_c17,
                             erfc_i1_c15,
                             erfc_i1_c13,
                             erfc_i1_c11,
                             erfc_i1_c9,
                             erfc_i1_c7,
                             erfc_i1_c5);
            vf_type o=horner(x2h,
                             erfc_i1_c24,
                             erfc_i1_c22,
                             erfc_i1_c20,
                             erfc_i1_c18,
                             erfc_i1_c16,
                             erfc_i1_c14,
                             erfc_i1_c12,
                             erfc_i1_c10,
                             erfc_i1_c8,
                             erfc_i1_c6,
                             erfc_i1_c4);
            i1h = horner(x, e, o, erfc_i1_c3);
            horner_comp(i1h, i1l, x, i1h,
                        erfc_i1_c2, erfc_i1_c1, erfc_i1_c0);
#endif
        }
        if (any_of(x_in_i2)) {
            // [3, 6] : | p - f | <= 2^-68.15625
            // coefficients for erfc generated by sollya
            // x^0 : -0x8.2e673d9199eap-14
            const double erfc_i2_c0=-4.9934465484968238238594e-04;
            // x^1 : +0x8.04511ea0aab28p-3
            const double erfc_i2_c1=+1.0021078484326946256289e+00;
            // x^2 : -0x9.0d0bdb8815ef8p-3
            const double erfc_i2_c2=-1.1313702727227263888921e+00;
            // x^3 : +0xf.fa34adb1e274p-4
            const double erfc_i2_c3=+9.9858539437823612416878e-01;
            // x^4 : -0xb.d309489a3dbap-4
            const double erfc_i2_c4=-7.3902252540925283952333e-01;
            // x^5 : +0xf.1b231f6cc433p-5
            const double erfc_i2_c5=+4.7206264627141647505226e-01;
            // x^6 : -0x8.6c3263482dccp-5
            const double erfc_i2_c6=-2.6320762053495050381002e-01;
            // x^7 : +0x8.39562706501cp-6
            const double erfc_i2_c7=+1.2849954424859943991066e-01;
            // x^8 : -0xe.0ed066655c5ap-8
            const double erfc_i2_c8=-5.4913544653900997483120e-02;
            // x^9 : +0xa.8093080c9c3b8p-9
            const double erfc_i2_c9=+2.0512194378448058568187e-02;
            // x^10 : -0xd.b16ea0e720dep-11
            const double erfc_i2_c10=-6.6860812047626026755065e-03;
            // x^11 : +0xf.8d520788284fp-13
            const double erfc_i2_c11=+1.8984415185104084981826e-03;
            // x^12 : -0xf.5b35bcb9213dp-15
            const double erfc_i2_c12=-4.6863674055778287933643e-04;
            // x^13 : +0xd.269271549221p-17
            const double erfc_i2_c13=+1.0033166533064775201474e-04;
            // x^14 : -0x9.bc878f1627de8p-19
            const double erfc_i2_c14=-1.8570792131702757479491e-05;
            // x^15 : +0xc.698220850a2p-22
            const double erfc_i2_c15=+2.9592852189308266764450e-06;
            // x^16 : -0xd.8bd7a3d78444p-25
            const double erfc_i2_c16=-4.0370998249603567002469e-07;
            // x^17 : +0xc.8ff478519b96p-28
            const double erfc_i2_c17=+4.6798303969537503155563e-08;
            // x^18 : -0x9.cd01042e2a14p-31
            const double erfc_i2_c18=-4.5638516349513647339253e-09;
            // x^19 : +0xc.b1863a248bd5p-35
            const double erfc_i2_c19=+3.6942814457325880752631e-10;
            // x^20 : -0xd.655dc29f05c4p-39
            const double erfc_i2_c20=-2.4367112778616892814419e-11;
            // x^21 : +0xb.38e92889de378p-43
            const double erfc_i2_c21=+1.2758286759591620347701e-12;
            // x^22 : -0xe.5b08e8a8d0c8p-48
            const double erfc_i2_c22=-5.1001353142139015038409e-14;
            // x^23 : +0xd.2ad0ac1ea081p-53
            const double erfc_i2_c23=+1.4618580332087292160850e-15;
            // x^24 : -0xf.6b96a561831cp-59
            const double erfc_i2_c24=-2.6749899909427018062844e-17;
            // x^25 : +0x8.a8ea5c03759d8p-65
            const double erfc_i2_c25=+2.3472505517695831739038e-19;
#if 1
            horner_comp(i2h, i2l, x, i2h,
                        erfc_i2_c25, erfc_i2_c24,
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
                             erfc_i2_c10,
                             erfc_i2_c9,
                             erfc_i2_c8,
                             erfc_i2_c7,
                             erfc_i2_c6,
                             erfc_i2_c5,
                             erfc_i2_c4,
                             erfc_i2_c3,
                             erfc_i2_c2, erfc_i2_c1, erfc_i2_c0);
#else
            vf_type e=horner(x2h,
                             erfc_i2_c25,
                             erfc_i2_c23,
                             erfc_i2_c21,
                             erfc_i2_c19,
                             erfc_i2_c17,
                             erfc_i2_c15,
                             erfc_i2_c13,
                             erfc_i2_c11,
                             erfc_i2_c9,
                             erfc_i2_c7,
                             erfc_i2_c5);
            vf_type o=horner(x2h,
                             erfc_i2_c24,
                             erfc_i2_c22,
                             erfc_i2_c20,
                             erfc_i2_c18,
                             erfc_i2_c16,
                             erfc_i2_c14,
                             erfc_i2_c12,
                             erfc_i2_c10,
                             erfc_i2_c8,
                             erfc_i2_c6,
                             erfc_i2_c4);
            i2h = horner(x, e, o, erfc_i2_c3, erfc_i2_c2, erfc_i2_c1);
            horner_comp(i2h, i2l, x, i2h, erfc_i2_c0);
#endif
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
        i123h = _T::sel(x_gt_3_00, i2h, i1h);
        i123l = _T::sel(x_gt_3_00, i2l, i1l);
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
    const int _N=1;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    } else {
        mpfr_cache::use(mpfr_erfc, "erfc", 0.0);
    }
    // func_domain<double> d=std::make_pair(6, 27.25);
    //func_domain<double> d=std::make_pair(-0.75, 0.75);
    // func_domain<double> d=std::make_pair(0.75, 3.0);
    // func_domain<double> d=std::make_pair(3.0, 6.0);
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
