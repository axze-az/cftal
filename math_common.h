#if !defined (__CFTAL_MATH_COMMON_H__)
#define __CFTAL_MATH_COMMON_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <cftal/divisor.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {

        namespace math {

                template <typename _FLOAT_T, typename _INT_T>
                struct func_traits;

		template <typename _FLOAT_T, typename _INT_T,
                          typename _TRAITS_T= func_traits<_FLOAT_T, _INT_T> > 
		struct func_core {
                        typedef typename _TRAITS_T::vf_type vf_type;
                        typedef typename _TRAITS_T::vi_type vi_type;
                        typedef typename _TRAITS_T::vmf_type vmf_type;
                        typedef typename _TRAITS_T::vmi_type vmi_type;
                        typedef d_real<vf_type> dvf_type;

			// exp core
                        static dvf_type 
			exp_k2(const dvf_type& dvf);
			// log core
                        static dvf_type 
			log_k2(const dvf_type& dvf);
			// sin and cos core, return sin in first
			static std::pair<dvf_type, dvf_type>
			sin_cos_k(const vf_type& v);
			// native sin and cos core, return sin in first
			static std::pair<vf_type, vf_type>
			native_sin_cos_k(const vf_type& v);
		};
		
                template <typename _FLOAT_T, typename _INT_T,
                          typename _TRAITS_T= func_traits<_FLOAT_T, _INT_T> >
                struct func_common : public func_core< _FLOAT_T,
						       _INT_T,
						       _TRAITS_T> {
			typedef func_core<_FLOAT_T,
					  _INT_T,
					  _TRAITS_T> base_type;

			typedef func_common<_FLOAT_T,
					    _INT_T,
					    _TRAITS_T> my_type;

#if 0
                        typedef typename base_type::vf_type vf_type;
                        typedef typename base_type::vi_type vi_type;
                        typedef typename base_type::vmf_type vmf_type;
                        typedef typename base_type::vmi_type vmi_type;
			typedef typename base_type::dvf_type dvf_type;
#else
                        using vf_type = typename base_type::vf_type;
                        using vi_type = typename base_type::vi_type;
                        using vmf_type = typename base_type::vmf_type;
                        using vmi_type = typename base_type::vmi_type;
			using dvf_type = typename base_type::dvf_type;
#endif
			
			static void sincos(const vf_type& vf,
					   vf_type* psin, 
					   vf_type* pcos);
                        static vf_type sin(const vf_type& vf);
			static vf_type cos(const vf_type& vf);
                        static vf_type tan(const vf_type& vf);
			static vf_type cot(const vf_type& vf);

			static void native_sincos(const vf_type& vf,
						  vf_type* psin, 
						  vf_type* pcos);
			static vf_type native_sin(const vf_type& vf);
			static vf_type native_cos(const vf_type& vf);
			static vf_type native_tan(const vf_type& vf);
			static vf_type native_cot(const vf_type& vf);
		};


                template <typename _FLOAT_T, typename _INT_T,
                          typename _TRAITS_T= func_traits<_FLOAT_T, _INT_T> >
                struct func : public func_common< _FLOAT_T,
						  _INT_T,
						  _TRAITS_T> {
                        typedef typename _TRAITS_T::vf_type vf_type;
                        typedef typename _TRAITS_T::vi_type vi_type;
                        typedef typename _TRAITS_T::vmf_type vmf_type;
                        typedef typename _TRAITS_T::vmi_type vmi_type;
		};


                namespace approx {

                }

                namespace impl {

                        template <class _VEC, typename _FLOAT_T>
                        struct d_real_constants {};

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
			
			// integer power 
			template <class _T>
			struct ivpow {
				static _T v(const _T& xx, int p);
			};

			// unsigned integer pow
                        template <class _T, unsigned _P>
                        struct ipow {
                                static _T v(const _T& x);
                        };

			// unsigned integer pow, specialized for _P==0
                        template <class _T>
                        struct ipow<_T, 0U> {
                                static _T v(const _T& x);
                        };

			// unsigned integer pow, specialized for _P==1
                        template <class _T>
                        struct ipow<_T, 1U> {
                                static _T v(const _T& x);
                        };

			// unsigned integer pow, specialized for _P==2
                        template <class _T>
                        struct ipow<_T, 2U> {
                                static _T v(const _T& x);
                        };


			template <class _T>
			struct nth_root_vnr {
                                static _T v(const _T& xi, const _T& x, unsigned r) {
                                        const _T rr(r);
                                        _T x_pow_nm1(ivpow<_T>::v(xi, r-1));
                                        _T en( x - xi * x_pow_nm1);
                                        _T den(rr * x_pow_nm1);
                                        _T xip1( xi + en / den);
                                        return xip1;
                                }
			};

			// nth root newton raphson step
                        template <unsigned _R, class _T>
                        struct nth_root_nr : public nth_root_vnr<_T> {
                                // one newton raphson step
                                static _T v(const _T& xi, const _T& x) {
                                        const _T r(_R);
                                        _T x_pow_nm1(ipow<_T, _R-1>::v(xi));
                                        _T en( x - xi * x_pow_nm1);
                                        _T den(r * x_pow_nm1);
                                        _T xip1( xi + en / den);

                                        return xip1;
                                }
                        };

			// the initial guess for a vector of _SCALAR_FLOAT
			// with an corresponding _SCALAR_INT using traits
			// for root r
			template <typename _SCALAR_FLOAT,
				  typename _SCALAR_INT,
				  typename _TRAITS> 
			struct nth_root_guess {
                                typedef typename _TRAITS::vf_type vf_type;
				static vf_type v(const vf_type& f, unsigned r);
			};

			// the initial guess for a vector of float
			// with int32_t using traits
			// for root _R
			template <typename _TRAITS>
			struct nth_root_guess<float, int32_t, _TRAITS> {
				typedef typename _TRAITS::vf_type vf_type;
				typedef typename _TRAITS::vi_type vi_type;
				static vf_type v(const vf_type& f, unsigned r) {
					// const int ebits = 8;
					// const int fbits = 23;
					vi_type i(_TRAITS::as_int(f));
					const int bias = (1 << (8-1))-1;
					const int bias_shl_23(bias << 23);
					const divisor<vi_type, int32_t> rr(r);
					i = (i - bias_shl_23) / rr + 
						bias_shl_23;
					vf_type x(_TRAITS::as_float(i));
					return x;
				}
			};

			// the initial guess for a vector of double
			// with int32_t using traits
			// for root _R
			template <typename _TRAITS>
			struct nth_root_guess<double, int32_t, _TRAITS> {
				typedef typename _TRAITS::vf_type vf_type;
				typedef typename _TRAITS::vi_type vi_type;

				static vf_type v(const vf_type& f, unsigned r) {
					vi_type hw=
						_TRAITS::extract_high_word(f);
					const int32_t bias = (1 << (11-1))-1;
					vi_type bias_shl_20(bias << 20);
					const divisor<vi_type, int32_t> rr(r);
					hw = (hw - bias_shl_20)/rr + 
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

			// nth root implementation
                        template <class _SCALAR_FLOAT,
                                  class _SCALAR_INT,
                                  typename _TRAITS, unsigned _R>
                        struct nth_root {
                                typedef typename _TRAITS::vf_type vf_type;
				template <unsigned _STEPS>
                                static vf_type v(const vf_type& x);
                        };

			// nth root implementation for double+int32_t
			template <typename _TRAITS, unsigned _R>
			struct nth_root<double, int32_t, _TRAITS, _R> {

                                typedef typename _TRAITS::vf_type vf_type;
				typedef d_real<vf_type> dvf_type;
                                typedef typename _TRAITS::vmf_type vmf_type;
				typedef nth_root_nr<_R, 
						    vf_type> nr_step_t;
				typedef nth_root_nr<_R, 
						    dvf_type> last_nr_step_t;
				typedef nth_root_guess<double, 
						       int32_t,
						       _TRAITS> guess_t;

				template <unsigned _NR_STEPS=6>
				static vf_type v(const vf_type& f) {
					vf_type x(abs(f));
					vf_type xin(guess_t::v(x, _R));

					for (unsigned i=0; i< _NR_STEPS; ++i)
						xin = nr_step_t::v(xin, x);

					xin = copysign(xin, f);
					const vf_type zero(vf_type(0.0));
					vmf_type is_zero_or_inf_or_nan(
						(x == zero) | isinf(x) | isnan(x));
					vf_type r(_TRAITS::sel(is_zero_or_inf_or_nan,
							       x,
							       xin));
					if ((_R & 1) == 0) {
						vmf_type is_neg(x < zero);
						r = _TRAITS::sel(is_neg, 
								 vf_type(_TRAITS::nan()),
								 r);
					}
					return r;
				}
			};

                } // impl

                template <int _I, class _T>
                _T pow(const _T& x) {
                        _T r(impl::ipow<_T, (_I < 0 ? -_I : _I) >::v(x));
                        if (_I < 0 ) {
                                r = _T(1)/r;
                        }
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
_T cftal::math::impl::ivpow<_T>::v(const _T& xx, int p) 
{
	_T x(xx);
	_T r(1);
	int n(p < 0 ? -p : p);
	while (1) {
		if (n & 1) 
			r*= x;
		n >>= 1;
		if (n == 0)
			break;
		x *= x;
	}
	if (p < 0)
		r= _T(1)/r;
	return r;
}

template <class _T, unsigned _P>
inline
_T cftal::math::impl::ipow<_T, _P>::v(const _T& x)
{
	_T r(ipow<_T, _P/2>::v(x*x));
	if (_P & 1)
		r *= x;
	return r;
}

template <class _T>
inline
_T cftal::math::impl::ipow<_T, 0U>::v(const _T& x)
{
	return _T(1);
}

template <class _T>
inline
_T cftal::math::impl::ipow<_T, 1U>::v(const _T& x)
{
	return x;
}

template <class _T>
inline
_T cftal::math::impl::ipow<_T, 2U>::v(const _T& x)
{
	return x*x;
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
sincos(const vf_type& d, vf_type* psin, vf_type* pcos)
{
	if ((psin!=nullptr) || (pcos!=nullptr)) {
		std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
		if (psin) {
			*psin = sin_cos.first.h() + sin_cos.first.l();
		}
		if (pcos) {
			*pcos = sin_cos.second.h() + sin_cos.second.l();
		}
	}
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
sin(const vf_type& d)
{
	std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
        return sin_cos.first.h() + sin_cos.first.l();
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
cos(const vf_type& d)
{
	std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
        return sin_cos.second.h() + sin_cos.second.l();
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
tan(const vf_type& d)
{
	std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
	dvf_type tn(sin_cos.first / sin_cos.second);
        return tn.h() + tn.l();
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
cot(const vf_type& d)
{
	std::pair<dvf_type, dvf_type> sin_cos(my_type::sin_cos_k(d));
	dvf_type ct(sin_cos.second / sin_cos.first);
        return ct.h() + ct.l();
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
void
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
native_sincos(const vf_type& d, vf_type* psin, vf_type* pcos)
{
	if ((psin!=nullptr) || (pcos!=nullptr)) {
		std::pair<vf_type, vf_type> sin_cos(
			my_type::native_sin_cos_k(d));
		if (psin) {
			*psin = sin_cos.first;
		}
		if (pcos) {
			*pcos = sin_cos.second;
		}
	}
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
native_sin(const vf_type& d)
{
	std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
        return sin_cos.first;
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
native_cos(const vf_type& d)
{
	std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
        return sin_cos.second;
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
native_tan(const vf_type& d)
{
	std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
	vf_type tn(sin_cos.first / sin_cos.second);
        return tn;
}

template <typename _FLOAT_T, typename _INT_T, 
	  typename _TRAITS_T>
typename cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::vf_type
cftal::math::func_common<_FLOAT_T, _INT_T, _TRAITS_T>::
native_cot(const vf_type& d)
{
	std::pair<vf_type, vf_type> sin_cos(my_type::native_sin_cos_k(d));
	vf_type tn(sin_cos.second / sin_cos.first);
        return tn;
}



// Local Variables:
// mode: c++
// end:
#endif
