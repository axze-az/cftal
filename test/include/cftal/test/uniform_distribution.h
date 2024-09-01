//
// Copyright (C) 2010-2024 Axel Zeuner
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
#include <cftal/f16_t.h>
#include <cftal/bf16_t.h>

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

        template <>
        class uniform_real_distribution<int16_t>
            : public std::uniform_int_distribution<int16_t> {
            using base_type=std::uniform_int_distribution<int16_t>;
            using base_type::base_type;
        };

        template <>
        class uniform_real_distribution<f16_t> {

            using int_type = uint16_t;
            using bytesx = bytes2;

            std::uniform_int_distribution<int_type> _i_dist;
            f16_t _min;
            f16_t _max;
            f16_t _range;
            f16_t _f16_min;
            // f16_t _f16_max;
            f16_t _f16_range;
            bool _use_int;

            static
            f16_t
            trunc_max_val(const f16_t m) {
                using std::sqrt;
                const f16_t _max_val= sqrt(std::numeric_limits<f16_t>::max());
                using std::min;
                return min(m, _max_val);
            }

            static
            f16_t
            trunc_min_val(f16_t m) {
                using std::sqrt;
                const f16_t _min_val= -sqrt(std::numeric_limits<f16_t>::max());
                using std::max;
                return max(m, _min_val);
            }

            static
            f16_t
            make_fp(const bytes2& b) { return b.u16(); }

        public:
            using result_type = f16_t;
            uniform_real_distribution(const f16_t& amin, const f16_t& amax)
                 : _i_dist(),
                  _min(amin), _max(amax),
                  _range(_max - _min),
                  _f16_min(_min), // _f16_max(_max),
                  _f16_range(_range),
                  _use_int((trunc_min_val(amin) != amin) ||
                           (trunc_max_val(amax) != amax))
            {
            }
            // switch off fma to get the same random numbers
            // on machines with and without fma
            template <class _G>
#if defined (__x86_64__) || defined (__i386__)
            __attribute__((__target__("no-fma,no-fma4")))
#endif
            result_type
            operator()(_G& g) {
                f16_t r;
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
                    f16_t t=_f16_range;
                    f16_t rnd= static_cast<f16_t>(std::generate_canonical<
                        float, std::numeric_limits<f16_t>::digits, _G>(g));
                    t *= rnd;
                    r = t + _f16_min;
                }
                return r;
            }
        };


        template <>
        class uniform_real_distribution<bf16_t> {

            using int_type = uint16_t;
            using bytesx = bytes2;

            std::uniform_int_distribution<int_type> _i_dist;
            bf16_t _min;
            bf16_t _max;
            bf16_t _range;
            bf16_t _f16_min;
            // bf16_t _f16_max;
            bf16_t _f16_range;
            bool _use_int;

            static
            bf16_t
            trunc_max_val(const bf16_t m) {
                using std::sqrt;
                const bf16_t _max_val= sqrt(std::numeric_limits<bf16_t>::max());
                using std::min;
                return min(m, _max_val);
            }

            static
            bf16_t
            trunc_min_val(bf16_t m) {
                using std::sqrt;
                const bf16_t _min_val= -sqrt(std::numeric_limits<bf16_t>::max());
                using std::max;
                return max(m, _min_val);
            }

            static
            bf16_t
            make_fp(const bytes2& b) { return b.u16(); }

        public:
            using result_type = bf16_t;
            uniform_real_distribution(const bf16_t& amin, const bf16_t& amax)
                 : _i_dist(),
                  _min(amin), _max(amax),
                  _range(_max - _min),
                  _f16_min(_min), // _f16_max(_max),
                  _f16_range(_range),
                  _use_int((trunc_min_val(amin) != amin) ||
                           (trunc_max_val(amax) != amax))
            {
            }
            // switch off fma to get the same random numbers
            // on machines with and without fma
            template <class _G>
#if defined (__x86_64__) || defined (__i386__)
            __attribute__((__target__("no-fma,no-fma4")))
#endif
            result_type
            operator()(_G& g) {
                bf16_t r;
                if (_use_int) {
                    while (1) {
                        int_type i=_i_dist(g);
                        bytesx t(i);
                        r = make_fp(t);
#if __CFTAL_CFG_FLUSH_BFLOAT16_TO_ZERO>0
                        // do not produce subnormal outputs
                        uint16_t ui=i & 0x7fff;
                        if (ui > 0 && ui < 0x0080)
                            continue;
#endif
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
                    bf16_t t=_f16_range;
                    bf16_t rnd= static_cast<bf16_t>(std::generate_canonical<
                        float, std::numeric_limits<bf16_t>::digits, _G>(g));
                    t *= rnd;
                    r = t + _f16_min;
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
