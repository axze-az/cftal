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

        template <typename _T>
        using func_domain = std::pair<_T, _T>;

        template <typename _T>
        struct default_domain {
            static
            const func_domain<_T> value;
        };

        const std::size_t default_cnt=0x80000ULL;

        template <typename _T>
        const func_domain<_T>
        default_domain<_T>::value =
            std::make_pair(std::numeric_limits<_T>::lowest(),
                           std::numeric_limits<_T>::max());

        struct exec_stats {
            std::vector<uint64_t> _tics;
            std::vector<uint64_t> _evals;
            void insert(uint64_t _tic_before, uint64_t tic_after,
                        unsigned n);
            exec_stats(unsigned n)
                : _tics(n+1, uint64_t(0)), _evals(n+1, uint64_t(0)) {}
        };
        std::ostream& operator<<(std::ostream& s, const exec_stats& st);

        template <typename _T, std::size_t _N, typename _F>
        struct vec_parts {
            static
            bool
            v(const vec<_T, _N>& x, const vec<_T, _N>& fx,
              exec_stats& st);
            static
            bool
            v(const vec<_T, _N>& x, const vec<_T, _N>& y,
              const vec<_T, _N>& fx, exec_stats& st);
        };

        template <typename _T, typename _F>
        struct vec_parts<_T, 1, _F> {
            static
            bool
            v(const vec<_T, 1>& x, const vec<_T, 1>& fx, exec_stats& st) {
                static_cast<void>(x);
                static_cast<void>(fx);
                return true;
            }
            static
            bool
            v(const vec<_T, 1>& x, const vec<_T, 1>& y,
              const vec<_T, 1>& fx, exec_stats& st) {
                static_cast<void>(x);
                static_cast<void>(y);
                static_cast<void>(fx);
                return true;
            }
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func {

            template <typename _CMP=cmp_t<_T>>
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain = default_domain<_T>::value,
              _CMP cmp=_CMP(), std::size_t cnt=default_cnt);

            template <typename _CMP=cmp_t<_T> >
            static
            bool v(const _T(&ai)[_N], exec_stats& st, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_up_to {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats& st, func_domain<_T> domain = default_domain<_T>::value,
              _CMP cmp= _CMP(),
              std::size_t cnt=default_cnt) {
                bool r=of_fp_func<_T, _N, _F>::v(st, domain, cmp, cnt);
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
              _CMP cmp=_CMP(), std::size_t cnt=default_cnt);

            template <typename _CMP=cmp_t<_T> >
            static
            bool v(const _T(&ai)[_N], const _T(&bi)[_N],
                   exec_stats& st, _CMP cmp=_CMP());
        };

        template <typename _T, std::size_t _N, typename _F>
        struct of_fp_func_2_up_to {
            template <typename _CMP=cmp_t<_T> >
            static
            bool
            v(exec_stats& st,
              func_domain<_T> domain_1 = default_domain<_T>::value,
              func_domain<_T> domain_2 = default_domain<_T>::value,
              _CMP cmp= _CMP(), std::size_t cnt=default_cnt) {
                bool r=of_fp_func_2<_T, _N, _F>::v(st, domain_1, domain_2,
                                                   cmp, cnt);
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
            v(const _T& v) {
                return std::rint(v);
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
            v(const _T& v) {
                return std::floor(v);
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
            v(const _T& v) {
                return std::ceil(v);
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
            v(const _T& v) {
                return std::trunc(v);
            }
            static
            const char* fname() { return "trunc"; }
        };

    }
}

inline
void
cftal::test::exec_stats::
insert(uint64_t tics_before, uint64_t tics_after, unsigned n)
{
    if (_tics.size() <= n) {
        _tics.resize(n+1, uint64_t(0));
        _evals.resize(n+1, uint64_t(0));
    }
    uint64_t ta=std::max(tics_before, tics_after);
    uint64_t tb=std::min(tics_before, tics_after);
    uint64_t d=ta - tb;
    _tics[n] += d;
    _evals[n] += 1;
}

inline
std::ostream&
cftal::test::operator<<(std::ostream& s, const exec_stats& st)
{
    std::size_t n= st._tics.size();
    s << "execution statistics\n";
    for (std::size_t i=0; i<n; i=((i==0) ? 1: i*2)) {
        double t=st._tics[i];
        uint64_t ei=st._evals[i];
        double tc=t/double(ei);
        double te=i ? tc : tc/i;
        s << "vec-len: " << std::setw(2) << i << " calls: "
          << std::setw(16) << ei << " tics/call: "
          << std::setprecision(1)
          << std::fixed
          << std::setw(12)
          << tc
          << " tics/elem: "
          << std::setw(12)
          << te
          << std::scientific
          << std::setprecision(22)
          << "\n";
    }
    return s;
}

template <typename _T, std::size_t _N, typename _F>
bool
cftal::test::vec_parts<_T, _N, _F>::
v(const vec<_T, _N>& x, const vec<_T, _N>& fx, exec_stats& st)
{
    const int _N2=_N/2;
    vec<_T, _N2> xl=low_half(x);
    vec<_T, _N2> xh=high_half(x);
    uint64_t t0= rdtsc();
    vec<_T, _N2> fxl=_F::v(xl);
    uint64_t t1= rdtsc();
    st.insert(t0, t1, _N2);
    t0 = rdtsc();
    vec<_T, _N2> fxh=_F::v(xh);
    t1 = rdtsc();
    st.insert(t0, t1, _N2);
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, fxh, st);
    vec<_T, _N> fxlh(fxl, fxh);
    typename vec<_T, _N>::mask_type vr= (fx == fxlh) | (isnan(fx) & isnan(fxlh));
    r &= all_of(vr);
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
    uint64_t t0= rdtsc();
    vec<_T, _N2> fxl=_F::v(xl, yl);
    uint64_t t1= rdtsc();
    st.insert(t0, t1, _N2);
    t0 = rdtsc();
    vec<_T, _N2> fxh=_F::v(xh, yh);
    t1 = rdtsc();
    st.insert(t0, t1, _N2);
    bool r=true;
    r &= vec_parts<_T, _N2, _F>::v(xl, yl, fxl, st);
    r &= vec_parts<_T, _N2, _F>::v(xh, yh, fxh, st);
    vec<_T, _N> fxlh(fxl, fxh);
    typename vec<_T, _N>::mask_type vr= (fx == fxlh) | (isnan(fx) & isnan(fxlh));
    r &= all_of(vr);
    return r;
}


template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(const _T(&a)[_N],
                                       exec_stats& st,
                                       _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a);
    volatile uint64_t t0 = rdtsc();
    vec<_T, _N> vr=_F::v(va);
    volatile uint64_t t1 = rdtsc();
    st.insert(t0, t1, _N);
    _T r[_N];
    for (std::size_t i=0; i<_N; ++i) {
        volatile uint64_t t2 = rdtsc();
        r[i] = _F::v(a[i]);
        volatile uint64_t t3 = rdtsc();
        st.insert(t2, t3, 0);
    }
    // std::cout << std::setprecision(18) << a << std::endl;
    bool c= check(vr, r, _F::fname(), true, cmp);
    bool cs= vec_parts<_T, _N, _F>::v(va, vr, st);
    c &= cs;
    if (c == false) {
        for (std::size_t i=0; i < _N; ++i) {
            std::cerr << _F::fname() << "("<< a[i] << ") failed ?\n";
            std::cerr << _F::fname() << "= "<< r[i] << "\n";
        }
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
template <typename _CMP>
bool
cftal::test::of_fp_func<_T, _N, _F>::v(exec_stats& st,
                                       func_domain<_T> domain,
                                       _CMP cmp, std::size_t cnt)
{
    bool r = true;
    const _T inf_nan_args []= {
        _T(0.0),
        _T(-0.0),
        _T(1),
        _T(2),
        _T(7),
        _T(8),
        _T(uint64_t(1ULL<<23)),
        _T(uint64_t(1ULL<<52)),
        _T(0x1.0p31),
        _T(0x1.0p21),
        _T(0x1.0p23),
        _T(0x1.0p24),
        _T(0x1.0p51),
        _T(0x1.0p52),
        std::numeric_limits<_T>::infinity(),
        std::numeric_limits<_T>::quiet_NaN(),
    };

    _T va[_N];
    for (auto b=std::begin(inf_nan_args), e=std::end(inf_nan_args);
         b!=e; ++b) {
        const auto& ai= *b;
        std::fill(std::begin(va), std::end(va), ai);
        r &=v(va, st, cmp);
        std::fill(std::begin(va), std::end(va), -ai);
        r &=v(va, st, cmp);
    }

    std::mt19937_64 rnd;
    uniform_real_distribution<_T>
        distrib(domain.first, domain.second);


    std::cout << "[" << domain.first << ", " << domain.second << ")\n";
    const uint32_t N0=72;
    for (uint32_t j=0; j<N0; ++j) {
        for (std::size_t i=0; i<cnt; ++i) {
            for (std::size_t k=0; k<_N; ++k) {
                va[k] = distrib(rnd);
            }
            r &= v(va, st, cmp);
        }
        std::cout << '.' << std::flush;
    }
    _T minus1= std::max(_T(-1), domain.first);
    _T plus1= std::min(_T(1), domain.second);
    if (minus1 < plus1 && (minus1 != domain.first || plus1 != domain.second)) {
        std::cout << std::endl;
        _T nplus1=std::nextafter(plus1, _T(2)*plus1);
        uniform_real_distribution<_T>
            distrib1(minus1, nplus1);
        std::cout << "[" << minus1 << ", " << nplus1 << ")\n";
        for (uint32_t j=0; j<N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    va[k] = distrib1(rnd);
                }
                r &= v(va, st, cmp);
            }
            std::cout << '.' << std::flush;
        }
    }
    std::cout << std::endl;
    if (r == true) {
        std::cout << __func__ << _N << " to v1 test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " to v1 test failed " << std::endl;
    }
    return r;

}

template <typename _T, std::size_t _N, typename _F>
template <typename _CMP>
bool
cftal::test::of_fp_func_2<_T, _N, _F>::
v(const _T(&a)[_N], const _T(&b)[_N], exec_stats& st, _CMP cmp)
{
    vec<_T, _N> va=mem<vec<_T, _N> >::load(a);
    vec<_T, _N> vb=mem<vec<_T, _N> >::load(b);
    uint64_t t0=rdtsc();
    vec<_T, _N> vr=_F::v(va, vb);
    uint64_t t1=rdtsc();
    st.insert(t0, t1, _N);
    _T r[_N];
    for (std::size_t i=0; i<_N; ++i) {
        t0=rdtsc();
        r[i] = _F::v(a[i], b[i]);
        t1=rdtsc();
        st.insert(t0, t1, _N);
    }
    bool c= check(vr, r, _F::fname(), true, cmp);
    bool cs= vec_parts<_T, _N, _F>::v(va, vb, vr, st);
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
                                         _CMP cmp, std::size_t cnt)
{
    bool r = true;

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

    _T va[_N], vb[_N];

    for (auto ab=std::begin(inf_nan_args), ae=std::end(inf_nan_args);
         ab != ae; ++ab) {
        _T ai=*ab;
        for (auto bb=std::begin(inf_nan_args), be=std::end(inf_nan_args);
             bb !=be; ++bb) {
            _T bi= *bb;
            std::fill(std::begin(va), std::end(va), ai);
            std::fill(std::begin(vb), std::end(vb), bi);
            r &= v(va, vb, st, cmp);
            std::fill(std::begin(vb), std::end(vb), -bi);
            r &= v(va, vb, st, cmp);
            std::fill(std::begin(va), std::end(va), -ai);
            r &= v(va, vb, st, cmp);
            std::fill(std::begin(vb), std::end(vb), bi);
            r &= v(va, vb, st, cmp);
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
    for (uint32_t j=0; j< N0; ++j) {
        for (std::size_t i=0; i<cnt; ++i) {
            for (std::size_t k=0; k<_N; ++k) {
                va[k] = distrib1(rnd);
                vb[k] = distrib2(rnd);
            }
            r &= v(va, vb, st, cmp);
        }
        std::cout << '.' << std::flush;
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
        for (uint32_t j=0; j<N0; ++j) {
            for (std::size_t i=0; i<cnt; ++i) {
                for (std::size_t k=0; k<_N; ++k) {
                    va[k] = distrib_1_1(rnd);
                    vb[k] = distrib_1_2(rnd);
                }
                r &= v(va, vb, st, cmp);
            }
            std::cout << '.' << std::flush;
        }
    }
    std::cout << std::endl;
    if (r == true) {
        std::cout << __func__ << _N << " to v1 test passed " << std::endl;
    } else {
        std::cerr << __func__ << _N << " to v1 test failed " << std::endl;
    }
    return r;
}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_TEST_OF_FP_FUNCS_H__
