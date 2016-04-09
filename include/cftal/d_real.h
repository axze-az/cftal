#if !defined (__CFTAL_D_REAL_H__)
#define __CFTAL_D_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/select.h>
#include <cftal/std_types.h>
#include <cmath>
#include <type_traits>
#include <limits>

namespace cftal {

    template <class _T>
    _T fms(const _T& a, const _T& b, const _T& c)
    {
        return fma(a, b, -c);
    }

    template <typename _T>
    struct d_real_traits {};

    template <typename _T>
    struct has_fma {};

    // fma ?
    template <>
    struct has_fma<double> {
#if defined (FP_FAST_FMA) && (FP_FAST_FMA > 0)
        static constexpr bool fma = true;
#else
        static constexpr bool fma = false;
#endif
    };

    // fma ?
    template <>
    struct has_fma<float> {
#if defined (FP_FAST_FMAF) && (FP_FAST_FMAF > 0)
        static constexpr bool fma = true;
#else
        static constexpr bool fma = false;
#endif
    };

    template <>
    struct d_real_traits<double> : public has_fma<double> {
        constexpr d_real_traits<double>() = default;
        // result of a comparison operator
        typedef bool cmp_result_type;
        // corresponding integer type for ldexp, frexp
        using int_type = int32_t;

        static constexpr double eps() {
            // 2^-104
            return 4.93038065763132e-32;
        }

        // return true if any in b is true
        static bool any(const cmp_result_type& b) {
            return b;
        }
        // select an value
        static double sel(const cmp_result_type& s,
                          const double& on_true,
                          const double& on_false) {
            return s ? on_true : on_false;
        }

        static
        void split(double a, double& hi, double& lo) {
            // 2^996 = 2^{1023-28+1}
            const double split_threshold=
                6.69692879491417e+299;
            // 2^27 + 1
            const double split_val =
                134217729.0;
            // 2^-28
            const double split_scale_down=
                3.7252902984619140625e-09;
            // 2^28
            const double split_scale_up =
                268435456.0;
            cmp_result_type is_big(std::fabs(a) > split_threshold);
            double temp;
            if (unlikely(any(is_big))) {
                a*=split_scale_down;
                temp = split_val*a;
                hi=temp-(temp-a);
                lo= a-hi;
                hi*= split_scale_up;
                lo*= split_scale_up;
            } else {
                temp=split_val *a;
                hi=temp-(temp-a);
                lo=a-hi;
            }
        }

        static
        double
        scale_div_threshold() {
            return 0x1.p-969;
        }

    };

    template <>
    struct d_real_traits<float> : public has_fma<float> {
        constexpr d_real_traits<float>() = default;
        // result of a comparison operator
        typedef bool cmp_result_type;
        // corresponding integer type for ldexp, frexp
        using int_type = int32_t;

        static bool any(const cmp_result_type& b) {
            return b;
        }
        static float sel(const cmp_result_type& s,
                         const float& on_true,
                         const float& on_false) {
            return s ? on_true : on_false;
        }

        static
        void split(float a, float& hi, float& lo) {
            // 2^13 + 1
            const float split_val=8193.0f;
            // 2^115 = 2^{127-14+1}
            const float split_threshold= 4.15383749e+34f;
            // 2^-14
            const float split_scale_down = 1.0f/16384.0f;
            // 2^14
            const float split_scale_up = 16384.0f;
            cmp_result_type is_big(std::fabs(a) > split_threshold);
            float temp;
            if (unlikely(any(is_big))) {
                a*=split_scale_down;
                temp = split_val*a;
                hi=temp-(temp-a);
                lo= a-hi;
                hi*= split_scale_up;
                lo*= split_scale_up;
            } else {
                temp=split_val *a;
                hi=temp-(temp-a);
                lo=a-hi;
            }
        }

        static
        float
        scale_div_threshold() {
            // -126 + 24
            return 0x1.p-102f;
        }

    };

    template <typename _T>
    class d_real {
        _T _h;
        _T _l;
    public:
        using value_type = _T;
        constexpr d_real() : _h(0), _l(0) {}
        template <typename _U>
        constexpr d_real(const d_real<_U>& r) : _h(r.h()), _l(r.l()) {}
        constexpr d_real(const _T& h, const _T& l) : _h(h), _l(l) {}
        constexpr d_real(const _T& h) : _h(h), _l(_T(0)) {}
        const _T& l() const { return _l; }
        _T& l() { return _l; }
        const _T& h() const { return _h; }
        _T& h() { return _h; }
    };

