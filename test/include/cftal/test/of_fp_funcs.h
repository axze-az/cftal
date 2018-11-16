//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
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

        // domain of a functions
        template <typename _T>
        using func_domain = std::pair<_T, _T>;

        // the default domain
        template <typename _T>
        struct default_domain {
            static
            const func_domain<_T> value;
        };

        // default test cnt
        const std::size_t default_cnt=0x80000ULL;

        template <typename _T>
        const func_domain<_T>
        default_domain<_T>::value =
            std::make_pair(std::numeric_limits<_T>::lowest(),
                           std::numeric_limits<_T>::max());

        // the default test argumens
        template <typename _T>
        struct default_arguments {
            static
            const std::vector<_T> values;
        };

        // execution statistics
        struct exec_stats {
            // the tics for the vectors of length 1...2^tics.size()
            std::vector<uint64_t> _tics;
            // number of function calls
            std::vector<uint64_t> _evals;
            // insert into _tics
            void insert(uint64_t _tic_before, uint64_t tic_after,
                        unsigned n);
            // constructor
            exec_stats(unsigned n)
                : _tics(n+1, uint64_t(0)), _evals(n+1, uint64_t(0)) {}
            // timer function
            static
            uint64_t hr_timer() { return rdtsc(); }
        };
        std::ostream& operator<<(std::ostream& s, const exec_stats& st);

        // merge two exec_stats 
        void
        merge_from(exec_stats& dst, const exec_stats& src)
        
        // output operator for pairs of vectors with the same length
        template <typename _I, typename _T, std::size_t _N>
        std::ostream&
        operator<<(std::ostream& s,
                   const std::pair<vec<_I, _N>, vec<_T, _N> >& vp);

        // template to check if two half vectors yield the same
        // results as the full vector
        template <typename _T, std::size_t _N, typename _F>
        struct vec_parts {
            // check for functions with one argument returning a
            // single value
            static
            bool
            v(const vec<_T, _N>& x, const vec<_T, _N>& fx,
              exec_stats& st);
            // check for functions with one argument returning a pair
            static
            bool
            v(const vec<_T, _N>& x,
              const std::pair<vec<_T, _N>, vec<_T, _N> >& fx,
              exec_stats& st);
            // check for functions with one argument and an additional
            // result pointer
            template <typename _I>
            static
            bool
            v(const vec<_T, _N>& x,
              const std::pair<vec<_I, _N>, vec<_T, _N> >& fx,
              exec_stats& st);
            // check for functions with two arguments
            static
            bool
            v(const vec<_T, _N>& x, const vec<_T, _N>& y,
              const vec<_T, _N>& fx, exec_stats& st);
        };

        // specialization to stop recursion
        template <typename _T, typename _F>
        struct vec_parts<_T, 1, _F> {
            static
            bool
            v(const vec<_T, 1>& x, const vec<_T, 1>& fx, exec_stats& st) {
                static_cast<void>(x);
                static_cast<void>(fx);
                static_cast<void>(st);
                return true;
            }

            template <typename _I>
            static
            bool
            v(const vec<_T, 1>& x,
              const std::pair<vec<_I, 1>, vec<_T, 1> >& fx,
              exec_stats& st) {
                static_cast<void>(x);
                static_cast<void>(fx);
                static_cast<void>(st);
                return true;
            }

            static
            bool
            v(const vec<_T, 1>& x, const vec<_T, 1>& y,
              const vec<_T, 1>& fx, exec_stats& st) {
                static_cast<void>(x);
                static_cast<void>(y);
                static_cast<void>(fx);
                static_cast<void>(st);
                return true;
            }
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func {

            // tv is a container with additional values to test
            template <typename _CMP, typename _C>
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain,
              bool speed_only,
              _CMP cmp,
              std::size_t cnt,
              const _C& tv);

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain = default_domain<_T>::value,
              bool speed_only = false,
              _CMP cmp=_CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults= false);

            template <typename _CMP=cmp_t<_T> >
            static
            bool v(const _T(&ai)[_N],
                   exec_stats& st, bool speed_only, _CMP cmp=_CMP());
        };

        // test of vector function _F(vec<_T, _N>) up to length N
        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_up_to {

            // tv is a container with additional values to test
            template <typename _CMP, typename _C>
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain,
              bool speed_only,
              _CMP cmp,
              std::size_t cnt,
              const _C& tv) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain,
                                                 speed_only, cmp, cnt,
                                                 tv);
                return r;
            }

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain = default_domain<_T>::value,
              bool speed_only = false,
              _CMP cmp= _CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults= false) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain,
                                                 speed_only, cmp, cnt,
                                                 suppress_defaults);
                return r;
            }
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2 {

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              bool speed_only = false,
              _CMP cmp=_CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false);

            template <typename _CMP=cmp_t<_T> >
            static
            bool v(const _T(&ai)[_N], const _T(&bi)[_N],
                   exec_stats& st, bool speed_only, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2_up_to {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              bool speed_only = false,
              _CMP cmp= _CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false) {
                bool r=of_fp_func_2<_T, _N, _F>::v(st, domain_1, domain_2,
                                                   speed_only, cmp, cnt,
                                                   suppress_defaults);
                return r;
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
            r(const _T& v) {
                return std::rint(v);
            }
            static
            _T
            s(const _T& v) {
                return r(v);
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
            r(const _T& v) {
                return std::floor(v);
            }
            static
            _T
            s(const _T& v) {
                return r(v);
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
            r(const _T& v) {
                return std::ceil(v);
            }
                        static
            _T
            s(const _T& v) {
                return r(v);
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
            r(const _T& v) {
                return std::trunc(v);
            }
            static
            _T
            s(const _T& v) {
                return r(v);
            }
            static
            const char* fname() { return "trunc"; }
        };

    }
}

template <typename _I, typename _T, std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s,
                        const std::pair<vec<_I, _N>, vec<_T, _N> >& vp)
{
    s << vp.first << ' ' << vp.second;
    return s;
}

template <typename _T>
const std::vector<_T>
cftal::test::default_arguments<_T>::values={
    _T(0.0),
    _T(-0.0),
    _T(0.5),
    _T(1.0+0x1p-52),
    _T(1.0-0x1p-53),
    _T(1.0+0x1p-23),
    _T(1.0-0x1p-24),
    _T(2),
    _T(2.0+0x1p-51),
    _T(2.0-0x1p-52),
    _T(2.0+0x1p-22),
    _T(2.0-0x1p-23),
    _T(7),
    _T(8),
    _T(10),
    _T(10.25),
    _T(10.5),
    _T(10.75),
    _T(11.0),
    _T(11.25),
    _T(11.5),
    _T(11.75),
    _T(12.0),
    _T(19.5),
    _T(20),
    _T(20.5),
    _T(35),
    _T(40),
    _T(45),
    _T(57),
    _T(60),
    _T(63),
    _T(79),
    _T(80),
    _T(81),
    _T(100),
    _T(100.25),
    _T(100.5),
    _T(100.75),
    _T(101.0),
    _T(M_E), _T(1/M_E),
    _T(M_LOG2E),  _T(1/M_LOG2E),
    _T(M_LOG10E), _T(1/M_LOG10E),
    _T(M_LN2),  _T(1/M_LN2),
    _T(M_LN10), _T(1/M_LN10),
    _T(M_PI), _T(M_1_PI),
    _T(M_PI_2), _T(M_2_PI),
    _T(M_PI_4), _T(1/M_PI_4),
    _T(M_2_SQRTPI), _T(1/M_2_SQRTPI),
    _T(M_SQRT2), _T(M_SQRT1_2),
    _T(M_SQRT2/2), _T(2/M_SQRT2),
    // log functions
    _T(std::log(3)/2),
    // tan
    _T(6.0/7.0*M_PI_4),
    // atan
    _T(7.0/16), _T(11.0/16), _T(19.0/16), _T(39.0/16),
    // asinh
    _T(0x1p28),
    // acosh
    _T(0x1p26),
    // lgamma
    _T(-2.747682668831582298e+00),
    _T(-2.747682643214721665e+00),
    _T(uint64_t(1ULL<<23)),
    _T(uint64_t(1ULL<<52)),
    _T(0x1.0p31),
    _T(0x1.0p21),
    _T(0x1.0p23),
    _T(0x1.0p24),
    _T(0x1.0p51),
    _T(0x1.0p52),
    std::numeric_limits<_T>::denorm_min(),
    2*std::numeric_limits<_T>::denorm_min(),
    4*std::numeric_limits<_T>::denorm_min(),
    8*std::numeric_limits<_T>::denorm_min(),
    16*std::numeric_limits<_T>::denorm_min(),
    32*std::numeric_limits<_T>::denorm_min(),
    64*std::numeric_limits<_T>::denorm_min(),
    std::numeric_limits<_T>::min(),
    2*std::numeric_limits<_T>::min(),
    4*std::numeric_limits<_T>::min(),
    8*std::numeric_limits<_T>::min(),
    16*std::numeric_limits<_T>::min(),
    32*std::numeric_limits<_T>::min(),
    64*std::numeric_limits<_T>::min(),
    std::numeric_limits<_T>::max(),
    1.0/2.0*std::numeric_limits<_T>::max(),
    1.0/4.0*std::numeric_limits<_T>::max(),
    1.0/8.0*std::numeric_limits<_T>::max(),
    1.0/16.0*std::numeric_limits<_T>::max(),
    1.0/32.0*std::numeric_limits<_T>::max(),
    1.0/64.0*std::numeric_limits<_T>::max(),
    std::numeric_limits<_T>::infinity(),
    std::numeric_limits<_T>::quiet_NaN()
};

template <typename _T, std::size_t _N, typename _F>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x, const vec<_T, _N>& fx, exec_stats& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= exec_stats::hr_timer();
    vec<_T, _N2> fxl=_F::v(xl);
    uint64_t t1= exec_stats::hr_timer();
    vec<_T, _N2> fxh=_F::v(xh);
    uint64_t t2 = exec_stats::hr_timer();
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, fxh, st);
    vec<_T, _N> fxlh(fxl, fxh);
    typename vec<_T, _N>::mask_type vr=
        (fx == fxlh) | (isnan(fx) & isnan(fxlh));
    bool rc= all_of(vr);
    r &= rc;
    if (rc == false) {
        std::cerr << std::hexfloat;
        std::cerr << __FILE__ << ": " << __LINE__ << '\n';
        std::cerr << "sub vector test " << _N << " failed.\n";
        std::cerr << "x:    " << x << "\n";
        std::cerr << "fx:   " << fx << "\n";
        std::cerr << "fxlh: " << fxlh << "\n";
        std::cerr << "vr: " << vr << "\n";
        std::cerr << std::scientific;
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}

