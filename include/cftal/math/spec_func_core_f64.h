//
// Copyright Axel Zeuner 2010-2019. Use, modification and
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


            static
            vi2_type
            __reduce_trigpi_arg(vf_type& __restrict xrh,
                                vf_type& __restrict xrl,
                                arg_t<vf_type> x);

            // calculates sin(pi*x), cos(pi*x)
            static
            void
            sinpi_cospi_k(arg_t<vf_type> xc,
                          vf_type* ps, vf_type *pc);

            static
            void
            sinpi_cospi_k(arg_t<vf_type> xc,
                          dvf_type* ps, dvf_type *pc);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

            static
            vf_type
            tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_0);

            // calculates lngamma for x in [1, 2]
            static
            dvf_type
            __lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // returns _xr in the range [1, 2]
            // returns _f (including sign)= (x+N)(x+_N-1)...(x-1)(x-2)
            // lgamma(x) = lgamma(xr) * log(abs(_f))
            struct reduced_small_gamma_args {
                dvf_type _xr, _f;
                reduced_small_gamma_args() : _xr(), _f() {};
                reduced_small_gamma_args(const dvf_type& xr, const dvf_type& f)
                    : _xr(xr), _f(f) {};
            };
            static
            reduced_small_gamma_args
            __lgamma_reduce_small_k(arg_t<vf_type> x);

            static
            vf_type
            lgamma_k(arg_t<vf_type> xc, vi_type* signp);

        };

    } // end math
} // end cftal

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vi2_type
cftal::math::spec_func_core<double, _T>::
__reduce_trigpi_arg(vf_type& xrh, vf_type& xrl, arg_t<vf_type> xc)
{
    vf_type fh= rint(vf_type(xc*2.0));
    xrh = xc - 0.5 * fh;
    // poor mans fmod:
    fh = base_type::template __fmod<4>(fh);
    // d_ops::add12cond(xrh, xrl, xc, fh*(-0.5f));
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    d_ops::mul122(xrh, xrl, xrh, ctbl::m_pi[0], ctbl::m_pi[1]);
    vi_type q0= _T::cvt_f_to_i(fh);
    vi2_type q=_T::vi_to_vi2(q0);
    return q;
}


template <typename _T>
void
cftal::math::spec_func_core<double, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    vf_type xrh, xrl;
    auto q=__reduce_trigpi_arg(xrh, xrl, xc);
    base_type::__sin_cos_k(xrh, xrl, q, ps, pc);
}

