#if !defined (__CFTAL_TEST_OF_FP_FUNCS_H__)
#define __CFTAL_TEST_OF_FP_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/f32_f64.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>

namespace cftal {
    namespace test {

        template <typename _T>
        using func_domain = std::pair<_T, _T>;

        template <typename _T>
        struct default_domain {
            static
            const func_domain<_T> value;
        };

        const std::size_t default_cnt=0x80000ULL;

        template <typename _T>
        const func_domain<_T>
        default_domain<_T>::value =
            std::make_pair(std::numeric_limits<_T>::lowest(),
                           std::numeric_limits<_T>::max());

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func {

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(func_domain<_T> domain = default_domain<_T>::value,
              _CMP cmp=_CMP(), std::size_t cnt=default_cnt);

            template <typename _CMP=cmp_t<_T> >
            static
            bool v(_T ai, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_up_to {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(func_domain<_T> domain = default_domain<_T>::value,
              _CMP cmp= _CMP(), std::size_t cnt=default_cnt) {
                bool r=of_fp_func<_T, _N, _F>::v(domain, cmp, cnt);
                r &= of_fp_func_up_to<_T, _N/2, _F>::v(domain, cmp, cnt);
                return r;
            }
        };

        template <typename _T, typename _F>
        struct of_fp_func_up_to<_T, 1, _F> {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(func_domain<_T> domain = default_domain<_T>::value,
              _CMP cmp= _CMP(), std::size_t cnt=default_cnt)  {
                return of_fp_func<_T, 1, _F>::v(domain, cmp, cnt);
            }
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2 {

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              _CMP cmp=_CMP(), std::size_t cnt=default_cnt);

            template <typename _CMP=cmp_t<_T> >
            static
            bool v(_T ai, _T bi, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2_up_to {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              _CMP cmp= _CMP(), std::size_t cnt=default_cnt) {
                bool r=of_fp_func_2<_T, _N, _F>::v(domain_1, domain_2,
                                                   cmp, cnt);
                r &= of_fp_func_2_up_to<_T, _N/2, _F>::v(domain_1, domain_2,
                                                         cmp, cnt);
                return r;
            }
        };

        template <typename _T, typename _F>
        struct of_fp_func_2_up_to<_T, 1, _F> {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              _CMP cmp= _CMP(), std::size_t cnt=default_cnt)  {
                return of_fp_func_2<_T, 1, _F>::v(domain_1, domain_2,
                                                  cmp, cnt);
            }
        };

        template <typename _T>
        struct check_rint {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& v) {
                return rint(v);
            }
            static
            _T
            v(const _T& v) {
                return std::rint(v);
            }
            static
            const char* fname() { return "rint"; }
        };

        template <typename _T>
        struct check_floor {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& v) {
                return floor(v);
            }
            static
            _T
            v(const _T& v) {
                return std::floor(v);
            }
            static
            const char* fname() { return "floor"; }
        };

        template <typename _T>
        struct check_ceil {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& v) {
                return ceil(v);
            }
            static
            _T
            v(const _T& v) {
                return std::ceil(v);
            }
            static
            const char* fname() { return "ceil"; }
        };

