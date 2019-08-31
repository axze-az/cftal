//
// Copyright Axel Zeuner 2010-2019. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_IMPL_MASKS_H__)
#define __CFTAL_IMPL_MASKS_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>

namespace cftal {
    namespace impl {
        template <int _P0, int _P1, int _MSK>
        struct pos_msk_2 {
            enum {
                m =
                (((_P0 & _MSK)<<0) |
                    ((_P1 & _MSK)<<4))
            };
        };

        template <int _P0, int _P1>
        struct zero_msk_2 {
            enum {
                m =
                (((_P0 <0 ? 0 : 0xF) << 0)|
                    ((_P1 <0 ? 0 : 0xF) << 4))
            };
        };

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
