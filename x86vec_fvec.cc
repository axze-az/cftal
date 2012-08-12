#include "x86vec_fvec.h"

namespace x86vec {

	namespace impl {

		v2f64 pow2i(const v2s64& e);

		v2u64 extract_exp_with_bias(const v2f64& v);
		v2f64 insert_exp(const v2f64& v, v2u64& e);
		
		v2f64 frexp(arg<v2f64>::type v, v2s64& e);
		v2f64 ldexp(arg<v2f64>::type v, arg<v2s64>::type e);
		v2s64 ilogb(arg<v2f64>::type v);
		v2f64 exp(arg<v2f64>::type v);
		v2f64 log(arg<v2f64>::type v);

		v2f64 muladd(const v2f64& a, const v2f64& b, const v2f64& c);

		v2s64 ilogbp1(const v2f64& a);
	
	}
}

inline
x86vec::v2f64
x86vec::impl::muladd(const v2f64& a, const v2f64& b, const v2f64& c)
{
	return a* b + c;
}

inline
x86vec::v2s64
x86vec::impl::ilogbp1(const v2f64& d)
{
	v2f64 m(d < 4.9090934652977266E-91);
	v2f64 dd(2.037035976334486E90 * d);
	dd = select(m, dd, d);
	v2u64 q= (as<v2u64>(dd) >> const_shift::_52) & 0x7ff;
	const v2s64 qc0(300+ 0x3fe);
	const v2s64 qc1(     0x3fe);
	v2s64 qc(select(as<v2s64>(m), qc0, qc1));
	v2s64 r= as<v2s64>(q) - qc;
	return r;
}

x86vec::v2s64
x86vec::impl::ilogb(arg<v2f64>::type d)
{
	v2s64 e(ilogbp1(abs(d))- 1);
	e = select(as<v2s64>(d == 0.0), v2s64(-INT64_MAX), e);
	e = select(as<v2s64>(isinf(d)), v2s64(INT64_MAX), e);
	return e;
}

x86vec::v2f64
x86vec::impl::fma(arg<v2f64>::type x, arg<v2f64>::type y, arg<v2f64>::type z)
{
	const v2s64 hi_cor=const4_u32<0x4000000, 0,
				      0x4000000, 0>::iv();
	const v2s64 hi_msk=const4_u32<0xf8000000, 0xffffffff,
				      0xf8000000, 0xffffffff>::iv();
	v2s64 t;
	t= as<v2s64>(x);
	t += hi_cor;
	t &= hi_msk;
	v2f64 xh(as<v2f64>(t));
	v2f64 xl(x- xh);
	t = as<v2s64>(y);
	t += hi_cor;
	t &= hi_msk;
	v2f64 yh(as<v2f64>(t));
	v2f64 yl(y -yh);
	
	v2f64 h= x*y;
	v2f64 l= xh * yh - h + xl * yh + xh * yl + xl * yl;

	v2f64 h2 = h + z;
	v2f64 v = h2 - h;
	v2f64 l2 = (h - (h2 - v)) + (z - v) + l;
	return h2 + l2;
}


x86vec::v2f64 test_f(x86vec::v2f64 f)
{
	return isnan(f);
}

x86vec::v2f64 x86vec::frexp(const v2f64& v, v2s64* e)
{
	return impl::frexp(v, *e);
}

x86vec::v2f64 x86vec::impl::pow2i(const v2s64& e)
{
	return 0.0;
}

inline
x86vec::v2u64 x86vec::impl::extract_exp_with_bias(const v2f64& v)
{
	v2u64 r(as<v2u64>(v));
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
	r |= as<v2f64>(em);
	return r;
}

