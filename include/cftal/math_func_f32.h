#if !defined (__MATH_FUNC_F32_H__)
#define __MATH_FUNC_F32_H__ 1

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

            // returns (y0+y1) = x - N * pi/2
            // the integer results contains
            // only the lower bits of N
            int32_t
            __attribute__((__visibility__("internal")))
            __ieee754_rem_pio2(float x, float *y);

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

            static void
            native_sin_cos_k(arg_t<vf_type> x,
                             vf_type* s, vf_type* c);

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

#if 1

template <typename _T>
inline
std::pair<typename cftal::math::func_core<float, _T>::dvf_type,
          typename cftal::math::func_core<float, _T>::vi_type>
cftal::math::
func_core<float, _T>::
reduce_trig_arg_k(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    vmf_type v_large_arg(vf_type(ctbl::sin_cos_arg_large) < abs(d));
    // small argument reduction
    // reduce by pi half
    dvf_type qf(rint(d * dvf_type(ctbl::m_2_pi)));
    dvf_type d0=d;
    for (auto b=std::cbegin(ctbl::m_pi_2_bits), e=std::cend(ctbl::m_pi_2_bits);
         b!=e; ++b) {
        vf_type t=*b;
        d0 = d0 -qf * t;
    }
    vi_type q(_T::cvt_f_to_i(qf.h()+qf.l()));

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
        mem<vf_type>::store(tf._sc, d);
        mem<vi_type>::store(ti._sc, q);
        mem<vf_type>::store(d0_l._sc, d0.l());
        mem<vf_type>::store(d0_h._sc, d0.h());
        for (std::size_t i=0; i<N; ++i) {
            if (ctbl::sin_cos_arg_large < std::fabs(tf._sc[i])) {
                float y[2];
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
cftal::math::func_core<float, _T>::
sin_cos_k(arg_t<vf_type> d, std::size_t n,
          vf_type* ps, vf_type* pc)
{
    using ctbl = impl::d_real_constants<d_real<float>, float>;
    std::pair<dvf_type, vi_type> rr(reduce_trig_arg_k(d));
    const vi_type& q= rr.second;
    const dvf_type& dh= rr.first;

    vmi_type q_and_2(vi_type(q & vi_type(2))==vi_type(2));
    vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));

    vmi_type q_and_1(vi_type(q & vi_type(1))==vi_type(1));
    vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

    // calculate sin + cos
    dvf_type x= sqr(dh);

    dvf_type s = impl::poly(x, ctbl::sin_coeff);
    s = s * x + vf_type(1.0);
    s = s * dh;

    dvf_type c= impl::poly(x, ctbl::cos_coeff);
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

#else

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


// Local Variables:
// mode: c++
// end:
#endif
