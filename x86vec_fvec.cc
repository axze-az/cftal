#include "x86vec_fvec.h"

namespace x86vec {

	v2f64 frexp(const v2f64& v, v2s64* e);
	
	namespace impl {
		template <class _T> struct arg;

		template <> struct arg <v2f64> { typedef v2f64 type; };

		v2f64 frexp(v2f64 v, v2s64& e);

		v2u64 extract_exp(const v2f64& v);
		v2f64 insert_exp(const v2f64& v, v2u64& e);
		
	}
}

x86vec::v2f64 x86vec::frexp(const v2f64& v, v2s64* e)
{
	return impl::frexp(v, *e);
}

inline
x86vec::v2u64 x86vec::impl::extract_exp(const v2f64& v)
{
	v2u64 r(_mm_castpd_si128(v()));
	r &= v_exp_f64_msk::iv();
	r >>= const_u32<exp_shift_f64>();
	return r;
}

inline
x86vec::v2f64 x86vec::impl::insert_exp(const v2f64& v, v2u64& e)
{
	v2u64 em( e << const_u32<exp_shift_f64>());
	v2u64 e_msk_i= v_exp_f64_msk::iv();
	v2f64 e_msk_f= v_exp_f64_msk::dv();
	em &= e_msk_i;
	v2f64 r(andnot(e_msk_f, v));
	r |= _mm_castsi128_pd(em());
	return r;
}

x86vec::v2f64 x86vec::impl::frexp(v2f64 v, v2s64& er)
{
	v2u64 iv(_mm_castpd_si128(v()));
	v2u64 siv(iv << const_shift::_1);
	const v2u64 msk=const4_u32<0x00000000, 0xffe00000,
				   0x00000000, 0xffe00000>::iv();
	// inf nan zero handling
	v2u64 is_inf_nan((siv & msk) == msk);
	v2u64 is_zero(siv == make_zero_int::v());
	v2s64 is_inf_nan_zero_int(is_zero | is_inf_nan);
	v2f64 is_inf_nan_zero(_mm_castsi128_pd(is_inf_nan_zero_int()));
	v2s64 e_inf_nan_zero(make_zero_int::v());
	const v2f64& r_inf_nan_zero=v;

	// normal handling
	v2u64 exp_bias(extract_exp(v));
	v2s64 e_normal(exp_bias - int64_t(1022));
	const v2f64& r_normal= v;
		
	// denormal handling
	const v2f64 _2_54 = double_power_of_two<54>::dv();
	v2f64 r_denom(v* _2_54);
	v2s64 e_denom(extract_exp(r_denom) - int64_t(54 + 1022));
	
	// finite handling
	v2s64 is_denom_int(exp_bias == 0);
	v2f64 is_denom(_mm_castsi128_pd(is_denom_int()));
	// combine normal and denormal
	v2s64 e_finite(select(is_denom_int, e_denom, e_normal));
	v2f64 r_finite(select(is_denom, r_denom, r_normal));

	// mask out exponent
	r_finite &= v_not_exp_f64_msk::dv();
	// insert exponent
	r_finite |= const4_u32<0, 0x3fe00000, 0, 0x3fe00000>::dv();

	// combine inf nan zero and finite
	v2s64 e(select(is_inf_nan_zero_int, e_inf_nan_zero, e_finite));
	v2f64 r(select(is_inf_nan_zero, r_inf_nan_zero, r_finite));
		
	er = e;
	return r;
}
