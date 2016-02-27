#include <cftal/test/call_mpfr.h>
#include <cftal/test/of_fp_funcs.h>
#include <cftal/math_func_f64.h>
#include <cftal/math_func_f32.h>
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
        void write_constant(const char* name_type, _T val);

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

        template <typename _T>
        struct check_atan_eq_x  {
            bool operator() (_T a) const {
                _T at=call_mpfr::func(a, mpfr_tan);
                return at == a;
            }
        };

        template <typename _T>
        struct out_prec { };

        template <>
        struct out_prec<double> {
            constexpr static const int val= 22;
            constexpr static const int width = 27;
            constexpr static const char* suffix() { return ""; }
        };

        template <>
        struct out_prec<float> {
            constexpr static const int val= 13;
            constexpr static const int width= 18;
            constexpr static const char* suffix() { return "f"; }
        };

        template <typename _T>
        struct out_df {
            d_real<_T> _v;
            out_df(const d_real<_T>& v) : _v(v) {}
        };
        template <typename _T>
        std::ostream&
        operator<<(std::ostream& s, const out_df<_T>& v);

        template <typename _T>
        struct out_tf {
            t_real<_T> _v;
            out_tf(const t_real<_T>& v) : _v(v) {}
        };
        template <typename _T>
        std::ostream& operator<<(std::ostream& s,
                                 const out_tf<_T>& v);

        template <typename _T, std::size_t _B>
        out_df<_T>
        to_stream(d_real<_T>& d, const mpfr_real<_B>& v,
                  bool normalize=false);

        template <typename _T, std::size_t _B>
        out_tf<_T>
        to_stream(t_real<_T>& d, const mpfr_real<_B>& v,
                  bool normalize=false);

        template <std::size_t _B, typename _X,
                  template <typename _Y, typename _T> class _C>
        void
        gen_math_constants(std::ostream& s, const std::string& pfx);

        template <std::size_t _N, std::size_t _B>
        void csplit(double (&r)[_N], const mpfr_real<_B>& v);

        template <std::size_t _N, std::size_t _B>
        void csplit(float (&r)[_N], const mpfr_real<_B>& v);
        
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

template <typename _T>
void
cftal::test::write_constant(const char* name_type, _T val)
{
    std::cout << name_type << "= "
              << std::scientific
              << std::setprecision(out_prec<_T>::val)
              << val
              << out_prec<_T>::suffix()
              << ";\n";
}


template <typename _T>
std::ostream&
cftal::test::operator<<(std::ostream& s, const out_df<_T>& p)
{
    const cftal::d_real<_T>& d=p._v;
    s << std::scientific
      << std::setprecision(out_prec<_T>::val);
    if (d.h() >= 0.0)
        std::cout << ' ';
    s << std::setw(out_prec<_T>::width)
      << d.h() << out_prec<_T>::suffix()
      << std::setw(0)
      << ", " ;
    if (d.l() >= 0.0)
        s << ' ';
    s << std::setw(out_prec<_T>::width)
      << d.l() << out_prec<_T>::suffix()
      << std::setw(0);
    return s;
}

template <typename _T>
std::ostream&
cftal::test::operator<<(std::ostream& s, const out_tf<_T>& p)
{
    const cftal::t_real<_T>& d=p._v;
    s << std::scientific
      << std::setprecision(out_prec<_T>::val);
    if (d.h() >= 0.0)
        std::cout << ' ';
    s << std::setw(out_prec<_T>::width)
      << d.h() << out_prec<_T>::suffix()
      << std::setw(0)
      << ", " ;
    if (d.m() >= 0.0)
        std::cout << ' ';
    s << std::setw(out_prec<_T>::width)
      << d.m() << out_prec<_T>::suffix()
      << std::setw(0)
      << ", ";
    if (d.l() >= 0.0)
        std::cout << ' ';
    s << std::setw(out_prec<_T>::width)
      << d.l() << out_prec<_T>::suffix()
      << std::setw(0);
    return s;
}