x86vec::v2f64 x86vec::impl::frexp(arg<v2f64>::type v, v2s64& er)
{
	v2f64 vabs(abs(v));
	const v2s64 zero_int(make_zero_int::v());
	const v2f64 zero_f64(as<v2f64>(zero_int));
	v2f64 is_zero(v == zero_f64);
	v2f64 is_nan(v != v);
	const v2s64 exp_msk_int(v_exp_f64_msk::iv());
	const v2f64 exp_msk_f64(as<v2f64>(exp_msk_int));
	v2f64 is_inf(vabs == exp_msk_f64);
	v2f64 is_inf_nan_zero( is_zero | is_nan | is_inf);

	v2s64 is_inf_nan_zero_int(as<v2s64>(is_inf_nan_zero));
	const v2f64& r_inf_nan_zero=v;
	const v2s64& e_inf_nan_zero=zero_int;
	
	// denormal handling
	const v2f64 _2_54 = double_power_of_two<54>::dv();
	v2f64 r_denom(v* _2_54);
	const v2s64 e_denom_corr= const4_u32<-54-1022, -1, -54-1022, -1>::iv();

	// normal handling
	// v2u64 exp_orig_pos = iv & v_exp_f64_msk::iv();
	const v2s64 e_normal_corr= const4_u32<-1022, -1, -1022, -1>::iv();
	const v2f64& r_normal= v;
		
	// finite handling
	v2s64 iv(as<v2s64>(v));
	v2s64 is_denom_int((iv & exp_msk_int) == zero_int);
	v2f64 is_denom(as<v2f64>(is_denom_int));
	// combine normal and denormal
	v2s64 e_finite(select(is_denom_int, e_denom_corr, e_normal_corr));
	v2f64 r_finite(select(is_denom, r_denom, r_normal));
	// apply the corrections:
	v2u64 exponent(as<v2u64>(r_finite));
	exponent &= as<v2u64>(exp_msk_int);
	exponent >>= const_u32<exp_shift_f64>();
	e_finite += exponent;
	// mask out exponent
	r_finite &= v_not_exp_f64_msk::dv();
	// insert exponent 2^-1
	r_finite |= const4_u32<0, 0x3fe00000, 0, 0x3fe00000>::dv();

	// combine inf nan zero and finite
	v2s64 e(select(is_inf_nan_zero_int, e_inf_nan_zero, e_finite));
	v2f64 r(select(is_inf_nan_zero, r_inf_nan_zero, r_finite));
		
	er = e;
	return r;
}

x86vec::v2f64 x86vec::impl::ldexp(arg<v2f64>::type v, arg<v2s64>::type e)
{
	const v2s64 v_exp_bias=const4_u32<bias_f64, 0, 
					  bias_f64, 0>::iv();
	v2s64 m= e >> const_shift::_63;
	m = (((m+e) >> const_shift::_9) - m ) << const_shift::_7;
	v2s64 q= q - (m << const_shift::_2);
	v2f64 u= as<v2f64>((m + v_exp_bias) << const_shift::_52);
	v2f64 x = v * u * u * u * u;
	u = as<v2f64>((q + v_exp_bias) << const_shift::_52);
	return x * u;
}

x86vec::v2f64 x86vec::ldexp(const v2f64& v, const v2s64& e)
{
	return impl::ldexp(v, e);
}

#if 0
static inline float ldexpkf(float x, int q) {
  float u;
  int m;
  m = q >> 31;
  m = (((m + q) >> 6) - m) << 4;
  q = q - (m << 2);
  u = intBitsToFloat(((int32_t)(m + 0x7f)) << 23);
  x = x * u * u * u * u;
  u = intBitsToFloat(((int32_t)(q + 0x7f)) << 23);
  return x * u;
}

static inline double ldexpk(double x, int q) {
  double u;
  int m;
  m = q >> 31;
  m = (((m + q) >> 9) - m) << 7;
  q = q - (m << 2);
  u = longBitsToDouble(((int64_t)(m + 0x3ff)) << 52);
  x = x * u * u * u * u;
  u = longBitsToDouble(((int64_t)(q + 0x3ff)) << 52);
  return x * u;
}
#endif
