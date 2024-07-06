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

        struct f16_j0_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=31745;
            alignas(64) static const uint16_t _tbl[31745+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_j1_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=31745;
            alignas(64) static const uint16_t _tbl[31745+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_y0_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=31745;
            alignas(64) static const uint16_t _tbl[31745+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_y1_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=31745;
            alignas(64) static const uint16_t _tbl[31745+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_tgamma_data {
            static constexpr const uint32_t zero_offset=19009;
            static constexpr const int16_t min_offset=-19009;
            static constexpr const int32_t max_offset=18590;
            alignas(64) static const uint16_t _tbl[37599+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_lgamma_data {
            static constexpr const uint32_t zero_offset=25602;
            static constexpr const int16_t min_offset=-25602;
            static constexpr const int32_t max_offset=28671;
            alignas(64) static const uint32_t _tbl[54273];

            static const int32_t* tbl() {
                return reinterpret_cast<const int32_t*>(_tbl);
            }

            static const int32_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_erfc_data {
            static constexpr const uint32_t zero_offset=17369;
            static constexpr const int16_t min_offset=-17369;
            static constexpr const int32_t max_offset=17368;
            alignas(64) static const uint16_t _tbl[34737+2];

            static const f16_t* tbl() {
                return reinterpret_cast<const f16_t*>(_tbl);
            }

            static const f16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct f16_erf_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=16690;
            alignas(64) static const uint16_t _tbl[16690+2];

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
