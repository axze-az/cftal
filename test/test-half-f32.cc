//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include <tuple>
#include <iostream>
#include <iomanip>
#include <memory>


namespace cftal {

    namespace test {

        template <typename _T>
        struct check_half_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::exp(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp(a);
            }
            static
            const char* fname() {
                return "half_exp";
            }
        };

        template <typename _T>
        struct check_half_exp2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::exp2(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_exp2, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::exp2(a);
            }
            static
            const char* fname() {
                return "half_exp2";
            }
        };

        template <typename _T>
        struct check_half_exp10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::exp10(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_ext::exp10, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return ::exp10(a);
            }
            static
            const char* fname() {
                return "half_exp10";
            }
        };

        template <typename _T>
        struct check_half_log {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::log(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::log(a);
            }
            static
            const char* fname() { return "half_log"; }
        };

        template <typename _T>
        struct check_half_log2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::log2(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log2, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::log2(a);
            }
            static
            const char* fname() { return "half_log2"; }
        };

        template <typename _T>
        struct check_half_log10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::log10(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_log10, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::log10(a);
            }
            static
            const char* fname() { return "half_log10"; }
        };

        template <typename _T>
        struct check_half_sin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::sin(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_sin, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::sin(a);
            }
            static
            const char* fname() { return "half_sin"; }
        };

        template <typename _T>
        struct check_half_cos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::cos(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_cos, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::cos(a);
            }
            static
            const char* fname() { return "half_cos"; }
        };

        template <typename _T>
        struct check_half_tan {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::tan(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_tan, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::tan(a);
            }
            static
            const char* fname() { return "half_tan"; }
        };

        template <typename _T>
        struct check_rsqrt {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::rsqrt(a);
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_rec_sqrt, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return 1.0/std::sqrt(a);
            }
            static
            const char* fname() { return "half_rsqrt"; }
        };

        template <typename _T>
        struct check_sqrt {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return half_math::sqrt(a);
            }
            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_sqrt, &i);
                return std::make_tuple(v, i.first, i.second);
            }
            static
            _T
            s(const _T& a) {
                return std::sqrt(a);
            }
            static
            const char* fname() { return "half_sqrt"; }
        };
    }

}

int main_exp(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-16.5f, 10.4f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp<ftype> >::v(st, d,
                                              ags._speed_only,
                                              ags._mt,
                                              cmp_ulp<ftype>(ulp, us),
                                              ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_exp2(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-24.5f, 15.1f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp2<ftype> >::v(st, d,
                                               ags._speed_only,
                                               ags._mt,
                                               cmp_ulp<ftype>(ulp, us),
                                               ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_exp10(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;

    using ftype = float;
    func_domain<ftype> d=std::make_pair(-7.3f, 4.6f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp10<ftype> >::v(st, d,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;

    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log<ftype> >::v(st, d,
                                              ags._speed_only,
                                              ags._mt,
                                              cmp_ulp<ftype>(ulp, us),
                                              ags._cnt, true);;
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log2(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;

    using ftype = float;

    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log2<ftype> >::v(st, d,
                                               ags._speed_only,
                                               ags._mt,
                                               cmp_ulp<ftype>(ulp, us),
                                               ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log10(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats<_N> st;
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log10<ftype> >::v(st, d,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_sin(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;

    auto dp=std::make_pair(-0x1p16f, 0x1p16f);
    auto us=std::make_shared<ulp_stats>();

    using ftype = float;

    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_sin<ftype> >::v(st, dp,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);;
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_cos(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    auto dp=std::make_pair(-0x1p16f, 0x1p16f);
    auto us=std::make_shared<ulp_stats>();
    using ftype =float;
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_cos<ftype> >::v(st, dp,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_tan(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    auto dp=std::make_pair(-0x1p16f, 0x1p16f);
    // auto dp=std::make_pair(M_PI/2, M_PI/2);
    auto us=std::make_shared<ulp_stats>();
    using ftype=float;
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_tan<ftype> >::v(st, dp,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_rsqrt(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    func_domain<float> d=std::make_pair(-1.0e-38f,
                                        // std::numeric_limits< float >::max()
                                        0x1p16f);
    using ftype = float;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        ftype, _N, check_rsqrt<ftype> >::v(st, d,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_sqrt(const cftal::test::pgm_args& ags)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;

    const int ulp=8;
    const int _N=16;
    bool rc=true;
    func_domain<float> d=std::make_pair(-1.0e-38f,
                                        // std::numeric_limits< float >::max()
                                        0x1p16f);
    using ftype=float;
    auto us=std::make_shared<ulp_stats>();
    exec_stats<_N> st;
    rc &= of_fp_func_up_to<
        ftype, _N, check_sqrt<ftype> >::v(st, d,
                                                ags._speed_only,
                                                ags._mt,
                                                cmp_ulp<ftype>(ulp, us),
                                                ags._cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char** argv)
{
    int r=0;

    using namespace cftal::test;
    pgm_args ags=parse(argc, argv, 0x800);

    r |= main_log(ags);
    r |= main_log2(ags);
    r |= main_log10(ags);
    r |= main_exp(ags);
    r |= main_exp2(ags);
    r |= main_exp10(ags);
    r |= main_cos(ags);
    r |= main_sin(ags);
    r |= main_tan(ags);
    r |= main_rsqrt(ags);
    r |= main_sqrt(ags);
    return r;
}
