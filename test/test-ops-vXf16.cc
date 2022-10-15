//
// Copyright (C) 2010-2022 Axel Zeuner
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
#include "cftal/vxf16.h"
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
            float _f32_min;
            float _f32_max;
            float _f32_range;
            bool _use_int;

            static
            f16_t
            trunc_max_val(const f16_t m) {
                const f16_t _max_val= sqrt(std::numeric_limits<f16_t>::max());
                using std::min;
                return min(m, _max_val);
            }

            static
            f16_t
            trunc_min_val(f16_t m) {
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
                  _f32_min(_min), _f32_max(_max),
                  _f32_range(_range),
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
                    float t=_f32_range;
                    float rnd= std::generate_canonical<
                        float, std::numeric_limits<f16_t>::digits, _G>(g);
                    t *= rnd;
                    r = t + _f32_min;
                }
                return r;
            }
        };

        template <>
        struct cmp_t<f16_t> {
            cmp_t() {}
            bool operator()(f16_t a, f16_t b) const {
                return f_eq(float(a), float(b));
            }
        };

    }

    template <std::size_t _N>
    bool
    check_cmp(const f16_t(&a)[_N], bool expected , const char* msg)
    {
        bool r=true;
        std::size_t i=0;
        const test::cmp_t<uint16_t> cmp;
        uint16_t expect= expected ? uint16_t(-1) : uint16_t(0);
        for (auto b=std::begin(a), e= std::end(a); b!=e; ++b, ++i) {
            const f16_t& ai= *b;
            uint16_t aii=as<uint16_t>(ai);
            if (cmp(aii, expect) == false) {
                std::cerr << msg << " element " << i
                        << " failed: " << ai << " expected: "
                        << expect << std::endl;
                r = false;
            }
        }
        return r;
    }


    inline
    f16_t do_div(f16_t u, f16_t v)
    {
        return u/v;
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

