#if !defined (__CFTAL_TEST_OF_MATH_FUNCS_H__)
#define __CFTAL_TEST_OF_MATH_FUNCS_H__ 1

#include <cftal/config.h>
#include <cftal/test/of_fp_funcs.h>
#include <cftal/test/call_mpfr.h>
#include <boost/math/special_functions.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

namespace cftal {
    namespace test {

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
    int64_t ticks(0), s_ticks(0);
    cmp_t<_T> cmp;
    for (std::size_t i=0; i< calls; ++i) {
        const func_arg_result<_T>& vi= v[i];
        _T a0 = vi.arg0();
        _T expected = vi.res();
        vec_type va0=a0;
        int64_t t0, t1, t2;
        t0= cftal::rdtsc();
        _T res = _F::v(a0);
        t1= cftal::rdtsc();
        vec_type vres = _F::v(va0);
        t2 = cftal::rdtsc();
        s_ticks+= (t1 -t0);
        ticks += (t2 -t1);

        bool c= check(vres, expected, _F::fname(), verbose);
        bool libc_err= (cmp(expected, res) == false);
        if (libc_err) {
            std::cerr << "libc error: " << res <<  " != "
                      << _F::fname()
                      << '(' << a0 << ")\n";
        }
        if (c == true)
            continue;
        _T vres0 = extract<0>(vres);
        int32_t ulp=0;
        try {
            ulp=boost::math::float_distance<_T>(vres0, expected);
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
        static_cast<void>(res);
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
        std::cout << "scalar ticks per call: "
                  << std::fixed << std::setprecision(2)
                  << double(s_ticks)/calls
                  << std::endl;
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
    int64_t ticks(0), s_ticks(0);
    cmp_t<_T> cmp;
    for (std::size_t i=0; i< calls; ++i) {
        const func_arg_result<_T>& vi= v[i];
        _T a0 = vi.arg0();
        _T a1 = vi.arg1();
        _T expected = vi.res();
        vec_type va0=a0;
        vec_type va1=a1;
        int64_t t0, t1, t2;
        t0= cftal::rdtsc();
        _T res = _F::v(a0, a1);
        t1= cftal::rdtsc();
        vec_type vres = _F::v(va0, va1);
        t2 = cftal::rdtsc();
        s_ticks+= (t1 -t0);
        ticks += (t2 -t1);

        bool c= check(vres, expected, _F::fname(), verbose);
        bool libc_err= (cmp(expected, res) == false);
        if (libc_err) {
            std::cerr << "libc error: " << res <<  " != "
                      << _F::fname()
                      << '(' << a0 << ", " << a1 << ")\n";
        }
        if (c == true)
            continue;
        _T vres0 = extract<0>(vres);
        int32_t ulp=0;
        try {
            ulp=boost::math::float_distance<_T>(vres0, expected);
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
        static_cast<void>(res);
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
        std::cout << "scalar ticks per call: "
                  << std::fixed << std::setprecision(2)
                  << double(s_ticks)/calls
                  << std::endl;
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
