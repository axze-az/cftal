//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_X86_H__)
#define __CFTAL_TEST_X86_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cmath>

namespace cftal {
    namespace test {

        bool div();

        double make_double(unsigned sgn, unsigned exp, uint64_t sig);
        float make_float(unsigned sgn, unsigned exp, uint32_t sig);

        // compare a and b, returns also true for a==NAN and b
        // == NAN
        bool f_eq(double a, double b);
        bool f_eq(float a, float b);

        template <class _FV, class _IV>
        bool check_frexp(typename _FV::value_type vp,
                         typename _FV::value_type vn);

        template <class _FV, class _IV>
        bool check_frexp_f64();

        template <class _FV, class _IV>
        bool check_frexp_f32();

        template <class _V>
        int check_cbrt_f64(const _V& v0, double x);

        template <class _V>
        bool check_cbrt_f64(const _V& v0);

    }
}


inline
double
cftal::test::make_double(unsigned sgn, unsigned exp, uint64_t sig)
{
    uint64_t _sgn= uint64_t(sgn & 1) << 63;
    uint64_t _exp= uint64_t(exp & 0x7FF) << 52;
    uint64_t _sig= sig & 0x000fffffffffffffULL;
    union {
        uint64_t _u;
        double _d;
    } t;
    t._u = _sgn | _exp | _sig;
    return t._d;
}

inline
float
cftal::test::make_float(unsigned sgn, unsigned exp, uint32_t sig)
{
    uint32_t _sgn= uint64_t(sgn & 1) << 31;
    uint32_t _exp= uint64_t(exp & 0xFF) << 23;
    uint32_t _sig= sig & 0x007fffff;
    union {
        uint32_t _u;
        float _d;
    } t;
    t._u = _sgn | _exp | _sig;
    return t._d;
}

inline
bool cftal::test::f_eq(double a, double b)
{
    return (a == b) || (std::isnan(a) && std::isnan(b));
}

inline
bool cftal::test::f_eq(float a, float b)
{
    return (a == b) || (std::isnan(a) && std::isnan(b));
}


// local variables:
// mode: c++
// end:
#endif
