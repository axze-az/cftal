// 
// Copyright (C) 2010-2021 Axel Zeuner
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#if !defined (__CFTAL_TEST_F32_F64_H__)
#define __CFTAL_TEST_F32_F64_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/mem.h>
#include <cftal/select.h>
#include <cftal/bitops.h>
#include <cftal/test/spinlock.h>
#include <iostream>
#include <sstream>
#include <map>
#include <mutex>
#include <atomic>

namespace cftal {
    namespace test {

        // construct a double from sign & 1, exponent with bias and
        // significant
        double make_double(unsigned sgn, unsigned exp, uint64_t sig);
        // construct a float from sign &1, exponent with bias and
        // significant
        float make_float(unsigned sgn, unsigned exp, uint32_t sig);

        struct alignas(64) ulp_stats {

            using lock_type = spinlock;

            // count of operations with nonzero ulp
            std::atomic<uint64_t> _ulps;
            char _pad0[64-sizeof(_ulps)];
            // count of nan
            std::atomic<uint64_t> _nans;
            char _pad1[64-sizeof(_nans)];
            // count of unexpected nans
            std::atomic<uint64_t> _nans_unexpected;
            char _pad2[64-sizeof(_nans_unexpected)];
            // count of not calculated nans
            std::atomic<uint64_t> _nans_not_calculated;
            char _pad3[64-sizeof(_nans_not_calculated)];
            // operation count
            std::atomic<uint64_t> _cnt;
            char _pad4[64-sizeof(_cnt)];
            // faithul rounding: bit 0 true/false (1/0)
            //                   bit 1 not tested/tested (1/0)
            std::atomic<uint32_t> _faithful;
            char _pad5[64-sizeof(_faithful)];
            // mutex protecting _devs;
            lock_type _mtx_devs;
            char _pad6[64-sizeof(_mtx_devs)];
            // deviations of x ulp's n times, deviations larger/smaller
            // than lin_max are grouped together into ranges (2^(n-1), 2^n]
            // where 2^(n-1) < x <= 2^n if x positive ....
            static const int32_t lin_max=32;
            static_assert((lin_max & (lin_max-1))==0,
                          "lin_max must be a power of 2");
            std::map<int32_t, uint64_t> _devs;
            // constructor.
            ulp_stats()
                : _ulps(0), _nans(0),
                  _nans_unexpected(0),
                  _nans_not_calculated(0),
                  _cnt(0),
                  _faithful(3),
                  _mtx_devs(),
                  _devs() {};
            // inrecrement the _ulps, ...
            void inc(int32_t ulp,
                     bool is_nan,
                     bool nan_not_calculated,
                     bool nan_unexpected);

            // set the faithful rounding values
            void faithful(bool v);
        };

        std::ostream& operator<<(std::ostream& s, const ulp_stats& us);

        // output control for ulp_stats: hist = false supresses
        // the output of the histogram with the deviations
        struct ulp_stats_to_stream {
            const ulp_stats* _us;
            bool _hist;
            ulp_stats_to_stream(const ulp_stats& us,
                                bool hist)
                : _us(&us), _hist(hist) {}
        };

        std::ostream&
        operator<<(std::ostream& s, const ulp_stats_to_stream& uss);

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

        int32_t
        distance(double a, double b);

        int32_t
        distance(float a, float b);

        template <typename _I, typename _T>
        std::ostream&
        operator<<(std::ostream& s, const std::pair<_I, _T>& );

        template <typename _T>
        std::ostream&
        operator<<(std::ostream& s, const std::tuple<_T, _T, _T>& );

