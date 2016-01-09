#if !defined (__CFTAL_MATH_COMMON_H__)
#define __CFTAL_MATH_COMMON_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/divisor.h>
#include <cftal/constants.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {

    namespace math {

        template <typename _FLOAT_T, typename _INT_T>
        struct func_traits;

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct func_core {
            typedef typename _TRAITS_T::vf_type vf_type;
            typedef typename _TRAITS_T::vi_type vi_type;
            typedef typename _TRAITS_T::vmf_type vmf_type;
            typedef typename _TRAITS_T::vmi_type vmi_type;
            typedef d_real<vf_type> dvf_type;

            // exp core
            static dvf_type
            exp_k2(const dvf_type& dvf);
            // native exp core
            static vf_type
            native_exp_k(const vf_type& vf);
            // log core
            static dvf_type
            log_k2(const dvf_type& dvf);
            // native log core
            static dvf_type
            native_log_k2(const dvf_type& dvf);
            // sin and cos core, return sin in first
            static std::pair<dvf_type, dvf_type>
            sin_cos_k(const vf_type& v);
            // native sin and cos core, return sin in first
            static std::pair<vf_type, vf_type>
            native_sin_cos_k(const vf_type& v);
            // atan2 core
            static dvf_type
            atan2_k2(const dvf_type& x, const dvf_type& y);
            // atan2 core
            static dvf_type
            native_atan2_k(const dvf_type& x, const dvf_type& y);
        };

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct func_common : public func_core< _FLOAT_T,
                                               _TRAITS_T> {
            typedef func_core<_FLOAT_T,
                              _TRAITS_T> base_type;

            typedef func_common<_FLOAT_T,
                                _TRAITS_T> my_type;

            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;

            // exp, expm1, sinh, cosh call exp_k2 if native == false
            // or native_exp
            template <bool _NATIVE>
            static vf_type _exp(const vf_type& vf);
            template <bool _NATIVE>
            static vf_type _exp2(const vf_type& vf);
            template <bool _NATIVE>
            static vf_type _exp10(const vf_type& vf);
            template <bool _NATIVE>
            static vf_type _expm1(const vf_type& vf);
            template <bool _NATIVE>
            static vf_type _sinh(const vf_type& vf);
            template <bool _NATIVE>
            static vf_type _cosh(const vf_type& vf);

            // log _call log_k2 if native == false, or native_log
            template <bool _NATIVE>
            static vf_type _log(const vf_type& cf);

            // exp, expm1, sinh, cosh call exp_k2
            static vf_type exp(const vf_type& vf);
            static vf_type exp2(const vf_type& vf);
            static vf_type exp10(const vf_type& vf);
            static vf_type expm1(const vf_type& vf);
            static vf_type sinh(const vf_type& vf);
            static vf_type cosh(const vf_type& vf);

            // native exp, expm1, sinh, cosh call exp_k
            static vf_type native_exp(const vf_type& vf);
            static vf_type native_exp2(const vf_type& vf);
            static vf_type native_exp10(const vf_type& vf);
            static vf_type native_expm1(const vf_type& vf);
            static vf_type native_sinh(const vf_type& vf);
            static vf_type native_cosh(const vf_type& vf);

            // log calls log_k2
            static vf_type log(const vf_type& vf);
            // native log calls native_log_k
            static vf_type native_log(const vf_type& vf);

            // pow calls exp_k2 and log_k2
            static vf_type pow(const vf_type& b,
                               const vf_type& e);

            // sincos, sin, cos, tan and cot call
            // sin_cos_k
            static void sincos(const vf_type& vf,
                               vf_type* psin,
                               vf_type* pcos);
            static vf_type sin(const vf_type& vf);
            static vf_type cos(const vf_type& vf);
            static vf_type tan(const vf_type& vf);
            static vf_type cot(const vf_type& vf);
            // sincos, sin, cos, tan and cot call
            // native_sin_cos_k
            static void native_sincos(const vf_type& vf,
                                      vf_type* psin,
                                      vf_type* pcos);
            static vf_type native_sin(const vf_type& vf);
            static vf_type native_cos(const vf_type& vf);
            static vf_type native_tan(const vf_type& vf);
            static vf_type native_cot(const vf_type& vf);

            // atan2, atan, ... call atan2_k2
            static vf_type atan2(const vf_type& x,
                                 const vf_type& y);
            static vf_type atan(const vf_type& x);
        };


        template <typename _FLOAT_T, typename _TRAITS_T>
        struct func : public func_common<_FLOAT_T, _TRAITS_T> {
            typedef typename _TRAITS_T::vf_type vf_type;
            typedef typename _TRAITS_T::vi_type vi_type;
            typedef typename _TRAITS_T::vmf_type vmf_type;
            typedef typename _TRAITS_T::vmi_type vmi_type;
        };


        namespace impl {

            template <class _VEC, typename _FLOAT_T>
            struct d_real_constants {};

            // sin(x + y) = sin(x) * cos(y) + sin(y) * cos(x);
            // sin(x - y) = sin(x) * cos(y) - sin(y) * cos(x);
            // sin(2x) = 2 * sin(x) * cos(x);

            // cos(x + y) = cos(x) * cos(y) - sin(x) * sin(y);
            // cos(x - y) = cos(x) * cos(y) + sin(x) * sin(y);
            // cos(2x) = cos(x)^2 - sin(x)^2 = 1 - 2 sin(x)^2

            template <class _T>
            _T sin2x(const _T& sinx, const _T& cosx);
            template <class _T>
            d_real<_T> sin2x(const d_real<_T>& sinx,
                             const d_real<_T>& cosx);
            template <class _T>
            _T cos2x(const _T& sinx, const _T& cosx);
            template <class _T>
            d_real<_T> cos2x(const d_real<_T>& sinx,
                             const d_real<_T>& cosx);
            template <class _T>
            _T sin4x(const _T& sinx, const _T& cosx);
            template <class _T>
            _T cos4x(const _T& sinx, const _T& cosx);

            // integer power
            template <class _T>
            struct ivpow {
                static _T v(const _T& xx, int p);
            };

            // unsigned integer pow
            template <class _T, unsigned _P>
            struct ipow {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==0
            template <class _T>
            struct ipow<_T, 0U> {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==1
            template <class _T>
            struct ipow<_T, 1U> {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==2
            template <class _T>
            struct ipow<_T, 2U> {
                static _T v(const _T& x);
            };

            // n-th root calculator: newton raphson step with n variable
            template <class _T>
            struct nth_root_vnr {
                static _T v(const _T& xi, const _T& x,
                            unsigned r) {
                    const _T rr(r);
                    _T x_pow_nm1(ivpow<_T>::v(xi, r-1));
                    _T en( x - xi * x_pow_nm1);
                    _T den(rr * x_pow_nm1);
                    _T xip1( xi + en / den);
                    return xip1;
                }
            };

            // n-th root calculatr: newton raphson step with n=_R
            template <unsigned _R, class _T>
            struct nth_root_nr : public nth_root_vnr<_T> {
                // one newton raphson step
                static _T v(const _T& xi, const _T& x) {
                    const _T r(_R);
                    _T x_pow_nm1(ipow<_T, _R-1>::v(xi));
                    _T en( x - xi * x_pow_nm1);
                    _T den(r * x_pow_nm1);
                    _T xip1( xi + en / den);

                    return xip1;
                }
            };

            // the initial guess for a vector of _SCALAR_FLOAT
            // using traits for root r
            template <typename _SCALAR_FLOAT,
                      typename _TRAITS>
            struct nth_root_guess {
                typedef typename _TRAITS::vf_type vf_type;
                static vf_type v(const vf_type& f, unsigned r);
            };

            // the initial guess for a vector of float
            // with int32_t using traits
            // for root _R
            template <typename _TRAITS>
            struct nth_root_guess<float, _TRAITS> {
                typedef typename _TRAITS::vf_type vf_type;
                typedef typename _TRAITS::vi_type vi_type;
                static vf_type v(const vf_type& f, unsigned r) {
                    // const int ebits = 8;
                    // const int fbits = 23;
                    vi_type i(_TRAITS::as_int(f));
                    const int bias = (1 << (8-1))-1;
                    const int bias_shl_23(bias << 23);
                    const divisor<vi_type, int32_t> rr(r);
                    i = vi_type(i - bias_shl_23) / rr +
                        bias_shl_23;
                    vf_type x(_TRAITS::as_float(i));
                    return x;
                }
            };

            // the initial guess for a vector of double
            // using traits for root _R
            template <typename _TRAITS>
            struct nth_root_guess<double, _TRAITS> {
                typedef typename _TRAITS::vf_type vf_type;
                typedef typename _TRAITS::vi_type vi_type;

                static vf_type v(const vf_type& f, unsigned r) {
                    vi_type hw=
                        _TRAITS::extract_high_word(f);
                    const int32_t bias = (1 << (11-1))-1;
                    vi_type bias_shl_20(bias << 20);
                    const divisor<vi_type, int32_t> rr(r);
                    hw = vi_type(hw - bias_shl_20)/rr +
                        bias_shl_20;
                    vf_type g0;
                    g0 = _TRAITS::combine_words(vi_type(0),
                                                hw  );
                    return g0;
#if 0
                    const int ebits = 11;
                    const int fbits = 52;
                    int64& i = (int64&) x;
                    const _int64 bias = (1 << (ebits-1))-1;
                    i = (i - (bias << fbits)) / n +
                        (bias << fbits);
                    return x;
#endif

                }
            };

            template <typename _FLOAT_T, typename _TRAITS,
                      unsigned _R>
            struct root_guess : public nth_root_guess<_FLOAT_T, _TRAITS> {
                using vf_type = typename _TRAITS::vf_type;

                static vf_type v(const vf_type& x) {
                    return nth_root_guess<_FLOAT_T, _TRAITS>::v(x, _R);
                }
            };

#if 0
            template <typename _TRAITS>
            struct root_guess<double, _TRAITS, 3> {
                using vf_type = typename _TRAITS::vf_type;
                using vi_type = typename _TRAITS::vi_type;

                static vf_type(const vf_type& x) {

                }
            };
#endif
            // nth root implementation for double/float
            template <typename _FLOAT_T, typename _TRAITS,
                      unsigned _R>
            struct nth_root {

                typedef typename _TRAITS::vf_type vf_type;
                typedef typename _TRAITS::vmf_type vmf_type;
                typedef nth_root_nr<_R, vf_type> nr_step_t;
                typedef root_guess<_FLOAT_T, _TRAITS, _R>
                    guess_t;

                template <unsigned _NR_STEPS=6>
                static vf_type v(const vf_type& f) {
                    vf_type x(abs(f));
                    vf_type xin(guess_t::v(x));
#if 0
                    for (unsigned i=0; i< _NR_STEPS-1; ++i)
                        xin = nr_step_t::v(xin, x);
#else
                    using dvf_type = typename _TRAITS::dvf_type;
                    for (unsigned i=0; i< _NR_STEPS-1; ++i)
                        xin = nr_step_t::v(xin, x);
                    dvf_type xhin=xin;
                    dvf_type xh=x;
                    for (unsigned i=_NR_STEPS-1; i< _NR_STEPS; ++i)
                        xhin = nth_root_nr<_R, dvf_type>::v(xhin, xh);
                    xin = xhin.h() + xhin.l();
#endif
                    xin = copysign(xin, f);
                    const vf_type zero(vf_type(0.0));
                    vmf_type is_zero_or_inf_or_nan(
                        (f == zero) | isinf(f) | isnan(f));
                    vf_type r(_TRAITS::sel(is_zero_or_inf_or_nan,
                                           f, xin));
                    if ((_R & 1) == 0) {
                        vmf_type is_neg(x < zero);
                        r = _TRAITS::sel(is_neg,
                                         vf_type(_TRAITS::nan()), r);
                    }
                    return r;
                }
            };

        } // impl

        // integer power with constant _I
        template <int _I, class _T>
        _T pow(const _T& x) {
            _T r(impl::ipow<_T, (_I < 0 ? -_I : _I) >::v(x));
            if (_I < 0 ) {
                r = _T(1)/r;
            }
            return r;
        }
    }
}


template <class _T>
_T
cftal::math::impl::sin2x(const _T& sinx, const _T& cosx)
{
    return _T(2.0) * sinx * cosx;
}

template <class _T>
cftal::d_real<_T>
cftal::math::impl::sin2x(const d_real<_T>& sinx,
                         const d_real<_T>& cosx)
{
    return mul_pwr2(sinx* cosx, _T(2.0));
}

template <class _T>
_T
cftal::math::impl::cos2x(const _T& sinx, const _T& cosx)
{
    return cosx * cosx - sinx * sinx;
}

template <class _T>
cftal::d_real<_T>
cftal::math::impl::cos2x(const d_real<_T>& sinx,
                         const d_real<_T>& cosx)
{
    return sqr(cosx) - sqr(sinx);
}

template <class _T>
_T
cftal::math::impl::sin4x(const _T& sinx, const _T& cosx)
{
    return sin2x(sin2x(sinx, cosx),
                 cos2x(sinx, cosx));
}

template <class _T>
_T
cftal::math::impl::cos4x(const _T& sinx, const _T& cosx)
{
    return cos2x(sin2x(sinx, cosx),
                 cos2x(sinx, cosx));
}

template <class _T>
_T cftal::math::impl::ivpow<_T>::v(const _T& xx, int p)
{
    _T x(xx);
    _T r(1);
    int n(p < 0 ? -p : p);
    while (1) {
        if (n & 1)
            r*= x;
        n >>= 1;
        if (n == 0)
            break;
        x *= x;
    }
    if (p < 0)
        r= _T(1)/r;
    return r;
}

template <class _T, unsigned _P>
inline
_T cftal::math::impl::ipow<_T, _P>::v(const _T& x)
{
    _T r(ipow<_T, _P/2>::v(x*x));
    if (_P & 1)
        r *= x;
    return r;
}

template <class _T>
inline
_T cftal::math::impl::ipow<_T, 0U>::v(const _T& x)
{
    return _T(1);
}

template <class _T>
inline
_T cftal::math::impl::ipow<_T, 1U>::v(const _T& x)
{
    return x;
}

template <class _T>
inline
_T cftal::math::impl::ipow<_T, 2U>::v(const _T& x)
{
    return x*x;
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_exp(const vf_type& d)
{
    vf_type res;
    if (_NATIVE) {
        res=my_type::native_exp_k(d);
    } else {
        dvf_type xr(my_type::exp_k2(d));
        res=xr.h() + xr.l();
    }

    const vf_type exp_hi_inf= 7.097827128933840867830440e+02;
    const vf_type exp_lo_zero= -7.451332191019412221066887e+02;
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, M_E, res);
    // res = _T::sel(d== vf_type(_T::ninf()), 0.0, res);
    // res = _T::sel(d== vf_type(_T::pinf()), _T::pinf(), res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
exp(const vf_type& d)
{
    return my_type::_exp<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_exp(const vf_type& d)
{
    return my_type::_exp<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_exp2(const vf_type& d)
{
    vf_type res;
    if (_NATIVE) {
        res=my_type::native_exp2_k(d);
    } else {
        dvf_type xr(my_type::exp2_k2(d));
        res=xr.h() + xr.l();
    }
    const vf_type exp2_hi_inf= 1.024000000000000000000000e+03;
    const vf_type exp2_lo_zero= -1.075000000000000000000000e+03;
    res = _T::sel(d <= exp2_lo_zero, 0.0, res);
    res = _T::sel(d >= exp2_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, 2.0, res);
    return res;
}


template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
exp2(const vf_type& d)
{
    return my_type::_exp2<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_exp2(const vf_type& d)
{
    return my_type::_exp2<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_exp10(const vf_type& d)
{
    vf_type res;
    if (_NATIVE) {
        res=my_type::native_exp10_k(d);
    } else {
        dvf_type xr(my_type::exp10_k2(d));
        res=xr.h() + xr.l();
    }
    const vf_type exp10_hi_inf=3.082547155599167467698862e+02;
    const vf_type exp10_lo_zero=-3.236072453387798191215552e+02;
    res = _T::sel(d <= exp10_lo_zero, 0.0, res);
    res = _T::sel(d >= exp10_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, 10.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
exp10(const vf_type& d)
{
    return my_type::_exp10<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_exp10(const vf_type& d)
{
    return my_type::_exp10<true>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
expm1(const vf_type& d)
{
    dvf_type r(my_type::exp_k2(d));
    // res=xr.h() + xr.l();
    dvf_type rm1= r - vf_type(1.0);
    // select is not required
    vf_type res = rm1.h() + rm1.l();
    const vf_type expm1_hi_inf= 7.097827128933840867830440e+02;
    const vf_type expm1_lo_minus_one= -3.742994775023704789873591e+01;
    res = _T::sel(d <= expm1_lo_minus_one, -1.0, res);
    res = _T::sel(d >= expm1_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 0.0, res);
    res = _T::sel(d == 1.0, M_E-1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
sinh(const vf_type& d)
{
    // sinh (x) = 1/2 (exp(x) - exp(-x))
    // cosh (x) = 1/2 (exp(x) + exp(-x));
    // sinh (x+y) = sinh(x)*cosh(y) + cosh(x)*sinh(y)
    // sinh (x-y) = sinh(x)*cosh(y) - cosh(x)*sinh(y)
    // cosh (x+y) = cosh(x)*cosh(y) + sinh(x)*sinh(y)
    // cosh (x-y) = cosh(x)*cosh(y) - sinh(x)*sinh(y)
    // -->
    // sinh (x+x) = sinh(x)*cosh(x) + cosh(x)*sinh(x)
    // sinh (2x) = 2 * sinh(x) * cosh(x)
    dvf_type dh=vf_type(0.5*d);
    dvf_type exph=my_type::exp_k2(dh);
    dvf_type rexph=(vf_type(1.0)/exph);
    dvf_type sinh_xh= mul_pwr2(exph - rexph, vf_type(0.5));
    dvf_type cosh_xh= mul_pwr2(exph + rexph, vf_type(0.5));
    dvf_type sinh_x= mul_pwr2(sinh_xh * cosh_xh, vf_type(2.0));
    vf_type res = sinh_x.h() + sinh_x.l();
    const vf_type sinh_hi_inf= 7.104758600739439771132311e+02;
    const vf_type sinh_lo_inf= -7.104758600739439771132311e+02;
    res = _T::sel(d >= sinh_hi_inf, _T::pinf(), res);
    res = _T::sel(d <= sinh_lo_inf, _T::ninf(), res);
    res = _T::sel(d == 0.0, 0.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
cosh(const vf_type& d)
{
    // sinh (x) = 1/2 (exp(x) - exp(-x))
    // cosh (x) = 1/2 (exp(x) + exp(-x));
    // sinh (x+y) = sinh(x)*cosh(y) + cosh(x)*sinh(y)
    // sinh (x-y) = sinh(x)*cosh(y) - cosh(x)*sinh(y)
    // cosh (x+y) = cosh(x)*cosh(y) + sinh(x)*sinh(y)
    // cosh (x-y) = cosh(x)*cosh(y) - sinh(x)*sinh(y)
    // -->
    // cosh (x+x) = cosh(x)*cosh(x) + sinh(x)*sinh(x)
    // cosh (2x) = 2 * sinh(x)*sinh(x) + 1

    dvf_type dh=vf_type(0.5*d);
    dvf_type exph=my_type::exp_k2(dh);
    dvf_type rexph=(vf_type(1.0)/exph);
    dvf_type two_sinh_xh= exph - rexph;
    dvf_type sinh_xh = mul_pwr2(two_sinh_xh, vf_type(0.5));
    dvf_type cosh_x = mul_pwr2(sqr(sinh_xh), vf_type(2.0)) + vf_type(1.0);
    vf_type res = cosh_x.h() + cosh_x.l();
    const vf_type cosh_hi_inf= 7.104758600739439771132311e+02;
    // const vf_type cosh_lo_inf= -7.104758600739439771132311e+02;
    res = _T::sel(abs(d) >= cosh_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_log(const vf_type& d)
{
    vf_type x;
    if (_NATIVE) {
        x= my_type::native_log_k(d);
    } else {
        dvf_type xr(my_type::log_k2(d));
        x= xr.h() + xr.l();
    }
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    const vf_type log_lo_fin= 4.940656458412465441765688e-324;
    const vf_type log_lo_val= -7.444400719213812180896639e+02;
    x = _T::sel(d == log_lo_fin, log_lo_val, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
log(const vf_type& d)
{
    return my_type::_log<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_log(const vf_type& d)
{
    return my_type::_log<true>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
pow(const vf_type& x, const vf_type& y)
{
    // we have a problem if e is an integer
    dvf_type ln_x(my_type::log_k2(abs(x)));
    dvf_type ln_x_y(ln_x * y);
    dvf_type pow0(my_type::exp_k2(ln_x_y));
    vf_type res(pow0.h() + pow0.l());

    // vmf_type b_zero_and_e_zero((b == vf_type(0)) & (e == vf_type(0)));
    // res = _T::sel(b_zero_and_e_zero, vf_type(1.0), res);

    vmf_type x_lt_z = x < 0.0;
    vf_type yhalf=y*0.5;
    vmf_type y_odd_int= (rint(y) == y) & (rint(yhalf) != yhalf);
    res = _T::sel(x_lt_z & ~y_odd_int, _T::nan(), res);

    vmf_type x_nan = isnan(x);
    res = _T::sel(x_nan, x, res);
    vmf_type y_nan = isnan(y);
    res = _T::sel(y_nan, y, res);
    vmf_type x_one_y_zero= (x == 1.0) | (y == 0.0);
    res = _T::sel(x_one_y_zero, vf_type(1.0), res);


    vmf_type x_zero = x == 0;
    vmf_type y_odd_int_gt_0 = (y > 0.0) & y_odd_int;
    res = _T::sel(x_zero & y_odd_int_gt_0, x, res);
    res = _T::sel(x_zero & (y > 0.0) & ~y_odd_int, vf_type(0.0), res);

    vmf_type x_minus_1 = x == -1.0;
    vmf_type y_inf= isinf(y);
    res = _T::sel(x_minus_1 | y_inf, vf_type(1.0), res);


    res = _T::sel((abs(x) < 1.0) & y_inf & (y < 0.0), _T::pinf(), res);
    res = _T::sel((abs(x) > 1.0) & y_inf & (y < 0.0), vf_type(0.0), res);
    res = _T::sel((abs(x) < 1.0) & y_inf & (y > 0.0), vf_type(0.0), res);
    res = _T::sel((abs(x) > 1.0) & y_inf & (y > 0.0), _T::pinf(), res);

    vmf_type x_inf = isinf(x);
    vmf_type x_n_inf= (x < 0) | x_inf;

    res = _T::sel(x_n_inf & (y < 0.0) & y_odd_int, vf_type(-0.0), res);
    res = _T::sel(x_n_inf & (y < 0.0) & ~y_odd_int, vf_type(+0.0), res);

    res = _T::sel(x_n_inf & y_odd_int_gt_0, _T::ninf(), res);
    res = _T::sel(x_n_inf & (y > 0.0) & ~y_odd_int, _T::pinf(), res);

    res = _T::sel(x_inf & (x > 0) & (y < 0), vf_type(0.0), res);
    res = _T::sel(x_inf & (x > 0) & (y > 0), _T::pinf(), res);

    res = _T::sel(x_zero & (y < 0) & y_odd_int,
                  copysign(vf_type(_T::pinf()), x), res);
    res = _T::sel(x_zero & (y < 0) & ~y_odd_int, _T::pinf(), res);

    res = _T::sel(y==1.0, x, res);


    return res;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
sincos(const vf_type& d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
        if (psin) {
            *psin = sin_cos.first.h() + sin_cos.first.l();
        }
        if (pcos) {
            *pcos = sin_cos.second.h() + sin_cos.second.l();
        }
    }
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
sin(const vf_type& d)
{
    std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
    return sin_cos.first.h() + sin_cos.first.l();
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
cos(const vf_type& d)
{
    std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
    return sin_cos.second.h() + sin_cos.second.l();
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
tan(const vf_type& d)
{
    std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
    dvf_type tn(sin_cos.first / sin_cos.second);
    return tn.h() + tn.l();
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
cot(const vf_type& d)
{
    std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
    dvf_type ct(sin_cos.second / sin_cos.first);
    return ct.h() + ct.l();
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_sincos(const vf_type& d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        std::pair<vf_type, vf_type> sin_cos(
            my_type::native_sin_cos_k(d));
        if (psin) {
            *psin = sin_cos.first;
        }
        if (pcos) {
            *pcos = sin_cos.second;
        }
    }
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_sin(const vf_type& d)
{
    std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
    return sin_cos.first;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_cos(const vf_type& d)
{
    std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
    return sin_cos.second;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_tan(const vf_type& d)
{
    std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
    vf_type tn(sin_cos.first / sin_cos.second);
    return tn;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_cot(const vf_type& d)
{
    std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
    vf_type tn(sin_cos.second / sin_cos.first);
    return tn;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atan2(const vf_type& x, const vf_type& y)
{
    dvf_type r(base_type::atan2_k2(abs(y), x));
    r = dvf_type(mulsign(r.h(), x),
                 mulsign(r.l(), x));
    return x;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atan(const vf_type& x)
{
    return x;
}



// Local Variables:
// mode: c++
// end:
#endif
