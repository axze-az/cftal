//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_TEST_OF_VSVEC_H__)
#define __CFTAL_TEST_OF_VSVEC_H__ 1
#include <cftal/vsvec.h>
#include <cftal/test/exec_stats.h>
#include <cftal/test/func_domain_common.h>
#include <cftal/test/check_exp.h>
#include <cftal/test/check_expm1.h>
#include <cftal/test/check_log.h>
#include <cftal/test/check_log1p.h>
#include <cftal/test/check_erf.h>
#include <cftal/test/check_erfc.h>
#include <cftal/test/check_tgamma.h>
#include <cftal/test/uniform_distribution.h>
#include <iostream>
#include <iomanip>
#include <random>

namespace cftal {

    namespace test {

        template <size_t _N>
        struct vsvec_exec_stats {
            const exec_stats<_N>& _stats;
            size_t _len;
            vsvec_exec_stats(const exec_stats<_N>& st, size_t len)
                : _stats(st), _len(len) {}
        };

        template <size_t _N>
        std::ostream&
        operator<<(std::ostream& s, const vsvec_exec_stats<_N>& lst);

        template <typename _T, typename _A=aligned_allocator<_T, 64> >
        struct of_vsvec {

            constexpr
            static
            const size_t LVEC_LEN=((1024<<1)*8)/(sizeof(_T))-1;

            template <size_t _N>
            static
            bool
            equal(const _T* pr, const vec<_T, _N>& r);

            template <size_t _N>
            static
            bool
            equal(const _T* pr, const vec<_T, _N>& r,
                  const vec<_T, _N>& x,
                  const std::string& msg);

            template <size_t _N>
            static
            bool
            equal(const _T* pr, const vec<_T, _N>& r,
                  const vec<_T, _N>& x, const vec<_T, _N>& y,
                  const std::string& msg);

            template <size_t _N, typename _LF, typename _SF>
            static
            bool
            f1(exec_stats<_N>& st,
               const vsvec<_T, _A>& x,
               const std::string& msg,
               _LF vsvec_f, _SF scal_f);

            template <size_t _N, typename _LF, typename _SF>
            static
            bool
            f1(exec_stats<_N>& st,
               const func_domain<_T>& d,
               const std::string& msg,
               _LF vsvec_f, _SF scal_f);

            template <size_t _N, typename _LF, typename _SF>
            static
            bool
            f2(exec_stats<_N>& st,
               const vsvec<_T, _A>& x, const vsvec<_T, _A>& y,
               const std::string& msg,
               _LF vsvec_f, _SF scal_f);

            template <size_t _N, typename _LF, typename _SF>
            static
            bool
            f2(exec_stats<_N>& st,
               const func_domain<_T>& dx,
               const func_domain<_T>& dy,
               const std::string& msg,
               _LF vsvec_f, _SF scal_f);

            static
            bool
            execute();
        };
    }
}

