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
#if !defined (__CFTAL_X86_PERM_H__)
#define __CFTAL_X86_PERM_H__ 1

#include <cftal/config.h>
#include <cftal/x86/ops_0.h>
#include <cftal/x86/ops_1.h>
#include <cftal/x86/select.h>

namespace cftal {

    namespace x86 {

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
        struct perm1_v2f64< 0, 0> : public vunpcklpd {};
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
            : public vunpcklpd {};
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

        template <>
        struct perm2_v8u32<0, 1, 8, 9, 4, 5, 12, 13>
            : public vpunpcklqdq {};

        template <>
        struct perm2_v8u32<2, 3, 10, 11, 6, 7, 14, 15>
            : public vpunpckhqdq {};

        template <>
        struct perm2_v8u32<0, 8, 1, 9, 4, 12, 5, 13>
            : public vpunpckldq {};

        template <>
        struct perm2_v8u32<2, 10, 3, 11, 6, 14, 7, 15>
            : public vpunpckhdq {};

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

#endif // __AVX2__
#if defined (__AVX512F__)
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
#if defined (__AVX512F__)
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m512d perm_v8f64(__m512d a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m512d perm_v8f64(__m512d a, __m512d b);
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
    constexpr const bool sm00 = _P00 < 16;
    constexpr const bool sm01 = _P01 < 16;
    constexpr const bool sm02 = _P02 < 16;
    constexpr const bool sm03 = _P03 < 16;
    constexpr const bool sm04 = _P04 < 16;
    constexpr const bool sm05 = _P05 < 16;
    constexpr const bool sm06 = _P06 < 16;
    constexpr const bool sm07 = _P07 < 16;
    constexpr const bool sm08 = _P08 < 16;
    constexpr const bool sm09 = _P09 < 16;
    constexpr const bool sm10 = _P10 < 16;
    constexpr const bool sm11 = _P11 < 16;
    constexpr const bool sm12 = _P12 < 16;
    constexpr const bool sm13 = _P13 < 16;
    constexpr const bool sm14 = _P14 < 16;
    constexpr const bool sm15 = _P15 < 16;
    // select all elements to clear or from first vector
    constexpr const int ma00 = sm00 ? ((_P00 < 0) ? -1 : _P00 & 15) : -1;
    constexpr const int ma01 = sm01 ? ((_P01 < 0) ? -1 : _P01 & 15) : -1;
    constexpr const int ma02 = sm02 ? ((_P02 < 0) ? -1 : _P02 & 15) : -1;
    constexpr const int ma03 = sm03 ? ((_P03 < 0) ? -1 : _P03 & 15) : -1;
    constexpr const int ma04 = sm04 ? ((_P04 < 0) ? -1 : _P04 & 15) : -1;
    constexpr const int ma05 = sm05 ? ((_P05 < 0) ? -1 : _P05 & 15) : -1;
    constexpr const int ma06 = sm06 ? ((_P06 < 0) ? -1 : _P06 & 15) : -1;
    constexpr const int ma07 = sm07 ? ((_P07 < 0) ? -1 : _P07 & 15) : -1;
    constexpr const int ma08 = sm08 ? ((_P08 < 0) ? -1 : _P08 & 15) : -1;
    constexpr const int ma09 = sm09 ? ((_P09 < 0) ? -1 : _P09 & 15) : -1;
    constexpr const int ma10 = sm10 ? ((_P10 < 0) ? -1 : _P10 & 15) : -1;
    constexpr const int ma11 = sm11 ? ((_P11 < 0) ? -1 : _P11 & 15) : -1;
    constexpr const int ma12 = sm12 ? ((_P12 < 0) ? -1 : _P12 & 15) : -1;
    constexpr const int ma13 = sm13 ? ((_P13 < 0) ? -1 : _P13 & 15) : -1;
    constexpr const int ma14 = sm14 ? ((_P14 < 0) ? -1 : _P14 & 15) : -1;
    constexpr const int ma15 = sm15 ? ((_P15 < 0) ? -1 : _P15 & 15) : -1;
    __m128i ma=perm1_v16u8<ma00, ma01, ma02, ma03,
                           ma04, ma05, ma06, ma07,
                           ma08, ma09, ma10, ma11,
                           ma12, ma13, ma14, ma15>::v(a);
    constexpr const int mb00 = sm00 ? -1 : _P00-16;
    constexpr const int mb01 = sm01 ? -1 : _P01-16;
    constexpr const int mb02 = sm02 ? -1 : _P02-16;
    constexpr const int mb03 = sm03 ? -1 : _P03-16;
    constexpr const int mb04 = sm04 ? -1 : _P04-16;
    constexpr const int mb05 = sm05 ? -1 : _P05-16;
    constexpr const int mb06 = sm06 ? -1 : _P06-16;
    constexpr const int mb07 = sm07 ? -1 : _P07-16;
    constexpr const int mb08 = sm08 ? -1 : _P08-16;
    constexpr const int mb09 = sm09 ? -1 : _P09-16;
    constexpr const int mb10 = sm10 ? -1 : _P10-16;
    constexpr const int mb11 = sm11 ? -1 : _P11-16;
    constexpr const int mb12 = sm12 ? -1 : _P12-16;
    constexpr const int mb13 = sm13 ? -1 : _P13-16;
    constexpr const int mb14 = sm14 ? -1 : _P14-16;
    constexpr const int mb15 = sm15 ? -1 : _P15-16;
    __m128i mb=perm1_v16u8<mb00, mb01, mb02, mb03,
                           mb04, mb05, mb06, mb07,
                           mb08, mb09, mb10, mb11,
                           mb12, mb13, mb14, mb15>::v(b);
    return _mm_or_si128(ma, mb);
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
         (((m1 & 0x4444000) & m2) == (0x44440000 & m2))) {
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
    if ( ((m1 & m2) == (0x1032 & m2)) ) {
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
    if ( ((m1 & m2) == (0x32107654 & m2)) ) {
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

    if (u32_perm && zero_elements==false) {
        return perm1_v8u32<u32_0_t::idx, u32_1_t::idx,
                           u32_2_t::idx, u32_3_t::idx,
                           u32_4_t::idx, u32_4_t::idx,
                           u32_6_t::idx, u32_7_t::idx>::v(a);
    }
    if (lh_from_lo_lane && hh_from_hi_lane) {
        const __m256i msk=_mm256_setr_epi8(
            _P00<0 ? -1 : _P00, _P01<0 ? -1 : _P01,
            _P02<0 ? -1 : _P02, _P03<0 ? -1 : _P03,
            _P04<0 ? -1 : _P04, _P05<0 ? -1 : _P05,
            _P06<0 ? -1 : _P06, _P07<0 ? -1 : _P07,
            _P08<0 ? -1 : _P08, _P09<0 ? -1 : _P09,
            _P10<0 ? -1 : _P10, _P11<0 ? -1 : _P11,
            _P12<0 ? -1 : _P12, _P13<0 ? -1 : _P13,
            _P14<0 ? -1 : _P14, _P15<0 ? -1 : _P15,
            _P16<0 ? -1 : _P16-16, _P17<0 ? -1 : _P17-16,
            _P18<0 ? -1 : _P18-16, _P19<0 ? -1 : _P19-16,
            _P20<0 ? -1 : _P20-16, _P21<0 ? -1 : _P21-16,
            _P22<0 ? -1 : _P22-16, _P23<0 ? -1 : _P23-16,
            _P24<0 ? -1 : _P24-16, _P25<0 ? -1 : _P25-16,
            _P26<0 ? -1 : _P26-16, _P27<0 ? -1 : _P27-16,
            _P28<0 ? -1 : _P28-16, _P29<0 ? -1 : _P29-16,
            _P30<0 ? -1 : _P30-16, _P31<0 ? -1 : _P31-16);
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
        const __m256i msk=_mm256_setr_epi8(
            _P00<0 ? 0 : 0xff, _P01<0 ? 0 : 0xff,
            _P02<0 ? 0 : 0xff, _P03<0 ? 0 : 0xff,
            _P04<0 ? 0 : 0xff, _P05<0 ? 0 : 0xff,
            _P06<0 ? 0 : 0xff, _P07<0 ? 0 : 0xff,
            _P08<0 ? 0 : 0xff, _P09<0 ? 0 : 0xff,
            _P10<0 ? 0 : 0xff, _P11<0 ? 0 : 0xff,
            _P12<0 ? 0 : 0xff, _P13<0 ? 0 : 0xff,
            _P14<0 ? 0 : 0xff, _P15<0 ? 0 : 0xff,
            _P16<0 ? 0 : 0xff, _P17<0 ? 0 : 0xff,
            _P18<0 ? 0 : 0xff, _P19<0 ? 0 : 0xff,
            _P20<0 ? 0 : 0xff, _P21<0 ? 0 : 0xff,
            _P22<0 ? 0 : 0xff, _P23<0 ? 0 : 0xff,
            _P24<0 ? 0 : 0xff, _P25<0 ? 0 : 0xff,
            _P26<0 ? 0 : 0xff, _P27<0 ? 0 : 0xff,
            _P28<0 ? 0 : 0xff, _P29<0 ? 0 : 0xff,
            _P30<0 ? 0 : 0xff, _P31<0 ? 0 : 0xff);
        return _mm256_and_si256(ap, msk);
    }
    if (lh_from_hi_lane && hh_from_lo_lane) {
        // swap lo and high half
        constexpr const int sh4=shuffle4<2, 3, 0, 1>::val;
        const __m256i as=_mm256_permute4x64_epi64(a, sh4);
        const __m256i msk=_mm256_setr_epi8(
            _P00<0 ? -1 : _P00-16, _P01<0 ? -1 : _P01-16,
            _P02<0 ? -1 : _P02-16, _P03<0 ? -1 : _P03-16,
            _P04<0 ? -1 : _P04-16, _P05<0 ? -1 : _P05-16,
            _P06<0 ? -1 : _P06-16, _P07<0 ? -1 : _P07-16,
            _P08<0 ? -1 : _P08-16, _P09<0 ? -1 : _P09-16,
            _P10<0 ? -1 : _P10-16, _P11<0 ? -1 : _P11-16,
            _P12<0 ? -1 : _P12-16, _P13<0 ? -1 : _P13-16,
            _P14<0 ? -1 : _P14-16, _P15<0 ? -1 : _P15-16,
            _P16<0 ? -1 : _P16, _P17<0 ? -1 : _P17,
            _P18<0 ? -1 : _P18, _P19<0 ? -1 : _P19,
            _P20<0 ? -1 : _P20, _P21<0 ? -1 : _P21,
            _P22<0 ? -1 : _P22, _P23<0 ? -1 : _P23,
            _P24<0 ? -1 : _P24, _P25<0 ? -1 : _P25,
            _P26<0 ? -1 : _P26, _P27<0 ? -1 : _P27,
            _P28<0 ? -1 : _P28, _P29<0 ? -1 : _P29,
            _P30<0 ? -1 : _P30, _P31<0 ? -1 : _P31);
        return vpshufb::v(as, msk);
    }
    if (lh_from_lo_lane && hh_from_lo_lane) {
        // distribute the low 128bits to high 128bits
        constexpr const int sh4=shuffle4<0, 1, 0, 1>::val;
        const __m256i as=_mm256_permute4x64_epi64(a, sh4);
        const __m256i msk=_mm256_setr_epi8(
            _P00<0 ? -1 : _P00, _P01<0 ? -1 : _P01,
            _P02<0 ? -1 : _P02, _P03<0 ? -1 : _P03,
            _P04<0 ? -1 : _P04, _P05<0 ? -1 : _P05,
            _P06<0 ? -1 : _P06, _P07<0 ? -1 : _P07,
            _P08<0 ? -1 : _P08, _P09<0 ? -1 : _P09,
            _P10<0 ? -1 : _P10, _P11<0 ? -1 : _P11,
            _P12<0 ? -1 : _P12, _P13<0 ? -1 : _P13,
            _P14<0 ? -1 : _P14, _P15<0 ? -1 : _P15,
            _P16<0 ? -1 : _P16, _P17<0 ? -1 : _P17,
            _P18<0 ? -1 : _P18, _P19<0 ? -1 : _P19,
            _P20<0 ? -1 : _P20, _P21<0 ? -1 : _P21,
            _P22<0 ? -1 : _P22, _P23<0 ? -1 : _P23,
            _P24<0 ? -1 : _P24, _P25<0 ? -1 : _P25,
            _P26<0 ? -1 : _P26, _P27<0 ? -1 : _P27,
            _P28<0 ? -1 : _P28, _P29<0 ? -1 : _P29,
            _P30<0 ? -1 : _P30, _P31<0 ? -1 : _P31);
        return vpshufb::v(as, msk);
    }
    if (lh_from_hi_lane && hh_from_hi_lane) {
        // distribute the high 128bits to low 128bits
        constexpr const int sh4=shuffle4<2, 3, 2, 3>::val;
        const __m256i as=_mm256_permute4x64_epi64(a, sh4);
        const __m256i msk=_mm256_setr_epi8(
            _P00<0 ? -1 : _P00-16, _P01<0 ? -1 : _P01-16,
            _P02<0 ? -1 : _P02-16, _P03<0 ? -1 : _P03-16,
            _P04<0 ? -1 : _P04-16, _P05<0 ? -1 : _P05-16,
            _P06<0 ? -1 : _P06-16, _P07<0 ? -1 : _P07-16,
            _P08<0 ? -1 : _P08-16, _P09<0 ? -1 : _P09-16,
            _P10<0 ? -1 : _P10-16, _P11<0 ? -1 : _P11-16,
            _P12<0 ? -1 : _P12-16, _P13<0 ? -1 : _P13-16,
            _P14<0 ? -1 : _P14-16, _P15<0 ? -1 : _P15-16,
            _P16<0 ? -1 : _P16-16, _P17<0 ? -1 : _P17-16,
            _P18<0 ? -1 : _P18-16, _P19<0 ? -1 : _P19-16,
            _P20<0 ? -1 : _P20-16, _P21<0 ? -1 : _P21-16,
            _P22<0 ? -1 : _P22-16, _P23<0 ? -1 : _P23-16,
            _P24<0 ? -1 : _P24-16, _P25<0 ? -1 : _P25-16,
            _P26<0 ? -1 : _P26-16, _P27<0 ? -1 : _P27-16,
            _P28<0 ? -1 : _P28-16, _P29<0 ? -1 : _P29-16,
            _P30<0 ? -1 : _P30-16, _P31<0 ? -1 : _P31-16);
        return vpshufb::v(as, msk);
    }
    // swap lo and high half
    constexpr const int sh4=shuffle4<2, 3, 0, 1>::val;
    const __m256i as=_mm256_permute4x64_epi64(a, sh4);
    // shuffle the original values
    const __m256i msk=_mm256_setr_epi8(
        _UP00 > 15 ? -1 : _P00, _UP01 > 15 ? -1 : _P01,
        _UP02 > 15 ? -1 : _P02, _UP03 > 15 ? -1 : _P03,
        _UP04 > 15 ? -1 : _P04, _UP05 > 15 ? -1 : _P05,
        _UP06 > 15 ? -1 : _P06, _UP07 > 15 ? -1 : _P07,
        _UP08 > 15 ? -1 : _P08, _UP09 > 15 ? -1 : _P09,
        _UP10 > 15 ? -1 : _P10, _UP11 > 15 ? -1 : _P11,
        _UP12 > 15 ? -1 : _P12, _UP13 > 15 ? -1 : _P13,
        _UP14 > 15 ? -1 : _P14, _UP15 > 15 ? -1 : _P15,
        _P16 < 16 ? -1 : _P16-16, _P17 < 16 ? -1 : _P17-16,
        _P18 < 16 ? -1 : _P18-16, _P19 < 16 ? -1 : _P19-16,
        _P20 < 16 ? -1 : _P20-16, _P21 < 16 ? -1 : _P21-16,
        _P22 < 16 ? -1 : _P22-16, _P23 < 16 ? -1 : _P23-16,
        _P24 < 16 ? -1 : _P24-16, _P25 < 16 ? -1 : _P25-16,
        _P26 < 16 ? -1 : _P26-16, _P27 < 16 ? -1 : _P27-16,
        _P28 < 16 ? -1 : _P28-16, _P29 < 16 ? -1 : _P29-16,
        _P30 < 16 ? -1 : _P30-16, _P31 < 16 ? -1 : _P31-16);
    const __m256i v0=vpshufb::v(a, msk);
    // shuffle the swapped values
    const __m256i msk_sw=_mm256_setr_epi8(
        _P00 < 16 ? -1 : _P00-16, _P01 < 16 ? -1 : _P01-16,
        _P02 < 16 ? -1 : _P02-16, _P03 < 16 ? -1 : _P03-16,
        _P04 < 16 ? -1 : _P04-16, _P05 < 16 ? -1 : _P05-16,
        _P06 < 16 ? -1 : _P06-16, _P07 < 16 ? -1 : _P07-16,
        _P08 < 16 ? -1 : _P08-16, _P09 < 16 ? -1 : _P09-16,
        _P10 < 16 ? -1 : _P10-16, _P11 < 16 ? -1 : _P11-16,
        _P12 < 16 ? -1 : _P12-16, _P13 < 16 ? -1 : _P13-16,
        _P14 < 16 ? -1 : _P14-16, _P15 < 16 ? -1 : _P15-16,
        _UP16 > 15 ? -1 : _P16, _UP17 > 15 ? -1 : _P17,
        _UP18 > 15 ? -1 : _P18, _UP19 > 15 ? -1 : _P19,
        _UP20 > 15 ? -1 : _P20, _UP21 > 15 ? -1 : _P21,
        _UP22 > 15 ? -1 : _P22, _UP23 > 15 ? -1 : _P23,
        _UP24 > 15 ? -1 : _P24, _UP25 > 15 ? -1 : _P25,
        _UP26 > 15 ? -1 : _P26, _UP27 > 15 ? -1 : _P27,
        _UP28 > 15 ? -1 : _P28, _UP29 > 15 ? -1 : _P29,
        _UP30 > 15 ? -1 : _P30, _UP31 > 15 ? -1 : _P31);
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

    using perm1_t=perm1_v32u8<
        _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
        _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15,
        _P16, _P17, _P18, _P19, _P20, _P21, _P22, _P23,
        _P24, _P25, _P26, _P27, _P28, _P29, _P30, _P31>;
    if (a_only) {
        return perm1_t::v(a);
    }
    if (b_only) {
        return perm1_t::v(a);
    }

    constexpr const int32_t
        a00 = _UP00 > 31 ? -1 : _UP00, a01 = _UP01 > 31 ? -1 : _UP01,
        a02 = _UP02 > 31 ? -1 : _UP02, a03 = _UP03 > 31 ? -1 : _UP03,
        a04 = _UP04 > 31 ? -1 : _UP04, a05 = _UP05 > 31 ? -1 : _UP05,
        a06 = _UP06 > 31 ? -1 : _UP06, a07 = _UP07 > 31 ? -1 : _UP07,
        a08 = _UP08 > 31 ? -1 : _UP08, a09 = _UP09 > 31 ? -1 : _UP09,
        a10 = _UP10 > 31 ? -1 : _UP10, a11 = _UP11 > 31 ? -1 : _UP11,
        a12 = _UP12 > 31 ? -1 : _UP12, a13 = _UP13 > 31 ? -1 : _UP13,
        a14 = _UP14 > 31 ? -1 : _UP14, a15 = _UP15 > 31 ? -1 : _UP15,
        a16 = _UP16 > 31 ? -1 : _UP16, a17 = _UP17 > 31 ? -1 : _UP17,
        a18 = _UP18 > 31 ? -1 : _UP18, a19 = _UP19 > 31 ? -1 : _UP19,
        a20 = _UP20 > 31 ? -1 : _UP20, a21 = _UP21 > 31 ? -1 : _UP21,
        a22 = _UP22 > 31 ? -1 : _UP22, a23 = _UP23 > 31 ? -1 : _UP23,
        a24 = _UP24 > 31 ? -1 : _UP24, a25 = _UP25 > 31 ? -1 : _UP25,
        a26 = _UP26 > 31 ? -1 : _UP26, a27 = _UP27 > 31 ? -1 : _UP27,
        a28 = _UP28 > 31 ? -1 : _UP28, a29 = _UP29 > 31 ? -1 : _UP29,
        a30 = _UP30 > 31 ? -1 : _UP30, a31 = _UP31 > 31 ? -1 : _UP31;

    constexpr const int32_t
        b00 = _P00 < 32 ? -1 : _P00, b01 = _P01 < 32 ? -1 : _P01,
        b02 = _P02 < 32 ? -1 : _P02, b03 = _P03 < 32 ? -1 : _P03,
        b04 = _P04 < 32 ? -1 : _P04, b05 = _P05 < 32 ? -1 : _P05,
        b06 = _P06 < 32 ? -1 : _P06, b07 = _P07 < 32 ? -1 : _P07,
        b08 = _P08 < 32 ? -1 : _P08, b09 = _P09 < 32 ? -1 : _P09,
        b10 = _P10 < 32 ? -1 : _P10, b11 = _P11 < 32 ? -1 : _P11,
        b12 = _P12 < 32 ? -1 : _P12, b13 = _P13 < 32 ? -1 : _P13,
        b14 = _P14 < 32 ? -1 : _P14, b15 = _P15 < 32 ? -1 : _P15,
        b16 = _P16 < 32 ? -1 : _P16, b17 = _P17 < 32 ? -1 : _P17,
        b18 = _P18 < 32 ? -1 : _P18, b19 = _P19 < 32 ? -1 : _P19,
        b20 = _P20 < 32 ? -1 : _P20, b21 = _P21 < 32 ? -1 : _P21,
        b22 = _P22 < 32 ? -1 : _P22, b23 = _P23 < 32 ? -1 : _P23,
        b24 = _P24 < 32 ? -1 : _P24, b25 = _P25 < 32 ? -1 : _P25,
        b26 = _P26 < 32 ? -1 : _P26, b27 = _P27 < 32 ? -1 : _P27,
        b28 = _P28 < 32 ? -1 : _P28, b29 = _P29 < 32 ? -1 : _P29,
        b30 = _P30 < 32 ? -1 : _P30, b31 = _P31 < 32 ? -1 : _P31;

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
#if defined (__AVX512F__)
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
    const int m1= pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 7>::m;
    const int m2= zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;
    const bool do_zero= m2 != 0xFFFFFFFF;

    if (m2 == 0xFFFFFFFF)
        return _mm512_setzero_pd();

    const __mmask8 zm=
        ((_P0 >= 0 ? (1<<0) : 0)) |
        ((_P1 >= 0 ? (1<<1) : 0)) |
        ((_P2 >= 0 ? (1<<2) : 0)) |
        ((_P3 >= 0 ? (1<<3) : 0)) |
        ((_P4 >= 0 ? (1<<4) : 0)) |
        ((_P5 >= 0 ? (1<<5) : 0)) |
        ((_P6 >= 0 ? (1<<6) : 0)) |
        ((_P7 >= 0 ? (1<<7) : 0));

    if (((m1 ^ 0x76543210) & m2) == 0) {
        // no shuffling:
        return _mm512_maskz_mov_pd(zm, a);
    }
    // full permute:
    const __m512i pperm=
        _mm512_setr_epi32(_P0 & 7, 0,
                          _P1 & 7, 0,
                          _P2 & 7, 0,
                          _P3 & 7, 0,
                          _P4 & 7, 0,
                          _P5 & 7, 0,
                          _P6 & 7, 0,
                          _P7 & 7, 0);
    if (zm != 0) {
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
    const unsigned m1 = pos_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7, 15>::m;
    // Mask to zero out negative indexes
    const unsigned m2 = zero_msk_8<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::m;

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
        ((_P0 >= 0 ? (1<<0) : 0)) |
        ((_P1 >= 0 ? (1<<1) : 0)) |
        ((_P2 >= 0 ? (1<<2) : 0)) |
        ((_P3 >= 0 ? (1<<3) : 0)) |
        ((_P4 >= 0 ? (1<<4) : 0)) |
        ((_P5 >= 0 ? (1<<5) : 0)) |
        ((_P6 >= 0 ? (1<<6) : 0)) |
        ((_P7 >= 0 ? (1<<7) : 0));
    // full permute:
    const __m512i pperm=
        _mm512_setr_epi32(_P0 & 15, 0,
                          _P1 & 15, 0,
                          _P2 & 15, 0,
                          _P3 & 15, 0,
                          _P4 & 15, 0,
                          _P5 & 15, 0,
                          _P6 & 15, 0,
                          _P7 & 15, 0);
    if (zm != 0) {
        return _mm512_maskz_permutex2var_pd(a, zm, pperm, b);
    }
    return _mm512_permutex2var_pd(a, pperm, b);
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
#if defined (__AVX512F__)
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
