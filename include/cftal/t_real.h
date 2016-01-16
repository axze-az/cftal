#if !defined (__CFTAL_T_REAL_H__)
#define __CFTAL_T_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cstdlib>

namespace cftal {

    template <typename _T>
    class t_real {
        _T _h;
        _T _m;
        _T _l;
    public:
        constexpr
        t_real()
            : _h(0), _m(0), _l(0) {}
        constexpr
        t_real(_T v)
            : _h(v), _m(0), _l(0) {}
        constexpr
        t_real(_T v0, _T v1)
            : _h(v0), _m(v1), _l(0) {}
        constexpr
        t_real(_T v0, _T v1, _T v2)
            : _h(v0), _m(v1), _l(v2) {}
        template <typename _U>
        constexpr
        t_real(const t_real<_U>& r)
            : _h(r.h()), _m(r.m()), _l(r.l()) {}
        constexpr
        t_real(const d_real<_T>& h, const _T& l=_T(0))
            : _h(h.h()), _m(h.l()), _l(l) {}

        const _T& h() const { return _h; }
        const _T& m() const { return _m; }
        const _T& l() const { return _l; }
        _T& h() { return _h; }
        _T& m() { return _m; }
        _T& l() { return _l; }
    };

    template <typename _T>
    struct t_real_traits : public d_real_traits<_T> {};


