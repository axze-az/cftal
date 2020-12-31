//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined(__CFTAL_TEST_CHECK_SINPICOSPI_H__)
#define __CFTAL_TEST_CHECK_SINPICOSPI_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        struct check_sinpicospi {

            template <std::size_t _N>
            static
            std::pair<vec<_T, _N>, vec<_T, _N> >
            v(const vec<_T, _N>& a) {
                vec<_T, _N> s, c;
                sinpicospi(a, &s, &c);
                return std::pair<vec<_T, _N>, vec<_T, _N> >(s, c);
            }

            static
            auto
            r(const _T& a) {
                std::pair<_T, _T> i0, i1;
                _T v0=call_mpfr::func(a, mpfr_ext::sinpi, &i0);
                _T v1=call_mpfr::func(a, mpfr_ext::cospi, &i1);
                auto r0=std::make_tuple(v0, i0.first, i0.second);
                auto r1=std::make_tuple(v1, i1.first, i1.second);
#if 0
                r=call_mpfr::func(a, mpfr_sin_cos, &i0, &i1);
                auto r0=std::make_tuple(r.first, i0.first, i0.second);
                auto r1=std::make_tuple(r.second, i1.first, i1.second);
#endif
                return std::make_pair(r0, r1);
            }

            static
            std::pair<double, double>
            __sinpicospi(double a) {
                double s, c;
                ::sincos(a*M_PI, &s, &c);
                return std::make_pair(s, c);
            }


            static
            std::pair<float, float>
            __sinpicospi(float a) {
                float s, c;
                ::sincosf(a*M_PI, &s, &c);
                return std::make_pair(s, c);
            }

            static
            std::pair<_T, _T>
            s(const _T& a) {
                return __sinpicospi(a);
            }

            static
            const char* fname() { return "sinpicospi"; }

            struct sinpi {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> s, c;
                    sinpicospi(a, &s, &c);
                    return s;
                }
                static
                auto
                r(const _T& a) {
                    std::pair<_T, _T> i;
                    _T v=call_mpfr::func(a, mpfr_ext::sinpi, &i);
                    return std::make_tuple(v, i.first, i.second);
                    // return call_mpfr::func(a, mpfr_log2);
                }
                static
                _T
                s(const _T& a) {
                    return std::sin(a*M_PI);
                }
                static
                const char* fname() { return "sinpicospi: sinpi"; }
            };

            struct cospi {
                template <std::size_t _N>
                static
                vec<_T, _N>
                v(const vec<_T, _N>& a) {
                    vec<_T, _N> s, c;
                    sinpicospi(a, &s, &c);
                    return c;
                }
                static
                auto
                r(const _T& a) {
                    std::pair<_T, _T> i;
                    _T v=call_mpfr::func(a, mpfr_ext::cospi, &i);
                    return std::make_tuple(v, i.first, i.second);
                    // return call_mpfr::func(a, mpfr_log2);
                }
                static
                _T
                s(const _T& a) {
                    return std::cos(a*M_PI);
                }
                static
                const char* fname() { return "sinpicospi: cospi"; }
            };

        };

    }
}

// local variables:
// mode: c++
// end:

#endif
