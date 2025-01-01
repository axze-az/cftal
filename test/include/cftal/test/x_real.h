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
#if !defined (__CFTAL_TEST_X_REAL_H__)
#define __CFTAL_TEST_X_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <cftal/d_real_traits_f64.h>
#include <cftal/d_real_traits_f32.h>
#include <cftal/d_real_traits_f16.h>
#include <cftal/test/uniform_distribution.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/f32_f64.h>
#include <random>
#include <iostream>

namespace cftal {
    namespace test {
        template <template <typename _T> class _X,
                  typename _T,
                  class _R>
        class check_x_real {

            static
            _R make_ref(_X<_T> a);

            static
            bool
            check(_X<_T> res, _R expected, const char* msg);

            static
            bool
            ops(const _X<_T>& a0, const _X<_T>& a1);

            static bool ops();

        public:
            static bool v();
        };

        template <template <typename _T> class _X, typename _T>
        struct check_x_real_traits;

        template <>
        struct check_x_real_traits<d_real, double> {
            static
            double eps() {
                return 0x1.0p-104; // std::ldexp(1.0, -104);
            }

            template <typename _D, typename _RND>
            static
            d_real<double> make_rnd(_D& d, _RND& rnd) {
                double h=d(rnd);
                double l=h*1e-16;
                mpfr_real<128> t=h;
                t += mpfr_real<128>(l);
                double hn= double(t);
                t -= mpfr_real<128>(hn);
                double ln= double(t);
                return d_real<double>(hn, ln);
            }

            constexpr static const bool check_div = false;
        };

        template <>
        struct check_x_real_traits<t_real, double> {
            static
            double eps() {
                return 0x1.0p-156; // std::ldexp(1.0, -156);
            }

            template <typename _D, typename _RND>
            static
            t_real<double> make_rnd(_D& d, _RND& rnd) {
                double h=d(rnd);
                double m=h*1e-16;
                double l=m*1e-16;
                mpfr_real<192> t=h;
                t += mpfr_real<192>(m);
                t += mpfr_real<192>(l);
                double hn= double(t);
                t -= mpfr_real<192>(hn);
                double mn= double(t);
                t -= mpfr_real<192>(mn);
                double ln= double(t);
                return t_real<double>(hn, mn, ln);
            }

            constexpr static const bool check_div = false;
        };

        template <>
        struct check_x_real_traits<d_real, float> {
            static
            float eps() {
                return 0x1.0p-47f; // std::ldexp(1.0, -47);
            }
            template <typename _D, typename _RND>
            static
            d_real<float> make_rnd(_D& d, _RND& rnd) {
                float h=d(rnd);
                float l=h*1e-8f;
                mpfr_real<64> t=h;
                t += mpfr_real<64>(l);
                float hn= float(t);
                t -= mpfr_real<64>(hn);
                float ln= float(t);
                return d_real<float>(hn, ln);
            }

            constexpr static const bool check_div = false;
        };

        template <>
        struct check_x_real_traits<t_real, float> {
            static
            float eps() {
                // return std::pow(2, -64);
                return 0x1.0p-65f; //std::ldexp(1.0, -65);
            }
            template <typename _D, typename _RND>
            static
            t_real<float> make_rnd(_D& d, _RND& rnd) {
                float h=d(rnd);
                float m=h*1e-8;
                float l=m*1e-8;
                mpfr_real<128> t=h;
                t += mpfr_real<128>(m);
                t += mpfr_real<128>(l);
                float hn= float(t);
                t -= mpfr_real<128>(hn);
                float mn= float(t);
                t -= mpfr_real<128>(mn);
                float ln= float(t);
                return t_real<float>(hn, mn, ln);
            }
            constexpr static const bool check_div = false;
        };

        template <>
        struct check_x_real_traits<d_real, f16_t> {
            static
            float eps() {
                return 0x1.0p-21f; // std::ldexp(1.0, -47);
            }

            template <typename _D, typename _RND>
            static
            d_real<f16_t> make_rnd(_D& d, _RND& rnd) {
                f16_t h=d(rnd);
                f16_t l=h*1e-4_f16;
                mpfr_real<32> t=float(h);
                t += mpfr_real<32>(float(l));
                f16_t hn=static_cast<f16_t>(float(t));
                t -= mpfr_real<32>(float(hn));
                f16_t ln=static_cast<f16_t>(float(t));
                return d_real<f16_t>(hn, ln);
            }

            constexpr static const bool check_div = false;
        };


    }
}

template <template <typename _T> class _X, class _T, class _R>
_R
cftal::test::check_x_real<_X, _T, _R>::make_ref(_X<_T> a)
{
    _R r = a;
    // _R r= a.h();
    // r+=_R(a.l());
    return r;
}

