#if !defined (__CFTAL_MATH_IMPL_POLY_H__)
#define __CFTAL_MATH_IMPL_POLY_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <stdexcept>
#include <iterator>

namespace cftal {
    namespace math {
        namespace impl {

            // arrays and containers contain c_n in C[0]

            template <typename _X, typename _C1, typename _C0>
            _X
            poly(_X x, _C1 c1, _C0 c0);

            template <typename _X,
                      typename _CN, typename _CNM1, typename ... _CS>
            _X
            poly(_X x, _CN cn, _CNM1 cnm1, _CS... cs);

            template <typename _X, typename _C>
            _X
            poly(_X x, const _C& c);

            template <typename _X, typename _C, std::size_t _N>
            _X
            poly(_X x, const _C (&a)[_N]);

            template <typename _F, typename _C, std::size_t _N>
            d_real<_F>
            poly(d_real<_F> x, const d_real<_C> (&a)[_N]);

            template <typename _F, typename _C, std::size_t _N>
            _F
            poly(_F x, const d_real<_C> (&a)[_N]);

            // polynomial with c1 = 1.0
            template <typename _X, typename _C0>
            _X
            poly1(_X x, _C0 c0);

            // polynomial with cn = 1.0
            template <typename _X,
                      typename _CNM1, typename ... _CS>
            _X
            poly1(_X x, _CNM1 cnm1, _CS... cs);

        }
    }
}

template <typename _X, typename _C1, typename _C0>
_X
cftal::math::impl::poly(_X x, _C1 c1, _C0 c0)
{
    return x*c1 + c0;
}

template <typename _X,
            typename _CN, typename _CNM1, typename ... _CS>
_X
cftal::math::impl::poly(_X x, _CN cn, _CNM1 cnm1, _CS... cs)
{
    _X t = poly(x, cn, cnm1);
    _X r = poly(x, t, cs...);
    return r;
}

template <typename _X, typename _C>
_X
cftal::math::impl::poly(_X x, const _C& c)
{
    auto b=std::cbegin(c);
    auto e=std::cend(c);
    if (b==e) {
        throw std::invalid_argument("cftal::math::poly(x, C)");
    }
    _X r= (*b);
    ++b;
    while (b != e) {
        r = poly(x, r, *b);
        ++b;
    }
    return r;
}

template <typename _X, typename _C, std::size_t _N>
_X
cftal::math::impl::poly(_X x, const _C (&a)[_N])
{
    static_assert(_N > 0, "invalid call to poly(x, array)");
    _X r= _X(a[0]);
    for (std::size_t i=1; i<_N; ++i) {
        r= poly(x, r, a[i]);
    }
    return r;
}

template <typename _F, typename _C, std::size_t _N>
cftal::d_real<_F>
cftal::math::impl::poly(d_real<_F> x, const d_real<_C> (&a)[_N])
{
    static_assert(
        _N > 0,
        "invalid call to poly(d_real<_F>, d_real<_C>(&a)[])");
    d_real<_F> r=d_real<_F>(a[0]);
    for (std::size_t i=1; i<_N; ++i) {
        r=poly(x, r, d_real<_F>(a[i] ));
    }
    return r;
}

template <typename _F, typename _C, std::size_t _N>
_F
cftal::math::impl::poly(_F x, const d_real<_C> (&a)[_N])
{
    static_assert(_N > 0, "invalid call to poly(_F, d_real<_C>(&a)[])");
    _F r= a[0].h();
    for (std::size_t i=1; i<_N; ++i) {
        r= poly(x, r, _F(a[i].h()));
    }
    return r;
}

// polynomial with c1 = 1.0
template <typename _X, typename _C0>
_X
cftal::math::impl::poly1(_X x, _C0 c0)
{
    return x + c0;
}

// polynomial with cn = 1.0
template <typename _X,typename _CNM1, typename ... _CS>
_X
cftal::math::impl::poly1(_X x, _CNM1 cnm1, _CS... cs)
{
    _X t = poly1(x, cnm1);
    _X r = poly(x, t, cs...);
    return r;
}


// local variables:
// mode: c++
// end:
#endif
