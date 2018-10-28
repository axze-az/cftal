//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cftal/test/call_mpfr.h>
#include <cftal/test/of_fp_funcs.h>
#include <cftal/test/pr_fp.h>
#include <cftal/math/elem_func_core_f64.h>
#include <cftal/math/elem_func_core_f32.h>
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
        struct check_one {
            bool operator()(_T a) const {
                return a == 1.0;
            }
        };

        template <typename _T>
        struct check_pi_half {
            bool operator()(_T a) const {
                return a == _T(M_PI_2);
            }
        };

        template <typename _T>
        struct check_max_denormal {
            bool operator() (_T a) const  {
                return false;
            }
        };

        template <>
        struct check_max_denormal<double> {
            bool operator() (double a) const  {
                const double dbl_max_denormal= 2.225073858507200889024587e-308;
                return std::fabs(a) <= dbl_max_denormal;
            }
        };

        template <>
        struct check_max_denormal<float> {
            bool operator() (float a) const  {
                const float flt_max_denormal= 1.175494210692441075487029e-38;
                return std::fabs(a) <= flt_max_denormal;
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
        struct out_df {
            d_real<_T> _v;
            explicit
            out_df(const d_real<_T>& v) : _v(v) {}
        };
        template <typename _T>
        std::ostream&
        operator<<(std::ostream& s, const out_df<_T>& v);

        template <typename _T>
        struct out_tf {
            t_real<_T> _v;
            explicit
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
        void csplit(double (&r)[_N], const mpfr_real<_B>& v,
                    std::size_t low_bits_to_clear);

        template <std::size_t _N, std::size_t _B>
        void csplit(float (&r)[_N], const mpfr_real<_B>& v,
                    std::size_t low_bits_to_clear);


        template <typename _T, std::size_t _N, std::size_t _B>
        void
        create_expansion(_T (&r)[_N], const mpfr_real<_B>& v);

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
cftal::test::operator<<(std::ostream& s, const out_df<_T>& v)
{
    const cftal::d_real<_T>& d=v._v;
    s << pr_fp<_T>(d[0])
      << std::setw(0)
      << ", " ;
    s << pr_fp<_T>(d[1])
      << std::setw(0);
    return s;
}

template <typename _T>
std::ostream&
cftal::test::operator<<(std::ostream& s, const out_tf<_T>& v)
{
    const cftal::t_real<_T>& d=v._v;
    s << pr_fp<_T>(d[0])
      << std::setw(0)
      << ", " ;
    s << pr_fp<_T>(d[1])
      << std::setw(0)
      << ", ";
    s << pr_fp<_T>(d[2])
      << std::setw(0);
    return s;
}

template <typename _T, std::size_t _B>
cftal::test::out_df<_T>
cftal::test::to_stream(d_real<_T>& d, const mpfr_real<_B>& v,
                       bool normalize)
{
    d = d_real<_T>(v);
    _T h=d[0], l=d[1];
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
cftal::test::csplit(double (&r)[_N], const mpfr_real<_B>& v,
                    std::size_t low_bits_to_clear)
{
    // uint64_t msk=const_u64<0xffe00000U, 0xffffffffU>::v.u64();
    uint64_t msk = const_u64<uint32_t(-1), uint32_t(-1)>::v.u64() <<
        low_bits_to_clear;
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
cftal::test::csplit(float (&r)[_N], const mpfr_real<_B>& v,
                    std::size_t low_bits_to_clear)
{
    // uint32_t msk=const_u32<0xfffffE00U>::v.u32();
    uint32_t msk=const_u32<0xffffffffU>::v.u32() << low_bits_to_clear;
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

template <typename _T, std::size_t _N, std::size_t _B>
void
cftal::test::create_expansion(_T (&r)[_N], const mpfr_real<_B>& v)
{
    mpfr_real<_B> vv(v);
    for (std::size_t i=0; i<_N-1; ++i) {
        _T t= _T(vv);
        r[i]= t;
        vv -= mpfr_real<_B>(t);
    }
    r[_N-1]= _T(vv);
}

#if 0
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
#endif

template <std::size_t _B, typename _X,
          template <typename _Y, typename _T> class _C>
void
cftal::test::gen_math_constants(std::ostream& s, const std::string& pfx)
{
    using f_t = mpfr_real<_B>;
    using value_type = typename _X::value_type;

    _X d;

    bool is_double = std::numeric_limits<double>::max() ==
        std::numeric_limits<value_type>::max();

    std::size_t low_bits_to_clear= is_double ? 21 : 9;
    // mpfr_set_default_prec(_B);
    f_t v, x;

    const int ln2_bits=2;
    value_type ln2_cw[ln2_bits];
    x=2.0;
    v=log(x);
    csplit(ln2_cw, v, low_bits_to_clear);
    s << "template <class _T>\nconst " << (is_double ? "double" : "float")
      << "\n"
      << "cftal::math::impl::" << pfx << "::\nm_ln2_cw["
      << ln2_bits << "]={\n";
    for (std::size_t i=0; i< ln2_bits; ++i) {
        s << "   " << pr_fp<value_type>(ln2_cw[i]);
        if (i != ln2_bits-1)
            s << ',';
        s << "\n";
    }
    s << "};\n\n";

    const int ld2_bits=2;
    value_type ld2_cw[ld2_bits];
    x=2.0;
    v=log10(x);
    low_bits_to_clear = is_double ? 21 : 9;
    csplit(ld2_cw, v, low_bits_to_clear);
    s << "template <class _T>\nconst " << (is_double ? "double" : "float")
      << "\n"
      << "cftal::math::impl::" << pfx << "::\nm_ld2_cw["
      << ld2_bits << "]={\n";
    for (std::size_t i=0; i< ld2_bits; ++i) {
        s << "   " << pr_fp<value_type>(ld2_cw[i]);
        if (i != ld2_bits-1)
            s << ',';
        s << "\n";
    }
    s << "};\n\n";

    x=0.5;
    load_pi(v);
    v *= x;
    const int pi_2_bits=3;
    value_type pi_2_cw[pi_2_bits];
    low_bits_to_clear = is_double ? 21 : 9;
    csplit(pi_2_cw, v, low_bits_to_clear);
    s << "template <class _T>\nconst " << (is_double ? "double" : "float")
      << "\n"
      << "cftal::math::impl::" << pfx << "::\nm_pi_2_cw["
      << pi_2_bits << "]={\n";
    for (std::size_t i=0; i< pi_2_bits; ++i) {
        s << "   " << pr_fp<value_type>(pi_2_cw[i]);
        if (i != pi_2_bits-1)
            s << ',';
        s << "\n";
    }
    s << "};\n\n";


    // ln(2) and reciprocal
    x=2.0;
    v=log(x);
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
    // ld(2) and reciprocal
    x=2.0;
    v=log10(x);
    f_t ld2=v;
    // mpfr_printf("%.128Rf\n", v);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_lg2("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    v= f_t(1.0)/v;
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_1_lg2("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    // ln(10) and reciprocal
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

    x = is_double ? 0x1p106 : 0x1p48;
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

    v = log(x);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_ln_pi("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;

    v= exp(f_t(0.75))/f_t(2.0)-f_t(1.0);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_exp_3_4_m_1("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
    v= exp(f_t(-0.75))/f_t(2.0);
    s << "template <class _T>\nconst _T\n"
      << "cftal::math::impl::" << pfx << "::m_1_exp_3_4("
        "\n    "
      << to_stream(d, v)
      << ");\n"
      << std::endl;
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
        // expm1
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
        gen_constant(dm, "const double exp2_lo_den", mpfr_exp2,
                     check_max_denormal<double>(), "nom");

        // exp2m1
        gen_constant(dp, "const double exp2m1_hi", mpfr_ext::exp2m1,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double exp2m1_lo", mpfr_ext::exp2m1,
                     check_minus_one<double>(), "m_1");

        // exp10
        gen_constant(dp, "const double exp10_hi", mpfr_exp10,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double exp10_lo", mpfr_exp10,
                     check_zero<double>(), "m_0");
        gen_constant(dm, "const double exp10_lo_den", mpfr_exp10,
                     check_max_denormal<double>(), "nom");
        // exp10m1
        gen_constant(dp, "const double exp10m1_hi", mpfr_ext::exp10m1,
                     check_inf<double>(), "inf");
        gen_constant(dm, "const double exp10m1_lo", mpfr_ext::exp10m1,
                     check_minus_one<double>(), "m_1");

        gen_constant(dp, "const double erf_lt_one", mpfr_erf,
                     check_one<double>(), "1");
        gen_constant(dp, "const double erfc_gt_zero", mpfr_erfc,
                     check_zero<double>(), "zzz");
        gen_constant(dp, "const double erfc_lo_den", mpfr_erfc,
                     check_max_denormal<double>(), "nom");

        // tgamma
        auto gp=std::make_pair(10.0, 1100.0);
        gen_constant(gp, "const double tgamma_hi", mpfr_gamma,
                     check_inf<double>(), "inf");

        auto gm=std::make_pair(-178.0+0x1p-50,
                               -177.0-0x1p-50);
        gen_constant(gm, "const double tgamma_gt_zero", mpfr_gamma,
                     check_zero<double>(), "m_0");

        // lgamma
        auto lngp=std::make_pair(174.0, std::numeric_limits<double>::max());
        gen_constant(lngp, "const double lgamma_hi", mpfr_lngamma,
                     check_inf<double>(), "inf");

        dp=std::make_pair(1.0, std::numeric_limits<double>::max());
        gen_constant(dp, "const double rqsrt_", mpfr_rec_sqrt,
                     check_zero<double>(), "zero");

        dp=std::make_pair(1.0, std::numeric_limits<double>::max());
        gen_constant(dp, "const double atan_pi_2", mpfr_atan,
                     check_pi_half<double>(), "equal");

        std::cout << "const double max_denormal= "
                  <<  sig_f64_msk::v.f64() << ";\n\n";
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
        csplit(a, ln2, 21);
        // std::cout << std::hexfloat;
        for (std::size_t i=0; i<2; ++i) {
            std::cout << "const double m_ln2_" << i << "= "
                      << a[i]
                      << ";\n";
        }

        std::cout << std::scientific<<'\n';

        gen_math_constants<256,
                           d_real<double>,
                           math::impl::d_real_constants >(
                               std::cout,
                               "d_real_constants<_T, double>");
        gen_math_constants<512, t_real<double>,
                           math::impl::t_real_constants>(
                               std::cout,
                               "t_real_constants<_T, double>");
    }
    if (gen_float) {
        auto dp=std::make_pair(0.0f, 200.0f);
        gen_constant(dp, "const float sinh_hi", mpfr_sinh,
                     check_inf<float>(), "inf");
        auto dm=std::make_pair(-200.0f, 0.0f);
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
        // exp2m1
        gen_constant(dp, "const float exp2m1_hi", mpfr_ext::exp2m1,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float exp2m1_lo", mpfr_ext::exp2m1,
                     check_minus_one<float>(), "m_1");

        // exp10
        gen_constant(dp, "const float exp10_hi", mpfr_exp10,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float exp10_lo", mpfr_exp10,
                     check_zero<float>(), "m_0");

        // exp10m1
        gen_constant(dp, "const float exp10m1_hi", mpfr_ext::exp10m1,
                     check_inf<float>(), "inf");
        gen_constant(dm, "const float exp10m1_lo", mpfr_ext::exp10m1,
                     check_minus_one<float>(), "m_1");

        gen_constant(dp, "const float erf_lt_one", mpfr_erf,
                     check_one<float>(), "1");
        gen_constant(dp, "const float erfc_gt_zero", mpfr_erfc,
                     check_zero<float>(), "zzz");
        gen_constant(dp, "const float erfc_lo_den", mpfr_erfc,
                     check_max_denormal<float>(), "nom");
        // tgamma
        auto gm=std::make_pair(10.0f, 200.0f);
        gen_constant(gm, "const float tgamma_hi", mpfr_gamma,
                     check_inf<float>(), "inf");

        dp=std::make_pair(1.0f, std::numeric_limits<float>::max());
        gen_constant(dp, "const float rqsrt_", mpfr_rec_sqrt,
                     check_zero<double>(), "zero");

        // lgamma
        auto lngp=std::make_pair(174.0f, std::numeric_limits<float>::max());
        gen_constant(lngp, "const float lgamma_hi", mpfr_lngamma,
                     check_inf<float>(), "inf");

        dp=std::make_pair(1.0f, std::numeric_limits<float>::max());
        gen_constant(dp, "const double atan_pi_2", mpfr_atan,
                     check_pi_half<float>(), "equal");

        std::cout << "const float max_denormal= "
                  <<  sig_f32_msk::v.f32() << ";\n\n";

        float a[2];
        mpfr_real<512> ln2=2.0;
        ln2=log(ln2);
        csplit(a, ln2, 9);
        // std::cout << std::hexfloat;
        for (std::size_t i=0; i<2; ++i) {
            std::cout << "const float m_ln2_" << i << "= "
                      << a[i]
                      << "f;\n";
        }

        gen_math_constants<128,
                           d_real<float>,
                           math::impl::d_real_constants >(
                               std::cout,
                               "d_real_constants<_T, float>");
        gen_math_constants<256,
                           t_real<float>,
                           math::impl::t_real_constants >(
                               std::cout,
                               "t_real_constants<_T, float>");

    }
    return 0;
}
