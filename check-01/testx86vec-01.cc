#include <x86vec.h>
#include <x86vec_test.h>

#if 0
__m128 perm_f_6677(__m128 a, __m128 b)
{
	return x86vec::perm_f32<6,6,7,7>(a, b);
}

#define EXTRACT8(i)                                     \
        std::int8_t extract_u8_##i(__m128i v)		\
	{						\
                return x86vec::extract_u8< i > (v);     \
        }

EXTRACT8(0)
EXTRACT8(1)
EXTRACT8(2)
EXTRACT8(3)
EXTRACT8(4)
EXTRACT8(5)
EXTRACT8(6)
EXTRACT8(7)
EXTRACT8(8)
EXTRACT8(9)
EXTRACT8(10)
EXTRACT8(11)
EXTRACT8(12)
EXTRACT8(13)
EXTRACT8(14)
EXTRACT8(15)
// EXTRACT8(16)

#define INSERT8(i)                                              \
        __m128i insert_u8_##i(__m128i v, std::uint8_t n)        \
        {                                                       \
                return x86vec::insert_u8< i > (v, n);           \
        }

INSERT8(0)
INSERT8(1)
INSERT8(2)
INSERT8(3)
INSERT8(4)
INSERT8(5)
INSERT8(6)
INSERT8(7)
INSERT8(8)
INSERT8(9)
INSERT8(10)
INSERT8(11)
INSERT8(12)
INSERT8(13)
INSERT8(14)
INSERT8(15)
// INSERT8(16)

#define EXTRACT16(i)                                    \
        std::int16_t extract_u16_##i(__m128i v)         \
        {                                               \
                return x86vec::extract_u16< i > (v);    \
        }

EXTRACT16(0)
EXTRACT16(1)
EXTRACT16(2)
EXTRACT16(3)
EXTRACT16(4)
EXTRACT16(5)
EXTRACT16(6)
EXTRACT16(7)

#define INSERT16(i)                                             \
        __m128i insert_u16_##i(__m128i v, std::uint16_t n) {    \
                return x86vec::insert_u16< i > (v, n);          \
        }

INSERT16(0)
INSERT16(1)
INSERT16(2)
INSERT16(3)
INSERT16(4)
INSERT16(5)
INSERT16(6)
INSERT16(7)

#define EXTRACT32(i)                                    \
        std::int32_t extract_u32_##i(__m128i v) {       \
                return x86vec::extract_u32< i > (v);    \
        }

EXTRACT32(0)
EXTRACT32(1)
EXTRACT32(2)
EXTRACT32(3)

#define INSERT32(i)                                             \
        __m128i insert_u32_##i(__m128i v, std::uint32_t n)      \
        {                                                       \
                return x86vec::insert_u32< i > (v, n);          \
        }

INSERT32(0)
INSERT32(1)
INSERT32(2)
INSERT32(3)

__m128i insert_multi_u32(const std::uint32_t* p, std::size_t stride)
{
	__m128i r= _mm_cvtsi32_si128(*p);
 	r=x86vec::insert_u32<1>(r, *(p+1*stride));
 	r=x86vec::insert_u32<2>(r, *(p+2*stride));
 	r=x86vec::insert_u32<3>(r, *(p+3*stride));
	return r;
}

std::int64_t extract_u64_0(__m128i v)
{
        return x86vec::extract_u64<0>(v);
}

std::int64_t extract_u64_1(__m128i v)
{
        return x86vec::extract_u64<1>(v);
}


__m128i insert_u64_0(__m128i v, std::uint64_t n)
{
        return x86vec::insert_u64<0>(v, n);
}

__m128i insert_u64_1(__m128i v, std::uint64_t n)
{
        return x86vec::insert_u64<1>(v, n);
}

double extract_d_0(__m128d d)
{
        return x86vec::extract_f64<0>(d);
}

double extract_d_1(__m128d d)
{
        return x86vec::extract_f64<1>(d);
}

__m128d insert_d_0(__m128d d, double v)
{
        return x86vec::insert_f64<0>(d, v);
}

__m128d insert_d_1(__m128d d, double v)
{
        return x86vec::insert_f64<1>(d, v);
}

float extract_f_0(__m128 f)
{
        return x86vec::extract_f32<0>(f);
}

float extract_f_1(__m128 f)
{
        return x86vec::extract_f32<1>(f);
}

float extract_f_2(__m128 f)
{
        return x86vec::extract_f32<2>(f);
}

float extract_f_3(__m128 f)
{
        return x86vec::extract_f32<3>(f);
}

__m128 insert_f_0(__m128 f, float v)
{
        return x86vec::insert_f32<0>(f, v);
}

__m128 insert_f_1(__m128 f, float v)
{
        return x86vec::insert_f32<1>(f, v);
}

__m128 insert_f_2(__m128 f, float v)
{
        return x86vec::insert_f32<2>(f, v);
}

__m128 insert_f_3(__m128 f, float v)
{
        return x86vec::insert_f32<3>(f, v);
}

x86vec::v8s16 t1(int16_t v)
{
        return x86vec::v8s16(v);
}

x86vec::v8s16 t2(int16_t* v)
{
        return x86vec::v8s16(mem::load_bcast(v));
}

x86vec::v8s16 t3(const x86vec::v8s16& a, const x86vec::v8s16& b)
{
        return a + b;
}

x86vec::v8s16 t4(const x86vec::v8s16& a)
{
        return x86vec::permute<0, 1, 2, 3, 4, 5, 6, 7>(a);
}

x86vec::v8s16 t5(x86vec::v8s16 a)
{
        x86vec::v8s16 t(x86vec::permute<6, 7, 4, 5, 2, 3, 0, 1>(a));
        return a+t;
}

// x86-64: gcc uses xmm registers for v8s16 value arguments
x86vec::v8s16 t6(x86vec::v8s16 a, x86vec::v8s16 b)
{
        x86vec::v8s16 al(x86vec::permute<6, 7, 4, 5, 2, 3, 0, 1>(a));
        x86vec::v8s16 bl(x86vec::permute<6, 7, 4, 5, 2, 3, 0, 1>(b));
        return (a+al)*(b+bl);
}

x86vec::v8s16 t7(x86vec::v8s16 a, x86vec::v8s16 b)
{
        using x86vec::v8s16;
        v8s16 aa(abs(a)), ab(abs(b));
        v8s16 abh(max(a,b)), abl(min(a,b));
        return aa+ab + abh* abl;
}

x86vec::v8s16 t8(x86vec::v8s16 a, x86vec::v8s16 b, x86vec::v8s16 c)
{
        return mad(a, b, c);
}

void t9(x86vec::v8s16* d,
        const x86vec::v8s16* a,
        const x86vec::v8s16* b,
        const x86vec::v8s16* c,
        std::size_t n)
{
        for (std::size_t i=0; i<n; ++i) {
                d[i] = mad(a[i], b[i], c[i]);
        }
}

x86vec::v8s16 t10(x86vec::v8s16 a, x86vec::v8s16 b)
{
        return a^b;
}

x86vec::v8s16 t11()
{
        return x86vec::v8s16();
}
#endif

bool all_tests_01()
{
	bool r(true);
	r &= x86vec::test::check_signs();
	r &= x86vec::test::check_popcnt();
	r &= x86vec::test::check_select_perm_specializations();
	r &= x86vec::test::check_div();
	return r;
}

int main(int argc, char** argv)
{
	return all_tests_01()==true ? 0 : 3;
}
