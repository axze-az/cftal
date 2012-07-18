#include "x86vec.h"
#include "emuvec.h"
#include "divisor.h"
#include "x86vec_test.h"


void t4(x86vec::v4u32& r0, x86vec::v4u32& r1, 
	x86vec::v4u32& r2, x86vec::v4u32& r3)
{
	transpose_4x4(r0, r1, r2, r3);
}

void t4(emuvec::v4u32& r0, emuvec::v4u32& r1, 
	emuvec::v4u32& r2, emuvec::v4u32& r3)
{
	x86vec::transpose_4x4(r0, r1, r2, r3);
}

void t4(x86vec::v4f32& r0, x86vec::v4f32& r1, 
	x86vec::v4f32& r2, x86vec::v4f32& r3)
{
	transpose_4x4(r0, r1, r2, r3);
}

void t4(emuvec::v4f32& r0, emuvec::v4f32& r1, 
	emuvec::v4f32& r2, emuvec::v4f32& r3)
{
	x86vec::transpose_4x4(r0, r1, r2, r3);
}

void t8(x86vec::v8u16& r0, x86vec::v8u16& r1, 
	x86vec::v8u16& r2, x86vec::v8u16& r3,
	x86vec::v8u16& r4, x86vec::v8u16& r5, 
	x86vec::v8u16& r6, x86vec::v8u16& r7)
{
	transpose_8x8(r0, r1, r2, r3, r4, r5, r6, r7);
}

void t8(emuvec::v8u16& r0, emuvec::v8u16& r1, 
	emuvec::v8u16& r2, emuvec::v8u16& r3,
	emuvec::v8u16& r4, emuvec::v8u16& r5, 
	emuvec::v8u16& r6, emuvec::v8u16& r7)
{
	x86vec::transpose_8x8(r0, r1, r2, r3, r4, r5, r6, r7);
}

x86vec::v8u16 t9(x86vec::v8u16::element_type r)
{
	return r;
}

x86vec::v8u16 t9(x86vec::v8u16 u, x86vec::v8u16::element_type r,
		 x86vec::v8u16::element_type* p)
{
	x86vec::v8u16 t(u+r);
	mem::store(p, t);
	return t;
}

emuvec::v8u16 t10(emuvec::v8u16::element_type r)
{
	return r;
}

emuvec::v8u16 t10(emuvec::v8u16 u, emuvec::v8u16::element_type r)
{
	return u+r;
}


#if 0
void check_float()
{
        bool rc(true);
        __m128 a = x86vec::test::load_float(false);
        // __m128 b = x86vec::test::load_float(true);
        __m128 r;
        r = x86vec::perm_float<0, -1, 1, -1>(a);
        rc &= x86vec::test::check_float("perm1_float", r,
                                        x86vec::test::idx(0,-1,1,-1));
}

template <int _P0, int _P1, int _P2, int _P3>
void check_u32()
{
        bool rc(true);
        __m128i a = x86vec::test::load_u32(false);
        // __m128 b = x86vec::test::load_u32(true);
        __m128i r;
        r = x86vec::perm_u32<_P0, _P1, _P2, _P3>(a);
        rc &= x86vec::test::check_u32("perm1_u32", r,
                                      x86vec::test::idx(_P0,_P1,_P2,_P3));
}

void chk_u32_cases()
{
        check_u32< 0,-1, 1,-1>();
        check_u32< 2,-1, 3,-1>();
        check_u32<-1, 0,-1, 1>();
        check_u32<-1, 2,-1, 3>();
        check_u32< 0, 1,-1,-1>();
        check_u32< 2, 3,-1,-1>();
        check_u32<-1,-1, 0, 1>();
        check_u32<-1,-1, 2, 3>();


}
#endif

__m128i test_perm1_u16(__m128i a)
{
        return x86vec::perm_u16<0, 1, 2, 3, 7, 6, 5, 4>(a);
}


template <int _P0, int _P1, int _P2, int _P3,
          int _P4, int _P5, int _P6, int _P7>
void chk_u16()
{
        using namespace x86vec::test;

        bool rc(true);
        __m128i a = load_u16(false);
        // __m128 b = load_u16(true);
        __m128i r;
        r = x86vec::perm_u16<_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7>(a);
        rc &= check_u16("perm1_u16", r,
                        idx(_P0, _P1, _P2, _P3, _P4, _P5, _P6, _P7));
}

void chk_u16_cases()
{
        using namespace x86vec::test;
        // copy
        chk_u16< 0, 1, 2, 3, 4, 5, 6, 7>();
        // lqdq
        chk_u16< 0, 1, 2, 3, 0, 1, 2, 3>();
        // ldq
        chk_u16< 0, 1, 0, 1, 2, 3, 2, 3>();
        // lwd
        chk_u16< 0, 0, 1, 1, 2, 2, 3, 3>();

        // copied from x86vec_perm.h
        chk_u16<-1,-1,-1,-1,-1,-1,-1,-1>();
        chk_u16< 0, 1, 2, 3, 4, 5, 6, 7>();
        chk_u16< 0, 0, 1, 1, 2, 2, 3, 3>();
        chk_u16< 4, 4, 5, 5, 6, 6, 7, 7>();
        chk_u16< 0, 1, 0, 1, 2, 3, 2, 3>();
        chk_u16< 4, 5, 4, 5, 6, 7, 6, 7>();
        chk_u16< 0, 1, 2, 3, 0, 1, 2, 3>();
        chk_u16< 4, 5, 6, 7, 4, 5, 6, 7>();
        chk_u16< 0,-1, 1,-1, 2,-1, 3,-1>();
        chk_u16< 4,-1, 5,-1, 6,-1, 7,-1>();
        chk_u16<-1, 0,-1, 1,-1, 2, -1, 3>();
        chk_u16<-1, 4,-1, 5,-1, 6, -1, 7>();

        // low/high shuffles
        chk_u16< 3, 2, 1, 0, 7, 6, 5, 4>();
        chk_u16<-1, 2,-1, 0, 7, 6, 6, 4>();
        chk_u16<-1, 2, 5, 1, 0, 0, 7, 1>();

        // low/high shifts
        chk_u16<7, 6, 5, 4, 3, 2, 1, 0>();
        // 32 bit perms
        chk_u16<6, 7, 4, 5, 2, 3, 0, 1>();
        // zero only
        chk_u16< 0, -1, 2, 3, 4, 5, -1, 7>();
#if 0
        chk_u16<8, 6, 5, 4, 3, 2, 1, 0>();
        chk_u16<8, -2, 5, 4, 3, 2, 1, 0>();
#endif
}

x86vec::v4u32 muluh(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return mulh(a, b);
}

x86vec::v4s32 mulsh(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return mulh(a, b);
}

void check_div()
{
	using x86vec::test::pr_v4u32;
	__m128i u= _mm_setr_epi32(768554852, 3197531405, 
				 4035289754, 1097461812);
	__m128i v= _mm_set1_epi32(1);
	__m128i r;
	__m128i q= x86vec::impl::div_u32::v(u, v, &r);
	std::cout << pr_v4u32(q) << std::endl;
	std::cout << pr_v4u32(r) << std::endl;
}

void check_div2()
{
}


int main(int argc, char** argv)
{
        check_div();
        return 0;
}
