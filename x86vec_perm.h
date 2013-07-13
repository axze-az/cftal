#if !defined (__X86VEC_PERM_H__)
#define __X86VEC_PERM_H__ 1

#include <cftal/x86vec_ops_0.h>

namespace x86vec {

        namespace impl {

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
                struct perm1_v2f64<-1,-1> : public make_zero_f64 {};
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
                struct perm2_v2f64<-1,-1> : public make_zero_f64 {};
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
                struct perm1_v4f32<-1,-1,-1,-1> : public make_zero_f32 {};
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
                        : public fixed_arg_2<__m128, make_zero_f32,
                                             vunpcklps> {};
                template <>
                struct perm1_v4f32< 2,-1, 3,-1>
                        : public fixed_arg_2<__m128, make_zero_f32,
                                             vunpckhps> {};
                template <>
                struct perm1_v4f32<-1, 0, -1, 1>
                        : public fixed_arg_1<__m128, make_zero_f32,
                                             vunpcklps> {};
                template <>
                struct perm1_v4f32<-1, 2, -1, 3>
                        : public fixed_arg_1<__m128, make_zero_f32,
                                             vunpckhps> {};
                template <>
                struct perm1_v4f32< 0, 1,-1,-1>
                        : public fixed_arg_2<__m128, make_zero_f32,
                                             exec_f64<vunpcklpd> > {};
                template <>
                struct perm1_v4f32<-1,-1, 2, 3>
                        : public fixed_arg_1<__m128, make_zero_f32,
                                             exec_f64<vunpckhpd> > {};
                template <>
                struct perm1_v4f32<0, 0, 0, 0> : public splat_f32<0> {};
                template <>
                struct perm1_v4f32<1, 1, 1, 1> : public splat_f32<1> {};
                template <>
                struct perm1_v4f32<2, 2, 2, 2> : public splat_f32<2> {};
                template <>
                struct perm1_v4f32<3, 3, 3, 3> : public splat_f32<3> {};

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
                struct perm2_v4f32<-1,-1,-1,-1> : public make_zero_f32 {};
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
                struct perm1_v4u32< 0, 0, 0, 0> : public splat_u32<0> {};
                template <>
                struct perm1_v4u32< 1, 1, 1, 1> : public splat_u32<1> {};
                template <>
                struct perm1_v4u32< 2, 2, 2, 2> : public splat_u32<2> {};
                template <>
                struct perm1_v4u32< 3, 3, 3, 3> : public splat_u32<3> {};

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


                // specialisations for two uint32_t vectors.
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

#if 0
                // permutation of the high half of one uint16_t vector
                template <int _P4, int _P5, int _P6, int _P7>
                struct perm1_v8u16<0, 1, 2, 3, _P4, _P5, _P6, _P7> {
                        static __m128i v(__m128i a);
                };
                // permutation of the low half of one uint16_t vector
                template <int _P0, int _P1, int _P2, int _P3>
                struct perm1_v8u16<_P0, _P1, _P2, _P3, 4, 5, 6, 7> {
                        static __m128i v(__m128i a);
                };
#endif
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
                        : public splat_u16<0> {};
                template <>
                struct perm1_v8u16<1, 1, 1, 1, 1, 1, 1, 1>
                        : public splat_u16<1> {};
                template <>
                struct perm1_v8u16<2, 2, 2, 2, 2, 2, 2, 2>
                        : public splat_u16<2> {};
                template <>
                struct perm1_v8u16<3, 3, 3, 3, 3, 3, 3, 3>
                        : public splat_u16<3> {};
                template <>
                struct perm1_v8u16<4, 4, 4, 4, 4, 4, 4, 4>
                        : public splat_u16<4> {};
                template <>
                struct perm1_v8u16<5, 5, 5, 5, 5, 5, 5, 5>
                        : public splat_u16<5> {};
                template <>
                struct perm1_v8u16<6, 6, 6, 6, 6, 6, 6, 6>
                        : public splat_u16<6> {};
                template <>
                struct perm1_v8u16<7, 7, 7, 7, 7, 7, 7, 7>
                        : public splat_u16<7> {};
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
 
#endif
        }

        template <int _P0, int _P1>
        __m128d perm_f64(__m128d a);
        template <int _P0, int _P1>
        __m128d perm_f64(__m128d a, __m128d b);

        template <int _P0, int _P1, int _P2, int _P3>
        __m128 perm_f32(__m128 a);
        template <int _P0, int _P1, int _P2, int _P3>
        __m128 perm_f32(__m128 a, __m128 b);

