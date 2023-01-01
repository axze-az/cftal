//
// Copyright (C) 2010-2023 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_TEST_UNIFORM_DISTRIBUTION_H__)
#define __CFTAL_TEST_UNIFORM_DISTRIBUTION_H__ 1

#include <cftal/config.h>
#include <cftal/constants.h>
#include <random>
#include <cftal/type_traits.h>

namespace cftal {
    namespace test {

        template <class _T>
        class uniform_real_distribution
            : public std::uniform_real_distribution<_T> {
            using base_type = std::uniform_real_distribution<_T>;

            using int_type = typename
                std::conditional<std::is_same<_T, double>::value,
                                 uint64_t,
                                 typename std::conditional<
                                    std::is_same<_T, float>::value,
                                    uint32_t, uint16_t>::type
                                 >::type;
            using bytesx = typename
                std::conditional<std::is_same<_T, double>::value,
                                 bytes8,
                                 typename std::conditional<
                                    std::is_same<_T, float>::value,
                                    bytes4, bytes2>::type
                                 >::type;

            std::uniform_int_distribution<int_type> _i_dist;
            _T _min;
            _T _max;
            _T _range;
            bool _use_int;

            static
            _T
            trunc_max_val(_T m) {
                const _T _max_val= std::sqrt(std::numeric_limits<_T>::max());
                return std::min(m, _max_val);
            }

            static
            _T
            trunc_min_val(_T m) {
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
                  _range(_max - _min),
                  _use_int((trunc_min_val(amin) != amin) ||
                           (trunc_max_val(amax) != amax)) {
            }

            // switch off fma to get the same random numbers
            // on machines with and without fma
            template <class _G>
#if defined (__x86_64__) || defined (__i386__)
            __attribute__((__target__("no-fma,no-fma4")))
#endif
            result_type
            operator()(_G& g) {
                _T r;
                if (_use_int) {
                    while (1) {
                        int_type i=_i_dist(g);
                        bytesx t(i);
                        r = make_fp(t);
                        using std::isnan;
                        if (isnan(r))
                            continue;
                        if (r>=_max)
                            continue;
                        if (r<_min)
                            continue;
                        break;
                    }
                } else {
                    _T t= _range;
                    _T rnd= std::generate_canonical<
                        _T, std::numeric_limits<_T>::digits, _G>(g);
                    t *= rnd;
                    r = t + _min;
                }
                return r;
            }
        };

        template <>
        class uniform_real_distribution<int32_t>
            : public std::uniform_int_distribution<int32_t> {
            using base_type=std::uniform_int_distribution<int32_t>;
            using base_type::base_type;
        };

    }
}

// local variables:
// mode: c++
// end:
#endif
