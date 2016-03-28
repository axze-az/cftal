#if !defined (__MATH_IMPL_D_REAL_CONSTANTS_F64_H__)
#define __MATH_IMPL_D_REAL_CONSTANTS_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/std_types.h>
#include <cftal/math_func_constants.h>


namespace cftal {

    namespace math {

        namespace impl {

            template <class _T>
            struct d_real_constants<_T, double> {
                // exp(x) may be to large
                static const double exp_arg_large;
                // log(x): avoid denormals
                static const double log_arg_small;
                // if above factor to multiply with
                static const double log_arg_small_factor;
                // large sin cos argument
                static const double sin_cos_arg_large;
                // large native sin cos argument
                static const double native_sin_cos_arg_large;
                // M_LN2 LOG_E(2) for cody and waite argument reduction
                static const double m_ln2_cw[2];
                // M_LD2 LOG_10(2) for cody and waite argument reduction
                static const double m_ld2_cw[2];
                // M_PI/2 for cody and waite argument reduction
                static const double m_pi_2_cw[];

                // expansion of pi/2
                static const unsigned PI_2_BITS_MAX=3;
                static const double m_pi_2_bits[PI_2_BITS_MAX];

                // 1/(i!)
                static const unsigned MAX_FAC=30;
                static const _T inv_fac[MAX_FAC+1];
                // 2/i i=0,1,2,3,4...
                static const unsigned MAX_2_OVER_I=30;
                static const _T _2_over_i[MAX_2_OVER_I+1];

                // coefficents for log(x) 2/i in reverse order
                static const unsigned MAX_LOG_COEFF=12;
                static const _T log_coeff[MAX_LOG_COEFF];

                // coefficents for exp(x)
                static const unsigned MAX_EXP_COEFF=7;
                static const _T exp_coeff[MAX_EXP_COEFF];
                // polynomial of degree 12
                static const unsigned MAX_NATIVE_EXP_COEFF=7;
                static const double native_exp_coeff[MAX_NATIVE_EXP_COEFF];

                // table for sin -1/21! +1/19! .. -1/3! with alternating signs
                static const unsigned MAX_SIN_COEFF=11;
                static const _T sin_coeff[MAX_SIN_COEFF];
                static const double native_sin_coeff[MAX_SIN_COEFF];
                // table for cos -1/22! +1/20! .. +1/4! with alternating signs
                static const unsigned MAX_COS_COEFF=12;
                static const _T cos_coeff[MAX_COS_COEFF];
                static const double native_cos_coeff[MAX_COS_COEFF];

                // table for atan2
                static const unsigned MAX_ATAN2_COEFF=25;
                static const _T atan2_coeff[MAX_ATAN2_COEFF];