template <typename _T>
void
cftal::math::spec_func_core<double, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, dvf_type* ps, dvf_type* pc)
{
    vf_type xrh, xrl;
    auto q=__reduce_trigpi_arg(xrh, xrl, xc);
    base_type::__sin_cos_k(xrh, xrl, q, ps, pc);
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
        const double erf_i0_c1=+1.1283791670955125585607e+00;
        // x^3 : -0xc.093a3581bcdep-5
        const double erf_i0_c3=-3.7612638903183515104445e-01;
        // x^5 : +0xe.71790d0206a48p-7
        const double erf_i0_c5=+1.1283791670944255669529e-01;
        // x^7 : -0xd.c167188f35fap-9
        const double erf_i0_c7=-2.6866170642829659276352e-02;
        // x^9 : +0xa.b2de6784c358p-11
        const double erf_i0_c9=+5.2239775983210917642552e-03;
        // x^11 : -0xe.016d6a3ef017p-14
        const double erf_i0_c11=-8.5483250675988885734780e-04;
        // x^13 : +0xf.cd116c04eb3cp-17
        const double erf_i0_c13=+1.2055242224015018642075e-04;
        // x^15 : -0xf.a5d4b323d2f78p-20
        const double erf_i0_c15=-1.4922882834294901377502e-05;
        // x^17 : +0xd.c359e3d2a913p-23
        const double erf_i0_c17=+1.6406882240210931047373e-06;
        // x^19 : -0xa.83e395b26706p-26
        const double erf_i0_c19=-1.5668856230000872722501e-07;
        // x^21 : +0xa.6cd8665fd081p-30
        const double erf_i0_c21=+9.7092026848530503315802e-09;
        // x^23 : +0x8.91a24edd71ee8p-34
        const double erf_i0_c23=+4.9877462876900157143168e-10;
        vf_type xx= x*x;
        static const double c_y_i0[]= {
            erf_i0_c23,
            erf_i0_c21,
            erf_i0_c19,
            erf_i0_c17,
            erf_i0_c15,
            erf_i0_c13,
            erf_i0_c11,
            erf_i0_c9,
            erf_i0_c7
        };
        vf_type y_i0= horner2(xx, vf_type(xx*xx), c_y_i0);
        y_i0 = horner(xx, y_i0, erf_i0_c5, erf_i0_c3);
        vf_type ye;
        horner_comp_quick(y_i0, ye, xx, y_i0, erf_i0_c1);
        vf_type p_i;
        y_i0 = d_ops::two_prod(y_i0, x, p_i);
        ye = ye*x + p_i;
        y_i0 += ye;
        y = y_i0;
    }

    vmf_type x_in_i1 = (x > erf_i1_left) & (x<=erf_i2_left);
    if (likely(any_of(x_in_i1))) {
        // [0.75, 1.875] : | p - f | <= 2^-65.65625
        // coefficients for erf_i1 generated by sollya
        // x^0 h: +0xd.a00ad76b9204p-4
        const double erf_i1_c0h=+8.5157283924593318857887e-01;
        // x^0 l: +0xe.0bace157c715p-59
        const double erf_i1_c0l=+2.4365243665033013894766e-17;
        // x^1 : +0xc.b59ff8cfc23f8p-5
        const double erf_i1_c1=+3.9717100711829539383402e-01;
        // x^2 : -0xc.fcb4a8d44e408p-5
        const double erf_i1_c2=-4.0584786390758870178175e-01;
        // x^3 : +0x9.38b3dd1da6eb8p-6
        const double erf_i1_c3=+1.4408585160582162987275e-01;
        // x^4 : +0xf.c9546cfdda59p-8
        const double erf_i1_c4=+6.1665798768311033684064e-02;
        // x^5 : -0x8.c2586d568b56p-7
        const double erf_i1_c5=-6.8430951488233915380732e-02;
        // x^6 : +0xe.0ef0a178d53f8p-11
        const double erf_i1_c6=+6.8644332196564619361090e-03;
        // x^7 : +0xe.a1c48a68778fp-10
        const double erf_i1_c7=+1.4288969943769876808082e-02;
        // x^8 : -0xa.7d0064636f1fp-11
        const double erf_i1_c8=-5.1212340007889527865315e-03;
        // x^9 : -0xd.3bf0ea237c58p-13
        const double erf_i1_c9=-1.6154961932524462830951e-03;
        // x^10 : +0xa.29b9c60073768p-13
        const double erf_i1_c10=+1.2405994784913624163353e-03;
        // x^11 : +0x8.e07992a9980b8p-18
        const double erf_i1_c11=+3.3862514706578683988236e-05;
        // x^12 : -0xc.b25c1918cbf1p-16
        const double erf_i1_c12=-1.9373653876469861543144e-04;
        // x^13 : +0xd.76eba164d97cp-19
        const double erf_i1_c13=+2.5681558485523913555257e-05;
        // x^14 : +0xb.6d8849d428178p-19
        const double erf_i1_c14=+2.1796914760299927396733e-05;
        // x^15 : -0xc.e3e4daac0ea3p-21
        const double erf_i1_c15=-6.1465314806838005837327e-06;
        // x^16 : -0xe.b8e83c40bb9ap-23
        const double erf_i1_c16=-1.7550341642395222597627e-06;
        // x^17 : +0xe.9642d594a2f9p-24
        const double erf_i1_c17=+8.6945040884462715306098e-07;
        // x^18 : +0x8.434fa13b037d8p-26
        const double erf_i1_c18=+1.2312730855381382499845e-07;
        // x^19 : -0x9.8f7487e83636p-26
        const double erf_i1_c19=-1.4246064231133920797507e-07;
        // x^20 : +0x8.aad670629c2d8p-28
        const double erf_i1_c20=+3.2288337422680242895254e-08;
        // x^21 : -0x9.eb079386d623p-32
        const double erf_i1_c21=-2.3092339641415239179504e-09;
        // x^ : +0x8.2cbdfp-3
        const double erf_i1_x0=+1.0218466520309448242188e+00;
        vf_type x_i1 = x - erf_i1_x0;
        vf_type xx= x_i1*x_i1;
        static const double c[]={
            erf_i1_c21, erf_i1_c20, erf_i1_c19, erf_i1_c18, erf_i1_c17,
            erf_i1_c16, erf_i1_c15, erf_i1_c14, erf_i1_c13, erf_i1_c12,
            erf_i1_c11, erf_i1_c10, erf_i1_c9, erf_i1_c8, erf_i1_c7,
            erf_i1_c6, erf_i1_c5,  erf_i1_c4
        };
        vf_type y_i1= horner2(x_i1, xx, c);
        y_i1 = horner(x_i1, y_i1,
                      erf_i1_c3,
                      erf_i1_c2,
                      erf_i1_c1);
        vf_type ye;
        horner_comp_quick(y_i1, ye, x_i1, y_i1, erf_i1_c0h);
        y_i1 += ye+erf_i1_c0l;
        y = _T::sel(x_in_i1, y_i1, y);
    };

    vmf_type x_in_i2 = (x > erf_i2_left) & (x<=erf_i3_left);
    if (likely(any_of(x_in_i2))) {
        // [1.875, 3.5] : | p - f | <= 2^-60.90625
        // coefficients for erf_i2 generated by sollya
        // x^0 h: +0xf.ef9817e2c51a8p-4
        const double erf_i2_c0h=+9.9599465685270749393254e-01;
        // x^0 l: +0xe.ea4df2f66f138p-58
        const double erf_i2_c0l=+5.1747675271424131958331e-17;
        // x^1 : +0x9.3155c40283268p-9
        const double erf_i2_c1=+1.7954521347979746775936e-02;
        // x^2 : -0x9.5a5d850dd55p-8
        const double erf_i2_c2=-3.6535115226645986652443e-02;
        // x^3 : +0xb.27ecea03b4548p-8
        const double erf_i2_c3=+4.3577963955344252433566e-02;
        // x^4 : -0x8.3b98bb29e3f2p-8
        const double erf_i2_c4=-3.2159372038122829851048e-02;
        // x^5 : +0xd.6ac90b41e7748p-10
        const double erf_i2_c5=+1.3102666198825345736378e-02;
        // x^6 : -0xa.35ad2fc18ccb8p-15
        const double erf_i2_c6=-3.1157451986665293591425e-04;
        // x^7 : -0xc.09472b631ce8p-12
        const double erf_i2_c7=-2.9385356958251188097542e-03;
        // x^8 : +0xc.cb04cae657cdp-13
        const double erf_i2_c8=+1.5616506199860103777655e-03;
        // x^9 : -0x8.d557a80197158p-16
        const double erf_i2_c9=-1.3478651090391541278977e-04;
        // x^10 : -0xe.9984e98a632p-16
        const double erf_i2_c10=-2.2277350357451271289921e-04;
        // x^11 : +0xd.b21fada9734e8p-17
        const double erf_i2_c11=+1.0449063013853251036690e-04;
        // x^12 : -0xe.8c7985c2fb768p-23
        const double erf_i2_c12=-1.7343436820855339363241e-06;
        // x^13 : -0xe.c2fcb6920a32p-20
        const double erf_i2_c13=-1.4077824208156247784863e-05;
        // x^14 : +0x8.adcd11a64e448p-21
        const double erf_i2_c14=+4.1384269493855688456575e-06;
        // x^15 : +0xd.eafbd15889fep-24
        const double erf_i2_c15=+8.2957177961111339101782e-07;
        // x^16 : -0xe.921eb4322d228p-24
        const double erf_i2_c16=-8.6848622585478523869560e-07;
        // x^17 : +0xe.c887defc270c8p-26
        const double erf_i2_c17=+2.2028868239318452089703e-07;
        // x^18 : -0x9.d9038b554d91p-35
        const double erf_i2_c18=-2.8660609186842229174787e-10;
        // x^19 : -0xd.fb15b0fa873p-30
        const double erf_i2_c19=-1.3020634402817493488279e-08;
        // x^20 : +0xd.287a0e3c87118p-32
        const double erf_i2_c20=+3.0636117842102736309007e-09;
        // x^21 : -0x8.91299618558a8p-35
        const double erf_i2_c21=-2.4933370315452378001011e-10;
        // x^ : +0x8.23b4fp-2
        const double erf_i2_x0=+2.0348699092864990234375e+00;
        vf_type x_i2 = x - erf_i2_x0;
        vf_type xx= x_i2*x_i2;
        static const double c[]={
            erf_i2_c21, erf_i2_c20, erf_i2_c19, erf_i2_c18, erf_i2_c17,
            erf_i2_c16, erf_i2_c15, erf_i2_c14, erf_i2_c13, erf_i2_c12,
            erf_i2_c11, erf_i2_c10, erf_i2_c9, erf_i2_c8, erf_i2_c7,
            erf_i2_c6, erf_i2_c5,  erf_i2_c4
        };
        vf_type y_i2=horner2(x_i2, xx, c);
        y_i2 = horner(x_i2, y_i2,
                      erf_i2_c3,
                      erf_i2_c2,
                      erf_i2_c1);
        vf_type ye;
        horner_comp_quick(y_i2, ye, x_i2, y_i2, erf_i2_c0h);
        y_i2 += ye+erf_i2_c0l;
        y = _T::sel(x_in_i2, y_i2, y);
    };

    vmf_type x_in_i3 = (x > erf_i3_left);
    if (likely(any_of(x_in_i3))) {
        // [3.5, 6] : | p - f | <= 2^-58.109375
        // coefficients for erf_i3 generated by sollya
        // x^0 h: +0xf.ffff9c4350758p-4
        const double erf_i3_c0h=+9.9999962845052203785912e-01;
        // x^0 l: +0xb.caf1dd3904968p-58
        const double erf_i3_c0l=+4.0914331138571226372713e-17;
        // x^1 : +0xb.9b8659624d8f8p-22
        const double erf_i3_c1=+2.7674481285657176957832e-06;
        // x^2 : -0xa.6e12c20f42108p-20
        const double erf_i3_c2=-9.9467980623786509997196e-06;
        // x^3 : +0xc.031fb3a65261p-19
        const double erf_i3_c3=+2.2911457978090595856164e-05;
        // x^4 : -0x9.eca80dc283bcp-18
        const double erf_i3_c4=-3.7858731448027949009066e-05;
        // x^5 : +0xc.77654fc74de58p-18
        const double erf_i3_c5=+4.7555502482858254557820e-05;
        // x^6 : -0xc.4a021f4b75ad8p-18
        const double erf_i3_c6=-4.6879176646772150371858e-05;
        // x^7 : +0x9.a6d073de7f738p-18
        const double erf_i3_c7=+3.6818001687864182383102e-05;
        // x^8 : -0xc.13cdc36c5f8dp-19
        const double erf_i3_c8=-2.3035733127395927705931e-05;
        // x^9 : +0xb.c7c1a19a2d53p-20
        const double erf_i3_c9=+1.1234567955526363942529e-05;
        // x^10 : -0x8.529e8bd618bf8p-21
        const double erf_i3_c10=-3.9685877435520957654653e-06;
        // x^11 : +0xc.547e8a04dfc2p-24
        const double erf_i3_c11=+7.3492859804616469880764e-07;
        // x^12 : +0xc.85ec9d5c5b36p-26
        const double erf_i3_c12=+1.8660935317950479413396e-07;
        // x^13 : -0xf.8fd15d59bd238p-26
        const double erf_i3_c13=-2.3188871742844543630620e-07;
        // x^14 : +0xf.3ed20621d0eap-27
        const double erf_i3_c14=+1.1358702340129324142554e-07;
        // x^15 : -0x9.f61fc73b32e1p-28
        const double erf_i3_c15=-3.7109190216543264217597e-08;
        // x^16 : +0x9.50a9702108248p-30
        const double erf_i3_c16=+8.6753493349650820866145e-09;
        // x^17 : -0xc.4cc58c305bdb8p-33
        const double erf_i3_c17=-1.4318955756438658326616e-09;
        // x^18 : +0xa.9fa758a91467p-36
        const double erf_i3_c18=+1.5459441423225671075377e-10;
        // x^19 : -0x9.8b0042d43c5d8p-40
        const double erf_i3_c19=-8.6792831401194721286056e-12;
        // x^20 : -0xf.835a0e526809p-50
        const double erf_i3_c20=-1.3778394331846918471113e-14;
        // x^21 : +0xc.1aecc242ad2p-49
        const double erf_i3_c21=+2.1503110675247887643702e-14;
        // x^ : +0xe.60796p-2
        const double erf_i3_x0=+3.5942130088806152343750e+00;


        vf_type x_i3 = x - erf_i3_x0;
        vf_type xx= x_i3*x_i3;
        static const double c[]={
            erf_i3_c21, erf_i3_c20, erf_i3_c19, erf_i3_c18, erf_i3_c17,
            erf_i3_c16, erf_i3_c15, erf_i3_c14, erf_i3_c13, erf_i3_c12,
            erf_i3_c11, erf_i3_c10, erf_i3_c9, erf_i3_c8, erf_i3_c7,
            erf_i3_c6, erf_i3_c5,  erf_i3_c4
        };
        vf_type y_i3=horner2(x_i3, xx, c);
        y_i3 = horner(x_i3, y_i3,
                      erf_i3_c3,
                      erf_i3_c2,
                      erf_i3_c1);
        vf_type ye;
        horner_comp_quick(y_i3, ye, x_i3, y_i3, erf_i3_c0h);
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
    vi_type k=0;
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
        vf_type xrh, xrl;
        vi_type idx;
        base_type::__reduce_exp_arg(xrh, xrl, idx, k, x2h, x2l);
        exh=base_type::template __exp_tbl_k<
            base_type::result_prec::high>(xrh, xrl, idx, &exl);
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

        static const double ci0[]={
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
            erfc_i0_c3
        };
        i0h = horner2(x2h, vf_type(x2h*x2h), ci0);
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
            const double erfc_i1_c0h=+4.5638700783238173031009e-01;
            // x^0 l: +0xa.d84458027608p-60
            const double erfc_i1_c0l=+9.4063583688085847229697e-18;
            // x^1 : +0xe.491a04c8c74cp-7
            const double erfc_i1_c1=+1.1160588487251243972054e-01;
            // x^2 : -0xa.2f2e2cef14d4p-7
            const double erfc_i1_c2=-7.9564830723177437654670e-02;
            // x^3 : +0xc.04e45b228aecp-8
            const double erfc_i1_c3=+4.6949646234263731070513e-02;
            // x^4 : -0xc.81f3181aaca28p-9
            const double erfc_i1_c4=-2.4428936664969275877057e-02;
            // x^5 : +0xb.d768c57589a98p-10
            const double erfc_i1_c5=+1.1563908626507723650945e-02;
            // x^6 : -0xa.63b9b4a1478e8p-11
            const double erfc_i1_c6=-5.0730236290837090254446e-03;
            // x^7 : +0x8.8d49ff8862c7p-12
            const double erfc_i1_c7=+2.0878687432960901446122e-03;
            // x^8 : -0xd.52c57361f90b8p-14
            const double erfc_i1_c8=-8.1319124504336786751074e-04;
            // x^9 : +0x9.e2cbf3c4e126p-15
            const double erfc_i1_c9=+3.0169447521813798178403e-04;
            // x^10 : -0xe.0bb151c7a8528p-17
            const double erfc_i1_c10=-1.0715999168492641908674e-04;
            // x^11 : +0x9.977b7170369bp-18
            const double erfc_i1_c11=+3.6589536066079111453590e-05;
            // x^12 : -0xc.a2ab8ebd56438p-20
            const double erfc_i1_c12=-1.2050085316536611183716e-05;
            // x^13 : +0x8.0ccdcd4bed6b8p-21
            const double erfc_i1_c13=+3.8385464136067494822307e-06;
            // x^14 : -0x9.f2c8b4ede0f7p-23
            const double erfc_i1_c14=-1.1859387209455998480028e-06;
            // x^15 : +0xb.f40aca445959p-25
            const double erfc_i1_c15=+3.5623579156227751425936e-07;
            // x^16 : -0xd.ee6cf0d2c7e4p-27
            const double erfc_i1_c16=-1.0379664453424312714811e-07;
            // x^17 : +0xf.68af910b030dp-29
            const double erfc_i1_c17=+2.8701366732499267312170e-08;
            // x^18 : -0xf.378a81de6765p-31
            const double erfc_i1_c18=-7.0859478803687918441900e-09;
            // x^19 : +0xc.09f239228b7b8p-33
            const double erfc_i1_c19=+1.4015068628896234563066e-09;
            // x^20 : -0xc.ee9ba8cd582ap-36
            const double erfc_i1_c20=-1.8818627975554374952333e-10;
            // x^21 : +0xd.a3aa20852e5p-40
            const double erfc_i1_c21=+1.2404884439545507477160e-11;
            // x^ : +0xcp-4
            // const double erfc_i1_left=+7.5000000000000000000000e-01;
            // x^ : +0x9.c061p-3
            const double erfc_i1_x0=+1.2189350128173828125000e+00;
            vf_type x_i1 = x - erfc_i1_x0;
            vf_type i1h, i1l;

            vf_type x_i1_sqr= x_i1* x_i1;
            static const double c[]={
                erfc_i1_c21, erfc_i1_c20, erfc_i1_c19, erfc_i1_c18,
                erfc_i1_c17, erfc_i1_c16, erfc_i1_c15, erfc_i1_c14,
                erfc_i1_c13, erfc_i1_c12, erfc_i1_c11, erfc_i1_c10,
                erfc_i1_c9,  erfc_i1_c8
            };
            i1h=horner2(x_i1, x_i1_sqr, c);
            i1h = horner(x_i1, i1h,
                         erfc_i1_c7, erfc_i1_c6,
                         erfc_i1_c5, erfc_i1_c4,
                         erfc_i1_c3, erfc_i1_c2, erfc_i1_c1);
            i1h *= x_i1;
            d_ops::add122cond(i1h, i1l, i1h, erfc_i1_c0h, erfc_i1_c0l);
            i123h= i1h;
            i123l= i1l;
        }
        if (likely(any_of(x_in_i2))) {
            // [2.75, 6] : | p - f | <= 2^-60.78125
            // coefficients for erfc_i2 generated by sollya
            // x^0 h: +0x8.b6be4ee0e3cf8p-4
            const double erfc_i2_c0h=+5.4461508571533900902040e-01;
            // x^0 l: -0xf.671435e10336p-60
            const double erfc_i2_c0l=-1.3359671127367542122339e-17;
            // x^1 : +0xa.16d74869fa14p-10
            const double erfc_i2_c1=+9.8527563045483629311505e-03;
            // x^2 : -0xe.d301c034b6d9p-12
            const double erfc_i2_c2=-3.6192005530161991747051e-03;
            // x^3 : +0x9.6ff24eeab773p-13
            const double erfc_i2_c3=+1.1520130713824016342739e-03;
            // x^4 : -0xa.ffdc08a0d9bd8p-15
            const double erfc_i2_c4=-3.3567661126348403250949e-04;
            // x^5 : +0xc.08d7ee8566bap-17
            const double erfc_i2_c5=+9.1816290715132132822102e-05;
            // x^6 : -0xc.887d80312e89p-19
            const double erfc_i2_c6=-2.3905115107495057615462e-05;
            // x^7 : +0xc.883cc02440b08p-21
            const double erfc_i2_c7=+5.9758076571828292662702e-06;
            // x^8 : -0xc.1a3be6d993c6p-23
            const double erfc_i2_c8=-1.4427276287414592112544e-06;
            // x^9 : +0xb.55dd7bd65fcp-25
            const double erfc_i2_c9=+3.3782156776389365591615e-07;
            // x^10 : -0xa.5477bd400695p-27
            const double erfc_i2_c10=-7.6964140505220350364034e-08;
            // x^11 : +0x9.2e98812edf9dp-29
            const double erfc_i2_c11=+1.7102834835369625553510e-08;
            // x^12 : -0xf.f3fc9d2840758p-32
            const double erfc_i2_c12=-3.7143643321806636143601e-09;
            // x^13 : +0xd.90ea70083d63p-34
            const double erfc_i2_c13=+7.8964962357884016169953e-10;
            // x^14 : -0xb.5034a2ead7708p-36
            const double erfc_i2_c14=-1.6463022864863182286291e-10;
            // x^15 : +0x9.48326e811c72p-38
            const double erfc_i2_c15=+3.3767790322690686244921e-11;
            // x^16 : -0xf.008d0c171947p-41
            const double erfc_i2_c16=-6.8221889750437386369149e-12;
            // x^17 : +0xb.b4c57a7769f08p-43
            const double erfc_i2_c17=+1.3308338431005692045565e-12;
            // x^18 : -0x8.3d69a3d340728p-45
            const double erfc_i2_c18=-2.3419184991537750722353e-13;
            // x^19 : +0x9.44ce323295aap-48
            const double erfc_i2_c19=+3.2929290592266954093199e-14;
            // x^20 : -0xd.fddde3facf0bp-52
            const double erfc_i2_c20=-3.1067741781483397623413e-15;
            // x^21 : +0xa.3910a3ae7e2p-56
            const double erfc_i2_c21=+1.4187137779577336243611e-16;
            // x^ : +0xbp-2
            // const double erfc_i2_left=+2.7500000000000000000000e+00;
            // x^ : +0xe.6c9f6p-2
            const double erfc_i2_x0=+3.6060767173767089843750e+00;
            vf_type x_i2 = x - erfc_i2_x0;
            vf_type i2h, i2l;
            vf_type x_i2_sqr= x_i2* x_i2;
            static const double c[]={
                erfc_i2_c21, erfc_i2_c20, erfc_i2_c19, erfc_i2_c18,
                erfc_i2_c17, erfc_i2_c16, erfc_i2_c15, erfc_i2_c14,
                erfc_i2_c13, erfc_i2_c12, erfc_i2_c11, erfc_i2_c10,
                erfc_i2_c9, erfc_i2_c8, erfc_i2_c7, erfc_i2_c6,
                erfc_i2_c5, erfc_i2_c4, erfc_i2_c3, erfc_i2_c2,
                erfc_i2_c1
            };
            i2h = horner2(x_i2, x_i2_sqr, c);
            i2h *= x_i2;
            d_ops::add122cond(i2h, i2l, i2h, erfc_i2_c0h, erfc_i2_c0l);
            i123h = _T::sel(x_gt_2_75, i2h, i123h);
            i123l = _T::sel(x_gt_2_75, i2l, i123l);
        }
        vf_type inv_x, inv_x_l;
        d_ops::rcp12(inv_x, inv_x_l, x);
        if (likely(any_of(x_in_i3))) {
            // [3.6697246134281158447265625e-2, 0.16666667163372039794921875] : | p - f | <= 2^-60.515625
            // coefficients for erfc generated by sollya
            // x^0 : +0x9.06eba82144228p-4
            const double erfc_i3_c0=+5.6418958354721182590907e-01;
            // x^1 : +0xd.8d9c4446e07p-37
            const double erfc_i3_c1=+9.8612259103624561244669e-11;
            // x^2 : -0x9.06ebac7c03518p-5
            const double erfc_i3_c2=-2.8209479988445645970430e-01;
            // x^3 : +0xd.799c43ef18e28p-25
            const double erfc_i3_c3=+4.0158750624281484922580e-07;
            // x^4 : +0xd.8a456e51c91ep-5
            const double erfc_i3_c4=+4.2312881037495109204372e-01;
            // x^5 : +0xa.6511389850f2p-15
            const double erfc_i3_c5=+3.1722393868219137848252e-04;
            // x^6 : -0x8.81ccb34294a3p-3
            const double erfc_i3_c6=-1.0633787159627714480337e+00;
            // x^7 : +0x9.2d944f6cb446p-7
            const double erfc_i3_c7=+7.1703470975451988334015e-02;
            // x^8 : +0xc.063eeb629ba3p-2
            const double erfc_i3_c8=+3.0060993937430877664951e+00;
            // x^9 : +0xa.06df1211bf4p-1
            const double erfc_i3_c9=+5.0134206434883026304306e+00;
            // x^10 : -0xa.ac34d8fca9c98p+2
            const double erfc_i3_c10=-4.2690725561849056646224e+01;
            // x^11 : +0xb.6b5e28424a428p+3
            const double erfc_i3_c11=+9.1355243806336218881370e+01;
            // x^12 : -0xb.0eb6cc3d336b8p+3
            const double erfc_i3_c12=-8.8459814185650756712676e+01;
            // x^13 : +0xf.5604386f36c5p+1
            const double erfc_i3_c13=+3.0672003797820742931890e+01;
            vf_type inv_x2= inv_x*inv_x;

            static const double c[]={
                erfc_i3_c13, erfc_i3_c12, erfc_i3_c11, erfc_i3_c10,
                erfc_i3_c9, erfc_i3_c8, erfc_i3_c7, erfc_i3_c6,
                erfc_i3_c5, erfc_i3_c4, erfc_i3_c3, erfc_i3_c2,
                erfc_i3_c1
            };
            vf_type i3h, i3l;
            i3h = horner2(inv_x, inv_x2, c);
            i3h *= inv_x;
            d_ops::add12cond(i3h, i3l, i3h, erfc_i3_c0);
            i123h = _T::sel(x_gt_6_00, i3h, i123h);
            i123l = _T::sel(x_gt_6_00, i3l, i123l);
        }
        // multiply with e^(-x^2)
        d_ops::mul22(i123h, i123l, exh, exl, i123h, i123l);
        // divide by x
        vf_type rh, rl;
        d_ops::mul22(rh, rl, i123h, i123l, inv_x, inv_x_l);
        auto sc=base_type::__scale_exp_k(k);
        rh *= sc.f0();
        rl *= sc.f0();
        rh *= sc.f1();
        rl *= sc.f1();
        i123h = rh;
        i123l = rl;
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
tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_zero)
{
    // G(z+1) = z * G(z)
    // G(z) * G(1-z) = pi/sin(pi*z)
    // with G(-z+1) = -z * G(z)
    // G(z) * -z * G(-z) = pi/sin(pi*z)
    // G(-z) = -pi/[sin(pi*z)*z * G(z)]
    // legendre's doubling formula:
    // G(2z) = 2^(2*z-1)*pi^(-1/2)*G(z+1/2)*G(z)

    vf_type xa=abs(x);
    // lanczos sum:
    using lanczos_ratfunc = lanczos_table_g_12_06815_N12;

    auto pq=lanczos_rational_at(xa,
                                lanczos_ratfunc::pd,
                                lanczos_ratfunc::q);
    vf_type sum = pq[0], sum_l= pq[1];
    // base of the Lanczos exponential
    vf_type base, base_l;
    d_ops::add122cond(base, base_l, xa,
                      lanczos_ratfunc::gm0_5(),
                      lanczos_ratfunc::gm0_5_l());
    vf_type zh, zl;
    d_ops::add12cond(zh, zl, xa,  -0.5);
    vf_type gh, gl;
    base_type::exp_k2(gh, gl, -base, -base_l);
    d_ops::mul22(gh, gl, gh, gl, sum, sum_l);
    if (any_of(x_lt_zero)) {
        dvf_type s;
        sinpi_cospi_k(xa, &s, nullptr);
        // vf_type r_n = -M_PI/(s * x0 * r);
        using ctbl = impl::d_real_constants<d_real<double>, double>;
        const dvf_type p=-ctbl::m_pi;
        // dvf_type q=s * (xa *dvf_type(gh, gl));
        dvf_type q;
        d_ops::mul122(q[0], q[1], xa, gh, gl);
        d_ops::mul22(q[0], q[1], q[0], q[1], s[0], s[1]);
        // g_n = p / q;
        dvf_type g_n;
        d_ops::div22(g_n[0], g_n[1], p[0], p[1], q[0], q[1]);
        gh = _T::sel(x_lt_zero, g_n[0], gh);
        gl = _T::sel(x_lt_zero, g_n[1], gl);
        zh = _T::sel(x_lt_zero, -zh, zh);
        zl = _T::sel(x_lt_zero, -zl, zl);
    }
    auto p_sc=base_type::pow_k2(base, base_l, 0.5*zh, 0.5*zl);
    const dvf_type& powh= p_sc.first;
    d_ops::mul22(gh, gl, powh[0], powh[1], gh, gl);
    d_ops::mul22(gh, gl, powh[0], powh[1], gh, gl);
    const auto& sc=p_sc.second;
    gh *= sc.f0();
    gh *= sc.f1();
    gh *= sc.f0();
    gh *= sc.f1();
    gh = _T::sel(xa < 0x1p-54, 1.0/x, gh);
    return gh;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::dvf_type
cftal::math::spec_func_core<double, _T>::
__lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    // [1, 2] : | p - f | <= 2^-72.9375
    // coefficients for lngamma generated by sollya
    // x^0 h: +0xe.7d56bc1649568p-3
    const double lngamma_i0_c0h=+1.8112005895901959195982e+00;
    // x^0 l: +0xd.068d70b1d342p-58
    const double lngamma_i0_c0l=+4.5191613320884300760087e-17;
    // x^1 h: -0xf.c70f7849fe26p-1
    const double lngamma_i0_c1h=-7.8887899008105470954888e+00;
    // x^1 l: +0x8.bcf73eab5018p-57
    const double lngamma_i0_c1l=+6.0633079503556026048504e-17;
    // x^2 h: +0x9.bc69656668658p+2
    const double lngamma_i0_c2h=+3.8943932867057434066282e+01;
    // x^2 l: +0x9.71724c86f5e9p-52
    const double lngamma_i0_c2l=+2.0968005805708429897311e-15;
    // x^3 : -0x9.bc2050a4d82fp+4
    const double lngamma_i0_c3=-1.5575788940803880677777e+02;
    // x^4 : +0xf.8f4c58121a7c8p+5
    const double lngamma_i0_c4=+4.9791227735656099184780e+02;
    // x^5 : -0xa.1b41ca3d644e8p+7
    const double lngamma_i0_c5=-1.2936284960923142079992e+03;
    // x^6 : +0xa.db79c085b5e9p+8
    const double lngamma_i0_c6=+2.7794755939072720138938e+03;
    // x^7 : -0x9.c8e97e488a438p+9
    const double lngamma_i0_c7=-5.0098241663622966370895e+03;
    // x^8 : +0xe.f62fb4d5dedb8p+9
    const double lngamma_i0_c8=+7.6603727061594172482728e+03;
    // x^9 : -0x9.c99c06b5257p+10
    const double lngamma_i0_c9=-1.0022437909399566706270e+04;
    // x^10 : +0xb.07239d00c6598p+10
    const double lngamma_i0_c10=+1.1292556457704258718877e+04;
    // x^11 : -0xa.c0271f86839e8p+10
    const double lngamma_i0_c11=-1.1008611299160513226525e+04;
    // x^12 : +0x9.189a2042fa4p+10
    const double lngamma_i0_c12=+9.3144082190936896950006e+03;
    // x^13 : -0xd.6211a96bef07p+9
    const double lngamma_i0_c13=-6.8521379828374028875260e+03;
    // x^14 : +0x8.9068d405cadbp+9
    const double lngamma_i0_c14=+4.3848189704170708864694e+03;
    // x^15 : -0x9.86db5229afap+8
    const double lngamma_i0_c15=-2.4388567224553844425827e+03;
    // x^16 : +0x9.311755e915f3p+7
    const double lngamma_i0_c16=+1.1765455773200314979476e+03;
    // x^17 : -0xf.543cda5bdcf6p+5
    const double lngamma_i0_c17=-4.9052971336143559710763e+02;
    // x^18 : +0xa.fd211ab58f3ep+4
    const double lngamma_i0_c18=+1.7582058211251921875373e+02;
    // x^19 : -0xd.72190676196cp+2
    const double lngamma_i0_c19=-5.3782777419406272656488e+01;
    // x^20 : +0xd.e6cd6ab4bfa08p+0
    const double lngamma_i0_c20=+1.3901571911933958247687e+01;
    // x^21 : -0xb.fb619ed1640fp-2
    const double lngamma_i0_c21=-2.9954895797063860740650e+00;
    // x^22 : +0x8.73780310995a8p-4
    const double lngamma_i0_c22=+5.2819062421038742716206e-01;
    // x^23 : -0x9.809084ddd7ab8p-7
    const double lngamma_i0_c23=-7.4235978008514322268319e-02;
    // x^24 : +0x8.3087e7767aaf8p-10
    const double lngamma_i0_c24=+7.9976305984199008020097e-03;
    // x^25 : -0xa.2917da1ae0338p-14
    const double lngamma_i0_c25=-6.2014893812368805225271e-04;
    // x^26 : +0x8.13b39059dc29p-18
    const double lngamma_i0_c26=+3.0811152180607593296414e-05;
    // x^27 : -0xc.5bd71a5a2eb2p-24
    const double lngamma_i0_c27=-7.3663896086015872528082e-07;
    const static double ci[]= {
        lngamma_i0_c27,
        lngamma_i0_c26,
        lngamma_i0_c25,
        lngamma_i0_c24,
        lngamma_i0_c23,
        lngamma_i0_c22,
        lngamma_i0_c21,
        lngamma_i0_c20,
        lngamma_i0_c19,
        lngamma_i0_c18,
        lngamma_i0_c17,
        lngamma_i0_c16,
        lngamma_i0_c15,
        lngamma_i0_c14,
        lngamma_i0_c13,
        lngamma_i0_c12,
        lngamma_i0_c11,
        lngamma_i0_c10,
        lngamma_i0_c9,
        lngamma_i0_c8,
        lngamma_i0_c7,
        lngamma_i0_c6,
        lngamma_i0_c5,
        lngamma_i0_c4,
        lngamma_i0_c3
    };

    vf_type ph, pl;
    const double* pci=ci;
    d_ops::mul122(ph, pl, pci[0], xh, xl);
    const std::size_t N=std::distance(std::cbegin(ci), std::cend(ci));
#pragma GCC unroll 0
#pragma clang loop unroll(disable)
    for (std::size_t i=1; i<N; ++i) {
        d_ops::add122(ph, pl, pci[i], ph, pl);
        d_ops::mul22(ph, pl, xh, xl, ph, pl);
    }
    d_ops::add22(ph, pl, ph, pl, lngamma_i0_c2h, lngamma_i0_c2l);
    d_ops::mul22(ph, pl, xh, xl, ph, pl);
    d_ops::add22(ph, pl, ph, pl, lngamma_i0_c1h, lngamma_i0_c1l);
    d_ops::mul22(ph, pl, xh, xl, ph, pl);
    d_ops::add22(ph, pl, ph, pl, lngamma_i0_c0h, lngamma_i0_c0l);
    vf_type xm1h, xm1l;
    d_ops::add212(xm1h, xm1l, xh, xl, -1.0);
    vf_type xm2h, xm2l;
    d_ops::add122(xm2h, xm2l, -2.0, xh, xl);
    vf_type th, tl;
    d_ops::mul22(th, tl, xm1h, xm1l, xm2h, xm2l);
    d_ops::mul22(th, tl, ph, pl, th, tl);
    return dvf_type(th, tl);
}

