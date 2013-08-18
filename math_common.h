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
                struct func;


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
                        _T sin2x(const _T& sinx, const _T& cosx) {
                                return _T(2.0) * sinx * cosx;
                        }

                        template <class _T>
                        d_real<_T> sin2x(const d_real<_T>& sinx,
                                         const d_real<_T>& cosx) {
                                return mul_pwr2(sinx* cosx, _T(2.0));
                        }

                        template <class _T>
                        _T cos2x(const _T& sinx, const _T& cosx) {
                                return cosx * cosx - sinx * sinx;
                        }

                        template <class _T>
                        d_real<_T> cos2x(const d_real<_T>& sinx,
                                         const d_real<_T>& cosx) {
                                return sqr(cosx) - sqr(sinx);
                        }

                        template <class _T>
                        _T sin4x(const _T& sinx, const _T& cosx) {
                                return sin2x(sin2x(sinx, cosx),
                                             cos2x(sinx, cosx));
                        }

                        template <class _T>
                        _T cos4x(const _T& sinx, const _T& cosx) {
                                return cos2x(sin2x(sinx, cosx),
                                             cos2x(sinx, cosx));
                        }

			// unsigned integer pow
                        template <class _T, unsigned _P>
                        struct ipow {
                                static _T v(const _T& x) {
                                        _T r(ipow<_T, _P/2>::v(x*x));
                                        if (_P & 1)
                                                r *= x;
                                        return r;
                                }
                        };

			// unsigned integer pow, specialized for _P==0
                        template <class _T>
                        struct ipow<_T, 0U> {
                                static _T v(const _T& x) {
                                        return _T(1);
                                }
                        };

			// unsigned integer pow, specialized for _P==1
                        template <class _T>
                        struct ipow<_T, 1U> {
                                static _T v(const _T& x) {
                                        return x;
                                }
                        };

			// unsigned integer pow, specialized for _P==2
                        template <class _T>
                        struct ipow<_T, 2U> {
                                static _T v(const _T& x) {
                                        return x*x;
                                }
                        };

			// nth root newton raphson step
                        template <unsigned _R, class _T>
                        struct nth_root_nr {
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
			// for root _R
			template <typename _SCALAR_FLOAT,
				  typename _SCALAR_INT,
				  typename _TRAITS,
				  unsigned _R> 
			struct nth_root_guess {
                                typedef typename _TRAITS::vf_type vf_type;
				static vf_type v(const vf_type& f);
			};

			// the initial guess for a vector of float
			// with int32_t using traits
			// for root _R
			template <typename _TRAITS, unsigned _R>
			struct nth_root_guess<float, int32_t,
					      _TRAITS, _R> {
				typedef typename _TRAITS::vf_type vf_type;
				typedef typename _TRAITS::vi_type vi_type;
				static vf_type v(const vf_type& f) {
					const int ebits = 8;
					const int fbits = 23;
					vf_type x(f);
					vi_type& i = (vi_type&) f;
					const int bias = (1 << (ebits-1))-1;
					i = (i - (bias << fbits)) / _R + 
						(bias << fbits);
					return x;
				}
			};

			// the initial guess for a vector of double
			// with int32_t using traits
			// for root _R
			template <typename _TRAITS, unsigned _R>
			struct nth_root_guess<double, int32_t,
					      _TRAITS, _R> {
				typedef typename _TRAITS::vf_type vf_type;
				typedef typename _TRAITS::vi_type vi_type;
				static vf_type v(const vf_type& f) {
					vi_type hw=
						_TRAITS::extract_high_word(f);
					const int32_t bias = (1 << (11-1))-1;
					vi_type bias_shl_20(bias << 20);
					divisor<vi_type, int32_t> r(_R);
					hw = (hw - bias_shl_20)/r + 
						bias_shl_20;
					vf_type g0;
					g0 = _TRAITS::combine_words(hw, 
								    vi_type(0));
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
                                static vf_type v(const vf_type& x);
#if 0
                                static _T v(const _T& x) {
                                        // xi0 should contain at least 4 bits
                                        _T xi0(iguess(x));
                                        _T xi1(nr(xi0, x));
                                        _T xi2(nr(xi1, x));
                                        _T xi3(nr(xi2, x));
                                        _T xi4(nr(xi3, x));
                                        _T xi5(nr(xi4, x));
                                        return xi5;
                                        int expo(0);
                                        std::frexp(xi5, &expo);
                                        _T xulp(std::ldexp(1.0, expo-53));
                                        _T xup(ipow<_T,_R>::v(xi5+xulp));
                                        _T xcur(ipow<_T,_R>::v(xi5));
                                        _T xdn(ipow<_T,_R>::v(xi5-xulp));

                                        _T res(xi5);
                                        if (abs(xup -x) < abs(xcur -x)) {
                                                res = xi5+xulp;
                                                xcur = xup;
                                        }
                                        if (abs(xdn -x) < abs(xcur -x)) {
                                                res = xi5-xulp;
                                        }
                                }
#endif
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
						       _TRAITS,
						       _R> guess_t;

				static vf_type v(const vf_type& x) {
					vf_type xi0(guess_t::v(x));
					vf_type xi1(nr_step_t::v(xi0, x));
					vf_type xi2(nr_step_t::v(xi1, x));
					vf_type xi3(nr_step_t::v(xi2, x));
					vf_type xi4(nr_step_t::v(xi3, x));
					dvf_type dxi5(
						last_nr_step_t::v(xi4, x));
					vf_type xi5(dxi5.h() + dxi5.l());
					const vf_type zero(vf_type(0.0));
					vmf_type is_zero(x == zero);
					vf_type r(_TRAITS::sel(is_zero,
							       zero,
							       xi5));
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

// Local Variables:
// mode: c++
// end:
#endif
