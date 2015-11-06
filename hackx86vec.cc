#include <cftal/vec.h>
#include <cftal/d_int.h>
#include <cftal/d_real.h>
#include <cftal/mul_div.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/vec_traits.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstddef>

namespace cftal {
    namespace test {

        double make_double(unsigned sgn, unsigned exp, uint64_t sig);

    }

    vec<double, 4>
    test_merge(const vec<double, 4>& a, const vec<double, 4>& b);

    vec<float, 4>
    test_merge(const vec<float, 4>& a, const vec<float, 4>& b);
}

cftal::vec<double, 4>
cftal::test_merge(const vec<double, 4>& a, const vec<double, 4>& b)
{
    vec<double, 4>::mask_type a_gt_b = a > b;
    vec<double, 4> r=a;
    zero(r).update_if(a_gt_b).with = a + b * b * b + a;

    return r;
}

cftal::vec<float, 4>
cftal::test_merge(const vec<float, 4>& a, const vec<float, 4>& b)
{
    vec<float, 4>::mask_type a_gt_b = a > b;
    vec<float, 4> r=a;
    zero(r).update_if(a_gt_b).with = a + b * b * b + a;

    return r;
}


double
cftal::test::make_double(unsigned sgn, unsigned exp, uint64_t sig)
{
    uint64_t _sgn= uint64_t(sgn & 1) << 63;
    uint64_t _exp= uint64_t(exp & 0x7FF) << 52;
    uint64_t _sig= sig & 0x000fffffffffffffULL;
    union {
        uint64_t _u;
        double _d;
    } t;
    t._u = _sgn | _exp | _sig;
    return t._d;
}



//namespace vec=x86vec;
//namespace vec=emuvec;

cftal::v4f64::mask_type
test_inf(cftal::v4f64 a)
{
    return isinf(a);
}

cftal::v2f64::mask_type
test_inf(cftal::v2f64 a)
{
    return isinf(a);
}

cftal::v4f64::mask_type
test_nan(cftal::v4f64 a)
{
    return isnan(a);
}

cftal::v2f64::mask_type
test_nan(cftal::v2f64 a)
{
    return isnan(a);
}


// v4f64 compile tests
cftal::v4f64 test1a(cftal::v4f64 a, cftal::v4f64 b, cftal::v4f64 c)
{
    return a*b + c;
}

cftal::v4f64 test1b(cftal::v4f64 a, cftal::v4f64 b, cftal::v4f64 c)
{
    return c+ a*b;
}

cftal::v4f64 test1c(cftal::v4f64 a, cftal::v4f64 b, cftal::v4f64 c)
{
    return a*b - c;
}

cftal::v4f64 test1d(cftal::v4f64 a, cftal::v4f64 b, cftal::v4f64 c)
{
    return c- a*b;
}

cftal::v4f64 test2a(cftal::v4f64 a, cftal::v4f64 b,
                    cftal::v4f64 c, cftal::v4f64 d)
{
    return a*b + c*d;
}

cftal::v4f64 test2b(cftal::v4f64 a, cftal::v4f64 b,
                    cftal::v4f64 c, cftal::v4f64 d)
{
    return a*b - c*d;
}

cftal::v4f64 test2c(cftal::v4f64 a, cftal::v4f64 b,
                    cftal::v4f64 c, cftal::v4f64 d)
{
    return (a*b + c) * d;
}

cftal::v4f64 test2d(cftal::v4f64 a, cftal::v4f64 b,
                    cftal::v4f64 c, cftal::v4f64 d)
{
    return (a*b - c) * d;
}

cftal::v4f64 test3a(cftal::v4f64 a, cftal::v4f64 b,
                    cftal::v4f64 c, cftal::v4f64 d)
{
    return 1.0 + a * b + 1.0 + c * d;
}

// v8f64 compile tests
cftal::v8f64 test1a(cftal::v8f64 a, cftal::v8f64 b, cftal::v8f64 c)
{
    return a*b + c;
}

cftal::v8f64 test1b(cftal::v8f64 a, cftal::v8f64 b, cftal::v8f64 c)
{
    return c+ a*b;
}