    namespace impl {

        template <class _T>
        struct d_real_ops_common {

            // return s + r = a + b
            // with |a| > |b|
            static
            void
            add12(_T& s, _T& r, const _T& a, const _T& b);

            // return s + r = a + b
            static
            void
            add12cond(_T& s, _T& r, const _T& a, const _T& b);

            static
            void
            add22cond(_T& zh, _T& zl,
                      const _T& xh, const _T& xl,
                      const _T& yh, const _T& al);

            static
            _T
            quick_two_sum(const _T& a, const _T& b, _T& e);

            static
            _T
            quick_two_diff(const _T& a, const _T& b, _T& e);

            static
            _T
            two_sum(const _T& a, const _T& b, _T& e);

            static
            _T
            two_diff(const _T& a, const _T& b, _T& e);

            static
            d_real<_T> add(const _T& a, const _T& b);

            static
            d_real<_T> add(const d_real<_T>& a,
                           const _T& b);
            static
            d_real<_T> add(const d_real<_T>& a,
                           const d_real<_T>& b);

            static
            d_real<_T> ieee_add(const d_real<_T>& a,
                                const d_real<_T>& b);
            static
            d_real<_T> sloppy_add(const d_real<_T>& a,
                                  const d_real<_T>& b);

            static
            d_real<_T> sub(const _T& a, const _T& b);
            static
            d_real<_T> sub(const d_real<_T>& a,
                           const _T& b);
            static
            d_real<_T> sub(const _T& a,
                           const d_real<_T>& b);
            static
            d_real<_T> sub(const d_real<_T>& a,
                           const d_real<_T>& b);
            static
            d_real<_T> ieee_sub(const d_real<_T>& a,
                                const d_real<_T>& b);
            static
            d_real<_T> sloppy_sub(const d_real<_T>& a,
                                  const d_real<_T>& b);

        };

        template <class _T, bool _FMA>
        struct d_real_ops_fma : public d_real_ops_common<_T> {
            using base_type=d_real_ops_common<_T>;
            using my_type=d_real_ops_fma<_T, _FMA>;

            static
            _T two_prod(const _T& a, const _T& b, _T& e);
            static
            _T two_sqr(const _T& a, _T& e);
            static
            d_real<_T> mul(const _T& a, const _T& b);
            static
            d_real<_T> mul(const d_real<_T>& a,
                           const _T& b);
            static
            d_real<_T> mul(const d_real<_T>& a,
                           const d_real<_T>& b);
            static
            d_real<_T> sqr(const _T& a);

            static
            d_real<_T> sqr(const d_real<_T>& a);

        };

        // specialization using no fma
        template <class _T>
        struct d_real_ops_fma<_T, false> : public d_real_ops_common<_T> {
            using base_type=d_real_ops_common<_T>;
            using my_type=d_real_ops_fma<_T, false>;

            using base_type::add12;
            using base_type::add12cond;
            using base_type::add22cond;

            static
            _T two_prod(const _T& a, const _T& b, _T& e);
            static
            _T two_sqr(const _T& a, _T& e);
            static
            d_real<_T> mul(const _T& a, const _T& b);
            static
            d_real<_T> mul(const d_real<_T>& a,
                           const _T& b);
            static
            d_real<_T> mul(const d_real<_T>& a,
                           const d_real<_T>& b);
            static
            d_real<_T> sqr(const _T& a);

            static
            d_real<_T> sqr(const d_real<_T>& a);

            static
            void
            mul12(_T& rh, _T& rl, const _T& u, const _T& v);

            static
            void
            mul22(_T& rh, _T& rl,
                  const _T& xh, const _T& xl,
                  const _T& yh, const _T& yl);
        };

        // specialization using fma
        template <class _T>
        struct d_real_ops_fma<_T, true> : public d_real_ops_common<_T> {
            using base_type=d_real_ops_common<_T>;
            using my_type=d_real_ops_fma<_T, true>;

            using base_type::add12;
            using base_type::add12cond;
            using base_type::add22cond;

            static
            _T two_prod(const _T& a, const _T& b, _T& e);
            static
            _T two_sqr(const _T& a, _T& e);
            static
            d_real<_T> mul(const _T& a, const _T& b);
            static
            d_real<_T> mul(const d_real<_T>& a,
                           const _T& b);
            static
            d_real<_T> mul(const d_real<_T>& a,
                           const d_real<_T>& b);
            static
            d_real<_T> sqr(const _T& a);