        template <typename _T>
        struct check_trunc {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& v) {
                return trunc(v);
            }
            static
            _T
            v(const _T& v) {
                return std::trunc(v);
            }
            static
            const char* fname() { return "trunc"; }
        };

    }
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(_T a, _CMP cmp)
{
    vec<_T, _N> va=a;
    vec<_T, _N> vr=_F::v(va);
    _T r= _F::v(a);
    // std::cout << std::setprecision(18) << a << std::endl;
    bool c= check(vr, r, _F::fname(), true, cmp);
    if (c == false) {
        std::cerr << _F::fname() << "("<< a << ") failed.\n";
    }
    return c;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(func_domain<_T> domain,
                                       _CMP cmp, std::size_t cnt)
{
    bool r = true;
    const _T inf_nan_args []= {
        _T(0),
        _T(1),
        _T(2),
        _T(7),
        _T(8),
        _T(uint64_t(1ULL<<23)),
        _T(uint64_t(1ULL<<52)),
        std::numeric_limits<_T>::infinity(),
        std::numeric_limits<_T>::quiet_NaN(),
    };

    for (auto b=std::begin(inf_nan_args), e=std::end(inf_nan_args);
         b!=e; ++b) {
        const auto& ai= *b;
        r &=v(ai, cmp);
        r &=-v(ai, cmp);
    }

    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib(domain.first, domain.second);

    std::cout << "[" << domain.first << ", " << domain.second << ")\n";
    const uint32_t N0=72;
    for (uint32_t j=0; j<N0; ++j) {
        for (std::size_t i=0; i<cnt; ++i) {
            _T ah=distrib(rnd);
            r &= v(ah, cmp);
        }
        std::cout << '.' << std::flush;
    }
    _T minus1= std::max(_T(-1), domain.first);
    _T plus1= std::min(_T(1), domain.second);
    if (minus1 < plus1 && (minus1 != domain.first || plus1 != domain.second)) {
        std::cout << std::endl;
        _T nplus1=std::nextafter(plus1, _T(2)*plus1);
        uniform_real_distribution<_T>
            distrib1(minus1, nplus1);
        std::cout << "[" << minus1 << ", " << nplus1 << ")\n";
        for (uint32_t j=0; j<N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                _T ah=distrib1(rnd);
                r &= v(ah, cmp);
            }
            std::cout << '.' << std::flush;
        }
    }
    std::cout << std::endl;
    if (r == true) {
        std::cout << __func__ << _N << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " test failed " << std::endl;
    }
    return r;

}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::v(_T a, _T b, _CMP cmp)
{
    vec<_T, _N> va=a;
    vec<_T, _N> vb=b;
    vec<_T, _N> vr=_F::v(va, vb);
    _T r= _F::v(a, b);
    bool c= check(vr, r, _F::fname(), true, cmp);
    if (c == false) {
        std::cerr << _F::fname() << "("<< a << ", " <<  b << ") failed.\n";
    }
    return c;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::v(func_domain<_T> domain_1,
                                         func_domain<_T> domain_2,
                                         _CMP cmp, std::size_t cnt)
{
    bool r = true;

    const _T inf_nan_args []= {
        _T(0),
        _T(1),
        _T(2),
        _T(7),
        _T(8),
        _T(uint64_t(1ULL<<23)),
        _T(uint64_t(1ULL<<52)),
        std::numeric_limits<_T>::infinity(),
        std::numeric_limits<_T>::quiet_NaN(),
    };

    for (auto ab=std::begin(inf_nan_args), ae=std::end(inf_nan_args);
         ab != ae; ++ab) {
        _T ai=*ab;
        for (auto bb=std::begin(inf_nan_args), be=std::end(inf_nan_args);
             bb !=be; ++bb) {
            _T bi= *bb;
            r &= v(ai, bi, cmp);
            r &= v(ai, -bi, cmp);
            r &= v(-ai, bi, cmp);
            r &= v(-ai,-bi, cmp);
        }
    }

    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib1(domain_1.first, domain_1.second);
    uniform_real_distribution<_T>
        distrib2(domain_2.first, domain_2.second);

    std::cout << "[" << domain_1.first << ", " << domain_1.second
              << ") x [" << domain_2.first << ", " << domain_2.second
              << ")\n";
    const uint32_t N0=72;
    for (uint32_t j=0; j< N0; ++j) {
        for (std::size_t i=0; i<cnt; ++i) {
            _T ah=distrib1(rnd);
            _T bh=distrib2(rnd);
            r &= v(ah, bh, cmp);
        }
        std::cout << '.' << std::flush;
    }
    _T a_minus1= std::max(_T(-1), domain_1.first);
    _T a_plus1= std::min(_T(1), domain_1.second);
    _T b_minus1= std::max(_T(-1), domain_2.first);
    _T b_plus1= std::min(_T(1), domain_2.second);
    if (a_minus1 < a_plus1 && b_minus1 < b_plus1) {
        std::cout << std::endl;
        _T a_nplus1=std::nextafter(a_plus1, _T(2)*a_plus1);
        _T b_nplus1=std::nextafter(b_plus1, _T(2)*b_plus1);
        uniform_real_distribution<_T>
            distrib_1_1(a_minus1, a_nplus1);
        uniform_real_distribution<_T>
            distrib_1_2(b_minus1, b_nplus1);
        std::cout << "[" << a_minus1 << ", " << a_nplus1
                  << ") x [" << b_minus1 << ", " << b_nplus1
                  << ")\n";
        for (uint32_t j=0; j<N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                _T ah=distrib_1_1(rnd);
                _T bh=distrib_1_2(rnd);
                r &= v(ah, bh, cmp);
            }
            std::cout << '.' << std::flush;
        }
    }
    std::cout << std::endl;
    if (r == true) {
        std::cout << __func__ << _N << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " test failed " << std::endl;
    }
    return r;
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_OF_FP_FUNCS_H__
