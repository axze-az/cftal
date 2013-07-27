#if !defined (__X86VEC_CONST_H__)
#define __X86VEC_CONST_H__ 1

#include <cftal/x86vec_intrin.h>
#include <cstdint>

namespace x86vec {

        using std::uint8_t;
        using std::uint16_t;
        using std::uint32_t;
        using std::uint64_t;

        using std::int8_t;
        using std::int16_t;
        using std::int32_t;
        using std::int64_t;

        namespace impl {

                // union of all mixed types
                template <class _V, class _E, int _EN>
                struct vecunion {
                        union u {
                                _V _v;
                                _E _e[_EN];
                        };
                        typedef u u_t;
                };

        }

        // constants consisting of 1 uint32_t
        template <uint32_t _P>
        struct const_u32 {
                const_u32() = default;
                static
                const uint32_t val = _P;
        };

        namespace const_shift {

                static const const_u32<0> _0;
                static const const_u32<1> _1;
                static const const_u32<2> _2;
                static const const_u32<3> _3;
                static const const_u32<4> _4;
                static const const_u32<5> _5;
                static const const_u32<6> _6;
                static const const_u32<7> _7;
                static const const_u32<8> _8;
                static const const_u32<9> _9;

                static const const_u32<10> _10;
                static const const_u32<11> _11;
                static const const_u32<12> _12;
                static const const_u32<13> _13;
                static const const_u32<14> _14;
                static const const_u32<15> _15;
                static const const_u32<16> _16;
                static const const_u32<17> _17;
                static const const_u32<18> _18;
                static const const_u32<19> _19;

                static const const_u32<20> _20;
                static const const_u32<21> _21;
                static const const_u32<22> _22;
                static const const_u32<23> _23;
                static const const_u32<24> _24;
                static const const_u32<25> _25;
                static const const_u32<26> _26;
                static const const_u32<27> _27;
                static const const_u32<28> _28;
                static const const_u32<29> _29;

                static const const_u32<30> _30;
                static const const_u32<31> _31;
                static const const_u32<32> _32;
                static const const_u32<33> _33;
                static const const_u32<34> _34;
                static const const_u32<35> _35;
                static const const_u32<36> _36;
                static const const_u32<37> _37;
                static const const_u32<38> _38;
                static const const_u32<39> _39;

                static const const_u32<40> _40;
                static const const_u32<41> _41;
                static const const_u32<42> _42;
                static const const_u32<43> _43;
                static const const_u32<44> _44;
                static const const_u32<45> _45;
                static const const_u32<46> _46;
                static const const_u32<47> _47;
                static const const_u32<48> _48;
                static const const_u32<49> _49;

                static const const_u32<50> _50;
                static const const_u32<51> _51;
                static const const_u32<52> _52;
                static const const_u32<53> _53;
                static const const_u32<54> _54;
                static const const_u32<55> _55;
                static const const_u32<56> _56;
                static const const_u32<57> _57;
                static const const_u32<58> _58;
                static const const_u32<59> _59;

                static const const_u32<60> _60;
                static const const_u32<61> _61;
                static const const_u32<62> _62;
                static const const_u32<63> _63;
        }

        // static constants consisting of 4 uint32_t
        template <uint32_t _P0, uint32_t _P1,
                  uint32_t _P2, uint32_t _P3>
        class const_v4u32 {
                union u_t {
                        const uint32_t _u32[4];
                        const __m128i _iv;
                };
                static __attribute__((__aligned__(16),
                                      __visibility__("hidden")))
                const u_t _msk;
        public:
                static constexpr __m128i iv();
                static constexpr __m128 fv();
                static constexpr __m128d dv();
        };

