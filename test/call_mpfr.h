#if !defined (__CFTAL_TEST_CALL_MPFR_H__)
#define __CFTAL_TEST_CALL_MPFR_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/d_real.h>
#include <cftal/t_real.h>
#include <mpfr.h>

namespace cftal {
    namespace test {

        namespace call_mpfr {

            using f1_t = int (*)(mpfr_t, const mpfr_t,
                                 mpfr_rnd_t);
            using f2_t = int (*)(mpfr_t, const mpfr_t,
                                 const mpfr_t, mpfr_rnd_t);

            double
            func(double a, f1_t f);

            double
            func(double a, double b, f2_t f);

            template <typename _F>
            float
            func(float a, _F f);

            template <typename _F>
            float
            func(float a, float b, _F f);

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
            explicit operator double() const {
                double r=mpfr_get_d((*this)(), MPFR_RNDN);
                return r;
            }
            explicit operator float() const {
                float r=mpfr_get_flt((*this)(), MPFR_RNDN);
                return r;
            }
        };

        template <std::size_t _B>
        bool
        operator<(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return b > a;
        }

        template <std::size_t _B>
        bool
        operator<=(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return !(a > b);
        }

        template <std::size_t _B>
        bool
        operator==(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_equal_p(a(), b());
        }

        template <std::size_t _B>
        bool
        operator!=(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return !(a==b);
        }

        template <std::size_t _B>
        bool
        operator>=(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_greaterequal_p(a(), b());
        }

        template <std::size_t _B>
        bool
        operator>(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            return mpfr_greater_p(a(), b());
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
            a = a + b;
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
            a = a - b;
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
            a = a * b;
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
            a = a / b;
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        max(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            if (mpfr_greater_p(a, b)) {
                return a;
            }
            return b;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        min(const mpfr_real<_B>& a, const mpfr_real<_B>& b) {
            if (mpfr_greater_p(b, a)) {
                return b;
            }
            return a;
        }

        template <std::size_t _B>
        mpfr_real<_B>
        abs(const mpfr_real<_B>& a) {
            mpfr_real<_B> r;
            mpfr_abs(r(), a(), MPFR_RNDN);
            return r;
        }

    }
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
}

inline
cftal::test::fpn_handle::fpn_handle(fpn_handle&& r)
    : _v()
{
    mpfr_init2(_v, 10);
    mpfr_swap(_v, r._v);
}

inline
cftal::test::fpn_handle&
cftal::test::fpn_handle::operator=(const fpn_handle& r)
{
    if (&r != this) {
        mpfr_clear(_v);
        mpfr_init_set(_v, r._v, MPFR_RNDN);
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
    mpfr_add((*this)(), (*this)(), l(), MPFR_RNDN);
}

template <std::size_t _B>
template <class _F>
cftal::test::mpfr_real<_B>::mpfr_real(const t_real<_F>& d)
    : fpn_handle(d.h(), _B)
{
    mpfr_real<_B> m(d.m());
    mpfr_add((*this)(), (*this)(), m(), MPFR_RNDN);
    mpfr_real<_B> l(d.l());
    mpfr_add((*this)(), (*this)(), l(), MPFR_RNDN);
}


// Local variables:
// mode: c++
// end:
#endif
