#if !defined (__X86VEC_CONST_H__)
#define __X86VEC_CONST_H__ 1

#include <x86vec_intrin.h>
#include <cstdint>

namespace x86vec {

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
	template <std::uint32_t _P>
	struct const_u32 {
		static
		const std::uint32_t val = _P;
	};

	namespace const_shift {

		typedef const_u32<0> _0;
		typedef const_u32<1> _1;
		typedef const_u32<2> _2;
		typedef const_u32<3> _3;
		typedef const_u32<4> _4;
		typedef const_u32<5> _5;
		typedef const_u32<6> _6;
		typedef const_u32<7> _7;
		typedef const_u32<8> _8;
		typedef const_u32<9> _9;

		typedef const_u32<10> _10;
		typedef const_u32<11> _11;
		typedef const_u32<12> _12;
		typedef const_u32<13> _13;
		typedef const_u32<14> _14;
		typedef const_u32<15> _15;
		typedef const_u32<16> _16;
		typedef const_u32<17> _17;
		typedef const_u32<18> _18;
		typedef const_u32<19> _19;

		typedef const_u32<20> _20;
		typedef const_u32<21> _21;
		typedef const_u32<22> _22;
		typedef const_u32<23> _23;
		typedef const_u32<24> _24;
		typedef const_u32<25> _25;
		typedef const_u32<26> _26;
		typedef const_u32<27> _27;
		typedef const_u32<28> _28;
		typedef const_u32<29> _29;

		typedef const_u32<30> _30;
		typedef const_u32<31> _31;
		typedef const_u32<32> _32;
		typedef const_u32<33> _33;
		typedef const_u32<34> _34;
		typedef const_u32<35> _35;
		typedef const_u32<36> _36;
		typedef const_u32<37> _37;
		typedef const_u32<38> _38;
		typedef const_u32<39> _39;

		typedef const_u32<40> _40;
		typedef const_u32<41> _41;
		typedef const_u32<42> _42;
		typedef const_u32<43> _43;
		typedef const_u32<44> _44;
		typedef const_u32<45> _45;
		typedef const_u32<46> _46;
		typedef const_u32<47> _47;
		typedef const_u32<48> _48;
		typedef const_u32<49> _49;

		typedef const_u32<50> _50;
		typedef const_u32<51> _51;
		typedef const_u32<52> _52;
		typedef const_u32<53> _53;
		typedef const_u32<54> _54;
		typedef const_u32<55> _55;
		typedef const_u32<56> _56;
		typedef const_u32<57> _57;
		typedef const_u32<58> _58;
		typedef const_u32<59> _59;

		typedef const_u32<60> _60;
		typedef const_u32<61> _61;
		typedef const_u32<62> _62;
		typedef const_u32<63> _63;
	}

        // static constants consisting of 4 uint32_t
        template <std::uint32_t _P0, std::uint32_t _P1,
                  std::uint32_t _P2, std::uint32_t _P3>
        class const4_u32 {
                static __attribute__((__aligned__(16),
                                      __visibility__("hidden")))
                const std::uint32_t _msk[4];
        public:
                static constexpr __m128i iv();
                static constexpr __m128 fv();
                static constexpr __m128d dv();
        };

        // static constants consisting of 8 uint16_t
        template <std::uint16_t _P0, std::uint16_t _P1,
                  std::uint16_t _P2, std::uint16_t _P3,
                  std::uint16_t _P4, std::uint16_t _P5,
                  std::uint16_t _P6, std::uint16_t _P7>
        class const8_u16 {
                static __attribute__((__aligned__(16),
                                      __visibility__("hidden")))
                const std::uint16_t _msk[8];
        public:
                static constexpr __m128i iv();
                static constexpr __m128 fv();
                static constexpr __m128d dv();
        };

        // static constants consisting of 16 uint8_t
        template <std::uint8_t _P00, std::uint8_t _P01,
                  std::uint8_t _P02, std::uint8_t _P03,
                  std::uint8_t _P04, std::uint8_t _P05,
                  std::uint8_t _P06, std::uint8_t _P07,
                  std::uint8_t _P08, std::uint8_t _P09,
                  std::uint8_t _P10, std::uint8_t _P11,
                  std::uint8_t _P12, std::uint8_t _P13,
                  std::uint8_t _P14, std::uint8_t _P15>
        class const16_u8 {
                static __attribute__((__aligned__(16),
                                      __visibility__("hidden")))
                const std::uint8_t _msk[16];
        public:
                static constexpr __m128i iv();
                static constexpr __m128 fv();
                static constexpr __m128d dv();
        };

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

