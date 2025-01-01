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
#if !defined (__CFTAL_TEST_CALL_MPFR_H__)
#define __CFTAL_TEST_CALL_MPFR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/f16_t.h>
#include <cftal/bf16_t.h>
#include <cftal/d_real.h>
#include <cftal/d_real_traits_f32.h>
#include <cftal/d_real_traits_f64.h>
#include <cftal/t_real.h>
#include <utility>
#include <cmath>
#include <climits>
#include <algorithm>
#include <mpfr.h>

namespace cftal {
    namespace test {

        namespace call_mpfr {
            // mpfr function with one argument
            using f1_t = int (*)(mpfr_t, const mpfr_t,
                                 mpfr_rnd_t);

            // mpfr function with one argument and two results
            using f1p_t = int (*)(mpfr_t, mpfr_t,
                                  const mpfr_t, mpfr_rnd_t);

            // mpfr function with one argument returning an
            // additional integer via pointer
            using f1i_t = int (*)(mpfr_t, int32_t*, const mpfr_t,
                                  mpfr_rnd_t);

            // mpfr function with two arguments
            using f2_t = int (*)(mpfr_t, const mpfr_t,
                                 const mpfr_t, mpfr_rnd_t);

            // mpfr function with one floating point and one integer
            // argument
            using f2fi_t = int (*)(mpfr_t, const mpfr_t,
                                   long int,
                                   mpfr_rnd_t);

            // call f(a), returns also the interval
            // containing the unrounded result
            double
            func(double a, f1_t f,
                 std::pair<double, double>* ulp1i= nullptr);

            // call f(a), returns also the intervals
            // containing the unrounded results
            std::pair<double, double>
            func(double a, f1p_t f,
                 std::pair<double, double>* ulp1i0 = nullptr,
                 std::pair<double, double>* ulp1i1 = nullptr);

            // call f(a, ib), returns also the interval
            // containing the unrounded result
            double
            func(double a, int ib, f2fi_t f,
                 std::pair<double, double>* ulp1i= nullptr);

            // call f(a, i), returns also the interval
            // containing the unrounded result
            double
            func(int32_t* ip, double a, f1i_t f,
                 std::pair<double, double>* ulp1i= nullptr);

            // call f(a, b), returns also the interval
            // containing the unrounded result
            double
            func(double a, double b, f2_t f,
                 std::pair<double, double>* ulp1i= nullptr);

            // call f(a), returns also the interval
            // containing the unrounded result
            float
            func(float a, f1_t f,
                 std::pair<float, float>* ulp1i= nullptr);

            // call f(a), returns also the intervals
            // containing the unrounded results
            std::pair<float, float>
            func(float a, f1p_t f,
                 std::pair<float, float>* ulp1i0 = nullptr,
                 std::pair<float, float>* ulp1i1 = nullptr);

            // call f(a, i), returns also the interval
            // containing the unrounded result
            float
            func(int32_t* ip, float a, f1i_t f,
                 std::pair<float, float>* ulp1i= nullptr);

            // call f(a, b), returns also the interval
            // containing the unrounded result
            float
            func(float a, float b, f2_t f,
                 std::pair<float, float>* ulp1i= nullptr);

            // call f(a), returns also the interval
            // containing the unrounded result
            float
            func(float a, int ib, f2fi_t f,
                 std::pair<float, float>* ulp1i= nullptr);

            // call f(a), returns also the interval
            // containing the unrounded result
            f16_t
            func(f16_t a, f1_t f,
                 std::pair<f16_t, f16_t>* ulp1i= nullptr);

            // call f(a), returns also the intervals
            // containing the unrounded results
            std::pair<f16_t, f16_t>
            func(f16_t a, f1p_t f,
                 std::pair<f16_t, f16_t>* ulp1i0 = nullptr,
                 std::pair<f16_t, f16_t>* ulp1i1 = nullptr);

            // call f(a, i), returns also the interval
            // containing the unrounded result
            f16_t
            func(int32_t* ip, f16_t a, f1i_t f,
                 std::pair<f16_t, f16_t>* ulp1i= nullptr);

            // call f(a, b), returns also the interval
            // containing the unrounded result
            f16_t
            func(f16_t a, f16_t b, f2_t f,
                 std::pair<f16_t, f16_t>* ulp1i= nullptr);

            // call f(a), returns also the interval
            // containing the unrounded result
            f16_t
            func(f16_t a, int ib, f2fi_t f,
                 std::pair<f16_t, f16_t>* ulp1i= nullptr);

