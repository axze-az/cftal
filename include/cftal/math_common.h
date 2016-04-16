#if !defined (__CFTAL_MATH_COMMON_H__)
#define __CFTAL_MATH_COMMON_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/divisor.h>
#include <cftal/constants.h>
#include <cftal/mem.h>
#include <cftal/math_func_constants.h>
#include <cftal/math_impl_poly.h>
#include <type_traits>
#include <limits>
#include <utility>
#include <stdexcept>

namespace cftal {

    namespace math {

        namespace impl {

            // returns (y0+y1) = x - N * pi/2
            // the integer results contains
            // only the lower bits of N
            int32_t
            __attribute__((__visibility__("internal")))
            __ieee754_rem_pio2(float x, float *y);


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

        template <typename _FLOAT_T, typename _INT_T>
        struct func_traits;

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct func_core {
            typedef typename _TRAITS_T::vf_type vf_type;
            typedef typename _TRAITS_T::vi_type vi_type;
            typedef typename _TRAITS_T::vmf_type vmf_type;
            typedef typename _TRAITS_T::vmi_type vmi_type;
            typedef d_real<vf_type> dvf_type;

        };

        template <typename _FLOAT_T, typename _TRAITS_T>
        struct func_common : public func_core< _FLOAT_T,
                                               _TRAITS_T> {
            using base_type = func_core<_FLOAT_T, _TRAITS_T>;
            using my_type = func_common<_FLOAT_T, _TRAITS_T>;
            using vf_type = typename base_type::vf_type;
            using vi_type = typename base_type::vi_type;
            using vmf_type = typename base_type::vmf_type;
            using vmi_type = typename base_type::vmi_type;
            using dvf_type = typename base_type::dvf_type;
            using tvf_type = typename base_type::tvf_type;

            using base_type::frexp;
            using base_type::ldexp;
            using base_type::ilogbp1;

            // exp, expm1, sinh, cosh call exp_k2 if native == false
            // or native_exp
            template <bool _NATIVE>
            static vf_type _exp(arg_t<vf_type> vf);
            template <bool _NATIVE>
            static vf_type _exp2(arg_t<vf_type> vf);
            template <bool _NATIVE>
            static vf_type _exp10(arg_t<vf_type> vf);
            template <bool _NATIVE>
            static vf_type _expm1(arg_t<vf_type> vf);
            template <bool _NATIVE>
            static vf_type _sinh(arg_t<vf_type> vf);
            template <bool _NATIVE>
            static vf_type _cosh(arg_t<vf_type> vf);

            // log _call log_k2 if native == false, or native_log
            template <bool _NATIVE>
            static vf_type _log(arg_t<vf_type> cf);
            template <bool _NATIVE>
            static vf_type _log1p(arg_t<vf_type> cf);
            template <bool _NATIVE>
            static vf_type _log10(arg_t<vf_type> cf);
            template <bool _NATIVE>
            static vf_type _log2(arg_t<vf_type> cf);

            // exp, expm1, sinh, cosh call exp_k2
            static vf_type exp(arg_t<vf_type> vf);
            static vf_type exp2(arg_t<vf_type> vf);
            static vf_type exp10(arg_t<vf_type> vf);
            static vf_type expm1(arg_t<vf_type> vf);
            static vf_type sinh(arg_t<vf_type> vf);
            static vf_type cosh(arg_t<vf_type> vf);

            // native exp, expm1, sinh, cosh call exp_k
            static vf_type native_exp(arg_t<vf_type> vf);
            static vf_type native_exp2(arg_t<vf_type> vf);
            static vf_type native_exp10(arg_t<vf_type> vf);
            static vf_type native_expm1(arg_t<vf_type> vf);
            static vf_type native_sinh(arg_t<vf_type> vf);
            static vf_type native_cosh(arg_t<vf_type> vf);

            // log calls log_k2
            static vf_type log(arg_t<vf_type> vf);
            // native log calls native_log_k
            static vf_type native_log(arg_t<vf_type> vf);

            // log calls log_k2
            static vf_type log1p(arg_t<vf_type> vf);
            // native log calls native_log_k
            static vf_type native_log1p(arg_t<vf_type> vf);

            static vf_type log10(arg_t<vf_type> vf);
            static vf_type native_log10(arg_t<vf_type> vf);
            static vf_type log2(arg_t<vf_type> vf);
            static vf_type native_log2(arg_t<vf_type> vf);

            // pow calls exp_k2 and log_k2
            static
            vf_type
            pow(arg_t<vf_type> b, arg_t<vf_type> e);

            // done by squaring
            static
            vf_type
            pow(arg_t<vf_type> b, arg_t<vi_type> e);

            // sincos, sin, cos, tan and cot call
            // sin_cos_k
            static void sincos(arg_t<vf_type> vf,
                               vf_type* psin,
                               vf_type* pcos);
            static vf_type sin(arg_t<vf_type> vf);
            static vf_type cos(arg_t<vf_type> vf);
            static vf_type tan(arg_t<vf_type> vf);
            static vf_type cot(arg_t<vf_type> vf);
            // sincos, sin, cos, tan and cot call
            // native_sin_cos_k
            static void native_sincos(arg_t<vf_type> vf,
                                      vf_type* psin,
                                      vf_type* pcos);
            static vf_type native_sin(arg_t<vf_type> vf);
            static vf_type native_cos(arg_t<vf_type> vf);
            static vf_type native_tan(arg_t<vf_type> vf);
            static vf_type native_cot(arg_t<vf_type> vf);

            // atan2, atan, ... call atan2_k2
            static vf_type atan2(arg_t<vf_type> x,
                                 arg_t<vf_type> y);
            static vf_type atan(arg_t<vf_type> x);
            static vf_type asin(arg_t<vf_type> x);
            static vf_type acos(arg_t<vf_type> x);
            static vf_type asinh(arg_t<vf_type> x);
            static vf_type acosh(arg_t<vf_type> x);
            static vf_type atanh(arg_t<vf_type> x);
        };


