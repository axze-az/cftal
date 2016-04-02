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

            static constexpr double pinf() {
                return std::numeric_limits<float>::infinity();
            }
            static constexpr double ninf() {
                return -std::numeric_limits<double>::infinity();
            }
            static constexpr double nan() {
                return std::numeric_limits<double>::quiet_NaN();
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

            static vf_type pow2i(arg_t<vi_type> d);
            static vf_type ldexp(arg_t<vf_type> vf,
                                 arg_t<vi_type> vi);
            static vf_type frexp(arg_t<vf_type> vf,
                                 vi_type* vi);
            static vi_type ilogbp1(arg_t<vf_type> x);

            static vi_type ilogb(arg_t<vf_type> vf);


            static std::pair<vf_type, vi_type>
            reduce_trig_arg_k(arg_t<vf_type> x);
            // core sine, cosine calculation
            static
            void
            sin_cos_k(arg_t<vf_type> x, vf_type* s, vf_type* c);

            static
            vf_type
            tan_k(arg_t<vf_type> x);

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
            log_k(arg_t<vf_type> x);

            static
            vf_type
            log1p_k(arg_t<vf_type> x);

            static
            vf_type
            log2_k(arg_t<vf_type> x);

            static
            vf_type
            log10_k(arg_t<vf_type> x);

            static
            vf_type
            atan_k(arg_t<vf_type> x);

            static
            vf_type
            atan2_k(arg_t<vf_type> y, arg_t<vf_type> x);

            static
            vf_type
            asin_k(arg_t<vf_type> x);

            static
            vf_type
            acos_k(arg_t<vf_type> x);

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
    // see math_func_f64 for comments about the code
    using ctbl = impl::d_real_constants<d_real<float>, float>;

    vf_type x=xc;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ln2.h()));
    vf_type hi = x - kf * ctbl::m_ln2_cw[0];
    vf_type lo = kf * ctbl::m_ln2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);
    vf_type y;
    if (exp_m1 == false) {
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
    const vf_type exp2_c5=0x1.427918p-13;  // 0x3f24279180000000
    // x^4
    const vf_type exp2_c4=0x1.5ef4a2p-10;  // 0x3f55ef4a20000000
    // x^3
    const vf_type exp2_c3=0x1.3b2c58p-7;  // 0x3f83b2c580000000
    // x^2
    const vf_type exp2_c2=0x1.c6af9ep-5;  // 0x3fac6af9e0000000
    // x^1
    const vf_type exp2_c1=0x1.ebfbdep-3;  // 0x3fcebfbde0000000
    // x^0
    const vf_type exp2_c0=0x1.62e43p-1;  // 0x3fe62e4300000000
    vf_type y=impl::poly(xr,
                         exp2_c5,
                         exp2_c4,
                         exp2_c3,
                         exp2_c2,
                         exp2_c1,
                         exp2_c0);
    y *= xr;
    y += 1.0;
    y= scale_exp_k(y, kf, k);
    return y;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
exp10_k(arg_t<vf_type> x)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type kf = rint(vf_type(x * ctbl::m_1_ld2.h()));
    vf_type hi = x - kf * ctbl::m_ld2_cw[0];
    vf_type lo = kf * ctbl::m_ld2_cw[1];
    vf_type xr = hi - lo;
    vi_type k= _T::cvt_f_to_i(kf);
    // coefficients for exp10 generated by sollya
    // x^5
    const vf_type exp10_c5=0x1.a8649cp-3;  // 0x3fca8649c0000000
    // x^4
    const vf_type exp10_c4=0x1.155f1p-1;  // 0x3fe155f100000000
    // x^3
    const vf_type exp10_c3=0x1.2bd7cap0;  // 0x3ff2bd7ca0000000
    // x^2
    const vf_type exp10_c2=0x1.046faap1;  // 0x400046faa0000000
    // x^1
    const vf_type exp10_c1=0x1.53524cp1;  // 0x40053524c0000000
    // x^0
    const vf_type exp10_c0=0x1.26bb1cp1;  // 0x40026bb1c0000000
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
log_k(arg_t<vf_type> d0)
{
    using ctbl=impl::d_real_constants<d_real<float>, float>;

    // -1022+53 = -969
    vmf_type d_small= d0 < ctbl::log_arg_small;
    vf_type d=d0;
    if (any_of(d_small)) {
        vf_type t= d0 * vf_type(ctbl::log_arg_small_factor);
        d = _T::sel(d_small, t, d);
    }

    vf_type sc(d* vf_type(0.7071) /*vf_type(M_SQRT1_2)*/);

    vi_type e = ilogbp1(sc);
    vf_type ef= _T::cvt_i_to_f(e);
    vf_type m(ldexp(d, -e));

    vf_type xm= m - vf_type(1.0);
    vf_type xp= m + vf_type(1.0);
    vf_type xr= xm / xp;
    vf_type x2 = xr*xr;

    vf_type t= impl::poly(x2, ctbl::log_coeff);
    t = t * x2 + vf_type(2.0);
    t = t * xr;

    xr = t + M_LN2 * ef;

    if (any_of(d_small)) {
        vf_type t= xr - vf_type(ctbl::m_ln_small_arg.h());
        xr = _T::sel(d_small, t, xr);
    }
    return xr;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log1p_k(arg_t<vf_type> d0)
{
    return d0;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log2_k(arg_t<vf_type> d0)
{
    return d0;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
log10_k(arg_t<vf_type> d0)
{
    return d0;
}

#if 0
template <typename _T>
inline
void
cftal::math::func_core<float, _T>::
sin_cos_k(arg_t<vf_type> x,
          std::size_t n,
          vf_type* ps, vf_type* pc)
{
    using vhpf_type = typename _T::vhpf_type;
    const std::size_t elements = _T::vhpf_per_vf();

    vhpf_type xi[elements];
    _T::vf_to_vhpf(x, xi);

    using hpf_traits = typename _T::hpf_traits;
    using hpf_func =
        func_core<double, hpf_traits>;

    vhpf_type hpf_sin[elements];
    vhpf_type hpf_cos[elements];
    for (std::size_t i=0; i < elements; ++i) {
        vhpf_type* hps= ps != nullptr ? hpf_sin + i : nullptr;
        vhpf_type* hpc= pc != nullptr ? hpf_cos + i : nullptr;
        hpf_func::native_sin_cos_k(xi[i], hps, hpc);
    }
    if (ps != nullptr) {
        dvf_type sr;
        _T::vhpf_to_dvf(hpf_sin, sr);
        ps[0] = sr.h();
        if (n > 1)
            ps[1] = sr.l();
    }
    if (pc != nullptr) {
        dvf_type cr;
        _T::vhpf_to_dvf(hpf_cos, cr);
        pc[0] = cr.h();
        if (n > 1)
            pc[1] = cr.l();
    }
}
#endif



template <typename _T>
inline
std::pair<typename cftal::math::func_core<float, _T>::vf_type,
          typename cftal::math::func_core<float, _T>::vi_type>
cftal::math::func_core<float, _T>::
reduce_trig_arg_k(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vmf_type v_large_arg(
        vf_type(ctbl::native_sin_cos_arg_large) < abs(d));

    vf_type qf(rint(vf_type(d * (2 * M_1_PI))));
    vi_type q(_T::cvt_f_to_i(qf));

#if 1
    using d_real_traits_t= d_real_traits<vf_type>;
    vf_type qfl, qfh;
    d_real_traits_t::split(qf, qfh, qfl);
    vf_type d0(d);
    for (auto b=std::cbegin(ctbl::m_pi_2_cw), e=std::cend(ctbl::m_pi_2_cw);
         b != e; ++b) {
        vf_type t=*b;
        d0 = d0 - qfh * t;
        d0 = d0 - qfl * t;
    }
#else
    vf_type d0(d);
    for (auto b=std::cbegin(ctbl::m_pi_2_cw), e=std::cend(ctbl::m_pi_2_cw);
         b != e; ++b) {
        vf_type t=*b;
        d0 = d0 - qf * t;
    }
#endif

    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(float)) v_d {
            float _sc[N];
        } tf, d0_l;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, d);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0);
        for (std::size_t i=0; i<N; ++i) {
            if (ctbl::native_sin_cos_arg_large < std::fabs(tf._sc[i])) {
                float y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i], y);
                d0_l._sc[i]= y[1] + y[0];
            }
        }
        d0 = mem<vf_type>::load(d0_l._sc, N);
        q = mem<vi_type>::load(ti._sc, NI);
    }
    return std::make_pair(d0, q);
}

template <typename _T>
__attribute__((flatten, noinline))
void
cftal::math::func_core<float, _T>::
sin_cos_k(arg_t<vf_type> d, vf_type* ps, vf_type* pc)
{
    std::pair<vf_type, vi_type> rq=reduce_trig_arg_k(d);
    vf_type x= rq.first;
    const vi_type& q= rq.second;

    vf_type x2(x*x);

    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vf_type s = impl::poly(x2, ctbl::native_sin_coeff);
    s = s * x;

    vf_type c= impl::poly(x2, ctbl::native_cos_coeff);

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
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
tan_k(arg_t<vf_type> x)
{
    return x;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
atan_k(arg_t<vf_type> x)
{
    return x;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
atan2_k(arg_t<vf_type> y, arg_t<vf_type> x)
{
    return x;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
asin_k(arg_t<vf_type> x)
{
    return x;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
acos_k(arg_t<vf_type> x)
{
    return x;
}

template <typename _T>
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
cbrt_k(arg_t<vf_type> xc)
{
    return xc;
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