	// definition of position of signs ..
        typedef const8_u16<0x8000, 0x8000,
                           0x8000, 0x8000,
                           0x8000, 0x8000,
                           0x8000, 0x8000> v_sign_s16_msk;
        typedef const8_u16<0x7fff, 0x7fff,
                           0x7fff, 0x7fff,
                           0x7fff, 0x7fff,
                           0x7fff, 0x7fff> v_not_sign_s16_msk;
        const int sign_s16_msk = 0xAAAA;

        typedef const4_u32<0x80000000, 0x80000000,
                           0x80000000, 0x80000000> v_sign_s32_msk;
        typedef const4_u32<0x7fffffff, 0x7fffffff,
                           0x7fffffff, 0x7fffffff> v_not_sign_s32_msk;
        const int sign_s32_msk = 0x8888;

        typedef v_sign_s32_msk v_sign_f32_msk;
        typedef v_not_sign_s32_msk v_not_sign_f32_msk;
        const int sign_f32_msk = 0x0f;

        typedef const4_u32<0x00000000, 0x80000000,
                           0x00000000, 0x80000000> v_sign_s64_msk;
        typedef const4_u32<0xffffffff, 0x7fffffff,
                           0xffffffff, 0x7fffffff> v_not_sign_s64_msk;
        const int sign_s64_msk = 0x8080;

        typedef v_sign_s64_msk v_sign_f64_msk;
        typedef v_not_sign_s64_msk v_not_sign_f64_msk;
        const int sign_f64_msk = 0x03;

	// definition of common used constants
        typedef const4_u32<0x01010101, 0x01010101,
                           0x01010101, 0x01010101> v_uint8_0x01;
        typedef const4_u32<0x33333333, 0x33333333,
                           0x33333333, 0x33333333> v_uint8_0x33;
        typedef const4_u32<0x55555555, 0x55555555,
                           0x55555555, 0x55555555> v_uint8_0x55;
        typedef const4_u32<0x0f0f0f0f, 0x0f0f0f0f,
                           0x0f0f0f0f, 0x0f0f0f0f> v_uint8_0x0f;

        typedef const4_u32<0x00ff00ff, 0x00ff00ff,
                           0x00ff00ff, 0x00ff00ff> v_uint16_0x00ff;
        typedef const4_u32<0x00010001, 0x00010001,
                           0x00010001, 0x00010001> v_uint16_0x0001;
}


template <std::uint32_t _P0, std::uint32_t _P1,
          std::uint32_t _P2, std::uint32_t _P3>
const std::uint32_t
x86vec::const4_u32<_P0, _P1, _P2, _P3>::_msk[4]= {
        _P0, _P1, _P2, _P3
};

template <std::uint32_t _P0, std::uint32_t _P1,
          std::uint32_t _P2, std::uint32_t _P3>
inline
constexpr __m128i x86vec::const4_u32<_P0, _P1, _P2, _P3>::iv()
{
        __m128i v(_mm_load_si128(reinterpret_cast<const __m128i*>(_msk)));
        return v;
}

template <std::uint32_t _P0, std::uint32_t _P1,
          std::uint32_t _P2, std::uint32_t _P3>
inline
constexpr __m128 x86vec::const4_u32<_P0, _P1, _P2, _P3>::fv()
{
        __m128 v(_mm_load_ps(reinterpret_cast<const float*>(_msk)));
        return v;
}

template <std::uint32_t _P0, std::uint32_t _P1,
          std::uint32_t _P2, std::uint32_t _P3>
inline
constexpr __m128d x86vec::const4_u32<_P0, _P1, _P2, _P3>::dv()
{
        __m128d v(_mm_load_pd(reinterpret_cast<const double*>(_msk)));
        return v;
}

template <std::uint16_t _P0, std::uint16_t _P1,
          std::uint16_t _P2, std::uint16_t _P3,
          std::uint16_t _P4, std::uint16_t _P5,
          std::uint16_t _P6, std::uint16_t _P7>