template <typename _T, std::size_t _N, typename _F>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x,
  const std::pair<vec<_T, _N>, vec<_T, _N> >& fx,
  exec_stats& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= exec_stats::hr_timer();
    auto fxl=_F::v(xl);
    uint64_t t1= exec_stats::hr_timer();
    auto fxh=_F::v(xh);
    uint64_t t2 = exec_stats::hr_timer();
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, fxh, st);

    vec<_T, _N> fxlh0(fxl.first, fxh.first);
    typename vec<_T, _N>::mask_type vr0=
        (fx.first == fxlh0) | (isnan(fx.first) & isnan(fxlh0));
    bool r0= all_of(vr0);
    r &= r0;

    vec<_T, _N> fxlh1(fxl.second, fxh.second);
    typename vec<_T, _N>::mask_type vr1=
        (fx.second == fxlh1) | (isnan(fx.second) & isnan(fxlh1));
    bool r1= all_of(vr1);
    r &= r1;

    if (r0 == false || r1==false) {
        std::cerr << std::hexfloat;
        std::cerr << __FILE__ << ": "<<  __LINE__ << '\n';
        std::cerr << "sub vector test " << _N << " failed.\n";
        std::cerr << "x:    " << x << "\n";
        std::cerr << "fx.first:    " << fx.first << "\n";
        std::cerr << "fx.second:   " << fx.second << "\n";
        std::cerr << "fxlh.first:  " << fxlh0 << "\n";
        std::cerr << "fxlh.second: " << fxlh1 << "\n";
        std::cerr << "vr.first:    " << vr0 << "\n";
        std::cerr << "vr.second:   " << vr1 << "\n";
        std::cerr << std::scientific;
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _I>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x,
  const std::pair<vec<_I, _N>, vec<_T, _N> >& fx,
  exec_stats& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= exec_stats::hr_timer();
    auto fxl=_F::v(xl);
    uint64_t t1= exec_stats::hr_timer();
    auto fxh=_F::v(xh);
    uint64_t t2 = exec_stats::hr_timer();
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, fxh, st);

    vec<_I, _N> ifxlh(fxl.first, fxh.first);
    typename vec<_I, _N>::mask_type vi=(fx.first == ifxlh);
    bool ri= all_of(vi);
    r &= ri;
    vec<_T, _N> fxlh(fxl.second, fxh.second);
    typename vec<_T, _N>::mask_type vr=
        (fx.second == fxlh) | (isnan(fx.second) & isnan(fxlh));
    bool rc= all_of(vr);
    r &= rc;
    if (rc == false || ri==false) {
        std::cerr << std::hexfloat;
        std::cerr << __FILE__ << ": "<<  __LINE__ << '\n';
        std::cerr << "sub vector test " << _N << " failed.\n";
        std::cerr << "x:    " << x << "\n";
        std::cerr << "fxi:   " << fx.first << "\n";
        std::cerr << "fx:   " << fx.second << "\n";
        std::cerr << "fxlhi: " << ifxlh << "\n";
        std::cerr << "fxlh: " << fxlh << "\n";
        std::cerr << "vr: " << vr << "\n";
        std::cerr << std::scientific;
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}

