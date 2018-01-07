//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F64_H__)
#define __CFTAL_MATH_SPEC_FUNC_CORE_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/horner.h>
#include <cftal/math/impl_d_real_constants_f64.h>
#include <cftal/math/lanczos.h>
#include <cftal/mem.h>
#include <cmath>


namespace cftal {
    namespace math {


        // specialization of elem_func_core for double and different
        // traits
        template <typename _T>
        struct spec_func_core<double, _T>
            : public elem_func_core<double, _T> {
            using base_type = elem_func_core<double, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            using dvf_type = d_real<vf_type>;

            using my_type = spec_func_core<double, _T>;

            using d_ops=cftal::impl::d_real_ops<vf_type,
                                                d_real_traits<vf_type>::fma>;

            // calculates sin(pi*x), cos(pi*x)
            static
            void
            __sinpi_cospi_k(arg_t<vf_type> xc,
                            vf_type* ps, vf_type *pc);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

            static
            vf_type
            tgamma_k(arg_t<vf_type> x);

        };

    } // end math
} // end cftal

template <typename _T>
void
cftal::math::spec_func_core<double, _T>::
__sinpi_cospi_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type fh= rint(vf_type(xc*2.0));
    vf_type xrh, xrl;
    d_ops::add12cond(xrh, xrl, xc, fh*(-0.5));
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    d_ops::mul22(xrh, xrl, ctbl::m_pi.h(), ctbl::m_pi.l(), xrh, xrl);
    vi_type q0= _T::cvt_f_to_i(fh);
    vi2_type q=_T::vi_to_vi2(q0);

    vf_type s = base_type::__sin_k(xrh, xrl);
    vf_type c = base_type::__cos_k(xrh, xrl);

    vmi2_type q_and_2(vi2_type(q & vi2_type(2))==vi2_type(2));
    vmf_type q_and_2_f(_T::vmi2_to_vmf(q_and_2));
    vmi2_type q_and_1(vi2_type(q & vi2_type(1))==vi2_type(1));
    vmf_type q_and_1_f(_T::vmi2_to_vmf(q_and_1));

    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        rs = _T::sel(q_and_2_f, -rs, rs);
        *ps = rs;
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        rc = _T::sel(mt, -rc, rc);
        *pc= rc;
    }
}


