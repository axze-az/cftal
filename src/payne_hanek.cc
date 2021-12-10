//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/math/payne_hanek.h>
#include <cftal/vec_math_funcs.h>

const double
cftal::math::payne_hanek_pi_over_2_base::
two_over_pi_b24_dbl[96]={
    0xa2f983, 0x6e4e44, 0x1529fc, 0x2757d1, 0xf534dd, 0xc0db62,
    0x95993c, 0x439041, 0xfe5163, 0xabdebb, 0xc561b7, 0x246e3a,
    0x424dd2, 0xe00649, 0x2eea09, 0xd1921c, 0xfe1deb, 0x1cb129,
    0xa73ee8, 0x8235f5, 0x2ebb44, 0x84e99c, 0x7026b4, 0x5f7e41,
    0x3991d6, 0x398353, 0x39f49c, 0x845f8b, 0xbdf928, 0x3b1ff8,
    0x97ffde, 0x05980f, 0xef2f11, 0x8b5a0a, 0x6d1f6d, 0x367ecf,
    0x27cb09, 0xb74f46, 0x3f669e, 0x5fea2d, 0x7527ba, 0xc7ebe5,
    0xf17b3d, 0x0739f7, 0x8a5292, 0xea6bfb, 0x5fb11f, 0x8d5d08,
    0x560330, 0x46fc7b, 0x6babf0, 0xcfbc20, 0x9af436, 0x1da9e3,
    0x91615e, 0xe61b08, 0x659985, 0x5f14a0, 0x68408d, 0xffd880,
    0x4d7327, 0x310606, 0x1556ca, 0x73a8c9, 0x60e27b, 0xc08c6b,
    0x47c419, 0xc367cd, 0xdce809, 0x2a8359, 0xc4768b, 0x961ca6,
    0xddaf44, 0xd15719, 0x053ea5, 0xff0705, 0x3f7e33, 0xe832c2,
    0xde4f98, 0x327dbb, 0xc33d26, 0xef6b1e, 0x5ef89f, 0x3a1f35,
    0xcaf27f, 0x1d87f1, 0x21907c, 0x7c246a, 0xfa6ed5, 0x772d30,
    0x433b15, 0xc614b5, 0x9d19c3, 0xc2c4ad, 0x414d2c, 0x5d000c
};

const double
cftal::math::payne_hanek_pi_over_2_base::
two_over_pi_b24_unscaled_dbl[18]={
    0xa2f983 * 0x1p-24,
    0x6e4e44 * 0x1p-48,
    0x1529fc * 0x1p-72,
    0x2757d1 * 0x1p-96,
    0xf534dd * 0x1p-120,
    0xc0db62 * 0x1p-144,
    0x95993c * 0x1p-168,
    0x439041 * 0x1p-192,
    0xfe5163 * 0x1p-216,
    0xabdebb * 0x1p-240,
    0xc561b7 * 0x1p-264,
    0x246e3a * 0x1p-288,
    0x424dd2 * 0x1p-312,
    0xe00649 * 0x1p-336,
    0x2eea09 * 0x1p-360,
    0xd1921c * 0x1p-384,
    0xfe1deb * 0x1p-408,
    0x1cb129 * 0x1p-432
};

inline
double
cftal::math::payne_hanek_pi_over_2<double, void>::
__rint(double x)
{
#if defined (__SSE4_2__)
    const int rm=_MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC;
    return _mm_cvtsd_f64(_mm_round_pd(_mm_set_sd(x), rm));
#else
    constexpr const double rint_magic=0x1p52 + 0x1p51;
    return (x + rint_magic) - rint_magic;
#endif
}

inline
double
cftal::math::payne_hanek_pi_over_2<double, void>::
__r4int(double x)
{
#if 0 // defined (__SSE4_2__)
    const int rm=_MM_FROUND_TO_NEAREST_INT|_MM_FROUND_NO_EXC;
    return _mm_cvtsd_f64(_mm_round_pd(_mm_set_sd(x*0.25), rm))*4.0;
#else
    constexpr const double rint_magic=(0x1p52 + 0x1p51)*4;
    return (x + rint_magic) - rint_magic;
#endif
}

