//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_CALL_MPFR_H__)
#define __CFTAL_TEST_CALL_MPFR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <utility>
#include <cmath>
#include <climits>
#include <mpfr.h>

namespace cftal {
    namespace test {

        namespace call_mpfr {

            using f1_t = int (*)(mpfr_t, const mpfr_t,
                                 mpfr_rnd_t);
            using f2_t = int (*)(mpfr_t, const mpfr_t,
                                 const mpfr_t, mpfr_rnd_t);

            double
            func(double a, f1_t f,
                 std::pair<double, double>* ulp1i= nullptr);

            double
            func(double a, double b, f2_t f,
                 std::pair<double, double>* ulp1i= nullptr);

            float
            func(float a, f1_t f,
                 std::pair<float, float>* ulp1i= nullptr);

            float
            func(float a, float b, f2_t f,
                 std::pair<float, float>* ulp1i= nullptr);

            template <class _T>
            std::pair<_T, _T>
            ulp1_interval(_T res, int mpfr_res);

        }

        // wrapper around a mpfr_t
        class fpn_handle {
            mpfr_t _v;
        public:
            fpn_handle(std::size_t prec);
            fpn_handle(const mpfr_t t);
            fpn_handle(double x, std::size_t prec);
            fpn_handle(float x, std::size_t prec);
            fpn_handle(const fpn_handle& r);
            fpn_handle(fpn_handle&& r);
            fpn_handle& operator=(const mpfr_t r);
            fpn_handle& operator=(const fpn_handle& r);
            fpn_handle& operator=(fpn_handle&& r);
            template <class _F>
            fpn_handle(const d_real<_F>& d, std::size_t prec);
            template <class _F>
            fpn_handle(const t_real<_F>& t, std::size_t prec);
            ~fpn_handle();
            mpfr_t& operator()() { return _v; };
            const mpfr_t& operator()() const { return _v; }
            mpfr_prec_t prec() const { return mpfr_get_prec(_v); }
            explicit operator double() const;
            explicit operator float() const;
            explicit operator d_real<double>() const;
            explicit operator t_real<double>() const;
            explicit operator d_real<float>() const;
            explicit operator t_real<float>() const;
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

        namespace mpfr_ext {
            // return exp10 with res precision bits
            int
            exp10(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // return exp2m1 with res precision bits
            int
            exp2m1(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);
            // return exp10m1 with res precision bits
            int
            exp10m1(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);
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

            // return x^(1/12)
            int
            root12(mpfr_t res, const mpfr_t x, mpfr_rnd_t rm);

            // returns c_n*x^n + .. c_1*x^1 + c_0, nullptr as last argument
            int
            horner(mpfr_t res,
                   const mpfr_t x,
                   mpfr_rnd_t rm,
                   const mpfr_t c_n,
                   ...);

        }

        template <std::size_t _B>
        class mpfr_real : public fpn_handle {
        public:
            mpfr_real() : fpn_handle(_B) {}
            mpfr_real(double x) : fpn_handle(x, _B) {}
            mpfr_real(float f) : fpn_handle(f, _B) {}
            template <class _F>
            mpfr_real(const d_real<_F>& d) : fpn_handle(d, _B) {}
            template <class _F>
            mpfr_real(const t_real<_F>& t) : fpn_handle(t, _B) {}
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
        log10(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_log10(r(), a(), MPFR_RNDN);
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
cftal::test::call_mpfr::ulp1_interval(_T res, int mpres)
{
    std::pair<_T, _T> pr(res, res);
    const _T up=std::numeric_limits<_T>::max();
    const _T down=-std::numeric_limits<_T>::max();
    if (mpres > 0) {
        // res is greater than the real value
        pr.first = std::nextafter(res, down);
    } else if (mpres < 0) {
        // res is smaller than the real value
        pr.second = std::nextafter(res, up);
    } else if (mpres == 0) {
        // res is exact:
        // pr.first = std::nextafter(res, down);
        // pr.second = std::nextafter(res, up);
        // exact result --> no interval for faithul rounding
        pr.first = pr.second= res;
    }
    return pr;
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
        mpfr_clear(_v);
        mpfr_init2(_v, mpfr_get_prec(r._v));
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
        mpfr_clear(_v);
        mpfr_init2(_v, mpfr_get_prec(r));
        mpfr_set(_v, r, MPFR_RNDN);
    }
    return *this;
}


template <class _F>
inline
cftal::test::fpn_handle::fpn_handle(const d_real<_F>& d, std::size_t p)
    : fpn_handle(d.h(), p)
{
    fpn_handle t(d.l(), p);
    mpfr_add(_v, _v, t(), MPFR_RNDN);
}

template <class _F>
inline
cftal::test::fpn_handle::fpn_handle(const t_real<_F>& d, std::size_t p)
    : fpn_handle(d.h(), p)
{
    fpn_handle m(d.m(), p);
    mpfr_add(_v, _v, m(), MPFR_RNDN);
    fpn_handle l(d.l(), p);
    mpfr_add(_v, _v, l(), MPFR_RNDN);
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

inline
cftal::test::fpn_handle::operator d_real<double>() const
{
    double h=mpfr_get_d(_v, MPFR_RNDN);
    fpn_handle th(h, prec());
    fpn_handle tr(prec());
    mpfr_sub(tr(), _v, th(), MPFR_RNDN);
    double l=mpfr_get_d(tr(), MPFR_RNDN);
    return d_real<double>(h, l);
}

inline
cftal::test::fpn_handle::operator t_real<double>() const
{
    double h=mpfr_get_d(_v, MPFR_RNDN);
    fpn_handle th(h, prec());
    fpn_handle tr(prec());
    mpfr_sub(tr(), _v, th(), MPFR_RNDN);
    double m=mpfr_get_d(tr(), MPFR_RNDN);
    fpn_handle tm(m, prec());
    mpfr_sub(tr(), tr(), tm(), MPFR_RNDN);
    double l=mpfr_get_d(tr(), MPFR_RNDN);
    return t_real<double>(h, m, l);
}

inline
cftal::test::fpn_handle::operator float() const
{
    float r=mpfr_get_flt(_v, MPFR_RNDN);
    return r;
}

inline
cftal::test::fpn_handle::operator d_real<float>() const
{
    float h=mpfr_get_flt(_v, MPFR_RNDN);
    fpn_handle th(h, prec());
    fpn_handle tr(prec());
    mpfr_sub(tr(), _v, th(), MPFR_RNDN);
    float l=mpfr_get_flt(tr(), MPFR_RNDN);
    return d_real<float>(h, l);
}

inline
cftal::test::fpn_handle::operator t_real<float>() const
{
    float h=mpfr_get_flt(_v, MPFR_RNDN);
    fpn_handle th(h, prec());
    fpn_handle tr(prec());
    mpfr_sub(tr(), _v, th(), MPFR_RNDN);
    float m=mpfr_get_flt(tr(), MPFR_RNDN);
    fpn_handle tm(m, prec());
    mpfr_sub(tr(), tr(), tm(), MPFR_RNDN);
    float l=mpfr_get_flt(tr(), MPFR_RNDN);
    return t_real<float>(h, m, l);
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



// Local variables:
// mode: c++
// end:
#endif