        // static constants consisting of 8 uint16_t
        template <uint16_t _P0, uint16_t _P1,
                  uint16_t _P2, uint16_t _P3,
                  uint16_t _P4, uint16_t _P5,
                  uint16_t _P6, uint16_t _P7>
        class const_v8u16 {
                union u_t {
                        const uint16_t _u16[8];
                        const __m128i _iv;
                };
                static __attribute__((__aligned__(16),
                                      __visibility__("hidden")))
                const u_t _msk;
        public:
                static constexpr __m128i iv();
                static constexpr __m128 fv();
                static constexpr __m128d dv();
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
                union u_t {
                        const uint8_t _u8[16];
                        const __m128i _iv;
                };
                static __attribute__((__aligned__(16),
                                      __visibility__("hidden")))
                const u_t _msk;
        public:
                static constexpr __m128i iv();
                static constexpr __m128 fv();
                static constexpr __m128d dv();
        };

#if defined (__AVX__)
        // static constants consisting of 8 uint32_t
        template <uint32_t _P0, uint32_t _P1,
                  uint32_t _P2, uint32_t _P3,
                  uint32_t _P4, uint32_t _P5,
                  uint32_t _P6, uint32_t _P7>
        class const_v8u32 {
                union u_t {
                        const uint32_t _u32[8];
                        const __m256i _iv;
                        const __m256 _fv;
                        const __m256d _dv;
                };
                static __attribute__((__aligned__(32),
                                      __visibility__("hidden")))
                const u_t _msk;
        public:
                static constexpr __m256i iv();
                static constexpr __m256 fv();
                static constexpr __m256d dv();
        };
#endif

        namespace impl {

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
        }

        // (u)int16_t constants
        typedef const_v8u16<0x8000, 0x8000, 0x8000, 0x8000,
			    0x8000, 0x8000, 0x8000, 0x8000> v_sign_s16_msk;
        typedef const_v8u16<0x7fff, 0x7fff, 0x7fff, 0x7fff,
			    0x7fff, 0x7fff, 0x7fff, 0x7fff> v_not_sign_s16_msk;
        const int sign_s16_msk = 0xAAAA;

        // (u)int32_t constants
        typedef const_v4u32<0x80000000, 0x80000000,
			    0x80000000, 0x80000000> v_sign_s32_msk;
        typedef const_v4u32<0x7fffffff, 0x7fffffff,
			    0x7fffffff, 0x7fffffff> v_not_sign_s32_msk;
        const int sign_s32_msk = 0x8888;

        // (u)int64_t constants
        typedef const_v4u32<0x00000000, 0x80000000,
			    0x00000000, 0x80000000> v_sign_s64_msk;
        typedef const_v4u32<0xffffffff, 0x7fffffff,
			    0xffffffff, 0x7fffffff> v_not_sign_s64_msk;
        const int sign_s64_msk = 0x8080;

        // f32 constants
        typedef v_sign_s32_msk v_sign_v4f32_msk;
        typedef v_not_sign_s32_msk v_not_sign_f32_msk;

        typedef const_v8u32<0x80000000, 0x80000000,
			    0x80000000, 0x80000000,
			    0x80000000, 0x80000000,
			    0x80000000, 0x80000000> v_sign_v8f32_msk;

        typedef const_v4u32<0x7f800000, 0x7f800000,
			    0x7f800000, 0x7f800000> v_exp_f32_msk;
        typedef const_v4u32<0x807fffff, 0x807fffff,
			    0x807fffff, 0x807fffff> v_not_exp_f32_msk;
        typedef const_v4u32<0x007fffff, 0x007fffff,
			    0x007fffff, 0x007fffff> v_sig_f32_msk;
        const int sign_f32_msk = 0x0f;
        const int exp_shift_f32 = 23;
        const int exp_msk_f32 = 0xff;

        // f64 constants
        typedef v_sign_s64_msk v_sign_v2f64_msk;
        typedef v_not_sign_s64_msk v_not_sign_f64_msk;

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

        typedef const_v4u32<0x00000000,0x7ff00000,
			    0x00000000,0x7ff00000> v_exp_f64_msk;
        typedef const_v4u32<0xffffffff,0x800fffff,
			    0xffffffff,0x800fffff> v_not_exp_f64_msk;
        typedef const_v4u32<0xffffffff,0x000fffff,
			    0xffffffff,0x000fffff> v_sig_f64_msk;
        const int sign_f64_msk = 0x03;
        const int bias_f64 = 0x3ff;
        const int exp_shift_f64 = 52;
        const int exp_msk_f64 = 0x7ff;

        namespace impl {

                template <int _I>
                struct double_exp {
                        static
                        const unsigned value =
                                (_I + bias_f64) & exp_msk_f64;
                        static
                        const unsigned value_shifted =
                                value << (exp_shift_f64-32);
                };