template <typename _T>
__attribute__((optimize("no-unroll-loops")))
typename cftal::math::spec_func_core<double, _T>::reduced_small_gamma_args
cftal::math::spec_func_core<double, _T>::
__lgamma_reduce_small_k(arg_t<vf_type> xc)
{
    dvf_type x=xc;
    dvf_type f0=vf_type(1.0);
    vf_type f1(1.0);
    vmf_type t;

    const double il=1.0;
    const double ir=2.0;

    if (any_of(t= x[0]>vf_type(ir))) {
        // x -= _T::sel(t, 1.0, 0.0);
        // dvf_type p= select(t, x, dvf_type(1.0));
        x -= _T::sel(t, 1.0, 0.0);
        f0[0]=_T::sel(t, x[0], 1.0);
        while (any_of(t= x[0]>vf_type(ir))) {
            // x -= _T::sel(t, 1.0, 0.0);
            // dvf_type p= select(t, x, dvf_type(1.0));
            x -= _T::sel(t, 1.0, 0.0);
#if 0
            dvf_type p= select(t, x, dvf_type(1.0));
            f0 *= p;
#else
            vf_type p= select(t, x[0], vf_type(1.0));
            // f *= p;
            // d_ops::mul122(f0[0], f0[1], p, f0[0], f0[1]);
            // compensated product:
            vf_type pl;
            d_ops::mul12(f0[0], pl, f0[0], p);
            f0[1] = f0[1] * p + pl;
#endif
#if 0
            // avoid overflows in f0
            if (any_of(t=f0[0] > 0x1p500)) {
                vf_type h=_T::sel(t, 0x1p-501, 1.0);
                f0[1] *= h;
                f0[0] *= h;
                f1 *= _T::sel(t, 0x1p501, 1.0);
            }
#endif
        }
    }

    if (any_of(t= x[0]<vf_type(il))) {
        dvf_type q0(_T::sel(t, x[0], 1.0), vf_type(0.0));
        x += _T::sel(t, 1.0, 0.0);
        // see below
        while(any_of(t= x[0]<vf_type(-1.0))) {
#if 0
            dvf_type q= select(t, x, dvf_type(1.0));
            q0 *= q;
#else
            vf_type q= _T::sel(t, x[0], vf_type(1.0));
            // q0 *= q;
            // d_ops::mul122(q0[0], q0[1], q, q0[0], q0[1]);
            vf_type pl;
            d_ops::mul12(q0[0], pl, q0[0], q);
            q0[1] = q0[1] * q + pl;
#endif
            x += _T::sel(t, 1.0, 0.0);
#if 0
            // avoid overflows in q0
            if (any_of(t=abs(q0[0]) > 0x1p500)) {
                vf_type h=_T::sel(t, 0x1p-501, 1.0);
                q0[1] *= h;
                q0[0] *= h;
                // we divide by f1
                f1 *= h;
            }
#endif
        }
        // the range between -1 and 1 must be handled more precise
        while(any_of(t= x[0]<vf_type(il))) {
            dvf_type q= select(t, x, dvf_type(1.0));
            q0 *= q;
            x += _T::sel(t, 1.0, 0.0);
        }
        // f0 /= q0;
        f0 = d_ops::sloppy_div(f0, q0);
    }
    return reduced_small_gamma_args{x, f0};
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
lgamma_k(arg_t<vf_type> xc, vi_type* signp)
{
    vf_type xa=abs(xc);
    constexpr const double x_tiny= 0x1p-54;
    constexpr const double x_small_delta = 6.0;
    constexpr const double x_small_left  = 1.0-x_small_delta;
    constexpr const double x_small_right = 2.0+x_small_delta;
    constexpr const double x_large= 0x1p54;

    reduced_small_gamma_args sst;

    // the reflection implementation below works only if the
    // reflection for really tiny values delegated to __lgamma_small_k
    static_assert(x_small_left < - x_tiny, "constraint violated");
    vmf_type xa_in_small =
        ((xc >= x_small_left) & (xc <= x_small_right) & (xa >= x_tiny));

    vf_type base_h=xa, base_l=0.0;
    if (any_of(xa_in_small)) {
        vf_type xs=_T::sel(xa_in_small, xc, 1.5);
        sst = __lgamma_reduce_small_k(xs);
        dvf_type log_a=select(sst._f[0]>0, sst._f, -sst._f);
        base_h = _T::sel(xa_in_small, log_a[0], base_h);
        base_l = _T::sel(xa_in_small, log_a[1], base_l);
    }

    using lanczos_ratfunc = lanczos_table_g_12_06815_N12;
    vmf_type xa_in_lanczos =
        (((xc < x_small_left) | (xc > x_small_right)) & (xa < x_large));
    if (any_of(xa_in_lanczos)) {
        vf_type th, tl;
        d_ops::add122cond(th, tl, xa,
                          lanczos_ratfunc::gm0_5(),
                          lanczos_ratfunc::gm0_5_l());
        base_h= _T::sel(xa_in_lanczos, th, base_h);
        base_l= _T::sel(xa_in_lanczos, tl, base_l);
    }
    // lb contains log(xa+g-0.5) for xa_in_lanczos
    // log(xa) for xa > x_large | xa < x_tiny
    // log(f) for xa < x_small & xa >= tiny
    dvf_type lb= base_type::template
        __pow_log_k2<base_type::log_func::c_log_e,
                     base_type::result_prec::high>(base_h, base_l);

    vf_type lgh=0.0, lgl=0.0;
    vmf_type xa_in_large = (xa >= x_large);
    if (any_of(xa_in_large)) {
        // log(gamma(x)) = xa * (log(xa) - 1.0), xa >> 1
        vf_type th, tl;
        d_ops::add212(th, tl, lb[0], lb[1], -1.0);
        d_ops::mul122(th, tl, xa, th, tl);
        lgh = _T::sel(xa_in_large, th, lgh);
        lgl = _T::sel(xa_in_large, tl, lgl);
    }
    if (any_of(xa_in_lanczos)) {
        // lanczos sum:
        auto pq=lanczos_rational_at(xa,
                                    lanczos_ratfunc::pd,
                                    lanczos_ratfunc::q);

        vf_type sum_h = pq[0], sum_l= pq[1];
        vf_type zh, zl;
        d_ops::add12cond(zh, zl, xa,  -0.5);

        // g = z * log(base) + log(sum) - base;
        dvf_type ls=base_type::template
            __pow_log_k2<base_type::log_func::c_log_e,
                         base_type::result_prec::high>(sum_h, sum_l);
        vf_type th, tl;
        d_ops::mul22(th, tl, zh, zl, lb[0], lb[1]);
        d_ops::add22cond(th, tl, th, tl, -base_h, -base_l);
        d_ops::add22cond(th, tl, th, tl, ls[0], ls[1]);
        lgh = _T::sel(xa_in_lanczos, th, lgh);
        lgl = _T::sel(xa_in_lanczos, tl, lgl);
    }
    if (any_of(xa_in_small)) {
        dvf_type lg12=__lgamma_1_2_k(sst._xr[0], sst._xr[1]);
        vf_type th, tl;
        d_ops::add22cond(th, tl, lb[0], lb[1], lg12[0], lg12[1]);
        lgh = _T::sel(xa_in_small, th, lgh);
        lgl = _T::sel(xa_in_small, tl, lgl);
    }
    // xa_in_tiny:
    vmf_type xa_in_tiny= xa < x_tiny;
    lgh = _T::sel(xa_in_tiny, -lb[0], lgh);

    // reflection part
    vi_type sgn=1;
    vmf_type x_lt_0 = xc < 0.0;
    if (any_of(x_lt_0)) {
        // tiny
        vmf_type t= x_lt_0 & xa_in_tiny;
        sgn = _T::sel(_T::vmf_to_vmi(t), -1, sgn);
        // small
        t = x_lt_0 & xa_in_small;
        if (any_of(t)) {
            vf_type sgn_g=copysign(vf_type(1.0), sst._f[0]);
            vi_type si= _T::cvt_f_to_i(sgn_g);
            sgn=_T::sel(_T::vmf_to_vmi(t), si, sgn);
        }
        // lanczos
        t = x_lt_0 & xa_in_lanczos;
        if (any_of(t)) {
            // G(-z) = -pi/[sin(pi*z)*z * G(z)]
            dvf_type s;
            sinpi_cospi_k(xa, &s, nullptr);
            using ctbl = impl::d_real_constants<d_real<double>, double>;
            // log(G(-z)) = log(pi) - log(z) - log(abs(sin(pi*z))-log(G(z))
            //            = log(pi) - log(abs(sin(pi*z)*z) - log(G(z))
            //            = log(pi) - [log(abs(sin(pi*z)*z) + log(G(z))]
            dvf_type sa= select(s[0] < 0.0, -s, s);
            d_ops::mul122(sa[0], sa[1], xa, sa[0], sa[1]);
            dvf_type lg_n=base_type::template
                __pow_log_k2<base_type::log_func::c_log_e,
                             base_type::result_prec::high>(sa[0], sa[1]);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             lg_n[0], lg_n[1],
                             lgh, lgl);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             ctbl::m_ln_pi[0], ctbl::m_ln_pi[1],
                             -lg_n[0], -lg_n[1]);
            lgh = _T::sel(t, lg_n[0], lgh);
            vmf_type s_lt_0 = (s[0] >= 0.0) & t;
            vmi_type i_s_lt_0 = _T::vmf_to_vmi(s_lt_0);
            sgn = _T::sel(i_s_lt_0, -1, sgn);
        }
        // no large handling because xc is integer anyway
    }
    if (signp != nullptr)
        *signp = sgn;
    return lgh;
}


// Local Variables:
// mode: c++
// end:
#endif
