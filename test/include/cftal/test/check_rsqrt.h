//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined(__CFTAL_TEST_CHECK_RSQRT_H__)
#define __CFTAL_TEST_CHECK_RSQRT_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/test/call_mpfr.h>
#include <cftal/test/func_domain_common.h>
#include <cmath>

namespace cftal {
    namespace test {

        template <typename _T>
        using domain_rsqrt = domain_positive_x_axis<_T>;

        template <typename _T>
        struct check_rsqrt {
            template <std::size_t _N>
            static
            vec<_T, _N>
            v(const vec<_T, _N>& a) {
                return rsqrt(a);
                // return rootn(a, vec<int32_t, _N>(-2));
            }
            static
            std::tuple<_T, _T, _T>
            r(const _T& a) {
                std::pair<_T, _T> i;
                _T v=call_mpfr::func(a, mpfr_rec_sqrt, &i);
                return std::make_tuple(v, i.first, i.second);
            }

#if 0	    
	    static
	    float
	    _s(const float& a) {
		return ::rsqrtf(a);
	    }

	    static
	    double
	    _s(const double& a) {
		return ::rsqrt(a);
	    }
#endif	    

	    template <typename _T1>
	    static
	    _T1
	    _s(const _T1& a) {
                if (a==std::numeric_limits<_T1>::infinity()) {
                    return _T1(0.0);
                }
                if (a==_T1(0.0)) {
                    return std::numeric_limits<_T1>::infinity();
                }
                using std::sqrt;
                return _T1(1.0)/sqrt(a);
	    }    

            static
            bf16_t
            _s(const bf16_t& a) {
                return static_cast<bf16_t>(_s<float>(static_cast<float>(a)));
            }

            static
            f16_t
            _s(const f16_t& a) {
                return static_cast<f16_t>(_s<float>(static_cast<float>(a)));
            }    
	    
            static
            _T
            s(const _T& a) {
		return _s(a);
            }
	    
            static
            const char* fname() { return "rsqrt"; }
        };

    }
}

// local variables:
// mode: c++
// end:

#endif
