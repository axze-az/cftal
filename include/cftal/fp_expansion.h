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
        fp_expansion(std::initializer_list<_E> l) {
            const auto* p=std::begin(l);
            const std::size_t ll=l.size();
            const std::size_t len=_N < ll ? _N : ll;
            for (std::size_t i=0; i<len; ++i)
                _e[i] = p[i];
            for (std::size_t i=len; i<_N; ++i)
                _e[i] = _T(0);
        }

        template <std::size_t _M>
        constexpr
        explicit
        fp_expansion(const fp_expansion<_T, _M>& r) {
            const std::size_t len=_N < _M ? _N : _M;
            for (std::size_t i=0; i<len; ++i)
                _e[i] = r[i];
            for (std::size_t i=len; i<_N; ++i)
                _e[i] = _T(0);
        }

        template <std::size_t _N0, std::size_t _N1>
        constexpr
        fp_expansion(const fp_expansion<_T, _N0>& r0,
                     const fp_expansion<_T, _N1>& r1) {
            static_assert(_N == _N0 + _N1, "ooops");
            for (std::size_t i=0; i<_N0; ++i)
                _e[i] = r0[i];
            for (std::size_t i=0; i<_N1; ++i)
                _e[_N0+i] = r1[+i];
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
