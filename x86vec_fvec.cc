#include "x86vec_fvec.h"
#include "x86vec_cvt.h"
#include <cmath>
#include <limits>

#define PI4_A .7853981554508209228515625
#define PI4_B .794662735614792836713604629039764404296875e-8
#define PI4_C .306161699786838294306516483068750264552437361480769e-16
#define M_4_PI 1.273239544735162542821171882678754627704620361328125

#define L2U .69314718055966295651160180568695068359375
#define L2L .28235290563031577122588448175013436025525412068e-12
#define R_LN2 1.442695040888963407359924681001892137426645954152985934135449406931

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


	template <typename _T>
	class dd {
		_T _x;
		_T _y;
	public:
		dd(const _T& xx, const _T& yy) : _x(x), _y(y) {}
		dd(const _T& xx) : _x(x), _y(_T(0)) {}
		const _T& x() const { return _x; }
		_T& x() { return _x; }
		const _T& y() const { return _y; }
		_T& y() { return _y; }
	};


	template <typename _T>
	dd<_T> normalize(const dd<_T>& n);

	template <typename _T>
	dd<_T> scale_d(const dd<_T>& d, const _T& s);

	template <typename _T>
	dd<_T> add2_ss(const _T& x, const _T& y);
	
	template <typename _T>
	dd<_T> add_ds(const dd<_T>& x, const _T& y);

	template <typename _T>
	dd<_T> add2_ds(const dd<_T>& x, const _T& y);

	template <typename _T>
	dd<_T> add_sd(const _T& x, const dd<_T>& y);

	template <typename _T>
	dd<_T> add_dd(const dd<_T>& x, const dd<_T>& y);
	
	template <typename _T>
	dd<_T> add2_dd(const dd<_T>& x, const dd<_T>& y);

	template <typename _T>
	dd<_T> div_dd(const dd<_T>& x, const dd<_T>& y);

	template <typename _T>
	dd<_T> mul_ss(const _T& x, const _T& y);

	template <typename _T>
	dd<_T> mul_ds(const dd<_T>& x, const _T& y);

	template <typename _T>
	dd<_T> mul_dd(const dd<_T>& x, const dd<_T>& y);

	template <typename _T>
	dd<_T> squ_d(const dd<_T>& x);

	template <typename _T>
	dd<_T> rec_s(const _T& x);

	template <typename _T>
	dd<_T> sqrt_d(const dd<_T>& x);

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

                static constexpr double pinf() {
                        return std::numeric_limits<double>::infinity();
		}
                static constexpr double ninf() {
                        return -std::numeric_limits<double>::infinity();
		}
                static constexpr double nan() {
                        return std::numeric_limits<double>::quiet_NaN();
		}
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

		typedef dd<vf_type> vdf_type;

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
		static vf_type sin(const vf_type& d);
		static vf_type cos(const vf_type& d);
		static std::pair<vf_type, vf_type>
		sincos(const vf_type& d);
		static vf_type tan(const vf_type& d);
		static vf_type log(const vf_type& d);
		static vf_type exp(const vf_type& d);
	private:
		static vdf_type logk(const vf_type& d);
		static vf_type expk(const vdf_type& d);
		static vdf_type expk2(const vdf_type& d);
	public:
		static vf_type pow(const vf_type& x, const vf_type& y);
        };

};

template <typename _T>
inline
math::dd<_T> math::normalize(const dd<_T>& t)
{
	_T x = t.x() + t.y();
	_T y = t.x() - x + t.y();
	return dd<_T>(x, y);
}

template <typename _T>
inline
math::dd<_T> math::scale_d(const dd<_T>& t, const _T& s)
{
	_T x = t.x() * s;
	_T y = t.y() * s;
	return dd<_T>(x, y);
}

template <typename _T>
inline
math::dd<_T> math::add2_ss(const _T& x, const _T& y)
{
	_T rx = x + y;
	_T v =  rx - x;
	_T ry = (x - (rx - v)) + (y - v);
	return dd<_T>(rx, ry);
}

