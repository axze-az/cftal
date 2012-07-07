#if !defined (__X86VEC_TEST_H__)
#define __X86VEC_TEST_H__ 1

#include <x86vec_ops_1.h>
#include <string>
#include <array>
#include <iostream>

namespace x86vec {

        namespace test {

		// check-01
		bool check_signs();
		bool check_popcnt();
		bool check_bitrev();
		// check non tested specializations of perm and select
		bool check_select_perm_specializations();
		// integer division routines
		bool check_div();

		// check-00

		// select tests, generated
                bool check_select_f64();
                bool check_select_f32();
                bool check_select_u64();
                bool check_select_u32();
                bool check_select_u16();

		// full perm tests, generated
		bool check_perm1_f64();
		bool check_perm2_f64();
		bool check_perm1_f32();
		bool check_perm2_f32();
		bool check_perm1_u64();
		bool check_perm2_u64();
		bool check_perm1_u32();
		bool check_perm2_u32();

		// randomized perm tests, generated
		bool check_perm1_u16();
		bool check_perm2_u16();

		// split generated functions
		bool check_perm1_f32__();
		bool check_perm1_f32_0();
		bool check_perm1_f32_1();
		bool check_perm1_f32_2();
		bool check_perm1_f32_3();

		bool check_perm2_f32__();
		bool check_perm2_f32_0();
		bool check_perm2_f32_1();
		bool check_perm2_f32_2();
		bool check_perm2_f32_3();
		bool check_perm2_f32_4();
		bool check_perm2_f32_5();
		bool check_perm2_f32_6();
		bool check_perm2_f32_7();

		// split generated functions.
		bool check_perm1_u32__();
		bool check_perm1_u32_0();
		bool check_perm1_u32_1();
		bool check_perm1_u32_2();
		bool check_perm1_u32_3();

		bool check_perm2_u32__();
		bool check_perm2_u32_0();
		bool check_perm2_u32_1();
		bool check_perm2_u32_2();
		bool check_perm2_u32_3();
		bool check_perm2_u32_4();
		bool check_perm2_u32_5();
		bool check_perm2_u32_6();
		bool check_perm2_u32_7();

		// split generated functions
		bool check_perm1_u16__();
		bool check_perm1_u16_0();
		bool check_perm1_u16_1();
		bool check_perm1_u16_2();
		bool check_perm1_u16_3();
		bool check_perm1_u16_4();
		bool check_perm1_u16_5();
		bool check_perm1_u16_6();
		bool check_perm1_u16_7();

		bool check_perm2_u16___();
		bool check_perm2_u16_00();
		bool check_perm2_u16_01();
		bool check_perm2_u16_02();
		bool check_perm2_u16_03();
		bool check_perm2_u16_04();
		bool check_perm2_u16_05();
		bool check_perm2_u16_06();
		bool check_perm2_u16_07();
		bool check_perm2_u16_08();
		bool check_perm2_u16_09();
		bool check_perm2_u16_10();
		bool check_perm2_u16_11();
		bool check_perm2_u16_12();
		bool check_perm2_u16_13();
		bool check_perm2_u16_14();
		bool check_perm2_u16_15();

		// global test generation function
                void generate(const std::string& fnamebase);
		void generate_f64(const std::string& fnamebase);
		void generate_f32(const std::string& fnamebase);
		void generate_u64(const std::string& fnamebase);
		void generate_u32(const std::string& fnamebase);
		void generate_u16(const std::string& fnamebase);

                __m128d load_f64(bool second);
                __m128 load_f32(bool second);
                __m128i load_u64(bool second);
                __m128i load_u32(bool second);
                __m128i load_u16(bool second);

		template <class _V, class _E, int _EN>
		struct vec_pr {
			typename impl::vecunion<_V, _E, _EN>::u_t _val;
			vec_pr(_V t) { _val._v= t; }
		};

		template <class _V, class _E, int _EN>
		std::ostream& operator <<(std::ostream& s,
					  const vec_pr<_V, _E, _EN>& val);

