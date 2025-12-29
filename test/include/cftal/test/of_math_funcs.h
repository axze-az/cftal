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
#if !defined (__CFTAL_TEST_OF_MATH_FUNCS_H__)
#define __CFTAL_TEST_OF_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/test/of_fp_funcs.h>
#include <cftal/test/call_mpfr.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {

        // divides cnt by 16 if CFTAL_DEV is set in the
        // environment
        std::size_t
        update_cnt(std::size_t cnt);

        std::string
        dirname(const std::string& fn);
        std::string
        append_filename(const std::string& dn, const std::string& fn);
        std::string
        filename_from_argv(const char* argv0, const std::string& fn);


        template <class _T>
        class func_arg_result {
            _T _a0;
            _T _a1;
            _T _r;
        public:
            constexpr func_arg_result(_T a, _T r) : _a0(a), _a1(a), _r(r) {}
            constexpr func_arg_result(_T a0, _T a1, _T r)
                : _a0(a0), _a1(a1), _r(r) {}
            const _T& arg0() const { return _a0; }
            const _T& arg1() const { return _a1; }
            const _T& res() const { return _r; }
        };

        // delete a # comment in a line
        std::string
        delete_comment(const std::string& s);
        // read file with hexadecimal 32 bit numbers for one and two arg
        // functions.
        // the lines contain a0high a0low [a1high a1low] reshigh reslow
        std::vector<func_arg_result<double> >
        read_double_file(const std::string& fn, bool two_args);

        template <typename _T, std::size_t _N, class _F>
        bool check_func_1(const std::vector<func_arg_result<_T> >& v,
                          uint32_t max_ulp, uint32_t max_err,
                          bool verbose);

        template <typename _T, std::size_t _N, class _F>
        bool check_func_2(const std::vector<func_arg_result<_T> >& v,
                          uint32_t max_ulp, uint32_t max_err,
                          bool verbose);

        // comparison against reference with non zero tolerance
        template <typename _T>
        struct cmp_ulp {
            uint32_t _ulp;
            std::shared_ptr<ulp_stats> _stats;
            cmp_ulp(uint32_t u, const std::shared_ptr<ulp_stats>& us )
                : _ulp(u), _stats(us) {}
            bool operator()(const _T& a, const _T& b) {
                ulp_stats* p= &*_stats;
                return f_eq_ulp(a, b, _ulp, p);
            }
            bool operator()(const _T& a, const std::tuple<_T, _T, _T>& b) {
                ulp_stats* p=&*_stats;
                return f_eq_ulp(a, b, _ulp, p);
            }
        };

        // comparison against reference with non zero tolerance for
        // functions returning pairs
        template <typename _T>
        struct cmp_ulp< std::pair<_T, _T> > {
            uint32_t _ulp;
            std::shared_ptr<ulp_stats> _stats0;
            std::shared_ptr<ulp_stats> _stats1;
            cmp_ulp(uint32_t u,
                    const std::shared_ptr<ulp_stats>& us0,
                    const std::shared_ptr<ulp_stats>& us1)
                : _ulp(u), _stats0(us0), _stats1(us1) {}
            bool operator()(const std::pair<_T, _T>& a,
                            const std::pair<_T, _T>& b) {
                ulp_stats* p0= &*_stats0;
                bool r0=f_eq_ulp(a.first, b.first, _ulp, p0);
                ulp_stats* p1= &*_stats1;
                bool r1=f_eq_ulp(a.second, b.second, _ulp, p1);
                return r0 && r1;
            }
            bool operator()(const std::pair<_T, _T>& a,
                            const std::pair<std::tuple<_T, _T, _T>,
                                            std::tuple<_T, _T, _T> >& b) {
                ulp_stats* p0= &*_stats0;
                bool r0=f_eq_ulp(a.first, b.first, _ulp, p0);
                ulp_stats* p1= &*_stats1;
                bool r1=f_eq_ulp(a.second, b.second, _ulp, p1);
                return r0 && r1;
            }
        };

        template <typename _I, typename _T>
        struct cmp_i_ulp : public cmp_ulp<_T> {
            cmp_i_ulp(uint32_t u, const std::shared_ptr<ulp_stats>& us)
                : cmp_ulp<_T>(u, us) {}
            using cmp_ulp<_T>::operator();
            // compare an _I, _T pair
            bool
            operator()(const std::pair<_I, _T>& a,
                       const std::pair<_I, _T>& b) {
                ulp_stats* p=&(*(this->_stats));
                bool r1=f_eq_ulp(a.second, b.second, this->_ulp, p);
                bool r2=a.first==b.first;
                return r1 && r2;
            }
            // compare an _I, _T pair with interval information
            bool
            operator()(const std::pair<_I, _T>& a,
                       const std::pair<_I, std::tuple<_T, _T, _T> >& b) {
                ulp_stats* p=&(*(this->_stats));
                bool r1=f_eq_ulp(a.second, b.second, this->_ulp, p);
#if 0
                if (r1== false) {
                    std::cout << "value failed" << std::endl;
                } else {
                    std::cout << "value success" << std::endl;
                }
#endif
                bool r2=a.first==b.first;
#if 0
                if (r2== false) {
                    std::cout << "sign failed" << std::endl;
                } else {
                    std::cout << "sign success" << std::endl;
                }
#endif
                return r1 && r2;
            }
        };

    }
}

