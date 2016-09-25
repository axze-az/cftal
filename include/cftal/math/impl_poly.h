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


            template <typename _X, typename _C1, typename _C0>
            void
            poly_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                    _X x0, _X x1, _X x2, _X x3,
                    _C1 c1_0, _C1 c1_1, _C1 c1_2, _C1 c1_3,
                    _C0 c0_0, _C0 c0_1, _C0 c0_2, _C0 c0_3);

            template <typename _X,
                      typename _CN, typename _CNM1, typename ... _CS>
            void
            poly_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                    _X x0, _X x1, _X x2, _X x3,
                    _CN cn_0, _CN cn_1, _CN cn_2, _CN cn_3,
                    _CNM1 cnm1_0, _CNM1 cnm1_1, _CNM1 cnm1_2, _CNM1 cnm1_3,
                    _CS... cs);

            // error free transformation of evaluation of polynomials
            // setup step
            template <typename _X, typename _C1, typename _C0>
            void
            eft_poly_s0(_X& y, _X& ye, _X x, _C1 c1, _C0 c0);

            // error free transformation of evaluation of polynomials
            // next step
            template <typename _X, typename _C1, typename _C0>
            void
            eft_poly_si(_X& y, _X& ye, _X x, _C1 c1h, _C1 c1l, _C0 c0);

            // error free transformation of evaluation of polynomials
            // recursive next steps
            template <typename _X, typename _CN, typename _CNM1,
                      typename ... _CS>
            void
            eft_poly_si(_X& y, _X& ye, _X x, _CN cnh, _CN cnl, _CNM1 cnm1,
                        _CS... cs);

            // error free transformation of evaluation of polynomials
            // overload for degree 1
            template <typename _X, typename _CN, typename _CNM1>
            void
            eft_poly(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1);
            
            // error free transformation of evaluation of polynomials
            template <typename _X, typename _CN, typename _CNM1,
                      typename ... _CS>
            void
            eft_poly(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1,
                     _CS... cs);

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

template <typename _X, typename _C1, typename _C0>
void
cftal::math::impl::poly_n4(_X& y0, _X& y1, _X& y2, _X& y3,
                           _X x0, _X x1, _X x2, _X x3,
                           _C1 c1_0, _C1 c1_1, _C1 c1_2, _C1 c1_3,
                           _C0 c0_0, _C0 c0_1, _C0 c0_2, _C0 c0_3)
{
    y0 = poly(x0, c1_0, c0_0);
    y1 = poly(x1, c1_1, c0_1);
    y2 = poly(x2, c1_2, c0_2);
    y3 = poly(x3, c1_3, c0_3);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::impl::
poly_n4(_X& y0, _X& y1, _X& y2, _X& y3,
        _X x0, _X x1, _X x2, _X x3,
        _CN cn_0, _CN cn_1, _CN cn_2, _CN cn_3,
        _CNM1 cnm1_0, _CNM1 cnm1_1, _CNM1 cnm1_2, _CNM1 cnm1_3,
        _CS... cs)
{
    poly_n4(y0, y1, y2, y3, x0, x1, x2, x3,
            cn_0, cn_1, cn_2, cn_3,
            cnm1_0, cnm1_1, cnm1_2, cnm1_3);
    poly_n4(y0, y1, y2, y3, x0, x1, x2, x3,
            y0, y1, y2, y3, cs...);
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::impl::eft_poly_s0(_X& y, _X& ye, _X x, _C1 c1, _C0 c0)
{
    using d_ops=cftal::impl::d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    y = d_ops::two_prod(c1, x, p_i);
    y = d_ops::two_sum(y, c0, o_i);
    ye= (p_i + o_i);
}

template <typename _X, typename _C1, typename _C0>
void
cftal::math::impl::eft_poly_si(_X& y, _X& ye, _X x, _C1 c1h, _C1 c1l, _C0 c0)
{
    using d_ops=cftal::impl::d_real_ops<_X, d_real_traits<_X>::fma>;
    _X p_i, o_i;
    y = d_ops::two_prod(c1h, x, p_i);
    y = d_ops::two_sum(y, c0, o_i);
    ye= c1l*x + (p_i + o_i);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::impl::
eft_poly_si(_X& y, _X& ye, _X x, _CN cnh, _CN cnl, _CNM1 cnm1, _CS ... cs)
{
    eft_poly_si(y, ye, x, cnh, cnl, cnm1);
    const _X _y=y;
    const _X _ye=ye;
    eft_poly_si(y, ye, x, _y, _ye, cs...);
}

template <typename _X, typename _CN, typename _CNM1>
void
cftal::math::impl::
eft_poly(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1)
{
    eft_poly_s0(y, ye, x, cn, cnm1);
}

template <typename _X,
          typename _CN, typename _CNM1, typename ... _CS>
void
cftal::math::impl::
eft_poly(_X& y, _X& ye, _X x, _CN cn, _CNM1 cnm1, _CS ... cs)
{
    eft_poly_s0(y, ye, x, cn, cnm1);
    const _X _y=y;
    const _X _ye=ye;
    eft_poly_si(y, ye, x, _y, _ye, cs...);
}


// local variables:
// mode: c++
// end:
#endif
