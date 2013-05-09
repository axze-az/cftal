#if !defined (__CFTAL_MATH_FUNC_H__)
#define __CFTAL_MATH_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {

        namespace math {

                namespace impl {

			// returns (y0+y1) = x - N * pi/2
			// the integer results contains 
			// only the lower bits of N
			int32_t
			__ieee754_rem_pio2(double x, double *y);
			int 
			__kernel_rem_pio2(double *x, double *y, int e0, 
					  int nx, int prec, 
					  const int32_t *ipio2);
				
                        template <class _T, typename _E>
                        struct d_real_constants {};

                        template <class _T>
                        struct d_real_constants<_T, double> {
                                // 1/(i!)
                                static const unsigned MAX_FAC=30;
                                static const _T inv_fac[MAX_FAC+1];
                                // 2/i i=0,1,2,3,4...
                                static const unsigned MAX_2_OVER_I=30;
                                static const _T _2_over_i[MAX_FAC+1];
                                // M_LN2 LOG_E(2)
                                static const _T m_ln2;
                                static const _T m_ln2_low;
                                // M_1_LN2 1/LOG_E(2)
                                static const _T m_1_ln2;
				// 2*PI
				static const _T m_pi2;
				// 1/2*PI
				static const _T m_1_pi2;
                                // PI
                                static const _T m_pi;
                                // 1/PI
                                static const _T m_1_pi;
                                // PI/4
                                static const _T m_pi_4;
                                // 4/PI
                                static const _T m_4_pi;
                        };

                }

                template <typename _FLOAT_T, typename _INT_T>
                struct func_traits;

                template <typename _FLOAT_T, typename _INT_T,
                          typename _TRAITS_T= func_traits<_FLOAT_T, _INT_T> >
                struct func;

                template <>
                struct func_traits<double, int32_t> : public d_real_traits<double> {
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
			static constexpr int32_t vec_len=1;

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
                        typedef typename _T::vf_type vf_type;
                        typedef typename _T::vi_type vi_type;
                        typedef typename _T::vmf_type vmf_type;
                        typedef typename _T::vmi_type vmi_type;

                        typedef d_real<vf_type> dvf_type;

                        static dvf_type exp_k2(const dvf_type& dvf);
                        static dvf_type log_k2(const dvf_type& dvf);

			// return dfv mod pi, and the half in second
			static std::pair<dvf_type, vi_type>
			reduce_trig_arg_k2(const dvf_type& dvf);

			static dvf_type sin_k2(const dvf_type& dvf);
			static dvf_type cos_k2(const dvf_type& dvf);

                public:
                        static vf_type pow2i(const vi_type& vi);
                        static vf_type ldexp(const vf_type& vf, const vi_type& vi);

                        static vi_type ilogbp1(const vf_type& vi);
                        static vi_type ilogb(const vf_type& vf);

                        static vf_type exp(const vf_type& vf);
                        static vf_type log(const vf_type& vf);

			static vf_type sin(const vf_type& vf);

                };

        }
}