template <std::size_t _N>
std::ostream&
cftal::test::operator<<(std::ostream& s, const vsvec_exec_stats<_N>& lst)
{
    const exec_stats<_N>& st=lst._stats;
    std::size_t n= _N + 1;
    s << "execution statistics\n";

    size_t vlen=lst._len;
    double t=st._tics[0]._v;
    uint64_t ei=st._evals[0]._v;
    double tc=ei ? t/double(ei) : 0.0;
    double te=vlen ? tc/vlen : tc;
    s << "vec-len: " << std::setw(5) << vlen  << " calls: "
      << std::setw(14) << ei << " tics/call: "
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

    for (std::size_t i=1; i<n; i=i*2) {
        double t=st._tics[i]._v;
        uint64_t ei=st._evals[i]._v;
        double tc=ei ? t/double(ei) : 0.0;
        double te=i ? tc/i : tc;
        s << "vec-len: " << std::setw(5) << i << " calls: "
          << std::setw(14) << ei << " tics/call: "
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

template <typename _T, typename _A>
template <std::size_t _N>
bool
cftal::test::of_vsvec<_T, _A>::
equal(const _T* pr, const vec<_T, _N>& vr)
{
    vec<_T, _N> v=mem<vec<_T, _N> >::load(pr, _N);
    typename vec<_T, _N>::mask_type c=v==vr;
    if constexpr (cftal::is_floating_point<_T>::value == true) {
        c = c | (isnan(v) & isnan(vr));
    }
    return all_of(c);
}

template <typename _T, typename _A>
template <std::size_t _N>
bool
cftal::test::of_vsvec<_T, _A>::
equal(const _T* pr, const vec<_T, _N>& vr,
      const vec<_T, _N>& x, const std::string& msg)
{
    if (!equal(pr, vr)) {
        std::ostringstream s;
        s << msg << " failed\n";
        vec<_T, _N> v=mem<vec<_T, _N> >::load(pr, _N);
        s << "result:\n" << v << "\n"
          << "expected:\n" <<  vr << "\n"
          << "x:\n" << x << "\n";
        std::cerr << s.str();
        return false;
    }
    return true;
}

template <typename _T, typename _A>
template <std::size_t _N>
bool
cftal::test::of_vsvec<_T, _A>::
equal(const _T* pr, const vec<_T, _N>& vr,
      const vec<_T, _N>& x, const vec<_T, _N>& y,
      const std::string& msg)
{
    if (!equal(pr, vr)) {
        std::ostringstream s;
        s << msg << " failed\n";
        vec<_T, _N> v=mem<vec<_T, _N> >::load(pr, _N);
        s << "result:\n" << v << "\n"
          << "expected:\n" <<  vr << "\n"
          << "x:\n" << x << "\n"
          << "y:\n" << y << "\n";
        std::cerr << s.str();
        return false;
    }
    return true;
}

template <typename _T, typename _A>
template <std::size_t _N, typename _LF, typename _SF>
bool
cftal::test::of_vsvec<_T, _A>::f1(exec_stats<_N>& st,
                                  const vsvec<_T, _A>& x,
                                  const std::string& msg,
                                  _LF vsvec_f, _SF scal_f)
{
    bool r=true;
    uint64_t t0 = exec_stats<_N>::hr_timer();
    vsvec<_T, _A> lr= vsvec_f(x);
    uint64_t t1 = exec_stats<_N>::hr_timer();
    st.insert(t0, t1, 0);
    size_t n=x.size();
    const _T* px=&x[0];
    const _T* pr=&lr[0];

    const size_t NN=32;
    const size_t nn= n & (~(NN-1));
    for (size_t i=0; i<nn; i+=NN) {
        vec<_T, NN> vx=mem<vec<_T, NN> >::load(px, NN);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, NN> rx=scal_f(vx);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, NN);
        r &= equal(pr, rx, vx, msg);
        px += NN;
        pr += NN;
    }
    if (NN > 16 && (n&16) != 0) {
        vec<_T, 16> vx=mem<vec<_T, 16> >::load(px, 16);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 16> rx=scal_f(vx);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 16);
        r &= equal(pr, rx, vx, msg);
        px += 16;
        pr += 16;
    }
    if (NN > 8 && (n&8) != 0) {
        vec<_T, 8> vx=mem<vec<_T, 8> >::load(px, 8);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 8> rx=scal_f(vx);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 8);
        r &= equal(pr, rx, vx, msg);
        px += 8;
        pr += 8;
    }
    if (NN > 4 && (n&4) != 0) {
        vec<_T, 4> vx=mem<vec<_T, 4> >::load(px, 4);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 4> rx=scal_f(vx);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 4);
        r &= equal(pr, rx, vx, msg);
        px += 4;
        pr += 4;
    }
    if (NN > 2 && (n&2) != 0) {
        vec<_T, 2> vx=mem<vec<_T, 2> >::load(px, 2);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 2> rx=scal_f(vx);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 2);
        r &= equal(pr, rx, vx, msg);
        px += 2;
        pr += 2;
    }
    if (NN > 1 && (n&1) != 0) {
        vec<_T, 1> vx=mem<vec<_T, 1> >::load(px, 1);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 1> rx=scal_f(vx);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 1);
        r &= equal(pr, rx, vx, msg);
        px += 1;
        pr += 1;
    }
    return true;
}

template <typename _T, typename _A>
template <std::size_t _N, typename _LF, typename _SF>
bool
cftal::test::of_vsvec<_T, _A>::f1(exec_stats<_N>& st,
                                  const func_domain<_T>& d,
                                  const std::string& msg,
                                  _LF vsvec_f, _SF scal_f)
{
    std::mt19937_64 rnd;

    using distribution_t = select_t<is_floating_point_v<_T>,
                                    uniform_real_distribution<_T>,
                                    std::uniform_int_distribution<_T> >;
    distribution_t distrib(d.first, d.second);

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
    const uint32_t N0=72;
    const uint32_t N1=4;
    const uint32_t NN=64;
#else
    const uint32_t N0=72;
    const uint32_t N1=4;
    const uint32_t NN=(2047*2048)/(LVEC_LEN);
#endif
    bool r=true;
    vsvec<_T, _A> x(_T(0), LVEC_LEN);
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            for (uint32_t k=0; k<NN; ++k) {
                for (size_t i=0; i<LVEC_LEN; ++i) {
                    x[i] = distrib(rnd);
                }
                r &= f1(st, x, msg, vsvec_f, scal_f);
            }
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
    }
    return r;
}

