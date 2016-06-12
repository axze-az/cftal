#if !defined (__MATH_FUNC_F32_H__)
#define __MATH_FUNC_F32_H__ 1

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
#include <cftal/std_types.h>
#include <cftal/math_common.h>
#include <cftal/math_impl_d_real_constants_f32.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {
    namespace math {

        namespace impl {

        }

        template <>
        struct func_traits<float, int32_t>
            : public d_real_traits<float> {
            typedef float vf_type;
            typedef int32_t vi_type;
            typedef bool vmf_type;
            typedef bool vmi_type;
            typedef uint32_t mask_type;
            typedef union {
                float _d;
                uint32_t _u;
            } ud_t;

            static constexpr int32_t bias = 127;
            static constexpr int32_t e_max= 127;
            static constexpr int32_t e_min= -126;
            static constexpr int32_t e_mask= 0xff;
            static constexpr int32_t bits=23;
            static constexpr int32_t vec_len=1;

            static constexpr float pinf() {
                return std::numeric_limits<float>::infinity();
            }
            static constexpr float ninf() {
                return -std::numeric_limits<float>::infinity();
            }
            static constexpr float nan() {
                return std::numeric_limits<float>::quiet_NaN();
            }
            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return mi;
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return mf;
            }
            static
            vi_type sel(const vmi_type& msk,
                        const vi_type& t, const vi_type& f) {
                return msk ? t : f;
            }
            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return msk ? t : f;
            }
            static
            vf_type insert_exp(const vi_type& e) {
                ud_t t;
                t._u = uint32_t(e) << bits;
                return t._d;
            }
            static
            vi_type extract_exp(const vf_type& d) {
                ud_t t;
                t._d = d;
                return (t._u >> bits) & e_mask;
            }
            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return vf_type(i);
            }
            // including rounding to nearest.
            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return f < 0 ?
                           (vi_type)(f - 0.5) :
                    (vi_type)(f + 0.5);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return (vi_type)f;
            }

            static
            vi_type as_int(const vf_type& f) {
                ud_t t;
                t._d = f;
                return t._u;
            }

            static
            vf_type as_float(const vi_type& i) {
                ud_t t;
                t._u = i;
                return t._d;
            }
        };

        template <typename _T>
        struct func_core<float, _T> {

            typedef func_core<float, _T> my_type;

            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            typedef d_real<vf_type> dvf_type;
            using tvf_type = t_real<vf_type>;

            static
            vf_type
            pow2i(arg_t<vi_type> d);

            static
            vf_type
            frexp(arg_t<vf_type> vf, vi_type* vi);

            static
            vf_type
            ldexp(arg_t<vf_type> vf, arg_t<vi_type> vi);

            static
            vi_type
            ilogbp1(arg_t<vf_type> x);

            static
            vi_type
            ilogb(arg_t<vf_type> vf);

            static
            vf_type
            scale_exp_k(arg_t<vf_type> y, arg_t<vf_type> kf,
                        arg_t<vi_type> k);

            static
            vf_type
            exp_k(arg_t<vf_type> x, bool exp_m1);

            static
            vf_type
            exp2_k(arg_t<vf_type> x);

            static
            vf_type
            exp10_k(arg_t<vf_type> x);

            static
            vf_type
            sinh_k(arg_t<vf_type> x);

            static
            vf_type
            tanh_k(arg_t<vf_type> x);

            static
            vf_type
            cosh_k(arg_t<vf_type> x);

            // polynomial approximation of log(1+f) with
            // s = f/(2.0+f) and z = s*s;
            static
            vf_type
            log_k_poly(arg_t<vf_type> z);

            enum log_func {
                c_log_e,
                c_log_2,
                c_log_10
            };

            static
            vf_type
            log_k(arg_t<vf_type> x, log_func f=log_func::c_log_e);

            static
            vf_type
            log1p_k(arg_t<vf_type> x);

            static
            vf_type
            log2_k(arg_t<vf_type> x);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static
            std::pair<dvf_type, vi_type>
            reduce_trig_arg_k(arg_t<vf_type> x);

            // calculates sin(xh, xl) in [+0, pi/4]
            static
            vf_type
            __sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates cos(xh, xl) in [+0, pi/4]
            static
            vf_type
            __cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl);

            // calculates tan(xh, xl) in [+0, pi/4] and
            // returns tan or -1/tan if q & 1
            static
            vf_type
            __tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl,
                    arg_t<vi_type> q);

            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            // core tan calculation
            static
            vf_type
            tan_k(arg_t<vf_type> x);

            static
            vf_type
            atan_k(arg_t<vf_type> x);

            static
            vf_type
            atan2_k(arg_t<vf_type> y, arg_t<vf_type> x);

            static
            vf_type
            asin_k_poly(arg_t<vf_type> z2);

            static
            vf_type
            asin_k(arg_t<vf_type> x);

            static
            vf_type
            acos_k(arg_t<vf_type> x);

            static
            vf_type
            asinh_k(arg_t<vf_type> x);

            static
            vf_type
            acosh_k(arg_t<vf_type> x);

            static
            vf_type
            atanh_k(arg_t<vf_type> x);

            static
            vf_type
            erf_k(arg_t<vf_type> x);

            static
            vf_type
            cbrt_k(arg_t<vf_type> x);
        };

        template <typename _T>
        struct func<float, _T>
            : public func_common<float, _T> {
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
#if 0
            static vf_type native_sin(arg_t<vf_type> x);
            static vf_type native_cos(arg_t<vf_type> x);
#endif
        };
    }
}

template <typename _T>
inline
typename
cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
pow2i(arg_t<vi_type> vi)
{
    vi_type e(vi + vi_type(_T::bias));
    vf_type r(_T::insert_exp(e));
    vmi_type mi;
    vmf_type mf;
    mi= (vi < vi_type(_T::e_min));
    mf= _T::vmi_to_vmf(mi);
    r= _T::sel(mf, vf_type(0.0), r);
    mi= (vi > vi_type(_T::e_max));
    mf= _T::vmi_to_vmf(mi);
    vf_type inf(_T::pinf());
    r= _T::sel(mf, vf_type(inf), r);
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    vf_type xs=x;
    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;

    vi_type eo=vi_type(0);
    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p24f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-24), eo);
    // mantissa
    vi_type m=_T::as_int(xs);
    vi_type xe=((m>>23) & 0xff) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi_type nn= min(vi_type(4096), max(n, vi_type(-4096)));
    vi_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0xff normal result
    //     re >= 0xff inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

    // clear exponent bits from m
    m &= vi_type(~0x7f800000);

    // mantissa for normal results:
    vi_type mn= m | ((re & vi_type(0xff)) << 23);
    vf_type r= _T::as_float(mn);

    // overflow handling
    vmi_type i_is_inf = re > vi_type(0xfe);
    vmf_type f_is_inf = _T::vmi_to_vmf(i_is_inf);
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi_type i_is_near_z = re < vi_type (1);
    if (any_of(i_is_near_z)) {
        // create m*0x1.0p-126
        vi_type mu= m | vi_type(1<<23);
        vf_type r_u= _T::as_float(mu);
        // create a scaling factor
        vi_type ue= max(vi_type(re + (_T::bias-1)), vi_type(1));
        vf_type s_u= _T::as_float(vi_type(ue << 23));
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi_to_vmf(i_is_near_z);
        r = _T::sel(f_is_near_z, r_u, r);
    }
    // handle special cases:
    r = _T::sel(isinf(x) | isnan(x) | (x==vf_type(0.0)),
                x, r);
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vf_type xs=x;

    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;

    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p24f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-24), eo);

    // reinterpret a integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) & 0xff) + eo;

    // insert exponent
    i = (i & vi_type(0x807fffff)) | vi_type(0x7e<<23);
    // interpret as float
    vf_type frc(_T::as_float(i));
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    frc = _T::sel(f_inz, x, frc);
    if (ve != nullptr) {
        vmi_type i_inz=_T::vmf_to_vmi(f_inz);
        e -= vi_type(_T::bias-1);
        e= _T::sel(i_inz, vi_type(0), e);
        *ve= e;
    }
    return frc;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vi_type
cftal::math::func_core<float, _T>::
ilogbp1(arg_t<vf_type> x)
{
#if 1
    vf_type xs=x;
    using fc=func_constants<float>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p24f), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-24), eo);
    // reinterpret as integer
    vi_type i=_T::as_int(xs);
    // exponent:
    vi_type e=((i >> 23) & 0xff) + eo - vi_type(_T::bias-1);
    return e;
#else
    vmf_type mf= vd < 5.421010862427522E-20f;
    vf_type d = _T::sel(mf, 1.8446744073709552E19f * x, x);
    vi_type q = _T::extract_exp(d);
    vmi_type mi= _T::vmf_to_vmi(mf);
    vi_type qs = _T::sel(mi, vi_type(64 + 0x7e), vi_type(0x7e));
    return q - qs;
