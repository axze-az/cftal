//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_X86_PERM_H__)
#define __CFTAL_X86_PERM_H__ 1

#include <cftal/config.h>
#include <cftal/x86/ops_0.h>
#include <cftal/x86/ops_1.h>
#include <cftal/x86/select.h>

namespace cftal {

    namespace x86 {

        // permute s8/u8 using s8 indices
        __m128i
        permute_v16u8_v16s8(__m128i s, __m128i idx);

        __m128i
        permute_v16u8_v16s8(__m128i l, __m128i h, __m128i idx);

        // permute s16/u16 using s16 indices
        __m128i
        permute_v8u16_v8s16(__m128i s, __m128i idx);

        __m128i
        permute_v8u16_v8s16(__m128i l, __m128i h, __m128i idx);

        // permute s32/u32 using s32 indices
        __m128i
        permute_v4u32_v4s32(__m128i s, __m128i idx);

        __m128i
        permute_v4u32_v4s32(__m128i l, __m128i h, __m128i idx);

        // permute s64/u64 using s64 indices
        __m128i
        permute_v2u64_v2s64(__m128i s, __m128i idx);

        __m128i
        permute_v2u64_v2s64(__m128i l, __m128i h, __m128i idx);

        // permute f32 using s32 indices
        __m128
        permute_v4f32_v4s32(__m128 s, __m128i idx);

        __m128
        permute_v4f32_v4s32(__m128 l, __m128 h, __m128i idx);

        // permute f64 using i64 indices
        __m128d
        permute_v2f64_v2s64(__m128d s, __m128i idx);

        __m128d
        permute_v2f64_v2s64(__m128d l, __m128d h, __m128i idx);

#if defined (__AVX2__)
        // permute s32/u32 using s32 indices
        __m256i
        permute_v8u32_v8s32(__m256i s, __m256i idx);

        __m256i
        permute_v8u32_v8s32(__m256i l, __m256i h, __m256i idx);

        // permute s64/u64 using s64 indices
        __m256i
        permute_v4u64_v4s64(__m256i s, __m256i idx);

        __m256i
        permute_v4u64_v4s64(__m256i l, __m256i h, __m256i idx);

        // permute f32 using s32 indices
        __m256
        permute_v8f32_v8s32(__m256 s, __m256i idx);

        __m256
        permute_v8f32_v8s32(__m256 l, __m256 h, __m256i idx);

        // permute f64 using s64 indices
        __m256d
        permute_v4f64_v4s64(__m256d s, __m256i idx);

        __m256d
        permute_v4f64_v4s64(__m256d l, __m256d h, __m256i idx);

        // return odd numbered elements
        __m128i
        odd_elements_v16u16(__m256i);

        // return even numbered elements
        __m128i
        even_elements_v16u16(__m256i);
#endif

#if defined (__AVX512F__)
        // permute s32/u32 using s32 indices
        __m512i
        permute_v16u32_v16s32(__m512i s, __m512i idx);

        // permute s64/u64 using s64 indices
        __m512i
        permute_v8u64_v8s64(__m512i s, __m512i idx);

        // permute f32 using s32 indices
        __m512
        permute_v16f32_v16s32(__m512 s, __m512i idx);

        // permute f64 using s64 indices
        __m512d
        permute_v8f64_v8s64(__m512d s, __m512i idx);
#endif

#if defined (__AVX512BW__)
#if defined (__AVX512VL__)
        // permute s16/u16 using s16 indices
        __m256i
        permute_v16u16_v16s16(__m256i s, __m256i idx);
#endif
        // permute s16/u16 using s16 indices
        __m512i
        permute_v32u16_v32s16(__m512i s, __m512i idx);

#if defined (__AVX512VL__)
        // return odd numbered elements
        __m256i
        odd_elements_v32u16(__m512i);

        // return even numbered elements
        __m256i
        even_elements_v32u16(__m512i);
#endif
#endif

        // generic permutation of one double vector
        template <int _P0, int _P1>
        struct perm1_v2f64 {
            static __m128d v(__m128d a);
        };

        // generic permutation of two double vectors
        template <int _P0, int _P1>
        struct perm2_v2f64 {
            static __m128d v(__m128d a, __m128d b);
        };

        // specializations for perm1_v2f64
        template <>
        struct perm1_v2f64<-1,-1> : public make_zero_v2f64 {};
        template <>
        struct perm1_v2f64< 0, 1> : public select_arg_1<__m128d> {};
        template <>
        struct perm1_v2f64< 1, 1> : public vunpckhpd {};
        template <>
        struct perm1_v2f64< 0, 0> : public vmovddup {};
        template <>
        struct perm1_v2f64<-1, 0>
            : public exec_int< vpslldq<8> > {};
        template <>
        struct perm1_v2f64< 1,-1>
            : public exec_int< vpsrldq<8> > {};

        // specializations for perm2_v2f64
        template <>
        struct perm2_v2f64<-1,-1> : public make_zero_v2f64 {};
        template <>
        struct perm2_v2f64<0,1> : public select_arg_1<__m128d> {};
        template <>
        struct perm2_v2f64<2,3> : public select_arg_2<__m128d> {};
        template <>
        struct perm2_v2f64<0,2> : public vunpcklpd {};
        template <>
        struct perm2_v2f64<2,0> :
            public swap_ab<__m128d, vunpcklpd> {};
        template <>
        struct perm2_v2f64<1,3> : public vunpckhpd {};
        template <>
        struct perm2_v2f64<3,1> :
            public swap_ab<__m128d, vunpckhpd> {};

        // generic permutation of one float vector
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm1_v4f32 {
            static __m128 v(__m128 a);
        };

        // generic permutation of two float vectors
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm2_v4f32 {
            static __m128 v(__m128 a, __m128 b);
        };

        // specializations for perm1_v4f32
        template <>
        struct perm1_v4f32<-1,-1,-1,-1> : public make_zero_v4f32 {};
        template <>
        struct perm1_v4f32<0,1,2,3> : public select_arg_1<__m128> {};
        template <>
        struct perm1_v4f32<0,1,0,1> : public exec_f64<vunpcklpd> {};
        template <>
        struct perm1_v4f32<2,3,2,3> : public exec_f64<vunpckhpd> {};
        template <>
        struct perm1_v4f32<0,0,1,1> : public vunpcklps {};
        template <>
        struct perm1_v4f32<0,0,2,2> : public vmovsldup {};
        template <>
        struct perm1_v4f32<1,1,3,3> : public vmovshdup {};
        template <>
        struct perm1_v4f32<2,2,3,3> : public vunpckhps {};

        template <>
        struct perm1_v4f32< 0,-1, 1,-1>
            : public fixed_arg_2<__m128, make_zero_v4f32,
                                 vunpcklps> {};
        template <>
        struct perm1_v4f32< 2,-1, 3,-1>
            : public fixed_arg_2<__m128, make_zero_v4f32,
                                 vunpckhps> {};
        template <>
        struct perm1_v4f32<-1, 0, -1, 1>
            : public fixed_arg_1<__m128, make_zero_v4f32,
                                 vunpcklps> {};
        template <>
        struct perm1_v4f32<-1, 2, -1, 3>
            : public fixed_arg_1<__m128, make_zero_v4f32,
                                 vunpckhps> {};
        template <>
        struct perm1_v4f32< 0, 1,-1,-1>
            : public fixed_arg_2<__m128, make_zero_v4f32,
                                 exec_f64<vunpcklpd> > {};
        template <>
        struct perm1_v4f32<-1,-1, 2, 3>
            : public fixed_arg_1<__m128, make_zero_v4f32,
                                 exec_f64<vunpckhpd> > {};
        template <>
        struct perm1_v4f32<0, 0, 0, 0> : public splat_v4f32<0> {};
        template <>
        struct perm1_v4f32<1, 1, 1, 1> : public splat_v4f32<1> {};
        template <>
        struct perm1_v4f32<2, 2, 2, 2> : public splat_v4f32<2> {};
        template <>
        struct perm1_v4f32<3, 3, 3, 3> : public splat_v4f32<3> {};

        template <>
        struct perm1_v4f32<-1, 0, 1, 2>
            : public exec_int< vpslldq<4> > {};
        template <>
        struct perm1_v4f32<-1,-1, 0, 1>
            : public exec_int< vpslldq<8> > {};
        template <>
        struct perm1_v4f32<-1,-1,-1, 0>
            : public exec_int< vpslldq<12> > {};
        template <>
        struct perm1_v4f32< 1, 2, 3,-1>
            : public exec_int< vpsrldq<4> > {};
        template <>
        struct perm1_v4f32< 2, 3,-1,-1>
            : public exec_int< vpsrldq<8> > {};
        template <>
        struct perm1_v4f32< 3,-1,-1,-1>
            : public exec_int< vpsrldq<12> > {};
        template <>
        struct perm1_v4f32<-1, 0,-1, 2>
            : public exec_int< vpsllq_const<32> > {};
        template <>
        struct perm1_v4f32< 1,-1, 3,-1>
            : public exec_int< vpsrlq_const<32> > {};

        // specializations for perm2_v4f32
        template <>
        struct perm2_v4f32<-1,-1,-1,-1> : public make_zero_v4f32 {};
        template <>
        struct perm2_v4f32<0,1,2,3> : public select_arg_1<__m128> {};
        template <>
        struct perm2_v4f32<4,5,6,7> : public select_arg_2<__m128> {};

        template <>
        struct perm2_v4f32<0,1,0,1> :
            public use_arg_1<__m128, exec_f64<vunpcklpd> > {};
        template <>
        struct perm2_v4f32<4,5,4,5> :
            public use_arg_2<__m128, exec_f64<vunpcklpd> > {};

        template <>
        struct perm2_v4f32<2,3,2,3> :
            public use_arg_1<__m128, exec_f64<vunpckhpd> > {};
        template <>
        struct perm2_v4f32<6,7,6,7> :
            public use_arg_2<__m128, exec_f64<vunpckhpd> > {};

        template <>
        struct perm2_v4f32<0,0,1,1> :
            public use_arg_1<__m128, vunpcklps> {};
        template <>
        struct perm2_v4f32<4,4,5,5> :
            public use_arg_2<__m128, vunpcklps> {};

        template <>
        struct perm2_v4f32<2,2,3,3> :
            public use_arg_1<__m128, vunpckhps> {};
        template <>
        struct perm2_v4f32<6,6,7,7> :
            public use_arg_2<__m128, vunpckhps> {};

        template <>
        struct perm2_v4f32<0,4,1,5> : public vunpcklps {};
        template <>
        struct perm2_v4f32<4,0,5,1>
            : public swap_ab<__m128, vunpcklps> {};
        template <>
        struct perm2_v4f32<2,6,3,7> : public vunpckhps {};
        template <>
        struct perm2_v4f32<6,2,7,3>
            : public swap_ab<__m128, vunpckhps> {};

        template <>
        struct perm2_v4f32<0,1,4,5> : public exec_f64<vunpcklpd> {};
        template <>
        struct perm2_v4f32<4,5,0,1>
            : public swap_ab<__m128, exec_f64<vunpcklpd> > {};

        template <>
        struct perm2_v4f32<2,3,6,7> : public exec_f64<vunpckhpd> {};
        template <>
        struct perm2_v4f32<6,7,2,3>
            : public swap_ab<__m128, exec_f64<vunpckhpd> > {};

        // generic permutation of one uint32_t vector
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm1_v4u32 {
            static __m128i v(__m128i a);
        };

        // generic permutation of two uint32_t vectors
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm2_v4u32 {
            static __m128i v(__m128i a, __m128i b);
        };

        // specializations for one uint32_t vector
        template <>
        struct perm1_v4u32<-1,-1,-1,-1> : public make_zero_int {};
        template <>
        struct perm1_v4u32<0,1,2,3> : public select_arg_1<__m128i> {};
        template <>
        struct perm1_v4u32<0,1,0,1> : public vpunpcklqdq {};
        template <>
        struct perm1_v4u32<2,3,2,3> : public vpunpckhqdq {};
        template <>
        struct perm1_v4u32<0,0,1,1> : public vpunpckldq {};
        template <>
        struct perm1_v4u32<2,2,3,3> : public vpunpckhdq {};

        template <>
        struct perm1_v4u32< 0,-1, 1,-1> : public vpmovzxdq {};
        template <>
        struct perm1_v4u32< 2,-1, 3,-1>
            : public fixed_arg_2<__m128i, make_zero_int,
                                 vpunpckhdq> {};
        template <>
        struct perm1_v4u32<-1, 0,-1, 1>
            : public fixed_arg_1<__m128i, make_zero_int,
                                 vpunpckldq> {};
        template <>
        struct perm1_v4u32<-1, 2,-1, 3>
            : public fixed_arg_1<__m128i, make_zero_int,
                                 vpunpckhdq> {};
        template <>
        struct perm1_v4u32< 0, 1,-1,-1>
            : public fixed_arg_2<__m128i, make_zero_int,
                                 vpunpcklqdq> {};
        template <>
        struct perm1_v4u32<-1,-1, 2, 3>
            : public fixed_arg_1<__m128i, make_zero_int,
                                 vpunpckhqdq> {};
        template <>
        struct perm1_v4u32< 0, 0, 0, 0> : public splat_v4u32<0> {};
        template <>
        struct perm1_v4u32< 1, 1, 1, 1> : public splat_v4u32<1> {};
        template <>
        struct perm1_v4u32< 2, 2, 2, 2> : public splat_v4u32<2> {};
        template <>
        struct perm1_v4u32< 3, 3, 3, 3> : public splat_v4u32<3> {};

        template <>
        struct perm1_v4u32<-1, 0, 1, 2> : public vpslldq<4> {};
        template <>
        struct perm1_v4u32<-1,-1, 0, 1> : public vpslldq<8> {};
        template <>
        struct perm1_v4u32<-1,-1,-1, 0> : public vpslldq<12> {};

        template <>
        struct perm1_v4u32< 1, 2, 3,-1> : public vpsrldq<4> {};
        template <>
        struct perm1_v4u32< 2, 3,-1,-1> : public vpsrldq<8> {};
        template <>
        struct perm1_v4u32< 3,-1,-1,-1> : public vpsrldq<12> {};

        template <>
        struct perm1_v4u32<-1, 0,-1, 2> : public vpsllq_const<32> {};
        template <>
        struct perm1_v4u32< 1,-1, 3,-1> : public vpsrlq_const<32> {};

        // specializations for two uint32_t vectors.
        template <>
        struct perm2_v4u32<-1,-1,-1,-1> : public make_zero_int {};
        template <>
        struct perm2_v4u32<0,1,2,3> : public select_arg_1<__m128i> {};
        template <>
        struct perm2_v4u32<4,5,6,7> : public select_arg_2<__m128i> {};

        template <>
        struct perm2_v4u32<0,1,0,1> :
            public use_arg_1<__m128i, vpunpcklqdq> {};
        template <>
        struct perm2_v4u32<4,5,4,5> :
            public use_arg_2<__m128i, vpunpcklqdq> {};

        template <>
        struct perm2_v4u32<2,3,2,3> :
            public use_arg_1<__m128i, vpunpckhqdq> {};
        template <>
        struct perm2_v4u32<6,7,6,7> :
            public use_arg_2<__m128i, vpunpckhqdq> {};

        template <>
        struct perm2_v4u32<0,0,1,1> :
            public use_arg_1<__m128i, vpunpckldq> {};
        template <>
        struct perm2_v4u32<4,4,5,5> :
            public use_arg_2<__m128i, vpunpckldq> {};

        template <>
        struct perm2_v4u32<2,2,3,3> :
            public use_arg_1<__m128i, vpunpckhdq> {};
        template <>
        struct perm2_v4u32<6,6,7,7> :
            public use_arg_2<__m128i, vpunpckhdq> {};

        template <>
        struct perm2_v4u32<0,4,1,5> : public vpunpckldq {};
        template <>
        struct perm2_v4u32<4,0,5,1>
            : public swap_ab<__m128i, vpunpckldq> {};
        template <>
        struct perm2_v4u32<2,6,3,7> : public vpunpckhdq {};
        template <>
        struct perm2_v4u32<6,2,7,3>
            : public swap_ab<__m128i, vpunpckhdq> {};

        template <>
        struct perm2_v4u32<0,1,4,5> : public vpunpcklqdq {};
        template <>
        struct perm2_v4u32<4,5,0,1>
            : public swap_ab<__m128i, vpunpcklqdq> {};

        template <>
        struct perm2_v4u32<2,3,6,7> : public vpunpckhqdq {};
        template <>
        struct perm2_v4u32<6,7,2,3>
            : public swap_ab<__m128i, vpunpckhqdq> {};

        // generic permutation of one uint16_t vector
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm1_v8u16 {
            static __m128i v(__m128i a);
        };

        // generic permutation of two uint16_t vectors
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm2_v8u16 {
            static __m128i v(__m128i a, __m128i b);
        };

        // specialisations of permutations of one uint16_t
        // vector
        template <>
        struct perm1_v8u16<-1,-1,-1,-1,-1,-1,-1,-1>
            : public make_zero_int {};
        template <>
        struct perm1_v8u16< 0, 1, 2, 3, 4, 5, 6, 7>
            : public select_arg_1<__m128i> {};
        template <>
        struct perm1_v8u16< 0, 0, 1, 1, 2, 2, 3, 3>
            : public vpunpcklwd {};
        template <>
        struct perm1_v8u16< 4, 4, 5, 5, 6, 6, 7, 7>
            : public vpunpckhwd {};
        template <>
        struct perm1_v8u16< 0, 1, 0, 1, 2, 3, 2, 3>
            : public vpunpckldq {};
        template <>
        struct perm1_v8u16< 4, 5, 4, 5, 6, 7, 6, 7>
            : public vpunpckhdq {};
        template <>
        struct perm1_v8u16< 0, 1, 2, 3, 0, 1, 2, 3>
            : public vpunpcklqdq {};
        template <>
        struct perm1_v8u16< 4, 5, 6, 7, 4, 5, 6, 7>
            : public vpunpckhqdq {};
        template <>
        struct perm1_v8u16< 0,-1, 1,-1, 2,-1, 3,-1>
            : public vpmovzxwd {};
        template <>
        struct perm1_v8u16< 4,-1, 5,-1, 6,-1, 7,-1>
            : public fixed_arg_2<__m128i, make_zero_int,
                                 vpunpckhwd> {};
        template <>
        struct perm1_v8u16<-1, 0,-1, 1,-1, 2, -1, 3>
            : public fixed_arg_1<__m128i, make_zero_int,
                                 vpunpcklwd> {};
        template <>
        struct perm1_v8u16<-1, 4,-1, 5,-1, 6, -1, 7>
            : public fixed_arg_1<__m128i, make_zero_int,
                                 vpunpckhwd> {};
        template <>
        struct perm1_v8u16<0, 0, 0, 0, 0, 0, 0, 0>
            : public splat_v8u16<0> {};
        template <>
        struct perm1_v8u16<1, 1, 1, 1, 1, 1, 1, 1>
            : public splat_v8u16<1> {};
        template <>
        struct perm1_v8u16<2, 2, 2, 2, 2, 2, 2, 2>
            : public splat_v8u16<2> {};
        template <>
        struct perm1_v8u16<3, 3, 3, 3, 3, 3, 3, 3>
            : public splat_v8u16<3> {};
        template <>
        struct perm1_v8u16<4, 4, 4, 4, 4, 4, 4, 4>
            : public splat_v8u16<4> {};
        template <>
        struct perm1_v8u16<5, 5, 5, 5, 5, 5, 5, 5>
            : public splat_v8u16<5> {};
        template <>
        struct perm1_v8u16<6, 6, 6, 6, 6, 6, 6, 6>
            : public splat_v8u16<6> {};
        template <>
        struct perm1_v8u16<7, 7, 7, 7, 7, 7, 7, 7>
            : public splat_v8u16<7> {};
        template <>
        struct perm1_v8u16<-1, 0, 1, 2, 3, 4, 5, 6>
            : public vpslldq<2> {};
        template <>
        struct perm1_v8u16<-1, -1, 0, 1, 2, 3, 4, 5>
            : public vpslldq<4> {};
        template <>
        struct perm1_v8u16<-1,-1,-1, 0, 1, 2, 3, 4>
            : public vpslldq<6> {};
        template <>
        struct perm1_v8u16<-1,-1,-1,-1, 0, 1, 2, 3>
            : public vpslldq<8> {};
        template <>
        struct perm1_v8u16<-1,-1,-1,-1,-1, 0, 1, 2>
            : public vpslldq<10> {};
        template <>
        struct perm1_v8u16<-1,-1,-1,-1,-1,-1, 0, 1>
            : public vpslldq<12> {};
        template <>
        struct perm1_v8u16<-1,-1,-1,-1,-1,-1,-1, 0>
            : public vpslldq<14> {};
        template <>
        struct perm1_v8u16< 1, 2, 3, 4, 5, 6, 7,-1>
            : public vpsrldq<2> {};
        template <>
        struct perm1_v8u16< 2, 3, 4, 5, 6, 7,-1,-1>
            : public vpsrldq<4> {};
        template <>
        struct perm1_v8u16< 3, 4, 5, 6, 7,-1,-1,-1>
            : public vpsrldq<6> {};
        template <>
        struct perm1_v8u16< 4, 5, 6, 7,-1,-1,-1,-1>
            : public vpsrldq<8> {};
        template <>
        struct perm1_v8u16< 5, 6, 7,-1,-1,-1,-1,-1>
            : public vpsrldq<10> {};
        template <>
        struct perm1_v8u16< 6, 7,-1,-1,-1,-1,-1,-1>
            : public vpsrldq<12> {};
        template <>
        struct perm1_v8u16< 7,-1,-1,-1,-1,-1,-1,-1>
            : public vpsrldq<14> {};

        template <>
        struct perm1_v8u16<-1, 0,-1, 2,-1, 4,-1, 6>
            : public vpslld_const<16> {};
        template <>
        struct perm1_v8u16< 1,-1, 3,-1, 5,-1, 7,-1>
            : public vpsrld_const<16> {};

        template <>
        struct perm1_v8u16<-1, 0, 1, 2,-1, 4, 5, 6>
            : public vpsllq_const<16> {};
        template <>
        struct perm1_v8u16<-1,-1, 0, 1,-1,-1, 4, 5>
            : public vpsllq_const<32> {};
        template <>
        struct perm1_v8u16<-1,-1,-1, 0,-1,-1,-1, 4>
            : public vpsllq_const<48> {};

        template <>
        struct perm1_v8u16< 1, 2, 3,-1, 5, 6, 7,-1>
            : public vpsrlq_const<16> {};
        template <>
        struct perm1_v8u16< 2, 3,-1,-1, 6, 7,-1,-1>
            : public vpsrlq_const<32> {};
        template <>
        struct perm1_v8u16< 3,-1,-1,-1, 7,-1,-1,-1>
            : public vpsrlq_const<48> {};

        // specialisations for two uint16_t vectors
        template <>
        struct perm2_v8u16< 0, 8, 1, 9, 2,10, 3,11>
            : public vpunpcklwd {};
        template <>
        struct perm2_v8u16< 8, 0, 9, 1,10, 2,11, 3>
            : public swap_ab<__m128i, vpunpcklwd> {};
        template <>
        struct perm2_v8u16< 4,12, 5,13, 6,14, 7,15>
            : public vpunpckhwd {};
        template <>
        struct perm2_v8u16<12, 4,13, 5,14, 6,15, 7>
            : public swap_ab<__m128i, vpunpckhwd> {};
        template <>
        struct perm2_v8u16< 0, 1, 2, 3, 8, 9,10,11>
            : public vpunpcklqdq {};
        template <>
        struct perm2_v8u16< 8, 9,10,11, 0, 1, 2, 3>
            : public swap_ab<__m128i, vpunpcklqdq> {};
        template <>
        struct perm2_v8u16< 4, 5, 6, 7,12,13,14,15>
            : public vpunpckhqdq {};
        template <>
        struct perm2_v8u16<12,13,14,15, 4, 5, 6, 7>
            : public swap_ab<__m128i, vpunpckhqdq> {};

        // generic permutation of one v16u8 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        struct perm1_v16u8 {
            static __m128i v(__m128i a);
        };

        // generic permutation of one v16u8 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        struct perm2_v16u8 {
            static __m128i v(__m128i a, __m128i b);
        };

#if defined (__AVX__)
        // generic permutation of one double vector
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm1_v4f64 {
            static __m256d v(__m256d a);
        };

        // generic permutation of two double vectors
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm2_v4f64 {
            static __m256d v(__m256d a, __m256d b);
        };

        // specialization of permutations of one double
        // vector
        template <>
        struct perm1_v4f64<-1,-1,-1,-1>
            : public make_zero_v4f64 {};
        template <>
        struct perm1_v4f64<0, 0, 0, 0>
            : public vbroadcastsd<__m256d> {};
        template <>
        struct perm1_v4f64<0, 1, 2, 3>
            : public select_arg_1<__m256d> {};
        template <>
        struct perm1_v4f64<0, 0, 2, 2>
            : public vmovddup {};
        template <>
        struct perm1_v4f64<0,-1, 2,-1>
            : public fixed_arg_2<__m256d, make_zero_v4f64,
                                 vunpcklpd> {};
        template <>
        struct perm1_v4f64<-1, 0,-1, 2>
            : public fixed_arg_1<__m256d, make_zero_v4f64,
                                 vunpcklpd> {};
        template <>
        struct perm1_v4f64<1, 1, 3, 3>
            : public vunpckhpd {};
        template <>
        struct perm1_v4f64<1,-1, 3,-1>
            : public fixed_arg_2<__m256d, make_zero_v4f64,
                                 vunpckhpd> {};
        template <>
        struct perm1_v4f64<-1, 1, -1, 3>
            : public fixed_arg_1<__m256d, make_zero_v4f64,
                                 vunpckhpd> {};
        template <>
        struct perm1_v4f64<0, 1, 0, 1>
            : public vinsertf128<1> {};
        template <>
        struct perm1_v4f64<2, 3, 0, 1>
            : public vperm2f128<1, 0> {};
        template <>
        struct perm1_v4f64<2, 3, 2, 3>
            : public vperm2f128<1, 1> {};

        // specialization of permutations of two double
        // vectors
        template <>
        struct perm2_v4f64<-1,-1,-1,-1>
            : public make_zero_v4f64 {};
        template <>
        struct perm2_v4f64< 0, 1, 2, 3>
            : public select_arg_1<__m256d> {};
        template <>
        struct perm2_v4f64< 4, 5, 6, 7>
            : public select_arg_2<__m256d> {};

        template <>
        struct perm2_v4f64< 0, 4, 2, 6>
            : public vunpcklpd {};
        template <>
        struct perm2_v4f64< 4, 0, 6, 2>
            : public swap_ab<__m256d, vunpcklpd> {};

        template <>
        struct perm2_v4f64< 1, 5, 3, 7>
            : public vunpckhpd {};
        template <>
        struct perm2_v4f64< 5, 1, 7, 3>
            : public swap_ab<__m256d, vunpckhpd> {};

        template <>
        struct perm2_v4f64< 0, 1, 4, 5>
            : public vinsertf128<1> {};
        template <>
        struct perm2_v4f64< 0, 1, 6, 7>
            : public vperm2f128<0, 3> {};
        template <>
        struct perm2_v4f64< 2, 3, 4, 5>
            : public vperm2f128<1, 2> {};
        template <>
        struct perm2_v4f64< 2, 3, 6, 7>
            : public vperm2f128<1, 3> {};
        template <>
        struct perm2_v4f64< 4, 5, 0, 1>
            : public swap_ab<__m256d, vinsertf128<1> > {};
        template <>
        struct perm2_v4f64< 4, 5, 2, 3>
            : public vperm2f128<2, 1> {};
        template <>
        struct perm2_v4f64< 6, 7, 0, 1>
            : public vperm2f128<3, 0> {};
        template <>
        struct perm2_v4f64< 6, 7, 2, 3>
            : public vperm2f128<3, 1> {};

        template <>
        struct perm2_v4f64< 0, 4, 1, 5> {
            static __m256d v(__m256d a, __m256d b) {
#if 1
                __m128d al=_mm256_castpd256_pd128(a);
                __m128d bl=_mm256_castpd256_pd128(b);
                // 0 4
                __m128d rl=vunpcklpd::v(al, bl);
                // 1 5
                __m128d rh=vunpckhpd::v(al, bl);
                __m256d r=_mm256_castpd128_pd256(rl);
                r = vinsertf128<1>::v(r, rh);
                return r;
#else
                // 0 4 2 6
                __m256d t0= vunpcklpd::v(a, b);
                // 1 5 3 7
                __m256d t1= vunpckhpd::v(a, b);
                __m256d r= vperm2f128<0, 2>::v(t0, t1);
#endif
                return r;
            }
        };

        template <>
        struct perm2_v4f64< 4, 0, 5, 1> {
            static __m256d v(__m256d a, __m256d b) {
#if 1
                __m128d al=_mm256_castpd256_pd128(a);
                __m128d bl=_mm256_castpd256_pd128(b);
                // 4 0
                __m128d rl=vunpcklpd::v(bl, al);
                // 5 1
                __m128d rh=vunpckhpd::v(bl, al);
                __m256d r=_mm256_castpd128_pd256(rl);
                r = vinsertf128<1>::v(r, rh);
                return r;
#else
                // 4 0 6 2
                __m256d t0= vunpcklpd::v(b, a);
                // 5 1 7 3
                __m256d t1= vunpckhpd::v(b, a);
                __m256d r= vperm2f128<0, 2>::v(t0, t1);
                return r;
#endif
            }
        };

        template <>
        struct perm2_v4f64< 2, 6, 3, 7> {
            static __m256d v(__m256d a, __m256d b) {
                // 0 4 2 6
                __m256d t0= vunpcklpd::v(a, b);
                // 1 5 3 7
                __m256d t1= vunpckhpd::v(a, b);
                __m256d r= vperm2f128<1, 3>::v(t0, t1);
                return r;
            }
        };

        template <>
        struct perm2_v4f64< 6, 2, 7, 3> {
            static __m256d v(__m256d a, __m256d b) {
                // 4 0 6 2
                __m256d t0= vunpcklpd::v(b, a);
                // 5 1 7 3
                __m256d t1= vunpckhpd::v(b, a);
                __m256d r= vperm2f128<1, 3>::v(t0, t1);
                return r;
            }
        };

        // generic permutation of one float vector
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm1_v8f32 {
            static __m256 v(__m256 a);
        };


        // generic permutation of two float vectors
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm2_v8f32 {
            static __m256 v(__m256 a, __m256 b);
        };

        template <>
        struct perm1_v8f32<-1, -1, -1, -1, -1, -1, -1, -1>
            : public make_zero_v8f32 {};

        template <>
        struct perm1_v8f32<0, 0, 0, 0, 0, 0, 0, 0>
            : public vbroadcastss<__m256> {};

        template <>
        struct perm1_v8f32<0, 1, 2, 3, 4, 5, 6, 7>
            : public select_arg_1<__m256> {};

        template <>
        struct perm1_v8f32<0, 0, 1, 1, 4, 4, 5, 5>
            : public vunpcklps {};

        template <>
        struct perm1_v8f32<0, 0, 2, 2, 4, 4, 6, 6>
            : public vmovsldup {};

        template <>
        struct perm1_v8f32<1, 1, 3, 3, 5, 5, 7, 7>
            : public vmovshdup {};

        template <>
        struct perm1_v8f32<0, -1, 1, -1, 4, -1, 5, -1>
            : public fixed_arg_2<__m256, make_zero_v8f32,
                                 vunpcklps> {};

        template <>
        struct perm1_v8f32<-1, 0, -1, 1, -1, 4, -1, 5>
            : public fixed_arg_1<__m256, make_zero_v8f32,
                                 vunpcklps> {};

        template <>
        struct perm1_v8f32<2, 2, 3, 3, 6, 6, 7, 7>
            : public vunpckhps {};

        template <>
        struct perm1_v8f32<2, -1, 3, -1, 6, -1, 7, -1>
            : public fixed_arg_2<__m256, make_zero_v8f32,
                                 vunpckhps> {};

        template <>
        struct perm1_v8f32<-1, 2, -1, 3, -1, 6, -1, 7>
            : public fixed_arg_1<__m256, make_zero_v8f32,
                                 vunpckhps> {};

        template <>
        struct perm1_v8f32<0, 1, 0, 1, 4, 5, 4, 5>
            : public exec_f64<vunpcklpd> {};

        template <>
        struct perm1_v8f32<2, 3, 2, 3, 6, 7, 6, 7>
            : public exec_f64<vunpckhpd> {};

        template <>
        struct perm1_v8f32<0, 1, 2, 3, 0, 1, 2, 3>
            : public vinsertf128<1> {};

        template <>
        struct perm1_v8f32<4, 5, 6, 7, 0, 1, 2, 3>
            : public vperm2f128<1, 0> {};

        template <>
        struct perm1_v8f32<4, 5, 6, 7, 4, 5, 6, 7>
            : public vperm2f128<1, 1> {};

        template <>
        struct perm2_v8f32<-1, -1, -1, -1, -1, -1, -1, -1>
            : public make_zero_v8f32{};

        template <>
        struct perm2_v8f32<0, 1, 2, 3, 4, 5, 6, 7>
            : public select_arg_1<__m256> {};

        template <>
        struct perm2_v8f32<8, 9, 10, 11, 12, 13, 14, 15>
            : public select_arg_2<__m256> {};

        template <>
        struct perm2_v8f32<0, 8, 1, 9, 4, 12, 5, 13>
            : public vunpcklps {};

        template <>
        struct perm2_v8f32<2, 10, 3, 11, 6, 14, 7, 15>
            : public vunpckhps {};

        template <>
        struct perm2_v8f32<0, 1, 8, 9, 4, 5, 12, 13>
            : public exec_f64<vunpcklpd> {};

        template <>
        struct perm2_v8f32<2, 3, 10, 11, 6, 7, 14, 15>
            : public exec_f64<vunpckhpd> {};

        template <>
        struct perm2_v8f32<0, 1, 2, 3, 8, 9, 10, 11>
            : public vinsertf128<1> {};

        template <>
        struct perm2_v8f32<0, 1, 2, 3, 12, 13, 14, 15>
            : public vperm2f128<0, 3> {};

        template <>
        struct perm2_v8f32<4, 5, 6, 7, 8, 9, 10, 11>
            : public vperm2f128<1, 2> {};

        template <>
        struct perm2_v8f32<4, 5, 6, 7, 12, 13, 14, 15>
            : public vperm2f128<1, 3> {};

