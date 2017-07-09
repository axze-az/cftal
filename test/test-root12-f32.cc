//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/vec.h"
#include "cftal/vec_traits.h"
#include "cftal/math/elem_func.h"
#include "cftal/math/elem_func_core_f64.h"
#include "cftal/math/elem_func_core_f32.h"
#include "cftal/math/impl_estrin.h"
#include "cftal/math/misc.h"
#include "cftal/test/of_math_funcs.h"
#include "cftal/test/check_expm1.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>

#define EXP 1

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
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vi2_type = typename _T::vi2_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;
            using vmi2_type = typename _T::vmi2_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<double, _T>;

            using d_ops = typename base_type::d_ops;

            // static vf_type func_k(arg_t<vf_type> vf);

            using base_type::ilogbp1_k;
            using base_type::ldexp_k;
            using base_type::pow_k;

        };

        template <typename _T>
        struct test_func<float, _T> : public elem_func_core<float, _T> {
            using base_type = elem_func_core<float, _T>;
            using vf_type = typename _T::vf_type;
            using vi_type = typename _T::vi_type;
            // using vli_type = typename _T::vli_type;
            using vmf_type = typename _T::vmf_type;
            using vmi_type = typename _T::vmi_type;

            using dvf_type = d_real<vf_type>;
            using tvf_type = t_real<vf_type>;
            using my_type = test_func<float, _T>;

            using d_ops = typename base_type::d_ops;

            static vf_type func(arg_t<vf_type> vf);
            static vf_type func_k(arg_t<vf_type> vf);

            using base_type::ilogbp1;
            using base_type::ldexp;
            using base_type::__reduce_exp_arg;
            using base_type::__scale_exp_k;
            using base_type::__exp_k;

            static
            vf_type
            root12_k(arg_t<vf_type> x);

            static
            vf_type
            root12(arg_t<vf_type> x);
        };


    }

    namespace test {

        template <typename _T>
        struct check_root12 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
#if 0
                // return sqrt(sqrt(cbrt(a))); // 1351533
                // return cbrt(sqrt(sqrt(a))); //  927090
                // return sqrt(cbrt(sqrt(a))); // 1289438
#else
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::root12(a);
#endif
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::root12, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::cbrt(std::sqrt(std::sqrt(a)));
                // return std::pow(a, 1.0/12.0);
            }
            static
            const char* fname() {
                return "root12";
            }
        };

        template <typename _T>
        struct check_pow {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                using traits_t=math::func_traits<vec<_T, _N>,
                                                 vec<int32_t, _N> >;
                using func_t=math::test_func<_T, traits_t>;
                return func_t::pow(a, b);
            }
            static
            auto
            r(const _T& a, const _T& b) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, b, mpfr_pow, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a, const _T& b) {
                return std::pow(a, b);
            }
            static
            const char* fname() {
                return "pow";
            }
        };



    }

}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
__attribute__((flatten))
cftal::math::test_func<float, _T>::
root12_k(arg_t<vf_type> xc)
{
    // reduce x into [2^-12, 1.0)
    const int32_t shift_1_12= 0x11;
    const int32_t fac_1_12= 0x2aab;

    vf_type xp=abs(xc);
    vf_type mm0;
    auto e=base_type::__frexp_k(mm0, xp);
    // do a division by 3
    // vi2_type e3 = (((e)*fac_1_3)>>shift_1_3) -(e>>31);
    // do a division by 3 rounded to - infinity
    const vi_type v_bias_12(12*_T::bias()), v_bias(_T::bias());
    vi_type e12_with_bias = (((e+v_bias_12)*fac_1_12)>>shift_1_12);
    vi_type e12 =e12_with_bias - v_bias;
    // r is always in [0, 1, 11] because of the round down
    vi_type r = e - e12 *12;

    // correction of mm0 in dependence of r
    // r    scale   log_2(scale) r - 12
    // 1    ...     -11          -11
    // 2            -10
    // 3            -9
    // 4            -8           ....
    // 5            -7
    // 6            -6
    // 7            -5
    // 8            -4
    // 9            -3
    // 10   0.25    -2           -2
    // 11   0.5     -1           -1
    // 0    1.0     -0            0
    // -1   0.5     -1           -4
    // -2   0.25    -2           -5
    vmi_type r_ne_z = r != 0;
    e12_with_bias=_T::sel(r_ne_z, e12_with_bias+1, e12_with_bias);

    // log_2(scale) = bias + (r-12) = bias - 12 + r
    const vi_type v_bias_plus_12(_T::bias()-12);
    vf_type scale = _T::insert_exp(v_bias_plus_12 + r);
    vmf_type f_r_ne_z = _T::vmi_to_vmf(r_ne_z);
    scale = _T::sel(f_r_ne_z, scale, 1.0);
    mm0 = mm0 * scale;
#if 1
#if 1
    // [2.44140625e-4, 1] : | p - f | <= 2^-2.6767578125
    // coefficients for root12 generated by sollya
    // x^0 : +0x9.3e756ac285bb8p-4
    const vf_type root12_c0=+5.7774869635646453058797e-01f;
    // x^1 : +0xe.45350dc5fb91p-3
    const vf_type root12_c1=+1.7837925983471412116899e+00f;
    // x^2 : -0xc.24adbc4221718p-3
    const vf_type root12_c2=-1.5179094989472836640942e+00f;
    vf_type mm = horner(mm0,
                        root12_c2,
                        root12_c1,
                        root12_c0);
    mm = impl::root12::householder4<float>(mm, mm0);
    mm = impl::root12::householder4<float>(mm, mm0);
    mm = impl::root12::nr<float>(mm, mm0);
    mm = impl::root12::nr<float>(mm, mm0);
#endif
#if 0
    // faithful: 864807
    vf_type mm = M_SQRT2/2;
    mm = impl::root12::householder5(mm, mm0);
    mm = impl::root12::householder5(mm, mm0);
    mm = impl::root12::householder5(mm, mm0);
    mm = impl::root12::nr(mm, mm0);
    mm = impl::root12::nr(mm, mm0);
#endif
#else
    // faithful: 927090
    vf_type mm= cbrt(sqrt(sqrt(mm0)));
#endif
    vf_type t= _T::insert_exp(e12_with_bias);
    mm *=t;
    // mm = copysign(mm, xc);
    return mm;
}

template <typename _T>
typename cftal::math::test_func<float, _T>::vf_type
cftal::math::test_func<float, _T>::
root12(arg_t<vf_type> x)
{
    vf_type y= root12_k(x);
    y=_T::sel(isnan(x), x, y);
    y=_T::sel(x == _T::pinf(), _T::pinf(), y);
    y=_T::sel(x == 0, 0.0, y);
    y=_T::sel(x < 0.0, _T::nan(), y);
    return y;
}

int main(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=32;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x8000);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> dd=std::make_pair(0.0,
                                          std::numeric_limits<float>::max());
    // dd=std::make_pair(0.125, 1.0);
    auto us=std::make_shared<ulp_stats>();
    exec_stats d_st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_root12<float> >::v(d_st, dd, speed_only,
                                            cmp_ulp<float>(ulp, us),
                                            cnt);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4) << *us << std::endl;
    std::cout << d_st << std::endl;
    return rc==true ? 0 : 1;
}
