#if !defined (__CFTAL_MATH_COMMON_H__)
#define __CFTAL_MATH_COMMON_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/divisor.h>
#include <cftal/constants.h>
#include <type_traits>
#include <limits>
#include <utility>
#include <stdexcept>

namespace cftal {

    namespace math {

        template <typename _T>
        struct func_constants {};

        template <>
        struct func_constants<double> {
            constexpr static const double
            max_denormal= 2.225073858507200889024587e-308;
            // exp(x) == +inf for x >=
            constexpr static const double
            exp_hi_inf= 7.097827128933840867830440e+02;
            // exp(x) == 0 for x <=
            constexpr static const double
            exp_lo_zero= -7.451332191019412221066887e+02;

            // expm1(x) == +inf for x >= 0
            constexpr static const double
            expm1_hi_inf= 7.097827128933840867830440e+02;
            // expm1(x) == 1 for x <=
            constexpr static const double
            expm1_lo_minus_one= -3.742994775023704789873591e+01;

            // exp2(x) == +inf for x >=
            constexpr static const double
            exp2_hi_inf= 1.024000000000000000000000e+03;
            // exp2(x) == 0 for x <=
            constexpr static const double
            exp2_lo_zero= -1.075000000000000000000000e+03;

            // exp10(x) == +inf for x >=
            constexpr static const double
            exp10_hi_inf= 3.082547155599167467698862e+02;
            // exp10(x) == 0 for x <=
            constexpr static const double
            exp10_lo_zero= -3.236072453387798191215552e+02;

            // cosh(x) == +inf for abs(x) >=
            constexpr static const double
            cosh_hi_inf= 7.104758600739439771132311e+02;

            // sinh(x) == +inf for x >=
            constexpr static const double
            sinh_hi_inf= 7.104758600739439771132311e+02;
            // sinh(x) == -inf for x <=
            constexpr static const double
            sinh_lo_inf= -7.104758600739439771132311e+02;

            // nextafter(log(x), -1) == +inf
            constexpr static const double
            log_lo_fin= 4.940656458412465441765688e-324;
            // log(log_lo_fin)
            constexpr static const double
            log_lo_val= -7.444400719213812180896639e+02;

        };

        template <>
        struct func_constants<float> {
            constexpr static const float
            max_denormal= 1.175494210692441075487029e-38f;

            constexpr static const float
            exp_hi_inf= 8.872283935546875000000000e+01f;
            constexpr static const float
            exp_lo_zero= -1.039720840454101562500000e+02f;

            // expm1(x) == +inf for x >= 0
            constexpr static const float
            expm1_hi_inf= 8.872283935546875000000000e+01f;
            // expm1(x) == 1 for x <=
            constexpr static const float
            expm1_lo_minus_one= -1.732868003845214843750000e+01f;

            // exp2(x) == +inf for x >=
            constexpr static const float
            exp2_hi_inf= 1.280000000000000000000000e+02f;
            // exp2(x) == 0 for x <=
            constexpr static const float
            exp2_lo_zero= -1.500000000000000000000000e+02f;

            // exp10(x) == +inf for x >=
            constexpr static const float
            exp10_hi_inf= 3.853184127807617187500000e+01f;
            // exp10(x) == 0 for x <=
            constexpr static const float
            exp10_lo_zero= -4.515450286865234375000000e+01f;

            // cosh(x) == +inf for abs(x) >=
            constexpr static const float
            cosh_hi_inf= 8.941599273681640625000000e+01f;

            // sinh(x) == +inf for x >=
            constexpr static const float
            sinh_hi_inf= 8.941599273681640625000000e+01f;
            // sinh(x) == -inf for x <=
            constexpr static const float
            sinh_lo_inf= -8.941599273681640625000000e+01f;

