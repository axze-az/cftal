//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_MATH_LANCZOS_H__)
#define __CFTAL_MATH_LANCZOS_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/math/horner.h>

namespace cftal {
    namespace math {

        // calculation of a lanczos rational
        template <typename _T, typename _C,
                  std::size_t _N1, std::size_t _N2>
        d_real<_T>
        lanczos_rational_at(const _T& x,
                            const d_real<_C>(&p)[_N1],
                            const _C (&q)[_N2]);

        // calculation of a lanczos rational
        template <typename _T, typename _C,
                  std::size_t _N1, std::size_t _N2>
        _T
        lanczos_rational_at(const _T& x,
                            const _C(&p)[_N1],
                            const _C(&q)[_N2]);

        // lanczos table for double (f64)
        struct lanczos_table_g_10_90990_N11 {
            static constexpr
            double g() {
                return +1.0909898534417152404785e+01;
            }
            static constexpr
            double g_l() {
                return -4.0478515624999999998911e-16;
            }
            static constexpr
            double gm0_5() {
                return +1.0409898534417152404785e+01;
            }
            static constexpr
            double gm0_5_l() {
                return -4.0478515624999999998911e-16;
            }
            static constexpr
            double exp_minus_gm0_5_h() {
                return +3.0132732023154958056997e-05;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return -1.1971360000000000000281e-21;
            }
            static constexpr
            const double p[]={
                +2.5066282746310006857016e+00, // 10
                +2.6187065518312238054932e+02, // 9
                +1.2311319767111477631261e+04, // 8
                +3.4299443207995168631896e+05, // 7
                +6.2711532085765050724149e+06, // 6
                +7.8624812015718936920166e+07, // 5
                +6.8457039664262735843658e+08, // 4
                +4.0872263850670909881592e+09, // 3
                +1.6014654956325389862061e+10, // 2
                +3.7185344427643363952637e+10, // 1
                +3.8855076805286621093750e+10  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 10
                +4.5000000000000000000000e+01, // 9
                +8.7000000000000000000000e+02, // 8
                +9.4500000000000000000000e+03, // 7
                +6.3273000000000000000000e+04, // 6
                +2.6932500000000000000000e+05, // 5
                +7.2368000000000000000000e+05, // 4
                +1.1727000000000000000000e+06, // 3
                +1.0265760000000000000000e+06, // 2
                +3.6288000000000000000000e+05, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282746310006857016e+00, -1.6773475855199999999913e-16}, // 10
                {+2.6187065518312238054932e+02, -1.2812429541626000000275e-14}, // 9
                {+1.2311319767111477631261e+04, +6.2201294658791100001415e-13}, // 8
                {+3.4299443207995168631896e+05, -4.3477764530887790001205e-12}, // 7
                {+6.2711532085765050724149e+06, +5.7137835076712168000887e-11}, // 6
                {+7.8624812015718936920166e+07, -2.0888657751873848870233e-09}, // 5
                {+6.8457039664262735843658e+08, +3.3146818638551557162211e-08}, // 4
                {+4.0872263850670909881592e+09, +1.0948108501573320361921e-07}, // 3
                {+1.6014654956325389862061e+10, +5.7745485035403720986856e-07}, // 2
                {+3.7185344427643363952637e+10, -1.6442761256697506217216e-06}, // 1
                {+3.8855076805286621093750e+10, -2.7172921628903544035295e-06}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 10
                {+4.5000000000000000000000e+01, +0.0000000000000000000000e+00}, // 9
                {+8.7000000000000000000000e+02, +0.0000000000000000000000e+00}, // 8
                {+9.4500000000000000000000e+03, +0.0000000000000000000000e+00}, // 7
                {+6.3273000000000000000000e+04, +0.0000000000000000000000e+00}, // 6
                {+2.6932500000000000000000e+05, +0.0000000000000000000000e+00}, // 5
                {+7.2368000000000000000000e+05, +0.0000000000000000000000e+00}, // 4
                {+1.1727000000000000000000e+06, +0.0000000000000000000000e+00}, // 3
                {+1.0265760000000000000000e+06, +0.0000000000000000000000e+00}, // 2
                {+3.6288000000000000000000e+05, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };
            static constexpr
            const d_real<double> ped[]={
                {+4.5812205752064319886230e-05, +1.0564479999999999999847e-21}, // 10
                {+4.7860596072798805220017e-03, +3.0699525000000000001306e-20}, // 9
                {+2.2500692262932167619915e-01, +8.1487113929999999999415e-18}, // 8
                {+6.2687122990234156461042e+00, +2.1528517438599999999516e-16}, // 7
                {+1.1461426650360344581259e+02, +3.5212217414830000000113e-15}, // 6
                {+1.4369805454347792874614e+03, +2.7663712860809999999870e-14}, // 5
                {+1.2511500081670890722307e+04, +5.6288996846778399999424e-13}, // 4
                {+7.4699889889147554640658e+04, -1.3919483467340759999526e-12}, // 3
                {+2.9269065354953682981431e+05, +2.8602525060603640000742e-12}, // 2
                {+6.7961518950445647351444e+05, +1.9333034673525960000213e-12}, // 1
                {+7.1013192946532566566020e+05, -1.3530750527567787000055e-11}  // 0
            };
        };