template <typename _T>
inline
math::dd<_T> math::add_ds(const dd<_T>& x, const _T& y)
{
	_T rx = x.x() + y;
	_T ry = x.x() - rx + y + x.y();
	return dd<_T>(rx, ry);
}

template <typename _T>
inline
math::dd<_T> math::add2_ds(const dd<_T>& x, const _T& y)
{
	_T rx  = x.x() + y;
	_T v = rx - x.x();
	_T ry = (x.x - (rx - v)) + (y - v);
	ry += x.y;
	return dd<_T>(rx, ry);
}

template <typename _T>
inline
math::dd<_T> math::add_sd(const _T& x, const dd<_T>& y)
{
	_T rx = x + y.x();
	_T ry = x - rx + y.x() + y.y();
	return dd<_T>(rx, ry);
}

template <typename _T>
inline
math::dd<_T> math::add_dd(const dd<_T>& x, const dd<_T>& y)
{
	_T rx = x.x() + y.x();
	_T ry = x.x() - rx + y.x() + x.y() + y.y();
	return dd<_T>(rx, ry);
}


template <typename _T>
inline
math::dd<_T> math::add2_dd(const dd<_T>& x, const dd<_T>& y)
{
	_T rx  = x.x() + y.x();
	_T v = rx - x.x();
	_T ry = (x.x() - (rx - v)) + (y.x() - v);
	ry += x.y() + y.y();
	return dd<_T>(rx, ry);
}

template <typename _T>
inline 
math::dd<_T> 
math::div_dd(const dd<_T>& n, const dd<_T>& d) 
{
	_T t = 1.0 / d.x();
	_T dh  = upper(d.x()), dl  = d.x() - dh;
	_T th  = upper(t  ), tl  = t   - th;
	_T nhh = upper(n.x()), nhl = n.x() - nhh;


	_T qx = n.x() * t;

	_T u = -qx + nhh * th + nhh * tl + nhl * th + nhl * tl +
		qx * (1 - dh * th - dh * tl - dl * th - dl * tl);
	_T qy = t * (n.y() - qx * d.y()) + u;
	return dd<_T>(qx, qy);
}

template <typename _T>
inline 
math::dd<_T> math::mul_ss(const _T& x, const _T& y) 
{
	_T xh = upper(x), xl = x - xh;
	_T yh = upper(y), yl = y - yh;

	_T rx = x * y;
	_T ry = xh * yh - rx + xl * yh + xh * yl + xl * yl;

	return dd<_T>(rx, ry);
}

template <typename _T>
inline 
math::dd<_T> math::mul_ds(const dd<_T>& x, const _T&  y) 
{
	_T xh = upper(x.x()), xl = x.x() - xh;
	_T yh = upper(y  ), yl = y   - yh;
	
	_T rx = x.x() * y;
	_T ry = xh * yh - rx + xl * yh + xh * yl + xl * yl + 
		x.y() * y;

	return dd<_T>(rx, ry);
}

template <typename _T>
inline 
math::dd<_T> 
math::mul_dd(const dd<_T>& x, const dd<_T>& y) 
{
	_T xh = upper(x.x()), xl = x.x() - xh;
	_T yh = upper(y.x()), yl = y.x() - yh;

	_T rx = x.x() * y.x();
	_T ry = xh * yh - rx + xl * yh + xh * yl + xl * yl + 
		x.x() * y.y() + x.y() * y.x();
	return dd<_T>(rx, ry);
}

template <typename _T>
inline 
math::dd<_T> math::squ_d(const dd<_T>& x) 
{
	_T xh = upper(x.x()), xl = x.x() - xh;

	_T rx = x.x * x.x;
	_T ry = xh * xh - rx + (xh + xh) * xl + xl * xl 
		+ x.x() * (x.y() + x.y());
	return dd<_T>(rx, ry);
}

template <typename _T>
inline 
math::dd<_T> math::rec_s(const _T& d) 
{
	_T t = 1.0 / d;
	_T dh = upper(d), dl = d - dh;
	_T th = upper(t), tl = t - th;
	_T qx = t;
	_T qy = t * (1 - dh * th - dh * tl - dl * th - dl * tl);
	return dd<_T>(qx, qy);
}

