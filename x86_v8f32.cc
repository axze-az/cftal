#include "x86_traits.h"
#include "math_func.h"
#include "d_real.h"
#include <cmath>
#include <limits>

#if 1

#include "x86_math_funcs.h"

DEF_MATH_FUNCS(cftal, v8f32, v8s32, float, 4)

#else

x86vec::v8f32 x86vec::pow2if(arg<v8s32>::type e)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::pow2i(e);
}

x86vec::v8f32 x86vec::ldexp(arg<v8f32>::type d, arg<v8s32>::type q)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::ldexp(d, q);
}

x86vec::v8f32 x86vec::frexp(arg<v8f32>::type d, v8s32* e)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::frexp(d, e);
}

x86vec::v8s32 x86vec::ilogbp1(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::ilogb(d);
}

x86vec::v8s32 x86vec::ilogb(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::ilogb(d);
}

#if 0
x86vec::v8f32 x86vec::exp(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::exp(d);
}

x86vec::v8f32 x86vec::log(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::log(d);
}

x86vec::v8f32 x86vec::pow(arg<v8f32>::type b, arg<v8f32>::type e)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::pow(b, e);
}
#endif

void x86vec::sincos(arg<v8f32>::type d, v8f32* psin, v8f32* pcos)
{
        using traits_t=cftal::math::func_traits<v4f64, v4s32>;
        using func_t=cftal::math::func<double, int32_t, traits_t>;

        if (psin != nullptr || pcos != nullptr) {
                std::pair<v4f64, v4f64> dd(cvt_widen<v4f64>(d));
                v4f64 dsin[2], dcos[2];
                v4f64* dps= psin ? &dsin[0] : nullptr;
                v4f64* dpc= pcos ? &dcos[0] : nullptr;
                func_t::native_sincos(dd.first, dps, dpc);
                dps= psin ? &dsin[1] : nullptr;
                dpc= pcos ? &dcos[1] : nullptr;
                func_t::native_sincos(dd.second, dps, dpc);
                if (psin) {
                        v8f32 ss(cvt_f32(dsin[0], dsin[1]));
                        *psin = ss;
                }
                if (pcos) {
                        v8f32 sc(cvt_f32(dcos[0], dcos[1]));
                        *pcos = sc;
                }
        }
}

x86vec::v8f32 x86vec::sin(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v4f64, v4s32>;
        using func_t=cftal::math::func<double, int32_t, traits_t>;
        std::pair<v4f64, v4f64> lh(cvt_lo<v4f64>(d), cvt_hi<v4f64>(d));
        std::pair<v4f64, v4f64> reslh(func_t::native_sin(lh.first),
                                      func_t::native_sin(lh.second));
        v8f32 res(cvt_f32(reslh.first, reslh.second));
        return res;
}

x86vec::v8f32 x86vec::cos(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v4f64, v4s32>;
        using func_t=cftal::math::func<double, int32_t, traits_t>;
        std::pair<v4f64, v4f64> lh(cvt_lo<v4f64>(d), cvt_hi<v4f64>(d));
        std::pair<v4f64, v4f64> reslh(func_t::native_cos(lh.first),
                                      func_t::native_cos(lh.second));
        v8f32 res(cvt_f32(reslh.first, reslh.second));
        return res;
}

x86vec::v8f32 x86vec::tan(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v4f64, v4s32>;
        using func_t=cftal::math::func<double, int32_t, traits_t>;
        std::pair<v4f64, v4f64> lh(cvt_lo<v4f64>(d), cvt_hi<v4f64>(d));
        std::pair<v4f64, v4f64> reslh(func_t::native_tan(lh.first),
                                      func_t::native_tan(lh.second));
        v8f32 res(cvt_f32(reslh.first, reslh.second));
        return res;
}

x86vec::v8f32 x86vec::cot(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v4f64, v4s32>;
        using func_t=cftal::math::func<double, int32_t, traits_t>;
        std::pair<v4f64, v4f64> lh(cvt_lo<v4f64>(d), cvt_hi<v4f64>(d));
        std::pair<v4f64, v4f64> reslh(func_t::native_cot(lh.first),
                                      func_t::native_cot(lh.second));
        v8f32 res(cvt_f32(reslh.first, reslh.second));
        return res;
}

void x86vec::native_sincos(arg<v8f32>::type d, 
                           v8f32* psin, v8f32* pcos)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::native_sincos(d, psin, pcos);
}

x86vec::v8f32 x86vec::native_sin(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::native_sin(d);
}

x86vec::v8f32 x86vec::native_cos(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::native_cos(d);
}

x86vec::v8f32 x86vec::native_tan(arg<v8f32>::type d)
{
        using traits_t=cftal::math::func_traits<v8f32, v8s32>;
        using func_t=cftal::math::func<float, int32_t, traits_t>;
        return func_t::native_tan(d);
}

#endif