template <typename _T, std::size_t _N, typename _F>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x, const vec<_T, _N>& y,
  const vec<_T, _N>& fx, exec_stats& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    vec<_T, _N2> yl=low_half(y);
    vec<_T, _N2> yh=high_half(y);
    uint64_t t0= exec_stats::hr_timer();
    vec<_T, _N2> fxl=_F::v(xl, yl);
    uint64_t t1= exec_stats::hr_timer();
    vec<_T, _N2> fxh=_F::v(xh, yh);
    uint64_t t2 = exec_stats::hr_timer();
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, yl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, yh, fxh, st);
    vec<_T, _N> fxlh(fxl, fxh);
    typename vec<_T, _N>::mask_type vr=
        (fx == fxlh) | (isnan(fx) & isnan(fxlh));
    bool rc=all_of(vr);
    r &= rc;
    if (rc == false) {
        std::cerr << __FILE__ << ": " << __LINE__ << '\n';
        std::cerr << "sub vector test " << _N << " failed.\n";
        std::cerr << "x:    " << x << "\n";
        std::cerr << "y:    " << y << "\n";
        std::cerr << "fx:   " << fx << "\n";
        std::cerr << "fxlh: " << fxlh << "\n";
        std::cerr << "vr: " << vr << "\n";
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}


