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
#if !defined (__CFTAL_TEST_OF_VSVEC_FUNCS_H__)
#define __CFTAL_TEST_OF_VSVEC_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec.h>
#include <cftal/test/exec_stats.h>
#include <cftal/test/of_math_funcs.h>

namespace cftal {
    namespace test {

        template <typename _T, typename _A>
        typename vsvec<_T, _A>::mask_type
        cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b);

        template <typename _T, typename _A, typename _CMP>
        typename vsvec<_T, _A>::mask_type
        cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b,
               _CMP cmp);

        template <typename _T, typename _A>
        bool
        all_cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b);

        template <typename _T, typename _A>
        bool
        all_cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b,
                   cmp_ulp<_T> cmp);

        template <typename _T, typename _A>
        struct vsvec_error {
            using vsvec_t=vsvec<_T, _A>;
            using mask_t=typename vsvec<_T, _A>::mask_type;
            const mask_t& _m;
            const vsvec_t& _x;
            const vsvec_t& _ref;
            const vsvec_t& _y;
            vsvec_error(const mask_t& m,
                       const vsvec_t& x,
                       const vsvec_t& ref,
                       const vsvec_t& y)
                : _m(m), _x(x), _ref(ref), _y(y) {}
        };

        template <typename _T, typename _A>
        vsvec_error<_T, _A>
        make_vsvec_error(const typename vsvec<_T, _A>::mask_type m,
                        const vsvec<_T, _A>& x,
                        const vsvec<_T, _A>& ref,
                        const vsvec<_T, _A>& y) {
            return vsvec_error<_T, _A>(m, x, ref, y);
        }

        template <typename _T, typename _A>
        std::ostream&
        operator<<(std::ostream& s, const vsvec_error<_T, _A>& e);

        struct vsvec_exec_stats {
            const exec_stats<1>& _st;
            size_t _vec_len;
            vsvec_exec_stats(const exec_stats<1>& st, size_t v)
                : _st(st), _vec_len(v) {}
        };
        std::ostream&
        operator<<(std::ostream& s, const vsvec_exec_stats& lst);

        template <typename _CHECK, typename _T>
        struct of_vsvec_func {
            using vsvec_t = vsvec<_T>;

            template <typename _CMP>
            static
            bool
            calc_and_cmp(exec_stats<1>& st,
                         const vsvec_t& xi,
                         _CMP cmp);

            template <typename _CMP>
            static
            bool
            v(exec_stats<1>& st,
              const func_domain<_T>& d,
              uint32_t thread_cnt,
              _CMP cmt,
              size_t cnt,
              size_t vec_len);

        };

    }
}

template <typename _T, typename _A>
typename cftal::vsvec<_T, _A>::mask_type
cftal::test::
cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b)
{
    typename vsvec<_T, _A>::mask_type r=
        (a == b) | (isnan(a) & isnan(b));
    return r;
}

template <typename _T, typename _A>
typename cftal::vsvec<_T, _A>::mask_type
cftal::test::
cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b,
       cmp_ulp<_T> cmp)
{
    typename vsvec<_T, _A>::mask_type::value_type z(0);
    typename vsvec<_T, _A>::mask_type r(z, a.size());
    for (size_t i=0; i<a.size(); ++i) {
        if (cmp(a[i], b[i])==true)
            r[i]= -std::numeric_limits<_T>::quiet_NaN();
    }
    return r;
}

template <typename _T, typename _A>
bool
cftal::test::
all_cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b)
{
    auto vr=cmp_eq(a, b);
    bool r=all_of(vr);
    return r;
}

template <typename _T, typename _A>
bool
cftal::test::
all_cmp_eq(const vsvec<_T, _A>& a, const vsvec<_T, _A>& b,
           cmp_ulp<_T> cmp)
{
    bool r=true;
    for (size_t i=0; i<a.size(); ++i) {
        if (cmp(a[i], b[i])==false) {
            r=false;
            std::cout << "all_cmp_eq\n";
            break;
        }
    }
    return r;
}