cftal::v8f64 test1c(cftal::v8f64 a, cftal::v8f64 b, cftal::v8f64 c)
{
    return a*b - c;
}

cftal::v8f64 test1d(cftal::v8f64 a, cftal::v8f64 b, cftal::v8f64 c)
{
    return c- a*b;
}

cftal::v8f64 test2a(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return a*b + c*d;
}

cftal::v8f64 test2b(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return a*b - c*d;
}

cftal::v8f64 test2c(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return (a*b + c) * d;
}

cftal::v8f64 test2d(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return (a*b - c) * d;
}

cftal::v8f64 test3a(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return 1.0 + a * b + 1.0 + c * d;
}

cftal::v8f64 test3b(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return (1.0 + a * b) + (1.0 + c * d);
}

cftal::v8f64::mask_type
test_cmp(cftal::v8f64 a, cftal::v8f64 b)
{
    // cftal::v8f64::mask_type c1 = a == b;
    // cftal::v8f64::mask_type c2 = a == b;

    return (a == b) | (a > b);
}


cftal::v8f64 test4a(cftal::v8f64 a, cftal::v8f64 b,
                    cftal::v8f64 c, cftal::v8f64 d)
{
    return (1.0+a*b) * (a*b + a*c + a*d + b* c + b* d +
                        c * d);
}

cftal::v4s32 test_as(cftal::v4f32 a)
{
    return cftal::as<cftal::v4s32>(a);
}

cftal::v4f32 test_as(cftal::v4s32 a)
{
    return cftal::as<cftal::v4f32>(a);
}


cftal::v8s32 test_as(cftal::v8f32 a)
{
    return cftal::as<cftal::v8s32>(a);
}

cftal::v8f32 test_as(cftal::v8s32 a)
{
    return cftal::as<cftal::v8f32>(a);
}

#if defined (__x86_64__)
cftal::uint32_t
test_read_signs(cftal::v8s16 a)
{
    return cftal::x86::read_signs_s16(a());
}

cftal::uint32_t
test_read_signs(cftal::v4s32 a)
{
    return cftal::x86::read_signs_s32(a());
}

cftal::uint32_t
test_read_signs(cftal::v2s64 a)
{
    return cftal::x86::read_signs_s64(a());
}
#endif


struct print_dpf64 {
    const cftal::d_real<double> _f;
	explicit
    print_dpf64(const cftal::d_real<double>& f) : _f(f) {}
};

std::ostream& operator<<(std::ostream& s, const print_dpf64& p)
{
    const cftal::d_real<double>& d=p._f;
    s << std::scientific
      << std::setprecision(22);
    if (d.h() >= 0.0)
        std::cout << ' ';
    s << std::setw(27)
      << d.h()
      << std::setw(0)
      << ", " ;
    if (d.l() >= 0.0)
        std::cout << ' ';
    std::cout << std::setw(27)
              << d.l()
              << std::setw(0);
    return s;
}

#if defined (__GNUC__) && !defined (__clang__) && defined (__x86_64__)
#include <quadmath.h>

struct out_as_dpf64 {
    double _h, _l;
    out_as_dpf64(const __float128& t) : _h(t), _l(t-_h) {
    }
};

std::ostream& operator<<(std::ostream& s, const out_as_dpf64& p)
{
    cftal::d_real<double> t(p._h, p._l);
    print_dpf64 o(t);
    s << o;
    return s;
}

