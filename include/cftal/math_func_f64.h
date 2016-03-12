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
#include <iterator>
#include <iostream>

namespace cftal {

    namespace math {

        namespace impl {


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
            void extract_words(vi_type& low_word, vi_type& high_word,
                               const vf_type& d) {
                ud_t t;
                t._d = d;
                low_word= vi_type(t._u);
                high_word= vi_type(t._u >>32);
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
ldexp(arg_t<vf_type> x, arg_t<vi_type> n)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    vi_type eo=vi_type(0);
    // input denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p53), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-53), eo);
    // split mantissa
    vi_type ml, mh;
    _T::extract_words(ml, mh, xs);
    vi_type xe=((mh>>20) & 0x7ff) + eo;

    // determine the exponent of the result
    // clamp nn to [-4096, 4096]
    vi_type nn= min(vi_type(4096), max(n, vi_type(-4096)));
    vi_type re= xe + nn;

    // 3 cases exist:
    // 0 < re < 0x7ff normal result
    //     re >= 0x7ff inf result (overflow)
    //     re <= 0 subnormal or 0 (underflow)

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
        // create a scaling factor, but avoid overflows
        vi_type ue= max(vi_type(re + (_T::bias-1)), vi_type(1));
        vf_type s_u= _T::insert_exp(ue);
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
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp(arg_t<vf_type> x, vi_type* ve)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;

    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p53), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-53), eo);
    // extract mantissa
    vi_type lo_word, hi_word;
    _T::extract_words(lo_word, hi_word, xs);
    // exponent:
    vi_type e=((hi_word >> 20) & 0x7ff) + eo;
    // insert exponent
    hi_word = (hi_word & vi_type(0x800fffff)) | vi_type(0x3fe00000);
    // combine low and high word
    vf_type frc(_T::combine_words(lo_word, hi_word));
    // inf, nan, zero
    vmf_type f_inz=isinf(x) | isnan(x) | (x==vf_type(0.0));
    frc = _T::sel(f_inz, x, frc);
    if (ve != nullptr) {
        // remove bias from e
        vmi_type i_inz=_T::vmf_to_vmi(f_inz);
        e -= vi_type(_T::bias-1);
        e= _T::sel(i_inz, vi_type(0), e);
        *ve= e;
    }
    return frc;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogbp1(arg_t<vf_type> x)
{
    vf_type xs=x;
    using fc=func_constants<double>;
    vmf_type is_denom= abs(x) <= fc::max_denormal;
    vi_type eo=vi_type(0);
    // denormal handling
    xs= _T::sel(is_denom, xs*vf_type(0x1.p53), xs);
    vmi_type i_is_denom= _T::vmf_to_vmi(is_denom);
    eo= _T::sel(i_is_denom, vi_type(-53), eo);
    // reinterpret as integer
    vi_type hi_word(_T::extract_high_word(xs));
    // exponent:
    vi_type e=((hi_word >> 20) & 0x7ff) + eo - vi_type(_T::bias-1);
    return e;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogb(arg_t<vf_type> d)
{
    vi_type e(ilogbp1(d) - vi_type(1));
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
std::pair<typename cftal::math::func_core<double, _T>::vf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::func_core<double, _T>::
native_reduce_trig_arg_k(arg_t<vf_type> d)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    constexpr double large_arg(0x1.0p31);
    vmf_type v_large_arg(vf_type(large_arg) < abs(d));

    vf_type qf(rint(vf_type(d * (2 * M_1_PI))));
    vi_type q(_T::cvt_f_to_i(qf));

    vf_type d0(d);
    for (auto b=std::cbegin(ctbl::m_pi_2_cw), e=std::cend(ctbl::m_pi_2_cw);
         b != e; ++b) {
        vf_type t=*b;
        d0 = d0 - qf * t;
    }

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
cftal::math::func_core<double, _T>::
native_sin_cos_k(arg_t<vf_type> d, vf_type* ps, vf_type* pc)
{
    std::pair<vf_type, vi_type> rq(
        native_reduce_trig_arg_k(d));
    vf_type x= rq.first;
    const vi_type& q= rq.second;

    vf_type x2(x*x);

    using ctbl = impl::d_real_constants<d_real<double>, double>;
    vf_type s = impl::poly(x2, ctbl::sin_coeff);
    s = s * x2 + vf_type(1.0);
    s = s * x;

    vf_type c= impl::poly(x2, ctbl::cos_coeff);
    c = c * x2 - vf_type(0.5);
    c = c * x2 + vf_type(1.0);

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
