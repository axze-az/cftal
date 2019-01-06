//
// Copyright Axel Zeuner 2010-2019. Use, modification and
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
#include <cftal/test/work_queue.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>
#include <future>
#include <thread>
#include <list>

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
        template <std::size_t _N>
        struct exec_stats {
            struct alignas(64) data_type {
                std::atomic<uint64_t> _v;
                char _pad[64-sizeof(_v)];
            };
            // the tics for the vectors of length 1...2^tics.size()
            data_type _tics[_N+1];
            // number of function calls
            data_type _evals[_N+1];
            // insert into _tics
            void insert(uint64_t tics_before, uint64_t tics_after,
                        unsigned n) {
                uint64_t ta=std::max(tics_before, tics_after);
                uint64_t tb=std::min(tics_before, tics_after);
                uint64_t d=ta - tb;
                _tics[n]._v += d;
                ++(_evals[n]._v);
            }
            // constructor
            exec_stats() {
                for (std::size_t i=0; i<_N+1; ++i) {
                    _tics[i]._v = 0;
                    _evals[i]._v = 0;
                }
            }
            // timer function
            static
            uint64_t hr_timer() { return rdtsc(); }
        };
        template <std::size_t _N>
        std::ostream&
        operator<<(std::ostream& s, const exec_stats<_N>& st);

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
            template <std::size_t _M>
            static
            bool
            v(const vec<_T, _N>& x, const vec<_T, _N>& fx,
              exec_stats<_M>& st);
            // check for functions with one argument returning a pair
            template <std::size_t _M>
            static
            bool
            v(const vec<_T, _N>& x,
              const std::pair<vec<_T, _N>, vec<_T, _N> >& fx,
              exec_stats<_M>& st);
            // check for functions with one argument and an additional
            // result pointer
            template <typename _I, std::size_t _M>
            static
            bool
            v(const vec<_T, _N>& x,
              const std::pair<vec<_I, _N>, vec<_T, _N> >& fx,
              exec_stats<_M>& st);
            // check for functions with two arguments
            template <std::size_t _M>
            static
            bool
            v(const vec<_T, _N>& x, const vec<_T, _N>& y,
              const vec<_T, _N>& fx, exec_stats<_M>& st);
        };

        // specialization to stop recursion
        template <typename _T, typename _F>
        struct vec_parts<_T, 1, _F> {
            template <std::size_t _M>
            static
            bool
            v(const vec<_T, 1>& x, const vec<_T, 1>& fx,
              exec_stats<_M>& st) {
                static_cast<void>(x);
                static_cast<void>(fx);
                static_cast<void>(st);
                return true;
            }

            template <typename _I, std::size_t _M>
            static
            bool
            v(const vec<_T, 1>& x,
              const std::pair<vec<_I, 1>, vec<_T, 1> >& fx,
              exec_stats<_M>& st) {
                static_cast<void>(x);
                static_cast<void>(fx);
                static_cast<void>(st);
                return true;
            }

            template <std::size_t _M>
            static
            bool
            v(const vec<_T, 1>& x, const vec<_T, 1>& y,
              const vec<_T, 1>& fx, exec_stats<_M>& st) {
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
            v(exec_stats<_N>& st,
              func_domain<_T> domain,
              bool speed_only,
              bool mt,
              _CMP cmp,
              std::size_t cnt,
              const _C& tv);

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain,
              bool speed_only,
              bool mt,
              _CMP cmp=_CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults= false);

            template <typename _CMP=cmp_t<_T> >
            static
            bool calc(const _T(&ai)[_N],
                      exec_stats<_N>& st,
                      bool speed_only, _CMP cmp=_CMP());
        };

        // test of vector function _F(vec<_T, _N>) up to length N
        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_up_to {

            // tv is a container with additional values to test
            template <typename _CMP, typename _C>
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain,
              bool speed_only,
              bool mt,
              _CMP cmp,
              std::size_t cnt,
              const _C& tv) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain,
                                                 speed_only,
                                                 mt,
                                                 cmp, cnt,
                                                 tv);
                return r;
            }

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain,
              bool speed_only,
              bool mt,
              _CMP cmp,
              std::size_t cnt,
              bool suppress_defaults=false) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain,
                                                 speed_only,
                                                 mt,
                                                 cmp, cnt,
                                                 suppress_defaults);
                return r;
            }

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain = default_domain<_T>::value,
              bool speed_only = false,
              _CMP cmp= _CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults= false) {
                return v(st, domain,
                         speed_only,
                         speed_only == false,
                         cmp, cnt,
                         suppress_defaults);
            }
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2 {

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              bool speed_only = false,
              bool mt = true,
              _CMP cmp=_CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false);

            template <typename _CMP=cmp_t<_T> >
            static
            bool calc(const _T(&ai)[_N], const _T(&bi)[_N],
                      exec_stats<_N>& st, bool speed_only, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2_up_to {

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain_1,
              func_domain<_T> domain_2,
              bool speed_only,
              bool mt,
              _CMP cmp,
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false) {
                bool r=of_fp_func_2<_T, _N, _F>::v(st, domain_1, domain_2,
                                                   speed_only,
                                                   mt,
                                                   cmp, cnt,
                                                   suppress_defaults);
                return r;
            }

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              bool speed_only = false,
              _CMP cmp= _CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false) {
                return v(st, domain_1, domain_2,
                         speed_only,
                         speed_only==false,
                         cmp, cnt,
                         suppress_defaults);
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

template <std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s, const exec_stats<_N>& st)
{
    std::size_t n= _N + 1;
    s << "execution statistics\n";
    for (std::size_t i=0; i<n; i=((i==0) ? 1: i*2)) {
        double t=st._tics[i]._v;
        uint64_t ei=st._evals[i]._v;
        double tc=ei ? t/double(ei) : 0.0;
        double te=i ? tc/i : tc;
        s << "vec-len: " << std::setw(2) << i << " calls: "
          << std::setw(16) << ei << " tics/call: "
          << std::setprecision(1)
          << std::fixed
          << std::setw(9)
          << tc
          << " tics/elem: "
          << std::setw(7)
          << te
          << std::scientific
          << std::setprecision(22)
          << "\n";
    }
    return s;
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
template <std::size_t _M>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x, const vec<_T, _N>& fx, exec_stats<_M>& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= exec_stats<_M>::hr_timer();
    vec<_T, _N2> fxl=_F::v(xl);
    uint64_t t1= exec_stats<_M>::hr_timer();
    vec<_T, _N2> fxh=_F::v(xh);
    uint64_t t2 = exec_stats<_M>::hr_timer();
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, fxh, st);
    vec<_T, _N> fxlh(fxl, fxh);
    typename vec<_T, _N>::mask_type vr=
        (fx == fxlh) | (isnan(fx) & isnan(fxlh));
    bool rc= all_of(vr);
    r &= rc;
    if (rc == false) {
        std::ostringstream s;
        s.copyfmt(std::cerr);
        s << std::hexfloat;
        s << __FILE__ << ": " << __LINE__ << '\n';
        s << "sub vector test " << _N << " failed.\n";
        s << "x:    " << x << "\n";
        s << "fx:   " << fx << "\n";
        s << "fxlh: " << fxlh << "\n";
        s << "vr: " << vr << "\n";
        std::cerr << s.str();
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <std::size_t _M>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x,
  const std::pair<vec<_T, _N>, vec<_T, _N> >& fx,
  exec_stats<_M>& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= exec_stats<_M>::hr_timer();
    auto fxl=_F::v(xl);
    uint64_t t1= exec_stats<_M>::hr_timer();
    auto fxh=_F::v(xh);
    uint64_t t2 = exec_stats<_M>::hr_timer();
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
        std::ostringstream s;
        s.copyfmt(std::cerr);
        s << std::hexfloat;
        s << __FILE__ << ": "<<  __LINE__ << '\n';
        s << "sub vector test " << _N << " failed.\n";
        s << "x:    " << x << "\n";
        s << "fx.first:    " << fx.first << "\n";
        s << "fx.second:   " << fx.second << "\n";
        s << "fxlh.first:  " << fxlh0 << "\n";
        s << "fxlh.second: " << fxlh1 << "\n";
        s << "vr.first:    " << vr0 << "\n";
        s << "vr.second:   " << vr1 << "\n";
        std::cerr << s.str();
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _I, std::size_t _M>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x,
  const std::pair<vec<_I, _N>, vec<_T, _N> >& fx,
  exec_stats<_M>& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= exec_stats<_M>::hr_timer();
    auto fxl=_F::v(xl);
    uint64_t t1= exec_stats<_M>::hr_timer();
    auto fxh=_F::v(xh);
    uint64_t t2 = exec_stats<_M>::hr_timer();
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
        std::ostringstream s;
        s.copyfmt(std::cerr);
        s << std::hexfloat;
        s << __FILE__ << ": "<<  __LINE__ << '\n';
        s << "sub vector test " << _N << " failed.\n";
        s << "x:    " << x << "\n";
        s << "fxi:   " << fx.first << "\n";
        s << "fx:   " << fx.second << "\n";
        s << "fxlhi: " << ifxlh << "\n";
        s << "fxlh: " << fxlh << "\n";
        s << "vr: " << vr << "\n";
        std::cerr << s.str();
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <std::size_t _M>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x, const vec<_T, _N>& y,
  const vec<_T, _N>& fx, exec_stats<_M>& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    vec<_T, _N2> yl=low_half(y);
    vec<_T, _N2> yh=high_half(y);
    uint64_t t0= exec_stats<_M>::hr_timer();
    vec<_T, _N2> fxl=_F::v(xl, yl);
    uint64_t t1= exec_stats<_M>::hr_timer();
    vec<_T, _N2> fxh=_F::v(xh, yh);
    uint64_t t2 = exec_stats<_M>::hr_timer();
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, yl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, yh, fxh, st);
    vec<_T, _N> fxlh(fxl, fxh);
    typename vec<_T, _N>::mask_type vr=
        (fx == fxlh) | (isnan(fx) & isnan(fxlh));
    bool rc=all_of(vr);
    r &= rc;
    if (rc == false) {
        std::ostringstream s;
        s.copyfmt(std::cerr);
        s << __FILE__ << ": " << __LINE__ << '\n';
        s << "sub vector test " << _N << " failed.\n";
        s << "x:    " << x << "\n";
        s << "y:    " << y << "\n";
        s << "fx:   " << fx << "\n";
        s << "fxlh: " << fxlh << "\n";
        s << "vr: " << vr << "\n";
        std::cerr << s.str();
        std::exit(3);
    }
    st.insert(t0, t1, _N2);
    st.insert(t1, t2, _N2);
    return r;
}


