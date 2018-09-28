//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_FP_EXPANSION_H__)
#define __CFTAL_FP_EXPANSION_H__ 1

#include <cftal/config.h>
#include <initializer_list>
#include <iterator>
#include <iosfwd>

namespace cftal {

    // a floating point expansion
    template <typename _T, std::size_t _N>
    class fp_expansion {
        _T _e[_N];
    public:
        using value_type = _T;

        constexpr
        fp_expansion() = default;

        template <typename _E>
        constexpr
        fp_expansion(std::initializer_list<_E> l) : _e{} {
            const auto* p=std::begin(l);
            const std::size_t len=std::min(_N, l.size());
            for (std::size_t i=0; i<len; ++i, ++p)
                _e[i] = *p;
            for (std::size_t i=l.size(); i<_N; ++i)
                _e[i] = _T(0);
        }

        constexpr
        const _T& operator[](std::size_t i) const {
            return _e[i];
        }
        _T& operator[](std::size_t i) {
            return _e[i];
        }
    };

    template <typename _T, std::size_t _N>
    std::ostream&
    operator<<(std::ostream& s, const fp_expansion<_T, _N>& e) {
        for (std::size_t i=0; i<_N; ++i) {
            if (i)
                s << s.fill();
            s << e[i];
        }
        return s;
    }

    template <typename _T, std::size_t _N>
    auto
    operator<(const fp_expansion<_T, _N>& a,
              const fp_expansion<_T, _N>& b)
        ->decltype(_T{} < _T{});

    template <typename _T, std::size_t _N>
    auto
    operator<=(const fp_expansion<_T, _N>& a,
               const fp_expansion<_T, _N>& b)
        ->decltype(_T{}<=_T{});

    template <typename _T, std::size_t _N>
    auto
    operator==(const fp_expansion<_T, _N>& a,
               const fp_expansion<_T, _N>& b)
        ->decltype(_T{}==_T{});

    template <typename _T, std::size_t _N>
    auto
    operator!=(const fp_expansion<_T, _N>& a,
               const fp_expansion<_T, _N>& b)
        ->decltype(_T{}!=_T{});

    template <typename _T, std::size_t _N>
    auto
    operator>=(const fp_expansion<_T, _N>& a,
               const fp_expansion<_T, _N>& b)
        ->decltype(_T{}>=_T{});

    template <typename _T, std::size_t _N>
    auto
    operator>(const fp_expansion<_T, _N>& a,
              const fp_expansion<_T, _N>& b)
        ->decltype(_T{}>_T{});

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 2>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 3>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 4>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 5>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 6>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 7>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(fp_expansion<_T, 8>& r, _CMP cp);

    template <typename _T, typename _CMP>
    void
    exchange(_T& cp_true, _T& cp_false, _CMP cp);

    template <typename _T>
    struct less_than_mag {
        auto
        operator()(const _T& a, const _T& b) const {
            using std::abs;
            return abs(a) < abs(b);
        }
    };

    template <typename _T>
    struct greater_than_mag {
        auto
        operator()(const _T& a, const _T& b) const {
            using std::abs;
            return abs(a) > abs(b);
        }
    };

    // returns mininum and maximum magnitude
    template <typename _T>
    void
    min_max_mag(_T& vmin_mag, _T& vmax_mag, const _T& va, const _T& vb);

    // sort lanes according to cmp
    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1,
               _CMP cmp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1, _T& r2,
               _CMP cmp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
               _CMP cmp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
               _T& r4,
               _CMP cmp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
               _T& r4, _T& r5,
               _CMP cmp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
               _T& r4, _T& r5, _T& r6,
               _CMP cmp);

    template <typename _T, typename _CMP>
    void
    sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
               _T& r4, _T& r5, _T& r6, _T& r7,
               _CMP cmp);
}

template <typename _T, std::size_t _N>
inline
auto
cftal::
operator<(const fp_expansion<_T, _N>& a, const fp_expansion<_T, _N>& b)
    ->decltype(_T{}<_T{})
{
    auto r= a[0]<b[0];
    auto all_aibi_eq= a[0] == b[0];
    for (std::size_t i=1; i<_N-1; ++i) {
        auto ci= a[i] < b[i];
        auto ri= all_aibi_eq & ci;
        r |= ri;
        auto ei= a[i] == b[i];
        all_aibi_eq &= ei;
    }
    auto ci= a[_N-1] < b[_N-1];
    r |= (all_aibi_eq & ci);
    return r;
}