#endif
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vi_type
cftal::math::func_core<float, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(ilogbp1(abs(d)) -1);
    vmf_type mf= d == 0.0f;
    vmi_type mi= _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(FP_ILOGB0), e);
    mf = isinf(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(0x7fffffff), e);
    mf = isnan(d);
    mi = _T::vmf_to_vmi(mf);
    e = _T::sel(mi, vi_type(FP_ILOGBNAN), e);
    return e;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
scale_exp_k(arg_t<vf_type> ym, arg_t<vf_type> kf, arg_t<vi_type> k)
{
    vi_type e_two_pow_k=_T::sel(k < vi_type(-125),
                                vi_type((_T::bias+100)+k),
                                vi_type(_T::bias+k));
    vf_type two_pow_k= _T::insert_exp(e_two_pow_k);
    // kf == 128f or kf>=-125
    vf_type yt= _T::sel(kf == vf_type(128),
                        ym * 2.0f * 0x1p127f,
                        ym*two_pow_k);
    vf_type y = _T::sel(kf < vf_type(-125),
                        ym*two_pow_k*0x1p-100f, yt);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
exp_k(arg_t<vf_type> xc, bool exp_m1)
{
    // see math_func_f64.h for comments about the code
    using ctbl = impl::d_real_constants<d_real<float>, float>;

    vf_type x=xc;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ln2.h()));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);
    vf_type y;
    if (exp_m1 == false) {
#if 1
        // exp(x) = 1 + 2x/(2-x+x^2*P(x^2)
        //                    x [x - x^2 * P]
        //        = 1 + x + ------------------
        //                    2 - [x - x^2 * P]
        // coefficients for expn generated by sollya
        // x^0
        const vf_type expn_c0=0x1.555556p-3f;
        // x^2
        const vf_type expn_c2=-0x1.6c1bf4p-9f;
        // x^4
        const vf_type expn_c4=0x1.18daccp-14f;
        vf_type xx= xr*xr;
        vf_type P= impl::poly(xx,
                              expn_c4,
                              expn_c2,
                              expn_c0);
        vf_type br= xr- xx*P;
        vf_type cr = (hi-xr)-lo;
        y = cr*xr;
        y += cr;
        y += (xr*br)/(2.0f-br);
        y += xr;
        y += 1.0f;
        y = scale_exp_k(y, kf, k);
#else
        // coefficients for exp generated by sollya
        // x^4
        const vf_type exp_c4=-0x1.6aa3e8p-9f;  // 0xbf66aa3e80000000
        // x^2
        const vf_type exp_c2=0x1.55551ep-3f;  // 0x3fc55551e0000000
        vf_type xx = xr*xr;
        vf_type c = xr - xx*impl::poly(xx,
                                       exp_c4,
                                       exp_c2);
        y = (xr*c/(2.0f-c) - lo + hi);
        y += 1.0f;
        // y = ldexp(y, k);
        y= scale_exp_k(y, kf, k);
#endif
    } else {
        vf_type cr = (hi-xr)-lo;
        // coefficients for expm1 generated by sollya
        // x^4
        const vf_type expm1_c4=0x1.9e6026p-10f; // 0x3f59e60260000000
        // x^2
        const vf_type expm1_c2=-0x1.1110dp-5f; // 0xbfa1110d00000000
        vf_type hfx = 0.5f*xr;
        vf_type hxs = xr*hfx;
        vf_type r1 = 1.0f+hxs*impl::poly(hxs,
                                        expm1_c4,
                                        expm1_c2);
        vf_type tt  = 3.0f-r1*hfx;
        vf_type e  = hxs*((r1-tt)/(6.0f - xr*tt));
        // if (k == 0)   /* c is 0 */
        //      return x - (x*e-hxs);
        e  = xr*(e-cr) - cr;
        e -= hxs;
        vi_type t= _T::bias - k;
        vf_type two_pow_minus_k=_T::insert_exp(t);
        // xr - e = y --> xr -y = e
        t = _T::bias + k;
        vf_type two_pow_k=_T::insert_exp(t);
        // default cases:
        vf_type ym = _T::sel(kf < vf_type(20),
                             (xr - e + (1.0f - two_pow_minus_k))*two_pow_k,
                             (xr - (e+two_pow_minus_k)+1.0f)*two_pow_k);
        // k < 0 || k > 56
        vf_type yt= xr - e  + 1.0f;
        yt= _T::sel(kf == vf_type(128),
                    yt * 2.0 *0x1p127f,
                    yt * two_pow_k);
        yt -= 1.0f;
        ym = _T::sel((kf < vf_type(0)) | (kf>vf_type(56)), yt, ym);
        // k == 1
        yt = _T::sel(xr < -0.25f, -2.0f*(e-(xr+0.5f)),1.0f+2.0f*(xr-e));
        ym = _T::sel(kf == vf_type(1.0f), yt, ym);
        // k == -1
        yt = 0.5f *(xr-e) - 0.5f;
        ym = _T::sel(kf == vf_type(-1.0f), yt, ym);
        // k == 0
        ym = _T::sel(kf == vf_type(0.0), xr-e, ym);
        // x small
        // ym = _T::sel(abs(x) < 0x1p-54, x, ym);
        y = ym;
    }
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
exp2_k(arg_t<vf_type> x)
{
    vf_type kf= rint(vf_type(x));
    vf_type xr = x - kf;
    vi_type k = _T::cvt_f_to_i(kf);
    // coefficients for exp2 generated by sollya
    // x^5
    const vf_type exp2_c5=0x1.427918p-13f;  // 0x3f24279180000000
    // x^4
    const vf_type exp2_c4=0x1.5ef4a2p-10f;  // 0x3f55ef4a20000000
    // x^3
    const vf_type exp2_c3=0x1.3b2c58p-7f;  // 0x3f83b2c580000000
    // x^2
    const vf_type exp2_c2=0x1.c6af9ep-5f;  // 0x3fac6af9e0000000
    // x^1
    const vf_type exp2_c1=0x1.ebfbdep-3f;  // 0x3fcebfbde0000000
    // x^0
    const vf_type exp2_c0=0x1.62e43p-1f;  // 0x3fe62e4300000000
    vf_type y=impl::poly(xr,
                         exp2_c5,
                         exp2_c4,
                         exp2_c3,
                         exp2_c2,
                         exp2_c1,
                         exp2_c0);
#if 1
    // EFT of the last multiplication and addition
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    vf_type ye;
    vf_type p_i;
    vf_type o_i;
    y = d_ops::two_prod(y, xr, p_i);
    y = d_ops::two_sum(y, 1.0, o_i);
    ye= (p_i + o_i);
    y += ye;
#else
    y *= xr;
    y += 1.0;
#endif
    y= scale_exp_k(y, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
exp10_k(arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ld2.h()));
    vf_type hi = x - kf * ctbl::m_ld2_cw[0];
    vf_type lo = kf * ctbl::m_ld2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);
    // coefficients for exp10 generated by sollya
    // x^5
    const vf_type exp10_c5=0x1.a8649cp-3f;  // 0x3fca8649c0000000
    // x^4
    const vf_type exp10_c4=0x1.155f1p-1f;  // 0x3fe155f100000000
    // x^3
    const vf_type exp10_c3=0x1.2bd7cap0f;  // 0x3ff2bd7ca0000000
    // x^2
    const vf_type exp10_c2=0x1.046faap1f;  // 0x400046faa0000000
    // x^1
    const vf_type exp10_c1=0x1.53524cp1f;  // 0x40053524c0000000
    // x^0
    const vf_type exp10_c0=0x1.26bb1cp1f;  // 0x40026bb1c0000000
    vf_type y=impl::poly(xr,
                         exp10_c5,
                         exp10_c4,
                         exp10_c3,
                         exp10_c2,
                         exp10_c1,
                         exp10_c0);
    y *= xr;
    // y += xrl + xr *xrl;
    y += 1.0;
    y= scale_exp_k(y, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
sinh_k(arg_t<vf_type> xc)
{
    // for huge arguments:
    // sinh(x) = sgn(x) [e^y + ((e^v)/2 -1)e^y - (e^-v)/2)e^-y]
    // y= |x| -v
    // ln(2) <= v <= ln(3) for base 2
    // ln(2) <= v <= ln(2.125) for other bases
    // (e^v)/2 - 1 < 1/ß
    // chosing v=0.75 (2 bits set)
    // between 1 and overflow of expm(1):
    // sinh (x) = 1/2 (exp(x) - exp(-x))
    //          = (expm1(x) + (expm1(x)/(expm1(x)+1))/2;
    vf_type x = abs(xc);
    using fc=func_constants<float>;
    vmf_type x_huge = x >= fc::exp_hi_inf;
    // between 0 and 1
    // sinh(x) = x + x^3/Q(x^2)
    // coefficients for sinh generated by sollya
    // x^6
    const vf_type sinh_c6=-0x1.1508b8p-13f;  // 0xb90a845c
    // x^4
    const vf_type sinh_c4=0x1.01687ap-7f;  // 0x3c00b43d
    // x^2
    const vf_type sinh_c2=-0x1.33332p-2f;  // 0xbe999990
    // x^0
    const vf_type sinh_c0=0x1.8p2f;  // 0x40c00000
    vf_type x2=x*x;
    vf_type q=impl::poly(x2,
                         sinh_c6,
                         sinh_c4,
                         sinh_c2,
                         sinh_c0);
    vf_type sinh_le_1 = x + (x*x2)/q;
    vf_type xr= _T::sel(x_huge, x - 0.75, x);
    vf_type em=exp_k(xr, true);
    vf_type e= em+1;
    const vf_type e_v_2_m_1 = +5.8500006794930e-02f;
    const vf_type e_m_v_2 = +2.3618327081203e-01f;
    vf_type sinh_gt_1 = 0.5 * (em + em/e);
    vf_type sinh_huge = e + e_v_2_m_1 * e - e_m_v_2 / e;
    vf_type sinh_x = _T::sel(x<=1.0, sinh_le_1, sinh_gt_1);
    sinh_x = _T::sel(x_huge, sinh_huge, sinh_x);
    vf_type y = copysign(sinh_x, xc);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
cosh_k(arg_t<vf_type> xc)
{
    // for really large arguments:
    // cosh(x) = sgn(x) [e^y + ((e^v)/2 -1)e^y + (e^-v)/2)e^-y]
    // y= |x| -v
    // ln(2) <= v <= ln(3) for base 2
    // ln(2) <= v <= ln(2.125) for other bases
    // (e^v)/2 - 1 < 1/ß
    // chosing v=0.75 (2 bits set)
    // between log(2) and overflow of expm(1):
    // cosh (x) = 1/2 (exp(x) + exp(-x))
    //          = 1 + (expm1(x)/(expm1(x)+1))/2;
    vf_type x=abs(xc);
    using fc=func_constants<float>;
    vmf_type x_huge = x >= fc::exp_hi_inf;
    /*
        cosh(x) = 1 + x^2/2 + x^4/24 ...
        cosh(x)-1) = x^2*R
        R= f(x^2)
        cosh(x)-1)/(x^2)= R
    */
    // coefficients for cosh generated by sollya
    // x^6
    const vf_type cosh_c6=0x1.a44a8cp-16f;  // 0x37d22546
    // x^4
    const vf_type cosh_c4=0x1.6c124p-10f;  // 0x3ab60920
    // x^2
    const vf_type cosh_c2=0x1.555558p-5f;  // 0x3d2aaaac
    // x^0
    const vf_type cosh_c0=0x1p-1f;  // 0x3f000000
    vf_type xx= x*x;
    vf_type cosh_le_ln2 = 1.0 + xx*impl::poly(xx,
                                              cosh_c6,
                                              cosh_c4,
                                              cosh_c2,
                                              cosh_c0);
    vf_type xr= _T::sel(x_huge, x - 0.75, x);
    vf_type em=exp_k(xr, true);
    vf_type e=em+1;
    const vf_type e_v_2_m_1 = +5.8500006794930e-02f;
    const vf_type e_m_v_2 = +2.3618327081203e-01f;
    vf_type cosh_gt_ln2 = 0.5 * (e + 1/e);
    vf_type cosh_huge = e + (e_v_2_m_1 * e - e_m_v_2 / e);
    vf_type cosh_x = _T::sel(x <= M_LN2, cosh_le_ln2, cosh_gt_ln2);
    cosh_x = _T::sel(x_huge, cosh_huge, cosh_x);
    return cosh_x;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
tanh_k(arg_t<vf_type> xc)
{
    /* tanh(x) = (exp(x) - exp(-x))/(exp(x) + exp(-x))
     *         = (exp(2*x) - 1)/(exp(2*x) - 1 + 2)
     *         = (1 - exp(-2*x))/(exp(-2*x) - 1 + 2)
     */
    vf_type x= abs(xc);
    // using fc=func_constants<double>;
    vmf_type x_gt_20 = x >= 20.0f;
    vf_type tanh_x_gt_20 = 1.0f;
    vf_type x2=2.0f*x;
    vf_type em1= exp_k(x2, true);
    vmf_type x_gt_ln_3_2= x > 5.493061443340549e-1f;
    vf_type tanh_x_gt_ln_3_2 = 1.0f - 2.0f/(em1+2);
    // tanh(x) = sgn(x) * x - x^3/(3+ x^2 R(x^2));
    // coefficients for tanh generated by sollya
    // x^6
    const vf_type tanh_c6=-0x1.d15302p-16f;  // 0xb7e8a981
    // x^4
    const vf_type tanh_c4=0x1.1307ecp-12f;  // 0x398983f6
    // x^2
    const vf_type tanh_c2=-0x1.7692f8p-8f;  // 0xbbbb497c
    // x^0
    const vf_type tanh_c0=0x1.333334p0f;  // 0x3f99999a
    vf_type xx= x*x;
    vf_type R= impl::poly(xx,
                          tanh_c6,
                          tanh_c4,
                          tanh_c2,
                          tanh_c0);
    vf_type tanh_x_small = x *( 1.0f - xx/(3.0f + xx * R));
    vf_type tanh_x = _T::sel(x_gt_ln_3_2, tanh_x_gt_ln_3_2, tanh_x_small);
    tanh_x = _T::sel(x_gt_20, tanh_x_gt_20, tanh_x);

    tanh_x= copysign(tanh_x, xc);
    return tanh_x;
}

template <typename _T>
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log_k_poly(arg_t<vf_type> z)
{
    // coefficients for log generated by sollya
    // x^8
    const vf_type log_c8=0x1.ec1e46p-3f;  // 0x3fcec1e460000000
    // x^6
    const vf_type log_c6=0x1.23f1ap-2f;  // 0x3fd23f1a00000000
    // x^4
    const vf_type log_c4=0x1.999bd4p-2f;  // 0x3fd999bd40000000
    // x^2
    const vf_type log_c2=0x1.555554p-1f;  // 0x3fe5555540000000
    vf_type y = z*impl::poly(z,
                             log_c8,
                             log_c6,
                             log_c4,
                             log_c2);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log_k(arg_t<vf_type> xc, log_func func)
{
    // const vf_type ln2_hi = 6.93147180369123816490e-01;  /* 3fe62e42 fee00000 */
    // const vf_type ln2_lo = 1.90821492927058770002e-10;  /* 3dea39ef 35793c76 */

    using fc = func_constants<float>;
    vmf_type is_denom=xc <= fc::max_denormal;
    vf_type x=_T::sel(is_denom, xc*0x1p25f, xc);
    vi_type k=_T::sel(_T::vmf_to_vmi(is_denom), vi_type(-25), vi_type(0));
    vi_type hx = _T::as_int(x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3f800000 - 0x3f3504f3;;
    k += (hx>>23) - _T::bias;
    hx = (hx&0x007fffff) + 0x3f3504f3;
    vf_type xr = _T::as_float(hx);

    vf_type f = xr - 1.0f;
    vf_type hfsq = 0.5f*f*f;
    vf_type s = f/(2.0f+f);
    vf_type z = s*s;

    // split of the polynomial reduces precision
    vf_type R = log_k_poly(z);
    vf_type res;
    vf_type kf = _T::cvt_i_to_f(k);
    if (func == log_func::c_log_e) {
        using ctbl=impl::d_real_constants<d_real<float>, float>;
        vf_type log_x=s*(hfsq+R) +
                    kf*ctbl::m_ln2_cw[1] - hfsq +
                    f + kf*ctbl::m_ln2_cw[0];
        res = log_x;
    } else if (func == log_func::c_log_10) {
        const vf_type ivln10hi  =  4.3432617188e-01f; /* 0x3ede6000 */
        const vf_type ivln10lo  = -3.1689971365e-05f; /* 0xb804ead9 */
        const vf_type log10_2hi =  3.0102920532e-01f; /* 0x3e9a2080 */
        const vf_type log10_2lo =  7.9034151668e-07f; /* 0x355427db */

        vf_type t = f - hfsq;
        vi_type it= _T::as_int(t);
        it &= vi_type(0xfffff000);
        vf_type hi= _T::as_float(it);
        vf_type lo= f - hi -hfsq + s * (hfsq + R);

        vf_type val_hi = hi * ivln10hi;
        vf_type y = kf* log10_2hi;
        vf_type val_lo = kf * log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;

        vf_type w= y + val_hi;
        val_lo += (y - w) + val_hi;
        val_hi = w;

        vf_type log10_x = val_lo + val_hi;
        res =log10_x;
    } else if (func == log_func::c_log_2) {
        const vf_type ivln2hi =  1.4428710938e+00f; /* 0x3fb8b000 */
        const vf_type ivln2lo = -1.7605285393e-04f; /* 0xb9389ad4 */

        vf_type t= f - hfsq;
        vi_type it= _T::as_int(t);
        it &= vi_type(0xfffff000);
        vf_type hi= _T::as_float(it);
        vf_type lo= f - hi - hfsq + s * (hfsq + R);
        vf_type val_hi = hi* ivln2hi;
        vf_type val_lo = (lo+hi)*ivln2lo + lo*ivln2hi;

        vf_type y= kf;
        vf_type w= y+ val_hi;
        val_lo += (y-w) + val_hi;
        val_hi = w;

        vf_type log2_x= val_lo + val_hi;
        res = log2_x;
    }
    return res;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log1p_k(arg_t<vf_type> xc)
{
/* float log1p(float x)
 * Return the natural logarithm of 1+x.
 *
 * Method :
 *   1. Argument Reduction: find k and f such that
 *                      1+x = 2^k * (1+f),
 *         where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *      Note. If k=0, then f=x is exact. However, if k!=0, then f
 *      may not be representable exactly. In that case, a correction
 *      term is need. Let u=1+x rounded. Let c = (1+x)-u, then
 *      log(1+x) - log(u) ~ c/u. Thus, we proceed to compute log(u),
 *      and add back the correction term c/u.
 *      (Note: when x > 2**53, one can simply return log(x))
 *
 *   2. Approximation of log(1+f): See log.c
 *
 *   3. Finally, log1p(x) = k*ln2 + log(1+f) + c/u. See log.c
 *
 * Special cases:
 *      log1p(x) is NaN with signal if x < -1 (including -INF) ;
 *      log1p(+INF) is +INF; log1p(-1) is -INF with signal;
 *      log1p(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *      according to an error analysis, the error is always less than
 *      1 ulp (unit in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 *
 * Note: Assuming log() return accurate answer, the following
 *       algorithm can be used to compute log1p(x) to within a few ULP:
 *
 *              u = 1+x;
 *              if(u==1.0) return x ; else
 *                         return log(u)*(x/(u-1.0));
 *
 *       See HP-15C Advanced Functions Handbook, p.193.
 */
    vf_type x=xc;
    vf_type u= 1+xc;
    vi_type hu=_T::as_int(u);
    hu += (0x3f800000 - 0x3f3504f3);
    vi_type k=(hu >> 23) - _T::bias;
    vf_type kf= _T::cvt_i_to_f(k);
    /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
    vf_type c_k_2 = _T::sel(kf >= vf_type(2.0f), 1.0f-(u-x), x-(u-1.0f));
    c_k_2 /= u;
    vf_type c = _T::sel(kf < vf_type(25.0f), c_k_2, vf_type(0));
    /* reduce u into [sqrt(2)/2, sqrt(2)] */
    hu = (hu&0x007fffff) + 0x3f3504f3;
    vf_type nu = _T::as_float(hu);
    vf_type f= nu -1.0f;

    vf_type hfsq = 0.5f*f*f;
    vf_type s = f/(2.0f+f);
    vf_type z = s*s;
    vf_type R = log_k_poly(z);

    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type log1p_x=s*(hfsq+R) +
                    (kf*ctbl::m_ln2_cw[1]+c) - hfsq +
                    f + kf*ctbl::m_ln2_cw[0];
    log1p_x= _T::sel(abs(x) < 0x1p-24, x, log1p_x);
    return log1p_x;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log2_k(arg_t<vf_type> xc)
{
/*
 * Return the base 2 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log2(x) = (f - f*f/2 + r)/log(2) + k
 */
    return log_k(xc, log_func::c_log_2);
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log10_k(arg_t<vf_type> xc)
{
/*
 * Return the base 10 logarithm of x.  See log.c for most comments.
 *
 * Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
 * as in log.c, then combine and scale in extra precision:
 *    log10(x) = (f - f*f/2 + r)/log(10) + k*log10(2)
 */
    return log_k(xc, log_func::c_log_10);
}

template <typename _T>
inline
std::pair<typename cftal::math::func_core<float, _T>::dvf_type,
          typename cftal::math::func_core<float, _T>::vi_type>
cftal::math::func_core<float, _T>::
reduce_trig_arg_k(arg_t<vf_type> x)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    vf_type y0, y1;
    vf_type fn= rint(vf_type(x* ctbl::m_2_pi.h()));
#if 0
    y0= d_ops::two_diff((x - fn* ctbl::m_pi_2_cw[0]) - fn*ctbl::m_pi_2_cw[1],
                        fn*ctbl::m_pi_2_cw[2],
                        y1);
    dvf_type d0(y0, y1);
#else
    y0= d_ops::two_diff(x, fn* ctbl::m_pi_2_cw[0], y1);
    dvf_type d0(y0, y1);
    d0= d_ops::sub(d0, fn*ctbl::m_pi_2_cw[1]);
    d0= d_ops::sub(d0, fn*ctbl::m_pi_2_cw[2]);
#endif
    vi_type q(_T::cvt_f_to_i(fn));

    const float large_arg=0x1p6f;
    vmf_type v_large_arg= vf_type(large_arg) < abs(x);
    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(float)) v_d {
            float _sc[N];
        } tf, d0_l, d0_h;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, x);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0.l());
        mem<vf_type>::store(d0_h._sc, d0.h());
        for (std::size_t i=0; i<N; ++i) {
            if (large_arg < std::fabs(tf._sc[i])) {
                float y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                d0_l._sc[i]= y[1];
                d0_h._sc[i]= y[0];
            }
        }
        vf_type rh(mem<vf_type>::load(d0_h._sc, N));
        vf_type rl(mem<vf_type>::load(d0_l._sc, N));
        d0 = dvf_type(rh, rl);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    return std::make_pair(d0, q);
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
__sin_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
/* __sin( x, y, iy)
 * kernel sin function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *      2. Callers must return sin(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization sin(x) ~ x for tiny x.
 *      3. sin(x) is approximated by a polynomial of degree 13 on
 *         [0,pi/4]
 *                               3            13
 *              sin(x) ~ x + S1*x + ... + S6*x
 *         where
 *
 *      |sin(x)         2     4     6     8     10     12  |     -58
 *      |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *      |  x                                               |
 *
 *      4. sin(x+y) = sin(x) + sin'(x')*y
 *                  ~ sin(x) + (1-x*x/2)*y
 *         For better accuracy, let
 *                   3      2      2      2      2
 *              r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *         then                   3    2
 *              sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */
    // coefficients for sin generated by sollya
    // x^8
    const vf_type sin_c8=0x1.77e21p-19f;  // 0x363bf108
    // x^6
    const vf_type sin_c6=-0x1.a04866p-13f;  // 0xb9502433
    // x^4
    const vf_type sin_c4=0x1.111164p-7f;  // 0x3c0888b2
    // x^2
    const vf_type sin_c2=-0x1.555556p-3f;  // 0xbe2aaaab
    vf_type z = xh*xh;
    // vf_type w = z*z;
    vf_type r = sin_c4 + z*(sin_c6 + z*sin_c8);
    vf_type v = z*xh;
    return xh - ((z*(0.5f*xl - v*r) - xl) - v*sin_c2);
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
__cos_k(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
/*
 * __cos( x,  y )
 * kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since cos(-x) = cos(x), we need only to consider positive x.
 *      2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *      3. cos(x) is approximated by a polynomial of degree 14 on
 *         [0,pi/4]
 *                                       4            14
 *              cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *         where the remez error is
 *
 *      |              2     4     6     8     10    12     14 |     -58
 *      |cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 *      |                                                      |
 *
 *                     4     6     8     10    12     14
 *      4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *             cos(x) ~ 1 - x*x/2 + r
 *         since cos(x+y) ~ cos(x) - sin(x)*y
 *                        ~ cos(x) - x*y,
 *         a correction term is necessary in cos(x) and hence
 *              cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *         For better accuracy, rearrange to
 *              cos(x+y) ~ w + (tmp + (r-x*y))
 *         where w = 1 - x*x/2 and tmp is a tiny correction term
 *         (1 - x*x/2 == w + tmp exactly in infinite precision).
 *         The exactness of w + tmp in infinite precision depends on w
 *         and tmp having the same precision as x.  If they have extra
 *         precision due to compiler bugs, then the extra precision is
 *         only good provided it is retained in all terms of the final
 *         expression for cos().  Retention happens in all cases tested
 *         under FreeBSD, so don't pessimize things by forcibly clipping
 *         any extra precision in w.
 */
    // coefficients for cos generated by sollya
    // x^10
    const vf_type cos_c10=-0x1.58f13p-22f;  // 0xb4ac7898
    // x^8
    const vf_type cos_c8=0x1.a0f5bp-16f;  // 0x37d07ad8
    // x^6
    const vf_type cos_c6=-0x1.6c17d4p-10f;  // 0xbab60bea
    // x^4
    const vf_type cos_c4=0x1.555556p-5f;  // 0x3d2aaaab
    vf_type z  = xh*xh;
    // vf_type w  = z*z;
    vf_type r  = z*(cos_c4+z*(cos_c6+z*(cos_c8+z*cos_c10)));
    vf_type hz = 0.5f*z;
    vf_type w  = 1.0f-hz;
    return w + (((1.0f-w)-hz) + (z*r-xh*xl));
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
__tan_k(arg_t<vf_type> xh, arg_t<vf_type> xl, arg_t<vi_type> q)
{
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* tan(x)
 * Return tangent function of x.
 *
 * kernel function:
 *      __tan           ... tangent function on [-pi/4,pi/4]
 *      __rem_pio2      ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *      [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *      in [-pi/4 , +pi/4], and let n = k mod 4.
 *      We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *          0          S           C             T
 *          1          C          -S            -1/T
 *          2         -S          -C             T
 *          3         -C           S            -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *      TRIG(x) returns trig(x) nearly rounded
 */
/* __tan( x, y, k )
 * kernel tan function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input odd indicates whether tan (if odd = 0) or -1/tan (if odd = 1) is returned.
 *
 * Algorithm
 *      1. Since tan(-x) = -tan(x), we need only to consider positive x.
 *      2. Callers must return tan(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization tan(x) ~ x for tiny x.
 *      3. tan(x) is approximated by a odd polynomial of degree 27 on
 *         [0,0.67434]
 *                               3             27
 *              tan(x) ~ x + T1*x + ... + T13*x
 *         where
 *
 *              |tan(x)         2     4            26   |     -59.2
 *              |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
 *              |  x                                    |
 *
 *         Note: tan(x+y) = tan(x) + tan'(x)*y
 *                        ~ tan(x) + (1+x*x)*y
 *         Therefore, for better accuracy in computing tan(x+y), let
 *                   3      2      2       2       2
 *              r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
 *         then
 *                                  3    2
 *              tan(x+y) = x + (T1*x + (x *(r+y)+y))
 *
 *      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
 *              tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
 *                     = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
 */
    // coefficients for tan generated by sollya
    // x^18
    const vf_type tan_c18=0x1.cfadf8p-9f;  // 0x3b67d6fc
    // x^16
    const vf_type tan_c16=-0x1.86fb12p-8f;  // 0xbbc37d89
    // x^14
    const vf_type tan_c14=0x1.d13dap-8f;  // 0x3be89ed0
    // x^12
    const vf_type tan_c12=0x1.e62de8p-11f;  // 0x3a7316f4
    // x^10
    const vf_type tan_c10=0x1.3ac8ecp-7f;  // 0x3c1d6476
    // x^8
    const vf_type tan_c8=0x1.6449aep-6f;  // 0x3cb224d7
    // x^6
    const vf_type tan_c6=0x1.ba341ep-5f;  // 0x3d5d1a0f
    // x^4
    const vf_type tan_c4=0x1.1110c6p-3f;  // 0x3e088863
    // x^2
    const vf_type tan_c2=0x1.555556p-2f;  // 0x3eaaaaab
    // make xrh positive
    vf_type sgn_x = copysign(vf_type(1.0f), xh);
    vmf_type x_is_neg = sgn_x < 0.0f;
    vf_type xrh = _T::sel(x_is_neg, -xh, xh);
    vf_type xrl = _T::sel(x_is_neg, -xl, xl);

    using ctbl = impl::d_real_constants<d_real<float>, float>;
    const vf_type large_arg=0.6731984257692414;
    vmf_type x_large= xrh > large_arg;
    // for xh in [6/7*pi/4, pi/4] we replace xh with pi/4 - xh
#if 1
    dvf_type dxrl= dvf_type(ctbl::m_pi_4) - dvf_type(xrh, xrl);
    xrh = _T::sel(x_large, dxrl.h(), xrh);
    xrl = _T::sel(x_large, dxrl.l(), xrl);
#else
    xrh = _T::sel(x_large,
                  (ctbl::m_pi_4.h() - xrh) + (ctbl::m_pi_4.l() - xrl) , xrh);
    xrl = _T::sel(x_large, 0, xrl);
#endif
    vf_type z = xrh*xrh;

    vf_type s= z * xrh;
    vf_type r = s* impl::poly(z,
                              tan_c18,
                              tan_c16,
                              tan_c14,
                              tan_c12,
                              tan_c10,
                              tan_c8,
                              tan_c6,
                              tan_c4);
    r = tan_c2*s + (z *(r+xrl)+ xrl);
    vf_type txy= xrh + r;

    // tan(x+y) = (tan x + tan y)/(1 - tan(x) * tan(y))
    // tan(x-y) = (tan x - tan y)/(1 + tan(x) * tan(y))
    // because xr = pi/4-x --> tan(pi/4) = 1
    // tan(pi/4-x) = (1- tan(x))/(1 + tan(x))
    //             = 1 - 2*(tan(x) - (tan(x)^2)/(1+tan(x)))
    vi_type q1= q & 1;
    vmi_type qm1= q1 == vi_type(1);
    vmf_type fqm1= _T::vmi_to_vmf(qm1);

    // calculate the values for x large including the sign
    s = _T::sel(fqm1, vf_type(-1.0f), vf_type(1.0f));
    vf_type txyl = s - 2.0f*(xrh + (r - (txy*txy)/(s +txy)));
    txyl *= sgn_x;

    // calculate -1/tan: -1/(xrh +r) has an error to up to 2 ulp
    // use multiprecision arithmetic and one newton raphson step
    vi_type ti=_T::as_int(txy);
    ti &= 0xfffff000;
    vf_type w0 = _T::as_float(ti);
    vf_type w1 = r - (w0 -xrh);
    vf_type a = -1.0f/txy;
    ti= _T::as_int(a);
    ti &= 0xfffff000;
    vf_type a0 = _T::as_float(ti);
    vf_type inv_txy= a0 + a *(1.0f + a0*w0 + a0*w1);
    inv_txy= _T::sel(x_is_neg, -inv_txy, inv_txy);

    // restore the sign
    txy = copysign(txy, sgn_x);

    vf_type tt= _T::sel(fqm1, inv_txy, txy);
    tt = _T::sel(x_large, txyl, tt);
    return tt;
}

template <typename _T>
__attribute__((flatten))
void
cftal::math::func_core<float, _T>::
sin_cos_k(arg_t<vf_type> xc, vf_type* ps, vf_type* pc)
{
    std::pair<dvf_type, vi_type> rq=reduce_trig_arg_k(xc);
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;

    vf_type s = __sin_k(x.h(), x.l());
    vf_type c = __cos_k(x.h(), x.l());

    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // swap sin/cos if q & 1
    vf_type rs(_T::sel(q_and_1_f, c, s));
    vf_type rc(_T::sel(q_and_1_f, s, c));
    // swap signs
    if (ps != nullptr) {
        vf_type fs = _T::sel(q_and_2_f, vf_type(-1.0), vf_type(1.0));
        rs *= fs;
        *ps = rs;
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        vf_type fc =  _T::sel(mt, vf_type(-1.0), vf_type(1.0));
        rc *= fc;
        *pc= rc;
    }
}

template <typename _T>
__attribute__((flatten))
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
tan_k(arg_t<vf_type> xc)
{
    std::pair<dvf_type, vi_type> rq=reduce_trig_arg_k(xc);
    const dvf_type& x= rq.first;
    const vi_type& q= rq.second;
    vf_type t = __tan_k(x.h(), x.l(), q);
    return t;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
atan_k(arg_t<vf_type> xc)
{
    const vf_type atan_0_5_hi=4.6364760399e-01; /* atan(0.5)hi 0x3eed6338 */
    const vf_type atan_0_5_lo=5.0121582440e-09; /* atan(0.5)lo 0x31ac3769 */
    const vf_type atan_1_0_hi=7.8539812565e-01; /* atan(1.0)hi 0x3f490fda */
    const vf_type atan_1_0_lo=3.7748947079e-08; /* atan(1.0)lo 0x33222168 */
    const vf_type atan_1_5_hi=9.8279368877e-01; /* atan(1.5)hi 0x3f7b985e */
    const vf_type atan_1_5_lo=3.4473217170e-08; /* atan(1.5)lo 0x33140fb4 */
    const vf_type atan_inf_hi=1.5707962513e+00; /* atan(inf)hi 0x3fc90fda */
    const vf_type atan_inf_lo=7.5497894159e-08; /* atan(inf)lo 0x33a22168 */

    vf_type x=abs(xc);
    // range reduction
    vmf_type r=x > 7.0/16;
    vf_type atan_hi= _T::sel(r, atan_0_5_hi, vf_type(0.0));
    vf_type atan_lo= _T::sel(r, atan_0_5_lo, vf_type(0.0));
    vf_type t=_T::sel(r, (2.0f*x-1.0f)/(2.0f+x), x);
    r = x>11.0f/16;
    atan_hi=_T::sel(r, atan_1_0_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_0_lo, atan_lo);
    t = _T::sel(r, (x-1.0f)/(1.0f+x), t);
    r = x>19.0f/16;
    atan_hi=_T::sel(r, atan_1_5_hi, atan_hi);
    atan_lo=_T::sel(r, atan_1_5_lo, atan_lo);
    t = _T::sel(r, (x-1.5f)/(1.0f+1.5f*x), t);
    r = x>39.0f/16;
    atan_hi=_T::sel(r, atan_inf_hi, atan_hi);
    atan_lo=_T::sel(r, atan_inf_lo, atan_lo);
    t = _T::sel(r, -1.0f/x, t);

    // coefficients for atan generated by sollya
    // x^0
    const vf_type atan_c0=0x1.555556p-2f;
    // x^2
    const vf_type atan_c2=-0x1.9999fep-3f;
    // x^4
    const vf_type atan_c4=0x1.249736p-3f;
    // x^6
    const vf_type atan_c6=-0x1.c6868ap-4f;
    // x^8
    const vf_type atan_c8=0x1.65b0fp-4f;
    // x^10
    const vf_type atan_c10=-0x1.aa221ep-5f;

    vf_type t2=t*t;
    vf_type p= t2 * impl::poly(t2,
                               atan_c10,
                               atan_c8,
                               atan_c6,
                               atan_c4,
                               atan_c2,
                               atan_c0);
    vf_type at=  atan_hi - (t * p - atan_lo - t);
    at = copysign(at, xc);
    return at;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
atan2_k(arg_t<vf_type> y, arg_t<vf_type> x)
{
    vf_type yx=y/x;
    vf_type t=atan_k(abs(yx));
    vf_type y_s = copysign(vf_type(1.0f), y);
    vf_type x_s = copysign(vf_type(1.0f), x);

    vmf_type y_lt_0 = y_s < 0.0f;
    vmf_type x_lt_0 = x_s < 0.0f;
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    // default y>=0, x>=0,
    vf_type at= _T::sel(y_lt_0 & x_lt_0,
                        (t - ctbl::m_pi.l()) - ctbl::m_pi.h(),
                        t);
    at = _T::sel(y_lt_0 & (x_s>=0), -t, at);
    at = _T::sel((y_s >=0) & x_lt_0,
                 ctbl::m_pi.h() - (t - ctbl::m_pi.l()),
                 at);
    return at;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
asin_k_poly(arg_t<vf_type> x2)
{
    // coefficients for asin generated by sollya
    // x^12
    const vf_type asin_c12=0x1.3416p-5;  // 0x3fa3416000000000
    // x^10
    const vf_type asin_c10=0x1.560432p-8;  // 0x3f75604320000000
    // x^8
    const vf_type asin_c8=0x1.9e114ep-6;  // 0x3f99e114e0000000
    // x^6
    const vf_type asin_c6=0x1.ebe2dep-6;  // 0x3f9ebe2de0000000
    // x^4
    const vf_type asin_c4=0x1.6de63ap-5;  // 0x3fa6de63a0000000
    // x^2
    const vf_type asin_c2=0x1.33328cp-4;  // 0x3fb33328c0000000
    // x^0
    const vf_type asin_c0=0x1.555556p-3;  // 0x3fc5555560000000
    vf_type r=x2*impl::poly(x2,
                            asin_c12,
                            asin_c10,
                            asin_c8,
                            asin_c6,
                            asin_c4,
                            asin_c2,
                            asin_c0);
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
asin_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vmf_type x_lt_1_2= x<0.5f;
    vf_type x2= x*x;
    vf_type z= (1.0f-x)*0.5f;
    vf_type s= sqrt(z);

    vf_type xr=_T::sel(x_lt_1_2, x2, z);
    vf_type r=asin_k_poly(xr);
    vf_type as0= x + x*r;
    // default: x>0.975
    // vf_type as = ctbl::m_pi_2.h() - (2*(s+s*r) - ctbl::m_pi_2.l());
    // x in [0, 1]
    vi_type t=_T::as_int(s);
    t &= 0xfffff000;
    vf_type f=_T::as_float(t);
    vf_type c= (z-f*f)/(s+f);
    vf_type as1= 0.5f * ctbl::m_pi_2.h() -
        (2.0f*s*r - (ctbl::m_pi_2.l() -2.0f *c) -
         (0.5f*ctbl::m_pi_2.h()-2.0f*f));
    vf_type as=_T::sel(x_lt_1_2, as0, as1);
    as = copysign(as, xc);
    return as;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
acos_k(arg_t<vf_type> xc)
{
    vf_type x= xc;

    vmf_type x_lt_m_1_2 = x < -0.5f;
    vmf_type x_gt_1_2 = x>0.5f;
    vmf_type abs_x_le_1_2 = abs(x) <= 0.5f;

    vf_type z= _T::sel(x_lt_m_1_2, (1.0f+x)*0.5f, (1.0f-x)*0.5f);
    vf_type s= sqrt(z);
    vf_type x2=x*x;
    vf_type xr= _T::sel(abs_x_le_1_2, x2, z);
    vf_type r= asin_k_poly(xr);

    // x in [-0.5, 0.5]
    using ctbl=impl::d_real_constants<d_real<float>, float>;
    vf_type ac = ctbl::m_pi_2.h() - (x - (ctbl::m_pi_2.l()-x*r));
    // x in [-1.0, -0.5]
    vf_type wn = r*s - ctbl::m_pi_2.l();
    vf_type ac1= 2*(ctbl::m_pi_2.h() - (s+wn));
    ac = _T::sel(x_lt_m_1_2, ac1, ac);
    // x in [0.5, 1.0]
    vi_type t=_T::as_int(s);
    t &= 0xfffff000;
    vf_type df= _T::as_float(t);
    vf_type c= (z-df*df)/(s+df);
    vf_type wp= r*s+c;
    vf_type ac2=2.0f*(df+wp);
    ac = _T::sel(x_gt_1_2, ac2, ac);
    return ac;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
asinh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vmf_type x_gt_0x1p12 = x > 0x1p12;
    vf_type add_2_log=_T::sel(x_gt_0x1p12, ctbl::m_ln2.h(), vf_type(0));
    vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p12,
                            x,
                            2.0f * x+ 1.0f/(sqrt(vf_type(t+1.0f))+x));
    vf_type yl= log_k(log_arg, log_func::c_log_e);
    yl += add_2_log;
    // |x| < 2.0
    vf_type log1p_arg= x+t/(1.0f+sqrt(vf_type(1.0f+t)));
    vf_type ys= log1p_k(log1p_arg);

    // coefficients for asinh generated by sollya
    // x^0
    const vf_type asinh_c0=0x1p0f;
    // x^2
    const vf_type asinh_c2=-0x1.55554ep-3f;
    // x^4
    const vf_type asinh_c4=0x1.333034p-4f;
    // x^6
    const vf_type asinh_c6=-0x1.6d4b1p-5f;
    // x^8
    const vf_type asinh_c8=0x1.ea71d4p-6f;
    // x^10
    const vf_type asinh_c10=-0x1.4b2f94p-6f;
    // x^12
    const vf_type asinh_c12=0x1.700f9ep-7f;
    // x^14
    const vf_type asinh_c14=-0x1.c3613ap-9f;

    vf_type yss= x* impl::poly(t,
                               asinh_c14,
                               asinh_c12,
                               asinh_c10,
                               asinh_c8,
                               asinh_c6,
                               asinh_c4,
                               asinh_c2,
                               asinh_c0);

    ys = _T::sel(x<= M_SQRT2*0.5f, yss, ys);

    vf_type ash=_T::sel(x <= 2.0f, ys, yl);
    ash = copysign(ash, xc);
    return ash;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
acosh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    vmf_type x_gt_0x1p12 = x > 0x1p12;
    vf_type add_2_log=_T::sel(x_gt_0x1p12, ctbl::m_ln2.h(), vf_type(0));
    // vf_type t= x*x;
    vf_type log_arg=_T::sel(x_gt_0x1p12,
                            x,
                            2.0f*x - 1.0f/(x+sqrt(vf_type(x*x-1.0f))));
    vf_type yl= log_k(log_arg, log_func::c_log_e);
    yl += add_2_log;
#if 1
    using d_ops=cftal::impl::d_real_ops<vf_type, d_real_traits<vf_type>::fma>;
    vf_type xm1l;
    vf_type xm1=d_ops::two_diff(x, vf_type(1), xm1l);
    dvf_type sqrt2xm1=sqrt(mul_pwr2(dvf_type(xm1, xm1l), vf_type(2)));
    // acosh(x) = sqrt(2*x) * [1-1/12*x+3/160*x^2-5/896*x^3+ ...]
    // coefficients for acosh generated by sollya
    // x^0
    const vf_type acosh_c0=0x1p0f;
    // x^1
    const vf_type acosh_c1=-0x1.555554p-4f;
    // x^2
    const vf_type acosh_c2=0x1.3332ap-6f;
    // x^3
    const vf_type acosh_c3=-0x1.6d9f54p-8f;
    // x^4
    const vf_type acosh_c4=0x1.efdceep-10f;
    // x^5
    const vf_type acosh_c5=-0x1.6301b8p-11f;
    // x^6
    const vf_type acosh_c6=0x1.e311ap-13f;
    // x^7
    const vf_type acosh_c7=-0x1.00a3fep-14f;
    // x^8
    const vf_type acosh_c8=0x1.2323e8p-17f;
    vf_type ys=impl::poly(xm1,
                          acosh_c8,
                          acosh_c7,
                          acosh_c6,
                          acosh_c5,
                          acosh_c4,
                          acosh_c3,
                          acosh_c2,
                          acosh_c1,
                          acosh_c0);
    ys= (sqrt2xm1 * ys).h();
#else
    vf_type log1p_arg=x-1.0f+ sqrt(
        vf_type((x-1.0f)*(x-1.0f)+2.0f*(x-1.0f)));
    vf_type ys=log1p_k(log1p_arg);
#endif
    vf_type y= _T::sel(x < 2.0f, ys, yl);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
atanh_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
#if 1
    // atanh(x) = x + 1/3*x^3 + 1/5*x^5
    //          = x + x^3/(3+x^2*Q)
    // coefficients for atanh generated by sollya
    // x^0
    const vf_type atanh_c0=-0x1.ccccccp0f;
    // x^2
    const vf_type atanh_c2=-0x1.a55046p-3f;
    // x^4
    const vf_type atanh_c4=-0x1.adffdp-4f;
    // x^6
    const vf_type atanh_c6=-0x1.1ae666p-4f;
    // x^8
    const vf_type atanh_c8=-0x1.198b46p-5f;
    // x^10
    const vf_type atanh_c10=-0x1.2a5606p-4f;
    // x^12
    const vf_type atanh_c12=-0x1.861d78p-10f;
    vf_type xx=x*x;
    vf_type Q = impl::poly(xx,
                           atanh_c12,
                           atanh_c10,
                           atanh_c8,
                           atanh_c6,
                           atanh_c4,
                           atanh_c2,
                           atanh_c0);
    vf_type ys= x + x*xx/(3.0f + xx * Q);
    vf_type log1p_arg= 2.0f*(x/(1.0f-x));
    vf_type yl= 0.5f*log1p_k(log1p_arg);
    vf_type y=_T::sel(x<=0.5f, ys, yl);
    y = copysign(y, xc);
    return y;
#else
    // vf_type s=copysign(vf_type(1.0), xc);
    vf_type log1p_arg= _T::sel(x < 0.5f,
                               2.0f*x + 2.0f*x*x/(1.0f-x),
                               2.0f*(x/(1.0f-x)));
    vf_type r=0.5f*log1p_k(log1p_arg);
    r=copysign(r, xc);
    return r;
#endif
}

template <typename _T>
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
erf_k(arg_t<vf_type> xc)
{
    vf_type x=abs(xc);
#if 0
    // coefficients for erf_i1 generated by sollya
    // x^1 : +0x8.7ae8bp-3f
    const vf_type erf_i1_c1=+1.0600141287e+00f;
    // x^2 : -0x8.7ae8bp-5f
    const vf_type erf_i1_c2=-2.6500353217e-01f;
    // x^3 : -0x9.e4b9fp-5f
    const vf_type erf_i1_c3=-3.0917069316e-01f;
    // x^4 : +0x8.20744p-6f
    const vf_type erf_i1_c4=+1.2698084116e-01f;
    // x^5 : +0xa.3f0acp-7f
    const vf_type erf_i1_c5=+8.0048888922e-02f;
    // x^6 : -0xa.604dap-8f
    const vf_type erf_i1_c6=-4.0531970561e-02f;
    // x^7 : -0x8.3c7b5p-9f
    const vf_type erf_i1_c7=-1.6086438671e-02f;
    // x^8 : +0x9.ea8fbp-10f
    const vf_type erf_i1_c8=+9.6838427708e-03f;
    // x^9 : +0x8.7dc84p-12f
    const vf_type erf_i1_c9=+2.0730802789e-03f;
    // x^10 : -0xe.632bbp-13f
    const vf_type erf_i1_c10=-1.7562726280e-03f;
    // x^ h: +0x8.d7aa7p-5f
    const vf_type erf_i1h=+2.7632638812e-01f;
    // x^ l: +0x8.cb582p-32f
    const vf_type erf_i1l=+2.0475856566e-09f;
    // x^ : +0x0p+0f
    const vf_type erf_i1_left=+0.0000000000e+00f;
    // x^ : +0x8p-5f
    const vf_type erf_i1_x0=+2.5000000000e-01f;
    vf_type x_i1 = x - erf_i1_x0;
    vf_type y_i1= impl::poly(x_i1,
                             // erf_i1_c18,
                             // erf_i1_c17,
                             // erf_i1_c16,
                             // erf_i1_c15,
                             // erf_i1_c14,
                             // erf_i1_c13,
                             // erf_i1_c12,
                             // erf_i1_c11,
                             erf_i1_c10,
                             erf_i1_c9,
                             erf_i1_c8,
                             erf_i1_c7,
                             erf_i1_c6,
                             erf_i1_c5,
                             erf_i1_c4,
                             erf_i1_c3,
                             erf_i1_c2,
                             erf_i1_c1)*x_i1;
    y_i1 += erf_i1l;
    y_i1 += erf_i1h;
    vf_type y_i0=y_i1;
#else
    // coefficients for erf_i0 generated by sollya
    // x^0 : +0xcp-2f
    const vf_type erf_i0_c0=+3.0000000000e+00f;
    // x^2 : +0xe.66666p-4f
    const vf_type erf_i0_c2=+8.9999997616e-01f;
    // x^4 : +0xe.436b4p-8f
    const vf_type erf_i0_c4=+5.5716231465e-02f;
    // x^6 : -0xc.34e84p-11f
    const vf_type erf_i0_c6=-5.9602875262e-03f;
    // x^8 : +0xa.a8aa3p-14f
    const vf_type erf_i0_c8=+6.5056438325e-04f;
    // x^10 : -0x8.b3c65p-11f
    const vf_type erf_i0_c10=-4.2491429485e-03f;
    // x^12 : +0xa.1f9aap-10f
    const vf_type erf_i0_c12=+9.8861847073e-03f;
    // x^ h: +0x9.06ebbp-3f
    const vf_type two_o_sqrt_pih=+1.1283792257e+00f;
    // x^ l: -0xf.bd649p-28f
    const vf_type two_o_sqrt_pil=-5.8635382771e-08f;
    // x^ : +0x9.06ebap-3f
    const vf_type two_o_sqrt_pi_h=+1.1283791065e+00f;
    // x^ : +0xcp-27f
    const vf_type two_o_sqrt_pi_l=+8.9406967163e-08f;
    vf_type xx= xc*xc;
    vf_type P= impl::poly(xx,
                          // erf_i0_c18,
                          // erf_i0_c16,
                          // erf_i0_c14,
                          erf_i0_c12,
                          erf_i0_c10,
                          erf_i0_c8,
                          erf_i0_c6,
                          erf_i0_c4,
                          erf_i0_c2,
                          erf_i0_c0);
    vf_type y_i0= x - x * xx/P;
    y_i0 = y_i0*two_o_sqrt_pi_h + y_i0 * two_o_sqrt_pi_l;
#endif
    vf_type y = y_i0;
#if 0
    y=_T::sel(x > erf_i1_left, y_i1, y_i0);
    y = _T::sel(x > erf_i2_left, y_i2, y);
    y = _T::sel(x > erf_i3_left, y_i3, y);
    y = _T::sel(x > erf_i4_left, y_i4, y);
#endif
    y = copysign(y, xc);
    return y;
}

template <typename _T>
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    vf_type xp=abs(xc);
    // m in [0.5, 1)
    const divisor<vi_type, int32_t> idiv3(3);
    vi_type e = ilogbp1(xp);
    vi_type e3= e / idiv3;
    // vi2_type r3= remainder(e, vi2_type(3), e3);
    vi_type r3= e-(e3+e3+e3);
    // select r3c so that r3c [-2,-1,0]
    vmi_type r3gt0 = r3 > 0;
    vi_type r3c= _T::sel(r3gt0, r3-3, r3);
    vi_type e3c= _T::sel(r3gt0, e3+1, e3);
    vi_type sc= r3c - e;
    vf_type mm0 = ldexp(xp, sc);
    // coefficients for cbrt generated by sollya
    // x^3
    const vf_type cbrt_c3=0x1.2f32e2p-1f;  // 0x3f179971
    // x^2
    const vf_type cbrt_c2=-0x1.62cbf8p0f;  // 0xbfb165fc
    // x^1
    const vf_type cbrt_c1=0x1.7546e4p0f;  // 0x3fbaa372
    // x^0
    const vf_type cbrt_c0=0x1.5d05aap-2f;  // 0x3eae82d5
    vf_type mm = impl::poly(mm0,
                            cbrt_c3,
                            cbrt_c2,
                            cbrt_c1,
                            cbrt_c0);
    // 1st iteration
    vf_type s=mm*mm*mm;
    mm = mm -(s - mm0) * mm/(2*s+mm0);
    vi_type hw=_T::as_int(mm);
    // round mm to 8 bits (including the hidden one)
    // round up if the first bit truncated is set
    // hw += hw & 0x0008000;
    vi_type corr= hw & 0x000008000;
    // vi_type corr= hw & 0x0000e000;
    // vmi_type m=(vi_type(hw & 0x0001e000) != vi_type(0x00008000)) &
    //    (corr != vi_type(0));
    // corr= _T::sel(m, vi_type(0x00008000), vi_type(0));
    hw += corr;
    hw &= 0xffff0000;
    mm=_T::as_float(hw);
    // second iteration
    s= (mm*mm*mm-mm0)/mm0;
    mm = mm - mm * ((((14.0/81.0) * s -(2.0/9.0))*s)+1.0/3.0)*s;
    mm = ldexp(mm, e3c);
    mm = copysign(mm, xc);
    return mm;
}

#if 0
template <typename _T>
inline
void
cftal::math::func_core<float, _T>::
native_sin_cos_k(arg_t<vf_type> x, vf_type* ps, vf_type* pc)
{
#define PI4_Af 0.78515625f
#define PI4_Bf 0.00024187564849853515625f
#define PI4_Cf 3.7747668102383613586e-08f
#define PI4_Df 1.2816720341285448015e-12f

    vf_type xs(x *vf_type(2*M_1_PI));
    vi_type q(_T::cvt_f_to_i(xs));
    vf_type qf(_T::cvt_i_to_f(q));
    vf_type s(x);

    s = qf* vf_type(-PI4_Af*2.0f) + s;
    s = qf* vf_type(-PI4_Bf*2.0f) + s;
    s = qf* vf_type(-PI4_Cf*2.0f) + s;
    s = qf* vf_type(-PI4_Df*2.0f) + s;

    vf_type t(s);
    s = s * s;

    vf_type u(-0.000195169282960705459117889f);
    u = u * s + vf_type(0.00833215750753879547119141f);
    u = u * s + vf_type(-0.166666537523269653320312f);
    u = u * s * t;

    vf_type si(t + u);

    u = vf_type(-2.71811842367242206819355e-07f);
    u = u * s + vf_type(2.47990446951007470488548e-05f);
    u = u * s + vf_type(-0.00138888787478208541870117f);
    u = u * s + vf_type(0.0416666641831398010253906f);
    u = u * s + vf_type(0.5f);

    vf_type co(u * s + vf_type(1));

    vmi_type i_q_and_1(vi_type(q & vi_type(1)) != vi_type(0));
    vmi_type i_q_and_2(vi_type(q & vi_type(1)) != vi_type(0));

    vmi_type i_qp1_and_2( vi_type((vi_type(q) + vi_type(1)) &
                                  vi_type(2)) != vi_type(0));

    vmf_type q_and_1(_T::vmi_to_vmf(i_q_and_1));
    vf_type tsi(si);
    vf_type tco(co);
    // swap sin and cos if q_and_1 != 0
    si = _T::sel(q_and_1, tco, tsi);
    co = _T::sel(q_and_1, tsi, tco);

    vmf_type q_and_2(_T::vmi_to_vmf(i_q_and_2));
    // si = _T::sel(q_and_2, -si, si);
    vf_type fs = _T::sel(q_and_2, vf_type(-1.0), vf_type(1.0));
    si *= fs;
    // si = mulsign(si, q_and_2);
    vmf_type qp1_and_2(_T::vmi_to_vmf(i_qp1_and_2));
    // co = _T::sel(qp1_and_2, -co, co);
    vf_type fc= _T::sel(qp1_and_2, vf_type(-1.0), vf_type(1.0));
    co *= fc;
    // co = mulsign(co, qp1_and_2);

    vmf_type x_is_inf(isinf(x));
    const vf_type nanf(_T::nan());

    si = _T::sel(x_is_inf, nanf, si);
    co = _T::sel(x_is_inf, nanf, co);

    if (ps != nullptr)
        *ps = si;
    if (pc != nullptr)
        *pc = co;
    // return std::make_pair(si, co);
#undef PI4_Df
#undef PI4_Cf
#undef PI4_Bf
#undef PI4_Af

}
#endif

#if 0
template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
native_exp_k(arg_t<vf_type> v, bool exp_m1)
{
#define L2Uf 0.693145751953125f
#define L2Lf 1.428606765330187045e-06f
#define R_LN2f 1.442695040888963407359924681001892137426645954152985934135449406931f

    vi_type q(_T::cvt_f_to_i(v * R_LN2f));
    vf_type qf(_T::cvt_i_to_f(q));

    vf_type s(v - qf * vf_type(L2Uf));
    s = s - qf * vf_type(L2Lf);

    vf_type u(0.00136324646882712841033936f);
    u = u * s + 0.00836596917361021041870117f;
    u = u * s + 0.0416710823774337768554688f;
    u = u * s + 0.166665524244308471679688f;
    u = u * s + 0.499999850988388061523438f;

    u = s * s * u + s + vf_type(1.0f);
    u = my_type::ldexp(u, q);

    // vmf_type isminf(v == _T::ninf());
    // u = _T::sel(isminf, vf_type(0.0f), u);
    return u;
#undef L2Lf
#undef L2Uf
}
#endif


#if 0
template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
native_log_k(arg_t<vf_type> v)
{
    vi_type e(my_type::ilogbp1(v * 0.7071f));
    vf_type m(my_type::ldexp(v, -e));

    vf_type x((m-vf_type(1.0f))/(m-vf_type(1.0f)));
    vf_type x2(x * x);
    vf_type   t = 0.2371599674224853515625f;
    t = t * x2 + 0.285279005765914916992188f;
    t = t * x2 + 0.400005519390106201171875f;
    t = t * x2 + 0.666666567325592041015625f;
    t = t * x2 + 2.0f;
    vf_type ef(_T::cvt_i_to_f(e));
    x = x * t + 0.693147180559945286226764f * ef;
    return x;
}
#endif

#if 0
template <typename _T>
inline
typename
cftal::math::func<float, _T>::vf_type
cftal::math::func<float, _T>::native_sin(arg_t<vf_type> x)
{
#define PI4_Af 0.78515625f
#define PI4_Bf 0.00024187564849853515625f
#define PI4_Cf 3.7747668102383613586e-08f
#define PI4_Df 1.2816720341285448015e-12f

    vi_type q(_T::cvt_f_to_i(x * M_1_PI));
    vf_type qf(_T::cvt_i_to_f(q));

    vf_type d(qf * vf_type(-PI4_Af*4.0f) + x);
    d = qf * vf_type(-PI4_Bf*4.0f) + d;
    d = qf * vf_type(-PI4_Cf*4.0f) + d;
    d = qf * vf_type(-PI4_Df*4.0f) + d;

    vf_type s(d* d);

    vmi_type q_and_1_i(vi_type(q & vi_type(1)) != vi_type(0));
    vmf_type q_and_1(_T::vmi_to_vmf(q_and_1_i));

    d = _T::sel(q_and_1, -d, d);

    vf_type u(2.6083159809786593541503e-06f);
    u = u * s -0.0001981069071916863322258f;
    u = u * s +0.00833307858556509017944336f;
    u = u * s -0.166666597127914428710938f;
    u = s * u * d + d;

    vmf_type d_s_inf(isinf(d));
    u = _T::sel(d_s_inf, _T::nan(), u);
    return u;

#undef PI4_Df
#undef PI4_Cf
#undef PI4_Bf
#undef PI4_Af

}

template <typename _T>
inline
typename
cftal::math::func<float, _T>::vf_type
cftal::math::func<float, _T>::native_cos(arg_t<vf_type> x)
{
#define PI4_Af 0.78515625f
#define PI4_Bf 0.00024187564849853515625f
#define PI4_Cf 3.7747668102383613586e-08f
#define PI4_Df 1.2816720341285448015e-12f

    vi_type q(_T::cvt_f_to_i( x * vf_type(M_1_PI) - vf_type(0.5)));
    q <<= 1;
    q += vi_type(1);

    vf_type qf(_T::cvt_i_to_f(q));

    vf_type d( qf - vf_type(PI4_Af*2) + x);
    d = qf - vf_type(PI4_Bf*2) + d;
    d = qf - vf_type(PI4_Cf*2) + d;
    d = qf - vf_type(PI4_Df*2) + d;

    vf_type s(d * d);

    vmi_type q_and_2_zero_i(vi_type(q & vi_type(2)) == vi_type(2));
    vmf_type q_and_2_zero(_T::vmi_to_vmf(q_and_2_zero_i));

    d = _T::sel(q_and_2_zero, -d, d);

    vf_type u(2.6083159809786593541503e-06f);
    u = u * s -0.0001981069071916863322258f;
    u = u * s +0.00833307858556509017944336f;
    u = u * s -0.166666597127914428710938f;
    u = s * u * d +  d;

    vmf_type d_is_inf(isinf(d));

    u = _T::sel(d_is_inf, _T::nan(), u);
    return u;

#undef PI4_Df
#undef PI4_Cf
#undef PI4_Bf
#undef PI4_Af
}
#endif

// Local Variables:
// mode: c++
// end:
#endif