            constexpr static const float
            log_lo_fin= 1.401298464324817070923730e-45f;
            constexpr static const float
            log_lo_val= -1.032789306640625000000000e+02;
        };

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
            exp_k2(arg_t<vf_type> xh,
                   arg_t<vf_type> xl,
                   bool exp_m1);
            // native exp core
            static vf_type
            native_exp_k(arg_t<vf_type> x, bool exp_m1);
            // log core
            static dvf_type
            log_k2(arg_t<vf_type> xh,
                   arg_t<vf_type> xl);
            // native log core
            static dvf_type
            native_log_k2(arg_t<vf_type> x);
            // sin and cos core, return sin in first
            static std::pair<dvf_type, dvf_type>
            sin_cos_k(arg_t<vf_type> x);
            // native sin and cos core, return sin in first
            static std::pair<vf_type, vf_type>
            native_sin_cos_k(arg_t<vf_type> v);
            // atan2 core
            static dvf_type
            atan2_k2(arg_t<vf_type> xh, arg_t<vf_type> xl,
                     arg_t<vf_type> yh, arg_t<vf_type> yl);
            // atan2 core
            static dvf_type
            native_atan2_k(arg_t<vf_type> x, arg_t<vf_type> y);
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
            using tvf_type = typename base_type::tvf_type;

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

            // pow calls exp_k2 and log_k2
            static vf_type pow(arg_t<vf_type> b,
                               arg_t<vf_type> e);

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

            template <class _VEC, typename _FLOAT_T>
            struct t_real_constants {};


            template <typename _X, typename _C1, typename _C0>
            _X
            poly(_X x, _C1 c1, _C0 c0) {
                return x*_X(c1) + _X(c0);
            }

            template <typename _X,
                      typename _CN, typename _CNM1, typename ... _CS>
            _X
            poly(_X x, _CN cn, _CNM1 cnm1, _CS... cs) {
                _X t = poly(x, cn, cnm1);
                _X r = poly(x, t, cs...);
                return r;
            }

            template <typename _X, typename _C>
            _X
            poly(_X x, const _C& c) {
                auto b=std::cbegin(c);
                auto e=std::cend(c);
                auto bn=std::next(b);
                if (bn==e) {
                    throw std::invalid_argument("cftal::math::poly(x, C)");
                }
                _X r= (*b) * x + (*bn);
                ++b;
                ++b;
                while (b != e) {
                    r = poly(x, r, *b);
                    ++b;
                }
                return r;
            }

            template <typename _X, typename _C, std::size_t _N>
            _X
            poly(_X x, const _C (&a)[_N]) {
                static_assert(_N > 1, "invalid call to poly(x, array)");
                _X r= _X(a[0]) * x + _X(a[1]);
                for (std::size_t i=2; i<_N; ++i) {
                    r= poly(x, r, a[i]);
                }
                return r;
            }

            // polynomial with c1 = 1.0
            template <typename _X, typename _C0>
            _X
            poly1(_X x, _C0 c0) {
                return x + c0;
            }

            // polynomial with cn = 1.0
            template <typename _X,
                      typename _CNM1, typename ... _CS>
            _X
            poly1(_X x, _CNM1 cnm1, _CS... cs) {
                _X t = poly1(x, cnm1);
                _X r = poly(x, t, cs...);
                return r;
            }


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

                typedef typename _TRAITS::vf_type vf_type;
                typedef typename _TRAITS::vmf_type vmf_type;
                typedef nth_root_nr<_R, vf_type> nr_step_t;
                typedef root_guess<_FLOAT_T, _TRAITS, _R>
                    guess_t;

