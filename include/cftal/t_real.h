//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
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
        using value_type = _T;
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
        template<typename _U>
        constexpr
        t_real(const d_real<_U>& h, const _T& l=_U(0))
            : _h(h.h()), _m(h.l()), _l(l) {}

        constexpr
        const _T& h() const { return _h; }
        constexpr
        const _T& m() const { return _m; }
        constexpr
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

            using base_type = d_real_ops<_T, d_real_traits<_T>::fma>;

            using base_type::add12;
            using base_type::add12cond;
            using base_type::add22cond;
            using base_type::mul12;
            using base_type::mul22;
            using base_type::mul122;
            using base_type::div22;

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
            mul133(_T& rh, _T& rm, _T& rl,
                   const _T& a,
                   const _T& bh, const _T& bm, const _T& bl);

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
            add123(_T& rh, _T& rm, _T& rl,
                   const _T& a,
                   const _T& bh, const _T& bl);

            static
            void
            add123cond(_T& rh, _T& rm, _T& rl,
                       const _T& a,
                       const _T& bh, const _T& bl);

            static
            void
            add213(_T& rh, _T& rm, _T& rl,
                   const _T& ah, const _T& al,
                   const _T& b);

            static
            void
            add213cond(_T& rh, _T& rm, _T& rl,
                       const _T& ah, const _T& al,
                       const _T& b);

            static
            void
            add23(_T& rh, _T& rm, _T& rl,
                  const _T& ah, const _T& al,
                  const _T& bh, const _T& bl);

            static
            void
            add23cond(_T& rh, _T& rm, _T& rl,
                      const _T& ah, const _T& al,
                      const _T& bh, const _T& bl);

            static
            void
            add33(_T& rh, _T& rm, _T& rl,
                  const _T& ah, const _T& am, const _T& al,
                  const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add33cond(_T& rh, _T& rm, _T& rl,
                      const _T& ah, const _T& am, const _T& al,
                      const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add233(_T& rh, _T& rm, _T& rl,
                  const _T& ah, const _T& al,
                  const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add233cond(_T& rh, _T& rm, _T& rl,
                       const _T& ah, const _T& al,
                       const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add133(_T& rh, _T& rm, _T& rl,
                   const _T& a,
                   const _T& bh, const _T& bm, const _T& bl);

            static
            void
            add133cond(_T& rh, _T& rm, _T& rl,
                       const _T& a,
                       const _T& bh, const _T& bm, const _T& bl);

            static
            void
            recp3(_T& rh, _T& rm, _T& rl,
                  const _T& dh, const _T& dm, const _T& dl);


            static
            t_real<_T>
            renormalize(const _T& rh, const _T& rm, const _T& rl);

            static
            t_real<_T>
            add(const _T& a,
                const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            add(const _T& ah, const _T& al,
                const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            add(const _T& ah, const _T& am, const _T& al,
                const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            mul(const _T& a,
                const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            mul(const _T& ah, const _T& al,
                const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            mul(const _T& ah, const _T& am, const _T& al,
                const _T& bh, const _T& bm, const _T& bl);

            static
            t_real<_T>
            recp(const _T& ah, const _T& am, const _T& al);

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
__attribute__((__always_inline__))
inline
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
mul133(_T& rh, _T& rm, _T& rl,
       const _T& a,
       const _T& bh, const _T& bm, const _T& bl)
{
    _T t2, t3, t4, t5, t7, t8, t9, t10;
    mul12(rh, t2, a, bh);
    mul12(t3, t4, a, bm);
    t5 = a * bl;
    add12cond(t9, t7, t2, t3);
    t8 = t4 + t5;
    t10 = t7 + t8;
    add12cond(rm, rl, t9, t10);
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
    add12cond(t14,t15,t1,t6);
    t16 = t7 + t15;
    t17 = t12 + t13;
    t18 = t16 + t17;
    add12cond(t19,t20,t14,t18) ;
    add22cond(t21,t22,t2,t3,t4,t5) ;
    add22cond(rm ,rl ,t21,t22,t19,t20) ;
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
recp3(_T& rh, _T& rm, _T& rl,
      const _T& dh, const _T& dm, const _T& dl)
{
    _T rec_r1, rec_t1, rec_t2, rec_t3, rec_t4, rec_t5, rec_t6;
    _T rec_t7, rec_t8, rec_t9, rec_t10, rec_t11, rec_t12, rec_t13;
    _T rec_t14,rec_r2h, rec_r2l, rec_t15, rec_t16, rec_t17;
    _T rec_t18, rec_t19, rec_t20, rec_t21, rec_t22, rec_t23;

    rec_r1 = _T(1.0) / dh;
    mul12(rec_t1,rec_t2,rec_r1, dh);
    rec_t3 = rec_t1 - _T(1.0);
    add12cond(rec_t4,rec_t5,rec_t3,rec_t2);
    mul12(rec_t6,rec_t7,rec_r1, dm);
    add12(rec_t8,rec_t9,-1.0,rec_t6);
    rec_t10 = rec_t9 + rec_t7;
    add12(rec_t11,rec_t12,rec_t8,rec_t10);
    rec_r1 = -rec_r1;
    add22cond(rec_t13,rec_t14,rec_t4,rec_t5,rec_t11,rec_t12);
    mul122(rec_r2h,rec_r2l,rec_r1,rec_t13,rec_t14);
    mul233(rec_t15,rec_t16,rec_t17,rec_r2h,rec_r2l, dh, dm, dl);
    renormalize3(rec_t18,rec_t19,rec_t20,rec_t15,rec_t16,rec_t17);
    rec_t18 = _T(-1.0);
    mul233(rec_t21,rec_t22,rec_t23,rec_r2h,rec_r2l,rec_t18,rec_t19,rec_t20);
    rec_t21 = -rec_t21;
    rec_t22 = -rec_t22;
    rec_t23 = -rec_t23;
    renormalize3(rh, rm, rl,rec_t21,rec_t22,rec_t23);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add123(_T& rh, _T& rm, _T& rl, const _T& a, const _T& bh, const _T& bl)
{
    _T t1;
    add12(rh, t1, a, bh);
    add12(rm, rl, t1, bl);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add123cond(_T& rh, _T& rm, _T& rl, const _T& a, const _T& bh, const _T& bl)
{
    _T t1;
    add12cond(rh, t1, a, bh);
    add12(rm, rl, t1, bl);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add213(_T& rh, _T& rm, _T& rl, const _T& ah, const _T& al, const _T& b)
{
    _T t1;
    add12(rh, t1, ah, b);
    add12cond(rm, rl, al, t1);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add213cond(_T& rh, _T& rm, _T& rl, const _T& ah, const _T& al, const _T& b)
{
    _T t1;
    add12cond(rh, t1, ah, b);
    add12cond(rm, rl, al, t1);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add23(_T& rh, _T& rm, _T& rl,
      const _T& ah, const _T& al,
      const _T& bh, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6;
    add12(rh, t1, ah, bh);
    add12cond(t2, t3, al, bl);
    add12cond(t4, t4, t1, t2);
    t6 = t3+t5;
    add12cond(rm, rl, t4, t6);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add23cond(_T& rh, _T& rm, _T& rl,
           const _T& ah, const _T& al,
           const _T& bh, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6;
    add12cond(rh, t1, ah, bh);
    add12cond(t2, t3, al, bl);
    add12cond(t4, t4, t1, t2);
    t6 = t3+t5;
    add12cond(rm, rl, t4, t6);
}

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add33(_T& rh, _T& rm, _T& rl,
      const _T& ah, const _T& am, const _T& al,
      const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7, t8;
    add12(rh, t1, ah, bh);
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
add233(_T& rh, _T& rm, _T& rl,
       const _T& ah, const _T& al,
       const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4, t5, t6, t7;
    add12(rh, t1, ah, bh);
    add12cond(t2, t3, al, bm);
    add12cond(t4, t5, t1, t2);
    t6 = t3 + bl;
    t7 = t6 + t5;
    add12cond(rm, rl, t4, t7);
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

template <typename _T>
void
cftal::impl::t_real_ops<_T>::
add133(_T& rh, _T& rm, _T& rl,
       const _T& a,
       const _T& bh, const _T& bm, const _T& bl)
{
    _T t1, t2, t3, t4;
    add12(rh, t1, a, bh);
    add12cond(t2, t3, t1, bm);
    t4 = t3+ bl;
    add12cond(rm, rl, t2, t4);
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
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
renormalize(const _T& ah, const _T& am, const _T& al)
{
    _T rh, rm, rl;
    renormalize3(rh, rm, rl,
                 ah, am, al);
    return t_real<_T>(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
add(const _T& a,
    const _T& bh, const _T& bm, const _T& bl)
{
    _T rh, rm, rl;
    add133cond(rh, rm, rl,
               a,
               bh, bm, bl);
    return renormalize(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
add(const _T& ah, const _T& al,
    const _T& bh, const _T& bm, const _T& bl)
{
    _T rh, rm, rl;
    add233cond(rh, rm, rl,
               ah, al,
               bh, bm, bl);
    return renormalize(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
add(const _T& ah, const _T& am, const _T& al,
    const _T& bh, const _T& bm, const _T& bl)
{
    _T rh, rm, rl;
    add33cond(rh, rm, rl,
              ah, am, al,
              bh, bm, bl);
    return renormalize(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
mul(const _T& a,
    const _T& bh, const _T& bm, const _T& bl)
{
    _T rh, rm, rl;
    mul133(rh, rm, rl,
           a,
           bh, bm, bl);
    return renormalize(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
mul(const _T& ah, const _T& al,
    const _T& bh, const _T& bm, const _T& bl)
{
    _T rh, rm, rl;
    mul233(rh, rm, rl,
           ah, al,
           bh, bm, bl);
    return renormalize(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
mul(const _T& ah, const _T& am, const _T& al,
    const _T& bh, const _T& bm, const _T& bl)
{
    _T rh, rm, rl;
    mul33(rh, rm, rl,
          ah, am, al,
          bh, bm, bl);
    return renormalize(rh, rm, rl);
}

template <typename _T>
cftal::t_real<_T>
cftal::impl::t_real_ops<_T>::
recp(const _T& ah, const _T& am, const _T& al)
{
    _T rh, rm, rl;
    recp3(rh, rm, rl, ah, am, al);
    return t_real<_T>(rh, rm, rl);
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
    return (a.h() == b.h()) & ((a.m() == b.m()) | (a.l() == b.l()));
}

template <typename _T>
inline
typename cftal::t_real_traits<_T>::cmp_result_type
cftal::operator!=(const t_real<_T>& a, const t_real<_T>& b)
{
    return (a.h() != b.h()) | ((a.m() != b.m()) | (a.l() != b.l()));
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
    return impl::t_real_ops<_T>::add(a,
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.l(),
                                     b.h(), b.m(), b.l());
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
    return impl::t_real_ops<_T>::add(b.h(), b.l(),
                                     a.h(), a.m(), a.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator+(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::add(b,
                                     a.h(), a.m(), a.l());
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
    return impl::t_real_ops<_T>::add(a,
                                     -b.h(), -b.m(), -b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::add(a.h(), a.l(),
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
    return impl::t_real_ops<_T>::add(-b(), -b.l(),
                                     a.h(), a.m(), a.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator-(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::add(-b,
                                     a.h(), a.m(), a.l());
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
    return impl::t_real_ops<_T>::mul(a,
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const d_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::mul(a.h(), a.l(),
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const t_real<_T>& a, const t_real<_T>& b)
{
    return impl::t_real_ops<_T>::mul(a.h(), a.m(), a.l(),
                                     b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const t_real<_T>& a, const d_real<_T>& b)
{
    return impl::t_real_ops<_T>::mul(b.h(), b.l(),
                                     a.h(), a.m(), a.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator*(const t_real<_T>& a, const _T& b)
{
    return impl::t_real_ops<_T>::mul(b,
                                     a.h(), a.m(), a.l());
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
    return a * impl::t_real_ops<_T>::recp(b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const d_real<_T>& a, const t_real<_T>& b)
{
    return a * impl::t_real_ops<_T>::recp(b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const t_real<_T>& a, const t_real<_T>& b)
{
    return a * impl::t_real_ops<_T>::recp(b.h(), b.m(), b.l());
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const t_real<_T>& a, const d_real<_T>& b)
{
    return a * impl::t_real_ops<_T>::recp(b.h(), b.l(), _T(0));
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::operator/(const t_real<_T>& a, const _T& b)
{
    return a * impl::t_real_ops<_T>::recp(b, _T(0), _T(0));
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

template <typename _T>
inline
cftal::t_real<_T>
cftal::select(const typename t_real_traits<_T>::cmp_result_type& m,
              const t_real<_T>& on_true,
              const t_real<_T>& on_false)
{
    using traits= t_real_traits<_T>;
    return t_real<_T>(traits::sel(m, on_true.h(), on_false.h()),
                      traits::sel(m, on_true.m(), on_false.m()),
                      traits::sel(m, on_true.l(), on_false.l()));
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::max(const t_real<_T>& a, const t_real<_T>& b)
{
    return select(a>b, a, b);
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::min(const t_real<_T>& a, const t_real<_T>& b)
{
    return select(a<b, a, b);
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::abs(const t_real<_T>& a)
{
    return select(a < t_real<_T>(0), -a, a);
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::sqr(const t_real<_T>& a)
{
    return a*a;
}

template <typename _T>
inline
cftal::t_real<_T>
cftal::mul_pwr2(const t_real<_T>& a, const _T& p)
{
    return t_real<_T>( a.h() * p, a.m() * p, a.l()*p);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_T_REAL_H__
