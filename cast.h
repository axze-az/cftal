#if !defined (__CFTAL_CAST_H__)
#define __CFTAL_CAST_H__ 1

#include <cftal/config.h>

namespace cftal {

    namespace impl {

        template <typename _D, typename _S>
        struct cast {

            union ds {
                _D _d;
                _S _s;
                ds(const _S& s) : _s{s} {}
            };

            static _D v(const _S& s) {
                ds c{s};
                return c._d;
            }
        };

        template <typename _SD>
        struct cast<_SD, _SD> {
            static const _SD& v(const _SD& r) {
                return r;
            }
        };
    }

    // forwarder function to impl::cast<_D, _S>
    template <typename _D, typename _S>
    _D as(const _S& s);
}


template <typename _D, typename _S>
inline
_D
cftal::as(const _S& s)
{
    return impl::cast<_D, _S>::v(s);
}


// Local variables:
// mode: c++
// end:
#endif
