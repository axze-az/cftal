#if !defined (__MATH_FUNC_F64_H__)
#define __MATH_FUNC_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math_common.h>
#include <cftal/mem.h>
#include <cmath>

namespace cftal {

    namespace math {

        namespace impl {

            // returns (y0+y1) = x - N * pi/2
            // the integer results contains
            // only the lower bits of N
            int32_t
            __attribute__((__visibility__("internal")))
            __ieee754_rem_pio2(double x, double *y);
            int
            __attribute__((__visibility__("internal")))
            __kernel_rem_pio2(double *x, double *y, int e0,
                              int nx, int prec,
                              const int32_t *ipio2);


            template <class _T>
            struct d_real_constants<_T, double> {
                // 1/(i!)
                static const unsigned MAX_FAC=30;
                static const _T inv_fac[MAX_FAC+1];
                // 2/i i=0,1,2,3,4...
                static const unsigned MAX_2_OVER_I=30;
                static const _T _2_over_i[MAX_2_OVER_I+1];
                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // low half of m_ln2
                // static const _T m_ln2_low;
                // M_1_LN2 1/LOG_E(2)
                static const _T m_1_ln2;
                // 2*PI
                static const _T m_pi2;
                // 1/(2*PI)
                static const _T m_1_pi2;
                // PI
                static const _T m_pi;
                // 1/PI
                static const _T m_1_pi;
                // PI/2
                static const _T m_pi_2;
                // 2/PI
                static const _T m_2_pi;
                // PI/4
                static const _T m_pi_4;
                // 4/PI
                static const _T m_4_pi;
            };

            template <class _T>
            struct t_real_constants<_T, double> {
                // 1/(i!)
                static const unsigned MAX_FAC=30;
                static const _T inv_fac[MAX_FAC+1];
                // 2/i i=0,1,2,3,4...
                static const unsigned MAX_2_OVER_I=30;
                static const _T _2_over_i[MAX_2_OVER_I+1];
                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_1_LN2 1/LOG_E(2)
                static const _T m_1_ln2;
                // 2*PI
                static const _T m_pi2;
                // 1/(2*PI)
                static const _T m_1_pi2;
                // PI
                static const _T m_pi;
                // 1/PI
                static const _T m_1_pi;
                // PI/2
                static const _T m_pi_2;
                // 2/PI
                static const _T m_2_pi;
                // PI/4
                static const _T m_pi_4;
                // 4/PI
                static const _T m_4_pi;
            };

        }

