//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_SINCOS_H__)
#define __CFTAL_TEST_CHECK_SINCOS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_sincos {

            template <std::size_t _N>
            static
            std::pair<vec<_T, _N>, vec<_T, _N> >
            v(const vec<_T, _N>& a) {
                vec<_T, _N> s, c;
                sincos(a, &s, &c);
                return std::pair<vec<_T, _N>, vec<_T, _N> >(s, c);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> r, i0, i1;
                r=call_mpfr::func(a, mpfr_sin_cos, &i0, &i1);
                auto r0=std::make_tuple(r.first, i0.first, i0.second);
                auto r1=std::make_tuple(r.second, i1.first, i1.second);
                return std::make_pair(r0, r1);
            }

            static
            std::pair<double, double>
            __sincos(double a) {
                double s, c;
                ::sincos(a, &s, &c);
                return std::make_pair(s, c);
            }


            static
            std::pair<float, float>
            __sincos(float a) {
                float s, c;
                ::sincosf(a, &s, &c);
                return std::make_pair(s, c);
            }

            static
            std::pair<_T, _T>
            s(const _T& a) {
                return __sincos(a);
            }

            static
            const char* fname() { return "sincos"; }

            struct sin {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> s, c;
                    sincos(a, &s, &c);
                    return s;
                }
                static
                auto
                r(const _T& a) {
                    std::pair<_T, _T> i;
                    _T v=call_mpfr::func(a, mpfr_sin, &i);
                    return std::make_tuple(v, i.first, i.second);
                    // return call_mpfr::func(a, mpfr_log2);
                }
                static
                _T
                s(const _T& a) {
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
                    vec<_T, _N> s, c;
                    sincos(a, &s, &c);
                    return c;
                }
                static
                auto
                r(const _T& a) {
                    std::pair<_T, _T> i;
                    _T v=call_mpfr::func(a, mpfr_cos, &i);
                    return std::make_tuple(v, i.first, i.second);
                    // return call_mpfr::func(a, mpfr_log2);
                }
                static
                _T
                s(const _T& a) {
                    return std::cos(a);
                }
                static
                const char* fname() { return "sincos: cos"; }
            };

        };

    }
}

// local variables:
// mode: c++
// end:

#endif
