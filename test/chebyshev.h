#if !defined (__CFTAL_TEST_CHEBYSHEV_H__)
#define __CFTAL_TEST_CHEBYSHEV_H__ 1

#include <cftal/config.h>
#include <cftal/test/of_fp_func.h>
#include <vector>
#include <cmath>
#include <stdexcept>

namespace cftal {

    namespace test {

        namespace chebyshev {

            template <class _T>
            struct coefficents : public std::vector<_T> {
                using base_type=std::vector<_T>;
                // definition interval
                func_domain<_T> _dom;
                // coefficients
                coefficents(const func_domain<_T>& d, std::size_t n)
                    : base_type(n, _T(0)), _dom(d) {}
            };

            template <class _T, class _F>
            coefficents<_T>
            interpolate(const func_domain<_T>& d, std::size_t n, _F f);

            template <class _T>
            _T
            evaluate(const coefficents<_T>& c, _T x);

            // polynomial coefficients
            template <class _T>
            struct poly_coefficents : public coefficents<_T> {
                using base_type=coefficents<_T>;
                poly_coefficents(const func_domain<_T>& d, std::size_t n)
                    : base_type(d, n) {}
            };
            
            // convert the chebyshev coefficients to a polynomial
            template <class _T>
            poly_coefficents<_T>
            to_polynomial(const coefficents<_T>& c);

            // and shift the polynomial coefficents to avoid 
            // transformations during the evaluation
            template <class _T>
            poly_coefficents<_T>
            shift_to_interval(const poly_coefficents<_T>& c);
            
        }
    }
}

template <class _T, class _F>
cftal::test::chebyshev::coefficents<_T>
cftal::test::chebyshev::interpolate(const func_domain<_T>& d,
                                    std::size_t n, _F f)
{
    coefficients<_T> r(d, n);

    _T bma = 0.5 * (d.second - d.first);
    _T bpa = 0.5 * (d.second + d.first);

    std::vector<_T> fx(n, _T(0));
    using std::cos;
    
    for (std::size_t k=0; k<n ; ++k) {
        // We evaluate the function at the n points required
        _T xs=cos(M_PI*(k+0.5)/n);
        fx[k]=f(y*bma+bpa);
    }
    _T fac=2.0/n;
    for (std::size_t j=0; j<n; ++j) {
        _T sum=0.0;
        for (std::size_t k=0; k<n; ++k) {
            sum += fx[k]*cos(M_PI*j*(k+0.5)/n);
        }
        r[j]=fac*sum;
    }
    return r;
}

template <class _T>
_T
cftal::test::chebyshev::evaluate(const coefficents<_T>& c, _T x)
{
    // the chebyshev polynomial is evaluated at:
    // y = [x − (b + a)/2]/[(b − a)/2], 
    // clenshaw algorithm:
    _T a= c._dom.first;
    _T b= c._dom.second;
    if (_T((x-a)*(x-b)) > _T(0)) {
        throw std::range_error(
            "cftal::test:chebyshev::evaluate: x out of range");
    }
    _T y=(_T(2.0)*x-a-b)/(b-a);
    _T y2=_T(2.0)*y;
    _T d=_T(0), dd=_T(0);
    for (std::size_t j=c.size()-1; j>0; --j) {
        _T sv=d;
        d = y2*d -dd + c[j];
        dd = sv;
    }
    _T fx=y*d-dd+_T(0.5)*c[0];
    return fx;
}

template <class _T>
cftal::test::chebyshev::poly_coefficents<_T>
cftal::test::chebyshev::to_polynomial(const coefficents<_T>& c)
{
    std::size_t n= c.size();
    std::vector<_T> dd(n, _T(0));
    poly_coefficents<_T> d(n, _T(0));
    
    _T sv;
    d[0]=c[n-1];
    for (std::size_t j=n-2; j>0; --j) {
        for (std::size_t k=n-j; k>0; --k) {
            sv=d[k];
            d[k]=_T(2.0)*d[k-1]-dd[k];
            dd[k]=sv;
        }
        sv=d[0];
        d[0] = -dd[0]+c[j];
        dd[0]=sv;
    }
    for (std::size_t j=n-1;j>0;--j) {
        d[j]=d[j-1]-dd[j];
    }
    d[0] = -dd[0]+0.5*c[0];
    return d;
}

template <class _T>
cftal::test::chebyshev::poly_coefficents<_T>
cftal::test::chebyshev::shift_to_interval(const poly_coefficents<_T>& c)
{
{
    std::size_t n= c.size();
    _T a= c._dom.first;
    _T b= c._dom.second;
    poly_coefficents d(c);
    _T cnst=2.0/(b-a);
    _T fac=cnst;
    for (std::size_t j=1;j<n; ++j) {
        d[j] *= fac;
        fac *= cnst;
    }
    cnst=0.5*(a+b);
    for (std::size_t j=0;j<=n-2; ++j) {
        for (std::size_t k=n-2;k>=j; --k) {
            d[k] -= cnst*d[k+1];
        }
    }
    return d;
}


// local variables:
// mode: c++
// end:
#endif