            static
            d_real<_T> sqr(const d_real<_T>& a);

            static
            void
            mul12(_T& rh, _T& rl, const _T& u, const _T& v);

            static
            void
            mul22(_T& rh, _T& rl,
                  const _T& xh, const _T& xl,
                  const _T& yh, const _T& yl);
        };


        template <class _T, bool _FMA>
        struct d_real_ops : public d_real_ops_fma<_T, _FMA> {
            using base_type=d_real_ops_fma<_T, _FMA>;
            using my_type=d_real_ops<_T, _FMA>;

            using base_type::add12;
            using base_type::add12cond;
            using base_type::add22cond;
            using base_type::mul12;
            using base_type::mul22;

            static
            void
            mul122(_T& rh, _T& rl,
                   const _T& a,
                   const _T& bh, const _T& bl);

            // a*b + c
            static
            void
            div22(_T& rh, _T& rl,
                  const _T& ah, const _T& al,
                  const _T& bh, const _T& bl);

            static
            d_real<_T> div(const _T& a, const _T& b);

            static
            d_real<_T> div(const d_real<_T>& a,
                           const _T& b);

            static
            d_real<_T> div(const d_real<_T>& a,
                           const d_real<_T>& b);

            static
            d_real<_T>
            raw_ieee_div(const d_real<_T>& a, const d_real<_T>& b);

            static
            d_real<_T>
            scaled_div(const d_real<_T>& a, const d_real<_T>& b);

            static
            d_real<_T>
            ieee_div(const d_real<_T>& a, const d_real<_T>& b);

            static
            d_real<_T> sloppy_div(const d_real<_T>& a,
                                  const d_real<_T>& b);
        };

    }

