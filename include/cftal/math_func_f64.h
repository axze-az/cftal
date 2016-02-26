#if !defined (__MATH_FUNC_F64_H__)
#define __MATH_FUNC_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math_common.h>
#include <cftal/math_impl_d_real_constants_f64.h>
#include <cftal/mem.h>
#include <cmath>
#include <iostream>

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

            static tvf_type
            exp_k3(const tvf_type& tvf);

            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static std::pair<dvf_type, vi_type>
            reduce_trig_arg_k(arg_t<vf_type> x);
            // core sine, cosine calculation, n determines the
            // the number of result components to store into s[0..n1)
            // and c[0..n)
            static void
            sin_cos_k(arg_t<vf_type> v,
                      std::size_t n,
                      vf_type* s, vf_type* c);
            // argument reduction for all trigonometric
            // functions, reduction by %pi/2, the low bits
            // of multiple of %pi/2 is returned in the
            // second part of the return type
            static std::pair<vf_type, vi_type>
            native_reduce_trig_arg_k(arg_t<vf_type> x);
            // core sine, cosine calculation
            static void
            native_sin_cos_k(arg_t<vf_type> x,
                             vf_type* s, vf_type* c);

            // cofficients for atan2
            static const dvf_type m_atan2_c_k2[];

            // atan2 kernel
            static dvf_type
            atan2_k2(arg_t<vf_type> xh,
                     arg_t<vf_type> xl,
                     arg_t<vf_type> yh,
                     arg_t<vf_type> yl,
                     bool calc_atan2);

            // native atan2 kernel
            static vf_type
            native_atan2_k(arg_t<vf_type> x,
                           arg_t<vf_type> y);

            static vf_type
            pow2i(arg_t<vi_type> vi);
            static vf_type
            ldexp(arg_t<vf_type> x,
                  arg_t<vi_type> e);
            static vf_type
            frexp(arg_t<vf_type> x, vi_type* e);

            static vi_type
            ilogbp1(arg_t<vf_type> x);
            static vi_type
            ilogb(arg_t<vf_type> vf);
        };

    } // end math
} // end cftal