        template <>
        struct func_traits<double, int32_t>
            : public d_real_traits<double> {
            typedef double vf_type;
            typedef int32_t vi_type;
            typedef bool vmf_type;
            typedef bool vmi_type;
            typedef uint32_t mask_type;
            typedef union {
                double _d;
                uint64_t _u;
            } ud_t;

            static constexpr int32_t bias = 0x3ff;
            static constexpr int32_t e_max= 0x3ff;
            static constexpr int32_t e_min= -1022;
            static constexpr int32_t bits=52;
            static constexpr int32_t vec_len=1;

            static constexpr double pinf() {
                return std::numeric_limits<double>::infinity();
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
            vf_type gather(const double* p, vi_type idx, int sc) {
                const char* pc=
                    reinterpret_cast<const char*>(p);
                const char* d = pc + idx * sc;
                vf_type r(*reinterpret_cast<const double*>(d));
                return r;
            }
            static
            vf_type insert_exp(const vi_type& e) {
                ud_t t;
                t._u = uint64_t(e) << bits;
                return t._d;
            }
            static
            vi_type extract_exp(const vf_type& d) {
                ud_t t;
                t._d = d;
                return (t._u >> bits) & 0x7FF;
            }

            static
            vi_type extract_high_word(const vf_type& d) {
                ud_t t;
                t._d = d;
                return vi_type(t._u >>32);
            }

            static
            vi_type extract_low_word(const vf_type& d) {
                ud_t t;
                t._d = d;
                return vi_type(t._u);
            }

            static
            vf_type insert_high_word(const vf_type& d,
                                     const vi_type& w) {
                ud_t t;
                t._d = d;
                uint64_t hh= w;
                t._u = (t._u & 0xFFFFFFFF) | (hh << 32);
                return t._d;
            }

            static
            vf_type insert_low_word(const vf_type& d,
                                    const vi_type& w) {
                ud_t t;
                t._d = d;
                t._u = (t._u & 0xFFFFFFFF00000000ULL) | w;
                return t._d;
            }

            static
            vf_type combine_words(const vi_type& l,
                                  const vi_type& h) {
                vf_type t(insert_low_word(0.0, l));
                return insert_high_word(t, h);
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
        };

        template <typename _T>
        struct func_core<double, _T> {
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef func_core<double, _T> my_type;

            static const dvf_type m_sin_c_k2[];
            static const dvf_type m_cos_c_k2[];

            static tvf_type
            exp_k3(const tvf_type& tvf);

            static dvf_type
            exp_k2(const dvf_type& dvf, bool exp_m1=false);

            static vf_type
            native_exp_k(const vf_type& v, bool exp_m1=false);

            static dvf_type
            exp2_k2(const dvf_type& dvf);

            static vf_type
            native_exp2_k(const vf_type& v);

            static dvf_type
            exp10_k2(const dvf_type& dvf);

            static vf_type
            native_exp10_k(const vf_type& v);

            static dvf_type
            log_k2(const dvf_type& dvf);

            static vf_type
            native_log_k(const vf_type& v);

            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static std::pair<dvf_type, vi_type>
            reduce_trig_arg_k(const vf_type& v);
            // core sine, cosine calculation, n determines the
            // the number of result components to store into s[0..n1)
            // and c[0..n)
            static void
            sin_cos_k(vf_type v, std::size_t n,
                      vf_type* s, vf_type* c);
            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static std::pair<vf_type, vi_type>
            native_reduce_trig_arg_k(const vf_type& v);
            // core sine, cosine calculation
            static void
            native_sin_cos_k(const vf_type& v,
                             vf_type* s, vf_type* c);

            // cofficients for atan2
            static const dvf_type m_atan2_c_k2[];

            // atan2 kernel
            static dvf_type
            atan2_k2(const dvf_type& x, const dvf_type& y);

            // native atan2 kernel
            static vf_type
            native_atan2_k(const vf_type& x, const vf_type& y);

            static vf_type pow2i(const vi_type& vi);
            static vf_type ldexp(const vf_type& vf,
                                 const vi_type& vi);
            static vf_type frexp(const vf_type& vf,
                                 vi_type* vi);

            static vi_type ilogbp1(const vf_type& vi);
            static vi_type ilogb(const vf_type& vf);
        };

    } // end math
} // end cftal

template <typename _T>
inline
typename
cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
pow2i(const vi_type& vi)
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
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
ldexp(const vf_type& vd, const vi_type& ve)
{
    vi_type q(ve);
    vi_type m(q >> 31);
    m = (((m + q) >> 9) - m) << 7;
    q = q - (m << 2);

    m += 0x3ff;
    m = max(vi_type(0), m);
    m = min(vi_type(0x7ff), m);

    vf_type fm(_T::insert_exp(m));
    // calculate fm^4
    fm *= fm;
    fm *= fm;
    vf_type r(vd * fm);
    q += 0x3ff;
    // q = max(vi_type(0), q);
    // q = min(vi_type(0x7ff), q);
    vf_type fq(_T::insert_exp(q));
    return r * fq;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp(const vf_type& vd, vi_type* ve)
{
    // normal numbers:
    vi_type hi_word(_T::extract_high_word(vd));
    vi_type lo_word(_T::extract_low_word(vd));

    vi_type value_head(hi_word & vi_type(0x7fffffff));

    vmi_type is_inf_nan_zero(
        (value_head >= vi_type(0x7ff00000)) |
        (vi_type(value_head| lo_word)==vi_type(0)));
    vmi_type is_denom(value_head < 0x00100000);

    // exponent:
    vi_type e((value_head >> 20) - vi_type(1022));

    // denormals
    // first multiply with 2^54
    // const vf_type two54=1.80143985094819840000e+16;
    const vf_type two54=0x1.p54;
    vf_type vden(two54 * vd);
    vi_type hden(_T::extract_high_word(vden));
    vi_type lden(_T::extract_low_word(vden));
    vi_type value_head_den(hden & vi_type(0x7fffffff));
    vi_type eden((value_head_den>>20) - vi_type(1022+54));

    // select denom/normal
    e = _T::sel(is_denom, eden, e);
    hi_word = _T::sel(is_denom, hden, hi_word);
    lo_word = _T::sel(is_denom, lden, lo_word);
    // insert exponent
    hi_word = (hi_word & vi_type(0x800fffff)) | vi_type(0x3fe00000);
    // combine low and high word
    vf_type frc(_T::combine_words(lo_word, hi_word));
    // inf, nan, zero
    vmf_type f_inz(_T::vmi_to_vmf(is_inf_nan_zero));
    e= _T::sel(is_inf_nan_zero, vi_type(0), e);
    frc = _T::sel(f_inz, vd, frc);

    if (ve != nullptr)
        *ve= e;
    return frc;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogbp1(const vf_type& vd)
{
    vmf_type mf= vd < 4.9090934652977266E-91;
    vf_type d = _T::sel(mf, 2.037035976334486E90 * vd, vd);
    vi_type q = _T::extract_exp(d);
    vmi_type mi= _T::vmf_to_vmi(mf);
    vi_type qs = _T::sel(mi, vi_type(300 + 0x3fe), vi_type(0x3fe));
    return q - qs;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogb(const vf_type& d)
{
    vi_type e(ilogbp1(abs(d)) - vi_type(1));
    vmf_type mf= d == 0.0;
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
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
log_k2(const dvf_type& d)
{
    using ctbl=impl::d_real_constants<dvf_type, double>;

    dvf_type sc(d* vf_type(0.7071) /*vf_type(M_SQRT1_2)*/);

    vi_type e = ilogbp1(sc.h() + sc.l());
    vf_type ef= _T::cvt_i_to_f(e);
    dvf_type m(ldexp(d.h(), -e), ldexp(d.l(), -e));

    dvf_type xm= m - vf_type(1.0);
    dvf_type xp= m + vf_type(1.0);
    dvf_type xr= xm / xp;
    dvf_type x2 = sqr(xr);

    const int _N=25;
    dvf_type t= ctbl::_2_over_i[_N];
    for (int i=_N-2; i>2; i-=2)
        t = t * x2 + ctbl::_2_over_i[i];
    t = t * x2 + vf_type(2.0);
    t = t * xr;

    xr = t + ctbl::m_ln2 * ef;
    return xr;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_log_k(const vf_type& d)
{
    using ctbl=impl::d_real_constants<dvf_type, double>;

    vf_type sc(d* vf_type(0.7071) /*vf_type(M_SQRT1_2)*/);

    vi_type e = ilogbp1(sc);
    vf_type ef= _T::cvt_i_to_f(e);
    vf_type m(ldexp(d, -e));

    vf_type xm= m - vf_type(1.0);
    vf_type xp= m + vf_type(1.0);
    vf_type xr= xm / xp;
    vf_type x2 = xr*xr;

    const int _N=25;
    vf_type t= ctbl::_2_over_i[_N].h();
    for (int i=_N-2; i>2; i-=2)
        t = t * x2 + ctbl::_2_over_i[i].h();
    t = t * x2 + vf_type(2.0);
    t = t * xr;
    xr = t + M_LN2 * ef;
    return xr;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::tvf_type
cftal::math::func_core<double, _T>::
exp_k3(const tvf_type& d)
{
    using ctbl = impl::t_real_constants<tvf_type, double>;

    vmf_type cmp_res;
    vmi_type i_cmp_res;
    vmf_type inf_nan= isinf(d.h()) | isnan(d.h());
    vmf_type finite= ~inf_nan;
    vi_type k_i(0);

    vmf_type d_large = d.h() > 709.0;
    tvf_type d2=d;
    bool any_of_d_large = any_of(d_large);
    if (any_of_d_large) {
        tvf_type dhalf(mul_pwr2(d, vf_type(0.5)));
        tvf_type dt(_T::sel(d_large, dhalf.h(), d.h()),
                    _T::sel(d_large, dhalf.m(), d.m()),
                    _T::sel(d_large, dhalf.l(), d.l()));
        d2=dt;
    }
    // remove exact powers of 2
    vf_type m2 = rint(vf_type(d2.h() * ctbl::m_1_ln2.h()));
    tvf_type r= d2 - tvf_type(ctbl::m_ln2)*m2;
    // dvf_type m2d= dvf_type(m2);
    // dvf_type r = d2 - ctbl::m_ln2.h()* m2d;
    // r -= m2d * ctbl::m_ln2.l();

    // reduce arguments further until anything is lt M_LN2/512 ~0.0135
    do {
        cmp_res = (abs(r.h()) > vf_type(M_LN2/512)) & finite;
        if (none_of(cmp_res))
            break;
        i_cmp_res = _T::vmf_to_vmi(cmp_res);
        k_i += _T::sel(i_cmp_res, vi_type(1), vi_type(0));
        tvf_type d1 = mul_pwr2(r, vf_type(0.5));
        vf_type d2_h = _T::sel(cmp_res, d1.h(), r.h());
        vf_type d2_m = _T::sel(cmp_res, d1.m(), r.m());
        vf_type d2_l = _T::sel(cmp_res, d1.l(), r.l());
        r = tvf_type(d2_h, d2_m, d2_l);
    } while (1);

    const int _N=9 /* 7 */;
    tvf_type s = ctbl::inv_fac[_N];
    for (unsigned int i=_N-1; i!=2; --i)
        s = s*r + tvf_type(ctbl::inv_fac[i]);
    s = s * r + vf_type(0.5);
    s = s * r + vf_type(1.0);
    s = s * r;

    // scale back the 1/k_i reduced value
    do {
        i_cmp_res = k_i > vi_type(0);
        if (none_of(i_cmp_res))
            break;
        cmp_res = _T::vmi_to_vmf(i_cmp_res);
        tvf_type d1= mul_pwr2(s, vf_type(2.0)) + sqr(s);
        vf_type d2_h = _T::sel(cmp_res, d1.h(), s.h());
        vf_type d2_m = _T::sel(cmp_res, d1.m(), s.m());
        vf_type d2_l = _T::sel(cmp_res, d1.l(), s.l());
        k_i -= vi_type(1);
        s = tvf_type(d2_h, d2_m, d2_l);
    } while (1);
    // const vf_type two(2.0);
    // for (int i=0; i<k_i; ++i)
    //    s = mul_pwr2(s, two) + sqr(s);
    s += vf_type(1.0);

    // scale back
    vi_type mi= _T::cvt_f_to_i(m2);
    tvf_type res(ldexp(s.h(), mi), ldexp(s.m(), mi), ldexp(s.l(), mi));
    if (any_of_d_large) {
        tvf_type xres= sqr(res);
        tvf_type tres(_T::sel(d_large, xres.h(), res.h()),
                      _T::sel(d_large, xres.m(), res.m()),
                      _T::sel(d_large, xres.l(), res.l()));
        res=tres;
    }
    return res;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
exp_k2(const dvf_type& d, bool exp_m1)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;

    vmf_type cmp_res;
    vmi_type i_cmp_res;
    vmf_type inf_nan= isinf(d.h()) | isnan(d.h());
    vmf_type finite= ~inf_nan;
    vi_type k_i(0);

    vmf_type d_large = d.h() > 709.0;
    dvf_type d2=d;
    bool any_of_d_large = any_of(d_large);
    if (any_of_d_large) {
        dvf_type dhalf(mul_pwr2(d, vf_type(0.5)));
        dvf_type dt(_T::sel(d_large, dhalf.h(), d.h()),
                    _T::sel(d_large, dhalf.l(), d.l()));
        d2=dt;
    }
    // remove exact powers of 2
    vf_type m2 = rint(vf_type(d2.h() * ctbl::m_1_ln2.h()));
    dvf_type r= d2 - dvf_type(ctbl::m_ln2)*m2;
    // dvf_type m2d= dvf_type(m2);
    // dvf_type r = d2 - ctbl::m_ln2.h()* m2d;
    // r -= m2d * ctbl::m_ln2.l();

    // reduce arguments further until anything is lt M_LN2/512 ~0.0135
    do {
        cmp_res = (abs(r.h()) > vf_type(M_LN2/512)) & finite;
        if (none_of(cmp_res))
            break;
        i_cmp_res = _T::vmf_to_vmi(cmp_res);
        k_i += _T::sel(i_cmp_res, vi_type(1), vi_type(0));
        dvf_type d1 = mul_pwr2(r, vf_type(0.5));
        vf_type d2_h = _T::sel(cmp_res, d1.h(), r.h());
        vf_type d2_l = _T::sel(cmp_res, d1.l(), r.l());
        r = dvf_type(d2_h, d2_l);
    } while (1);

    const int _N=9 /* 7 */;
    dvf_type s = ctbl::inv_fac[_N];
    for (unsigned int i=_N-1; i!=2; --i)
        s = s*r + dvf_type(ctbl::inv_fac[i]);
    s = s * r + vf_type(0.5);
    s = s * r + vf_type(1.0);
    s = s * r;

    // scale back the 1/k_i reduced value
    do {
        i_cmp_res = k_i > vi_type(0);
        if (none_of(i_cmp_res))
            break;
        cmp_res = _T::vmi_to_vmf(i_cmp_res);
        dvf_type d1= mul_pwr2(s, vf_type(2.0)) + sqr(s);
        vf_type d2_h = _T::sel(cmp_res, d1.h(), s.h());
        vf_type d2_l = _T::sel(cmp_res, d1.l(), s.l());
        k_i -= vi_type(1);
        s = dvf_type(d2_h, d2_l);
    } while (1);
    // const vf_type two(2.0);
    // for (int i=0; i<k_i; ++i)
    //    s = mul_pwr2(s, two) + sqr(s);
    if (exp_m1 == false) {
        s += vf_type(1.0);
    }
    vi_type mi= _T::cvt_f_to_i(m2);
    // scale back
    dvf_type res= dvf_type(ldexp(s.h(), mi), ldexp(s.l(), mi));
    if (exp_m1 == true) {
        vf_type scale=ldexp(vf_type(1.0), mi);
        res += (dvf_type(scale) - vf_type(1.0));
    }
    if (any_of_d_large) {
        // works because for these d at double precision
        // exp(d) == expm1(d)
        dvf_type xres= sqr(res);
        dvf_type tres(_T::sel(d_large, xres.h(), res.h()),
                      _T::sel(d_large, xres.l(), res.l()));
        res=tres;
    }
    return res;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_exp_k(const vf_type& d, bool exp_m1)
{
#if 1
    using ctbl = impl::d_real_constants<d_real<double>, double>;

    vmf_type cmp_res;
    vmi_type i_cmp_res;
    vmf_type inf_nan= isinf(d) | isnan(d);
    vmf_type finite= ~inf_nan;
    vi_type k_i(0);

    vmf_type d_large = d > 709.0;
    vf_type d2=d;
    bool any_of_d_large = any_of(d_large);
    if (any_of_d_large) {
        vf_type dt(_T::sel(d_large, d*vf_type(0.5), d));
        d2=dt;
    }
    // remove exact powers of 2
    vf_type m2= rint(vf_type(d2 * ctbl::m_1_ln2.h()));
    // vf_type r= (d2 - ctbl::m_ln2.h()*m2);
    // subtraction in two steps for higher precision
    const vf_type ln2d_hi = 0.693145751953125;
    const vf_type ln2d_lo = 1.42860682030941723212E-6;
    vf_type r = d2 - m2* ln2d_hi;
    r -= m2 * ln2d_lo;

     // reduce arguments further until anything is lt M_LN2/512 ~ 0.0135
    do {
        cmp_res = (abs(r) > vf_type(M_LN2/512)) & finite;
        if (none_of(cmp_res))
            break;
        i_cmp_res = _T::vmf_to_vmi(cmp_res);
        k_i += _T::sel(i_cmp_res, vi_type(1), vi_type(0));
        vf_type d1 = r * vf_type(0.5);
        vf_type d2 = _T::sel(cmp_res, d1, r);
        r = d2;
    } while (1);

    const int _N=9 /* 7 */;
    vf_type s = ctbl::inv_fac[_N].h();
    for (unsigned int i=_N-1; i!=2; --i)
        s = s*r + ctbl::inv_fac[i].h();
    s = s * r + vf_type(0.5);
    s = s * r + vf_type(1.0);
    s = s * r;

    // scale back the 1/k_i reduced value
    do {
        i_cmp_res = k_i > vi_type(0);
        if (none_of(i_cmp_res))
            break;
        cmp_res = _T::vmi_to_vmf(i_cmp_res);
        vf_type d1= s * 2.0 + s * s;
        vf_type d2 = _T::sel(cmp_res, d1, s);
        k_i -= vi_type(1);
        s = d2;
    } while (1);
    // const vf_type two(2.0);
    // for (int i=0; i<k_i; ++i)
    //    s = mul_pwr2(s, two) + sqr(s);
    if (exp_m1 == false) {
        s += vf_type(1.0);
    }
    vi_type mi= _T::cvt_f_to_i(m2);
    // scale back
    vf_type res= ldexp(s, mi);
    if (exp_m1 == true) {
        vf_type scale=ldexp(vf_type(1.0), mi);
        res += (scale - vf_type(1.0));
    }
    if (any_of_d_large) {
        vf_type tres(_T::sel(d_large, res*res, res));
        res=tres;
    }
    return res;
#else
    using ctbl = impl::d_real_constants<dvf_type, double>;

    const double k(512.0);
    const int k_i(9);
    const vf_type inv_k(1.0/k);

    vf_type m2= rint(vf_type(d * ctbl::m_1_ln2.h()));
    vf_type r= (d - ctbl::m_ln2.h()*m2) * inv_k;
    vf_type m=m2;

    vf_type s = ctbl::inv_fac[9].h();
    // s = s * r + ctbl::inv_fac[8];
    // s = s * r + ctbl::inv_fac[7];
    // s = s * r + ctbl::inv_fac[6];
    // s = s * r + ctbl::inv_fac[5];
    // s = s * r + ctbl::inv_fac[4];
    // s = s * r + ctbl::inv_fac[3];
    for (unsigned int i=8; i!=2; --i)
        s = s*r + ctbl::inv_fac[i].h();
    s = s * r + vf_type(0.5);
    s = s * r + vf_type(1.0);
    s = s * r;

    // scale back the 1/k reduced value
    const vf_type two(2.0);
    for (int i=0; i<k_i; ++i)
        s = s * two + s * s;
    s += vf_type(1.0);

    // scale back
    vi_type mi= _T::cvt_f_to_i(m);
    vf_type res(my_type::ldexp(s, mi));
    return res;
#endif
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
exp2_k2(const dvf_type& d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    dvf_type d2=dvf_type(ctbl::m_ln2) * d;
    return exp_k2(d2);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_exp2_k(const vf_type& d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type d2=ctbl::m_ln2.h() * d;
    return native_exp_k(d2);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
exp10_k2(const dvf_type& d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    dvf_type d10=dvf_type(ctbl::m_ln10) * d;
    return exp_k2(d10);
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_exp10_k(const vf_type& d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type d10=ctbl::m_ln10.h() * d;
    return native_exp_k(d10);
}


template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::dvf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::
func_core<double, _T>::
reduce_trig_arg_k(const vf_type& d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    constexpr double large_arg(2.0e8);
    vmf_type v_large_arg(vf_type(large_arg) < abs(d));
    // small argument reduction
    // reduce by pi half
    dvf_type qf(rint(d * dvf_type(ctbl::m_2_pi)));
    dvf_type d0(d -
                qf * vf_type(ctbl::m_pi_2.h()) -
                qf * vf_type(ctbl::m_pi_2.l()));
    vi_type q(_T::cvt_f_to_i(qf.h()+qf.l()));

    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(double)) v_d {
            double _sc[N];
        } tf, d0_l, d0_h;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, d);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0.l());
        mem<vf_type>::store(d0_h._sc, d0.h());
        for (std::size_t i=0; i<N; ++i) {
            if (std::fabs(tf._sc[i]) >= large_arg) {
                double y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i],
                                                   y);
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
const
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::m_sin_c_k2[]= {
    // +1/21!
    dvf_type(  1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
    // -1/19!
    dvf_type( -8.2206352466243294955370e-18, -2.2141894119604265363725e-34),
    // +1/17!
    dvf_type(  2.8114572543455205981105e-15,  1.6508842730861432599403e-31),
    // -1/15!
    dvf_type( -7.6471637318198164055138e-13, -7.0387287773345300106125e-30),
    // +1/13!
    dvf_type(  1.6059043836821613340863e-10,  1.2585294588752098052117e-26),
    // -1/11!
    dvf_type( -2.5052108385441720223866e-08,  1.4488140709359119660293e-24),
    // +1/9!
    dvf_type(  2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
    // -1/7!
    dvf_type( -1.9841269841269841252632e-04, -1.7209558293420705286779e-22),
    // +1/5!
    dvf_type(  8.3333333333333332176851e-03,  1.1564823173178713802252e-19),
    // -1/3!
    dvf_type( -1.6666666666666665741481e-01, -9.2518585385429706566156e-18)
};

template <typename _T>
const
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::m_cos_c_k2[]= {
    // -1/22!
    dvf_type( -8.8967913924505740778892e-22,  7.9114026148723762170263e-38),
    // +1/20!
    dvf_type(  4.1103176233121648440650e-19,  1.4412973378659527149817e-36),
    // -1/18!
    dvf_type( -1.5619206968586225271148e-16, -1.1910679660273754002389e-32),
    // +1/16!
    dvf_type(  4.7794773323873852534462e-14,  4.3992054858340812566328e-31),
    // -1/14!
    dvf_type( -1.1470745597729724507297e-11, -2.0655512752830745424540e-28),
    // +1/12!
    dvf_type(  2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
    // -1/10!
    dvf_type( -2.7557319223985888275786e-07, -2.3767714622250297318518e-23),
    // +1/8!
    dvf_type(  2.4801587301587301565790e-05,  2.1511947866775881608473e-23),
    // -1/6!
    dvf_type( -1.3888888888888889418943e-03,  5.3005439543735770590566e-20),
    // +1/4!
    dvf_type(  4.1666666666666664353702e-02,  2.3129646346357426641539e-18)
};


template <typename _T>
__attribute__((flatten, noinline))
void
cftal::math::func_core<double, _T>::
sin_cos_k(vf_type d, std::size_t n,
          vf_type* ps, vf_type* pc)
{
    // using ctbl = impl::d_real_constants<dvf_type, double>;
    std::pair<dvf_type, vi_type> rr(reduce_trig_arg_k(d));
    const vi_type& q= rr.second;
    const dvf_type& dh= rr.first;

    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));

    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // calculate sin + cos
    dvf_type x= sqr(dh);
    dvf_type s, c;

    s = m_sin_c_k2[0];
    for (unsigned i=0; i<10; ++i)
        s = s * x + m_sin_c_k2[i];
    s = s * x + vf_type(1.0);
    s = s * dh;

    c= m_cos_c_k2[0];
    for (unsigned i=0; i<10; ++i)
        c = c * x + m_cos_c_k2[i];
    c = c * x - vf_type(0.5);
    c = c * x + vf_type(1.0);
    // swap sin/cos if q & 1
    dvf_type rsin(
        _T::sel(q_and_1_f, c.h(), s.h()),
        _T::sel(q_and_1_f, c.l(), s.l()));
    dvf_type rcos(
        _T::sel(q_and_1_f, s.h(), c.h()),
        _T::sel(q_and_1_f, s.l(), c.l()));
    // swap signs
    if (ps != nullptr) {
        vf_type fs = _T::sel(q_and_2_f, vf_type(-1.0), vf_type(1.0));
        ps[0] = rsin.h() * fs;
        if (n > 1)
            ps[1] = rsin.l() * fs;
    }
    if (pc != nullptr) {
        vmf_type mt = q_and_2_f ^ q_and_1_f;
        vf_type fc =  _T::sel(mt, vf_type(-1.0), vf_type(1.0));
        pc[0] = rcos.h() * fc;
        if (n > 1)
            pc[1] = rcos.l() * fc;
    }
}


template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::vf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::func_core<double, _T>::
native_reduce_trig_arg_k(const vf_type& d)
{
#define PI4_A 0.78539816290140151978
#define PI4_B 4.9604678871439933374e-10
#define PI4_C 1.1258708853173288931e-18
#define PI4_D 1.7607799325916000908e-27

    constexpr double large_arg(2.0e8);
    vmf_type v_large_arg(vf_type(large_arg) < abs(d));

    vf_type qf(rint(vf_type(d * (2 * M_1_PI))));
    vi_type q(_T::cvt_f_to_i(qf));

    vf_type d0(d);
    d0 = d0 - qf * (2*PI4_A);
    d0 = d0 - qf * (2*PI4_B);
    d0 = d0 - qf * (2*PI4_C);
    d0 = d0 - qf * (2*PI4_D);

#undef PI4_A
#undef PI4_B
#undef PI4_C
#undef PI4_C

    if (any_of(v_large_arg)) {
        // reduce the large arguments
        constexpr std::size_t N=_T::NVF();
        constexpr std::size_t NI=_T::NVI();
        struct alignas(N*sizeof(double)) v_d {
            double _sc[N];
        } tf, d0_l;
        struct alignas(NI*sizeof(int)) v_i {
            int32_t _sc[NI];
        } ti;
        mem<vf_type>::store(tf._sc, d);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0);
        for (std::size_t i=0; i<N; ++i) {
            if (std::fabs(tf._sc[i]) >= large_arg) {
                double y[2];
                ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i],
                                                   y);
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
cftal::math::func_core<double, _T>::
native_sin_cos_k(const vf_type& d, vf_type* ps, vf_type* pc)
{
    std::pair<vf_type, vi_type> rq(
        native_reduce_trig_arg_k(d));
    vf_type& x= rq.first;
    const vi_type& q= rq.second;

    vf_type x2(x*x);

    vf_type s, c;
    s = 1.58938307283228937328511e-10;
    s = s * x2 - 2.50506943502539773349318e-08;
    s = s * x2 + 2.75573131776846360512547e-06;
    s = s * x2 - 0.000198412698278911770864914;
    s = s * x2 + 0.0083333333333191845961746;
    s = s * x2 - 0.166666666666666130709393;
    s = s * x2 + 1.0;
    s = s * x;

    c = -1.13615350239097429531523e-11;
    c = c * x2 + 2.08757471207040055479366e-09;
    c = c * x2 - 2.75573144028847567498567e-07;
    c = c * x2 + 2.48015872890001867311915e-05;
    c = c * x2 - 0.00138888888888714019282329;
    c = c * x2 + 0.0416666666666665519592062;
    c = c * x2 - 0.5;
    c = c * x2 + 1.0;

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
const
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::m_atan2_c_k2[]= {
    dvf_type( 1.0)/vf_type(45.0),
    dvf_type(-1.0)/vf_type(43.0),
    dvf_type( 1.0)/vf_type(41.0),
    dvf_type(-1.0)/vf_type(39.0),
    dvf_type( 1.0)/vf_type(37.0),
    dvf_type(-1.0)/vf_type(35.0),
    dvf_type( 1.0)/vf_type(33.0),
    dvf_type(-1.0)/vf_type(31.0),
    dvf_type( 1.0)/vf_type(29.0),
    dvf_type(-1.0)/vf_type(27.0),
    dvf_type( 1.0)/vf_type(25.0),
    dvf_type(-1.0)/vf_type(23.0),
    dvf_type( 1.0)/vf_type(21.0),
    dvf_type(-1.0)/vf_type(19.0),
    dvf_type( 1.0)/vf_type(17.0),
    dvf_type(-1.0)/vf_type(15.0),
    dvf_type( 1.0)/vf_type(13.0),
    dvf_type(-1.0)/vf_type(11.0),
    dvf_type( 1.0)/vf_type( 9.0),
    dvf_type(-1.0)/vf_type( 7.0),
    dvf_type( 1.0)/vf_type( 5.0),
    dvf_type(-1.0)/vf_type( 3.0),
};

template <typename _T>
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
atan2_k2(const dvf_type& cx, const dvf_type& cy)
{
    vmf_type f_x_lt_z(cx.h() < vf_type(0));
    vmi_type i_x_lt_z(_T::vmf_to_vmi(f_x_lt_z));
    vi_type q(_T::sel(i_x_lt_z, vi_type(-2), vi_type(0)));
    dvf_type x(_T::sel(f_x_lt_z, -cx.h(), cx.h()),
               _T::sel(f_x_lt_z, -cx.l(), cx.l()));

    vmf_type f_y_gt_x(cy > x);
    vmi_type i_y_gt_x(_T::vmf_to_vmi(f_y_gt_x));

    q += _T::sel(i_y_gt_x, vi_type(1), vi_type(0));

    // vf_type y = _T::sel(mf, -x, cy);
    dvf_type y(_T::sel(f_y_gt_x, -(x.h()), cy.h()),
               _T::sel(f_y_gt_x, -(x.l()), cy.l()));
    // x = _T::sel(mf, cy, x);
    x = dvf_type(_T::sel(f_y_gt_x, cy.h(), x.h()),
                 _T::sel(f_y_gt_x, cy.l(), x.l()));

    dvf_type s(y / x);
    dvf_type t(sqr(s));

    const std::size_t N= sizeof(m_atan2_c_k2)/sizeof(m_atan2_c_k2[0]);
    dvf_type u(m_atan2_c_k2[0]);
    for (std::size_t i=1; i<N; ++i) {
        u = u * t + m_atan2_c_k2[i];
    }

    t = u * t * s  + s;

    using ctbl=impl::d_real_constants<dvf_type, double>;
    t = _T::cvt_i_to_f(q) * ctbl::m_pi_2 + t;
    return t;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_atan2_k(const vf_type& x, const vf_type& y)
{
    return 0.0;
}

#if 0
#if 0
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
    // 0.693147180559945286226764, 2.319046813846299558417771e-17
    6.931471805599452862e-01, 2.319046813846299558e-17);
#endif

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
    6.9314718055994528622676e-01, 2.3190468138462995584178e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln10(
    // 2.3025850929940459010936e+00, -2.1707562233822493507613e-16);
    2.3025850929940454570044e+00,  2.2701358751183765644142e-16);

#if 0
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2_low(
    5.707708438416212066e-34, -3.582432210601811423e-50);
#endif

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln2(
    _T(1.0) / _T( 6.931471805599452862e-01, 2.319046813846299558e-17));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi2(
    6.283185307179586232e+00, 2.449293598294706414e-16);


template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi2(
    _T(1.0) / _T(6.283185307179586232e+00, 2.449293598294706414e-16));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi(
    3.141592653589793116e+00, 1.224646799147353207e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi(
    _T(1.0) / _T(3.141592653589793116e+00, 1.224646799147353207e-16));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_2(
    1.570796326794896558e+00, 6.123233995736766036e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_2_pi(
    _T(1.0) / _T(1.570796326794896558e+00,
                 6.123233995736766036e-17));


template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_4(
    7.853981633974482790e-01, 3.061616997868383018e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_4_pi(
    _T(1.0) / _T(7.853981633974482790e-01, 3.061616997868383018e-17));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
inv_fac[MAX_FAC+1]= {
    _T( 1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
    _T( 1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
    _T( 5.0000000000000000000000e-01,  0.0000000000000000000000e+00),
    _T( 1.6666666666666665741481e-01,  9.2518585385429706566156e-18),
    _T( 4.1666666666666664353702e-02,  2.3129646346357426641539e-18),
    _T( 8.3333333333333332176851e-03,  1.1564823173178713802252e-19),
    _T( 1.3888888888888889418943e-03, -5.3005439543735770590566e-20),
    _T( 1.9841269841269841252632e-04,  1.7209558293420705286779e-22),
    _T( 2.4801587301587301565790e-05,  2.1511947866775881608473e-23),
    _T( 2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
    _T( 2.7557319223985888275786e-07,  2.3767714622250297318518e-23),
    _T( 2.5052108385441720223866e-08, -1.4488140709359119660293e-24),
    _T( 2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
    _T( 1.6059043836821613340863e-10,  1.2585294588752098052117e-26),
    _T( 1.1470745597729724507297e-11,  2.0655512752830745424540e-28),
    _T( 7.6471637318198164055138e-13,  7.0387287773345300106125e-30),
    _T( 4.7794773323873852534462e-14,  4.3992054858340812566328e-31),
    _T( 2.8114572543455205981105e-15,  1.6508842730861432599403e-31),
    _T( 1.5619206968586225271148e-16,  1.1910679660273754002389e-32),
    _T( 8.2206352466243294955370e-18,  2.2141894119604265363725e-34),
    _T( 4.1103176233121648440650e-19,  1.4412973378659527149817e-36),
    _T( 1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
    _T( 8.8967913924505740778892e-22, -7.9114026148723762170263e-38),
    _T( 3.8681701706306841261487e-23, -8.8431776554823422165616e-40),
    _T( 1.6117375710961183858953e-24, -3.6846573564509766032865e-41),
    _T( 6.4469502843844735894989e-26, -1.9330404233703468010728e-42),
    _T( 2.4795962632247975896123e-27, -1.2953730964765228775764e-43),
    _T( 9.1836898637955460053942e-29,  1.4303150396787318912725e-45),
    _T( 3.2798892370698377589766e-30,  1.5117542744029878689714e-46),
    _T( 1.1309962886447715881757e-31,  1.0498015412959506023854e-47),
    _T( 3.7699876288159053851494e-33,  2.5870347832750323834849e-49)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
_2_over_i[MAX_2_OVER_I+1]= {
    _T( 2.0000000000000000000000e+00,  0.0000000000000000000000e+00),
    _T( 2.0000000000000000000000e+00,  0.0000000000000000000000e+00),
    _T( 1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
    _T( 6.6666666666666662965923e-01,  3.7007434154171882626462e-17),
    _T( 5.0000000000000000000000e-01,  0.0000000000000000000000e+00),
    _T( 4.0000000000000002220446e-01, -2.2204460492503132041068e-17),
    _T( 3.3333333333333331482962e-01,  1.8503717077085941313231e-17),
    _T( 2.8571428571428569842539e-01,  1.5860328923216521125627e-17),
    _T( 2.5000000000000000000000e-01,  0.0000000000000000000000e+00),
    _T( 2.2222222222222220988641e-01,  1.2335811384723960875487e-17),
    _T( 2.0000000000000001110223e-01, -1.1102230246251566020534e-17),
    _T( 1.8181818181818182322829e-01, -5.0464682937507116874478e-18),
    _T( 1.6666666666666665741481e-01,  9.2518585385429706566156e-18),
    _T( 1.5384615384615385469402e-01, -8.5401771125012046311799e-18),
    _T( 1.4285714285714284921269e-01,  7.9301644616082605628134e-18),
    _T( 1.3333333333333333148296e-01,  1.8503717077085942083603e-18),
    _T( 1.2500000000000000000000e-01,  0.0000000000000000000000e+00),
    _T( 1.1764705882352941013202e-01,  1.6326809185664066544356e-18),
    _T( 1.1111111111111110494321e-01,  6.1679056923619804377437e-18),
    _T( 1.0526315789473683626198e-01,  5.8432790769745077831256e-18),
    _T( 1.0000000000000000555112e-01, -5.5511151231257830102669e-18),
    _T( 9.5238095238095232808462e-02,  5.2867763077388403752089e-18),
    _T( 9.0909090909090911614143e-02, -2.5232341468753558437239e-18),
    _T( 8.6956521739130432369080e-02,  2.4135283144025141513234e-18),
    _T( 8.3333333333333328707404e-02,  4.6259292692714853283078e-18),
    _T( 8.0000000000000001665335e-02, -1.6653345369377347490057e-18),
    _T( 7.6923076923076927347012e-02, -4.2700885562506023155900e-18),
    _T( 7.4074074074074069962137e-02,  4.1119371282413202918292e-18),
    _T( 7.1428571428571424606346e-02,  3.9650822308041302814067e-18),
    _T( 6.8965517241379309387739e-02,  9.5708881433203148708292e-19),
};
#else
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
         6.9314718055994528622676e-01,  2.3190468138462995584178e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln2(
         1.4426950408889633870047e+00,  2.0355273740931033111021e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln10(
         2.3025850929940454570044e+00,  2.2701358751183765644142e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi(
         3.1415926535897931159980e+00,  1.2246467991473532071738e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi2(
         6.2831853071795862319959e+00,  2.4492935982947064143475e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_2(
         1.5707963267948965579990e+00,  6.1232339957367660358688e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_4(
         7.8539816339744827899949e-01,  3.0616169978683830179344e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi(
         3.1830988618379069121644e-01, -1.9678676675182485881895e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_2_pi(
         6.3661977236758138243289e-01, -3.9357353350364971763790e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_4_pi(
         1.2732395447351627648658e+00, -7.8714706700729943527581e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
inv_fac[MAX_FAC+1]= {
        _T(  1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  5.0000000000000000000000e-01,  0.0000000000000000000000e+00),
        _T(  1.6666666666666665741481e-01,  9.2518585385429706566156e-18),
        _T(  4.1666666666666664353702e-02,  2.3129646346357426641539e-18),
        _T(  8.3333333333333332176851e-03,  1.1564823173178713802252e-19),
        _T(  1.3888888888888889418943e-03, -5.3005439543735770590566e-20),
        _T(  1.9841269841269841252632e-04,  1.7209558293420705286779e-22),
        _T(  2.4801587301587301565790e-05,  2.1511947866775881608473e-23),
        _T(  2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
        _T(  2.7557319223985888275786e-07,  2.3767714622250297318518e-23),
        _T(  2.5052108385441720223866e-08, -1.4488140709359119660293e-24),
        _T(  2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
        _T(  1.6059043836821613340863e-10,  1.2585294588752098052117e-26),
        _T(  1.1470745597729724507297e-11,  2.0655512752830745424540e-28),
        _T(  7.6471637318198164055138e-13,  7.0387287773345300106125e-30),
        _T(  4.7794773323873852534462e-14,  4.3992054858340812566328e-31),
        _T(  2.8114572543455205981105e-15,  1.6508842730861432599403e-31),
        _T(  1.5619206968586225271148e-16,  1.1910679660273754002389e-32),
        _T(  8.2206352466243294955370e-18,  2.2141894119604265363725e-34),
        _T(  4.1103176233121648440650e-19,  1.4412973378659527149817e-36),
        _T(  1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
        _T(  8.8967913924505740778892e-22, -7.9114026148723762170263e-38),
        _T(  3.8681701706306841261487e-23, -8.8431776554823438478877e-40),
        _T(  1.6117375710961183858953e-24, -3.6846573564509766032865e-41),
        _T(  6.4469502843844735894989e-26, -1.9330404233703464824544e-42),
        _T(  2.4795962632247975896123e-27, -1.2953730964765228775764e-43),
        _T(  9.1836898637955460053942e-29,  1.4303150396787322024232e-45),
        _T(  3.2798892370698377589766e-30,  1.5117542744029878689714e-46),
        _T(  1.1309962886447715881757e-31,  1.0498015412959506023854e-47),
        _T(  3.7699876288159053851494e-33,  2.5870347832750323834849e-49)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
_2_over_i[MAX_2_OVER_I+1]= {
        _T(  2.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  2.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  6.6666666666666662965923e-01,  3.7007434154171882626462e-17),
        _T(  5.0000000000000000000000e-01,  0.0000000000000000000000e+00),
        _T(  4.0000000000000002220446e-01, -2.2204460492503132041068e-17),
        _T(  3.3333333333333331482962e-01,  1.8503717077085941313231e-17),
        _T(  2.8571428571428569842539e-01,  1.5860328923216521125627e-17),
        _T(  2.5000000000000000000000e-01,  0.0000000000000000000000e+00),
        _T(  2.2222222222222220988641e-01,  1.2335811384723960875487e-17),
        _T(  2.0000000000000001110223e-01, -1.1102230246251566020534e-17),
        _T(  1.8181818181818182322829e-01, -5.0464682937507116874478e-18),
        _T(  1.6666666666666665741481e-01,  9.2518585385429706566156e-18),
        _T(  1.5384615384615385469402e-01, -8.5401771125012046311799e-18),
        _T(  1.4285714285714284921269e-01,  7.9301644616082605628134e-18),
        _T(  1.3333333333333333148296e-01,  1.8503717077085942083603e-18),
        _T(  1.2500000000000000000000e-01,  0.0000000000000000000000e+00),
        _T(  1.1764705882352941013202e-01,  1.6326809185664066544356e-18),
        _T(  1.1111111111111110494321e-01,  6.1679056923619804377437e-18),
        _T(  1.0526315789473683626198e-01,  5.8432790769745077831256e-18),
        _T(  1.0000000000000000555112e-01, -5.5511151231257830102669e-18),
        _T(  9.5238095238095232808462e-02,  5.2867763077388403752089e-18),
        _T(  9.0909090909090911614143e-02, -2.5232341468753558437239e-18),
        _T(  8.6956521739130432369080e-02,  2.4135283144025141513234e-18),
        _T(  8.3333333333333328707404e-02,  4.6259292692714853283078e-18),
        _T(  8.0000000000000001665335e-02, -1.6653345369377347490057e-18),
        _T(  7.6923076923076927347012e-02, -4.2700885562506023155900e-18),
        _T(  7.4074074074074069962137e-02,  4.1119371282413202918292e-18),
        _T(  7.1428571428571424606346e-02,  3.9650822308041302814067e-18),
        _T(  6.8965517241379309387739e-02,  9.5708881433203148708292e-19),
        _T(  6.6666666666666665741481e-02,  9.2518585385429710418016e-19)
};

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_ln2(
         6.9314718055994528622676e-01,  2.3190468138462995584178e-17,  5.7077084384162120657770e-34);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_1_ln2(
         1.4426950408889633870047e+00,  2.0355273740931033111021e-17, -1.0614659956117257872617e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_ln10(
         2.3025850929940459010936e+00, -2.1707562233822493507613e-16, -9.9842624544657765701194e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_pi(
         3.1415926535897931159980e+00,  1.2246467991473532071738e-16, -2.9947698097183396658870e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_pi2(
         6.2831853071795862319959e+00,  2.4492935982947064143475e-16, -5.9895396194366793317740e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_pi_2(
         1.5707963267948965579990e+00,  6.1232339957367660358688e-17, -1.4973849048591698329435e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_pi_4(
         7.8539816339744827899949e-01,  3.0616169978683830179344e-17, -7.4869245242958491647175e-34);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_1_pi(
         3.1830988618379069121644e-01, -1.9678676675182485881895e-17, -1.0721436282893004003290e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_2_pi(
         6.3661977236758138243289e-01, -3.9357353350364971763790e-17, -2.1442872565786008006580e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::m_4_pi(
         1.2732395447351627648658e+00, -7.8714706700729943527581e-17, -4.2885745131572016013160e-33);

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::
inv_fac[MAX_FAC+1]= {
        _T(  1.0000000000000000000000e+00,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  1.0000000000000000000000e+00,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  5.0000000000000000000000e-01,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  1.6666666666666665741481e-01,  9.2518585385429706566156e-18,  5.1358131850326286563877e-34),
        _T(  4.1666666666666664353702e-02,  2.3129646346357426641539e-18,  1.2839532962581571640969e-34),
        _T(  8.3333333333333332176851e-03,  1.1564823173178713802252e-19,  1.6049416203226965219403e-36),
        _T(  1.3888888888888889418943e-03, -5.3005439543735770590566e-20, -1.7386867553495877595621e-36),
        _T(  1.9841269841269841252632e-04,  1.7209558293420705286779e-22,  1.4926912391394127072370e-40),
        _T(  2.4801587301587301565790e-05,  2.1511947866775881608473e-23,  1.8658640489242658840463e-41),
        _T(  2.7557319223985892510951e-06, -1.8583932740464720810392e-22,  8.4917546048819928700866e-39),
        _T(  2.7557319223985888275786e-07,  2.3767714622250297318518e-23, -3.2631889033408829436975e-40),
        _T(  2.5052108385441720223866e-08, -1.4488140709359119660293e-24,  2.0426735146714454589097e-41),
        _T(  2.0876756987868100186555e-09, -1.2073450591132599716911e-25,  1.7022279288928710033458e-42),
        _T(  1.6059043836821613340863e-10,  1.2585294588752098052117e-26, -5.3133460276298503069446e-43),
        _T(  1.1470745597729724507297e-11,  2.0655512752830745424540e-28,  6.8890792324666460329027e-45),
        _T(  7.6471637318198164055138e-13,  7.0387287773345300106125e-30, -7.8275392771625834452004e-48),
        _T(  4.7794773323873852534462e-14,  4.3992054858340812566328e-31, -4.8922120482266146532503e-49),
        _T(  2.8114572543455205981105e-15,  1.6508842730861432599403e-31, -2.8777717930744791798661e-50),
        _T(  1.5619206968586225271148e-16,  1.1910679660273754002389e-32, -4.5775060596299832341612e-49),
        _T(  8.2206352466243294955370e-18,  2.2141894119604265363725e-34, -1.5089140237741989707211e-50),
        _T(  4.1103176233121648440650e-19,  1.4412973378659527149817e-36, -5.2856275487898120830271e-53),
        _T(  1.9572941063391262595198e-20, -1.3643503830087908487197e-36,  1.3392348251125064230801e-53),
        _T(  8.8967913924505740778892e-22, -7.9114026148723762170263e-38, -3.1877976790570933267487e-54),
        _T(  3.8681701706306841261487e-23, -8.8431776554823438478877e-40,  3.8718157106173246717527e-56),
        _T(  1.6117375710961183858953e-24, -3.6846573564509766032865e-41,  1.6132565460905519465636e-57),
        _T(  6.4469502843844735894989e-26, -1.9330404233703464824544e-42, -1.5213023807039144171803e-58),
        _T(  2.4795962632247975896123e-27, -1.2953730964765228775764e-43,  6.4033901598499624050454e-60),
        _T(  9.1836898637955460053942e-29,  1.4303150396787322024232e-45, -8.5512267746505047994753e-62),
        _T(  3.2798892370698377589766e-30,  1.5117542744029878689714e-46,  8.0585177195197159285221e-63),
        _T(  1.1309962886447715881757e-31,  1.0498015412959506023854e-47, -4.3461509293977951762205e-64),
        _T(  3.7699876288159053851494e-33,  2.5870347832750323834849e-49,  3.2378900274256399861937e-66)
};

template <class _T>
const _T
cftal::math::impl::t_real_constants<_T, double>::
_2_over_i[MAX_2_OVER_I+1]= {
        _T(  2.0000000000000000000000e+00,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  2.0000000000000000000000e+00,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  1.0000000000000000000000e+00,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  6.6666666666666662965923e-01,  3.7007434154171882626462e-17,  2.0543252740130514625551e-33),
        _T(  5.0000000000000000000000e-01,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  4.0000000000000002220446e-01, -2.2204460492503132041068e-17,  1.2325951644078310143786e-33),
        _T(  3.3333333333333331482962e-01,  1.8503717077085941313231e-17,  1.0271626370065257312775e-33),
        _T(  2.8571428571428569842539e-01,  1.5860328923216521125627e-17,  8.8042511743416491252361e-34),
        _T(  2.5000000000000000000000e-01,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  2.2222222222222220988641e-01,  1.2335811384723960875487e-17,  6.8477509133768382085169e-34),
        _T(  2.0000000000000001110223e-01, -1.1102230246251566020534e-17,  6.1629758220391550718930e-34),
        _T(  1.8181818181818182322829e-01, -5.0464682937507116874478e-18,  1.4006763231907170229173e-34),
        _T(  1.6666666666666665741481e-01,  9.2518585385429706566156e-18,  5.1358131850326286563877e-34),
        _T(  1.5384615384615385469402e-01, -8.5401771125012046311799e-18,  4.7407506323378115937639e-34),
        _T(  1.4285714285714284921269e-01,  7.9301644616082605628134e-18,  4.4021255871708245626180e-34),
        _T(  1.3333333333333333148296e-01,  1.8503717077085942083603e-18,  2.5679065925163144351044e-35),
        _T(  1.2500000000000000000000e-01,  0.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T(  1.1764705882352941013202e-01,  1.6326809185664066544356e-18,  2.2657999345732186192098e-35),
        _T(  1.1111111111111110494321e-01,  6.1679056923619804377437e-18,  3.4238754566884191042585e-34),
        _T(  1.0526315789473683626198e-01,  5.8432790769745077831256e-18,  3.2436714852837654671922e-34),
        _T(  1.0000000000000000555112e-01, -5.5511151231257830102669e-18,  3.0814879110195775359465e-34),
        _T(  9.5238095238095232808462e-02,  5.2867763077388403752089e-18,  2.9347503914472163750787e-34),
        _T(  9.0909090909090911614143e-02, -2.5232341468753558437239e-18,  7.0033816159535851145864e-35),
        _T(  8.6956521739130432369080e-02,  2.4135283144025141513234e-18,  6.6988867630860375638285e-35),
        _T(  8.3333333333333328707404e-02,  4.6259292692714853283078e-18,  2.5679065925163143281939e-34),
        _T(  8.0000000000000001665335e-02, -1.6653345369377347490057e-18, -6.1629758220391548580718e-35),
        _T(  7.6923076923076927347012e-02, -4.2700885562506023155900e-18,  2.3703753161689057968819e-34),
        _T(  7.4074074074074069962137e-02,  4.1119371282413202918292e-18,  2.2825836377922794028390e-34),
        _T(  7.1428571428571424606346e-02,  3.9650822308041302814067e-18,  2.2010627935854122813090e-34),
        _T(  6.8965517241379309387739e-02,  9.5708881433203148708292e-19,  1.3282275478532660871230e-35),
        _T(  6.6666666666666665741481e-02,  9.2518585385429710418016e-19,  1.2839532962581572175522e-35)
};

#endif

// Local Variables:
// mode: c++
// end:
#endif