    // comparison operators
    template <typename _T>
    typename d_real_traits<_T>::cmp_result_type
    operator<(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    typename d_real_traits<_T>::cmp_result_type
    operator<=(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    typename d_real_traits<_T>::cmp_result_type
    operator==(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    typename d_real_traits<_T>::cmp_result_type
    operator!=(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    typename d_real_traits<_T>::cmp_result_type
    operator>(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    typename d_real_traits<_T>::cmp_result_type
    operator>=(const d_real<_T>& a, const d_real<_T>& b);

    // unary minus
    template <typename _T>
    d_real<_T>
    operator-(const d_real<_T>& a);
    // unary plus
    template <typename _T>
    const d_real<_T>&
    operator+(const d_real<_T>& a);

    // addition
    template <typename _T>
    d_real<_T>
    operator+(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator+(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>
    operator+(const d_real<_T>& a,  const d_real<_T>& b);

    template <typename _T>
    d_real<_T>&
    operator+=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator+=(d_real<_T>& a, const d_real<_T>& b);

    // subtraction
    template <typename _T>
    d_real<_T>
    operator-(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator-(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>
    operator-(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>&
    operator-=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator-=(d_real<_T>& a, const d_real<_T>& b);

    // multiplication
    template <typename _T>
    d_real<_T>
    operator*(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator*(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>
    operator*(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>&
    operator*=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator*=(d_real<_T>& a, const d_real<_T>& b);

    // division
    template <typename _T>
    d_real<_T>
    operator/(const d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator/(const _T& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T>
    operator/(const d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator/=(d_real<_T>& a, const _T& b);

    template <typename _T>
    d_real<_T>&
    operator/=(d_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    d_real<_T> rcp(const d_real<_T>& r);

    template <typename _T>
    d_real<_T> abs(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> rint(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> floor(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> ceil(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> trunc(const d_real<_T>& r);

    template <typename _T>
    d_real<_T> powi(const d_real<_T>& r, int e);

    template <typename _T>
    d_real<_T> sqr(const d_real<_T>& r);
    template <typename _T>
    d_real<_T> mul_pwr2(const d_real<_T>& a, const _T& b);
    template <typename _T>
    d_real<_T> sqrt(const d_real<_T>& a);

    template <typename _T>
    d_real<_T> select(const typename d_real_traits<_T>::cmp_result_type& m,
                      const d_real<_T>& on_true,
                      const d_real<_T>& on_false);

    template <typename _T>
    d_real<_T> min(const d_real<_T>& on_true,
                   const d_real<_T>& on_false);

    template <typename _T>
    d_real<_T> max(const d_real<_T>& on_true,
                   const d_real<_T>& on_false);

    d_real<double> str_to_d_double(const char* p, std::size_t n);
    d_real<double> str_to_d_double(const char* p);
    d_real<float> str_to_d_float(const char* p, std::size_t n);
    d_real<float> str_to_d_float(const char* p);

    d_real<double> operator "" _dd(const char* dd);
    d_real<float> operator "" _df(const char* df);
}


template <typename _T>
inline
void
cftal::impl::d_real_ops_common<_T>::
add12(_T& s, _T& r, const _T& a, const _T& b)
{
    _T _a = a;
    _T _b = b;
    s = _a + _b;
    _T t0 = s - _a;
    r = _b - t0;
}

template <typename _T>
inline
void
cftal::impl::d_real_ops_common<_T>::
add12cond(_T& s, _T& r, const _T& a, const _T& b)
{
    _T _a= a;
    _T _b= b;
    s = _a + _b;
    _T _u1 = s - _a;
    _T _u2 = s - _u1;
    _T _u3 = _b - _u1;
    _T _u4 = _a - _u2;
    r = _u4 + _u3;
}

template <typename _T>
inline
void
cftal::impl::d_real_ops_common<_T>::
add22cond(_T& zh, _T& zl,
          const _T& xh, const _T& xl,
          const _T& yh, const _T& yl)
{
    _T v1, v2;
    add12cond(v1, v2, xh, yh);
    _T v3 = xl + yl;
    _T v4 = v2 + v3;
    add12(zh, zl, v1, v4);
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_common<_T>::
quick_two_sum(const _T& a, const _T& b, _T& err)
{
    _T s=a+b;
    err=b-(s-a);
    return s;
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_common<_T>::
quick_two_diff(const _T& a, const _T& b, _T& err)
{
    _T s=a-b;
    err=(a-s)-b;
    return s;
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_common<_T>::
two_sum(const _T& a, const _T& b, _T& err)
{
    _T s=a+b;
    _T bb=s-a;
    err=(a-(s-bb)) + (b -bb);
    return s;
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_common<_T>::
two_diff(const _T& a, const _T& b, _T& err)
{
    _T s=a-b;
    _T bb=s-a;
    err=(a-(s-bb))-(b+bb);
    return s;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
add(const _T& a, const _T& b)
{
    _T err, s= two_sum(a, b, err);
    return d_real<_T>(s, err);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
add(const d_real<_T>& a, const _T& b)
{
    _T s1, s2;
    s1 = two_sum(a.h(), b, s2);
    s2+= a.l();
    s1 = quick_two_sum(s1, s2, s2);
    return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
ieee_add(const d_real<_T>& a, const d_real<_T>& b)
{
    _T s1, s2, t1, t2;
    s1 = two_sum(a.h(), b.h(), s2);
    t1 = two_sum(a.l(), b.l(), t2);
    s2+= t1;
    s1 = quick_two_sum(s1, s2, s2);
    s2+= t2;
    s1 = quick_two_sum(s1, s2, s2);
    return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
sloppy_add(const d_real<_T>& a, const d_real<_T>& b)
{
    _T s, e;
    s = two_sum(a.h(), b.h(), e);
    e+= (a.l() + b.l());
    s = quick_two_sum(s, e, e);
    return d_real<_T>(s, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
add(const d_real<_T>& a, const d_real<_T>& b)
{
    return ieee_add(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
sub(const _T& a, const _T& b)
{
    _T err, s= two_diff(a, b, err);
    return d_real<_T>(s, err);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
ieee_sub(const d_real<_T>& a, const d_real<_T>& b)
{
    _T s1, s2, t1, t2;
    s1 = two_diff(a.h(), b.h(), s2);
    t1 = two_diff(a.l(), b.l(), t2);
    s2+= t1;
    s1 = quick_two_sum(s1, s2, s2);
    s2+= t2;
    s1 = quick_two_sum(s1, s2, s2);
    return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
sloppy_sub(const d_real<_T>& a, const d_real<_T>& b)
{
    _T s, e;
    s = two_diff(a.h(), b.h(), e);
    e+= a.l();
    e-= b.l();
    s= quick_two_sum(s, e, e);
    return d_real<_T>(s, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
sub(const d_real<_T>& a, const _T& b)
{
    _T s1, s2;
    s1 = two_diff(a.h(), b, s2);
    s2+= a.l();
    s1 = quick_two_sum(s1, s2, s2);
    return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
sub(const _T& a, const d_real<_T>& b)
{
    _T s1, s2;
    s1 = two_diff(a, b.h(), s2);
    s2-= b.l();
    s1 = quick_two_sum(s1, s2, s2);
    return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_common<_T>::
sub(const d_real<_T>& a, const d_real<_T>& b)
{
    return ieee_sub(a, b);
}

template <typename _T>
inline
void
cftal::impl::d_real_ops_fma<_T, true>::
mul12(_T& rh, _T& rl, const _T& u, const _T& v)
{
    rh = u * v;
    rl = fms(u, v, rh);
}

template <typename _T>
inline
void
cftal::impl::d_real_ops_fma<_T, true>::
mul22(_T& pzh, _T& pzl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
    _T ph = xh * yh;
    _T pl = fms(xh, yh, ph);
    pl = fma(xh, yl, pl);
    pl = fma(xl, yh, pl);
    pzh = ph + pl;
    pzl = ph - pzh;
    pzl+= pl;
}

template <typename _T>
inline
void
cftal::impl::d_real_ops_fma<_T, false>::
mul12(_T& rh, _T& rl, const _T& a, const _T& b)
{
    _T a_h, a_l, b_h, b_l;
    using traits=d_real_traits<_T>;
    traits::split(a, a_h, a_l);
    traits::split(b, b_h, b_l);
    rh=a*b;
    rl=((a_h*b_h-rh)+a_h*b_l+a_l*b_h)+a_l*b_l;
}

template <typename _T>
inline
void
cftal::impl::d_real_ops_fma<_T, false>::
mul22(_T& pzh, _T& pzl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
    _T p1, p2;
    mul12(p1, p2, xh, yh);
    p2+= (xh*yl + xl * yh);
    add12(pzh, pzl, p1, p2);
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_fma<_T, true>::
two_prod(const _T& a, const _T& b, _T& err)
{
    _T p=a*b;
    err = fms(a, b, p);
    return p;
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_fma<_T, false>::
two_prod(const _T& a, const _T& b, _T& err)
{
    _T p=a*b;
    _T a_h, a_l, b_h, b_l;
    using traits=d_real_traits<_T>;
    traits::split(a, a_h, a_l);
    traits::split(b, b_h, b_l);
    err=((a_h*b_h-p)+a_h*b_l+a_l*b_h)+a_l*b_l;
    return p;
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_fma<_T, true>::
two_sqr(const _T& a, _T& err)
{
    _T p=a*a;
    err = fms(a, a, p);
    return p;
}

template <typename _T>
inline
_T
cftal::impl::d_real_ops_fma<_T, false>::
two_sqr(const _T& a, _T& err)
{
    _T p=a*a;
    _T a_h, a_l;
    using traits=d_real_traits<_T>;
    traits::split(a, a_h, a_l);
    err=((a_h*a_h-p)+2.0*a_h*a_l)+a_l*a_l;
    return p;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, true>::
mul(const _T& a, const _T& b)
{
    _T p, e;
    p=two_prod(a, b, e);
    return d_real<_T>(p, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, false>::
mul(const _T& a, const _T& b)
{
    _T p, e;
    p=two_prod(a, b, e);
    return d_real<_T>(p, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, true>::
mul(const d_real<_T>& a, const _T& b)
{
    _T p1, p2;
    _T ph = a.h() * b;
    _T pl = fms(a.h(), b, ph);
    // pl = fma(a.h(), b.l(), pl);
    pl = fma(a.l(), b, pl);
    p1 = ph + pl;
    p2 = (ph - p1);
    p2 += pl;
    return d_real<_T>(p1, p2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, false>::
mul(const d_real<_T>& a, const _T& b)
{
    _T p1, p2;
    p1 = two_prod(a.h(), b, p2);
    p2+= (a.l()*b);
    p1 = base_type::quick_two_sum(p1, p2, p2);
    return d_real<_T>(p1, p2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, true>::
mul(const d_real<_T>& a, const d_real<_T>& b)
{
    _T p1, p2;
    _T ph = a.h() * b.h();
    _T pl = fms(a.h(), b.h(), ph);
    pl = fma(a.h(), b.l(), pl);
    pl = fma(a.l(), b.h(), pl);
    p1 = ph + pl;
    p2 = (ph - p1);
    p2 += pl;
    return d_real<_T>(p1, p2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, false>::
mul(const d_real<_T>& a, const d_real<_T>& b)
{
    _T p1, p2;
    p1 = two_prod(a.h(), b.h(), p2);
    p2+= (a.h()*b.l() + a.l() * b.h());
    p1 = base_type::quick_two_sum(p1, p2, p2);
    return d_real<_T>(p1, p2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, true>::
sqr(const _T& a)
{
    _T p, e;
    p= two_prod(a, a);
    return d_real<_T>(p, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, false>::
sqr(const _T& a)
{
    _T p, e;
    p= two_prod(a, a);
    return d_real<_T>(p, e);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, true>::
sqr(const d_real<_T>& a)
{
    _T p1, p2, s1, s2;
    p1 = a.h() * a.h();
    p2 = fms(a.h(), a.h(), p1);
    p2 = fma(_T(2*a.h()), a.l(), p2);
    s1 = p1 + p2;
    s2 = (p1 - s1);
    s2 += p2;
    return d_real<_T>(s1, s2);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops_fma<_T, false>::
sqr(const d_real<_T>& a)
{
    _T p1, p2, s1, s2;
    p1 = two_sqr(a.h(), p2);
    p2 += 2.0 * a.h() * a.l();
    p2 += a.l() * a.l();
    s1 = base_type::quick_two_sum(p1, p2, s2);
    return d_real<_T>(s1, s2);
}

template <typename _T, bool _FMA>
inline
void
cftal::impl::d_real_ops<_T, _FMA>::
mul122(_T& rh, _T& rl,
       const _T& a,
       const _T& bh, const _T& bl)
{
    _T t1, t2, t3, t4;
    mul12(t1,t2, a, bh);
    t3 = a * bl;
    t4 = t2 + t3;
    add12(rh, rl, t1, t4);
}

template <typename _T, bool _FMA>
inline
void
cftal::impl::d_real_ops<_T, _FMA>::
div22(_T& rh, _T& rl,
      const _T& xh, const _T& xl,
      const _T& yh, const _T& yl)
{
    _T _ch = xh / yh;
    _T _uh, _ul;
    mul12(_uh, _ul, _ch, yh);
    _T _cl = xh - _uh;
    _cl-= _ul;
    _cl+= xl;
    _cl-= _ch * yl;
    _cl/= yh;
    rh = _ch + _cl;
    rl = (_ch - rh) + _cl;
}


template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
div(const _T& a, const _T& b)
{
    _T q1, q2, p1, p2, s, e;
    q1 = a/b;
    /* a - q1 * b */
    p1 = base_type::two_prod(q1, b, p2);
    s = base_type::two_diff(a, p1, e);
    e-= p2;
    /* next approximation */
    q2= (s+e)/b;
    s = base_type::quick_two_sum(q1, q2, e);
    return d_real<_T>(s, e);
}

template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
raw_ieee_div(const d_real<_T>&a, const d_real<_T>& b)
{
    _T q1, q2, q3;
    d_real<_T> r(0);
    q1 = a.h() / b.h();  /* approximate quotient */
    r = a - q1 * b;
    q2 = r.h() / b.h();
    r -= (q2 * b);
    q3 = r.h() / b.h();
    q1 = base_type::quick_two_sum(q1, q2, q2);
    r = d_real<_T>(q1, q2) + q3;
    return r;
}

template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
scaled_div(const d_real<_T>&a, const d_real<_T>& b)
{
    using traits_t=d_real_traits<_T>;
    using std::frexp;
    using std::ldexp;
    using int_type = typename traits_t::int_type;
    int_type ea, eb;
    _T sah=frexp(a.h(), &ea);
    _T sbh=frexp(b.h(), &eb);
    _T sal=ldexp(a.l(), -ea);
    _T sbl=ldexp(b.l(), -eb);
    d_real<_T> as(sah, sal);
    d_real<_T> bs(sbh, sbl);
    d_real<_T> q0=raw_ieee_div(as, bs);
    int_type eq= ea - eb;
    d_real<_T> q(ldexp(q0.h(), eq), ldexp(q0.l(), eq));
    return q;
}

template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
ieee_div(const d_real<_T>&a, const d_real<_T>& b)
{
#if 0
    return scaled_div(a, b);
#else
    using std::abs;
    using traits_t=d_real_traits<_T>;
    auto a_small = abs(a.h()) < traits_t::scale_div_threshold();
    auto b_small = abs(b.h()) < traits_t::scale_div_threshold();
    d_real<_T> q;
    auto one_small = a_small | b_small;
    if (traits_t::any(one_small)) {
        q= scaled_div(a, b);
    } else {
        q= raw_ieee_div(a, b);
    }
    return q;
#endif
}

template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
sloppy_div(const d_real<_T>&a, const d_real<_T>& b)
{
    _T s1, s2, q1, q2;
    d_real<_T> r;
    /* approximate quotient */
    q1 = a.h() / b.h();
    /* compute  this - q1 * dd */
    r = b * q1;
    s1 = base_type::two_diff(a.h(), r.h(), s2);
    s2 -= r.l();
    s2 += a.l();
    /* get next approximation */
    q2 = (s1 + s2) / b.h();
    /* renormalize */
    r.h() = base_type::quick_two_sum(q1, q2, r.l());
    return r;
}

template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
div(const d_real<_T>& a, const _T& b)
{
    _T q1, q2, p1, p2, s, e;
    d_real<_T> r;
    /* approximate quotient. */
    q1 = a.h() / b;
    /* Compute  this - q1 * d */
    p1 = base_type::two_prod(q1, b, p2);
    s = base_type::two_diff(a.h(), p1, e);
    e += a.l();
    e -= p2;
    /* get next approximation. */
    q2 = (s + e) / b;
    /* renormalize */
    r.h() = base_type::quick_two_sum(q1, q2, r.l());
    return r;
}

template <typename _T, bool _FMA>
inline
cftal::d_real<_T>
cftal::impl::d_real_ops<_T, _FMA>::
div(const d_real<_T>&a, const d_real<_T>& b)
{
    return ieee_div(a, b);
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator<(const d_real<_T>& a, const d_real<_T>& b)
{
    return (a.h() < b.h()) |
        ((a.h()==b.h()) & (a.l() < b.l()));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator<=(const d_real<_T>& a, const d_real<_T>& b)
{
    return (a.h() < b.h()) |
        ((a.h()==b.h()) & (a.l() <= b.l()));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator==(const d_real<_T>& a, const d_real<_T>& b)
{
    return ((a.h()==b.h()) & (a.l() == b.l()));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator!=(const d_real<_T>& a, const d_real<_T>& b)
{
    return ((a.h()!=b.h()) | (a.l() != b.l()));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator>=(const d_real<_T>& a, const d_real<_T>& b)
{
    return ((a.h()>b.h()) ||
            ((a.h()==b.h()) & (a.l() >= b.l())));
}

template <typename _T>
inline
typename cftal::d_real_traits<_T>::cmp_result_type
cftal::operator>(const d_real<_T>& a, const d_real<_T>& b)
{
    return ((a.h()>b.h()) |
            ((a.h()==b.h()) & (a.l() > b.l())));
}


template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a)
{
    return d_real<_T>(-a.h(), -a.l());
}

template <typename _T>
inline
const cftal::d_real<_T>&
cftal::operator+(const d_real<_T>& a)
{
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const d_real<_T>& a, const _T& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::add(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const _T& a, const d_real<_T>& b)
{
    return b + a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator+(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::add(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator+=(d_real<_T>& a, const _T& b)
{
    a= a + b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator+=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a + b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a, const _T& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::sub(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const _T& a, const d_real<_T>& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::sub(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator-(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::sub(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator-=(d_real<_T>& a, const _T& b)
{
    a= a - b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator-=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a - b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const d_real<_T>& a, const _T& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::mul(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const _T& a, const d_real<_T>& b)
{
    return b*a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator*(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::mul(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator*=(d_real<_T>& a, const _T& b)
{
    a= a * b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator*=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a * b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const d_real<_T>& a, const _T& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::div(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const _T& a, const d_real<_T>& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::div(d_real<_T>(a), b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::operator/(const d_real<_T>& a, const d_real<_T>& b)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::div(a, b);
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator/=(d_real<_T>& a, const _T& b)
{
    a= a / b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>&
cftal::operator/=(d_real<_T>& a, const d_real<_T>& b)
{
    a= a / b;
    return a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::rcp(const d_real<_T>& a)
{
    return _T(1)/a;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::abs(const d_real<_T>& a)
{
    typename d_real_traits<_T>::cmp_result_type a_lt_z=
        a < d_real<_T>(0);
    d_real<_T> an(-a);
    _T hi_res = d_real_traits<_T>::sel(
        a_lt_z, an.h(), a.h());
    _T lo_res = d_real_traits<_T>::sel(
        a_lt_z, an.l(), a.l());
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::rint(const d_real<_T>& a)
{
    _T hi= rint(a.h());
    // _T lo;

    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;

    // if hi == a.h()
    _T lo_hi_int = rint(a.l());
    _T hi_hi_int = impl_t::quick_two_sum(hi, lo_hi_int, lo_hi_int);

    // hi != a.h()
    _T lo_hi_no_int(0);
    _T hi_m1 = hi - 1.0;
    _T hi_hi_no_int = d_real_traits<_T>::sel(
        (abs(_T(hi - a.h()))==_T(0.5)) & (a.l() < _T(0.0)),
        hi_m1, hi);

    typename d_real_traits<_T>::cmp_result_type hi_eq_ah=
        hi == a.h();

    _T hi_res = d_real_traits<_T>::sel(
        hi_eq_ah, hi_hi_int, hi_hi_no_int);
    _T lo_res = d_real_traits<_T>::sel(
        hi_eq_ah, lo_hi_int, lo_hi_int);

    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::floor(const d_real<_T>& a)
{
    _T hi = floor(a.h());
    _T lo(0);
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    typename d_real_traits<_T>::cmp_result_type r=
        hi == a.h();
    _T lo_hi_int = floor(a.l());
    _T hi_hi_int = impl_t::quick_two_sum(hi, lo_hi_int, lo_hi_int);

    _T hi_res = d_real_traits<_T>::sel(
        r, hi_hi_int, hi);
    _T lo_res = d_real_traits<_T>::sel(
        r, lo_hi_int, lo);
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::ceil(const d_real<_T>& a)
{
    _T hi = floor(a.h());
    _T lo(0);
    typename d_real_traits<_T>::cmp_result_type r=
        hi == a.h();
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    _T lo_hi_int = ceil(a.l());
    _T hi_hi_int = impl_t::quick_two_sum(hi, lo_hi_int, lo_hi_int);

    _T hi_res = d_real_traits<_T>::sel(
        r, hi_hi_int, hi);
    _T lo_res = d_real_traits<_T>::sel(
        r, lo_hi_int, lo);
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::trunc(const d_real<_T>& a)
{
    typename d_real_traits<_T>::cmp_result_type a_lt_z=
        a < d_real<_T>(0);
    d_real<_T> a_floor(floor(a));
    d_real<_T> a_ceil(ceil(a));
    _T hi_res= d_real_traits<_T>::sel(
        a_lt_z, a_ceil.h(), a_floor.h());
    _T lo_res= d_real_traits<_T>::sel(
        a_lt_z, a_ceil.l(), a_floor.l());
    return d_real<_T>(hi_res, lo_res);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::powi(const d_real<_T>& a, int e)
{
    d_real<_T> r = a;
    d_real<_T> s = 1.0;
    int np = std::abs(e);
    if (np > 1) {
        /* Use binary exponentiation */
        while (np > 0) {
            if ((np & 1) == 1) {
                s *= r;
            }
            np >>= 1;
            if (np > 0)
                r = r * r;
        }
    } else {
        s = r;
    }
    /* Compute the reciprocal if n is negative. */
    if (e < 0)
        s= (_T(1.0) / s);
    return s;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::sqr(const d_real<_T>& a)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    return impl_t::sqr(a);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::mul_pwr2(const d_real<_T> &a, const _T& b)
{
    return d_real<_T>(a.h() * b, a.l() * b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::sqrt(const d_real<_T>& a)
{
    using impl_t=impl::d_real_ops<_T, d_real_traits<_T>::fma>;
    using std::sqrt;
    _T ah= a.h();
    _T root(sqrt(ah));
    _T x= _T(1.0)/root;
    _T ax= a.h() * x;
    _T err, ax2= impl_t::two_sqr(ax, err);
    d_real<_T> a0(a - d_real<_T>(ax2, err));
    _T a1(a0.h() * (x * _T(0.5)));
    d_real<_T> res(impl_t::add(ax, a1));
    return res;
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::select(const typename d_real_traits<_T>::cmp_result_type& m,
              const d_real<_T>& a, const d_real<_T>& b)
{
    _T h= select(m, a.h(), b.h());
    _T l= select(m, a.l(), b.l());
    return d_real<_T>(h, l);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::max(const d_real<_T>& a, const d_real<_T>& b)
{
    typename d_real_traits<_T>::cmp_result_type m= a > b;
    return select(m, a, b);
}

template <typename _T>
inline
cftal::d_real<_T>
cftal::min(const d_real<_T>& a, const d_real<_T>& b)
{
    typename d_real_traits<_T>::cmp_result_type m= a < b;
    return select(m, a, b);
}

// Local variables:
// mode: c++
// end:
#endif