inline
void
cftal::math::payne_hanek_pi_over_2<double, void>::
process_part(double& ipart, double& rh, double& rl, double x)
{
#if 0
    // scaling must be done before splitting of the numbers
    // exp_shift_down C is determined by (with scale 0x1p-600)
    // (((x_e - 600) + 1023) - C)/24 = (x_e - 27)/24
    // ==> C = -600 + 1023 - 27 = 450
    double xu=x*0x1p512;
    int kk= ((as<uint64_t>(xu) >> 52) & 2047)- bias_f64;
    int idx = std::max((kk-27)/24, 0);
    int exp= (idx+1)*bits_per_elem_f64;
    double scale= as<double>(int64_t(bias_f64-exp)<<52);
    scale *= 0x1p512;
    double p[elem_count_f64];
    for (uint32_t i=0; i<elem_count_f64; ++i) {
        p[i] = (x*two_over_pi_b24_dbl[idx+i])*scale;
        scale *= scale_step_f64();
    }

#else
    int32_t k = (as<uint64_t>(x) >> 52) & 2047;
#if 1
    const int32_t shift_1_24= 0x12;
    const int32_t fac_1_24= 0x2aab;
    int32_t ks=k-exp_shift_down_f64;
    k= (ks*fac_1_24)>> shift_1_24;
#else
    k = (k-exp_shift_down_f64)/bits_per_elem_f64;
#endif
    using std::max;
    k = max(k, 0);
    const int64_t scale_i = as<int64_t>(scale_up_f64());
    double scale = as<double>(scale_i - (int64_t(k*bits_per_elem_f64)<<52));

    double p[elem_count_f64];
    for (uint32_t i=0; i<elem_count_f64; ++i) {
        p[i] = x*two_over_pi_b24_dbl[k+i]*scale;
        scale *= scale_step_f64();
    }
#endif
    // ip contains the integer parts of pi[i]
    double ip=__rint(p[0]);
    p[0] -= ip;
    for (uint32_t i=1; i<3; ++i) {
        double ii= __rint(p[i]);
        ip += ii;
        p[i] -= ii;
    }
    // ph, pl: compensated sum of p[i]
    double ph = p[elem_count_f64-1];
    for (uint32_t i=1; i<elem_count_f64; ++i) {
        ph += p[(elem_count_f64-1)-i];
    }
    double pl = p[0] - ph;
    for (uint32_t i=1; i<elem_count_f64; ++i) {
        pl += p[i];
    }
    // subtract integer part from ph, pl
    double ii=__rint(ph);
    ip+=ii;
    ph-=ii;
    d_ops::add12(ph, pl, ph, pl);
    // remove multiple of 4 from integer part
    ii = __r4int(ip);
    ip -= ii;
    ipart = ip;
    rh = ph;
    rl = pl;
}

inline
void
cftal::math::payne_hanek_pi_over_2<double, void>::
process_and_add_part(double& ipa, double& rh, double& rl, double x)
{
    double ipart = ipa;
    double m1h = rh;
    double m1l = rl;
    double ipart2, m2h, m2l;
    process_part(ipart2, m2h, m2l, x);
    ipart += ipart2;
    double mh, ml;
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
    mh = select(mh_gt_half, mh_m_1, mh);
    ipart = select(mh_gt_half, ipart_p_1, ipart);
    mh = select(mh_lt_mhalf, mh_p_1, mh);
    ipart = select(mh_lt_mhalf, ipart_m_1, ipart);
#else
    double mh_corr = select(mh_gt_half, -1.0, 0.0);
    double ipart_corr= select(mh_gt_half, +1.0, 0.0);
    mh_corr = select(mh_lt_mhalf, +1.0, mh_corr);
    ipart_corr= select(mh_lt_mhalf, -1.0, ipart_corr);
    mh += mh_corr;
    ipart += ipart_corr;
#endif
    // add mh, ml, m2h, m2l into th, tl
    double th=mh+(ml+m1l+m2l);
    double tl=((mh-th)+ml)+(m1l+m2l);
    ipa=ipart;
    rh = th;
    rl = tl;
}

int
cftal::math::payne_hanek_pi_over_2<double, void>::
rem(double& xrh, double& xrl, double x)
{
    x*=scale_down_f64();
    // d_traits::veltkamp_split(x, x1, x2);
    double x1= round_to_nearest_even_last_bits<27>(x);
    double ipart, mh, ml;
    process_part(ipart, mh, ml, x1);
    double x2= x - x1;
    process_and_add_part(ipart, mh, ml, x2);
    // multiply mh, ml with pi/2
    using c_t = impl::d_real_constants<d_real<double>, double>;
    double th, tl;
    d_ops::unorm_mul22(th, tl, mh, ml, c_t::m_pi_2[0], c_t::m_pi_2[1]);
    d_ops::add12(mh, ml, th, tl);
    xrh=mh;
    xrl=ml;
    // return last 2 bits of the integer part
    return ((int)ipart)&3;
}

int
cftal::math::payne_hanek_pi_over_2<double, void>::
rem(double& xrh, double& xrl, double xh, double xl)
{
    xh*=scale_down_f64();
    xl*=scale_down_f64();
    // d_traits::veltkamp_split(x, x1, x2);
    double x1= round_to_nearest_even_last_bits<27>(xh);
    double ipart, mh, ml;
    process_part(ipart, mh, ml, x1);
    double x2= xh - x1;
    process_and_add_part(ipart, mh, ml, x2);
    double x3= round_to_nearest_even_last_bits<27>(xl);
    process_and_add_part(ipart, mh, ml, x3);
    double x4= xl - x3;
    process_and_add_part(ipart, mh, ml, x4);
    // multiply mh, ml with pi/2
    using c_t = impl::d_real_constants<d_real<double>, double>;
    double th, tl;
    d_ops::unorm_mul22(th, tl, mh, ml, c_t::m_pi_2[0], c_t::m_pi_2[1]);
    d_ops::add12(mh, ml, th, tl);
    xrh=mh;
    xrl=ml;
    // return last 2 bits of the integer part
    return ((int)ipart)&3;
}