        template <int _P0, int _P1, int _P2, int _P3>
        __m128i perm_u32(__m128i a);
        template <int _P0, int _P1, int _P2, int _P3>
        __m128i perm_u32(__m128i a, __m128i b);

        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m128i perm_u16(__m128i a);
        template <int _P0, int _P1, int _P2, int _P3,
                  int _P4, int _P5, int _P6, int _P7>
        __m128i perm_u16(__m128i a, __m128i b);

        template <int _P0, int _P1>
        __m128i perm_u64(__m128i a);
        template <int _P0, int _P1>
        __m128i perm_u64(__m128i a, __m128i b);
}

template <int _P0, int _P1>
inline
__m128d x86vec::impl::perm1_v2f64<_P0, _P1>::v(__m128d a)
{
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
                        return make_zero_f64::v();
                }
                // zero some elements
                const __m128d msk= const4_u32<
                        (_P0<0 ? 0 : -1),
                        (_P0<0 ? 0 : -1),
                        (_P1<0 ? 0 : -1),
                        (_P1<0 ? 0 : -1)>::dv();
                return _mm_and_pd(a, msk);
	}

        if (do_shuffle && !do_zero) {
                // shuffling, not zeroing
                return vshufpd<_P0, _P1>::v(a);
        }
	if (do_shuffle && do_zero) {
		// shuffling and zeroing
		const __m128d zero= _mm_setzero_pd();
		// both shuffle and zero
		if (_P0 < 0 && _P1 >= 0) {
			// zero low half, shuffle high half
			return vshufpd<0, _P1>::v(zero, a);
		}
		if (_P0 >= 0 && _P1 < 0) {
			// shuffle low half, zero high half
			return vshufpd<_P1, 0>::v(a, zero);
		}
	}
	// trivial case: do n
	return a;
}

template <int _P0, int _P1>
inline
__m128d x86vec::impl::perm2_v2f64<_P0, _P1>::v(__m128d a, __m128d b)
{
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
                return vshufpd<_P0, _P1>::v(a, b);
        }
        // first element from b, second element from a
        return vshufpd<_P0, _P1>::v(b, a);
}

template <int _P0, int _P1, int _P2, int _P3>
__m128 x86vec::impl::perm1_v4f32<_P0, _P1, _P2, _P3>::v(__m128 a)
{
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
                        return make_zero_f32::v();
                }
                // zero some elements
                const int z0 = (_P0 < 0) ? 0 : -1;
                const int z1 = (_P1 < 0) ? 0 : -1;
                const int z2 = (_P2 < 0) ? 0 : -1;
                const int z3 = (_P3 < 0) ? 0 : -1;
                const __m128 zm= const4_u32<z0, z1, z2, z3>::fv();
                // zero with AND mask
                return  _mm_and_ps(a,zm);
        }

        if (do_shuffle && !do_zero) {
                // shuffling, not zeroing
                return vshufps<_P0, _P1, _P2, _P3>::v(a, a);
        }
        // both shuffle and zero
        if (m2 == 0xFF00) {
                // zero low half, shuffle high half
                return vshufps<0, 0, _P2, _P3>::v(_mm_setzero_ps(), a);
        }
        if (m2 == 0x00FF) {
                // shuffle low half, zero high half
                return vshufps<_P0, _P1, 0, 0>::v(a, _mm_setzero_ps());
        }
#ifdef __SSSE3__
        const int c00 = (_P0<0 ? -1 : 4*(_P0&3)+0);
        const int c01 = (_P0<0 ? -1 : 4*(_P0&3)+1);
        const int c02 = (_P0<0 ? -1 : 4*(_P0&3)+2);
        const int c03 = (_P0<0 ? -1 : 4*(_P0&3)+3);
        const int c04 = (_P1<0 ? -1 : 4*(_P1&3)+0);
        const int c05 = (_P1<0 ? -1 : 4*(_P1&3)+1);
        const int c06 = (_P1<0 ? -1 : 4*(_P1&3)+2);
        const int c07 = (_P1<0 ? -1 : 4*(_P1&3)+3);
        const int c08 = (_P2<0 ? -1 : 4*(_P2&3)+0);
        const int c09 = (_P2<0 ? -1 : 4*(_P2&3)+1);
        const int c10 = (_P2<0 ? -1 : 4*(_P2&3)+2);
        const int c11 = (_P2<0 ? -1 : 4*(_P2&3)+3);
        const int c12 = (_P3<0 ? -1 : 4*(_P3&3)+0);
        const int c13 = (_P3<0 ? -1 : 4*(_P3&3)+1);
        const int c14 = (_P3<0 ? -1 : 4*(_P3&3)+2);
        const int c15 = (_P3<0 ? -1 : 4*(_P3&3)+3);
        const __m128i msk=const16_u8<c00, c01, c02, c03,
		c04, c05, c06, c07,
		c08, c09, c10, c11,
		c12, c13, c14, c15>::iv();
        return as<__m128>(_mm_shuffle_epi8(as<__m128i>(a),msk));
