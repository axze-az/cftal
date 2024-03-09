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
#if !defined (__CFTAL_MATH_F16_TABLES_H__)
#define __CFTAL_MATH_F16_TABLES_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/f16_t.h>

namespace cftal {
    namespace math {

        struct f16_sqrt_data {
            static constexpr const uint32_t zero_offset=0;
            alignas(64) static const uint16_t _tbl[32768+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_rsqrt_data {
            static constexpr const uint32_t zero_offset=0;
            alignas(64) static const uint16_t _tbl[32768+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_j0_data {
            static constexpr const uint32_t zero_offset=0;
            alignas(64) static const uint16_t _tbl[32768+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_j1_data {
            static constexpr const uint32_t zero_offset=0;
            alignas(64) static const uint16_t _tbl[32768+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_y0_data {
            static constexpr const uint32_t zero_offset=0;
            alignas(64) static const uint16_t _tbl[32768+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_y1_data {
            static constexpr const uint32_t zero_offset=0;
            alignas(64) static const uint16_t _tbl[32768+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_tgamma_data {
            static constexpr const uint32_t zero_offset=32768;
            alignas(64) static const uint16_t _tbl[65536+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

    }
}

#endif // __CFTAL_MATH_F16_TABLES_H__