        template <typename _FLOAT_T, typename _TRAITS_T>
        struct func : public func_common<_FLOAT_T, _TRAITS_T> {
            typedef typename _TRAITS_T::vf_type vf_type;
            typedef typename _TRAITS_T::vi_type vi_type;
            typedef typename _TRAITS_T::vmf_type vmf_type;
            typedef typename _TRAITS_T::vmi_type vmi_type;
        };


        namespace impl {



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

            // unsigned integer power
            template <class _T>
            struct powvu {
                static _T v(const _T& xx, unsigned p);
            };

            // integer power
            template <class _T>
            struct powvi {
                static _T v(const _T& xx, int p);
            };

            // unsigned integer pow
            template <class _T, unsigned _P>
            struct powu {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==0
            template <class _T>
            struct powu<_T, 0U> {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==1
            template <class _T>
            struct powu<_T, 1U> {
                static _T v(const _T& x);
            };

            // unsigned integer pow, specialized for _P==2
            template <class _T>
            struct powu<_T, 2U> {
                static _T v(const _T& x);
            };

            // n-th root calculator: newton raphson step with n variable
            template <class _RT, class _T=_RT>
            struct nth_root_vnr {
                static
                _RT v(const _T& xi, const _T& x, unsigned r);
            };

            // n-th root calculator: newton raphson step with n=_R
            template <unsigned _R, class _RT, class _T = _RT>
            struct nth_root_nr : public nth_root_vnr<_T> {
                // one newton raphson step
                static
                _RT v(const _T& xi, const _T& x);
            };

            // n-th root calculator: halley step with n=_R
            template <unsigned _R, class _RT, class _T = _RT>
            struct nth_root_halley : public nth_root_vnr<_T> {
                // one halley step
                static _RT v(const _T& xi, const _T& x);
            };

            template <unsigned _R, typename _T>
            struct nth_root_approx {
                // return a guess for root _R in [2^-R, 1)
                static _T v(_T x) { return _T(0.75); }
            };

            template <typename _T>
            struct nth_root_approx<3, _T> {
                static _T v(_T x);
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

            // nth root implementation for double/float
            template <typename _FLOAT_T, typename _TRAITS,
                      unsigned _R>
            struct nth_root : public func<_FLOAT_T, _TRAITS> {

                using vf_type = typename _TRAITS::vf_type;
                using vi_type = typename _TRAITS::vi_type;
                using vmf_type= typename _TRAITS::vmf_type;
                using vmi_type = typename _TRAITS::vmi_type;
                using dvf_type = typename _TRAITS::dvf_type;

                using base_type = func<_FLOAT_T, _TRAITS>;
                using base_type::frexp;
                using base_type::ldexp;
                using base_type::ilogbp1;
                using base_type::scale_exp_k;

                template <unsigned _STEPS=6>
                static vf_type v(arg_t<vf_type> f);
            };
#if 1
            // specialization for cubic root
            template <typename _FLOAT_T, typename _TRAITS>
            struct nth_root<_FLOAT_T, _TRAITS, 3>
                : public func<_FLOAT_T, _TRAITS> {

                using vf_type = typename _TRAITS::vf_type;
                using vi_type = typename _TRAITS::vi_type;
                using vmf_type= typename _TRAITS::vmf_type;
                using vmi_type = typename _TRAITS::vmi_type;
                using dvf_type = typename _TRAITS::dvf_type;

                using base_type = func<_FLOAT_T, _TRAITS>;
                using base_type::frexp;
                using base_type::ldexp;
                using base_type::ilogbp1;
                using base_type::scale_exp_k;

                template <unsigned _NR_STEPS=6>
                static
                vf_type
                v(arg_t<vf_type> x);
            };
#endif
        } // impl

