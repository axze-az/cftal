//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_BOOST_COMPAT_H__)
#define __CFTAL_BOOST_COMPAT_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <boost/numeric/odeint.hpp>

namespace boost {
    namespace numeric {
        namespace odeint {

            template <typename _T, std::size_t _N>
            struct vector_space_norm_inf<cftal::vec<_T, _N> > {
                using result_type = _T;
                result_type operator()(const cftal::vec<_T, _N>& v)         const {
                    cftal::vec<_T, _N> va= abs(v);
                    return cftal::max_element(va);
                }
            };
        }
    }
}


// local variables:
// mode: c++
// end:
#endif