template <typename _T, typename _A>
template <std::size_t _N, typename _LF, typename _SF>
bool
cftal::test::of_vsvec<_T, _A>::f2(exec_stats<_N>& st,
                                  const vsvec<_T, _A>& x,
                                  const vsvec<_T, _A>& y,
                                  const std::string& msg,
                                  _LF vsvec_f, _SF scal_f)
{
    bool r=true;
    uint64_t t0 = exec_stats<_N>::hr_timer();
    vsvec<_T, _A> lr= vsvec_f(x, y);
    uint64_t t1 = exec_stats<_N>::hr_timer();
    st.insert(t0, t1, 0);
    size_t n=x.size();
    const _T* px=&x[0];
    const _T* py=&y[0];
    const _T* pr=&lr[0];

    const size_t NN=32;
    const size_t nn= n & (~(NN-1));
    for (size_t i=0; i<nn; i+=NN) {
        vec<_T, NN> vx=mem<vec<_T, NN> >::load(px, NN);
        vec<_T, NN> vy=mem<vec<_T, NN> >::load(py, NN);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, NN> rx=scal_f(vx, vy);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, NN);
        r &= equal(pr, rx, vx, vy, msg);
        px += NN;
        py += NN;
        pr += NN;
    }
    if (NN > 16 && (n&16) != 0) {
        vec<_T, 16> vx=mem<vec<_T, 16> >::load(px, 16);
        vec<_T, 16> vy=mem<vec<_T, 16> >::load(py, 16);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 16> rx=scal_f(vx, vy);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 16);
        r &= equal(pr, rx, vx, vy, msg);
        px += 16;
        py += 16;
        pr += 16;
    }
    if (NN > 8 && (n&8) != 0) {
        vec<_T, 8> vx=mem<vec<_T, 8> >::load(px, 8);
        vec<_T, 8> vy=mem<vec<_T, 8> >::load(py, 8);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 8> rx=scal_f(vx, vy);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 8);
        r &= equal(pr, rx, vx, vy, msg);
        px += 8;
        py += 8;
        pr += 8;
    }
    if (NN > 4 && (n&4) != 0) {
        vec<_T, 4> vx=mem<vec<_T, 4> >::load(px, 4);
        vec<_T, 4> vy=mem<vec<_T, 4> >::load(py, 4);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 4> rx=scal_f(vx, vy);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 4);
        r &= equal(pr, rx, vx, vy, msg);
        px += 4;
        py += 4;
        pr += 4;
    }
    if (NN > 2 && (n&2) != 0) {
        vec<_T, 2> vx=mem<vec<_T, 2> >::load(px, 2);
        vec<_T, 2> vy=mem<vec<_T, 2> >::load(py, 2);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 2> rx=scal_f(vx, vy);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 2);
        r &= equal(pr, rx, vx, vy, msg);
        px += 2;
        py += 2;
        pr += 2;
    }
    if (NN > 1 && (n&1) != 0) {
        vec<_T, 1> vx=mem<vec<_T, 1> >::load(px, 1);
        vec<_T, 1> vy=mem<vec<_T, 1> >::load(py, 1);
        uint64_t t2=exec_stats<_N>::hr_timer();
        vec<_T, 1> rx=scal_f(vx, vy);
        uint64_t t3=exec_stats<_N>::hr_timer();
        st.insert(t2, t3, 1);
        r &= equal(pr, rx, vx, vy, msg);
        px += 1;
        py += 1;
        pr += 1;
    }
    return true;
}

template <typename _T, typename _A>
template <std::size_t _N, typename _LF, typename _SF>
bool
cftal::test::of_vsvec<_T, _A>::f2(exec_stats<_N>& st,
                                  const func_domain<_T>& dx,
                                  const func_domain<_T>& dy,
                                  const std::string& msg,
                                  _LF vsvec_f, _SF scal_f)
{
    std::mt19937_64 rnd;
    using distribution_t = select_t<is_floating_point_v<_T>,
                                    uniform_real_distribution<_T>,
                                    std::uniform_int_distribution<_T> >;
    distribution_t distrib_x(dx.first, dx.second);
    distribution_t distrib_y(dy.first, dy.second);

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
    const uint32_t N0=72;
    const uint32_t N1=4;
    const uint32_t NN=64;
#else
    const uint32_t N0=72;
    const uint32_t N1=4;
    const uint32_t NN=(2047*2048)/(LVEC_LEN);
#endif
    bool r=true;
    vsvec<_T> x(_T(0), LVEC_LEN);
    vsvec<_T> y(_T(0), LVEC_LEN);
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            for (uint32_t k=0; k<NN; ++k) {
                for (size_t i=0; i<LVEC_LEN; ++i) {
                    x[i] = distrib_x(rnd);
                }
                for (size_t i=0; i<LVEC_LEN; ++i) {
                    y[i] = distrib_y(rnd);
                }
                r &= f2(st, x, y, msg, vsvec_f, scal_f);
            }
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
    }
    return r;
}