template <typename _T, typename _A>
std::ostream&
cftal::test::operator<<(std::ostream& s, const vsvec_error<_T, _A>& ee)
{
    const auto& m= ee._m;
    using std::size;
    size_t n=size(m);
    s << "\ntotal vector size: " << n << '\n';
    for (size_t i=0; i<n; ++i) {
        using std::signbit;
        // m[i] contains ee._ref[i] == ee._y[i]
        // --> look for signbit(m[i]) == 0
        if (!signbit(m[i])) {
            s << "i=" << std::setw(4) << i
              << " m=" << m[i]
              << " x=" << std::setprecision(22) << ee._x[i] << '\n'
              << "ref=" << std::setprecision(22) << ee._ref[i]
              << " y=" << std::setprecision(22) << ee._y[i]
              << " ref-y=" << std::setprecision(22) << ee._ref[i] - ee._y[i]
              << '\n';
        }
    }
    return s;
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const vsvec_exec_stats& lst)
{
    s << "execution statistics"
      << std::setw(42) << "relative"
      << std::setw(12) << "relative"
      << '\n';
    s << std::setw(26) << "calls"
      << std::setw(12) << "tics/call"
      << std::setw(12) << "tics/elem"
      << std::setw(12) << "tics/call"
      << std::setw(12) << "tics/elem"
      << '\n';
    for (size_t i=0; i<2; ++i) {
        if (i==0)
            s << "default function: ";
        else
            s << "vsvec function:   ";
        double t=lst._st._tics[i]._v;
        uint64_t ei=lst._st._evals[i]._v;
        double tc=ei ? t/double(ei) : 0.0;
        double te=lst._vec_len ? tc/lst._vec_len: tc;

        double t0=lst._st._tics[0]._v;
        uint64_t ei0=lst._st._evals[0]._v;
        double tc0=ei0 ? t0/double(ei0) : 0.0;
        double te0=lst._vec_len ? tc0/lst._vec_len : tc0;
        double rtc=tc0 != 0.0 ? tc/tc0 : 0.0;
        double rte= te0 != 0.0 ? te/te0 : te;

        s << std::setw(8) << ei << ' '
          << std::setprecision(1)
          << std::fixed
          << std::setw(11)
          << tc
          << ' '
          << std::setw(11)
          << te
          << ' '
          << std::setw(11)
          << std::setprecision(4)
          << rtc
          << ' '
          << std::setw(11)
          << rte
          << std::scientific
          << std::setprecision(22)
          << '\n';
    }
    return s;
}

template <typename _CHECK, typename _T>
template <typename _CMP>
bool
cftal::test::of_vsvec_func<_CHECK, _T>::
calc_and_cmp(exec_stats<1>& st,
             const vsvec_t& xi,
             _CMP cmp)
{
    uint64_t t0=st.hr_timer();
    vsvec_t r0=_CHECK::ref(xi);
    uint64_t t1=st.hr_timer();
    vsvec_t r1=_CHECK::v(xi);
    uint64_t t2=st.hr_timer();
    typename vsvec_t::mask_type mr01=cmp_eq(r0, r1, cmp);
    bool rc=all_of(mr01);
    if (rc == false) {
        // std::cout << mr01 << std::endl;
        std::cout << make_vsvec_error(mr01, xi, r0, r1) << '\n';
    }
    st.insert(t0, t1, 0);
    st.insert(t1, t2, 1);
    return rc;
}

