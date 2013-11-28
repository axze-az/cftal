#if !defined (__MATH_FUNC_F64_H__)
#define __MATH_FUNC_F64_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/math_common.h>
#include <cftal/mem_load.h>

namespace cftal {

        namespace math {

                namespace impl {

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

                template <>
                struct func_traits<double, int32_t>
                        : public d_real_traits<double> {
                        typedef double vf_type;
                        typedef int32_t vi_type;
                        typedef bool vmf_type;
                        typedef bool vmi_type;
                        typedef uint32_t mask_type;
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
			vf_type gather(const double* p, vi_type idx, int sc) {
				const char* pc= 
					reinterpret_cast<const char*>(p);
				const char* d = pc + idx * sc;
				vf_type r(*reinterpret_cast<const double*>(d));
				return r;
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
			vi_type extract_high_word(const vf_type& d) {
				ud_t t;
				t._d = d;
				return vi_type(t._u >>32);
			}

			static
			vi_type extract_low_word(const vf_type& d) {
				ud_t t;
				t._d = d;
				return vi_type(t._u);
			}

			static
			vf_type insert_high_word(const vf_type& d, 
						 const vi_type& w) {
				ud_t t;
				t._d = d;
				uint64_t hh= w;
				t._u = (t._u & 0xFFFFFFFF) | (hh << 32);
				return t._d;
			}

			static
			vf_type insert_low_word(const vf_type& d,
						const vi_type& w) {
				ud_t t;
				t._d = d;
				t._u = (t._u & 0xFFFFFFFF00000000ULL) | w;
				return t._d;
			}

			static 
			vf_type combine_words(const vi_type& l,
					      const vi_type& h) {
				vf_type t(insert_low_word(0.0, l));
				return insert_high_word(t, h);
			}

                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return vf_type(i);
                        }
                        // including rounding to nearest.
                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return f < 0 ?
                                        (vi_type)(f - 0.5) :
                                        (vi_type)(f + 0.5);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return (vi_type)f;
                        }
                };

                template <typename _T>
                struct func_core<double, _T> {
                        typedef typename _T::vf_type vf_type;
                        typedef typename _T::vi_type vi_type;
                        typedef typename _T::vmf_type vmf_type;
                        typedef typename _T::vmi_type vmi_type;

                        typedef d_real<vf_type> dvf_type;
			typedef func_core<double, _T> my_type;

			static const dvf_type m_exp_c_k2[];
			static const dvf_type m_log_c_k2[];
			static const dvf_type m_sin_c_k2[];
			static const dvf_type m_cos_c_k2[];

                        static dvf_type 
			exp_k2(const dvf_type& dvf);

                        static vf_type 
			native_exp_k(const vf_type& v);

                        static dvf_type 
			log_k2(const dvf_type& dvf);

			static vf_type
			native_log_k(const vf_type& v);

			// argument reduction for all trigonometric
			// functions, reduction by %pi/2, the low bits
			// of multiple of %pi/2 is returned in the
			// second part of the return type
                        static std::pair<dvf_type, vi_type>
                        reduce_trig_arg_k(const vf_type& v);
			// core sine, cosine calculation
			static std::pair<dvf_type, dvf_type>
			sin_cos_k(const vf_type& v);

			// argument reduction for all trigonometric
			// functions, reduction by %pi/2, the low bits
			// of multiple of %pi/2 is returned in the
			// second part of the return type
			static std::pair<vf_type, vi_type>
			native_reduce_trig_arg_k(const vf_type& v);
			// core sine, cosine calculation
			static std::pair<vf_type, vf_type>
			native_sin_cos_k(const vf_type& v);

			// cofficients for atan2
			static const dvf_type m_atan2_c_k2[];

			// atan2 kernel
			static dvf_type
			atan2_k2(const dvf_type& x, const dvf_type& y);

			// native atan2 kernel
			static vf_type
			native_atan2_k(const vf_type& x, const vf_type& y);