const std::uint16_t
x86vec::const8_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::_msk[8]= {
        _P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7
};

template <std::uint16_t _P0, std::uint16_t _P1,
          std::uint16_t _P2, std::uint16_t _P3,
          std::uint16_t _P4, std::uint16_t _P5,
          std::uint16_t _P6, std::uint16_t _P7>
inline
constexpr __m128i
x86vec::const8_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::iv()
{
        __m128i v(_mm_load_si128(reinterpret_cast<const __m128i*>(_msk)));
        return v;
}

template <std::uint16_t _P0, std::uint16_t _P1,
          std::uint16_t _P2, std::uint16_t _P3,
          std::uint16_t _P4, std::uint16_t _P5,
          std::uint16_t _P6, std::uint16_t _P7>
inline
constexpr __m128
x86vec::const8_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::fv()
{
        __m128 v(_mm_load_ps(reinterpret_cast<const float*>(_msk)));
        return v;
}

template <std::uint16_t _P0, std::uint16_t _P1,
          std::uint16_t _P2, std::uint16_t _P3,
          std::uint16_t _P4, std::uint16_t _P5,
          std::uint16_t _P6, std::uint16_t _P7>
inline
constexpr __m128d
x86vec::const8_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>::dv()
{
        __m128d v(_mm_load_pd(reinterpret_cast<const double*>(_msk)));
        return v;
}

template <std::uint8_t _P00, std::uint8_t _P01,
          std::uint8_t _P02, std::uint8_t _P03,
          std::uint8_t _P04, std::uint8_t _P05,
          std::uint8_t _P06, std::uint8_t _P07,
          std::uint8_t _P08, std::uint8_t _P09,
          std::uint8_t _P10, std::uint8_t _P11,
          std::uint8_t _P12, std::uint8_t _P13,
          std::uint8_t _P14, std::uint8_t _P15>
const std::uint8_t
x86vec::const16_u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                   _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::
_msk[16]= {
        _P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
        _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15
};

template <std::uint8_t _P00, std::uint8_t _P01,
          std::uint8_t _P02, std::uint8_t _P03,
          std::uint8_t _P04, std::uint8_t _P05,
          std::uint8_t _P06, std::uint8_t _P07,
          std::uint8_t _P08, std::uint8_t _P09,
          std::uint8_t _P10, std::uint8_t _P11,
          std::uint8_t _P12, std::uint8_t _P13,
          std::uint8_t _P14, std::uint8_t _P15>
inline
constexpr __m128i
x86vec::const16_u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                   _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::iv()
{
        __m128i v(_mm_load_si128(reinterpret_cast<const __m128i*>(_msk)));
        return v;
}

template <std::uint8_t _P00, std::uint8_t _P01,
          std::uint8_t _P02, std::uint8_t _P03,
          std::uint8_t _P04, std::uint8_t _P05,
          std::uint8_t _P06, std::uint8_t _P07,
          std::uint8_t _P08, std::uint8_t _P09,
          std::uint8_t _P10, std::uint8_t _P11,
          std::uint8_t _P12, std::uint8_t _P13,
          std::uint8_t _P14, std::uint8_t _P15>
inline
constexpr __m128
x86vec::const16_u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                   _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::fv()
{
        __m128 v(_mm_load_ps(reinterpret_cast<const float*>(_msk)));
        return v;
}

template <std::uint8_t _P00, std::uint8_t _P01,
          std::uint8_t _P02, std::uint8_t _P03,
          std::uint8_t _P04, std::uint8_t _P05,
          std::uint8_t _P06, std::uint8_t _P07,
          std::uint8_t _P08, std::uint8_t _P09,
          std::uint8_t _P10, std::uint8_t _P11,
          std::uint8_t _P12, std::uint8_t _P13,
          std::uint8_t _P14, std::uint8_t _P15>
inline
constexpr __m128d
x86vec::const16_u8<_P00, _P01, _P02, _P03, _P04, _P05, _P06, _P07,
                   _P08, _P09, _P10, _P11, _P12, _P13, _P14, _P15>::dv()
{
        __m128d v(_mm_load_pd(reinterpret_cast<const double*>(_msk)));
        return v;
}

// Local variables:
// mode: c++
// end:
#endif