                // M_LN2 LOG_E(2)
                static const _T m_ln2;
                // M_LD2 LOG_10(2)
                static const _T m_ld2;
                // M_LN10 LOG_E(10)
                static const _T m_ln10;
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

        } // impl
    } // math
} // cftal

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
exp_arg_large= 7.0900000000000000000000e+02;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
log_arg_small= 2.0041683600089727779961e-292;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
log_arg_small_factor= 8.1129638414606681695789e+31;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
sin_cos_arg_large= 0x1.0p31;

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
native_sin_cos_arg_large= 0x1.0p31;

/* ----------------------------------------------------------------*/
template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_ln2_cw[2]={
   +6.9314718036912381649017e-01,
   +1.9082149292705877000220e-10
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_ld2_cw[2]={
   +3.0102999554947018623352e-01,
   +1.1451100898021838421065e-10
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_pi_2_cw[3]={
   +1.5707963267341256141663e+00,
   +6.0771005063039659765955e-11,
   +2.0222662487959506315411e-21
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
m_pi_2_bits[PI_2_BITS_MAX]={
   +1.5707963267948965579990e+00,
   +6.1232339957367660358688e-17,
   -1.4973849048591698329435e-33
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
    +6.9314718055994528622676e-01, +2.3190468138462995584178e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln2(
    +1.4426950408889633870047e+00, +2.0355273740931033111021e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ld2(
    +3.0102999566398119801747e-01, -2.8037281277851703937326e-18);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ld2(
    +3.3219280948873621817086e+00, +1.6616175169735920064130e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln10(
    +2.3025850929940454570044e+00, +2.2701358751183765644142e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln10(
    +4.3429448190325181666793e-01, +1.0983196502167650727389e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2pow106(
    +7.3473601139354201450260e+01, +1.3479665980519211209217e-15);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2pow48(
    +3.3271064666877371962528e+01, +2.8894993100464744006298e-15);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln_small_arg(
    +7.3473601139354201450260e+01, +1.3479665980519211209217e-15);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi(
    +3.1415926535897931159980e+00, +1.2246467991473532071738e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi2(
    +6.2831853071795862319959e+00, +2.4492935982947064143475e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_2(
    +1.5707963267948965579990e+00, +6.1232339957367660358688e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_4(
    +7.8539816339744827899949e-01, +3.0616169978683830179344e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi(
    +3.1830988618379069121644e-01, -1.9678676675182485881895e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_2_pi(
    +6.3661977236758138243289e-01, -3.9357353350364971763790e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_4_pi(
    +1.2732395447351627648658e+00, -7.8714706700729943527581e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
inv_fac[MAX_FAC+1]= {
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00),
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00),
    _T( +5.0000000000000000000000e-01, +0.0000000000000000000000e+00),
    _T( +1.6666666666666665741481e-01, +9.2518585385429706566156e-18),
    _T( +4.1666666666666664353702e-02, +2.3129646346357426641539e-18),
    _T( +8.3333333333333332176851e-03, +1.1564823173178713802252e-19),
    _T( +1.3888888888888889418943e-03, -5.3005439543735770590566e-20),
    _T( +1.9841269841269841252632e-04, +1.7209558293420705286779e-22),
    _T( +2.4801587301587301565790e-05, +2.1511947866775881608473e-23),
    _T( +2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
    _T( +2.7557319223985888275786e-07, +2.3767714622250297318518e-23),
    _T( +2.5052108385441720223866e-08, -1.4488140709359119660293e-24),
    _T( +2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
    _T( +1.6059043836821613340863e-10, +1.2585294588752098052117e-26),
    _T( +1.1470745597729724507297e-11, +2.0655512752830745424540e-28),
    _T( +7.6471637318198164055138e-13, +7.0387287773345300106125e-30),
    _T( +4.7794773323873852534462e-14, +4.3992054858340812566328e-31),
    _T( +2.8114572543455205981105e-15, +1.6508842730861432599403e-31),
    _T( +1.5619206968586225271148e-16, +1.1910679660273754002389e-32),
    _T( +8.2206352466243294955370e-18, +2.2141894119604265363725e-34),
    _T( +4.1103176233121648440650e-19, +1.4412973378659527149817e-36),
    _T( +1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
    _T( +8.8967913924505740778892e-22, -7.9114026148723762170263e-38),
    _T( +3.8681701706306841261487e-23, -8.8431776554823438478877e-40),
    _T( +1.6117375710961183858953e-24, -3.6846573564509766032865e-41),
    _T( +6.4469502843844735894989e-26, -1.9330404233703464824544e-42),
    _T( +2.4795962632247975896123e-27, -1.2953730964765228775764e-43),
    _T( +9.1836898637955460053942e-29, +1.4303150396787322024232e-45),
    _T( +3.2798892370698377589766e-30, +1.5117542744029878689714e-46),
    _T( +1.1309962886447715881757e-31, +1.0498015412959506023854e-47),
    _T( +3.7699876288159053851494e-33, +2.5870347832750323834849e-49)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
_2_over_i[MAX_2_OVER_I+1]= {
    _T( +2.0000000000000000000000e+00, +0.0000000000000000000000e+00),
    _T( +2.0000000000000000000000e+00, +0.0000000000000000000000e+00),
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00),
    _T( +6.6666666666666662965923e-01, +3.7007434154171882626462e-17),
    _T( +5.0000000000000000000000e-01, +0.0000000000000000000000e+00),
    _T( +4.0000000000000002220446e-01, -2.2204460492503132041068e-17),
    _T( +3.3333333333333331482962e-01, +1.8503717077085941313231e-17),
    _T( +2.8571428571428569842539e-01, +1.5860328923216521125627e-17),
    _T( +2.5000000000000000000000e-01, +0.0000000000000000000000e+00),
    _T( +2.2222222222222220988641e-01, +1.2335811384723960875487e-17),
    _T( +2.0000000000000001110223e-01, -1.1102230246251566020534e-17),
    _T( +1.8181818181818182322829e-01, -5.0464682937507116874478e-18),
    _T( +1.6666666666666665741481e-01, +9.2518585385429706566156e-18),
    _T( +1.5384615384615385469402e-01, -8.5401771125012046311799e-18),
    _T( +1.4285714285714284921269e-01, +7.9301644616082605628134e-18),
    _T( +1.3333333333333333148296e-01, +1.8503717077085942083603e-18),
    _T( +1.2500000000000000000000e-01, +0.0000000000000000000000e+00),
    _T( +1.1764705882352941013202e-01, +1.6326809185664066544356e-18),
    _T( +1.1111111111111110494321e-01, +6.1679056923619804377437e-18),
    _T( +1.0526315789473683626198e-01, +5.8432790769745077831256e-18),
    _T( +1.0000000000000000555112e-01, -5.5511151231257830102669e-18),
    _T( +9.5238095238095232808462e-02, +5.2867763077388403752089e-18),
    _T( +9.0909090909090911614143e-02, -2.5232341468753558437239e-18),
    _T( +8.6956521739130432369080e-02, +2.4135283144025141513234e-18),
    _T( +8.3333333333333328707404e-02, +4.6259292692714853283078e-18),
    _T( +8.0000000000000001665335e-02, -1.6653345369377347490057e-18),
    _T( +7.6923076923076927347012e-02, -4.2700885562506023155900e-18),
    _T( +7.4074074074074069962137e-02, +4.1119371282413202918292e-18),
    _T( +7.1428571428571424606346e-02, +3.9650822308041302814067e-18),
    _T( +6.8965517241379309387739e-02, +9.5708881433203148708292e-19),
    _T( +6.6666666666666665741481e-02, +9.2518585385429710418016e-19)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
log_coeff[MAX_LOG_COEFF]= {
    // + 2/25
    _T( +8.0000000000000001665335e-02, -1.6653345369377347490057e-18),
    // + 2/23
    _T( +8.6956521739130432369080e-02, +2.4135283144025141513234e-18),
    // + 2/21
    _T( +9.5238095238095232808462e-02, +5.2867763077388403752089e-18),
    // + 2/19
    _T( +1.0526315789473683626198e-01, +5.8432790769745077831256e-18),
    // + 2/17
    _T( +1.1764705882352941013202e-01, +1.6326809185664066544356e-18),
    // + 2/15
    _T( +1.3333333333333333148296e-01, +1.8503717077085942083603e-18),
    // + 2/13
    _T( +1.5384615384615385469402e-01, -8.5401771125012046311799e-18),
    // + 2/11
    _T( +1.8181818181818182322829e-01, -5.0464682937507116874478e-18),
    // + 2/9
    _T( +2.2222222222222220988641e-01, +1.2335811384723960875487e-17),
    // + 2/7
    _T( +2.8571428571428569842539e-01, +1.5860328923216521125627e-17),
    // + 2/5
    _T( +4.0000000000000002220446e-01, -2.2204460492503132041068e-17),
    // + 2/3
    _T( +6.6666666666666662965923e-01, +3.7007434154171882626462e-17)
};

#if 1
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
exp_coeff[MAX_EXP_COEFF] =  {
    // + 1/7!
    _T( +1.9841269841269841252632e-04, +1.7209558293420705286779e-22),
    // + 1/6!
    _T( +1.3888888888888889418943e-03, -5.3005439543735770590566e-20),
    // + 1/5!
    _T( +8.3333333333333332176851e-03, +1.1564823173178713802252e-19),
    // + 1/4!
    _T( +4.1666666666666664353702e-02, +2.3129646346357426641539e-18),
    // + 1/3!
    _T( +1.6666666666666665741481e-01, +9.2518585385429706566156e-18),
    // + 1/2!
    _T( +5.0000000000000000000000e-01, +0.0000000000000000000000e+00),
    // + 1/1!
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00)
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
native_exp_coeff[MAX_EXP_COEFF] =  {
    // + 1/7!
    +1.9841269841269841252632e-04,
    // + 1/6!
    +1.3888888888888889418943e-03,
    // + 1/5!
    +8.3333333333333332176851e-03,
    // + 1/4!
    +4.1666666666666664353702e-02,
    // + 1/3!
    +1.6666666666666665741481e-01,
    // + 1/2!
    +5.0000000000000000000000e-01,
    // + 1/1!
    +1.0000000000000000000000e+00
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
sin_coeff[MAX_SIN_COEFF] =  {
    // +1/21!
    _T( +1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
    // -1/19!
    _T( -8.2206352466243294955370e-18, -2.2141894119604265363725e-34),
    // +1/17!
    _T( +2.8114572543455205981105e-15, +1.6508842730861432599403e-31),
    // -1/15!
    _T( -7.6471637318198164055138e-13, -7.0387287773345300106125e-30),
    // +1/13!
    _T( +1.6059043836821613340863e-10, +1.2585294588752098052117e-26),
    // -1/11!
    _T( -2.5052108385441720223866e-08, +1.4488140709359119660293e-24),
    // +1/9!
    _T( +2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
    // -1/7!
    _T( -1.9841269841269841252632e-04, -1.7209558293420705286779e-22),
    // +1/5!
    _T( +8.3333333333333332176851e-03, +1.1564823173178713802252e-19),
    // -1/3!
    _T( -1.6666666666666665741481e-01, -9.2518585385429706566156e-18),
    // +1/1!
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00)
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
native_sin_coeff[MAX_SIN_COEFF] =  {
    // +1/21!
    +1.9572941063391262595198e-20,
    // -1/19!
    -8.2206352466243294955370e-18,
    // +1/17!
    +2.8114572543455205981105e-15,
    // -1/15!
    -7.6471637318198164055138e-13,
    // +1/13!
    +1.6059043836821613340863e-10,
    // -1/11!
    -2.5052108385441720223866e-08,
    // +1/9!
    +2.7557319223985892510951e-06,
    // -1/7!
    -1.9841269841269841252632e-04,
    // +1/5!
    +8.3333333333333332176851e-03,
    // -1/3!
    -1.6666666666666665741481e-01,
    // +1/1!
    +1.0000000000000000000000e+00
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
cos_coeff[MAX_COS_COEFF] =  {
    // -1/22!
    _T( -8.8967913924505740778892e-22, +7.9114026148723762170263e-38),
    // +1/20!
    _T( +4.1103176233121648440650e-19, +1.4412973378659527149817e-36),
    // -1/18!
    _T( -1.5619206968586225271148e-16, -1.1910679660273754002389e-32),
    // +1/16!
    _T( +4.7794773323873852534462e-14, +4.3992054858340812566328e-31),
    // -1/14!
    _T( -1.1470745597729724507297e-11, -2.0655512752830745424540e-28),
    // +1/12!
    _T( +2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
    // -1/10!
    _T( -2.7557319223985888275786e-07, -2.3767714622250297318518e-23),
    // +1/8!
    _T( +2.4801587301587301565790e-05, +2.1511947866775881608473e-23),
    // -1/6!
    _T( -1.3888888888888889418943e-03, +5.3005439543735770590566e-20),
    // +1/4!
    _T( +4.1666666666666664353702e-02, +2.3129646346357426641539e-18),
    // -1/2!
    _T( -5.0000000000000000000000e-01, +0.0000000000000000000000e+00),
    // +1/0!
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00)
};

template <class _T>
const double
cftal::math::impl::d_real_constants<_T, double>::
native_cos_coeff[MAX_COS_COEFF] =  {
    // -1/22!
    -8.8967913924505740778892e-22,
    // +1/20!
    +4.1103176233121648440650e-19,
    // -1/18!
    -1.5619206968586225271148e-16,
    // +1/16!
    +4.7794773323873852534462e-14,
    // -1/14!
    -1.1470745597729724507297e-11,
    // +1/12!
    +2.0876756987868100186555e-09,
    // -1/10!
    -2.7557319223985888275786e-07,
    // +1/8!
    +2.4801587301587301565790e-05,
    // -1/6!
    -1.3888888888888889418943e-03,
    // +1/4!
    +4.1666666666666664353702e-02,
    // -1/2!
    -5.0000000000000000000000e-01,
    // +1/0!
    +1.0000000000000000000000e+00
};

#endif
template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
atan2_coeff[MAX_ATAN2_COEFF] =  {
    // prod(even numbers to 48)/product(odd numbers to 49)
    _T( +1.7813377193108356766338e-01, +8.2639790981134668507681e-18),
    // prod(even numbers to 46)/product(odd numbers to 47)
    _T( +1.8184489217964780460868e-01, +1.2483833439936714220578e-17),
    // prod(even numbers to 44)/product(odd numbers to 45)
    _T( +1.8579804200964017413256e-01, -1.3190208256413428702000e-17),
    // prod(even numbers to 42)/product(odd numbers to 43)
    _T( +1.9002072478258652532546e-01, +2.9110362379033512864522e-18),
    // prod(even numbers to 40)/product(odd numbers to 41)
    _T( +1.9454502775360049682263e-01, -3.6281237601534529159507e-18),
    // prod(even numbers to 38)/product(odd numbers to 39)
    _T( +1.9940865344744049258985e-01, +1.2934518515220058347504e-17),
    // prod(even numbers to 36)/product(odd numbers to 37)
    _T( +2.0465624959079420364105e-01, -6.0288722640439653275903e-19),
    // prod(even numbers to 34)/product(odd numbers to 35)
    _T( +2.1034114541276072163356e-01, -1.2955445478528480125310e-17),
    // prod(even numbers to 32)/product(odd numbers to 33)
    _T( +2.1652764968960661051689e-01, +1.3576402744948126907721e-18),
    // prod(even numbers to 30)/product(odd numbers to 31)
    _T( +2.2329413874240680581984e-01, +1.2675769126922021695018e-17),
    // prod(even numbers to 28)/product(odd numbers to 29)
    _T( +2.3073727670048704840866e-01, -2.6298647510369619301622e-18),
    // prod(even numbers to 26)/product(odd numbers to 27)
    _T( +2.3897789372550443109944e-01, +9.1714582002669668546491e-18),
    // prod(even numbers to 24)/product(odd numbers to 25)
    _T( +2.4816935117648539210755e-01, -1.1826236188668083689288e-17),
    // prod(even numbers to 22)/product(odd numbers to 23)
    _T( +2.5850974080883892813887e-01, +9.6541679991769692886780e-18),
    // prod(even numbers to 20)/product(odd numbers to 21)
    _T( +2.7026018357287706628256e-01, +5.0465255235706661365759e-18),
    // prod(even numbers to 18)/product(odd numbers to 19)
    _T( +2.8377319275152090849446e-01, +1.6401082046000763576527e-17),
    // prod(even numbers to 16)/product(odd numbers to 17)
    _T( +2.9953837012660544658615e-01, -2.5863086575755280658533e-17),
    // prod(even numbers to 14)/product(odd numbers to 15)
    _T( +3.1825951825951825924221e-01, +2.7604612888892781089931e-19),
    // prod(even numbers to 12)/product(odd numbers to 13)
    _T( +3.4099234099234099204523e-01, +2.9576370952385122596355e-19),
    // prod(even numbers to 10)/product(odd numbers to 11)
    _T( +3.6940836940836940804900e-01, +3.2041068531750549479384e-19),
    // prod(even numbers to 8)/product(odd numbers to 9)
    _T( +4.0634920634920634885390e-01, +3.5245175384925604427323e-19),
    // prod(even numbers to 6)/product(odd numbers to 7)
    _T( +4.5714285714285712858285e-01, +1.4274296030894868396767e-17),
    // prod(even numbers to 4)/product(odd numbers to 5)
    _T( +5.3333333333333332593185e-01, +7.4014868308343768334413e-18),
    // prod(even numbers to 2)/product(odd numbers to 3)
    _T( +6.6666666666666662965923e-01, +3.7007434154171882626462e-17),
    // prod(even numbers to 0)/product(odd numbers to 1)
    _T( +1.0000000000000000000000e+00, +0.0000000000000000000000e+00)
};

// Local Variables:
// mode: c++
// end:
#endif