template <typename _T>
inline
typename
cftal::math::func<double, cftal::int32_t, _T>::vf_type
cftal::math::func<double, cftal::int32_t, _T>::pow2i(const vi_type& vi)
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
typename cftal::math::func<double, cftal::int32_t, _T>::vf_type
cftal::math::func<double, cftal::int32_t, _T>::ldexp(const vf_type& vd,
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
typename cftal::math::func<double, cftal::int32_t, _T>::vi_type
cftal::math::func<double, cftal::int32_t, _T>::ilogbp1(const vf_type& vd)
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
typename cftal::math::func<double, cftal::int32_t, _T>::vi_type
cftal::math::func<double, cftal::int32_t, _T>::ilogb(const vf_type& d)
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
typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type
cftal::math::func<double, cftal::int32_t, _T>::log_k2(const dvf_type& d)
{
        using ctbl=impl::d_real_constants<dvf_type, double>;

        dvf_type sc(d* vf_type(M_SQRT1_2));

        vi_type e = ilogbp1(sc.h() + sc.l());
        vf_type ef= _T::cvt_i_to_f(e);
        dvf_type m(ldexp(d.h(), -e), ldexp(d.l(), -e));

        dvf_type xm= m - vf_type(1.0);
        dvf_type xp= m + vf_type(1.0);
        dvf_type xr= xm / xp;
        dvf_type x2 = sqr(xr);

        dvf_type t= ctbl::_2_over_i[23];
        // t = t * x2 + ctbl::_2_over_i[21];
        // t = t * x2 + ctbl::_2_over_i[19];
        // t = t * x2 + ctbl::_2_over_i[17];
        // t = t * x2 + ctbl::_2_over_i[15];
        // t = t * x2 + ctbl::_2_over_i[13];
        // t = t * x2 + ctbl::_2_over_i[11];
        // t = t * x2 + ctbl::_2_over_i[9];
        // t = t * x2 + ctbl::_2_over_i[7];
        // t = t * x2 + ctbl::_2_over_i[5];
        // t = t * x2 + ctbl::_2_over_i[3];
        for (int i=21; i>2; i-=2)
                t = t * x2 + ctbl::_2_over_i[i];
        t = t * x2 + vf_type(2.0);
        t = t * xr;

        xr = t + ctbl::m_ln2 * ef;
        return xr;
}

template <typename _T>
inline
typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type
cftal::math::func<double, cftal::int32_t, _T>::exp_k2(const dvf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;

        const double k(512.0);
        const double k_i(9);
        const vf_type inv_k(1.0/k);

        dvf_type m2= rint(d * ctbl::m_1_ln2);
        dvf_type r= mul_pwr2(
		(d - ctbl::m_ln2*m2), inv_k);
        vf_type m=m2.h() + m2.l();

        dvf_type s = ctbl::inv_fac[9];
        // s = s * r + ctbl::inv_fac[8];
        // s = s * r + ctbl::inv_fac[7];
        // s = s * r + ctbl::inv_fac[6];
        // s = s * r + ctbl::inv_fac[5];
        // s = s * r + ctbl::inv_fac[4];
        // s = s * r + ctbl::inv_fac[3];
        for (unsigned int i=8; i!=2; --i)
                s = s*r + ctbl::inv_fac[i];
        s = s * r + vf_type(0.5);
        s = s * r + vf_type(1.0);
        s = s * r;

        // scale back the 1/k reduced value
        const vf_type two(2.0);
        for (int i=0; i<k_i; ++i)
                s = mul_pwr2(s, two) + sqr(s);
        s += vf_type(1.0);

        // scale back
        vi_type mi= _T::cvt_f_to_i(m);
        dvf_type res(ldexp(s.h(), mi), ldexp(s.l(), mi));
        return res;
}

template <typename _T>
inline
std::pair<typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type,
	  typename cftal::math::func<double, cftal::int32_t, _T>::vi_type>
cftal::math::
func<double, cftal::int32_t, _T>::reduce_trig_arg_k2(const dvf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;

	dvf_type n2pif(rint(d * ctbl::m_1_pi2));
	dvf_type d0((d - n2pif * ctbl::m_pi2.h()) -
		    n2pif * ctbl::m_pi2.l());
	// reduce by pi
	dvf_type qf(rint(d0 * ctbl::m_1_pi));
	vi_type q(_T::cvt_f_to_i(qf.h()+qf.l()));
	dvf_type d1(d0 - qf * ctbl::m_pi);
	return std::make_pair(d1, q);
}

template <typename _T>
inline
typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type
cftal::math::func<double, cftal::int32_t, _T>::sin_k2(const dvf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;
	// reduce argument
	std::pair<dvf_type, vi_type> rr(reduce_trig_arg_k2(d));
	const dvf_type& d1= rr.first;
	const vi_type q= rr.second;
#if 0
	std::cout << "d =  " << x86vec::extract<0>(d.h()) 
		  << ", " << x86vec::extract<0>(d.l()) 
		  << std::endl;
	std::cout << "n2= " << x86vec::extract<0>(n2pif.h()) 
		  << ", " << x86vec::extract<0>(n2pif.l()) 
		  << std::endl;
	std::cout << "d0=  " << x86vec::extract<0>(d0.h()) 
		  << ", " << x86vec::extract<0>(d0.l()) << std::endl;
	std::cout << "qf= " << x86vec::extract<0>(qf.h()) 
		  << ", " << x86vec::extract<0>(qf.l()) 
		  << std::endl;
	std::cout << "d1=  " << x86vec::extract<0>(d1.h()) 
		  << ", " << x86vec::extract<0>(d1.l()) << std::endl;
#endif
	vmi_type q_and_1((q & vi_type(1))== vi_type(1));
	vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));
	dvf_type d2(_T::sel(q_and_1_f, -d1.h(), d1.h()),
		    _T::sel(q_and_1_f, -d1.l(), d1.l()));
		
	dvf_type x= sqr(d1);
	dvf_type s;

	s = ctbl::inv_fac[21];
	s = s * x - ctbl::inv_fac[19];
	s = s * x + ctbl::inv_fac[17];
	s = s * x - ctbl::inv_fac[15];
	s = s * x + ctbl::inv_fac[13];
	s = s * x - ctbl::inv_fac[11];
	s = s * x + ctbl::inv_fac[9];
	s = s * x - ctbl::inv_fac[7];
	s = s * x + ctbl::inv_fac[5];
	s = s * x - ctbl::inv_fac[3];
	s = s * x + vf_type(1);
	s = s * d2;

	return s;
}

