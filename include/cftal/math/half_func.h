//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_HALF_FUNC_H__)
#define __CFTAL_MATH_HALF_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/math/elem_func_core_f32.h>

namespace cftal {
    namespace math {

        // template, may be we need a specialization for double
        // later
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct half_func {};

        // specialization for float
        template <typename _T>
        struct half_func<float, _T> : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using d_ops= typename base_type::d_ops;

            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using dvf_type = d_real<vf_type>;

            static
            vf_type
            __scale_exp_k(arg_t<vf_type> kf);

            static
            vf_type
            __half_exp_k(arg_t<vf_type> xrh,
                         arg_t<vf_type> kf);

            static
            vf_type
            half_exp_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp(arg_t<vf_type> x);

            static
            vf_type
            half_exp2_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp2(arg_t<vf_type> x);

            static
            vf_type
            half_exp10_k(arg_t<vf_type> x);

            static
            vf_type
            half_exp10(arg_t<vf_type> x);

            static
            vf_type
            half_log_k(arg_t<vf_type> x);

            static
            vf_type
            half_log(arg_t<vf_type> x);

            static
            vf_type
            half_log2(arg_t<vf_type> x);

            static
            vf_type
            half_log10(arg_t<vf_type> x);

            static
            vi_type
            __half_reduce_trig_arg(vf_type& xr, arg_t<vf_type> x);

            static
            void
            half_sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            static
            vf_type
            half_sin(arg_t<vf_type> x);

            static
            vf_type
            half_cos(arg_t<vf_type> x);

            static
            vf_type
            half_tan(arg_t<vf_type> x);

            static
            vf_type
            half_rsqrt(arg_t<vf_type> x);