template <typename _T, std::size_t _N, class _F>
bool
cftal::test::check_func_1(const std::vector<func_arg_result<_T> >& v,
                          uint32_t max_ulp, uint32_t max_err,
                          bool verbose)
{
    using vec_type = vec<_T, _N>;

    bool rc(true);
    uint32_t errs(0);
    std::size_t calls=v.size();
    int64_t ticks(0);
#if 0
    int64_t s_ticks(0);
#endif
    cmp_t<_T> cmp;
    for (std::size_t i=0; i< calls; ++i) {
        const func_arg_result<_T>& vi= v[i];
        _T a0 = vi.arg0();
        _T expected = vi.res();
        vec_type va0=a0;
        int64_t t1, t2;
#if 0
        int64_t t0= cftal::rdtsc();
        _T res = _F::s(a0);
#endif
        t1= cftal::rdtsc();
        vec_type vres = _F::v(va0);
        t2 = cftal::rdtsc();
#if 0
        s_ticks+= (t1 -t0);
#endif
        ticks += (t2 -t1);

        bool c= check(vres, expected, _F::fname(), verbose);
#if 0
        bool libc_err= (cmp(expected, res) == false);
        if (libc_err) {
            std::cerr << "libc error: " << res <<  " != "
                      << _F::fname()
                      << '(' << a0 << ")\n";
        }
#endif
        if (c == true)
            continue;
        _T vres0 = extract<0>(vres);
        int32_t ulp=0;
        try {
            ulp= distance(vres0, expected);
        }
        catch (...) {
            ulp = sizeof(_T) * 8;
        }
        if (max_ulp > 0) {
            if (verbose) {
                std::cerr << "ulp: " << ulp << '\n';
                std::cerr << _F::fname() << "("<< a0 << ")\n";
            }
            if ((ulp >= -int32_t(max_ulp)) && (ulp <= int32_t(max_ulp))) {
                continue;
            }
        }
        if (verbose==false) {
            std::cerr << "ulp: " << ulp << '\n';
            check(vres, expected, _F::fname(), true);
        }
        std::cerr << _F::fname() << "("<< a0 << ") failed.\n";
        rc = false;
        ++errs;
    }
    std::cout << "test cases: " << calls
              << " errors: " << errs << std::endl;
    std::cout << "error rate = ";
    if (calls) {
        std::cout << std::setprecision(6)
                  << double(errs)/calls << std::endl;
        std::cout << "ticks per call: "
                  << std::fixed << std::setprecision(2)
                  << double(ticks)/calls
                  << std::endl;
#if 0
        std::cout << "scalar ticks per call: "
                  << std::fixed << std::setprecision(2)
                  << double(s_ticks)/calls
                  << std::endl;
#endif
        std::cout << std::scientific;
    } else {
        std::cout << 0.0 << std::endl;
    }
    if (errs <= max_err)
        rc=true;
    if (rc == true) {
        std::cout << _F::fname() << " v" << _N << " test passed " << std::endl;
    } else {
        std::cerr << _F::fname() << " v" << _N << " test failed " << std::endl;
    }
    return rc;
}


