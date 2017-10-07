//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_TEST_UNIFORM_DISTRIBUTION_H__)
#define __CFTAL_TEST_UNIFORM_DISTRIBUTION_H__ 1

#include <cftal/config.h>
#include <cftal/constants.h>
#include <random>
#include <type_traits>

namespace cftal {
    namespace test {

        template <class _T>
        class uniform_real_distribution
            : public std::uniform_real_distribution<_T> {
            using base_type = std::uniform_real_distribution<_T>;

            using int_type = typename
                std::conditional<std::is_same<_T, double>::value,
                                 uint64_t,
                                 uint32_t>::type;
            using bytesx = typename
                std::conditional<std::is_same<_T, double>::value,
                                 bytes8,
                                 bytes4>::type;

            std::uniform_int_distribution<int_type> _i_dist;
            _T _min;
            _T _max;
            bool _use_int;

            _T trunc_max_val(_T m) {
                const _T _max_val= std::sqrt(std::numeric_limits<_T>::max());
                return std::min(m, _max_val);
            }

            _T trunc_min_val(_T m) {
                const _T _min_val= -std::sqrt(std::numeric_limits<_T>::max());
                return std::max(m, _min_val);
            }

            static
            double
            make_fp(const bytes8& b) { return b.f64(); }

            static
            float
            make_fp(const bytes4& b) { return b.f32(); }

        public:
            using result_type = typename base_type::result_type;
            uniform_real_distribution(_T amin, _T amax)
                : base_type(trunc_min_val(amin), trunc_max_val(amax)),
                  _i_dist(),
                  _min(amin), _max(amax),
                  _use_int(1 /*(trunc_min_val(amin) != amin) ||
                           (trunc_max_val(amax) != amax)*/) {
            }

            template <class _G>
            result_type
            operator()(_G& g) {
                _T r;
                if (_use_int) {
                    while (1) {
                        int_type i=_i_dist(g);
                        bytesx t(i);
                        r = make_fp(t);
                        if (std::isnan(r))
                            continue;
                        if (r>=_max)
                            continue;
                        if (r<_min)
                            continue;
                        break;
                    }
                } else {
                    r = base_type::operator()(g);
                }
                return r;
            }
        };
    }
}

// local variables:
// mode: c++
// end:
#endif
