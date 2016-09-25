#if !defined (__CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F32_H__)
#define __CFTAL_MATH_IMPL_D_REAL_CONSTANTS_F32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/math/func_constants.h>

namespace cftal {
    namespace math {

        namespace impl {

            template <class _T>
            struct d_real_constants<_T, float> {
                // large exp argument
                static const float exp_arg_large;
                // log(x): avoid denormals
                static const float log_arg_small;
                // if above factor to multiply with
                static const float log_arg_small_factor;
                // large sin cos argument
                static const float sin_cos_arg_large;
                // large native sin cos argument
                static const float native_sin_cos_arg_large;
                // M_LN2 LOG_E(2) for cody and waite argument reduction
                static const float m_ln2_cw[2];
                // M_LD2 LOG_10(2) for cody and waite argument reduction
                static const float m_ld2_cw[2];
                // M_PI/2 for cody and waite argument reduction
                static const float m_pi_2_cw[3];

                // expansion of pi/2
                static const unsigned PI_2_BITS_MAX=3;
                static const float m_pi_2_bits[PI_2_BITS_MAX];
                // 1/(i!)
                static const unsigned MAX_FAC=20;
                static const _T inv_fac[MAX_FAC+1];
                // 2/i i=0,1,2,3,4...
                static const unsigned MAX_2_OVER_I=20;
                static const _T _2_over_i[MAX_2_OVER_I+1];

                // coefficents for log(x)
                static const unsigned MAX_LOG_COEFF=6;
                static const _T log_coeff[MAX_LOG_COEFF];

                // coefficents for exp(x)
                static const unsigned MAX_EXP_COEFF=4;
                static const _T exp_coeff[MAX_EXP_COEFF];
                static const unsigned MAX_NATIVE_EXP_COEFF=4;
                static const float native_exp_coeff[MAX_NATIVE_EXP_COEFF];

                // table for sin -1/21! +1/19! .. -1/3! with alternating signs
                static const unsigned MAX_SIN_COEFF=8;
                static const _T sin_coeff[MAX_SIN_COEFF];
                static const float native_sin_coeff[MAX_SIN_COEFF];
                // table for cos -1/22! +1/20! .. +1/4! with alternating signs
                static const unsigned MAX_COS_COEFF=9;
                static const _T cos_coeff[MAX_COS_COEFF];
                static const float native_cos_coeff[MAX_COS_COEFF];