#endif
#if defined (__AVX2__)
        // generic permutation of one u64 vector
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm1_v4u64 {
            static __m256i v(__m256i a);
        };

        // generic permutation of two u64 vectors
        template <int _P0, int _P1, int _P2, int _P3>
        struct perm2_v4u64 {
            static __m256i v(__m256i a, __m256i b);
        };

        template <>
        struct perm1_v4u64<-1,-1,-1,-1>
            : public make_zero_int256 {};

        template <>
        struct perm1_v4u64<0, 1, 2, 3>
            : public select_arg_1<__m256i> {};

        template <>
        struct perm1_v4u64<0, 0, 0, 0>
            : public vbroadcastq<__m256i> {};

        template <>
        struct perm1_v4u64<0, 0, 2, 2>
            : public vpunpcklqdq {};

        template <>
        struct perm1_v4u64<1, 1, 3, 3>
            : public vpunpckhqdq {};

        template <>
        struct perm1_v4u64<0, 1, 0, 1>
            : public vinsertf128<1> {};
        template <>
        struct perm1_v4u64<2, 3, 0, 1>
            : public vperm2f128<1, 0> {};
        template <>
        struct perm1_v4u64<2, 3, 2, 3>
            : public vperm2f128<1, 1> {};

        template <>
        struct perm1_v4u64<0, -1, 2, -1>
            : public fixed_arg_2<__m256i, make_zero_int256,
                                 vpunpcklqdq> {};
        template <>
        struct perm1_v4u64<-1, 0, -1, 2>
            : public fixed_arg_1<__m256i, make_zero_int256,
                                 vpunpcklqdq> {};

        template <>
        struct perm2_v4u64<-1,-1,-1,-1>
            : public make_zero_int256 {};
        template <>
        struct perm2_v4u64< 0, 1, 2, 3>
            : public select_arg_1<__m256i> {};
        template <>
        struct perm2_v4u64< 4, 5, 6, 7>
            : public select_arg_2<__m256i> {};

        template <>
        struct perm2_v4u64< 0, 4, 2, 6>
            : public vpunpcklqdq {};
        template <>
        struct perm2_v4u64< 4, 0, 6, 2>
            : public swap_ab<__m256i, vpunpcklqdq> {};

        template <>
        struct perm2_v4u64< 1, 5, 3, 7>
            : public vpunpckhqdq {};
        template <>
        struct perm2_v4u64< 5, 1, 7, 3>
            : public swap_ab<__m256i, vpunpckhqdq> {};

        template <>
        struct perm2_v4u64< 0, 1, 4, 5>
            : public vinsertf128<1> {};
        template <>
        struct perm2_v4u64< 0, 1, 6, 7>
            : public vperm2f128<0, 3> {};
        template <>
        struct perm2_v4u64< 2, 3, 4, 5>
            : public vperm2f128<1, 2> {};
        template <>
        struct perm2_v4u64< 2, 3, 6, 7>
            : public vperm2f128<1, 3> {};
        template <>
        struct perm2_v4u64< 4, 5, 0, 1>
            : public swap_ab<__m256i, vinsertf128<1> > {};
        template <>
        struct perm2_v4u64< 4, 5, 2, 3>
            : public vperm2f128<2, 1> {};
        template <>
        struct perm2_v4u64< 6, 7, 0, 1>
            : public vperm2f128<3, 0> {};
        template <>
        struct perm2_v4u64< 6, 7, 2, 3>
            : public vperm2f128<3, 1> {};

        // generic permutation of one u32 vector
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm1_v8u32 {
            static __m256i v(__m256i a);
        };

        // generic permutation of two u32 vectors
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm2_v8u32 {
            static __m256i v(__m256i a, __m256i b);
        };

        // perm1_v8u32 specializations
        template <>
        struct perm1_v8u32<-1, -1, -1, -1, -1, -1, -1, -1>
            : public make_zero_int256 {};
        template <>
        struct perm1_v8u32<0, 1, 2, 3, 4, 5, 6, 7>
            : public select_arg_1<__m256i> {};

        template <>
        struct perm1_v8u32<0, 0, 0, 0, 0, 0, 0, 0>
            : public vbroadcastd<__m256i> {};

        template <>
        struct perm1_v8u32<-1, 0, 1, 2,-1, 4, 5, 6>
        : public vpslldq<4> {};
        template <>
        struct perm1_v8u32<-1,-1, 0, 1,-1,-1, 4, 5> :
            public vpslldq<8> {};
        template <>
        struct perm1_v8u32<-1,-1,-1, 0,-1,-1,-1, 4> :
            public vpslldq<12> {};

        template <>
        struct perm1_v8u32< 1, 2, 3,-1, 5, 6, 7,-1>
            : public vpsrldq<4> {};
        template <>
        struct perm1_v8u32< 2, 3,-1,-1, 6, 7,-1,-1>
            : public vpsrldq<8> {};
        template <>
        struct perm1_v8u32< 3,-1,-1,-1, 7,-1,-1,-1>
            : public vpsrldq<12> {};

        template <>
        struct perm1_v8u32<0, 1, 0, 1, 4, 5, 4, 5>
            : public vpunpcklqdq {};

        template <>
        struct perm1_v8u32<2, 3, 2, 3, 6, 7, 6, 7>
            : public vpunpckhqdq {};

        template <>
        struct perm1_v8u32<0, -1, 1, -1, 2, -1, 3, -1>
            : public vpmovzxdq {};

        template <>
        struct perm1_v8u32<0, 1, 2, 3,  0, 1, 2, 3>
            : public vinsertf128<1> {};

        // perm2_v8u32 specialisations
        template <>
        struct perm2_v8u32<0, 1, 8, 9, 4, 5, 12, 13>
            : public vpunpcklqdq {};

        template <>
        struct perm2_v8u32<8, 9, 0, 1, 12, 13, 4, 5>
            : public swap_ab<__m256i, vpunpcklqdq> {};

        template <>
        struct perm2_v8u32<2, 3, 10, 11, 6, 7, 14, 15>
            : public vpunpckhqdq {};

        template <>
        struct perm2_v8u32<10, 11, 2, 3, 14, 15, 6, 7>
            : public swap_ab<__m256i, vpunpckhqdq> {};

        template <>
        struct perm2_v8u32<0, 8, 1, 9, 4, 12, 5, 13>
            : public vpunpckldq {};

        template <>
        struct perm2_v8u32<8, 0, 9, 1, 12, 4, 13, 5>
            : public swap_ab<__m256i, vpunpckldq> {};

        template <>
        struct perm2_v8u32<2, 10, 3, 11, 6, 14, 7, 15>
            : public vpunpckhdq {};

        template <>
        struct perm2_v8u32<10, 2, 11, 3, 14, 6, 15, 7>
            : public swap_ab<__m256i, vpunpckhdq> {};

        template <>
        struct perm2_v8u32<0, 1, 2, 3, 8, 9, 10, 11>
            : public vinsertf128<1> {};

        template <>
        struct perm2_v8u32<0, 1, 2, 3, 12, 13, 14, 15>
            : public vperm2f128<0, 3> {};

        template <>
        struct perm2_v8u32<4, 5, 6, 7, 8, 9, 10, 11>
            : public vperm2f128<1, 2> {};

        template <>
        struct perm2_v8u32<4, 5, 6, 7, 12, 13, 14, 15>
            : public vperm2f128<1, 3> {};

        // generic permutation of one v32u8 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15,
                  int _P16, int _P17, int _P18, int _P19,
                  int _P20, int _P21, int _P22, int _P23,
                  int _P24, int _P25, int _P26, int _P27,
                  int _P28, int _P29, int _P30, int _P31>
        struct perm1_v32u8 {
            static __m256i v(__m256i a);
        };

        // generic permutation of two v32u8 vectors
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15,
                  int _P16, int _P17, int _P18, int _P19,
                  int _P20, int _P21, int _P22, int _P23,
                  int _P24, int _P25, int _P26, int _P27,
                  int _P28, int _P29, int _P30, int _P31>
        struct perm2_v32u8 {
            static __m256i v(__m256i a, __m256i b);
        };

        // specializations of perm1_v32u8
        template <>
        struct perm1_v32u8<-1, -1, -1, -1, -1, -1, -1, -1,
                           -1, -1, -1, -1, -1, -1, -1, -1,
                           -1, -1, -1, -1, -1, -1, -1, -1,
                           -1, -1, -1, -1, -1, -1, -1, -1>
            : public make_zero_int256 {};
        template <>
        struct perm1_v32u8< 0,  1,  2,  3,  4,  5,  6,  7,
                            8,  9, 10, 11, 12, 13, 14, 15,
                           16, 17, 18, 19, 20, 21, 22, 23,
                           24, 25, 26, 27, 28, 29, 30, 31>
            : public select_arg_1<__m256i> {};
        template <>
        struct perm1_v32u8< 0,  0,  1,  1,  2,  2,  3,  3,
                            4,  4,  5,  5,  6,  6,  7,  7,
                           16, 16, 17, 17, 18, 18, 19, 19,
                           20, 20, 21, 21, 22, 22, 23, 23>
            : public vpunpcklbw {};
        template <>
        struct perm1_v32u8< 8,  8,  9,  9, 10, 10, 11, 11,
                           12, 12, 13, 13, 14, 14, 15, 15,
                           24, 24, 25, 25, 26, 26, 27, 27,
                           28, 28, 29, 29, 30, 30, 31, 31>
            : public vpunpckhbw {};
        template <>
        struct perm1_v32u8< 0, -1,  1, -1,  2, -1,  3, -1,
                            4, -1,  5, -1,  6, -1,  7, -1,
                            8, -1,  9, -1, 10, -1, 11, -1,
                           12, -1, 13, -1, 14, -1, 15, -1>
            : public vpmovzxbw {};
        template <>
        struct perm1_v32u8< 0,  1, -1, -1,  2,  3, -1, -1,
                            4,  5, -1, -1,  6,  7, -1, -1,
                            8,  9, -1, -1, 10, 11, -1, -1,
                           12, 13, -1, -1, 14, 15, -1, -1>
            : public vpmovzxwd {};

        // specializations of perm2_v32u8
        template <>
        struct perm2_v32u8< 0, 32,  1, 33,  2, 34,  3, 35,
                            4, 36,  5, 37,  6, 38,  7, 39,
                           16, 48, 17, 49, 18, 50, 19, 51,
                           20, 52, 21, 53, 22, 54, 23, 55>
            : public vpunpcklbw {};
        template <>
        struct perm1_v32u8<32,  0, 33,  1, 34,  2, 35,  3,
                           36,  4, 37,  5, 38,  6, 39,  7,
                           48, 16, 49, 17, 50, 18, 51, 19,
                           52, 20, 53, 21, 54, 22, 55, 23>
            : public swap_ab<__m256i, vpunpcklbw> {};
        template <>
        struct perm2_v32u8< 8, 40,  9, 41, 10, 42, 11, 43,
                           12, 44, 13, 45, 14, 46, 15, 47,
                           24, 56, 25, 57, 26, 58, 27, 59,
                           28, 60, 29, 61, 30, 62, 31, 63>
            : public vpunpckhbw {};
        template <>
        struct perm2_v32u8<40,  8, 41,  9, 42, 10, 43, 11,
                           44, 12, 45, 13, 46, 14, 47, 15,
                           56, 24, 57, 25, 58, 26, 59, 27,
                           60, 28, 61, 29, 62, 30, 63, 31>
            : public swap_ab<__m256i, vpunpckhbw> {};

        template <>
        struct perm2_v32u8< 0,  1, 32, 33,  2,  3, 34, 35,
                            4,  5, 36, 37,  6,  7, 38, 39,
                           16, 17, 48, 49, 18, 19, 50, 51,
                           20, 21, 52, 53, 22, 23, 54, 55>
            : public vpunpcklwd {};

        template <>
        struct perm2_v32u8<32, 33,  0,  1, 34, 35,  2,  3,
                           36, 37,  4,  5, 38, 39,  6,  7,
                           48, 49, 16, 17, 50, 51, 18, 19,
                           52, 53, 20, 21, 54, 55, 22, 23>
            : public swap_ab<__m256i, vpunpcklwd> {};

        template <>
        struct perm2_v32u8< 8,  9, 40, 41, 10, 11, 42, 43,
                           12, 13, 44, 45, 14, 15, 46, 47,
                           24, 25, 56, 57, 26, 27, 58, 59,
                           28, 29, 60, 61, 30, 31, 62, 63>
            : public vpunpckhwd {};

        template <>
        struct perm2_v32u8<40, 41,  8,  9, 42, 43, 10, 11,
                           44, 45, 12, 13, 46, 47, 14, 15,
                           56, 57, 24, 25, 58, 59, 26, 27,
                           60, 61, 28, 29, 62, 63, 30, 31>
            : public swap_ab<__m256i, vpunpckhwd> {};
#endif // __AVX2__

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        // generic permutation of one v8f64 vector
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm1_v8f64 {
            static __m512d v(__m512d a);
        };

        // generic permutation of two v8f64 vectors
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm2_v8f64 {
            static __m512d v(__m512d a, __m512d b);
        };

        // generic permutation of one v16u32 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        struct perm1_v16f32 {
            static __m512 v(__m512 a);
        };

        // generic permutation of two v16u32 vectors
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        struct perm2_v16f32 {
            static __m512 v(__m512 a, __m512 b);
        };

        // generic permutation of one v16u32 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        struct perm1_v16u32 {
            static __m512i v(__m512i a);
        };

        // generic permutation of two v16u32 vectors
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        struct perm2_v16u32 {
            static __m512i v(__m512i a, __m512i b);
        };

        // generic permutation of one v8u64 vector
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm1_v8u64 {
            static __m512i v(__m512i a);
        };

        // generic permutation of two v8u64 vectors
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        struct perm2_v8u64 {
            static __m512i v(__m512i a, __m512i b);
        };

