//
// Copyright (C) 2010-2026 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_TEST_OF_FP_FUNCS_H__)
#define __CFTAL_TEST_OF_FP_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/f32_f64.h>
#include <cftal/test/work_queue.h>
#include <cftal/test/exec_stats.h>
#include <cftal/test/func_domain.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>
#include <future>
#include <thread>
#include <list>
#include <array>

namespace cftal {
    namespace test {

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

        // the default additional arguments to test
        template <typename _T>
        struct default_arguments {
            static
            const std::vector<_T> values;
        };

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
            template <typename _T1, typename _T2, std::size_t _M>
            static
            bool
            v(const vec<_T1, _N>& x, const vec<_T2, _N>& y,
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

            template <typename _T1, typename _T2, std::size_t _M>
            static
            bool
            v(const vec<_T1, 1>& x, const vec<_T2, 1>& y,
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
              uint32_t thread_cnt,
              _CMP cmp,
              std::size_t cnt,
              const _C& tv);

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T> domain,
              bool speed_only,
              uint32_t thread_cnt,
              _CMP cmp=_CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults= false);

            using array_t = std::array<_T, _N>;

            template <typename _CMP=cmp_t<_T> >
            static
            bool calc(const array_t& ai,
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
              uint32_t thread_cnt,
              _CMP cmp,
              std::size_t cnt,
              const _C& tv) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain,
                                                 speed_only,
                                                 thread_cnt,
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
              uint32_t thread_cnt,
              _CMP cmp,
              std::size_t cnt,
              bool suppress_defaults=false) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain,
                                                 speed_only,
                                                 thread_cnt,
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
                uint32_t thread_cnt= speed_only ?
                    0 : std::numeric_limits<uint32_t>::max();
                return v(st, domain,
                         speed_only,
                         thread_cnt,
                         cmp, cnt,
                         suppress_defaults);
            }
        };

        template <typename _T, std::size_t _N, typename _F,
                  typename _T1=_T, typename _T2=_T>
        struct of_fp_func_2 {

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T1> domain_1 = default_domain<_T1>::value,
              func_domain<_T2> domain_2 = default_domain<_T2>::value,
              bool speed_only = false,
              uint32_t thread_cnt=std::numeric_limits<uint32_t>::max(),
              _CMP cmp=_CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false);

            using array_1_t = std::array<_T1, _N>;
            using array_2_t = std::array<_T2, _N>;

            template <typename _CMP=cmp_t<_T> >
            static
            bool calc(const array_1_t& ai, const array_2_t& bi,
                      exec_stats<_N>& st, bool speed_only, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F,
                  typename _T1=_T, typename _T2=_T>
        struct of_fp_func_2_up_to {

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T1> domain_1,
              func_domain<_T2> domain_2,
              bool speed_only,
              uint32_t thread_cnt,
              _CMP cmp,
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false) {
                bool r=of_fp_func_2<_T, _N, _F, _T1, _T2>::
                    v(st, domain_1, domain_2,
                      speed_only,
                      thread_cnt,
                      cmp, cnt,
                      suppress_defaults);
                return r;
            }

            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats<_N>& st,
              func_domain<_T1> domain_1 = default_domain<_T1>::value,
              func_domain<_T2> domain_2 = default_domain<_T2>::value,
              bool speed_only = false,
              _CMP cmp= _CMP(),
              std::size_t cnt=default_cnt,
              bool suppress_defaults=false) {
                uint32_t thread_cnt= speed_only ?
                    0 : std::numeric_limits<uint32_t>::max();
                return v(st, domain_1, domain_2,
                         speed_only,
                         thread_cnt,
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
    _T(1.0-0x1p-23),
    _T(1.0-0x1p-24),
    _T(1.0-0x1p-52),
    _T(1.0-0x1p-53),
    _T(1.0),
    _T(1.0+0x1p-53),
    _T(1.0+0x1p-52),
    _T(1.0+0x1p-24),
    _T(1.0+0x1p-23),
    _T(1.5),
    _T(2.0-0x1p-22),
    _T(2.0-0x1p-23),
    _T(2.0-0x1p-24),
    _T(2.0-0x1p-51),
    _T(2.0-0x1p-52),
    _T(2.0-0x1p-53),
    _T(2),
    _T(2.0+0x1p-53),
    _T(2.0+0x1p-52),
    _T(2.0+0x1p-51),
    _T(2.0+0x1p-24),
    _T(2.0+0x1p-23),
    _T(2.0+0x1p-22),
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
    // sin
    _T(23.5619444748828748),
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
    _T(-2.457021951675415039e+00),
    // y0 f64
    _T(2.049895304256149586e+02),
    // j0 f32
    _T(-2.193278948355061352e+33),
    _T(-6.307293931122133098e+37),
    _T(-7.641344679031603200e+16),
    _T(2.841169323672596088e+23),
    // j1 f32
    _T(2.319091691391733073e+25),
    // y0 f32
    _T(1.964130973815917969e+01),
    // f32 payne hanek
    _T(7.729178919452901966e+28),
    _T(-1.522788990976000000e+12),
    _T(8.117626639064560252e+22),
    _T(1.545835783890580393e+29),
    _T(uint64_t(1ULL<<23)),
    _T(uint64_t(1ULL<<52)),
    _T(0x1.0p31),
    _T(0x1.0p21),
    _T(0x1.0p23),
    _T(0x1.0p24),
    _T(0x1.0p51),
    _T(0x1.0p52),
    std::numeric_limits<_T>::denorm_min(),
    _T(2.0*std::numeric_limits<_T>::denorm_min()),
    _T(4.0*std::numeric_limits<_T>::denorm_min()),
    _T(8.0*std::numeric_limits<_T>::denorm_min()),
    _T(16.0*std::numeric_limits<_T>::denorm_min()),
    _T(32.0*std::numeric_limits<_T>::denorm_min()),
    _T(64.0*std::numeric_limits<_T>::denorm_min()),
    std::numeric_limits<_T>::min(),
    _T(2.0*std::numeric_limits<_T>::min()),
    _T(4.0*std::numeric_limits<_T>::min()),
    _T(8.0*std::numeric_limits<_T>::min()),
    _T(16.0*std::numeric_limits<_T>::min()),
    _T(32.0*std::numeric_limits<_T>::min()),
    _T(64.0*std::numeric_limits<_T>::min()),
    std::numeric_limits<_T>::max(),
    _T(1.0/2.0*std::numeric_limits<_T>::max()),
    _T(1.0/4.0*std::numeric_limits<_T>::max()),
    _T(1.0/8.0*std::numeric_limits<_T>::max()),
    _T(1.0/16.0*std::numeric_limits<_T>::max()),
    _T(1.0/32.0*std::numeric_limits<_T>::max()),
    _T(1.0/64.0*std::numeric_limits<_T>::max()),
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
template <typename _T1, typename _T2, std::size_t _M>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T1, _N>& x,
  const vec<_T2, _N>& y,
  const vec<_T, _N>& fx, exec_stats<_M>& st)
{
    const int _N2=_N/2;
    vec<_T1, _N2> xl=low_half(x);
    vec<_T1, _N2> xh=high_half(x);
    vec<_T2, _N2> yl=low_half(y);
    vec<_T2, _N2> yh=high_half(y);
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
calc(const array_t& a, exec_stats<_N>& st,
     bool speed_only, _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a.data());
    uint64_t t0 = exec_stats<_N>::hr_timer();
    auto vr=_F::v(va);
    uint64_t t1 = exec_stats<_N>::hr_timer();
    uint64_t t0i[_N], t1i[_N];
    bool c;
    if (speed_only) {
        // typename std::result_of<decltype(&_F::s)(_T)>::type r[_N];
        typename std::invoke_result<decltype(&_F::s), _T>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i] = exec_stats<_N>::hr_timer();
            r[i] = _F::s(a[i]);
            t1i[i]= exec_stats<_N>::hr_timer();
        }
        c= check(vr, r, _F::fname(), false, cmp);
    } else {
        // typename std::result_of<decltype(&_F::r)(_T)>::type r[_N];
        typename std::invoke_result<decltype(&_F::r),_T>::type r[_N];
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
    if (speed_only) {
        c= cs;
    } else {
        c &= cs;
    }
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
                                       uint32_t thread_cnt,
                                       _CMP cmp, std::size_t cnt,
                                       const _C& tv)
{
    bool r = true;
    array_t va;

    if (!(std::is_same_v<_T, f16_t> || std::is_same_v<_T, bf16_t>) ||
        speed_only==true) {
        for (auto b=std::begin(tv), e=std::end(tv);
            b!=e; ++b) {
            const auto& ai= *b;
            std::fill(std::begin(va), std::end(va), ai);
            r &=calc(va, st, speed_only, cmp);
            std::fill(std::begin(va), std::end(va), -ai);
            r &=calc(va, st, speed_only, cmp);
        }
    }
    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib(domain.first, domain.second);

    if (!(std::is_same_v<_T, f16_t> || std::is_same_v<_T, bf16_t>) ||
        speed_only==true) {
        std::cout << "[" << domain.first << ", " << domain.second << ")\n";
    }
    const uint32_t N0=72;
    const uint32_t N1=4;

#if 1
    using vec_t = array_t;
    using job_t = std::vector<vec_t>;

    struct thread_data {
        std::deque<bool> _vr;
        std::vector<std::thread> _vt;
        std::vector<exec_stats<_N> > _vst;
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
                             uint32_t thread_cnt)->void {
        if (thread_cnt == 0) {
            r &= calc_vec(std::move(va), st, speed_only, cmp);
            return;
        }
        if (v_res._vt.empty()) {
            const uint32_t max_thrd_cnt=
                std::max(std::thread::hardware_concurrency(), 1u);
            uint32_t thrd_cnt=std::min(max_thrd_cnt, thread_cnt);
            // setup
            v_res._vr.resize(thrd_cnt, true);
            v_res._vst.resize(thrd_cnt);
            for (std::size_t i=0; i<thrd_cnt; ++i) {
                auto ti=std::thread(thr_main,
                                    std::ref(v_res._wq),
                                    std::ref(v_res._vr[i]),
                                    std::ref(v_res._vst[i]),
                                    speed_only,
                                    cmp);
                v_res._vt.emplace_back(std::move(ti));
            }
        }
        v_res._wq.write(std::move(va));
    };
    auto wait_for_completion=[](bool& r,
                                exec_stats<_N>& st,
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
        for (const exec_stats<_N>& sti : v_res._vst) {
            st += sti;
        }
    };

    if constexpr ((std::is_same_v<_T, f16_t> || std::is_same_v<_T, bf16_t>)) {
        if (speed_only==false) {
            if constexpr (std::is_same_v<_T, f16_t>) {
                std::cout << "checking all binary16 inputs\n";
            } else if constexpr (std::is_same_v<_T, bf16_t>) {
                std::cout << "checking all bfloat16 inputs\n";
            } else {
                std::cout << "checking all of unknown 16 bit type inputs\n";
            }
            for (uint32_t l=0; l<0x10000; l+= _N*cnt) {
                std::vector<array_t> v_va(0);
                uint32_t j=l;
                for (std::size_t i=0; i<cnt && j < 0x10000; ++i) {
                    v_va.emplace_back(array_t());
                    for (std::size_t k=0; k<_N; ++k, ++j) {
                        uint16_t h=j;
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO>0
                        if (std::is_same_v<_T, bf16_t>) {
                            // flush to zero
                            uint16_t uh=h & 0x7fff;
                            if (uh > 0 && uh < 0x0080)
                                h= h & 0x8000;
                        }
#endif

                        v_va[i][k] =as<_T>(h);
                    }
                }
                exec_or_queue(r, v_res,
                              std::move(v_va),
                              st,
                              speed_only,
                              cmp,
                              thread_cnt);
            }
            wait_for_completion(r, st, v_res);
            if (r == true) {
                std::cout << _F::fname() << ' '
                        << __func__ << _N << " to v1 test passed "
                        << std::endl;
            } else {
                std::cerr << _F::fname() << ' '
                        << __func__ << _N << " to v1 test failed "
                        << std::endl;
            }
            return r;
        }
    }
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            std::vector<array_t> v_va(cnt);
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
                          thread_cnt);
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
    }
    _T minus1= std::max(_T(-1), domain.first);
    _T plus1= std::min(_T(1), domain.second);
    if (minus1 < plus1 && (minus1 != domain.first || plus1 != domain.second)) {
        std::cout << std::endl;
        using std::nextafter;
        _T nplus1=nextafter(plus1, _T(2)*plus1);
        uniform_real_distribution<_T>
            distrib1(minus1, nplus1);
        std::cout << "[" << minus1 << ", " << nplus1 << ")\n";
        for (uint32_t l=0; l< N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                std::vector<array_t> v_va(cnt);
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
                              thread_cnt);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    wait_for_completion(r, st, v_res);
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
        using std::nextafter;
        _T nplus1=nextafter(plus1, _T(2)*plus1);
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
                                       uint32_t thread_cnt,
                                       _CMP cmp, std::size_t cnt,
                                       bool suppress_defaults)
{
    bool r;
    if (suppress_defaults == false) {
        r=v(st, domain, speed_only, thread_cnt, cmp, cnt,
            default_arguments<_T>::values);
    } else {
        const std::vector<_T> empty_def_args;
        r=v(st, domain, speed_only, thread_cnt, cmp, cnt,
            empty_def_args);
    }
    return r;
}

