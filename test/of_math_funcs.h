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


        template <typename _T>
        struct check_sqrt {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sqrt(a);
            }
            static
            _T
            v(const _T& a) {
                return std::sqrt(a);
            }
            static
            const char* fname() { return "sqrt"; }
        };

        template <typename _T>
        struct check_cbrt {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return cbrt(a);
            }

            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_cbrt);
#else
                return std::cbrt(a);
#endif
            }
            static
            const char* fname() { return "cbrt"; }
        };


        template <typename _T>
        struct check_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp(a);
            }
            static
            _T
            v(const _T& a) {
#if 0
                return call_mpfr::func(a, mpfr_exp);
#else
                return std::exp(a);
#endif
            }
            static
            const char* fname() { return "exp"; }
        };

        template <typename _T>
        struct check_expm1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return expm1(a);
            }
            static
            _T
            v(const _T& a) {
                return std::expm1(a);
            }
            static
            const char* fname() { return "expm1"; }
        };

        template <typename _T>
        struct check_sinh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sinh(a);
            }

            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_sinh);
#else
                return std::sinh(a);
#endif
            }
            static
            const char* fname() { return "sinh"; }
        };

        template <typename _T>
        struct check_cosh {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return cosh(a);
            }

            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_cosh);
#else
                return std::cosh(a);
#endif
            }
            static
            const char* fname() { return "cosh"; }
        };

        template <typename _T>
        struct check_exp2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp2(a);
            }
            static
            _T
            v(const _T& a) {
#if 0
                return call_mpfr::func(a, mpfr_exp2);
#else
                return std::exp2(a);
#endif
            }
            static
            const char* fname() { return "exp2"; }
        };

        template <typename _T>
        struct check_exp10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return exp10(a);
            }

            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_exp10);
#else
                return ::exp10(a);
#endif
            }
            static
            const char* fname() { return "exp10"; }
        };

        template <typename _T>
        struct check_log {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log(a);
            }
            static
            _T
            v(const _T& a) {
                return std::log(a);
            }
            static
            const char* fname() { return "log"; }
        };

        template <typename _T>
        struct check_log1p {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log1p(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_log1p);
#else
                return std::log1p(a);
#endif
            }
            static
            const char* fname() { return "log1p"; }
        };
        
        template <typename _T>
        struct check_log10 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log10(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_log10);
#else
                return std::log10(a);
#endif
            }
            static
            const char* fname() { return "log10"; }
        };

        template <typename _T>
        struct check_log2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return log2(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_log2);
#else
                return std::log2(a);
#endif
            }
            static
            const char* fname() { return "log2"; }
        };
        
        template <typename _T>
        struct check_pow {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return pow(a, b);
            }
            static
            _T
            v(const _T& a, const _T& b) {
#if 1
                return call_mpfr::func(a, b, mpfr_pow);
#else
                return std::pow(a, b);
#endif

            }
            static
            const char* fname() { return "pow"; }
        };

        template <>
        struct check_pow<double> {
            template <std::size_t _N>
            static
            vec<double, _N>
            v(const vec<double, _N>& a, const vec<double, _N>& b) {
                return pow(a, b);
            }
            static
            double
            v(const double& a, const double& b) {
                return std::pow(a, b);
            }
            static
            const char* fname() { return "pow"; }
        };


        template <typename _T>
        struct check_sin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return sin(a);
            }
            static
            _T
            v(const _T& a) {
#if 0
                return call_mpfr::func(a, mpfr_sin);
#else
                return std::sin(a);
#endif
            }
            static
            const char* fname() { return "sin"; }
        };

        template <typename _T>
        struct check_cos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return cos(a);
            }
            static
            _T
            v(const _T& a) {
                return std::cos(a);
            }
            static
            const char* fname() { return "cos"; }
        };

        template <typename _T>
        struct check_sincos {
            struct sin {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> s;
                    sincos(a, &s, nullptr);
                    return s;
                }
                static
                _T
                v(const _T& a) {
                    return std::sin(a);
                }
                static
                const char* fname() { return "sincos: sin"; }
            };

            struct cos {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> c;
                    sincos(a, nullptr, &c);
                    return c;
                }
                static
                _T
                v(const _T& a) {
                    return std::cos(a);
                }
                static
                const char* fname() { return "sincos: cos"; }
            };

        };

        template <typename _T>
        struct check_tan {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return tan(a);
            }
            static
            _T
            v(const _T& a) {
                return std::tan(a);
            }
            static
            const char* fname() { return "tan"; }
        };

        template <typename _T>
        struct check_atan {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return atan(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_atan);
#else
                return std::atan(a);
#endif
            }
            static
            const char* fname() { return "atan"; }
        };
        
        template <typename _T>
        struct check_atan2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a, const vec<_T, _N>& b) {
                return atan2(a, b);
            }
            static
            _T
            v(const _T& a, const _T& b) {
#if 1
                return call_mpfr::func(a, b, mpfr_atan2);
#else
                return std::atan2(a, b);
#endif
            }
            static
            const char* fname() { return "atan2"; }
        };

        template <typename _T>
        struct check_asin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return asin(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_asin);
