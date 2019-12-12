//
// Copyright Axel Zeuner 2010-2019. Use, modification and
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

        constexpr
        fp_expansion(const _T& h);

        template <typename _E>
        constexpr
        fp_expansion(std::initializer_list<_E> l);

        template <std::size_t _M>
        constexpr
        explicit
        fp_expansion(const fp_expansion<_T, _M>& r);

        template <std::size_t _M>
        fp_expansion& operator=(const fp_expansion<_T, _M>& r);

        constexpr
        const _T& operator[](std::size_t i) const;
        _T& operator[](std::size_t i);

        constexpr
        const _T* data() const;
        _T* data();
    };

    template <typename _T, std::size_t _N>
    std::ostream&
    operator<<(std::ostream& s, const fp_expansion<_T, _N>& e);

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

}

template <typename _T, std::size_t _N>
constexpr
cftal::fp_expansion<_T, _N>::
fp_expansion(const _T& r)
{
    _e[0]=r;
    for (std::size_t i=1; i<_N; ++i)
        _e[i] = _T(0);
}

template <typename _T, std::size_t _N>
template <typename _E>
constexpr
cftal::fp_expansion<_T, _N>::
fp_expansion(std::initializer_list<_E> l)
{
    const auto* p=std::begin(l);
    const std::size_t ll=l.size();
    const std::size_t len=_N < ll ? _N : ll;
#pragma GCC unroll 8
    for (std::size_t i=0; i<len; ++i)
        _e[i] = p[i];
#pragma GCC unroll 8
    for (std::size_t i=len; i<_N; ++i)
        _e[i] = _T(0);
}

template <typename _T, std::size_t _N>
template <std::size_t _M>
constexpr
cftal::fp_expansion<_T, _N>::
fp_expansion(const fp_expansion<_T, _M>& r)
{
    const std::size_t len=_N < _M ? _N : _M;
#pragma GCC unroll 8
    for (std::size_t i=0; i<len; ++i)
        _e[i] = r[i];
#pragma GCC unroll 8
    for (std::size_t i=len; i<_N; ++i)
        _e[i] = _T(0);
}

template <typename _T, std::size_t _N>
template <std::size_t _M>
cftal::fp_expansion<_T, _N>&
cftal::fp_expansion<_T, _N>::
operator=(const fp_expansion<_T, _M>& r)
{
    const std::size_t len=_N < _M ? _N : _M;
#pragma GCC unroll 8
    for (std::size_t i=0; i<len; ++i)
        _e[i] = r[i];
#pragma GCC unroll 8
    for (std::size_t i=len; i<_N; ++i)
        _e[i] = _T(0);
    return *this;
}

template <typename _T, std::size_t _N>
inline
constexpr
const _T&
cftal::fp_expansion<_T, _N>::
operator[](std::size_t i) const
{
    return _e[i];
}

template <typename _T, std::size_t _N>
inline
_T&
cftal::fp_expansion<_T, _N>::
operator[](std::size_t i)
{
    return _e[i];
}

template <typename _T, std::size_t _N>
inline
constexpr
const _T*
cftal::fp_expansion<_T, _N>::
data() const
{
    return _e;
}

template <typename _T, std::size_t _N>
inline
_T*
cftal::fp_expansion<_T, _N>::
data()
{
    return _e;
}

template <typename _T, std::size_t _N>
std::ostream&
cftal::operator<<(std::ostream& s, const fp_expansion<_T, _N>& e)
{
    for (std::size_t i=0; i<_N; ++i) {
        if (i)
            s << s.fill();
        s << e[i];
    }
    return s;
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



// Local variables:
// mode: c++
// end:
#endif