        // integer power with constant _I
        template <int _I, class _T>
        _T pow(const _T& x) {
            const unsigned _N= _I < 0 ? -_I : _I;
            _T r=impl::powu<_T, _N>::v(x);
            if (_I<0)
                r=_T(1)/r;
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
_T
cftal::math::impl::powvu<_T>::v(const _T& xx, unsigned n)
{
    _T x(xx);
    _T r(1);
    while (1) {
        if (n & 1)
            r*= x;
        n >>= 1;
        if (n == 0)
            break;
        x *= x;
    }
    return r;
}

template <class _T>
_T
cftal::math::impl::powvi<_T>::v(const _T& xx, int i)
{
    unsigned n= i < 0 ? -i : i;
    _T r=powvu<_T>::v(xx, n);
    if (i<0)
        r= _T(1)/r;
    return r;
}


template <class _T, unsigned _P>
inline
_T
cftal::math::impl::powu<_T, _P>::v(const _T& x)
{
    _T r(powu<_T, _P/2>::v(x*x));
    if (_P & 1)
        r *= x;
    return r;
}

template <class _T>
inline
_T
cftal::math::impl::powu<_T, 0U>::v(const _T& x)
{
    return _T(1);
}

template <class _T>
inline
_T
cftal::math::impl::powu<_T, 1U>::v(const _T& x)
{
    return x;
}

template <class _T>
inline
_T
cftal::math::impl::powu<_T, 2U>::v(const _T& x)
{
    return x*x;
}

template <class _RT, class _T>
_RT
cftal::math::impl::nth_root_vnr<_RT, _T>::
v(const _T& xi, const _T& x, unsigned r)
{
    const _T rr(r);
    _T x_pow_nm1(powvu<_T>::v(xi, r-1));
    _T en( x - xi * x_pow_nm1);
    _T den(rr * x_pow_nm1);
    _T xip1( xi + en / den);
    return xip1;
};


template <unsigned _R, class _RT, class _T>
_RT
cftal::math::impl::nth_root_nr<_R, _RT, _T>::v(const _T& xi, const _T& x)
{
#if 1
    const _T rcp_r(1.0/_R);
    _RT x_pow_nm1=powu<_RT, _R-1>::v(_RT(xi));
    _RT corr = rcp_r*(xi-x/x_pow_nm1);
    _RT xip1 = xi - corr;
    return xip1;
#else
    const _T r(_R);
    _RT x_pow_nm1(powu<_RT, _R-1>::v(xi));
    _RT en( x - xi * x_pow_nm1);
    _RT den(r * x_pow_nm1);
    _RT xip1( xi + en / den);
    return xip1;
#endif
};

template <unsigned _R, class _RT, class _T>
_RT
cftal::math::impl::nth_root_halley<_R, _RT, _T>::v(const _T& xi, const _T& x)
{
    const _T r(_R);
    const _T two(2.0);
    _RT x_pow(powu<_RT, _R>::v(xi));
    _RT en(_T(two* xi) * (x - x_pow));
    _RT den(r * (x+x_pow) - x + x_pow);
    _RT xip1(xi + en /den);
    return xip1;
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_exp(arg_t<vf_type> d)
{
    vf_type res=base_type::exp_k(d, false);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp_hi_inf= fc::exp_hi_inf;
    const vf_type exp_lo_zero= fc::exp_lo_zero;
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
exp(arg_t<vf_type> d)
{
    return my_type::_exp<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_exp(arg_t<vf_type> d)
{
    return my_type::_exp<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_exp2(arg_t<vf_type> d)
{
    vf_type res=base_type::exp2_k(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp2_hi_inf= fc::exp2_hi_inf;
    const vf_type exp2_lo_zero= fc::exp2_lo_zero;
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
exp2(arg_t<vf_type> d)
{
    return my_type::_exp2<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_exp2(arg_t<vf_type> d)
{
    return my_type::_exp2<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_exp10(arg_t<vf_type> d)
{
    vf_type res=base_type::exp10_k(d);
    using fc= func_constants<_FLOAT_T>;
    const vf_type exp10_hi_inf=fc::exp10_hi_inf;
    const vf_type exp10_lo_zero=fc::exp10_lo_zero;
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
exp10(arg_t<vf_type> d)
{
    return my_type::_exp10<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_exp10(arg_t<vf_type> d)
{
    return my_type::_exp10<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_expm1(arg_t<vf_type> d)
{
    vf_type res = base_type::exp_k(d, true);
    using fc= func_constants<_FLOAT_T>;
    const vf_type expm1_hi_inf= fc::expm1_hi_inf;
    const vf_type expm1_lo_minus_one= fc::expm1_lo_minus_one;
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
expm1(arg_t<vf_type> d)
{
    return _expm1<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_expm1(arg_t<vf_type> d)
{
    return _expm1<true>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
sinh(arg_t<vf_type> x)
{
    // sinh (x) = 1/2 (exp(x) - exp(-x))
    //          = (expm1(x) + (expm1(x)/(expm1(x)+1))/2;
    // cosh (x) = 1/2 (exp(x) + exp(-x));
    // sinh (x+y) = sinh(x)*cosh(y) + cosh(x)*sinh(y)
    // sinh (x-y) = sinh(x)*cosh(y) - cosh(x)*sinh(y)
    // cosh (x+y) = cosh(x)*cosh(y) + sinh(x)*sinh(y)
    // cosh (x-y) = cosh(x)*cosh(y) - sinh(x)*sinh(y)
    // -->
    // sinh (x+x) = sinh(x)*cosh(x) + cosh(x)*sinh(x)
    // sinh (2x) = 2 * sinh(x) * cosh(x)
    vf_type h= copysign(vf_type(0.5), x);
    vf_type absx = abs(x);
    using fc=func_constants<_FLOAT_T>;
    vmf_type x_large = absx >= fc::exp_hi_inf;
    vf_type xx= _T::sel(x_large, 0.5*absx, absx);
    vf_type t= base_type::exp_k(xx, true);
    vf_type t1= t+1;
    vf_type sinh_lt_1 = h * (2*t - t*t/(t1));
    vf_type sinh_ge_1 = h * (t + t/(t1));
    // vf_type sinh_l_h= (t1 - 1/t1)*0.5; // --> t1*0.5
    // vf_type cosh_l_h= (t1 + 1/t1)*0.5; // --> t1*0.5
    // here we produce most of the 2 ulp deviations:
    vf_type sinh_l= copysign(vf_type(t1 * (t1*0.5)), x);
    vf_type sinh_x = _T::sel(absx<1.0, sinh_lt_1, sinh_ge_1);
    sinh_x = _T::sel(x_large, sinh_l, sinh_x);
    vf_type res = sinh_x;
    const vf_type sinh_hi_inf= fc::sinh_hi_inf;
    const vf_type sinh_lo_inf= fc::sinh_lo_inf;
    res = _T::sel(x >= sinh_hi_inf, _T::pinf(), res);
    res = _T::sel(x <= sinh_lo_inf, _T::ninf(), res);
    res = _T::sel(x == 0.0, 0.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
cosh(arg_t<vf_type> x)
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
    vf_type absx = abs(x);
    using fc=func_constants<_FLOAT_T>;
    vmf_type x_large = absx >= fc::exp_hi_inf;
    vf_type xx= _T::sel(x_large, 0.5*absx, absx);
    vf_type t= base_type::exp_k(xx, true);
    vf_type t1= t+1;
    vf_type cosh_lt_log2 = 1 + t * t/(2*t1);
    vf_type cosh_ge_log2 = 0.5 * (t1 + 1/t1);
    // here we produce most of the 2 ulp deviations:
    vf_type cosh_l= t1 * (t1*0.5);
    vf_type cosh_x = _T::sel(absx<M_LN2, cosh_lt_log2, cosh_ge_log2);
    cosh_x = _T::sel(x_large, cosh_l, cosh_x);
    vf_type res = cosh_x;
    const vf_type cosh_hi_inf= fc::cosh_hi_inf;
    res = _T::sel(absx >= cosh_hi_inf, _T::pinf(), res);
    res = _T::sel(x == 0.0, 1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_log(arg_t<vf_type> d)
{
    vf_type x = base_type::log_k(d);
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    // using fc= func_constants<_FLOAT_T>;
    // const vf_type log_lo_fin= fc::log_lo_fin;
    // const vf_type log_lo_val= fc::log_lo_val;
    // x = _T::sel(d == log_lo_fin, log_lo_val, x);
    return x;
}


template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
log(arg_t<vf_type> d)
{
    return my_type::_log<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_log(arg_t<vf_type> d)
{
    return my_type::_log<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_log1p(arg_t<vf_type> d)
{
    vf_type x=base_type::log1p_k(d);
    // double log1p(double x)
    // {
    //    double u = 1.+x;
    //    if (u == 1.)
    //        return x;
    //    else
    //        return log(u)*x/(u-1.);
    // }
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < -1.0) x = NAN;
    x = _T::sel(d < vf_type(-1.0), vf_type(_T::nan()), x);
    // if (d == -1.0) x = -INFINITY;
    x = _T::sel(d == vf_type(-1.0), ninf, x);
    // NAN --> n_and_1
    x = _T::sel(isnan(d), d, x);
    return x;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
log1p(arg_t<vf_type> d)
{
    return my_type::_log1p<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_log1p(arg_t<vf_type> d)
{
    return my_type::_log1p<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_log10(arg_t<vf_type> d)
{
    vf_type x=base_type::log10_k(d);
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

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
log10(arg_t<vf_type> d)
{
    return my_type::_log10<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_log10(arg_t<vf_type> d)
{
    return my_type::_log10<true>(d);
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_log2(arg_t<vf_type> d)
{
    vf_type x=base_type::log2_k(d);
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

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
log2(arg_t<vf_type> d)
{
    return my_type::_log2<false>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
native_log2(arg_t<vf_type> d)
{
    return my_type::_log2<true>(d);
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
pow(arg_t<vf_type> x, arg_t<vf_type> y)
{
#if 1
    return x+y;
#else
    // we have a problem if e is an integer
    dvf_type ln_x(my_type::log_k2(abs(x), vf_type(0)));
    dvf_type ln_x_y(ln_x * y);
    dvf_type pow0(my_type::exp_k2(ln_x_y.h(), ln_x_y.l(), false));
    vf_type res(pow0.h() + pow0.l());

    using fc=func_constants<_FLOAT_T>;
    const vf_type& d= ln_x_y.h();
    const vf_type exp_hi_inf= fc::exp_hi_inf;
    const vf_type exp_lo_zero= fc::exp_lo_zero;
    res = _T::sel(d <= exp_lo_zero, 0.0, res);
    res = _T::sel(d >= exp_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    res = _T::sel(d == 1.0, M_E, res);

    // guess the result if the calculation failed
    vmf_type res_nan = isnan(res);
    vmf_type abs_x_lt_1 = abs(x) < 1.0;
    vmf_type y_gt_1 = y > 1.0;
    res = _T::sel(res_nan, _T::pinf(), res);
    res = _T::sel(res_nan & abs_x_lt_1 & y_gt_1, 0.0, res);
    res = _T::sel(res_nan & (~abs_x_lt_1) & (~y_gt_1), 0.0, res);

    vmf_type y_is_int = rint(y) == y;
    vf_type y_half=0.5 *y;
    vmf_type y_is_odd = y_is_int & (rint(y_half) != y_half);

    vf_type res_fac= _T::sel(y_is_odd, vf_type(-1), vf_type(1));
    res_fac = _T::sel(~y_is_int, _T::nan(), res_fac);
    res_fac = _T::sel(x >= 0, vf_type(1), res_fac);
    res *= res_fac;

    vf_type efx= (abs(x) -1) * _T::sel(y<0, vf_type(-1), vf_type(1));

    vmf_type y_inf= isinf(y);
    vf_type t= _T::sel(efx==0.0, vf_type(1), _T::pinf());
    t = _T::sel(efx < 0.0, vf_type(0.0), t);
    res = _T::sel(y_inf, t, res);

    vmf_type x_zero = x == 0.0;
    vmf_type x_inf_or_zero= isinf(x) | x_zero;
    t= _T::sel(x_zero, -y, y);
    t= _T::sel(t < 0.0, vf_type(0), _T::pinf());
    vf_type sgn_x= copysign(vf_type(1), x);
    vf_type t1=_T::sel(y_is_odd, sgn_x, vf_type(1));
    t1 *= t;
    res = _T::sel(x_inf_or_zero, t1, res);

    res = _T::sel(isnan(x) | isnan(y), _T::nan(), res);
    res = _T::sel((y==0.0) | (x==1.0), vf_type(1), res);

#if 0
    res = xisnan(result) ? INFINITY : res;
    res *=  (x >= 0 ? 1 : (!yisint ? NAN : (yisodd ? -1 : 1)));

    double efx = mulsign(xfabs(x) - 1, y);
    if (xisinf(y)) res = efx < 0 ? 0.0 : (efx == 0 ? 1.0 : INFINITY);
    if (xisinf(x) || x == 0) res = (yisodd ? sign(x) : 1) * ((x == 0 ? -y : y) < 0 ? 0 : INFINITY);
    if (xisnan(x) || xisnan(y)) res = NAN;
    if (y == 0 || x == 1) res = 1;

    return res;
#endif
    return res;
#endif
}

template <typename _FLOAT_T, typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
pow(arg_t<vf_type> b, arg_t<vi_type> e)
{
    using _T = _TRAITS_T;
    vmi_type e_lt_z = e < vi_type(0);
    vmf_type f_e_lt_z = _T::vmi_to_vmf(e_lt_z);
    vi_type n= _T::sel(e_lt_z, -e, e);
    vf_type x= _T::sel(f_e_lt_z, vf_type(1.0)/b, b);
    vf_type r= vf_type(1.0);

    vmi_type n_ne_0 = n != vi_type(0);
    while (any_of(n_ne_0)) {
        vmi_type n_and_1 = (n & vi_type(1)) != vi_type(0);
        vmf_type f_n_and_1 = _T::vmi_to_vmf(n_and_1);
        r = _T::sel(f_n_and_1, r*x, r);
        n >>= 1;
        n_ne_0 = n != vi_type(0);
        vmf_type f_n_ne_0 = _T::vmi_to_vmf(n_ne_0);
        // clear vector entries not required any more
        x = _T::sel(f_n_ne_0, x*x, 0);
    }
    return r;
}


template <typename _FLOAT_T,
          typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
sincos(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        base_type::sin_cos_k(d, psin, pcos);
    }
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
sin(arg_t<vf_type> d)
{
    vf_type s;
    base_type::sin_cos_k(d, &s, nullptr);
    return s;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
cos(arg_t<vf_type> d)
{
    vf_type c;
    base_type::sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
tan(arg_t<vf_type> d)
{
    vf_type t=base_type::tan_k(d);
    t = _TRAITS_T::sel(isinf(d) | isnan(d),
                       copysign(vf_type(_TRAITS_T::nan()), d),
                       t);
    return t;
}


template <typename _FLOAT_T,
          typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_sincos(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        base_type::sin_cos_k(d, psin, pcos);
    }
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_sin(arg_t<vf_type> d)
{
    vf_type s;
    base_type::sin_cos_k(d, &s, nullptr);
    return s;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_cos(arg_t<vf_type> d)
{
    vf_type c;
    base_type::sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_tan(arg_t<vf_type> d)
{
    vf_type tn=base_type::tan_k(d);
    return tn;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atan2(arg_t<vf_type> y, arg_t<vf_type> x)
{
#if 1
    vf_type r=base_type::atan2_k(y, x);

    using _T = _TRAITS_T;

    vmf_type y_zero = y==vf_type(0);
    vmf_type x_inf = isinf(x);
    vmf_type y_inf = isinf(y);
    vmf_type x_zero = x==vf_type(0);
    vmf_type x_nan = isnan(x);
    vmf_type y_nan = isnan(y);

    vmf_type special = y_zero | x_inf | y_inf | x_zero | x_nan | y_nan;

    if (any_of(special)) {
        vf_type y_sgn = copysign(vf_type(1), y);
        vmf_type y_p= y_sgn == vf_type(1.0);
        vmf_type y_n= y_sgn == vf_type(-1.0);
        vmf_type y_p_zero = y_p & y_zero;
        vmf_type y_n_zero = y_n & y_zero;
        vmf_type y_gt_z = y>vf_type(0);
        vmf_type y_lt_z = y<vf_type(0);
        vmf_type y_p_inf = y_inf & y_p;
        vmf_type y_n_inf = y_inf & y_n;

        vf_type x_sgn = copysign(vf_type(1), x);
        vmf_type x_p= x_sgn == vf_type(1.0);
        vmf_type x_n= x_sgn == vf_type(-1.0);
        vmf_type x_p_zero = x_p & x_zero;
        vmf_type x_n_zero = x_n & x_zero;
        vmf_type x_p_inf = x_p & x_inf;
        vmf_type x_n_inf = x_n & x_inf;
        vmf_type x_gt_z = x>vf_type(0);
        vmf_type x_lt_z = x<vf_type(0);
        vmf_type x_ge_p_z = x_p_zero | x_gt_z;
        vmf_type x_le_n_z = x_n_zero | x_lt_z;

        //  atan2(+0, x>=0) = +0
        r = _T::sel(y_p_zero & x_ge_p_z, y, r);
        //  atan2(-0, x>=0) = -0
        r = _T::sel(y_n_zero & x_ge_p_z, y, r);
        //  atan2(+0, x<=-0) = +Pi
        r = _T::sel(y_p_zero & x_le_n_z, +M_PI, r);
        //  atan2(-0, x<=-0) = -Pi
        r = _T::sel(y_n_zero & x_le_n_z, -M_PI, r);
        //  atan2(y>0, 0) = +Pi/2
        r = _T::sel(y_gt_z & x_zero, +M_PI/2, r);
        //  atan2(y<0, 0) = -Pi/2
        r = _T::sel(y_lt_z & x_zero, -M_PI/2, r);
        //  atan2(y, +Inf) = 0
        r = _T::sel(x_p_inf, 0, r);
        //  atan2(y>0, -Inf) = +Pi
        r = _T::sel(y_gt_z & x_n_inf, M_PI, r);
        //  atan2(y<0, -Inf) = -Pi
        r = _T::sel(y_lt_z & x_n_inf, -M_PI, r);
        //  atan2(+Inf, x) = +Pi/2
        r = _T::sel(y_p_inf, M_PI/2, r);
        //  atan2(-Inf, x) = -Pi/2
        r= _T::sel(y_n_inf, -M_PI/2, r);
        //  atan2(+Inf, +Inf) = +Pi/4
        r = _T::sel(y_p_inf & x_p_inf, +M_PI/4, r);
        //  atan2(-Inf, +Inf) = -Pi/4
        r = _T::sel(y_n_inf & x_p_inf, -M_PI/4, r);
        //  atan2(+Inf, -Inf) = 3Pi/4
        r = _T::sel(y_p_inf & x_n_inf, (3*M_PI)/4, r);
        //  atan2(-Inf, -Inf) = -3Pi/4
        r = _T::sel(y_n_inf & x_n_inf, -(3*M_PI)/4, r);
        //  atan2(y, NaN) = NaN
        //  atan2(NaN, x) = NaN
        r = _T::sel(x_nan | y_nan, _T::nan(), r);
    }
    return r;
#else
    // r = dvf_type(mulsign(r.h(), x),
    //             mulsign(r.l(), x));
    // r = mulsign(r, x);
    vf_type sgn_x = copysign(vf_type(1.0), x);
    vf_type r = rd.h();
    r *= sgn_x;

    vmf_type x_is_inf = isinf(x);
    vmf_type y_is_inf = isinf(y);

    // if (xisinf(x) || x == 0)
    //    r = M_PI/2 - (xisinf(x) ? (sign(x) * (M_PI  /2)) : 0);
    vf_type t1= _TRAITS_T::sel(x_is_inf, sgn_x * M_PI/2, 0);
    r = _TRAITS_T::sel(x_is_inf | (x==0), M_PI/2 - t1, r);
    // if (xisinf(y)          )
    //    r = M_PI/2 - (xisinf(x) ? (sign(x) * (M_PI*1/4)) : 0);
    vf_type t2= _TRAITS_T::sel(x_is_inf, sgn_x * M_PI/4, 0);
    r = _TRAITS_T::sel(y_is_inf, M_PI/2 - t2, r);
    // if (             y == 0) r = (sign(x) == -1 ? -M_PI : 0);
    vf_type t3= _TRAITS_T::sel(sgn_x == -1.0, -vf_type(M_PI), vf_type(0));
    r = _TRAITS_T::sel(y==0, t3, r);
    // return xisnan(x) || xisnan(y) ? NAN : mulsign(r, y);
    vf_type sgn_y= copysign(vf_type(1.0), y);
    r *= sgn_y;
    r = _TRAITS_T::sel(isnan(x) | isnan(y), _TRAITS_T::nan(), r);
    return r;
#endif
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atan(arg_t<vf_type> x)
{
    vf_type r= base_type::atan_k(x);
    // r=copysign(r, x);
    r=_TRAITS_T::sel(x==vf_type(0), x, r);
    r=_TRAITS_T::sel(isinf(x), copysign(vf_type(M_PI/2), x) , r);
    r=_TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
asin(arg_t<vf_type> x)
{
    // vf_type xt= (vf_type(1) - x)*(vf_type(1) + x);
    // vf_type sqrt_xt= sqrt(xt);
    // vf_type asin_x= x/(1+sqrt_xt);
    // vf_type r=2.0*base_type::atan_k(asin_x);
    vf_type r=base_type::asin_k(x);
    r = _TRAITS_T::sel(x == vf_type(-1), -M_PI/2, r);
    r = _TRAITS_T::sel(x == vf_type(1), M_PI/2, r);
    r = _TRAITS_T::sel(x < vf_type(-1), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x > vf_type(1), _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
acos(arg_t<vf_type> x)
{
    vf_type r=base_type::acos_k(x);
    r = _TRAITS_T::sel(x == vf_type(-1), M_PI, r);
    r = _TRAITS_T::sel(x == vf_type(1), 0, r);
    r = _TRAITS_T::sel(x == vf_type(0), M_PI/2, r);
    r = _TRAITS_T::sel(x < vf_type(-1), -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x > vf_type(1), _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
asinh(arg_t<vf_type> x)
{
    vf_type r=base_type::asinh_k(x);
    r = _TRAITS_T::sel(isinf(x), x, r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
acosh(arg_t<vf_type> x)
{
    vf_type r=base_type::acosh_k(x);
    r = _TRAITS_T::sel(x < 1.0, _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x== _TRAITS_T::pinf(), x, r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atanh(arg_t<vf_type> x)
{
    vf_type r=base_type::atanh_k(x);
    r = _TRAITS_T::sel(x == -1.0, _TRAITS_T::ninf(), r);
    r = _TRAITS_T::sel(x < -1.0, -_TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(x == 1.0, _TRAITS_T::pinf(), r);
    r = _TRAITS_T::sel(x >  1.0, _TRAITS_T::nan(), r);
    r = _TRAITS_T::sel(isnan(x), x, r);
    return r;
}

template <typename _T>
_T
cftal::math::impl::nth_root_approx<3, _T>::v(_T x)
{
#if 0
    // maximum error 6.774866715814284b-4 in [2^-3, 2^0)
    static const _T a[]= {
        +1.431375762469744e0 /* x^5 */,
        -4.691579063121689e0 /* x^4 */,
        +6.15346734720791e0  /* x^3 */,
        -4.287580954173022e0 /* x^2 */,
        +2.101233104609554e0 /* x^1 */
        +2.937612896790845e-1 /* x^0 */
    };
    // maximum error 2.651222503616686b-4 in [2^-3, 2^0)
    static const _T a[]={
        -2.462358311592589e0 /* x^6 */,
        +9.368149930890834e0 /* x^5 */,
        -1.463283356717269e1 /* x^4 */,
        +1.226301448576061e1 /* x^3 */,
        -6.200836296768183e0 /* x^2 */,
        +2.38655227371457e0  /* x^1 */,
        +2.780463629170873e-1 /* x^0 */
    };
    // maximum error 1.070325426252539b-4 in [2^-3, 2^0)
    static const _T a[]={
        +4.407940728992934e0, // x^7
        -1.914086520846586e1, // x^6
        +3.491722222528436e1, // x^5
        -3.498415183424161e1, // x^4
        +2.127308275625481e1, // x^3
        -8.394369046537729e0, // x^2
        +2.656039417162971e0, // x
        +2.652079940927634e-1
    };
    // maximum error 4.395396547265176b-5 in [2^-3, 2^0)
    static const _T a[]= {
        -8.082321821879138e0  /* x^8*/ ,
        +3.951186826818802e1  /* x^7*/ ,
        -8.271122758768972e1  /* x^6*/ ,
        +9.719626611621892e1  /* x^5*/ ,
        -7.082056933547489e1  /* x^4*/ ,
        +3.357862597275239e1  /* x^3*/ ,
        -1.083848841889517e1  /* x^2*/ ,
        +2.911304691900277e0  /* x^1 */ ,
        +2.544981609138214e-1 /* x^0 */
    };
    // maximum error 7.794566660340572b-6 in [2^-3, 2^0)
    static const _T a[] = {
        -2.893793723365649e1, // x^10
        +1.733287884346741e2, // x^9
        -4.574701604941978e2, // x^8
        +7.010147297308644e2, // x^7
        -6.921659085115613e2, // x^6
        +4.62560031574252e2, // x^5
        -2.14374717173087e2, // x^4
        +6.988046400220901e1, // x^3
        -1.646473046613031e1, // x^2
        +3.392112926339188e0, // x^1
        2.373194157275016e-1
    };
    // maximum error 1.429853296572885b-6 in [2^-3, 2^0)
    static const _T a[]= {
        -1.086223987436328e2, // x^12
        +7.713403390094619e2, // x^11
        -2.462544006306743e3, // x^10
        +4.672629599539334e3, // x^9
        -5.870886414752144e3, // x^8
        +5.152410559174283e3, // x^7
        -3.248621593913108e3, // x^6
        +1.492090997687755e3, // x^5
        -5.01902172146935e2, // x^4
        +1.240088668410992e2, // x^3
        -2.296653315520015e1, // x^2
        +3.838691064614486e0, // x
        +2.240642713619926e-1
    };
    // maximum error 1.070325426252539b-4 in [2^-3, 2^0)
    static const _T a[]={
        +4.407940728992934e0, // x^7
        -1.914086520846586e1, // x^6
        +3.491722222528436e1, // x^5
        -3.498415183424161e1, // x^4
        +2.127308275625481e1, // x^3
        -8.394369046537729e0, // x^2
        +2.656039417162971e0, // x
        +2.652079940927634e-1
    };
    _T g=poly(x, a);
#endif
    using vf_type = _T;
  // coefficients for cbrt generated by sollya
    // x^4
    const vf_type cbrt_c4=-0x1.c517452d08a9ep-1;  // 0xbfec517452d08a9e
    // x^3
    const vf_type cbrt_c3=0x1.3a0af15bcfa1ap1;  // 0x4003a0af15bcfa1a
    // x^2
    const vf_type cbrt_c2=-0x1.5724904ed69cap1;  // 0xc005724904ed69ca
    // x^1
    const vf_type cbrt_c1=0x1.cbf973dd98759p0;  // 0x3ffcbf973dd98759
    // x^0
    const vf_type cbrt_c0=0x1.412cc5a825c41p-2;  // 0x3fd412cc5a825c41
    _T g= poly(x,
               cbrt_c4,
               cbrt_c3,
               cbrt_c2,
               cbrt_c1,
               cbrt_c0);
    return g;
};

template <typename _FLOAT_T, typename _TRAITS, unsigned _R>
template <unsigned _STEPS>
typename cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, _R>::vf_type
cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, _R>::v(arg_t<vf_type> x)
{
    using std::abs;
    vf_type xp=abs(x);
    // m in [0.5, 1)
    const divisor<vi_type, int32_t> idivr(_R);
    vi_type e = ilogbp1(xp);
    vi_type en= e / idivr;
    vi_type rn= remainder(e, vi_type(_R), en);
    // select rnc so that rnc [-R, -R+1, -R2,-1,0]
    vmi_type rngt0 = rn > 0;
    vi_type rnc= _TRAITS::sel(rngt0, rn-vi_type(_R), rn);
    vi_type re= _TRAITS::sel(rngt0, en+1, en);
    vi_type sc= rnc - e;
    // mm0 in [2^-R, 2^0)
    vf_type mm0 = ldexp(xp, sc);
    vf_type mm = nth_root_approx<_R, vf_type>::v(mm0);
    if (_STEPS>1) {
        using step_t= nth_root_halley<_R, vf_type, vf_type>;
        for (uint32_t i=0; i<_STEPS-1; ++i) {
            mm= step_t::v(mm, mm0);
        }
    }
    if (_STEPS>0) {
        if (_R==3) {
            using step_t= nth_root_nr<_R, vf_type, vf_type>;
            mm= step_t::v(mm, mm0);
        } else {
            using step_t=nth_root_nr<_R, dvf_type, vf_type>;
            dvf_type dmm;
            for (uint32_t i=_STEPS-1; i< _STEPS; ++i)
                dmm = step_t::v(mm, mm0);
            mm = dmm.h() + dmm.l();
        }
    }
    // scale back
    vf_type res=ldexp(mm, re);
    if ((_R&1) != 0) {
        // restore sign
        res=copysign(res, x);
    }
    vmf_type is_zero_or_inf_or_nan=
        (x == vf_type(0)) | isinf(x) | isnan(x);
    res=_TRAITS::sel(is_zero_or_inf_or_nan,
                     x, res);
    if ((_R&1) == 0) {
        res = _TRAITS::sel(x<0, _TRAITS::nan(), res);
    }
    return res;
}

#if 1
template <typename _FLOAT_T, typename _TRAITS>
template <unsigned _STEPS>
typename cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, 3>::vf_type
cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, 3>::v(arg_t<vf_type> x)
{
#if 1
    vf_type r=base_type::cbrt_k(x);
    vmf_type is_zero_or_inf_or_nan=
        (x == vf_type(0)) | isinf(x) | isnan(x);
    r=_TRAITS::sel(is_zero_or_inf_or_nan, x, r);
    return r;
#else
    vf_type xp=abs(x);
    vi_type e3c;
    // m in [0.5, 1)
    const divisor<vi_type, int32_t> idiv3(3);
    vi_type e = ilogbp1(xp);
    vi_type e3= e / idiv3;
    vi_type r3= remainder(e, vi_type(3), e3);
    // select r3c so that r3c [-2,-1,0]
    vmi_type r3gt0 = r3 > 0;
    vi_type r3c= _TRAITS::sel(r3gt0, r3-3, r3);
    e3c= _TRAITS::sel(r3gt0, e3+1, e3);
    vi_type sc= r3c - e;
    vf_type mm0 = ldexp(xp, sc);
    vf_type mm = nth_root_approx<3, vf_type>::v(mm0);
    if (_STEPS>1) {
        using step_t= nth_root_halley<3, vf_type, vf_type>;
        for (uint32_t i=0; i<_STEPS-1; ++i) {
            mm= step_t::v(mm, mm0);
        }
    }
    if (_STEPS>0) {
        using step_t= nth_root_nr<3, vf_type, vf_type>;
        mm= step_t::v(mm, mm0);
    }
    // scale back
    vf_type res=scale_exp_k(mm, _TRAITS::cvt_i_to_f(e3c), e3c);
    //vf_type res=ldexp(mm, e3c);
    // restore sign
    res=copysign(res, x);

    vmf_type is_zero_or_inf_or_nan=
        (x == vf_type(0)) | isinf(x) | isnan(x);
    res=_TRAITS::sel(is_zero_or_inf_or_nan,
                     x, res);
    return res;
#endif
}
#endif



// Local Variables:
// mode: c++
// end:
#endif
