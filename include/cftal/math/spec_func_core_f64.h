//
// Copyright (C) 2010-2022 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_MATH_SPEC_FUNC_CORE_F64_H__)
#define __CFTAL_MATH_SPEC_FUNC_CORE_F64_H__ 1

#include <cftal/config.h>
#include <cftal/math/spec_func.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/func_traits_f64_s32.h>
#include <cftal/math/impl_d_real_constants_f64.h>
#include <cftal/math/lanczos.h>
#include <cftal/math/horner_idx.h>
#include <cftal/mem.h>
#include <cmath>


namespace cftal {
    namespace math {

        // specialization of spec_func_core for double and different
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
            using vdf_type = typename _T::vdf_type;

            using my_type = spec_func_core<double, _T>;

            using d_ops=typename base_type::d_ops;

            using base_type::sinpi_cospi_k;

            static
            void
            sinpi_cospi_k(arg_t<vf_type> xc,
                          vdf_type* ps, vdf_type *pc);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_k(arg_t<vf_type> x);

            static
            vf_type
            erfc_tbl_k(arg_t<vf_type> x);

            static
            vf_type
            tgamma_k(arg_t<vf_type> x, arg_t<vmf_type> x_lt_0);

            // calculates lngamma for x in [1, 2)
            static
            vdf_type
            __lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates lngamma for x in [1, 2] using tables
            static
            vdf_type
            __lgamma_1_2_tbl_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // returns _xr in the range [1, 2]
            // returns _f (including sign)= (x+N)(x+_N-1)...(x-1)(x-2)
            // returns _inv_f as true if f must be inverted or false if not
            // lgamma(x) = lgamma(xr) +- log(abs(_f))
            struct reduced_small_gamma_args {
                vdf_type _xr, _f;
                vmf_type _inv_f;
                reduced_small_gamma_args() : _xr(), _f(), _inv_f() {}
                reduced_small_gamma_args(const vdf_type& xr,
                                         const vdf_type& f,
                                         const vmf_type& inv_f)
                    : _xr(xr), _f(f), _inv_f(inv_f) {}
            };

            // reduces x into [1, 2)
            static
            reduced_small_gamma_args
            __lgamma_reduce_small_k(arg_t<vf_type> x);

            static
            vf_type
            lgamma_k(arg_t<vf_type> xc, vi_type* signp);

            static
            vi2_type
            __reduce_trig_arg(vf_type& xrh, vf_type& xrm, vf_type& xrl,
                              arg_t<vf_type> x);

            // works only in the interval [-3/2*pi/2, 3/2*pi/2]
            static
            vi2_type
            __reduce_trig_arg_tiny(vf_type& xrh, vf_type& xrl,
                                   arg_t<vf_type> xh,
                                   arg_t<vf_type> xl);
            using
            base_type::__reduce_trig_arg;

            static
            vdf_type
            rsqrt12_k(arg_t<vf_type> x);

            static
            void
            __check_tbl_idx(arg_t<vi_type> idx,
                            arg_t<vf_type> xb,
                            const double* t,
                            int32_t span);

            // handle small arguments up to ~128
            static
            vf_type
            __j01y01_small_tbl_k(arg_t<vf_type> xc,
                                 const double tb[j01y01_data<double>::ENTRIES],
                                 double max_small_x);

            // handle the interval [0, 4.75]
            static
            vf_type
            __y0_singular_k(arg_t<vf_type> xc);

            // xr2 square of reciprocal
            // xr reciprocal
            static
            vdf_type
            __j0y0_phase_corr_k(arg_t<vf_type> xr2h,
                                arg_t<vf_type> xr2l,
                                arg_t<vf_type> xrh,
                                arg_t<vf_type> xrl);

            // xr2 square of reciprocal
            static
            vdf_type
            __j0y0_amplitude_corr_k(arg_t<vf_type> xr2,
                                    arg_t<vf_type> xr2l);

            // handle the interval [0, 4.75]
            static
            vf_type
            __y1_singular_k(arg_t<vf_type> xc);

            // xr2 square of reciprocal
            // xr reciprocal
            static
            vdf_type
            __j1y1_phase_corr_k(arg_t<vf_type> xr2h,
                                arg_t<vf_type> xr2l,
                                arg_t<vf_type> xrh,
                                arg_t<vf_type> xrl);

            // xr2 square of reciprocal
            static
            vdf_type
            __j1y1_amplitude_corr_k(arg_t<vf_type> xr2,
                                    arg_t<vf_type> xr2l);

            // handle large arguments greater than ~128 to inf
            // calc_y01 select the calculation of y0/y1 or j0/j1
            // calc_j01 selects j0/y0 or j1/y1
            static
            vf_type
            __j01y01_large_phase_amplitude_k(arg_t<vf_type> xc,
                                             bool calc_y01,
                                             bool calc_jy1);


            static
            vf_type
            j0_k(arg_t<vf_type> xc);

            static
            vf_type
            j1_k(arg_t<vf_type> xc);

            static
            vf_type
            y0_k(arg_t<vf_type> xc);

            static
            vf_type
            y1_k(arg_t<vf_type> xc);

        };

    } // end math
} // end cftal


