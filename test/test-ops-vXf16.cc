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
#include "cftal/vec.h"
#include "cftal/vec_f16.h"
#include "cftal/test/of_ops.h"
#include "cftal/test/cpu_times.h"

#if !defined (__AVX512F__) || (__CFTAL_CFG_ENABLE_AVX512__==0)

namespace cftal {
    namespace test {
        template <>
        class uniform_real_distribution<f16_t> {

            using int_type = uint16_t;
            using bytesx = bytes2;

            std::uniform_int_distribution<int_type> _i_dist;
            f16_t _min;
            f16_t _max;
            f16_t _range;
            f16_t _f16_min;
            f16_t _f16_max;
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
                  _f16_min(_min), _f16_max(_max),
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
                    f16_t rnd= std::generate_canonical<
                        f16_t, std::numeric_limits<f16_t>::digits, _G>(g);
                    t *= rnd;
                    r = t + _f16_min;
                }
                return r;
            }
        };
    }
}

int main()
{
    cftal::test::cpu_times_to_stdout tt;
    std::cout << "testing vXf16" << std::endl;
    using cftal::f16_t;
    bool rc=cftal::test::of_ops_up_to<f16_t, 16>::v();
    if (rc==false)
        std::cerr << "f16_t test failed" << std::endl;
    return rc==true ? 0 : 1;
}

#else

int main()
{
    std::cout << "not testing vXf16 (missing implementation)" << std::endl;
    return 0;
}

#endif

