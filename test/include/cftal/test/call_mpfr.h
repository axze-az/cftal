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

        class fpn_handle {
            mpfr_t _v;
            void cleanup();
        protected:
            fpn_handle(std::size_t prec);
            fpn_handle(mpfr_t t);
            fpn_handle(double x, std::size_t prec);
            fpn_handle(float x, std::size_t prec);
            fpn_handle(const fpn_handle& r);
            fpn_handle(fpn_handle&& r);
            fpn_handle& operator=(const fpn_handle& r);
            fpn_handle& operator=(fpn_handle&& r);
            ~fpn_handle();
        public:
            mpfr_t& operator()() { return _v; };
            const mpfr_t& operator()() const { return _v; }
        };

        template <std::size_t _B>
        class mpfr_real : public fpn_handle {
        public:
            mpfr_real() : fpn_handle(_B) {}
            mpfr_real(double x) : fpn_handle(x, _B) {}
            // mpfr_real(float f) : fpn_handle(f, _B) {}
            template <class _F>
            mpfr_real(const d_real<_F>& d);
            template <class _F>
            mpfr_real(const t_real<_F>& t);
            explicit operator double() const;
            explicit operator float() const;
            explicit operator d_real<double>() const;
            explicit operator t_real<double>() const;
            explicit operator d_real<float>() const;
            explicit operator t_real<float>() const;
        };

        template <std::size_t _B>
        bool
        operator<(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_cmp(a(), b()) <0;
        }

        template <std::size_t _B>
        bool
        operator<=(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_cmp(a(), b()) <=0;
        }

        template <std::size_t _B>
        bool
        operator==(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_cmp(a(), b()) ==0;
        }

        template <std::size_t _B>
        bool
        operator!=(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_cmp(a(), b()) !=0;
        }

        template <std::size_t _B>
        bool
        operator>=(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_cmp(a(), b()) >=0;
        }

        template <std::size_t _B>
        bool
        operator>(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_cmp(a(), b()) >0;
        }

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
        pr.first = std::nextafter(res, down);
        pr.second = std::nextafter(res, up);
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
cftal::test::fpn_handle::~fpn_handle()
{
    mpfr_clear(_v);
}

template <std::size_t _B>
template <class _F>
cftal::test::mpfr_real<_B>::mpfr_real(const d_real<_F>& d)
    : fpn_handle(d.h(), _B)
{
    mpfr_real<_B> l(d.l());
    *this += l;
}

template <std::size_t _B>
template <class _F>
cftal::test::mpfr_real<_B>::mpfr_real(const t_real<_F>& d)
    : fpn_handle(d.h(), _B)
{
    mpfr_real<_B> m(d.m());
    mpfr_real<_B> l(d.l());
    *this += m;
    *this += l;
}

template <std::size_t _B>
cftal::test::mpfr_real<_B>::operator double() const
{
    mpfr_real<_B> t(*this);
    double r=mpfr_get_d(t(), MPFR_RNDN);
    return r;
}

template <std::size_t _B>
cftal::test::mpfr_real<_B>::operator d_real<double>() const
{
    mpfr_real<_B> t(*this);
    double h= double(t);
    t -= mpfr_real<_B>(h);
    double l= double(t);
    return d_real<double>(h, l);
}

template <std::size_t _B>
cftal::test::mpfr_real<_B>::operator t_real<double>() const
{
    mpfr_real<_B> t(*this);
    double h= double(t);
    t -= mpfr_real<_B>(h);
    double m= double(t);
    t -= mpfr_real<_B>(m);
    double l= double(t);
    return t_real<double>(h, m, l);
}

template <std::size_t _B>
cftal::test::mpfr_real<_B>::operator float() const
{
    float r=mpfr_get_flt((*this)(), MPFR_RNDN);
    return r;
}

template <std::size_t _B>
cftal::test::mpfr_real<_B>::operator d_real<float>() const
{
    mpfr_real<_B> t(*this);
    float h= float(t);
    t -= mpfr_real<_B>(h);
    float l= float(t);
    return d_real<float>(h, l);
}

template <std::size_t _B>
cftal::test::mpfr_real<_B>::operator t_real<float>() const
{
    mpfr_real<_B> t(*this);
    float h= float(t);
    t -= mpfr_real<_B>(h);
    float m= float(t);
    t -= mpfr_real<_B>(m);
    float l= float(t);
    return t_real<float>(h, m, l);
}



// Local variables:
// mode: c++
// end:
#endif