#else
        // shuffle
        __m128 t= vshufps<_P0, _P1, _P2, _P3>::v(a, a);
        // zero with AND mask
        const int z0 = (_P0 < 0) ? 0 : -1;
        const int z1 = (_P1 < 0) ? 0 : -1;
        const int z2 = (_P2 < 0) ? 0 : -1;
        const int z3 = (_P3 < 0) ? 0 : -1;
        const __m128 zm= const4_u32<z0, z1, z2, z3>::fv();
        return  _mm_and_ps(t,zm);
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m128 x86vec::impl::perm2_v4f32<_P0, _P1, _P2, _P3>::v(__m128 a, __m128 b)
{
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

        if (((m1 & ~0x4444) ^ 0x3210) == 0 && m2 == 0xFFFF) {
                // selecting without shuffling or zeroing
                const bool sm0 = _P0 < 4;
                const bool sm1 = _P1 < 4;
                const bool sm2 = _P2 < 4;
                const bool sm3 = _P3 < 4;
                return select_v4f32<sm0, sm1, sm2, sm3>::v(a, b);
        }
        // Use AMD XOP instruction PPERM here later
        if ((((m1 & ~0x4444) ^ 0x3210) & m2) == 0) {
                // selecting and zeroing, not shuffling
                const bool sm0 = _P0 < 4;
                const bool sm1 = _P1 < 4;
                const bool sm2 = _P2 < 4;
                const bool sm3 = _P3 < 4;
                __m128 t = select_v4f32<sm0, sm1, sm2, sm3>::v(a, b);
                // zero
                const __m128 zm = const4_u32<
                        (_P0 < 0 ? 0 : -1),
                        (_P1 < 0 ? 0 : -1),
                        (_P2 < 0 ? 0 : -1),
                        (_P3 < 0 ? 0 : -1)>::fv();
                return  _mm_and_ps(t, zm);
	}
        if (((m1 & 0x4400)==0x4400) && ((m1 & 0x0044)==0x00)) {
                // lower half from a, higher half from b
                __m128 t = vshufps<_P0, _P1, _P2, _P3>::v(a, b);
                if ( m2 != 0xFFFF) {
                        // zero
                        const __m128 zm = const4_u32<
                                (_P0 < 0 ? 0 : -1),
                                (_P1 < 0 ? 0 : -1),
                                (_P2 < 0 ? 0 : -1),
                                (_P3 < 0 ? 0 : -1)>::fv();
                        return  _mm_and_ps(t, zm);
		}
                return t;
	}
        if (((m1 & 0x4400)==0x0000) && ((m1 & 0x0044)==0x44)) {
                // lower half from b, higher half from a
                __m128 t=vshufps<_P0, _P1, _P2, _P3>::v(b, a);
                if ( m2 != 0xFFFF) {
                        // zero
                        const __m128 zm = const4_u32<
                                (_P0 < 0 ? 0 : -1),
                                (_P1 < 0 ? 0 : -1),
                                (_P2 < 0 ? 0 : -1),
                                (_P3 < 0 ? 0 : -1)>::fv();
                        return  _mm_and_ps(t, zm);
		}
                return t;
	}
        // general case
        // select all elements to clear or from 1st vector
        const int ma0 = _P0 < 4 ? _P0 : -1;
	const int ma1 = _P1 < 4 ? _P1 : -1;
	const int ma2 = _P2 < 4 ? _P2 : -1;
	const int ma3 = _P3 < 4 ? _P3 : -1;
	__m128 a1 = perm1_v4f32<ma0, ma1, ma2, ma3>::v(a);
	// select all elements from second vector
	const int mb0 = _P0 > 3 ? (_P0-4) : -1;
	const int mb1 = _P1 > 3 ? (_P1-4) : -1;
	const int mb2 = _P2 > 3 ? (_P2-4) : -1;
	const int mb3 = _P3 > 3 ? (_P3-4) : -1;
	__m128 b1 = perm1_v4f32<mb0, mb1, mb2, mb3>::v(b);
	return  _mm_or_ps(a1,b1);
}

