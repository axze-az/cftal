#include <cftal/test/chebyshev.h>
#include <cftal/test/of_fp_funcs.h>
#include <cmath>

namespace cftal {
    namespace test {
        template <class _T, class _F>
        chebyshev::poly_coefficients<_T>
        interpolate(const func_domain<_T>& d, std::size_t n, _F f);

    }
}

template <class _T, class _F>
cftal::test::chebyshev::poly_coefficients<_T>
cftal::test::interpolate(const func_domain<_T>& d, std::size_t n, _F f)
{
    chebyshev::coefficients<_T> c= chebyshev::interpolate(d, n, f);
    chebyshev::poly_coefficients<_T> p0= chebyshev::to_polynomial(c);
    chebyshev::poly_coefficients<_T> p=chebyshev::to_interval(p0);
    return p;
}

template <class _T>
struct calc_f {
    _T operator()(_T x) const {
        // return 1*x*x*x*x + 2*x*x*x + 3*x*x + 4*x +5;
        return std::sin(x);
    }
};

int main()
{
    using namespace cftal::test;
    auto pi=interpolate(std::make_pair(-M_PI, M_PI),
                        std::size_t(10), calc_f<double>());
    std::cout << chebyshev::poly_to_table(pi) << "\n";

    std::cout << chebyshev::poly_to_maxima(pi) << "\n";
    chebyshev::coefficients<double> c=
        chebyshev::interpolate(std::make_pair(-M_PI, M_PI),
                               std::size_t(10), calc_f<double>());
    for (const auto& a : c) {
        std::cout << pr_fp<double>(a) << std::endl;
    }
    return 0;
}
