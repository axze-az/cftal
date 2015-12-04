#if !defined (__CFTAL_TEST_F32_F64_H__)
#define __CFTAL_TEST_F32_F64_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec.h>
#include <cftal/mem.h>
#include <cftal/select.h>
#include <iostream>

namespace cftal {
    namespace test {

        double make_double(unsigned sgn, unsigned exp, uint64_t sig);
        float make_float(unsigned sgn, unsigned exp, uint32_t sig);

        // compare a and b, returns also true for a==NAN and b
        // == NAN
        bool f_eq(double a, double b);
        bool f_eq(float a, float b);
        
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
        struct cmp_t<float> {
            cmp_t() {}
            bool operator()(float a, float b) const {
                return f_eq(a, b);
            }
        };
        
     
        template <class _T, std::size_t _N>
        bool check(const _T(&a)[_N], _T expected, const char* msg);
        
        template <class _T, std::size_t _N>
        bool check(vec<_T, _N> a, _T expected, const char* msg);        
        
        template <class _T>
        _T abs_err(_T a0, _T a1);
        
        template <class _T>
        _T rel_err(_T a0, _T a1);
        
    }
}

template <class _T, std::size_t _N>
bool cftal::test::check(const _T(&a)[_N], _T expected , const char* msg)
{
    bool r=true;
    std::size_t i=0; 
    const cmp_t<_T> cmp;
    for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
        const _T& ai= *b;
        if (cmp(ai, expected) == false) {
            std::cerr << msg << " element " << i 
                      << " failed: " << ai << " expected: "
                      << expected << std::endl;
            r = false;
        }
    }
    return r;
}

template <class _T, std::size_t _N>
bool cftal::test::check(vec<_T, _N> vr, _T expected, const char* msg)
{
    _T vsr[_N];
    mem< vec<_T, _N> >::store(vsr, vr);
    return check(vsr, expected, msg);
}

template <class _T>
_T
cftal::test::abs_err(_T a0, _T a1)
{    
    _T d= a0 - a1;
    return select(d > _T(0), d , -d);
}

template <class _T>
_T
cftal::test::rel_err(_T a0, _T a1)
{
    return abs_err(a0, a1)/(_T(0.5) * (a0 + a1));
}


#endif