template <int _P0, int _P1, int _P2, int _P3>
__m128i x86vec::impl::perm1_v4u32<_P0, _P1, _P2, _P3>::v(__m128i a)
{
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
                const int z0 = (_P0 < 0) ? 0 : -1;
                const int z1 = (_P1 < 0) ? 0 : -1;
                const int z2 = (_P2 < 0) ? 0 : -1;
                const int z3 = (_P3 < 0) ? 0 : -1;
                const __m128i zm= const4_u32<z0, z1, z2, z3>::iv();
                // zero with AND mask
                return  _mm_and_si128(a,zm);
        }
        if (do_shuffle && !do_zero) {
                // No zero, high elements kept in order, low elements
                // only from low half.
                if (((m1 & 0xFF00) == 0x3200) && ((m1 & 0x22)==0)) {
                        const int l0= 2*_P0+0;
                        const int l1= 2*_P0+1;
                        const int l2= 2*_P1+0;
                        const int l3= 2*_P1+1;
                        return vpshuflw<l0, l1, l2, l3>::v(a);
                }
                // No zero, low elements kept in order, high elements
                // only from high half
                if (((m1 & 0xFF) == 0x10) && ((m1 & 0x2200)==0x2200)) {
                        const int h0= 2*(_P2-2) + 0;
                        const int h1= 2*(_P2-2) + 1;
                        const int h2= 2*(_P3-2) + 0;
                        const int h3= 2*(_P3-2) + 1;
                        return vpshufhw<h0, h1, h2, h3>::v(a);
                }
                return vpshufd<_P0, _P1, _P2, _P3>::v(a);
        }
#if defined (__SSSE3__)
        //if (do_shuffle && do_zero) {
        const int c00 = (_P0<0 ? -1 : 4*(_P0&3)+0);
        const int c01 = (_P0<0 ? -1 : 4*(_P0&3)+1);
        const int c02 = (_P0<0 ? -1 : 4*(_P0&3)+2);
        const int c03 = (_P0<0 ? -1 : 4*(_P0&3)+3);
        const int c04 = (_P1<0 ? -1 : 4*(_P1&3)+0);
        const int c05 = (_P1<0 ? -1 : 4*(_P1&3)+1);
        const int c06 = (_P1<0 ? -1 : 4*(_P1&3)+2);
        const int c07 = (_P1<0 ? -1 : 4*(_P1&3)+3);
        const int c08 = (_P2<0 ? -1 : 4*(_P2&3)+0);
        const int c09 = (_P2<0 ? -1 : 4*(_P2&3)+1);
        const int c10 = (_P2<0 ? -1 : 4*(_P2&3)+2);
        const int c11 = (_P2<0 ? -1 : 4*(_P2&3)+3);
        const int c12 = (_P3<0 ? -1 : 4*(_P3&3)+0);
        const int c13 = (_P3<0 ? -1 : 4*(_P3&3)+1);
        const int c14 = (_P3<0 ? -1 : 4*(_P3&3)+2);
        const int c15 = (_P3<0 ? -1 : 4*(_P3&3)+3);
        const __m128i msk=const16_u8<c00, c01, c02, c03,
		c04, c05, c06, c07,
		c08, c09, c10, c11,
		c12, c13, c14, c15>::iv();
        return _mm_shuffle_epi8(a, msk);
        // }
#else
        // both shuffle and zero
        if (m2 == 0xFF00) {
                // zero low half, shuffle high half
                return exec_f32<vshufps<0, 0, _P2, _P3> >::
                        v(make_zero_int::v(), a);
        }
        if (m2 == 0x00FF) {
                // shuffle low half, zero high half
                return exec_f32<vshufps<_P0, _P1, 0, 0> >::
                        v(a, make_zero_int::v());
        }
        // both
        __m128i t= vpshufd<_P0, _P1, _P2, _P3>::v(a);
        const int z0 = (_P0 < 0) ? 0 : -1;
        const int z1 = (_P1 < 0) ? 0 : -1;
        const int z2 = (_P2 < 0) ? 0 : -1;
        const int z3 = (_P3 < 0) ? 0 : -1;
        const __m128i zm= const4_u32<z0, z1, z2, z3>::iv();
        // zero with AND mask
        return  _mm_and_si128(t,zm);
#endif
}

