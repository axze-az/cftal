#include <cftal/test/call_mpfr.h>
#include <cftal/test/of_fp_funcs.h>
#include <cmath>
#include <iostream>
#include <iomanip>
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


        struct out_df64 {
            d_real<double> _v;
            out_df64(const d_real<double>& v) : _v(v) {}
        };

        std::ostream& operator<<(std::ostream& s, const out_df64& v);

        struct out_tf64 {
            t_real<double> _v;
            out_tf64(const t_real<double>& v) : _v(v) {}
        };
        std::ostream& operator<<(std::ostream& s, const out_tf64& v);

        template <std::size_t _B>
        out_df64
        to_stream(d_real<double>& d, const mpfr_real<_B>& v,
                  bool normalize=false);

        template <std::size_t _B>
        out_tf64
        to_stream(t_real<double>& d, const mpfr_real<_B>& v,
                  bool normalize=false);

        template <std::size_t _B, typename _X>
        void
        gen_math_constants(std::ostream& s, const std::string& pfx);
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
    _T fl= call_mpfr::func(l, f);
    _T fr= call_mpfr::func(r, f);
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
        fn= call_mpfr::func(ln, f);
        bool is_inf = chk(fn);
        // std::cout << std::setw(30) << ln << '\r' << std::flush;
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
                    << call_mpfr::func(r, f)
                    << ";\n\n";
    } else {
        std::cout << std::scientific << std::setprecision(24)
                    << pfx << "_fin= "
                    << l
                    << ";\n"
                    << pfx << "_val= "
                    << call_mpfr::func(l, f)
                    << ";\n"
                    << pfx << '_' << check_name<< "= "
                    << r
                    << ";\n\n";
    }
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const out_df64& p)
{
    const cftal::d_real<double>& d=p._v;
    s << std::scientific
      << std::setprecision(22);
    if (d.h() >= 0.0)
        std::cout << ' ';
    s << std::setw(27)
      << d.h()
      << std::setw(0)
      << ", " ;
    if (d.l() >= 0.0)
        s << ' ';
    s << std::setw(27)
      << d.l()
      << std::setw(0);
    return s;
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const out_tf64& p)
{
    const cftal::t_real<double>& d=p._v;
    s << std::scientific
      << std::setprecision(22);
    if (d.h() >= 0.0)
        std::cout << ' ';
    s << std::setw(27)
      << d.h()
      << std::setw(0)
      << ", " ;
    if (d.m() >= 0.0)
        std::cout << ' ';
    s << std::setw(27)
      << d.m()
      << std::setw(0)
      << ", ";
    if (d.l() >= 0.0)
        std::cout << ' ';
    s << std::setw(27)
      << d.l()
      << std::setw(0);
    return s;
}

template <std::size_t _B>
cftal::test::out_df64
cftal::test::to_stream(d_real<double>& d, const mpfr_real<_B>& v,
                       bool normalize)
{
    d = d_real<double>(v);
    if (normalize) {
        double h=d.h(), l=d.l();
        if (h > 0) {
            while (l < 0.0) {
                // std::cout << h << std::endl;
                h = std::nextafter(h, -std::numeric_limits<double>::max());
                mpfr_real<_B> s(v);
                s -= mpfr_real<_B>(h);
                l = double(s);
            }
        } else if (h < 0) {
            while (l > 0.0) {
                h = std::nextafter(h, std::numeric_limits<double>::max());
                mpfr_real<_B> s(v);
                s -= mpfr_real<_B>(h);
                l = double(s);
            }
        }
        d=d_real<double>(h, l);
    }
    return out_df64(d);
}

template <std::size_t _B>
cftal::test::out_tf64
cftal::test::to_stream(t_real<double>& d, const mpfr_real<_B>& v,
                       bool normalize)
{
    d = t_real<double>(v);
    return out_tf64(d);
}