        template <typename _I, typename _T>
        std::ostream&
        operator<<(std::ostream& s,
                   const std::pair<_I, std::tuple<_T, _T, _T> >& );

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
        struct cmp_t<std::pair<double, double> > {
            cmp_t() {}
            bool operator()(const std::pair<double, double>& a,
                            const std::pair<double, double>& b) const {
                return f_eq(a.first, b.first) && f_eq(a.second, b.second);
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
        struct cmp_t<std::pair<float, float> > {
            cmp_t() {}
            bool operator()(const std::pair<float, float>& a,
                            const std::pair<float, float>& b) const {
                return f_eq(a.first, b.first) && f_eq(a.second, b.second);
            }
        };

        template <>
        struct cmp_t<bit> {
            cmp_t() {}
            bool operator()(bit a, bit b) const {
                return a() == b();
            }
        };

        // check a[_N] against expected
        template <class _T, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(const _T(&a)[_N], _T expected, _MSG msg,
                   bool verbose=true,
                   _CMP cmp = _CMP());

        // check a against expected
        template <class _T, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(vec<_T, _N> a, _T expected, _MSG msg,
                   bool verbose=true,
                   _CMP cmp= _CMP());

        // check a[_N] against expected[_N]
        template <class _T, class _R, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(const _T(&a)[_N], const _R(&expected)[_N], _MSG msg,
                   bool verbose=true,
                   _CMP cmp = _CMP());

        // check a against expected[_N]
        template <class _T, class _R, std::size_t _N, typename _MSG,
                  typename _CMP = cmp_t<_T> >
        bool check(vec<_T, _N> a,
                   const _R(&expected)[_N] , _MSG msg,
                   bool verbose=true,
                   _CMP cmp = _CMP());

        // check i,a against expected[_N]
        template <class _I, class _T, class _R, std::size_t _N,
                  typename _MSG, typename _CMP>
        bool check(const std::pair<vec<_I, _N>, vec<_T, _N> >& a,
                   const _R(&expected)[_N] , _MSG msg,
                   bool verbose,
                   _CMP cmp);

        // check a against expected, a contains the result of
        // a comparison
        template <class _T, std::size_t _N>
        bool check_cmp(const _T(&a)[_N], bool expected, const char* msg);

        // check a against expected, a contains the result of
        // a comparison
        template <std::size_t _N>
        bool check_cmp(const double(&a)[_N], bool expected, const char* msg);

        template <std::size_t _N>
        bool check_cmp(const float(&a)[_N], bool expected, const char* msg);

        // check a against expected, a contains the result of
        // a comparison
        template <std::size_t _N>
        bool check_cmp(const bit(&a)[_N], bool expected, const char* msg);

        // check a against expected, a contains the result of
        // a comparison
        template <class _T, std::size_t _N>
        bool check_cmp(vec<_T, _N> a, bool expected, const char* msg);

        // error [abs of difference] between a0 and a1
        template <class _T>
        _T abs_err(_T a0, _T a1);

        // relative error [abs of difference] between a0 and a1
        template <class _T>
        _T rel_err(_T a0, _T a1);

    }
}

template <typename _I, typename _T>
std::ostream&
cftal::test::
operator<<(std::ostream& s,
           const std::pair<_I,  _T>& t)
{
    s << t.first << ' ' << t.second;
    return s;
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

template <typename _I, typename _T>
std::ostream&
cftal::test::
operator<<(std::ostream& s,
           const std::pair<_I, std::tuple<_T, _T, _T> >& t)
{
    s << t.first << ' ' << t.second;
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
    
    using out_t = typename 
        std::conditional<std::is_same<int8_t, _T>::value || 
                         std::is_same<uint8_t, _T>::value,
                         typename std::conditional<cftal::is_signed<_T>::value, 
                                                   int, unsigned>::type,
                         _T>::type;
    
    for (auto b=std::next(e0), e= std::end(a); b!=e; ++b, ++i) {
        const _T& ai= *b;
        if (cmp_elems(a0, ai)==false) {
            if (verbose) {
                std::ostringstream s;
                s.copyfmt(std::cerr);
                s << msg << " element " << i
                  << " not equal to element 0 " << out_t(ai) << " expected: "
                  << out_t(a0) << std::endl;
                std::cerr << s.str();
            }
            r = false;
        }
    }
    if (cmp(a0, expected) == false) {
        if (verbose) {
            std::ostringstream s;
            s.copyfmt(std::cerr);
            s << msg << " failed: " << out_t(a0) << " expected: "
              << out_t(expected) << std::endl;
            s << std::hexfloat;
            s << msg << " failed: " << out_t(a0) << " expected: "
              << out_t(expected) << std::endl;
            std::cerr << s.str();
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
    using out_t = typename 
        std::conditional<std::is_same<int8_t, _T>::value || 
                         std::is_same<uint8_t, _T>::value,
                         typename std::conditional<cftal::is_signed<_T>::value, 
                                                   int, unsigned>::type,
                         _T>::type;
    using out_ex_t = typename 
        std::conditional<std::is_same<int8_t, _R>::value || 
                         std::is_same<uint8_t, _R>::value,
                         typename std::conditional<cftal::is_signed<_R>::value, 
                                                   int, unsigned>::type,
                         _R>::type;
    bool r=true;
    auto ex=std::cbegin(expected);
    for (auto b=std::cbegin(a), e=std::cend(a); b != e; ++b, ++ex) {
        const auto& ei= *ex;
        _T ai=*b;
        if (cmp(ai, ei) == false) {
            if (verbose) {
                std::ostringstream s;
                s.copyfmt(std::cerr);
                s << msg << " failed: " << out_t(ai) << " expected: "
                  << out_ex_t(ei) << std::endl;
                s << std::hexfloat;
                s << msg << " failed: " << out_t(ai) << " expected: "
                  << out_ex_t(ei) << std::endl;
                std::cerr << s.str();
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

template <class _I, class _T, class _R, std::size_t _N,
          typename _MSG, typename _CMP>
bool
cftal::test::check(const std::pair<vec<_I, _N>, vec<_T, _N> >& vr,
                   const _R(&expected)[_N], _MSG msg,
                   bool verbose, _CMP cmp)
{
    _I vir[_N];
    _T vtr[_N];
    mem< vec<_I, _N> >::store(vir, vr.first);
    mem< vec<_T, _N> >::store(vtr, vr.second);
    bool r=true;
    std::size_t i=0;
    for (auto b=std::cbegin(expected), e=std::cend(expected);
         b != e; ++b, ++i) {
        const auto& exi=*b;
        auto ri=std::make_pair(vir[i], vtr[i]);
        if (cmp(ri, exi) == false) {
            if (verbose) {
                std::ostringstream s;
                s.copyfmt(std::cerr);
                s << msg << " failed: "
                  << ri.first << ' ' << ri.second
                  << " expected: "
                  << exi
                  << std::endl;
                s << std::hexfloat;
                s << msg << " failed: "
                  << ri.first << ' ' << ri.second
                  << " expected: "
                  << exi
                  << std::endl;
                std::cerr << s.str();
            }
            r = false;
        }
    }
    return r;
}


template <class _T, std::size_t _N>
bool
cftal::test::check_cmp(const _T(&a)[_N], bool expected , const char* msg)
{
    using out_t = typename 
        std::conditional<std::is_same<int8_t, _T>::value || 
                         std::is_same<uint8_t, _T>::value,
                         typename std::conditional<cftal::is_signed<_T>::value, 
                                                   int, unsigned>::type,
                         _T>::type;
    bool r=true;
    std::size_t i=0;
    const cmp_t<_T> cmp;
    _T expect= expected ? ~_T(0) : _T(0);
    for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
        const _T& ai= *b;
        if (cmp(ai, expect) == false) {
            std::cerr << msg << " element " << i
                      << " failed: " << out_t(ai) << " expected: "
                      << out_t(expect) << std::endl;
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
                      << expect << std::endl;
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
                      << expect << std::endl;
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
                      << expect << std::endl;
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
    return select(d > _T(0.0), d , -d);
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