    namespace impl {
        template <typename _T>
        struct t_real_ops
            : public d_real_ops<_T, d_real_traits<_T>::fma > {

            using traits_t = d_real_traits<_T>;

            static
            void
            renormalize3(_T& rh, _T& rm, _T& rl,
                         const _T& ah, const _T& am, const _T& al);

            static
            void
            mul23(_T& rh, _T& rm, _T& rl,
                  const _T& ah, const _T& al,
                  const _T& bh, const _T& bl);

            static
            void
            mul233(_T& rh, _T& rm, _T& rl,
                   const _T& ah, const _T& al,
                   const _T& bh, const _T& bm, const _T& bl);

            static
            void
            mul33(_T& rh, _T& rm, _T& rl,
                  const _T& ah, const _T& am, const _T& al,
                  const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add33cond(_T& rh, _T& rm, _T& rl,
                      const _T& ah, const _T& am, const _T& al,
                      const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add133cond(_T& rh, _T& rm, _T& rl,
                       const _T& a,
                       const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add233cond(_T& rh, _T& rm, _T& rl,
                       const _T& ah, const _T& al,
                       const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            add(_T ah, _T am, _T al,
                _T b);

            static
            t_real<_T>
            add(_T ah, _T am, _T al,
                _T bh, _T bl);

            static
            t_real<_T>
            add(_T ah, _T am, _T al,
                _T bh, _T bm, _T bl);


            static
            t_real<_T>
            mul(_T ah, _T am, _T al,
                _T b);

            static
            t_real<_T>
            mul(_T ah, _T am, _T al,
                _T bh, _T bl);

            static
            t_real<_T>
            mul(_T ah, _T am, _T al,
                _T bh, _T bm, _T bl);

            static
            t_real<_T>
            div(_T ah, _T am, _T al,
                _T bh, _T bm, _T bl);

            static
            t_real<_T>
            rcp(_T ah, _T am, _T al);
        };
    }

    // comparison operators
    template <typename _T>
    typename t_real_traits<_T>::cmp_result_type
    operator<(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    typename t_real_traits<_T>::cmp_result_type
    operator<=(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    typename t_real_traits<_T>::cmp_result_type
    operator==(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    typename t_real_traits<_T>::cmp_result_type
    operator!=(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    typename t_real_traits<_T>::cmp_result_type
    operator>(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    typename t_real_traits<_T>::cmp_result_type
    operator>=(const t_real<_T>& a, const t_real<_T>& b);

    // unary minus
    template <typename _T>
    t_real<_T>
    operator-(const t_real<_T>& a);
    // unary plus
    template <typename _T>
    const t_real<_T>&
    operator+(const t_real<_T>& a);

    // addition
    template <typename _T>
    t_real<_T>
    operator+(const _T& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator+(const d_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator+(const t_real<_T>& a,  const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator+(const t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator+(const t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator+=(t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator+=(t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>&
    operator+=(t_real<_T>& a, const t_real<_T>& b);

    // subtraction
    template <typename _T>
    t_real<_T>
    operator-(const _T& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator-(const d_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator-(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator-(const t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator-(const t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator-=(t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator-=(t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>&
    operator-=(t_real<_T>& a, const t_real<_T>& b);

    // multiplication
    template <typename _T>
    t_real<_T>
    operator*(const _T& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator*(const d_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator*(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator*(const t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator*(const t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator*=(t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator*=(t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>&
    operator*=(t_real<_T>& a, const t_real<_T>& b);

    // division
    template <typename _T>
    t_real<_T>
    operator/(const _T& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator/(const d_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator/(const t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator/(const t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>
    operator/(const t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator/=(t_real<_T>& a, const _T& b);

    template <typename _T>
    t_real<_T>&
    operator/=(t_real<_T>& a, const d_real<_T>& b);

    template <typename _T>
    t_real<_T>&
    operator/=(t_real<_T>& a, const t_real<_T>& b);

    template <typename _T>
    t_real<_T> rcp(const t_real<_T>& r);

    template <typename _T>
    t_real<_T> abs(const t_real<_T>& r);
    template <typename _T>
    t_real<_T> rint(const t_real<_T>& r);
    template <typename _T>
    t_real<_T> floor(const t_real<_T>& r);
    template <typename _T>
    t_real<_T> ceil(const t_real<_T>& r);
    template <typename _T>
    t_real<_T> trunc(const t_real<_T>& r);

    template <typename _T>
    t_real<_T> powi(const t_real<_T>& r, int e);

    template <typename _T>
    t_real<_T> sqr(const t_real<_T>& r);
    template <typename _T>
    t_real<_T> mul_pwr2(const t_real<_T>& a, const _T& b);
    template <typename _T>
    t_real<_T> sqrt(const t_real<_T>& a);

    template <typename _T>
    t_real<_T> select(const typename t_real_traits<_T>::cmp_result_type& m,
                      const t_real<_T>& on_true,
                      const t_real<_T>& on_false);

    template <typename _T>
    t_real<_T> min(const t_real<_T>& on_true,
                   const t_real<_T>& on_false);

    template <typename _T>
    t_real<_T> max(const t_real<_T>& on_true,
                   const t_real<_T>& on_false);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
renormalize3(_T& rh, _T& rm, _T& rl,
             const _T& ah, const _T& am, const _T& al)
{
    _T _t1h, _t1l, _t2l;
    add12(_t1h, _t1l, am, al);
    add12(rh, _t2l, ah, _t1h);
    add12(rm, rl, _t2l, _t1l);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
mul23(_T& rh, _T& rm, _T& rl,
      const _T& ah, const _T& al,
      const _T& bh, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    mul12(rh, t1, ah, bh);
    mul12(t2, t3, ah, bl);
    mul12(t4, t5, al, bh);
    t6 = al * bl;
    add22cond(t7, t8, t2, t3, t4, t5);
    add12(t9, t10, t1, t6);
    add22cond(rm, rl, t7, t8, t9, t10);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
mul233(_T& rh, _T& rm, _T& rl,
       const _T& ah, const _T& al,
       const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    _T t11, t12, t13, t14, t15, t16, t17, t18;
    mul12(rh, t1, ah, bh);
    mul12(t2, t3, ah, bm);
    mul12(t4, t5, ah, bl);
    mul12(t6, t7, al, bh);
    mul12(t8, t9, al, bm);
    t10 = al * bl;
    add22cond(t11, t12, t2, t3, t4, t5);
    add22cond(t13, t14, t6, t7, t8, t9);
    add22cond(t15, t16, t11, t12, t13, t14);
    add12cond(t17, t18, t1, t10);
    add22cond(rm, rl, t17, t18, t15, t16);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
mul33(_T& rh, _T& rm, _T& rl,
      const _T& ah, const _T& am, const _T& al,
       const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    _T t11, t12, t13, t14, t15, t16, t17, t18;
    _T t19, t20, t21, t22;
    mul12(rh,t1, ah , bh);
    mul12(t2,t3, ah , bm);
    mul12(t4,t5, am , bh);
    mul12(t6,t7, am , bm);
    t8 = ah * bl ;
    t9 = al * bh ;
    t10 = am * bl ;
    t11 = al * bm ;
    t12 = t8 + t9;
    t13 = t10 + t11;
    add12ond(t14,t15,t1,t6);
    t16 = t7 + t15;
    t17 = t12 + t13;
    t18 = t16 + t17;
    add12cond(t19,t20,t14,t18) ;
    add22cond(t21,t22,t2,t3,t4,t5) ;
    add22cond(rm ,rl ,t21,t22,t19,t20) ;
}


#if 0
template <typename _T>
cftal::impl::t_real_ops<_T>::
add33(_T& rh, _T& rm, _T& rl,
      const _T& ah, const _T& am, const _T& al,
      const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7, t8;
    add12(rh, _t1, ah, bh);
    add12cond(t2, t3, am, bm);
    t6 = al + bl;
    add12cond(t7, t4, t1, t2);
    t5 = t3 + t4;
    t8 = t5 + t6;
    add12cond(rm, rl, t7, t8);
}
#endif

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add33cond(_T& rh, _T& rm, _T& rl,
          const _T& ah, const _T& am, const _T& al,
          const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7, t8;
    add12cond(rh, t1, ah, bh);
    add12cond(t2, t3, am, bm);
    t6 = al + bl;
    add12cond(t7, t4, t1, t2);
    t5 = t3 + t4;
    t8 = t5 + t6;
    add12cond(rm, rl, t7, t8);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add133cond(_T& rh, _T& rm, _T& rl,
           const _T& a,
           const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4;
    add12cond(rh, t1, a, bh);
    add12cond(t2, t3, t1, bm);
    t4 = t3+ bl;
    add12cond(rm, rl, t2, t4);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add233cond(_T& rh, _T& rm, _T& rl,
           const _T& ah, const _T& al,
           const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7;
    add12cond(rh, t1, ah, bh);
    add12cond(t2, t3, al, bm);
    add12cond(t4, t5, t1, t2);
    t6 = t3 + bl;
    t7 = t6 + t5;
    add12cond(rm, rl, t4, t7);
}

#if 0
template <typename _T>
inline
void
cftal::impl::add22cond(_T& zh, _T& zl,
                       const _T& xh, const _T& xl,
                       const _T& yh, const _T& al)
{
    _T _v1, _v2;
    add12cond(_v1, v2, xh, xh);
    _T v3 = xl + yl;
    _T v4 = _v2 + _v3;
    add12(zh, zl, _v1, _v4);
}
#endif


template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::add(_T ah, _T am, _T al,
                                 _T b)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::add(_T ah, _T am, _T al,
                                 _T bh, _T bl)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::add(_T ah, _T am, _T al,
                                 _T bh, _T bm, _T bl)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::mul(_T ah, _T am, _T al,
                                 _T b)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::mul(_T ah, _T am, _T al,
                                 _T bh, _T bl)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::mul(_T ah, _T am, _T al,
                                 _T bh, _T bm, _T bl)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::div(_T ah, _T am, _T al,
                                 _T bh, _T bm, _T bl)
{
    return cftal::t_real<_T>();
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::rcp(_T ah, _T am, _T al)
{
    return cftal::t_real<_T>();
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator<(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() < b.h()) | ((a.h()==b.h()) &
                              ((a.m() < b.m()) |
                               ((a.m() == b.m()) & (a.l() < b.l()))));
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator<=(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() <= b.h()) | ((a.h()==b.h()) &
                               ((a.m() <= b.m()) |
                                ((a.m() == b.m()) & (a.l() <= b.l()))));
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator==(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() == b.h()) & (a.m() == b.m()) | (a.l() == b.l());
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator!=(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() != b.h()) | (a.m() != b.m()) | (a.l() != b.l());
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator>=(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() >= b.h()) | ((a.h()==b.h()) &
                               ((a.m() >= b.m()) |
                                ((a.m() == b.m()) & (a.l() >= b.l()))));
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator>(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() > b.h()) | ((a.h()==b.h()) &
                              ((a.m() > b.m()) |
                               ((a.m() == b.m()) & (a.l() > b.l()))));
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const t_real<_T>& a)
{
    return t_real<_T>(-a.h(), -a.m(), -a.l());
}

template <typename _T>
inline
const cftal::t_real<_T>&
cftal::operator+(const t_real<_T>& a)
{
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const _T& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(b.h(), b.m(), b.l(),
                                     a);
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(b.h(), b.m(), b.l(),
                                     a.h(), a.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const t_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const t_real<_T>& a, const d_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     b.h(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     b.h());
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator+=(t_real<_T>& a, const _T& b)
{
    a = a + b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator+=(t_real<_T>& a, const d_real<_T>& b)
{
    a = a + b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator+=(t_real<_T>& a, const t_real<_T>& b)
{
    a = a + b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const _T& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a, _T(0), _T(0),
                                     -b.h(), -b.m(), -b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.l(), _T(0),
                                     -b.h(), -b.m(), -b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const t_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     -b.h(), -b.m(), -b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const t_real<_T>& a, const d_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     -b.h(), -b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     -b.h());
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator-=(t_real<_T>& a, const _T& b)
{
    a = a - b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator-=(t_real<_T>& a, const d_real<_T>& b)
{
    a = a - b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator-=(t_real<_T>& a, const t_real<_T>& b)
{
    a = a - b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const _T& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(b.h(), b.m(), b.l(),
                                     a);
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(b.h(), b.m(), b.l(),
                                     a.h(), a.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const t_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const t_real<_T>& a, const d_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     b.h(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.m(), a.l(),
                                     b);
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator*=(t_real<_T>& a, const _T& b)
{
    a = a * b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator*=(t_real<_T>& a, const d_real<_T>& b)
{
    a = a * b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator*=(t_real<_T>& a, const t_real<_T>& b)
{
    a = a * b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const _T& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::div(a, _T(0), _T(0),
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::div(a.h(), a.l(), _T(0),
                                     a.h(), a.m(), a.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const t_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::div(a.h(), a.m(), a.l(),
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const t_real<_T>& a, const d_real<_T>& b)
{
    return impl::t_real_ops<_T>::div(a.h(), a.m(), a.l(),
                                     b.h(), b.l(), _T(0));
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::div(a.h(), a.m(), a.l(),
                                     b, _T(0), _T(0));
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator/=(t_real<_T>& a, const _T& b)
{
    a = a / b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator/=(t_real<_T>& a, const d_real<_T>& b)
{
    a = a / b;
    return a;
}

template <typename _T>
inline
cftal::t_real<_T>&
cftal::operator/=(t_real<_T>& a, const t_real<_T>& b)
{
    a = a / b;
    return a;
}



// Local variables:
// mode: c++
// end:
#endif // __CFTAL_T_REAL_H__