            // call f(a), returns also the interval
            // containing the unrounded result
            bf16_t
            func(bf16_t a, f1_t f,
                 std::pair<bf16_t, bf16_t>* ulp1i= nullptr);

            // call f(a), returns also the intervals
            // containing the unrounded results
            std::pair<bf16_t, bf16_t>
            func(bf16_t a, f1p_t f,
                 std::pair<bf16_t, bf16_t>* ulp1i0 = nullptr,
                 std::pair<bf16_t, bf16_t>* ulp1i1 = nullptr);

            // call f(a, i), returns also the interval
            // containing the unrounded result
            bf16_t
            func(int32_t* ip, bf16_t a, f1i_t f,
                 std::pair<bf16_t, bf16_t>* ulp1i= nullptr);

            // call f(a, b), returns also the interval
            // containing the unrounded result
            bf16_t
            func(bf16_t a, bf16_t b, f2_t f,
                 std::pair<bf16_t, bf16_t>* ulp1i= nullptr);

            // call f(a), returns also the interval
            // containing the unrounded result
            bf16_t
            func(bf16_t a, int ib, f2fi_t f,
                 std::pair<bf16_t, bf16_t>* ulp1i= nullptr);


            namespace impl {

                // mpfr result to interval conversion:
                // returns [nextafter(res, -inf), res] for mpfr_res > 0
                // returns [res, nextafter(res, +inf)] for mpfr_res < 0
                // returns [res, res] for mpfr_res=0
                template <class _T>
                std::pair<_T, _T>
                ulp1_interval(_T res, int mpfr_res);

            }

            // mpfr result to interval conversion:
            // returns [nextafter(res, -inf), res] for mpfr_res > 0
            // returns [res, nextafter(res, +inf)] for mpfr_res < 0
            // returns [res, res] for mpfr_res=0
            template <class _T>
            std::pair<_T, _T>
            ulp1_interval(_T res, int mpfr_res);

            // mpfr result to interval conversion:
            // returns [nextafter(res, -inf), res] for mpfr_res > 0
            // returns [res, nextafter(res, +inf)] for mpfr_res < 0
            // returns [res, res] for mpfr_res=0
            std::pair<bf16_t, bf16_t>
            ulp1_interval(bf16_t res, int mpfr_res);

            class set_emin_emax {
                mpfr_exp_t _emin;
                mpfr_exp_t _emax;
            protected:
                static
                constexpr const mpfr_exp_t double_emin=-1022-(53-1)+1;
                static
                constexpr const mpfr_exp_t double_emax=1023+1;

                static
                constexpr const mpfr_exp_t float_emin=-126-(24-1)+1;
                static
                constexpr const mpfr_exp_t float_emax=127+1;

                static
                constexpr const mpfr_exp_t half_emin=-14-(11-1)+1;
                static
                constexpr const mpfr_exp_t half_emax=15+1;

                static
                constexpr const mpfr_exp_t bfloat16_emin=-126-(24-16-1)+1;
                static
                constexpr const mpfr_exp_t bfloat16_emax=127+1;

                set_emin_emax(mpfr_exp_t emin, mpfr_exp_t emax)
                    : _emin(mpfr_get_emin()), _emax(mpfr_get_emax()) {
                    mpfr_set_emin(emin);
                    mpfr_set_emax(emax);
                }
            public:
                ~set_emin_emax() {
                    mpfr_set_emin(_emin);
                    mpfr_set_emax(_emax);
                }
            };

            class double_emin_emax : public set_emin_emax {
            public:
                double_emin_emax() : set_emin_emax(double_emin, double_emax) {}
            };

            class float_emin_emax : public set_emin_emax {
            public:
                float_emin_emax() : set_emin_emax(float_emin, float_emax) {}
            };

            class half_emin_emax : public set_emin_emax {
            public:
                half_emin_emax() : set_emin_emax(half_emin, half_emax) {}
            };

            class bfloat16_emin_emax : public set_emin_emax {
            public:
                bfloat16_emin_emax()
                    : set_emin_emax(bfloat16_emin, bfloat16_emax) {}
            };

        }