template <std::size_t _B, typename _X>
void
cftal::test::gen_math_constants(std::ostream& s, const std::string& pfx)
{
    using f_t = mpfr_real<_B>;
    _X d;

    // mpfr_set_default_prec(_B);

    f_t x=2.0;
    f_t v=log(x);
    // mpfr_printf("%.128Rf\n", v);
    s << "template <class _T>\nconst _T\n"
        << "cftal::math::impl::" << pfx << "::m_ln2("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;
    v= f_t(1.0)/v;
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::" << pfx << "::m_1_ln2("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;
    x = 10.0;
    v= log(x);
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::" << pfx << "::m_ln10("
        "\n\t"
              << to_stream(d, v, true)
              << ");\n"
              << std::endl;

    load_pi(x);
    v = x;
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::" << pfx << "::m_pi("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;
    v= f_t(2.0) *x;
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::" << pfx << "::m_pi2("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;
    v= x*f_t(0.5);
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::"<< pfx << "::m_pi_2("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;

    v=x*f_t(0.25);
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::" << pfx << "::m_pi_4("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;

    load_pi(x);
    v = f_t(1.0)/x;
    s << "template <class _T>\nconst _T\n"
     << "cftal::math::impl::" << pfx << "::m_1_pi("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;

    v = f_t(2.0)/x;
    s << "template <class _T>\nconst _T\n"
    << "cftal::math::impl::" << pfx << "::m_2_pi("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;

    v = f_t(4.0)/x;
    s << "template <class _T>\nconst _T\n"
        << "cftal::math::impl::" << pfx << "::m_4_pi("
        "\n\t"
              << to_stream(d, v)
              << ");\n"
              << std::endl;

    const std::size_t MAX_FAC=30;
    s << "template <class _T>\n"
              << "const _T\n"
              << "cftal::math::impl::" << pfx << "::\n"
              << "inv_fac[MAX_FAC+1]= {"
              << std::endl;

    f_t fac(1.0);
    for (std::size_t i=0; i<MAX_FAC+1; ++i) {
        f_t  inv_fac(1.0);
        if (i>1) {
            fac *= f_t(i);
            inv_fac /= fac;
        }
        s << std::setprecision(22)
                  << "\t_T( "
                  << to_stream(d, inv_fac)
                  << ")";
        if (i != MAX_FAC)
            s << ',';
        s << std::endl;
    }
    s << "};\n" << std::endl;

    const std::size_t MAX_2_OVER_I=30;
    s << "template <class _T>\n"
              << "const _T\n"
              << "cftal::math::impl::" << pfx << "::\n"
              << "_2_over_i[MAX_2_OVER_I+1]= {"
              << std::endl;
    for (std::size_t i=0; i<MAX_2_OVER_I+1; ++i) {
        f_t two_over_i(2.0);
        if (i>1) {
            two_over_i /= f_t(i);
        }
        s << std::scientific
                  << std::setprecision(22)
                  << "\t_T( "
                  << to_stream(d, two_over_i)
                  << ")";
        if (i != MAX_2_OVER_I)
            s << ',';
        s << std::endl;
    }
    s << "};\n" << std::endl;
}


int main()
{
    using namespace cftal;
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

    dp=std::make_pair(0.0, 1100.0);
    dm=std::make_pair(-1100.0, 0.0);
    gen_constant(dp, "const double exp2_hi", mpfr_exp2,  check_inf, "inf");
    gen_constant(dm, "const double exp2_lo", mpfr_exp2,  check_zero, "m_0");

    gen_constant(dp, "const double exp10_hi", mpfr_exp10,  check_inf, "inf");
    gen_constant(dm, "const double exp10_lo", mpfr_exp10,  check_zero, "m_0");

    gen_math_constants<128, d_real<double> >(std::cout,
                                             "d_real_constants<_T, double>");
    gen_math_constants<192, t_real<double> >(std::cout,
                                             "t_real_constants<_T, double>");
    return 0;
}
