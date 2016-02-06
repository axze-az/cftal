#if !defined (__CFTAL_ARG_H__)
#define __CFTAL_ARG_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>


namespace cftal {

    template <typename _T>
    struct arg {
        using type = const _T&;
    };

    template <typename _T>
    using arg_t = typename arg<_T>::type;

    template <>
    struct arg<char> { using type= char; };

    template <>
    struct arg<wchar_t> { using type= wchar_t; };

    template <>
    struct arg<uint8_t> { using type= uint8_t; };

    template <>
    struct arg<int8_t> { using type= int8_t; };

    template <>
    struct arg<uint16_t> { using type= uint16_t; };

    template <>
    struct arg<int16_t> { using type= int16_t; };

    template <>
    struct arg<uint32_t> { using type= uint32_t; };

    template <>
    struct arg<int32_t> { using type= uint32_t; };

    template <>
    struct arg<uint64_t> { using type= uint64_t; };

    template <>
    struct arg<int64_t> { using type= uint64_t; };

    template <>
    struct arg<float> { using type= float; };

    template <>
    struct arg<double> { using type= double; };
    
}

// local variables:
// mode: c++
// end:
#endif
