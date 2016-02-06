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
}

// local variables:
// mode: c++
// end:
#endif