#endif


        template <int _P0, int _P1>
        __m128d perm_v2f64(__m128d a);
        template <int _P0, int _P1>
        __m128d perm_v2f64(__m128d a, __m128d b);

        template <int _P0, int _P1, int _P2, int _P3>
        __m128 perm_v4f32(__m128 a);
        template <int _P0, int _P1, int _P2, int _P3>
        __m128 perm_v4f32(__m128 a, __m128 b);

        template <int _P0, int _P1, int _P2, int _P3>
        __m128i perm_v4u32(__m128i a);
        template <int _P0, int _P1, int _P2, int _P3>
        __m128i perm_v4u32(__m128i a, __m128i b);

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m128i perm_v8u16(__m128i a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m128i perm_v8u16(__m128i a, __m128i b);

        template <int _P0, int _P1>
        __m128i perm_v2u64(__m128i a);
        template <int _P0, int _P1>
        __m128i perm_v2u64(__m128i a, __m128i b);

#if defined (__AVX__)
        template <int _P0, int _P1, int _P2, int _P3>
        __m256d perm_v4f64(__m256d a);
        template <int _P0, int _P1, int _P2, int _P3>
        __m256d perm_v4f64(__m256d a, __m256d b);

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m256 perm_v8f32(__m256 a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m256 perm_v8f32(__m256 a, __m256 b);
#endif
#if defined (__AVX2__)
        template <int _P0, int _P1, int _P2, int _P3>
        __m256i perm_v4u64(__m256i a);
        template <int _P0, int _P1, int _P2, int _P3>
        __m256i perm_v4u64(__m256i a, __m256i b);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m256i perm_v8u32(__m256i a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m256i perm_v8u32(__m256i a, __m256i b);

        // generic permutation of one v16u16 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m256i perm_v16u16(__m256i a);

        // generic permutation of one v16u16 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m256i perm_v16u16(__m256i a, __m256i b);

#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m512 perm_v16f32(__m512 a);
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m512 perm_v16f32(__m512 a, __m512 b);

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m512d perm_v8f64(__m512d a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m512d perm_v8f64(__m512d a, __m512d b);

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m512i perm_v8u64(__m512i a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m512i perm_v8u64(__m512i a, __m512i b);

        // generic permutation of one v16u32 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m512i perm_v16u32(__m512i a);

        // generic permutation of one v16u32 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m512i perm_v16u32(__m512i a, __m512i b);
#endif

        // generic permutation of one v16u8 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m128i perm_v16u8(__m128i a);

        // generic permutation of one v16u8 vector
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15>
        __m128i perm_v16u8(__m128i a, __m128i b);

#if defined (__AVX2__)
        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15,
                  int _P16, int _P17, int _P18, int _P19,
                  int _P20, int _P21, int _P22, int _P23,
                  int _P24, int _P25, int _P26, int _P27,
                  int _P28, int _P29, int _P30, int _P31>
        __m256i perm_v32u8(__m256i a);

        template <int _P00, int _P01, int _P02, int _P03,
                  int _P04, int _P05, int _P06, int _P07,
                  int _P08, int _P09, int _P10, int _P11,
                  int _P12, int _P13, int _P14, int _P15,
                  int _P16, int _P17, int _P18, int _P19,
                  int _P20, int _P21, int _P22, int _P23,
                  int _P24, int _P25, int _P26, int _P27,
                  int _P28, int _P29, int _P30, int _P31>
        __m256i perm_v32u8(__m256i a, __m256i b);
#endif


    }
}

// permute s8/u8 using s8 indices
inline
__m128i
cftal::x86::permute_v16u8_v16s8(__m128i s, __m128i idx)
{
    return vpshufb::v(s, idx);
}

inline
__m128i
cftal::x86::permute_v16u8_v16s8(__m128i l, __m128i h, __m128i idx)
{
#if defined (__AVX512VL__) && defined (__AVX512BW__)
    const __m128i zero=_mm_setzero_si128();
    __mmask16 rm=_mm_cmpge_epi8_mask(idx, zero);
    return _mm_maskz_permutex2var_epi8(rm, l, idx, h);
#else
    // set idxgt15 to -1 where idx > 15
    __m128i idxgt15=_mm_cmpgt_epi8(idx, _mm_set1_epi8(15));
    // idx < 16 --> 16 > idx
    __m128i idxlt16=_mm_cmpgt_epi8(_mm_set1_epi8(16), idx);
    // and or in theses -1 into idx
    __m128i idxl= _mm_or_si128(idx, idxgt15);
    // pshufb uses only 4 bits, therefore it is ok not to subtract 16 from
    // idx for idxh
    __m128i idxh= _mm_or_si128(idx, idxlt16);
    __m128i rl=vpshufb::v(l, idxl);
    __m128i rh=vpshufb::v(h, idxh);
    return _mm_or_si128(rl, rh);
#endif
}

// permute s16/u16 using s16 indices
inline
__m128i
cftal::x86::permute_v8u16_v8s16(__m128i s, __m128i idx)
{
#if defined (__AVX512VL__) && defined (__AVX512BW__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi16_mask(idx, zero);
    return _mm_maskz_permutexvar_epi16(rm, idx, s);
#else
    // multiply mask by two, shuffle it to low/high bytes
    // and add 1 to the high bytes
    __m128i m=vpsllw_const<1>::v(idx);
    const __m128i& p=const_v16u8< 0,  0,  2,  2,  4,  4,  6,  6,
                                  8,  8, 10, 10, 12, 12, 14, 14>::iv();
    const __m128i& o=const_v16u8< 0,  1,  0,  1,  0,  1,  0,  1,
                                  0,  1,  0,  1,  0,  1,  0,  1>::iv();
    m=vpshufb::v(m, p);
    m=_mm_add_epi8(m, o);
    return permute_v16u8_v16s8(s, m);
#endif
}

inline
__m128i
cftal::x86::permute_v8u16_v8s16(__m128i l, __m128i h, __m128i idx)
{
#if defined (__AVX512VL__) && defined (__AVX512BW__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi8_mask(idx, zero);
    return _mm_maskz_permutex2var_epi16(rm, l, idx, h);
#else
    // multiply mask by two, shuffle it to low/high bytes
    // and add 1 to the high bytes
    __m128i m=vpsllw_const<1>::v(idx);
    const __m128i& p=const_v16u8< 0,  0,  2,  2,  4,  4,  6,  6,
                                  8,  8, 10, 10, 12, 12, 14, 14>::iv();
    const __m128i& o=const_v16u8< 0,  1,  0,  1,  0,  1,  0,  1,
                                  0,  1,  0,  1,  0,  1,  0,  1>::iv();
    m=vpshufb::v(m, p);
    m=_mm_add_epi8(m, o);
    return permute_v16u8_v16s8(l, h, m);
#endif
}

// permute s32/u32 using s32 indices
inline
__m128i
cftal::x86::permute_v4u32_v4s32(__m128i s, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi32_mask(idx, zero);
    return _mm_castps_si128(
        _mm_maskz_permutevar_ps(rm, _mm_castsi128_ps(s), idx));
#elif defined (__AVX__)
    __m128i r=_mm_castps_si128(
        _mm_permutevar_ps(_mm_castsi128_ps(s), idx));
    __m128i z_e=_mm_srai_epi32(idx, 31);
    r = _mm_andnot_si128(z_e, r);
    return r;
#else
    // multiply mask by 4, shuffle it to dwords
    // and add 0, 1, 2, 3 to the bytes.
    __m128i m=vpslld_const<2>::v(idx);
    const __m128i& p=const_v16u8< 0,  0,  0,  0,  4,  4,  4,  4,
                                  8,  8,  8,  8, 12, 12, 12, 12>::iv();
    const __m128i& o=const_v16u8< 0,  1,  2,  3,  0,  1,  2,  3,
                                  0,  1,  2,  3,  0,  1,  2,  3>::iv();
    m=vpshufb::v(m, p);
    m=_mm_add_epi8(m, o);
    return permute_v16u8_v16s8(s, m);
#endif
}

// permute s32/u32 using s32 indices
inline
__m128i
cftal::x86::permute_v4u32_v4s32(__m128i l, __m128i h, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi32_mask(idx, zero);
    return _mm_maskz_permutex2var_epi32(rm, l, idx, h);
#elif defined (__AVX__)
    __m128i rl=_mm_castps_si128(
        _mm_permutevar_ps(_mm_castsi128_ps(l), idx));
    __m128i rh=_mm_castps_si128(
        _mm_permutevar_ps(_mm_castsi128_ps(h), idx));
    __m128i idx_lt_z=_mm_srai_epi32(idx, 31);
    __m128i idx_lt_4=_mm_cmpgt_epi32(_mm_set1_epi32(4), idx);
    rl=_mm_and_si128(idx_lt_4, rl);
    rh=_mm_andnot_si128(idx_lt_4, rh);
    __m128i r=_mm_or_si128(rl, rh);
    return _mm_andnot_si128(idx_lt_z, r);
#else
    // multiply mask by 4, shuffle it to dwords
    // and add 0, 1, 2, 3 to the bytes.
    __m128i m=vpslld_const<2>::v(idx);
    const __m128i& p=const_v16u8< 0,  0,  0,  0,  4,  4,  4,  4,
                                  8,  8,  8,  8, 12, 12, 12, 12>::iv();
    const __m128i& o=const_v16u8< 0,  1,  2,  3,  0,  1,  2,  3,
                                  0,  1,  2,  3,  0,  1,  2,  3>::iv();
    m=vpshufb::v(m, p);
    m=_mm_add_epi8(m, o);
    return permute_v16u8_v16s8(l, h, m);
#endif
}


// permute s64/u64 using s64 indices
inline
__m128i
cftal::x86::permute_v2u64_v2s64(__m128i s, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi64_mask(idx, zero);
    return _mm_castpd_si128(
        _mm_maskz_permutevar_pd(rm, _mm_castsi128_pd(s), idx));
#elif defined (__AVX__)
    __m128i r=_mm_castpd_si128(
        _mm_permutevar_pd(_mm_castsi128_pd(s), _mm_add_epi64(idx, idx)));
    __m128i neg=_mm_cmpgt_epi64(_mm_setzero_si128(), idx);
    r = _mm_andnot_si128(neg, r);
    return r;
#else
    // multiply mask by 8, shuffle it to qwords
    // and add 0, 1, 2, 3, 4, 5, 6, 7 to the bytes.
    __m128i m=vpsllq_const<3>::v(idx);
    const __m128i& p=const_v16u8< 0,  0,  0,  0,  0,  0,  0,  0,
                                  8,  8,  8,  8,  8,  8,  8,  8>::iv();
    const __m128i& o=const_v16u8< 0,  1,  2,  3,  4,  5,  6,  7,
                                  0,  1,  2,  3,  4,  5,  6,  7>::iv();
    m=vpshufb::v(m, p);
    m=_mm_add_epi8(m, o);
    return permute_v16u8_v16s8(s, m);
#endif
}

inline
__m128i
cftal::x86::permute_v2u64_v2s64(__m128i l, __m128i h, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi64_mask(idx, zero);
    return _mm_maskz_permutex2var_epi64(rm, l, idx, h);
#elif defined (__AVX__)
    __m128i idx64=_mm_add_epi64(idx, idx);
    __m128i rl=_mm_castpd_si128(
        _mm_permutevar_pd(_mm_castsi128_pd(l), idx64));
    __m128i rh=_mm_castpd_si128(
        _mm_permutevar_pd(_mm_castsi128_pd(h), idx64));
    __m128i idx_lt_z=_mm_cmpgt_epi64(_mm_setzero_si128(), idx);
    __m128i idx_lt_2=_mm_cmpgt_epi64(_mm_set1_epi64x(2), idx);
    rl = _mm_and_si128(idx_lt_2, rl);
    rh = _mm_andnot_si128(idx_lt_2, rh);
    __m128i r= _mm_or_si128(rl, rh);
    return _mm_andnot_si128(idx_lt_z, r);
#else
    // multiply mask by 8, shuffle it to qwords
    // and add 0, 1, 2, 3, 4, 5, 6, 7 to the bytes.
    __m128i m=vpsllq_const<3>::v(idx);
    const __m128i& p=const_v16u8< 0,  0,  0,  0,  0,  0,  0,  0,
                                  8,  8,  8,  8,  8,  8,  8,  8>::iv();
    const __m128i& o=const_v16u8< 0,  1,  2,  3,  4,  5,  6,  7,
                                  0,  1,  2,  3,  4,  5,  6,  7>::iv();
    m=vpshufb::v(m, p);
    m=_mm_add_epi8(m, o);
    return permute_v16u8_v16s8(l, h, m);
#endif
}

// permute f32 using s32 indices
inline
__m128
cftal::x86::permute_v4f32_v4s32(__m128 s, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi32_mask(idx, zero);
    return _mm_maskz_permutevar_ps(rm, s, idx);
#elif defined (__AVX__)
    __m128 r=_mm_permutevar_ps(s, idx);
    __m128i z_e=_mm_srai_epi32(idx, 31);
    r = _mm_castsi128_ps(_mm_andnot_si128(z_e, _mm_castps_si128(r)));
    return r;
#else
    return _mm_castsi128_ps(
        permute_v4u32_v4s32(_mm_castps_si128(s), idx));
#endif
}

inline
__m128
cftal::x86::permute_v4f32_v4s32(__m128 l, __m128 h, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi32_mask(idx, zero);
    return _mm_maskz_permutex2var_ps(rm, l, idx, h);
#elif defined (__AVX__)
    __m128 rl=_mm_permutevar_ps(l, idx);
    __m128 rh=_mm_permutevar_ps(l, idx);
    __m128i idx_lt_z=_mm_srai_epi32(idx, 31);
    __m128i idx_lt_4=_mm_cmpgt_epi32(_mm_set1_epi32(4), idx);
    rl = _mm_and_ps(_mm_castsi128_ps(idx_lt_4), rl);
    rh = _mm_andnot_ps(_mm_castsi128_ps(idx_lt_4), rh);
    __m128 r=_mm_or_ps(rl, rh);
    return _mm_andnot_ps(_mm_castsi128_ps(idx_lt_z), r);
#else
    return _mm_castsi128_ps(
        permute_v4u32_v4s32(_mm_castps_si128(s), idx));
#endif
}

// permute f64 using s64 indices
inline
__m128d
cftal::x86::permute_v2f64_v2s64(__m128d s, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi64_mask(idx, zero);
    return _mm_maskz_permutevar_pd(rm, s, idx);
#elif defined (__AVX__)
    __m128d r=_mm_permutevar_pd(s, _mm_add_epi64(idx, idx));
    __m128i neg=_mm_cmpgt_epi64(_mm_setzero_si128(), idx);
    r = _mm_castsi128_pd(_mm_andnot_si128(neg, _mm_castpd_si128(r)));
    return r;
#else
    return _mm_castsi128_pd(
        permute_v2u64_v2s64(_mm_castpd_si128(s), idx));
#endif
}

inline
__m128d
cftal::x86::permute_v2f64_v2s64(__m128d l, __m128d h, __m128i idx)
{
#if defined (__AVX512VL__)
    const __m128i zero=_mm_setzero_si128();
    __mmask8 rm=_mm_cmpge_epi64_mask(idx, zero);
    return _mm_maskz_permutex2var_pd(rm, l, idx, h);
#elif defined (__AVX__)
    __m128i idx64=_mm_add_epi64(idx, idx);
    __m128d rl=_mm_permutevar_pd(l, idx64);
    __m128d rh=_mm_permutevar_pd(h, idx64);
    __m128i idx_lt_z=_mm_cmpgt_epi64(_mm_setzero_si128(), idx);
    __m128i idx_lt_2=_mm_cmpgt_epi64(_mm_set1_epi64x(2), idx);
    rl = _mm_and_pd(_mm_castsi128_pd(idx_lt_2), rl);
    rh = _mm_andnot_pd(_mm_castsi128_pd(idx_lt_2), rh);
    __m128d r= _mm_or_pd(rl, rh);
    return _mm_andnot_pd(_mm_castsi128_pd(idx_lt_z), r);
#else
    return _mm_castsi128_pd(
        permute_v2u64_v2s64(_mm_castpd_si128(s), idx));
#endif
}

#if defined (__AVX2__)
// permute s32/u32 using s32 indices
inline
__m256i
cftal::x86::permute_v8u32_v8s32(__m256i s, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi32_mask(idx, zero);
    return _mm256_maskz_permutexvar_epi32(rm, idx, s);
#else
    __m256i r=_mm256_permutevar8x32_epi32(s, idx);
    __m256i z_e=_mm256_srai_epi32(idx, 31);
    r = _mm256_andnot_si256(z_e, r);
    return r;
#endif
}

inline
__m256i
cftal::x86::permute_v8u32_v8s32(__m256i l, __m256i h, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi32_mask(idx, zero);
    return _mm256_maskz_permutex2var_epi32(rm, l, idx, h);
#else
    __m256i rl=_mm256_permutevar8x32_epi32(l, idx);
    __m256i rh=_mm256_permutevar8x32_epi32(h, idx);
    __m256i idx_lt_z=_mm256_srai_epi32(idx, 31);
    __m256i idx_lt_8=_mm256_cmpgt_epi32(_mm256_set1_epi32(8), idx);
    rl=_mm256_and_si256(idx_lt_8, rl);
    rh=_mm256_andnot_si256(idx_lt_8, rh);
    __m256i r=_mm256_or_si256(rl, rh);
    return _mm256_andnot_si256(idx_lt_z, r);
#endif
}

// permute s64/u64 using s64 indices
inline
__m256i
cftal::x86::permute_v4u64_v4s64(__m256i s, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi64_mask(idx, zero);
    return _mm256_maskz_permutexvar_epi64(rm, idx, s);
#else
    __m256i idx32=perm1_v8u32<0, 0, 2, 2, 4, 4, 6, 6>::v(
        _mm256_add_epi64(idx, idx));
    const __m256i& idxc=const_v8u32<0, 1, 0, 1, 0, 1, 0, 1>::iv();
    idx32 = _mm256_add_epi32(idx32, idxc);
    return permute_v8u32_v8s32(s, idx32);
#endif
}

inline
__m256i
cftal::x86::permute_v4u64_v4s64(__m256i l, __m256i h, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi64_mask(idx, zero);
    return _mm256_maskz_permutex2var_epi64(rm, l, idx, h);
#else
    __m256i idx32=perm1_v8u32<0, 0, 2, 2, 4, 4, 6, 6>::v(
        _mm256_add_epi64(idx, idx));
    const __m256i& idxc=const_v8u32<0, 1, 0, 1, 0, 1, 0, 1>::iv();
    idx32 = _mm256_add_epi32(idx32, idxc);
    return permute_v8u32_v8s32(l, h, idx32);
#endif
}

// permute f32 using s32 indices
inline
__m256
cftal::x86::permute_v8f32_v8s32(__m256 s, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi32_mask(idx, zero);
    return _mm256_maskz_permutexvar_ps(rm, idx, s);
#else
    __m256 r=_mm256_permutevar8x32_ps(s, idx);
    __m256i z_e=_mm256_srai_epi32(idx, 31);
    r = _mm256_castsi256_ps(_mm256_andnot_si256(z_e, _mm256_castps_si256(r)));
    return r;
#endif
}

inline
__m256
cftal::x86::permute_v8f32_v8s32(__m256 l, __m256 h, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi32_mask(idx, zero);
    return _mm256_maskz_permutex2var_ps(rm, l, idx, h);
#else
    return _mm256_castsi256_ps(permute_v8u32_v8s32(
        _mm256_castps_si256(l), _mm256_castps_si256(h), idx));
#endif
}

// permute f64 using s64 indices
inline
__m256d
cftal::x86::permute_v4f64_v4s64(__m256d s, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi64_mask(idx, zero);
    return _mm256_maskz_permutexvar_pd(rm, idx, s);
#else
    return _mm256_castsi256_pd(permute_v4u64_v4s64(
        _mm256_castpd_si256(s), idx));
#endif
}

inline
__m256d
cftal::x86::permute_v4f64_v4s64(__m256d l, __m256d h, __m256i idx)
{
#if defined (__AVX512VL__)
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi64_mask(idx, zero);
    return _mm256_maskz_permutex2var_pd(rm, l, idx, h);
#else
    return _mm256_castsi256_pd(permute_v4u64_v4s64(
        _mm256_castpd_si256(l), _mm256_castpd_si256(h), idx));
#endif
}

// return odd elements
inline
__m128i
cftal::x86::odd_elements_v16u16(__m256i s)
{
#if defined (__AVX512VL__) && defined (__AVX512BW__)
    const __m256i idx=const_v16u16<1, 3, 5, 7, 9, 11, 13, 15,
                                   0, 0, 0, 0, 0,  0,  0,  0>::iv();
    return _mm256_castsi256_si128(_mm256_permutexvar_epi16(idx, s));
#else
    // 1 3 5 7 --> 2 6 10 14
    const __m256i& p=const_v32u8< 2,  3,  6,  7,  10,  11, 14, 15,
                                  0,  0,  0,  0,   0,   0,  0,  0,
                                  2,  3,  6,  7,  10,  11, 14, 15,
                                  0,  0,  0,  0,   0,   0,  0,  0>::iv();
    __m256i r=vpshufb::v(s, p);
    r = perm1_v4u64<0, 2, 1, 3>::v(r);
    return _mm256_castsi256_si128(r);
#endif
}

// return even elements
inline
__m128i
cftal::x86::even_elements_v16u16(__m256i s)
{
#if defined (__AVX512VL__) && defined (__AVX512BW__)
    const __m256i idx=const_v16u16<0, 2, 4, 6, 8, 10, 12, 14,
                                   0, 0, 0, 0, 0,  0,  0,  0>::iv();
    return _mm256_castsi256_si128(_mm256_permutexvar_epi16(idx, s));
#else
    // 0 2 4 6 --> 0 4 8 12
    const __m256i& p=const_v32u8< 0,  1,  4,  5,  8,  9, 12, 13,
                                  0,  0,  0,  0,  0,  0,  0,  0,
                                  0,  1,  4,  5,  8,  9, 12, 13,
                                  0,  0,  0,  0,  0,  0,  0,  0>::iv();
    __m256i r=vpshufb::v(s, p);
    r = perm1_v4u64<0, 2, 1, 3>::v(r);
    return _mm256_castsi256_si128(r);
#endif
}

#endif

#if defined (__AVX512F__)
// permute s32/u32 using s32 indices
inline
__m512i
cftal::x86::permute_v16u32_v16s32(__m512i s, __m512i idx)
{
    const __m512i zero=_mm512_setzero_si512();
    __mmask16 rm=_mm512_cmpge_epi32_mask(idx, zero);
    return _mm512_maskz_permutexvar_epi32(rm, idx, s);
}

// permute s64/u64 using s64 indices
inline
__m512i
cftal::x86::permute_v8u64_v8s64(__m512i s, __m512i idx)
{
    const __m512i zero=_mm512_setzero_si512();
    __mmask8 rm=_mm512_cmpge_epi64_mask(idx, zero);
    return _mm512_maskz_permutexvar_epi64(rm, idx, s);
}

// permute f32 using s32 indices
inline
__m512
cftal::x86::permute_v16f32_v16s32(__m512 s, __m512i idx)
{
    const __m512i zero=_mm512_setzero_si512();
    __mmask16 rm=_mm512_cmpge_epi32_mask(idx, zero);
    return _mm512_maskz_permutexvar_ps(rm, idx, s);
}

// permute f64 using s64 indices
inline
__m512d
cftal::x86::permute_v8f64_v8s64(__m512d s, __m512i idx)
{
    const __m512i zero=_mm512_setzero_si512();
    __mmask8 rm=_mm512_cmpge_epi64_mask(idx, zero);
    return _mm512_maskz_permutexvar_pd(rm, idx, s);
}

#endif

#if defined (__AVX512BW__)
#if defined (__AVX512VL__)
// permute s16/u16 using s16 indices
inline
__m256i
cftal::x86::permute_v16u16_v16s16(__m256i s, __m256i idx)
{
    const __m256i zero=_mm256_setzero_si256();
    __mmask8 rm=_mm256_cmpge_epi16_mask(idx, zero);
    return _mm256_maskz_permutexvar_epi16(rm, idx, s);
}
#endif

// permute s16/u16 using s16 indices
inline
__m512i
cftal::x86::permute_v32u16_v32s16(__m512i s, __m512i idx)
{
    const __m512i zero=_mm512_setzero_si512();
    __mmask16 rm=_mm512_cmpge_epi16_mask(idx, zero);
    return _mm512_maskz_permutexvar_epi16(rm, idx, s);
}

#if defined (__AVX512VL__)
inline
__m256i
cftal::x86::odd_elements_v32u16(__m512i s)
{
    const __m512i idx=const_v32u16< 1,  3,  5,  7,  9, 11, 13, 15,
                                   17, 19, 21, 23, 25, 27, 29, 31,
                                    0,  0,  0,  0,  0,  0,  0,  0,
                                    0,  0,  0,  0,  0,  0,  0,  0>::iv();
    return _mm512_castsi512_si256(_mm512_permutexvar_epi16(idx, s));
}

// return even elements
inline
__m256i
cftal::x86::even_elements_v32u16(__m512i s)
{
    const __m512i idx=const_v32u16< 0,  2,  4,  6,  8, 10, 12, 14,
                                   16, 18, 20, 22, 24, 26, 28, 30,
                                    0,  0,  0,  0,  0,  0,  0,  0,
                                    0,  0,  0,  0,  0,  0,  0,  0>::iv();
    return _mm512_castsi512_si256(_mm512_permutexvar_epi16(idx, s));
}
#endif
#endif



template <int _P0, int _P1>
inline
__m128d cftal::x86::perm1_v2f64<_P0, _P1>::v(__m128d a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int m1 = pos_msk_2<_P0, _P1, 1>::m;
    const int m2 = zero_msk_2<_P0, _P1>::m;
    // is shuffling needed
    const bool do_shuffle= ((m1 ^ 0x10) & m2) !=0;
    // is zeroing needed
    const bool do_zero= ((m2 & 0xFF) != 0xFF);

    if (do_zero && !do_shuffle) {
        // zeroing, not shuffling
        if ((_P0 & _P1) < 0)  {
            // zero everything
            return make_zero_v2f64::v();
        }
        // zero some elements
        const __m128d msk= const_v4u32<
            (_P0<0 ? 0 : uint32_t(-1)),
            (_P0<0 ? 0 : uint32_t(-1)),
            (_P1<0 ? 0 : uint32_t(-1)),
            (_P1<0 ? 0 : uint32_t(-1))>::dv();
        return _mm_and_pd(a, msk);
    }

    if (do_shuffle && !do_zero) {
        // shuffling, not zeroing
        return vshufpd<uint32_t(_P0), uint32_t(_P1)>::v(a);
    }
    if (do_shuffle && do_zero) {
        // shuffling and zeroing
        const __m128d zero= _mm_setzero_pd();
        // both shuffle and zero
        if (_P0 < 0 && _P1 >= 0) {
            // zero low half, shuffle high half
            return vshufpd<0, uint32_t(_P1)>::v(zero, a);
        }
        if (_P0 >= 0 && _P1 < 0) {
            // shuffle low half, zero high half
            return vshufpd<uint32_t(_P1), 0>::v(a, zero);
        }
    }
    // trivial case: do n
    return a;
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1>
inline
__m128d cftal::x86::perm2_v2f64<_P0, _P1>::v(__m128d a, __m128d b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const int m1 = pos_msk_2<_P0, _P1, 3>::m;
    // Mask to zero out negative indexes
    const int m2 = zero_msk_2<_P0, _P1>::m;
    if ((m1 & 0x022 & m2) == 0) {
        // no elements from b, only elements from a and
        // possibly zero
        return perm1_v2f64<_P0, _P1>::v (a);
    }
    if (((m1^0x0022) & 0x0022 & m2) == 0) {
        // no elements from a, only elements from b and
        // possibly zero
        return perm1_v2f64<_P0 & ~2, _P1 & ~2>::v(b);
    }
    // selecting from both a and b without zeroing
    if ((_P0 & 2) == 0) {
        // first element from a, second element from b
        return vshufpd<uint32_t(_P0), uint32_t(_P1)>::v(a, b);
    }
    // first element from b, second element from a
    return vshufpd<uint32_t(_P0), uint32_t(_P1)>::v(b, a);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m128 cftal::x86::perm1_v4f32<_P0, _P1, _P2, _P3>::v(__m128 a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 3>::m;
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    const bool do_shuffle = ((m1 ^ 0x3210) & m2) !=0;
    const bool do_zero =  ((m2 & 0xFFFF) != 0xFFFF);

    if (!do_shuffle && !do_zero) {
        // trivial case: do nothing
        return a;
    }
    if (do_zero && !do_shuffle) {
        // zeroing, not shuffling
        if (m2 == 0) {
            // zero everything
            return make_zero_v4f32::v();
        }
        // zero some elements
        const unsigned int z0 = (_P0 < 0) ? 0 : -1;
        const unsigned int z1 = (_P1 < 0) ? 0 : -1;
        const unsigned int z2 = (_P2 < 0) ? 0 : -1;
        const unsigned int z3 = (_P3 < 0) ? 0 : -1;
        const __m128 zm= const_v4u32<z0, z1, z2, z3>::fv();
        // zero with AND mask
        return  _mm_and_ps(a,zm);
    }

    if (do_shuffle && !do_zero) {
        // shuffling, not zeroing
        return vshufps<unsigned(_P0),
                       unsigned(_P1),
                       unsigned(_P2),
                       unsigned(_P3)>::v(a, a);
    }
    // both shuffle and zero
    if (m2 == 0xFF00) {
        // zero low half, shuffle high half
        return vshufps<0,
                       0,
                       unsigned(_P2),
                       unsigned(_P3)>::v(_mm_setzero_ps(), a);
    }
    if (m2 == 0x00FF) {
        // shuffle low half, zero high half
        return vshufps<unsigned(_P0),
                       unsigned(_P1),
                       0, 0>::v(a, _mm_setzero_ps());
    }
#ifdef __SSSE3__
    const uint8_t c00 = (_P0<0 ? -1 : 4*(_P0&3)+0);
    const uint8_t c01 = (_P0<0 ? -1 : 4*(_P0&3)+1);
    const uint8_t c02 = (_P0<0 ? -1 : 4*(_P0&3)+2);
    const uint8_t c03 = (_P0<0 ? -1 : 4*(_P0&3)+3);
    const uint8_t c04 = (_P1<0 ? -1 : 4*(_P1&3)+0);
    const uint8_t c05 = (_P1<0 ? -1 : 4*(_P1&3)+1);
    const uint8_t c06 = (_P1<0 ? -1 : 4*(_P1&3)+2);
    const uint8_t c07 = (_P1<0 ? -1 : 4*(_P1&3)+3);
    const uint8_t c08 = (_P2<0 ? -1 : 4*(_P2&3)+0);
    const uint8_t c09 = (_P2<0 ? -1 : 4*(_P2&3)+1);
    const uint8_t c10 = (_P2<0 ? -1 : 4*(_P2&3)+2);
    const uint8_t c11 = (_P2<0 ? -1 : 4*(_P2&3)+3);
    const uint8_t c12 = (_P3<0 ? -1 : 4*(_P3&3)+0);
    const uint8_t c13 = (_P3<0 ? -1 : 4*(_P3&3)+1);
    const uint8_t c14 = (_P3<0 ? -1 : 4*(_P3&3)+2);
    const uint8_t c15 = (_P3<0 ? -1 : 4*(_P3&3)+3);
    const __m128i msk=const_v16u8<c00, c01, c02, c03,
                                  c04, c05, c06, c07,
                                  c08, c09, c10, c11,
                                  c12, c13, c14, c15>::iv();
    return as<__m128>(_mm_shuffle_epi8(as<__m128i>(a),msk));
#else
    // shuffle
    __m128 t= vshufps<uint32_t(_P0), uint32_t(_P1),
                      uint32_t(_P2), uint32_t(_P3)>::v(a, a);
    // zero with AND mask
    const unsigned z0 = (_P0 < 0) ? 0 : -1;
    const unsigned z1 = (_P1 < 0) ? 0 : -1;
    const unsigned z2 = (_P2 < 0) ? 0 : -1;
    const unsigned z3 = (_P3 < 0) ? 0 : -1;
    const __m128 zm= const_v4u32<z0, z1, z2, z3>::fv();
    return  _mm_and_ps(t,zm);
#endif
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m128 cftal::x86::perm2_v4f32<_P0, _P1, _P2, _P3>::v(__m128 a, __m128 b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 7>::m;
    // Mask to zero out negative indexes
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    if ((m1 & 0x4444 & m2) == 0) {
        // no elements from b
        return perm1_v4f32<_P0,_P1,_P2,_P3>::v(a);
    }
    if (((m1^0x4444) & 0x4444 & m2) == 0) {
        // no elements from a
        return perm1_v4f32<_P0 & ~4, _P1 & ~4,
                           _P2 & ~4, _P3 &~4>::v(b);
    }

    const bool sm0 = _P0 < 4;
    const bool sm1 = _P1 < 4;
    const bool sm2 = _P2 < 4;
    const bool sm3 = _P3 < 4;

    const bool z0 = _P0 < 0;
    const bool z1 = _P1 < 0;
    const bool z2 = _P2 < 0;
    const bool z3 = _P3 < 0;

    if (((m1 & ~0x4444) ^ 0x3210) == 0 && m2 == 0xFFFF) {
        // selecting without shuffling or zeroing
        return select_v4f32<sm0, sm1, sm2, sm3>::v(a, b);
    }
    // Use AMD XOP instruction PPERM here later
    if ((((m1 & ~0x4444) ^ 0x3210) & m2) == 0) {
        // selecting and zeroing, not shuffling
        __m128 t = select_v4f32<sm0, sm1, sm2, sm3>::v(a, b);
        // zero
        const __m128 zm = const_v4u32<
            (z0 ? 0 : uint32_t(-1)),
            (z1 ? 0 : uint32_t(-1)),
            (z2 ? 0 : uint32_t(-1)),
            (z3 ? 0 : uint32_t(-1))>::fv();
        return  _mm_and_ps(t, zm);
    }
    if (((m1 & 0x4400)==0x4400) && ((m1 & 0x0044)==0x00)) {
        // lower half from a, higher half from b
        __m128 t = vshufps<uint32_t(_P0), uint32_t(_P1),
                           uint32_t(_P2), uint32_t(_P3)>::v(a, b);
        if ( m2 != 0xFFFF) {
            // zero
            const __m128 zm = const_v4u32<
                (z0 ? 0 : uint32_t(-1)),
                (z1 ? 0 : uint32_t(-1)),
                (z2 ? 0 : uint32_t(-1)),
                (z3 ? 0 : uint32_t(-1))>::fv();
            return  _mm_and_ps(t, zm);
        }
        return t;
    }
    if (((m1 & 0x4400)==0x0000) && ((m1 & 0x0044)==0x44)) {
        // lower half from b, higher half from a
        __m128 t=vshufps<uint32_t(_P0), uint32_t(_P1),
                         uint32_t(_P2), uint32_t(_P3)>::v(b, a);
        if ( m2 != 0xFFFF) {
            // zero
            const __m128 zm = const_v4u32<
                (z0 ? 0 : uint32_t(-1)),
                (z1 ? 0 : uint32_t(-1)),
                (z2 ? 0 : uint32_t(-1)),
                (z3 ? 0 : uint32_t(-1))>::fv();
            return  _mm_and_ps(t, zm);
        }
        return t;
    }
    // general case
    const int zz= m2 == 0xFFFF ? 0 : -1;
    // select all elements to clear or from 1st vector
    const int ma0 = sm0 ? _P0 : zz;
    const int ma1 = sm1 ? _P1 : zz;
    const int ma2 = sm2 ? _P2 : zz;
    const int ma3 = sm3 ? _P3 : zz;
    __m128 ta = perm1_v4f32<ma0, ma1, ma2, ma3>::v(a);
    // select all elements from second vector
    const int mb0 = sm0 ? 0 : (_P0-4);
    const int mb1 = sm1 ? 0 : (_P1-4);
    const int mb2 = sm2 ? 0 : (_P2-4);
    const int mb3 = sm3 ? 0 : (_P3-4);
    __m128 tb = perm1_v4f32<mb0, mb1, mb2, mb3>::v(b);
    return  select_v4f32<sm0, sm1, sm2, sm3>::v(ta, tb);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m128i cftal::x86::perm1_v4u32<_P0, _P1, _P2, _P3>::v(__m128i a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 3>::m;
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;
    const bool do_shuffle = ((m1 ^ 0x3210) & m2) !=0;
    const bool do_zero =  ((m2 & 0xFFFF) != 0xFFFF);
    if (!do_shuffle && !do_zero) {
        return a;
    }
    if (do_zero && !do_shuffle) {
        // zeroing, not shuffling
        if (m2 == 0) {
            // zero everything
            return make_zero_int::v();
        }
        // zero some elements
        const unsigned z0 = (_P0 < 0) ? 0 : -1;
        const unsigned z1 = (_P1 < 0) ? 0 : -1;
        const unsigned z2 = (_P2 < 0) ? 0 : -1;
        const unsigned z3 = (_P3 < 0) ? 0 : -1;
        const __m128i zm= const_v4u32<z0, z1, z2, z3>::iv();
        // zero with AND mask
        return  _mm_and_si128(a,zm);
    }
    if (do_shuffle && !do_zero) {
        // No zero, high elements kept in order, low elements
        // only from low half.
        if (((m1 & 0xFF00) == 0x3200) && ((m1 & 0x22)==0)) {
            const unsigned l0= 2*_P0+0;
            const unsigned l1= 2*_P0+1;
            const unsigned l2= 2*_P1+0;
            const unsigned l3= 2*_P1+1;
            return vpshuflw<l0, l1, l2, l3>::v(a);
        }
        // No zero, low elements kept in order, high elements
        // only from high half
        if (((m1 & 0xFF) == 0x10) && ((m1 & 0x2200)==0x2200)) {
            const unsigned h0= 2*(_P2-2) + 0;
            const unsigned h1= 2*(_P2-2) + 1;
            const unsigned h2= 2*(_P3-2) + 0;
            const unsigned h3= 2*(_P3-2) + 1;
            return vpshufhw<h0, h1, h2, h3>::v(a);
        }
        return vpshufd<uint32_t(_P0), uint32_t(_P1),
                       uint32_t(_P2), uint32_t(_P3)>::v(a);
    }
#if defined (__SSSE3__)
    //if (do_shuffle && do_zero) {
    const uint8_t c00 = (_P0<0 ? -1 : 4*(_P0&3)+0);
    const uint8_t c01 = (_P0<0 ? -1 : 4*(_P0&3)+1);
    const uint8_t c02 = (_P0<0 ? -1 : 4*(_P0&3)+2);
    const uint8_t c03 = (_P0<0 ? -1 : 4*(_P0&3)+3);
    const uint8_t c04 = (_P1<0 ? -1 : 4*(_P1&3)+0);
    const uint8_t c05 = (_P1<0 ? -1 : 4*(_P1&3)+1);
    const uint8_t c06 = (_P1<0 ? -1 : 4*(_P1&3)+2);
    const uint8_t c07 = (_P1<0 ? -1 : 4*(_P1&3)+3);
    const uint8_t c08 = (_P2<0 ? -1 : 4*(_P2&3)+0);
    const uint8_t c09 = (_P2<0 ? -1 : 4*(_P2&3)+1);
    const uint8_t c10 = (_P2<0 ? -1 : 4*(_P2&3)+2);
    const uint8_t c11 = (_P2<0 ? -1 : 4*(_P2&3)+3);
    const uint8_t c12 = (_P3<0 ? -1 : 4*(_P3&3)+0);
    const uint8_t c13 = (_P3<0 ? -1 : 4*(_P3&3)+1);
    const uint8_t c14 = (_P3<0 ? -1 : 4*(_P3&3)+2);
    const uint8_t c15 = (_P3<0 ? -1 : 4*(_P3&3)+3);
    const __m128i msk=const_v16u8<c00, c01, c02, c03,
                                  c04, c05, c06, c07,
                                  c08, c09, c10, c11,
                                  c12, c13, c14, c15>::iv();
    return _mm_shuffle_epi8(a, msk);
    // }
#else
    // both shuffle and zero
    if (m2 == 0xFF00) {
        // zero low half, shuffle high half
        return exec_f32<vshufps<0, 0, uint32_t(_P2), uint32_t(_P3)> >::
            v(make_zero_int::v(), a);
    }
    if (m2 == 0x00FF) {
        // shuffle low half, zero high half
        return exec_f32<vshufps<uint32_t(_P0), uint32_t(_P1), 0, 0> >::
            v(a, make_zero_int::v());
    }
    // both
    __m128i t= vpshufd<uint32_t(_P0), uint32_t(_P1),
                       uint32_t(_P2), uint32_t(_P3)>::v(a);
    const unsigned z0 = (_P0 < 0) ? 0 : -1;
    const unsigned z1 = (_P1 < 0) ? 0 : -1;
    const unsigned z2 = (_P2 < 0) ? 0 : -1;
    const unsigned z3 = (_P3 < 0) ? 0 : -1;
    const __m128i zm= const_v4u32<z0, z1, z2, z3>::iv();
    // zero with AND mask
    return  _mm_and_si128(t,zm);
#endif
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m128i cftal::x86::perm2_v4u32<_P0, _P1, _P2, _P3>::v(__m128i a, __m128i b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 7>::m;
    // Mask to zero out negative indexes
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    const bool sm0 = _P0 < 4;
    const bool sm1 = _P1 < 4;
    const bool sm2 = _P2 < 4;
    const bool sm3 = _P3 < 4;

    const bool z0 = _P0 < 0;
    const bool z1 = _P1 < 0;
    const bool z2 = _P2 < 0;
    const bool z3 = _P3 < 0;

    if ((m1 & 0x4444 & m2) == 0) {
        // no elements from b
        return perm1_v4u32<_P0,_P1,_P2,_P3>::v(a);
    }
    if (((m1^0x4444) & 0x4444 & m2) == 0) {
        // no elements from a
        return perm1_v4u32<_P0 & ~4, _P1 & ~4,
                           _P2 & ~4, _P3 &~4>::v(b);
    }
    if (((m1 & ~0x4444) ^ 0x3210) == 0 && m2 == 0xFFFF) {
        // selecting without shuffling or zeroing
        return select_v4u32<sm0, sm1, sm2, sm3>::v(a, b);
    }
    // Use AMD XOP instruction PPERM here later
    if ((((m1 & ~0x4444) ^ 0x3210) & m2) == 0) {
        // selecting and zeroing, not shuffling
        __m128i t = select_v4u32<sm0, sm1, sm2, sm3>::v(a, b);
        // zero
        const __m128i zm = const_v4u32<
            uint32_t(z0 ? 0 : -1),
            uint32_t(z1 ? 0 : -1),
            uint32_t(z2 ? 0 : -1),
            uint32_t(z3 ? 0 : -1)>::iv();
        return  _mm_and_si128(t, zm);
    }
    if (((m1 & 0x4400)==0x4400) && ((m1 & 0x0044)==0x00)) {
        // lower half from a, higher half from b
        __m128i t= exec_f32<
            vshufps<uint32_t(_P0), uint32_t(_P1),
                    uint32_t(_P2), uint32_t(_P3)> >::v(a, b);
        if ( m2 != 0xFFFF) {
            // zero
            const __m128i zm = const_v4u32<
                uint32_t(z0 ? 0 : -1),
                uint32_t(z1 ? 0 : -1),
                uint32_t(z2 ? 0 : -1),
                uint32_t(z3 ? 0 : -1)>::iv();
            return  _mm_and_si128(t, zm);
        }
        return t;
    }
    if (((m1 & 0x4400)==0x0000) && ((m1 & 0x0044)==0x44)) {
        // lower half from b, higher half from a
        __m128i t= exec_f32<
            vshufps<uint32_t(_P0), uint32_t(_P1),
                    uint32_t(_P2), uint32_t(_P3)> >::v(b, a);
        if ( m2 != 0xFFFF) {
            // zero
            const __m128i zm = const_v4u32<
                uint32_t(z0 ? 0 : -1),
                uint32_t(z1 ? 0 : -1),
                uint32_t(z2 ? 0 : -1),
                uint32_t(z3 ? 0 : -1)>::iv();
            return  _mm_and_si128(t, zm);
        }
        return t;
    }
    // general case
    const int zz= m2 == 0xFFFF ? 0 : -1;
    // select all elements to clear or from 1st vector
    const int ma0 = sm0 ? _P0 : zz;
    const int ma1 = sm1 ? _P1 : zz;
    const int ma2 = sm2 ? _P2 : zz;
    const int ma3 = sm3 ? _P3 : zz;
    __m128i ta = perm1_v4u32<ma0, ma1, ma2, ma3>::v(a);
    // select all elements from second vector
    const int mb0 = sm0 ? 0 : (_P0-4);
    const int mb1 = sm1 ? 0 : (_P1-4);
    const int mb2 = sm2 ? 0 : (_P2-4);
    const int mb3 = sm3 ? 0 : (_P3-4);
    __m128i tb = perm1_v4u32<mb0, mb1, mb2, mb3>::v(b);
    return  select_v4u32<sm0, sm1, sm2, sm3>::v(ta, tb);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i cftal::x86::perm1_v8u16<_P0, _P1, _P2, _P3,
                                _P4, _P5, _P6, _P7>::v(__m128i a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int me= pos_msk_4<_P0, _P2, _P4, _P6, 7>::m;
    const int mo= pos_msk_4<_P1, _P3, _P5, _P7, 7>::m;
    const int mez= zero_msk_4<_P0, _P2, _P4, _P6>::m;
    const int moz= zero_msk_4<_P1, _P3, _P5, _P7>::m;
    const bool pairs=
        ((me & 0x1111) & mez) ==0 &&
        ((mo - me) & mez) == (0x1111 & mez) &&
        (moz == mez);
    if (pairs) {
        // special cases like all -1 are done in perm1_u2
        const int _p0 = (_P0 < 0 ? -1 : _P0>>1);
        const int _p1 = (_P2 < 0 ? -1 : _P2>>1);
        const int _p2 = (_P4 < 0 ? -1 : _P4>>1);
        const int _p3 = (_P6 < 0 ? -1 : _P6>>1);
        return perm1_v4u32<_p0, _p1, _p2, _p3>::v(a);
    }
    const int m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 7>::m;
    const int m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;
    if (((m1 ^ 0x76543210) & m2)==0 && m2 !=-1) {
        // zero only
        const unsigned short z0= (_P0<0 ? 0 : -1);
        const unsigned short z1= (_P1<0 ? 0 : -1);
        const unsigned short z2= (_P2<0 ? 0 : -1);
        const unsigned short z3= (_P3<0 ? 0 : -1);
        const unsigned short z4= (_P4<0 ? 0 : -1);
        const unsigned short z5= (_P5<0 ? 0 : -1);
        const unsigned short z6= (_P6<0 ? 0 : -1);
        const unsigned short z7= (_P7<0 ? 0 : -1);
        const __m128i zm= const_v8u16<z0, z1, z2, z3,
                                      z4, z5, z6, z7>::iv();
        return _mm_and_si128(a, zm);
    }
    // No zero, high elements kept in order, low elements
    // only from low half.
    if ((m2 == -1) &&
        ((m1 & 0xFFFF0000) == 0x76540000) &&
        ((m1 & 0x00004444)==0) ) {
        const unsigned int l0= _P0;
        const unsigned int l1= _P1;
        const unsigned int l2= _P2;
        const unsigned int l3= _P3;
        return vpshuflw<l0, l1, l2, l3>::v(a);
    }
    // No zero, low elements kept in order, high elements
    // only from high half
    if ((m2 == -1) &&
        ((m1 & 0xFFFF) == 0x3210) &&
        ((m1 & 0x44440000)==0x44440000)) {
        const unsigned int h0= _P4&3;
        const unsigned int h1= _P5&3;
        const unsigned int h2= _P6&3;
        const unsigned int h3= _P7&3;
        return vpshufhw<h0, h1, h2, h3>::v(a);
    }
#if defined (__SSSE3__)
    if ((m2 == -1) &&
        ((m1 == 0x65432107) || (m1 == 0x54321076) ||
         (m1 == 0x43210765) || (m1 == 0x32107654) ||
         (m1 == 0x21076543) || (m1 == 0x07654321))) {
        // rotate only.
        return _mm_alignr_epi8(a, a, (_P0 & 7) * 2);
    }
    const uint8_t c00 = (_P0<0 ? -1 : 2*(_P0&7)+0);
    const uint8_t c01 = (_P0<0 ? -1 : 2*(_P0&7)+1);
    const uint8_t c02 = (_P1<0 ? -1 : 2*(_P1&7)+0);
    const uint8_t c03 = (_P1<0 ? -1 : 2*(_P1&7)+1);
    const uint8_t c04 = (_P2<0 ? -1 : 2*(_P2&7)+0);
    const uint8_t c05 = (_P2<0 ? -1 : 2*(_P2&7)+1);
    const uint8_t c06 = (_P3<0 ? -1 : 2*(_P3&7)+0);
    const uint8_t c07 = (_P3<0 ? -1 : 2*(_P3&7)+1);
    const uint8_t c08 = (_P4<0 ? -1 : 2*(_P4&7)+0);
    const uint8_t c09 = (_P4<0 ? -1 : 2*(_P4&7)+1);
    const uint8_t c10 = (_P5<0 ? -1 : 2*(_P5&7)+0);
    const uint8_t c11 = (_P5<0 ? -1 : 2*(_P5&7)+1);
    const uint8_t c12 = (_P6<0 ? -1 : 2*(_P6&7)+0);
    const uint8_t c13 = (_P6<0 ? -1 : 2*(_P6&7)+1);
    const uint8_t c14 = (_P7<0 ? -1 : 2*(_P7&7)+0);
    const uint8_t c15 = (_P7<0 ? -1 : 2*(_P7&7)+1);
    const __m128i msk=const_v16u8<c00, c01, c02, c03,
                                  c04, c05, c06, c07,
                                  c08, c09, c10, c11,
                                  c12, c13, c14, c15>::iv();
    return _mm_shuffle_epi8(a, msk);
#else
    // sse2 only code, we are really loosers
    __m128i r= a;
    // We know that all trivial cases are gone: permutation of
    // pairs, masks only
    // indexes 0-3 points to 0-3, 4-7 to 4-7
    const bool l_shuffle = ((m1 & 0x00004444) & m2)==0;
    const bool h_shuffle = (((m1 & 0x44440000) ^ 0x44440000) & m2)==0;
    // const bool lh_shuffle= (((m1 & 0x44444444) ^ 0x44440000) & m2)==0;
    if (l_shuffle && h_shuffle ) {
        if (l_shuffle) {
            r = vpshuflw<uint32_t(_P0), uint32_t(_P1),
                         uint32_t(_P2), uint32_t(_P3)>::v(r);
        }
        if (h_shuffle) {
            r = vpshufhw<uint32_t(_P4&3), uint32_t(_P5&3),
                         uint32_t(_P6&3), uint32_t(_P7&3)>::v(r);
        }
    } else {
        // general case: determine the count of uint32_t in
        // every half of of the vectors

        // Index to where each dword of a is needed
        // indicate which dwords are needed
        const int nn = (m1 & 0x66666666) | 0x88888888;
        const int n0 = ((((uint32_t)(nn ^ 0x00000000) - 0x22222222) &
                         0x88888888) ^ 0x88888888) & m2;
        const int n1 = ((((uint32_t)(nn ^ 0x22222222) - 0x22222222) &
                         0x88888888) ^ 0x88888888) & m2;
        const int n2 = ((((uint32_t)(nn ^ 0x44444444) - 0x22222222) &
                         0x88888888) ^ 0x88888888) & m2;
        const int n3 = ((((uint32_t)(nn ^ 0x66666666) - 0x22222222) &
                         0x88888888) ^ 0x88888888) & m2;
        // indicate which dwords are needed in low half
        const int l0 = (n0 & 0xFFFF) != 0;
        const int l1 = (n1 & 0xFFFF) != 0;
        const int l2 = (n2 & 0xFFFF) != 0;
        const int l3 = (n3 & 0xFFFF) != 0;
        // indicate which dwords are needed in high half
        const int h0 = (n0 & 0xFFFF0000) != 0;
        const int h1 = (n1 & 0xFFFF0000) != 0;
        const int h2 = (n2 & 0xFFFF0000) != 0;
        const int h3 = (n3 & 0xFFFF0000) != 0;

        // Test if we can do with two permute steps in three
        // operations
        const bool three_perms =
            l0 + l1 + l2 + l3 <= 2  &&  h0 + h1 + h2 + h3 <= 2;
        if (three_perms) {
            // one 32-bit permute followed by one 16-bit
            // permute in each half.
            // Find permute indices for 32-bit permute
            const int j0 = l0 ? 0 : l1 ? 1 : l2 ? 2 : 3;
            const int j1 = l3 ? 3 : l2 ? 2 : l1 ? 1 : 0;
            const int j2 = h0 ? 0 : h1 ? 1 : h2 ? 2 : 3;
            const int j3 = h3 ? 3 : h2 ? 2 : h1 ? 1 : 0;

            // Find permute indices for low 16-bit permute
            const int r0 = _P0 < 0 ? 0 :
                (_P0>>1 == j0 ? 0 : 2) + (_P0 & 1);
            const int r1 = _P1 < 0 ? 1 :
                (_P1>>1 == j0 ? 0 : 2) + (_P1 & 1);
            const int r2 = _P2 < 0 ? 2 :
                (_P2>>1 == j1 ? 2 : 0) + (_P2 & 1);
            const int r3 = _P3 < 0 ? 3 :
                (_P3>>1 == j1 ? 2 : 0) + (_P3 & 1);

            // Find permute indices for high 16-bit permute
            const int s0 = _P4 < 0 ? 0 :
                (_P4>>1 == j2 ? 0 : 2) + (_P4 & 1);
            const int s1 = _P5 < 0 ? 1 :
                (_P5>>1 == j2 ? 0 : 2) + (_P5 & 1);
            const int s2 = _P6 < 0 ? 2 :
                (_P6>>1 == j3 ? 2 : 0) + (_P6 & 1);
            const int s3 = _P7 < 0 ? 3 : (_P7>>1 == j3 ? 2 : 0) +
                (_P7 & 1);

            // 32-bit permute
            r = vpshufd<j0, j1, j2, j3>::v(r);
            // 16-bit permutes
            // 16 bit permute of low  half
            r = vpshuflw<r0, r1, r2, r3>::v(r);
            // 16 bit permute of high half
            r = vpshufhw<s0, s1, s2, s3>::v(r);
        } else {
            // Worst case. We need two sets of 16-bit permutes
            // swap low and high 64-bits
            r = vpshufd<2, 3, 0, 1>::v(a);
            __m128i t0, t1;
            // Find permute indices for low 16-bit permute
            // from swapped r
            const int r0 = _P0 < 4 ? 0 : _P0 & 3;
            const int r1 = _P1 < 4 ? 1 : _P1 & 3;
            const int r2 = _P2 < 4 ? 2 : _P2 & 3;
            const int r3 = _P3 < 4 ? 3 : _P3 & 3;
            // Find permute indices for high 16-bit
            // permute from swapped r
            const int s0 = _P4 < 0 || _P4 >= 4 ? 0 : _P4 & 3;
            const int s1 = _P5 < 0 || _P5 >= 4 ? 1 : _P5 & 3;
            const int s2 = _P6 < 0 || _P6 >= 4 ? 2 : _P6 & 3;
            const int s3 = _P7 < 0 || _P7 >= 4 ? 3 : _P7 & 3;
            // Find permute indices for low 16-bit permute
            // from direct a
            const int u0 = _P0 < 0 || _P0 >= 4 ? 0 : _P0 & 3;
            const int u1 = _P1 < 0 || _P1 >= 4 ? 1 : _P1 & 3;
            const int u2 = _P2 < 0 || _P2 >= 4 ? 2 : _P2 & 3;
            const int u3 = _P3 < 0 || _P3 >= 4 ? 3 : _P3 & 3;
            // Find permute indices for high 16-bit
            // permute from direct a
            const int v0 = _P4 < 4 ? 0 : _P4 & 3;
            const int v1 = _P5 < 4 ? 1 : _P5 & 3;
            const int v2 = _P6 < 4 ? 2 : _P6 & 3;
            const int v3 = _P7 < 4 ? 3 : _P7 & 3;
            // 16-bit permutes
            // 16 bit permute of low half swapped
            t0 = vpshuflw<r0, r1, r2, r3>::v(r);
            // 16 bit permute of low half orignal
            t1 = vpshuflw<u0, u1, u2, u3>::v(a);
            // 16 bit permute of high half swapped
            t0 = vpshufhw<s0, s1, s2, s3>::v(t0);
            // merge data from t0 and t1
            t1 = vpshufhw<v0, v1, v2, v3>::v(t1);
            r = select_v8u16<
                (_P0 & 4) != 0,
                (_P1 & 4) != 0,
                (_P2 & 4) != 0,
                (_P3 & 4) != 0,
                (_P4 & 4) == 0,
                (_P5 & 4) == 0,
                (_P6 & 4) == 0,
                (_P7 & 4) == 0>::v(t0, t1);
        }
    }
    // any zeros?
    if (m2 != -1) {
        const uint16_t z0= (_P0<0 ? 0 : -1);
        const uint16_t z1= (_P1<0 ? 0 : -1);
        const uint16_t z2= (_P2<0 ? 0 : -1);
        const uint16_t z3= (_P3<0 ? 0 : -1);
        const uint16_t z4= (_P4<0 ? 0 : -1);
        const uint16_t z5= (_P5<0 ? 0 : -1);
        const uint16_t z6= (_P6<0 ? 0 : -1);
        const uint16_t z7= (_P7<0 ? 0 : -1);
        const __m128i zm= const_v8u16<z0, z1, z2, z3,
                                      z4, z5, z6, z7>::iv();
        r = _mm_and_si128(r, zm);
    }
    return r;
#endif
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i cftal::x86::perm2_v8u16<_P0, _P1, _P2, _P3,
                                _P4, _P5, _P6, _P7>::v(__m128i a, __m128i b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int me= pos_msk_4<_P0, _P2, _P4, _P6, 7>::m;
    const int mo= pos_msk_4<_P1, _P3, _P5, _P7, 7>::m;
    const int mez= zero_msk_4<_P0, _P2, _P4, _P6>::m;
    const int moz= zero_msk_4<_P1, _P3, _P5, _P7>::m;
    const bool pairs=
        ((me & 0x1111) & mez) ==0 &&
        ((mo - me) & mez) == (0x1111 & mez) &&
        (moz == mez);
    if (pairs) {
        // special cases like all -1 are done in perm2_v4u32
        const int _p0 = (_P0 < 0 ? -1 : _P0>>1);
        const int _p1 = (_P2 < 0 ? -1 : _P2>>1);
        const int _p2 = (_P4 < 0 ? -1 : _P4>>1);
        const int _p3 = (_P6 < 0 ? -1 : _P6>>1);
        return perm2_v4u32<_p0, _p1, _p2, _p3>::v(a,b);
    }
    const int m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
    const int m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

    if ((m1 & 0x88888888 & m2) == 0) {
        // no elements from b
        return perm1_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a);
    }
    if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
        // no elements from a
        const int mb0 = _P0 < 0 ? -1 : _P0 & 7;
        const int mb1 = _P1 < 0 ? -1 : _P1 & 7;
        const int mb2 = _P2 < 0 ? -1 : _P2 & 7;
        const int mb3 = _P3 < 0 ? -1 : _P3 & 7;
        const int mb4 = _P4 < 0 ? -1 : _P4 & 7;
        const int mb5 = _P5 < 0 ? -1 : _P5 & 7;
        const int mb6 = _P6 < 0 ? -1 : _P6 & 7;
        const int mb7 = _P7 < 0 ? -1 : _P7 & 7;
        return perm1_v8u16<mb0, mb1, mb2, mb3, mb4, mb5, mb6, mb7>::v(b);
    }
#if defined (__SSSE3__)
    // special case: shift left
    if (_P0 > 0 && _P0 < 8 && m2 == -1 &&
        (m1 ^ ((_P0 & 7) * 0x11111111u + 0x76543210u)) == 0) {
        return _mm_alignr_epi8(b, a, (_P0 & 7) * 2);
    }
    // special case: shift right
    if (_P0 > 8 && _P0 < 16 && m2 == -1 &&
        (m1 ^ 0x88888888 ^ ((_P0 & 7) * 0x11111111u + 0x76543210u)) == 0) {
        return _mm_alignr_epi8(a, b, (_P0 & 7) * 2);
    }
#endif
    if (((m1 & ~0x88888888) ^ 0x76543210) == 0 &&
        (m2 == -1)) {
        // selecting without shuffling or zeroing
        const bool b0  = _P0 < 8 ? true : false;
        const bool b1  = _P1 < 8 ? true : false;
        const bool b2  = _P2 < 8 ? true : false;
        const bool b3  = _P3 < 8 ? true : false;
        const bool b4  = _P4 < 8 ? true : false;
        const bool b5  = _P5 < 8 ? true : false;
        const bool b6  = _P6 < 8 ? true : false;
        const bool b7  = _P7 < 8 ? true : false;
        return select_v8u16<b0, b1, b2, b3, b4, b5, b6, b7>::v(a, b);
    }
    // use AMD XOP pperm here later
    // combine two perm1 operations
    // select all elements to clear or from 1st vector
    const int ma0 = _P0 < 8 ? _P0 : -1;
    const int ma1 = _P1 < 8 ? _P1 : -1;
    const int ma2 = _P2 < 8 ? _P2 : -1;
    const int ma3 = _P3 < 8 ? _P3 : -1;
    const int ma4 = _P4 < 8 ? _P4 : -1;
    const int ma5 = _P5 < 8 ? _P5 : -1;
    const int ma6 = _P6 < 8 ? _P6 : -1;
    const int ma7 = _P7 < 8 ? _P7 : -1;
    __m128i a1 = perm1_v8u16<ma0, ma1, ma2, ma3, ma4, ma5, ma6, ma7>::v(a);
    // select all elements from second vector
    const int mb0 = _P0 > 7 ? (_P0-8) : -1;
    const int mb1 = _P1 > 7 ? (_P1-8) : -1;
    const int mb2 = _P2 > 7 ? (_P2-8) : -1;
    const int mb3 = _P3 > 7 ? (_P3-8) : -1;
    const int mb4 = _P4 > 7 ? (_P4-8) : -1;
    const int mb5 = _P5 > 7 ? (_P5-8) : -1;
    const int mb6 = _P6 > 7 ? (_P6-8) : -1;
    const int mb7 = _P7 > 7 ? (_P7-8) : -1;
    __m128i b1 = perm1_v8u16<mb0, mb1, mb2, mb3, mb4, mb5, mb6, mb7>::v(b);
    return _mm_or_si128(a1,b1);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
inline
__m128i
cftal::x86::
perm1_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m128i a)
{
    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0);
    constexpr const bool no_perm=
        (_P00<0 || _P00==0) && (_P01<0 || _P01==1) &&
        (_P02<0 || _P02==2) && (_P03<0 || _P03==3) &&
        (_P04<0 || _P04==4) && (_P05<0 || _P05==5) &&
        (_P06<0 || _P06==6) && (_P07<0 || _P07==7) &&
        (_P08<0 || _P08==8) && (_P09<0 || _P09==9) &&
        (_P10<0 || _P10==10) && (_P11<0 || _P11==11) &&
        (_P12<0 || _P12==12) && (_P13<0 || _P13==13) &&
        (_P14<0 || _P14==14) && (_P15<0 || _P15==15);

    using impl::idx_pair;
    using u16_00_t=idx_pair<_P00, _P01>;
    using u16_01_t=idx_pair<_P02, _P03>;
    using u16_02_t=idx_pair<_P04, _P05>;
    using u16_03_t=idx_pair<_P06, _P07>;
    using u16_04_t=idx_pair<_P08, _P09>;
    using u16_05_t=idx_pair<_P10, _P11>;
    using u16_06_t=idx_pair<_P12, _P13>;
    using u16_07_t=idx_pair<_P14, _P15>;

    constexpr const bool u16_perm=
        u16_00_t::is_valid && u16_01_t::is_valid &&
        u16_02_t::is_valid && u16_03_t::is_valid &&
        u16_04_t::is_valid && u16_05_t::is_valid &&
        u16_06_t::is_valid && u16_07_t::is_valid;

    using u32_0_t=idx_pair<u16_00_t::idx, u16_01_t::idx>;
    using u32_1_t=idx_pair<u16_02_t::idx, u16_03_t::idx>;
    using u32_2_t=idx_pair<u16_04_t::idx, u16_05_t::idx>;
    using u32_3_t=idx_pair<u16_06_t::idx, u16_07_t::idx>;

    constexpr const bool u32_perm= u16_perm &&
        u32_0_t::is_valid && u32_1_t::is_valid &&
        u32_2_t::is_valid && u32_3_t::is_valid;

    if (no_perm) {
        if (zero_elements==false)
            return a;
        constexpr const uint8_t
            n00=_P00<0 ? 0 : 0xff, n01=_P01<0 ? 0 : 0xff,
            n02=_P02<0 ? 0 : 0xff, n03=_P03<0 ? 0 : 0xff,
            n04=_P04<0 ? 0 : 0xff, n05=_P05<0 ? 0 : 0xff,
            n06=_P06<0 ? 0 : 0xff, n07=_P07<0 ? 0 : 0xff,
            n08=_P08<0 ? 0 : 0xff, n09=_P09<0 ? 0 : 0xff,
            n10=_P10<0 ? 0 : 0xff, n11=_P11<0 ? 0 : 0xff,
            n12=_P12<0 ? 0 : 0xff, n13=_P13<0 ? 0 : 0xff,
            n14=_P14<0 ? 0 : 0xff, n15=_P15<0 ? 0 : 0xff;
        const __m128i msk=const_v16u8<n00, n01, n02, n03,
                                      n04, n05, n06, n07,
                                      n08, n09, n10, n11,
                                      n12, n13, n14, n15>::iv();
        return _mm_and_si128(a, msk);
    }

    if (u32_perm && zero_elements==false) {
        return perm1_v4u32<u32_0_t::idx, u32_1_t::idx,
                           u32_2_t::idx, u32_3_t::idx>::v(a);
    }

    constexpr const uint8_t c00 = (_P00 < 0) ? -1 : _P00 & 15;
    constexpr const uint8_t c01 = (_P01 < 0) ? -1 : _P01 & 15;
    constexpr const uint8_t c02 = (_P02 < 0) ? -1 : _P02 & 15;
    constexpr const uint8_t c03 = (_P03 < 0) ? -1 : _P03 & 15;
    constexpr const uint8_t c04 = (_P04 < 0) ? -1 : _P04 & 15;
    constexpr const uint8_t c05 = (_P05 < 0) ? -1 : _P05 & 15;
    constexpr const uint8_t c06 = (_P06 < 0) ? -1 : _P06 & 15;
    constexpr const uint8_t c07 = (_P07 < 0) ? -1 : _P07 & 15;
    constexpr const uint8_t c08 = (_P08 < 0) ? -1 : _P08 & 15;
    constexpr const uint8_t c09 = (_P09 < 0) ? -1 : _P09 & 15;
    constexpr const uint8_t c10 = (_P10 < 0) ? -1 : _P10 & 15;
    constexpr const uint8_t c11 = (_P11 < 0) ? -1 : _P11 & 15;
    constexpr const uint8_t c12 = (_P12 < 0) ? -1 : _P12 & 15;
    constexpr const uint8_t c13 = (_P13 < 0) ? -1 : _P13 & 15;
    constexpr const uint8_t c14 = (_P14 < 0) ? -1 : _P14 & 15;
    constexpr const uint8_t c15 = (_P15 < 0) ? -1 : _P15 & 15;
    const __m128i msk=const_v16u8<c00, c01, c02, c03,
                                  c04, c05, c06, c07,
                                  c08, c09, c10, c11,
                                  c12, c13, c14, c15>::iv();
    return vpshufb::v(a, msk);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
inline
__m128i
cftal::x86::
perm2_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m128i a, __m128i b)
{
    constexpr const uint32_t
        _UP00=_P00, _UP01=_P01, _UP02=_P02, _UP03=_P03,
        _UP04=_P04, _UP05=_P05, _UP06=_P06, _UP07=_P07,
        _UP08=_P08, _UP09=_P09, _UP10=_P10, _UP11=_P11,
        _UP12=_P12, _UP13=_P13, _UP14=_P14, _UP15=_P15;

    constexpr const bool a_only=
        (_P00 < 16) && (_P01 < 16) && (_P02 < 16) && (_P03 < 16) &&
        (_P04 < 16) && (_P05 < 16) && (_P06 < 16) && (_P07 < 16) &&
        (_P08 < 16) && (_P09 < 16) && (_P10 < 16) && (_P11 < 16) &&
        (_P12 < 16) && (_P13 < 16) && (_P14 < 16) && (_P15 < 16);
    constexpr const bool b_only=
        (_UP00 > 15) && (_UP01 > 15) && (_UP02 > 15) && (_UP03 > 15) &&
        (_UP04 > 15) && (_UP05 > 15) && (_UP06 > 15) && (_UP07 > 15) &&
        (_UP08 > 15) && (_UP09 > 15) && (_UP10 > 15) && (_UP11 > 15) &&
        (_UP12 > 15) && (_UP13 > 15) && (_UP14 > 15) && (_UP15 > 15);

    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0);

    // elements to select from vector a or zero
    constexpr const int32_t
        a00 = _P00 > 15 ? -1 : _P00, a01 = _P01 > 15 ? -1 : _P01,
        a02 = _P02 > 15 ? -1 : _P02, a03 = _P03 > 15 ? -1 : _P03,
        a04 = _P04 > 15 ? -1 : _P04, a05 = _P05 > 15 ? -1 : _P05,
        a06 = _P06 > 15 ? -1 : _P06, a07 = _P07 > 15 ? -1 : _P07,
        a08 = _P08 > 15 ? -1 : _P08, a09 = _P09 > 15 ? -1 : _P09,
        a10 = _P10 > 15 ? -1 : _P10, a11 = _P11 > 15 ? -1 : _P11,
        a12 = _P12 > 15 ? -1 : _P12, a13 = _P13 > 15 ? -1 : _P13,
        a14 = _P14 > 15 ? -1 : _P14, a15 = _P15 > 15 ? -1 : _P15;

    // elements to select from vector b or zero
    constexpr const int16_t
        b00 = _P00 < 16 ? -1 : _P00-16, b01 = _P01 < 16 ? -1 : _P01-16,
        b02 = _P02 < 16 ? -1 : _P02-16, b03 = _P03 < 16 ? -1 : _P03-16,
        b04 = _P04 < 16 ? -1 : _P04-16, b05 = _P05 < 16 ? -1 : _P05-16,
        b06 = _P06 < 16 ? -1 : _P06-16, b07 = _P07 < 16 ? -1 : _P07-16,
        b08 = _P08 < 16 ? -1 : _P08-16, b09 = _P09 < 16 ? -1 : _P09-16,
        b10 = _P10 < 16 ? -1 : _P10-16, b11 = _P11 < 16 ? -1 : _P11-16,
        b12 = _P12 < 16 ? -1 : _P12-16, b13 = _P13 < 16 ? -1 : _P13-16,
        b14 = _P14 < 16 ? -1 : _P14-16, b15 = _P15 < 16 ? -1 : _P15-16;

    constexpr const bool no_perm=
        (_P00<0 || _P00==0 || _P00==16) &&
        (_P01<0 || _P01==1 || _P01==17) &&
        (_P02<0 || _P02==2 || _P02==18) &&
        (_P03<0 || _P03==3 || _P03==19) &&
        (_P04<0 || _P04==4 || _P04==20) &&
        (_P05<0 || _P05==5 || _P05==21) &&
        (_P06<0 || _P06==6 || _P06==22) &&
        (_P07<0 || _P07==7 || _P07==23) &&
        (_P08<0 || _P08==8 || _P08==24) &&
        (_P09<0 || _P09==9 || _P09==25) &&
        (_P10<0 || _P10==10 || _P10==26) &&
        (_P11<0 || _P11==11 || _P11==27) &&
        (_P12<0 || _P12==12 || _P12==28) &&
        (_P13<0 || _P13==13 || _P13==29) &&
        (_P14<0 || _P14==14 || _P14==30) &&
        (_P15<0 || _P15==15 || _P15==31);

    if (a_only) {
        const __m128i ap=perm1_v16u8<
            a00, a01, a02, a03, a04, a05, a06, a07,
            a08, a09, a10, a11, a12, a13, a14, a15>::v(a);
        return ap;
    }
    if (b_only) {
        const __m128i bp=perm1_v16u8<
            b00, b01, b02, b03, b04, b05, b06, b07,
            b08, b09, b10, b11, b12, b13, b14, b15>::v(b);
        return bp;
    }
    if (no_perm) {
        constexpr const bool
            s00 = _P00 < 16 ? true: false, s01 = _P01 < 16 ? true: false,
            s02 = _P02 < 16 ? true: false, s03 = _P03 < 16 ? true: false,
            s04 = _P04 < 16 ? true: false, s05 = _P05 < 16 ? true: false,
            s06 = _P06 < 16 ? true: false, s07 = _P07 < 16 ? true: false,
            s08 = _P08 < 16 ? true: false, s09 = _P09 < 16 ? true: false,
            s10 = _P10 < 16 ? true: false, s11 = _P11 < 16 ? true: false,
            s12 = _P12 < 16 ? true: false, s13 = _P13 < 16 ? true: false,
            s14 = _P14 < 16 ? true: false, s15 = _P15 < 16 ? true: false;
        const __m128i rs=select_v16u8<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15>::v(a, b);
        if (zero_elements==false)
            return rs;
        constexpr const uint8_t
            z00 = _P00 < 0 ? 0x00: 0xff, z01 = _P01 < 0 ? 0x00: 0xff,
            z02 = _P02 < 0 ? 0x00: 0xff, z03 = _P03 < 0 ? 0x00: 0xff,
            z04 = _P04 < 0 ? 0x00: 0xff, z05 = _P05 < 0 ? 0x00: 0xff,
            z06 = _P06 < 0 ? 0x00: 0xff, z07 = _P07 < 0 ? 0x00: 0xff,
            z08 = _P08 < 0 ? 0x00: 0xff, z09 = _P09 < 0 ? 0x00: 0xff,
            z10 = _P10 < 0 ? 0x00: 0xff, z11 = _P11 < 0 ? 0x00: 0xff,
            z12 = _P12 < 0 ? 0x00: 0xff, z13 = _P13 < 0 ? 0x00: 0xff,
            z14 = _P14 < 0 ? 0x00: 0xff, z15 = _P15 < 0 ? 0x00: 0xff;
        const __m128i zm=const_v16u8<z00, z01, z02, z03,
                                     z04, z05, z06, z07,
                                     z08, z09, z10, z11,
                                     z12, z13, z14, z15>::iv();
        return _mm_and_si128(rs, zm);
    }
    const __m128i ap=perm1_v16u8<
        a00, a01, a02, a03, a04, a05, a06, a07,
        a08, a09, a10, a11, a12, a13, a14, a15>::v(a);
    const __m128i bp=perm1_v16u8<
        b00, b01, b02, b03, b04, b05, b06, b07,
        b08, b09, b10, b11, b12, b13, b14, b15>::v(b);
    const __m128i r=_mm_or_si128(ap, bp);
    return r;
}

#if defined (__AVX__)

template <int _P0, int _P1, int _P2, int _P3>
__m256d cftal::x86::perm1_v4f64<_P0, _P1, _P2, _P3>::v(__m256d a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 3>::m;
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    const bool do_shuffle = ((m1 ^ 0x3210) & m2) !=0;
    const bool do_zero =  ((m2 & 0xFFFF) != 0xFFFF);
    if (!do_shuffle && !do_zero) {
        // trivial case: do nothing
        return a;
    }
    if (do_zero && !do_shuffle) {
        // zeroing, not shuffling
        if (m2 == 0) {
            // zero everything
            return _mm256_setzero_pd();
        }
        // zero some elements
        const unsigned z0 = (_P0 < 0) ? 0 : -1;
        const unsigned z1 = (_P1 < 0) ? 0 : -1;
        const unsigned z2 = (_P2 < 0) ? 0 : -1;
        const unsigned z3 = (_P3 < 0) ? 0 : -1;
        const __m256d zm= const_v8u32<z0, z0, z1, z1,
                                      z2, z2, z3, z3>::dv();
        // zero with AND mask
        return  _mm256_and_pd(a, zm);
    }
    __m256d res;
    if ( (((m1 & 0x22) & m2) == 0) &&
         (((m1 & 0x2200) & m2) == (0x2200 & m2))) {
        // low from low src, high from high src
        const int sel= csel4<_P0, _P1, _P2, _P3>::val;
        res= _mm256_permute_pd(a, sel & 0xf);
    } else if ( ((m1 & m2) == (0x1032 & m2)) ) {
        res= _mm256_permute2f128_pd(a, a, 0x01);
    } else if ( ((m1 & m2) == (0x3232 & m2)) ) {
        res= _mm256_permute2f128_pd(a, a, 0x11);
    } else if ( ((m1 & m2) == (0x1010 & m2)) ) {
        res= _mm256_insertf128_pd(a,
                                  _mm256_castpd256_pd128(a),
                                  1);
    } else {
#if defined (__AVX2__)
        // general case
        const int sh4=shuffle4<_P0, _P1, _P2, _P3>::val;
        res=_mm256_permute4x64_pd(a, sh4 & 0xff);
#else
        if (((m1 & 0x2222) & m2)==0) {
            // only from low lane
            __m256d lo2lo_lo2hi=
                _mm256_insertf128_pd(a,
                                     _mm256_castpd256_pd128(a),
                                     1);
            const int sel_lo= csel4<_P0, _P1, _P2, _P3>::val;
            res = _mm256_permute_pd(lo2lo_lo2hi, sel_lo & 0xF);
        } else if (((m1 & 0x2222) & m2)==(0x2222 & m2)) {
            // only from high lane
            __m256d hi2lo_hi2hi= _mm256_permute2f128_pd(a, a, 0x11);
            enum { sel_hi= csel4<_P0, _P1, _P2, _P3>::val };
            res = _mm256_permute_pd(hi2lo_hi2hi, sel_hi);
        } else {
            // general case
            // copy high half to low half
            __m256d hi2lo_hi2hi= _mm256_permute2f128_pd(a, a, 0x11);
            // copy low half to high half
            __m256d lo2lo_lo2hi=
                _mm256_insertf128_pd(a,
                                     _mm256_castpd256_pd128(a),
                                     1);
            enum {
                sel_hi= csel4<_P0, _P1, _P2, _P3>::val,
                sel_lo= csel4<_P0, _P1, _P2, _P3>::val
            };

            hi2lo_hi2hi = _mm256_permute_pd(hi2lo_hi2hi, sel_hi);
            lo2lo_lo2hi = _mm256_permute_pd(lo2lo_lo2hi, sel_lo);

            const bool b0= _P0 < 2 ? true : false;
            const bool b1= _P1 < 2 ? true : false;
            const bool b2= _P2 < 2 ? true : false;
            const bool b3= _P3 < 2 ? true : false;
            res= select_v4f64<b0, b1, b2, b3>::
                v(lo2lo_lo2hi, hi2lo_hi2hi);
        }
#endif
    }
    if (do_zero) {
        const unsigned z0 = (_P0 < 0) ? 0 : -1;
        const unsigned z1 = (_P1 < 0) ? 0 : -1;
        const unsigned z2 = (_P2 < 0) ? 0 : -1;
        const unsigned z3 = (_P3 < 0) ? 0 : -1;
        const __m256d zm= const_v8u32<z0, z0, z1, z1,
                                      z2, z2, z3, z3>::dv();
        // zero with AND mask
        res = _mm256_and_pd(res, zm);
    }
    return res;
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m256d cftal::x86::perm2_v4f64<_P0, _P1, _P2, _P3>::v(__m256d a, __m256d b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 7>::m;
    // Mask to zero out negative indexes
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    if ((m1 & 0x4444 & m2) == 0) {
        // no elements from b
        return perm1_v4f64<_P0, _P1, _P2, _P3>::v(a);
    }
    if (((m1^0x4444) & 0x4444 & m2) == 0) {
        // no elements from a
        return perm1_v4f64< _P0 & ~4, _P1 & ~4,
                            _P2 & ~4, _P3 & ~4>::v(b);
    }
    const bool sm0 = _P0 < 4;
    const bool sm1 = _P1 < 4;
    const bool sm2 = _P2 < 4;
    const bool sm3 = _P3 < 4;
    if (((m1 & ~0x4444) ^ 0x3210) == 0 && m2 == 0xFFFF) {
        // selecting without shuffling or zeroing
        return select_v4f64<sm0, sm1, sm2, sm3>::v(a, b);
    }
    // general case
    const int zz= m2 == 0xFFFF ? 0 : -1;
    // select all elements to clear or from 1st vector
    const int ma0 = sm0 ? _P0 : zz;
    const int ma1 = sm1 ? _P1 : zz;
    const int ma2 = sm2 ? _P2 : zz;
    const int ma3 = sm3 ? _P3 : zz;
    __m256d ta = perm1_v4f64<ma0, ma1, ma2, ma3>::v(a);
    // select all elements from second vector
    const int mb0 = sm0 ? 0 : (_P0-4);
    const int mb1 = sm1 ? 0 : (_P1-4);
    const int mb2 = sm2 ? 0 : (_P2-4);
    const int mb3 = sm3 ? 0 : (_P3-4);
    __m256d tb = perm1_v4f64<mb0, mb1, mb2, mb3>::v(b);
    return select_v4f64<sm0, sm1, sm2, sm3>::v(ta, tb);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}


template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m256 cftal::x86::perm1_v8f32<_P0, _P1, _P2, _P3,
                               _P4, _P5, _P6, _P7>::v(__m256 a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int me= pos_msk_4<_P0, _P2, _P4, _P6, 7>::m;
    const int mo= pos_msk_4<_P1, _P3, _P5, _P7, 7>::m;
    const int mez= zero_msk_4<_P0, _P2, _P4, _P6>::m;
    const int moz= zero_msk_4<_P1, _P3, _P5, _P7>::m;
    const bool pairs=
        ((me & 0x1111) & mez) ==0 &&
        ((mo - me) & mez) == (0x1111 & mez) &&
        (moz == mez);
    if (pairs) {
        // special cases like all -1 are done in perm1_v4f64
        const int _p0 = (_P0 < 0 ? -1 : _P0>>1);
        const int _p1 = (_P2 < 0 ? -1 : _P2>>1);
        const int _p2 = (_P4 < 0 ? -1 : _P4>>1);
        const int _p3 = (_P6 < 0 ? -1 : _P6>>1);
        __m256d ad(as<__m256d>(a));
        __m256d rd(perm1_v4f64<_p0, _p1, _p2, _p3>::v(ad));
        return as<__m256>(rd);
    }
    const uint32_t m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 7>::m;
    const uint32_t m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;
    const bool do_zero= m2 != 0xFFFFFFFF;
    if (((m1 ^ 0x76543210) & m2)==0 && m2 !=0xFFFFFFFF) {
        // zero only
        const unsigned z0= (_P0<0 ? 0 : -1);
        const unsigned z1= (_P1<0 ? 0 : -1);
        const unsigned z2= (_P2<0 ? 0 : -1);
        const unsigned z3= (_P3<0 ? 0 : -1);
        const unsigned z4= (_P4<0 ? 0 : -1);
        const unsigned z5= (_P5<0 ? 0 : -1);
        const unsigned z6= (_P6<0 ? 0 : -1);
        const unsigned z7= (_P7<0 ? 0 : -1);
        const __m256 zm= const_v8u32<z0, z1, z2, z3,
                                     z4, z5, z6, z7>::fv();
        return _mm256_and_ps(a, zm);
    }
    // in lane permutation
    __m256 res;
    if ( (((m1 & 0x4444) & m2) == 0) &&
         (((m1 & 0x44440000) & m2) == (0x44440000 & m2))) {
        // low from low src, high from high src
        const __m256i p= const_v8u32<_P0 & 3, _P1 & 3,
                                     _P2 & 3, _P3 & 3,
                                     _P4 & 3, _P5 & 3,
                                     _P6 & 3, _P7 & 3>::iv();
        res= _mm256_permutevar_ps(a, p);
    } else if ( ((m1 & m2) == (0x32107654 & m2)) ) {
        res= _mm256_permute2f128_ps(a, a, 0x01);
    } else if ( ((m1 & m2) == (0x76547654 & m2)) ) {
        res= _mm256_permute2f128_ps(a, a, 0x11);
    } else if ( ((m1 & m2) == (0x32103210 & m2)) ) {
        res= _mm256_insertf128_ps(a,
                                  _mm256_castps256_ps128(a),
                                  1);
    } else {
#if defined (__AVX2__)
        // general case
        const __m256i p= const_v8u32<_P0 & 7, _P1 & 7,
                                     _P2 & 7, _P3 & 7,
                                     _P4 & 7, _P5 & 7,
                                     _P6 & 7, _P7 & 7>::iv();
        res=_mm256_permutevar8x32_ps(a, p);
#else
        if (((m1 & 0x44444444) & m2)==0) {
            // only from low lane
            __m256 lo2lo_lo2hi=
                _mm256_insertf128_ps(a,
                                     _mm256_castps256_ps128(a),
                                     1);
            const __m256i p= const_v8u32<_P0 & 3, _P1 & 3,
                                         _P2 & 3, _P3 & 3,
                                         _P4 & 3, _P5 & 3,
                                         _P6 & 3, _P7 & 3>::iv();
            res = _mm256_permutevar_ps(lo2lo_lo2hi, p);
        } else if (((m1 & 0x44444444) & m2)==(0x44444444 & m2)) {
            // only from high lane
            __m256 hi2lo_hi2hi= _mm256_permute2f128_ps(a, a, 0x11);
            const __m256i p= const_v8u32<_P0 & 3, _P1 & 3,
                                         _P2 & 3, _P3 & 3,
                                         _P4 & 3, _P5 & 3,
                                         _P6 & 3, _P7 & 3>::iv();
            res = _mm256_permutevar_ps(hi2lo_hi2hi, p);
        } else {
            // general case
            // copy high half to low half
            __m256 hi2lo_hi2hi= _mm256_permute2f128_ps(a, a, 0x11);
            // copy low half to high half
            __m256 lo2lo_lo2hi=
                _mm256_insertf128_ps(a,
                                     _mm256_castps256_ps128(a),
                                     1);
            const __m256i p= const_v8u32<_P0 & 3, _P1 & 3,
                                         _P2 & 3, _P3 & 3,
                                         _P4 & 3, _P5 & 3,
                                         _P6 & 3, _P7 & 3>::iv();

            hi2lo_hi2hi = _mm256_permutevar_ps(hi2lo_hi2hi, p);
            lo2lo_lo2hi = _mm256_permutevar_ps(lo2lo_lo2hi, p);
            const bool b0= _P0 < 4 ? true : false;
            const bool b1= _P1 < 4 ? true : false;
            const bool b2= _P2 < 4 ? true : false;
            const bool b3= _P3 < 4 ? true : false;
            const bool b4= _P4 < 4 ? true : false;
            const bool b5= _P5 < 4 ? true : false;
            const bool b6= _P6 < 4 ? true : false;
            const bool b7= _P7 < 4 ? true : false;
            res= select_v8f32<b0, b1, b2, b3, b4, b5, b6, b7>::
                v(lo2lo_lo2hi, hi2lo_hi2hi);
        }
#endif
    }
    if (do_zero) {
        const unsigned z0= (_P0<0 ? 0 : -1);
        const unsigned z1= (_P1<0 ? 0 : -1);
        const unsigned z2= (_P2<0 ? 0 : -1);
        const unsigned z3= (_P3<0 ? 0 : -1);
        const unsigned z4= (_P4<0 ? 0 : -1);
        const unsigned z5= (_P5<0 ? 0 : -1);
        const unsigned z6= (_P6<0 ? 0 : -1);
        const unsigned z7= (_P7<0 ? 0 : -1);
        const __m256 zm= const_v8u32<z0, z1, z2, z3,
                                     z4, z5, z6, z7>::fv();
        // zero with AND mask
        res = _mm256_and_ps(res, zm);
    }
    return res;
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
__m256 cftal::x86::perm2_v8f32<_P0, _P1, _P2, _P3,
                               _P4, _P5, _P6, _P7>::v(__m256 a, __m256 b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const unsigned m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
    // Mask to zero out negative indexes
    const unsigned m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

    if ((m1 & 0x88888888 & m2) == 0) {
        // no elements from b
        return perm1_v8f32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>::v(a);
    }
    if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
        // no elements from a
        return perm1_v8f32<_P0 & ~8, _P1 & ~8,
                           _P2 & ~8, _P3 & ~8,
                           _P4 & ~8, _P5 & ~8,
                           _P6 & ~8, _P7 & ~8>::v(b);
    }
    const bool sm0 = _P0 < 8;
    const bool sm1 = _P1 < 8;
    const bool sm2 = _P2 < 8;
    const bool sm3 = _P3 < 8;
    const bool sm4 = _P4 < 8;
    const bool sm5 = _P5 < 8;
    const bool sm6 = _P6 < 8;
    const bool sm7 = _P7 < 8;
    if (((m1 & ~0x88888888) ^ 0x76543210) == 0 && m2 == 0xFFFFFFFF) {
        // selecting without shuffling or zeroing
        return select_v8f32<sm0, sm1, sm2, sm3,
                            sm4, sm5, sm6, sm7>::v(a, b);
    }

    const int zz= m2 == 0xFFFFFFFF ? 0 : -1;
    // select all elements to clear or from 1st vector
    const int ma0 = sm0 ? _P0 : zz;
    const int ma1 = sm1 ? _P1 : zz;
    const int ma2 = sm2 ? _P2 : zz;
    const int ma3 = sm3 ? _P3 : zz;
    const int ma4 = sm4 ? _P4 : zz;
    const int ma5 = sm5 ? _P5 : zz;
    const int ma6 = sm6 ? _P6 : zz;
    const int ma7 = sm7 ? _P7 : zz;
    __m256 a1 = perm1_v8f32<ma0, ma1, ma2, ma3,
                            ma4, ma5, ma6, ma7>::v(a);
    // select all elements from second vector
    const int mb0 = sm0 ? 0: (_P0-8);
    const int mb1 = sm1 ? 0: (_P1-8);
    const int mb2 = sm2 ? 0: (_P2-8);
    const int mb3 = sm3 ? 0: (_P3-8);
    const int mb4 = sm4 ? 0: (_P4-8);
    const int mb5 = sm5 ? 0: (_P5-8);
    const int mb6 = sm6 ? 0: (_P6-8);
    const int mb7 = sm7 ? 0: (_P7-8);
    __m256 b1 = perm1_v8f32<mb0, mb1, mb2, mb3,
                            mb4, mb5, mb6, mb7>::v(b);
    return  select_v8f32<sm0, sm1, sm2, sm3,
                         sm4, sm5, sm6, sm7>::v(a1 ,b1);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

#endif
#if defined (__AVX2__)
template <int _P0, int _P1, int _P2, int _P3>
__m256i cftal::x86::perm1_v4u64<_P0, _P1, _P2, _P3>::v(__m256i a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 3>::m;
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    const bool do_shuffle = ((m1 ^ 0x3210) & m2) !=0;
    const bool do_zero =  ((m2 & 0xFFFF) != 0xFFFF);
    if (!do_shuffle && !do_zero) {
        // trivial case: do nothing
        return a;
    }
    if (do_zero && !do_shuffle) {
        // zeroing, not shuffling
        if (m2 == 0) {
            // zero everything
            return _mm256_setzero_si256();
        }
        // zero some elements
        const unsigned z0 = (_P0 < 0) ? 0 : -1;
        const unsigned z1 = (_P1 < 0) ? 0 : -1;
        const unsigned z2 = (_P2 < 0) ? 0 : -1;
        const unsigned z3 = (_P3 < 0) ? 0 : -1;
        const __m256i zm= const_v8u32<z0, z0, z1, z1,
                                      z2, z2, z3, z3>::iv();
        // zero with AND mask
        return  _mm256_and_si256(a, zm);
    }
    __m256i res;
    if ( (((m1 & 0x22) & m2) == 0) &&
         (((m1 & 0x2200) & m2) == (0x2200 & m2))) {
        // low from low src, high from high src
        if (do_zero) {
            constexpr const uint8_t
                s00=_P0<0 ? -1 : _P0*8+0, s01=_P0<0 ? -1 : _P0*8+1,
                s02=_P0<0 ? -1 : _P0*8+2, s03=_P0<0 ? -1 : _P0*8+3,
                s04=_P0<0 ? -1 : _P0*8+4, s05=_P0<0 ? -1 : _P1*8+5,
                s06=_P0<0 ? -1 : _P0*8+6, s07=_P0<0 ? -1 : _P1*8+7,
                s08=_P1<0 ? -1 : _P1*8+0, s09=_P1<0 ? -1 : _P2*8+1,
                s10=_P1<0 ? -1 : _P1*8+2, s11=_P1<0 ? -1 : _P2*8+3,
                s12=_P1<0 ? -1 : _P1*8+4, s13=_P1<0 ? -1 : _P3*8+5,
                s14=_P1<0 ? -1 : _P1*8+6, s15=_P1<0 ? -1 : _P3*8+7,
                s16=_P2<0 ? -1 : _P2*8-16+0, s17=_P2<0 ? -1 : _P2*8-16+1,
                s18=_P2<0 ? -1 : _P2*8-16+2, s19=_P2<0 ? -1 : _P2*8-16+3,
                s20=_P2<0 ? -1 : _P2*8-16+4, s21=_P2<0 ? -1 : _P2*8-16+5,
                s22=_P2<0 ? -1 : _P2*8-16+6, s23=_P2<0 ? -1 : _P2*8-16+7,
                s24=_P3<0 ? -1 : _P3*8-16+0, s25=_P3<0 ? -1 : _P3*8-16+1,
                s26=_P3<0 ? -1 : _P3*8-16+2, s27=_P3<0 ? -1 : _P3*8-16+3,
                s28=_P3<0 ? -1 : _P3*8-16+4, s29=_P3<0 ? -1 : _P3*8-16+5,
                s30=_P3<0 ? -1 : _P3*8-16+6, s31=_P3<0 ? -1 : _P3*8-16+7;
            const __m256i msk=const_v32u8<
                s00, s01, s02, s03, s04, s05, s06, s07,
                s08, s09, s10, s11, s12, s13, s14, s15,
                s16, s17, s18, s19, s20, s21, s22, s23,
                s24, s25, s26, s27, s28, s29, s30, s31>::iv();
            res=vpshufb::v(a, msk);
            return res;
        }
        const int sel= csel4<_P0, _P1, _P2, _P3>::val;
        res= _mm256_castpd_si256(
            _mm256_permute_pd(_mm256_castsi256_pd(a), sel & 0xf));
    } else if ( ((m1 & m2) == (0x1032 & m2)) ) {
        res= _mm256_permute2x128_si256(a, a, 0x01);
    } else if ( ((m1 & m2) == (0x3232 & m2)) ) {
        res= _mm256_permute2x128_si256(a, a, 0x11);
    } else if ( ((m1 & m2) == (0x1010 & m2)) ) {
        res= _mm256_inserti128_si256(a,
                                     _mm256_castsi256_si128(a),
                                     1);
    } else {
        // general case
        const int sh4=shuffle4<_P0, _P1, _P2, _P3>::val;
        res=_mm256_permute4x64_epi64(a, sh4);
    }
    if (do_zero) {
        const unsigned z0 = (_P0 < 0) ? 0 : -1;
        const unsigned z1 = (_P1 < 0) ? 0 : -1;
        const unsigned z2 = (_P2 < 0) ? 0 : -1;
        const unsigned z3 = (_P3 < 0) ? 0 : -1;
        const __m256i zm= const_v8u32<z0, z0, z1, z1,
                                      z2, z2, z3, z3>::iv();
        // zero with AND mask
        res = _mm256_and_si256(res, zm);
    }
    return res;
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m256i cftal::x86::perm2_v4u64<_P0, _P1, _P2, _P3>::v(__m256i a, __m256i b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 7>::m;
    // Mask to zero out negative indexes
    const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

    if ((m1 & 0x4444 & m2) == 0) {
        // no elements from b
        return perm1_v4u64<_P0, _P1, _P2, _P3>::v(a);
    }
    if (((m1^0x4444) & 0x4444 & m2) == 0) {
        // no elements from a
        return perm1_v4u64< _P0 & ~4, _P1 & ~4,
                            _P2 & ~4, _P3 & ~4>::v(b);
    }
    // selecting without shuffling or zeroing
    const bool sm0 = _P0 < 4;
    const bool sm1 = _P1 < 4;
    const bool sm2 = _P2 < 4;
    const bool sm3 = _P3 < 4;
    if (((m1 & ~0x4444) ^ 0x3210) == 0 && m2 == 0xFFFF) {
        return select_v4u64<sm0, sm1, sm2, sm3>::v(a, b);
    }
    // general case
    const int zz= m2 == 0xFFFF ? 0 : -1;
    // select all elements to clear or from 1st vector
    const int ma0 = sm0 ? _P0 : zz;
    const int ma1 = sm1 ? _P1 : zz;
    const int ma2 = sm2 ? _P2 : zz;
    const int ma3 = sm3 ? _P3 : zz;
    __m256i ta = perm1_v4u64<ma0, ma1, ma2, ma3>::v(a);
    // select all elements from second vector
    const int mb0 = sm0 ? 0 : (_P0-4);
    const int mb1 = sm1 ? 0 : (_P1-4);
    const int mb2 = sm2 ? 0 : (_P2-4);
    const int mb3 = sm3 ? 0 : (_P3-4);
    __m256i tb = perm1_v4u64<mb0, mb1, mb2, mb3>::v(b);
    return  select_v4u64<sm0, sm1, sm2, sm3>::v(ta, tb);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m256i
cftal::x86::perm1_v8u32<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(__m256i a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const int me= pos_msk_4<_P0, _P2, _P4, _P6, 7>::m;
    const int mo= pos_msk_4<_P1, _P3, _P5, _P7, 7>::m;
    const int mez= zero_msk_4<_P0, _P2, _P4, _P6>::m;
    const int moz= zero_msk_4<_P1, _P3, _P5, _P7>::m;
    const bool pairs=
        ((me & 0x1111) & mez) ==0 &&
        ((mo - me) & mez) == (0x1111 & mez) &&
        (moz == mez);
    if (pairs) {
        // special cases like all -1 are done in perm1_v4u64
        const int _p0 = (_P0 < 0 ? -1 : _P0>>1);
        const int _p1 = (_P2 < 0 ? -1 : _P2>>1);
        const int _p2 = (_P4 < 0 ? -1 : _P4>>1);
        const int _p3 = (_P6 < 0 ? -1 : _P6>>1);
        __m256i rd(perm1_v4u64<_p0, _p1, _p2, _p3>::v(a));
        return rd;
    }
    const uint32_t m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 7>::m;
    const uint32_t m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;
    const bool do_zero= m2 != 0xFFFFFFFF;
    if (((m1 ^ 0x76543210) & m2)==0 && m2 !=uint32_t(-1)) {
        // zero only
        const unsigned z0= (_P0<0 ? 0 : -1);
        const unsigned z1= (_P1<0 ? 0 : -1);
        const unsigned z2= (_P2<0 ? 0 : -1);
        const unsigned z3= (_P3<0 ? 0 : -1);
        const unsigned z4= (_P4<0 ? 0 : -1);
        const unsigned z5= (_P5<0 ? 0 : -1);
        const unsigned z6= (_P6<0 ? 0 : -1);
        const unsigned z7= (_P7<0 ? 0 : -1);
        const __m256i zm= const_v8u32<z0, z1, z2, z3,
                                      z4, z5, z6, z7>::iv();
        return _mm256_and_si256(a, zm);
    }
    // in lane permutation
    __m256i res;
    if ( (((m1 & 0x4444) & m2) == 0) &&
         (((m1 & 0x44440000) & m2) == (0x44440000 & m2))) {
        // low from low src, high from high src
        if (do_zero) {
            constexpr const uint8_t
                s00=_P0<0 ? -1 : _P0*4+0, s01=_P0<0 ? -1 : _P0*4+1,
                s02=_P0<0 ? -1 : _P0*4+2, s03=_P0<0 ? -1 : _P0*4+3,
                s04=_P1<0 ? -1 : _P1*4+0, s05=_P1<0 ? -1 : _P1*4+1,
                s06=_P1<0 ? -1 : _P1*4+2, s07=_P1<0 ? -1 : _P1*4+3,
                s08=_P2<0 ? -1 : _P2*4+0, s09=_P2<0 ? -1 : _P2*4+1,
                s10=_P2<0 ? -1 : _P2*4+2, s11=_P2<0 ? -1 : _P2*4+3,
                s12=_P3<0 ? -1 : _P3*4+0, s13=_P3<0 ? -1 : _P3*4+1,
                s14=_P3<0 ? -1 : _P3*4+2, s15=_P3<0 ? -1 : _P3*4+3,
                s16=_P4<0 ? -1 : _P4*4-16+0, s17=_P4<0 ? -1 : _P4*4-16+1,
                s18=_P4<0 ? -1 : _P4*4-16+2, s19=_P4<0 ? -1 : _P4*4-16+3,
                s20=_P5<0 ? -1 : _P5*4-16+0, s21=_P5<0 ? -1 : _P5*4-16+1,
                s22=_P5<0 ? -1 : _P5*4-16+2, s23=_P5<0 ? -1 : _P5*4-16+3,
                s24=_P6<0 ? -1 : _P6*4-16+0, s25=_P6<0 ? -1 : _P6*4-16+1,
                s26=_P6<0 ? -1 : _P6*4-16+2, s27=_P6<0 ? -1 : _P6*4-16+3,
                s28=_P7<0 ? -1 : _P7*4-16+0, s29=_P7<0 ? -1 : _P7*4-16+1,
                s30=_P7<0 ? -1 : _P7*4-16+2, s31=_P7<0 ? -1 : _P7*4-16+3;
            const __m256i msk=const_v32u8<
                s00, s01, s02, s03, s04, s05, s06, s07,
                s08, s09, s10, s11, s12, s13, s14, s15,
                s16, s17, s18, s19, s20, s21, s22, s23,
                s24, s25, s26, s27, s28, s29, s30, s31>::iv();
            res=vpshufb::v(a, msk);
            return res;
        }
        const __m256i p= const_v8u32<_P0 & 3, _P1 & 3,
                                    _P2 & 3, _P3 & 3,
                                    _P4 & 3, _P5 & 3,
                                    _P6 & 3, _P7 & 3>::iv();
        res= _mm256_castps_si256(
            _mm256_permutevar_ps(_mm256_castsi256_ps(a), p));
    } else if ( ((m1 & m2) == (0x32107654 & m2)) ) {
        res= _mm256_permute2x128_si256(a, a, 0x01);
    } else if ( ((m1 & m2) == (0x76547654 & m2)) ) {
        res= _mm256_permute2x128_si256(a, a, 0x11);
    } else if ( ((m1 & m2) == (0x32103210 & m2)) ) {
        res= _mm256_inserti128_si256(a,
                                     _mm256_castsi256_si128(a),
                                     1);
    } else {
        // general case
        const __m256i p= const_v8u32<_P0 & 7, _P1 & 7,
                                     _P2 & 7, _P3 & 7,
                                     _P4 & 7, _P5 & 7,
                                     _P6 & 7, _P7 & 7>::iv();
        res=_mm256_permutevar8x32_epi32(a, p);
    }
    if (do_zero) {
        const unsigned z0= (_P0<0 ? 0 : -1);
        const unsigned z1= (_P1<0 ? 0 : -1);
        const unsigned z2= (_P2<0 ? 0 : -1);
        const unsigned z3= (_P3<0 ? 0 : -1);
        const unsigned z4= (_P4<0 ? 0 : -1);
        const unsigned z5= (_P5<0 ? 0 : -1);
        const unsigned z6= (_P6<0 ? 0 : -1);
        const unsigned z7= (_P7<0 ? 0 : -1);
        const __m256i zm= const_v8u32<z0, z1, z2, z3,
                                      z4, z5, z6, z7>::iv();
        // zero with AND mask
        res = _mm256_and_si256(res, zm);
    }
    return res;
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
__m256i
cftal::x86::perm2_v8u32<_P0, _P1, _P2, _P3,
                        _P4, _P5, _P6, _P7>::v(__m256i a, __m256i b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const unsigned m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
    // Mask to zero out negative indexes
    const unsigned m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

    if ((m1 & 0x88888888 & m2) == 0) {
        // no elements from b
        return perm1_v8u32<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>::v(a);
    }
    if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
        // no elements from a
        return perm1_v8u32<_P0 & ~8, _P1 & ~8,
                           _P2 & ~8, _P3 & ~8,
                           _P4 & ~8, _P5 & ~8,
                           _P6 & ~8, _P7 & ~8>::v(b);
    }
    const bool sm0 = _P0 < 8;
    const bool sm1 = _P1 < 8;
    const bool sm2 = _P2 < 8;
    const bool sm3 = _P3 < 8;
    const bool sm4 = _P4 < 8;
    const bool sm5 = _P5 < 8;
    const bool sm6 = _P6 < 8;
    const bool sm7 = _P7 < 8;
    if (((m1 & ~0x88888888) ^ 0x76543210) == 0 && m2 == 0xFFFFFFFF) {
        // selecting without shuffling or zeroing
        return select_v8u32<sm0, sm1, sm2, sm3,
                            sm4, sm5, sm6, sm7>::v(a, b);
    }

    const int zz= m2 == 0xFFFFFFFF ? 0 : -1;
    // select all elements to clear or from 1st vector
    const int ma0 = sm0 ? _P0 : zz;
    const int ma1 = sm1 ? _P1 : zz;
    const int ma2 = sm2 ? _P2 : zz;
    const int ma3 = sm3 ? _P3 : zz;
    const int ma4 = sm4 ? _P4 : zz;
    const int ma5 = sm5 ? _P5 : zz;
    const int ma6 = sm6 ? _P6 : zz;
    const int ma7 = sm7 ? _P7 : zz;
    __m256i a1 = perm1_v8u32<ma0, ma1, ma2, ma3,
                             ma4, ma5, ma6, ma7>::v(a);
    // select all elements from second vector
    const int mb0 = sm0 ? 0: (_P0-8);
    const int mb1 = sm1 ? 0: (_P1-8);
    const int mb2 = sm2 ? 0: (_P2-8);
    const int mb3 = sm3 ? 0: (_P3-8);
    const int mb4 = sm4 ? 0: (_P4-8);
    const int mb5 = sm5 ? 0: (_P5-8);
    const int mb6 = sm6 ? 0: (_P6-8);
    const int mb7 = sm7 ? 0: (_P7-8);
    __m256i b1 = perm1_v8u32<mb0, mb1, mb2, mb3,
                             mb4, mb5, mb6, mb7>::v(b);
    return select_v8u32<sm0, sm1, sm2, sm3,
                        sm4, sm5, sm6, sm7>::v(a1 ,b1);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15,
          int _P16, int _P17, int _P18, int _P19,
          int _P20, int _P21, int _P22, int _P23,
          int _P24, int _P25, int _P26, int _P27,
          int _P28, int _P29, int _P30, int _P31>
inline
__m256i
cftal::x86::
perm1_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::
v(__m256i a)
{
    constexpr const uint32_t
        _UP00=_P00, _UP01=_P01, _UP02=_P02, _UP03=_P03,
        _UP04=_P04, _UP05=_P05, _UP06=_P06, _UP07=_P07,
        _UP08=_P08, _UP09=_P09, _UP10=_P10, _UP11=_P11,
        _UP12=_P12, _UP13=_P13, _UP14=_P14, _UP15=_P15,
        _UP16=_P16, _UP17=_P17, _UP18=_P18, _UP19=_P19,
        _UP20=_P20, _UP21=_P21, _UP22=_P22, _UP23=_P23,
        _UP24=_P24, _UP25=_P25, _UP26=_P26, _UP27=_P27,
        _UP28=_P28, _UP29=_P29, _UP30=_P30, _UP31=_P31;

    constexpr const bool lh_from_lo_lane=
        (_P00 < 16) && (_P01 < 16) && (_P02 < 16) && (_P03 < 16) &&
        (_P04 < 16) && (_P05 < 16) && (_P06 < 16) && (_P07 < 16) &&
        (_P08 < 16) && (_P09 < 16) && (_P10 < 16) && (_P11 < 16) &&
        (_P12 < 16) && (_P13 < 16) && (_P14 < 16) && (_P15 < 16);
    constexpr const bool hh_from_hi_lane=
        (_UP16 > 15) && (_UP17 > 15) && (_UP18 > 15) && (_UP19 > 15) &&
        (_UP20 > 15) && (_UP21 > 15) && (_UP22 > 15) && (_UP23 > 15) &&
        (_UP24 > 15) && (_UP25 > 15) && (_UP26 > 15) && (_UP27 > 15) &&
        (_UP28 > 15) && (_UP29 > 15) && (_UP30 > 15) && (_UP31 > 15);
    constexpr const bool lh_from_hi_lane=
        (_UP00 > 15) && (_UP01 > 15) && (_UP02 > 15) && (_UP03 > 15) &&
        (_UP04 > 15) && (_UP05 > 15) && (_UP06 > 15) && (_UP07 > 15) &&
        (_UP08 > 15) && (_UP09 > 15) && (_UP10 > 15) && (_UP11 > 15) &&
        (_UP12 > 15) && (_UP13 > 15) && (_UP14 > 15) && (_UP15 > 15);
    constexpr const bool hh_from_lo_lane=
        (_P16 < 16) && (_P17 < 16) && (_P18 < 16) && (_P19 < 16) &&
        (_P20 < 16) && (_P21 < 16) && (_P22 < 16) && (_P23 < 16) &&
        (_P24 < 16) && (_P25 < 16) && (_P26 < 16) && (_P27 < 16) &&
        (_P28 < 16) && (_P29 < 16) && (_P30 < 16) && (_P31 < 16);
    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0) ||
        (_P16 < 0) || (_P17 < 0) || (_P18 < 0) || (_P19 < 0) ||
        (_P20 < 0) || (_P21 < 0) || (_P22 < 0) || (_P23 < 0) ||
        (_P24 < 0) || (_P25 < 0) || (_P26 < 0) || (_P27 < 0) ||
        (_P28 < 0) || (_P29 < 0) || (_P30 < 0) || (_P31 < 0);
    constexpr const bool no_perm=
        (_P00<0 || _P00==0) && (_P01<0 || _P01==1) &&
        (_P02<0 || _P02==2) && (_P03<0 || _P03==3) &&
        (_P04<0 || _P04==4) && (_P05<0 || _P05==5) &&
        (_P06<0 || _P06==6) && (_P07<0 || _P07==7) &&
        (_P08<0 || _P08==8) && (_P09<0 || _P09==9) &&
        (_P10<0 || _P10==10) && (_P11<0 || _P11==11) &&
        (_P12<0 || _P12==12) && (_P13<0 || _P13==13) &&
        (_P14<0 || _P14==14) && (_P15<0 || _P15==15) &&
        (_P16<0 || _P16==16) && (_P17<0 || _P17==17) &&
        (_P18<0 || _P18==18) && (_P19<0 || _P19==19) &&
        (_P20<0 || _P20==20) && (_P21<0 || _P21==21) &&
        (_P22<0 || _P22==22) && (_P23<0 || _P23==23) &&
        (_P24<0 || _P24==24) && (_P25<0 || _P25==25) &&
        (_P26<0 || _P26==26) && (_P27<0 || _P27==27) &&
        (_P28<0 || _P28==28) && (_P29<0 || _P29==29) &&
        (_P30<0 || _P30==30) && (_P31<0 || _P31==31);

    using impl::idx_pair;
    using u16_00_t=idx_pair<_P00, _P01>;
    using u16_01_t=idx_pair<_P02, _P03>;
    using u16_02_t=idx_pair<_P04, _P05>;
    using u16_03_t=idx_pair<_P06, _P07>;
    using u16_04_t=idx_pair<_P08, _P09>;
    using u16_05_t=idx_pair<_P10, _P11>;
    using u16_06_t=idx_pair<_P12, _P13>;
    using u16_07_t=idx_pair<_P14, _P15>;
    using u16_08_t=idx_pair<_P16, _P17>;
    using u16_09_t=idx_pair<_P18, _P19>;
    using u16_10_t=idx_pair<_P20, _P21>;
    using u16_11_t=idx_pair<_P22, _P23>;
    using u16_12_t=idx_pair<_P24, _P25>;
    using u16_13_t=idx_pair<_P26, _P27>;
    using u16_14_t=idx_pair<_P28, _P29>;
    using u16_15_t=idx_pair<_P30, _P31>;

    constexpr const bool u16_perm=
        u16_00_t::is_valid && u16_01_t::is_valid &&
        u16_02_t::is_valid && u16_03_t::is_valid &&
        u16_04_t::is_valid && u16_05_t::is_valid &&
        u16_06_t::is_valid && u16_07_t::is_valid &&
        u16_08_t::is_valid && u16_09_t::is_valid &&
        u16_10_t::is_valid && u16_11_t::is_valid &&
        u16_12_t::is_valid && u16_13_t::is_valid &&
        u16_14_t::is_valid && u16_15_t::is_valid;

    using u32_0_t=idx_pair<u16_00_t::idx, u16_01_t::idx>;
    using u32_1_t=idx_pair<u16_02_t::idx, u16_03_t::idx>;
    using u32_2_t=idx_pair<u16_04_t::idx, u16_05_t::idx>;
    using u32_3_t=idx_pair<u16_06_t::idx, u16_07_t::idx>;
    using u32_4_t=idx_pair<u16_08_t::idx, u16_09_t::idx>;
    using u32_5_t=idx_pair<u16_10_t::idx, u16_11_t::idx>;
    using u32_6_t=idx_pair<u16_12_t::idx, u16_13_t::idx>;
    using u32_7_t=idx_pair<u16_14_t::idx, u16_15_t::idx>;

    constexpr const bool u32_perm= u16_perm &&
        u32_0_t::is_valid && u32_1_t::is_valid &&
        u32_2_t::is_valid && u32_3_t::is_valid &&
        u32_4_t::is_valid && u32_5_t::is_valid &&
        u32_6_t::is_valid && u32_7_t::is_valid;

    if (no_perm) {
        if (zero_elements==false)
            return a;
        constexpr const uint8_t
            a00=_P00<0 ? 0 : 0xff, a01=_P01<0 ? 0 : 0xff,
            a02=_P02<0 ? 0 : 0xff, a03=_P03<0 ? 0 : 0xff,
            a04=_P04<0 ? 0 : 0xff, a05=_P05<0 ? 0 : 0xff,
            a06=_P06<0 ? 0 : 0xff, a07=_P07<0 ? 0 : 0xff,
            a08=_P08<0 ? 0 : 0xff, a09=_P09<0 ? 0 : 0xff,
            a10=_P10<0 ? 0 : 0xff, a11=_P11<0 ? 0 : 0xff,
            a12=_P12<0 ? 0 : 0xff, a13=_P13<0 ? 0 : 0xff,
            a14=_P14<0 ? 0 : 0xff, a15=_P15<0 ? 0 : 0xff,
            a16=_P16<0 ? 0 : 0xff, a17=_P17<0 ? 0 : 0xff,
            a18=_P18<0 ? 0 : 0xff, a19=_P19<0 ? 0 : 0xff,
            a20=_P20<0 ? 0 : 0xff, a21=_P21<0 ? 0 : 0xff,
            a22=_P22<0 ? 0 : 0xff, a23=_P23<0 ? 0 : 0xff,
            a24=_P24<0 ? 0 : 0xff, a25=_P25<0 ? 0 : 0xff,
            a26=_P26<0 ? 0 : 0xff, a27=_P27<0 ? 0 : 0xff,
            a28=_P28<0 ? 0 : 0xff, a29=_P29<0 ? 0 : 0xff,
            a30=_P30<0 ? 0 : 0xff, a31=_P31<0 ? 0 : 0xff;
        const __m256i msk=const_v32u8<
            a00, a01, a02, a03, a04, a05, a06, a07,
            a08, a09, a10, a11, a12, a13, a14, a15,
            a16, a17, a18, a19, a20, a21, a22, a23,
            a24, a25, a26, a27, a28, a29, a30, a31>::iv();
        return _mm256_and_si256(a, msk);
    }

    if (u32_perm && zero_elements==false) {
        return perm1_v8u32<u32_0_t::idx, u32_1_t::idx,
                           u32_2_t::idx, u32_3_t::idx,
                           u32_4_t::idx, u32_5_t::idx,
                           u32_6_t::idx, u32_7_t::idx>::v(a);
    }
    if (lh_from_lo_lane && hh_from_hi_lane) {
        constexpr const uint8_t
            s00=_P00<0 ? -1 : _P00, s01=_P01<0 ? -1 : _P01,
            s02=_P02<0 ? -1 : _P02, s03=_P03<0 ? -1 : _P03,
            s04=_P04<0 ? -1 : _P04, s05=_P05<0 ? -1 : _P05,
            s06=_P06<0 ? -1 : _P06, s07=_P07<0 ? -1 : _P07,
            s08=_P08<0 ? -1 : _P08, s09=_P09<0 ? -1 : _P09,
            s10=_P10<0 ? -1 : _P10, s11=_P11<0 ? -1 : _P11,
            s12=_P12<0 ? -1 : _P12, s13=_P13<0 ? -1 : _P13,
            s14=_P14<0 ? -1 : _P14, s15=_P15<0 ? -1 : _P15,
            s16=_P16<0 ? -1 : _P16-16, s17=_P17<0 ? -1 : _P17-16,
            s18=_P18<0 ? -1 : _P18-16, s19=_P19<0 ? -1 : _P19-16,
            s20=_P20<0 ? -1 : _P20-16, s21=_P21<0 ? -1 : _P21-16,
            s22=_P22<0 ? -1 : _P22-16, s23=_P23<0 ? -1 : _P23-16,
            s24=_P24<0 ? -1 : _P24-16, s25=_P25<0 ? -1 : _P25-16,
            s26=_P26<0 ? -1 : _P26-16, s27=_P27<0 ? -1 : _P27-16,
            s28=_P28<0 ? -1 : _P28-16, s29=_P29<0 ? -1 : _P29-16,
            s30=_P30<0 ? -1 : _P30-16, s31=_P31<0 ? -1 : _P31-16;
        const __m256i msk=const_v32u8<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15,
            s16, s17, s18, s19, s20, s21, s22, s23,
            s24, s25, s26, s27, s28, s29, s30, s31>::iv();
        return vpshufb::v(a, msk);
    }
    if (u32_perm) {
        constexpr const int u32_0= u32_0_t::idx < 0 ? 0 : u32_0_t::idx;
        constexpr const int u32_1= u32_1_t::idx < 0 ? 1 : u32_1_t::idx;
        constexpr const int u32_2= u32_2_t::idx < 0 ? 2 : u32_2_t::idx;
        constexpr const int u32_3= u32_3_t::idx < 0 ? 3 : u32_3_t::idx;
        constexpr const int u32_4= u32_4_t::idx < 0 ? 4 : u32_4_t::idx;
        constexpr const int u32_5= u32_5_t::idx < 0 ? 5 : u32_5_t::idx;
        constexpr const int u32_6= u32_6_t::idx < 0 ? 6 : u32_6_t::idx;
        constexpr const int u32_7= u32_7_t::idx < 0 ? 7 : u32_7_t::idx;
        const __m256i ap=perm1_v8u32<u32_0, u32_1, u32_2, u32_3,
                                     u32_4, u32_5, u32_6, u32_7>::v(a);
        constexpr const uint8_t
            a00=_P00<0 ? 0 : 0xff, a01=_P01<0 ? 0 : 0xff,
            a02=_P02<0 ? 0 : 0xff, a03=_P03<0 ? 0 : 0xff,
            a04=_P04<0 ? 0 : 0xff, a05=_P05<0 ? 0 : 0xff,
            a06=_P06<0 ? 0 : 0xff, a07=_P07<0 ? 0 : 0xff,
            a08=_P08<0 ? 0 : 0xff, a09=_P09<0 ? 0 : 0xff,
            a10=_P10<0 ? 0 : 0xff, a11=_P11<0 ? 0 : 0xff,
            a12=_P12<0 ? 0 : 0xff, a13=_P13<0 ? 0 : 0xff,
            a14=_P14<0 ? 0 : 0xff, a15=_P15<0 ? 0 : 0xff,
            a16=_P16<0 ? 0 : 0xff, a17=_P17<0 ? 0 : 0xff,
            a18=_P18<0 ? 0 : 0xff, a19=_P19<0 ? 0 : 0xff,
            a20=_P20<0 ? 0 : 0xff, a21=_P21<0 ? 0 : 0xff,
            a22=_P22<0 ? 0 : 0xff, a23=_P23<0 ? 0 : 0xff,
            a24=_P24<0 ? 0 : 0xff, a25=_P25<0 ? 0 : 0xff,
            a26=_P26<0 ? 0 : 0xff, a27=_P27<0 ? 0 : 0xff,
            a28=_P28<0 ? 0 : 0xff, a29=_P29<0 ? 0 : 0xff,
            a30=_P30<0 ? 0 : 0xff, a31=_P31<0 ? 0 : 0xff;
        const __m256i msk=const_v32u8<
            a00, a01, a02, a03, a04, a05, a06, a07,
            a08, a09, a10, a11, a12, a13, a14, a15,
            a16, a17, a18, a19, a20, a21, a22, a23,
            a24, a25, a26, a27, a28, a29, a30, a31>::iv();
        return _mm256_and_si256(ap, msk);
    }
    if (lh_from_hi_lane && hh_from_lo_lane) {
        // swap lo and high half
        constexpr const int sh4=shuffle4<2, 3, 0, 1>::val;
        const __m256i as=_mm256_permute4x64_epi64(a, sh4);
        constexpr const uint8_t
            s00=_P00<0 ? -1 : _P00-16, s01=_P01<0 ? -1 : _P01-16,
            s02=_P02<0 ? -1 : _P02-16, s03=_P03<0 ? -1 : _P03-16,
            s04=_P04<0 ? -1 : _P04-16, s05=_P05<0 ? -1 : _P05-16,
            s06=_P06<0 ? -1 : _P06-16, s07=_P07<0 ? -1 : _P07-16,
            s08=_P08<0 ? -1 : _P08-16, s09=_P09<0 ? -1 : _P09-16,
            s10=_P10<0 ? -1 : _P10-16, s11=_P11<0 ? -1 : _P11-16,
            s12=_P12<0 ? -1 : _P12-16, s13=_P13<0 ? -1 : _P13-16,
            s14=_P14<0 ? -1 : _P14-16, s15=_P15<0 ? -1 : _P15-16,
            s16=_P16<0 ? -1 : _P16, s17=_P17<0 ? -1 : _P17,
            s18=_P18<0 ? -1 : _P18, s19=_P19<0 ? -1 : _P19,
            s20=_P20<0 ? -1 : _P20, s21=_P21<0 ? -1 : _P21,
            s22=_P22<0 ? -1 : _P22, s23=_P23<0 ? -1 : _P23,
            s24=_P24<0 ? -1 : _P24, s25=_P25<0 ? -1 : _P25,
            s26=_P26<0 ? -1 : _P26, s27=_P27<0 ? -1 : _P27,
            s28=_P28<0 ? -1 : _P28, s29=_P29<0 ? -1 : _P29,
            s30=_P30<0 ? -1 : _P30, s31=_P31<0 ? -1 : _P31;
        const __m256i msk=const_v32u8<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15,
            s16, s17, s18, s19, s20, s21, s22, s23,
            s24, s25, s26, s27, s28, s29, s30, s31>::iv();
        return vpshufb::v(as, msk);
    }
    if (lh_from_lo_lane && hh_from_lo_lane) {
        // distribute the low 128bits to high 128bits
        constexpr const int sh4=shuffle4<0, 1, 0, 1>::val;
        const __m256i as=_mm256_permute4x64_epi64(a, sh4);
        constexpr const uint8_t
            s00=_P00<0 ? -1 : _P00, s01=_P01<0 ? -1 : _P01,
            s02=_P02<0 ? -1 : _P02, s03=_P03<0 ? -1 : _P03,
            s04=_P04<0 ? -1 : _P04, s05=_P05<0 ? -1 : _P05,
            s06=_P06<0 ? -1 : _P06, s07=_P07<0 ? -1 : _P07,
            s08=_P08<0 ? -1 : _P08, s09=_P09<0 ? -1 : _P09,
            s10=_P10<0 ? -1 : _P10, s11=_P11<0 ? -1 : _P11,
            s12=_P12<0 ? -1 : _P12, s13=_P13<0 ? -1 : _P13,
            s14=_P14<0 ? -1 : _P14, s15=_P15<0 ? -1 : _P15,
            s16=_P16<0 ? -1 : _P16, s17=_P17<0 ? -1 : _P17,
            s18=_P18<0 ? -1 : _P18, s19=_P19<0 ? -1 : _P19,
            s20=_P20<0 ? -1 : _P20, s21=_P21<0 ? -1 : _P21,
            s22=_P22<0 ? -1 : _P22, s23=_P23<0 ? -1 : _P23,
            s24=_P24<0 ? -1 : _P24, s25=_P25<0 ? -1 : _P25,
            s26=_P26<0 ? -1 : _P26, s27=_P27<0 ? -1 : _P27,
            s28=_P28<0 ? -1 : _P28, s29=_P29<0 ? -1 : _P29,
            s30=_P30<0 ? -1 : _P30, s31=_P31<0 ? -1 : _P31;
        const __m256i msk=const_v32u8<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15,
            s16, s17, s18, s19, s20, s21, s22, s23,
            s24, s25, s26, s27, s28, s29, s30, s31>::iv();
        return vpshufb::v(as, msk);
    }
    if (lh_from_hi_lane && hh_from_hi_lane) {
        // distribute the high 128bits to low 128bits
        constexpr const int sh4=shuffle4<2, 3, 2, 3>::val;
        const __m256i as=_mm256_permute4x64_epi64(a, sh4);
        constexpr const uint8_t
            s00=_P00<0 ? -1 : _P00-16, s01=_P01<0 ? -1 : _P01-16,
            s02=_P02<0 ? -1 : _P02-16, s03=_P03<0 ? -1 : _P03-16,
            s04=_P04<0 ? -1 : _P04-16, s05=_P05<0 ? -1 : _P05-16,
            s06=_P06<0 ? -1 : _P06-16, s07=_P07<0 ? -1 : _P07-16,
            s08=_P08<0 ? -1 : _P08-16, s09=_P09<0 ? -1 : _P09-16,
            s10=_P10<0 ? -1 : _P10-16, s11=_P11<0 ? -1 : _P11-16,
            s12=_P12<0 ? -1 : _P12-16, s13=_P13<0 ? -1 : _P13-16,
            s14=_P14<0 ? -1 : _P14-16, s15=_P15<0 ? -1 : _P15-16,
            s16=_P16<0 ? -1 : _P16-16, s17=_P17<0 ? -1 : _P17-16,
            s18=_P18<0 ? -1 : _P18-16, s19=_P19<0 ? -1 : _P19-16,
            s20=_P20<0 ? -1 : _P20-16, s21=_P21<0 ? -1 : _P21-16,
            s22=_P22<0 ? -1 : _P22-16, s23=_P23<0 ? -1 : _P23-16,
            s24=_P24<0 ? -1 : _P24-16, s25=_P25<0 ? -1 : _P25-16,
            s26=_P26<0 ? -1 : _P26-16, s27=_P27<0 ? -1 : _P27-16,
            s28=_P28<0 ? -1 : _P28-16, s29=_P29<0 ? -1 : _P29-16,
            s30=_P30<0 ? -1 : _P30-16, s31=_P31<0 ? -1 : _P31-16;
        const __m256i msk=const_v32u8<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15,
            s16, s17, s18, s19, s20, s21, s22, s23,
            s24, s25, s26, s27, s28, s29, s30, s31>::iv();
        return vpshufb::v(as, msk);
    }
    // swap lo and high half
    constexpr const int sh4=shuffle4<2, 3, 0, 1>::val;
    const __m256i as=_mm256_permute4x64_epi64(a, sh4);
    // shuffle the original values
    constexpr const uint8_t
        o00=_UP00 > 15 ? -1 : _P00, o01=_UP01 > 15 ? -1 : _P01,
        o02=_UP02 > 15 ? -1 : _P02, o03=_UP03 > 15 ? -1 : _P03,
        o04=_UP04 > 15 ? -1 : _P04, o05=_UP05 > 15 ? -1 : _P05,
        o06=_UP06 > 15 ? -1 : _P06, o07=_UP07 > 15 ? -1 : _P07,
        o08=_UP08 > 15 ? -1 : _P08, o09=_UP09 > 15 ? -1 : _P09,
        o10=_UP10 > 15 ? -1 : _P10, o11=_UP11 > 15 ? -1 : _P11,
        o12=_UP12 > 15 ? -1 : _P12, o13=_UP13 > 15 ? -1 : _P13,
        o14=_UP14 > 15 ? -1 : _P14, o15=_UP15 > 15 ? -1 : _P15,
        o16=_P16 < 16 ? -1 : _P16-16, o17=_P17 < 16 ? -1 : _P17-16,
        o18=_P18 < 16 ? -1 : _P18-16, o19=_P19 < 16 ? -1 : _P19-16,
        o20=_P20 < 16 ? -1 : _P20-16, o21=_P21 < 16 ? -1 : _P21-16,
        o22=_P22 < 16 ? -1 : _P22-16, o23=_P23 < 16 ? -1 : _P23-16,
        o24=_P24 < 16 ? -1 : _P24-16, o25=_P25 < 16 ? -1 : _P25-16,
        o26=_P26 < 16 ? -1 : _P26-16, o27=_P27 < 16 ? -1 : _P27-16,
        o28=_P28 < 16 ? -1 : _P28-16, o29=_P29 < 16 ? -1 : _P29-16,
        o30=_P30 < 16 ? -1 : _P30-16, o31=_P31 < 16 ? -1 : _P31-16;
    const __m256i msk=const_v32u8<
        o00, o01, o02, o03, o04, o05, o06, o07,
        o08, o09, o10, o11, o12, o13, o14, o15,
        o16, o17, o18, o19, o20, o21, o22, o23,
        o24, o25, o26, o27, o28, o29, o30, o31>::iv();
    const __m256i v0=vpshufb::v(a, msk);
    // shuffle the swapped values
    constexpr const uint8_t
        p00=_P00 < 16 ? -1 : _P00-16, p01=_P01 < 16 ? -1 : _P01-16,
        p02=_P02 < 16 ? -1 : _P02-16, p03=_P03 < 16 ? -1 : _P03-16,
        p04=_P04 < 16 ? -1 : _P04-16, p05=_P05 < 16 ? -1 : _P05-16,
        p06=_P06 < 16 ? -1 : _P06-16, p07=_P07 < 16 ? -1 : _P07-16,
        p08=_P08 < 16 ? -1 : _P08-16, p09=_P09 < 16 ? -1 : _P09-16,
        p10=_P10 < 16 ? -1 : _P10-16, p11=_P11 < 16 ? -1 : _P11-16,
        p12=_P12 < 16 ? -1 : _P12-16, p13=_P13 < 16 ? -1 : _P13-16,
        p14=_P14 < 16 ? -1 : _P14-16, p15=_P15 < 16 ? -1 : _P15-16,
        p16=_UP16 > 15 ? -1 : _P16, p17=_UP17 > 15 ? -1 : _P17,
        p18=_UP18 > 15 ? -1 : _P18, p19=_UP19 > 15 ? -1 : _P19,
        p20=_UP20 > 15 ? -1 : _P20, p21=_UP21 > 15 ? -1 : _P21,
        p22=_UP22 > 15 ? -1 : _P22, p23=_UP23 > 15 ? -1 : _P23,
        p24=_UP24 > 15 ? -1 : _P24, p25=_UP25 > 15 ? -1 : _P25,
        p26=_UP26 > 15 ? -1 : _P26, p27=_UP27 > 15 ? -1 : _P27,
        p28=_UP28 > 15 ? -1 : _P28, p29=_UP29 > 15 ? -1 : _P29,
        p30=_UP30 > 15 ? -1 : _P30, p31=_UP31 > 15 ? -1 : _P31;
    const __m256i msk_sw=const_v32u8<
        p00, p01, p02, p03, p04, p05, p06, p07,
        p08, p09, p10, p11, p12, p13, p14, p15,
        p16, p17, p18, p19, p20, p21, p22, p23,
        p24, p25, p26, p27, p28, p29, p30, p31>::iv();
    const __m256i v1=vpshufb::v(as, msk_sw);
    // or the values together
    const __m256i r=_mm256_or_si256(v0, v1);
    return r;
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15,
          int _P16, int _P17, int _P18, int _P19,
          int _P20, int _P21, int _P22, int _P23,
          int _P24, int _P25, int _P26, int _P27,
          int _P28, int _P29, int _P30, int _P31>
inline
__m256i
cftal::x86::
perm2_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
            _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
            _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::
v(__m256i a, __m256i b)
{
    constexpr const uint32_t
        _UP00=_P00, _UP01=_P01, _UP02=_P02, _UP03=_P03,
        _UP04=_P04, _UP05=_P05, _UP06=_P06, _UP07=_P07,
        _UP08=_P08, _UP09=_P09, _UP10=_P10, _UP11=_P11,
        _UP12=_P12, _UP13=_P13, _UP14=_P14, _UP15=_P15,
        _UP16=_P16, _UP17=_P17, _UP18=_P18, _UP19=_P19,
        _UP20=_P20, _UP21=_P21, _UP22=_P22, _UP23=_P23,
        _UP24=_P24, _UP25=_P25, _UP26=_P26, _UP27=_P27,
        _UP28=_P28, _UP29=_P29, _UP30=_P30, _UP31=_P31;

    constexpr const bool a_only=
        (_P00 < 32) && (_P01 < 32) && (_P02 < 32) && (_P03 < 32) &&
        (_P04 < 32) && (_P05 < 32) && (_P06 < 32) && (_P07 < 32) &&
        (_P08 < 32) && (_P09 < 32) && (_P10 < 32) && (_P11 < 32) &&
        (_P12 < 32) && (_P13 < 32) && (_P14 < 32) && (_P15 < 32) &&
        (_P16 < 32) && (_P17 < 32) && (_P18 < 32) && (_P19 < 32) &&
        (_P20 < 32) && (_P21 < 32) && (_P22 < 32) && (_P23 < 32) &&
        (_P24 < 32) && (_P25 < 32) && (_P26 < 32) && (_P27 < 32) &&
        (_P28 < 32) && (_P29 < 32) && (_P30 < 32) && (_P31 < 32);
    constexpr const bool b_only=
        (_UP00 > 31) && (_UP01 > 31) && (_UP02 > 31) && (_UP03 > 31) &&
        (_UP04 > 31) && (_UP05 > 31) && (_UP06 > 31) && (_UP07 > 31) &&
        (_UP08 > 31) && (_UP09 > 31) && (_UP10 > 31) && (_UP11 > 31) &&
        (_UP12 > 31) && (_UP13 > 31) && (_UP14 > 31) && (_UP15 > 31) &&
        (_UP16 > 31) && (_UP17 > 31) && (_UP18 > 31) && (_UP19 > 31) &&
        (_UP20 > 31) && (_UP21 > 31) && (_UP22 > 31) && (_UP23 > 31) &&
        (_UP24 > 31) && (_UP25 > 31) && (_UP26 > 31) && (_UP27 > 31) &&
        (_UP28 > 31) && (_UP29 > 31) && (_UP30 > 31) && (_UP31 > 31);

    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0) ||
        (_P16 < 0) || (_P17 < 0) || (_P18 < 0) || (_P19 < 0) ||
        (_P20 < 0) || (_P21 < 0) || (_P22 < 0) || (_P23 < 0) ||
        (_P24 < 0) || (_P25 < 0) || (_P26 < 0) || (_P27 < 0) ||
        (_P28 < 0) || (_P29 < 0) || (_P30 < 0) || (_P31 < 0);

    // elements to select from vector a or zero
    constexpr const int32_t
        a00 = _P00 > 31 ? -1 : _P00, a01 = _P01 > 31 ? -1 : _P01,
        a02 = _P02 > 31 ? -1 : _P02, a03 = _P03 > 31 ? -1 : _P03,
        a04 = _P04 > 31 ? -1 : _P04, a05 = _P05 > 31 ? -1 : _P05,
        a06 = _P06 > 31 ? -1 : _P06, a07 = _P07 > 31 ? -1 : _P07,
        a08 = _P08 > 31 ? -1 : _P08, a09 = _P09 > 31 ? -1 : _P09,
        a10 = _P10 > 31 ? -1 : _P10, a11 = _P11 > 31 ? -1 : _P11,
        a12 = _P12 > 31 ? -1 : _P12, a13 = _P13 > 31 ? -1 : _P13,
        a14 = _P14 > 31 ? -1 : _P14, a15 = _P15 > 31 ? -1 : _P15,
        a16 = _P16 > 31 ? -1 : _P16, a17 = _P17 > 31 ? -1 : _P17,
        a18 = _P18 > 31 ? -1 : _P18, a19 = _P19 > 31 ? -1 : _P19,
        a20 = _P20 > 31 ? -1 : _P20, a21 = _P21 > 31 ? -1 : _P21,
        a22 = _P22 > 31 ? -1 : _P22, a23 = _P23 > 31 ? -1 : _P23,
        a24 = _P24 > 31 ? -1 : _P24, a25 = _P25 > 31 ? -1 : _P25,
        a26 = _P26 > 31 ? -1 : _P26, a27 = _P27 > 31 ? -1 : _P27,
        a28 = _P28 > 31 ? -1 : _P28, a29 = _P29 > 31 ? -1 : _P29,
        a30 = _P30 > 31 ? -1 : _P30, a31 = _P31 > 31 ? -1 : _P31;

    // elements to select from vector b or zero
    constexpr const int32_t
        b00 = _P00 < 32 ? -1 : _P00-32, b01 = _P01 < 32 ? -1 : _P01-32,
        b02 = _P02 < 32 ? -1 : _P02-32, b03 = _P03 < 32 ? -1 : _P03-32,
        b04 = _P04 < 32 ? -1 : _P04-32, b05 = _P05 < 32 ? -1 : _P05-32,
        b06 = _P06 < 32 ? -1 : _P06-32, b07 = _P07 < 32 ? -1 : _P07-32,
        b08 = _P08 < 32 ? -1 : _P08-32, b09 = _P09 < 32 ? -1 : _P09-32,
        b10 = _P10 < 32 ? -1 : _P10-32, b11 = _P11 < 32 ? -1 : _P11-32,
        b12 = _P12 < 32 ? -1 : _P12-32, b13 = _P13 < 32 ? -1 : _P13-32,
        b14 = _P14 < 32 ? -1 : _P14-32, b15 = _P15 < 32 ? -1 : _P15-32,
        b16 = _P16 < 32 ? -1 : _P16-32, b17 = _P17 < 32 ? -1 : _P17-32,
        b18 = _P18 < 32 ? -1 : _P18-32, b19 = _P19 < 32 ? -1 : _P19-32,
        b20 = _P20 < 32 ? -1 : _P20-32, b21 = _P21 < 32 ? -1 : _P21-32,
        b22 = _P22 < 32 ? -1 : _P22-32, b23 = _P23 < 32 ? -1 : _P23-32,
        b24 = _P24 < 32 ? -1 : _P24-32, b25 = _P25 < 32 ? -1 : _P25-32,
        b26 = _P26 < 32 ? -1 : _P26-32, b27 = _P27 < 32 ? -1 : _P27-32,
        b28 = _P28 < 32 ? -1 : _P28-32, b29 = _P29 < 32 ? -1 : _P29-32,
        b30 = _P30 < 32 ? -1 : _P30-32, b31 = _P31 < 32 ? -1 : _P31-32;

    constexpr const bool no_perm=
        (_P00<0 || _P00==0 || _P00==32) &&
        (_P01<0 || _P01==1 || _P01==33) &&
        (_P02<0 || _P02==2 || _P02==34) &&
        (_P03<0 || _P03==3 || _P03==35) &&
        (_P04<0 || _P04==4 || _P04==36) &&
        (_P05<0 || _P05==5 || _P05==37) &&
        (_P06<0 || _P06==6 || _P06==38) &&
        (_P07<0 || _P07==7 || _P07==39) &&
        (_P08<0 || _P08==8 || _P08==40) &&
        (_P09<0 || _P09==9 || _P09==41) &&
        (_P10<0 || _P10==10 || _P10==42) &&
        (_P11<0 || _P11==11 || _P11==43) &&
        (_P12<0 || _P12==12 || _P12==44) &&
        (_P13<0 || _P13==13 || _P13==45) &&
        (_P14<0 || _P14==14 || _P14==46) &&
        (_P15<0 || _P15==15 || _P15==47) &&
        (_P16<0 || _P16==16 || _P16==48) &&
        (_P17<0 || _P17==17 || _P17==49) &&
        (_P18<0 || _P18==18 || _P18==50) &&
        (_P19<0 || _P19==19 || _P19==51) &&
        (_P20<0 || _P20==20 || _P20==52) &&
        (_P21<0 || _P21==21 || _P21==53) &&
        (_P22<0 || _P22==22 || _P22==54) &&
        (_P23<0 || _P23==23 || _P23==55) &&
        (_P24<0 || _P24==24 || _P24==56) &&
        (_P25<0 || _P25==25 || _P25==57) &&
        (_P26<0 || _P26==26 || _P26==58) &&
        (_P27<0 || _P27==27 || _P27==59) &&
        (_P28<0 || _P28==28 || _P28==60) &&
        (_P29<0 || _P29==29 || _P29==61) &&
        (_P30<0 || _P30==30 || _P30==62) &&
        (_P31<0 || _P31==31 || _P31==63);

    if (a_only) {
        const __m256i ap=perm1_v32u8<
            a00, a01, a02, a03, a04, a05, a06, a07,
            a08, a09, a10, a11, a12, a13, a14, a15,
            a16, a17, a18, a19, a20, a21, a22, a23,
            a24, a25, a26, a27, a28, a29, a30, a31>::v(a);
        return ap;
    }
    if (b_only) {
        const __m256i bp=perm1_v32u8<
            b00, b01, b02, b03, b04, b05, b06, b07,
            b08, b09, b10, b11, b12, b13, b14, b15,
            b16, b17, b18, b19, b20, b21, b22, b23,
            b24, b25, b26, b27, b28, b29, b30, b31>::v(b);
        return bp;
    }
    if (no_perm) {
        constexpr const bool
            s00 = _P00 < 32 ? true: false, s01 = _P01 < 32 ? true: false,
            s02 = _P02 < 32 ? true: false, s03 = _P03 < 32 ? true: false,
            s04 = _P04 < 32 ? true: false, s05 = _P05 < 32 ? true: false,
            s06 = _P06 < 32 ? true: false, s07 = _P07 < 32 ? true: false,
            s08 = _P08 < 32 ? true: false, s09 = _P09 < 32 ? true: false,
            s10 = _P10 < 32 ? true: false, s11 = _P11 < 32 ? true: false,
            s12 = _P12 < 32 ? true: false, s13 = _P13 < 32 ? true: false,
            s14 = _P14 < 32 ? true: false, s15 = _P15 < 32 ? true: false,
            s16 = _P16 < 32 ? true: false, s17 = _P17 < 32 ? true: false,
            s18 = _P18 < 32 ? true: false, s19 = _P19 < 32 ? true: false,
            s20 = _P20 < 32 ? true: false, s21 = _P21 < 32 ? true: false,
            s22 = _P22 < 32 ? true: false, s23 = _P23 < 32 ? true: false,
            s24 = _P24 < 32 ? true: false, s25 = _P25 < 32 ? true: false,
            s26 = _P26 < 32 ? true: false, s27 = _P27 < 32 ? true: false,
            s28 = _P28 < 32 ? true: false, s29 = _P29 < 32 ? true: false,
            s30 = _P30 < 32 ? true: false, s31 = _P31 < 32 ? true: false;
        const __m256i rs=select_v32u8<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15,
            s16, s17, s18, s19, s20, s21, s22, s23,
            s24, s25, s26, s27, s28, s29, s30, s31>::v(a, b);
        if (zero_elements==false)
            return rs;
        constexpr const uint8_t
            z00 = _P00 < 0 ? 0x00: 0xff, z01 = _P01 < 0 ? 0x00: 0xff,
            z02 = _P02 < 0 ? 0x00: 0xff, z03 = _P03 < 0 ? 0x00: 0xff,
            z04 = _P04 < 0 ? 0x00: 0xff, z05 = _P05 < 0 ? 0x00: 0xff,
            z06 = _P06 < 0 ? 0x00: 0xff, z07 = _P07 < 0 ? 0x00: 0xff,
            z08 = _P08 < 0 ? 0x00: 0xff, z09 = _P09 < 0 ? 0x00: 0xff,
            z10 = _P10 < 0 ? 0x00: 0xff, z11 = _P11 < 0 ? 0x00: 0xff,
            z12 = _P12 < 0 ? 0x00: 0xff, z13 = _P13 < 0 ? 0x00: 0xff,
            z14 = _P14 < 0 ? 0x00: 0xff, z15 = _P15 < 0 ? 0x00: 0xff,
            z16 = _P16 < 0 ? 0x00: 0xff, z17 = _P17 < 0 ? 0x00: 0xff,
            z18 = _P18 < 0 ? 0x00: 0xff, z19 = _P19 < 0 ? 0x00: 0xff,
            z20 = _P20 < 0 ? 0x00: 0xff, z21 = _P21 < 0 ? 0x00: 0xff,
            z22 = _P22 < 0 ? 0x00: 0xff, z23 = _P23 < 0 ? 0x00: 0xff,
            z24 = _P24 < 0 ? 0x00: 0xff, z25 = _P25 < 0 ? 0x00: 0xff,
            z26 = _P26 < 0 ? 0x00: 0xff, z27 = _P27 < 0 ? 0x00: 0xff,
            z28 = _P28 < 0 ? 0x00: 0xff, z29 = _P29 < 0 ? 0x00: 0xff,
            z30 = _P30 < 0 ? 0x00: 0xff, z31 = _P31 < 0 ? 0x00: 0xff;
        const __m256i zm=const_v32u8<
            z00, z01, z02, z03, z04, z05, z06, z07,
            z08, z09, z10, z11, z12, z13, z14, z15,
            z16, z17, z18, z19, z20, z21, z22, z23,
            z24, z25, z26, z27, z28, z29, z30, z31>::iv();
        return _mm256_and_si256(rs, zm);
    }
    const __m256i ap=perm1_v32u8<
        a00, a01, a02, a03, a04, a05, a06, a07,
        a08, a09, a10, a11, a12, a13, a14, a15,
        a16, a17, a18, a19, a20, a21, a22, a23,
        a24, a25, a26, a27, a28, a29, a30, a31>::v(a);
    const __m256i bp=perm1_v32u8<
        b00, b01, b02, b03, b04, b05, b06, b07,
        b08, b09, b10, b11, b12, b13, b14, b15,
        b16, b17, b18, b19, b20, b21, b22, b23,
        b24, b25, b26, b27, b28, b29, b30, b31>::v(b);
    const __m256i r=_mm256_or_si256(ap, bp);
    return r;
}


#endif // __AVX2__
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m512d
cftal::x86::
perm1_v8f64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m512d a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const uint32_t m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 7>::m;
    const uint32_t m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;
    // const bool do_zero= m2 != 0xFFFFFFFF;

    if (m2 == 0xFFFFFFFF)
        return _mm512_setzero_pd();

    const __mmask8 zm=
        set_mask_if_gt_zero::m8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>();

    if (((m1 ^ 0x76543210) & m2) == 0) {
        // no shuffling:
        return _mm512_maskz_mov_pd(zm, a);
    }
    // full permute:
    const __m512i pperm=const_v8u64<
        _P0 & 7, _P1 & 7, _P2 & 7, _P3 & 7,
        _P4 & 7, _P5 & 7, _P6 & 7, _P7 & 7>::iv();
    if (zm != 0xFF) {
        return _mm512_maskz_permutexvar_pd(zm, pperm, a);
    }
    return _mm512_permutexvar_pd(pperm, a);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m512d
cftal::x86::
perm2_v8f64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m512d a, __m512d b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const uint32_t m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
    // Mask to zero out negative indexes
    const uint32_t m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

    if ((m1 & 0x88888888 & m2) == 0) {
        // no elements from b
        return perm1_v8f64<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>::v(a);
    }
    if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
        // no elements from a
        return perm1_v8f64<_P0 & ~8, _P1 & ~8,
                           _P2 & ~8, _P3 & ~8,
                           _P4 & ~8, _P5 & ~8,
                           _P6 & ~8, _P7 & ~8>::v(b);
    }
    if (((m1 & ~0x88888888) ^ 0x76543210) == 0 && m2 == 0xFFFFFFFF) {
        // selecting without shuffling or zeroing
        const bool sm0 = _P0 < 8;
        const bool sm1 = _P1 < 8;
        const bool sm2 = _P2 < 8;
        const bool sm3 = _P3 < 8;
        const bool sm4 = _P4 < 8;
        const bool sm5 = _P5 < 8;
        const bool sm6 = _P6 < 8;
        const bool sm7 = _P7 < 8;
        return select_v8f64<sm0, sm1, sm2, sm3,
                            sm4, sm5, sm6, sm7>::v(a, b);
    }
    const __mmask8 zm=
        set_mask_if_gt_zero::m8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>();
    // full permute:
    const __m512i pperm=const_v8u64<
        _P0 & 15, _P1 & 15, _P2 & 15, _P3 & 15,
        _P4 & 15, _P5 & 15, _P6 & 15, _P7 & 15>::iv();

    if (zm != 0xFF) {
        return _mm512_maskz_permutex2var_pd(zm, a, pperm, b);
    }
    return _mm512_permutex2var_pd(a, pperm, b);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}


template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
inline
__m512
cftal::x86::
perm1_v16f32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m512 a)
{
    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0);
    constexpr const bool no_perm=
        (_P00<0 || _P00==0) && (_P01<0 || _P01==1) &&
        (_P02<0 || _P02==2) && (_P03<0 || _P03==3) &&
        (_P04<0 || _P04==4) && (_P05<0 || _P05==5) &&
        (_P06<0 || _P06==6) && (_P07<0 || _P07==7) &&
        (_P08<0 || _P08==8) && (_P09<0 || _P09==9) &&
        (_P10<0 || _P10==10) && (_P11<0 || _P11==11) &&
        (_P12<0 || _P12==12) && (_P13<0 || _P13==13) &&
        (_P14<0 || _P14==14) && (_P15<0 || _P15==15);

    const __mmask16 zm= set_mask_if_gt_zero::
        m16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>();

    if (no_perm) {
        if (!zero_elements)
            return a;
        return _mm512_maskz_mov_ps(zm, a);
    }
    constexpr const uint32_t c00 = (_P00 < 0) ? -1 : _P00 & 15;
    constexpr const uint32_t c01 = (_P01 < 0) ? -1 : _P01 & 15;
    constexpr const uint32_t c02 = (_P02 < 0) ? -1 : _P02 & 15;
    constexpr const uint32_t c03 = (_P03 < 0) ? -1 : _P03 & 15;
    constexpr const uint32_t c04 = (_P04 < 0) ? -1 : _P04 & 15;
    constexpr const uint32_t c05 = (_P05 < 0) ? -1 : _P05 & 15;
    constexpr const uint32_t c06 = (_P06 < 0) ? -1 : _P06 & 15;
    constexpr const uint32_t c07 = (_P07 < 0) ? -1 : _P07 & 15;
    constexpr const uint32_t c08 = (_P08 < 0) ? -1 : _P08 & 15;
    constexpr const uint32_t c09 = (_P09 < 0) ? -1 : _P09 & 15;
    constexpr const uint32_t c10 = (_P10 < 0) ? -1 : _P10 & 15;
    constexpr const uint32_t c11 = (_P11 < 0) ? -1 : _P11 & 15;
    constexpr const uint32_t c12 = (_P12 < 0) ? -1 : _P12 & 15;
    constexpr const uint32_t c13 = (_P13 < 0) ? -1 : _P13 & 15;
    constexpr const uint32_t c14 = (_P14 < 0) ? -1 : _P14 & 15;
    constexpr const uint32_t c15 = (_P15 < 0) ? -1 : _P15 & 15;
    const __m512i msk=const_v16u32<c00, c01, c02, c03,
                                   c04, c05, c06, c07,
                                   c08, c09, c10, c11,
                                   c12, c13, c14, c15>::iv();
    if (zm != 0xFFFF) {
        return _mm512_maskz_permutexvar_ps(zm, msk, a);
    }
    return _mm512_permutexvar_ps(msk, a);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
inline
__m512
cftal::x86::
perm2_v16f32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m512 a, __m512 b)
{
    constexpr const uint32_t
        _UP00=_P00, _UP01=_P01, _UP02=_P02, _UP03=_P03,
        _UP04=_P04, _UP05=_P05, _UP06=_P06, _UP07=_P07,
        _UP08=_P08, _UP09=_P09, _UP10=_P10, _UP11=_P11,
        _UP12=_P12, _UP13=_P13, _UP14=_P14, _UP15=_P15;

    constexpr const bool a_only=
        (_P00 < 16) && (_P01 < 16) && (_P02 < 16) && (_P03 < 16) &&
        (_P04 < 16) && (_P05 < 16) && (_P06 < 16) && (_P07 < 16) &&
        (_P08 < 16) && (_P09 < 16) && (_P10 < 16) && (_P11 < 16) &&
        (_P12 < 16) && (_P13 < 16) && (_P14 < 16) && (_P15 < 16);
    constexpr const bool b_only=
        (_UP00 > 15) && (_UP01 > 15) && (_UP02 > 15) && (_UP03 > 15) &&
        (_UP04 > 15) && (_UP05 > 15) && (_UP06 > 15) && (_UP07 > 15) &&
        (_UP08 > 15) && (_UP09 > 15) && (_UP10 > 15) && (_UP11 > 15) &&
        (_UP12 > 15) && (_UP13 > 15) && (_UP14 > 15) && (_UP15 > 15);

    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0);

    constexpr const bool no_perm=
        (_P00<0 || _P00==0 || _P00==16) &&
        (_P01<0 || _P01==1 || _P01==17) &&
        (_P02<0 || _P02==2 || _P02==18) &&
        (_P03<0 || _P03==3 || _P03==19) &&
        (_P04<0 || _P04==4 || _P04==20) &&
        (_P05<0 || _P05==5 || _P05==21) &&
        (_P06<0 || _P06==6 || _P06==22) &&
        (_P07<0 || _P07==7 || _P07==23) &&
        (_P08<0 || _P08==8 || _P08==24) &&
        (_P09<0 || _P09==9 || _P09==25) &&
        (_P10<0 || _P10==10 || _P10==26) &&
        (_P11<0 || _P11==11 || _P11==27) &&
        (_P12<0 || _P12==12 || _P12==28) &&
        (_P13<0 || _P13==13 || _P13==29) &&
        (_P14<0 || _P14==14 || _P14==30) &&
        (_P15<0 || _P15==15 || _P15==31);


    if (a_only) {
        const __m512 ap=perm1_v16f32<
            _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::v(a);
        return ap;
    }
    if (b_only) {
        // elements to select from vector b or zero
        constexpr const int32_t
            b00 = _P00 < 16 ? -1 : _P00-16, b01 = _P01 < 16 ? -1 : _P01-16,
            b02 = _P02 < 16 ? -1 : _P02-16, b03 = _P03 < 16 ? -1 : _P03-16,
            b04 = _P04 < 16 ? -1 : _P04-16, b05 = _P05 < 16 ? -1 : _P05-16,
            b06 = _P06 < 16 ? -1 : _P06-16, b07 = _P07 < 16 ? -1 : _P07-16,
            b08 = _P08 < 16 ? -1 : _P08-16, b09 = _P09 < 16 ? -1 : _P09-16,
            b10 = _P10 < 16 ? -1 : _P10-16, b11 = _P11 < 16 ? -1 : _P11-16,
            b12 = _P12 < 16 ? -1 : _P12-16, b13 = _P13 < 16 ? -1 : _P13-16,
            b14 = _P14 < 16 ? -1 : _P14-16, b15 = _P15 < 16 ? -1 : _P15-16;
        const __m512 bp=perm1_v16f32<
            b00, b01, b02, b03, b04, b05, b06, b07,
            b08, b09, b10, b11, b12, b13, b14, b15>::v(b);
        return bp;
    }

    if (no_perm && zero_elements==false) {
        constexpr const bool
            s00 = _P00 < 16 ? true: false, s01 = _P01 < 16 ? true: false,
            s02 = _P02 < 16 ? true: false, s03 = _P03 < 16 ? true: false,
            s04 = _P04 < 16 ? true: false, s05 = _P05 < 16 ? true: false,
            s06 = _P06 < 16 ? true: false, s07 = _P07 < 16 ? true: false,
            s08 = _P08 < 16 ? true: false, s09 = _P09 < 16 ? true: false,
            s10 = _P10 < 16 ? true: false, s11 = _P11 < 16 ? true: false,
            s12 = _P12 < 16 ? true: false, s13 = _P13 < 16 ? true: false,
            s14 = _P14 < 16 ? true: false, s15 = _P15 < 16 ? true: false;
        return select_v16f32<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15>::v(a, b);
    }

    const __mmask16 zm= set_mask_if_gt_zero::
        m16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>();

    const __m512i msk=const_v16u32<_P00, _P01, _P02, _P03,
                                   _P04, _P05, _P06, _P07,
                                   _P08, _P09, _P10, _P11,
                                   _P12, _P13, _P14, _P15>::iv();
    if (zm != 0xFFFF) {
        return _mm512_maskz_permutex2var_ps(zm, a, msk, b);
    }
    return _mm512_permutex2var_ps(a, msk, b);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
inline
__m512i
cftal::x86::
perm1_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m512i a)
{
    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0);
    constexpr const bool no_perm=
        (_P00<0 || _P00==0) && (_P01<0 || _P01==1) &&
        (_P02<0 || _P02==2) && (_P03<0 || _P03==3) &&
        (_P04<0 || _P04==4) && (_P05<0 || _P05==5) &&
        (_P06<0 || _P06==6) && (_P07<0 || _P07==7) &&
        (_P08<0 || _P08==8) && (_P09<0 || _P09==9) &&
        (_P10<0 || _P10==10) && (_P11<0 || _P11==11) &&
        (_P12<0 || _P12==12) && (_P13<0 || _P13==13) &&
        (_P14<0 || _P14==14) && (_P15<0 || _P15==15);

    const __mmask16 zm= set_mask_if_gt_zero::
        m16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>();

    if (no_perm) {
        if (!zero_elements)
            return a;
        return _mm512_maskz_mov_epi32(zm, a);
    }
    constexpr const uint32_t c00 = (_P00 < 0) ? -1 : _P00 & 15;
    constexpr const uint32_t c01 = (_P01 < 0) ? -1 : _P01 & 15;
    constexpr const uint32_t c02 = (_P02 < 0) ? -1 : _P02 & 15;
    constexpr const uint32_t c03 = (_P03 < 0) ? -1 : _P03 & 15;
    constexpr const uint32_t c04 = (_P04 < 0) ? -1 : _P04 & 15;
    constexpr const uint32_t c05 = (_P05 < 0) ? -1 : _P05 & 15;
    constexpr const uint32_t c06 = (_P06 < 0) ? -1 : _P06 & 15;
    constexpr const uint32_t c07 = (_P07 < 0) ? -1 : _P07 & 15;
    constexpr const uint32_t c08 = (_P08 < 0) ? -1 : _P08 & 15;
    constexpr const uint32_t c09 = (_P09 < 0) ? -1 : _P09 & 15;
    constexpr const uint32_t c10 = (_P10 < 0) ? -1 : _P10 & 15;
    constexpr const uint32_t c11 = (_P11 < 0) ? -1 : _P11 & 15;
    constexpr const uint32_t c12 = (_P12 < 0) ? -1 : _P12 & 15;
    constexpr const uint32_t c13 = (_P13 < 0) ? -1 : _P13 & 15;
    constexpr const uint32_t c14 = (_P14 < 0) ? -1 : _P14 & 15;
    constexpr const uint32_t c15 = (_P15 < 0) ? -1 : _P15 & 15;
    const __m512i msk=const_v16u32<c00, c01, c02, c03,
                                   c04, c05, c06, c07,
                                   c08, c09, c10, c11,
                                   c12, c13, c14, c15>::iv();
    if (zm != 0xFFFF) {
        return _mm512_maskz_permutexvar_epi32(zm, msk, a);
    }
    return _mm512_permutexvar_epi32(msk, a);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
inline
__m512i
cftal::x86::
perm2_v16u32<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
             _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
v(__m512i a, __m512i b)
{
    constexpr const uint32_t
        _UP00=_P00, _UP01=_P01, _UP02=_P02, _UP03=_P03,
        _UP04=_P04, _UP05=_P05, _UP06=_P06, _UP07=_P07,
        _UP08=_P08, _UP09=_P09, _UP10=_P10, _UP11=_P11,
        _UP12=_P12, _UP13=_P13, _UP14=_P14, _UP15=_P15;

    constexpr const bool a_only=
        (_P00 < 16) && (_P01 < 16) && (_P02 < 16) && (_P03 < 16) &&
        (_P04 < 16) && (_P05 < 16) && (_P06 < 16) && (_P07 < 16) &&
        (_P08 < 16) && (_P09 < 16) && (_P10 < 16) && (_P11 < 16) &&
        (_P12 < 16) && (_P13 < 16) && (_P14 < 16) && (_P15 < 16);
    constexpr const bool b_only=
        (_UP00 > 15) && (_UP01 > 15) && (_UP02 > 15) && (_UP03 > 15) &&
        (_UP04 > 15) && (_UP05 > 15) && (_UP06 > 15) && (_UP07 > 15) &&
        (_UP08 > 15) && (_UP09 > 15) && (_UP10 > 15) && (_UP11 > 15) &&
        (_UP12 > 15) && (_UP13 > 15) && (_UP14 > 15) && (_UP15 > 15);

    constexpr const bool zero_elements=
        (_P00 < 0) || (_P01 < 0) || (_P02 < 0) || (_P03 < 0) ||
        (_P04 < 0) || (_P05 < 0) || (_P06 < 0) || (_P07 < 0) ||
        (_P08 < 0) || (_P09 < 0) || (_P10 < 0) || (_P11 < 0) ||
        (_P12 < 0) || (_P13 < 0) || (_P14 < 0) || (_P15 < 0);

    constexpr const bool no_perm=
        (_P00<0 || _P00==0 || _P00==16) &&
        (_P01<0 || _P01==1 || _P01==17) &&
        (_P02<0 || _P02==2 || _P02==18) &&
        (_P03<0 || _P03==3 || _P03==19) &&
        (_P04<0 || _P04==4 || _P04==20) &&
        (_P05<0 || _P05==5 || _P05==21) &&
        (_P06<0 || _P06==6 || _P06==22) &&
        (_P07<0 || _P07==7 || _P07==23) &&
        (_P08<0 || _P08==8 || _P08==24) &&
        (_P09<0 || _P09==9 || _P09==25) &&
        (_P10<0 || _P10==10 || _P10==26) &&
        (_P11<0 || _P11==11 || _P11==27) &&
        (_P12<0 || _P12==12 || _P12==28) &&
        (_P13<0 || _P13==13 || _P13==29) &&
        (_P14<0 || _P14==14 || _P14==30) &&
        (_P15<0 || _P15==15 || _P15==31);


    if (a_only) {
        const __m512i ap=perm1_v16u32<
            _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::v(a);
        return ap;
    }
    if (b_only) {
        // elements to select from vector b or zero
        constexpr const int32_t
            b00 = _P00 < 16 ? -1 : _P00-16, b01 = _P01 < 16 ? -1 : _P01-16,
            b02 = _P02 < 16 ? -1 : _P02-16, b03 = _P03 < 16 ? -1 : _P03-16,
            b04 = _P04 < 16 ? -1 : _P04-16, b05 = _P05 < 16 ? -1 : _P05-16,
            b06 = _P06 < 16 ? -1 : _P06-16, b07 = _P07 < 16 ? -1 : _P07-16,
            b08 = _P08 < 16 ? -1 : _P08-16, b09 = _P09 < 16 ? -1 : _P09-16,
            b10 = _P10 < 16 ? -1 : _P10-16, b11 = _P11 < 16 ? -1 : _P11-16,
            b12 = _P12 < 16 ? -1 : _P12-16, b13 = _P13 < 16 ? -1 : _P13-16,
            b14 = _P14 < 16 ? -1 : _P14-16, b15 = _P15 < 16 ? -1 : _P15-16;
        const __m512i bp=perm1_v16u32<
            b00, b01, b02, b03, b04, b05, b06, b07,
            b08, b09, b10, b11, b12, b13, b14, b15>::v(b);
        return bp;
    }

    if (no_perm && zero_elements==false) {
        constexpr const bool
            s00 = _P00 < 16 ? true: false, s01 = _P01 < 16 ? true: false,
            s02 = _P02 < 16 ? true: false, s03 = _P03 < 16 ? true: false,
            s04 = _P04 < 16 ? true: false, s05 = _P05 < 16 ? true: false,
            s06 = _P06 < 16 ? true: false, s07 = _P07 < 16 ? true: false,
            s08 = _P08 < 16 ? true: false, s09 = _P09 < 16 ? true: false,
            s10 = _P10 < 16 ? true: false, s11 = _P11 < 16 ? true: false,
            s12 = _P12 < 16 ? true: false, s13 = _P13 < 16 ? true: false,
            s14 = _P14 < 16 ? true: false, s15 = _P15 < 16 ? true: false;
        return select_v16u32<
            s00, s01, s02, s03, s04, s05, s06, s07,
            s08, s09, s10, s11, s12, s13, s14, s15>::v(a, b);
    }

    const __mmask16 zm= set_mask_if_gt_zero::
        m16<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
            _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>();
    const __m512i pperm=const_v16u32<_P00, _P01, _P02, _P03,
                                     _P04, _P05, _P06, _P07,
                                     _P08, _P09, _P10, _P11,
                                     _P12, _P13, _P14, _P15>::iv();
    if (zm != 0xFFFF) {
        return _mm512_maskz_permutex2var_epi32(zm, a, pperm, b);
    }
    return _mm512_permutex2var_epi32(a, pperm, b);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m512i
cftal::x86::
perm1_v8u64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m512i a)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    const uint32_t m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 7>::m;
    const uint32_t m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;
    // const bool do_zero= m2 != 0xFFFFFFFF;

    if (m2 == 0xFFFFFFFF)
        return _mm512_setzero_si512();

    const __mmask8 zm=
        set_mask_if_gt_zero::m8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>();

    if (((m1 ^ 0x76543210) & m2) == 0) {
        // no shuffling:
        return _mm512_maskz_mov_epi64(zm, a);
    }
    // full permute:
    const __m512i pperm=const_v8u64<
        _P0 & 7, _P1 & 7, _P2 & 7, _P3 & 7,
        _P4 & 7, _P5 & 7, _P6 & 7, _P7 & 7>::iv();
    if (zm != 0xFF) {
        return _mm512_maskz_permutexvar_epi64(zm, pperm, a);
    }
    return _mm512_permutexvar_epi64(pperm, a);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m512i
cftal::x86::
perm2_v8u64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(__m512i a, __m512i b)
{
#if 0
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtautological-compare"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
    // Combine all the indexes into a single bitfield, with 4 bits
    // for each
    const uint32_t m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
    // Mask to zero out negative indexes
    const uint32_t m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

    if ((m1 & 0x88888888 & m2) == 0) {
        // no elements from b
        return perm1_v8u64<_P0, _P1, _P2, _P3,
                           _P4, _P5, _P6, _P7>::v(a);
    }
    if (((m1^0x88888888) & 0x88888888 & m2) == 0) {
        // no elements from a
        return perm1_v8u64<_P0 & ~8, _P1 & ~8,
                           _P2 & ~8, _P3 & ~8,
                           _P4 & ~8, _P5 & ~8,
                           _P6 & ~8, _P7 & ~8>::v(b);
    }
    if (((m1 & ~0x88888888) ^ 0x76543210) == 0 && m2 == 0xFFFFFFFF) {
        // selecting without shuffling or zeroing
        const bool sm0 = _P0 < 8;
        const bool sm1 = _P1 < 8;
        const bool sm2 = _P2 < 8;
        const bool sm3 = _P3 < 8;
        const bool sm4 = _P4 < 8;
        const bool sm5 = _P5 < 8;
        const bool sm6 = _P6 < 8;
        const bool sm7 = _P7 < 8;
        return select_v8u64<sm0, sm1, sm2, sm3,
                            sm4, sm5, sm6, sm7>::v(a, b);
    }
    const __mmask8 zm=
        set_mask_if_gt_zero::m8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>();
    // full permute:
    const __m512i pperm=const_v8u64<
        _P0 & 15, _P1 & 15, _P2 & 15, _P3 & 15,
        _P4 & 15, _P5 & 15, _P6 & 15, _P7 & 15>::iv();
    if (zm != 0xFF) {
        return _mm512_maskz_permutex2var_epi64(zm, a, pperm, b);
    }
    return _mm512_permutex2var_epi64(a, pperm, b);
#if 0
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
#endif
}

#endif


template <int _P0, int _P1>
inline
__m128d cftal::x86::perm_v2f64(__m128d a)
{
    static_assert(_P0 < 2,
                  "cftal::x86::perm_v2f64(a) : _P0 < 2");
    static_assert(_P1 < 2,
                  "cftal::x86::perm_v2f64(a) : _P1 < 2");
    return perm1_v2f64<_P0, _P1>::v(a);
}


template <int _P0, int _P1>
inline
__m128d cftal::x86::perm_v2f64(__m128d a, __m128d b)
{
    static_assert(_P0 < 4,
                  "cftal::x86::perm_v2f64(a, b) : _P0 < 4");
    static_assert(_P1 < 4,
                  "cftal::x86::perm_v2f64(a, b) : _P1 < 4");
    return perm2_v2f64<_P0, _P1>::v(a, b);
}

#if defined (__AVX__)
template <int _P0, int _P1, int _P2, int _P3>
inline
__m256d cftal::x86::perm_v4f64(__m256d a)
{
    static_assert(_P0 < 4,
                  "cftal::x86::perm_v4f64(a) : _P0 < 4");
    static_assert(_P1 < 4,
                  "cftal::x86::perm_v4f64(a) : _P1 < 4");
    static_assert(_P2 < 4,
                  "cftal::x86::perm_v4f64(a) : _P2 < 4");
    static_assert(_P3 < 4,
                  "cftal::x86::perm_v4f64(a) : _P3 < 4");
    return perm1_v4f64<_P0, _P1, _P2, _P3>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m256d cftal::x86::perm_v4f64(__m256d a, __m256d b)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v4f64(a, b) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v4f64(a, b) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v4f64(a, b) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v4f64(a, b) : _P3 < 8");
    return perm2_v4f64<_P0, _P1, _P2, _P3>::v(a, b);
}

#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
__m512d cftal::x86::perm_v8f64(__m512d a)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v8f64(a) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v8f64(a) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v8f64(a) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v8f64(a) : _P3 < 8");
    static_assert(_P4 < 8,
                  "cftal::x86::perm_v8f64(a) : _P4 < 8");
    static_assert(_P5 < 8,
                  "cftal::x86::perm_v8f64(a) : _P5 < 8");
    static_assert(_P6 < 8,
                  "cftal::x86::perm_v8f64(a) : _P6 < 8");
    static_assert(_P7 < 8,
                  "cftal::x86::perm_v8f64(a) : _P7 < 8");
    return perm1_v8f64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m512d cftal::x86::perm_v8f64(__m512d a, __m512d b)
{
    static_assert(_P0 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P0 < 16");
    static_assert(_P1 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P1 < 16");
    static_assert(_P2 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P2 < 16");
    static_assert(_P3 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P3 < 16");
    static_assert(_P4 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P4 < 16");
    static_assert(_P5 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P5 < 16");
    static_assert(_P6 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P6 < 16");
    static_assert(_P7 < 16,
                  "cftal::x86::perm_v8f64(a, b) : _P7 < 16");
    return perm2_v8f64<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a, b);
}
#endif

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128 cftal::x86::perm_v4f32(__m128 a)
{
    static_assert(_P0 < 4,
                  "cftal::x86::perm_v4f32(a) : _P0 < 4");
    static_assert(_P1 < 4,
                  "cftal::x86::perm_v4f32(a) : _P1 < 4");
    static_assert(_P2 < 4,
                  "cftal::x86::perm_v4f32(a) : _P2 < 4");
    static_assert(_P3 < 4,
                  "cftal::x86::perm_v4f32(a) : _P3 < 4");
    return perm1_v4f32<_P0, _P1, _P2, _P3>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128 cftal::x86::perm_v4f32(__m128 a, __m128 b)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v4f32(a, b) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v4f32(a, b) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v4f32(a, b) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v4f32(a, b) : _P3 < 8");
    return perm2_v4f32<_P0, _P1, _P2, _P3>::v(a, b);
}

#if defined (__AVX__)
template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
__m256 cftal::x86::perm_v8f32(__m256 a)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v8f32(a) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v8f32(a) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v8f32(a) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v8f32(a) : _P3 < 8");
    static_assert(_P4 < 8,
                  "cftal::x86::perm_v8f32(a) : _P4 < 8");
    static_assert(_P5 < 8,
                  "cftal::x86::perm_v8f32(a) : _P5 < 8");
    static_assert(_P6 < 8,
                  "cftal::x86::perm_v8f32(a) : _P6 < 8");
    static_assert(_P7 < 8,
                  "cftal::x86::perm_v8f32(a) : _P7 < 8");
    return perm1_v8f32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m256 cftal::x86::perm_v8f32(__m256 a, __m256 b)
{
    static_assert(_P0 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P0 < 16");
    static_assert(_P1 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P1 < 16");
    static_assert(_P2 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P2 < 16");
    static_assert(_P3 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P3 < 16");
    static_assert(_P4 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P4 < 16");
    static_assert(_P5 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P5 < 16");
    static_assert(_P6 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P6 < 16");
    static_assert(_P7 < 16,
                  "cftal::x86::perm_v8f32(a, b) : _P7 < 16");
    return perm2_v8f32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a, b);
}

#endif

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
__m128i cftal::x86::perm_v16u8(__m128i a)
{
    static_assert(_P00 < 16,
                  "cftal::x86::perm_v16u8(a) : _P00 < 16");
    static_assert(_P01 < 16,
                  "cftal::x86::perm_v16u8(a) : _P01 < 16");
    static_assert(_P02 < 16,
                  "cftal::x86::perm_v16u8(a) : _P02 < 16");
    static_assert(_P03 < 16,
                  "cftal::x86::perm_v16u8(a) : _P03 < 16");
    static_assert(_P04 < 16,
                  "cftal::x86::perm_v16u8(a) : _P04 < 16");
    static_assert(_P05 < 16,
                  "cftal::x86::perm_v16u8(a) : _P05 < 16");
    static_assert(_P06 < 16,
                  "cftal::x86::perm_v16u8(a) : _P06 < 16");
    static_assert(_P07 < 16,
                  "cftal::x86::perm_v16u8(a) : _P07 < 16");
    static_assert(_P08 < 16,
                  "cftal::x86::perm_v16u8(a) : _P08 < 16");
    static_assert(_P09 < 16,
                  "cftal::x86::perm_v16u8(a) : _P09 < 16");
    static_assert(_P10 < 16,
                  "cftal::x86::perm_v16u8(a) : _P10 < 16");
    static_assert(_P11 < 16,
                  "cftal::x86::perm_v16u8(a) : _P11 < 16");
    static_assert(_P12 < 16,
                  "cftal::x86::perm_v16u8(a) : _P12 < 16");
    static_assert(_P13 < 16,
                  "cftal::x86::perm_v16u8(a) : _P13 < 16");
    static_assert(_P14 < 16,
                  "cftal::x86::perm_v16u8(a) : _P14 < 16");
    static_assert(_P15 < 16,
                  "cftal::x86::perm_v16u8(a) : _P15 < 16");
    return perm1_v16u8<_P00, _P01, _P02, _P03,
                       _P04, _P05, _P06, _P07,
                       _P08, _P09, _P10, _P11,
                       _P12, _P13, _P14, _P15>::v(a);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
__m128i cftal::x86::perm_v16u8(__m128i a, __m128i b)
{
    static_assert(_P00 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P00 < 32");
    static_assert(_P01 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P01 < 32");
    static_assert(_P02 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P02 < 32");
    static_assert(_P03 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P03 < 32");
    static_assert(_P04 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P04 < 32");
    static_assert(_P05 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P05 < 32");
    static_assert(_P06 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P06 < 32");
    static_assert(_P07 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P07 < 32");
    static_assert(_P08 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P08 < 32");
    static_assert(_P09 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P09 < 32");
    static_assert(_P10 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P10 < 32");
    static_assert(_P11 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P11 < 32");
    static_assert(_P12 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P12 < 32");
    static_assert(_P13 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P13 < 32");
    static_assert(_P14 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P14 < 32");
    static_assert(_P15 < 32,
                  "cftal::x86::perm_v16u8(a, b) : _P15 < 32");
    return perm2_v16u8<_P00, _P01, _P02, _P03,
                       _P04, _P05, _P06, _P07,
                       _P08, _P09, _P10, _P11,
                       _P12, _P13, _P14, _P15>::v(a, b);
}

#if defined (__AVX2__)

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
__m256i cftal::x86::perm_v16u16(__m256i a)
{
    static_assert(_P00 < 16,
                  "cftal::x86::perm_v16u16(a) : _P00 < 16");
    static_assert(_P01 < 16,
                  "cftal::x86::perm_v16u16(a) : _P01 < 16");
    static_assert(_P02 < 16,
                  "cftal::x86::perm_v16u16(a) : _P02 < 16");
    static_assert(_P03 < 16,
                  "cftal::x86::perm_v16u16(a) : _P03 < 16");
    static_assert(_P04 < 16,
                  "cftal::x86::perm_v16u16(a) : _P04 < 16");
    static_assert(_P05 < 16,
                  "cftal::x86::perm_v16u16(a) : _P05 < 16");
    static_assert(_P06 < 16,
                  "cftal::x86::perm_v16u16(a) : _P06 < 16");
    static_assert(_P07 < 16,
                  "cftal::x86::perm_v16u16(a) : _P07 < 16");
    static_assert(_P08 < 16,
                  "cftal::x86::perm_v16u16(a) : _P08 < 16");
    static_assert(_P09 < 16,
                  "cftal::x86::perm_v16u16(a) : _P09 < 16");
    static_assert(_P10 < 16,
                  "cftal::x86::perm_v16u16(a) : _P10 < 16");
    static_assert(_P11 < 16,
                  "cftal::x86::perm_v16u16(a) : _P11 < 16");
    static_assert(_P12 < 16,
                  "cftal::x86::perm_v16u16(a) : _P12 < 16");
    static_assert(_P13 < 16,
                  "cftal::x86::perm_v16u16(a) : _P13 < 16");
    static_assert(_P14 < 16,
                  "cftal::x86::perm_v16u16(a) : _P14 < 16");
    static_assert(_P15 < 16,
                  "cftal::x86::perm_v16u16(a) : _P15 < 16");
    return perm1_v32u8<_P00*2, _P00*2+1, _P01*2, _P01*2+1,
                       _P02*2, _P02*2+1, _P03*2, _P03*2+1,
                       _P04*2, _P04*2+1, _P05*2, _P05*2+1,
                       _P06*2, _P06*2+1, _P07*2, _P07*2+1,
                       _P08*2, _P08*2+1, _P09*2, _P09*2+1,
                       _P10*2, _P10*2+1, _P11*2, _P11*2+1,
                       _P12*2, _P12*2+1, _P13*2, _P13*2+1,
                       _P14*2, _P14*2+1, _P15*2, _P15*2+1>::v(a);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
__m256i cftal::x86::perm_v16u16(__m256i a, __m256i b)
{
    static_assert(_P00 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P00 < 32");
    static_assert(_P01 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P01 < 32");
    static_assert(_P02 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P02 < 32");
    static_assert(_P03 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P03 < 32");
    static_assert(_P04 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P04 < 32");
    static_assert(_P05 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P05 < 32");
    static_assert(_P06 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P06 < 32");
    static_assert(_P07 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P07 < 32");
    static_assert(_P08 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P08 < 32");
    static_assert(_P09 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P09 < 32");
    static_assert(_P10 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P10 < 32");
    static_assert(_P11 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P11 < 32");
    static_assert(_P12 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P12 < 32");
    static_assert(_P13 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P13 < 32");
    static_assert(_P14 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P14 < 32");
    static_assert(_P15 < 32,
                  "cftal::x86::perm_v16u16(a, b) : _P15 < 32");
    return perm2_v32u8<_P00*2, _P00*2+1, _P01*2, _P01*2+1,
                       _P02*2, _P02*2+1, _P03*2, _P03*2+1,
                       _P04*2, _P04*2+1, _P05*2, _P05*2+1,
                       _P06*2, _P06*2+1, _P07*2, _P07*2+1,
                       _P08*2, _P08*2+1, _P09*2, _P09*2+1,
                       _P10*2, _P10*2+1, _P11*2, _P11*2+1,
                       _P12*2, _P12*2+1, _P13*2, _P13*2+1,
                       _P14*2, _P14*2+1, _P15*2, _P15*2+1>::v(a, b);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15,
          int _P16, int _P17, int _P18, int _P19,
          int _P20, int _P21, int _P22, int _P23,
          int _P24, int _P25, int _P26, int _P27,
          int _P28, int _P29, int _P30, int _P31>
__m256i cftal::x86::perm_v32u8(__m256i a)
{
    static_assert(_P00 < 32,
                  "cftal::x86::perm_v32u8(a) : _P00 < 32");
    static_assert(_P01 < 32,
                  "cftal::x86::perm_v32u8(a) : _P01 < 32");
    static_assert(_P02 < 32,
                  "cftal::x86::perm_v32u8(a) : _P02 < 32");
    static_assert(_P03 < 32,
                  "cftal::x86::perm_v32u8(a) : _P03 < 32");
    static_assert(_P04 < 32,
                  "cftal::x86::perm_v32u8(a) : _P04 < 32");
    static_assert(_P05 < 32,
                  "cftal::x86::perm_v32u8(a) : _P05 < 32");
    static_assert(_P06 < 32,
                  "cftal::x86::perm_v32u8(a) : _P06 < 32");
    static_assert(_P07 < 32,
                  "cftal::x86::perm_v32u8(a) : _P07 < 32");
    static_assert(_P08 < 32,
                  "cftal::x86::perm_v32u8(a) : _P08 < 32");
    static_assert(_P09 < 32,
                  "cftal::x86::perm_v32u8(a) : _P09 < 32");
    static_assert(_P10 < 32,
                  "cftal::x86::perm_v32u8(a) : _P10 < 32");
    static_assert(_P11 < 32,
                  "cftal::x86::perm_v32u8(a) : _P11 < 32");
    static_assert(_P12 < 32,
                  "cftal::x86::perm_v32u8(a) : _P12 < 32");
    static_assert(_P13 < 32,
                  "cftal::x86::perm_v32u8(a) : _P13 < 32");
    static_assert(_P14 < 32,
                  "cftal::x86::perm_v32u8(a) : _P14 < 32");
    static_assert(_P15 < 32,
                  "cftal::x86::perm_v32u8(a) : _P15 < 32");
    static_assert(_P16 < 32,
                  "cftal::x86::perm_v32u8(a) : _P16 < 32");
    static_assert(_P17 < 32,
                  "cftal::x86::perm_v32u8(a) : _P17 < 32");
    static_assert(_P18 < 32,
                  "cftal::x86::perm_v32u8(a) : _P18 < 32");
    static_assert(_P19 < 32,
                  "cftal::x86::perm_v32u8(a) : _P19 < 32");
    static_assert(_P20 < 32,
                  "cftal::x86::perm_v32u8(a) : _P20 < 32");
    static_assert(_P21 < 32,
                  "cftal::x86::perm_v32u8(a) : _P21 < 32");
    static_assert(_P22 < 32,
                  "cftal::x86::perm_v32u8(a) : _P22 < 32");
    static_assert(_P23 < 32,
                  "cftal::x86::perm_v32u8(a) : _P23 < 32");
    static_assert(_P24 < 32,
                  "cftal::x86::perm_v32u8(a) : _P24 < 32");
    static_assert(_P25 < 32,
                  "cftal::x86::perm_v32u8(a) : _P25 < 32");
    static_assert(_P26 < 32,
                  "cftal::x86::perm_v32u8(a) : _P26 < 32");
    static_assert(_P27 < 32,
                  "cftal::x86::perm_v32u8(a) : _P27 < 32");
    static_assert(_P28 < 32,
                  "cftal::x86::perm_v32u8(a) : _P28 < 32");
    static_assert(_P29 < 32,
                  "cftal::x86::perm_v32u8(a) : _P29 < 32");
    static_assert(_P30 < 32,
                  "cftal::x86::perm_v32u8(a) : _P30 < 32");
    static_assert(_P31 < 32,
                  "cftal::x86::perm_v32u8(a) : _P31 < 32");
    return perm1_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                       _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
                       _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
                       _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::v(a);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15,
          int _P16, int _P17, int _P18, int _P19,
          int _P20, int _P21, int _P22, int _P23,
          int _P24, int _P25, int _P26, int _P27,
          int _P28, int _P29, int _P30, int _P31>
__m256i cftal::x86::perm_v32u8(__m256i a, __m256i b)
{
    static_assert(_P00 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P00 < 64");
    static_assert(_P01 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P01 < 64");
    static_assert(_P02 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P02 < 64");
    static_assert(_P03 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P03 < 64");
    static_assert(_P04 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P04 < 64");
    static_assert(_P05 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P05 < 64");
    static_assert(_P06 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P06 < 64");
    static_assert(_P07 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P07 < 64");
    static_assert(_P08 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P08 < 64");
    static_assert(_P09 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P09 < 64");
    static_assert(_P10 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P10 < 64");
    static_assert(_P11 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P11 < 64");
    static_assert(_P12 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P12 < 64");
    static_assert(_P13 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P13 < 64");
    static_assert(_P14 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P14 < 64");
    static_assert(_P15 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P15 < 64");
    static_assert(_P16 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P16 < 64");
    static_assert(_P17 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P17 < 64");
    static_assert(_P18 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P18 < 64");
    static_assert(_P19 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P19 < 64");
    static_assert(_P20 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P20 < 64");
    static_assert(_P21 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P21 < 64");
    static_assert(_P22 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P22 < 64");
    static_assert(_P23 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P23 < 64");
    static_assert(_P24 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P24 < 64");
    static_assert(_P25 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P25 < 64");
    static_assert(_P26 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P26 < 64");
    static_assert(_P27 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P27 < 64");
    static_assert(_P28 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P28 < 64");
    static_assert(_P29 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P29 < 64");
    static_assert(_P30 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P30 < 64");
    static_assert(_P31 < 64,
                  "cftal::x86::perm_v32u8(a, b) : _P31 < 64");
    return perm2_v32u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                       _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
                       _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
                       _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>::v(a, b);
}

#endif

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i cftal::x86::perm_v8u16(__m128i a)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v8u16(a) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v8u16(a) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v8u16(a) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v8u16(a) : _P3 < 8");
    static_assert(_P4 < 8,
                  "cftal::x86::perm_v8u16(a) : _P4 < 8");
    static_assert(_P5 < 8,
                  "cftal::x86::perm_v8u16(a) : _P5 < 8");
    static_assert(_P6 < 8,
                  "cftal::x86::perm_v8u16(a) : _P6 < 8");
    static_assert(_P7 < 8,
                  "cftal::x86::perm_v8u16(a) : _P7 < 8");
    return perm1_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i cftal::x86::perm_v8u16(__m128i a, __m128i b)
{
    static_assert(_P0 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P0 < 16");
    static_assert(_P1 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P1 < 16");
    static_assert(_P2 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P2 < 16");
    static_assert(_P3 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P3 < 16");
    static_assert(_P4 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P4 < 16");
    static_assert(_P5 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P5 < 16");
    static_assert(_P6 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P6 < 16");
    static_assert(_P7 < 16,
                  "cftal::x86::perm_v8u16(a, b) : _P7 < 16");
    return perm2_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a, b);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128i cftal::x86::perm_v4u32(__m128i a)
{
    static_assert(_P0 < 4,
                  "cftal::x86::perm_v4u32(a) : _P0 < 4");
    static_assert(_P1 < 4,
                  "cftal::x86::perm_v4u32(a) : _P1 < 4");
    static_assert(_P2 < 4,
                  "cftal::x86::perm_v4u32(a) : _P2 < 4");
    static_assert(_P3 < 4,
                  "cftal::x86::perm_v4u32(a) : _P3 < 4");
    return perm1_v4u32<_P0, _P1, _P2, _P3>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128i cftal::x86::perm_v4u32(__m128i a, __m128i b)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v4u32(a, b) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v4u32(a, b) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v4u32(a, b) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v4u32(a, b) : _P3 < 8");
#if defined (__AVX2__)
    __m256i t=_mm256_inserti128_si256(_mm256_castsi128_si256(a), b, 1);
    __m256i r=perm1_v8u32<_P0, _P1, _P2, _P3, 4, 5, 6, 7>::v(t);
    return _mm256_castsi256_si128(r);
#else
    return perm2_v4u32<_P0, _P1, _P2, _P3>::v(a, b);
#endif
}

#if defined (__AVX2__)
template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
__m256i cftal::x86::perm_v8u32(__m256i a)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v8u32(a) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v8u32(a) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v8u32(a) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v8u32(a) : _P3 < 8");
    static_assert(_P4 < 8,
                  "cftal::x86::perm_v8u32(a) : _P4 < 8");
    static_assert(_P5 < 8,
                  "cftal::x86::perm_v8u32(a) : _P5 < 8");
    static_assert(_P6 < 8,
                  "cftal::x86::perm_v8u32(a) : _P6 < 8");
    static_assert(_P7 < 8,
                  "cftal::x86::perm_v8u32(a) : _P7 < 8");
    return perm1_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m256i cftal::x86::perm_v8u32(__m256i a, __m256i b)
{
    static_assert(_P0 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P0 < 16");
    static_assert(_P1 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P1 < 16");
    static_assert(_P2 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P2 < 16");
    static_assert(_P3 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P3 < 16");
    static_assert(_P4 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P4 < 16");
    static_assert(_P5 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P5 < 16");
    static_assert(_P6 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P6 < 16");
    static_assert(_P7 < 16,
                  "cftal::x86::perm_v8u32(a, b) : _P7 < 16");
    return perm2_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a, b);
}
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
__m512i cftal::x86::perm_v16u32(__m512i a)
{
    static_assert(_P00 < 16,
                  "cftal::x86::perm_v16u32(a) : _P00 < 16");
    static_assert(_P01 < 16,
                  "cftal::x86::perm_v16u32(a) : _P01 < 16");
    static_assert(_P02 < 16,
                  "cftal::x86::perm_v16u32(a) : _P02 < 16");
    static_assert(_P03 < 16,
                  "cftal::x86::perm_v16u32(a) : _P03 < 16");
    static_assert(_P04 < 16,
                  "cftal::x86::perm_v16u32(a) : _P04 < 16");
    static_assert(_P05 < 16,
                  "cftal::x86::perm_v16u32(a) : _P05 < 16");
    static_assert(_P06 < 16,
                  "cftal::x86::perm_v16u32(a) : _P06 < 16");
    static_assert(_P07 < 16,
                  "cftal::x86::perm_v16u32(a) : _P07 < 16");
    static_assert(_P08 < 16,
                  "cftal::x86::perm_v16u32(a) : _P08 < 16");
    static_assert(_P09 < 16,
                  "cftal::x86::perm_v16u32(a) : _P09 < 16");
    static_assert(_P10 < 16,
                  "cftal::x86::perm_v16u32(a) : _P10 < 16");
    static_assert(_P11 < 16,
                  "cftal::x86::perm_v16u32(a) : _P11 < 16");
    static_assert(_P12 < 16,
                  "cftal::x86::perm_v16u32(a) : _P12 < 16");
    static_assert(_P13 < 16,
                  "cftal::x86::perm_v16u32(a) : _P13 < 16");
    static_assert(_P14 < 16,
                  "cftal::x86::perm_v16u32(a) : _P14 < 16");
    static_assert(_P15 < 16,
                  "cftal::x86::perm_v16u32(a) : _P15 < 16");
    return perm1_v16u32<_P00, _P01, _P02, _P03,
                        _P04, _P05, _P06, _P07,
                        _P08, _P09, _P10, _P11,
                        _P12, _P13, _P14, _P15>::v(a);
}

template <int _P00, int _P01, int _P02, int _P03,
          int _P04, int _P05, int _P06, int _P07,
          int _P08, int _P09, int _P10, int _P11,
          int _P12, int _P13, int _P14, int _P15>
__m512i cftal::x86::perm_v16u32(__m512i a, __m512i b)
{
    static_assert(_P00 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P00 < 32");
    static_assert(_P01 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P01 < 32");
    static_assert(_P02 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P02 < 32");
    static_assert(_P03 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P03 < 32");
    static_assert(_P04 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P04 < 32");
    static_assert(_P05 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P05 < 32");
    static_assert(_P06 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P06 < 32");
    static_assert(_P07 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P07 < 32");
    static_assert(_P08 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P08 < 32");
    static_assert(_P09 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P09 < 32");
    static_assert(_P10 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P10 < 32");
    static_assert(_P11 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P11 < 32");
    static_assert(_P12 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P12 < 32");
    static_assert(_P13 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P13 < 32");
    static_assert(_P14 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P14 < 32");
    static_assert(_P15 < 32,
                  "cftal::x86::perm_v16u32(a, b) : _P15 < 32");
    return perm2_v16u32<_P00, _P01, _P02, _P03,
                        _P04, _P05, _P06, _P07,
                        _P08, _P09, _P10, _P11,
                        _P12, _P13, _P14, _P15>::v(a, b);
}
#endif

template <int _P0, int _P1>
inline
__m128i cftal::x86::perm_v2u64(__m128i a)
{
    static_assert(_P0 < 2,
                  "cftal::x86::perm_v2u64(a) : _P0 < 2");
    static_assert(_P1 < 2,
                  "cftal::x86::perm_v2u64(a) : _P1 < 2");
    const int p0 = _P0 < 0 ? -1 : _P0 * 2;
    const int p1 = _P0 < 0 ? -1 : _P0 * 2 +1;
    const int p2 = _P1 < 0 ? -1 : _P1 * 2;
    const int p3 = _P1 < 0 ? -1 : _P1 * 2 +1;
    return perm1_v4u32<p0, p1, p2, p3>::v(a);
}

template <int _P0, int _P1>
inline
__m128i cftal::x86::perm_v2u64(__m128i a, __m128i b)
{
    static_assert(_P0 < 4,
                  "cftal::x86::perm_v2u64(a, b) : _P0 < 4");
    static_assert(_P1 < 4,
                  "cftal::x86::perm_v2u64(a, b) : _P1 < 4");
    const int p0 = _P0 < 0 ? -1 : _P0 * 2;
    const int p1 = _P0 < 0 ? -1 : _P0 * 2 +1;
    const int p2 = _P1 < 0 ? -1 : _P1 * 2;
    const int p3 = _P1 < 0 ? -1 : _P1 * 2 +1;
#if defined (__AVX2__)
    __m256i t=_mm256_inserti128_si256(_mm256_castsi128_si256(a), b, 1);
    __m256i r=perm1_v8u32<p0, p1, p2, p3, 4, 5, 6, 7>::v(t);
    return _mm256_castsi256_si128(r);
#else
    return perm2_v4u32<p0, p1, p2, p3>::v(a, b);
#endif
}

#if defined (__AVX2__)
template <int _P0, int _P1, int _P2, int _P3>
inline
__m256i cftal::x86::perm_v4u64(__m256i a)
{
    static_assert(_P0 < 4,
                  "cftal::x86::perm_v4u64(a) : _P0 < 4");
    static_assert(_P1 < 4,
                  "cftal::x86::perm_v4u64(a) : _P1 < 4");
    static_assert(_P2 < 4,
                  "cftal::x86::perm_v4u64(a) : _P2 < 4");
    static_assert(_P3 < 4,
                  "cftal::x86::perm_v4u64(a) : _P3 < 4");
    return perm1_v4u64<_P0, _P1, _P2, _P3>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m256i cftal::x86::perm_v4u64(__m256i a, __m256i b)
{
    static_assert(_P0 < 8,
                  "cftal::x86::perm_v4u64(a, b) : _P0 < 8");
    static_assert(_P1 < 8,
                  "cftal::x86::perm_v4u64(a, b) : _P1 < 8");
    static_assert(_P2 < 8,
                  "cftal::x86::perm_v4u64(a, b) : _P2 < 8");
    static_assert(_P3 < 8,
                  "cftal::x86::perm_v4u64(a, b) : _P3 < 8");
    return perm2_v4u64<_P0, _P1, _P2, _P3>::v(a, b);
}
#endif

// Local variables:
// mode: c++
// end:
#endif
