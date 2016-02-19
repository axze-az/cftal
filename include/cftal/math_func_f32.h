#if !defined (__MATH_FUNC_F32_H__)
#define __MATH_FUNC_F32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {
    namespace math {

        namespace impl {

            template <class _T>
            struct d_real_constants<_T, float> {
                // large exp argument
                constexpr static const float
                exp_arg_large= 8.8000000000000e+01f;

                // log(x): avoid denormals
                constexpr static const float
                log_arg_small= 1.9721522630525e-31f;
                // if above factor to multiply with
                constexpr static const float
                log_arg_small_factor= 2.8147497671066e+14f;

                // 1/(i!)
                static const unsigned MAX_FAC=20;
                static const _T inv_fac[MAX_FAC+1];
                // 2/i i=0,1,2,3,4...
                static const unsigned MAX_2_OVER_I=20;
                static const _T _2_over_i[MAX_2_OVER_I+1];

                // coefficents for exp(x)
                static const unsigned MAX_EXP_COEFF=5;
                static const _T exp_coeff[MAX_EXP_COEFF];

                // table for sin -1/21! +1/19! .. -1/3! with alternating signs
                static const unsigned MAX_SIN_COEFF=5;
                static const _T sin_coeff[MAX_SIN_COEFF];
                // table for cos -1/22! +1/20! .. +1/4! with alternating signs
                static const unsigned MAX_COS_COEFF=5;
                static const _T cos_coeff[MAX_COS_COEFF];

                // table for atan2
                static const unsigned MAX_ATAN2_COEFF=13;
                static const _T atan2_coeff[MAX_ATAN2_COEFF];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_LN_2POW106
                static const _T m_ln2pow106;
                // M_LN_2POW48
                static const _T m_ln2pow48;
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

            static constexpr int32_t bias = 126;
            static constexpr int32_t e_max= 127;
            static constexpr int32_t e_min= -126;
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

            static void
            sin_cos_k(arg_t<vf_type> v,
                      std::size_t n,
                      vf_type* s, vf_type* c);

            static void
            native_sin_cos_k(arg_t<vf_type> x,
                             vf_type* s, vf_type* c);

            static tvf_type
            exp_k3(const tvf_type& tvf);

            static dvf_type
            exp_k2(arg_t<vf_type> xh,
                   arg_t<vf_type> xl,
                   bool exp_m1=false);

            static vf_type
            native_exp_k(arg_t<vf_type> v, bool exp_m1=false);

            static dvf_type
            exp2_k2(arg_t<vf_type> xh,
                    arg_t<vf_type> xl);

            static vf_type
            native_exp2_k(arg_t<vf_type> v);

            static dvf_type
            exp10_k2(arg_t<vf_type> xh,
                     arg_t<vf_type> xl);

            static vf_type
            native_exp10_k(arg_t<vf_type> v);

            static dvf_type
            log_k2(arg_t<vf_type> xh,
                   arg_t<vf_type> xl);
            
            static vf_type
            native_log_k(arg_t<vf_type> v);

            // atan2 kernel
            static dvf_type
            atan2_k2(arg_t<vf_type> xh,
                     arg_t<vf_type> xl,
                     arg_t<vf_type> yh,
                     arg_t<vf_type> yl,
                     bool calc_atan2);
        };

        template <typename _T>
        struct func<float, _T>
            : public func_common<float, _T> {
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;

            static vf_type native_sin(arg_t<vf_type> x);
            static vf_type native_cos(arg_t<vf_type> x);
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
ldexp(arg_t<vf_type> vd, arg_t<vi_type> ve)
{
    vi_type q= ve;
    vi_type m = q >> 31;
    m = (((m + q) >> 6) - m) << 4;
    q = q - (m << 2);

    m += 127;
    m = max(vi_type(0), m);
    m = min(vi_type(0xff), m);

    vf_type fm = _T::insert_exp(m);
    vf_type r = vd * fm * fm * fm * fm;
    q += 0x7f;
    // q = max(vi_type(0), q);
    // q = min(vi_type(0x7ff), q);
    vf_type fq = _T::insert_exp(q);
    r *= fq;
    r = _T::sel(vd == vf_type(0), vd, r);
    return r;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::vf_type
cftal::math::func_core<float, _T>::
frexp(arg_t<vf_type> vd, vi_type* ve)
{
    // normal numbers:
    vi_type i(_T::as_int(vd));

    vi_type value_head(i & vi_type(0x7fffffff));

    vmi_type is_inf_nan_zero((value_head >= 0x7f800000) |
                             (value_head==vi_type(0)));
    vmi_type is_denom(value_head < 0x008000000);

    // exponent:
    vi_type e((value_head >> 23) - vi_type(126));

    // denormals
    if (any_of(is_denom)) {
        // multiply with 2^25
        const vf_type two25(0x1.p25f);
        vf_type vden(two25 * vd);
        vi_type iden(_T::as_int(vden));
        vi_type value_head_den(iden & vi_type(0x7fffffff));
        vi_type eden((value_head_den>>23) - vi_type(126 +25));

        // select denom/normal
        e = _T::sel(is_denom, eden, e);
        i = _T::sel(is_denom, iden, i);
    }
    // insert exponent
    i = (i & vi_type(0x807fffff)) | vi_type(0x7e<<23);
    // interpret as float
    vf_type frc(_T::as_float(i));
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
typename cftal::math::func_core<float, _T>::vi_type
cftal::math::func_core<float, _T>::
ilogbp1(arg_t<vf_type> vd)
{
    vmf_type mf= vd < 5.421010862427522E-20f;
    vf_type d = _T::sel(mf, 1.8446744073709552E19f * vd, vd);
    vi_type q = _T::extract_exp(d);
    vmi_type mi= _T::vmf_to_vmi(mf);
    vi_type qs = _T::sel(mi, vi_type(64 + 0x7e), vi_type(0x7e));
    return q - qs;
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

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::tvf_type
cftal::math::func_core<float, _T>::
exp_k3(const tvf_type& x)
{
    dvf_type xt(x.h(), x.m());
    dvf_type r(exp_k2(xt));
    return tvf_type(r);
}

template <typename _T>
__attribute__((__flatten__, __noinline__))
typename cftal::math::func_core<float, _T>::dvf_type
cftal::math::func_core<float, _T>::
exp_k2(arg_t<vf_type> dh, arg_t<vf_type> dl, bool exp_m1)
{
#if 1
    using ctbl = impl::d_real_constants<d_real<float>, float>;

    vmf_type cmp_res;
    vmi_type i_cmp_res=vmi_type();
    vmf_type inf_nan= isinf(dh) | isnan(dh);
    vmf_type finite= ~inf_nan;
    vi_type k_i(0);

    // first reduction required because we want to use rint below
    vmf_type d_large = dh > ctbl::exp_arg_large;
    dvf_type d2=dvf_type(dh, dl);
    bool any_of_d_large = any_of(d_large);
    if (any_of_d_large) {
        dvf_type dhalf(mul_pwr2(d2, vf_type(0.5)));
        dvf_type dt(_T::sel(d_large, dhalf.h(), dh),
                    _T::sel(d_large, dhalf.l(), dl));
        d2=dt;
    }
    // remove exact powers of 2
    vf_type m2 = rint(vf_type(d2.h() * ctbl::m_1_ln2.h()));
    dvf_type r= d2 - dvf_type(ctbl::m_ln2)*m2;

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

    // calculate 1! + x^1/2!+x^2/3! .. +x^8/9!
    dvf_type s=impl::poly(r, ctbl::exp_coeff);
    // convert to s=x^1/1! + x^2/2!+x^3/3! .. +x^9/9! == expm1(r)
    s = s*r;

    // scale back the 1/k_i reduced value for expm1
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
#else
    dvf_type x(xh, xl);
    using vhpf_type = typename _T::vhpf_type;
    const std::size_t elements = _T::vhpf_per_vf();

    using hpf_traits = typename _T::hpf_traits;
    using hpf_func =
        func_core<double, hpf_traits>;

    vhpf_type vxh[elements];
    _T::vf_to_vhpf(x.h(), vxh);
    vhpf_type vxl[elements];
    _T::vf_to_vhpf(x.l(), vxl);
    // evaluate unevaluated sum
    for (std::size_t i=0; i<elements; ++i)
        vxh[i] += vxl[i];

    vhpf_type vres[elements];
    for (std::size_t i=0; i<elements; ++i) {
        vres[i]= hpf_func::native_exp_k(vxh[i], exp_m1);
    }
    dvf_type res;
    _T::vhpf_to_dvf(vres, res);
    return res;
#endif
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::dvf_type
cftal::math::func_core<float, _T>::
exp2_k2(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    using vhpf_type = typename _T::vhpf_type;
    const std::size_t elements = _T::vhpf_per_vf();

    using hpf_traits = typename _T::hpf_traits;
    using hpf_func =
        func_core<double, hpf_traits>;

    vhpf_type vxh[elements];
    _T::vf_to_vhpf(xh, vxh);
    vhpf_type vxl[elements];
    _T::vf_to_vhpf(xl, vxl);
    // evaluate unevaluated sum
    for (std::size_t i=0; i<elements; ++i)
        vxh[i] += vxl[i];

    vhpf_type vres[elements];
    for (std::size_t i=0; i<elements; ++i) {
        vres[i]= hpf_func::native_exp2_k(vxh[i]);
    }
    dvf_type res;
    _T::vhpf_to_dvf(vres, res);
    return res;
}

template <typename _T>
inline
typename cftal::math::func_core<float, _T>::dvf_type
cftal::math::func_core<float, _T>::
exp10_k2(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    using vhpf_type = typename _T::vhpf_type;
    const std::size_t elements = _T::vhpf_per_vf();

    using hpf_traits = typename _T::hpf_traits;
    using hpf_func =
        func_core<double, hpf_traits>;

    vhpf_type vxh[elements];
    _T::vf_to_vhpf(xh, vxh);
    vhpf_type vxl[elements];
    _T::vf_to_vhpf(xl, vxl);
    // evaluate unevaluated sum
    for (std::size_t i=0; i<elements; ++i)
        vxh[i] += vxl[i];

    vhpf_type vres[elements];
    for (std::size_t i=0; i<elements; ++i) {
        vres[i]= hpf_func::native_exp10_k(vxh[i]);
    }
    dvf_type res;
    _T::vhpf_to_dvf(vres, res);
    return res;
}

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


template <typename _T>
inline
typename cftal::math::func_core<float, _T>::dvf_type
cftal::math::func_core<float, _T>::
log_k2(arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    using vhpf_type = typename _T::vhpf_type;
    const std::size_t elements = _T::vhpf_per_vf();

    using hpf_traits = typename _T::hpf_traits;
    using hpf_func =
        func_core<double, hpf_traits>;

    vhpf_type vxh[elements];
    _T::vf_to_vhpf(xh, vxh);
    vhpf_type vxl[elements];
    _T::vf_to_vhpf(xl, vxl);
    // evaluate unevaluated sum
    for (std::size_t i=0; i<elements; ++i)
        vxh[i] += vxl[i];

    vhpf_type vres[elements];
    for (std::size_t i=0; i<elements; ++i) {
        vres[i]= hpf_func::native_log_k(vxh[i]);
    }
    dvf_type res;
    _T::vhpf_to_dvf(vres, res);
    return res;
}

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


template <typename _T>
inline
typename cftal::math::func_core<float, _T>::dvf_type
cftal::math::func_core<float, _T>::
atan2_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
         arg_t<vf_type> yh, arg_t<vf_type> yl,
         bool calc_atan2)
{
    return dvf_type(xh + yh);
}

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2(
     6.9314718246460e-01f, -1.9046542121259e-09f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ln2(
     1.4426950216293e+00f,  1.9259630335000e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln10(
     2.3025848865509e+00f,  2.0644314702167e-07f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2pow106(
     7.3473594665527e+01f,  6.4738269429654e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2pow48(
     3.3271060943604e+01f,  3.7232739487081e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi(
     3.1415927410126e+00f, -8.7422776573476e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi2(
     6.2831854820251e+00f, -1.7484555314695e-07f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi_2(
     1.5707963705063e+00f, -4.3711388286738e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi_4(
     7.8539818525314e-01f, -2.1855694143369e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_pi(
     3.1830987334251e-01f,  1.2841276486597e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_2_pi(
     6.3661974668503e-01f,  2.5682552973194e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_4_pi(
     1.2732394933701e+00f,  5.1365105946388e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
inv_fac[MAX_FAC+1]= {
    _T(  1.0000000000000e+00f,  0.0000000000000e+00f),
    _T(  1.0000000000000e+00f,  0.0000000000000e+00f),
    _T(  5.0000000000000e-01f,  0.0000000000000e+00f),
    _T(  1.6666667163372e-01f, -4.9670538793123e-09f),
    _T(  4.1666667908430e-02f, -1.2417634698281e-09f),
    _T(  8.3333337679505e-03f, -4.3461720333760e-10f),
    _T(  1.3888889225200e-03f, -3.3631094437103e-11f),
    _T(  1.9841270113830e-04f, -2.7255968749335e-12f),
    _T(  2.4801587642287e-05f, -3.4069960936668e-13f),
    _T(  2.7557318844629e-06f,  3.7935712242972e-14f),
    _T(  2.7557319981497e-07f, -7.5751122090512e-15f),
    _T(  2.5052107943679e-08f,  4.4176230446484e-16f),
    _T(  2.0876755879584e-09f,  1.1082839147460e-16f),
    _T(  1.6059044372074e-10f, -5.3525265115627e-18f),
    _T(  1.1470745360509e-11f,  2.3722076892312e-19f),
    _T(  7.6471636098127e-13f,  1.2200710471178e-20f),
    _T(  4.7794772561329e-14f,  7.6254440444864e-22f),
    _T(  2.8114573589664e-15f, -1.0462084739764e-22f),
    _T(  1.5619206814542e-16f,  1.5404471465942e-24f),
    _T(  8.2206350784765e-18f,  1.6814780968559e-25f),
    _T(  4.1103175909370e-19f,  3.2375117328603e-27f)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
_2_over_i[MAX_2_OVER_I+1]= {
    _T(  2.0000000000000e+00f,  0.0000000000000e+00f),
    _T(  2.0000000000000e+00f,  0.0000000000000e+00f),
    _T(  1.0000000000000e+00f,  0.0000000000000e+00f),
    _T(  6.6666668653488e-01f, -1.9868215517249e-08f),
    _T(  5.0000000000000e-01f,  0.0000000000000e+00f),
    _T(  4.0000000596046e-01f, -5.9604645663569e-09f),
    _T(  3.3333334326744e-01f, -9.9341077586246e-09f),
    _T(  2.8571429848671e-01f, -1.2772424007323e-08f),
    _T(  2.5000000000000e-01f,  0.0000000000000e+00f),
    _T(  2.2222222387791e-01f, -1.6556845894300e-09f),
    _T(  2.0000000298023e-01f, -2.9802322831785e-09f),
    _T(  1.8181818723679e-01f, -5.4186042319770e-09f),
    _T(  1.6666667163372e-01f, -4.9670538793123e-09f),
    _T(  1.5384615957737e-01f, -5.7312159462697e-09f),
    _T(  1.4285714924335e-01f, -6.3862120036617e-09f),
    _T(  1.3333334028721e-01f, -6.9538752534015e-09f),
    _T(  1.2500000000000e-01f,  0.0000000000000e+00f),
    _T(  1.1764705926180e-01f, -4.3826944851055e-10f),
    _T(  1.1111111193895e-01f, -8.2784229471500e-10f),
    _T(  1.0526315867901e-01f, -7.8427164762473e-10f),
    _T(  1.0000000149012e-01f, -1.4901161415892e-09f)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
exp_coeff[MAX_EXP_COEFF] =  {
    // + 1/5!
    _T(  8.3333337679505e-03f, -4.3461720333760e-10f),
    // + 1/4!
    _T(  4.1666667908430e-02f, -1.2417634698281e-09f),
    // + 1/3!
    _T(  1.6666667163372e-01f, -4.9670538793123e-09f),
    // + 1/2!
    _T(  5.0000000000000e-01f,  0.0000000000000e+00f),
    // + 1/1!
    _T(  1.0000000000000e+00f,  0.0000000000000e+00f),
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
sin_coeff[MAX_SIN_COEFF] =  {
    // +1/11!
    _T(  2.5052107943679e-08f,  4.4176230446484e-16f),
    // -1/9!
    _T( -2.7557318844629e-06f, -3.7935712242972e-14f),
    // +1/7!
    _T(  1.9841270113830e-04f, -2.7255968749335e-12f),
    // -1/5!
    _T( -8.3333337679505e-03f,  4.3461720333760e-10f),
    // +1/3!
    _T(  1.6666667163372e-01f, -4.9670538793123e-09f)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
cos_coeff[MAX_COS_COEFF] =  {
    // -1/12!
    _T( -2.0876755879584e-09f, -1.1082839147460e-16f),
    // +1/10!
    _T(  2.7557319981497e-07f, -7.5751122090512e-15f),
    // -1/8!
    _T( -2.4801587642287e-05f,  3.4069960936668e-13f),
    // +1/6!
    _T(  1.3888889225200e-03f, -3.3631094437103e-11f),
    // -1/4!
    _T( -4.1666667908430e-02f,  1.2417634698281e-09f)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
atan2_coeff[MAX_ATAN2_COEFF] =  {
    // prod(even numbers to 24)/product(odd numbers to 25)
    _T(  2.4816934764385e-01f,  3.5326330749541e-09f),
    // prod(even numbers to 22)/product(odd numbers to 23)
    _T(  2.5850975513458e-01f, -1.4325743258325e-08f),
    // prod(even numbers to 20)/product(odd numbers to 21)
    _T(  2.7026018500328e-01f, -1.4304035733659e-09f),
    // prod(even numbers to 18)/product(odd numbers to 19)
    _T(  2.8377318382263e-01f,  8.9288887394900e-09f),
    // prod(even numbers to 16)/product(odd numbers to 17)
    _T(  2.9953837394714e-01f, -3.8205381081013e-09f),
    // prod(even numbers to 14)/product(odd numbers to 15)
    _T(  3.1825950741768e-01f,  1.0841839426234e-08f),
    // prod(even numbers to 12)/product(odd numbers to 13)
    _T(  3.4099233150482e-01f,  9.4875192147015e-09f),
    // prod(even numbers to 10)/product(odd numbers to 11)
    _T(  3.6940836906433e-01f,  3.4403835336150e-10f),
    // prod(even numbers to 8)/product(odd numbers to 9)
    _T(  4.0634921193123e-01f, -5.5820223998637e-09f),
    // prod(even numbers to 6)/product(odd numbers to 7)
    _T(  4.5714285969734e-01f, -2.5544848458736e-09f),
    // prod(even numbers to 4)/product(odd numbers to 5)
    _T(  5.3333336114883e-01f, -2.7815501013606e-08f),
    // prod(even numbers to 2)/product(odd numbers to 3)
    _T(  6.6666668653488e-01f, -1.9868215517249e-08f),
    // prod(even numbers to 0)/product(odd numbers to 1)
    _T(  1.0000000000000e+00f,  0.0000000000000e+00f)
};

// Local Variables:
// mode: c++
// end:
#endif
