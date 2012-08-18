#include "x86vec_fvec.h"
#include "x86vec_cvt.h"
#include <cmath>
#include <limits>

namespace math {

        using std::int32_t;
        using std::uint32_t;
        using std::uint64_t;

        template <typename _F, typename _I>
        struct func_traits;

        template <typename _F, typename _I,
                  typename _T= func_traits<_F, _I> >
        struct base_func {};

        template <typename _F, typename _I,
                  typename _T= func_traits<_F, _I> >
        struct func {};


        template <>
        struct func_traits<double, int32_t> {
                typedef double vf_type;
                typedef int32_t vi_type;
                typedef bool vmf_type;
                typedef bool vmi_type;

                typedef union {
                        double _d;
                        uint64_t _u;
                } ud_t;

                static constexpr int32_t bias = 0x3ff;
                static constexpr int32_t e_max= 0x3ff;
                static constexpr int32_t e_min= -1022;
                static constexpr int32_t bits=52;

                static constexpr double infinity=
                        std::numeric_limits<double>::infinity();
                static constexpr double nan=
                        std::numeric_limits<double>::quiet_NaN();

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
                vf_type cvt_i_to_f(const vi_type& i) {
                        return vf_type(i);
                }
                // including rounding to nearest.
                static
                vi_type cvt_f_to_i(const vf_type& f) {
                        return f < 0 ? (vi_type)(f - 0.5) : (vi_type)(f + 0.5);
                }
                // including rounding towards zero
                static
                vi_type cvt_rz_f_to_i(const vf_type& f) {
                        return (vi_type)f;
                }
        };

        template <typename _T>
        class func<double, int32_t, _T> {
        public:
                typedef typename _T::vf_type vf_type;
                typedef typename _T::vi_type vi_type;
                typedef typename _T::vmf_type vmf_type;
                typedef typename _T::vmi_type vmi_type;

                static vf_type pow2i(const vi_type& vi);
                static vf_type ldexp(const vf_type& vf, const vi_type& vi);