                // table for atan2
                static const unsigned MAX_ATAN2_COEFF=13;
                static const _T atan2_coeff[MAX_ATAN2_COEFF];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
                // M_LD(2) LOG_10(2)
                static const _T m_ld2;
                // M_LN_2POW106
                static const _T m_ln2pow106;
                // M_LN_2POW48
                static const _T m_ln2pow48;
                // M_LN_2_SMALL_ARG
                static const _T m_ln_small_arg;
                // low half of m_ln2
                // static const _T m_ln2_low;
                // M_1_LN2 1/LOG_E(2)
                static const _T m_1_ln2;
                // M_1_LD2 1/LOG_10(2)
                static const _T m_1_ld2;
                // M_1_LN10 1/LOG_E(10)
                static const _T m_1_ln10;
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
    }
}

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
exp_arg_large= 8.8000000000000e+01f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
log_arg_small= 1.9721522630525e-31f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
log_arg_small_factor= 2.8147497671066e+14f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
sin_cos_arg_large= 0x1.0p24f;

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
native_sin_cos_arg_large= 0x1.0p20f;

/* ---------------------------------------------------------------- */
template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_ln2_cw[2]={
   +6.9314575195312e-01f,
   +1.4286067653302e-06f
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_ld2_cw[2]={
   +3.0102539062500e-01f,
   +4.6050390665187e-06f
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_pi_2_cw[3]={
   +1.5707397460938e+00f,
   +5.6579709053040e-05f,
   +9.9209362947050e-10f
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
m_pi_2_bits[PI_2_BITS_MAX]={
   +1.5707963705063e+00f,
   -4.3711388286738e-08f,
   -1.7151245100059e-15f
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2(
    +6.9314718246460e-01f, -1.9046542121259e-09f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ln2(
    +1.4426950216293e+00f, +1.9259630335000e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ld2(
    +3.0103000998497e-01f, -1.4320988839245e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ld2(
    +3.3219280242920e+00f, +7.0595369550119e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln10(
    +2.3025848865509e+00f, +2.0644314702167e-07f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_ln10(
    +4.3429446220398e-01f, +1.9699271547324e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2pow106(
    +7.3473594665527e+01f, +6.4738269429654e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln2pow48(
    +3.3271060943604e+01f, +3.7232739487081e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_ln_small_arg(
    +3.3271060943604e+01f, +3.7232739487081e-06f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi(
    +3.1415927410126e+00f, -8.7422776573476e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi2(
    +6.2831854820251e+00f, -1.7484555314695e-07f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi_2(
    +1.5707963705063e+00f, -4.3711388286738e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_pi_4(
    +7.8539818525314e-01f, -2.1855694143369e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_1_pi(
    +3.1830987334251e-01f, +1.2841276486597e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_2_pi(
    +6.3661974668503e-01f, +2.5682552973194e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::m_4_pi(
    +1.2732394933701e+00f, +5.1365105946388e-08f);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
inv_fac[MAX_FAC+1]= {
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f),
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f),
    _T( +5.0000000000000e-01f, +0.0000000000000e+00f),
    _T( +1.6666667163372e-01f, -4.9670538793123e-09f),
    _T( +4.1666667908430e-02f, -1.2417634698281e-09f),
    _T( +8.3333337679505e-03f, -4.3461720333760e-10f),
    _T( +1.3888889225200e-03f, -3.3631094437103e-11f),
    _T( +1.9841270113830e-04f, -2.7255968749335e-12f),
    _T( +2.4801587642287e-05f, -3.4069960936668e-13f),
    _T( +2.7557318844629e-06f, +3.7935712242972e-14f),
    _T( +2.7557319981497e-07f, -7.5751122090512e-15f),
    _T( +2.5052107943679e-08f, +4.4176230446484e-16f),
    _T( +2.0876755879584e-09f, +1.1082839147460e-16f),
    _T( +1.6059044372074e-10f, -5.3525265115627e-18f),
    _T( +1.1470745360509e-11f, +2.3722076892312e-19f),
    _T( +7.6471636098127e-13f, +1.2200710471178e-20f),
    _T( +4.7794772561329e-14f, +7.6254440444864e-22f),
    _T( +2.8114573589664e-15f, -1.0462084739764e-22f),
    _T( +1.5619206814542e-16f, +1.5404471465942e-24f),
    _T( +8.2206350784765e-18f, +1.6814780968559e-25f),
    _T( +4.1103175909370e-19f, +3.2375117328603e-27f)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
_2_over_i[MAX_2_OVER_I+1]= {
    _T( +2.0000000000000e+00f, +0.0000000000000e+00f),
    _T( +2.0000000000000e+00f, +0.0000000000000e+00f),
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f),
    _T( +6.6666668653488e-01f, -1.9868215517249e-08f),
    _T( +5.0000000000000e-01f, +0.0000000000000e+00f),
    _T( +4.0000000596046e-01f, -5.9604645663569e-09f),
    _T( +3.3333334326744e-01f, -9.9341077586246e-09f),
    _T( +2.8571429848671e-01f, -1.2772424007323e-08f),
    _T( +2.5000000000000e-01f, +0.0000000000000e+00f),
    _T( +2.2222222387791e-01f, -1.6556845894300e-09f),
    _T( +2.0000000298023e-01f, -2.9802322831785e-09f),
    _T( +1.8181818723679e-01f, -5.4186042319770e-09f),
    _T( +1.6666667163372e-01f, -4.9670538793123e-09f),
    _T( +1.5384615957737e-01f, -5.7312159462697e-09f),
    _T( +1.4285714924335e-01f, -6.3862120036617e-09f),
    _T( +1.3333334028721e-01f, -6.9538752534015e-09f),
    _T( +1.2500000000000e-01f, +0.0000000000000e+00f),
    _T( +1.1764705926180e-01f, -4.3826944851055e-10f),
    _T( +1.1111111193895e-01f, -8.2784229471500e-10f),
    _T( +1.0526315867901e-01f, -7.8427164762473e-10f),
    _T( +1.0000000149012e-01f, -1.4901161415892e-09f)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
log_coeff[MAX_LOG_COEFF]= {
    // + 2/13
    _T( +1.5384615957737e-01f, -5.7312159462697e-09f),
    // + 2/11
    _T( +1.8181818723679e-01f, -5.4186042319770e-09f),
    // + 2/9
    _T( +2.2222222387791e-01f, -1.6556845894300e-09f),
    // + 2/7
    _T( +2.8571429848671e-01f, -1.2772424007323e-08f),
    // + 2/5
    _T( +4.0000000596046e-01f, -5.9604645663569e-09f),
    // + 2/3
    _T( +6.6666668653488e-01f, -1.9868215517249e-08f)
};

#if 1
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
exp_coeff[MAX_EXP_COEFF] =  {
    // + 1/4!
    _T( +4.1666667908430e-02f, -1.2417634698281e-09f),
    // + 1/3!
    _T( +1.6666667163372e-01f, -4.9670538793123e-09f),
    // + 1/2!
    _T( +5.0000000000000e-01f, +0.0000000000000e+00f),
    // + 1/1!
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f)
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
native_exp_coeff[MAX_NATIVE_EXP_COEFF] =  {
    // + 1/4!
    +4.1666667908430e-02f,
    // + 1/3!
    +1.6666667163372e-01f,
    // + 1/2!
    +5.0000000000000e-01f,
    // + 1/1!
    +1.0000000000000e+00f
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
sin_coeff[MAX_SIN_COEFF] =  {
    // -1/15!
    _T( -7.6471636098127e-13f, -1.2200710471178e-20f),
    // +1/13!
    _T( +1.6059044372074e-10f, -5.3525265115627e-18f),
    // -1/11!
    _T( -2.5052107943679e-08f, -4.4176230446484e-16f),
    // +1/9!
    _T( +2.7557318844629e-06f, +3.7935712242972e-14f),
    // -1/7!
    _T( -1.9841270113830e-04f, +2.7255968749335e-12f),
    // +1/5!
    _T( +8.3333337679505e-03f, -4.3461720333760e-10f),
    // -1/3!
    _T( -1.6666667163372e-01f, +4.9670538793123e-09f),
    // +1/1!
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f)
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
native_sin_coeff[MAX_SIN_COEFF] =  {
    // -1/15!
    -7.6471636098127e-13f,
    // +1/13!
    +1.6059044372074e-10f,
    // -1/11!
    -2.5052107943679e-08f,
    // +1/9!
    +2.7557318844629e-06f,
    // -1/7!
    -1.9841270113830e-04f,
    // +1/5!
    +8.3333337679505e-03f,
    // -1/3!
    -1.6666667163372e-01f,
    // +1/1!
    +1.0000000000000e+00f
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
cos_coeff[MAX_COS_COEFF] =  {
    // +1/16!
    _T( +4.7794772561329e-14f, +7.6254440444864e-22f),
    // -1/14!
    _T( -1.1470745360509e-11f, -2.3722076892312e-19f),
    // +1/12!
    _T( +2.0876755879584e-09f, +1.1082839147460e-16f),
    // -1/10!
    _T( -2.7557319981497e-07f, +7.5751122090512e-15f),
    // +1/8!
    _T( +2.4801587642287e-05f, -3.4069960936668e-13f),
    // -1/6!
    _T( -1.3888889225200e-03f, +3.3631094437103e-11f),
    // +1/4!
    _T( +4.1666667908430e-02f, -1.2417634698281e-09f),
    // -1/2!
    _T( -5.0000000000000e-01f, +0.0000000000000e+00f),
    // +1/0!
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f)
};

template <class _T>
const float
cftal::math::impl::d_real_constants<_T, float>::
native_cos_coeff[MAX_COS_COEFF] =  {
    // +1/16!
    +4.7794772561329e-14f,
    // -1/14!
    -1.1470745360509e-11f,
    // +1/12!
    +2.0876755879584e-09f,
    // -1/10!
    -2.7557319981497e-07f,
    // +1/8!
    +2.4801587642287e-05f,
    // -1/6!
    -1.3888889225200e-03f,
    // +1/4!
    +4.1666667908430e-02f,
    // -1/2!
    -5.0000000000000e-01f,
    // +1/0!
    +1.0000000000000e+00f
};

#endif
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, float>::
atan2_coeff[MAX_ATAN2_COEFF] =  {
    // prod(even numbers to 24)/product(odd numbers to 25)
    _T( +2.4816934764385e-01f, +3.5326330749541e-09f),
    // prod(even numbers to 22)/product(odd numbers to 23)
    _T( +2.5850975513458e-01f, -1.4325743258325e-08f),
    // prod(even numbers to 20)/product(odd numbers to 21)
    _T( +2.7026018500328e-01f, -1.4304035733659e-09f),
    // prod(even numbers to 18)/product(odd numbers to 19)
    _T( +2.8377318382263e-01f, +8.9288887394900e-09f),
    // prod(even numbers to 16)/product(odd numbers to 17)
    _T( +2.9953837394714e-01f, -3.8205381081013e-09f),
    // prod(even numbers to 14)/product(odd numbers to 15)
    _T( +3.1825950741768e-01f, +1.0841839426234e-08f),
    // prod(even numbers to 12)/product(odd numbers to 13)
    _T( +3.4099233150482e-01f, +9.4875192147015e-09f),
    // prod(even numbers to 10)/product(odd numbers to 11)
    _T( +3.6940836906433e-01f, +3.4403835336150e-10f),
    // prod(even numbers to 8)/product(odd numbers to 9)
    _T( +4.0634921193123e-01f, -5.5820223998637e-09f),
    // prod(even numbers to 6)/product(odd numbers to 7)
    _T( +4.5714285969734e-01f, -2.5544848458736e-09f),
    // prod(even numbers to 4)/product(odd numbers to 5)
    _T( +5.3333336114883e-01f, -2.7815501013606e-08f),
    // prod(even numbers to 2)/product(odd numbers to 3)
    _T( +6.6666668653488e-01f, -1.9868215517249e-08f),
    // prod(even numbers to 0)/product(odd numbers to 1)
    _T( +1.0000000000000e+00f, +0.0000000000000e+00f)
};

// Local Variables:
// mode: c++
// end:
#endif