                        static vf_type pow2i(const vi_type& vi);
                        static vf_type ldexp(const vf_type& vf,
                                             const vi_type& vi);
			static vf_type frexp(const vf_type& vf,
					     vi_type* vi);

                        static vi_type ilogbp1(const vf_type& vi);
                        static vi_type ilogb(const vf_type& vf);
		};

        } // end math
} // end cftal

template <typename _T>
inline
typename
cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
pow2i(const vi_type& vi)
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
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
ldexp(const vf_type& vd,
      const vi_type& ve)
{
        vi_type q(ve);
        vi_type m(q >> 31);
        m = (((m + q) >> 9) - m) << 7;
        q = q - (m << 2);

        m += 0x3ff;
        m = max(vi_type(0), m);
        m = min(vi_type(0x7ff), m);

        vf_type fm(_T::insert_exp(m));
	fm = fm* fm;
	fm = fm* fm;
        vf_type r(vd * fm /* * fm * fm * fm*/ );
        q += 0x3ff;
        // q = max(vi_type(0), q);
        // q = min(vi_type(0x7ff), q);
        vf_type fq(_T::insert_exp(q));
        return r * fq;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
frexp(const vf_type& vd,
      vi_type* ve)
{
	// normal numbers:
	vi_type hi_word(_T::extract_high_word(vd));
	vi_type lo_word(_T::extract_low_word(vd));

	vi_type value_head(hi_word & vi_type(0x7fffffff));

	vi_type is_inf_nan_zero((value_head >= 0x7ff00000) |
				((value_head| lo_word)==vi_type(0)));
	vi_type is_denom(value_head < 0x00100000);

	// exponent:
	vi_type e((value_head >> 20) - vi_type(1022));

	// denormals
	// first multiply with 2^54
	// const vf_type two54=1.80143985094819840000e+16;
	const vf_type two54=0x1.p54;
	vf_type vden(two54 * vd);
	vi_type hden(_T::extract_high_word(vden));
	vi_type lden(_T::extract_low_word(vden));
	vi_type value_head_den(hden & vi_type(0x7fffffff));
	vi_type eden((value_head_den>>20) - vi_type(1022+54));

	// select denom/normal
	e = _T::sel(is_denom, eden, e);
	hi_word = _T::sel(is_denom, hden, hi_word);
	lo_word = _T::sel(is_denom, lden, lo_word);
	// insert exponent
	hi_word = (hi_word & vi_type(0x800fffff)) | vi_type(0x3fe00000);
	// combine low and high word
	vf_type frc(_T::combine_words(lo_word, hi_word));
	// inf, nan, zero
	vmf_type f_inz(_T::vmi_to_vmf(is_inf_nan_zero));
	e= _T::sel(is_inf_nan_zero, vi_type(0), e);
	frc = _T::sel(f_inz, vd, frc);

	if (ve != nullptr)
		*ve= e;
	return frc;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogbp1(const vf_type& vd)
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
typename cftal::math::func_core<double, _T>::vi_type
cftal::math::func_core<double, _T>::
ilogb(const vf_type& d)
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
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
log_k2(const dvf_type& d)
{
        using ctbl=impl::d_real_constants<dvf_type, double>;

        dvf_type sc(d* vf_type(0.7071) /*vf_type(M_SQRT1_2)*/);

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
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_log_k(const vf_type& d)
{
        using ctbl=impl::d_real_constants<dvf_type, double>;

        vf_type sc(d* vf_type(0.7071) /*vf_type(M_SQRT1_2)*/);

        vi_type e = ilogbp1(sc);
        vf_type ef= _T::cvt_i_to_f(e);
        vf_type m(ldexp(d, -e));

        vf_type xm= m - vf_type(1.0);
        vf_type xp= m + vf_type(1.0);
        vf_type xr= xm / xp;
        vf_type x2 = xr*xr;

        vf_type t= ctbl::_2_over_i[23].h();
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
                t = t * x2 + ctbl::_2_over_i[i].h();
        t = t * x2 + vf_type(2.0);
        t = t * xr;

        xr = t + M_LN2 * ef;
        return xr;
}

template <typename _T>
inline
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
exp_k2(const dvf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;

        const double k(512.0);
        const int k_i(9);
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
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_exp_k(const vf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;

        const double k(512.0);
        const int k_i(9);
        const vf_type inv_k(1.0/k);

        vf_type m2= rint(d * ctbl::m_1_ln2.h());
        vf_type r= (d - ctbl::m_ln2.h()*m2) * inv_k;
	vf_type m=m2;

	vf_type s = ctbl::inv_fac[9].h();
        // s = s * r + ctbl::inv_fac[8];
        // s = s * r + ctbl::inv_fac[7];
        // s = s * r + ctbl::inv_fac[6];
        // s = s * r + ctbl::inv_fac[5];
        // s = s * r + ctbl::inv_fac[4];
        // s = s * r + ctbl::inv_fac[3];
        for (unsigned int i=8; i!=2; --i)
                s = s*r + ctbl::inv_fac[i].h();
        s = s * r + vf_type(0.5);
        s = s * r + vf_type(1.0);
        s = s * r;

        // scale back the 1/k reduced value
        const vf_type two(2.0);
        for (int i=0; i<k_i; ++i)
                s = s * two + s * s;
        s += vf_type(1.0);

        // scale back
        vi_type mi= _T::cvt_f_to_i(m);
        vf_type res(my_type::ldexp(s, mi));
        return res;
}


template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::dvf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::
func_core<double, _T>::
reduce_trig_arg_k(const vf_type& d)
{
        using ctbl = impl::d_real_constants<dvf_type, double>;
	constexpr double large_arg(2.0e8);
        vmf_type v_small_arg(abs(d) < vf_type(large_arg));
        // small argument reduction
        // reduce by pi half
        dvf_type qf(rint(d * ctbl::m_2_pi));
        dvf_type d0((d - qf * ctbl::m_pi_2.h()) -
                    qf * ctbl::m_pi_2.l());
        vi_type q(_T::cvt_f_to_i(qf.h()+qf.l()));

        if (!all_signs(v_small_arg)) {
                // reduce the large arguments
		constexpr std::size_t N=_T::NVF();
		constexpr std::size_t NI=_T::NVI();
		struct alignas(N*sizeof(double)) v_d {
			double _sc[N];
		} tf, d0_l, d0_h;
		struct alignas(NI*sizeof(int)) v_i {
			int32_t _sc[NI];
		} ti;
		mem::aligned::store(tf._sc, d);
		mem::aligned::store(ti._sc, q);
		mem::aligned::store(d0_l._sc, d0.l());
		mem::aligned::store(d0_h._sc, d0.h());
		for (std::size_t i=0; i<N; ++i) {
			if (fabs(tf._sc[i]) >= large_arg) {
				double y[2];
				ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i],
								   y);
				d0_l._sc[i]= y[1];
 				d0_h._sc[i]= y[0];
			}
		}
		vf_type rh(mem::aligned::load(d0_h._sc));
		vf_type rl(mem::aligned::load(d0_l._sc));
		d0 = dvf_type(rh, rl);
		q = mem::aligned::load(ti._sc); 
        }
        return std::make_pair(d0, q);
}

template <typename _T>
const 
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::m_sin_c_k2[]= {
	// +1/21!
	dvf_type(  1.9572941063391262595198e-20, -1.3643503830087908487197e-36),
	// -1/19!
	dvf_type( -8.2206352466243294955370e-18, -2.2141894119604265363725e-34),
	// +1/17!
	dvf_type(  2.8114572543455205981105e-15,  1.6508842730861432599403e-31),
	// -1/15!
	dvf_type( -7.6471637318198164055138e-13, -7.0387287773345300106125e-30),
	// +1/13!
	dvf_type(  1.6059043836821613340863e-10,  1.2585294588752098052117e-26),
	// -1/11!
	dvf_type( -2.5052108385441720223866e-08,  1.4488140709359119660293e-24),
	// +1/9!
	dvf_type(  2.7557319223985892510951e-06, -1.8583932740464720810392e-22),
	// -1/7!
	dvf_type( -1.9841269841269841252632e-04, -1.7209558293420705286779e-22),
	// +1/5!
	dvf_type(  8.3333333333333332176851e-03,  1.1564823173178713802252e-19),
	// -1/3!
	dvf_type( -1.6666666666666665741481e-01, -9.2518585385429706566156e-18)
};

template <typename _T>
const 
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::m_cos_c_k2[]= {
	// -1/22!
	dvf_type( -8.8967913924505740778892e-22,  7.9114026148723762170263e-38),
	// +1/20!
	dvf_type(  4.1103176233121648440650e-19,  1.4412973378659527149817e-36),
	// -1/18!
	dvf_type( -1.5619206968586225271148e-16, -1.1910679660273754002389e-32),
	// +1/16!
	dvf_type(  4.7794773323873852534462e-14,  4.3992054858340812566328e-31),
	// -1/14!
	dvf_type( -1.1470745597729724507297e-11, -2.0655512752830745424540e-28),
	// +1/12!
	dvf_type(  2.0876756987868100186555e-09, -1.2073450591132599716911e-25),
	// -1/10!
	dvf_type( -2.7557319223985888275786e-07, -2.3767714622250297318518e-23),
	// +1/8!
	dvf_type(  2.4801587301587301565790e-05,  2.1511947866775881608473e-23),
	// -1/6!
	dvf_type( -1.3888888888888889418943e-03,  5.3005439543735770590566e-20),
	// +1/4!
	dvf_type(  4.1666666666666664353702e-02,  2.3129646346357426641539e-18)
};


template <typename _T>
__attribute__((flatten, noinline))
std::pair<typename cftal::math::func_core<double, _T>::dvf_type,
	  typename cftal::math::func_core<double, _T>::dvf_type>
cftal::math::func_core<double, _T>::sin_cos_k(const vf_type& d)
{
        // using ctbl = impl::d_real_constants<dvf_type, double>;
	std::pair<dvf_type, vi_type> rr(reduce_trig_arg_k(d));
	const vi_type& q= rr.second;
	const dvf_type& dh= rr.first;

        vmi_type q_and_2((q & vi_type(2))==vi_type(2));
        vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));

        vmi_type q_and_1((q & vi_type(1))==vi_type(1));
        vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

	// calculate sin + cos
        dvf_type x= sqr(dh);
        dvf_type s, c;

	s = m_sin_c_k2[0];
	for (unsigned i=0; i<10; ++i)
		s = s * x + m_sin_c_k2[i];
        s = s * x + vf_type(1.0);
        s = s * dh;

	c= m_cos_c_k2[0];
	for (unsigned i=0; i<10; ++i)
		c = c * x + m_cos_c_k2[i];
	c = c * x - vf_type(0.5);
	c = c * x + vf_type(1.0);
	// swap sin/cos if q & 1
	dvf_type rsin(
		_T::sel(q_and_1_f, c.h(), s.h()),
		_T::sel(q_and_1_f, c.l(), s.l()));
	dvf_type rcos(
		_T::sel(q_and_1_f, s.h(), c.h()),
		_T::sel(q_and_1_f, s.l(), c.l()));
	// swap signs 
	rsin.h() = mulsign(rsin.h(), q_and_2_f);
	rsin.l() = mulsign(rsin.l(), q_and_2_f);
	rcos.h() = mulsign(rcos.h(), q_and_2_f ^ q_and_1_f);
	rcos.l() = mulsign(rcos.l(), q_and_2_f ^ q_and_1_f);
	return std::make_pair(rsin, rcos);
}


