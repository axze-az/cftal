#include "x86vec_fvec.h"
#include "x86vec_ivec.h"

namespace x86vec {

	v2f64 frexp(const v2f64& v, v2s64* e);
	
	namespace impl {
		template <class _T> struct arg;

		template <> struct arg <v2f64> { typedef v2f64 type; };

		v2f64 frexp(arg<v2f64>::type v, v2s64& e);
	}
}

x86vec::v2f64 x86vec::frexp(const v2f64& v, v2s64* e)
{
	return impl::frexp(v, *e);
}

x86vec::v2f64 x86vec::impl::frexp(arg<v2f64>::type v, v2s64& er)
{
	v2u64 iv(_mm_castpd_si128(v()));
	v2u64 siv(iv << const_shift::_1);
	const v2u64 msk=const4_u32<0x00000000, 0xffe00000,
				   0x00000000, 0xffe00000>::iv();
	v2u64 is_inf_nan((siv & msk) == msk);
	v2u64 is_zero(siv == make_zero_int::v());
	v2u64 is_inf_nan_zero_int(is_zero | is_inf_nan);
	v2f64 is_inf_nan_zero(_mm_castsi128_pd(is_inf_nan_zero_int()));

	v2s64 e_inf_nan_zero(make_zero_int::v());




	v2f64 res(select(is_inf_nan_zero, v, v));
	v2s64 e(select(v2s64(is_inf_nan_zero_int), e_inf_nan_zero, er));


	er = e;
	return res;
}
