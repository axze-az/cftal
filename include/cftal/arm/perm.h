//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_ARM_PERM_H__)
#define __CFTAL_ARM_PERM_H__ 1

#include <cftal/config.h>
#include <cftal/arm/intrin.h>
#include <cftal/types.h>

namespace cftal {
    namespace arm {
        namespace impl {

            template <int _P0, int _P1, int _P2, int _P3,
                      int _P4, int _P5, int _P6, int _P7>
            struct perm1_v8u8 {
                static
                uint8x8_t v(uint8x8_t a);
            };

            template <int _P0, int _P1, int _P2, int _P3,
                      int _P4, int _P5, int _P6, int _P7>
            struct perm2_v8u8 {
                static
                uint8x8_t v(uint8x8_t a, uint8x8_t b);
            };

            template <int _P0, int _P1>
            struct perm1_v2u32 {
                static
                uint32x2_t v(uint32x2_t a);
            };

            template <int _P0, int _P1>
            struct perm2_v2u32 {
                static
                uint32x2_t v(uint32x2_t a, uint32x2_t b);
            };

            template <int _P0, int _P1, int _P2, int _P3,
                      int _P4, int _P5, int _P6, int _P7,
                      int _P8, int _P9, int _PA, int _PB,
                      int _PC, int _PD, int _PE, int _PF>
            struct perm1_v16u8 {
                static
                uint8x16_t v(uint8x16_t a);
            };

            template <int _P0, int _P1, int _P2, int _P3,
                      int _P4, int _P5, int _P6, int _P7,
                      int _P8, int _P9, int _PA, int _PB,
                      int _PC, int _PD, int _PE, int _PF>
            struct perm2_v16u8 {
                static
                uint8x16_t v(uint8x16_t a, uint8x16_t b);
            };

            template <int _P0, int _P1, int _P2, int _P3>
            struct perm1_v4u32 {
                static
                uint32x4_t v(uint32x4_t a);
            };

            template <int _P0, int _P1, int _P2, int _P3>
            struct perm2_v4u32 {
                static
                uint32x4_t v(uint32x4_t a, uint32x4_t b);
            };
            // TODO add specializations

            template <int _P0, int _P1>
            struct perm1_v2u64 {
                static
                uint64x2_t v(uint64x2_t a);
            };

            template <int _P0, int _P1>
            struct perm2_v2u64 {
                static
                uint64x2_t v(uint64x2_t a, uint64x2_t b);
            };

            // TODO add specializations

        }

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        uint8x8_t perm_v8u8(uint8x8_t a);

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        uint8x8_t perm_v8u8(uint8x8_t a, uint8x8_t b);

        template <int _P0, int _P1>
        uint32x2_t perm_v2u32(uint32x2_t a);
        template <int _P0, int _P1>
        uint32x2_t perm_v2u32(uint32x2_t a, uint32x2_t b);

        template <int _P0, int _P1>
        int32x2_t perm_v2s32(int32x2_t a);
        template <int _P0, int _P1>
        int32x2_t perm_v2s32(int32x2_t a, int32x2_t b);

        template <int _P0, int _P1>
        float32x2_t perm_v2f32(float32x2_t a);
        template <int _P0, int _P1>
        float32x2_t perm_v2f32(float32x2_t a, float32x2_t b);


        template <int _P0, int _P1>
        uint64x2_t perm_v2u64(uint64x2_t a);
        template <int _P0, int _P1>
        uint64x2_t perm_v2u64(uint64x2_t a, uint64x2_t b);

        template <int _P0, int _P1>
        int64x2_t perm_v2s64(int64x2_t a);
        template <int _P0, int _P1>
        int64x2_t perm_v2s64(int64x2_t a, int64x2_t b);

        template <int _P0, int _P1>
        float64x2_t perm_v2f64(float64x2_t a);
        template <int _P0, int _P1>
        float64x2_t perm_v2f64(float64x2_t a, float64x2_t b);

        inline
        int compress_mask_u32(uint32x2_t x);

        inline
        int compress_mask_u32(uint32x4_t x);

        inline
        int compress_mask_u64(uint64x2_t x);

        inline
        int read_signs_s32(int32x2_t x);

        inline
        int read_signs_s32(int32x4_t x);