template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
erf_k(arg_t<vf_type> xc)
{
    // x^ : +0xcp-4
    vf_type x=abs(xc);
    const double erf_i1_left=+7.5000000000000000000000e-01;
    // x^ : +0xfp-3
    const double erf_i2_left=+1.8750000000000000000000e+00;
    // x^ : +0xep-2
    const double erf_i3_left=+3.5000000000000000000000e+00;

    vmf_type x_in_i0 = x <= erf_i1_left;
    vf_type y=0;
    if (likely(any_of(x_in_i0))) {
        // [3.4694469519536141888238489627838134765625e-18, 0.75] : | p - f | <= 2^-60.78125
        // coefficients for erf_i0 generated by sollya
        // x^1 : +0x9.06eba8214db68p-3
        const vf_type erf_i0_c1=+1.1283791670955125585607e+00;
        // x^3 : -0xc.093a3581bcdep-5
        const vf_type erf_i0_c3=-3.7612638903183515104445e-01;
        // x^5 : +0xe.71790d0206a48p-7
        const vf_type erf_i0_c5=+1.1283791670944255669529e-01;
        // x^7 : -0xd.c167188f35fap-9
        const vf_type erf_i0_c7=-2.6866170642829659276352e-02;
        // x^9 : +0xa.b2de6784c358p-11
        const vf_type erf_i0_c9=+5.2239775983210917642552e-03;
        // x^11 : -0xe.016d6a3ef017p-14
        const vf_type erf_i0_c11=-8.5483250675988885734780e-04;
        // x^13 : +0xf.cd116c04eb3cp-17
        const vf_type erf_i0_c13=+1.2055242224015018642075e-04;
        // x^15 : -0xf.a5d4b323d2f78p-20
        const vf_type erf_i0_c15=-1.4922882834294901377502e-05;
        // x^17 : +0xd.c359e3d2a913p-23
        const vf_type erf_i0_c17=+1.6406882240210931047373e-06;
        // x^19 : -0xa.83e395b26706p-26
        const vf_type erf_i0_c19=-1.5668856230000872722501e-07;
        // x^21 : +0xa.6cd8665fd081p-30
        const vf_type erf_i0_c21=+9.7092026848530503315802e-09;
        // x^23 : +0x8.91a24edd71ee8p-34
        const vf_type erf_i0_c23=+4.9877462876900157143168e-10;
        vf_type xx= x*x;
        vf_type y_i0= horner(xx,
                             erf_i0_c23,
                             erf_i0_c21,
                             erf_i0_c19,
                             erf_i0_c17,
                             erf_i0_c15,
                             erf_i0_c13,
                             erf_i0_c11,
                             erf_i0_c9,
                             erf_i0_c7,
                             erf_i0_c5,
                             erf_i0_c3);
        vf_type ye;
        horner_comp(y_i0, ye, xx, y_i0,
                    erf_i0_c1);
        vf_type p_i;
        y_i0 = d_ops::two_prod(y_i0, x, p_i);
        ye = ye*x + p_i;
        //
        // impl::eft_poly_si(y_i0, ye, x, y_i0, ye,
        //                   0.0);
        y_i0 += ye;
        y = y_i0;
    }

    vmf_type x_in_i1 = (x > erf_i1_left) & (x<=erf_i2_left);
    if (likely(any_of(x_in_i1))) {
        // [0.75, 1.875] : | p - f | <= 2^-65.65625
        // coefficients for erf_i1 generated by sollya
        // x^0 h: +0xd.a00ad76b9204p-4
        const vf_type erf_i1_c0h=+8.5157283924593318857887e-01;
        // x^0 l: +0xe.0bace157c715p-59
        const vf_type erf_i1_c0l=+2.4365243665033013894766e-17;
        // x^1 : +0xc.b59ff8cfc23f8p-5
        const vf_type erf_i1_c1=+3.9717100711829539383402e-01;
        // x^2 : -0xc.fcb4a8d44e408p-5
        const vf_type erf_i1_c2=-4.0584786390758870178175e-01;
        // x^3 : +0x9.38b3dd1da6eb8p-6
        const vf_type erf_i1_c3=+1.4408585160582162987275e-01;
        // x^4 : +0xf.c9546cfdda59p-8
        const vf_type erf_i1_c4=+6.1665798768311033684064e-02;
        // x^5 : -0x8.c2586d568b56p-7
        const vf_type erf_i1_c5=-6.8430951488233915380732e-02;
        // x^6 : +0xe.0ef0a178d53f8p-11
        const vf_type erf_i1_c6=+6.8644332196564619361090e-03;
        // x^7 : +0xe.a1c48a68778fp-10
        const vf_type erf_i1_c7=+1.4288969943769876808082e-02;
        // x^8 : -0xa.7d0064636f1fp-11
        const vf_type erf_i1_c8=-5.1212340007889527865315e-03;
        // x^9 : -0xd.3bf0ea237c58p-13
        const vf_type erf_i1_c9=-1.6154961932524462830951e-03;
        // x^10 : +0xa.29b9c60073768p-13
        const vf_type erf_i1_c10=+1.2405994784913624163353e-03;
        // x^11 : +0x8.e07992a9980b8p-18
        const vf_type erf_i1_c11=+3.3862514706578683988236e-05;
        // x^12 : -0xc.b25c1918cbf1p-16
        const vf_type erf_i1_c12=-1.9373653876469861543144e-04;
        // x^13 : +0xd.76eba164d97cp-19
        const vf_type erf_i1_c13=+2.5681558485523913555257e-05;
        // x^14 : +0xb.6d8849d428178p-19
        const vf_type erf_i1_c14=+2.1796914760299927396733e-05;
        // x^15 : -0xc.e3e4daac0ea3p-21
        const vf_type erf_i1_c15=-6.1465314806838005837327e-06;
        // x^16 : -0xe.b8e83c40bb9ap-23
        const vf_type erf_i1_c16=-1.7550341642395222597627e-06;
        // x^17 : +0xe.9642d594a2f9p-24
        const vf_type erf_i1_c17=+8.6945040884462715306098e-07;
        // x^18 : +0x8.434fa13b037d8p-26
        const vf_type erf_i1_c18=+1.2312730855381382499845e-07;
        // x^19 : -0x9.8f7487e83636p-26
        const vf_type erf_i1_c19=-1.4246064231133920797507e-07;
        // x^20 : +0x8.aad670629c2d8p-28
        const vf_type erf_i1_c20=+3.2288337422680242895254e-08;
        // x^21 : -0x9.eb079386d623p-32
        const vf_type erf_i1_c21=-2.3092339641415239179504e-09;
        // x^ : +0x8.2cbdfp-3
        const vf_type erf_i1_x0=+1.0218466520309448242188e+00;
        vf_type x_i1 = x - erf_i1_x0;
#if 1
        vf_type xx= x_i1*x_i1;
        vf_type i= horner(xx,
                          erf_i1_c21,
                          erf_i1_c19,
                          erf_i1_c17,
                          erf_i1_c15,
                          erf_i1_c13,
                          erf_i1_c11,
                          erf_i1_c9,
                          erf_i1_c7,
                          erf_i1_c5);
        vf_type j= horner(xx,
                          erf_i1_c20,
                          erf_i1_c18,
                          erf_i1_c16,
                          erf_i1_c14,
                          erf_i1_c12,
                          erf_i1_c10,
                          erf_i1_c8,
                          erf_i1_c6,
                          erf_i1_c4);
        vf_type y_i1= i*x_i1 + j;
        y_i1 = horner(x_i1, y_i1,
                      erf_i1_c3,
                      erf_i1_c2,
                      erf_i1_c1);
#else
        vf_type y_i1= horner(x_i1,
                             erf_i1_c21,
                             erf_i1_c20,
                             erf_i1_c19,
                             erf_i1_c18,
                             erf_i1_c17,
                             erf_i1_c16,
                             erf_i1_c15,
                             erf_i1_c14,
                             erf_i1_c13,
                             erf_i1_c12,
                             erf_i1_c11,
                             erf_i1_c10,
                             erf_i1_c9,
                             erf_i1_c8,
                             erf_i1_c7,
                             erf_i1_c6,
                             erf_i1_c5,
                             erf_i1_c4,
                             erf_i1_c3,
                             erf_i1_c2,
                             erf_i1_c1);
#endif
        vf_type ye;
        horner_comp(y_i1, ye, x_i1, y_i1,
                    erf_i1_c0h);
        y_i1 += ye+erf_i1_c0l;
        y = _T::sel(x_in_i1, y_i1, y);
    };

    vmf_type x_in_i2 = (x > erf_i2_left) & (x<=erf_i3_left);
    if (likely(any_of(x_in_i2))) {
        // [1.875, 3.5] : | p - f | <= 2^-60.90625
        // coefficients for erf_i2 generated by sollya
        // x^0 h: +0xf.ef9817e2c51a8p-4
        const vf_type erf_i2_c0h=+9.9599465685270749393254e-01;
        // x^0 l: +0xe.ea4df2f66f138p-58
        const vf_type erf_i2_c0l=+5.1747675271424131958331e-17;
        // x^1 : +0x9.3155c40283268p-9
        const vf_type erf_i2_c1=+1.7954521347979746775936e-02;
        // x^2 : -0x9.5a5d850dd55p-8
        const vf_type erf_i2_c2=-3.6535115226645986652443e-02;
        // x^3 : +0xb.27ecea03b4548p-8
        const vf_type erf_i2_c3=+4.3577963955344252433566e-02;
        // x^4 : -0x8.3b98bb29e3f2p-8
        const vf_type erf_i2_c4=-3.2159372038122829851048e-02;
        // x^5 : +0xd.6ac90b41e7748p-10
        const vf_type erf_i2_c5=+1.3102666198825345736378e-02;
        // x^6 : -0xa.35ad2fc18ccb8p-15
        const vf_type erf_i2_c6=-3.1157451986665293591425e-04;
        // x^7 : -0xc.09472b631ce8p-12
        const vf_type erf_i2_c7=-2.9385356958251188097542e-03;
        // x^8 : +0xc.cb04cae657cdp-13
        const vf_type erf_i2_c8=+1.5616506199860103777655e-03;
        // x^9 : -0x8.d557a80197158p-16
        const vf_type erf_i2_c9=-1.3478651090391541278977e-04;
        // x^10 : -0xe.9984e98a632p-16
        const vf_type erf_i2_c10=-2.2277350357451271289921e-04;
        // x^11 : +0xd.b21fada9734e8p-17
        const vf_type erf_i2_c11=+1.0449063013853251036690e-04;
        // x^12 : -0xe.8c7985c2fb768p-23
        const vf_type erf_i2_c12=-1.7343436820855339363241e-06;
        // x^13 : -0xe.c2fcb6920a32p-20
        const vf_type erf_i2_c13=-1.4077824208156247784863e-05;
        // x^14 : +0x8.adcd11a64e448p-21
        const vf_type erf_i2_c14=+4.1384269493855688456575e-06;
        // x^15 : +0xd.eafbd15889fep-24
        const vf_type erf_i2_c15=+8.2957177961111339101782e-07;
        // x^16 : -0xe.921eb4322d228p-24
        const vf_type erf_i2_c16=-8.6848622585478523869560e-07;
        // x^17 : +0xe.c887defc270c8p-26
        const vf_type erf_i2_c17=+2.2028868239318452089703e-07;
        // x^18 : -0x9.d9038b554d91p-35
        const vf_type erf_i2_c18=-2.8660609186842229174787e-10;
        // x^19 : -0xd.fb15b0fa873p-30
        const vf_type erf_i2_c19=-1.3020634402817493488279e-08;
        // x^20 : +0xd.287a0e3c87118p-32
        const vf_type erf_i2_c20=+3.0636117842102736309007e-09;
        // x^21 : -0x8.91299618558a8p-35
        const vf_type erf_i2_c21=-2.4933370315452378001011e-10;
        // x^ : +0x8.23b4fp-2
        const vf_type erf_i2_x0=+2.0348699092864990234375e+00;
        vf_type x_i2 = x - erf_i2_x0;
#if 1
        vf_type xx= x_i2*x_i2;
        vf_type i= horner(xx,
                          erf_i2_c21,
                          erf_i2_c19,
                          erf_i2_c17,
                          erf_i2_c15,
                          erf_i2_c13,
                          erf_i2_c11,
                          erf_i2_c9,
                          erf_i2_c7,
                          erf_i2_c5);
        vf_type j= horner(xx,
                          erf_i2_c20,
                          erf_i2_c18,
                          erf_i2_c16,
                          erf_i2_c14,
                          erf_i2_c12,
                          erf_i2_c10,
                          erf_i2_c8,
                          erf_i2_c6,
                          erf_i2_c4);
        vf_type y_i2= i*x_i2 + j;
        y_i2 = horner(x_i2, y_i2,
                      erf_i2_c3,
                      erf_i2_c2,
                      erf_i2_c1);
#else
        vf_type y_i2= horner(x_i2,
                             erf_i2_c21,
                             erf_i2_c20,
                             erf_i2_c19,
                             erf_i2_c18,
                             erf_i2_c17,
                             erf_i2_c16,
                             erf_i2_c15,
                             erf_i2_c14,
                             erf_i2_c13,
                             erf_i2_c12,
                             erf_i2_c11,
                             erf_i2_c10,
                             erf_i2_c9,
                             erf_i2_c8,
                             erf_i2_c7,
                             erf_i2_c6,
                             erf_i2_c5,
                             erf_i2_c4,
                             erf_i2_c3,
                             erf_i2_c2,
                             erf_i2_c1);
#endif
        vf_type ye;
        horner_comp(y_i2, ye, x_i2, y_i2,
                    erf_i2_c0h);
        y_i2 += ye+erf_i2_c0l;
        y = _T::sel(x_in_i2, y_i2, y);
    };

    vmf_type x_in_i3 = (x > erf_i3_left);
    if (likely(any_of(x_in_i3))) {
        // [3.5, 6] : | p - f | <= 2^-58.109375
        // coefficients for erf_i3 generated by sollya
        // x^0 h: +0xf.ffff9c4350758p-4
        const vf_type erf_i3_c0h=+9.9999962845052203785912e-01;
        // x^0 l: +0xb.caf1dd3904968p-58
        const vf_type erf_i3_c0l=+4.0914331138571226372713e-17;
        // x^1 : +0xb.9b8659624d8f8p-22
        const vf_type erf_i3_c1=+2.7674481285657176957832e-06;
        // x^2 : -0xa.6e12c20f42108p-20
        const vf_type erf_i3_c2=-9.9467980623786509997196e-06;
        // x^3 : +0xc.031fb3a65261p-19
        const vf_type erf_i3_c3=+2.2911457978090595856164e-05;
        // x^4 : -0x9.eca80dc283bcp-18
        const vf_type erf_i3_c4=-3.7858731448027949009066e-05;
        // x^5 : +0xc.77654fc74de58p-18
        const vf_type erf_i3_c5=+4.7555502482858254557820e-05;
        // x^6 : -0xc.4a021f4b75ad8p-18
        const vf_type erf_i3_c6=-4.6879176646772150371858e-05;
        // x^7 : +0x9.a6d073de7f738p-18
        const vf_type erf_i3_c7=+3.6818001687864182383102e-05;
        // x^8 : -0xc.13cdc36c5f8dp-19
        const vf_type erf_i3_c8=-2.3035733127395927705931e-05;
        // x^9 : +0xb.c7c1a19a2d53p-20
        const vf_type erf_i3_c9=+1.1234567955526363942529e-05;
        // x^10 : -0x8.529e8bd618bf8p-21
        const vf_type erf_i3_c10=-3.9685877435520957654653e-06;
        // x^11 : +0xc.547e8a04dfc2p-24
        const vf_type erf_i3_c11=+7.3492859804616469880764e-07;
        // x^12 : +0xc.85ec9d5c5b36p-26
        const vf_type erf_i3_c12=+1.8660935317950479413396e-07;
        // x^13 : -0xf.8fd15d59bd238p-26
        const vf_type erf_i3_c13=-2.3188871742844543630620e-07;
        // x^14 : +0xf.3ed20621d0eap-27
        const vf_type erf_i3_c14=+1.1358702340129324142554e-07;
        // x^15 : -0x9.f61fc73b32e1p-28
        const vf_type erf_i3_c15=-3.7109190216543264217597e-08;
        // x^16 : +0x9.50a9702108248p-30
        const vf_type erf_i3_c16=+8.6753493349650820866145e-09;
        // x^17 : -0xc.4cc58c305bdb8p-33
        const vf_type erf_i3_c17=-1.4318955756438658326616e-09;
        // x^18 : +0xa.9fa758a91467p-36
        const vf_type erf_i3_c18=+1.5459441423225671075377e-10;
        // x^19 : -0x9.8b0042d43c5d8p-40
        const vf_type erf_i3_c19=-8.6792831401194721286056e-12;
        // x^20 : -0xf.835a0e526809p-50
        const vf_type erf_i3_c20=-1.3778394331846918471113e-14;
        // x^21 : +0xc.1aecc242ad2p-49
        const vf_type erf_i3_c21=+2.1503110675247887643702e-14;
        // x^ : +0xe.60796p-2
        const vf_type erf_i3_x0=+3.5942130088806152343750e+00;


        vf_type x_i3 = x - erf_i3_x0;
#if 1
        vf_type xx= x_i3*x_i3;
        vf_type i= horner(xx,
                          erf_i3_c21,
                          erf_i3_c19,
                          erf_i3_c17,
                          erf_i3_c15,
                          erf_i3_c13,
                          erf_i3_c11,
                          erf_i3_c9,
                          erf_i3_c7,
                          erf_i3_c5);
        vf_type j= horner(xx,
                          erf_i3_c20,
                          erf_i3_c18,
                          erf_i3_c16,
                          erf_i3_c14,
                          erf_i3_c12,
                          erf_i3_c10,
                          erf_i3_c8,
                          erf_i3_c6,
                          erf_i3_c4);
        vf_type y_i3= i*x_i3 + j;
        y_i3 = horner(x_i3, y_i3,
                      erf_i3_c3,
                      erf_i3_c2,
                      erf_i3_c1);
#else
        vf_type y_i3= horner(x_i3,
                             erf_i3_c21,
                             erf_i3_c20,
                             erf_i3_c19,
                             erf_i3_c18,
                             erf_i3_c17,
                             erf_i3_c16,
                             erf_i3_c15,
                             erf_i3_c14,
                             erf_i3_c13,
                             erf_i3_c12,
                             erf_i3_c11,
                             erf_i3_c10,
                             erf_i3_c9,
                             erf_i3_c8,
                             erf_i3_c7,
                             erf_i3_c6,
                             erf_i3_c5,
                             erf_i3_c4,
                             erf_i3_c3,
                             erf_i3_c2,
                             erf_i3_c1);
#endif
        vf_type ye;
        horner_comp(y_i3, ye, x_i3, y_i3,
                    erf_i3_c0h);
        y_i3 += ye+erf_i3_c0l;
        y=_T::sel(x_in_i3, y_i3, y);
    };
    y = copysign(y, xc);
    return y;
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
erfc_k(arg_t<vf_type> xc)
{
    // erfc(-x) = 2 - erfc(x)

    vf_type x= abs(xc);
    vmf_type x_le_0_75 = x <= 0.75;
    vmf_type x_gt_0_75 = x > 0.75;

    vf_type exl=0, exh=0;

    vf_type i0h=0, i0l=0, i123h=0, i123l=0;
    vf_type x2h;
    bool any_of_x_gt_0_75=any_of(x_gt_0_75);
    if (likely(any_of_x_gt_0_75)) {
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
    if (likely(any_of(x_le_0_75))) {
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
    if (likely(any_of_x_gt_0_75)) {
        vmf_type x_gt_2_75 = x > 2.75;
        vmf_type x_gt_6_00 = x > 6.0;
        vmf_type x_in_i1 = x_gt_0_75 & (x <= 2.75);
        vmf_type x_in_i2 = x_gt_2_75 & (x <= 6.0);
        vmf_type x_in_i3 = x_gt_6_00;
        if (likely(any_of(x_in_i1))) {
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
            vf_type i1h, i1l;
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
            i123h= i1h;
            i123l= i1l;
        }
        if (likely(any_of(x_in_i2))) {
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
            vf_type i2h, i2l;
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
            i123h = _T::sel(x_gt_2_75, i2h, i123h);
            i123l = _T::sel(x_gt_2_75, i2l, i123l);
        }
        if (likely(any_of(x_in_i3))) {
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
            vf_type i3h, i3l;
            i3h = horner(inv_x, e, o, erfc_i3_c1);
            i3h *= inv_x;
            d_ops::add12cond(i3h, i3l, i3h, erfc_i3_c0);
            i123h = _T::sel(x_gt_6_00, i3h, i123h);
            i123l = _T::sel(x_gt_6_00, i3l, i123l);
        }
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
    if (likely(any_of(x_lt_0_00))) {
        vf_type il= _T::sel(x_le_0_75, i0l, i123l);
        vf_type nih, nil;
        d_ops::add122(nih, nil, 2.0, -ih, -il);
        ih = _T::sel(x_lt_0_00, nih, ih);
    }
    return ih;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
tgamma_k(arg_t<vf_type> xc)
{
    vmf_type xc_lt_0 = xc < 0.0;
    vmf_type x0 = abs(xc);
    // G(z+1) = z * G(z)
    // G(z) * G(1-z) = pi/sin(pi*z)
    // with G(-z+1) = -z * G(z)
    // G(z) * -z * G(-z) = pi/sin(pi*z)
    // G(-z) = -pi/[sin(pi*z)*z * G(z)]
    // lanczos sum:
    using lanczos_ratfunc=lanczos_rational_f64<vf_type>;
    vf_type sum= lanczos_ratfunc::at(x0);
    // base of the Lanczos exponential
    vf_type base, base_l;
    d_ops::add12cond(base, base_l, x0, lanczos_ratfunc::gm0_5());
    vf_type r = sum * base_type::template exp_k<false>(-base);
    vf_type z = x0 - 0.5;
    if (any_of(xc_lt_0)) {
        // G(-z) = -pi/[sin(pi*z)*z * G(z)]
        vf_type s;
        __sinpi_cospi_k(x0, &s, nullptr);
        vf_type r_n = -M_PI/(s * x0 * r);
        r = _T::sel(xc_lt_0, r_n, r);
        base_l = _T::sel(xc_lt_0, -base_l, base_l);
        z = _T::sel(xc_lt_0, -z, z);
    }
    // how does this error correction work?
    r += base_l * (-lanczos_ratfunc::g()) * r/base;
    // calculate the base^z as base^(1/2 z)^2 to avoid overflows
    vf_type powh = base_type::pow_k(base,0.5*z);
    vf_type t= r * powh*powh;
    t = _T::sel(x0 < 0x1p-54f, 1.0f/xc, t);
    return t;
}

// Local Variables:
// mode: c++
// end:
#endif
