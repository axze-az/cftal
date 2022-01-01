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
#if !defined (__CFTAL_IMPL_MASKS_H__)
#define __CFTAL_IMPL_MASKS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {
    namespace impl {
        
        // 4 bit position mask with 2 elements
        template <int _P0, int _P1, int _MSK>
        struct pos_msk_2 {
            enum {
                m =
                (((_P0 & _MSK)<<0) |
                    ((_P1 & _MSK)<<4))
            };
        };

        // 4 bit zero mask with 2 elements
        template <int _P0, int _P1>
        struct zero_msk_2 {
            enum {
                m =
                (((_P0 <0 ? 0 : 0xF) << 0)|
                    ((_P1 <0 ? 0 : 0xF) << 4))
            };
        };

        // 4 bit position mask with 4 elements
        template <int _P0, int _P1, int _P2, int _P3, int _MSK>
        struct pos_msk_4 {
            enum {
                m=
                (((_P0 & _MSK)<< 0) |
                    ((_P1 & _MSK)<< 4) |
                    ((_P2 & _MSK)<< 8) |
                    ((_P3 & _MSK)<<12))
            };
        };

        // 4 bit zero mask with 4 elements
        template <int _P0, int _P1, int _P2, int _P3>
        struct zero_msk_4 {
            enum {
                m =
                (((_P0 <0 ? 0 : 0xF) << 0) |
                    ((_P1 <0 ? 0 : 0xF) << 4) |
                    ((_P2 <0 ? 0 : 0xF) << 8) |
                    ((_P3 <0 ? 0 : 0xF) <<12))
            };
        };

        // 4 bit position mask with 8 elements
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7,
                  int _MSK>
        struct pos_msk_8 {
            enum {
                m =
                (((_P0 & _MSK)<< 0) |
                    ((_P1 & _MSK)<< 4) |
                    ((_P2 & _MSK)<< 8) |
                    ((_P3 & _MSK)<<12) |
                    ((_P4 & _MSK)<<16) |
                    ((_P5 & _MSK)<<20) |
                    ((_P6 & _MSK)<<24) |
                    ((_P7 & _MSK)<<28))
            };
        };

        // 4 bit zero mask with 8 elements
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct zero_msk_8 {
            enum {
                m =
                (((_P0 <0 ? 0 : 0xF) << 0) |
                    ((_P1 <0 ? 0 : 0xF) << 4) |
                    ((_P2 <0 ? 0 : 0xF) << 8) |
                    ((_P3 <0 ? 0 : 0xF) <<12) |
                    ((_P4 <0 ? 0 : 0xF) <<16) |
                    ((_P5 <0 ? 0 : 0xF) <<20) |
                    ((_P6 <0 ? 0 : 0xF) <<24) |
                    ((_P7 <0 ? 0 : 0xF) <<28))
            };
        };
    }
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_IMPL_MASKS_H__