template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::
check(_X<_T> res, _R expected, const char* msg)
{
    _R rs=make_ref(res);
    bool r=true;
    static const _R eps=check_x_real_traits<_X, _T>::eps();
    if (rel_err(rs, expected) > eps) {
        std::cerr << double(rs) << ' '  << double(expected) << ' '
                  << msg << std::endl;
        std::cerr << "rel_err: " << double(rel_err(rs, expected)) << std::endl;
        std::cerr << "abs_err:" << double(abs_err(rs, expected)) << std::endl;
        r = false;
    }
    return r;
}

template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::
ops(const _X<_T>& a0, const _X<_T>& b0)
{
    _R a = make_ref(a0);
    _R b = make_ref(b0);
    _R r;
    const _X<_T> va=a0;
    const _X<_T> vb=b0;
    _X<_T> vr;
    bool rc=true;

    r = -a;
    vr = -va;
    rc &= check(vr, r, "-a");

    r = +a;
    vr = +va;
    rc &= check(vr, r, "+a");

    r = a + b;
    vr = va + vb;
    rc &= check(vr, r, "a+b");

    r = a; r += b;
    vr = va; vr += vb;
    rc &= check(vr, r, "a+=b");

    r = a - b;
    vr = va - vb;
    rc &= check(vr, r, "a-b");

    r = a; r -= b;
    vr = va; vr -= vb;
    rc &= check(vr, r, "a-=b");

    r = a * b;
    vr = va * vb;
    rc &= check(vr, r, "a*b");

    r = a; r *= b;
    vr = va; vr *= vb;
    rc &= check(vr, r, "a*=b");

    if (check_x_real_traits<_X, _T>::check_div == true) {
        r = a / b;
        vr = va / vb;
        rc &= check(vr, r, "a/b");

        r = a; r /= b;
        vr = va; vr /= vb;
        rc &= check(vr, r, "a/=b");
    }

    using std::max;
    r = max(a, b);
    vr = max(va, vb);
    rc &= check(vr, r, "max");

    using std::min;
    r = min(a, b);
    vr = min(va, vb);
    rc &= check(vr, r, "min");

    r = a > _R(0.0) ? a : -a;
    vr = abs(va);
    rc &= check(vr, r, "abs");

    return rc;
}


template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::ops()
{
    static const _T operands[] = {
         _T(4), _T(2),
         _T(-4), _T(-2),
         _T(4), _T(0),
         _T(-4), _T(0),
         _T(0), _T(4),
         _T(0), _T(-4),
         _T(32), _T(21),
         _T(-32), _T(21),
         _T(32), _T(-21),
         _T(-32), _T(-21),
         _T(12), _T(-21),
         _T(-12), _T(21),
         _T(12), _T(21),
         _T(-12), _T(-21)
    };

    bool rc =true;
    for (auto b=std::begin(operands), e=std::end(operands); b!=e; b+=2) {
        _X<_T> b0=*b;
        _X<_T> b1=*std::next(b);
        rc &= ops(b0, b1);
        rc &= ops(b1, b0);
    }
    std::mt19937 rnd;
    // avoid underflows if we test higher fp expansions
    using std::ldexp;
    _T l0= ldexp(_T(1.0),
                 std::numeric_limits<_T>::min_exponent/5);
    uniform_real_distribution<_T>
        distrib(l0,
                std::numeric_limits<_T>::max());
    const std::size_t N0=0x2000ULL;
    for (uint32_t j=0; j<72; ++j) {
        for (std::size_t i=0; i<N0; ++i) {
            _X<_T> va0=check_x_real_traits<_X, _T>::make_rnd(distrib, rnd);
            _X<_T> vb0=check_x_real_traits<_X, _T>::make_rnd(distrib, rnd);
            _X<_T> va=va0, vb=vb0;
            rc &= ops(va, vb);
            va = -va0;
            rc &= ops(va, vb);
            va = va0; vb= -vb0;
            rc &= ops(va, vb);
            va = -va0;
            rc &= ops(va, vb);
        }
        std::cout << '.' << std::flush;
    }
    std::cout << std::endl;
    if (rc == true) {
        std::cout << __func__ << " test passed " << std::endl;
    } else {
        std::cerr << __func__ << " test failed " << std::endl;
    }
    return rc;
}

template <template <typename _T> class _X, class _T, class _R>
bool
cftal::test::check_x_real<_X, _T, _R>::v()
{
    return ops();
}


// Local variables:
// mode: c++
// end:
#endif
