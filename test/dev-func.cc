#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/elem_func.h"
#include "cftal/math/elem_func_core_f64.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>

namespace cftal {

    namespace math {
        template <typename _FLOAT_T, typename _TRAITS_T>
        struct test_func : public elem_func_core< _FLOAT_T, _TRAITS_T> {
            using base_type = elem_func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = test_func<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;

            static vf_type func(arg_t<vf_type> vf);
        };

        template <typename _T>
        struct test_func<double, _T> : public elem_func_core<double, _T> {
            using base_type = elem_func_core<double, _T>;
            typedef typename _T::vf_type vf_type;
            typedef typename _T::vi_type vi_type;
            // using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            typedef typename _T::vmf_type vmf_type;
            typedef typename _T::vmi_type vmi_type;
            // using vmi2_type = typename _T::vmi2_type;

            typedef d_real<vf_type> dvf_type;
            typedef t_real<vf_type> tvf_type;
            typedef elem_func_core<double, _T> my_type;

            using d_ops = typename base_type::d_ops;
            

            static vf_type func(arg_t<vf_type> vf);

            static dvf_type log_k2(arg_t<vf_type> vf);
            
            static vf_type exp_k2(arg_t<vf_type> xh, arg_t<vf_type> xl);

        };
    }

    namespace test {

        template <typename _T>
        struct check_func {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::func(a);
            }
            static
            auto
            r(const _T& a) {
#if 1 
                std::pair<_T, _T> i;
#if 1
                _T v=call_mpfr::func(a, mpfr_exp, &i);
#else
                _T v=call_mpfr::func(a, mpfr_log, &i);
#endif
                return std::make_tuple(v, i.first, i.second);                
#else
                using mp_t=mpfr_real<2*sizeof(_T)*8>;
                mp_t x=a;
                x *= x;
                x = -x;
                mp_t mr;
                int mpres=mpfr_exp2(mr(), x(), GMP_RNDN);
                _T r=mpfr_get_d(mr(), GMP_RNDN);
                std::pair<_T, _T> i= call_mpfr::ulp1_interval(r, mpres);
                return std::make_tuple(r, i.first, i.second);
#endif
            }
            static
            _T
            s(const _T& a) {
                return std::exp(a);
            }
            static
            const char* fname() { return "func"; }
        };



    }
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::func(arg_t<vf_type> xc)
{
#if 1
    const vf_type d=xc;
    vf_type res=exp_k2(xc, 0.0);
    using fc= func_constants<double>;
    const vf_type exp_hi_inf= fc::exp_hi_inf();
    const vf_type exp_lo_zero= fc::exp_lo_zero();
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, M_E, res);
    return res;
    
#else
    auto log_x = log_k2(xc);  
    vf_type x= log_x.h() + log_x.l();
    
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(xc), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(xc < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(xc == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(xc), xc, x);
    // using fc= func_constants<_FLOAT_T>;
    // const vf_type log_lo_fin= fc::log_lo_fin;
    // const vf_type log_lo_val= fc::log_lo_val;
    // x = _T::sel(d == log_lo_fin, log_lo_val, x);
    return x;
#endif
}
    
template <typename _T>
typename cftal::math::test_func<double, _T>::dvf_type
cftal::math::test_func<double, _T>::log_k2(arg_t<vf_type> xc)
{

    using fc = func_constants<double>;
    vmf_type is_denom=xc <= fc::max_denormal();
    vf_type x=_T::sel(is_denom, xc*0x1p54, xc);
    vi2_type k=_T::sel(_T::vmf_to_vmi2(is_denom), vi2_type(-54), vi2_type(0));
    vi2_type lx, hx;
    _T::extract_words(lx, hx, x);
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += (hx>>20) - _T::bias();
    hx = (hx&0x000fffff) + 0x3fe6a09e;
    vf_type xr = _T::combine_words(lx, hx);

    // vf_type f = xr - 1.0;
    dvf_type df= d_ops::add(xr, vf_type(-1.0));
    vf_type f= df.h();
    dvf_type dhfsq = mul_pwr2(df, vf_type(0.5))*df;
    vf_type s = f/(2.0+f);
    vf_type z = s*s;    

    // [3.4694469519536141888238489627838134765625e-18, 0.17157287895679473876953125] : | p - f | <= 2^-64.625
    // coefficients for log generated by sollya
    // x^2 : +0xa.aaaaaaaaaaaa8p-4
    const vf_type log_c2=+6.6666666666666662965923e-01;
    // x^4 : +0xc.ccccccccceac8p-5
    const vf_type log_c4=+4.0000000000005325739849e-01;
    // x^6 : +0x9.24924921770b8p-5
    const vf_type log_c6=+2.8571428569168361155661e-01;
    // x^8 : +0xe.38e392e2fd49p-6
    const vf_type log_c8=+2.2222222656633455750708e-01;
    // x^10 : +0xb.a2e6dba5baafp-6
    const vf_type log_c10=+1.8181773614825663676342e-01;
    // x^12 : +0x9.d90aca733a8d8p-6
    const vf_type log_c12=+1.5387220163840073516859e-01;
    // x^14 : +0x8.7a5091423103p-6
    const vf_type log_c14=+1.3246549783140454392694e-01;
    // x^16 : +0x8.811edd68c1cb8p-6
    const vf_type log_c16=+1.3288089391701582431260e-01;

    vf_type w = z*z;
    vf_type t1= z*impl::poly(w,
                             log_c14,
                             log_c10,
                             log_c6,
                             log_c2);
    vf_type t2= impl::poly(w,
                           log_c16,
                           log_c12,
                           log_c8,
                           log_c4);
    vf_type y = t2*w + t1;

    using ctbl=impl::d_real_constants<d_real<double>, double>;
    vf_type kf = _T::cvt_i_to_f(_T::vi2_odd_to_vi(k));

    dvf_type log_x= kf* dvf_type(ctbl::m_ln2);
    log_x += vf_type(s*dhfsq.h());
    log_x += vf_type(s*y);
    // log_x -= dhfsq;
    // log_x += df;
    log_x += (df -dhfsq);
    return log_x;
}