template <typename _T, std::size_t _N>
inline
auto
cftal::
operator<=(const fp_expansion<_T, _N>& a, const fp_expansion<_T, _N>& b)
    ->decltype(_T{}<=_T{})
{
    auto r= a[0]<b[0];
    auto all_aibi_eq= a[0] == b[0];
    for (std::size_t i=1; i<_N; ++i) {
        auto ci= a[i] <= b[i];
        auto ri= all_aibi_eq & ci;
        r |= ri;
        auto ei= a[i] == b[i];
        all_aibi_eq &= ei;
     }
    auto ci= a[_N-1] <= b[_N-1];
    r |= (all_aibi_eq & ci);
    return r;
}

template <typename _T, std::size_t _N>
inline
auto
cftal::
operator==(const fp_expansion<_T, _N>& a, const fp_expansion<_T, _N>& b)
    ->decltype(_T{}==_T{})
{
    auto r= a[0]==b[0];
    for (std::size_t i=1; i<_N; ++i) {
        auto ci= a[i] == b[i];
        r &= ci;
    }
    return r;
}

template <typename _T, std::size_t _N>
inline
auto
cftal::
operator!=(const fp_expansion<_T, _N>& a, const fp_expansion<_T, _N>& b)
    ->decltype(_T{}!=_T{})
{
    auto r= a[0]!=b[0];
    for (std::size_t i=1; i<_N; ++i) {
        auto ci= a[i] != b[i];
        r |= ci;
    }
    return r;
}

template <typename _T, std::size_t _N>
inline
auto
cftal::
operator>=(const fp_expansion<_T, _N>& a, const fp_expansion<_T, _N>& b)
    ->decltype(_T{}>=_T{})
{
    auto r= a[0]>b[0];
    auto all_aibi_eq= a[0] == b[0];
    for (std::size_t i=1; i<_N-1; ++i) {
        auto ci= a[i] > b[i];
        auto ri= all_aibi_eq & ci;
        r |= ri;
        auto ei= a[i] == b[i];
        all_aibi_eq &= ei;
     }
    auto ci= a[_N-1] > b[_N-1];
    auto ri= all_aibi_eq & ci;
    r |= ri;
    return r;
}

template <typename _T, std::size_t _N>
inline
auto
cftal::
operator>(const fp_expansion<_T, _N>& a, const fp_expansion<_T, _N>& b)
    ->decltype(_T{}>_T{})
{
    auto r= a[0]>b[0];
    auto all_aibi_eq= a[0] == b[0];
    for (std::size_t i=1; i<_N-1; ++i) {
        auto ci= a[i] > b[i];
        auto ri= all_aibi_eq & ci;
        r |= ri;
        auto ei= a[i] == b[i];
        all_aibi_eq &= ei;
    }
    auto ci= a[_N-1] > b[_N-1];
    auto ri= all_aibi_eq & ci;
    r |= ri;
    return r;
}


template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 2>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 3>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], r[2], cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 4>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], r[2], r[3], cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 5>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], r[2], r[3], r[4], cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 6>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], r[2], r[3], r[4], r[5], cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 7>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], r[2], r[3], r[4], r[5], r[6], cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(fp_expansion<_T, 8>& r, _CMP cmp)
{
    sort_lanes(r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], cmp);
}


template <typename _T, typename _CMP>
inline
void
cftal::exchange(_T& cp_true, _T& cp_false, _CMP cp)
{
    _T s0=cp_true, s1=cp_false;
    auto cmp_res=cp(s0, s1);
    cp_true = select(cmp_res, s0, s1);
    cp_false = select(cmp_res, s1, s0);
}