template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::
calc(const _T(&a)[_N], exec_stats<_N>& st,
     bool speed_only, _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a);
    uint64_t t0 = exec_stats<_N>::hr_timer();
    auto vr=_F::v(va);
    uint64_t t1 = exec_stats<_N>::hr_timer();
    uint64_t t0i[_N], t1i[_N];
    // std::result_of<decltype(&F::r)(_T)>::type ri[_N];
    bool c;
    if (speed_only) {
        typename std::result_of<decltype(&_F::s)(_T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i] = exec_stats<_N>::hr_timer();
            r[i] = _F::s(a[i]);
            t1i[i]= exec_stats<_N>::hr_timer();
        }
        c= check(vr, r, _F::fname(), false, cmp);
    } else {
        typename std::result_of<decltype(&_F::r)(_T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i] = exec_stats<_N>::hr_timer();
            r[i] = _F::r(a[i]);
            t1i[i]= exec_stats<_N>::hr_timer();
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
        std::ostringstream s;
        s.copyfmt(std::cerr);
        s << "va: " << va << std::endl;
        s << "vr: " << vr << std::endl;
        s << std::endl;
        if (cs == false) {
            s << "subvector test failed" << std::endl;
        }
        std::cerr << s.str();
    }
    return c;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP, typename _C>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(exec_stats<_N>& st,
                                       func_domain<_T> domain,
                                       bool speed_only,
                                       bool mt,
                                       _CMP cmp, std::size_t cnt,
                                       const _C& tv)
{
    bool r = true;
    _T va[_N];

    for (auto b=std::begin(tv), e=std::end(tv);
         b!=e; ++b) {
        const auto& ai= *b;
        std::fill(std::begin(va), std::end(va), ai);
        r &=calc(va, st, speed_only, cmp);
        std::fill(std::begin(va), std::end(va), -ai);
        r &=calc(va, st, speed_only, cmp);
    }
    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib(domain.first, domain.second);


    std::cout << "[" << domain.first << ", " << domain.second << ")\n";
    const uint32_t N0=72;
    const uint32_t N1=4;

#if 1
#if 1
    using job_t = std::vector<_T[_N]>;

    struct thread_data {
        std::deque<bool> _vr;
        std::vector<std::thread> _vt;
        work_queue<job_t> _wq;
        thread_data() : _vr(), _vt(),
            _wq(std::max(std::thread::hardware_concurrency(), 1u)+2) {}
    };

    auto calc_vec=[](job_t va,
                     exec_stats<_N>& st,
                     bool speed_only,
                     _CMP cmp)->bool {
        bool r= true;
        for (size_t i=0; i<va.size(); ++i) {
            r &= calc(va[i], st, speed_only, cmp);
        }
        return r;
    };
    thread_data v_res;

    auto thr_main=[calc_vec](work_queue<job_t>& wq,
                             bool& r,
                             exec_stats<_N>& st,
                             bool speed_only,
                             _CMP cmp)->void {
        job_t va;
        bool rt=r;
        while (wq.read(va)==true) {
            rt &= calc_vec(std::move(va), st, speed_only, cmp);
        }
        r = rt;
    };
    auto exec_or_queue=
        [calc_vec, thr_main](bool& r,
                             thread_data& v_res,
                             job_t va,
                             exec_stats<_N>& st,
                             bool speed_only,
                             _CMP cmp,
                             bool mt)->void {
        if (mt == false) {
            r &= calc_vec(std::move(va), st, speed_only, cmp);
            return;
        }
        if (v_res._vt.empty()) {
            const size_t max_thrd_cnt=
                std::max(std::thread::hardware_concurrency(), 1u);
            // allow one core for generating the numbers
            const size_t thrd_cnt = max_thrd_cnt>1 ? max_thrd_cnt-1 : 1;
            // favour througput
            // const size_t thrd_cnt = max_thrd_cnt;
            // setup
            v_res._vr.resize(thrd_cnt, true);
            // std::thread t0;
            // bind_thread_to_cpu(t0, 0);
            for (std::size_t i=0; i<thrd_cnt; ++i) {
                auto ti=std::thread(thr_main,
                                    std::ref(v_res._wq),
                                    std::ref(v_res._vr[i]),
                                    std::ref(st),
                                    speed_only,
                                    cmp);
                // bind_thread_to_cpu(ti, i+1);
                v_res._vt.emplace_back(std::move(ti));
            }
        }
        v_res._wq.write(std::move(va));
    };
    auto wait_for_completion=[](bool& r,
                                thread_data& v_res)->void {
        if (v_res._vt.empty())
            return;
        v_res._wq.deactivate();
        for (std::size_t i=0; i<v_res._vt.size(); ++i) {
            v_res._vt[i].join();
        }
        for (bool b : v_res._vr) {
            r &= b;
        }
    };
#else
    std::list<std::future<bool> > v_res;

    auto exec_or_queue=[calc_vec](bool& r,
                                  std::list<std::future<bool> >& v_res,
                                  std::vector<_T[_N]> va,
                                  exec_stats<_N>& st,
                                  bool speed_only,
                                  _CMP cmp,
                                  bool mt)->void {
        if (mt == false) {
            r &= calc_vec(std::move(va), st, speed_only, cmp);
            return;
        }
        const size_t thrd_cnt=
            std::max(std::thread::hardware_concurrency(), 1u);
        while (v_res.size() > thrd_cnt) {
            auto ri= std::move(v_res.front());
            v_res.pop_front();
            r &= ri.get();
        }
        auto ri=std::async(std::launch::async,
                           calc_vec,
                           std::move(va),
                           std::ref(st),
                           speed_only,
                           cmp);
        v_res.emplace_back(std::move(ri));
    };

    auto wait_for_completion=[](bool& r,
                                std::list<std::future<bool> >& v_res) ->void {
        while (v_res.size() > 0) {
            auto ri= std::move(v_res.front());
            v_res.pop_front();
            r &= ri.get();
        }
    };
#endif
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            std::vector<_T[_N]> v_va(cnt);
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    v_va[i][k] = distrib(rnd);
                }
            }
            exec_or_queue(r, v_res,
                          std::move(v_va),
                          st,
                          speed_only,
                          cmp,
                          mt);
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
                std::vector<_T[_N]> v_va(cnt);
                for (std::size_t i=0; i<cnt; ++i) {
                    for (std::size_t k=0; k<_N; ++k) {
                        v_va[i][k] = distrib1(rnd);
                    }
                }
                exec_or_queue(r, v_res,
                              std::move(v_va),
                              st,
                              speed_only,
                              cmp,
                              mt);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    wait_for_completion(r, v_res);