template <int _P0, int _P1, int _P2, int _P3>
__m128i x86vec::impl::perm2_v4u32<_P0, _P1, _P2, _P3>::v(__m128i a, __m128i b)
{
        // Combine all the indexes into a single bitfield, with 4 bits
        // for each
        const int m1 = pos_msk_4<_P0, _P1, _P2, _P3, 7>::m;
        // Mask to zero out negative indexes
        const int m2 = zero_msk_4<_P0, _P1, _P2, _P3>::m;

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
                const bool sm0 = _P0 < 4;
                const bool sm1 = _P1 < 4;
                const bool sm2 = _P2 < 4;
                const bool sm3 = _P3 < 4;
                return select_v4u32<sm0, sm1, sm2, sm3>::v(a, b);
        }
        // Use AMD XOP instruction PPERM here later
        if ((((m1 & ~0x4444) ^ 0x3210) & m2) == 0) {
                // selecting and zeroing, not shuffling
                const bool sm0 = _P0 < 4;
                const bool sm1 = _P1 < 4;
                const bool sm2 = _P2 < 4;
                const bool sm3 = _P3 < 4;
                __m128i t = select_v4u32<sm0, sm1, sm2, sm3>::v(a, b);
                // zero
                const __m128i zm = const4_u32<
                        (_P0 < 0 ? 0 : -1),
                        (_P1 < 0 ? 0 : -1),
                        (_P2 < 0 ? 0 : -1),
                        (_P3 < 0 ? 0 : -1)>::iv();
                return  _mm_and_si128(t, zm);
	}
        if (((m1 & 0x4400)==0x4400) && ((m1 & 0x0044)==0x00)) {
                // lower half from a, higher half from b
                __m128i t= exec_f32<vshufps<_P0, _P1, _P2, _P3> >::v(a, b);
                if ( m2 != 0xFFFF) {
                        // zero
                        const __m128i zm = const4_u32<
                                (_P0 < 0 ? 0 : -1),
                                (_P1 < 0 ? 0 : -1),
                                (_P2 < 0 ? 0 : -1),
                                (_P3 < 0 ? 0 : -1)>::iv();
                        return  _mm_and_si128(t, zm);
		}
                return t;
	}
        if (((m1 & 0x4400)==0x0000) && ((m1 & 0x0044)==0x44)) {
                // lower half from b, higher half from a
                __m128i t= exec_f32<vshufps<_P0, _P1, _P2, _P3> >::v(b, a);
                if ( m2 != 0xFFFF) {
                        // zero
                        const __m128i zm = const4_u32<
                                (_P0 < 0 ? 0 : -1),
                                (_P1 < 0 ? 0 : -1),
                                (_P2 < 0 ? 0 : -1),
                                (_P3 < 0 ? 0 : -1)>::iv();
                        return  _mm_and_si128(t, zm);
		}
                return t;
	}
        // general case
        // select all elements to clear or from 1st vector
        const int ma0 = _P0 < 4 ? _P0 : -1;
	const int ma1 = _P1 < 4 ? _P1 : -1;
	const int ma2 = _P2 < 4 ? _P2 : -1;
	const int ma3 = _P3 < 4 ? _P3 : -1;
	__m128i a1 = perm1_v4u32<ma0, ma1, ma2, ma3>::v(a);
	// select all elements from second vector
	const int mb0 = _P0 > 3 ? (_P0-4) : -1;
	const int mb1 = _P1 > 3 ? (_P1-4) : -1;
	const int mb2 = _P2 > 3 ? (_P2-4) : -1;
	const int mb3 = _P3 > 3 ? (_P3-4) : -1;
	__m128i b1 = perm1_v4u32<mb0, mb1, mb2, mb3>::v(b);
	return _mm_or_si128(a1,b1);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i x86vec::impl::perm1_v8u16<_P0, _P1, _P2, _P3,
                                _P4, _P5, _P6, _P7>::v(__m128i a)
{
#if 0
        const bool pair0 = (_P0 < 0 && _P1 < 0) ||
                ((_P0 & 1)==0 && _P0>= 0 && _P0 == _P1-1);
        const bool pair1 = (_P2 < 0 && _P3 < 0) ||
                ((_P2 & 1)==0 && _P2>= 0 && _P2 == _P3-1);
        const bool pair2 = (_P4 < 0 && _P5 < 0) ||
                ((_P4 & 1)==0 && _P4>= 0 && _P4 == _P5-1);
        const bool pair3 = (_P6 < 0 && _P7 < 0) ||
                ((_P6 & 1)==0 && _P6>= 0 && _P6 == _P7-1);
        const bool pairs= pair0 && pair1 && pair2 && pair3;
#else
        const int me= pos_msk_4<_P0, _P2, _P4, _P6, 7>::m;
        const int mo= pos_msk_4<_P1, _P3, _P5, _P7, 7>::m;
        const int mez= zero_msk_4<_P0, _P2, _P4, _P6>::m;
        const int moz= zero_msk_4<_P1, _P3, _P5, _P7>::m;
        const bool pairs=
                ((me & 0x1111) & mez) ==0 &&
                ((mo - me) & mez) == (0x1111 & mez) &&
                (moz == mez);
#endif
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
                const int z0= (_P0<0 ? 0 : -1);
                const int z1= (_P1<0 ? 0 : -1);
                const int z2= (_P2<0 ? 0 : -1);
                const int z3= (_P3<0 ? 0 : -1);
                const int z4= (_P4<0 ? 0 : -1);
                const int z5= (_P5<0 ? 0 : -1);
                const int z6= (_P6<0 ? 0 : -1);
                const int z7= (_P7<0 ? 0 : -1);
                const __m128i zm= const8_u16<z0, z1, z2, z3,
			z4, z5, z6, z7>::iv();
                return _mm_and_si128(a, zm);
        }
        // No zero, high elements kept in order, low elements
        // only from low half.
        if ((m2 == -1) &&
            ((m1 & 0xFFFF0000) == 0x76540000) &&
            ((m1 & 0x00004444)==0) ) {
                const int l0= _P0;
                const int l1= _P1;
                const int l2= _P2;
                const int l3= _P3;
                return vpshuflw<l0, l1, l2, l3>::v(a);
        }
        // No zero, low elements kept in order, high elements
        // only from high half
        if ((m2 == -1) &&
            ((m1 & 0xFFFF) == 0x3210) &&
            ((m1 & 0x44440000)==0x44440000)) {
                const int h0= _P4&3;
                const int h1= _P5&3;
                const int h2= _P6&3;
                const int h3= _P7&3;
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
        const int c00 = (_P0<0 ? -1 : 2*(_P0&7)+0);
        const int c01 = (_P0<0 ? -1 : 2*(_P0&7)+1);
        const int c02 = (_P1<0 ? -1 : 2*(_P1&7)+0);
        const int c03 = (_P1<0 ? -1 : 2*(_P1&7)+1);
        const int c04 = (_P2<0 ? -1 : 2*(_P2&7)+0);
        const int c05 = (_P2<0 ? -1 : 2*(_P2&7)+1);
        const int c06 = (_P3<0 ? -1 : 2*(_P3&7)+0);
        const int c07 = (_P3<0 ? -1 : 2*(_P3&7)+1);
        const int c08 = (_P4<0 ? -1 : 2*(_P4&7)+0);
        const int c09 = (_P4<0 ? -1 : 2*(_P4&7)+1);
        const int c10 = (_P5<0 ? -1 : 2*(_P5&7)+0);
        const int c11 = (_P5<0 ? -1 : 2*(_P5&7)+1);
        const int c12 = (_P6<0 ? -1 : 2*(_P6&7)+0);
        const int c13 = (_P6<0 ? -1 : 2*(_P6&7)+1);
        const int c14 = (_P7<0 ? -1 : 2*(_P7&7)+0);
        const int c15 = (_P7<0 ? -1 : 2*(_P7&7)+1);
        const __m128i msk=const16_u8<c00, c01, c02, c03,
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
                        r = vpshuflw<_P0, _P1, _P2, _P3>::v(r);
                }
                if (h_shuffle) {
                        r = vpshufhw<_P4&3, _P5&3, _P6&3, _P7&3>::v(r);
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
                        r = select_v8v8u16<
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
                const int z0= (_P0<0 ? 0 : -1);
                const int z1= (_P1<0 ? 0 : -1);
                const int z2= (_P2<0 ? 0 : -1);
                const int z3= (_P3<0 ? 0 : -1);
                const int z4= (_P4<0 ? 0 : -1);
                const int z5= (_P5<0 ? 0 : -1);
                const int z6= (_P6<0 ? 0 : -1);
                const int z7= (_P7<0 ? 0 : -1);
                const __m128i zm= const8_v8u16<z0, z1, z2, z3,
			z4, z5, z6, z7>::iv();
                r = _mm_and_si128(r, zm);
        }
	return r;
