#include "x86vec_traits.h"
#include "math_func.h"
#include "d_real.h"
#include <cmath>
#include <limits>

x86vec::v4f32 x86vec::pow2if(arg<v4s32>::type e)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::pow2i(e);
}

x86vec::v4f32 x86vec::ldexp(arg<v4f32>::type d, arg<v4s32>::type q)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::ldexp(d, q);
}

x86vec::v4s32 x86vec::ilogbp1(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::ilogb(d);
}

x86vec::v4s32 x86vec::ilogb(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::ilogb(d);
}

#if 0
x86vec::v4f32 x86vec::exp(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::exp(d);
}

x86vec::v4f32 x86vec::log(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::log(d);
}

x86vec::v4f32 x86vec::pow(arg<v4f32>::type b, arg<v4f32>::type e)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::pow(b, e);
}
#endif

void x86vec::sin_cos(arg<v4f32>::type d, v4f32* psin, v4f32* pcos)
{
	using traits_t=cftal::math::func_traits<v2f64, v4s32>;
	using func_t=cftal::math::func<double, int32_t, traits_t>;
	// return func_t::sin_cos(d, psin, pcos);

	if (psin != nullptr || pcos != nullptr) {
		std::pair<v2f64, v2f64> dd(cvt_widen<v2f64>(d));
		v2f64 dsin[2], dcos[2];
		v2f64* dps= psin ? &dsin[0] : nullptr;
		v2f64* dpc= pcos ? &dcos[0] : nullptr;
		func_t::native_sin_cos(dd.first, dps, dpc);
		dps= psin ? &dsin[1] : nullptr;
		dpc= pcos ? &dcos[1] : nullptr;
		func_t::native_sin_cos(dd.second, dps, dpc);
		if (psin) {
			v4f32 ss(cvt<v4f32>(dsin[0], dsin[1]));
			*psin = ss;
		}
		if (pcos) {
			v4f32 sc(cvt<v4f32>(dcos[0], dcos[1]));
			*pcos = sc;
		}
	}

}

#if 0
x86vec::v4f32 x86vec::sin(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::sin(d);
}

x86vec::v4f32 x86vec::cos(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::cos(d);
}

x86vec::v4f32 x86vec::tan(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::tan(d);
}

x86vec::v4f32 x86vec::cot(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::cot(d);
}

void x86vec::native_sincos(arg<v4f32>::type d, 
			   v4f32* psin, v4f32* pcos)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::native_sin_cos(d, psin, pcos);
}

x86vec::v4f32 x86vec::native_sin(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::native_sin(d);
}

x86vec::v4f32 x86vec::native_cos(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::native_cos(d);
}

x86vec::v4f32 x86vec::native_tan(arg<v4f32>::type d)
{
	using traits_t=cftal::math::func_traits<v4f32, v4s32>;
	using func_t=cftal::math::func<float, int32_t, traits_t>;
	return func_t::native_tan(d);
}

#endif