            static
            vf_type
            half_sqrt(arg_t<vf_type> x);

        };

    }
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
__scale_exp_k(arg_t<vf_type> kf)
{
#if 1
    vi_type ki= _T::cvt_f_to_i(kf);
    vf_type rh= _T::insert_exp(_T::bias()+ki);
#else
    vf_type kt=max(vf_type(-64.0f), kf);
    kt= min(vf_type(64.0f), kt);
    vi_type ki= _T::cvt_f_to_i(kt);
    vf_type rh= _T::insert_exp(_T::bias()+ki);
#endif
    return rh;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
__half_exp_k(arg_t<vf_type> xrh,
             arg_t<vf_type> kf)
{
   // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-22.984375
    // coefficients for exp_f16 generated by sollya
    // x^0 : +0x8.00001p-3f
    const vf_type exp_f16_c0=+1.0000001192e+00f;
    // x^1 : +0xf.ffffcp-4f
    const vf_type exp_f16_c1=+9.9999976158e-01f;
    // x^2 : +0xf.ffe57p-5f
    const vf_type exp_f16_c2=+4.9998733401e-01f;
    // x^3 : +0xa.aac63p-6f
    const vf_type exp_f16_c3=+1.6667322814e-01f;
    // x^4 : +0xa.bbadap-8f
    const vf_type exp_f16_c4=+4.1926242411e-02f;
    // x^5 : +0x8.83bb8p-10f
    const vf_type exp_f16_c5=+8.3150193095e-03f;
#if 1
    vf_type xrh2=xrh*xrh;
    vf_type e=horner(xrh2,
                     exp_f16_c5,
                     exp_f16_c3,
                     exp_f16_c1);
    vf_type o=horner(xrh2,
                     exp_f16_c4,
                     exp_f16_c2,
                     exp_f16_c0);
    vf_type y=horner(xrh, e, o);
#else
    vf_type y= fast_poly(xrh,
                         exp_f16_c5,
                         exp_f16_c4,
                         exp_f16_c3,
                         exp_f16_c2,
                         exp_f16_c1,
                         exp_f16_c0);
#endif
    // vf_type ee=_T::insert_exp(k + _T::bias());
    // y *= ee;
    // y=base_type::__scale_exp_k(y, kf);
    y*= __scale_exp_k(kf);
    return y;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_exp_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xc * ctbl::m_1_ln2[0]));
    vf_type xrh = (xc - kf*ctbl::m_ln2_cw[0]) -
        kf*ctbl::m_ln2_cw[1];
    auto y= __half_exp_k(xrh, kf);
    return y;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_exp(arg_t<vf_type> d)
{
    vf_type res=half_exp_k(d);
    using fc= func_constants<float>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_exp2_k(arg_t<vf_type> xc)
{
    vf_type kf = rint(xc);
    vf_type xrh = xc - kf;
#if 1
   // [-0.5, 0.5] : | p - f | <= 2^-22.9921875
    // coefficients for exp2_f16 generated by sollya
    // x^0 : +0x8.00001p-3f
    const float exp2_f16_c0=+1.0000001192e+00f;
    // x^1 : +0xb.17216p-4f
    const float exp2_f16_c1=+6.9314706326e-01f;
    // x^2 : +0xf.5fc57p-6f
    const float exp2_f16_c2=+2.4022041261e-01f;
    // x^3 : +0xe.359ecp-8f
    const float exp2_f16_c3=+5.5505678058e-02f;
    // x^4 : +0x9.e90d9p-10f
    const float exp2_f16_c4=+9.6780890599e-03f;
    // x^5 : +0xa.e9cdp-13f
    const float exp2_f16_c5=+1.3321880251e-03f;
    vf_type xrh2=xrh*xrh;
    vf_type e=horner(xrh2,
                     exp2_f16_c5,
                     exp2_f16_c3,
                     exp2_f16_c1);
    vf_type o=horner(xrh2,
                     exp2_f16_c4,
                     exp2_f16_c2,
                     exp2_f16_c0);
    vf_type y=horner(xrh, e, o);
    y*= __scale_exp_k(kf);
    return y;
#else
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    auto y= __half_exp_k(xrh*ctbl::m_ln2[0], kf);
    return y;
#endif
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_exp2(arg_t<vf_type> d)
{
    vf_type res=half_exp2_k(d);
    using fc= func_constants<float>;
    const vf_type exp2_hi_inf= fc::exp2_hi_inf();
    const vf_type exp2_lo_zero= fc::exp2_lo_zero();
    res = _T::sel(d <= exp2_lo_zero, 0.0, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_exp10_k(arg_t<vf_type> xc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(xc * ctbl::m_1_lg2[0]));
    vf_type xrh = (xc - kf*ctbl::m_lg2_cw[0]) -
        (kf*ctbl::m_lg2_cw[1]);
    auto y= __half_exp_k(xrh*ctbl::m_ln10[0], kf);
    return y;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_exp10(arg_t<vf_type> d)
{
    vf_type res=half_exp10_k(d);
    using fc= func_constants<float>;
    const vf_type exp10_hi_inf= fc::exp10_hi_inf();
    const vf_type exp10_lo_zero= fc::exp10_lo_zero();
    res = _T::sel(d <= exp10_lo_zero, 0.0, res);
    res = _T::sel(d >= exp10_hi_inf, _T::pinf(), res);
    return res;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::half_log_k(arg_t<vf_type> xc)
{
    // one could remove the denormal handling here
    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel(_T::vmf_to_vmi(is_denom), vi_type(-25), vi_type(0));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3f800000 - 0x3f3504f3;;
    k += (hx>>23) - _T::bias();
    hx = (hx&0x007fffff) + 0x3f3504f3;
    vf_type xr = _T::as_float(hx);
    vf_type kf = _T::cvt_i_to_f(k);

    // brute force:
    vf_type ym= xr-1.0f;
    vf_type yp= xr+1.0f;
    vf_type s= native_div(ym, yp);
    // vf_type s= ym/yp;
    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-24.53125
    // coefficients for log_f16 generated by sollya
    // x^1 : +0x8.00001p-2f
    const vf_type log_f16_c1=+2.0000002384e+00f;
    // x^3 : +0xa.aa131p-4f
    const vf_type log_f16_c3=+6.6652208567e-01f;
    // x^5 : +0xd.37089p-5f
    const vf_type log_f16_c5=+4.1296795011e-01f;
    vf_type s2=s*s;
    vf_type y = horner(s2,
                       log_f16_c5,
                       log_f16_c3,
                       log_f16_c1)*s;
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type log_x = kf * ctbl::m_ln2[0] + y;
    return log_x;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_log(arg_t<vf_type> d)
{
    vf_type x = half_log_k(d);
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_log2(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type x = half_log_k(d)*ctbl::m_1_ln2[0];
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_log10(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type l=half_log_k(d);
    vf_type x=l * ctbl::m_1_ln10[0];
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _T>
inline
typename cftal::math::half_func<float, _T>::vi_type
cftal::math::half_func<float, _T>::
__half_reduce_trig_arg(vf_type& xrh, arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type fn= rint(vf_type(x*ctbl::m_2_pi[0]));
#if 0
    const float m_pi_2_h=+1.5707963705063e+00f;
    const float m_pi_2_m=-4.3711388286738e-08f;
    const float m_pi_2_l=-1.7151245100059e-15f;
    vf_type f0, f1, f2, f3, f4;
    d_ops::mul12(f0, f1, fn, -m_pi_2_h);
    d_ops::mul12(f2, f3, fn, -m_pi_2_m);
    f4 = fn * -m_pi_2_l;
    // d_ops::mul12(f4, f5, fn, -m_pi_2_l);
    // normalize f0 - f4 into p0..p2
    vf_type p0, p1, p2, t;
    p0 = f0;
    d_ops::add12(p1, t, f1, f2);
    p2 = f4 + t + f3;
    d_ops::add12(p0, p1, p0, p1);
    d_ops::add12(p1, p2, p1, p2);
    t = x + p0;
    xrh = t + p1;
    // xrl = p1 - (xrh - t) + p2;
#else
    // seven bit chunks of pi/2
    // x^ : +0xc.ap-3f
    const float pi_2_0=+1.5781250000e+00f;
    // x^ : -0xfp-11f
    const float pi_2_1=-7.3242187500e-03f;
    // x^ : -0x9.6p-21f
    const float pi_2_2=-4.4703483582e-06f;
    // x^ : +0x8.8p-29f
    const float pi_2_3=+1.5832483768e-08f;
    // x^ : +0x8.6p-37f
    const float pi_2_4=+6.0936145019e-11f;
    // and the remaining bits
    // x^ : -0xb.9ee5ap-46f
    const float pi_2_5=-1.6513995575e-13f;
    xrh = x + fn * -pi_2_0;
    xrh = xrh + fn * -pi_2_1;
    xrh = xrh + fn * -pi_2_2;
    xrh = xrh + fn * -pi_2_3;
    xrh = xrh + fn * -pi_2_4;
    xrh = xrh + fn * -pi_2_5;
#endif
    vi_type q=_T::cvt_f_to_i(fn);
    return q;
}

template <typename _T>
inline
void
cftal::math::half_func<float, _T>::
half_sin_cos_k(arg_t<vf_type> x, vf_type* ps, vf_type* pc)
{
    vf_type xr;
    auto q= __half_reduce_trig_arg(xr, x);

    vf_type xr2= xr*xr;
    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // [0, 0.785398185253143310546875] : | p - f | <= 2^-33.09375
    // coefficients for cos_f16 generated by sollya
    // x^0 : +0x8p-3f
    const vf_type cos_f16_c0=+1.0000000000e+00f;
    // x^2 : -0x8p-4f
    const vf_type cos_f16_c2=-5.0000000000e-01f;
    // x^4 : +0xa.aaaa5p-8f
    const vf_type cos_f16_c4=+4.1666645557e-02f;
    // x^6 : -0xb.60615p-13f
    const vf_type cos_f16_c6=-1.3887310633e-03f;
    // x^8 : +0xc.cf48ap-19f
    const vf_type cos_f16_c8=+2.4432567443e-05f;
    vf_type c= horner(xr2,
                      cos_f16_c8,
                      cos_f16_c6,
                      cos_f16_c4,
                      cos_f16_c2,
                      cos_f16_c0);
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-33.890625
    // coefficients for sin_f16 generated by sollya
    // x^1 : +0x8p-3f
    const vf_type sin_f16_c1=+1.0000000000e+00f;
    // x^3 : -0xa.aaaabp-6f
    const vf_type sin_f16_c3=-1.6666667163e-01f;
    // x^5 : +0x8.888b2p-10f
    const vf_type sin_f16_c5=+8.3333719522e-03f;
    // x^7 : -0xd.02433p-16f
    const vf_type sin_f16_c7=-1.9849911041e-04f;
    // x^9 : +0xb.bf108p-22f
    const vf_type sin_f16_c9=+2.8005470085e-06f;
    vf_type s= horner(xr2,
                      sin_f16_c9,
                      sin_f16_c7,
                      sin_f16_c5,
                      sin_f16_c3,
                      sin_f16_c1)*xr;
    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        // vf_type fs = _T::sel(q_and_2_f, vf_type(-1.0), vf_type(1.0));
        // rs *= fs;
        *ps = _T::sel(q_and_2_f, -rs, rs);
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        // vf_type fc =  _T::sel(mt, vf_type(-1.0), vf_type(1.0));
        // rc *= fc;
        *pc= _T::sel(mt, -rc, rc);
    }
}


template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_sin(arg_t<vf_type> d)
{
    vf_type s;
    half_sin_cos_k(d, &s, nullptr);
    return s;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_cos(arg_t<vf_type> d)
{
    vf_type c;
    half_sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_tan(arg_t<vf_type> x)
{
    vf_type xr;
    auto q= __half_reduce_trig_arg(xr, x);
    // [0, 0.785398185253143310546875] : | p - f | <= 2^-29.546875
    // coefficients for tan_16 generated by sollya
    // x^1 : +0x8p-3f
    const float tan_f16_c1=+1.0000000000e+00f;
    // x^3 : +0xa.aaabp-5f
    const float tan_f16_c3=+3.3333349228e-01f;
    // x^5 : +0x8.886dp-6f
    const float tan_f16_c5=+1.3332676888e-01f;
    // x^7 : +0xd.d6c9cp-8f
    const float tan_f16_c7=+5.4058656096e-02f;
    // x^9 : +0xa.e63c5p-9f
    const float tan_f16_c9=+2.1287808195e-02f;
    // x^11 : +0xb.15241p-10f
    const float tan_f16_c11=+1.0822833516e-02f;
    // x^13 : +0xd.b2701p-17f
    const float tan_f16_c13=+1.0449998808e-04f;
    // x^15 : +0x8.f2db7p-11f
    const float tan_f16_c15=+4.3694633059e-03f;
    vf_type x2=xr*xr;
#if 1
    vf_type x4=x2*x2;
    vf_type e=horner(x4,
                     tan_f16_c15,
                     tan_f16_c11,
                     tan_f16_c7,
                     tan_f16_c3);
    vf_type o=horner(x4,
                     tan_f16_c13,
                     tan_f16_c9,
                     tan_f16_c5,
                     tan_f16_c1);
    vf_type t=horner(x2, e, o)*xr;
#else
    vf_type t= xr*horner(x2,
                         tan_f16_c15,
                         tan_f16_c13,
                         tan_f16_c11,
                         tan_f16_c9,
                         tan_f16_c7,
                         tan_f16_c5,
                         tan_f16_c3,
                         tan_f16_c1);
#endif
    vmi_type qm1= vi_type(q & vi_type(1)) == vi_type(1);
    vmf_type fqm1= _T::vmi_to_vmf(qm1);

    vf_type ct=native_recip(t);
    t = _T::sel(fqm1, -ct, t);
    return t;
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_rsqrt(arg_t<vf_type> x)
{
#if 1
    vf_type y=native_rsqrt(x);
    // ensure higher precision at the cost of one operation
    y = y + (0.5f*y) * (1.0f- y*(x * y));
    // y= 0.5f*y *(3.0f - y*(y*x));
    return y;
#else
    vi_type yi = _T::as_int(x);
    yi = ((0xbe6eb50c - yi) >> 1) & 0x7fffffff;
    vf_type y= _T::as_float(yi);
#if 1
    vf_type xh=0.5f *x;
    y= y *(1.5f - y*(y*xh));
    y= y *(1.5f - y*(y*xh));
    y = y + (0.5f*y) * (1.0f- y*(x * y));
    return y;
#else
    vf_type xh= 0.5f *x;
    y= y *(1.5f - y*y*xh);
    y= y *(1.5f - y*y*xh);
    y= y *(1.5f - y*y*xh);
    // y= 0.5f * y *(3.0f - y*y*x);
    // y= y + 0.5f * y * (1.0f - yi*y*x);
    yi= _T::sel(x<0, _T::nan(), y);
    yi= _T::sel(x!=x, x, y);
    return yi;
#endif
#endif
}

template <typename _T>
typename cftal::math::half_func<float, _T>::vf_type
cftal::math::half_func<float, _T>::
half_sqrt(arg_t<vf_type> x)
{
    // return x*native_rsqrt(x);
    return sqrt(x);
}

// local variables:
// mode: c++
// end:
#endif
