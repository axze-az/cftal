#include <cftal/test/of_math_funcs.h>
#include <cmath>
#include <iostream>
#include <limits>


namespace cftal {
    namespace test {
        template <typename _T, typename _F>
        void gen_constant(func_domain<_T> d, const char* pfx);
    }
}

template <typename _T, typename _F>
void
cftal::test::gen_constant(func_domain<_T> d, const char* pfx)
{
    _T l = d.first;
    _T r = d.second;
    // _T dir = std::numeric_limits<_T>::max();
    _T fl= _F::v(l);
    _T fh= _F::v(r);
    _T fn;

    bool l_is_inf= std::isinf(fl);
    bool r_is_inf= std::isinf(fh);

    if ((l_is_inf && r_is_inf) || (!l_is_inf && !r_is_inf)) {
        std::cerr << "invalid interval" << std::endl;
        return;
    }
    std::cout << std::setprecision(20) << std::scientific;
    while (l != r) {
        _T ln= (l+r)*0.5;
        if (ln == l || ln == r)
            break;
        fn= _F::v(ln);
        bool is_inf = std::isinf(fn);
        std::cout << std::setw(30) << ln << '\r' << std::flush;
        if (l_is_inf) {
            if (is_inf == true) {
                l = ln;
            } else {
                r = ln;
            }
        } else {
            if (is_inf == true) {
                r = ln;
            } else {
                l = ln;
            }
        }
    }

    if (l_is_inf) {
        std::cout << std::scientific << std::setprecision(24)
                    << pfx << "_inf= "
                    << l
                    << ";\n"
                    << pfx << "_fin= "
                    << r
                    << ";\n"
                    << pfx << "_val= "
                    << _F::v(r)
                    << ";\n\n";
    } else {
        std::cout << std::scientific << std::setprecision(24)
                    << pfx << "_fin= "
                    << l
                    << ";\n"
                    << pfx << "_val= "
                    << _F::v(l)
                    << ";\n"
                    << pfx << "_inf= "
                    << r
                    << ";\n\n";
    }
}

int main()
{
    using namespace cftal::test;
    auto dp=std::make_pair(0, 800);
    gen_constant<double, check_sinh<double> >(dp, "const double sinh_hi");
    auto dm=std::make_pair(-800, 0);
    gen_constant<double, check_sinh<double> >(dm, "const double sinh_lo");

    gen_constant<double, check_exp<double> >(dp, "const double exp_hi");
    gen_constant<double, check_expm1<double> >(dp, "const double expm1_hi");

    gen_constant<double, check_sinh<double> >(dp, "const double cosh_hi");
    gen_constant<double, check_sinh<double> >(dm, "const double cosh_lo");

    gen_constant<double, check_log<double> >(std::make_pair(.0, 0.001),
                                             "const double log_lo");

    return 0;
}
