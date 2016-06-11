#if !defined (__CFTAL_TEST_F32_F64_H__)
#define __CFTAL_TEST_F32_F64_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/mem.h>
#include <cftal/select.h>
#include <iostream>
#include <map>

namespace cftal {
    namespace test {

        double make_double(unsigned sgn, unsigned exp, uint64_t sig);
        float make_float(unsigned sgn, unsigned exp, uint32_t sig);

        struct ulp_stats {
            uint64_t _ulps;
            uint64_t _nans;
            uint64_t _cnt;
            std::pair<bool, bool> _faithful;
            std::map<int32_t, uint32_t> _devs;
            ulp_stats()
                : _ulps(0), _nans(0), _cnt(0), _faithful(false, true) {};
            void inc(int32_t ulp, int32_t is_nan) {
                ++_cnt;
                uint32_t au= ulp != 0 ? 1 : 0;
                _ulps +=  au;
                _devs[ulp] += 1;
                _nans += is_nan != 0 ? 1 : 0;
            }
            void faithful(bool v) {
                _faithful.first = true;
                if (_faithful.second == true)
                    _faithful.second =v;
            }
        };

        std::ostream& operator<<(std::ostream& s, const ulp_stats& us);

        // compare a and b, returns also true for a==NAN and b
        // == NAN
        bool f_eq(double a, double b);
        bool f_eq(float a, float b);
        // same a above, but allows also deviations up to and including +-ulp
        bool f_eq_ulp(double a, double b, uint32_t ulp, ulp_stats* us);
        bool f_eq_ulp(float a, float b, uint32_t ulp, ulp_stats* us);

        // b contains value, interval low, interval high
        bool f_eq_ulp(double a, const std::tuple<double, double, double>& b,
                      uint32_t ulp, ulp_stats* us);
        bool f_eq_ulp(float a, const std::tuple<float, float, float>& b,
                      uint32_t ulp, ulp_stats* us);

        template <typename _T>
        std::ostream&
        operator<<(std::ostream& s, const std::tuple<_T, _T, _T>& );

        template <typename _T>
        struct cmp_t {
            cmp_t() {}
            bool operator()(const _T& a, const _T& b) const {
                return a == b;
            }
        };

        template <>
        struct cmp_t<double> {
            cmp_t() {}
            bool operator()(double a, double b) const {
                return f_eq(a, b);
            }
        };

        template <>
        struct cmp_t<float> {
            cmp_t() {}
            bool operator()(float a, float b) const {
                return f_eq(a, b);
            }
        };

        template <>
        struct cmp_t<bit> {
            cmp_t() {}
            bool operator()(bit a, bit b) const {
                return a() == b();
            }
        };

        template <class _T, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(const _T(&a)[_N], _T expected, _MSG msg,
                   bool verbose=true,
                   _CMP cmp = _CMP());

        template <class _T, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(vec<_T, _N> a, _T expected, _MSG msg,
                   bool verbose=true,
                   _CMP cmp= _CMP());

        template <class _T, class _R, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(const _T(&a)[_N], const _R(&expected)[_N], _MSG msg,
                   bool verbose=true,
                   _CMP cmp = _CMP());

        template <class _T, class _R, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(vec<_T, _N> a,
                   const _R(&expected)[_N] , _MSG msg,
                   bool verbose=true,
                   _CMP cmp = _CMP());

        template <class _T, std::size_t _N>
        bool check_cmp(const _T(&a)[_N], bool expected, const char* msg);

        template <std::size_t _N>
        bool check_cmp(const double(&a)[_N], bool expected, const char* msg);

        template <std::size_t _N>
        bool check_cmp(const float(&a)[_N], bool expected, const char* msg);

        template <std::size_t _N>
        bool check_cmp(const bit(&a)[_N], bool expected, const char* msg);

        template <class _T, std::size_t _N>
        bool check_cmp(vec<_T, _N> a, bool expected, const char* msg);

        template <class _T>
        _T abs_err(_T a0, _T a1);

        template <class _T>
        _T rel_err(_T a0, _T a1);

    }
}

template <typename _T>
std::ostream&
cftal::test::
operator<<(std::ostream& s, const std::tuple<_T, _T, _T>& t)
{
    s << std::get<0>(t)
      << " [ "  << std::get<1>(t) << ", "  << std::get<2>(t) << " ]";
    return s;
}


template <class _T, std::size_t _N, typename _MSG, typename _CMP>
bool cftal::test::check(const _T(&a)[_N], _T expected , _MSG msg,
                        bool verbose, _CMP cmp)
{
    bool r=true;
    std::size_t i=1;
    auto e0= std::begin(a);
    const _T& a0= *e0;
    const cmp_t<_T> cmp_elems;
    for (auto b=std::next(e0), e= std::end(a); b!=e; ++b, ++i) {
        const _T& ai= *b;
        if (cmp_elems(a0, ai)==false) {
            if (verbose) {
                std::cerr << msg << " element " << i
                          << " not equal to element 0 " << ai << " expected: "
                          << a0 << std::endl;
            }
            r = false;
        }
    }
    if (cmp(a0, expected) == false) {
        if (verbose) {
            std::cerr << msg << " failed: " << a0 << " expected: "
                      << expected << std::endl;
        }
        r = false;
    }
    return r;
}