template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(const _T(&a)[_N],
                                       exec_stats& st,
                                       bool speed_only,
                                       _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a);
    uint64_t t0 = exec_stats::hr_timer();
    auto vr=_F::v(va);
    uint64_t t1 = exec_stats::hr_timer();
    uint64_t t0i[_N], t1i[_N];
    // std::result_of<decltype(&F::r)(_T)>::type ri[_N];
    bool c;
    if (speed_only) {
        typename std::result_of<decltype(&_F::s)(_T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i] = exec_stats::hr_timer();
            r[i] = _F::s(a[i]);
            t1i[i]= exec_stats::hr_timer();
        }
        c= check(vr, r, _F::fname(), false, cmp);
    } else {
        typename std::result_of<decltype(&_F::r)(_T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i] = exec_stats::hr_timer();
            r[i] = _F::r(a[i]);
            t1i[i]= exec_stats::hr_timer();
        }
        c= check(vr, r, _F::fname(), true, cmp);
    }
    for (std::size_t i=0; i<_N; ++i) {
        st.insert(t0i[i], t1i[i], 0);
    }
    st.insert(t0, t1, _N);
    // std::cout << std::setprecision(18) << a << std::endl;
    bool cs= vec_parts<_T, _N, _F>::v(va, vr, st);
    // do only a subvector test if speed_only==true
    if (speed_only)
        c= cs;
    else
        c &= cs;
    if (c == false) {
        std::cerr << "va: " << va << std::endl;
        std::cerr << "vr: " << vr << std::endl;
        std::cerr << std::endl;
        if (cs == false) {
            std::cerr << "subvector test failed" << std::endl;
        }
    }
    return c;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP, typename _C>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(exec_stats& st,
                                       func_domain<_T> domain,
                                       bool speed_only,
                                       _CMP cmp, std::size_t cnt,
                                       const _C& tv)
{
    bool r = true;
    _T va[_N];
    
    for (auto b=std::begin(tv), e=std::end(tv);
         b!=e; ++b) {
        const auto& ai= *b;
        std::fill(std::begin(va), std::end(va), ai);
        r &=v(va, st, speed_only, cmp);
        std::fill(std::begin(va), std::end(va), -ai);
        r &=v(va, st, speed_only, cmp);
    }
    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib(domain.first, domain.second);


    std::cout << "[" << domain.first << ", " << domain.second << ")\n";
    const uint32_t N0=72;
    const uint32_t N1=4;
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    va[k] = distrib(rnd);
                }
                r &= v(va, st, speed_only, cmp);
            }
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
    }
    _T minus1= std::max(_T(-1), domain.first);
    _T plus1= std::min(_T(1), domain.second);
    if (minus1 < plus1 && (minus1 != domain.first || plus1 != domain.second)) {
        std::cout << std::endl;
        _T nplus1=std::nextafter(plus1, _T(2)*plus1);
        uniform_real_distribution<_T>
            distrib1(minus1, nplus1);
        std::cout << "[" << minus1 << ", " << nplus1 << ")\n";
        for (uint32_t l=0; l< N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                for (std::size_t i=0; i<cnt; ++i) {
                    for (std::size_t k=0; k<_N; ++k) {
                        va[k] = distrib1(rnd);
                    }
                    r &= v(va, st, speed_only, cmp);
                }
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    if (r == true) {
        std::cout << _F::fname() << ' '
                  << __func__ << _N << " to v1 test passed " << std::endl;
    } else {
        std::cerr << _F::fname() << ' '
                  << __func__ << _N << " to v1 test failed " << std::endl;
    }
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(exec_stats& st,
                                       func_domain<_T> domain,
                                       bool speed_only,
                                       _CMP cmp, std::size_t cnt,
                                       bool suppress_defaults)
{
    bool r;
    if (suppress_defaults == false) {
        r=v(st, domain, speed_only, cmp, cnt, default_arguments<_T>::values);
    } else {
        const std::vector<_T> empty_def_args;
        r=v(st, domain, speed_only, cmp, cnt, empty_def_args);
    }
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::
v(const _T(&a)[_N], const _T(&b)[_N], exec_stats& st, bool speed_only, _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a);
    vec<_T, _N> vb=mem<vec<_T, _N> >::load(b);
    uint64_t t0=exec_stats::hr_timer();
    auto vr=_F::v(va, vb);
    uint64_t t1=exec_stats::hr_timer();
    uint64_t t0i[_N], t1i[_N];
    bool c;
    if (speed_only) {
        typename std::result_of<decltype(&_F::s)(_T, _T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i]=exec_stats::hr_timer();
            r[i] = _F::s(a[i], b[i]);
            t1i[i]=exec_stats::hr_timer();
        }
        c= check(vr, r, _F::fname(), false, cmp);
    } else {
        typename std::result_of<decltype(&_F::r)(_T, _T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i]=exec_stats::hr_timer();
            r[i] = _F::r(a[i], b[i]);
            t1i[i]=exec_stats::hr_timer();
        }
        c= check(vr, r, _F::fname(), true, cmp);
    }
    for (std::size_t i=0; i<_N; ++i) {
        st.insert(t0i[i], t1i[i], 0);
    }
    st.insert(t0, t1, _N);
    bool cs= vec_parts<_T, _N, _F>::v(va, vb, vr, st);
    // do only the subvector test if speed_only==true
    if (speed_only)
        c= cs;
    else
        c &= cs;
    if (c == false) {
        for (std::size_t i=0; i < _N; ++i) {
            std::cerr << _F::fname() << "("
                      << a[i] << ", " <<  b[i] << ") failed?.\n";
        }
        if (cs == false) {
            std::cerr << "subvector test failed" << std::endl;
        }
    }
    return c;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::v(exec_stats& st,
                                         func_domain<_T> domain_1,
                                         func_domain<_T> domain_2,
                                         bool speed_only,
                                         _CMP cmp, std::size_t cnt,
                                         bool suppress_defaults)
{
    bool r = true;
    _T va[_N], vb[_N];
    if (suppress_defaults == false) {
        const _T inf_nan_args []= {
            _T(0.0),
            _T(-0.0),
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
                std::fill(std::begin(va), std::end(va), ai);
                std::fill(std::begin(vb), std::end(vb), bi);
                r &= v(va, vb, st, speed_only, cmp);
                std::fill(std::begin(vb), std::end(vb), -bi);
                r &= v(va, vb, st, speed_only, cmp);
                std::fill(std::begin(va), std::end(va), -ai);
                r &= v(va, vb, st, speed_only, cmp);
                std::fill(std::begin(vb), std::end(vb), bi);
                r &= v(va, vb, st, speed_only, cmp);
            }
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
    const uint32_t N1=4;
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j< N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    va[k] = distrib1(rnd);
                    vb[k] = distrib2(rnd);
                }
                r &= v(va, vb, st, speed_only, cmp);
            }
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
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
        for (uint32_t l=0; l<N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                for (std::size_t i=0; i<cnt; ++i) {
                    for (std::size_t k=0; k<_N; ++k) {
                        va[k] = distrib_1_1(rnd);
                        vb[k] = distrib_1_2(rnd);
                    }
                    r &= v(va, vb, st, speed_only, cmp);
                }
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    if (r == true) {
        std::cout << _F::fname() << ' '
                  << __func__ << _N << " to v1 test passed " << std::endl;
    } else {
        std::cerr << _F::fname() << ' '
                  << __func__ << _N << " to v1 test failed " << std::endl;
    }
    return r;
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_OF_FP_FUNCS_H__