template <typename _CHECK, typename _T>
template <typename _CMP>
bool
cftal::test::of_vsvec_func<_CHECK, _T>::
v(exec_stats<1>& st,
  const func_domain<_T>& d,
  uint32_t thread_cnt,
  _CMP cmp,
  size_t cnt,
  size_t vec_len)
{
    const auto& vd=default_arguments<_T>::values;
    using std::size, std::cbegin, std::cend;
    // size_t vds=size(vd);
    using vsvec_t = typename _CHECK::vsvec_t;
    vsvec_t xi(cbegin(vd), cend(vd));
    bool r=calc_and_cmp(st, xi, cmp);
    if (r==false) {
        std::cout << "default values test failed\n";
    }

    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib(d.first, d.second);

    std::cout << "[" << d.first << ", " << d.second << ")\n";
    const uint32_t N0=72;
    const uint32_t N1=4;

    using job_t = std::vector<vsvec_t>;

    struct thread_data {
        std::deque<bool> _vr;
        std::vector<std::thread> _vt;
        std::vector<exec_stats<1> > _vst;
        work_queue<job_t> _wq;
        thread_data() : _vr(), _vt(),
            _wq(std::max(std::thread::hardware_concurrency(), 1u)+2) {}
    };

    auto calc_vec=[](job_t va,
                     exec_stats<1>& st,
                     _CMP cmp)->bool {
        bool r= true;
        for (size_t i=0; i<va.size(); ++i) {
            r &= calc_and_cmp(st, va[i], cmp);
        }
        return r;
    };
    thread_data v_res;

    auto thr_main=[calc_vec](work_queue<job_t>& wq,
                             bool& r,
                             exec_stats<1>& st,
                             _CMP cmp)->void {
        job_t va;
        bool rt=r;
        while (wq.read(va)==true) {
            rt &= calc_vec(std::move(va), st, cmp);
        }
        r = rt;
    };
    auto exec_or_queue=
        [calc_vec, thr_main](bool& r,
                             thread_data& v_res,
                             job_t va,
                             exec_stats<1>& st,
                             uint32_t thread_cnt,
                             _CMP cmp)->void {
        if (thread_cnt == 0) {
            r &= calc_vec(std::move(va), st, cmp);
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
                                    cmp);
                v_res._vt.emplace_back(std::move(ti));
            }
        }
        v_res._wq.write(std::move(va));
    };
    auto wait_for_completion=[](bool& r,
                                exec_stats<1>& st,
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
        for (const exec_stats<1>& sti : v_res._vst) {
            st += sti;
        }
    };
    const vsvec_t zz(_T(0), vec_len);
    for (uint32_t l=0; l< N1; ++l) {
        for (uint32_t j=0; j<N0; ++j) {
            std::vector<vsvec_t> v_va(cnt, zz);
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<vec_len; ++k) {
                    v_va[i][k] = distrib(rnd);
                }
            }
            exec_or_queue(r, v_res,
                          std::move(v_va),
                          st,
                          thread_cnt,
                          cmp);
            std::cout << '.' << std::flush;
        }
        std::cout << std::endl;
    }
    _T minus1= std::max(_T(-1), d.first);
    _T plus1= std::min(_T(1), d.second);
    if (minus1 < plus1 && (minus1 != d.first || plus1 != d.second)) {
        std::cout << std::endl;
        _T nplus1=std::nextafter(plus1, _T(2)*plus1);
        uniform_real_distribution<_T>
            distrib1(minus1, nplus1);
        std::cout << "[" << minus1 << ", " << nplus1 << ")\n";
        for (uint32_t l=0; l< N1; ++l) {
            for (uint32_t j=0; j<N0; ++j) {
                std::vector<vsvec_t> v_va(cnt, zz);
                for (std::size_t i=0; i<cnt; ++i) {
                    for (std::size_t k=0; k<vec_len; ++k) {
                        v_va[i][k] = distrib1(rnd);
                    }
                }
                exec_or_queue(r, v_res,
                              std::move(v_va),
                              st,
                              thread_cnt,
                              cmp);
                std::cout << '.' << std::flush;
            }
            std::cout << std::endl;
        }
    }
    wait_for_completion(r, st, v_res);
    return r;
}

#endif