template <class _T, std::size_t _N, typename _MSG, typename _CMP>
bool cftal::test::check(vec<_T, _N> vr, _T expected, _MSG msg,
                        bool verbose, _CMP cmp)
{
    _T vsr[_N];
    mem< vec<_T, _N> >::store(vsr, vr);
    return check(vsr, expected, msg, verbose, cmp);
}

template <class _T, class _R, std::size_t _N, typename _MSG, typename _CMP>
bool cftal::test::check(const _T(&a)[_N],
                        const _R(&expected)[_N] , _MSG msg,
                        bool verbose, _CMP cmp)
{
    bool r=true;
    for (auto b=std::cbegin(a), ex=std::cbegin(expected), e=std::cend(a);
         b != e; ++b, ++ex) {
        auto ei= *ex;
        _T ai=*b;
        if (cmp(ai, ei) == false) {
            if (verbose) {
                std::cerr << msg << " failed: " << ai << " expected: "
                          << ei << std::endl;
            }
            r = false;
        }
    }
    return r;
}

template <class _T, class _R, std::size_t _N, typename _MSG, typename _CMP>
bool cftal::test::check(vec<_T, _N> vr,
                        const _R(&expected)[_N], _MSG msg,
                        bool verbose, _CMP cmp)
{
    _T vsr[_N];
    mem< vec<_T, _N> >::store(vsr, vr);
    return check(vsr, expected, msg, verbose, cmp);
}


template <class _T, std::size_t _N>
bool
cftal::test::check_cmp(const _T(&a)[_N], bool expected , const char* msg)
{
    bool r=true;
    std::size_t i=0;
    const cmp_t<_T> cmp;
    _T expect= expected ? ~_T(0) : _T(0);
    for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
        const _T& ai= *b;
        if (cmp(ai, expect) == false) {
            std::cerr << msg << " element " << i
                      << " failed: " << ai << " expected: "
                      << expected << std::endl;
            r = false;
        }
    }
    return r;
}

template <std::size_t _N>
bool
cftal::test::check_cmp(const double(&a)[_N], bool expected , const char* msg)
{
    bool r=true;
    std::size_t i=0;
    const cmp_t<uint64_t> cmp;
    uint64_t expect= expected ? uint64_t(-1LL) : uint64_t(0);
    for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
        const double& ai= *b;
        uint64_t aii=as<uint64_t>(ai);
        if (cmp(aii, expect) == false) {
            std::cerr << msg << " element " << i
                      << " failed: " << ai << " expected: "
                      << expected << std::endl;
            r = false;
        }
    }
    return r;
}

template <std::size_t _N>
bool
cftal::test::check_cmp(const float(&a)[_N], bool expected , const char* msg)
{
    bool r=true;
    std::size_t i=0;
    const cmp_t<uint32_t> cmp;
    uint32_t expect= expected ? uint32_t(-1) : uint32_t(0);
    for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
        const float& ai= *b;
        uint32_t aii=as<uint32_t>(ai);
        if (cmp(aii, expect) == false) {
            std::cerr << msg << " element " << i
                      << " failed: " << ai << " expected: "
                      << expected << std::endl;
            r = false;
        }
    }
    return r;
}

template <std::size_t _N>
bool
cftal::test::check_cmp(const bit(&a)[_N], bool expected , const char* msg)
{
    bool r=true;
    std::size_t i=0;
    const cmp_t<uint32_t> cmp;
    uint32_t expect= expected ? uint32_t(1) : uint32_t(0);
    for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
        const bit& ai= *b;
        uint32_t aii=ai();
        if (cmp(aii, expect) == false) {
            std::cerr << msg << " element " << i
                      << " failed: " << ai << " expected: "
                      << expected << std::endl;
            r = false;
        }
    }
    return r;
}

template <class _T, std::size_t _N>
bool
cftal::test::check_cmp(vec<_T, _N> vr, bool expected, const char* msg)
{
    _T vsr[_N];
    mem< vec<_T, _N> >::store(vsr, vr);
    return check_cmp(vsr, expected, msg);
}


template <class _T>
_T
cftal::test::abs_err(_T a0, _T a1)
{
    _T d= a0 - a1;
    return select(d > _T(0), d , -d);
}

template <class _T>
_T
cftal::test::rel_err(_T a0, _T a1)
{
    return abs_err(a0, a1)/(_T(0.5) * (a0 + a1));
}

// Local variables:
// mode: c++
// end:
#endif