template <typename _T>
inline
typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type
cftal::math::func<double, cftal::int32_t, _T>::cos_k2(const dvf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;
	// reduce argument
	std::pair<dvf_type, vi_type> rr(reduce_trig_arg_k2(d));
	const dvf_type& d1= rr.first;
	const vi_type q= rr.second;
#if 0
	std::cout << "d =  " << x86vec::extract<0>(d.h()) 
		  << ", " << x86vec::extract<0>(d.l()) 
		  << std::endl;
	std::cout << "n2= " << x86vec::extract<0>(n2pif.h()) 
		  << ", " << x86vec::extract<0>(n2pif.l()) 
		  << std::endl;
	std::cout << "d0=  " << x86vec::extract<0>(d0.h()) 
		  << ", " << x86vec::extract<0>(d0.l()) << std::endl;
	std::cout << "qf= " << x86vec::extract<0>(qf.h()) 
		  << ", " << x86vec::extract<0>(qf.l()) 
		  << std::endl;
	std::cout << "d1=  " << x86vec::extract<0>(d1.h()) 
		  << ", " << x86vec::extract<0>(d1.l()) << std::endl;
#endif
	vmi_type q_and_1((q & vi_type(1))== vi_type(1));
	vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));
	dvf_type d2(_T::sel(q_and_1_f, -d1.h(), d1.h()),
		    _T::sel(q_and_1_f, -d1.l(), d1.l()));
		
	dvf_type x= sqr(d1);
	dvf_type s;

	s = ctbl::inv_fac[21];
	s = s * x - ctbl::inv_fac[19];
	s = s * x + ctbl::inv_fac[17];
	s = s * x - ctbl::inv_fac[15];
	s = s * x + ctbl::inv_fac[13];
	s = s * x - ctbl::inv_fac[11];
	s = s * x + ctbl::inv_fac[9];
	s = s * x - ctbl::inv_fac[7];
	s = s * x + ctbl::inv_fac[5];
	s = s * x - ctbl::inv_fac[3];
	s = s * x + vf_type(1);
	s = s * d2;

	return s;
}