template <typename _T>
inline
std::pair<typename cftal::math::func_core<double, _T>::vf_type,
          typename cftal::math::func_core<double, _T>::vi_type>
cftal::math::func_core<double, _T>::
native_reduce_trig_arg_k(const vf_type& d)
{
#define PI4_A 0.78539816290140151978
#define PI4_B 4.9604678871439933374e-10
#define PI4_C 1.1258708853173288931e-18
#define PI4_D 1.7607799325916000908e-27

	constexpr double large_arg(2.0e8);
        vmf_type v_small_arg(abs(d) < vf_type(large_arg));

	vf_type qf(rint(d * (2 * M_1_PI)));
	vi_type q(_T::cvt_f_to_i(qf));
	
	vf_type d0(d);
	d0 = d0 - qf * (2*PI4_A);
	d0 = d0 - qf * (2*PI4_B);
	d0 = d0 - qf * (2*PI4_C);
	d0 = d0 - qf * (2*PI4_D);

#undef PI4_A
#undef PI4_B
#undef PI4_C
#undef PI4_C

        if (!all_signs(v_small_arg)) {
                // reduce the large arguments
		constexpr std::size_t N=_T::NVF();
		constexpr std::size_t NI=_T::NVI();
		struct alignas(N*sizeof(double)) v_d {
			double _sc[N];
		} tf, d0_l;
		struct alignas(NI*sizeof(int)) v_i {
			int32_t _sc[NI];
		} ti;
		mem::aligned::store(tf._sc, d);
		mem::aligned::store(ti._sc, q);
		mem::aligned::store(d0_l._sc, d0);
		for (std::size_t i=0; i<N; ++i) {
			if (fabs(tf._sc[i]) >= large_arg) {
				double y[2];
				ti._sc[i]=impl::__ieee754_rem_pio2(tf._sc[i],
								   y);
				d0_l._sc[i]= y[1] + y[0];
			}
		}
		d0 = mem::aligned::load(d0_l._sc);
		q = mem::aligned::load(ti._sc); 
        }
        return std::make_pair(d0, q);
}

