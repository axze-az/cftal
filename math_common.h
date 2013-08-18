#if !defined (__CFTAL_MATH_COMMON_H__)
#define __CFTAL_MATH_COMMON_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {

        namespace math {

		namespace impl {

			template <class _T, unsigned _P>
			struct ipow {
				static _T v(const _T& x) {
					_T r(ipow<_T, _P/2>::v(x*x));
					if (_P & 1)
						r *= x;
					return r;
				}
			};

			template <class _T>
			struct ipow<_T, 0U> {
				static _T v(const _T& x) {
					return _T(1);
				}
			};

			template <class _T>
			struct ipow<_T, 1U> {
				static _T v(const _T& x) {
					return x;
				}
			};

			template <class _T>
			struct ipow<_T, 2U> {
				static _T v(const _T& x) {
					return x*x;
				}
			};
		}

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