void calc_pi()
{
#if 1
    __float128 v;

    v= M_LN2q;
    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_ln2("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;

    v= M_PIq;
    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_pi("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;

    v=M_PI_2q;
    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_pi_2("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;

    v=M_PI_4q;
    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_pi_4("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;


    v = M_1_PIq;
    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_1_pi("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;

    v = M_2_PIq;

    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_2_pi("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;

    v = M_2_PIq * 0.5;

    std::cout << "cftal::math::impl::d_real_constants<_T, double>::m_4_pi("
        "\n\t"
              << out_as_dpf64(v)
              << ");"
              << std::endl;

#else
    using dpf64 = cftal::d_real<double>;
    // arctan(x) = x/1 - {x^3}/3 + x^5/5
    // arctan(1) = PI/4
    dpf64 pi(0);
    double pi_d(0);
    for (std::int64_t i=100000000; i>=0 ; --i) {
        const std::int64_t i0=2*i+2;
        dpf64 t0(i0);
        dpf64 t1(t0+1.0);
        dpf64 t2(t0+2.0);
        dpf64 p(t0*t1*t2);
        dpf64 rp(1.0/p);
        if ((i&1)==0) {
            // std::cout << i0 << std::endl;
            pi += rp;
        } else {
            // std::cout << -i0 << std::endl;
            pi -= rp;
        }
        // std::cout << pi.h() << ' ' << pi.l() << std::endl;
    }
    pi *= 4.0;
    pi += 3.0;
    std::cout << std::scientific
              << std::setprecision(18)
              << pi.h()
              << ' '
              << pi.l()
              << std::endl
              << pi_d
              << std::endl;
#endif
}

#endif


void print_inv_fac()
{
    using dpf64 = cftal::d_real<double>;

    dpf64 fac(1.0);
    std::vector<dpf64> v;

    const std::size_t MAX_FAC=30;

    std::cout << "template <class _T>\n"
              << "const _T\n"
              << "cftal::impl::d_real_constants_dbl<_T>::\n"
              << "inv_fac[MAX_FAC+1]= {"
              << std::endl;
    for (std::size_t i=0; i<MAX_FAC+1; ++i) {
        dpf64  inv_fac(1.0);
        if (i>1) {
            fac *= double(i);
            inv_fac /= fac;
        }
        v.push_back(inv_fac);
        std::cout << std::scientific
                  << std::setprecision(22)
                  << "\t_T( "
                  << print_dpf64(inv_fac)
                  << ")";
        if (i != MAX_FAC)
            std::cout << ',';
        std::cout << std::endl;
    }
    std::cout << "};" << std::endl;

    // parameters for sin
    std::cout << "template <typename _T>" << std::endl
              << "const " << std::endl
              << "typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type" << std::endl
              << "cftal::math::func<double, cftal::int32_t, _T>::m_sin_c_k2[]= {" << std::endl;

    std::cout << "\t// +1/21!\n"
              << "\tdvf_type( " << print_dpf64(v[21]) <<"),\n";

    std::cout << "\t// -1/19!\n"
              << "\tdvf_type( " << print_dpf64(-v[19]) <<"),\n";

    std::cout << "\t// +1/17!\n"
              << "\tdvf_type( " << print_dpf64(v[17]) <<"),\n";

    std::cout << "\t// -1/15!\n"
              << "\tdvf_type( " << print_dpf64(-v[15]) <<"),\n";

    std::cout << "\t// +1/13!\n"
              << "\tdvf_type( " << print_dpf64(v[13]) <<"),\n";

    std::cout << "\t// -1/11!\n"
              << "\tdvf_type( " << print_dpf64(-v[11]) <<"),\n";

    std::cout << "\t// +1/9!\n"
              << "\tdvf_type( " << print_dpf64(v[9]) <<"),\n";

    std::cout << "\t// -1/7!\n"
              << "\tdvf_type( " << print_dpf64(-v[7]) <<"),\n";

    std::cout << "\t// +1/5!\n"
              << "\tdvf_type( " << print_dpf64(v[5]) <<"),\n";

    std::cout << "\t// -1/3!\n"
              << "\tdvf_type( " << print_dpf64(-v[3]) <<")\n};\n\n";

    // parameters for cos
    std::cout << "template <typename _T>" << std::endl
              << "const " << std::endl
              << "typename cftal::math::func<double, cftal::int32_t, _T>::dvf_type" << std::endl
              << "cftal::math::func<double, cftal::int32_t, _T>::m_cos_c_k2[]= {" << std::endl;

    std::cout << "\t// -1/22!\n"
              << "\tdvf_type( " << print_dpf64(-v[22]) <<"),\n";

    std::cout << "\t// +1/20!\n"
              << "\tdvf_type( " << print_dpf64(v[20]) <<"),\n";

    std::cout << "\t// -1/18!\n"
              << "\tdvf_type( " << print_dpf64(-v[18]) <<"),\n";

    std::cout << "\t// +1/16!\n"
              << "\tdvf_type( " << print_dpf64(v[16]) <<"),\n";

    std::cout << "\t// -1/14!\n"
              << "\tdvf_type( " << print_dpf64(-v[14]) <<"),\n";

    std::cout << "\t// +1/12!\n"
              << "\tdvf_type( " << print_dpf64(v[12]) <<"),\n";

    std::cout << "\t// -1/10!\n"
              << "\tdvf_type( " << print_dpf64(-v[10]) <<"),\n";

    std::cout << "\t// +1/8!\n"
              << "\tdvf_type( " << print_dpf64(v[8]) <<"),\n";

    std::cout << "\t// -1/6!\n"
              << "\tdvf_type( " << print_dpf64(-v[6]) <<"),\n";

    std::cout << "\t// +1/4!\n"
              << "\tdvf_type( " << print_dpf64(v[4]) <<")\n};\n\n";
    // parameters for exp
}

void print_2_over_i()
{
    using dpf64 = cftal::d_real<double>;

    const std::size_t MAX_2_OVER_I=30;

    std::cout << "template <class _T>\n"
              << "const _T\n"
              << "cftal::impl::d_real_constants_dbl<_T>::\n"
              << "_2_over_i[MAX_2_OVER_I]= {"
              << std::endl;
    for (std::size_t i=0; i<MAX_2_OVER_I; ++i) {
        dpf64 two_over_i(2.0);
        if (i>1) {
            two_over_i /= double(i);
        }
        std::cout << std::scientific
                  << std::setprecision(22)
                  << "\t_T( "
                  << std::setw(27)
                  << two_over_i.h()
                  << std::setw(0)
                  << ", " ;
        if (two_over_i.l() >= 0.0)
            std::cout << ' ';
        std::cout << std::setw(27)
                  << two_over_i.l()
                  << std::setw(0)
                  << ")";
        if (i != MAX_2_OVER_I)
            std::cout << ',';
        std::cout << std::endl;
    }
    std::cout << "};" << std::endl;
}

void print_sqrtx()
{
    using dpf64 = cftal::d_real<double>;
    dpf64 sqrt12(sqrt(dpf64(0.5)));
    std::cout << "template <class _T>\n"
              << "const _T\n"
              << "cftal::impl::d_real_constants_dbl<_T>::\n"
              << "m_sqrt1_2("
              << std::endl;
    std::cout << std::scientific
              << std::setprecision(22)
              << "\t_T( "
              << std::setw(27)
              << sqrt12.h()
              << std::setw(0)
              << ", " ;
    if (sqrt12.l() >= 0.0)
        std::cout << ' ';
    std::cout << std::scientific
              << std::setprecision(22)
              << std::setw(27)
              << sqrt12.l()
              << std::setw(0)
              << ");";
    std::cout << std::endl;

#if defined (__GNUC__) && !defined (__clang__) && defined(__x86_64__)
    __float128 t2= __builtin_sqrtl(__float128(0.5));
    std::cout << std::setprecision(22)
              << double(t2)
              << ' '
              << double(t2 - double(t2))
              << std::endl;
#endif
}


void testpowi()
{
    using dpf64 = cftal::d_real<double>;
    dpf64 base(1.0);
    dpf64 t1=cftal::str_to_d_double("0.025e1");
    std::cout.setf(std::ios_base::fixed |
                   std::ios_base::scientific,
                   std::ios_base::floatfield);
    std::cout << std::setprecision(22)
              << t1.h()
              << ", "
              << t1.l()
              << std::endl;
    base+= t1;
    for (std::size_t i=0; i<10; ++i) {
        dpf64 t= powi(base, i);
        std::cout << std::setprecision(22)
                  << t.h()
                  << ", "
                  << t.l()
                  << std::endl;
    }

}

#if 0 // defined (__AVX__)
__m256d tr1(__m256d a, __m256d b)
{
    return x86perm_f64<0, 4, 1, 5>(a, b);
}

__m256d tr2(__m256d a, __m256d b)
{
    return x86perm_f64<2, 6, 3, 7>(a, b);
}

__m256d tr1a(__m256d a, __m256d b)
{
    // x86perm_f64<0, 4, 1, 5>(a, b);
#if 0
    // 5 operations
    __m256d a0= x86perm_f64<0, 0, 1, 1>(a);
    __m256d b0= x86perm_f64<0, 0, 1, 1>(b);
    return x86select_f64<true, false, true, false>(a0, b0);
#endif
    using namespace x86vec;
    using namespace x86impl;
    // 0 4 2 6
    __m256d t0= vunpcklpd::v(a, b);
    // 1 5 3 7
    __m256d t1= vunpckhpd::v(a, b);
    __m256d r= vperm2f128<0, 2>::v(t0, t1);
    return r;

}

__m256d tr2a(__m256d a, __m256d b)
{
    // x86perm_f64<2, 6, 3, 7>(a, b);
#if 0
    // 5 operations
    __m256d a0= x86perm_f64<2, 2, 3, 3>(a);
    __m256d b0= x86perm_f64<2, 2, 3, 3>(b);
    return x86select_f64<true, false, true, false>(a0, b0);
#endif
    using namespace x86vec;
    using namespace x86impl;
    // 0 4 2 6
    __m256d t0= vunpcklpd::v(a, b);
    // 1 5 3 7
    __m256d t1= vunpckhpd::v(a, b);
    __m256d r= vperm2f128<1, 3>::v(t0, t1);
    return r;
}

__m256d tr2b(__m256d a)
{
    return x86perm_f64< 2, -1, 3, -1>(a);
}

#endif

cftal::vec<double, 4>
do_add(cftal::vec<double, 4> a,
       cftal::vec<double, 4> b)
{
    // return cftal::op::add<double, 4>::v(a, b);
    return 2.0 * a / b - (4.0 + a *  b);
    // return a * b  + a / b - (a+b);
}

cftal::vec<double, 8>
do_add(cftal::vec<double, 8> a,
       cftal::vec<double, 8> b)
{
    // return cftal::op::add<double, 4>::v(a, b);
    return 2.0 * a / b - (4.0 + a *  b);
    // return a * b  + a / b - (a+b);
}

cftal::vec<double, 32>
do_add(cftal::vec<double, 32> a,
       cftal::vec<double, 32> b)
{
    return 2.0 * a / b - (4.0 + a *  b);
}

cftal::vec<double, 256>
do_add(const cftal::vec<double, 256>& a,
       const cftal::vec<double, 256>& b)
{
    return 2.0 * a / b - (4.0 + a *  b);
}

cftal::vec<double, 8>::mask_type
do_cmp_lt(cftal::vec<double, 8> a,
          cftal::vec<double, 8> b)
{
    return a < b;
}

cftal::vec<double, 1>
do_logical(cftal::vec<double, 1> a,
           cftal::vec<double, 1> b,
           cftal::vec<double, 1> c,
           cftal::vec<double, 1> d)
{
    return ((a | b) & (c ^ d)) << 2;
}

cftal::vec<int32_t, 4>
check_v4s32(cftal::vec<int32_t, 4> a,
            cftal::vec<int32_t, 4> b,
            cftal::vec<int32_t, 4> c)
{
    const cftal::v4s32 c0={1, 2, 3, 4};
    return (a ^ b) & (c ^ c0);
}

cftal::vec<int32_t, 8>
check_v8s32(cftal::vec<int32_t, 8> a,
            cftal::vec<int32_t, 8> b,
            cftal::vec<int32_t, 8> c)
{
    const cftal::v8s32 c0={1, 2, 3, 4, 5, 6, 7, 8};
    return (a ^ b) & (c ^ c0);
}

cftal::vec<int32_t, 16>
check_v16s32(cftal::vec<int32_t, 16> a,
             cftal::vec<int32_t, 16> b,
             cftal::vec<int32_t, 16> c)
{
    return (a ^ b) & c;
}

std::pair<cftal::vec<int32_t, 8>, cftal::vec<int32_t, 8> >
check_mul_lo_hi(cftal::vec<int32_t, 8> a,
                cftal::vec<int32_t, 8> b)
{
    return mul_lo_hi(a, b);
}

cftal::vec<int32_t, 8>
check_perm_v8s32(cftal::vec<int32_t, 8> a,
                 cftal::vec<int32_t, 8> b)
{
    return cftal::permute<0, 0+8,
                          2, 2+8,
                          4, 4+8,
                          6, 6+8>(a, b);
}

cftal::vec<int32_t, 8>
check_perm_v8s32(cftal::vec<int32_t, 8> a)
{
    return cftal::permute<1, -1,
                          3, -1,
                          4, -1,
                          7, -1>(a);
}

cftal::vec<int32_t, 2>
check_even_elements(cftal::vec<int32_t, 4> a)
{
    return even_elements(a);
}

cftal::vec<int32_t, 2>
check_odd_elements(cftal::vec<int32_t, 4> a)
{
    return odd_elements(a);
}

int main(int argc, char** argv)
{
    std::cout << "alignof(max_align_t) "
              << alignof(std::max_align_t)
              << std::endl;
    cftal::v4f64 t4(4.94066e-324);
    cftal::v4s32 e4;
    cftal::v4f64 r4=frexp(t4, &e4);
    cftal::v2f64 t(4.94066e-324);
    cftal::v2s32 e;
    cftal::v2f64 r=frexp(t, &e);
    int se;
    double st=4.94066e-324;
    double sr=frexp(st, &se);
    std::cout << r4 << " : " << e4 << std::endl;
    std::cout << r << " : " << e << std::endl;
    std::cout << sr << " : " << se << std::endl;


    cftal::v8u16 ut= {1, 2, 3, 4, 5, 6, 7, 8};
    cftal::v8u16 ut1= cftal::permute<0, 1, 2, 3, 7, 6, 5, 4>(ut);
    std::cout << ut1 << std::endl;
    cftal::v8u16 ut2= ut1 * 2;
    std::cout << ut2 << std::endl;
    
#if 0
    cftal::vec<double, 4> t1(1.0), t2(2.0);
    cftal::vec<double, 4> t3(
        cftal::op::add<double, 4>::v(t1, t2));
    using namespace cftal;
    using namespace x86vec;
    uint64_t v(18446744073709551615U);
    divisor<v2u64, uint64_t> dd(v);
    v2u64 u(2210649152261252908U, 18446663117077536102U);
    v2u64 q(u / dd);
    v2u64 r(u % dd);
    uint64_t rr[2];
    rr[0]= extract<0>(r);
    rr[1]= extract<1>(r);
    std::cout << rr[0] << ' ' << rr[1] << std::endl;

#if 0
    // x86cftal::v4f64 t=exp(x86cftal::v4f64(0.0));
    // static_cast<void>(t);
    // calc_pi();
    // print_inv_fac();
    // print_2_over_i();
    // print_sqrtx();
    // testpowi();

    using namespace emuvec;

    const double c=1.0;

    v4f64 res(sin(v4f64(c)));
    x86v4f64 tres(sin(x86v4f64(c)));

    std::cout << std::setprecision(18) << std::scientific
              << extract<0>(res) << ' '
              << extract<1>(res)
              << std::endl
              << extract<0>(tres) << ' '
              << extract<1>(tres)
              << std::endl;
    std::cout << std::setprecision(18) << std::scientific << 0x1.p54 << std::endl;

#if 0
#if defined (__AVX__)
    using namespace x86vec;
    using namespace x86test;

    bool rc(true);
    __m256d a = load_v4f64(false);
    __m256d b = load_v4f64(true);
    __m256d r;
    idx id(-2,-2);
    r=tr1a(a, b);
    id.assign(0, 4, 1, 5);
    rc &= check_v4f64("perm2_v4f64", r, id);

    a = load_v4f64(false);
    b = load_v4f64(true);
    r=tr2a(a, b);
    id.assign(2, 6, 3, 7);
    rc &= check_v4f64("perm2_v4f64", r, id);
#endif
#endif
#endif
#endif
    return 0;
}