template <typename _T>
__attribute__((flatten, noinline))
std::pair<typename cftal::math::func_core<double, _T>::vf_type,
	  typename cftal::math::func_core<double, _T>::vf_type>
cftal::math::func_core<double, _T>::
native_sin_cos_k(const vf_type& d)
{
	std::pair<vf_type, vi_type> rq(
		native_reduce_trig_arg_k(d));
	vf_type& x= rq.first;
	const vi_type& q= rq.second;

	vf_type x2(x*x);

	vf_type s, c;
	s = 1.58938307283228937328511e-10;
	s = s * x2 - 2.50506943502539773349318e-08;
	s = s * x2 + 2.75573131776846360512547e-06;
	s = s * x2 - 0.000198412698278911770864914;
	s = s * x2 + 0.0083333333333191845961746;
	s = s * x2 - 0.166666666666666130709393;
	s = s * x2 + 1.0;
	s = s * x;

	c = -1.13615350239097429531523e-11;
	c = c * x2 + 2.08757471207040055479366e-09;
	c = c * x2 - 2.75573144028847567498567e-07;
	c = c * x2 + 2.48015872890001867311915e-05;
	c = c * x2 - 0.00138888888888714019282329;
	c = c * x2 + 0.0416666666666665519592062;
	c = c * x2 - 0.5;
	c = c * x2 + 1.0; 

        vmi_type q_and_2((q & vi_type(2))==vi_type(2));
        vmf_type q_and_2_f(_T::vmi_to_vmf(q_and_2));
        vmi_type q_and_1((q & vi_type(1))==vi_type(1));
        vmf_type q_and_1_f(_T::vmi_to_vmf(q_and_1));

	// swap sin/cos if q & 1
	vf_type rs(_T::sel(q_and_1_f, c, s));
	vf_type rc(_T::sel(q_and_1_f, s, c));
	// swap signs 
	rs = mulsign(rs, q_and_2_f);
	rc = mulsign(rc, q_and_2_f ^ q_and_1_f);

	return std::make_pair(rs, rc);
}