template <typename _T, std::size_t _B>
cftal::test::out_df<_T>
cftal::test::to_stream(d_real<_T>& d, const mpfr_real<_B>& v,
                       bool normalize)
{
    d = d_real<_T>(v);
    _T h=d.h(), l=d.l();
    if (normalize && ((h*l)<0.0)) {
        if (h > 0) {
            while (l < 0.0) {
                // std::cout << h << std::endl;
                h = std::nextafter(h, -std::numeric_limits<_T>::max());
                mpfr_real<_B> s(v);
                s -= mpfr_real<_B>(h);
                l = _T(s);
            }
        } else if (h < 0) {
            while (l > 0.0) {
                h = std::nextafter(h, std::numeric_limits<_T>::max());
                mpfr_real<_B> s(v);
                s -= mpfr_real<_B>(h);
                l = _T(s);
            }
        }
        d=d_real<_T>(h, l);
    }
    return out_df<_T>(d);
}

template <typename _T, std::size_t _B>
cftal::test::out_tf<_T>
cftal::test::to_stream(t_real<_T>& d, const mpfr_real<_B>& v,
                       bool normalize)
{
    d = t_real<_T>(v);
    return out_tf<_T>(d);
}

template <std::size_t _N, std::size_t _B>
void
cftal::test::csplit(double (&r)[_N], const mpfr_real<_B>& v)
{
    uint64_t msk=const_u64<0x00000000U, 0xfffffff0U>::v._u64;
    mpfr_real<_B> vv(v);
    for (std::size_t i=0; i<_N-1; ++i) {
        double t= double(vv);
        uint64_t u=as<uint64_t>(t);
        u &= msk;
        double tt=as<double>(u);
        r[i] = tt;
        vv -= mpfr_real<_B>(tt);
    }
    r[_N-1]= double(vv);
}

