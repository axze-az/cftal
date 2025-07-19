//
// Copyright (C) 2010-2025 Axel Zeuner
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
                _T v0=call_mpfr::func(a, mpfr_sinpi, &i0);
                _T v1=call_mpfr::func(a, mpfr_cospi, &i1);
                auto r0=std::make_tuple(v0, i0.first, i0.second);
                auto r1=std::make_tuple(v1, i1.first, i1.second);
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
            std::pair<f16_t, f16_t>
            __sinpicospi(f16_t a) {
                float af=static_cast<float>(a)*M_PI;
                float sf, cf;
                ::sincosf(af, &sf, &cf);
                f16_t s=static_cast<f16_t>(sf);
                f16_t c=static_cast<f16_t>(cf);
                return std::make_pair(s, c);
            }

            static
            std::pair<bf16_t, bf16_t>
            __sinpicospi(bf16_t a) {
                float af=static_cast<float>(a)*M_PI;
                float sf, cf;
                ::sincosf(af, &sf, &cf);
                bf16_t s=static_cast<bf16_t>(sf);
                bf16_t c=static_cast<bf16_t>(cf);
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
                    _T v=call_mpfr::func(a, mpfr_sinpi, &i);
                    return std::make_tuple(v, i.first, i.second);
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
                    _T v=call_mpfr::func(a, mpfr_cospi, &i);
                    return std::make_tuple(v, i.first, i.second);
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
