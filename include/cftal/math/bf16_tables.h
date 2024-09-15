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
#if !defined (__CFTAL_MATH_BF16_TABLES_H__)
#define __CFTAL_MATH_BF16_TABLES_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/bf16_t.h>

namespace cftal {
    namespace math {

        struct bf16_j0_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=32641;
            alignas(64) static const uint16_t _tbl[32641+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_j1_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=32641;
            alignas(64) static const uint16_t _tbl[32641+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_y0_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=32641;
            alignas(64) static const uint16_t _tbl[32641+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_y1_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=32641;
            alignas(64) static const uint16_t _tbl[32641+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_tgamma_data {
            static constexpr const uint32_t zero_offset=16713;
            static constexpr const int16_t min_offset=-16713;
            static constexpr const int32_t max_offset=16910;
            alignas(64) static const uint16_t _tbl[33623+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_lgamma_data {
            static constexpr const uint32_t zero_offset=17537;
            static constexpr const int16_t min_offset=-17537;
            static constexpr const int32_t max_offset=31814;
            alignas(64) static const uint32_t _tbl[49351];

            static const int32_t* tbl() {
                return reinterpret_cast<const int32_t*>(_tbl);
            }

            static const int32_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_erfc_data {
            static constexpr const uint32_t zero_offset=16662;
            static constexpr const int16_t min_offset=-16662;
            static constexpr const int32_t max_offset=16661;
            alignas(64) static const uint16_t _tbl[33323+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

        struct bf16_erf_data {
            static constexpr const uint32_t zero_offset=0;
            static constexpr const int16_t min_offset=0;
            static constexpr const int32_t max_offset=16398;
            alignas(64) static const uint16_t _tbl[16398+2];

            static const bf16_t* tbl() {
                return reinterpret_cast<const bf16_t*>(_tbl);
            }

            static const bf16_t* tbl_zero() {
                return tbl() + zero_offset;
            }
        };

    }
}

#endif // __CFTAL_MATH_BF16_TABLES_H__