                static vi_type ilogbp1(const vf_type& vi);
                static vi_type ilogb(const vf_type& vf);
        private:
                static vf_type atan2k(const vf_type& y, const vf_type& x);
        public:
                static vf_type atan2(const vf_type& y, const vf_type& x);
                static vf_type asin(const vf_type& d);
                static vf_type acos(const vf_type& d);
                static vf_type atan(const vf_type& d);
        };

};

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::pow2i(const vi_type& vi)
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
        r= _T::sel(mf, vf_type(_T::infinity), r);
        return r;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::ldexp(const vf_type& vd,
                                             const vi_type& ve)
{
        vi_type q= ve;
        vi_type m = q >> 31;
        m = (((m + q) >> 9) - m) << 7;
        q = q - (m << 2);
        vf_type fm = _T::insert_exp(m + 0x3ff);
        vf_type r = vd * fm * fm * fm * fm;
        vf_type fq = _T::insert_exp(q + 0x3ff);
        return r * fq;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vi_type
math::func<double, math::int32_t, _T>::ilogbp1(const vf_type& vd)
{
        vmf_type mf= vd < 4.9090934652977266E-91;
        vf_type d = _T::sel(mf, 2.037035976334486E90 * vd, vd);
        vi_type q = _T::extract_exp(d);
        vmi_type mi= _T::vmf_to_vmi(mf);
        vi_type qs = _T::sel(mi, vi_type(300 + 0x3fe), vi_type(0x3fe));
        return q - qs;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vi_type
math::func<double, math::int32_t, _T>::ilogb(const vf_type& d)
{
        vi_type e(ilogbp1(abs(d) -1));
        vmf_type mf= d == 0.0;
        vmi_type mi= _T::vmf_to_vmi(mf);
        e = _T::sel(mi, vi_type(-2147483648), e);
        mf = isinf(d);
        mi = _T::vmf_to_vmi(mf);
        e = _T::sel(mi, vi_type(2147483647), e);
        return e;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
atan2k(const vf_type& cy,  const vf_type& cx)
{
        vi_type q = 0;
        vmf_type mf = cx < 0;
        vmi_type mi = _T::vmf_to_vmi(mf);
        q = _T::sel(mi, vi_type(-2), q);
        vf_type x = _T::sel(mf, -cx, cx);

        mf = cy > x;
        mi = _T::vmf_to_vmi(mf);

        q += _T::sel(mi, vi_type(1), vi_type(0));

        vf_type y = _T::sel(mf, -cx, cy);
        x = _T::sel(mf, cy, x);

        vf_type s = y / x;
        vf_type t = s * s;

        vf_type u = -1.88796008463073496563746e-05;
        u = mad(u, t, 0.000209850076645816976906797);
        u = mad(u, t, -0.00110611831486672482563471);
        u = mad(u, t, 0.00370026744188713119232403);
        u = mad(u, t, -0.00889896195887655491740809);
        u = mad(u, t, 0.016599329773529201970117);
        u = mad(u, t, -0.0254517624932312641616861);
        u = mad(u, t, 0.0337852580001353069993897);
        u = mad(u, t, -0.0407629191276836500001934);
        u = mad(u, t, 0.0466667150077840625632675);
        u = mad(u, t, -0.0523674852303482457616113);
        u = mad(u, t, 0.0587666392926673580854313);
        u = mad(u, t, -0.0666573579361080525984562);
        u = mad(u, t, 0.0769219538311769618355029);
        u = mad(u, t, -0.090908995008245008229153);
        u = mad(u, t, 0.111111105648261418443745);
        u = mad(u, t, -0.14285714266771329383765);
        u = mad(u, t, 0.199999999996591265594148);
        u = mad(u, t, -0.333333333333311110369124);

        t = u * t * s + s;
        t = mad(_T::cvt_i_to_f(q), (M_PI/2), t);
        return t;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
atan2(const vf_type& y,  const vf_type& x)
{
        vf_type r= atan2k(abs(y), x);
        r = mulsign(r, x);

        vmf_type inf_x = isinf(x);
        vmf_type zero_or_inf_x = inf_x | (x == vf_type(0.0));
        vf_type rs = vf_type(M_PI/2);
        vf_type x_m_pi_2 = copysign(M_PI/2, x);
        vf_type rs0= rs - _T::sel(inf_x, x_m_pi_2, vf_type(0.0));
        r = _T::sel(zero_or_inf_x, rs0, r);

        vmf_type inf_y = isinf(y);
        vf_type x_m_pi_4= copysign(M_PI/4, x);
        vf_type rs1= rs - _T::sel(inf_x, x_m_pi_4, vf_type(0.0));
        r= _T::sel(inf_y, rs1, r);

        vf_type rs2 = _T::sel(x < 0.0, vf_type(M_PI), 0);
        r= _T::sel(y== 0.0, rs2, r);
        r= _T::sel(isnan(x) | isnan(y), vf_type(_T::nan), mulsign(r, y));
        return r;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
asin(const vf_type& d)
{
        return mulsign(atan2k(abs(d), sqrt((1.0+d)*(1.0-d))), d);
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
acos(const vf_type& d)
{
        vf_type m_pi= _T::sel(d < 0, vf_type(M_PI), vf_type(0));
        return mulsign(atan2k(sqrt((1+d)*(1-d)), abs(d)), d) + m_pi;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
atan(const vf_type& d)
{
        return d;
}

namespace x86vec {

        v2f64 pow2i(arg<v4s32>::type e);
        v2f64 ldexp(arg<v2f64>::type d, arg<v4s32>::type e);
        v4s32 ilogbp1(arg<v2f64>::type v);
        v4s32 ilogb(arg<v2f64>::type v);
        v2f64 atan2(arg<v2f64>::type y, arg<v2f64>::type x);
        v2f64 asin(arg<v2f64>::type d);
        v2f64 acos(arg<v2f64>::type d);

        v2f64 atan(arg<v2f64>::type d);
        v2f64 sin(arg<v2f64>::type d);
        v2f64 cos(arg<v2f64>::type d);
        v2f64 sincos(arg<v2f64>::type d, v2f64* cos_d);

        v2f64 cbrt(arg<v2f64>::type d);

        namespace impl {

                template <typename _VF, typename _VI>
                struct vec_func_traits;

                template <>
                struct vec_func_traits<v2f64, v4s32> :
                        public math::func_traits<typename v2f64::element_type,
                                                 typename v4s32::element_type> {
                        typedef v2f64 vf_type;
                        typedef v2f64 vmf_type;
                        typedef v4s32 vi_type;
                        typedef v4s32 vmi_type;

                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
                                v4s32 xm= permute<0, 0, 1, 1>(mi);
                                return as<v2f64>(xm);
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                v4s32 xm= as<v4s32>(mf);
                                xm = permute<1, 3, 0, 2>(xm);
                                return xm;
                        }
                        static
                        vi_type sel(const vmi_type& msk,
                                    const vi_type& t, const vi_type& f) {
                                return select(msk, t, f);
                        }
                        static
                        vf_type sel(const vmf_type& msk,
                                    const vf_type& t, const vf_type& f) {
                                return select(msk, t, f);
                        }
                        static
                        vf_type insert_exp(const vi_type& e) {
                                v2u64 m= as<v2u64>(permute<0, 0, 1, 1>(e));
                                m <<= const_shift::_52;
                                return as<v2f64>(m);
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                v4s32 e= as<v4s32>(d);
                                e >>= const_shift::_20;
                                e = permute<1, 3, 0, 0>(e);
                                e &= v4s32(0x7ff, 0x7ff, 0, 0);
                                return e;
                        }
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return cvt_lo<v2f64>(i);
                        }

                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return cvt_lo<v4s32>(f);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return cvt_rz_lo<v4s32>(f);
                        }
                };


                v2f64 pow2i(const v2s64& e);

                v2u64 extract_exp_with_bias(const v2f64& v);
                v2f64 insert_exp(const v2f64& v, v2u64& e);

                v2f64 frexp(arg<v2f64>::type v, v2s64& e);
                v2f64 ldexp(arg<v2f64>::type v, arg<v2s64>::type e);
                v2s64 ilogb(arg<v2f64>::type v);
                v2f64 exp(arg<v2f64>::type v);
                v2f64 log(arg<v2f64>::type v);

                v2s64 ilogbp1(const v2f64& a);

                template <typename _FV>
                struct const_f64 {
                        typedef _FV f64;
                        static const f64 ZERO
                        __attribute__((__visibility__("hidden")));
                        static const f64 ONE
                        __attribute__((__visibility__("hidden")));
                        static const f64 TWO;
                        static const f64 HALF;
                        static const f64 PI4_A;
                        static const f64 PI4_B;
                        static const f64 PI4_C;
                        static const f64 M_4_PI;
                        static const f64 L2U;
                        static const f64 L2L;
                        static const f64 R_LN2;
                };

                template <typename _FV, typename _SV>
                struct frexp_f64 {
                        typedef _FV f64;
                        typedef _SV s64;
                        typedef typename std::make_unsigned<_SV>::type u64;
                        static f64 v(const f64& v, s64* e);
                };

        }
}

x86vec::v2f64 x86vec::pow2i(arg<v4s32>::type e)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::pow2i(e);
}

x86vec::v2f64 x86vec::ldexp(arg<v2f64>::type d, arg<v4s32>::type q)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::ldexp(d, q);
}

x86vec::v4s32 x86vec::ilogbp1(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::ilogbp1(d);
}

x86vec::v4s32 x86vec::ilogb(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::ilogb(d);
}

x86vec::v2f64 x86vec::asin(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                asin(d);
}

x86vec::v2f64 x86vec::acos(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                acos(d);
}


template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::ZERO(0.0);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::ONE(1.0);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::TWO(2.0);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::HALF(0.5);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::PI4_A(
        .7853981554508209228515625);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::PI4_B(
        .794662735614792836713604629039764404296875e-8);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::PI4_C(
        .306161699786838294306516483068750264552437361480769e-16);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::M_4_PI(
        1.273239544735162542821171882678754627704620361328125);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::L2U(
        .69314718055966295651160180568695068359375);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::L2L(
        .28235290563031577122588448175013436025525412068e-12);
template <typename _FV>
const _FV
x86vec::impl::const_f64<_FV>::R_LN2(
        1.442695040888963407359924681001892137426645954152985934135449406931);

// double constants
#define PI4_A .7853981554508209228515625
#define PI4_B .794662735614792836713604629039764404296875e-8
#define PI4_C .306161699786838294306516483068750264552437361480769e-16
#define M_4_PI 1.273239544735162542821171882678754627704620361328125

#define L2U .69314718055966295651160180568695068359375
#define L2L .28235290563031577122588448175013436025525412068e-12
#define R_LN2 1.442695040888963407359924681001892137426645954152985934135449406931

//

#define PI4_Af 0.78515625f
#define PI4_Bf 0.00024127960205078125f
#define PI4_Cf 6.3329935073852539062e-07f
#define PI4_Df 4.9604681473525147339e-10f

#define L2Uf 0.693145751953125f
#define L2Lf 1.428606765330187045e-06f
#define R_LN2f 1.442695040888963407359924681001892137426645954152985934135449406


inline
x86vec::v2s64
x86vec::impl::ilogbp1(const v2f64& d)
{
        v2f64 m(d < 4.9090934652977266E-91);
        v2f64 dd(2.037035976334486E90 * d);
        dd = select(m, dd, d);
        v2u64 q= (as<v2u64>(dd) >> const_shift::_52) & 0x7ff;
        const v2s64 qc0(300+ 0x3fe);
        const v2s64 qc1(     0x3fe);
        v2s64 qc(select(as<v2s64>(m), qc0, qc1));
        v2s64 r= as<v2s64>(q) - qc;
        return r;
}


#if 0
x86vec::v2f64 x86vec::impl::log(arg<v2f64>::type d)
{
        v2s64 e= ilogbp1(d * 0.7071);
        v2s64 e32= permute<0,2,1,3>(as<v4s32>(e));
        v2f64 m = impl::ldexp(d, -e);

        const v2f64 one= const_f64<v2f64>::ONE;

        v2f64 x = (m - one) / (m + one);
        v2f64 x2 = x*x;
        v2f64 t= 0.148197055177935105296783;
        t = mad(t, x2, 0.153108178020442575739679);
        t = mad(t, x2, 0.181837339521549679055568);
        t = mad(t, x2, 0.22222194152736701733275);
        t = mad(t, x2, 0.285714288030134544449368);
        t = mad(t, x2, 0.399999999989941956712869);
        t = mad(t, x2, 0.666666666666685503450651);
        t = mad(t, x2, 2.0);

        x = x* t + 0.693147180559945286226764* cvt_s32_f64_lo(e32);

        // x = vsel(vmask_ispinf(d), vcast_vd_d(INFINITY), x);
        // x = vsel(vmask_gt(vcast_vd_d(0), d), vcast_vd_d(NAN), x);
        // x = vsel(vmask_eq(d, vcast_vd_d(0)), vcast_vd_d(-INFINITY), x);
        return x;
}
#endif


x86vec::v2f64
x86vec::impl::fma(arg<v2f64>::type x, arg<v2f64>::type y, arg<v2f64>::type z)
{
        const v2s64 hi_cor=const4_u32<0x4000000, 0,
                0x4000000, 0>::iv();
        const v2s64 hi_msk=const4_u32<0xf8000000, 0xffffffff,
                0xf8000000, 0xffffffff>::iv();
        v2s64 t;
        t= as<v2s64>(x);
        t += hi_cor;
        t &= hi_msk;
        v2f64 xh(as<v2f64>(t));
        v2f64 xl(x- xh);
        t = as<v2s64>(y);
        t += hi_cor;
        t &= hi_msk;
        v2f64 yh(as<v2f64>(t));
        v2f64 yl(y -yh);

        v2f64 h= x*y;
        v2f64 l= xh * yh - h + xl * yh + xh * yl + xl * yl;

        v2f64 h2 = h + z;
        v2f64 v = h2 - h;
        v2f64 l2 = (h - (h2 - v)) + (z - v) + l;
        return h2 + l2;
}


x86vec::v2f64 test_f(x86vec::v2f64 f)
{
        return isnan(f);
}

x86vec::v2f64 x86vec::frexp(const v2f64& v, v2s64* e)
{
        return impl::frexp(v, *e);
}

inline
x86vec::v2u64 x86vec::impl::extract_exp_with_bias(const v2f64& v)
{
        v2u64 r(as<v2u64>(v));
        r &= v_exp_f64_msk::iv();
        r >>= const_u32<exp_shift_f64>();
        return r;
}

inline
x86vec::v2f64 x86vec::impl::insert_exp(const v2f64& v, v2u64& e)
{
        v2u64 em( e << const_u32<exp_shift_f64>());
        v2u64 e_msk_i= v_exp_f64_msk::iv();
        v2f64 e_msk_f= v_exp_f64_msk::dv();
        em &= e_msk_i;
        v2f64 r(andnot(e_msk_f, v));
        r |= as<v2f64>(em);
        return r;
}

x86vec::v2f64 x86vec::impl::frexp(arg<v2f64>::type v, v2s64& er)
{
        v2f64 vabs(abs(v));
        const v2s64 zero_int(make_zero_int::v());
        const v2f64 zero_f64(as<v2f64>(zero_int));
        v2f64 is_zero(v == zero_f64);
        v2f64 is_nan(v != v);
        const v2s64 exp_msk_int(v_exp_f64_msk::iv());
        const v2f64 exp_msk_f64(as<v2f64>(exp_msk_int));
        v2f64 is_inf(vabs == exp_msk_f64);
        v2f64 is_inf_nan_zero( is_zero | is_nan | is_inf);

        v2s64 is_inf_nan_zero_int(as<v2s64>(is_inf_nan_zero));
        const v2f64& r_inf_nan_zero=v;
        const v2s64& e_inf_nan_zero=zero_int;

        // denormal handling
        const v2f64 _2_54 = double_power_of_two<54>::dv();
        v2f64 r_denom(v* _2_54);
        const v2s64 e_denom_corr= const4_u32<-54-1022, -1, -54-1022, -1>::iv();

        // normal handling
        // v2u64 exp_orig_pos = iv & v_exp_f64_msk::iv();
        const v2s64 e_normal_corr= const4_u32<-1022, -1, -1022, -1>::iv();
        const v2f64& r_normal= v;

        // finite handling
        v2s64 iv(as<v2s64>(v));
        v2s64 is_denom_int((iv & exp_msk_int) == zero_int);
        v2f64 is_denom(as<v2f64>(is_denom_int));
        // combine normal and denormal
        v2s64 e_finite(select(is_denom_int, e_denom_corr, e_normal_corr));
        v2f64 r_finite(select(is_denom, r_denom, r_normal));
        // apply the corrections:
        v2u64 exponent(as<v2u64>(r_finite));
        exponent &= as<v2u64>(exp_msk_int);
        exponent >>= const_u32<exp_shift_f64>();
        e_finite += exponent;
        // mask out exponent
        r_finite &= v_not_exp_f64_msk::dv();
        // insert exponent 2^-1
        r_finite |= const4_u32<0, 0x3fe00000, 0, 0x3fe00000>::dv();

        // combine inf nan zero and finite
        v2s64 e(select(is_inf_nan_zero_int, e_inf_nan_zero, e_finite));
        v2f64 r(select(is_inf_nan_zero, r_inf_nan_zero, r_finite));

        er = e;
        return r;
}

x86vec::v2f64 x86vec::impl::ldexp(arg<v2f64>::type v, arg<v2s64>::type e)
{
        const v2s64 v_exp_bias=const4_u32<bias_f64, 0,
                bias_f64, 0>::iv();
        v2s64 m= e >> const_shift::_63;
        m = (((m+e) >> const_shift::_9) - m ) << const_shift::_7;
        v2s64 q= q - (m << const_shift::_2);
        v2f64 u= as<v2f64>((m + v_exp_bias) << const_shift::_52);
        v2f64 x = v * u * u * u * u;
        u = as<v2f64>((q + v_exp_bias) << const_shift::_52);
        return x * u;
}

x86vec::v2f64 x86vec::ldexp(const v2f64& v, const v2s64& e)
{
        return impl::ldexp(v, e);
}

#if 0
static inline float ldexpkf(float x, int q) {
        float u;
        int m;
        m = q >> 31;
        m = (((m + q) >> 6) - m) << 4;
        q = q - (m << 2);
        u = intBitsToFloat(((int32_t)(m + 0x7f)) << 23);
        x = x * u * u * u * u;
        u = intBitsToFloat(((int32_t)(q + 0x7f)) << 23);
        return x * u;
}

static inline double ldexpk(double x, int q) {
        double u;
        int m;
        m = q >> 31;
        m = (((m + q) >> 9) - m) << 7;
        q = q - (m << 2);
        u = longBitsToDouble(((int64_t)(m + 0x3ff)) << 52);
        x = x * u * u * u * u;
        u = longBitsToDouble(((int64_t)(q + 0x3ff)) << 52);
        return x * u;
}
#endif
