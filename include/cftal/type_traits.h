//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TYPE_TRAITS_H__)
#define __CFTAL_TYPE_TRAITS_H__ 1

#include <cftal/config.h>
#include <type_traits>

namespace cftal {
    
    // is_integral similiar to std::is_integral but we want
    // to add specializations
    template <typename _T>
    struct is_integral : public std::is_integral<_T> {};
    
    template< class T >
    inline constexpr bool 
    is_integral_v = is_integral<T>::value;

    // is_floating_point similiar to std::is_floating_point but we 
    // want to add specializations
    template <typename _T>
    struct is_floating_point : public std::is_floating_point<_T> {};

    template< class T >
    inline constexpr bool 
    is_floating_point_v = is_floating_point<T>::value;

    // is_signed similiar to std::is_signed but we want
    // to add specializations
    template <typename _T>
    struct is_signed : public std::is_signed<_T> {};
    
    template< class T >
    inline constexpr bool 
    is_signed_v = is_signed<T>::value;

    // is_unsigned similiar to std::is_unsigned but we want
    // to add specializations
    template <typename _T>
    struct is_unsigned : public std::is_unsigned<_T> {};
    
    template< class T >
    inline constexpr bool 
    is_unsigned_v = is_unsigned<T>::value;

    // make_signed similiar to std::make_signed but we want
    // to add specializations
    template <typename _T>
    struct make_signed : public std::make_signed<_T> {};
    
    template< class T >
    using make_signed_t = typename make_signed<T>::type;

    // make_unsigned similiar to std::make_unsigned but we want
    // to add specializations
    template <typename _T>
    struct make_unsigned : public std::make_unsigned<_T> {};

    template< class T >
    using make_unsigned_t = typename make_unsigned<T>::type;    
}

#endif