#endif
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i x86vec::impl::perm2_v8u16<_P0, _P1, _P2, _P3,
                                _P4, _P5, _P6, _P7>::v(__m128i a, __m128i b)
{
#if 0
        const bool pair0 = (_P0 < 0 && _P1 < 0) ||
                ((_P0 & 1)==0 && _P0>= 0 && _P0 == _P1-1);
        const bool pair1 = (_P2 < 0 && _P3 < 0) ||
                ((_P2 & 1)==0 && _P2>= 0 && _P2 == _P3-1);
        const bool pair2 = (_P4 < 0 && _P5 < 0) ||
                ((_P4 & 1)==0 && _P4>= 0 && _P4 == _P5-1);
        const bool pair3 = (_P6 < 0 && _P7 < 0) ||
                ((_P6 & 1)==0 && _P6>= 0 && _P6 == _P7-1);
        const bool pairs= pair0 && pair1 && pair2 && pair3;
#else
        const int me= pos_msk_4<_P0, _P2, _P4, _P6, 7>::m;
        const int mo= pos_msk_4<_P1, _P3, _P5, _P7, 7>::m;
        const int mez= zero_msk_4<_P0, _P2, _P4, _P6>::m;
        const int moz= zero_msk_4<_P1, _P3, _P5, _P7>::m;
        const bool pairs=
                ((me & 0x1111) & mez) ==0 &&
                ((mo - me) & mez) == (0x1111 & mez) &&
                (moz == mez);
#endif
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
}