inline
void
cftal::math::payne_hanek_pi_over_2<float, void>::
process_part(double& ipart, double& r, float x)
{
    constexpr const double scale_down_f64 = 0x1p0;
    constexpr const double scale_step_f64 = 0x1p-24;
    constexpr const double scale_up_f64 =
        1.0/scale_down_f64 * scale_step_f64;
    constexpr const int bits_per_elem_f64=24;
    // exp_shift_down C is determined by
    // (with scale_down 0x1p0)
    // note: we use the float bias here and use the
    // fact, that a float mantissa has only 24 bits
    // (((x_e - 0) + 127) - C)/24 = (x_e - 25)/24
    // ==> C = -0 + 127 + 25 = 152
    constexpr const int exp_shift_down_f64=152;
    // number of 24 bit chunks to use:  72 bits
    constexpr const int elem_count_f64=5;

    int32_t k = (as<uint32_t>(x) >> 23) & 255;

#if 1
    const int32_t shift_1_24= 0x12;
    const int32_t fac_1_24= 0x2aab;
    int32_t ks=k-exp_shift_down_f64;
    k= (ks*fac_1_24)>> shift_1_24;
#else
    k = (k-exp_shift_down_f64)/bits_per_elem_f64;
#endif
    double xd=double(x);
    using std::max;
    k = max(k, 0);
    const int64_t scale_i = as<int64_t>(scale_up_f64);
    double scale = as<double>(scale_i - (int64_t(k*bits_per_elem_f64)<<52));
    double p[elem_count_f64];
    const double *pibits=two_over_pi_b24_dbl;
    for (uint32_t i=0; i<elem_count_f64; ++i) {
        p[i] = xd*pibits[k+i]*scale;
        scale *= scale_step_f64;
    }
    // ip contains the integer parts of pi[i]
    double ip=__rint(p[0]);
    p[0] -= ip;
    for (uint32_t i=1; i<elem_count_f64; ++i) {
        double ii= __rint(p[i]);
        ip += ii;
        p[i] -= ii;
    }
    // ps  sum of p[i]
    double ps = p[elem_count_f64-1];
    for (uint32_t i=1; i<elem_count_f64; ++i) {
        ps += p[(elem_count_f64-1)-i];
    }
    // subtract integer part from ps
    double ii=__rint(ps);
    ip += ii;
    ps -= ii;
    // remove multiple of 4 from integer part
    ii = __r4int(ip);
    ip -= ii;
    ipart = ip;
    r = ps;
}

inline
void
cftal::math::payne_hanek_pi_over_2<float, void>::
process_and_add_part(double& ipa, double& r, float x)
{
    double ipart = ipa;
    double m1 = r;
    double ipart2, m2;
    process_part(ipart2, m2, x);
    ipart += ipart2;
    double m= m1 + m2;
    // if (m > 0.5)
    //    {m-=1.0; ipart+=1.0;}
    // else if (m < -0.5)
    //    {m+=1.0; ipart-=1.0;}
    auto m_gt_half = m > 0.5;
    auto m_lt_mhalf = m < -0.5;
#if 0
    auto m_m_1 = m - 1.0;
    auto ipart_p_1 = ipart + 1.0;
    auto m_p_1 = m + 1.0;
    auto ipart_m_1 = ipart - 1.0;
    m = select(m_gt_half, m_m_1, m);
    ipart = select(m_gt_half, ipart_p_1, ipart);
    m = select(m_lt_mhalf, m_p_1, m);
    ipart = select(m_lt_mhalf, ipart_m_1, ipart);
#else
    double m_corr = select(m_gt_half, -1.0, 0.0);
    double ipart_corr= select(m_gt_half, +1.0, 0.0);
    m_corr = select(m_lt_mhalf, +1.0, m_corr);
    ipart_corr= select(m_lt_mhalf, -1.0, ipart_corr);
    m += m_corr;
    ipart += ipart_corr;
#endif
    ipa=ipart;
    r = m;
}

int
cftal::math::payne_hanek_pi_over_2<float, void>::
rem(float& xrh, float& xrl, float x)
{
    double ipart, m;
    process_part(ipart, m, x);
    // multiply m with pi/2
    using c_t = impl::d_real_constants<d_real<double>, double>;
    double t= m * c_t::m_pi_2[0];
    split_f64_to_f32pair(t, xrh, xrl);
    // return last 2 bits of the integer part
    return ((int)ipart)&3;
}

int
cftal::math::payne_hanek_pi_over_2<float, void>::
rem(float& xrh, float& xrl, float xh, float xl)
{
    double ipart, m;
    process_part(ipart, m, xrh);
    process_and_add_part(ipart, m, xrl);
    // multiply m with pi/2
    using c_t = impl::d_real_constants<d_real<double>, double>;
    double t= m * c_t::m_pi_2[0];
    split_f64_to_f32pair(t, xrh, xrl);
    // return last 2 bits of the integer part
    return ((int)ipart)&3;
}