#else
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    va[k] = distrib(rnd);
                }
                r &= calc(va, st, speed_only, cmp);
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
                    r &= calc(va, st, speed_only, cmp);
                }
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
#endif
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
cftal::test::of_fp_func<_T, _N, _F>::v(exec_stats<_N>& st,
                                       func_domain<_T> domain,
                                       bool speed_only,
                                       bool mt,
                                       _CMP cmp, std::size_t cnt,
                                       bool suppress_defaults)
{
    bool r;
    if (suppress_defaults == false) {
        r=v(st, domain, speed_only, mt, cmp, cnt,
            default_arguments<_T>::values);
    } else {
        const std::vector<_T> empty_def_args;
        r=v(st, domain, speed_only, mt, cmp, cnt,
            empty_def_args);
    }
    return r;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::
calc(const _T(&a)[_N], const _T(&b)[_N],
     exec_stats<_N>& st, bool speed_only, _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a);
    vec<_T, _N> vb=mem<vec<_T, _N> >::load(b);
    uint64_t t0=exec_stats<_N>::hr_timer();
    auto vr=_F::v(va, vb);
    uint64_t t1=exec_stats<_N>::hr_timer();
    uint64_t t0i[_N], t1i[_N];
    bool c;
    if (speed_only) {
        typename std::result_of<decltype(&_F::s)(_T, _T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i]=exec_stats<_N>::hr_timer();
            r[i] = _F::s(a[i], b[i]);
            t1i[i]=exec_stats<_N>::hr_timer();
        }
        c= check(vr, r, _F::fname(), false, cmp);
    } else {
        typename std::result_of<decltype(&_F::r)(_T, _T)>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i]=exec_stats<_N>::hr_timer();
            r[i] = _F::r(a[i], b[i]);
            t1i[i]=exec_stats<_N>::hr_timer();
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
        std::ostringstream s;
        s.copyfmt(std::cerr);
        for (std::size_t i=0; i < _N; ++i) {
            s << _F::fname() << "("
              << a[i] << ", " <<  b[i] << ") failed?.\n";
        }
        if (cs == false) {
            s<< "subvector test failed" << std::endl;
        }
        std::cerr << s.str();
    }
    return c;
}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::v(exec_stats<_N>& st,
                                         func_domain<_T> domain_1,
                                         func_domain<_T> domain_2,
                                         bool speed_only,
                                         bool mt,
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
                r &= calc(va, vb, st, speed_only, cmp);
                std::fill(std::begin(vb), std::end(vb), -bi);
                r &= calc(va, vb, st, speed_only, cmp);
                std::fill(std::begin(va), std::end(va), -ai);
                r &= calc(va, vb, st, speed_only, cmp);
                std::fill(std::begin(vb), std::end(vb), bi);
                r &= calc(va, vb, st, speed_only, cmp);
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

#if 1
#if 1
    using job_t = std::pair<std::vector<_T[_N]>, std::vector<_T[_N]> >;

    struct thread_data {
        std::deque<bool> _vr;
        std::vector<std::thread> _vt;
        work_queue<job_t> _wq;
        thread_data() : _vr(), _vt(),
            _wq(std::max(std::thread::hardware_concurrency(), 1u)+2) {}
    };

    auto calc_vec=[](job_t va,
                     exec_stats<_N>& st,
                     bool speed_only,
                     _CMP cmp)->bool {
        bool r= true;
        for (size_t i=0; i<va.first.size(); ++i) {
            r &= calc(va.first[i], va.second[i], st, speed_only, cmp);
        }
        return r;
    };
    thread_data v_res;

    auto thr_main=[calc_vec](work_queue<job_t>& wq,
                             bool& r,
                             exec_stats<_N>& st,
                             bool speed_only,
                             _CMP cmp)->void {
        job_t va;
        while (wq.read(va)==true) {
            r &= calc_vec(std::move(va), st, speed_only, cmp);
        }
    };
    auto exec_or_queue=
        [calc_vec, thr_main](bool& r,
                             thread_data& v_res,
                             job_t va,
                             exec_stats<_N>& st,
                             bool speed_only,
                             _CMP cmp,
                             bool mt)->void {
        if (mt == false) {
            r &= calc_vec(std::move(va), st, speed_only, cmp);
            return;
        }
        if (v_res._vt.empty()) {
            const size_t max_thrd_cnt=
                std::max(std::thread::hardware_concurrency(), 1u);
            // allow one core for generating the numbers
            const size_t thrd_cnt = max_thrd_cnt>1 ? max_thrd_cnt-1 : 1;
            // favour througput
            // const size_t thrd_cnt=max_thrd_cnt;
            // setup
            v_res._vr.resize(thrd_cnt, true);
            for (std::size_t i=0; i<thrd_cnt; ++i) {
                auto ti=std::thread(thr_main,
                                    std::ref(v_res._wq),
                                    std::ref(v_res._vr[i]),
                                    std::ref(st),
                                    speed_only,
                                    cmp);
                v_res._vt.emplace_back(std::move(ti));
            }
        }
        v_res._wq.write(std::move(va));
    };
    auto wait_for_completion=[](bool& r,
                                thread_data& v_res)->void {
        if (v_res._vt.empty())
            return;
        v_res._wq.deactivate();
        for (std::size_t i=0; i<v_res._vt.size(); ++i) {
            v_res._vt[i].join();
        }
        for (bool b : v_res._vr) {
            r &= b;
        }
    };
#else

    std::list<std::future<bool> > v_res;

    auto exec_or_queue=[](bool& r,
                          std::list<std::future<bool> >& v_res,
                          std::vector<_T[_N]> va,
                          std::vector<_T[_N]> vb,
                          exec_stats<_N>& st,
                          bool speed_only,
                          _CMP cmp,
                          bool mt)->void {
        if (mt == false) {
            for (size_t i=0; i<va.size(); ++i) {
                r &= calc(va[i], vb[i], st, speed_only, cmp);
            }
            return;
        }
        const size_t thrd_cnt=
            std::max(std::thread::hardware_concurrency(), 1u);
        while (v_res.size() > thrd_cnt) {
            auto ri= std::move(v_res.front());
            v_res.pop_front();
            r &= ri.get();
        }
        auto ri=std::async(std::launch::async,
                        [](std::vector<_T[_N]> va,
                           std::vector<_T[_N]> vb,
                           exec_stats<_N>& st,
                           bool speed_only,
                           _CMP cmp)->bool {
                                bool r=true;
                                for (size_t i=0; i<va.size(); ++i) {
                                    const _T (&a)[_N]=va[i];
                                    const _T (&b)[_N]=vb[i];
                                    r &= calc(a, b, st, speed_only, cmp);
                                }
                                return r;
                        },
                        std::move(va),
                        std::move(vb),
                        std::ref(st),
                        speed_only,
                        cmp);
        v_res.emplace_back(std::move(ri));
    };

    auto wait_for_completion=[](bool& r,
                                std::list<std::future<bool> >& v_res) ->void {
        while (v_res.size() > 0) {
            auto ri= std::move(v_res.front());
            v_res.pop_front();
            r &= ri.get();
        }
    };
#endif
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j< N0; ++j) {
            std::vector<_T[_N]> v_va(cnt), v_vb(cnt);
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    v_va[i][k] = distrib1(rnd);
                    v_vb[i][k] = distrib2(rnd);
                }
                // r &= calc(va, vb, st, speed_only, cmp);
            }
            job_t jb(std::move(v_va), std::move(v_vb));
            exec_or_queue(r, v_res,
                          std::move(jb),
                          st,
                          speed_only,
                          cmp,
                          mt);
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
                std::vector<_T[_N]> v_va(cnt), v_vb(cnt);
                for (std::size_t i=0; i<cnt; ++i) {
                    for (std::size_t k=0; k<_N; ++k) {
                        v_va[i][k] = distrib_1_1(rnd);
                        v_vb[i][k] = distrib_1_2(rnd);
                    }
                    // r &= calc(va, vb, st, speed_only, cmp);
                }
                job_t jb(std::move(v_va), std::move(v_vb));
                exec_or_queue(r, v_res,
                              std::move(jb),
                              st,
                              speed_only,
                              cmp,
                              mt);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    wait_for_completion(r, v_res);
#else
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j< N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    va[k] = distrib1(rnd);
                    vb[k] = distrib2(rnd);
                }
                r &= calc(va, vb, st, speed_only, cmp);
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
                    r &= calc(va, vb, st, speed_only, cmp);
                }
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
#endif
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
