#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F64_H__)
#define __CFTAL_MATH_SPEC_FUNC_CORE_F64_H__ 1

// This code uses code from sun libm:
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/impl_poly.h>
#include <cftal/math/impl_d_real_constants_f64.h>
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
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef spec_func_core<double, _T> my_type;

            using d_ops=cftal::impl::d_real_ops<vf_type,
                                                d_real_traits<vf_type>::fma>;


            using base_type::exp_mx2_k;
            
            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

        };

    } // end math
} // end cftal


namespace cftal {
    namespace math {
        namespace impl {

            template <typename _V>
            struct erf_res {
                _V _x;
                _V _yh;
                _V _yl;
                _V _c0h;
                _V _c0l;

                erf_res(_V x, _V yh, _V yl, _V c0h, _V c0l)
                    : _x(x), _yh(yh), _yl(yl), _c0h(c0h), _c0l(c0l) {}
            };

            template <typename _V>
            _V
            final_result(const erf_res<_V>& r)
            {
                _V rh, rl;
                eft_poly_si(rh, rl, r._x, r._yh, r._yl, r._c0h);
                rh += (rl + r._c0l);
                return rh;
            };

            template <typename _M, typename _V>
            erf_res<_V>
            select(const _M& m, const erf_res<_V>& t, const erf_res<_V>& f)
            {
                erf_res<_V> r(select(m, t._x, f._x),
                              select(m, t._yh, f._yh),
                              select(m, t._yl, f._yl),
                              select(m, t._c0h, f._c0l),
                              select(m, t._c0l, f._c0l));
                return r;
            }

        }
    }
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
erf_k(arg_t<vf_type> xc)
{

    vf_type x=abs(xc);

    auto i0 = [x]() -> vf_type {
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
        vf_type y_i0= impl::poly(xx,
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
        impl::eft_poly(y_i0, ye, xx, y_i0,
                       erf_i0_c1);
        vf_type p_i;
        y_i0 = d_ops::two_prod(y_i0, x, p_i);
        ye = ye*x + p_i;
        //
        // impl::eft_poly_si(y_i0, ye, x, y_i0, ye,
        //                   0.0);
        y_i0 += ye;
        return y_i0;
    };

    auto i1 = [x]()-> vf_type {
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
        // x^ : +0xcp-4
        //const vf_type erf_i1_left=+7.5000000000000000000000e-01;
        // x^ : +0x8.2cbdfp-3
        const vf_type erf_i1_x0=+1.0218466520309448242188e+00;
        vf_type x_i1 = x - erf_i1_x0;
#if 1
        vf_type xx= x_i1*x_i1;
        vf_type i= impl::poly(xx,
                              erf_i1_c21,
                              erf_i1_c19,
                              erf_i1_c17,
                              erf_i1_c15,
                              erf_i1_c13,
                              erf_i1_c11,
                              erf_i1_c9,
                              erf_i1_c7,
                              erf_i1_c5);
        vf_type j= impl::poly(xx,
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
        y_i1 = impl::poly(x_i1, y_i1,
                          erf_i1_c3,
                          erf_i1_c2,
                          erf_i1_c1);
#else
        vf_type y_i1= impl::poly(x_i1,
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
        impl::eft_poly(y_i1, ye, x_i1, y_i1,
                       erf_i1_c0h);
        y_i1 += ye+erf_i1_c0l;
        return y_i1;
    };

    auto i2 = [x]()->vf_type {
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
        // x^ : +0xfp-3
        // const vf_type erf_i2_left=+1.8750000000000000000000e+00;
        // x^ : +0x8.23b4fp-2
        const vf_type erf_i2_x0=+2.0348699092864990234375e+00;
        vf_type x_i2 = x - erf_i2_x0;
#if 1
        vf_type xx= x_i2*x_i2;
        vf_type i= impl::poly(xx,
                              erf_i2_c21,
                              erf_i2_c19,
                              erf_i2_c17,
                              erf_i2_c15,
                              erf_i2_c13,
                              erf_i2_c11,
                              erf_i2_c9,
                              erf_i2_c7,
                              erf_i2_c5);
        vf_type j= impl::poly(xx,
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
        y_i2 = impl::poly(x_i2, y_i2,
                          erf_i2_c3,
                          erf_i2_c2,
                          erf_i2_c1);
#else
        vf_type y_i2= impl::poly(x_i2,
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
        impl::eft_poly(y_i2, ye, x_i2, y_i2,
                       erf_i2_c0h);
        y_i2 += ye+erf_i2_c0l;
        return y_i2;
    };

    auto i3= [x]()->vf_type {
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
        // x^ : +0xep-2
        // const vf_type erf_i3_left=+3.5000000000000000000000e+00;
        // x^ : +0xe.60796p-2
        const vf_type erf_i3_x0=+3.5942130088806152343750e+00;


        vf_type x_i3 = x - erf_i3_x0;
#if 1
        vf_type xx= x_i3*x_i3;
        vf_type i= impl::poly(xx,
                              erf_i3_c21,
                              erf_i3_c19,
                              erf_i3_c17,
                              erf_i3_c15,
                              erf_i3_c13,
                              erf_i3_c11,
                              erf_i3_c9,
                              erf_i3_c7,
                              erf_i3_c5);
        vf_type j= impl::poly(xx,
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
        y_i3 = impl::poly(x_i3, y_i3,
                          erf_i3_c3,
                          erf_i3_c2,
                          erf_i3_c1);
#else
        vf_type y_i3= impl::poly(x_i3,
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
        impl::eft_poly(y_i3, ye, x_i3, y_i3,
                       erf_i3_c0h);
        y_i3 += ye+erf_i3_c0l;
        return y_i3;
    };

    auto s01 = [x, i0, i1]() -> vf_type {
        // x^ : +0xcp-4
        const vf_type erf_i1_left=+7.5000000000000000000000e-01;
        vf_type r=select_branch(x < erf_i1_left, i0, i1);
        return r;
    };

    auto s12 = [x, s01, i2]() -> vf_type {
        // x^ : +0xfp-3
        const vf_type erf_i2_left=+1.8750000000000000000000e+00;
        vf_type r=select_branch(x < erf_i2_left, s01, i2);
        return r;
    };

    auto s23 = [x, s12, i3]() ->vf_type {
        // x^ : +0xep-2
        const vf_type erf_i3_left=+3.5000000000000000000000e+00;
        vf_type r=select_branch(x <erf_i3_left, s12, i3);
        return r;
    };

    vf_type y= s23();
    y = copysign(y, xc);
    return y;
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
erfc_k(arg_t<vf_type> xc)
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
            _expmxx = exp_mx2_k(x);
            _1_plus_2_x= 1 + 2*x;
            _f = _expmxx / _1_plus_2_x;
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
        // [0.75, 1.875] : | p - f | <= 2^-65.71875
        // coefficients for erfc_i1 generated by sollya
        // x^0 h: +0x9.7fd4a251b7ef8p-6
        const vf_type erfc_i1_c0h=+1.4842716075406678366555e-01;
        // x^0 l: +0xf.9fb871dc60c8p-62
        const vf_type erfc_i1_c0l=+3.3878950326178034048751e-18;
        // x^1 : -0xc.b59ff8cfc23f8p-5
        const vf_type erfc_i1_c1=-3.9717100711829539383402e-01;
        // x^2 : +0xc.fcb4a8d44e408p-5
        const vf_type erfc_i1_c2=+4.0584786390758870178175e-01;
        // x^3 : -0x9.38b3dd1da6ecp-6
        const vf_type erfc_i1_c3=-1.4408585160582165762833e-01;
        // x^4 : -0xf.c9546cfdda53p-8
        const vf_type erfc_i1_c4=-6.1665798768310950417337e-02;
        // x^5 : +0x8.c2586d568bcc8p-7
        const vf_type erfc_i1_c5=+6.8430951488237204416443e-02;
        // x^6 : -0xe.0ef0a178f0318p-11
        const vf_type erfc_i1_c6=-6.8644332196684280586463e-03;
        // x^7 : -0xe.a1c48a69121f8p-10
        const vf_type erfc_i1_c7=-1.4288969943907157619800e-02;
        // x^8 : +0xa.7d0064694ab88p-11
        const vf_type erfc_i1_c8=+5.1212340014549087921503e-03;
        // x^9 : +0xd.3bf0ea72c49dp-13
        const vf_type erfc_i1_c9=+1.6154961955057848578543e-03;
        // x^10 : -0xa.29b9c864c618p-13
        const vf_type erfc_i1_c10=-1.2405994958946224560048e-03;
        // x^11 : -0x8.e07994534153p-18
        const vf_type erfc_i1_c11=-3.3862515084641817901361e-05;
        // x^12 : +0xc.b25d02723914p-16
        const vf_type erfc_i1_c12=+1.9373675099467022216182e-04;
        // x^13 : -0xd.76fa35fdf798p-19
        const vf_type erfc_i1_c13=-2.5681982832800171172999e-05;
        // x^14 : -0xb.6da3a40b0683p-19
        const vf_type erfc_i1_c14=-2.1797710819904308544078e-05;
        // x^15 : +0xc.e6363c0a35c28p-21
        const vf_type erfc_i1_c15=+6.1508488909078894529251e-06;
        // x^16 : +0xe.ae59a07aa1d7p-23
        const vf_type erfc_i1_c16=+1.7501181480315038643716e-06;
        // x^17 : -0xe.b598da16604f8p-24
        const vf_type erfc_i1_c17=-8.7674639135360295341307e-07;
        // x^18 : -0xc.558fa521527ap-27
        const vf_type erfc_i1_c18=-9.1897123302226876293458e-08;
        // x^19 : +0xc.b6dd7f5932538p-27
        const vf_type erfc_i1_c19=+9.4729045651409012425576e-08;
        // x^20 : +0xa.038a37b1fe3d8p-30
        const vf_type erfc_i1_c20=+9.3261038722361826518186e-09;
        // x^21 : -0xa.713a2a19131a8p-29
        const vf_type erfc_i1_c21=-1.9450287835670348636804e-08;
        // x^22 : +0xd.ab1c41f48e208p-31
        const vf_type erfc_i1_c22=+6.3648447056001057675020e-09;
        // x^23 : -0xd.c0f6f56ef1548p-34
        const vf_type erfc_i1_c23=-8.0057468096948020393389e-10;
        // x^ : +0xcp-4
        // const vf_type erfc_i1_left=+7.5000000000000000000000e-01;
        // x^ : +0x8.2cbdfp-3
        const vf_type erfc_i1_x0=+1.0218466520309448242188e+00;

        vf_type x_i1 = x - erfc_i1_x0;
        vf_type y_i1= impl::poly(x_i1,
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
                                 erfc_i1_c7);
        vf_type ye;
        impl::eft_poly(y_i1, ye, x_i1, y_i1,
                       erfc_i1_c6,
                       erfc_i1_c5,
                       erfc_i1_c4,
                       erfc_i1_c3,
                       erfc_i1_c2,
                       erfc_i1_c1,
                       erfc_i1_c0h);
        y_i1 += ye +erfc_i1_c0l;
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
        // const vf_type erfc_i2_left=+1.8750000000000000000000e+00;
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
        const vf_type erfc_i2_left=+1.8750000000000000000000e+00;
        vf_type r=select_branch(x < erfc_i2_left, s01, i2);
        return r;
    };

    vf_type y=s12();
    return y;
#endif
}

// Local Variables:
// mode: c++
// end:
#endif
