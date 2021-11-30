//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_IMPL_PAYNE_HANEK_H__)
#define __CFTAL_MATH_IMPL_PAYNE_HANEK_H__ 1

#include <cftal/config.h>
#include <cftal/arg.h>
#include <cftal/d_real.h>
#include <cftal/math/func_traits.h>
#include <cftal/math/func_constants.h>
#include <cftal/math/impl_d_real_constants_f32.h>
#include <cftal/math/impl_d_real_constants_f64.h>

namespace cftal::math {

    template <typename _T>
    struct payne_hanek_pi_over_2_base {};

    template <>
    struct payne_hanek_pi_over_2_base<double> {
        // bits of 2/(M_PI) in 24 bit chunks as double, i.e.
        // offset 0: bit [0, 24)*2^(1*24)
        // offset 1: bit [24, 48)*2^(2*24)
        // offset 2: bit [48, 62)*2^(3*24)
        // number of elements is determined by 2047/24+6=91,
        // rounded up to the next multiple of six
        static
        const double
        two_over_pi_b24_dbl[96];
    };

    template <typename _T, typename _TRAITS>
    struct payne_hanek_pi_over_2 {};

    // scalar f64 implementation
    template <>
    struct payne_hanek_pi_over_2<double, void>
        : public payne_hanek_pi_over_2_base<double> {
        using d_traits = d_real_traits<double>;
        using d_ops = d_real_ops<double, d_traits::fma>;

        // scale down factor for x
        constexpr static double scale_down_f64() {
            return 0x1p-512;
        }
        // 2 to the negative power of 2/pi bits per double element
        // in the table
        constexpr static const double scale_step_f64() {
            return 0x1p-24;
        }
        // idx equal to zero: scale= scale_step_f64()/scale_down_f64();
        // i.e. for scale_down = 1.0 0x1p-24;
        constexpr static double scale_up_f64() {
            return 1.0/scale_down_f64()*scale_step_f64();
        }
        // number of 2/pi bits per double element in the table
        constexpr
        static const int32_t bits_per_elem_f64=24;
        // exp_shift_down C is determined by
        // (with scale_down 0x1p-600)
        // (((x_e - 600) + 1023) - C)/24 = (x_e - 27)/24
        // ==> C = -600 + 1023 + 27 = 450
        // (with scale_down 0x1p-512)
        // (((x_e - 512) + 1023) - C)/24 = (x_e - 27)/24
        // ==> C = -512 + 1023 + 27 = 538
        constexpr
        static const int32_t exp_shift_down_f64=538;
        // number of 24 bit chunks to use
        constexpr
        static const int32_t elem_count_f64=6;

    private:
        // round x to the next multiple of 1
        static
        double
        __rint(double x);
        // round x to the next multiple of 4
        static
        double
        __r4int(double x);
        // performs the partial calculation of x * 2/pi
        // x may not have not more than 26 mantissa bits
        // including the hidden bit
        static
        void
        process_part(double& ipart,
                        double& rh,
                        double& rl,
                        double x);
        // performs the partial calculation of x*2/pi
        // and add the results to ipart, rh, rl
        // x may not have not more than 26 mantissa bits
        // including the hidden bit
        static
        void
        process_and_add_part(double& ipart,
                                double& rh,
                                double& rl,
                                double x);
    public:
        static
        int
        rem(double& xrh, double& xrl, double x);

        static
        int
        rem(double& xrh, double& xrl, double xh, double xl);
    };