template <typename _T>
inline 
math::dd<_T> math::sqrt_d(const dd<_T>& d) 
{
	_T t = sqrt(d.x() + d.y());
	return scale_d(mul_dd(add2_dd(d, mul_ss(t, t)), rec_s(t)), 0.5);
}

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
	vf_type inf(_T::pinf());
        r= _T::sel(mf, vf_type(inf), r);
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
        r= _T::sel(isnan(x) | isnan(y), vf_type(_T::nan()), mulsign(r, y));
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
atan(const vf_type& cs)
{
	vmf_type f_s_lt_0=cs < 0.0;
	vmi_type i_s_lt_0= _T::vmf_to_vmi(f_s_lt_0);

	vf_type s= _T::sel(f_s_lt_0, -cs, cs);
	vi_type q = _T::sel(i_s_lt_0, vi_type(2), vi_type(0));

	vmf_type f_s_gt_1= s > 1.0;
	vmi_type i_s_gt_1= _T::vmf_to_vmi(f_s_gt_1);
	
	s = _T::sel(f_s_gt_1, vf_type(1.0)/s, s);
	vi_type q_or= _T::sel(i_s_gt_1, vi_type(1), vi_type(0));
	q |= q_or;

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

	// t = s + s * (t * u);
	t = mad(t*u, s, s);
	
	vmi_type i_q_and_1= (q & vi_type(1)) == vi_type(1);
	vmf_type f_q_and_1= _T::vmi_to_vmf(i_q_and_1);

	t = _T::sel(f_q_and_1, 
		    1.570796326794896557998982 - t, t);
	
	vmi_type i_q_and_2=(q & vi_type(2)) == vi_type(2);
	vmf_type f_q_and_2=_T::vmi_to_vmf(i_q_and_2);

	t = _T::sel(f_q_and_2, -t, t);
	return t;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
sin(const vf_type& cd)
{
	vf_type qf= rint(cd * M_1_PI);
	vi_type q = _T::cvt_f_to_i(qf);
	vf_type d = mad(qf, -PI4_A*4, cd);
	d = mad(qf, -PI4_B*4, d);
	d = mad(qf, -PI4_C*4, d);

	vf_type s = d * d;
	
	// if ((q & 1) != 0) d = -d;
	vmi_type i_q_and_1 = (q & vi_type(1)) == vi_type(1);
	vmf_type f_q_and_1 = _T::vmi_to_vmf(i_q_and_1);
	d = _T::sel(f_q_and_1, -d, d);

	vf_type u = -7.97255955009037868891952e-18;
	u = mad(u, s, 2.81009972710863200091251e-15);
	u = mad(u, s, -7.64712219118158833288484e-13);
	u = mad(u, s, 1.60590430605664501629054e-10);
	u = mad(u, s, -2.50521083763502045810755e-08);
	u = mad(u, s, 2.75573192239198747630416e-06);
	u = mad(u, s, -0.000198412698412696162806809);
	u = mad(u, s, 0.00833333333333332974823815);
	u = mad(u, s, -0.166666666666666657414808);

	u = mad(s, u * d, d);
	return u;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
cos(const vf_type& cd)
{
	vf_type qf= 1.0+ 2.0 * rint(cd * M_1_PI -0.5);
	vi_type q = _T::cvt_f_to_i(qf);
	
	vf_type d= mad(qf, -PI4_A*2, cd);
	d = mad(qf, -PI4_B*2, d);
	d = mad(qf, -PI4_C*2, d);

	vf_type s = d * d;

	vmi_type i_not_q_and_2 = (q & vi_type(2)) == vi_type(0);
	vmf_type f_not_q_and_2 = _T::vmi_to_vmf(i_not_q_and_2);
	d = _T::sel(f_not_q_and_2, -d, d);
	
	vf_type u = -7.97255955009037868891952e-18;
	u = mad(u, s, 2.81009972710863200091251e-15);
	u = mad(u, s, -7.64712219118158833288484e-13);
	u = mad(u, s, 1.60590430605664501629054e-10);
	u = mad(u, s, -2.50521083763502045810755e-08);
	u = mad(u, s, 2.75573192239198747630416e-06);
	u = mad(u, s, -0.000198412698412696162806809);
	u = mad(u, s, 0.00833333333333332974823815);
	u = mad(u, s, -0.166666666666666657414808);

	u = mad(s, u * d, d);
	return u;
}

template <typename _T>
inline
std::pair<typename math::func<double, math::int32_t, _T>::vf_type,
	  typename math::func<double, math::int32_t, _T>::vf_type>
math::func<double, math::int32_t, _T>::
sincos(const vf_type& cd)
{
	vf_type qf=rint(cd * (2 * M_1_PI));
	vi_type q= _T::cvt_f_to_i(qf);

	vf_type s = cd;

	s = mad(qf, -PI4_A*2, s);
	s = mad(qf, -PI4_B*2, s);
	s = mad(qf, -PI4_C*2, s);

	vf_type t = s;

	s = s * s;

	vf_type u = 1.58938307283228937328511e-10;
	u = mad(u, s, -2.50506943502539773349318e-08);
	u = mad(u, s, 2.75573131776846360512547e-06);
	u = mad(u, s, -0.000198412698278911770864914);
	u = mad(u, s, 0.0083333333333191845961746);
	u = mad(u, s, -0.166666666666666130709393);
	u = u * s * t;

	vf_type rsin = t + u;

	u = -1.13615350239097429531523e-11;
	u = mad(u, s, 2.08757471207040055479366e-09);
	u = mad(u, s, -2.75573144028847567498567e-07);
	u = mad(u, s, 2.48015872890001867311915e-05);
	u = mad(u, s, -0.00138888888888714019282329);
	u = mad(u, s, 0.0416666666666665519592062);
	u = mad(u, s, -0.5);

	vf_type rcos = u * s + 1;

	// swap rsin, rcos
	vmi_type i_q_and_1 =(q & vi_type(1)) == vi_type(1);
	vmf_type f_q_and_1 =_T::vmi_to_vmf(i_q_and_1);
	vf_type saved_sin = rsin;
	
	rsin = _T::sel(f_q_and_1, rcos, rsin);
	rcos = _T::sel(f_q_and_1, saved_sin, rcos);

	vmi_type i_q_and_2 =(q & vi_type(2)) == vi_type(2);
	vmf_type f_q_and_2= _T::vmi_to_vmf(i_q_and_2);
	rsin = _T::sel(f_q_and_2, -rsin, rsin);

	vmi_type i_qp1_and_2= ((q + vi_type(1)) & vi_type(2))
		== vi_type(2);
	vmf_type f_qp1_and_2= _T::vmi_to_vmf(i_qp1_and_2);
	rcos = _T::sel(f_qp1_and_2, -rcos, rcos);

	vmf_type is_inf(isinf(cd));
	const vf_type n(vf_type(_T::nan()));
	rsin = _T::sel(is_inf, n, rsin);
	rcos = _T::sel(is_inf, n, rcos);

	return std::make_pair(rsin, rcos);
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
tan(const vf_type& cd)
{
	vf_type qf=rint(cd * (2 * M_1_PI));
	vi_type q= _T::cvt_f_to_i(qf);

	vf_type x = mad(qf, -PI4_A*2, cd);
	x = mad(qf, -PI4_B*2, x);
	x = mad(qf, -PI4_C*2, x);

	vf_type s = x* x;
	// if ((q & 1) != 0) x = -x;
	vmi_type i_q_and_1 = (q & vi_type(1)) == vi_type(1);
	vmf_type f_q_and_1 = _T::vmi_to_vmf(i_q_and_1);
	x = _T::sel(f_q_and_1, -x, x);

	vf_type u = 1.01419718511083373224408e-05;
	u = mad(u, s, -2.59519791585924697698614e-05);
	u = mad(u, s, 5.23388081915899855325186e-05);
	u = mad(u, s, -3.05033014433946488225616e-05);
	u = mad(u, s, 7.14707504084242744267497e-05);
	u = mad(u, s, 8.09674518280159187045078e-05);
	u = mad(u, s, 0.000244884931879331847054404);
	u = mad(u, s, 0.000588505168743587154904506);
	u = mad(u, s, 0.00145612788922812427978848);
	u = mad(u, s, 0.00359208743836906619142924);
	u = mad(u, s, 0.00886323944362401618113356);
	u = mad(u, s, 0.0218694882853846389592078);
	u = mad(u, s, 0.0539682539781298417636002);
	u = mad(u, s, 0.133333333333125941821962);
	u = mad(u, s, 0.333333333333334980164153);

	u = mad(s, u * x, x);
	
	// if ((q & 1) != 0) u = 1.0 / u;
	u = _T::sel(f_q_and_1, 1.0/u, u);

	// if (xisinf(d)) u = NAN;
	vmf_type is_inf(isinf(cd));
	const vf_type n(vf_type(_T::nan()));
	u = _T::sel(is_inf, n, u);
	return u;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
log(const vf_type& d)
{
	vi_type e = ilogbp1(d * 0.7071);
	vf_type ef= _T::cvt_i_to_f(e);
	vf_type m = ldexp(d, -e);

	vf_type x = (m-vf_type(1)) / (m+vf_type(1));
	vf_type x2 = x * x;

	vf_type t = 0.148197055177935105296783;
	t = mad(t, x2, 0.153108178020442575739679);
	t = mad(t, x2, 0.181837339521549679055568);
	t = mad(t, x2, 0.22222194152736701733275);
	t = mad(t, x2, 0.285714288030134544449368);
	t = mad(t, x2, 0.399999999989941956712869);
	t = mad(t, x2, 0.666666666666685503450651);
	t = mad(t, x2, 2.0);

	x = mad(x, t, 0.693147180559945286226764 * ef);
	
	// if (xisinf(d)) x = INFINITY;
	const vf_type pinf(_T::pinf());
	const vf_type ninf(_T::ninf());
	x = _T::sel(isinf(d), pinf, x);
	// if (d < 0) x = NAN;
	x = _T::sel(d < vf_type(0.0), vf_type(_T::nan()), x);
	// if (d == 0) x = -INFINITY;
	x = _T::sel(d == vf_type(0.0), ninf, x);
	return x;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
exp(const vf_type& d)
{
	vf_type qf = rint(d * R_LN2);
	vi_type q = _T::cvt_f_to_i(qf);

	vf_type s = mad(qf, -L2U, d);
	s = mad(qf, -L2L, s);
	vf_type u = 2.08860621107283687536341e-09;
	u = mad(u, s, 2.51112930892876518610661e-08);
	u = mad(u, s, 2.75573911234900471893338e-07);
	u = mad(u, s, 2.75572362911928827629423e-06);
	u = mad(u, s, 2.4801587159235472998791e-05);
	u = mad(u, s, 0.000198412698960509205564975);
	u = mad(u, s, 0.00138888888889774492207962);
	u = mad(u, s, 0.00833333333331652721664984);
	u = mad(u, s, 0.0416666666666665047591422);
	u = mad(u, s, 0.166666666666666851703837);
	u = mad(u, s, 0.5);
	// u = s * s * u +s + vf_type(1));
	// u = s^2 * u + s + 1 = s*(s*u+1.0) + 1.0
	u = mad(u, s, 1.0);
	u = mad(u, s, 1.0);

	u = ldexp(u, q);

	// if (xisminf(d)) u = 0;
	u = _T::sel( d== vf_type(_T::ninf()), vf_type(0), u);
	return u;
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vdf_type
math::func<double, math::int32_t, _T>::
logk(const vf_type& d)
{
	// double2 x, x2;
	// double m, t;
	// int e;

	vi_type e = ilogbp1(d * 0.7071);
	vf_type m = ldexp(d, -e);

	vdf_type x = div_dd(add2_ss(vf_type(-1.0), m), 
			    add2_ss(vf_type(1.0), m));
	vdf_type x2 = squ_d(x);

	vf_type t = 0.134601987501262130076155;
	t = mad(t, x2.x(), 0.132248509032032670243288);
	t = mad(t, x2.x(), 0.153883458318096079652524);
	t = mad(t, x2.x(), 0.181817427573705403298686);
	t = mad(t, x2.x(), 0.222222231326187414840781);
	t = mad(t, x2.x(), 0.285714285651261412873718);
	t = mad(t, x2.x(), 0.400000000000222439910458);
	t = mad(t, x2.x(), 0.666666666666666371239645);

	vdf_type c1(0.693147180559945286226764, 
		    2.319046813846299558417771e-17);
	vf_type ef= _T::cvt_i_to_f(e);
	return add2_dd(mul_ds(c1, ef),
		       add2_dd(scale_d(x, vf_type(2.0)), 
			       mul_ds(mul_dd(x2, x), t)));
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
expk(const vdf_type& d)
{
	vf_type qf= rint((d.x() + d.y()) * R_LN2);
	vi_type q= _T::cvt_f_to_i(qf);
	// int q = (int)rint((d.x + d.y) * R_LN2);
	// double2 s, t;
	// double u;

	vdf_type s = add2_ds(d, qf * -L2U);
	s = add2_ds(s, qf * -L2L);

	s = normalize(s);

	vf_type u = 2.51069683420950419527139e-08;
	u = mad(u, s.x(), 2.76286166770270649116855e-07);
	u = mad(u, s.x(), 2.75572496725023574143864e-06);
	u = mad(u, s.x(), 2.48014973989819794114153e-05);
	u = mad(u, s.x(), 0.000198412698809069797676111);
	u = mad(u, s.x(), 0.0013888888939977128960529);
	u = mad(u, s.x(), 0.00833333333332371417601081);
	u = mad(u, s.x(), 0.0416666666665409524128449);
	u = mad(u, s.x(), 0.166666666666666740681535);
	u = mad(u, s.x(), 0.500000000000000999200722);

	vdf_type t = add_dd(s, mul_ds(squ_d(s), u));
	t = add_sd(vf_type(1.0), t);
	return ldexp(t.x() + t.y(), q);
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vdf_type
math::func<double, math::int32_t, _T>::
expk2(const vdf_type& d)
{
	vf_type qf=rint((d.x() + d.y()) * R_LN2);
	vi_type q= _T::cvt_f_to_i(qf);
	// int q = (int)rint((d.x + d.y) * R_LN2);
	// double2 s, t;
	// double u;

	vdf_type s = add2_ds(d, qf * -L2U);
	s = add2_ds(s, qf * -L2L);

	s = normalize_d(s);

	vf_type u = 2.51069683420950419527139e-08;
	u = mad(u, s.x(), 2.76286166770270649116855e-07);
	u = mad(u, s.x(), 2.75572496725023574143864e-06);
	u = mad(u, s.x(), 2.48014973989819794114153e-05);
	u = mad(u, s.x(), 0.000198412698809069797676111);
	u = mad(u, s.x(), 0.0013888888939977128960529);
	u = mad(u, s.x(), 0.00833333333332371417601081);
	u = mad(u, s.x(), 0.0416666666665409524128449);
	u = mad(u, s.x(), 0.166666666666666740681535);
	u = mad(u, s.x(), 0.500000000000000999200722);

	vdf_type t = add_dd(s, mul_ds(squ_d(s), u));
	t = add_sd(1, t);
	return vdf_type(ldexp(t.x(), q), ldexp(t.y(), q));
}

template <typename _T>
inline
typename math::func<double, math::int32_t, _T>::vf_type
math::func<double, math::int32_t, _T>::
pow(const vf_type& x, const vf_type& y) 
{
	vi_type iy= _T::cvt_rz_f_to_i(y);
	vf_type fiy= _T::cvt_i_to_f(iy);
	vmf_type yisint= fiy == y;
	vmi_type i_yisodd= (iy & vi_type(1)) !=0;
	vmf_type tmsk = _T::vmi_to_vmf(i_yisodd);
	vmf_type yisodd= tmsk && yisint;

	vf_type abs_x=abs(x);
	
	vf_type result = expk(mul_ds(logk(abs_x), y));

	const vf_type nan= _T::nan();
	const vf_type inf= _T::pinf();
	
	result = _T::sel(isnan(result), inf, result);

	vf_type t0 = _T::sel(yisodd, vf_type(-1), vf_type(1));
	vf_type t1 = _T::sel(!yisint, nan, t0);
	vf_type t2 = _T::sel(x >= vf_type(0), vf_type(1), t1);
	result *= t2;

	vf_type efx = mulsign(abs_x -1.0, y);
	t0 = _T::sel(efx == vf_type(0), 1.0, inf);
	t1 = _T::sel(efx < vf_type(0), vf_type(0), t0);
	result = _T::sel(isinf(y), t1, result);

	vmf_type x_eq_zero(x == vf_type(0.0));

	t0 = copysign(vf_type(1.0), x);
	t1 = _T::sel(x_eq_zero, -y , y);
	t0 = _T::sel(yisodd, t0, vf_type(0.0));
	t1 = _T::sel(t1 < vf_type(0.0), vf_type(0.0), inf);
	t0 *= t1;

	result = _T::sel(isinf(x) | x_eq_zero, t0, result);
	result = _T::sel(isnan(x) | isnan(y), nan, result);
	result = _T::sel(x_eq_zero | (x== vf_type(1.0)), 
			 vf_type(1.0), result);
	return result;
#if 0
	int yisint = (int)y == y;
	int yisodd = (1 & (int)y) != 0 && yisint;

	double result = expk(mul_ds(logk(xfabs(x)), y));

	result = xisnan(result) ? INFINITY : result;
	result *=  (x >= 0 ? 1 : (!yisint ? NAN : (yisodd ? -1 : 1)));

	double efx = mulsign(xfabs(x) - 1, y);
	if (xisinf(y)) result = efx < 0 ? 0.0 : (efx == 0 ? 1.0 : INFINITY);
	if (xisinf(x) || x == 0) result = (yisodd ? sign(x) : 1) * ((x == 0 ? -y : y) < 0 ? 0 : INFINITY);
	if (xisnan(x) || xisnan(y)) result = NAN;
	if (y == 0 || x == 1) result = 1;

	return result;
#endif
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
	std::pair<v2f64, v2f64>
        sincos(arg<v2f64>::type d);
        v2f64 tan(arg<v2f64>::type d);
	v2f64 log(arg<v2f64>::type d);
	v2f64 exp(arg<v2f64>::type d);
	v2f64 pow(arg<v2f64>::type y, arg<v2f64>::type x);
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

x86vec::v2f64 x86vec::atan2(arg<v2f64>::type x, arg<v2f64>::type y)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                atan2(x, y);
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

x86vec::v2f64 x86vec::atan(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                atan(d);
}

x86vec::v2f64 x86vec::sin(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                sin(d);
}

x86vec::v2f64 x86vec::cos(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                cos(d);
}

std::pair<x86vec::v2f64, x86vec::v2f64>
x86vec::sincos(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                sincos(d);
}

x86vec::v2f64 x86vec::tan(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                tan(d);
}

x86vec::v2f64 x86vec::log(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                log(d);
}

x86vec::v2f64 x86vec::exp(arg<v2f64>::type d)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                exp(d);
}

x86vec::v2f64 x86vec::pow(arg<v2f64>::type x, arg<v2f64>::type y)
{
        return math::func<double, int32_t,
		impl::vec_func_traits<v2f64, v4s32> >::
                pow(x, y);
}


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

x86vec::v2f64 x86vec::frexp(arg<v2f64>::type v, v2s64* ex)
{
        v2f64 vabs(abs(v));
        const v2s64 zero_int(impl::make_zero_int::v());
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
        const v2f64 _2_54 = impl::double_power_of_two<54>::dv();
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

	if (ex)
		*ex = e;
        return r;
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