#if defined (__AVX__)

template <int _P0, int _P1, int _P2, int _P3>
__m256d x86vec::impl::perm1_v4f64<_P0, _P1, _P2, _P3>::v(__m256d a)
{
	return a;
#if 0
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
                        return make_zero_f32::v();
                }
                // zero some elements
                const int z0 = (_P0 < 0) ? 0 : -1;
                const int z1 = (_P1 < 0) ? 0 : -1;
                const int z2 = (_P2 < 0) ? 0 : -1;
                const int z3 = (_P3 < 0) ? 0 : -1;
                const __m128 zm= const4_u32<z0, z1, z2, z3>::fv();
                // zero with AND mask
                return  _mm_and_ps(a,zm);
        }

        if (do_shuffle && !do_zero) {
                // shuffling, not zeroing
                return vshufps<_P0, _P1, _P2, _P3>::v(a, a);
        }
        // both shuffle and zero
        if (m2 == 0xFF00) {
                // zero low half, shuffle high half
                return vshufps<0, 0, _P2, _P3>::v(_mm_setzero_ps(), a);
        }
        if (m2 == 0x00FF) {
                // shuffle low half, zero high half
                return vshufps<_P0, _P1, 0, 0>::v(a, _mm_setzero_ps());
        }
#endif
}

#endif

template <int _P0, int _P1>
inline
__m128d x86vec::perm_f64(__m128d a)
{
        static_assert(_P0>-2 && _P0 < 2,
                      "x86vec::perm_v2f64(a) : -1 <= P0 < 2");
        static_assert(_P1>-2 && _P1 < 2,
                      "x86vec::perm_v2f64(a) : -1 <= P1 < 2");
        return impl::perm1_v2f64<_P0, _P1>::v(a);
}