template <typename _T>
void
cftal::math::spec_func_core<double, _T>::
sinpi_cospi_k(arg_t<vf_type> xc, vdf_type* ps, vdf_type* pc)
{
    vf_type xrh, xrl;
    auto q=base_type::__reduce_trigpi_arg(xrh, xrl, xc);
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
    if (__likely(_T::any_of_vmf(x_in_i0))) {
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
        d_ops::mul12(y_i0, p_i, y_i0, x);
        ye = ye*x + p_i;
        y_i0 += ye;
        y = y_i0;
    }

    vmf_type x_in_i1 = (x > erf_i1_left) & (x<=erf_i2_left);
    if (__likely(_T::any_of_vmf(x_in_i1))) {
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
    if (__likely(_T::any_of_vmf(x_in_i2))) {
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
    if (__likely(_T::any_of_vmf(x_in_i3))) {
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

#define USE_HORNER4 0

    vf_type x= abs(xc);
    vmf_type x_le_0_75 = x <= 0.75;
    vmf_type x_gt_0_75 = x > 0.75;

    vf_type exl=0, exh=0;

    vf_type i0h=0, i0l=0, i123h=0, i123l=0;
    vi_type k=0;
    vf_type x2h;
    bool any_of_x_gt_0_75=any_of(x_gt_0_75);
    if (__likely(any_of_x_gt_0_75)) {
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
            base_type::result_prec::medium>(xrh, xrl, idx, &exl);
        x2h = -x2h;
    } else {
        x2h = x*x;
    }
    if (__likely(_T::any_of_vmf(x_le_0_75))) {
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
#if USE_HORNER4
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
            erfc_i0_c5
            // erfc_i0_c3
        };
        vf_type x4h=x2h*x2h;
        vf_type x8h=x4h*x4h;
        i0h = horner4(x2h, x4h, x8h, ci0);
        i0h = horner(x2h, i0h, erfc_i0_c3);
#else
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
        vf_type x4h=x2h*x2h;
        i0h = horner2(x2h, x4h, ci0);
#endif
        horner_comp_quick(i0h, i0l, x2h, i0h, erfc_i0_c1);
        d_ops::mul122(i0h, i0l, x, i0h, i0l);
        d_ops::add122(i0h, i0l, erfc_i0_c0, i0h, i0l);
    }
    if (__likely(any_of_x_gt_0_75)) {
        vmf_type x_gt_2_75 = x > 2.75;
        vmf_type x_gt_6_00 = x > 6.0;
        vmf_type x_in_i1 = x_gt_0_75 & (x <= 2.75);
        vmf_type x_in_i2 = x_gt_2_75 & (x <= 6.0);
        vmf_type x_in_i3 = x_gt_6_00;
        if (__likely(_T::any_of_vmf(x_in_i1))) {
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
#if USE_HORNER4
            vf_type x_i1_sqr= x_i1* x_i1;
            static const double c[]={
                erfc_i1_c21, erfc_i1_c20, erfc_i1_c19, erfc_i1_c18,
                erfc_i1_c17, erfc_i1_c16, erfc_i1_c15, erfc_i1_c14,
                erfc_i1_c13, erfc_i1_c12, erfc_i1_c11, erfc_i1_c10,
                erfc_i1_c9,  erfc_i1_c8,
                erfc_i1_c7
            };
            vf_type x_i1_q = x_i1_sqr* x_i1_sqr;
            i1h=horner4(x_i1, x_i1_sqr, x_i1_q, c);
            i1h = horner(x_i1, i1h,
                         erfc_i1_c6, erfc_i1_c5, erfc_i1_c4,
                         erfc_i1_c3, erfc_i1_c2, erfc_i1_c1);
            i1h *= x_i1;
#else
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
#endif
            d_ops::add122cond(i1h, i1l, i1h, erfc_i1_c0h, erfc_i1_c0l);
            i123h= i1h;
            i123l= i1l;
        }
        if (__likely(_T::any_of_vmf(x_in_i2))) {
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
#if USE_HORNER4
            vf_type x_i2_q = x_i2_sqr * x_i2_sqr;
            static const double c[]={
                erfc_i2_c21, erfc_i2_c20, erfc_i2_c19, erfc_i2_c18,
                erfc_i2_c17, erfc_i2_c16, erfc_i2_c15, erfc_i2_c14,
                erfc_i2_c13, erfc_i2_c12, erfc_i2_c11, erfc_i2_c10,
                erfc_i2_c9, erfc_i2_c8, erfc_i2_c7, erfc_i2_c6,
                erfc_i2_c5, erfc_i2_c4, erfc_i2_c3, erfc_i2_c2
            };
            i2h = horner4(x_i2, x_i2_sqr, x_i2_q, c);
            i2h = horner(x_i2, i2h, erfc_i2_c1);
#else
            static const double c[]={
                erfc_i2_c21, erfc_i2_c20, erfc_i2_c19, erfc_i2_c18,
                erfc_i2_c17, erfc_i2_c16, erfc_i2_c15, erfc_i2_c14,
                erfc_i2_c13, erfc_i2_c12, erfc_i2_c11, erfc_i2_c10,
                erfc_i2_c9, erfc_i2_c8, erfc_i2_c7, erfc_i2_c6,
                erfc_i2_c5, erfc_i2_c4, erfc_i2_c3, erfc_i2_c2,
                erfc_i2_c1
            };
            i2h = horner2(x_i2, x_i2_sqr, c);
#endif
            i2h *= x_i2;
            d_ops::add122cond(i2h, i2l, i2h, erfc_i2_c0h, erfc_i2_c0l);
            i123h = _T::sel(x_gt_2_75, i2h, i123h);
            i123l = _T::sel(x_gt_2_75, i2l, i123l);
        }
        vf_type inv_x, inv_x_l;
        d_ops::rcp12(inv_x, inv_x_l, x);
        if (__likely(_T::any_of_vmf(x_in_i3))) {
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
            vf_type i3h, i3l;
#if USE_HORNER4
            static const double c[]={
                erfc_i3_c13, erfc_i3_c12, erfc_i3_c11, erfc_i3_c10,
                erfc_i3_c9, erfc_i3_c8, erfc_i3_c7, erfc_i3_c6,
                erfc_i3_c5, erfc_i3_c4, erfc_i3_c3, erfc_i3_c2,
                erfc_i3_c1
            };
            vf_type inv_x4= inv_x2*inv_x2;
            i3h = horner4(inv_x, inv_x2, inv_x4, c);
            i3h *= inv_x;
#else
            static const double c[]={
                erfc_i3_c13, erfc_i3_c12, erfc_i3_c11, erfc_i3_c10,
                erfc_i3_c9, erfc_i3_c8, erfc_i3_c7, erfc_i3_c6,
                erfc_i3_c5, erfc_i3_c4, erfc_i3_c3, erfc_i3_c2,
                erfc_i3_c1
            };
            i3h = horner2(inv_x, inv_x2, c);
            i3h *= inv_x;
#endif
            d_ops::add12cond(i3h, i3l, i3h, erfc_i3_c0);
            i123h = _T::sel(x_gt_6_00, i3h, i123h);
            i123l = _T::sel(x_gt_6_00, i3l, i123l);
        }
        // multiply with e^(-x^2)
        d_ops::mul22(i123h, i123l, exh, exl, i123h, i123l);
        // divide by x
        vf_type rh, rl;
        d_ops::mul22(rh, rl, i123h, i123l, inv_x, inv_x_l);
        auto sc=base_type::__two_pow(k);
        rh *= sc.f0();
        rl *= sc.f0();
        rh *= sc.f1();
        rl *= sc.f1();
        i123h = rh;
        i123l = rl;
    }
    vmf_type x_lt_0_00 = xc < 0.0;
    vf_type ih= _T::sel(x_le_0_75, i0h, i123h);
    if (__likely(_T::any_of_vmf(x_lt_0_00))) {
        vf_type il= _T::sel(x_le_0_75, i0l, i123l);
        vf_type nih, nil;
        d_ops::add122(nih, nil, 2.0, -ih, -il);
        ih = _T::sel(x_lt_0_00, nih, ih);
    }
    return ih;
#undef USE_HORNER4
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
erfc_tbl_k(arg_t<vf_type> xc)
{
    // erfc(-x) = 2 - erfc(x)

    vf_type x= abs(xc);
    vf_type x2h, x2l;

    if (d_real_traits<vf_type>::fma==true) {
        d_ops::mul12(x2h, x2l, x, -x);
    } else {
        d_ops::sqr12(x2h, x2l, x);
        x2h = -x2h;
        x2l = -x2l;
    }
    vf_type xrh, xrl;
    vi_type eidx, k;
    base_type::__reduce_exp_arg(xrh, xrl, eidx, k, x2h, x2l);

    using erfc_table=erfc_data<double>;

#if 0
    vf_type xi= rint(vf_type(x * erfc_table::SCALE));
    vf_type xi0= xi*erfc_table::INV_SCALE;
    vi_type idx= _T::cvt_f_to_i(xi);
#else
    vf_type xscale=x * erfc_table::SCALE;
    vf_type xi= rint(xscale);
    vi_type idx= _T::cvt_f_to_i(xscale);
    vf_type xi0= xi*erfc_table::INV_SCALE;
#endif
    idx = max(min(idx, vi_type(erfc_table::COUNT-1)), vi_type(0));

    vf_type exl, exh=base_type::template __exp_tbl_k<
        base_type::result_prec::medium>(xrh, xrl, eidx, &exl);

    // vi_type idxs = idx * (erfc_table::POLY_ORDER+2) = idx * 12
    vi_type idx8= idx << 3;
    vi_type idx4= idx << 2;
    vi_type idxs = idx8 + idx4;
    vf_type xr=x - xi0;
    vf_type xr2=xr*xr;
    vf_type xr4=xr2*xr2;
    auto lck=make_variable_lookup_table<double>(idxs);
    const double* pt=erfc_table::_tbl;
    vf_type i=horner4_idx<erfc_table::POLY_ORDER-1>(xr, xr2, xr4, lck, pt);
    vf_type c1=lck.from(pt+erfc_table::POLY_ORDER-1);
    i = horner(xr, i, c1);
    vf_type c0h=lck.from(pt+erfc_table::POLY_ORDER);
    vf_type c0l=lck.from(pt+erfc_table::POLY_ORDER+1);
    i *= xr;
    vf_type ih, il;
    d_ops::add212cond(ih, il, c0h, c0l, i);
    d_ops::mul22(ih, il, ih, il, exh, exl);
    auto sc=base_type::__two_pow(k);
    ih *= sc.f0();
    ih *= sc.f1();
    vmf_type x_lt_0_00 = xc < 0.0;
    if (__likely(_T::any_of_vmf(x_lt_0_00))) {
        il *= sc.f0();
        il *= sc.f1();
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
    // using lanczos_ratfunc = lanczos_table_g_12_06815_N12;
    using lanczos_ratfunc = lanczos_table_g_10_90990_N11;

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
    if (_T::any_of_vmf(x_lt_zero)) {
        vdf_type s;
        sinpi_cospi_k(xa, &s, nullptr);
        // vf_type r_n = -M_PI/(s * x0 * r);
        using ctbl = impl::d_real_constants<d_real<double>, double>;
        const vdf_type p=-ctbl::m_pi;
        // vdf_type q=s * (xa *vdf_type(gh, gl));
        vdf_type q;
        d_ops::mul122(q[0], q[1], xa, gh, gl);
        d_ops::mul22(q[0], q[1], q[0], q[1], s[0], s[1]);
        // g_n = p / q;
        vdf_type g_n;
        d_ops::div22(g_n[0], g_n[1], p[0], p[1], q[0], q[1]);
        gh = _T::sel(x_lt_zero, g_n[0], gh);
        gl = _T::sel(x_lt_zero, g_n[1], gl);
        zh = _T::sel(x_lt_zero, -zh, zh);
        zl = _T::sel(x_lt_zero, -zl, zl);
    }
    auto p_sc=base_type::pow_k2(base, base_l, zh, zl);
    const vdf_type& powh= p_sc.first;
    d_ops::mul22(gh, gl, powh[0], powh[1], gh, gl);
    const auto& sc=p_sc.second;
    gh *= sc.f0();
    gh *= sc.f1();
    gh = _T::sel(xa < 0x1p-54, 1.0/x, gh);
    return gh;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
__lgamma_1_2_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    // [1, 2] : | p - f | <= 2^-75.375
    // coefficients for lngamma generated by sollya
    // x^0 h: +0xe.7992843cf8ebp-3
    const double lngamma_i0_c0h=+1.8093614894015579430686e+00;
    // x^0 l: -0xf.a9f7c857d96p-63
    const double lngamma_i0_c0l=-1.6982874646811769294839e-18;
    // x^1 h: -0xf.b50cbee411b38p-1
    const double lngamma_i0_c1h=-7.8536128667263715996683e+00;
    // x^1 l: +0xd.85ed6891c001p-56
    const double lngamma_i0_c1l=+1.8767145914846876394847e-16;
    // x^2 h: +0x9.a7b92da797a5p+2
    const double lngamma_i0_c2h=+3.8620677388824859121996e+01;
    // x^2 l: +0xd.7c7e61e063de8p-52
    const double lngamma_i0_c2l=+2.9945609195263928827005e-15;
    // x^3 h: -0x9.9db9c5589c18p+4
    const double lngamma_i0_c3h=-1.5385785421956234131358e+02;
    // x^3 l: -0xf.bbcab5f95c1cp-53
    const double lngamma_i0_c3l=-1.7467762649536680679211e-15;
    // x^4 h: +0xf.4f1c34352f71p+5
    const double lngamma_i0_c4h=+4.8988877145339040453109e+02;
    // x^4 l: +0xe.b9a8378b1e45p-49
    const double lngamma_i0_c4l=+2.6157250653840250884964e-14;
    // x^5 : -0x9.e76af3ca7ea28p+7
    const double lngamma_i0_c5=-1.2677088912276824430592e+03;
    // x^6 : +0xa.98e09f49ff28p+8
    const double lngamma_i0_c6=+2.7128774305580082000233e+03;
    // x^7 : -0x9.830f9cfcda1e8p+9
    const double lngamma_i0_c7=-4.8701219783844981066068e+03;
    // x^8 : +0xe.7c588c33c23p+9
    const double lngamma_i0_c8=+7.4166917786310368683189e+03;
    // x^9 : -0x9.701219bbdc5a8p+10
    const double lngamma_i0_c9=-9.6642828206684007454896e+03;
    // x^10 : +0xa.972c75079d8b8p+10
    const double lngamma_i0_c10=+1.0844694642928936445969e+04;
    // x^11 : -0xa.48339f3834418p+10
    const double lngamma_i0_c11=-1.0528806592989951241179e+04;
    // x^12 : +0x8.a9f8d05439a3p+10
    const double lngamma_i0_c12=+8.8718877153933390218299e+03;
    // x^13 : -0xc.b1d9ea6f81468p+9
    const double lngamma_i0_c13=-6.4997024669057109349524e+03;
    // x^14 : +0x8.1709954346e08p+9
    const double lngamma_i0_c14=+4.1420748676391676781350e+03;
    // x^15 : -0x8.f643de7ed60c8p+8
    const double lngamma_i0_c15=-2.2942651137611942431249e+03;
    // x^16 : +0x8.9c57b4d7ac338p+7
    const double lngamma_i0_c16=+1.1021713015935617931973e+03;
    // x^17 : -0xe.4cc0fe9838dd8p+5
    const double lngamma_i0_c17=-4.5759423560069598124755e+02;
    // x^18 : +0xa.35317a2905afp+4
    const double lngamma_i0_c18=+1.6332457939171121097388e+02;
    // x^19 : -0xc.6fed9a3bde16p+2
    const double lngamma_i0_c19=-4.9748877104248407476916e+01;
    // x^20 : +0xc.cde277a48a608p+0
    const double lngamma_i0_c20=+1.2804236867590931936434e+01;
    // x^21 : -0xa.fd300ed7e4fap-2
    const double lngamma_i0_c21=-2.7472536391517170528687e+00;
    // x^22 : +0xf.6f564aaf211bp-5
    const double lngamma_i0_c22=+4.8234095179308000833629e-01;
    // x^23 : -0x8.a3d44e55ee388p-7
    const double lngamma_i0_c23=-6.7499674081646934831191e-02;
    // x^24 : +0xe.d41068f6092dp-11
    const double lngamma_i0_c24=+7.2404176742152052265178e-03;
    // x^25 : -0x9.2893a1039e248p-14
    const double lngamma_i0_c25=-5.5899063959853015782359e-04;
    // x^26 : +0xe.7f47dc8e98888p-19
    const double lngamma_i0_c26=+2.7651196041576323747394e-05;
    // x^27 : -0xb.0ae449839e84p-24
    const double lngamma_i0_c27=-6.5818702493252170343746e-07;
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
        lngamma_i0_c5
    };

    vf_type ph, pl;
    const double* pci=ci;
    d_ops::unorm_mul122(ph, pl, pci[0], xh, xl);
    const std::size_t N0=std::distance(std::cbegin(ci), std::cend(ci));
#pragma clang unroll(1)
#pragma GCC unroll 1
    for (std::size_t i=1; i<N0; ++i) {
        d_ops::add122(ph, pl, pci[i], ph, pl);
        d_ops::unorm_mul22(ph, pl, xh, xl, ph, pl);
    }
    static const d_real<double> dci[]={
        {lngamma_i0_c4h, lngamma_i0_c4l},
        {lngamma_i0_c3h, lngamma_i0_c3l},
        {lngamma_i0_c2h, lngamma_i0_c2l},
        {lngamma_i0_c1h, lngamma_i0_c1l}
    };
    constexpr
    const std::size_t N1=std::distance(std::cbegin(dci), std::cend(dci));
    const d_real<double>* pdci=dci;
#pragma clang unroll(1)
#pragma GCC unroll 1
    for (std::size_t i=0; i<N1; ++i) {
        vf_type ch=mem<vf_type>::load(&(pdci[i][0]), 1);
        vf_type cl=mem<vf_type>::load(&(pdci[i][1]), 1);
        d_ops::add22(ph, pl, ch, cl, ph, pl);
        d_ops::unorm_mul22(ph, pl, xh, xl, ph, pl);
    }
    d_ops::add22(ph, pl, lngamma_i0_c0h, lngamma_i0_c0l, ph, pl);
    vf_type xm1h, xm1l;
    d_ops::add212(xm1h, xm1l, xh, xl, -1.0);
    vf_type xm2h, xm2l;
    d_ops::add122(xm2h, xm2l, -2.0, xh, xl);
    vf_type th, tl;
    d_ops::mul22(th, tl, xm1h, xm1l, xm2h, xm2l);
    d_ops::mul22(th, tl, ph, pl, th, tl);
    return vdf_type(th, tl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
__lgamma_1_2_tbl_k(arg_t<vf_type> xch, arg_t<vf_type> xcl)
{
    using lng_tbl=lngamma_data<double>;

    constexpr
    const double xi0=1.0;
#if 0
    vf_type fidx=rint(vf_type(xch-xi0)*lng_tbl::SCALE);
    vf_type x0=xi0+fidx*lng_tbl::INV_SCALE;
    vi_type idx= _T::cvt_f_to_i(fidx);
#else
    vf_type dxscale=(xch-xi0)*lng_tbl::SCALE;
    vf_type fidx=rint(dxscale);
    vi_type idx= _T::cvt_f_to_i(dxscale);
    vf_type x0=xi0+fidx*lng_tbl::INV_SCALE;
#endif
    vf_type ph, pl, cih, cil;
    vi_type idxs = idx*lng_tbl::ELEMS_PER_INTERVAL;
    auto lck=make_variable_lookup_table<double>(idxs);

    vf_type xh, xl;
    d_ops::add122(xh, xl, -x0, xch, xcl);
    const double* pt=lng_tbl::_12_tbl;
    cih=lck.from(pt);
    d_ops::unorm_mul122(ph, pl, cih, xh, xl);
    for (int i=1; i<lng_tbl::ELEMS_PER_INTERVAL-lng_tbl::DD_COEFFS*2; ++i) {
        cih=lck.from(pt+i);
        d_ops::add122(ph, pl, cih, ph, pl);
        d_ops::unorm_mul22(ph, pl, ph, pl, xh, xl);
    }
    for (int i=lng_tbl::ELEMS_PER_INTERVAL-lng_tbl::DD_COEFFS*2;
         i<lng_tbl::ELEMS_PER_INTERVAL-2; i+=2) {
        cih=lck.from(pt+i);
        cil=lck.from(pt+i+1);
        d_ops::add22(ph, pl, cih, cil, ph, pl);
        d_ops::unorm_mul22(ph, pl, ph, pl, xh, xl);
    }
    cih=lck.from(pt+lng_tbl::ELEMS_PER_INTERVAL-2);
    cil=lck.from(pt+lng_tbl::ELEMS_PER_INTERVAL-1);
    // cih+cil >= ph+pl or have at least the same exponent
    // because it is the value in the middle of the interval
    d_ops::add22(ph, pl, cih, cil, ph, pl);
    return vdf_type(ph, pl);
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::reduced_small_gamma_args
cftal::math::spec_func_core<double, _T>::
__lgamma_reduce_small_k(arg_t<vf_type> xc)
{
    vdf_type x=xc;
    vdf_type f0=vf_type(1.0);
    // vf_type f1(1.0);
    vmf_type t;

    const double il=1.0;
    const double ir=2.0;

    if (_T::any_of_vmf(t= x[0]>vf_type(ir))) {
        // x>= 2, if t
        x[0] += _T::sel_val_or_zero(t, -1.0);
        f0[0]=_T::sel(t, x[0], f0[0]);
        while (_T::any_of_vmf(t= x[0]>vf_type(ir))) {
            // x>=2, if t
            x[0] += _T::sel_val_or_zero(t, -1.0);
            vf_type p= _T::sel(t, x[0], vf_type(1.0));
            d_ops::unorm_mul122(f0[0], f0[1], p, f0[0], f0[1]);
#if 0
            // avoid overflows in f0
            if (_T::any_of_vmf(t=f0[0] > 0x1p500)) {
                vf_type h=_T::sel(t, 0x1p-501, 1.0);
                f0[1] *= h;
                f0[0] *= h;
                f1 *= _T::sel(t, 0x1p501, 1.0);
            }
#endif
        }
    }

    t= x[0]<vf_type(il);
    vmf_type inv_f= t;
    if (_T::any_of_vmf(t)) {
        vdf_type& q0=f0;
        q0[0] = _T::sel(t, x[0], q0[0]);
        q0[1] = _T::sel_zero_or_val(t, q0[1]);
        // nothing known about x
        d_ops::add122cond(x[0], x[1],
                          _T::sel_val_or_zero(t, 1.0),
                          x[0], x[1]);
        // see below
        while (_T::any_of_vmf(t= x[0]<vf_type(-1.0))) {
            vf_type q= _T::sel(t, x[0], vf_type(1.0));
            d_ops::unorm_mul122(q0[0], q0[1], q, q0[0], q0[1]);
            // works because we do not loose bits here
            // x < -1.0
            x[0] += _T::sel_val_or_zero(t, 1.0);
#if 0
            // avoid overflows in q0
            if (_T::any_of_vmf(t=abs(q0[0]) > 0x1p500)) {
                vf_type h=_T::sel(t, 0x1p-501, 1.0);
                q0[1] *= h;
                q0[0] *= h;
                // we divide by f1
                f1 *= h;
            }
#endif
        }
        // the range between -1 and 1 must be handled more precise
        if (_T::any_of_vmf(t= x[0]<vf_type(0.0))) {
            vf_type qh= _T::sel(t, x[0], vf_type(1.0));
            vf_type ql= _T::sel_val_or_zero(t, x[1]);
            d_ops::mul22(q0[0], q0[1], q0[0], q0[1], qh, ql);
            // |x| <= 1.0
            d_ops::add122(x[0], x[1],
                          _T::sel_val_or_zero(t, 1.0),
                          x[0], x[1]);
        }
        if (_T::any_of_vmf(t= x[0]<vf_type(il))) {
            vf_type qh= _T::sel(t, x[0], vf_type(1.0));
            vf_type ql= _T::sel_val_or_zero(t, x[1]);
            d_ops::mul22(q0[0], q0[1], q0[0], q0[1], qh, ql);
            // |x| <= 1.0
            d_ops::add122(x[0], x[1],
                        _T::sel_val_or_zero(t, 1.0),
                        x[0], x[1]);
        }
        // f0 /= q0;
        // d_ops::div22(f0[0], f0[1], f0[0], f0[1], q0[0], q0[1]);
    }
    return reduced_small_gamma_args{x, f0, inv_f};
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
lgamma_k(arg_t<vf_type> xc, vi_type* signp)
{
    vf_type xa=abs(xc);
    constexpr const double x_tiny= 0x1p-54;
#if 1
    constexpr const double x_small_delta = 6.0;
    constexpr const double x_small_left  = 1.0-x_small_delta;
    constexpr const double x_small_right = 2.0+x_small_delta;
#else
    constexpr const double x_small_left  = 1.0-4.0;
    constexpr const double x_small_right = 2.0+1.0;
#endif
    constexpr const double x_large= 0x1p54;

    reduced_small_gamma_args sst;

    // the reflection implementation below works only if the
    // reflection for really tiny values is delegated to __lgamma_small_k
    static_assert(x_small_left < - x_tiny, "constraint violated");
    vmf_type xa_in_small =
        ((xc >= x_small_left) & (xc <= x_small_right) & (xa >= x_tiny));

    vf_type base_h=xa, base_l=0.0;
    if (_T::any_of_vmf(xa_in_small)) {
        vf_type xs=_T::sel(xa_in_small, xc, 1.5);
        sst = __lgamma_reduce_small_k(xs);
        vdf_type log_a=select(sst._f[0]>0, sst._f, -sst._f);
        base_h = _T::sel(xa_in_small, log_a[0], base_h);
        base_l = _T::sel(xa_in_small, log_a[1], base_l);
    }

    // using lanczos_ratfunc = lanczos_table_g_12_06815_N12;
    using lanczos_ratfunc = lanczos_table_g_10_90990_N11;
    vmf_type xa_in_lanczos =
        (((xc < x_small_left) | (xc > x_small_right)) & (xa < x_large));
    if (_T::any_of_vmf(xa_in_lanczos)) {
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
    vdf_type lb= base_type::template
        __log_tbl_k2<base_type::result_prec::high>(base_h, base_l);

    vf_type lgh=0.0, lgl=0.0;
    vmf_type xa_in_large = (xa >= x_large);
    if (_T::any_of_vmf(xa_in_large)) {
        // log(gamma(x)) = xa * (log(xa) - 1.0), xa >> 1
        vf_type th, tl;
        d_ops::add212(th, tl, lb[0], lb[1], -1.0);
        d_ops::mul122(th, tl, xa, th, tl);
        lgh = _T::sel(xa_in_large, th, lgh);
        lgl = _T::sel(xa_in_large, tl, lgl);
    }
    if (_T::any_of_vmf(xa_in_lanczos)) {
        // lanczos sum:
        auto pq=lanczos_rational_at(xa,
                                    lanczos_ratfunc::pd,
                                    lanczos_ratfunc::q);

        vf_type sum_h = pq[0], sum_l= pq[1];
        vf_type zh, zl;
        d_ops::add12cond(zh, zl, xa,  -0.5);
        // g = z * log(base) + log(sum) - base;
        vdf_type ls=base_type::template
            __log_tbl_k2<base_type::result_prec::high>(sum_h, sum_l);

        vf_type th, tl;
        d_ops::unorm_mul22(th, tl, zh, zl, lb[0], lb[1]);
        d_ops::add22cond(th, tl, th, tl, -base_h, -base_l);
        d_ops::add22cond(th, tl, th, tl, ls[0], ls[1]);
        lgh = _T::sel(xa_in_lanczos, th, lgh);
        lgl = _T::sel(xa_in_lanczos, tl, lgl);
    }
    if (_T::any_of_vmf(xa_in_small)) {
        vdf_type lg12=__lgamma_1_2_tbl_k(sst._xr[0], sst._xr[1]);
        vf_type th, tl;
        // log(1/lb) = -log(lb):
        th = _T::sel(sst._inv_f, -lb[0], lb[0]);
        tl = _T::sel(sst._inv_f, -lb[1], lb[1]);
        d_ops::add22cond(th, tl, th, tl, lg12[0], lg12[1]);
        lgh = _T::sel(xa_in_small, th, lgh);
        lgl = _T::sel(xa_in_small, tl, lgl);
    }
    // xa_in_tiny:
    vmf_type xa_in_tiny= xa < x_tiny;
    lgh = _T::sel(xa_in_tiny, -lb[0], lgh);

    // reflection part
    vi_type sgn=1;
    vmf_type x_lt_0 = xc < 0.0;
    if (_T::any_of_vmf(x_lt_0)) {
        // tiny
        vmf_type t= x_lt_0 & xa_in_tiny;
        sgn = _T::sel_vi(_T::vmf_to_vmi(t), -1, sgn);
        // small
        t = x_lt_0 & xa_in_small;
        if (_T::any_of_vmf(t)) {
            vf_type sgn_g=copysign(vf_type(1.0), sst._f[0]);
            vi_type si= _T::cvt_f_to_i(sgn_g);
            sgn=_T::sel_vi(_T::vmf_to_vmi(t), si, sgn);
        }
        // lanczos
        t = x_lt_0 & xa_in_lanczos;
        if (_T::any_of_vmf(t)) {
            // G(-z) = -pi/[sin(pi*z)*z * G(z)]
            vdf_type s;
            sinpi_cospi_k(xa, &s, nullptr);
            using ctbl = impl::d_real_constants<d_real<double>, double>;
            // log(G(-z)) = log(pi) - log(z) - log(abs(sin(pi*z))-log(G(z))
            //            = log(pi) - log(abs(sin(pi*z)*z) - log(G(z))
            //            = log(pi) - [log(abs(sin(pi*z)*z) + log(G(z))]
            vdf_type sa= select(s[0] < 0.0, -s, s);
            d_ops::mul122(sa[0], sa[1], xa, sa[0], sa[1]);
            vdf_type lg_n=base_type::template
                __log_tbl_k2<base_type::result_prec::high>(sa[0], sa[1]);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             lg_n[0], lg_n[1],
                             lgh, lgl);
            d_ops::add22cond(lg_n[0], lg_n[1],
                             ctbl::m_ln_pi[0], ctbl::m_ln_pi[1],
                             -lg_n[0], -lg_n[1]);
            lgh = _T::sel(t, lg_n[0], lgh);
            vmf_type s_lt_0 = (s[0] >= 0.0) & t;
            vmi_type i_s_lt_0 = _T::vmf_to_vmi(s_lt_0);
            sgn = _T::sel_vi(i_s_lt_0, -1, sgn);
        }
        // no large handling because xc is integer anyway
    }
    if (signp != nullptr)
        *signp = sgn;
    return lgh;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
rsqrt12_k(arg_t<vf_type> xc)
{
    vf_type y=1.0/sqrt(xc);
    vf_type z=impl::root_r2::calc_z<double, true>(y, xc);
    vf_type d=-0.5*z;
    vf_type yh, yl;
    d_ops::add12(yh, yl, y, y*d);
    // d_ops::muladd12(yh, yl, y, d, y);
    return vdf_type(yh, yl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vi2_type
cftal::math::spec_func_core<double, _T>::
__reduce_trig_arg(vf_type& xrh, vf_type& xrm, vf_type& xrl,
                  arg_t<vf_type> x)
{
#if 0
    auto q=payne_hanek_pi_over_2<double, _T>::rem3(xrh, xrm, xrl, x);
    vi2_type q2=_T::vi_to_vi2(q);
    return q2;
#else
    using ctbl=impl::d_real_constants<d_real<double>, double>;

    constexpr const double large_arg=0x1p45;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);
    xrh = 0.0;
    xrm = 0.0;
    xrl = 0.0;
    vi_type q=0;
    if (__likely(!_T::all_of_vmf(v_large_arg))) {
        vf_type x_2_pi=x* ctbl::m_2_pi[0];
        vf_type fn= rint(x_2_pi);
        constexpr const double m_pi_2_h=+1.5707963267948965579990e+00;
        constexpr const double m_pi_2_m=+6.1232339957367660358688e-17;
        constexpr const double m_pi_2_l=-1.4973849048591698329435e-33;
        vf_type f0, f1, f2, f3, f4;
        d_ops::mul12(f0, f1, fn, -m_pi_2_h);
        d_ops::mul12(f2, f3, fn, -m_pi_2_m);
        f4 = fn * -m_pi_2_l;
        // normalize f0 - f4 into p0..p2
        vf_type p0, p1, p2, t;
        p0 = f0;
        d_ops::add12(p1, t, f1, f2);
        p2 = f4 + t + f3;
        d_ops::add12(p0, p1, p0, p1);
        d_ops::add12(p1, p2, p1, p2);
        vf_type t0, t1, t2;
        using t_ops=t_real_ops<vf_type>;
        t_ops::add133cond(t0, t1, t2, x, p0, p1, p2);
        t_ops::renormalize3(xrh, xrm, xrl, t0, t1, t2);
        fn = base_type::template __fmod<4>(fn);
        q=_T::cvt_f_to_i(fn);
    }
    if (_T::any_of_vmf(v_large_arg)) {
        // reduce the large arguments
        vf_type xrhl, xrml, xrll;
        // mask out not required values to avoid subnormals
        vf_type xl=_T::sel_val_or_zero(v_large_arg, x);
        vi_type ql=payne_hanek_pi_over_2<double, _T>::
            rem3(xrhl, xrml, xrll, xl);
        q = _T::sel_vi(_T::vmf_to_vmi(v_large_arg), ql, q);
        xrh = _T::sel(v_large_arg, xrhl, xrh);
        xrm = _T::sel(v_large_arg, xrml, xrm);
        xrl = _T::sel(v_large_arg, xrll, xrl);
    }
    vi2_type q2=_T::vi_to_vi2(q);
    return q2;
#endif
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vi2_type
cftal::math::spec_func_core<double, _T>::
__reduce_trig_arg_tiny(vf_type& xrh, vf_type& xrl,
                        arg_t<vf_type> x, arg_t<vf_type> xl)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type x_2_pi=x* ctbl::m_2_pi[0];
    vf_type fn= rint(x_2_pi);
    // x^ : +0xc.90fdaa22168cp-3
    constexpr
    const double pi_2_0=+1.5707963267948965579990e+00;
    // x^ : +0x8.d313198a2e038p-57
    constexpr
    const double pi_2_1=+6.1232339957367660358688e-17;
    // x^ : -0xf.8cbb5bf6c7dep-113
    constexpr
    const double pi_2_2=-1.4973849048591698329435e-33;
    constexpr
    static const double ci[]={
        -pi_2_0, -pi_2_1, -pi_2_2
    };
    vf_type sh=x, sl=xl;
    for (auto b=std::cbegin(ci), e=std::cend(ci); b!=e; ++b) {
#if 1
        const double m_pi_2=*b;
        d_ops::add122cond(sh, sl, m_pi_2*fn, sh, sl);
#else
        vf_type th, tl;
        const double m_pi_2=*b;
        d_ops::mul12(th, tl, fn, m_pi_2);
        d_ops::add22cond(sh, sl, sh, sl, th, tl);
#endif
    }
    xrh = sh;
    xrl = sl;
    // works only up to 2^31
    vi_type q=_T::cvt_f_to_i(x_2_pi);
    vi2_type q2=_T::vi_to_vi2(q);
    return q2;
}

template <typename _T>
void
cftal::math::spec_func_core<double, _T>::
__check_tbl_idx(arg_t<vi_type> idx, arg_t<vf_type> xb,
                const double* t, int32_t span)
{
#if 1
    static_cast<void>(idx);
    static_cast<void>(xb);
    static_cast<void>(t);
    static_cast<void>(span);
#else
    for (uint32_t i=0; i<size(idx); ++i) {
        double xi=extract(xb, i);
        int32_t idxi=extract(idx, i);
        int32_t idxm1=idxi-span;
        if (idxm1 > 0) {
            double xl= t[idxm1];
            if (xl > xi) {
                std::cerr << std::setprecision(22) << xi
                          << " has too large idx " << idxi
                          << " xl= "
                          << xl << std::endl;
            }
        }
        double xr=t[idxi];
        if (xr < xi) {
            std::cerr << std::setprecision(22) << xi
                        << " has too small idx " << idxi
                        << " xr= "
                        << xr << std::endl;
        }
    }
#endif
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
__j01y01_small_tbl_k(arg_t<vf_type> xc,
                     const double tb[j01y01_data<double>::ENTRIES],
                     double max_small_x)
{
    using tbl_t=j01y01_data<double>;
    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type xb=min(xc, vf_type(max_small_x));
    vf_type xb_idx=xb*ctbl::m_2_pi[0];
    vi_type idx=cvt_rz<vi_type>(xb_idx);
    idx *= tbl_t::ELEMS;
    auto lk=make_variable_lookup_table<double>(idx);
    vf_type xr_i0=lk.from(tb);
    vi_type i0=idx;
    vi_type i1=idx+tbl_t::ELEMS;
    i1 = min(i1, vi_type(tbl_t::ELEMS*(tbl_t::INTERVALS-1)));
    vmf_type xb_in_i1= xb > xr_i0;
    vmi_type sel_i1 = _T::vmf_to_vmi(xb_in_i1);
    idx=_T::sel_vi(sel_i1, i1, i0);
    // and update the lookup table
    __check_tbl_idx(idx, xb, tb, tbl_t::ELEMS);
    lk=make_variable_lookup_table<double>(idx);
    // read the negative interval centers
    const vf_type x0h=lk.from(tb + tbl_t::NEG_X_OFFS_H);
    const vf_type x0m=lk.from(tb + tbl_t::NEG_X_OFFS_M);
    const vf_type x0l=lk.from(tb + tbl_t::NEG_X_OFFS_L);
    vf_type xrh, xrl;
    d_ops::add122cond(xrh, xrl, xb, x0h, x0m);
    d_ops::add122cond(xrh, xrl, x0l, xrh, xrl);

    vf_type xr2=xrh*xrh;
    // produce a polynomial of order POLY_ORD-3
    vf_type p=horner2_idx<tbl_t::POLY_ORD-3>(
        xrh, xr2, lk, tb+tbl_t::NEG_X_OFFS_L+1);
    vf_type rh, rl;
    vf_type c3=lk.from(tb+tbl_t::C3);
    vf_type c2=lk.from(tb+tbl_t::C2);
    vf_type c1h=lk.from(tb+tbl_t::C1H);
    vf_type c1l=lk.from(tb+tbl_t::C1L);
    vf_type c0h=lk.from(tb+tbl_t::C0H);
    vf_type c0l=lk.from(tb+tbl_t::C0L);
    horner_comp_quick(rh, rl, xrh, p, c3, c2);
    horner_comp_quick_dpc_si(rh, rl, xrh, rh, rl, c1h, c1l);
    d_ops::unorm_mul22(rh, rl, rh, rl, xrh, xrl);
    d_ops::add22(rh, rl, c0h, c0l, rh, rl);
    return rh;
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
__y0_singular_k(arg_t<vf_type> xc)
{
    vf_type r;
    // x^ : +0xcp-4
    constexpr
    const double y0_i0_r=+7.5000000000000000000000e-01;
    static_cast<void>(y0_i0_r);
    if (_T::any_of_vmf(xc < y0_i0_r)) {
        // x^ h: -0xe.d6d80a2a0f59p-7
        constexpr
        const double log_half_plus_euler_gamma_h=-1.1593151565841244843291e-01;
        // x^ l: -0xd.f04ae82e05408p-65
        constexpr
        const double log_half_plus_euler_gamma_l=-3.7780767526472776010095e-19;
        // [12;12]
        // [0, 0.75] : | p - f | <= 2^-67.28125
        // coefficients for j0 generated by sollya
        // x^0 : +0x8p-3
        constexpr
        const double j0z0=+1.0000000000000000000000e+00;
        // x^2 : -0x8p-5
        constexpr
        const double j0z2=-2.5000000000000000000000e-01;
        // x^4 : +0xf.fffffffffffd8p-10
        constexpr
        const double j0z4=+1.5624999999999991326383e-02;
        // x^6 : -0xe.38e38e38dc518p-15
        constexpr
        const double j0z6=-4.3402777777757690523194e-04;
        // x^8 : +0xe.38e38e29151dp-21
        constexpr
        const double j0z8=+6.7816840260229131759221e-06;
        // x^10 : -0x9.1a2b2b3d586fp-27
        constexpr
        const double j0z10=-6.7816832700464963835905e-08;
        // x^12 : +0x8.172f5d59658a8p-34
        constexpr
        const double j0z12=+4.7093295009877648625093e-10;
        // x^14 : -0xa.7aa5c2f9c32f8p-42
        constexpr
        const double j0z14=-2.3826696227953901635238e-12;
        // [12;12]
        // [0, 0.75] : | p - f | <= 2^-64.71875
        // coefficients for y0_r generated by sollya
        // x^2 : +0x8p-5
        constexpr
        const double y0r2=+2.5000000000000000000000e-01;
        // x^4 : -0xb.ffffffffffffp-9
        constexpr
        const double y0r4=-2.3437499999999993061106e-02;
        // x^6 : +0xd.097b425ecc558p-14
        constexpr
        const double y0r6=+7.9571759259235619234779e-04;
        // x^8 : -0xe.d097b419c8958p-20
        constexpr
        const double y0r8=-1.4128508388507550461491e-05;
        // x^10 : +0xa.6446a1aee02d8p-26
        constexpr
        const double y0r10=+1.5484843779055184565981e-07;
        // x^12 : -0x9.e9364465c5268p-33
        constexpr
        const double y0r12=-1.1537904270715571440907e-09;
        // x^14 : +0xd.975c37852daap-41
        constexpr
        const double y0r14=+6.1805853273914269608914e-12;


        constexpr static const double j0coeffs[]={
            j0z14, j0z12, j0z10, j0z8, j0z6, j0z4//, j0z2
        };
        vf_type x2=xc*xc;
        vf_type j0p=horner(x2, j0coeffs)/*x2*/;
        vf_type j0h, j0l;
        horner_comp_quick(j0h, j0l, x2, j0p, j0z2, j0z0);
        // d_ops::add12(j0h, j0l, j0z0, j0p);
        constexpr static const double y0rcoeffs[]={
            y0r14, y0r12, y0r10, y0r8, y0r6, y0r4
        };
        vf_type y0rp=horner(x2, y0rcoeffs);
        vf_type y0rh, y0rl;
        horner_comp_quick(y0rh, y0rl, x2, y0rp, y0r2);
        d_ops::mul122(y0rh, y0rl, x2, y0rh, y0rl);
        vdf_type ln_x=base_type::__log_tbl_k12(xc);

        // y0(x) = 2/pi*(f(x) + (log(0.5*x) + euler_gamma) * j0(x));
        // y0(x) = 2/pi*(f(x) + (log(x) + log(0.5)+euler_gamma) * j0(x));
        using ctbl=impl::d_real_constants<d_real<double>, double>;
        vf_type y0h, y0l;
        // |log(3/4) ~ -0.28| > |log_half_plus_euler_gamma_h|
        d_ops::add22(y0h, y0l,
                     ln_x[0], ln_x[1],
                     log_half_plus_euler_gamma_h,
                     log_half_plus_euler_gamma_l);
        d_ops::unorm_mul22(y0h, y0l, j0h, j0l, y0h, y0l);
        d_ops::add22cond(y0h, y0l, y0rh, y0rl, y0h, y0l);
        d_ops::unorm_mul22(y0h, y0l, y0h, y0l, ctbl::m_2_pi[0], ctbl::m_2_pi[1]);
        r = y0h + y0l;
    }
    constexpr
    const double y0_i1_r=+1.2500000000000000000000e+00;
    vmf_type msk=(xc >= y0_i0_r)  & (xc < y0_i1_r);
    if (_T::any_of_vmf(msk)) {
        // [0.75;1.25] [20;20]
        // shifted [-0.14357696473598480224609375;0.35642302036285400390625] [20;20]
        // [-0.14357696473598480224609375, 0.35642302036285400390625] : | p - f | <= 2^-67.46875
        // coefficients for y0_i1 generated by sollya
        // x^1 h: +0xe.121b8c225c45p-4
        constexpr
        const double y0_i1_1h=+8.7942080249719478679538e-01;
        // x^1 l: -0x9.1453a92468e9p-59
        constexpr
        const double y0_i1_1l=-1.5750251035955136174859e-17;
        // x^2 : -0xf.bf1c5236b881p-5
        constexpr
        const double y0_i1_2=-4.9207893426297755201659e-01;
        // x^3 : +0xe.1d899c579f4cp-6
        constexpr
        const double y0_i1_3=+2.2055282848167645504134e-01;
        // x^4 : -0xe.78c735259c56p-6
        constexpr
        const double y0_i1_4=-2.2612171354416454871483e-01;
        // x^5 : +0xe.034043614a538p-6
        constexpr
        const double y0_i1_5=+2.1894842701036518195501e-01;
        // x^6 : -0xd.1cb5402cf15d8p-6
        constexpr
        const double y0_i1_6=-2.0487719790596323199416e-01;
        // x^7 : +0xc.a125c987c5ae8p-6
        constexpr
        const double y0_i1_7=+1.9733566933345061955585e-01;
        // x^8 : -0xc.69ada40b7f8fp-6
        constexpr
        const double y0_i1_8=-1.9395009059916729077244e-01;
        // x^9 : +0xc.60468198c368p-6
        constexpr
        const double y0_i1_9=+1.9337618499689890327886e-01;
        // x^10 : -0xc.7bf199cbb4ff8p-6
        constexpr
        const double y0_i1_10=-1.9506492632974922751821e-01;
        // x^11 : +0xc.b6f524b460768p-6
        constexpr
        const double y0_i1_11=+1.9866684517319957437032e-01;
        // x^12 : -0xd.0db783b83f008p-6
        constexpr
        const double y0_i1_12=-2.0396221030476627267269e-01;
        // x^13 : +0xd.7e0bc24bb3f5p-6
        constexpr
        const double y0_i1_13=+2.1081823324385534634828e-01;
        // x^14 : -0xe.06a6783ed7018p-6
        constexpr
        const double y0_i1_14=-2.1915590040894991630260e-01;
        // x^15 : +0xe.a897072fcf0dp-6
        constexpr
        const double y0_i1_15=+2.2903991414862973075017e-01;
        // x^16 : -0xf.6dc33627d93d8p-6
        constexpr
        const double y0_i1_16=-2.4107437409056217680892e-01;
        // x^17 : +0x8.2c72fbff3be3p-5
        constexpr
        const double y0_i1_17=+2.5542592256703888775604e-01;
        // x^18 : -0x8.6febd257ce1e8p-5
        constexpr
        const double y0_i1_18=-2.6366225321402564363282e-01;
        // x^19 : +0xf.38e440a4019d8p-6
        constexpr
        const double y0_i1_19=+2.3784738838733140986470e-01;
        // x^20 : -0x9.d81b250b2f76p-6
        constexpr
        const double y0_i1_20=-1.5381506555126323032567e-01;
        // x^21 : +0xc.c1ffdda798478p-8
        constexpr
        const double y0_i1_21=+4.9835197081479092051648e-02;
        // x^ h: +0xe.4c175c6a0bf5p-4
        constexpr
        const double y0_i1_x0h=+8.9357696627916749498866e-01;
        // x^ m: +0xf.54e9381a3fc18p-59
        constexpr
        const double y0_i1_x0m=+2.6596231539720384869752e-17;
        // x^ l: -0x9.617a6b74cd0f8p-115
        constexpr
        const double y0_i1_x0l=-2.2583392482023257066498e-34;

        constexpr static const double ci[]={
            y0_i1_21, y0_i1_20, y0_i1_19, y0_i1_18, y0_i1_17, y0_i1_16,
            y0_i1_15, y0_i1_14, y0_i1_13, y0_i1_12, y0_i1_11, y0_i1_10,
            y0_i1_9, y0_i1_8, y0_i1_7, y0_i1_6, y0_i1_5, y0_i1_4, y0_i1_3
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y0_i1_x0h, -y0_i1_x0m);
        d_ops::add122cond(xrh, xrl, -y0_i1_x0l, xrh, xrl);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i1_2);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i1_1h, y0_i1_1l);
        d_ops::unorm_mul22(ph, pl, ph, pl, xrh, xrl);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x8p-2
    constexpr
    const double y0_i2_r=+2.0000000000000000000000e+00;
    msk=(xc >= y0_i1_r)  & (xc < y0_i2_r);
    if (_T::any_of_vmf(msk)) {
        // [1.25;2] [16;16]
        // shifted [-0.375;0.375] [19;19]
        // [-0.375, 0.375] : | p - f | <= 2^-60.28125
        // coefficients for y0_i2 generated by sollya
        // x^0 h: +0xd.b9b15216ec7f8p-5
        constexpr
        const double y0_i2_0h=+4.2891756089319693634465e-01;
        // x^0 l: +0xc.cee7758a8623p-59
        constexpr
        const double y0_i2_0l=+2.2218718681350609206379e-17;
        // x^1 : +0xa.9d3d9f86fdb88p-5
        constexpr
        const double y0_i2_1=+3.3169442327191861474844e-01;
        // x^2 : -0xa.20eb9f0d9cefp-5
        constexpr
        const double y0_i2_2=-3.1651860299180423208298e-01;
        // x^3 : +0xf.a82911df78bb8p-9
        constexpr
        const double y0_i2_3=+3.0579837257151489676721e-02;
        // x^4 : -0x9.b8e5382fbb6fp-11
        constexpr
        const double y0_i2_4=-4.7471912166352197431918e-03;
        // x^5 : +0xa.ccdd4c1530aap-10
        constexpr
        const double y0_i2_5=+1.0547120827411639309990e-02;
        // x^6 : -0xc.09ab803655dd8p-11
        constexpr
        const double y0_i2_6=-5.8778189184449059975779e-03;
        // x^7 : +0xb.f49b5265e01fp-12
        constexpr
        const double y0_i2_7=+2.9188220272473855074202e-03;
        // x^8 : -0xc.f6fbcdd78c528p-13
        constexpr
        const double y0_i2_8=-1.5826147125479830563705e-03;
        // x^9 : +0xe.57b3165fc1298p-14
        constexpr
        const double y0_i2_9=+8.7540139201897971318184e-04;
        // x^10 : -0xf.f70905134a21p-15
        constexpr
        const double y0_i2_10=-4.8721256657763636638975e-04;
        // x^11 : +0x8.f61897fee8cd8p-15
        constexpr
        const double y0_i2_11=+2.7347756257902763139464e-04;
        // x^12 : -0xa.224554cace108p-16
        constexpr
        const double y0_i2_12=-1.5463059097983822905327e-04;
        // x^13 : +0xb.83d83940fb5e8p-17
        constexpr
        const double y0_i2_13=+8.7852615822082765905006e-05;
        // x^14 : -0xd.41f33d1be9bcp-18
        constexpr
        const double y0_i2_14=-5.0573798286913018620176e-05;
        // x^15 : +0xf.b9099a3c03498p-19
        constexpr
        const double y0_i2_15=+2.9988866371516582752131e-05;
        // x^16 : -0x8.1e10594de5bc8p-19
        constexpr
        const double y0_i2_16=-1.5482782294416977966972e-05;
        // x^17 : +0xc.d8e411c30f04p-21
        constexpr
        const double y0_i2_17=+6.1260366738323418262131e-06;
        // x^18 : -0xa.466c2f55fe498p-20
        constexpr
        const double y0_i2_18=-9.7990877825345343901100e-06;
        // x^19 : +0x9.539313f8a33bp-20
        constexpr
        const double y0_i2_19=+8.8944082092007590342308e-06;
        // x^20 : +0xf.d88b9527ccf2p-22
        constexpr
        const double y0_i2_20=+3.7779521613212945012035e-06;
        // x^ : +0xdp-3
        constexpr
        const double y0_i2_x0=+1.6250000000000000000000e+00;

        constexpr static const double ci[]={
            y0_i2_20, y0_i2_19, y0_i2_18, y0_i2_17, y0_i2_16,
            y0_i2_15, y0_i2_14, y0_i2_13, y0_i2_12, y0_i2_11, y0_i2_10,
            y0_i2_9, y0_i2_8, y0_i2_7, y0_i2_6, y0_i2_5, y0_i2_4, y0_i2_3
        };
        vf_type xrh, xrl;
        d_ops::add12cond(xrh, xrl, xc, -y0_i2_x0);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i2_2, y0_i2_1);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i2_0h, y0_i2_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0xdp-2
    constexpr
    const double y0_i3_r=+3.2500000000000000000000e+00;
    msk=(xc >= y0_i2_r)  & (xc < y0_i3_r);
    if (_T::any_of_vmf(msk)) {
        // [2;3.25] [16;16]
        // shifted [-0.625;0.625] [19;19]
        // [-0.625, 0.625] : | p - f | <= 2^-62.09375
        // coefficients for y0_i3 generated by sollya
        // x^0 h: +0xf.3f71832453958p-5
        constexpr
        const double y0_i3_0h=+4.7649455655720157620792e-01;
        // x^0 l: -0x8.1ead77a6db14p-62
        constexpr
        const double y0_i3_0l=-1.7607084198413380645893e-18;
        // x^1 : -0xc.b3fdef0f137e8p-6
        constexpr
        const double y0_i3_1=-1.9848583551020473891846e-01;
        // x^2 : -0xc.d404310912ebp-6
        constexpr
        const double y0_i3_2=-2.0044045246713321217769e-01;
        // x^3 : +0xd.c16fd3a76bbcp-8
        constexpr
        const double y0_i3_3=+5.3732861684166743909685e-02;
        // x^4 : +0xf.abfd48b0f5a38p-11
        constexpr
        const double y0_i3_4=+7.6522624786957210360483e-03;
        // x^5 : -0x9.d65c3fe674158p-13
        constexpr
        const double y0_i3_5=-1.2008477926444087718200e-03;
        // x^6 : -0x9.1cc5605e87e2p-14
        constexpr
        const double y0_i3_6=-5.5617594760137183465543e-04;
        // x^7 : +0x9.3a1838e7a4458p-16
        constexpr
        const double y0_i3_7=+1.4079181064958023301102e-04;
        // x^8 : -0xf.1d7a5f0af47ep-19
        constexpr
        const double y0_i3_8=-2.8829857801928614516838e-05;
        // x^9 : +0xb.459f04036ee98p-20
        constexpr
        const double y0_i3_9=+1.0749776493719942577708e-05;
        // x^10 : -0x8.4eadce497c7a8p-21
        constexpr
        const double y0_i3_10=-3.9612481909630230749353e-06;
        // x^11 : +0xb.86a3d6bd0e4dp-23
        constexpr
        const double y0_i3_11=+1.3739988186394175969306e-06;
        // x^12 : -0x8.112abed20d168p-24
        constexpr
        const double y0_i3_12=-4.8083415585335915438606e-07;
        // x^13 : +0xb.6661825bace7p-26
        constexpr
        const double y0_i3_13=+1.6987212557327338514996e-07;
        // x^14 : -0x8.17773bdc019b8p-27
        constexpr
        const double y0_i3_14=-6.0287588192497810673542e-08;
        // x^15 : +0xb.a5ebd1df328fp-29
        constexpr
        const double y0_i3_15=+2.1696332050054635600370e-08;
        // x^16 : -0x8.6cd676154da3p-30
        constexpr
        const double y0_i3_16=-7.8465299859340416241355e-09;
        // x^17 : +0xa.ccc13d1016e68p-32
        constexpr
        const double y0_i3_17=+2.5145298768576495072879e-09;
        // x^18 : -0xd.f3bf65586b568p-34
        constexpr
        const double y0_i3_18=-8.1212138869839136598263e-10;
        // x^19 : +0x9.74db07eb1e32p-34
        constexpr
        const double y0_i3_19=+5.5043883311910698324971e-10;
        // x^20 : -0x8.7bae5fdc512bp-35
        constexpr
        const double y0_i3_20=-2.4689156250779901466718e-10;
        // x^ : +0xa.8p-2
        constexpr
        const double y0_i3_x0=+2.6250000000000000000000e+00;

        constexpr static const double ci[]={
            y0_i3_20, y0_i3_19, y0_i3_18, y0_i3_17, y0_i3_16,
            y0_i3_15, y0_i3_14, y0_i3_13, y0_i3_12, y0_i3_11, y0_i3_10,
            y0_i3_9, y0_i3_8, y0_i3_7, y0_i3_6, y0_i3_5, y0_i3_4, y0_i3_3
        };
        vf_type xrh, xrl;
        d_ops::add12cond(xrh, xrl, xc, -y0_i3_x0);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i3_2, y0_i3_1);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i3_0h, y0_i3_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x9.8p-1
    constexpr
    const double y0_i4_r=+4.7500000000000000000000e+00;
    msk=(xc >= y0_i3_r)  & (xc <= y0_i4_r);
    if (_T::any_of_vmf(msk)) {
        // [3.25;4.75] [15;15]
        // shifted [-0.70767843723297119140625;0.79232156276702880859375] [17;17]
        // [-0.70767843723297119140625, 0.79232156276702880859375] : | p - f | <= 2^-65.90625
        // coefficients for y0_i4 generated by sollya
        // x^1 h: -0xc.e1a12b509506p-5
        constexpr
        const double y0_i4_1h=-4.0254267177502423002977e-01;
        // x^1 l: -0xd.211fe559ae0ap-61
        constexpr
        const double y0_i4_1l=-5.6939665408019283511565e-18;
        // x^2 : +0xd.04e49481b3f78p-8
        constexpr
        const double y0_i4_2=+5.0855909592158236864901e-02;
        // x^3 : +0xe.fb6acdfa875e8p-8
        constexpr
        const double y0_i4_3=+5.8523822105170243690342e-02;
        // x^4 : -0xe.08b7ee2cc0b3p-11
        constexpr
        const double y0_i4_4=-6.8525666771111822667129e-03;
        // x^5 : -0x8.f195e277c543p-12
        constexpr
        const double y0_i4_5=-2.1835188740493864309467e-03;
        // x^6 : +0xc.cc13b28c52018p-16
        constexpr
        const double y0_i4_6=+1.9526940245498400155165e-04;
        // x^7 : +0xd.5960ff677f57p-18
        constexpr
        const double y0_i4_7=+5.0922913807036548363393e-05;
        // x^8 : -0xa.431b90c02effp-21
        constexpr
        const double y0_i4_8=-4.8933693719481284313500e-06;
        // x^9 : -0x9.d90b445712c6p-25
        constexpr
        const double y0_i4_9=-2.9348814994302012224166e-07;
        // x^10 : -0xb.bb79383ea69fp-29
        constexpr
        const double y0_i4_10=-2.1853145986653325763315e-08;
        // x^11 : +0xa.29758e12dc438p-29
        constexpr
        const double y0_i4_11=+1.8928106867840794536847e-08;
        // x^12 : -0xf.b5b8b0b7144ap-32
        constexpr
        const double y0_i4_12=-3.6577343475612441665157e-09;
        // x^13 : +0xd.2cf27da5cfc9p-34
        constexpr
        const double y0_i4_13=+7.6691940870018196440261e-10;
        // x^14 : -0xc.a1e3b6a586308p-36
        constexpr
        const double y0_i4_14=-1.8382533572296433588247e-10;
        // x^15 : +0xc.456e1f0c44e68p-38
        constexpr
        const double y0_i4_15=+4.4642407619530769083865e-11;
        // x^16 : -0xf.1da2286079588p-40
        constexpr
        const double y0_i4_16=-1.3747699613737514555825e-11;
        // x^17 : +0xb.57c0a8a446eb8p-42
        constexpr
        const double y0_i4_17=+2.5790503717255544684247e-12;
        // x^18 : +0xf.2dc3613056c6p-43
        constexpr
        const double y0_i4_18=+1.7256255099223973945683e-12;
        // x^19 : +0xf.d4b9cc81c474p-47
        constexpr
        const double y0_i4_19=+1.1248573674676210591891e-13;
        // x^20 : -0xd.4e94bcd218188p-44
        constexpr
        const double y0_i4_20=-7.5641293366122783112802e-13;
        // x^ h: +0xf.d4a9a6cc2b4ep-2
        constexpr
        const double y0_i4_x0h=+3.9576784193148579760191e+00;
        // x^ m: -0xf.83573c021c27p-57
        constexpr
        const double y0_i4_x0m=-1.0764340697562706032789e-16;
        // x^ l: +0xd.016973bceb52p-112
        constexpr
        const double y0_i4_x0l=+2.5047711399617118050168e-33;

        constexpr static const double ci[]={
            y0_i4_20, y0_i4_19, y0_i4_18, y0_i4_17, y0_i4_16,
            y0_i4_15, y0_i4_14, y0_i4_13, y0_i4_12, y0_i4_11, y0_i4_10,
            y0_i4_9, y0_i4_8, y0_i4_7, y0_i4_6, y0_i4_5, y0_i4_4, y0_i4_3
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y0_i4_x0h, -y0_i4_x0m);
        d_ops::add122cond(xrh, xrl, -y0_i4_x0l, xrh, xrl);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y0_i4_2);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y0_i4_1h, y0_i4_1l);
        d_ops::unorm_mul22(ph, pl, ph, pl, xrh, xrl);
        r = _T::sel(msk, ph+pl, r);
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
__j0y0_phase_corr_k(arg_t<vf_type> xr2h,
                    arg_t<vf_type> xr2l,
                    arg_t<vf_type> xrh,
                    arg_t<vf_type> xrl)
{
    constexpr
    const double a0_c1=-1.2500000000000000000000e-01;
    constexpr
    const double a0_c3_h=+6.5104166666666671292596e-02;
    constexpr
    const double a0_c3_l=-4.6259292689999999998733e-18;
    constexpr
    const double a0_c5_h=-2.0957031249999999444888e-01;
    constexpr
    const double a0_c5_l=-5.5511151230000000001060e-18;
    constexpr
    const double a0_c7_h=+1.6380658830915177937015e+00;
    constexpr
    const double a0_c7_l=+6.3441315693000000002756e-17;
    constexpr
    const double a0_c9_h=-2.3475127749972873658635e+01;
    constexpr
    const double a0_c9_l=+3.9474596431099999998990e-16;
    constexpr
    const double a0_c11_h=+5.3564051951061594536441e+02;
    constexpr
    const double a0_c11_l=+1.0335167065600999999650e-14;
    constexpr
    const double a0_c13_h=-1.7837279688947477552574e+04;
    constexpr
    const double a0_c13_l=+1.6790671417346369999700e-12;
    constexpr
    const double a0_c15_h=+8.1673784219107672106475e+05;
    constexpr
    const double a0_c15_l=-3.8805107275644936000081e-11;

    static_cast<void>(a0_c5_l);
    static_cast<void>(a0_c7_l);
    static_cast<void>(a0_c9_l);
    static_cast<void>(a0_c11_l);
    static_cast<void>(a0_c13_l);
    static_cast<void>(a0_c15_h);
    static_cast<void>(a0_c15_l);
    constexpr const static double ci[]={
        /* a0_c15, */ a0_c13_h, a0_c11_h, a0_c9_h, a0_c7_h
    };
    vf_type p=horner(xr2h, ci);
    vf_type ph, pl;
    horner_comp_quick_dpc_s0(ph, pl, xr2h, p, a0_c5_h, a0_c5_l);
    horner_comp_quick_dpc_si(ph, pl, xr2h, ph, pl, a0_c3_h, a0_c3_l);

    d_ops::mul22(ph, pl, xr2h, xr2l, ph, pl);
    d_ops::add122(ph, pl, a0_c1, ph, pl);
    d_ops::mul22(ph, pl, xrh, xrl, ph, pl);
    return vdf_type(ph, pl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
__j0y0_amplitude_corr_k(arg_t<vf_type> xr2h, arg_t<vf_type> xr2l)
{
    constexpr
    const double b0_c0=+1.0000000000000000000000e+00;
    constexpr
    const double b0_c2=-6.2500000000000000000000e-02;
    constexpr
    const double b0_c4=+1.0351562500000000000000e-01;
    constexpr
    const double b0_c6=-5.4284667968750000000000e-01;
    constexpr
    const double b0_c8=+5.8486995697021479999160e+00;
    constexpr
    const double b0_c10=-1.0688679397106169999959e+02;
    constexpr
    const double b0_c12=+2.9681429378427570000554e+03;
    constexpr
    const double b0_c14=-1.1653847969683609999691e+05;
    // constexpr
    // const double b0_c16=+6.1484514628788009999880e+06;
    constexpr const static double ci[]={
        /* b0_c16, */ b0_c14, b0_c12, b0_c10, b0_c8, b0_c6, b0_c4, b0_c2
    };
    vf_type beta=horner2(xr2h, vf_type(xr2h*xr2h),ci);
    static_cast<void>(xr2l);
    vf_type bh, bl;
    d_ops::mul122(bh, bl, beta, xr2h, xr2l);
    d_ops::add122(bh, bl, b0_c0, bh, bl);
    return vdf_type(bh, bl);
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
__y1_singular_k(arg_t<vf_type> xc)
{
    vf_type r=0;
    // x^ : +0xcp-4
    constexpr
    const double y1_i0_r=+7.5000000000000000000000e-01;
    if (_T::any_of_vmf(xc < y1_i0_r)) {
        // [12;12]
        // [0, 0.75] : | p - f | <= 2^-72.6875
        // coefficients for j1 generated by sollya
        // x^1 : +0x8p-4
        constexpr
        const double j1z1=+5.0000000000000000000000e-01;
        // x^3 : -0x8p-7
        constexpr
        const double j1z3=-6.2500000000000000000000e-02;
        // x^5 : +0xa.aaaaaaaaaaaap-12
        constexpr
        const double j1z5=+2.6041666666666660884255e-03;
        // x^7 : -0xe.38e38e38dfe5p-18
        constexpr
        const double j1z7=-5.4253472222209520492604e-05;
        // x^9 : +0xb.60b60b5905bdp-24
        constexpr
        const double j1z9=+6.7816840267107568686518e-07;
        // x^11 : -0xc.22e4404c151d8p-31
        constexpr
        const double j1z11=-5.6514029094566818030946e-09;
        // x^13 : +0x9.3f15e0bb5c6ep-38
        constexpr
        const double j1z13=+3.3638307576017311882757e-11;
        // x^15 : -0xa.7cd4eb9f1d2cp-46
        constexpr
        const double j1z15=-1.4903809965601590510453e-13;
        // [13;13]
        // [0, 0.75] : | p - f | <= 2^-68.625
        // coefficients for y1_r generated by sollya
        // x^1 h: -0x9.dadb014541ebp-5
        constexpr
        const double y1r1h=-3.0796575782920621033867e-01;
        // x^1 l: -0x8.19b86f675d59p-59
        constexpr
        const double y1r1l=-1.4052076355591673554272e-17;
        // x^3 : +0xa.ed6d80a2a0f58p-7
        constexpr
        const double y1r3=+8.5370719728650776292334e-02;
        // x^5 : -0x9.81d7394ff96f8p-11
        constexpr
        const double y1r5=-4.6421827664715189717959e-03;
        // x^7 : +0xe.c0157bd2b4cdp-17
        constexpr
        const double y1r7=+1.1253607036590951837908e-04;
        // x^9 : -0xd.148c10de03818p-23
        constexpr
        const double y1r9=-1.5592887682717630693836e-06;
        // x^11 : +0xf.1094a3125a438p-30
        constexpr
        const double y1r11=+1.4030158538940729858144e-08;
        // x^13 : -0xc.31416e34db5e8p-37
        constexpr
        const double y1r13=-8.8711419376389649799246e-11;
        // x^15 : +0xe.72e6ca92d43c8p-45
        constexpr
        const double y1r15=+4.1066056427919538175287e-13;

        // y1(x) = 2/pi*(f(x) + (j1(x) * log(x) - 1/x));
        // y1(x) = 2/pi*(scale_down * f(x) +
        //               j1(x) * scale_down * log(x)
        //               -1,0/x/scale_down)*scale_up;
        // y1(x) = 2/pi*(scale_down * f(x) +
        //               j1(x) * scale_down * log(x)
        //               -1,0/(x*scale_up))*scale_up
        // scaling is required near zero to avoid nans
        // in the calculation of the sum
        const double scale_down=0x1p-54;
        const double scale_up=0x1p54;

        constexpr static const double j1coeffs[]={
            j1z15, j1z13, j1z11, j1z9, j1z7, j1z5
        };
        vf_type x2=xc*xc;
        vf_type j1p=horner(x2, j1coeffs);
        vf_type j1h, j1l;
        horner_comp_quick(j1h, j1l, x2, j1p, j1z3, j1z1);
        vf_type t;
        d_ops::mul12(j1h, t, j1h, xc);
        j1l= j1l*xc + t;

        constexpr static const double y1rcoeffs[]={
            y1r15, y1r13, y1r11, y1r9, y1r7, y1r5, y1r3
        };
        vf_type y1rp=horner(x2, y1rcoeffs);
        vf_type y1rh, y1rl;
        horner_comp_quick_dpc_s0(y1rh, y1rl, x2, y1rp, y1r1h, y1r1l);
        d_ops::mul122(y1rh, y1rl, xc, y1rh, y1rl);

        y1rh *= scale_down;
        y1rl *= scale_down;

        vdf_type ln_x=base_type::__log_tbl_k12(xc);
        ln_x[0] *=scale_down;
        ln_x[1] *=scale_down;

        vf_type y1h, y1l;
        vdf_type neg_inv_x;
        d_ops::rcp12(neg_inv_x[0], neg_inv_x[1], -(xc*scale_up));
        d_ops::unorm_mul22(y1h, y1l, j1h, j1l, ln_x[0], ln_x[1]);
        d_ops::add22cond(y1h, y1l, y1h, y1l, neg_inv_x[0], neg_inv_x[1]);
        d_ops::add22cond(y1h, y1l, y1h, y1l, y1rh, y1rl);
        using ctbl=impl::d_real_constants<d_real<double>, double>;
        d_ops::unorm_mul22(y1h, y1l, y1h, y1l, ctbl::m_2_pi[0], ctbl::m_2_pi[1]);
        r = (y1h + y1l)*scale_up;
    }
    // x^ : +0xap-3
    constexpr
    const double y1_i1_r=+1.2500000000000000000000e+00;
    vmf_type msk=(xc >= y1_i0_r)  & (xc < y1_i1_r);
    if (_T::any_of_vmf(msk)) {
        // [0.75;1.25] [21;21]
        // shifted [-0.25;0.25] [21;21]
        // [-0.25, 0.25] : | p - f | <= 2^-61.40625
        // coefficients for y1_i1 generated by sollya
        // x^0 h: -0xc.7fd903eb35cap-4
        constexpr
        const double y1_i1_0h=-7.8121282130028868451177e-01;
        // x^0 l: -0x9.3c009b9794c5p-58
        constexpr
        const double y1_i1_0l=-3.2038206372641654932001e-17;
        // x^1 : +0xd.e959265a6b58p-4
        constexpr
        const double y1_i1_1=+8.6946978551596565409909e-01;
        // x^2 : -0xd.e959265a6b578p-5
        constexpr
        const double y1_i1_2=-4.3473489275798277153839e-01;
        // x^3 : +0x8.cdbb636c8b518p-4
        constexpr
        const double y1_i1_3=+5.5022753560543369300007e-01;
        // x^4 : -0x9.f682d1496a348p-4
        constexpr
        const double y1_i1_4=-6.2268335106513206245182e-01;
        // x^5 : +0x9.fc89384272d5p-4
        constexpr
        const double y1_i1_5=+6.2415430046455822044038e-01;
        // x^6 : -0xa.056caac1c0b4p-4
        constexpr
        const double y1_i1_6=-6.2632433606999615705035e-01;
        // x^7 : +0xa.116d235acdcf8p-4
        constexpr
        const double y1_i1_7=+6.2925447283202007309200e-01;
        // x^8 : -0xa.18e057e7acefp-4
        constexpr
        const double y1_i1_8=-6.3107332551845352064390e-01;
        // x^9 : +0xa.1dccb2e2b0468p-4
        constexpr
        const double y1_i1_9=+6.3227529408597293869576e-01;
        // x^10 : -0xa.214bd391aefap-4
        constexpr
        const double y1_i1_10=-6.3312895435495741836007e-01;
        // x^11 : +0xa.23dedd813e828p-4
        constexpr
        const double y1_i1_11=+6.3375746274314848083264e-01;
        // x^12 : -0xa.25d30eb1ea6ep-4
        constexpr
        const double y1_i1_12=-6.3423448314884067755770e-01;
        // x^13 : +0xa.2712c98a542p-4
        constexpr
        const double y1_i1_13=+6.3453940130899155747102e-01;
        // x^14 : -0xa.27b1bd89e8f3p-4
        constexpr
        const double y1_i1_14=-6.3469099081572433185272e-01;
        // x^15 : +0xa.2d6512d3f60e8p-4
        constexpr
        const double y1_i1_15=+6.3608271937062321743639e-01;
        // x^16 : -0xa.38f69d16adf2p-4
        constexpr
        const double y1_i1_16=-6.3890706408244257730189e-01;
        // x^17 : +0xa.0090b1d551eb8p-4
        constexpr
        const double y1_i1_17=+6.2513799158215987983311e-01;
        // x^18 : -0x9.7f5b74ebd163p-4
        constexpr
        const double y1_i1_18=-5.9359307930306992595604e-01;
        // x^19 : +0xb.01cebfef856fp-4
        constexpr
        const double y1_i1_19=+6.8794131255011925496490e-01;
        // x^20 : -0xe.7191d41c65d78p-4
        constexpr
        const double y1_i1_20=-9.0272696357566484248736e-01;
        // x^21 : +0xa.0ac12f9943b18p-4
        constexpr
        const double y1_i1_21=+6.2762564271200138588114e-01;
        // x^ : +0x8p-3
        constexpr
        const double y1_i1_x0=+1.0000000000000000000000e+00;

        constexpr static const double ci[]={
            y1_i1_21, y1_i1_20, y1_i1_19, y1_i1_18, y1_i1_17, y1_i1_16,
            y1_i1_15, y1_i1_14, y1_i1_13, y1_i1_12, y1_i1_11, y1_i1_10,
            y1_i1_9, y1_i1_8, y1_i1_7, y1_i1_6, y1_i1_5, y1_i1_4, y1_i1_3
        };
        // sterbenz lemma: subtraction is exact
        vf_type xrh=xc - y1_i1_x0;
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y1_i1_2, y1_i1_1);
        horner_comp_quick_dpc_si(ph, pl, xrh, ph, pl, y1_i1_0h, y1_i1_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x8p-2
    constexpr
    const double y1_i2_r=+2.0000000000000000000000e+00;
    msk=(xc >= y1_i1_r)  & (xc < y1_i2_r);
    if (_T::any_of_vmf(msk)) {
        // [-0.375, 0.375] : | p - f | <= 2^-60.0625
        // coefficients for y1_i2 generated by sollya
        // x^0 h: -0xa.9d3d9f86fdb88p-5
        constexpr
        const double y1_i2_0h=-3.3169442327191861474844e-01;
        // x^0 l: -0xf.d0bd9329b54b8p-59
        constexpr
        const double y1_i2_0l=-2.7435332968517539628414e-17;
        // x^1 : +0xa.20eb9f0d9cefp-4
        constexpr
        const double y1_i2_1=+6.3303720598360846416597e-01;
        // x^2 : -0xb.be1ecd67974c8p-7
        constexpr
        const double y1_i2_2=-9.1739511771431372921803e-02;
        // x^3 : +0x9.b8e5382fc5fb8p-9
        constexpr
        const double y1_i2_3=+1.8988764866559617455755e-02;
        // x^4 : -0xd.80149f1e9cd78p-8
        constexpr
        const double y1_i2_4=-5.2735604140809903828124e-02;
        // x^5 : +0x9.0740a024aeba8p-8
        constexpr
        const double y1_i2_5=+3.5266913506968679270503e-02;
        // x^6 : -0xa.7607e5eed8d88p-9
        constexpr
        const double y1_i2_6=-2.0431753938667977094079e-02;
        // x^7 : +0xc.f6fbd269a0868p-10
        constexpr
        const double y1_i2_7=+1.2660917966429008699181e-02;
        // x^8 : -0x8.1155543d71358p-10
        constexpr
        const double y1_i2_8=-7.8786213556309627609187e-03;
        // x^9 : +0x9.fa645b7f84c5p-11
        constexpr
        const double y1_i2_9=+4.8721161292085788524497e-03;
        // x^10 : -0xc.52320152b49p-12
        constexpr
        const double y1_i2_10=-3.0080750777134040996330e-03;
        // x^11 : +0xf.33cedd189a638p-13
        constexpr
        const double y1_i2_11=+1.8557586961549952988410e-03;
        // x^12 : -0x9.5fa281259d09p-13
        constexpr
        const double y1_i2_12=-1.1442350307110421732404e-03;
        // x^13 : +0xb.904f5e84fcb2p-14
        constexpr
        const double y1_i2_13=+7.0579291248388771953803e-04;
        // x^14 : -0xe.3c2f2a8eec56p-15
        constexpr
        const double y1_i2_14=-4.3442061461663561243440e-04;
        // x^15 : +0x8.9aa0fed98158p-15
        constexpr
        const double y1_i2_15=+2.6257382496556579826175e-04;
        // x^16 : -0xa.d4b4493c90fp-16
        constexpr
        const double y1_i2_16=-1.6526605144152797105539e-04;
        // x^17 : +0x8.609243072517p-16
        constexpr
        const double y1_i2_17=+1.2782641263393970448500e-04;
        // x^18 : -0xf.be2c9045272cp-18
        constexpr
        const double y1_i2_18=-6.0054273551515726780464e-05;
        // x^19 : -0xa.62403da7326p-18
        constexpr
        const double y1_i2_19=-3.9611025761840303743844e-05;
        // x^20 : -0x8.2b00193d6155p-18
        constexpr
        const double y1_i2_20=-3.1158333795193907220407e-05;
        // x^21 : +0xf.43932b828a76p-17
        constexpr
        const double y1_i2_21=+1.1645480640705738835036e-04;
        // x^ : +0xdp-3
        constexpr
        const double y1_i2_x0=+1.6250000000000000000000e+00;
        constexpr static const double ci[]={
            y1_i2_21, y1_i2_20, y1_i2_19, y1_i2_18, y1_i2_17, y1_i2_16,
            y1_i2_15, y1_i2_14, y1_i2_13, y1_i2_12, y1_i2_11, y1_i2_10,
            y1_i2_9, y1_i2_8, y1_i2_7, y1_i2_6, y1_i2_5, y1_i2_4, y1_i2_3
        };
        // sterbenz lemma: subtraction is exact
        vf_type xrh=xc - y1_i2_x0;
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y1_i2_2, y1_i2_1);
        horner_comp_dpc_si(ph, pl, xrh, ph, pl, y1_i2_0h, y1_i2_0l);
        r = _T::sel(msk, ph+pl, r);
    }
    constexpr
    const double y1_i3_r=+3.2500000000000000000000e+00;
    msk=(xc >= y1_i2_r)  & (xc < y1_i3_r);
    if (_T::any_of_vmf(msk)) {
        // [2;3.25] [16;16]
        // shifted [-0.1971413195133209228515625;1.05285871028900146484375] [20;20]
        // [-0.1971413195133209228515625, 1.05285871028900146484375] : | p - f | <= 2^-63.40625
        // coefficients for y1_i3 generated by sollya
        // x^1 h: +0x8.5524221780a58p-4
        constexpr
        const double y1_i3_1h=+5.2078641240226752895381e-01;
        // x^1 l: -0xa.3f98a4843638p-59
        constexpr
        const double y1_i3_1l=-1.7778179782286171101554e-17;
        // x^2 : -0xf.2b7c110bdc79p-7
        constexpr
        const double y1_i3_2=-1.1851454574909661698889e-01;
        // x^3 : -0x8.6957a74991c7p-8
        constexpr
        const double y1_i3_3=-3.2857397405286467573227e-02;
        // x^4 : -0x9.d36f61b943a4p-11
        constexpr
        const double y1_i3_4=-4.7978116701033537983001e-03;
        // x^5 : +0xf.338e3e88d56a8p-11
        constexpr
        const double y1_i3_5=+7.4225533327118746809714e-03;
        // x^6 : -0xa.a14ee2d556618p-12
        constexpr
        const double y1_i3_6=-2.5952416884443565113505e-03;
        // x^7 : +0x8.bd5a57dda1de8p-13
        constexpr
        const double y1_i3_7=+1.0668530002713027139000e-03;
        // x^8 : -0x8.596c3a1e3318p-14
        constexpr
        const double y1_i3_8=-5.0960129781003025983832e-04;
        // x^9 : +0xf.753dc0cfe942p-16
        constexpr
        const double y1_i3_9=+2.3586995740711516351268e-04;
        // x^10 : -0xe.1fd7a760b5ad8p-17
        constexpr
        const double y1_i3_10=-1.0776050084030984281807e-04;
        // x^11 : +0xc.e8c5e09bae36p-18
        constexpr
        const double y1_i3_11=+4.9244954563647979272831e-05;
        // x^12 : -0xb.cae6891415858p-19
        constexpr
        const double y1_i3_12=-2.2492561706537047915662e-05;
        // x^13 : +0xa.c292a3fd892bp-20
        constexpr
        const double y1_i3_13=+1.0261583383360986493999e-05;
        // x^14 : -0x9.c6377972542cp-21
        constexpr
        const double y1_i3_14=-4.6607417927645218721187e-06;
        // x^15 : +0x8.b450329400a48p-22
        constexpr
        const double y1_i3_15=+2.0752784533063789490948e-06;
        // x^16 : -0xe.9591e1e8c913p-24
        constexpr
        const double y1_i3_16=-8.6928947208277715606717e-07;
        // x^17 : +0xa.a91ff585df5p-25
        constexpr
        const double y1_i3_17=+3.1771194656993402875237e-07;
        // x^18 : -0xc.326583773c178p-27
        constexpr
        const double y1_i3_18=-9.0873699439058287753613e-08;
        // x^19 : +0x9.5544a6c24a0b8p-29
        constexpr
        const double y1_i3_19=+1.7384213930487206294822e-08;
        // x^20 : -0xd.eff6801ae60a8p-33
        constexpr
        const double y1_i3_20=-1.6225216733020176261084e-09;
        // x^ h: +0x8.c9df6a6ff9218p-2
        constexpr
        const double y1_i3_x0h=+2.1971413260310170834089e+00;
        // x^ m: -0xd.e8f28690cdfe8p-58
        constexpr
        const double y1_i3_x0m=-4.8259835876454965669631e-17;
        // x^ l: -0xf.555e7499dfb2p-117
        constexpr
        const double y1_i3_x0l=-9.2284980904770750532002e-35;

        constexpr static const double ci[]={
            y1_i3_20, y1_i3_19, y1_i3_18, y1_i3_17, y1_i3_16,
            y1_i3_15, y1_i3_14, y1_i3_13, y1_i3_12, y1_i3_11, y1_i3_10,
            y1_i3_9, y1_i3_8, y1_i3_7, y1_i3_6, y1_i3_5, y1_i3_4
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y1_i3_x0h, -y1_i3_x0m);
        d_ops::add122cond(xrh, xrl, -y1_i3_x0l, xrh, xrl);
        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp_quick(ph, pl, xrh, p, y1_i3_3, y1_i3_2);
        horner_comp_dpc_si(ph, pl, xrh, ph, pl, y1_i3_1h, y1_i3_1l);
        d_ops::unorm_mul22(ph, pl, ph, pl, xrh, xrl);
        r = _T::sel(msk, ph+pl, r);
    }
    // x^ : +0x9.8p-1
    constexpr
    const double y1_i4_r=+4.7500000000000000000000e+00;
    msk=(xc >= y1_i3_r)  & (xc <= y1_i4_r);
    if (_T::any_of_vmf(msk)) {
        // [3.25;4.75] [15;15]
        // shifted [-0.4330228269100189208984375;1.06697714328765869140625] [18;18]
        // [-0.4330228269100189208984375, 1.06697714328765869140625] : | p - f | <= 2^-64.125
        // coefficients for y1_i4 generated by sollya
        // x^0 h: +0xd.55da008f6995p-5
        constexpr
        const double y1_i4_0h=+4.1672992810645104189149e-01;
        // x^0 l: +0xe.3c42e1b096bp-62
        constexpr
        const double y1_i4_0l=+3.0868093524486725474324e-18;
        // x^1 : +0x8.96ec971d2b59p-29
        constexpr
        const double y1_i4_1=+1.5999279136418596308008e-08;
        // x^2 : -0xc.5a2dd7e9cde5p-6
        constexpr
        const double y1_i4_2=-1.9300409398348811196300e-01;
        // x^3 : +0xf.0a382a5fad6f8p-10
        constexpr
        const double y1_i4_3=+1.4687421404159404711431e-02;
        // x^4 : +0xc.62d79154197cp-10
        constexpr
        const double y1_i4_4=+1.2095802540920783108014e-02;
        // x^5 : -0x8.99fd06c019c48p-14
        constexpr
        const double y1_i4_5=-5.2499494177170411435968e-04;
        // x^6 : -0xd.fc57cf848d458p-15
        constexpr
        const double y1_i4_6=-4.2681014659643666487795e-04;
        // x^7 : +0x9.0eb25d902b63p-18
        constexpr
        const double y1_i4_7=+3.4551273884781500962508e-05;
        // x^8 : +0xa.2696530413308p-23
        constexpr
        const double y1_i4_8=+1.2100614626996119782906e-06;
        // x^9 : +0x8.a61d31e3e6938p-23
        constexpr
        const double y1_i4_9=+1.0310271952834928524786e-06;
        // x^10 : -0xd.c7789a8f81cf8p-25
        constexpr
        const double y1_i4_10=-4.1065168432043908409109e-07;
        // x^11 : +0xd.4315027edb6a8p-27
        constexpr
        const double y1_i4_11=+9.8809892932443476132034e-08;
        // x^12 : -0xd.fc55741d65998p-29
        constexpr
        const double y1_i4_12=-2.6050356995414196360304e-08;
        // x^13 : +0xf.7b4458df5993p-31
        constexpr
        const double y1_i4_13=+7.2091406420188448608650e-09;
        // x^14 : -0x8.6e3ebec7b3858p-32
        constexpr
        const double y1_i4_14=-1.9629124822795750224572e-09;
        // x^15 : +0x9.5a2980db3322p-34
        constexpr
        const double y1_i4_15=+5.4436944138622550132294e-10;
        // x^16 : -0xc.0ca692207ffa8p-36
        constexpr
        const double y1_i4_16=-1.7534208991607721816191e-10;
        // x^17 : +0x8.d4fecf37dd4c8p-37
        constexpr
        const double y1_i4_17=+6.4261352844116474578262e-11;
        // x^18 : -0xe.a0c7175df6a4p-40
        constexpr
        const double y1_i4_18=-1.3304122959932861281662e-11;
        // x^19 : -0xc.02a51c355a218p-41
        constexpr
        const double y1_i4_19=-5.4616666064009058862486e-12;
        // x^20 : +0x9.ecae020cd1ae8p-41
        constexpr
        const double y1_i4_20=+4.5131537951832963771427e-12;
        // x^21 : -0xf.f1ff9e4ee8e78p-44
        constexpr
        const double y1_i4_21=-9.0638574631142475031700e-13;
        // x^ h: +0xe.bb6a5535be5c8p-2
        constexpr
        const double y1_i4_x0h=+3.6830228151371469103026e+00;
        // x^ m: +0x8.ec9ef46b6cf4p-56
        constexpr
        const double y1_i4_x0m=+1.2384954807844144259185e-16;
        // x^ l: -0xd.5b63f12dd3c6p-111
        constexpr
        const double y1_i4_x0l=-5.1449268442928228436045e-33;

        constexpr static const double ci[]={
            y1_i4_21, y1_i4_20, y1_i4_19, y1_i4_18, y1_i4_17, y1_i4_16,
            y1_i4_15, y1_i4_14, y1_i4_13, y1_i4_12, y1_i4_11, y1_i4_10,
            y1_i4_9, y1_i4_8, y1_i4_7, y1_i4_6, y1_i4_5
        };
        vf_type xrh, xrl;
        d_ops::add122cond(xrh, xrl, xc, -y1_i4_x0h, -y1_i4_x0m);
        d_ops::add122cond(xrh, xrl, -y1_i4_x0l, xrh, xrl);

        vf_type p=horner2(xrh, vf_type(xrh*xrh), ci);
        vf_type ph, pl;
        horner_comp(ph, pl, xrh, p, y1_i4_4, y1_i4_3, y1_i4_2, y1_i4_1);
        d_ops::unorm_mul22(ph, pl, xrh, xrl, ph, pl);
        d_ops::add22(ph, pl, y1_i4_0h, y1_i4_0l, ph, pl);
        r = _T::sel(msk, ph, r);
    }
    return r;
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
__j1y1_phase_corr_k(arg_t<vf_type> xr2h,
                    arg_t<vf_type> xr2l,
                    arg_t<vf_type> xrh,
                    arg_t<vf_type> xrl)
{
    constexpr
    const double a1_c1=+3.7500000000000000000000e-01;
    constexpr
    const double a1_c3=-1.6406250000000000000000e-01;
    constexpr
    const double a1_c5_h=+3.7089843750000001110223e-01;
    constexpr
    const double a1_c5_l=-1.1102230246000000000212e-17;
    constexpr
    const double a1_c7_h=-2.3693978445870533811046e+00;
    constexpr
    const double a1_c7_l=-1.9032394707900000000225e-16;
    constexpr
    const double a1_c9=+3.0624011993408203125000e+01;
    constexpr
    const double a1_c11_h=-6.5918522182377898843697e+02;
    constexpr
    const double a1_c11_l=-3.1005501196804000000324e-14;
    constexpr
    const double a1_c13_h=+2.1156314045527808048064e+04;
    constexpr
    const double a1_c13_l=-1.3992226181121969999522e-12;
    constexpr
    const double a1_c15_h=-9.4434660954805475194007e+05;
    constexpr
    const double a1_c15_l=+2.3283064365386964000079e-11;

    static_cast<void>(a1_c5_l);
    static_cast<void>(a1_c7_l);
    static_cast<void>(a1_c11_l);
    static_cast<void>(a1_c13_l);
    static_cast<void>(a1_c15_h);
    static_cast<void>(a1_c15_l);
    constexpr const static double ci[]={
        /* a0_c15, */ a1_c13_h, a1_c11_h, a1_c9, a1_c7_h
    };
    vf_type p=horner(xr2h, ci);
    vf_type ph, pl;
    horner_comp_quick_dpc_s0(ph, pl, xr2h, p, a1_c5_h, a1_c5_l);
    horner_comp_quick_si(ph, pl, xr2h, ph, pl, a1_c3);

    d_ops::mul22(ph, pl, xr2h, xr2l, ph, pl);
    d_ops::add122(ph, pl, a1_c1, ph, pl);
    d_ops::mul22(ph, pl, xrh, xrl, ph, pl);
    return vdf_type(ph, pl);
}

template <typename _T>
inline
typename cftal::math::spec_func_core<double, _T>::vdf_type
cftal::math::spec_func_core<double, _T>::
__j1y1_amplitude_corr_k(arg_t<vf_type> xr2h, arg_t<vf_type> xr2l)
{
    constexpr
    const double b1_c0=+1.0000000000000000000000e+00;
    constexpr
    const double b1_c2=+1.8750000000000000000000e-01;
    constexpr
    const double b1_c4=-1.9335937500000000000000e-01;
    constexpr
    const double b1_c6=+8.0529785156250000000000e-01;
    constexpr
    const double b1_c8=-7.7399539947509770000840e+00;
    constexpr
    const double b1_c10=+1.3276182425022130000059e+02;
    constexpr
    const double b1_c12=-3.5433036653660240000718e+03;
    constexpr
    const double b1_c14=+1.3539422856918089999567e+05;
    // constexpr
    // const double b1_c16=-7.0031415747524329999578e+06;
    constexpr const static double ci[]={
        /* b1_c16, */ b1_c14, b1_c12, b1_c10, b1_c8, b1_c6, b1_c4, b1_c2
    };
    vf_type beta=horner2(xr2h, vf_type(xr2h*xr2h), ci);
    static_cast<void>(xr2l);
    vf_type bh, bl;
    d_ops::mul122(bh, bl, beta, xr2h, xr2l);
    d_ops::add122(bh, bl, b1_c0, bh, bl);
    return vdf_type(bh, bl);
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
__j01y01_large_phase_amplitude_k(arg_t<vf_type> xc,
                                 bool calc_yn,
                                 bool calc_jy1)
{
    scoped_ftz_daz_mode ftz_daz_mode;

    vf_type rec_x_h, rec_x_l;
    d_ops::div12(rec_x_h, rec_x_l, 1.0, xc);
    vf_type xr2h, xr2l;
    d_ops::sqr22(xr2h, xr2l, rec_x_h, rec_x_l);

    // x^ : +0xc.c42299ea1b288p-4
    constexpr
    const double sqrt_two_over_pi_h=+7.9788456080286540572644e-01;
    // x^ : -0xe.5e069875fe8a8p-58
    constexpr
    const double sqrt_two_over_pi_l=-4.9846544045554600887898e-17;
    // select amplitude correction for j0/y0 or j1/y1
    vdf_type amp_cor= calc_jy1 == false ?
        __j0y0_amplitude_corr_k(xr2h, xr2l) :
        __j1y1_amplitude_corr_k(xr2h, xr2l);

    auto rsqrt_xc=rsqrt12_k(xc);
    vf_type amph, ampl;
    d_ops::mul22(amph, ampl,
                 amp_cor[0], amp_cor[1], rsqrt_xc[0], rsqrt_xc[1]);
    d_ops::mul22(amph, ampl, amph, ampl,
                 sqrt_two_over_pi_h, sqrt_two_over_pi_l);

    vf_type xrh, xrm, xrl;
    vi2_type q=__reduce_trig_arg(xrh, xrm, xrl, xc);

    vf_type xsh, xsl;
    // x^ : +0xc.90fdaa22168cp-4
    constexpr
    const double pi_4_0=+7.8539816339744827899949e-01;
    // x^ : +0x8.d313198a2e038p-58
    constexpr
    const double pi_4_1=+3.0616169978683830179344e-17;
    // x^ : -0xf.8cbb5bf6c7dep-114
    constexpr
    const double pi_4_2=-7.4869245242958491647175e-34;
    using t_ops=t_real_ops<vf_type>;
    // if x >= 0 subtract pi/4
    // if x < 0 add pi/4 and subtract -1 from q
    vmf_type is_x_lt_z = xrh < 0.0;
    vmi2_type i_is_x_lt_z = _T::vmf_to_vmi2(is_x_lt_z);
    vf_type d0=_T::sel(is_x_lt_z, pi_4_0, -pi_4_0);
    vf_type d1=_T::sel(is_x_lt_z, pi_4_1, -pi_4_1);
    vf_type d2=_T::sel(is_x_lt_z, pi_4_2, -pi_4_2);
    q = _T::sel_vi2(i_is_x_lt_z, q - 1, q);
    t_ops::add33cond(xrh, xrm, xrl,
                     xrh, xrm, xrl,
                     d0, d1, d2);
    // select phase  correction for j0/y0 or j1/y1
    vdf_type phase_cor= calc_jy1 == false ?
        __j0y0_phase_corr_k(xr2h, xr2l, rec_x_h, rec_x_l) :
        __j1y1_phase_corr_k(xr2h, xr2l, rec_x_h, rec_x_l);
    t_ops::add233cond(xrh, xrm, xrl, phase_cor[0], phase_cor[1],
                      xrh, xrm, xrl);
    t_ops::renormalize32(xsh, xsl, xrh, xrm, xrl);
    // perform argument reduction on xsh, xsl again
    vf_type xh, xl;
    auto q2=__reduce_trig_arg_tiny(xh, xl, xsh, xsl);
    if (calc_jy1 == false) {
        q2 += q;
    } else {
        // -1 for the subtraction of only pi/4 above, i.e. q2 is 1 too large
        q2 += q-1;
    }
    // q2 &= 3;

    vdf_type phase;
    // select sinus or cosinus for y0/1 or j0/1 calculation
    vdf_type* psin = calc_yn ? &phase : nullptr;
    vdf_type* pcos = calc_yn ? nullptr : &phase;
    base_type::__sin_cos_k(xh, xl, q2, psin, pcos);

    vf_type rh, rl;
    d_ops::mul22(rh, rl, phase[0], phase[1], amph, ampl);
    return rh;
}


template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
j0_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const double small_threshold=j01y01_data<double>::_max_small_j0;
    const vmf_type xa_small = xa <= small_threshold;
    bool any_small;
    if ((any_small=_T::any_of_vmf(xa_small))==true) {
        r= __j01y01_small_tbl_k(xa,
                                j01y01_data<double>::_j0_coeffs,
                                j01y01_data<double>::_max_small_j0);
    }
    if (!_T::all_of_vmf(xa_small)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, false, false);
        if (any_small) {
            r = _T::sel(xa_small, r, rl);
        } else {
            r = rl;
        }
    }
    return r;
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
j1_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const double small_threshold=j01y01_data<double>::_max_small_j1;
    const vmf_type xa_small = xa <= small_threshold;
    bool any_small;
    if ((any_small=_T::any_of_vmf(xa_small))==true) {
        r= __j01y01_small_tbl_k(xa,
                                j01y01_data<double>::_j1_coeffs,
                                j01y01_data<double>::_max_small_j1);
    }
    if (!_T::all_of_vmf(xa_small)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, false, true);
        if (any_small) {
            r = _T::sel(xa_small, r, rl);
        } else {
            r = rl;
        }
    }
    // r=r*copysign(1.0, xc);
    r = mulsign(r, xc);
    return r;
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
y0_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const double small_threshold=j01y01_data<double>::_max_small_y0;
    const double singular_threshold=4.75;
    bool select_required=false;
    if (_T::any_of_vmf(xa <= singular_threshold)==true) {
        r=__y0_singular_k(xa);
        select_required=true;
    }
    vmf_type msk_xa_small=(xa > singular_threshold) &
                          (xa <= small_threshold);
    if (_T::any_of_vmf(msk_xa_small)==true) {
        vf_type rs= __j01y01_small_tbl_k(xa,
                                         j01y01_data<double>::_y0_coeffs,
                                         j01y01_data<double>::_max_small_y0);
        if (select_required==false) {
            r=rs;
            select_required=true;
        } else {
            r=_T::sel(msk_xa_small, rs, r);
        }
    }
    vmf_type msk_xa_large= xa > small_threshold;
    if (_T::any_of_vmf(msk_xa_large)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, true, false);
        if (select_required==false) {
            r = rl;
        } else {
            r = _T::sel(msk_xa_large, rl, r);
        }
    }
    return r;
}

template <typename _T>
typename cftal::math::spec_func_core<double, _T>::vf_type
cftal::math::spec_func_core<double, _T>::
y1_k(arg_t<vf_type> xc)
{
    vf_type xa=abs(xc);
    vf_type r;
    const double small_threshold=j01y01_data<double>::_max_small_y1;
    const double singular_threshold=4.75;
    bool select_required=false;
    if (_T::any_of_vmf(xa <= singular_threshold)==true) {
        r=__y1_singular_k(xa);
        select_required=true;
    }
    vmf_type msk_xa_small=(xa > singular_threshold) &
                          (xa <= small_threshold);
    if (_T::any_of_vmf(msk_xa_small)==true) {
        vf_type rs= __j01y01_small_tbl_k(xa,
                                         j01y01_data<double>::_y1_coeffs,
                                         j01y01_data<double>::_max_small_y1);
        if (select_required==false) {
            r=rs;
            select_required=true;
        } else {
            r=_T::sel(msk_xa_small, rs, r);
        }
    }
    vmf_type msk_xa_large= xa > small_threshold;
    if (_T::any_of_vmf(msk_xa_large)) {
        vf_type rl= __j01y01_large_phase_amplitude_k(xa, true, true);
        if (select_required==false) {
            r = rl;
        } else {
            r = _T::sel(msk_xa_large, rl, r);
        }
    }
    return r;
}

// Local Variables:
// mode: c++
// end:
#endif
