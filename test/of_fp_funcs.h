#if !defined (__CFTAL_TEST_OF_FP_FUNCS_H__)
#define __CFTAL_TEST_OF_FP_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/test/f32_f64.h>
#include <random>
#include <iostream>
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
              _CMP cmp=_CMP(), std::size_t cnt=0x40000ULL);

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
              _CMP cmp= _CMP(), std::size_t cnt=0x40000ULL) {
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
              _CMP cmp= _CMP(), std::size_t cnt=0x40000ULL)  {
                return of_fp_func<_T, 1, _F>::v(domain, cmp, cnt);
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
    _T a;
    a = std::numeric_limits<_T>::quiet_NaN();
    r &= v(a);
    r &= v(-a);
    a = std::numeric_limits<_T>::infinity();
    r &= v(a);
    r &= v(-a);
    a = 0;
    r &= v(a);
    r &= v(-a);
    a = _T(uint64_t(1ULL<<23));
    r &= v(a);
    r &= v(-a);
    a = _T(uint64_t(1ULL<<52));
    r &= v(a);
    r &= v(-a);

    std::mt19937_64 rnd;
    std::uniform_real_distribution<_T>
        distrib(domain.first, domain.second);

    std::cout << "[" << domain.first << ", " << domain.second << ")\n";
    const int64_t N0=cnt;
    const int64_t N=72*N0;
    for (int64_t i=0; i<N; ++i) {
        if ((i & (N0-1)) == (N0-1))
            std::cout << '.' << std::flush;
        _T ah=distrib(rnd);
        r &= v(ah, cmp);
    }
    _T minus1= std::max(_T(-1), domain.first);
    _T plus1= std::min(_T(1), domain.second);
    if (minus1 < plus1) {
        std::cout << std::endl;
        _T nplus1=std::nextafter(plus1, _T(2)*plus1);
        std::uniform_real_distribution<_T>
            distrib1(minus1, nplus1);
        std::cout << "[" << minus1 << ", " << nplus1 << ")\n";
        for (int64_t i=0; i<N; ++i) {
            if ((i & (N0-1)) == (N0-1))
                std::cout << '.' << std::flush;
            _T ah=distrib1(rnd);
            r &= v(ah, cmp);
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
