#if !defined (__X86VEC_TEST_H__)
#define __X86VEC_TEST_H__ 1

#include <cftal/x86vec.h>
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
                bool check_select_v2f64();
                bool check_select_v4f32();
                bool check_select_v2u64();
                bool check_select_v4u32();
                bool check_select_v8u16();

                bool check_select_v4f64();

		// full perm tests, generated
		bool check_perm1_v2f64();
		bool check_perm2_v2f64();
		bool check_perm1_v4f32();
		bool check_perm2_v4f32();

		bool check_perm1_v2u64();
		bool check_perm2_v2u64();
		bool check_perm1_v4u32();
		bool check_perm2_v4u32();

		bool check_perm1_v4f64();
		bool check_perm2_v4f64();

		// randomized perm tests, generated
		bool check_perm1_v8u16();
		bool check_perm2_v8u16();

		// split generated functions
		bool check_perm1_v4f32__();
		bool check_perm1_v4f32_0();
		bool check_perm1_v4f32_1();
		bool check_perm1_v4f32_2();
		bool check_perm1_v4f32_3();

		bool check_perm2_v4f32__();
		bool check_perm2_v4f32_0();
		bool check_perm2_v4f32_1();
		bool check_perm2_v4f32_2();
		bool check_perm2_v4f32_3();
		bool check_perm2_v4f32_4();
		bool check_perm2_v4f32_5();
		bool check_perm2_v4f32_6();
		bool check_perm2_v4f32_7();

		// split generated functions.
		bool check_perm1_v4u32__();
		bool check_perm1_v4u32_0();
		bool check_perm1_v4u32_1();
		bool check_perm1_v4u32_2();
		bool check_perm1_v4u32_3();

		bool check_perm2_v4u32__();
		bool check_perm2_v4u32_0();
		bool check_perm2_v4u32_1();
		bool check_perm2_v4u32_2();
		bool check_perm2_v4u32_3();
		bool check_perm2_v4u32_4();
		bool check_perm2_v4u32_5();
		bool check_perm2_v4u32_6();
		bool check_perm2_v4u32_7();

		// split generated functions
		bool check_perm1_v8u16__();
		bool check_perm1_v8u16_0();
		bool check_perm1_v8u16_1();
		bool check_perm1_v8u16_2();
		bool check_perm1_v8u16_3();
		bool check_perm1_v8u16_4();
		bool check_perm1_v8u16_5();
		bool check_perm1_v8u16_6();
		bool check_perm1_v8u16_7();

		bool check_perm2_v8u16___();
		bool check_perm2_v8u16_00();
		bool check_perm2_v8u16_01();
		bool check_perm2_v8u16_02();
		bool check_perm2_v8u16_03();
		bool check_perm2_v8u16_04();
		bool check_perm2_v8u16_05();
		bool check_perm2_v8u16_06();
		bool check_perm2_v8u16_07();
		bool check_perm2_v8u16_08();
		bool check_perm2_v8u16_09();
		bool check_perm2_v8u16_10();
		bool check_perm2_v8u16_11();
		bool check_perm2_v8u16_12();
		bool check_perm2_v8u16_13();
		bool check_perm2_v8u16_14();
		bool check_perm2_v8u16_15();

		// split generated functions
		bool check_perm1_v4f64__();
		bool check_perm1_v4f64_0();
		bool check_perm1_v4f64_1();
		bool check_perm1_v4f64_2();
		bool check_perm1_v4f64_3();

		bool check_perm2_v4f64__();
		bool check_perm2_v4f64_0();
		bool check_perm2_v4f64_1();
		bool check_perm2_v4f64_2();
		bool check_perm2_v4f64_3();
		bool check_perm2_v4f64_4();
		bool check_perm2_v4f64_5();
		bool check_perm2_v4f64_6();
		bool check_perm2_v4f64_7();

		// global test generation function
                void generate(const std::string& fnamebase);
		void generate_v2f64(const std::string& fnamebase);
		void generate_v4f32(const std::string& fnamebase);
		void generate_v2u64(const std::string& fnamebase);
		void generate_v4u32(const std::string& fnamebase);
		void generate_v8u16(const std::string& fnamebase);

		void generate_v4f64(const std::string& fnamebase);

                __m128d load_v2f64(bool second);
                __m128 load_v4f32(bool second);
                __m128i load_v2u64(bool second);
                __m128i load_v4u32(bool second);
                __m128i load_v8u16(bool second);

#if defined (__AVX__)
		__m256d load_v4f64(bool second);