template <typename _T>
inline
typename
cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
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
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
ldexp(arg_t<vf_type> xc, arg_t<vi_type> n)
{
    vf_type x=xc;
#if 1
    vi_type mh=_T::extract_high_word(x);
    vi_type ml=_T::extract_low_word(x);
    vi_type xe=((mh>>20) & 0x7ff);

    vmi_type is_not_zero=vi_type((mh << 1) | ml) != vi_type(0);
    vmi_type is_denom= (xe == vi_type(0)) & is_not_zero;
        
    if (any_of(is_denom)) {
        // subnormal handling
        vf_type sx=x*vf_type(0x1.0p+53);
        vi_type sh=_T::extract_high_word(sx);
        vi_type sl=_T::extract_low_word(sx);
        vi_type se=((sh>>20) & 0x7ff) - vi_type(53);
        // vi_type rl=ml, rh=mh;
        xe = _T::sel(is_denom, se, xe);
        ml= _T::sel(is_denom, sl, ml);
        mh= _T::sel(is_denom, sh, mh);
    }
        
    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi_type nn= min(vi_type(4096), max(n, vi_type(-4096)));
    vi_type re= xe + nn;
    
    // 3 cases exist:
    // 0 < re < 0x7ff normal result
    //     re >= 0x7ff inf result (overflow)
    //     re <= 0 subnormal or 0 (undeflow)

    // clear exponent bits from mh
    mh &= vi_type(~0x7ff00000);

    // high part of mantissa for normal results:
    vi_type mhn= mh | ((re & vi_type(0x7ff)) << 20);
    vf_type r= _T::combine_words(ml, mhn);

    // overflow handling
    vmi_type i_is_inf = re > vi_type(0x7fe);
    vmf_type f_is_inf = _T::vmi_to_vmf(i_is_inf);
    vf_type r_inf = copysign(vf_type(_T::pinf()), x);
    r = _T::sel(f_is_inf, r_inf, r);

    // underflow handling
    vmi_type i_is_near_z = re < vi_type (1);
    if (any_of(i_is_near_z)) {
        // create m*0x1.0p-1022
        vi_type mhu= mh | vi_type(1<<20);
        vf_type r_u= _T::combine_words(ml, mhu);
        // create a scaling factor
        vi_type ue= max(vi_type(re + (_T::bias-1)), vi_type(1));
        // avoid overflows
        vf_type s_u= _T::insert_exp(ue);
        r_u *= s_u;
        vmf_type f_is_near_z = _T::vmi_to_vmf(i_is_near_z);
        r = _T::sel(f_is_near_z, r_u, r);
    }
    // handle special cases:
    r = _T::sel(isinf(x) | isnan(x) | (x==vf_type(0.0)),
                x, r);
    return r;
#else
    vi_type sgn = n>>31;
    // division by 2^k: shift right rounds down, correct it for
    // negative numbers, we divde ve by 4
    vi_type m= (n + (3 & sgn)) >>2;
    vi_type q = n - (m<<2);

    m += 0x3ff;
    m = max(vi_type(0), m);
    m = min(vi_type(0x7ff), m);
#if 1
    using fct_t = func_constants<double>;
    vmf_type is_zero= x == vf_type(0);
    vmf_type is_denom= (abs(x) <= fct_t::max_denormal) & (~is_zero);

    if (any_of(is_denom)) {
        vf_type rs= x* vf_type(0x1.0p53);
        x = _T::sel(is_denom, rs, x);
    }
#endif
    q += 0x3ff;
    vf_type fq(_T::insert_exp(q));
    // multiply with the remainder first to retain precision of
    // subnormal results
    vf_type r = fq * x;
    // multiply with ve/4
    vf_type fm(_T::insert_exp(m));
    r *= fm;
    r *= fm;
    r *= fm;
    r *= fm;
#if 1
    if (any_of(is_denom)) {
        vf_type rs= r* vf_type(0x1.0p-53);
        r = _T::sel(is_denom, rs, r);
    }
#else
    vmf_type is_zero= x == vf_type(0);
#endif
    r = _T::sel(is_zero, x, r);
    return r;
#endif
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp(arg_t<vf_type> vd, vi_type* ve)
{
    // normal numbers:
    vi_type hi_word(_T::extract_high_word(vd));
    vi_type lo_word(_T::extract_low_word(vd));

    vi_type value_head(hi_word & vi_type(0x7fffffff));

    vmi_type is_inf_nan_zero(
        (value_head >= vi_type(0x7ff00000)) |
        (vi_type(value_head| lo_word)==vi_type(0)));
    vmi_type is_denom((value_head < 0x00100000) &
                      ~is_inf_nan_zero);

    // exponent:
    vi_type e=(value_head >> 20);

    // denormals
    if (any_of(is_denom)) {
        // first multiply with 2^53
        const vf_type two53=0x1.p53;
        vf_type vden(two53 * vd);
        vi_type hden(_T::extract_high_word(vden));
        vi_type lden(_T::extract_low_word(vden));
        vi_type value_head_den(hden & vi_type(0x7fffffff));
        vi_type eden((value_head_den>>20) - vi_type(53));

        // select denom/normal
        e = _T::sel(is_denom, eden, e);
        hi_word = _T::sel(is_denom, hden, hi_word);
        lo_word = _T::sel(is_denom, lden, lo_word);
    }
    e -= vi_type(1022); //remove bias
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
ilogbp1(arg_t<vf_type> vd)
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
ilogb(arg_t<vf_type> d)
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
std::pair<typename cftal::math::func_core<double, _T>::dvf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::
func_core<double, _T>::
reduce_trig_arg_k(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    constexpr static const double large_arg(2.0e8);
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
__attribute__((flatten, noinline))
void
cftal::math::func_core<double, _T>::
sin_cos_k(arg_t<vf_type> d, std::size_t n,
          vf_type* ps, vf_type* pc)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
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

    s = ctbl::sin_coeff[0];
    for (unsigned i=0; i<10; ++i)
        s = s * x + dvf_type(ctbl::sin_coeff[i]);
    s = s * x + vf_type(1.0);
    s = s * dh;

    c= ctbl::cos_coeff[0];
    for (unsigned i=0; i<10; ++i)
        c = c * x + dvf_type(ctbl::cos_coeff[i]);
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
native_reduce_trig_arg_k(arg_t<vf_type> d)
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
native_sin_cos_k(arg_t<vf_type> d, vf_type* ps, vf_type* pc)
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
    dvf_type(-1.0)/vf_type(47.0),
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
atan2_k2(arg_t<vf_type> yh, arg_t<vf_type> yl,
         arg_t<vf_type> xh, arg_t<vf_type> xl,
         bool calc_atan2)
{

    using ctbl = impl::d_real_constants<d_real<double>, double>;
    dvf_type y(yh, yl);
    dvf_type x(xh, xl);
    dvf_type yp(abs(y));
    dvf_type xp(abs(x));

    dvf_type d=max(yp, xp);
    dvf_type e=min(yp, xp);
    dvf_type r=e/d;

    // reduce argument via arctan(x) = 2 * arctan(x/(1+sqrt(1-x^2)))
    vi_type k(0);
    do {
        vmf_type r_gt = r.h() > vf_type(1.0/2.0);
        if (none_of(r_gt))
            break;
        vmi_type ki= _T::vmf_to_vmi(r_gt);
        dvf_type den= sqrt(vf_type(1.0)+sqr(r)) + vf_type(1);
        dvf_type rs = r/den;
        r= dvf_type(_T::sel(r_gt, rs.h(), r.h()),
                    _T::sel(r_gt, rs.l(), r.l()));
        k += _T::sel(ki, vi_type(1), vi_type(0));
    } while (1);


    dvf_type rs=sqr(r);
    dvf_type t=rs/(vf_type(1)+rs);

    dvf_type p= impl::poly(t, ctbl::atan2_coeff);
    dvf_type at=t/r*p;

    // scale back
    vmi_type k_gt= k > vi_type(0);
    if (any_of(k_gt)) {
        vf_type scale=ldexp(vf_type(1.0), k);
        at *= scale;
    }

    // sqrt(DBL_MIN): 1.4916681462400413486582e-154
    // vmf_type r_small = r.h() < 1.4916681462400413486582e-154;
    vmf_type r_small = r.h() < 1e-16;
    dvf_type at_small = r;
    at = dvf_type(_T::sel(r_small, at_small.h(), at.h()),
                  _T::sel(r_small, at_small.l(), at.l()));

    vmf_type invert = (yp.h() > xp.h());
    // arctan (1/r) = M_PI/2 -  arctan(r) if r > 0
    // arctan (1/r) = -M_PI/2 - arctan(r) if r < 0
    dvf_type inv_at= dvf_type(ctbl::m_pi_2) - at;
    at= dvf_type(_T::sel(invert, inv_at.h(), at.h()),
                 _T::sel(invert, inv_at.l(), at.l()));
    vf_type sgn_y=copysign(vf_type(1.0), y.h());
    vf_type at_sgn=sgn_y * copysign(vf_type(1.0), x.h());
    at=mul_pwr2(at, copysign(vf_type(1.0), at_sgn));
    // at = atan(y/x);
    if (calc_atan2) {
        // atan2(y, x) = atan(x) x>0
        // atan2(y, x) = atan(x) + pi x<0 & y>=0
        // atan2(y, x) = atan(x) - pi x<0 & y <0
        // from mpfr:
        // atan2(y, x) with x<0 --> sgn_y * (PI-atan(|y/x|));
        dvf_type pi_at = dvf_type(ctbl::m_pi) - abs(at);
        pi_at = mul_pwr2(pi_at, sgn_y);
        vmf_type x_lt_z = xh < vf_type(0);
        at=dvf_type(_T::sel(x_lt_z, pi_at.h(), at.h()),
                    _T::sel(x_lt_z, pi_at.l(), at.l()));
    }
    return at;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_atan2_k(arg_t<vf_type> x, arg_t<vf_type> y)
{
    return 0.0;
}

// Local Variables:
// mode: c++
// end:
#endif