template <typename _T>
typename cftal::math::test_func<double, _T>::vf_type
cftal::math::test_func<double, _T>::exp_k2(arg_t<vf_type> xh,
                                           arg_t<vf_type> xl)
{
    using ctbl = impl::d_real_constants<d_real<double>, double>;
    dvf_type x(xh, xl);
    vf_type kf = rint(vf_type(xh * ctbl::m_1_ln2.h()));
    dvf_type xr = x - kf * dvf_type(ctbl::m_ln2);
    vi_type k= _T::cvt_f_to_i(kf);
    vi2_type k2= _T::vi_to_vi2(k);

    // [-0.3465735912322998046875, 0.3465735912322998046875] : | p - f | <= 2^-67.5
    // coefficients for exp generated by sollya
    // x^0 : +0x8p-3
    const vf_type exp_c0=+1.0000000000000000000000e+00;
    // x^1 : +0x8p-3
    const vf_type exp_c1=+1.0000000000000000000000e+00;
    // x^2 : +0x8p-4
    const vf_type exp_c2=+5.0000000000000000000000e-01;
    // x^3 : +0xa.aaaaaaaaaaaa8p-6
    const vf_type exp_c3=+1.6666666666666665741481e-01;
    // x^4 : +0xa.aaaaaaaaaaacp-8
    const vf_type exp_c4=+4.1666666666666685170384e-02;
    // x^5 : +0x8.888888888961p-10
    const vf_type exp_c5=+8.3333333333340843529502e-03;
    // x^6 : +0xb.60b60b60a81p-13
    const vf_type exp_c6=+1.3888888888873365812238e-03;
    // x^7 : +0xd.00d00cfa88cc8p-16
    const vf_type exp_c7=+1.9841269839039331096715e-04;
    // x^8 : +0xd.00d00d6b5b978p-19
    const vf_type exp_c8=+2.4801587348902822885563e-05;
    // x^9 : +0xb.8ef1e87f8178p-22
    const vf_type exp_c9=+2.7557322326013787452785e-06;
    // x^10 : +0x9.3f26623e02258p-25
    const vf_type exp_c10=+2.7557252167692825528943e-07;
    // x^11 : +0xd.72da4d99cea7p-29
    const vf_type exp_c11=+2.5050050656095725290235e-08;
    // x^12 : +0x8.fc5bcb2f9e01p-32
    const vf_type exp_c12=+2.0921639307947645130620e-09;
    // x^13 : +0xb.675e3ad02de48p-36
    const vf_type exp_c13=+1.6594686285988114700473e-10;

    vf_type xx=xr.h()*xr.h();
    vf_type i=impl::poly(xx,
                         exp_c13,
                         exp_c11,
                         exp_c9,
                         exp_c7,
                         exp_c5);
    vf_type j=impl::poly(xx,
                         exp_c12,
                         exp_c10,
                         exp_c8,
                         exp_c6,
                         exp_c4);
    vf_type y=i*xr.h() + j;
    y = impl::poly(xr.h(), y,
                   exp_c3);
    // correction for errors in argument reduction
    vf_type cr = xr.l();
    vf_type yee= cr + cr*xr.h() + 0.5*cr*xx;
    vf_type ye;
    // y = impl::poly(xr.h(), y, exp_c1);
    impl::eft_poly(y, ye, xr.h(), y,
                   exp_c2, exp_c1, exp_c0);
    // y = d_ops::two_sum(y, exp_c2, ye);
    // impl::eft_poly_si(y, ye, xr, y, ye,
    //                  exp_c1,
    //                  exp_c0);
    ye += yee;
    y += ye;
    y = base_type::scale_exp_k(y, kf, k2);
    return y;
}

    
int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=1;
    const int _N=4;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = double;
    
    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<double> d=std::make_pair(-750.0, 710.0);
    // func_domain<float> d=std::make_pair(1.0, 27);
    // func_domain<float> d=std::make_pair(0.0, 1.0);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_func<ftype> >::v(st, d, speed_only,
                                          cmp_ulp<ftype>(ulp, us),
                                          cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}