                template <int _I>
                class double_power_of_two : public
                const_v4u32<0, double_exp<_I>::value_shifted,
			    0, double_exp<_I>::value_shifted> {
                };

        }

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


template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3>
const
typename x86vec::const_v4u32<_P0, _P1, _P2, _P3>::u_t
x86vec::const_v4u32<_P0, _P1, _P2, _P3>::_msk= {{
                _P0, _P1, _P2, _P3
        }
};

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3>
inline
constexpr __m128i x86vec::const_v4u32<_P0, _P1, _P2, _P3>::iv()
{
        return _msk._iv;
}

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3>
inline
constexpr __m128 x86vec::const_v4u32<_P0, _P1, _P2, _P3>::fv()
{
        return _mm_castsi128_ps(iv());
}

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3>
inline
constexpr __m128d x86vec::const_v4u32<_P0, _P1, _P2, _P3>::dv()
{
        return _mm_castsi128_pd(iv());
}

template <uint16_t _P0, uint16_t _P1,
          uint16_t _P2, uint16_t _P3,
          uint16_t _P4, uint16_t _P5,
          uint16_t _P6, uint16_t _P7>
const typename
x86vec::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::u_t
x86vec::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::_msk= {{
                _P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7
        }
};

template <uint16_t _P0, uint16_t _P1,
          uint16_t _P2, uint16_t _P3,
          uint16_t _P4, uint16_t _P5,
          uint16_t _P6, uint16_t _P7>
inline
constexpr __m128i
x86vec::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::iv()
{
        return _msk._iv;
}

template <uint16_t _P0, uint16_t _P1,
          uint16_t _P2, uint16_t _P3,
          uint16_t _P4, uint16_t _P5,
          uint16_t _P6, uint16_t _P7>
inline
constexpr __m128
x86vec::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::fv()
{
        return _mm_castsi128_ps(iv());
}

template <uint16_t _P0, uint16_t _P1,
          uint16_t _P2, uint16_t _P3,
          uint16_t _P4, uint16_t _P5,
          uint16_t _P6, uint16_t _P7>
inline
constexpr __m128d
x86vec::const_v8u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::dv()
{
        return _mm_castsi128_pd(iv());
}

template <uint8_t _P00, uint8_t _P01,
          uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05,
          uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09,
          uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13,
          uint8_t _P14, uint8_t _P15>
const typename
x86vec::const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
		    _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::u_t
x86vec::const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
		    _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::_msk= {{
                _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15
        }
};

template <uint8_t _P00, uint8_t _P01,
          uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05,
          uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09,
          uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13,
          uint8_t _P14, uint8_t _P15>
inline
constexpr __m128i
x86vec::const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
		    _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::iv()
{
        return _msk._iv;
}

template <uint8_t _P00, uint8_t _P01,
          uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05,
          uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09,
          uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13,
          uint8_t _P14, uint8_t _P15>
inline
constexpr __m128
x86vec::const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
		    _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::fv()
{
        return _mm_castsi128_ps(iv());
}

template <uint8_t _P00, uint8_t _P01,
          uint8_t _P02, uint8_t _P03,
          uint8_t _P04, uint8_t _P05,
          uint8_t _P06, uint8_t _P07,
          uint8_t _P08, uint8_t _P09,
          uint8_t _P10, uint8_t _P11,
          uint8_t _P12, uint8_t _P13,
          uint8_t _P14, uint8_t _P15>
inline
constexpr __m128d
x86vec::const_v16u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
		    _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::dv()
{
        return _mm_castsi128_pd(iv());
}


#if defined (__AVX__)
template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3,
          uint32_t _P4, uint32_t _P5,
          uint32_t _P6, uint32_t _P7>
const typename
x86vec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::u_t
x86vec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::_msk= {{
                _P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7
        }
};

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3,
          uint32_t _P4, uint32_t _P5,
          uint32_t _P6, uint32_t _P7>
inline
constexpr __m256i
x86vec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::iv()
{
        return _msk._iv;
}

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3,
          uint32_t _P4, uint32_t _P5,
          uint32_t _P6, uint32_t _P7>
inline
constexpr __m256
x86vec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::fv()
{
        return _msk._fv;
}

template <uint32_t _P0, uint32_t _P1,
          uint32_t _P2, uint32_t _P3,
          uint32_t _P4, uint32_t _P5,
          uint32_t _P6, uint32_t _P7>
inline
constexpr __m256d
x86vec::const_v8u32<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::dv()
{
        return _msk._dv;
}

#endif // __AVX__

// Local variables:
// mode: c++
// end:
#endif