#endif


                // Complementary-multiply-with-carry random generator.
                class cmwc_rng_base {
                        static const uint32_t PHI=0x9e3779b9;
                        uint32_t _c, _i;
                        uint32_t _Q[4096];
                public:
                        cmwc_rng_base(uint32_t _seed);
                        uint32_t next();
                };

                template <class _T>
                class cmwc_rng;

                template <>
                class cmwc_rng<uint32_t> : public cmwc_rng_base {
                public:
                        cmwc_rng(uint32_t _seed) : cmwc_rng_base(_seed) {
                        }
                        uint32_t next() {
                                return cmwc_rng_base::next();
                        }
                };

                template <>
                class cmwc_rng<uint64_t> : public cmwc_rng_base {
                public:
                        cmwc_rng(uint32_t _seed) : cmwc_rng_base(_seed) {
                        }
                        uint64_t next() {
                                uint64_t h= cmwc_rng_base::next();
                                uint32_t l= cmwc_rng_base::next();
                                return (h<<32)|l;
                        }
                };
		
		template <class _V, class _E, int _EN>
		struct vec_pr {
			typename impl::vecunion<_V, _E, _EN>::u_t _val;
			vec_pr(_V t) { _val._v= t; }
		};

		template <class _V, class _E, int _EN>
		std::ostream& operator <<(std::ostream& s,
					  const vec_pr<_V, _E, _EN>& val);

		typedef vec_pr<__m128d, double, 2> pr_v2d;
		typedef vec_pr<__m128, float, 4> pr_v4f;
		typedef vec_pr<__m128i, int16_t, 8> pr_v8s16;
		typedef vec_pr<__m128i, uint16_t, 8> pr_v8u16;
		typedef vec_pr<__m128i, int32_t, 4> pr_v4s32;
		typedef vec_pr<__m128i, uint32_t, 4> pr_v4u32;
		typedef vec_pr<__m128i, int64_t, 2> pr_v2s64;
		typedef vec_pr<__m128i, uint64_t, 2> pr_v2u64;
#if defined (__AVX__)
		typedef vec_pr<__m256d, double, 4> pr_v4d;
#endif

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

                bool check_v2f64(const char* msg,
                                  __m128d r, const idx& i);
                bool check_v4f32(const char* msg,
                                 __m128 r, const idx& i);
		bool check_v8u16(const char* msg,
				 __m128i r, const idx& i);
		bool check_v4u32(const char* msg,
				 __m128i r, const idx& i);
		bool check_v2u64(const char* msg,
				 __m128i r, const idx& i);
#if defined (__AVX__)
		bool check_v4f64(const char* msg,
				 __m256d r, const idx& i);
#endif

        }
}

template <class _V, class _E, int _EN>
std::ostream& x86vec::test::operator<<(std::ostream& s,
				       const vec_pr< _V, _E, _EN >& v)
{
	for (int i=0; i<_EN-1; ++i) {
		s << v._val._e[i];
		s.write("; ", 2);
	}
	s << v._val._e[_EN-1];
	return s;
}


template <class _T>
inline
bool x86vec::test::check_val(_T t, int p)
{
        return ((p<0) && (t==0)) || (_T(p+1) == t);
}

inline __m128d x86vec::test::load_v2f64(bool second)
{
        __m128d r;
        if (second == true)
                r= _mm_set_pd(4.0, 3.0);
        else
                r= _mm_set_pd(2.0, 1.0);
        return r;
}

inline __m128 x86vec::test::load_v4f32(bool second)
{
        __m128 r;
        if (second == true)
                r= _mm_set_ps(8.0f, 7.0f, 6.0f, 5.0f);
        else
                r= _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
        return r;
}

inline __m128i x86vec::test::load_v2u64(bool second)
{
        __m128i r;
        if (second == true)
                r = const_v4u32<3,0,4,0>::iv();
        else
                r = const_v4u32<1,0,2,0>::iv();
        return r;
}

inline __m128i x86vec::test::load_v4u32(bool second)
{
        __m128i r;
        if (second == true)
                r = const_v4u32<5,6,7,8>::iv();
        else
                r = const_v4u32<1,2,3,4>::iv();
        return r;
}

inline __m128i x86vec::test::load_v8u16(bool second)
{
        __m128i r;
        if (second == true)
                r = const_v8u16< 9,10,11,12,13,14,15,16>::iv();
        else
                r = const_v8u16< 1, 2, 3, 4, 5, 6, 7, 8>::iv();
        return r;
}

#if defined (__AVX__)
inline __m256d x86vec::test::load_v4f64(bool second)
{
        __m256d r;
        if (second == true)
                r= _mm256_set_pd(8.0f, 7.0f, 6.0f, 5.0f);
        else
                r= _mm256_set_pd(4.0f, 3.0f, 2.0f, 1.0f);
        return r;
}
#endif

// Local variables:
// mode: c++
// end:
#endif