template <typename _T>
inline
typename cftal::math::func<double, cftal::int32_t, _T>::vf_type
cftal::math::func<double, cftal::int32_t, _T>::log(const vf_type& d)
{
        dvf_type xr(log_k2(d));
        // if (xisinf(d)) x = INFINITY;
        vf_type x= xr.h() + xr.l();
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
typename cftal::math::func<double, cftal::int32_t, _T>::vf_type
cftal::math::func<double, cftal::int32_t, _T>::exp(const vf_type& d)
{
        dvf_type xr(exp_k2(d));
        vf_type res(xr.h() + xr.l());
        res = _T::sel(d == 0.0, 1.0, res);
        res = _T::sel(d == 1.0, M_E, res);
        res = _T::sel(d== vf_type(_T::ninf()), 0.0, res);
        res = _T::sel(d== vf_type(_T::pinf()), _T::pinf(), res);
        return res;
}

template <typename _T>
inline
typename cftal::math::func<double, cftal::int32_t, _T>::vf_type
cftal::math::func<double, cftal::int32_t, _T>::sin(const vf_type& d)
{
        dvf_type xr(sin_k2(d));
        vf_type res(xr.h() + xr.l());
	return res;
}

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
        6.931471805599452862e-01, 2.319046813846299558e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2_low(
        5.707708438416212066e-34, -3.582432210601811423e-50);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_ln2(
        _T(1.0) / _T( 6.931471805599452862e-01, 2.319046813846299558e-17));


template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi2(
	6.283185307179586232e+00, 2.449293598294706414e-16);


template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi2(
        _T(1.0) / _T(6.283185307179586232e+00, 2.449293598294706414e-16));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi(
        3.141592653589793116e+00, 1.224646799147353207e-16);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_1_pi(
        _T(1.0) / _T(3.141592653589793116e+00, 1.224646799147353207e-16));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_pi_4(
        7.853981633974482790e-01, 3.061616997868383018e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_4_pi(
        _T(1.0) / _T(7.853981633974482790e-01, 3.061616997868383018e-17));

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
inv_fac[MAX_FAC+1]= {
        _T( 1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T( 1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T( 5.0000000000000000000000e-01,  0.0000000000000000000000e+00),
        _T( 1.6666666666666665741481e-01,  9.2518585385429706566156e-18),
        _T( 4.1666666666666664353702e-02,  2.3129646346357426641539e-18),
        _T( 8.3333333333333332176851e-03,  1.1564823173178713802252e-19),
        _T( 1.3888888888888889418943e-03, -5.3005439543735770590566e-20),
        _T( 1.9841269841269841252632e-04,  1.7209558293420705286779e-22),
        _T( 2.4801587301587301565790e-05,  2.1511947866775881608473e-23),
        _T( 2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
        _T( 2.7557319223985888275786e-07,  2.3767714622250297318518e-23),
        _T( 2.5052108385441720223866e-08, -1.4488140709359119660293e-24),
        _T( 2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
        _T( 1.6059043836821613340863e-10,  1.2585294588752098052117e-26),
        _T( 1.1470745597729724507297e-11,  2.0655512752830745424540e-28),
        _T( 7.6471637318198164055138e-13,  7.0387287773345300106125e-30),
        _T( 4.7794773323873852534462e-14,  4.3992054858340812566328e-31),
        _T( 2.8114572543455205981105e-15,  1.6508842730861432599403e-31),
        _T( 1.5619206968586225271148e-16,  1.1910679660273754002389e-32),
        _T( 8.2206352466243294955370e-18,  2.2141894119604265363725e-34),
        _T( 4.1103176233121648440650e-19,  1.4412973378659527149817e-36),
        _T( 1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
        _T( 8.8967913924505740778892e-22, -7.9114026148723762170263e-38),
        _T( 3.8681701706306841261487e-23, -8.8431776554823422165616e-40),
        _T( 1.6117375710961183858953e-24, -3.6846573564509766032865e-41),
        _T( 6.4469502843844735894989e-26, -1.9330404233703468010728e-42),
        _T( 2.4795962632247975896123e-27, -1.2953730964765228775764e-43),
        _T( 9.1836898637955460053942e-29,  1.4303150396787318912725e-45),
        _T( 3.2798892370698377589766e-30,  1.5117542744029878689714e-46),
        _T( 1.1309962886447715881757e-31,  1.0498015412959506023854e-47),
        _T( 3.7699876288159053851494e-33,  2.5870347832750323834849e-49)
};

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::
_2_over_i[MAX_2_OVER_I+1]= {
        _T( 2.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T( 2.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T( 1.0000000000000000000000e+00,  0.0000000000000000000000e+00),
        _T( 6.6666666666666662965923e-01,  3.7007434154171882626462e-17),
        _T( 5.0000000000000000000000e-01,  0.0000000000000000000000e+00),
        _T( 4.0000000000000002220446e-01, -2.2204460492503132041068e-17),
        _T( 3.3333333333333331482962e-01,  1.8503717077085941313231e-17),
        _T( 2.8571428571428569842539e-01,  1.5860328923216521125627e-17),
        _T( 2.5000000000000000000000e-01,  0.0000000000000000000000e+00),
        _T( 2.2222222222222220988641e-01,  1.2335811384723960875487e-17),
        _T( 2.0000000000000001110223e-01, -1.1102230246251566020534e-17),
        _T( 1.8181818181818182322829e-01, -5.0464682937507116874478e-18),
        _T( 1.6666666666666665741481e-01,  9.2518585385429706566156e-18),
        _T( 1.5384615384615385469402e-01, -8.5401771125012046311799e-18),
        _T( 1.4285714285714284921269e-01,  7.9301644616082605628134e-18),
        _T( 1.3333333333333333148296e-01,  1.8503717077085942083603e-18),
        _T( 1.2500000000000000000000e-01,  0.0000000000000000000000e+00),
        _T( 1.1764705882352941013202e-01,  1.6326809185664066544356e-18),
        _T( 1.1111111111111110494321e-01,  6.1679056923619804377437e-18),
        _T( 1.0526315789473683626198e-01,  5.8432790769745077831256e-18),
        _T( 1.0000000000000000555112e-01, -5.5511151231257830102669e-18),
        _T( 9.5238095238095232808462e-02,  5.2867763077388403752089e-18),
        _T( 9.0909090909090911614143e-02, -2.5232341468753558437239e-18),
        _T( 8.6956521739130432369080e-02,  2.4135283144025141513234e-18),
        _T( 8.3333333333333328707404e-02,  4.6259292692714853283078e-18),
        _T( 8.0000000000000001665335e-02, -1.6653345369377347490057e-18),
        _T( 7.6923076923076927347012e-02, -4.2700885562506023155900e-18),
        _T( 7.4074074074074069962137e-02,  4.1119371282413202918292e-18),
        _T( 7.1428571428571424606346e-02,  3.9650822308041302814067e-18),
        _T( 6.8965517241379309387739e-02,  9.5708881433203148708292e-19),
};

// Local Variables:
// mode: c++
// end:
#endif