		typedef vec_pr<__m128d, double, 2> pr_v2d;
		typedef vec_pr<__m128, float, 2> pr_v4f;
		typedef vec_pr<__m128i, std::int16_t, 8> pr_v8s16;
		typedef vec_pr<__m128i, std::uint16_t, 8> pr_v8u16;
		typedef vec_pr<__m128i, std::int32_t, 4> pr_v4s32;
		typedef vec_pr<__m128i, std::uint32_t, 4> pr_v4u32;
		typedef vec_pr<__m128i, std::int64_t, 2> pr_v2s64;
		typedef vec_pr<__m128i, std::uint64_t, 2> pr_v2u64;

		class idx {
			std::array<int,8> _v;
			std::size_t _s;
		public:
			void assign(int p0, int p1) {
				_v[0] = p0; _v[1] = p1;
				_s =2;
			}
			void assign(int p0, int p1, int p2, int p3) {
				_v[0] = p0; _v[1] = p1;
				_v[2] = p2; _v[3] = p3;
				_s =4;
			}
			void assign(int p0, int p1, int p2, int p3,
				    int p4, int p5, int p6, int p7) {
				_v[0] = p0; _v[1] = p1;
				_v[2] = p2; _v[3] = p3;
				_v[4] = p4; _v[5] = p5;
				_v[6] = p6; _v[7] = p7;
				_s =8;
			}

			idx(int p0, int p1) : _v() {
				assign(p0, p1);
			}
			idx(int p0, int p1, int p2, int p3) : _v() {
				assign(p0, p1, p2, p3);
			}
			idx(int p0, int p1, int p2, int p3,
			    int p4, int p5, int p6, int p7) : _v() {
				assign(p0, p1, p2, p3,
				       p4, p5, p6, p7);
			}
			int operator[](std::size_t i) const {
				return _v[i];
			}
			std::size_t size() const {
				return _s;
			}
		};

		std::ostream& operator<<(std::ostream& s, const idx& i);

                template <class _T>
                bool check_val(_T t, int p);

                bool check_f64(const char* msg,
                                  __m128d r, const idx& i);
                bool check_f32(const char* msg,
                                 __m128 r, const idx& i);
		bool check_u16(const char* msg,
			       __m128i r, const idx& i);
		bool check_u32(const char* msg,
			       __m128i r, const idx& i);
		bool check_u64(const char* msg,
			       __m128i r, const idx& i);
        }
}

template <class _V, class _E, int _EN>
std::ostream& x86vec::test::operator<<(std::ostream& s,
				       const vec_pr< _V, _E, _EN >& v)
{
	for (int i=0; i<_EN-1; ++i) {
		if (i)
			s.write("; ", 2);
		s << v._val._e[i];
	}
	return s;
}


template <class _T>
inline
bool x86vec::test::check_val(_T t, int p)
{
        return ((p<0) && (t==0)) || (_T(p+1) == t);
}

inline __m128d x86vec::test::load_f64(bool second)
{
        __m128d r;
        if (second == true)
                r= _mm_set_pd(4.0, 3.0);
        else
                r= _mm_set_pd(2.0, 1.0);
        return r;
}

inline __m128 x86vec::test::load_f32(bool second)
{
        __m128 r;
        if (second == true)
                r= _mm_set_ps(8.0f, 7.0f, 6.0f, 5.0f);
        else
                r= _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
        return r;
}

inline __m128i x86vec::test::load_u64(bool second)
{
        __m128i r;
        if (second == true)
                r = const4_u32<3,0,4,0>::iv();
        else
                r = const4_u32<1,0,2,0>::iv();
        return r;
}

inline __m128i x86vec::test::load_u32(bool second)
{
        __m128i r;
        if (second == true)
                r = const4_u32<5,6,7,8>::iv();
        else
                r = const4_u32<1,2,3,4>::iv();
        return r;
}

inline __m128i x86vec::test::load_u16(bool second)
{
        __m128i r;
        if (second == true)
                r = const8_u16<9,10,11,12,13,14,15,16>::iv();
        else
                r = const8_u16<1,2,3,4,5,6,7,8>::iv();
        return r;
}

// Local variables:
// mode: c++
// end:
#endif