template <typename _T, std::size_t _N, class _F>
bool
cftal::test::check_func_2(const std::vector<func_arg_result<_T> >& v,
                          uint32_t max_ulp, uint32_t max_err,
                          bool verbose)
{
    using vec_type = vec<_T, _N>;

    bool rc(true);
    uint32_t errs(0);
    std::size_t calls=v.size();
    int64_t ticks(0);
#if 0
    int64_t s_ticks(0);
#endif
    cmp_t<_T> cmp;
    for (std::size_t i=0; i< calls; ++i) {
        const func_arg_result<_T>& vi= v[i];
        _T a0 = vi.arg0();
        _T a1 = vi.arg1();
        _T expected = vi.res();
        vec_type va0=a0;
        vec_type va1=a1;
        int64_t t1, t2;
#if 0
        int64_t t0= cftal::rdtsc();
        _T res = _F::s(a0, a1);
#endif
        t1= cftal::rdtsc();
        vec_type vres = _F::v(va0, va1);
        t2 = cftal::rdtsc();
#if 0
        s_ticks+= (t1 -t0);
#endif
        ticks += (t2 -t1);

        bool c= check(vres, expected, _F::fname(), verbose);
#if 0
        bool libc_err= (cmp(expected, res) == false);
        if (libc_err) {
            std::cerr << "libc error: " << res <<  " != "
                      << _F::fname()
                      << '(' << a0 << ", " << a1 << ")\n";
        }
#endif
        if (c == true)
            continue;
        _T vres0 = extract<0>(vres);
        int32_t ulp=0;
        try {
            ulp=distance(vres0, expected);
        }
        catch (...) {
            ulp = sizeof(_T) * 8;
        }
        if (max_ulp > 0) {
            if (verbose) {
                std::cerr << "ulp: " << ulp << '\n';
                std::cerr << _F::fname() << "("<< a0 << ", " << a1 << ")\n";
            }
            if ((ulp >= -int32_t(max_ulp)) && (ulp <= int32_t(max_ulp))) {
                continue;
            }
        }
        if (verbose==false) {
            std::cerr << "ulp: " << ulp << '\n';
            check(vres, expected, _F::fname(), true);
        }
        std::cerr << _F::fname() << "("<< a0 << ", " << a1 << ") failed.\n";
        rc = false;
        ++errs;
    }
    std::cout << "test cases: " << calls
              << " errors: " << errs << std::endl;
    std::cout << "error rate = ";
    if (calls) {
        std::cout << std::setprecision(6)
                  << double(errs)/calls << std::endl;
        std::cout << "ticks per call: "
                  << std::fixed << std::setprecision(2)
                  << double(ticks)/calls
                  << std::endl;
#if 0
        std::cout << "scalar ticks per call: "
                  << std::fixed << std::setprecision(2)
                  << double(s_ticks)/calls
                  << std::endl;
#endif
        std::cout << std::scientific;
    } else {
        std::cout << 0.0 << std::endl;
    }
    if (errs <= max_err)
        rc=true;
    if (rc == true) {
        std::cout << _F::fname() << " v" << _N << " test passed " << std::endl;
    } else {
        std::cerr << _F::fname() << " v" << _N << " test failed " << std::endl;
    }
    return rc;
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_OF_MATH_FUNCS_H__