    // vectorized f64 implementation
    template<typename _T>
    struct payne_hanek_pi_over_2<double, _T>
        : public payne_hanek_pi_over_2<double, void> {

        using vf_type = typename _T::vf_type;
        using vi_type = typename _T::vi_type;
        using vli_type = typename _T::vli_type;
        using vi2_type = typename _T::vi2_type;
        using vmf_type = typename _T::vmf_type;
        using vmi_type = typename _T::vmi_type;
        using vmli_type = typename _T::vmli_type;
        using vmi2_type = typename _T::vmi2_type;
        using vdf_type = typename _T::vdf_type;

        using d_ops=d_real_ops<vf_type,
                                d_real_traits<vf_type>::fma>;
        using d_traits = d_real_traits<vf_type>;

    private:
        // round to multiples of 1
        static
        vf_type
        __rint(arg_t<vf_type> x);

        // round to multiples of 4
        static
        vf_type
        __r4int(arg_t<vf_type> x);

        // performs the partial calculation of x * 2/pi
        // x may not have not more than 26 mantissa bits
        // including the hidden bit
        static
        void
        process_part(vf_type& ipa,
                     vf_type& rh,
                     vf_type& rl,
                     arg_t<vf_type> x);
        // performs the partial calculation of x*2/pi
        // and add the results to ipart, rh, rl
        // x may not have not more than 26 mantissa bits
        // including the hidden bit
        static
        void
        process_and_add_part(vf_type& ipa,
                             vf_type& rh,
                             vf_type& rl,
                             arg_t<vf_type> x);
    public:
        static
        vi_type
        rem(vf_type& xrh, vf_type& xrl, arg_t<vf_type> x);

        static
        vi_type
        rem(vf_type& xrh, vf_type& xrl,
            arg_t<vf_type> xh, arg_t<vf_type> xl);
    };
}

template <typename _T>
inline
typename cftal::math::payne_hanek_pi_over_2<double, _T>::vf_type
cftal::math::payne_hanek_pi_over_2<double, _T>::
__rint(arg_t<vf_type> x)
{
    using std::rint;
    return rint(x);
}

template <typename _T>
inline
typename cftal::math::payne_hanek_pi_over_2<double, _T>::vf_type
cftal::math::payne_hanek_pi_over_2<double, _T>::
__r4int(arg_t<vf_type> x)
{
    constexpr const double rint_magic=(0x1p52 + 0x1p51)*4;
    return (x + rint_magic) - rint_magic;
}

template <typename _T>
void
cftal::math::payne_hanek_pi_over_2<double, _T>::
process_part(vf_type& ipa,
             vf_type& rh,
             vf_type& rl,
             arg_t<vf_type> x)
{
    vi_type k=(_T::extract_high_word(x) >> 20) & 2047;
    // int32_t k = (as<uint64_t>(x) >> 52) & 2047;
    // divide k -exp_shift_down_f64 by 24
    const int32_t shift_1_24= 0x12;
    const int32_t fac_1_24= 0x2aab;
    k = ((k-exp_shift_down_f64) * fac_1_24) >> shift_1_24;
    using std::max;
    k = max(k, vi_type(0));
    // const int64_t scale_i = as<int64_t>(scale_up_f64());
    // vf_type scale = as<vf_type>(scale_i - (int64_t(k*bits_per_elem_f64)<<52));
    const vf_type scale0 = scale_up_f64();
    vi_type sl, sh;
    _T::extract_words(sl, sh, scale0);
    sh -= (k*bits_per_elem_f64)<<20;
    vf_type scale=_T::combine_words(sl, sh);

    auto lck=make_variable_lookup_table<double>(k);
    vf_type p[elem_count_f64];
    for (uint32_t i=0; i<elem_count_f64; ++i) {
        vf_type pi_bits=lck.from(two_over_pi_b24_dbl+i);
        p[i] = x*pi_bits*scale;
        scale *= scale_step_f64();
    }

    // ip contains the integer parts of pi[i]
    vf_type ip=__rint(p[0]);
    p[0] -= ip;
    for (uint32_t i=1; i<elem_count_f64/2; ++i) {
        vf_type ii= __rint(p[i]);
        ip += ii;
        p[i] -= ii;
    }
    // ph, pl: compensated sum of p[i]
    vf_type ph = p[elem_count_f64-1];
    for (uint32_t i=1; i<elem_count_f64; ++i) {
        ph += p[(elem_count_f64-1)-i];
    }
    vf_type pl = p[0] - ph;
    for (uint32_t i=1; i<elem_count_f64; ++i) {
        pl += p[i];
    }
    // subtract integer part from ph, pl
    vf_type ii=__rint(ph);
    ip+=ii;
    ph-=ii;
    d_ops::add12(ph, pl, ph, pl);
    // remove multiple of 4 from sum
    ii = __r4int(ip);
    ip -= ii;
    ipa = ip;
    rh = ph;
    rl = pl;
}