        inline
        int read_signs_s64(int64x2_t x);

    }
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
uint8x8_t
cftal::arm::impl::
perm1_v8u8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(uint8x8_t a)
{
    const
    uint8x8_t dst{uint8_t(_P0), uint8_t(_P1), uint8_t(_P2), uint8_t(_P3),
                  uint8_t(_P4), uint8_t(_P5), uint8_t(_P6), uint8_t(_P7)};
    uint8x8_t r=vtbl1_u8(a, dst);
    return r;
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
uint8x8_t
cftal::arm::impl::
perm2_v8u8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(uint8x8_t a,
                                                      uint8x8_t b)
{
    const
    uint8x8_t dst{uint8_t(_P0), uint8_t(_P1), uint8_t(_P2), uint8_t(_P3),
                  uint8_t(_P4), uint8_t(_P5), uint8_t(_P6), uint8_t(_P7)};
    uint8x8x2_t ab{a, b};
    uint8x8_t r=vtbl2_u8(ab, dst);
    return r;
}

template <int _P0, int _P1>
inline
uint32x2_t
cftal::arm::impl::perm1_v2u32<_P0, _P1>::v(uint32x2_t a)
{
    const bool p0n = _P0 < 0;
    const bool p1n = _P1 < 0;
    const int u0= p0n ? -1 : (4*_P0) + 0;
    const int u1= p0n ? -1 : (4*_P0) + 1;
    const int u2= p0n ? -1 : (4*_P0) + 2;
    const int u3= p0n ? -1 : (4*_P0) + 3;
    const int u4= p1n ? -1 : (4*_P1) + 0;
    const int u5= p1n ? -1 : (4*_P1) + 1;
    const int u6= p1n ? -1 : (4*_P1) + 2;
    const int u7= p1n ? -1 : (4*_P1) + 3;
    uint8x8_t ai = vreinterpret_u8_u32(a);
    uint8x8_t ri=perm1_v8u8<u0, u1, u2, u3, u4, u5, u6, u7>::v(ai);
    return vreinterpret_u32_u8(ri);
}

template <int _P0, int _P1>
inline
uint32x2_t
cftal::arm::impl::perm2_v2u32<_P0, _P1>::v(uint32x2_t a, uint32x2_t b)
{
    const bool p0n = _P0 < 0;
    const bool p1n = _P1 < 0;
    const int u0= p0n ? -1 : (4*_P0) + 0;
    const int u1= p0n ? -1 : (4*_P0) + 1;
    const int u2= p0n ? -1 : (4*_P0) + 2;
    const int u3= p0n ? -1 : (4*_P0) + 3;
    const int u4= p1n ? -1 : (4*_P1) + 0;
    const int u5= p1n ? -1 : (4*_P1) + 1;
    const int u6= p1n ? -1 : (4*_P1) + 2;
    const int u7= p1n ? -1 : (4*_P1) + 3;
    uint8x8_t ai = vreinterpret_u8_u32(a);
    uint8x8_t bi = vreinterpret_u8_u32(b);
    uint8x8_t ri=perm2_v8u8<u0, u1, u2, u3, u4, u5, u6, u7>::v(ai, bi);
    return vreinterpret_u32_u8(ri);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7,
          int _P8, int _P9, int _PA, int _PB,
          int _PC, int _PD, int _PE, int _PF>
inline
uint8x16_t
cftal::arm::impl::
perm1_v16u8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7,
            _P8, _P9, _PA, _PB, _PC, _PD, _PE, _PF>::v(uint8x16_t a)
{
    uint8x16_t dst{uint8_t(_P0), uint8_t(_P1), uint8_t(_P2), uint8_t(_P3),
                   uint8_t(_P4), uint8_t(_P5), uint8_t(_P6), uint8_t(_P7),
                   uint8_t(_P8), uint8_t(_P9), uint8_t(_PA), uint8_t(_PB),
                   uint8_t(_PC), uint8_t(_PD), uint8_t(_PE), uint8_t(_PF)};
    uint8x16_t ri=vqtbl1q_u8(a, dst);
    return ri;
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7,
          int _P8, int _P9, int _PA, int _PB,
          int _PC, int _PD, int _PE, int _PF>
inline
uint8x16_t
cftal::arm::impl::
perm2_v16u8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7,
            _P8, _P9, _PA, _PB, _PC, _PD, _PE, _PF>::v(uint8x16_t a,
                                                       uint8x16_t b)
{
    uint8x16_t dst{uint8_t(_P0), uint8_t(_P1), uint8_t(_P2), uint8_t(_P3),
                   uint8_t(_P4), uint8_t(_P5), uint8_t(_P6), uint8_t(_P7),
                   uint8_t(_P8), uint8_t(_P9), uint8_t(_PA), uint8_t(_PB),
                   uint8_t(_PC), uint8_t(_PD), uint8_t(_PE), uint8_t(_PF)};
    uint8x16x2_t ab{a, b};
    uint8x16_t ri=vqtbl2q_u8(ab, dst);
    return ri;
}

template <int _P0, int _P1, int _P2, int _P3>
inline
uint32x4_t
cftal::arm::impl::perm1_v4u32<_P0, _P1, _P2, _P3>::v(uint32x4_t a)
{
    const bool p0n = _P0 < 0;
    const bool p1n = _P1 < 0;
    const bool p2n = _P2 < 0;
    const bool p3n = _P3 < 0;
    const int u0= p0n ? -1 : (4*_P0) + 0;
    const int u1= p0n ? -1 : (4*_P0) + 1;
    const int u2= p0n ? -1 : (4*_P0) + 2;
    const int u3= p0n ? -1 : (4*_P0) + 3;
    const int u4= p1n ? -1 : (4*_P1) + 0;
    const int u5= p1n ? -1 : (4*_P1) + 1;
    const int u6= p1n ? -1 : (4*_P1) + 2;
    const int u7= p1n ? -1 : (4*_P1) + 3;
    const int u8= p2n ? -1 : (4*_P2) + 0;
    const int u9= p2n ? -1 : (4*_P2) + 1;
    const int ua= p2n ? -1 : (4*_P2) + 2;
    const int ub= p2n ? -1 : (4*_P2) + 3;
    const int uc= p3n ? -1 : (4*_P3) + 0;
    const int ud= p3n ? -1 : (4*_P3) + 1;
    const int ue= p3n ? -1 : (4*_P3) + 2;
    const int uf= p3n ? -1 : (4*_P3) + 3;
    uint8x16_t ai = vreinterpretq_u8_u32(a);
    uint8x16_t ri=perm1_v16u8<u0, u1, u2, u3, u4, u5, u6, u7,
                              u8, u9, ua, ub, uc, ud, ue, uf>::v(ai);
    return vreinterpretq_u32_u8(ri);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
uint32x4_t
cftal::arm::impl::
perm2_v4u32<_P0, _P1, _P2, _P3>::v(uint32x4_t a, uint32x4_t b)
{
    const bool p0n = _P0 < 0;
    const bool p1n = _P1 < 0;
    const bool p2n = _P2 < 0;
    const bool p3n = _P3 < 0;
    const int u0= p0n ? -1 : (4*_P0) + 0;
    const int u1= p0n ? -1 : (4*_P0) + 1;
    const int u2= p0n ? -1 : (4*_P0) + 2;
    const int u3= p0n ? -1 : (4*_P0) + 3;
    const int u4= p1n ? -1 : (4*_P1) + 0;
    const int u5= p1n ? -1 : (4*_P1) + 1;
    const int u6= p1n ? -1 : (4*_P1) + 2;
    const int u7= p1n ? -1 : (4*_P1) + 3;
    const int u8= p2n ? -1 : (4*_P2) + 0;
    const int u9= p2n ? -1 : (4*_P2) + 1;
    const int ua= p2n ? -1 : (4*_P2) + 2;
    const int ub= p2n ? -1 : (4*_P2) + 3;
    const int uc= p3n ? -1 : (4*_P3) + 0;
    const int ud= p3n ? -1 : (4*_P3) + 1;
    const int ue= p3n ? -1 : (4*_P3) + 2;
    const int uf= p3n ? -1 : (4*_P3) + 3;
    uint8x16_t ai = vreinterpretq_u8_u32(a);
    uint8x16_t bi = vreinterpretq_u8_u32(b);
    uint8x16_t ri=perm2_v16u8<u0, u1, u2, u3, u4, u5, u6, u7,
                              u8, u9, ua, ub, uc, ud, ue, uf>::v(ai, bi);
    return vreinterpretq_u32_u8(ri);
}

template <int _P0, int _P1>
inline
uint64x2_t
cftal::arm::impl::perm1_v2u64<_P0, _P1>::v(uint64x2_t a)
{
    const bool p0n = _P0 < 0;
    const bool p1n = _P1 < 0;
    const int u0= p0n ? -1 : (8*_P0) + 0;
    const int u1= p0n ? -1 : (8*_P0) + 1;
    const int u2= p0n ? -1 : (8*_P0) + 2;
    const int u3= p0n ? -1 : (8*_P0) + 3;
    const int u4= p0n ? -1 : (8*_P0) + 4;
    const int u5= p0n ? -1 : (8*_P0) + 5;
    const int u6= p0n ? -1 : (8*_P0) + 6;
    const int u7= p0n ? -1 : (8*_P0) + 7;
    const int u8= p1n ? -1 : (8*_P1) + 0;
    const int u9= p1n ? -1 : (8*_P1) + 1;
    const int ua= p1n ? -1 : (8*_P1) + 2;
    const int ub= p1n ? -1 : (8*_P1) + 3;
    const int uc= p1n ? -1 : (8*_P1) + 4;
    const int ud= p1n ? -1 : (8*_P1) + 5;
    const int ue= p1n ? -1 : (8*_P1) + 6;
    const int uf= p1n ? -1 : (8*_P1) + 7;
    uint8x16_t ai = vreinterpretq_u8_u64(a);
    uint8x16_t ri=perm1_v16u8<u0, u1, u2, u3, u4, u5, u6, u7,
                              u8, u9, ua, ub, uc, ud, ue, uf>::v(ai);
    return vreinterpretq_u64_u8(ri);
}

template <int _P0, int _P1>
inline
uint64x2_t
cftal::arm::impl::
perm2_v2u64<_P0, _P1>::v(uint64x2_t a, uint64x2_t b)
{
    const bool p0n = _P0 < 0;
    const bool p1n = _P1 < 0;
    const int u0= p0n ? -1 : (8*_P0) + 0;
    const int u1= p0n ? -1 : (8*_P0) + 1;
    const int u2= p0n ? -1 : (8*_P0) + 2;
    const int u3= p0n ? -1 : (8*_P0) + 3;
    const int u4= p0n ? -1 : (8*_P0) + 4;
    const int u5= p0n ? -1 : (8*_P0) + 5;
    const int u6= p0n ? -1 : (8*_P0) + 6;
    const int u7= p0n ? -1 : (8*_P0) + 7;
    const int u8= p1n ? -1 : (8*_P1) + 0;
    const int u9= p1n ? -1 : (8*_P1) + 1;
    const int ua= p1n ? -1 : (8*_P1) + 2;
    const int ub= p1n ? -1 : (8*_P1) + 3;
    const int uc= p1n ? -1 : (8*_P1) + 4;
    const int ud= p1n ? -1 : (8*_P1) + 5;
    const int ue= p1n ? -1 : (8*_P1) + 6;
    const int uf= p1n ? -1 : (8*_P1) + 7;
    uint8x16_t ai = vreinterpretq_u8_u64(a);
    uint8x16_t bi = vreinterpretq_u8_u64(b);
    uint8x16_t ri=perm2_v16u8<u0, u1, u2, u3, u4, u5, u6, u7,
                              u8, u9, ua, ub, uc, ud, ue, uf>::v(ai, bi);
    return vreinterpretq_u64_u8(ri);
}



template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
uint8x8_t
cftal::arm::perm_v8u8(uint8x8_t a)
{
    return impl::perm1_v8u8<_P0, _P1, _P2, _P3,
                            _P4, _P5, _P6, _P7>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
uint8x8_t
cftal::arm::perm_v8u8(uint8x8_t a, uint8x8_t b)
{
    return impl::perm2_v8u8<_P0, _P1, _P2, _P3,
                            _P4, _P5, _P6, _P7>::v(a, b);
}

template <int _P0, int _P1>
inline
uint32x2_t
cftal::arm::perm_v2u32(uint32x2_t a)
{
    return impl::perm1_v2u32<_P0, _P1>::v(a);
}

template <int _P0, int _P1>
inline
uint32x2_t
cftal::arm::perm_v2u32(uint32x2_t a, uint32x2_t b)
{
    return impl::perm2_v2u32<_P0, _P1>::v(a, b);
}

template <int _P0, int _P1>
inline
int32x2_t
cftal::arm::perm_v2s32(int32x2_t a)
{
    uint32x2_t ai=vreinterpret_u32_s32(a);
    uint32x2_t ri=impl::perm1_v2u32<_P0, _P1>::v(ai);
    return vreinterpret_s32_u32(ri);
}

template <int _P0, int _P1>
inline
int32x2_t
cftal::arm::perm_v2s32(int32x2_t a, int32x2_t b)
{
    uint32x2_t ai=vreinterpret_u32_s32(a);
    uint32x2_t bi=vreinterpret_u32_s32(b);
    uint32x2_t ri=impl::perm2_v2u32<_P0, _P1>::v(ai, bi);
    return vreinterpret_s32_u32(ri);
}

template <int _P0, int _P1>
inline
float32x2_t
cftal::arm::perm_v2f32(float32x2_t a)
{
    uint32x2_t ai=vreinterpret_u32_f32(a);
    uint32x2_t ri=impl::perm1_v2u32<_P0, _P1>::v(ai);
    return vreinterpret_f32_u32(ri);
}

template <int _P0, int _P1>
inline
float32x2_t
cftal::arm::perm_v2f32(float32x2_t a, float32x2_t b)
{
    uint32x2_t ai=vreinterpret_u32_f32(a);
    uint32x2_t bi=vreinterpret_u32_f32(b);
    uint32x2_t ri=impl::perm2_v2u32<_P0, _P1>::v(ai, bi);
    return vreinterpret_f32_u32(ri);
}


template <int _P0, int _P1>
inline
uint64x2_t
cftal::arm::perm_v2u64(uint64x2_t a)
{
    return impl::perm1_v2u64<_P0, _P1>::v(a);
}

template <int _P0, int _P1>
inline
uint64x2_t
cftal::arm::perm_v2u64(uint64x2_t a, uint64x2_t b)
{
    return impl::perm2_v2u64<_P0, _P1>::v(a, b);
}

template <int _P0, int _P1>
inline
int64x2_t
cftal::arm::perm_v2s64(int64x2_t a)
{
    uint64x2_t ai=vreinterpretq_u64_s64(a);
    uint64x2_t ri=impl::perm1_v2u64<_P0, _P1>::v(ai);
    return vreinterpretq_s64_u64(ri);
}

template <int _P0, int _P1>
inline
int64x2_t
cftal::arm::perm_v2s64(int64x2_t a, int64x2_t b)
{
    uint64x2_t ai=vreinterpretq_u64_s64(a);
    uint64x2_t bi=vreinterpretq_u64_s64(b);
    uint64x2_t ri=impl::perm2_v2u64<_P0, _P1>::v(ai, bi);
    return vreinterpretq_s64_u64(ri);
}

template <int _P0, int _P1>
inline
float64x2_t
cftal::arm::perm_v2f64(float64x2_t a)
{
    uint64x2_t ai=vreinterpretq_u64_f64(a);
    uint64x2_t ri=impl::perm1_v2u64<_P0, _P1>::v(ai);
    return vreinterpretq_f64_u64(ri);
}

template <int _P0, int _P1>
inline
float64x2_t
cftal::arm::perm_v2f64(float64x2_t a, float64x2_t b)
{
    uint64x2_t ai=vreinterpretq_u64_f64(a);
    uint64x2_t bi=vreinterpretq_u64_f64(b);
    uint64x2_t ri=impl::perm2_v2u64<_P0, _P1>::v(ai, bi);
    return vreinterpretq_f64_u64(ri);
}

inline
int
cftal::arm::compress_mask_u32(uint32x2_t x)
{
    uint32x2_t xs=x;
    const uint32x2_t msk{1, 2};
    uint32x2_t xm= vand_u32(xs, msk);
    uint32x2_t r= vpadd_u32(xm, xm);
    return vget_lane_u32(r, 0);
}

inline
int
cftal::arm::compress_mask_u32(uint32x4_t x)
{
    uint32x4_t xs=x;
    const uint32x4_t msk{1, 2, 3, 4};
    uint32x4_t xm= vandq_u32(xs, msk);
    // combine bits from low and high lane
    uint32x2_t xml= vget_low_u32(xm);
    uint32x2_t xmh= vget_high_u32(xm);
    uint32x2_t xlh= vorr_u32(xml, xmh);
    // horizontal add
    uint32x2_t r= vpadd_u32(xlh, xlh);
    return vget_lane_u32(r, 0);
}

inline
int
cftal::arm::compress_mask_u64(uint64x2_t x)
{
    const uint64x2_t msk{1, 2};
    uint64x2_t xm= vandq_u64(x, msk);
    uint64x1_t xml= vget_low_u64(xm);
    uint64x1_t xmh= vget_high_u64(xm);
    uint64x1_t r = vorr_u64(xml, xmh);
    return vget_lane_u64(r, 0);
}


inline
int
cftal::arm::read_signs_s32(int32x2_t x)
{
    int32x2_t xs=vshr_n_s32(x, 31);
    return compress_mask_u32(vreinterpret_u32_s32(xs));
}

inline
int
cftal::arm::read_signs_s32(int32x4_t x)
{
    int32x4_t xs=vshrq_n_s32(x, 31);
    return compress_mask_u32(vreinterpretq_u32_s32(xs));
}

inline
int
cftal::arm::read_signs_s64(int64x2_t x)
{
    int64x2_t xs=vshrq_n_s64(x, 63);
    return compress_mask_u64(vreinterpretq_u64_s64(xs));
}

// Local variables:
// mode: c++
// end:
#endif