template <std::size_t _N, std::size_t _B>
void
cftal::test::csplit(float (&r)[_N], const mpfr_real<_B>& v)
{
    uint32_t msk=const_u32<0xffffc000U>::v._u32;
    mpfr_real<_B> vv(v);
    for (std::size_t i=0; i<_N-1; ++i) {
        float t= float(vv);
        uint32_t u=as<uint32_t>(t);
        u &= msk;
        float tt=as<float>(u);
        r[i] = tt;
        vv -= mpfr_real<_B>(tt);
    }
    r[_N-1]= float(vv);
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

template <std::size_t _B, typename _X,
          template <typename _Y, typename _T> class _C>
void
cftal::test::gen_math_constants(std::ostream& s, const std::string& pfx)
{
    using f_t = mpfr_real<_B>;
    using value_type = typename _X::value_type;
    using tbl_type = _C<_X, value_type>;

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
    v= f_t(1.0)/v;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_1_ln10("
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

    x = 0x1p48;
    v = log(x);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_ln2pow48("
        "\n    "
      << to_stream(d, v, true)
      << ");\n"
      << std::endl;

    x = std::numeric_limits<double>::max() ==
        std::numeric_limits<value_type>::max() ?
        0x1p106 : 0x1p48;
    v = log(x);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_ln_small_arg("
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


    const std::size_t MAX_FAC=tbl_type::MAX_FAC;
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

    const std::size_t MAX_2_OVER_I=tbl_type::MAX_2_OVER_I;
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

    const std::size_t MAX_LOG_COEFF=tbl_type::MAX_LOG_COEFF;
    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "log_coeff[MAX_LOG_COEFF]= {"
      << std::endl;
    for (std::size_t i=MAX_LOG_COEFF*2+1; i>2; i-=2) {
        f_t val(2.0);
        if (i!=1) {
            val /= f_t(i);
        }
        s << std::scientific
          << std::setprecision(22)
          << "    // + 2/" << i << "\n"
          << "    _T( "
          << to_stream(d, val)
          << ")";
        if (i != 3)
            s << ',';
        s << std::endl;
    }
    s << "};\n" << std::endl;

    const std::size_t MAX_EXP_COEFF=tbl_type::MAX_EXP_COEFF;
    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "exp_coeff[MAX_EXP_COEFF] =  {"
      << std::endl;
    for (std::size_t i=MAX_EXP_COEFF; i!=0; --i) {
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
    const std::size_t MAX_COS_COEFF=tbl_type::MAX_COS_COEFF;
    const std::size_t MAX_SIN_COEFF=tbl_type::MAX_SIN_COEFF;

    s << "template <class _T>\n"
      << "const _T\n"
      << "cftal::math::impl::" << pfx << "::\n"
      << "sin_coeff[MAX_SIN_COEFF] =  {"
      << std::endl;
    int sign= (MAX_SIN_COEFF & 2) ? 1 : -1;
    for (std::size_t i=MAX_SIN_COEFF*2+1; i>2; i-=2) {
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
    sign= (MAX_COS_COEFF & 2) ? -1 : 1;
    for (std::size_t i=MAX_COS_COEFF*2+2; i>3; i-=2) {
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

    const std::size_t MAX_ATAN2_COEFF=tbl_type::MAX_ATAN2_COEFF;
    std::vector<f_t> v_atan_coeff;
    for (std::size_t i=0; i<MAX_ATAN2_COEFF; ++i) {
        f_t e=1;
        f_t d=1;
        int ii=i;
        for (int j=1; j<=ii; ++j) {
            e *= f_t(2*j);
        }
        for (int j=1; j<=ii; ++j) {
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
    for (std::size_t i=0, j=MAX_ATAN2_COEFF-1;
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
        } else if (argv1 == "--no-float") {
            gen_float = false;
        } else if (argv1 == "--no-double") {
            gen_double = false;
        } else if (argv1 == "--double") {
            gen_float= false;
        }
    }

    using namespace cftal;
    using namespace cftal::test;
    using namespace cftal::math;
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
        write_constant(
            "const double exp_arg_large",
            std::floor(func_constants<double>::exp_hi_inf));
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

        // -1022 - 53
        write_constant(
            "const double log_arg_small", 0x1p-969);
        write_constant(
            "const double log_arg_small_factor",
            0x1p106);

        std::cout << "const double max_denormal= "
                  <<  sig_f64_msk::v._f64 << ";\n\n";
        std::cout << "const double _2pow106="
                  << 0x1p106 << ";\n\n";

        std::cout << "const double _2pow106="
                  << std::hexfloat
                  << std::ldexp(1.0, 106) << ";\n\n"
                  << std::scientific;

        dp = std::make_pair(0.0, 0.1);
        gen_constant(dm, "const double atan_eq_x", mpfr_atan,
                     check_atan_eq_x<double>(), "m_0");


        double a[2];
        mpfr_real<512> ln2=2.0;
        ln2=log(ln2);
        csplit(a, ln2);
        // std::cout << std::hexfloat;
        for (std::size_t i=0; i<2; ++i) {
            std::cout << "const double m_ln2_" << i << "= "
                      << a[i]
                      << ";\n";
        }

        std::cout << std::scientific<<'\n';
        
        gen_math_constants<128,
                           d_real<double>,
                           math::impl::d_real_constants >(
                               std::cout,
                               "d_real_constants<_T, double>");
        gen_math_constants<256, t_real<double>,
                           math::impl::t_real_constants>(
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
        write_constant(
            "const float exp_arg_large",
            std::floor(func_constants<float>::exp_hi_inf));
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

        // -126 + 24
        write_constant(
            "const double log_arg_small", 0x1p-102f);
        write_constant(
            "const double log_arg_small_factor",
            0x1p48f);

        std::cout << "const float max_denormal= "
                  <<  sig_f32_msk::v._f32 << ";\n\n";

        float a[2];
        mpfr_real<512> ln2=2.0;
        ln2=log(ln2);
        csplit(a, ln2);
        // std::cout << std::hexfloat;
        for (std::size_t i=0; i<2; ++i) {
            std::cout << "const float m_ln2_" << i << "= "
                      << a[i]
                      << "f;\n";
        }

        gen_math_constants<64,
                           d_real<float>,
                           math::impl::d_real_constants >(
                               std::cout,
                               "d_real_constants<_T, float>");

    }
    return 0;
}