        // wrapper around a mpfr_t
        class fpn_handle {
            mpfr_t _v;
        public:
            explicit fpn_handle(std::size_t prec);
            fpn_handle(const mpfr_t t);
            fpn_handle(double x, std::size_t prec);
            fpn_handle(float x, std::size_t prec);
            fpn_handle(f16_t x, std::size_t prec);
            fpn_handle(bf16_t x, std::size_t prec);
            fpn_handle(const fpn_handle& r);
            fpn_handle(fpn_handle&& r);
            fpn_handle& operator=(const mpfr_t r);
            fpn_handle& operator=(const fpn_handle& r);
            fpn_handle& operator=(fpn_handle&& r);
            template <class _F, std::size_t _N>
            fpn_handle(const fp_expansion<_F, _N>& d, std::size_t prec);
            ~fpn_handle();
            mpfr_t& operator()() { return _v; };
            const mpfr_t& operator()() const { return _v; }
            mpfr_prec_t prec() const { return mpfr_get_prec(_v); }
            explicit operator double() const;
            explicit operator float() const;
            explicit operator f16_t() const;
            explicit operator bf16_t() const;
            template <std::size_t _N>
            explicit operator fp_expansion<double, _N>() const;
            template <std::size_t _N>
            explicit operator fp_expansion<float, _N>() const;
            template <std::size_t _N>
            explicit operator fp_expansion<f16_t, _N>() const;
        };

        bool
        operator<(const fpn_handle& a, const fpn_handle& b);
        bool
        operator<=(const fpn_handle& a, const fpn_handle& b);
        bool
        operator==(const fpn_handle& a, const fpn_handle& b);
        bool
        operator!=(const fpn_handle& a, const fpn_handle& b);
        bool
        operator>=(const fpn_handle& a, const fpn_handle& b);
        bool
        operator>(const fpn_handle& a, const fpn_handle& b);

        fpn_handle
        operator-(const fpn_handle& b);

        fpn_handle&
        operator+=(fpn_handle& a, const fpn_handle& b);
        fpn_handle&
        operator-=(fpn_handle& a, const fpn_handle& b);
        fpn_handle&
        operator*=(fpn_handle& a, const fpn_handle& b);
        fpn_handle&
        operator/=(fpn_handle& a, const fpn_handle& b);

        fpn_handle
        operator+(const fpn_handle& a, const fpn_handle& b);
        fpn_handle
        operator-(const fpn_handle& a, const fpn_handle& b);
        fpn_handle
        operator*(const fpn_handle& a, const fpn_handle& b);
        fpn_handle
        operator/(const fpn_handle& a, const fpn_handle& b);

