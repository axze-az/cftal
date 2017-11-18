//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/of_math_funcs.h"
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

int main_exp(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d=std::make_pair(-16.5f, 10.4f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp<ftype> >::v(st, d, speed_only,
                                              cmp_ulp<ftype>(ulp, us),
                                              cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_exp2(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d=std::make_pair(-24.5f, 15.1f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp2<ftype> >::v(st, d, speed_only,
                                               cmp_ulp<ftype>(ulp, us),
                                               cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_exp10(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d=std::make_pair(-7.3f, 4.6f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_exp10<ftype> >::v(st, d, speed_only,
                                                cmp_ulp<ftype>(ulp, us),
                                                cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log10<ftype> >::v(st, d, speed_only,
                                              cmp_ulp<ftype>(ulp, us),
                                              cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log2(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log2<ftype> >::v(st, d, speed_only,
                                              cmp_ulp<ftype>(ulp, us),
                                              cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_log10(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    using ftype = float;

    // func_domain<double> d=std::make_pair(0.0,
    //                                     std::numeric_limits< double >::max());
    func_domain<ftype> d=std::make_pair(-std::numeric_limits<ftype>::max(),
                                         std::numeric_limits<ftype>::max());
    d = std::make_pair(-0x1p-25f, 0x1.1p16f);
    exec_stats st(_N);
    auto us=std::make_shared<ulp_stats>();
    rc &= of_fp_func_up_to<
        ftype, _N, check_half_log10<ftype> >::v(st, d, speed_only,
                                                cmp_ulp<ftype>(ulp, us),
                                                cnt, false);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_sin(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    auto dp=std::make_pair(-0x1p16f, 0x1p16f);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_half_sin<float> >::v(st, dp, speed_only,
                                              cmp_ulp<float>(ulp, us),
                                              cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_cos(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    auto dp=std::make_pair(-0x1p16f, 0x1p16f);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_half_cos<float> >::v(st, dp, speed_only,
                                              cmp_ulp<float>(ulp, us),
                                              cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_tan(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(18) << std::scientific;
    std::cerr << std::setprecision(18) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    auto dp=std::make_pair(-0x1p16f, 0x1p16f);
    // auto dp=std::make_pair(M_PI/2, M_PI/2);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_half_tan<float> >::v(st, dp, speed_only,
                                              cmp_ulp<float>(ulp, us),
                                              cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_rsqrt(int argc, char** argv)
{
    using namespace cftal::test;
    std::cout << std::setprecision(10) << std::scientific;
    std::cerr << std::setprecision(10) << std::scientific;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(-1.0e-38f,
                                        // std::numeric_limits< float >::max()
                                        0x1p16f);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_rsqrt<float> >::v(st, d, speed_only,
                                           cmp_ulp<float>(ulp, us),
                                           cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}

int main_sqrt(int argc, char** argv)
{
    using namespace cftal::test;
    const int ulp=8;
    const int _N=16;
    bool rc=true;
    bool speed_only=false;
    std::size_t cnt=update_cnt(0x800);
    if ((argc > 1) && (std::string(argv[1]) == "--speed")) {
        speed_only=true;
        cnt *=8;
    }
    func_domain<float> d=std::make_pair(-1.0e-38f,
                                        // std::numeric_limits< float >::max()
                                        0x1p16f);
    auto us=std::make_shared<ulp_stats>();
    exec_stats st(_N);
    rc &= of_fp_func_up_to<
        float, _N, check_sqrt<float> >::v(st, d, speed_only,
                                          cmp_ulp<float>(ulp, us),
                                          cnt, true);
    std::cout << "ulps: "
              << std::fixed << std::setprecision(4)
              << ulp_stats_to_stream(*us, true) << std::endl;
    std::cout << st << std::endl;
    return (rc == true) ? 0 : 1;
}


int main(int argc, char** argv)
{
    int r=0;
    r |= main_log(argc, argv);
    r |= main_log2(argc, argv);
    r |= main_log10(argc, argv);
    r |= main_exp(argc, argv);
    r |= main_exp2(argc, argv);
    r |= main_exp10(argc, argv);
    r |= main_cos(argc, argv);
    r |= main_sin(argc, argv);
    r |= main_tan(argc, argv);
    r |= main_rsqrt(argc, argv);
    r |= main_sqrt(argc, argv);
    return r;
}
