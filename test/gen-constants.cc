#include <cftal/test/of_math_funcs.h>
#include <cmath>
#include <iostream>
#include <limits>


namespace cftal {
    namespace test {
        template <typename _T, typename _F, typename _C>
        void gen_constant(func_domain<_T> d, const std::string& pfx,
                          _F f, _C chk, const std::string& check_name);

        double check_inf(double a) {
            return std::isinf(a);
        }

        double check_zero(double a) {
            return a == 0.0;
        }

        double check_minus_one(double a ) {
            return a == -1.0;
        }
    }
}

template <typename _T, typename _F, typename _C>
void
cftal::test::gen_constant(func_domain<_T> d, const std::string& pfx,
                          _F f, _C chk, const std::string& check_name)
{
    _T l = d.first;
    _T r = d.second;
    // _T dir = std::numeric_limits<_T>::max();
    _T fl= call_mpfr_func(l, f);
    _T fr= call_mpfr_func(r, f);
    _T fn;

    bool l_is_inf= chk(fl);
    bool r_is_inf= chk(fr);

    if ((l_is_inf && r_is_inf) || (!l_is_inf && !r_is_inf)) {
        std::cerr << "invalid interval" << std::endl;
        return;
    }
    std::cout << std::setprecision(20) << std::scientific;
    while (l != r) {
        _T ln= (l+r)*0.5;
        if (ln == l || ln == r)
            break;
        fn= call_mpfr_func(ln, f);
        bool is_inf = chk(fn);
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
                    << pfx << '_' << check_name<< "= "
                    << l
                    << ";\n"
                    << pfx << "_fin= "
                    << r
                    << ";\n"
                    << pfx << "_val= "
                    << call_mpfr_func(r, f)
                    << ";\n\n";
    } else {
        std::cout << std::scientific << std::setprecision(24)
                    << pfx << "_fin= "
                    << l
                    << ";\n"
                    << pfx << "_val= "
                    << call_mpfr_func(l, f)
                    << ";\n"
                    << pfx << '_' << check_name<< "= "
                    << r
                    << ";\n\n";
    }
}

int main()
{
    using namespace cftal::test;
    auto dp=std::make_pair(0.0, 800.0);
    gen_constant(dp, "const double sinh_hi", mpfr_sinh, check_inf, "inf");
    auto dm=std::make_pair(-800.0, 0.0);
    gen_constant(dm, "const double sinh_lo", mpfr_sinh, check_inf, "inf");

    gen_constant(dp, "const double exp_hi", mpfr_exp,  check_inf, "inf");
    gen_constant(dm, "const double exp_lo", mpfr_exp,  check_zero, "m_0");

    gen_constant(dp, "const double expm1_hi", mpfr_expm1, check_inf, "inf");
    gen_constant(dm, "const double expm1_lo", mpfr_expm1, check_minus_one, "m_1");

    gen_constant(dp, "const double cosh_hi", mpfr_cosh, check_inf, "inf");
    gen_constant(dm, "const double cosh_lo", mpfr_cosh, check_inf, "inf");

    gen_constant(std::make_pair(.0, 0.001), "const double log_lo",
                 mpfr_log, check_inf, "inf");

    return 0;
}