template <typename _T, std::size_t _N, typename _F,
          typename _T1, typename _T2>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F, _T1, _T2>::
calc(const array_1_t& a, const array_2_t& b,
     exec_stats<_N>& st, bool speed_only, _CMP cmp)
{
    vec<_T1, _N> va=mem<vec<_T1, _N> >::load(a.data());
    vec<_T2, _N> vb=mem<vec<_T2, _N> >::load(b.data());
    uint64_t t0=exec_stats<_N>::hr_timer();
    auto vr=_F::v(va, vb);
    uint64_t t1=exec_stats<_N>::hr_timer();
    uint64_t t0i[_N], t1i[_N];
    bool c;
    if (speed_only) {
        // typename std::result_of<decltype(&_F::s)(_T, _T)>::type r[_N];
        typename std::invoke_result<decltype(&_F::s),_T1, _T2>::type r[_N];
        for (std::size_t i=0; i<_N; ++i) {
            t0i[i]=exec_stats<_N>::hr_timer();
            r[i] = _F::s(a[i], b[i]);
            t1i[i]=exec_stats<_N>::hr_timer();
        }
        c= check(vr, r, _F::fname(), false, cmp);
    } else {
        // typename std::result_of<decltype(&_F::r)(_T, _T)>::type r[_N];
        typename std::invoke_result<decltype(&_F::r), _T1, _T2>::type r[_N];
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
    if (speed_only) {
        c= cs;
    } else {
        c &= cs;
    }
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

template <typename _T, std::size_t _N, typename _F,
          typename _T1, typename _T2>
template <typename _CMP>
bool
cftal::test::
of_fp_func_2<_T, _N, _F, _T1, _T2>::v(exec_stats<_N>& st,
                                      func_domain<_T1> domain_1,
                                      func_domain<_T2> domain_2,
                                      bool speed_only,
                                      uint32_t thread_cnt,
                                      _CMP cmp, std::size_t cnt,
                                      bool suppress_defaults)
{
    bool r = true;
    array_1_t va;
    array_2_t vb;
    if (suppress_defaults == false) {
        const auto& inf_nan_args_1=default_arguments<_T1>::values;
        const auto& inf_nan_args_2=default_arguments<_T2>::values;

        for (auto ab=std::begin(inf_nan_args_1), ae=std::end(inf_nan_args_1);
            ab != ae; ++ab) {
            _T1 ai=*ab;
            for (auto bb=std::begin(inf_nan_args_2),
                     be=std::end(inf_nan_args_2);
                bb !=be; ++bb) {
                _T2 bi= *bb;
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
	if constexpr (std::is_same_v<_T1, _T2>) {
	    static constexpr const _T1 crit_arg_pairs[]={
		// pow (double, double) no fma:
		_T1(9.925633628733863123e-01), _T1(8.126575857146648923e+04)
	    };
	    for (auto ab=std::begin(crit_arg_pairs), ae=std::end(crit_arg_pairs);
		 ab != ae;) {
		_T1 ai=*ab; ++ab;
		_T2 bi=*ab; ++ab;
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
    uniform_real_distribution<_T1>
        distrib1(domain_1.first, domain_1.second);
    uniform_real_distribution<_T2>
        distrib2(domain_2.first, domain_2.second);

    std::cout << "[" << domain_1.first << ", " << domain_1.second
              << ") x [" << domain_2.first << ", " << domain_2.second
              << ")\n";
    const uint32_t N0=72;
    const uint32_t N1=4;

#if 1
    using job_t = std::pair<std::vector<array_1_t>,
                            std::vector<array_2_t> >;

    struct thread_data {
        std::deque<bool> _vr;
        std::vector<std::thread> _vt;
        std::vector<exec_stats<_N> > _vst;
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
                             uint32_t thread_cnt)->void {
        if (thread_cnt == 0) {
            r &= calc_vec(std::move(va), st, speed_only, cmp);
            return;
        }
        if (v_res._vt.empty()) {
            const uint32_t max_thrd_cnt=
                std::max(std::thread::hardware_concurrency(), 1u);
            uint32_t thrd_cnt=std::min(max_thrd_cnt, thread_cnt);
            // setup
            v_res._vr.resize(thrd_cnt, true);
            v_res._vst.resize(thrd_cnt);
            for (std::size_t i=0; i<thrd_cnt; ++i) {
                auto ti=std::thread(thr_main,
                                    std::ref(v_res._wq),
                                    std::ref(v_res._vr[i]),
                                    std::ref(v_res._vst[i]),
                                    speed_only,
                                    cmp);
                v_res._vt.emplace_back(std::move(ti));
            }
        }
        v_res._wq.write(std::move(va));
    };
    auto wait_for_completion=[](bool& r,
                                exec_stats<_N>& st,
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
        for (const exec_stats<_N>& sti : v_res._vst) {
            st += sti;
        }
    };
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j< N0; ++j) {
            std::vector<array_1_t> v_va(cnt);
            std::vector<array_2_t> v_vb(cnt);
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
                          thread_cnt);
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
    }
    const bool is_T1_fp=is_floating_point<_T1>::value;
    using std::max;
    using std::min;
    using std::nextafter;
    _T1 a_minus1= max(_T1(-1), domain_1.first);
    _T1 a_plus1= min(_T1(1), domain_1.second);
    if (is_T1_fp && a_minus1 < a_plus1 &&
        (a_minus1 != domain_1.first || a_plus1 != domain_1.second)) {
        std::cout << std::endl;
        _T1 a_nplus1=nextafter(a_plus1, _T1(2)*a_plus1);
        uniform_real_distribution<_T1>
            distrib_1_1(a_minus1, a_nplus1);
        uniform_real_distribution<_T2>
            distrib_1_2(domain_2.first, domain_2.second);
        std::cout << "[" << a_minus1 << ", " << a_nplus1
                  << ") x [" << domain_2.first << ", " << domain_2.second
                  << ")\n";
        for (uint32_t l=0; l<N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                std::vector<array_1_t> v_va(cnt);
                std::vector<array_2_t> v_vb(cnt);
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
                                thread_cnt);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    const bool is_T2_fp=is_floating_point<_T2>::value;
    _T2 b_minus1= max(_T2(-1), domain_2.first);
    _T2 b_plus1= min(_T2(1), domain_2.second);
    if (is_T2_fp && b_minus1 < b_plus1 &&
        (b_minus1 != domain_2.first || b_plus1 != domain_2.second)) {
        std::cout << std::endl;
        _T2 b_nplus1=nextafter(b_plus1, _T2(2)*b_plus1);
        uniform_real_distribution<_T1>
            distrib_1_1(domain_1.first, domain_1.second);
        uniform_real_distribution<_T2>
            distrib_1_2(b_minus1, b_nplus1);
        std::cout << "[" << domain_1.first << ", " << domain_1.second
                  << ") x [" << b_minus1 << ", " << b_nplus1
                  << ")\n";
        for (uint32_t l=0; l<N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                std::vector<array_1_t> v_va(cnt);
                std::vector<array_2_t> v_vb(cnt);
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
                                thread_cnt);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    if (is_T2_fp && is_T1_fp && a_minus1 < a_plus1 && b_minus1 < b_plus1 &&
        (a_minus1 != domain_1.first || a_plus1 != domain_1.second ||
         b_minus1 != domain_2.first || b_plus1 != domain_2.second)) {
        std::cout << std::endl;
        _T1 a_nplus1=nextafter(a_plus1, _T1(2)*a_plus1);
        _T2 b_nplus1=nextafter(b_plus1, _T2(2)*b_plus1);
        uniform_real_distribution<_T1>
            distrib_1_1(a_minus1, a_nplus1);
        uniform_real_distribution<_T2>
            distrib_1_2(b_minus1, b_nplus1);
        std::cout << "[" << a_minus1 << ", " << a_nplus1
                  << ") x [" << b_minus1 << ", " << b_nplus1
                  << ")\n";
        for (uint32_t l=0; l<N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                std::vector<array_1_t> v_va(cnt);
                std::vector<array_2_t> v_vb(cnt);
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
                                thread_cnt);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    wait_for_completion(r, st, v_res);
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
    using std::max;
    using std::min;
    using std::nextafter;
    _T1 a_minus1= max(_T1(-1), domain_1.first);
    _T1 a_plus1= min(_T1(1), domain_1.second);
    _T2 b_minus1= max(_T2(-1), domain_2.first);
    _T2 b_plus1= min(_T2(1), domain_2.second);
    if (a_minus1 < a_plus1 && b_minus1 < b_plus1) {
        std::cout << std::endl;
        _T1 a_nplus1=nextafter(a_plus1, _T1(2)*a_plus1);
        _T2 b_nplus1=nextafter(b_plus1, _T2(2)*b_plus1);
        uniform_real_distribution<_T1>
            distrib_1_1(a_minus1, a_nplus1);
        uniform_real_distribution<_T2>
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
