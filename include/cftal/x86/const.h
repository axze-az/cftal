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
#if !defined (__CFTAL_X86_CONST_H__)
#define __CFTAL_X86_CONST_H__ 1

#include <cftal/config.h>
#include <cftal/x86/intrin.h>
#include <cftal/types.h>

namespace cftal {

    namespace x86 {

        // union of mixed types
        template <typename _SCALAR, size_t _SN,
                  typename _VF32, typename _VF64, typename _VI>
        union vecunion {
            // array of scalars
            _SCALAR _s[_SN];
            // f32 vector
            _VF32 _vf;
            // f64 vector
            _VF64 _vd;
            // integer vector
            _VI _vi;
        };

        // static constants consisting of 4 uint32_t
        template <uint32_t _P0, uint32_t _P1,
                  uint32_t _P2, uint32_t _P3>
        class const_v4u32 {
            using u_t = vecunion<uint32_t, 4, __m128, __m128d, __m128i>;
            static __attribute__((__aligned__(16),
                                  __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m128i& iv();
            static const __m128& fv();
            static const __m128d& dv();
        };

        // static constants consisting of 8 uint16_t
        template <uint16_t _P0, uint16_t _P1,
                  uint16_t _P2, uint16_t _P3,
                  uint16_t _P4, uint16_t _P5,
                  uint16_t _P6, uint16_t _P7>
        class const_v8u16 {
            using u_t = vecunion<uint16_t, 8, __m128, __m128d, __m128i>;
            static __attribute__((__aligned__(16),
                                  __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m128i& iv();
            static const __m128& fv();
            static const __m128d& dv();
        };

        // static constants consisting of 16 uint8_t
        template <uint8_t _P00, uint8_t _P01,
                  uint8_t _P02, uint8_t _P03,
                  uint8_t _P04, uint8_t _P05,
                  uint8_t _P06, uint8_t _P07,
                  uint8_t _P08, uint8_t _P09,
                  uint8_t _P10, uint8_t _P11,
                  uint8_t _P12, uint8_t _P13,
                  uint8_t _P14, uint8_t _P15>
        class const_v16u8 {
            using u_t = vecunion<uint8_t, 16, __m128, __m128d, __m128i>;
            static __attribute__((__aligned__(16),
                                  __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m128i& iv();
            static const __m128& fv();
            static const __m128d& dv();
        };

#if defined (__AVX__)
        // static constants consisting of 8 uint32_t
        template <uint32_t _P0, uint32_t _P1,
                  uint32_t _P2, uint32_t _P3,
                  uint32_t _P4, uint32_t _P5,
                  uint32_t _P6, uint32_t _P7>
        class const_v8u32 {
            using u_t = vecunion<uint32_t, 8, __m256, __m256d, __m256i>;
            static __attribute__((__aligned__(32),
                                  __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m256i& iv();
            static const __m256& fv();
            static const __m256d& dv();
        };

        // static constants consisting of 16 uint16_t
        template <uint16_t _P00, uint16_t _P01,
                  uint16_t _P02, uint16_t _P03,
                  uint16_t _P04, uint16_t _P05,
                  uint16_t _P06, uint16_t _P07,
                  uint16_t _P08, uint16_t _P09,
                  uint16_t _P10, uint16_t _P11,
                  uint16_t _P12, uint16_t _P13,
                  uint16_t _P14, uint16_t _P15>
        class const_v16u16 {
            using u_t = vecunion<uint16_t, 16, __m256, __m256d, __m256i>;
            static __attribute__((__aligned__(32),
                                  __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m256i& iv();
            static const __m256& fv();
            static const __m256d& dv();
        };

        // static constants consisting of 32 uint8_t
        template <uint8_t _P00, uint8_t _P01,
                  uint8_t _P02, uint8_t _P03,
                  uint8_t _P04, uint8_t _P05,
                  uint8_t _P06, uint8_t _P07,
                  uint8_t _P08, uint8_t _P09,
                  uint8_t _P10, uint8_t _P11,
                  uint8_t _P12, uint8_t _P13,
                  uint8_t _P14, uint8_t _P15,
                  uint8_t _P16, uint8_t _P17,
                  uint8_t _P18, uint8_t _P19,
                  uint8_t _P20, uint8_t _P21,
                  uint8_t _P22, uint8_t _P23,
                  uint8_t _P24, uint8_t _P25,
                  uint8_t _P26, uint8_t _P27,
                  uint8_t _P28, uint8_t _P29,
                  uint8_t _P30, uint8_t _P31>
        class const_v32u8 {
            using u_t = vecunion<uint8_t, 32, __m256, __m256d, __m256i>;
            static __attribute__((__aligned__(32),
                                  __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m256i& iv();
            static const __m256& fv();
            static const __m256d& dv();
        };

#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

        // static constants consisting of 16 uint32_t
        template <uint32_t _P00, uint32_t _P01,
                  uint32_t _P02, uint32_t _P03,
                  uint32_t _P04, uint32_t _P05,
                  uint32_t _P06, uint32_t _P07,
                  uint32_t _P08, uint32_t _P09,
                  uint32_t _P10, uint32_t _P11,
                  uint32_t _P12, uint32_t _P13,
                  uint32_t _P14, uint32_t _P15>
        class const_v16u32 {
            using u_t = vecunion<uint32_t, 16, __m512, __m512d, __m512i>;
            static
            __attribute__((__aligned__(64),
                          __visibility__("hidden")))
            const u_t _msk;
        public:
            static const __m512i& iv();
            static const __m512& fv();
            static const __m512d& dv();
        };

#endif

        template <int _P0, int _P1, int _P2, int _P3>
        struct shuffle4 {
            enum {
                val =
                (((_P3 & 3) << 6) |
                    ((_P2 & 3) << 4) |
                    ((_P1 & 3) << 2) |
                    ((_P0 & 3) << 0))
            };
        };

        template <int _P0, int _P1>
        struct shuffle2 {
            enum {
                val =
                (((_P0 & 1) << 0) |
                    ((_P1 & 1) << 1))
            };
        };

        // template for constant selects/blends with 2 elements
        template <int _P0, int _P1>
        struct csel2 {
            enum {
                val=
                (((_P1 & 1) << 1) |
                    ( _P0 & 1))
            };
        };

        // template for constant selects/blends with 4 elements
        template <int _P0, int _P1, int _P2, int _P3>
        struct csel4 {
            enum {
                val =
                (((_P3 & 1) << 3) |
                    ((_P2 & 1) << 2) |
                    ((_P1 & 1) << 1) |
                    ( _P0 & 1))
            };
        };

        // template for constant selects/blends with 8 elements
        template <int _P0, int _P1, int _P2, int _P3,
                    int _P4, int _P5, int _P6, int _P7>
        struct csel8 {
            enum {
                val =
                (((_P7 & 1) << 7) |
                    ((_P6 & 1) << 6) |
                    ((_P5 & 1) << 5) |
                    ((_P4 & 1) << 4) |
                    ((_P3 & 1) << 3) |
                    ((_P2 & 1) << 2) |
                    ((_P1 & 1) << 1) |
                    ((_P0 & 1) << 0))
            };
        };

        // (u)int16_t constants
        typedef const_v8u16<0x8080, 0x8080,
                            0x8080, 0x8090,
                            0x8080, 0x8090,
                            0x8080, 0x8080> v_sign_v16s8_msk;

        typedef const_v8u16<0x7f7f, 0x7f7f,
                            0x7f7f, 0x7f7f,
                            0x7f7f, 0x7f7f,
                            0x7f7f, 0x7f7f> v_not_sign_v16s8_msk;
        const int sign_v16s8_msk = 0xFFFF;

        // (u)int16_t constants
        typedef const_v8u16<0x8000, 0x8000,
                            0x8000, 0x8000,
                            0x8000, 0x8000,
                            0x8000, 0x8000> v_sign_v8s16_msk;

        typedef const_v8u16<0x7fff, 0x7fff,
                            0x7fff, 0x7fff,
                            0x7fff, 0x7fff,
                            0x7fff, 0x7fff> v_not_sign_v8s16_msk;
        const int sign_v8s16_msk = 0xAAAA;

        // (u)int32_t constants
        typedef const_v4u32<0x80000000, 0x80000000,
                            0x00000000, 0x00000000> v_sign_v2s32_msk;
        typedef const_v4u32<0x7fffffff, 0x7fffffff,
                            0xffffffff, 0xffffffff> v_not_sign_v2s32_msk;
        const int sign_v2s32_msk = 0x88;

        typedef const_v4u32<0x80000000, 0x80000000,
                            0x80000000, 0x80000000> v_sign_v4s32_msk;
        typedef const_v4u32<0x7fffffff, 0x7fffffff,
                            0x7fffffff, 0x7fffffff> v_not_sign_v4s32_msk;
        const int sign_v4s32_msk = 0x8888;

        // (u)int64_t constants
        typedef const_v4u32<0x00000000, 0x80000000,
                            0x00000000, 0x80000000> v_sign_v2s64_msk;
        typedef const_v4u32<0xffffffff, 0x7fffffff,
                            0xffffffff, 0x7fffffff> v_not_sign_v2s64_msk;
        const int sign_v2s64_msk = 0x8080;

        // f32 constants
        typedef v_sign_v4s32_msk v_sign_v4f32_msk;
        typedef v_not_sign_v4s32_msk v_not_sign_f32_msk;

#if defined (__AVX__)
        typedef const_v8u32<0x7fffffff, 0x7fffffff,
                            0x7fffffff, 0x7fffffff,
                            0x7fffffff, 0x7fffffff,
                            0x7fffffff, 0x7fffffff> v_not_sign_v8f32_msk;

        typedef const_v8u32<0x80000000, 0x80000000,
                            0x80000000, 0x80000000,
                            0x80000000, 0x80000000,
                            0x80000000, 0x80000000> v_sign_v8f32_msk;
        using v_sign_v8s32_msk = v_sign_v8f32_msk;
#endif

        typedef const_v4u32<0x7f800000, 0x7f800000,
                            0x7f800000, 0x7f800000> v_exp_f32_msk;

#if defined (__AVX__)
        typedef const_v8u32<0x7f800000, 0x7f800000,
                            0x7f800000, 0x7f800000,
                            0x7f800000, 0x7f800000,
                            0x7f800000, 0x7f800000> v_exp_v8f32_msk;
#endif
        typedef const_v4u32<0x007fffff, 0x007fffff,
                            0x007fffff, 0x007fffff> v_sig_f32_msk;
        const int sign_f32_msk = 0x0f;
        const int exp_shift_f32 = 23;
        const int exp_msk_f32 = 0xff;

        // f64 constants
        typedef v_sign_v2s64_msk v_sign_v2f64_msk;
        typedef v_not_sign_v2s64_msk v_not_sign_v2f64_msk;

#if defined (__AVX__)
        typedef const_v8u32<0x00000000, 0x80000000,
                            0x00000000, 0x80000000,
                            0x00000000, 0x80000000,
                            0x00000000, 0x80000000> v_sign_v4f64_msk;
        typedef const_v8u32<0xffffffff, 0x7fffffff,
                            0xffffffff, 0x7fffffff,
                            0xffffffff, 0x7fffffff,
                            0xffffffff, 0x7fffffff> v_not_sign_v4f64_msk;
        typedef const_v8u32<0xffffffff,0x000fffff,
                            0xffffffff,0x000fffff,
                            0xffffffff,0x000fffff,
                            0xffffffff,0x000fffff> v_sig_v4f64_msk;
        typedef const_v8u32<0x00000000,0x7ff00000,
                            0x00000000,0x7ff00000,
                            0x00000000,0x7ff00000,
                            0x00000000,0x7ff00000> v_exp_v4f64_msk;
#endif

        typedef const_v4u32<0x00000000,0x7ff00000,
                            0x00000000,0x7ff00000> v_exp_v2f64_msk;
        typedef const_v4u32<0xffffffff,0x000fffff,
                            0xffffffff,0x000fffff> v_sig_v2f64_msk;
        const int sign_f64_msk = 0x03;
        const int bias_f64 = 0x3ff;
        const int exp_shift_f64 = 52;
        const int exp_msk_f64 = 0x7ff;

        // definition of common used constants
        typedef const_v4u32<0x01010101, 0x01010101,
                            0x01010101, 0x01010101> v_uint8_0x01;
        typedef const_v4u32<0x33333333, 0x33333333,
                            0x33333333, 0x33333333> v_uint8_0x33;
        typedef const_v4u32<0x55555555, 0x55555555,
                            0x55555555, 0x55555555> v_uint8_0x55;
        typedef const_v4u32<0x0f0f0f0f, 0x0f0f0f0f,
                            0x0f0f0f0f, 0x0f0f0f0f> v_uint8_0x0f;

        typedef const_v4u32<0x00ff00ff, 0x00ff00ff,
                            0x00ff00ff, 0x00ff00ff> v_uint16_0x00ff;
        typedef const_v4u32<0x00010001, 0x00010001,
                            0x00010001, 0x00010001> v_uint16_0x0001;
    }
}

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3>
const
typename cftal::x86::const_v4u32<_P0, _P1, _P2, _P3>::u_t
cftal::x86::const_v4u32<_P0, _P1, _P2, _P3>::_msk= {{
        _P0, _P1, _P2, _P3
    }
};

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3>
inline
const __m128i&
cftal::x86::const_v4u32<_P0, _P1, _P2, _P3>::iv()
{
    return _msk._vi;
}

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3>
inline
const __m128&
cftal::x86::const_v4u32<_P0, _P1, _P2, _P3>::fv()
{
    return  _msk._vf;
}

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3>
inline
const __m128d&
cftal::x86::const_v4u32<_P0, _P1, _P2, _P3>::dv()
{
    return _msk._vd;
}

template <cftal::uint16_t _P0, cftal::uint16_t _P1,
          cftal::uint16_t _P2, cftal::uint16_t _P3,
          cftal::uint16_t _P4, cftal::uint16_t _P5,
          cftal::uint16_t _P6, cftal::uint16_t _P7>
const typename
cftal::x86::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::u_t
cftal::x86::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::_msk= {{
        _P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7
    }
};

template <cftal::uint16_t _P0, cftal::uint16_t _P1,
          cftal::uint16_t _P2, cftal::uint16_t _P3,
          cftal::uint16_t _P4, cftal::uint16_t _P5,
          cftal::uint16_t _P6, cftal::uint16_t _P7>
inline
const __m128i&
cftal::x86::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::iv()
{
    return _msk._vi;
}

template <cftal::uint16_t _P0, cftal::uint16_t _P1,
          cftal::uint16_t _P2, cftal::uint16_t _P3,
          cftal::uint16_t _P4, cftal::uint16_t _P5,
          cftal::uint16_t _P6, cftal::uint16_t _P7>
inline
const __m128&
cftal::x86::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::fv()
{
    return _msk._vf;
}

template <cftal::uint16_t _P0, cftal::uint16_t _P1,
          cftal::uint16_t _P2, cftal::uint16_t _P3,
          cftal::uint16_t _P4, cftal::uint16_t _P5,
          cftal::uint16_t _P6, cftal::uint16_t _P7>
inline
const __m128d&
cftal::x86::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::dv()
{
    return _msk._vd;
}

template <cftal::uint8_t _P00, cftal::uint8_t _P01,
          cftal::uint8_t _P02, cftal::uint8_t _P03,
          cftal::uint8_t _P04, cftal::uint8_t _P05,
          cftal::uint8_t _P06, cftal::uint8_t _P07,
          cftal::uint8_t _P08, cftal::uint8_t _P09,
          cftal::uint8_t _P10, cftal::uint8_t _P11,
          cftal::uint8_t _P12, cftal::uint8_t _P13,
          cftal::uint8_t _P14, cftal::uint8_t _P15>
const typename
cftal::x86::
const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::u_t
cftal::x86::
const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::_msk= {{
        _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
        _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15
    }
};

template <cftal::uint8_t _P00, cftal::uint8_t _P01,
          cftal::uint8_t _P02, cftal::uint8_t _P03,
          cftal::uint8_t _P04, cftal::uint8_t _P05,
          cftal::uint8_t _P06, cftal::uint8_t _P07,
          cftal::uint8_t _P08, cftal::uint8_t _P09,
          cftal::uint8_t _P10, cftal::uint8_t _P11,
          cftal::uint8_t _P12, cftal::uint8_t _P13,
          cftal::uint8_t _P14, cftal::uint8_t _P15>
inline
const __m128i&
cftal::x86::
const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::iv()
{
    return _msk._vi;
}

template <cftal::uint8_t _P00, cftal::uint8_t _P01,
          cftal::uint8_t _P02, cftal::uint8_t _P03,
          cftal::uint8_t _P04, cftal::uint8_t _P05,
          cftal::uint8_t _P06, cftal::uint8_t _P07,
          cftal::uint8_t _P08, cftal::uint8_t _P09,
          cftal::uint8_t _P10, cftal::uint8_t _P11,
          cftal::uint8_t _P12, cftal::uint8_t _P13,
          cftal::uint8_t _P14, cftal::uint8_t _P15>
inline
const __m128&
cftal::x86::
const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::fv()
{
    return _msk._vf;
}

template <cftal::uint8_t _P00, cftal::uint8_t _P01,
          cftal::uint8_t _P02, cftal::uint8_t _P03,
          cftal::uint8_t _P04, cftal::uint8_t _P05,
          cftal::uint8_t _P06, cftal::uint8_t _P07,
          cftal::uint8_t _P08, cftal::uint8_t _P09,
          cftal::uint8_t _P10, cftal::uint8_t _P11,
          cftal::uint8_t _P12, cftal::uint8_t _P13,
          cftal::uint8_t _P14, cftal::uint8_t _P15>
inline
const __m128d&
cftal::x86::
const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::dv()
{
    return _msk._vd;
}


#if defined (__AVX__)
template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3,
          cftal::uint32_t _P4, cftal::uint32_t _P5,
          cftal::uint32_t _P6, cftal::uint32_t _P7>
const typename
cftal::x86::
const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::u_t
cftal::x86::
const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::_msk= {{
        _P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7
    }
};

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3,
          cftal::uint32_t _P4, cftal::uint32_t _P5,
          cftal::uint32_t _P6, cftal::uint32_t _P7>
inline
const __m256i&
cftal::x86::
const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::iv()
{
    return _msk._vi;
}

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3,
          cftal::uint32_t _P4, cftal::uint32_t _P5,
          cftal::uint32_t _P6, cftal::uint32_t _P7>
inline
const __m256&
cftal::x86::
const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::fv()
{
    return _msk._vf;
}

template <cftal::uint32_t _P0, cftal::uint32_t _P1,
          cftal::uint32_t _P2, cftal::uint32_t _P3,
          cftal::uint32_t _P4, cftal::uint32_t _P5,
          cftal::uint32_t _P6, cftal::uint32_t _P7>
inline
const __m256d&
cftal::x86::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::dv()
{
    return _msk._vd;
}

template <cftal::uint16_t _P00, cftal::uint16_t _P01,
          cftal::uint16_t _P02, cftal::uint16_t _P03,
          cftal::uint16_t _P04, cftal::uint16_t _P05,
          cftal::uint16_t _P06, cftal::uint16_t _P07,
          cftal::uint16_t _P08, cftal::uint16_t _P09,
          cftal::uint16_t _P10, cftal::uint16_t _P11,
          cftal::uint16_t _P12, cftal::uint16_t _P13,
          cftal::uint16_t _P14, cftal::uint16_t _P15>
const typename
cftal::x86::
const_v16u16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::u_t
cftal::x86::
const_v16u16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::_msk= {{
        _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
        _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15
    }
};

template <cftal::uint16_t _P00, cftal::uint16_t _P01,
          cftal::uint16_t _P02, cftal::uint16_t _P03,
          cftal::uint16_t _P04, cftal::uint16_t _P05,
          cftal::uint16_t _P06, cftal::uint16_t _P07,
          cftal::uint16_t _P08, cftal::uint16_t _P09,
          cftal::uint16_t _P10, cftal::uint16_t _P11,
          cftal::uint16_t _P12, cftal::uint16_t _P13,
          cftal::uint16_t _P14, cftal::uint16_t _P15>
inline
const __m256i&
cftal::x86::
const_v16u16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::iv()
{
    return _msk._vi;
}

template <cftal::uint16_t _P00, cftal::uint16_t _P01,
          cftal::uint16_t _P02, cftal::uint16_t _P03,
          cftal::uint16_t _P04, cftal::uint16_t _P05,
          cftal::uint16_t _P06, cftal::uint16_t _P07,
          cftal::uint16_t _P08, cftal::uint16_t _P09,
          cftal::uint16_t _P10, cftal::uint16_t _P11,
          cftal::uint16_t _P12, cftal::uint16_t _P13,
          cftal::uint16_t _P14, cftal::uint16_t _P15>
inline
const __m256&
cftal::x86::
const_v16u16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::fv()
{
    return _msk._vf;
}

template <cftal::uint16_t _P00, cftal::uint16_t _P01,
          cftal::uint16_t _P02, cftal::uint16_t _P03,
          cftal::uint16_t _P04, cftal::uint16_t _P05,
          cftal::uint16_t _P06, cftal::uint16_t _P07,
          cftal::uint16_t _P08, cftal::uint16_t _P09,
          cftal::uint16_t _P10, cftal::uint16_t _P11,
          cftal::uint16_t _P12, cftal::uint16_t _P13,
          cftal::uint16_t _P14, cftal::uint16_t _P15>
inline
const __m256d&
cftal::x86::
const_v16u16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::dv()
{
    return _msk._vd;
}

template <uint8_t _P00, uint8_t _P01, uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05, uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09, uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13, uint8_t _P14, uint8_t _P15,
          uint8_t _P16, uint8_t _P17, uint8_t _P18, uint8_t _P19,
          uint8_t _P20, uint8_t _P21, uint8_t _P22, uint8_t _P23,
          uint8_t _P24, uint8_t _P25, uint8_t _P26, uint8_t _P27,
          uint8_t _P28, uint8_t _P29, uint8_t _P30, uint8_t _P31>
const typename
cftal::x86::
const_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::u_t
cftal::x86::
const_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::_msk= {{
        _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
        _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
        _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
        _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31
    }
};

template <uint8_t _P00, uint8_t _P01, uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05, uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09, uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13, uint8_t _P14, uint8_t _P15,
          uint8_t _P16, uint8_t _P17, uint8_t _P18, uint8_t _P19,
          uint8_t _P20, uint8_t _P21, uint8_t _P22, uint8_t _P23,
          uint8_t _P24, uint8_t _P25, uint8_t _P26, uint8_t _P27,
          uint8_t _P28, uint8_t _P29, uint8_t _P30, uint8_t _P31>
inline
const __m256i&
cftal::x86::
const_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::iv()
{
    return _msk._vi;
}

template <uint8_t _P00, uint8_t _P01, uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05, uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09, uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13, uint8_t _P14, uint8_t _P15,
          uint8_t _P16, uint8_t _P17, uint8_t _P18, uint8_t _P19,
          uint8_t _P20, uint8_t _P21, uint8_t _P22, uint8_t _P23,
          uint8_t _P24, uint8_t _P25, uint8_t _P26, uint8_t _P27,
          uint8_t _P28, uint8_t _P29, uint8_t _P30, uint8_t _P31>
inline
const __m256&
cftal::x86::
const_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::fv()
{
    return _msk._vf;
}

template <uint8_t _P00, uint8_t _P01, uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05, uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09, uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13, uint8_t _P14, uint8_t _P15,
          uint8_t _P16, uint8_t _P17, uint8_t _P18, uint8_t _P19,
          uint8_t _P20, uint8_t _P21, uint8_t _P22, uint8_t _P23,
          uint8_t _P24, uint8_t _P25, uint8_t _P26, uint8_t _P27,
          uint8_t _P28, uint8_t _P29, uint8_t _P30, uint8_t _P31>
inline
const __m256d&
cftal::x86::
const_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::dv()
{
    return _msk._vd;
}
#endif // __AVX__

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

template <cftal::uint32_t _P00, cftal::uint32_t _P01,
          cftal::uint32_t _P02, cftal::uint32_t _P03,
          cftal::uint32_t _P04, cftal::uint32_t _P05,
          cftal::uint32_t _P06, cftal::uint32_t _P07,
          cftal::uint32_t _P08, cftal::uint32_t _P09,
          cftal::uint32_t _P10, cftal::uint32_t _P11,
          cftal::uint32_t _P12, cftal::uint32_t _P13,
          cftal::uint32_t _P14, cftal::uint32_t _P15>
const typename
cftal::x86::
const_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
	     _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::u_t
cftal::x86::
const_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
	     _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::_msk= {{
        _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
        _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15
    }
};

template <cftal::uint32_t _P00, cftal::uint32_t _P01,
          cftal::uint32_t _P02, cftal::uint32_t _P03,
          cftal::uint32_t _P04, cftal::uint32_t _P05,
          cftal::uint32_t _P06, cftal::uint32_t _P07,
          cftal::uint32_t _P08, cftal::uint32_t _P09,
          cftal::uint32_t _P10, cftal::uint32_t _P11,
          cftal::uint32_t _P12, cftal::uint32_t _P13,
          cftal::uint32_t _P14, cftal::uint32_t _P15>
inline
const __m512i&
cftal::x86::
const_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
	     _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::iv()
{
    return _msk._vi;
}

template <cftal::uint32_t _P00, cftal::uint32_t _P01,
          cftal::uint32_t _P02, cftal::uint32_t _P03,
          cftal::uint32_t _P04, cftal::uint32_t _P05,
          cftal::uint32_t _P06, cftal::uint32_t _P07,
          cftal::uint32_t _P08, cftal::uint32_t _P09,
          cftal::uint32_t _P10, cftal::uint32_t _P11,
          cftal::uint32_t _P12, cftal::uint32_t _P13,
          cftal::uint32_t _P14, cftal::uint32_t _P15>
inline
const __m512&
cftal::x86::
const_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
	     _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::fv()
{
    return _msk._vf;
}

template <cftal::uint32_t _P00, cftal::uint32_t _P01,
          cftal::uint32_t _P02, cftal::uint32_t _P03,
          cftal::uint32_t _P04, cftal::uint32_t _P05,
          cftal::uint32_t _P06, cftal::uint32_t _P07,
          cftal::uint32_t _P08, cftal::uint32_t _P09,
          cftal::uint32_t _P10, cftal::uint32_t _P11,
          cftal::uint32_t _P12, cftal::uint32_t _P13,
          cftal::uint32_t _P14, cftal::uint32_t _P15>
inline
const __m512d&
cftal::x86::
const_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
	     _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::dv()
{
    return _msk._vd;
}

#endif

// Local variables:
// mode: c++
// end:
#endif
