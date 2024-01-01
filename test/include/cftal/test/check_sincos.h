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
            std::pair<f16_t, f16_t>
            __sincos(f16_t a) {
                float s, c;
                ::sincosf(float(a), &s, &c);
                return std::make_pair(f16_t(s), f16_t(c));
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
                    using std::sin;
                    return sin(a);
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
                    using std::cos;
                    return cos(a);
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