#else
                return std::asin(a);
#endif
            }
            static
            const char* fname() { return "asin"; }
        };

        template <typename _T>
        struct check_acos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return acos(a);
            }
            static
            _T
            v(const _T& a) {
#if 1
                return call_mpfr::func(a, mpfr_acos);
#else
                return std::acos(a);
#endif
            }
            static
            const char* fname() { return "acos"; }
        };
        
        template <typename _T>
        struct check_native_exp {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_exp(a);
            }
            static
            _T
            v(const _T& a) {
                return std::exp(a);
            }
            static
            const char* fname() { return "native_exp"; }
        };

        template <typename _T>
        struct check_native_exp2 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_exp2(a);
            }
            static
            _T
            v(const _T& a) {
#if 0
                return call_mpfr::func(a, mpfr_exp2);
#else
                return std::exp2(a);
#endif
            }
            static
            const char* fname() { return "exp2"; }
        };

        
        template <typename _T>
        struct check_native_expm1 {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_expm1(a);
            }
            static
            _T
            v(const _T& a) {
                return std::expm1(a);
            }
            static
            const char* fname() { return "native_expm1"; }
        };

        template <typename _T>
        struct check_native_log {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_log(a);
            }
            static
            _T
            v(const _T& a) {
                return std::log(a);
            }
            static
            const char* fname() { return "native_log"; }
        };

        template <typename _T>
        struct check_native_sin {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_sin(a);
            }
            static
            _T
            v(const _T& a) {
                return std::sin(a);
            }
            static
            const char* fname() { return "native_sin"; }
        };

        template <>
        struct check_native_sin<float> {
            template <std::size_t _N>
            static
            vec<float, _N>
            v(const vec<float, _N>& a) {
                return native_sin(a);
            }
            static
            float
            v(const float& a) {
#if 0
                return call_mpfr::func(a, mpfr_sin);
#else
                return std::sin(a);
#endif
            }
            static
            const char* fname() { return "native_sin"; }
        };
        
        template <typename _T>
        struct check_native_cos {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return native_cos(a);
            }
            static
            _T
            v(const _T& a) {
                return std::cos(a);
            }
            static
            const char* fname() { return "native_cos"; }
        };
        
        template <typename _T>
        struct check_native_sincos {
            struct sin {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> s;
                    native_sincos(a, &s, nullptr);
                    return s;
                }
                static
                _T
                v(const _T& a) {
                    return std::sin(a);
                }
                static
                const char* fname() { return "native_sincos: sin"; }
            };

            struct cos {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> c;
                    native_sincos(a, nullptr, &c);
                    return c;
                }
                static
                _T
                v(const _T& a) {
                    return std::cos(a);
                }
                static
                const char* fname() { return "native_sincos: cos"; }
            };

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