template <typename _T, typename _A>
bool
cftal::test::of_vsvec<_T, _A>::execute()
{
    auto make_val=[](const _T& v) ->auto {
        if constexpr (is_floating_point_v<_T>) {
            return v;
        } else if constexpr (is_signed_v<_T>) {
            return int64_t(v);
        } else {
            return uint64_t(v);
        }
    };


    using v_t = vsvec<_T, _A>;
    using vm_t = typename v_t::mask_type;
    v_t x0(_T(42.0), LVEC_LEN);

    vm_t x0_eq_x0=x0==_T(0.0);
    vm_t x1=select(x0_eq_x0, x0, x0);
    vm_t x2=select(x0_eq_x0, x0+x0, _T(2.0)*x0);

    const func_domain<_T>& d_full=domain_full_x_axis<_T>::domains[0];

    bool r = true;

    if constexpr (is_signed_v<_T>) {
        exec_stats<33> st_neg;
        const std::string msg_neg="operator-(x)";
        std::cout << "testing " << msg_neg
                <<  " in range ["  << make_val(d_full.first)
                << ", "  << make_val(d_full.second) << "]\n";
        r &= f1(st_neg, d_full, msg_neg,
                [](const v_t& x)->v_t {
                    return -x;
                },
                [](const auto& x)->auto {
                    return -x;
                });
        std::cout << vsvec_exec_stats<33>(st_neg, LVEC_LEN) << std::endl;
    }

    exec_stats<33> st_add;
    const std::string msg_add="operator+";
    std::cout << "testing " << msg_add
              <<  " in range ["  << make_val(d_full.first)
              << ", "  << make_val(d_full.second) << "]\n";
    r &= f2(st_add, d_full, d_full, msg_add,
            [](const v_t& x,
               const v_t& y)->v_t {
                return x+y;
            },
            [](const auto& x, const auto& y)->auto {
                return x+y;
            });
    std::cout << vsvec_exec_stats<33>(st_add, LVEC_LEN) << std::endl;

    exec_stats<33> st_sub;
    const std::string msg_sub="operator-";
    std::cout << "testing " << msg_sub
              <<  " in range ["  << make_val(d_full.first)
              << ", "  << make_val(d_full.second) << "]\n";
    r &= f2(st_sub, d_full, d_full, msg_sub,
            [](const v_t& x,
               const v_t& y)->v_t {
                return x-y;
            },
            [](const auto& x, const auto& y)->auto {
                return x-y;
            });
    std::cout << vsvec_exec_stats<33>(st_sub, LVEC_LEN) << std::endl;

    exec_stats<33> st_mul;
    const std::string msg_mul="operator*";
    std::cout << "testing " << msg_mul
              <<  " in range ["  << make_val(d_full.first)
              << ", "  << make_val(d_full.second) << "]\n";
    r &= f2(st_mul, d_full, d_full, msg_mul,
            [](const v_t& x,
               const v_t& y)->v_t {
                return x*y;
            },
            [](const auto& x, const auto& y)->auto {
                return x*y;
            });
    std::cout << vsvec_exec_stats<33>(st_mul, LVEC_LEN) << std::endl;

    exec_stats<33> st_div;
    const std::string msg_div="operator/";
    std::cout << "testing " << msg_div
              <<  " in range ["  << make_val(d_full.first)
              << ", "  << make_val(d_full.second) << "]\n";
    r &= f2(st_div, d_full, d_full, msg_div,
            [](const v_t& x,
               const v_t& y)->v_t {
                return x/y;
            },
            [](const auto& x, const auto& y)->auto {
                return x/y;
            });
    std::cout << vsvec_exec_stats<33>(st_div, LVEC_LEN) << std::endl;

    if constexpr (is_signed_v<_T>) {
        exec_stats<33> st_abs;
        const std::string msg_abs="abs";
        std::cout << "testing " << msg_abs
                  <<  " in range ["  << make_val(d_full.first)
                  << ", "  << make_val(d_full.second) << "]\n";
        r &= f1(st_abs, d_full, msg_abs,
                [](const v_t& x)->v_t {
                    return abs(x);
                },
                [](const auto& x)->auto {
                    return abs(x);
                });
        std::cout << vsvec_exec_stats<33>(st_abs, LVEC_LEN) << std::endl;
    }

    if constexpr (is_floating_point_v<_T>) {
        exec_stats<33> st_pow;
        const std::string msg_pow="pow";
        std::cout << "testing " << msg_pow << '\n';
        r &= f2(st_pow, d_full, d_full, msg_pow,
                [](const v_t& x,
                const v_t& y)->v_t {
                    return pow(x,y);
                },
                [](const auto& x, const auto& y)->auto {
                    return pow(x, y);
                });
        std::cout << vsvec_exec_stats<33>(st_pow, LVEC_LEN) << std::endl;

        exec_stats<33> st_exp;
        const func_domain<_T>& d_exp=domain_exp<_T>::domains[0];
        const std::string msg_exp="exp";
        std::cout << "testing " << msg_exp << '\n';
        r &= f1(st_exp, d_exp, msg_exp,
                [](const v_t& x)->v_t {
                    return exp(x);
                },
                [](const auto& x)->auto {
                    return exp(x);
                });
        std::cout << vsvec_exec_stats<33>(st_exp, LVEC_LEN) << std::endl;

        exec_stats<33> st_expm1;
        const func_domain<_T>& d_expm1=domain_expm1<_T>::domains[0];
        const std::string msg_expm1="expm1";
        std::cout << "testing " << msg_expm1 << '\n';
        r &= f1(st_expm1, d_expm1, msg_expm1,
                [](const v_t& x)->v_t {
                    return expm1(x);
                },
                [](const auto& x)->auto {
                    return expm1(x);
                });
        std::cout << vsvec_exec_stats<33>(st_expm1, LVEC_LEN) << std::endl;

        exec_stats<33> st_log;
        const func_domain<_T>& d_log=domain_log<_T>::domains[0];
        const std::string msg_log="log";
        std::cout << "testing " << msg_log << '\n';
        r &= f1(st_log, d_log, msg_log,
                [](const v_t& x)->v_t {
                    return log(x);
                },
                [](const auto& x)->auto {
                    return log(x);
                });
        std::cout << vsvec_exec_stats<33>(st_log, LVEC_LEN) << std::endl;

        exec_stats<33> st_log1p;
        const func_domain<_T>& d_log1p=domain_log1p<_T>::domains[0];
        const std::string msg_log1p="log1p";
        std::cout << "testing " << msg_log1p << '\n';
        r &= f1(st_log1p, d_log1p, msg_log1p,
                [](const v_t& x)->v_t {
                    return log1p(x);
                },
                [](const auto& x)->auto {
                    return log1p(x);
                });
        std::cout << vsvec_exec_stats<33>(st_log1p, LVEC_LEN) << std::endl;

        exec_stats<33> st_erf;
        const func_domain<_T>& d_erf=domain_erf<_T>::domains[0];
        const std::string msg_erf="erf";
        std::cout << "testing " << msg_erf << '\n';
        f1(st_erf, d_erf, msg_erf,
        [](const v_t& x)->v_t {
            return erf(x);
        },
        [](const auto& x)->auto {
            return erf(x);
        });
        std::cout << vsvec_exec_stats<33>(st_erf, LVEC_LEN) << std::endl;

        exec_stats<33> st_erfc;
        const func_domain<_T>& d_erfc=domain_erfc<_T>::domains[0];
        const std::string msg_erfc="erfc";
        std::cout << "testing " << msg_erfc << '\n';
        r &= f1(st_erfc, d_erfc, msg_erfc,
                [](const v_t& x)->v_t {
                    return erfc(x);
                },
                [](const auto& x)->auto {
                    return erfc(x);
                });
        std::cout << vsvec_exec_stats<33>(st_erfc, LVEC_LEN) << std::endl;

#if 0
        exec_stats<33> st_tgamma;
        const func_domain<_T>& d_tgamma=domain_tgamma<_T>::domains[0];
        const std::string msg_tgamma="tgamma";
        std::cout << "testing " << msg_tgamma << '\n';
        r &= f1(st_tgamma, d_tgamma, msg_tgamma,
                [](const v_t& x)->v_t {
                    return tgamma(x);
                },
                [](const auto& x)->auto {
                    return tgamma(x);
                });
        std::cout << vsvec_exec_stats<33>(st_tgamma, LVEC_LEN) << std::endl;
#endif
    }
    return r;
}

#endif // __CFTAL_TEST_OF_VSVEC_H__