template <int _P0, int _P1>
inline
__m128d x86vec::perm_f64(__m128d a, __m128d b)
{
        static_assert(_P0>-2 && _P0 < 4,
                      "x86vec::perm_f64(a, b) : -1 <= P0 < 4");
        static_assert(_P1>-2 && _P1 < 4,
                      "x86vec::perm_f64(a, b) : -1 <= P1 < 4");
        return impl::perm2_v2f64<_P0, _P1>::v(a, b);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128 x86vec::perm_f32(__m128 a)
{
        static_assert(_P0>-2 && _P0 < 4,
                      "x86vec::perm_v4f32(a) : -1 <= P0 < 4");
        static_assert(_P1>-2 && _P1 < 4,
                      "x86vec::perm_v4f32(a) : -1 <= P1 < 4");
        static_assert(_P2>-2 && _P2 < 4,
                      "x86vec::perm_v4f32(a) : -1 <= P2 < 4");
        static_assert(_P3>-2 && _P3 < 4,
                      "x86vec::perm_v4f32(a) : -1 <= P3 < 4");
        return impl::perm1_v4f32<_P0, _P1, _P2, _P3>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128 x86vec::perm_f32(__m128 a, __m128 b)
{
        static_assert(_P0>-2 && _P0 < 8,
                      "x86vec::perm_f32(a, b) : -1 <= P0 < 8");
        static_assert(_P1>-2 && _P1 < 8,
                      "x86vec::perm_f32(a, b) : -1 <= P1 < 8");
        static_assert(_P2>-2 && _P2 < 8,
                      "x86vec::perm_f32(a, b) : -1 <= P2 < 8");
        static_assert(_P3>-2 && _P3 < 8,
                      "x86vec::perm_f32(a, b) : -1 <= P3 < 8");
        return impl::perm2_v4f32<_P0, _P1, _P2, _P3>::v(a, b);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i x86vec::perm_u16(__m128i a)
{
        static_assert(_P0>-2 && _P0 < 8,
                      "x86vec::perm_u16(a) : -1 <= P0 < 8");
        static_assert(_P1>-2 && _P1 < 8,
                      "x86vec::perm_u16(a) : -1 <= P1 < 8");
        static_assert(_P2>-2 && _P2 < 8,
                      "x86vec::perm_u16(a) : -1 <= P2 < 8");
        static_assert(_P3>-2 && _P3 < 8,
                      "x86vec::perm_u16(a) : -1 <= P3 < 8");
        static_assert(_P4>-2 && _P4 < 8,
                      "x86vec::perm_u16(a) : -1 <= P4 < 8");
        static_assert(_P5>-2 && _P5 < 8,
                      "x86vec::perm_u16(a) : -1 <= P5 < 8");
        static_assert(_P6>-2 && _P6 < 8,
                      "x86vec::perm_u16(a) : -1 <= P6 < 8");
        static_assert(_P7>-2 && _P7 < 8,
                      "x86vec::perm_u16(a) : -1 <= P7 < 8");
        return impl::perm1_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
inline
__m128i x86vec::perm_u16(__m128i a, __m128i b)
{
        static_assert(_P0>-2 && _P0 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P0 < 16");
        static_assert(_P1>-2 && _P1 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P1 < 16");
        static_assert(_P2>-2 && _P2 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P2 < 16");
        static_assert(_P3>-2 && _P3 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P3 < 16");
        static_assert(_P4>-2 && _P4 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P4 < 16");
        static_assert(_P5>-2 && _P5 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P5 < 16");
        static_assert(_P6>-2 && _P6 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P6 < 16");
        static_assert(_P7>-2 && _P7 < 16,
                      "x86vec::perm_u16(a, b) : -1 <= P7 < 16");
        return impl::perm2_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::v(a, b);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128i x86vec::perm_u32(__m128i a)
{
        static_assert(_P0>-2 && _P0 < 4,
                      "x86vec::perm_u32(a) : -1 <= P0 < 4");
        static_assert(_P1>-2 && _P1 < 4,
                      "x86vec::perm_u32(a) : -1 <= P1 < 4");
        static_assert(_P2>-2 && _P2 < 4,
                      "x86vec::perm_u32(a) : -1 <= P2 < 4");
        static_assert(_P3>-2 && _P3 < 4,
                      "x86vec::perm_u32(a) : -1 <= P3 < 4");
        return impl::perm1_v4u32<_P0, _P1, _P2, _P3>::v(a);
}

template <int _P0, int _P1, int _P2, int _P3>
inline
__m128i x86vec::perm_u32(__m128i a, __m128i b)
{
        static_assert(_P0>-2 && _P0 < 8,
                      "x86vec::perm_u32(a, b) : -1 <= P0 < 8");
        static_assert(_P1>-2 && _P1 < 8,
                      "x86vec::perm_u32(a, b) : -1 <= P1 < 8");
        static_assert(_P2>-2 && _P2 < 8,
                      "x86vec::perm_u32(a, b) : -1 <= P2 < 8");
        static_assert(_P3>-2 && _P3 < 8,
                      "x86vec::perm_u32(a, b) : -1 <= P3 < 8");
        return impl::perm2_v4u32<_P0, _P1, _P2, _P3>::v(a, b);
}

template <int _P0, int _P1>
inline
__m128i x86vec::perm_u64(__m128i a)
{
        static_assert(_P0>-2 && _P0 < 2,
                      "x86vec::perm_u64(a) : -1 <= P0 < 2");
        static_assert(_P1>-2 && _P1 < 2,
                      "x86vec::perm_u64(a) : -1 <= P1 < 2");
        const int p0 = _P0 < 0 ? -1 : _P0 * 2;
        const int p1 = _P0 < 0 ? -1 : _P0 * 2 +1;
        const int p2 = _P1 < 0 ? -1 : _P1 * 2;
        const int p3 = _P1 < 0 ? -1 : _P1 * 2 +1;
        return impl::perm1_v4u32<p0, p1, p2, p3>::v(a);
}

template <int _P0, int _P1>
inline
__m128i x86vec::perm_u64(__m128i a, __m128i b)
{
        static_assert(_P0>-2 && _P0 < 4,
                      "x86vec::perm_u64(a, b) : -1 <= P0 < 4");
        static_assert(_P1>-2 && _P1 < 4,
                      "x86vec::perm_u64(a, b) : -1 <= P1 < 4");
        const int p0 = _P0 < 0 ? -1 : _P0 * 2;
        const int p1 = _P0 < 0 ? -1 : _P0 * 2 +1;
        const int p2 = _P1 < 0 ? -1 : _P1 * 2;
        const int p3 = _P1 < 0 ? -1 : _P1 * 2 +1;
        return impl::perm2_v4u32<p0, p1, p2, p3>::v(a, b);
}


// Local variables:
// mode: c++
// end:

#endif
