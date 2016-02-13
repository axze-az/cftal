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

        template <typename _T>
        struct check_inf {
            bool operator()(_T a) const {
                return std::isinf(a);
            }
        };

        template <typename _T>
        struct check_zero {
            bool operator()(_T a) const {
                return a == 0.0;
            }
        };

        template <typename _T>
        struct check_minus_one {
            bool operator()(_T a) const {
                return a == -1.0;
            }
        };

        template <typename _T>
        struct check_max_denormal {
            bool operator() (_T a) const  {
                return false;
                // const double dbl_max_denormal= 2.225073858507200889024587e-308;
                // return std::fabs(a) <= dbl_max_denormal;
            }
        };

        template <>
        struct check_max_denormal<double> {
            bool operator() (double a) const  {
                const double dbl_max_denormal= 2.225073858507200889024587e-308;
                return std::fabs(a) <= dbl_max_denormal;
            }
        };


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

std::pair<std::uint64_t, std::uint64_t>
atan_coeff(int n)
{
    std::pair<std::uint64_t, std::uint64_t> r(1U, 1U);
    for (int i=1; i<=n; ++i) {
        // std::cout << 2*i << std::endl;
        r.first *= (2*i);
    }
    for (int i=1; i<=n; ++i) {
        // std::cout << 2*i+1 << std::endl;
        r.second *= (2*i+1);
    }
    return r;
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
    f_t ln2=v;
    // mpfr_printf("%.128Rf\n", v);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_ln2("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    v= f_t(1.0)/v;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_1_ln2("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    x = 10.0;
    v= log(x);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_ln10("
        "\n    "
      << to_stream(d, v, true)
      << ");\n"
      << std::endl;

    x = 0x1p106;
    v = log(x);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_ln2pow106("
        "\n    "
      << to_stream(d, v, true)
      << ");\n"
      << std::endl;

    load_pi(x);
    v = x;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_pi("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    v= f_t(2.0) *x;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_pi2("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    v= x*f_t(0.5);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::"<< pfx << "::m_pi_2("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;

    v=x*f_t(0.25);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_pi_4("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;

    load_pi(x);
    v = f_t(1.0)/x;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_1_pi("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;

    v = f_t(2.0)/x;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_2_pi("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;

    v = f_t(4.0)/x;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_4_pi("
        "\n    "
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
    f_t pot_ln2(1.0);
    std::vector<f_t> v_inv_fac;
    std::vector<f_t> v_pot_ln2;
    for (std::size_t i=0; i<MAX_FAC+1; ++i) {
        f_t inv_fac(1.0);
        if (i>1) {
            fac *= f_t(i);
            inv_fac /= fac;
            pot_ln2 *= ln2;
        }
        v_inv_fac.push_back(inv_fac);
        v_pot_ln2.push_back(pot_ln2);
        s << std::setprecision(22)
          << "    _T( "
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
          << "    _T( "
          << to_stream(d, two_over_i)
          << ")";
        if (i != MAX_2_OVER_I)
            s << ',';
        s << std::endl;
    }
    s << "};\n" << std::endl;

    // const std::size_t MAX_EXP_COEFF=10;
    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "exp_coeff[MAX_EXP_COEFF] =  {"
      << std::endl;
    for (std::size_t i=9; i!=0; --i) {
        f_t val= v_inv_fac[i];
        s << std::scientific
          << std::setprecision(22)
          << "    // + 1/" << i << "!\n"
          << "    _T( "
          << to_stream(d, val)
          << ")";
        if (i != 0)
            s << ',';
        s << '\n';
    }
    s << "};\n" << std::endl;

    // const std::size_t MAX_EXP2_COEFF=10;
    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "exp2_coeff[MAX_EXP2_COEFF] =  {"
      << std::endl;
    for (std::size_t i=9; i!=0; --i) {
        f_t eval= v_inv_fac[i];
        f_t f=v_pot_ln2[i+1];
        f_t val= eval*f;
        s << std::scientific
          << std::setprecision(22)
          << "    // + ln(2)^" <<i << "/"<< i << "!\n"
          << "    _T( "
          << to_stream(d, val)
          << ")";
        if (i != 0)
            s << ',';
        s << '\n';
    }
    s << "};\n" << std::endl;
    
    // const std::size_t MAX_COS_COEFF=10;
    // const std::size_t MAX_SIN_COEFF=10;

    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "sin_coeff[MAX_SIN_COEFF] =  {"
      << std::endl;
    int sign=1;
    for (std::size_t i=21; i>2; i-=2) {
        f_t val= v_inv_fac[i];
        if (sign < 0)
            val = -val;
        s << std::scientific
          << std::setprecision(22)
          << "    // " << (sign > 0? '+' : '-') << "1/" << i << "!\n"
          << "    _T( "
          << to_stream(d, val)
          << ")";
        if (i != 3)
            s << ',';
        s << '\n';
        sign = -sign;
    }
    s << "};\n" << std::endl;

    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "cos_coeff[MAX_COS_COEFF] =  {"
      << std::endl;
    sign=-1;
    for (std::size_t i=22; i>3; i-=2) {
        f_t val= v_inv_fac[i];
        if (sign < 0)
            val = -val;
        s << std::scientific
          << std::setprecision(22)
          << "    // " << (sign > 0? '+' : '-') << "1/" << i << "!\n"
          << "    _T( "
          << to_stream(d, val)
          << ")";
        if (i != 4)
            s << ',';
        s << '\n';
        sign = -sign;
    }
    s << "};\n" << std::endl;

    std::vector<f_t> v_atan_coeff;
    for (int i=0; i<20; ++i) {
        f_t e=1;
        f_t d=1;
        for (int j=1; j<=i; ++j) {
            e *= f_t(2*j);
        }
        for (int j=1; j<=i; ++j) {
            d *= f_t(2*j+1);
        }
        f_t q= e/d;
        v_atan_coeff.push_back(q);
    }
    
    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "atan2_coeff[MAX_ATAN2_COEFF] =  {"
      << std::endl;
    for (std::size_t i=0, j=v_atan_coeff.size()-1;
         i<v_atan_coeff.size(); ++i, --j) {
        f_t val= v_atan_coeff[j];
        s << std::scientific
          << std::setprecision(22)
          << "    // prod(even numbers to " << 2*j
          << ")/product(odd numbers to " << (2*j) +1 << ")\n"
          << "    _T( "
          << to_stream(d, val)
          << ")";
        if (i != v_atan_coeff.size()-1)
            s << ',';
        s << '\n';
    }
    s << "};\n" << std::endl;
}

int main(int argc, char** argv)
{
    bool gen_double=true;
    bool gen_float=true;
    if (argc > 1) {
        const std::string argv1=argv[1];
        if (argv1 == "--float") {
            gen_double =false;
        }
        if (argv1 == "--double") {
            gen_float= false;
        }
    }

    using namespace cftal;
    using namespace cftal::test;
    if (gen_double) {
        auto dp=std::make_pair(0.0, 800.0);
        gen_constant(dp, "const double sinh_hi", mpfr_sinh,
                     check_inf<double>(), "inf");
        auto dm=std::make_pair(-800.0, 0.0);
        gen_constant(dm, "const double sinh_lo", mpfr_sinh,
                     check_inf<double>(), "inf");
        // exp constants
        gen_constant(dp, "const double exp_hi", mpfr_exp,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double exp_lo", mpfr_exp,
                     check_zero<double>(), "m_0");
        gen_constant(dm, "const double exp_lo_den", mpfr_exp,
                     check_max_denormal<double>(), "nom");
        // exp1
        gen_constant(dp, "const double expm1_hi", mpfr_expm1,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double expm1_lo", mpfr_expm1,
                     check_minus_one<double>(), "m_1");

        gen_constant(dp, "const double cosh_hi", mpfr_cosh,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double cosh_lo", mpfr_cosh,
                     check_inf<double>(), "inf");

        gen_constant(std::make_pair(.0, 0.001), "const double log_lo",
                     mpfr_log, check_inf<double>(), "inf");

        dp=std::make_pair(0.0, 1100.0);
        dm=std::make_pair(-1100.0, 0.0);
        gen_constant(dp, "const double exp2_hi", mpfr_exp2,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double exp2_lo", mpfr_exp2,
                     check_zero<double>(), "m_0");

        gen_constant(dp, "const double exp10_hi", mpfr_exp10,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double exp10_lo", mpfr_exp10,
                     check_zero<double>(), "m_0");

        std::cout << "const double max_denormal= "
                  <<  sig_f64_msk::v._f64 << ";\n\n";
        std::cout << "const double _2pow106="
                  << 0x1p106 << ";\n\n";

        std::cout << "const double _2pow106="
                  << std::hexfloat
                  << std::ldexp(1.0, 106) << ";\n\n"
                  << std::scientific;

        gen_math_constants<128, d_real<double> >(
            std::cout,
            "d_real_constants<_T, double>");
        gen_math_constants<256, t_real<double> >(
            std::cout,
            "t_real_constants<_T, double>");
    }
    if (gen_float) {
        auto dp=std::make_pair(0.0f, 800.0f);
        gen_constant(dp, "const float sinh_hi", mpfr_sinh,
                     check_inf<float>(), "inf");
        auto dm=std::make_pair(-800.0f, 0.0f);
        gen_constant(dm, "const float sinh_lo", mpfr_sinh,
                     check_inf<float>(), "inf");
        // exp constants
        gen_constant(dp, "const float exp_hi", mpfr_exp,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float exp_lo", mpfr_exp,
                     check_zero<float>(), "m_0");
        gen_constant(dm, "const float exp_lo_den", mpfr_exp,
                     check_max_denormal<float>(), "nom");
        // exp1
        gen_constant(dp, "const float expm1_hi", mpfr_expm1,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float expm1_lo", mpfr_expm1,
                     check_minus_one<float>(), "m_1");

        gen_constant(dp, "const float cosh_hi", mpfr_cosh,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float cosh_lo", mpfr_cosh,
                     check_inf<float>(), "inf");

        gen_constant(std::make_pair(.0f, 0.001f), "const float log_lo",
                     mpfr_log, check_inf<float>(), "inf");

        dp=std::make_pair(0.0f, 1100.0f);
        dm=std::make_pair(-1100.0f, 0.0f);
        gen_constant(dp, "const float exp2_hi", mpfr_exp2,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float exp2_lo", mpfr_exp2,
                     check_zero<float>(), "m_0");

        gen_constant(dp, "const float exp10_hi", mpfr_exp10,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float exp10_lo", mpfr_exp10,
                     check_zero<float>(), "m_0");

        std::cout << "const float max_denormal= "
                  <<  sig_f32_msk::v._f32 << ";\n\n";
    }
    return 0;
}