                template <unsigned _STEPS=6>
                static vf_type v(arg_t<vf_type> f) {
                    vf_type x(abs(f));
                    vf_type xin(guess_t::v(x));
#if 0
                    for (unsigned i=0; i< _NR_STEPS-1; ++i)
                        xin = nr_step_t::v(xin, x);
#else
                    using dvf_type = typename _TRAITS::dvf_type;
                    for (unsigned i=0; i< _STEPS-1; ++i)
                        xin = nr_step_t::v(xin, x);
                    dvf_type xhin=xin;
                    dvf_type xh=x;
                    for (unsigned i=_STEPS-1; i< _STEPS; ++i)
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

                template <unsigned _NR_STEPS=6>
                static
                vf_type
                v(arg_t<vf_type> x);
            };

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
    _T r=powvu<_T>::v(xx);
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
    const _T r(_R);
    _RT x_pow_nm1(powu<_RT, _R-1>::v(xi));
    _RT en( x - xi * x_pow_nm1);
    _RT den(r * x_pow_nm1);
    _RT xip1( xi + en / den);
    return xip1;
};

template <unsigned _R, class _RT, class _T>
_RT
cftal::math::impl::nth_root_halley<_R, _RT, _T>::v(const _T& xi, const _T& x)
{
    const _T r(_R);
    const _T two(2.0);
    _RT x_pow(powu<_RT, _R>::v(xi));
    _RT en(two* xi * (x - x_pow));
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
    vf_type res;
    if (_NATIVE) {
        res=my_type::native_exp_k(d);
    } else {
        dvf_type xr(my_type::exp_k2(d, vf_type(0)));
        res=xr.h() + xr.l();
    }
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
    vf_type res;
    if (_NATIVE) {
        res=my_type::native_exp2_k(d);
    } else {
        dvf_type xr(my_type::exp2_k2(d, vf_type(0)));
        res=xr.h() + xr.l();
    }
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
    vf_type res;
    if (_NATIVE) {
        res=my_type::native_exp10_k(d);
    } else {
        dvf_type xr(my_type::exp10_k2(d, vf_type(0)));
        res=xr.h() + xr.l();
    }
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
    vf_type res;
    if (_NATIVE) {
        vf_type r=my_type::native_exp_k(d, true);
        res = r;
    } else {
        dvf_type r(my_type::exp_k2(d, vf_type(0), true));
        res =r.h() + r.l();
    }
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
sinh(arg_t<vf_type> d)
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
    dvf_type exph=my_type::exp_k2(dh.h(), dh.l());
    dvf_type rexph=(vf_type(1.0)/exph);
    dvf_type sinh_xh= mul_pwr2(exph - rexph, vf_type(0.5));
    dvf_type cosh_xh= mul_pwr2(exph + rexph, vf_type(0.5));
    dvf_type sinh_x= mul_pwr2(sinh_xh * cosh_xh, vf_type(2.0));
    vf_type res = sinh_x.h() + sinh_x.l();
    using fc=func_constants<_FLOAT_T>;
    const vf_type sinh_hi_inf= fc::sinh_hi_inf;
    const vf_type sinh_lo_inf= fc::sinh_lo_inf;
    res = _T::sel(d >= sinh_hi_inf, _T::pinf(), res);
    res = _T::sel(d <= sinh_lo_inf, _T::ninf(), res);
    res = _T::sel(d == 0.0, 0.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
cosh(arg_t<vf_type> d)
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
    dvf_type exph=my_type::exp_k2(dh.h(), dh.l());
    dvf_type rexph=(vf_type(1.0)/exph);
    dvf_type two_sinh_xh= exph - rexph;
    dvf_type sinh_xh = mul_pwr2(two_sinh_xh, vf_type(0.5));
    dvf_type cosh_x = mul_pwr2(sqr(sinh_xh), vf_type(2.0)) + vf_type(1.0);
    vf_type res = cosh_x.h() + cosh_x.l();
    using fc=func_constants<_FLOAT_T>;
    const vf_type cosh_hi_inf= fc::cosh_hi_inf;
    res = _T::sel(abs(d) >= cosh_hi_inf, _T::pinf(), res);
    res = _T::sel(d == 0.0, 1.0, res);
    return res;
}

template <typename _FLOAT_T, typename _T>
template <bool _NATIVE>
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
_log(arg_t<vf_type> d)
{
    vf_type x;
    if (_NATIVE) {
        x= my_type::native_log_k(d);
    } else {
        dvf_type xr(my_type::log_k2(d, vf_type(0)));
        x= xr.h() + xr.l();
    }
    const vf_type pinf(_T::pinf());
    const vf_type ninf(_T::ninf());
    x = _T::sel(isinf(d), pinf, x);
    // if (d < 0) x = NAN;
    x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
    // if (d == 0) x = -INFINITY;
    x = _T::sel(d == vf_type(0.0), ninf, x);

    using fc= func_constants<_FLOAT_T>;
    const vf_type log_lo_fin= fc::log_lo_fin;
    const vf_type log_lo_val= fc::log_lo_val;
    x = _T::sel(d == log_lo_fin, log_lo_val, x);
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
inline
typename cftal::math::func_common<_FLOAT_T, _T>::vf_type
cftal::math::func_common<_FLOAT_T, _T>::
pow(arg_t<vf_type> x, arg_t<vf_type> y)
{
    // we have a problem if e is an integer
    dvf_type ln_x(my_type::log_k2(abs(x), vf_type(0)));
    dvf_type ln_x_y(ln_x * y);
    dvf_type pow0(my_type::exp_k2(ln_x_y.h(), ln_x_y.l()));
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
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
sincos(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        my_type::sin_cos_k(d, 1, psin, pcos);
    }
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
sin(arg_t<vf_type> d)
{
    vf_type s;
    my_type::sin_cos_k(d, 1, &s, nullptr);
    return s;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
cos(arg_t<vf_type> d)
{
    vf_type c;
    my_type::sin_cos_k(d, 1, nullptr, &c);
    return c;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
tan(arg_t<vf_type> d)
{
    vf_type s[2], c[2];
    my_type::sin_cos_k(d, 2, s, c);
    dvf_type ds(s[0], s[1]), dc(c[0], c[1]);
    dvf_type tn=ds /dc;
    return tn.h() + tn.l();
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
cot(arg_t<vf_type> d)
{
    vf_type s[2], c[2];
    my_type::sin_cos_k(d, 2, s, c);
    dvf_type ds(s[0], s[1]), dc(c[0], c[1]);
    dvf_type ct= dc /ds;
    using fc=func_constants<_FLOAT_T>;
    vf_type r=ct.h() + ct.l();
    vmf_type is_nan=isnan(r);
    if (any_of(is_nan)) {
        vmf_type is_small = (abs(d) <= fc::max_denormal) & is_nan;
        if (any_of(is_small)) {
            // vmf_type den_plus= may_be_denom & (d > 0.0);
            // vmf_type den_minus= may_be_denom & (d < 0.0);
            // r = _TRAITS_T::sel(den_plus, _TRAITS_T::pinf(), r);
            // r = _TRAITS_T::sel(den_minus, _TRAITS_T::ninf(), r);
            vf_type zinf= _TRAITS_T::pinf();
            zinf=copysign(zinf, d);
            r = _TRAITS_T::sel(is_small, zinf, r);
        }
    }
    return r;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_sincos(arg_t<vf_type> d, vf_type* psin, vf_type* pcos)
{
    if ((psin!=nullptr) || (pcos!=nullptr)) {
        my_type::native_sin_cos_k(d, psin, pcos);
    }
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_sin(arg_t<vf_type> d)
{
    vf_type s;
    my_type::native_sin_cos_k(d, &s, nullptr);
    return s;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_cos(arg_t<vf_type> d)
{
    vf_type c;
    my_type::native_sin_cos_k(d, nullptr, &c);
    return c;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_tan(arg_t<vf_type> d)
{
    vf_type s, c;
    my_type::native_sin_cos_k(d, &s, &c);
    vf_type tn(s / c);
    return tn;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
native_cot(arg_t<vf_type> d)
{
    vf_type s, c;
    my_type::native_sin_cos_k(d, &s, &c);
    vf_type ct(c / s);
    return ct;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atan2(arg_t<vf_type> y, arg_t<vf_type> x)
{
    dvf_type rd(base_type::atan2_k2(abs(y), vf_type(0), x, vf_type(0)));
    // r = dvf_type(mulsign(r.h(), x),
    //             mulsign(r.l(), x));
    // r = mulsign(r, x);
    vf_type sgn_x = copysign(vf_type(1.0), x);
    vf_type r = rd.h() * sgn_x;

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
    // if (             y == 0) r = (sign(x) == -1 ? M_PI : 0);
    vf_type t3= _TRAITS_T::sel(sgn_x == -1.0, vf_type(M_PI), vf_type(0));
    r = _TRAITS_T::sel(y==0, t3, r);
    // return xisnan(x) || xisnan(y) ? NAN : mulsign(r, y);
    vf_type sgn_y = copysign(vf_type(1.0), y);
    vf_type rs= r*sgn_y;
    rs = _TRAITS_T::sel(isnan(x) | isnan(y), _TRAITS_T::nan(), rs);
    return rs;
}

template <typename _FLOAT_T,
          typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _TRAITS_T>::
atan(arg_t<vf_type> x)
{
    return atan2(x, vf_type(1.0));
}

template <typename _FLOAT_T, typename _TRAITS>
template <unsigned _NR_STEPS>
typename cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, 3>::vf_type
cftal::math::impl::nth_root<_FLOAT_T, _TRAITS, 3>::v(arg_t<vf_type> x)
{
    vf_type xp=abs(x);
    vi_type e3c;
    vf_type mm, mm0;
    // m in [0.5, 1)
    using fc=func_constants<_FLOAT_T>;
    vmf_type is_denormal=(xp <= fc::max_denormal * _FLOAT_T(128)) & (xp != 0.0);
    const divisor<vi_type, int32_t> idiv3(3);
    if (any_of(is_denormal)) {
        vi_type e;
        vf_type m=frexp(xp, &e);
        vi_type e3= e / idiv3;
        vi_type r3= remainder(e, vi_type(3), e3);
        // select r3c so that r3c [-2,-1,0]
        vmi_type r3gt0 = r3 > 0;
        vi_type r3c= _TRAITS::sel(r3gt0, r3-3, r3);
        e3c= _TRAITS::sel(r3gt0, e3+1, e3);
        // mm in [0.125, 1) => m * 2 ^[-2,-1.0]
        mm= ldexp(m, r3c);
        mm0= mm;
    } else {
        // this code does not work for denormals:
        vi_type e = ilogbp1(xp);
        vi_type e3= e / idiv3;
        vi_type r3= remainder(e, vi_type(3), e3);
        // select r3c so that r3c [-2,-1,0]
        vmi_type r3gt0 = r3 > 0;
        vi_type r3c= _TRAITS::sel(r3gt0, r3-3, r3);
        e3c= _TRAITS::sel(r3gt0, e3+1, e3);
        vi_type sc= r3c - e;
        mm= ldexp(xp, sc);
        mm0 = mm;
    }
    // we should calculate x^(-1/3) first because
    // the newton raphson steps do not require a
    // division:
    // calculate 1/cbrt(mm0);
    mm = poly(mm0,
              -2.595873403893505e0,
              5.852550974497818e0,
              -4.747475053671543e0,
              2.474536628160067e0);
    if (_NR_STEPS > 1) {
        for (uint32_t i =0; i< _NR_STEPS-1; ++i)
            mm= mm + 1.0/3.0 * (mm - mm*mm*mm*mm*mm0);
    }
    // convert to cbrt(mm0)
    mm= mm*mm*mm0;
    // one newton raphson step with double precision
    if (_NR_STEPS>0) {
        dvf_type dmm;
        for (uint32_t i=_NR_STEPS-1; i< _NR_STEPS; ++i)
            dmm = nth_root_nr<3, dvf_type, vf_type>::v(mm, mm0);
        mm = dmm.h();
    }
    // scale back
    vf_type res=ldexp(mm, e3c);
    // restore sign
    res=copysign(res, x);

    vmf_type is_zero_or_inf_or_nan=
        (x == vf_type(0)) | isinf(x) | isnan(x);
    res=_TRAITS::sel(is_zero_or_inf_or_nan,
                     x, res);
    return res;
}



// Local Variables:
// mode: c++
// end:
#endif