template <typename _T>
const 
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::m_atan2_c_k2[]= {
	dvf_type( 1.0)/_T(45.0),
	dvf_type(-1.0)/_T(43.0),
	dvf_type( 1.0)/_T(41.0),
	dvf_type(-1.0)/_T(39.0),
	dvf_type( 1.0)/_T(37.0),
	dvf_type(-1.0)/_T(35.0),
	dvf_type( 1.0)/_T(33.0),
	dvf_type(-1.0)/_T(31.0),
	dvf_type( 1.0)/_T(29.0),
	dvf_type(-1.0)/_T(27.0),
	dvf_type( 1.0)/_T(25.0),
	dvf_type(-1.0)/_T(23.0),
	dvf_type( 1.0)/_T(21.0),
	dvf_type(-1.0)/_T(19.0),
	dvf_type( 1.0)/_T(17.0),
	dvf_type(-1.0)/_T(15.0),
	dvf_type( 1.0)/_T(13.0),
	dvf_type(-1.0)/_T(11.0),
	dvf_type( 1.0)/_T( 9.0),
	dvf_type(-1.0)/_T( 7.0),
	dvf_type( 1.0)/_T( 5.0),
	dvf_type(-1.0)/_T( 3.0),
};

template <typename _T>
typename cftal::math::func_core<double, _T>::dvf_type
cftal::math::func_core<double, _T>::
atan2_k2(const dvf_type& cx, const dvf_type& cy)
{
        vmf_type f_x_lt_z(cx.h() < vf_type(0));
        vmi_type i_x_lt_z(_T::vmf_to_vmi(f_x_lt_z));
        vi_type q(_T::sel(i_x_lt_z, vi_type(-2), vi_type(0)));
	dvf_type x(_T::sel(f_x_lt_z, -cx.h(), cx.h()),
		   _T::sel(f_x_lt_z, -cx.l(), cx.l()));

	vmf_type f_y_gt_x(cy > x);
	vmf_type i_y_gt_x(_T::vmf_to_vmi(f_y_gt_x));
	
        q += _T::sel(i_y_gt_x, vi_type(1), vi_type(0));

        // vf_type y = _T::sel(mf, -x, cy);
	dvf_type y(_T::sel(f_y_gt_x, -(x.h()), cy.h()),
		   _T::sel(f_y_gt_x, -(x.l()), cy.l()));
        // x = _T::sel(mf, cy, x);
	x = dvf_type(_T::sel(f_y_gt_x, cy.h(), x.h()),
		     _T::sel(f_y_gt_x, cy.l(), x.l()));
	
	dvf_type s(y / x);
	dvf_type t(sqr(s));

	const std::size_t N= sizeof(m_atan2_c_k2)/sizeof(m_atan2_c_k2[0]);
	dvf_type u(m_atan2_c_k2[0]);
	for (std::size_t i=1; i<N; ++i) {
		u = u * t + m_atan2_c_k2[i];
	}
	
	t = u * t * s  + s;

        using ctbl=impl::d_real_constants<dvf_type, double>;
	t = _T::cvt_f_to_i(q) * ctbl::m_pi_2 + t;
	return t;
}

template <typename _T>
typename cftal::math::func_core<double, _T>::vf_type
cftal::math::func_core<double, _T>::
native_atan2_k(const vf_type& x, const vf_type& y)
{
	return 0.0;
}

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_ln2(
        // 0.693147180559945286226764, 2.319046813846299558417771e-17
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
cftal::math::impl::d_real_constants<_T, double>::m_pi_2(
        1.570796326794896558e+00, 6.123233995736766036e-17);

template <class _T>
const _T
cftal::math::impl::d_real_constants<_T, double>::m_2_pi(
        _T(1.0) / _T(1.570796326794896558e+00,
                     6.123233995736766036e-17));


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