template <typename _T>
inline
void
cftal::min_max_mag(_T& vmin_mag, _T& vmax_mag, const _T& va, const _T& vb)
{
    vmin_mag=va;
    vmax_mag=vb;
    exchange(vmin_mag, vmax_mag, less_than_mag<_T>());
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(_T& r0, _T& r1, _CMP cmp)
{
    exchange(r0, r1, cmp);
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::
sort_lanes(_T& r0, _T& r1, _T& r2,
           _CMP cmp)
{
    _T t0=r0, t1=r1, t2=r2;

    exchange(t0, t2, cmp);

    exchange(t0, t1, cmp);

    exchange(t1, t2, cmp);

    r0 = t0;
    r1 = t1;
    r2 = t2;
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
                  _CMP cmp)
{
    _T t0=r0, t1=r1, t2=r2, t3=r3;

    exchange(t0, t2, cmp);
    exchange(t1, t3, cmp);

    exchange(t0, t1, cmp);
    exchange(t2, t3, cmp);

    exchange(t1, t2, cmp);

    r0 = t0;
    r1 = t1;
    r2 = t2;
    r3 = t3;
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
                  _T& r4,
                  _CMP cmp)
{
    _T t0=r0, t1=r1, t2=r2, t3=r3, t4=r4;

    exchange(t0, t4, cmp);
    exchange(t1, t3, cmp);

    exchange(t0, t2, cmp);

    exchange(t2, t4, cmp);
    exchange(t0, t1, cmp);

    exchange(t2, t3, cmp);
    exchange(t1, t4, cmp);

    exchange(t1, t2, cmp);
    exchange(t3, t4, cmp);

    r0 = t0;
    r1 = t1;
    r2 = t2;
    r3 = t3;
    r4 = t4;
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
                  _T& r4, _T& r5,
                  _CMP cmp)
{
    _T t0=r0, t1=r1, t2=r2, t3=r3, t4=r4, t5=r5;

    exchange(t0, t4, cmp);
    exchange(t1, t5, cmp);

    exchange(t0, t2, cmp);
    exchange(t1, t3, cmp);

    exchange(t2, t4, cmp);
    exchange(t3, t5, cmp);
    exchange(t0, t1, cmp);

    exchange(t2, t3, cmp);
    exchange(t4, t5, cmp);

    exchange(t1, t4, cmp);

    exchange(t1, t2, cmp);
    exchange(t3, t4, cmp);

    r0 = t0;
    r1 = t1;
    r2 = t2;
    r3 = t3;
    r4 = t4;
    r5 = t5;
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
                  _T& r4, _T& r5, _T& r6,
                  _CMP cmp)
{
    _T t0=r0, t1=r1, t2=r2, t3=r3, t4=r4, t5=r5, t6=r6;

    exchange(t0, t4, cmp);
    exchange(t1, t5, cmp);
    exchange(t2, t6, cmp);

    exchange(t0, t2, cmp);
    exchange(t1, t3, cmp);
    exchange(t4, t6, cmp);

    exchange(t2, t4, cmp);
    exchange(t3, t5, cmp);
    exchange(t0, t1, cmp);

    exchange(t2, t3, cmp);
    exchange(t4, t5, cmp);

    exchange(t1, t4, cmp);
    exchange(t3, t6, cmp);

    exchange(t1, t2, cmp);
    exchange(t3, t4, cmp);
    exchange(t5, t6, cmp);

    r0 = t0;
    r1 = t1;
    r2 = t2;
    r3 = t3;
    r4 = t4;
    r5 = t5;
    r6 = t6;
}

template <typename _T, typename _CMP>
__attribute__((__always_inline__))
inline
void
cftal::sort_lanes(_T& r0, _T& r1, _T& r2, _T& r3,
                  _T& r4, _T& r5, _T& r6, _T& r7,
                  _CMP cmp)
{
    _T t0=r0, t1=r1, t2=r2, t3=r3, t4=r4, t5=r5, t6=r6, t7=r7;

    exchange(t0, t4, cmp);
    exchange(t1, t5, cmp);
    exchange(t2, t6, cmp);
    exchange(t3, t7, cmp);

    exchange(t0, t2, cmp);
    exchange(t1, t3, cmp);
    exchange(t4, t6, cmp);
    exchange(t5, t7, cmp);

    exchange(t2, t4, cmp);
    exchange(t3, t5, cmp);
    exchange(t0, t1, cmp);
    exchange(t6, t7, cmp);

    exchange(t2, t3, cmp);
    exchange(t4, t5, cmp);

    exchange(t1, t4, cmp);
    exchange(t3, t6, cmp);

    exchange(t1, t2, cmp);
    exchange(t3, t4, cmp);
    exchange(t5, t6, cmp);

    r0 = t0;
    r1 = t1;
    r2 = t2;
    r3 = t3;
    r4 = t4;
    r5 = t5;
    r6 = t6;
    r7 = t7;
}

// Local variables:
// mode: c++
// end:
#endif