        namespace mpfr_ext {
            // return exp(x*x) with res precision bits
            int
            exp_px2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return exp(-x*x) with res precision bits
            int
            exp_mx2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return 2^(x*x) with res precision bits
            int
            exp2_px2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return 2^(-x*x) with res precision bits
            int
            exp2_mx2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return 10^(x*x) with res precision bits
            int
            exp10_px2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return 10^(-x*x) with res precision bits
            int
            exp10_mx2(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return x^-(1/3)
            int
            rcbrt(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return x^(1/12)
            int
            root12(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // x ^ (1/n), n may be negative
            int
            rootn(mpfr_t y, const mpfr_t x, long int n, mpfr_rnd_t rm);

            // return true if x is an half integer
            bool
            is_half_integer(const mpfr_t x);

            // 1/(1+exp(-x))
            int
            sig(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // returns c_n*x^n + .. c_1*x^1 + c_0, nullptr as last
            // argument
            int
            horner(mpfr_t res,
                   const mpfr_t x,
                   mpfr_rnd_t rm,
                   const mpfr_t c_n,
                   ...);

            bool
            mpfr_equal_or_nan(const mpfr_t a, const mpfr_t b);

            // int F(mfpr_t y, const mpfr_t x, mpfr_rnd_t rm)
            template <typename _F>
            int
            call_ziv_func(mpfr_t y, const mpfr_t x,
                          mpfr_rnd_t rm, _F f);
        }

        template <std::size_t _B>
        class mpfr_real : public fpn_handle {
        public:
            mpfr_real() : fpn_handle(_B) {}
            mpfr_real(double x) : fpn_handle(x, _B) {}
            mpfr_real(float f) : fpn_handle(f, _B) {}
            mpfr_real(f16_t f) : fpn_handle(f, _B) {}
            mpfr_real(bf16_t f) : fpn_handle(f, _B) {}
            template <class _F>
            mpfr_real(const d_real<_F>& d) : fpn_handle(d, _B) {}
            template <class _F>
            mpfr_real(const t_real<_F>& t) : fpn_handle(t, _B) {}
            template <class _F, std::size_t _N>
            mpfr_real(const fp_expansion<_F, _N>& t)
                : fpn_handle(t, _B) {}
        };

        template <std::size_t _B>
        const mpfr_real<_B>&
        operator+(const mpfr_real<_B>& a) {
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        operator-(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_neg(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        operator+(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            mpfr_real<_B> r;
            mpfr_add(r(), a(), b(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>&
        operator+=(mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            auto t= a +b;
            a = t;
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        operator-(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            mpfr_real<_B> r;
            mpfr_sub(r(), a(), b(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>&
        operator-=(mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            auto t= a - b;
            a = t;
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        operator*(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            mpfr_real<_B> r;
            mpfr_mul(r(), a(), b(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>&
        operator*=(mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            auto t= a * b;
            a = t;
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        operator/(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            mpfr_real<_B> r;
            mpfr_div(r(), a(), b(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>&
        operator/=(mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            auto t = a/b;
            a = t;
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        max(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            if (a > b) {
                return a;
            }
            return b;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        min(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            if (a< b) {
                return a;
            }
            return b;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        abs(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_abs(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        exp(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_exp(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        pow(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            mpfr_real<_B> r;
            mpfr_pow(r(), a(), b(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        log(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_log(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        log2(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_log2(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        log10(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_log10(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        sin(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_sin(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        cos(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_cos(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        erf(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_erf(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        tanh(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_tanh(r(), a(), MPFR_RNDN);
            return r;
        }

        template <std::size_t _B>
        void
        load_pi(mpfr_real<_B>& r) {
            mpfr_const_pi(r(), MPFR_RNDN);
        }

    }
}

template <class _T>
std::pair<_T, _T>
cftal::test::call_mpfr::impl::ulp1_interval(_T res, int mpres)
{
    std::pair<_T, _T> pr(res, res);
    const _T up=std::numeric_limits<_T>::infinity();
    const _T down=-std::numeric_limits<_T>::infinity();
    if (mpres > 0) {
        // res is greater than the real value
        using std::nextafter;
        pr.first = nextafter(res, down);
    } else if (mpres < 0) {
        // res is smaller than the real value
        using std::nextafter;
        pr.second = nextafter(res, up);
    } else if (mpres == 0) {
        // res is exact:
        // pr.first = std::nextafter(res, down);
        // pr.second = std::nextafter(res, up);
        // exact result --> no interval for faithul rounding
        pr.first = pr.second= res;
    }
    return pr;
}

template <class _T>
std::pair<_T, _T>
cftal::test::call_mpfr::ulp1_interval(_T res, int mpres)
{
    return impl::ulp1_interval(res, mpres);
}

inline
cftal::test::fpn_handle::fpn_handle(std::size_t prec)
    : _v()
{
    mpfr_init2(_v, prec);
}

inline
cftal::test::fpn_handle::fpn_handle(const mpfr_t r)
    : _v()
{
    mpfr_init2(_v, mpfr_get_prec(r));
    mpfr_set(_v, r, MPFR_RNDN);
}

inline
cftal::test::fpn_handle::fpn_handle(double x, std::size_t prec)
    : _v()
{
    mpfr_init2(_v, prec);
    mpfr_set_d(_v, x, MPFR_RNDN);
}

inline
cftal::test::fpn_handle::fpn_handle(float f, std::size_t prec)
    : _v()
{
    mpfr_init2(_v, prec);
    mpfr_set_flt(_v, f, MPFR_RNDN);
}

inline
cftal::test::fpn_handle::fpn_handle(f16_t h, std::size_t prec)
    : fpn_handle(float(h), prec)
{
}

inline
cftal::test::fpn_handle::fpn_handle(bf16_t h, std::size_t prec)
    : fpn_handle(float(h), prec)
{
}

inline
cftal::test::fpn_handle::fpn_handle(const fpn_handle& r)
    : _v()
{
    mpfr_init2(_v, mpfr_get_prec(r._v));
    mpfr_set(_v, r._v, MPFR_RNDN);
}

inline
cftal::test::fpn_handle::fpn_handle(fpn_handle&& r)
    : _v()
{
    mpfr_init2(_v, mpfr_get_prec(r._v));
    mpfr_swap(_v, r._v);
}

inline
cftal::test::fpn_handle&
cftal::test::fpn_handle::operator=(const fpn_handle& r)
{
    if (&r != this) {
        mpfr_prec_t pr=mpfr_get_prec(r._v);
        mpfr_prec_t pt=mpfr_get_prec(_v);
        if (pr != pt) {
            mpfr_clear(_v);
            mpfr_init2(_v, pr);
        }
        mpfr_set(_v, r._v, MPFR_RNDN);
    }
    return *this;
}

inline
cftal::test::fpn_handle&
cftal::test::fpn_handle::operator=(fpn_handle&& r)
{
    mpfr_swap(_v, r._v);
    return *this;
}

inline
cftal::test::fpn_handle&
cftal::test::fpn_handle::operator=(const mpfr_t r)
{
    if (r != this->_v) {
        mpfr_prec_t pr=mpfr_get_prec(r);
        mpfr_prec_t pt=mpfr_get_prec(_v);
        if (pr != pt) {
            mpfr_clear(_v);
            mpfr_init2(_v, pr);
        }
        mpfr_set(_v, r, MPFR_RNDN);
    }
    return *this;
}


template <class _F, std::size_t _N>
inline
cftal::test::fpn_handle::
fpn_handle(const fp_expansion<_F, _N>& d, std::size_t p)
    : fpn_handle(d[0], p)
{
    for (std::size_t i=1; i<_N; ++i) {
        fpn_handle t(d[i], p);
        mpfr_add(_v, _v, t(), MPFR_RNDN);
    }
}

inline
cftal::test::fpn_handle::~fpn_handle()
{
    mpfr_clear(_v);
}

inline
cftal::test::fpn_handle::operator double() const
{
    double r=mpfr_get_d(_v, MPFR_RNDN);
    return r;
}

template <std::size_t _N>
inline
cftal::test::fpn_handle::operator fp_expansion<double, _N>() const
{
    fp_expansion<double, _N> r;
    fpn_handle t(*this);
    double ri=double(t);
    r[0] = ri;
    for (std::size_t i=1; i<_N; ++i) {
        fpn_handle ti(ri, prec());
        mpfr_sub(t(), t(), ti(), MPFR_RNDN);
        ri=double(t);
        r[i] = ri;
    }
    return r;
}

inline
cftal::test::fpn_handle::operator float() const
{
    float r=mpfr_get_flt(_v, MPFR_RNDN);
    return r;
}

template <std::size_t _N>
inline
cftal::test::fpn_handle::operator fp_expansion<float, _N>() const
{
    fp_expansion<float, _N> r;
    fpn_handle t(*this);
    float ri=float(t);
    r[0] = ri;
    for (std::size_t i=1; i<_N; ++i) {
        fpn_handle ti(ri, prec());
        mpfr_sub(t(), t(), ti(), MPFR_RNDN);
        ri=float(t);
        r[i] = ri;
    }
    return r;
}

inline
cftal::test::fpn_handle::operator f16_t() const
{
    call_mpfr::half_emin_emax g;
    MPFR_DECL_INIT(t, 11);
    int mpres=mpfr_set(t, _v, MPFR_RNDN);
    mpres=mpfr_subnormalize(t, mpres, MPFR_RNDN);
    float fr=mpfr_get_flt(t, MPFR_RNDN);
    f16_t r=static_cast<f16_t>(fr);
    return r;
}

template <std::size_t _N>
inline
cftal::test::fpn_handle::operator fp_expansion<f16_t, _N>() const
{
    fp_expansion<f16_t, _N> r;
    fpn_handle t(*this);
    f16_t ri=static_cast<f16_t>(t);
    r[0] = ri;
    for (std::size_t i=1; i<_N; ++i) {
        fpn_handle ti(ri, prec());
        mpfr_sub(t(), t(), ti(), MPFR_RNDN);
        ri=static_cast<f16_t>(t);
        r[i] = ri;
    }
    return r;
}

inline
cftal::test::fpn_handle::operator bf16_t() const
{
    call_mpfr::bfloat16_emin_emax g;
    MPFR_DECL_INIT(t, 8);
    int mpres=mpfr_set(t, _v, MPFR_RNDN);
    mpres=mpfr_subnormalize(t, mpres, MPFR_RNDN);
    float fr=mpfr_get_flt(t, MPFR_RNDN);
    bf16_t r=static_cast<bf16_t>(fr);
    return r;
}

inline
bool
cftal::test::operator<(const fpn_handle& a, const fpn_handle& b)
{
    return mpfr_less_p(a(), b());
}

inline
bool
cftal::test::operator<=(const fpn_handle& a, const fpn_handle& b)
{
    return mpfr_lessequal_p(a(), b());
}

inline
bool
cftal::test::operator==(const fpn_handle& a, const fpn_handle& b)
{
    return mpfr_equal_p(a(), b());
}

inline
bool
cftal::test::operator!=(const fpn_handle& a, const fpn_handle& b)
{
    return !mpfr_equal_p(a(), b());
}

inline
bool
cftal::test::operator>=(const fpn_handle& a, const fpn_handle& b)
{
    return mpfr_greaterequal_p(a(), b());
}

inline
bool
cftal::test::operator>(const fpn_handle& a, const fpn_handle& b)
{
    return mpfr_greater_p(a(), b());
}

inline
cftal::test::fpn_handle
cftal::test::operator-(const fpn_handle& a)
{
    fpn_handle n(a);
    mpfr_neg(n(), a(), MPFR_RNDN);
    return n;
}

inline
cftal::test::fpn_handle&
cftal::test::operator+=(fpn_handle& a, const fpn_handle& b)
{
    mpfr_add(a(), a(), b(), MPFR_RNDN);
    return a;
}

inline
cftal::test::fpn_handle&
cftal::test::operator-=(fpn_handle& a, const fpn_handle& b)
{
    mpfr_sub(a(), a(), b(), MPFR_RNDN);
    return a;
}

inline
cftal::test::fpn_handle&
cftal::test::operator*=(fpn_handle& a, const fpn_handle& b)
{
    mpfr_mul(a(), a(), b(), MPFR_RNDN);
    return a;
}

inline
cftal::test::fpn_handle&
cftal::test::operator/=(fpn_handle& a, const fpn_handle& b)
{
    mpfr_div(a(), a(), b(), MPFR_RNDN);
    return a;
}

inline
cftal::test::fpn_handle
cftal::test::operator+(const fpn_handle& a, const fpn_handle& b)
{
    fpn_handle t(std::max(a.prec(), b.prec()));
    mpfr_add(t(), a(), b(), MPFR_RNDN);
    return t;
}

inline
cftal::test::fpn_handle
cftal::test::operator-(const fpn_handle& a, const fpn_handle& b)
{
    fpn_handle t(std::max(a.prec(), b.prec()));
    mpfr_sub(t(), a(), b(), MPFR_RNDN);
    return t;
}

inline
cftal::test::fpn_handle
cftal::test::operator*(const fpn_handle& a, const fpn_handle& b)
{
    fpn_handle t(std::max(a.prec(), b.prec()));
    mpfr_mul(t(), a(), b(), MPFR_RNDN);
    return t;
}

inline
cftal::test::fpn_handle
cftal::test::operator/(const fpn_handle& a, const fpn_handle& b)
{
    fpn_handle t(std::max(a.prec(), b.prec()));
    mpfr_div(t(), a(), b(), MPFR_RNDN);
    return t;
}

inline
bool
cftal::test::mpfr_ext::
mpfr_equal_or_nan(const mpfr_t a, const mpfr_t b)
{
    return (mpfr_nan_p(a) && mpfr_nan_p(b)) || (mpfr_cmp(a, b)==0);
}

template <typename _F>
int
cftal::test::mpfr_ext::
call_ziv_func(mpfr_t yf, const mpfr_t x, mpfr_rnd_t rm, _F f)
{
    fpn_handle y1(yf);
    fpn_handle y2(yf);
    fpn_handle x1(x);
    int r1, r2;

    mpfr_prec_t start_prec= ((mpfr_get_prec(x) + 31)/32)*32;
    mpfr_set_prec(x1(), start_prec);
    mpfr_set(x1(), x, MPFR_RNDN);
    r1 = f(y1(), x1(), rm);
    while (r1 !=0) {
        mpfr_set_prec(x1(), x1.prec()+32);
        mpfr_set(x1(), x, MPFR_RNDN);
        r2 = f(y2(), x1(), rm);
        if ((mpfr_equal_or_nan(y2(), y1()) == true) &&
            (r1 == r2)) {
            break;
        }
        std::swap(r1, r2);
        mpfr_swap(y1(), y2());
    }
    mpfr_set(yf, y1(), MPFR_RNDN);
    return r1;
}

// Local variables:
// mode: c++
// end:
#endif