        // lanczos table for float (f32)
        struct lanczos_table_g_4_35169_N5 {
            static constexpr
            double g() {
                return +4.3516943305730819702148e+00;
            }
            static constexpr
            double g_l() {
                return +2.9785156250000000000342e-17;
            }
            static constexpr
            double gm0_5() {
                return +3.8516943305730819702148e+00;
            }
            static constexpr
            double gm0_5_l() {
                return +2.9785156250000000000342e-17;
            }
            static constexpr
            double exp_minus_gm0_5_h() {
                return +2.1243712057565491968525e-02;
            }
            static constexpr
            double exp_minus_gm0_5_l() {
                return +1.1678894220000000000006e-18;
            }
            static constexpr
            const double p[]={
                +2.5066282851359193983853e+00, // 4
                +3.8669641557894443906207e+01, // 3
                +2.2368963390537291502369e+02, // 2
                +5.7504301631454700327595e+02, // 1
                +5.5430239062940745498054e+02  // 0
            };
            static constexpr
            const double q[]={
                +1.0000000000000000000000e+00, // 4
                +6.0000000000000000000000e+00, // 3
                +1.1000000000000000000000e+01, // 2
                +6.0000000000000000000000e+00, // 1
                +0.0000000000000000000000e+00  // 0
            };
            static constexpr
            const d_real<double> pd[]={
                {+2.5066282851359193983853e+00, -1.4386361349600000000127e-16}, // 4
                {+3.8669641557894443906207e+01, -3.1862923974699999999993e-15}, // 3
                {+2.2368963390537291502369e+02, +6.9682633233740000001718e-15}, // 2
                {+5.7504301631454700327595e+02, +5.4938602473891000001085e-14}, // 1
                {+5.5430239062940745498054e+02, -2.0356668284519000000637e-14}  // 0
            };
            static constexpr
            const d_real<double> qd[]={
                {+1.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 4
                {+6.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 3
                {+1.1000000000000000000000e+01, +0.0000000000000000000000e+00}, // 2
                {+6.0000000000000000000000e+00, +0.0000000000000000000000e+00}, // 1
                {+0.0000000000000000000000e+00, +0.0000000000000000000000e+00}  // 0
            };
            static constexpr
            const d_real<double> ped[]={
                {+3.2297811929219565063587e-02, +2.5523372809999999999165e-18}, // 4
                {+4.9825688867126349812509e-01, -1.7292132799000000000530e-17}, // 3
                {+2.8822325867913680674803e+00, -3.1763008602999999999492e-17}, // 2
                {+7.4094078097947013716862e+00, +2.9115928386500000000305e-16}, // 1
                {+7.1421656216947386752736e+00, +2.7467653356400000000558e-16}  // 0
            };

            static constexpr
            float gm0_5f() {
                return 3.8516943455e+00f;
            }
            static constexpr
            float gm0_5f_l() {
                return -1.4901161194e-08f;
            }
            static constexpr
            const d_real<float> pdf[]={
                { 2.5066282749e+00f, 1.0218316859e-08f },
                { 3.8669643402e+01f, -1.8442051442e-06f },
                { 2.2368963623e+02f, -2.3250959202e-06f },
                { 5.7504302979e+02f, -1.3470609701e-05f },
                { 5.5430236816e+02f, 2.2465344955e-05f }
            };
            static constexpr
            const d_real<float> pedf[]={
                { 3.2297812402e-02f, -4.7302883832e-10f },
                { 4.9825689197e-01f, -3.2946025907e-09f },
                { 2.8822326660e+00f, -7.9224257377e-08f },
                { 7.4094076157e+00f, 1.9413307939e-07f },
                { 7.1421656609e+00f, -3.9163417398e-08f }
            };
            static constexpr
            const float qf[]={
                1.0000000000e+00f,
                6.0000000000e+00f,
                1.1000000000e+01f,
                6.0000000000e+00f,
                0.0000000000e+00f
            };
        };
    }
}

template <typename _T, typename _C, std::size_t _N1, std::size_t _N2>
inline
__attribute__((__always_inline__))
cftal::d_real<_T>
cftal::math::
lanczos_rational_at(const _T& x,
                    const d_real<_C>(&p)[_N1],
                    const _C (&q)[_N2])
{
    using d_ops=d_real_ops<_T, d_real_traits<_T>::fma>;
    const d_real<_C>* pp=p;
    _T ph = pp[0][0];
    _T pl = pp[0][1];
#pragma clang unroll(1)
#pragma GCC unroll 1
    for (std::size_t i=1; i< _N1; ++i) {
#if 1
#if 1
        horner_comp_dpc_si(ph, pl, x, ph, pl, pp[i][0], pp[i][1]);
#else
        // compensated horner step with higher precision coefficients
        _T p_i, o_i;
        d_ops::mul12(ph, p_i, ph, x);
        d_ops::add12cond(ph, o_i, ph, pp[i][0]);
        pl = pl*x + (p_i + o_i + pp[i][1]);
#endif
#else
        d_ops::mul122(ph, pl, x, ph, pl);
        d_ops::add22cond(ph, pl,
                        pp[i][0], pp[i][1],
                        ph, pl);
#endif
    }
    _T qh, ql;
    if (__likely(q[_N2-1] == _C(0))) {
        const _C* pq=q;
        horner_comp_s0(qh, ql, x, pq[0], pq[1]);
#pragma clang unroll(1)
#pragma GCC unroll 1
        for (std::size_t i=2; i< _N2-1; ++i) {
            horner_comp_si(qh, ql, x, qh, ql, pq[i]);
        }
        // last step is without addition
        _T p_i;
        d_ops::mul12(qh, p_i, qh, x);
        ql = ql * x + p_i;
    } else {
        horner_comp(qh, ql, x, q);
    }
    _T pqh, pql;
#if 0
    _T inv_qh, inv_ql;
    d_ops::rcp2(inv_qh, inv_ql, qh, ql);
    d_ops::mul22(pqh, pql, ph, pl, inv_qh, inv_ql);
#else
    d_ops::div22(pqh, pql, ph, pl, qh, ql);
#endif
    return d_real<_T>(pqh, pql);
}

// calculation of a lanczos rational
template <typename _T, typename _C,
          std::size_t _N1, std::size_t _N2>
inline
__attribute__((__always_inline__))
_T
cftal::math::
lanczos_rational_at(const _T& x,
                    const _C(&p)[_N1],
                    const _C(&q)[_N2])
{
    _T rp=horner(x, p);
    _T rq=horner(x, q);
    _T r=rp/rq;
    return r;
}


// local variables:
// mode: c++
// end:
#endif