template <typename _T>
void
cftal::math::payne_hanek_pi_over_2<double, _T>::
process_and_add_part(vf_type& ipa,
                     vf_type& rh,
                     vf_type& rl,
                     arg_t<vf_type> x)
{
    vf_type ipart = ipa;
    vf_type m1h = rh;
    vf_type m1l = rl;
    vf_type ipart2, m2h, m2l;
    process_part(ipart2, m2h, m2l, x);
    ipart += ipart2;
    vf_type mh, ml;
    d_ops::add12cond(mh, ml, m1h, m2h);
    // if (mh > 0.5)
    //    {mh-=1.0; ipart+=1.0;}
    // else if (mh < -0.5)
    //    {mh+=1.0; ipart-=1.0;}
    auto mh_gt_half = mh > 0.5;
    auto mh_lt_mhalf = mh < -0.5;
#if 0
    auto mh_m_1 = mh - 1.0;
    auto ipart_p_1 = ipart + 1.0;
    auto mh_p_1 = mh + 1.0;
    auto ipart_m_1 = ipart - 1.0;
    mh = _T::sel(mh_gt_half, mh_m_1, mh);
    ipart = _T::sel(mh_gt_half, ipart_p_1, ipart);
    mh = _T::sel(mh_lt_mhalf, mh_p_1, mh);
    ipart = _T::sel(mh_lt_mhalf, ipart_m_1, ipart);
#else
    vf_type mh_corr = _T::sel_val_or_zero(mh_gt_half, -1.0);
    vf_type ipart_corr= _T::sel_val_or_zero(mh_gt_half, +1.0);
    mh_corr = _T::sel(mh_lt_mhalf, +1.0, mh_corr);
    ipart_corr= _T::sel(mh_lt_mhalf, -1.0, ipart_corr);
    mh += mh_corr;
    ipart += ipart_corr;
#endif
    // add mh, ml, m2h, m2l into th, tl
    vf_type th=mh+(ml+m1l+m2l);
    vf_type tl=((mh-th)+ml)+(m1l+m2l);
    ipa=ipart;
    rh = th;
    rl = tl;
}

template <typename _T>
typename cftal::math::payne_hanek_pi_over_2<double, _T>::vi_type
cftal::math::payne_hanek_pi_over_2<double, _T>::
rem(vf_type& xrh, vf_type& xrl,
    arg_t<vf_type> x)
{
    vf_type xs=x*scale_down_f64();
    // d_traits::veltkamp_split(x, x1, x2);
    vf_type x1= round_to_nearest_even_last_bits<27>(xs);
    vf_type ipart, mh, ml;
    process_part(ipart, mh, ml, x1);
    vf_type x2= xs - x1;
    process_and_add_part(ipart, mh, ml, x2);
    // multiply mh, ml with pi/2
    using c_t = impl::d_real_constants<d_real<double>, double>;
    vf_type th, tl;
    d_ops::unorm_mul22(th, tl, mh, ml, c_t::m_pi_2[0], c_t::m_pi_2[1]);
    d_ops::add12(mh, ml, th, tl);
    xrh=mh;
    xrl=ml;
    // return last 2 bits of the integer part
    vi_type i=_T::cvt_f_to_i(ipart) & 3;
    return i;
}

template <typename _T>
typename cftal::math::payne_hanek_pi_over_2<double, _T>::vi_type
cftal::math::payne_hanek_pi_over_2<double, _T>::
rem(vf_type& xrh, vf_type& xrl,
    arg_t<vf_type> xh, arg_t<vf_type> xl)
{
    vf_type xhs=xh*scale_down_f64();
    // d_traits::veltkamp_split(x, x1, x2);
    vf_type x1= round_to_nearest_even_last_bits<27>(xhs);
    vf_type ipart, mh, ml;
    process_part(ipart, mh, ml, x1);
    vf_type x2= xhs - x1;
    process_and_add_part(ipart, mh, ml, x2);
    vf_type xls=xl=scale_down_f64();
    vf_type x3= round_to_nearest_even_last_bits<27>(xls);
    process_and_add_part(ipart, mh, ml, x3);
    vf_type x4= xls - x3;
    process_and_add_part(ipart, mh, ml, x4);
    // multiply mh, ml with pi/2
    using c_t = impl::d_real_constants<d_real<double>, double>;
    vf_type th, tl;
    d_ops::unorm_mul22(th, tl, mh, ml, c_t::m_pi_2[0], c_t::m_pi_2[1]);
    d_ops::add12(mh, ml, th, tl);
    xrh=mh;
    xrl=ml;
    // return last 2 bits of the integer part
    vi_type i=_T::cvt_f_to_i(ipart) & 3;
    return i;
}

#endif