//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#include "cftal/config.h"
#include "cftal/impl/divide.h"
#if defined (__SSE2__)
#include "cftal/x86/ops_1.h"
#include "cftal/x86/ins_ext.h"
#include "cftal/bitops.h"
#include "cftal/mul_div.h"

#if 0
#include "cftal/vec.h"
__m128i cftal::x86::div_u16::v(__m128i x, __m128i y, __m128i* rem)
{
    v8u16 xs=x, ys=y;
    std::pair<v8u16, v8u16> qr=
        cftal::impl::udiv_double_shift<v8u16, v8u16, 16>(xs, ys);
    if (rem != nullptr)
        *rem = qr.second();
    return qr.first();
}

__m128i cftal::x86::div_s16::v(__m128i x, __m128i y, __m128i* rem)
{
    v8s16 xs=x, ys=y;
    std::pair<v8s16, v8s16> qr=
        cftal::impl::sdiv_double_shift<v8s16, v8u16, v8u16, 16>(xs, ys);
    if (rem != nullptr)
        *rem = qr.second();
    return qr.first();
}

__m128i cftal::x86::div_s32::v(__m128i x, __m128i y, __m128i* rem)
{
    v4s32 xs=x, ys=y;
    std::pair<v4s32, v4s32> qr=
        cftal::impl::sdiv_double_shift<v4s32, v4u32, v4u32, 32>(xs, ys);
    if (rem != nullptr)
        *rem = qr.second();
    return qr.first();
}
__m128i cftal::x86::div_s32::lh(__m128i x, __m128i y, __m128i* rem)
{
    return div_s32::v(x, y, rem);
}

__m128i cftal::x86::div_u32::v(__m128i x, __m128i y, __m128i* rem)
{
    v4u32 xs=x, ys=y;
    std::pair<v4u32, v4u32> qr=
        cftal::impl::udiv_double_shift<v4u32, v4u32, 32>(xs, ys);
    if (rem != nullptr)
        *rem = qr.second();
    return qr.first();
}

__m128i cftal::x86::div_u32::lh(__m128i x, __m128i y, __m128i* rem)
{
    return div_u32::v(x, y, rem);
}

#else

#define USE_RCP_PS 1

template <unsigned _POS>
__m128i cftal::x86::div_u8::pos(__m128i x, __m128i y)
{
    const __m128i msk4=const_v4u32<0xff, 0xff, 0xff, 0xff>::iv();
    __m128i xi=x, yi=y;
    if (_POS > 0) {
        xi=_mm_srli_epi32(xi, 8*_POS);
        yi=_mm_srli_epi32(yi, 8*_POS);
    }
    if (_POS < 3) {
        xi= _mm_and_si128(xi, msk4);
        yi= _mm_and_si128(yi, msk4);
    }
    __m128 xfi=_mm_cvtepi32_ps(xi);
    __m128 yfi=_mm_cvtepi32_ps(yi);
#if USE_RCP_PS>0
    __m128 offs=_mm_set1_ps(0.5f);
    xfi=_mm_add_ps(xfi, offs);
    __m128 rcp=_mm_rcp_ps(yfi);
    __m128 qfi=_mm_mul_ps(rcp, xfi);
#else
    __m128 qfi=_mm_div_ps(xfi, yfi);
#endif
    __m128i qi=_mm_cvttps_epi32(qfi);
    if (_POS < 3) {
        qi=_mm_and_si128(qi, msk4);
    }
    if (_POS > 0) {
        qi=_mm_slli_epi32(qi, 8*_POS);
    }
    return qi;
}

__m128i cftal::x86::div_u8::v(__m128i x, __m128i y, __m128i* rem)
{
    __m128i q=pos<0>(x, y);
    __m128i qi=pos<1>(x, y);
    q=_mm_or_si128(q, qi);
    qi =pos<2>(x, y);
    q=_mm_or_si128(q, qi);
    qi =pos<3>(x, y);
    q=_mm_or_si128(q, qi);
    __m128i eqz= _mm_cmpeq_epi8(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        __m128i xt = vpmullb::v(q, y);
        __m128i yt = _mm_sub_epi8(x, xt);
        _mm_store_si128(rem, yt);
    }
    return q;
}

#if defined (__AVX2__)
template <unsigned _POS>
__m256i cftal::x86::div_u8::pos(__m256i x, __m256i y)
{
    const __m256i msk4=const_v8u32<0xff, 0xff, 0xff, 0xff,
                                   0xff, 0xff, 0xff, 0xff>::iv();
    __m256i xi=x, yi=y;
    if (_POS > 0) {
        xi=_mm256_srli_epi32(xi, 8*_POS);
        yi=_mm256_srli_epi32(yi, 8*_POS);
    }
    if (_POS < 3) {
        xi= _mm256_and_si256(xi, msk4);
        yi= _mm256_and_si256(yi, msk4);
    }
    __m256 xfi=_mm256_cvtepi32_ps(xi);
    __m256 yfi=_mm256_cvtepi32_ps(yi);
#if USE_RCP_PS>0
    __m256 offs=_mm256_set1_ps(0.5f);
    xfi=_mm256_add_ps(xfi, offs);
    __m256 rcp=_mm256_rcp_ps(yfi);
    __m256 qfi=_mm256_mul_ps(rcp, xfi);
#else
    __m256 qfi=_mm_div_ps(xfi, yfi);
#endif
    __m256i qi=_mm256_cvttps_epi32(qfi);
    if (_POS < 3) {
        qi=_mm256_and_si256(qi, msk4);
    }
    if (_POS > 0) {
        qi=_mm256_slli_epi32(qi, 8*_POS);
    }
    return qi;
}

__m256i
cftal::x86::div_u8::v(__m256i x, __m256i y, __m256i* rem)
{
    __m256i q=pos<0>(x, y);
    __m256i qi=pos<1>(x, y);
    q=_mm256_or_si256(q, qi);
    qi =pos<2>(x, y);
    q=_mm256_or_si256(q, qi);
    qi =pos<3>(x, y);
    q=_mm256_or_si256(q, qi);
    __m256i eqz= _mm256_cmpeq_epi8(y, make_zero_int256::v());
    q = _mm256_or_si256(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        __m256i xt = vpmullb::v(q, y);
        __m256i yt = _mm256_sub_epi8(x, xt);
        _mm256_store_si256(rem, yt);
    }
    return q;
}

#endif

template <unsigned _POS>
__m128i cftal::x86::div_s8::pos(__m128i x, __m128i y)
{
    __m128i xi=x, yi=y;
    if (_POS < 3) {
        xi=_mm_slli_epi32(xi, 8*(3-_POS));
        yi=_mm_slli_epi32(yi, 8*(3-_POS));
    }
    xi=_mm_srai_epi32(xi, 8*3);
    yi=_mm_srai_epi32(yi, 8*3);
    __m128 xfi=_mm_cvtepi32_ps(xi);
    __m128 yfi=_mm_cvtepi32_ps(yi);
#if USE_RCP_PS>0
    __m128 offs=_mm_and_ps(xfi, v_sign_v4f32_msk::fv());
    offs=_mm_or_ps(offs, _mm_set1_ps(0.5f));
    xfi=_mm_add_ps(xfi, offs);
    __m128 rcp=_mm_rcp_ps(yfi);
    __m128 qfi=_mm_mul_ps(rcp, xfi);
#else
    __m128 qfi=_mm_div_ps(xfi, yfi);
#endif
    __m128i qi=_mm_cvttps_epi32(qfi);
    if (_POS < 3) {
        const __m128i msk4=const_v4u32<0xff, 0xff, 0xff, 0xff>::iv();
        qi=_mm_and_si128(qi, msk4);
    }
    if (_POS > 0) {
        qi=_mm_slli_epi32(qi, 8*_POS);
    }
    return qi;
}

__m128i cftal::x86::div_s8::v(__m128i x, __m128i y, __m128i* rem)
{
    __m128i q=pos<0>(x, y);
    __m128i qi=pos<1>(x, y);
    q=_mm_or_si128(q, qi);
    qi =pos<2>(x, y);
    q=_mm_or_si128(q, qi);
    qi =pos<3>(x, y);
    q=_mm_or_si128(q, qi);
    __m128i eqz= _mm_cmpeq_epi8(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        __m128i xt = vpmullb::v(q, y);
        __m128i yt = _mm_sub_epi8(x, xt);
        _mm_store_si128(rem, yt);
    }
    return q;
}


#if defined (__AVX2__)
template <unsigned _POS>
__m256i cftal::x86::div_s8::pos(__m256i x, __m256i y)
{
    __m256i xi=x, yi=y;
    if (_POS < 3) {
        xi=_mm256_slli_epi32(xi, 8*(3-_POS));
        yi=_mm256_slli_epi32(yi, 8*(3-_POS));
    }
    xi=_mm256_srai_epi32(xi, 8*3);
    yi=_mm256_srai_epi32(yi, 8*3);
    __m256 xfi=_mm256_cvtepi32_ps(xi);
    __m256 yfi=_mm256_cvtepi32_ps(yi);
#if USE_RCP_PS>0
    __m256 offs=_mm256_and_ps(xfi, v_sign_v8f32_msk::fv());
    offs=_mm256_or_ps(offs, _mm256_set1_ps(0.5f));
    xfi=_mm256_add_ps(xfi, offs);
    __m256 rcp=_mm256_rcp_ps(yfi);
    __m256 qfi=_mm256_mul_ps(rcp, xfi);
#else
    __m256 qfi=_mm256_div_ps(xfi, yfi);
#endif
    __m256i qi=_mm256_cvttps_epi32(qfi);
    if (_POS < 3) {
        const __m256i msk4=const_v8u32<0xff, 0xff, 0xff, 0xff,
                                       0xff, 0xff, 0xff, 0xff>::iv();
        qi=_mm256_and_si256(qi, msk4);
    }
    if (_POS > 0) {
        qi=_mm256_slli_epi32(qi, 8*_POS);
    }
    return qi;
}

__m256i cftal::x86::div_s8::v(__m256i x, __m256i y, __m256i* rem)
{
    __m256i q=pos<0>(x, y);
    __m256i qi=pos<1>(x, y);
    q=_mm256_or_si256(q, qi);
    qi =pos<2>(x, y);
    q=_mm256_or_si256(q, qi);
    qi =pos<3>(x, y);
    q=_mm256_or_si256(q, qi);
    __m256i eqz= _mm256_cmpeq_epi8(y, make_zero_int256::v());
    q = _mm256_or_si256(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        __m256i xt = vpmullb::v(q, y);
        __m256i yt = _mm256_sub_epi8(x, xt);
        _mm256_store_si256(rem, yt);
    }
    return q;
}
#endif

__m128i cftal::x86::div_u16::v(__m128i x, __m128i y, __m128i* rem)
{
#if defined (__AVX2__)
    __m256i xe=_mm256_cvtepu16_epi32(x);
    __m256i ye=_mm256_cvtepu16_epi32(y);
    __m256 xf=_mm256_cvtepi32_ps(xe);
    __m256 yf=_mm256_cvtepi32_ps(ye);
#if USE_RCP_PS>0
    __m256 offs=_mm256_set1_ps(0.5f);
    xf=_mm256_add_ps(xf, offs);
    __m256 rcp=_mm256_rcp_ps(yf);
#if defined (__FMA__)
    __m256 r=_mm256_fnmadd_ps(rcp, yf, _mm256_set1_ps(1.0f));
    rcp=_mm256_fmadd_ps(rcp, r, rcp);
#else
    __m256 r=_mm256_sub_ps(_mm256_set1_ps(1.0f),
                           _mm256_mul_ps(rcp, yf));
    rcp=_mm256_add_ps(_mm256_mul_ps(rcp, r), rcp);
#endif
    __m256 qf=_mm256_mul_ps(rcp, xf);
#else
    __m256 qf=_mm256_div_ps(xf, yf);
#endif
    __m256i qi=_mm256_cvttps_epi32(qf);
    const __m256i msk=
        const_v32u8<0, 1, 4, 5, 8, 9, 12, 13,
                    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                    0, 1, 4, 5, 8, 9, 12, 13,
                    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff>::iv();
    qi= vpshufb::v(qi, msk);
    qi= perm1_v8u32<0, 1, 4, 5, 0, 1, 4, 5>::v(qi);
    __m128i q=_mm256_castsi256_si128(qi);
    // set quotient to -1 where divisor is zero
    __m128i eqz= _mm_cmpeq_epi16(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        __m128i xt = _mm_mullo_epi16(q, y);
        __m128i yt = _mm_sub_epi16(x, xt);
        _mm_store_si128(rem, yt);
    }
    return q;
#else
    __m128i xt = vpsrld_const<16>::v(x);
    __m128i yt = vpsrld_const<16>::v(y);
    __m128 xf= _mm_cvtepi32_ps(xt);
    __m128 yf= _mm_cvtepi32_ps(yt);
#if USE_RCP_PS>0
    __m128 offs=_mm_set1_ps(0.5f);
    xf=_mm_add_ps(xf, offs);
    __m128 rcp=_mm_rcp_ps(yf);
#if defined (__FMA__)
    __m128 r=_mm_fnmadd_ps(rcp, yf, _mm_set1_ps(1.0f));
    rcp=_mm_fmadd_ps(rcp, r, rcp);
#else
    __m128 r=_mm_sub_ps(_mm_set1_ps(1.0f),
                        _mm_mul_ps(rcp, yf));
    rcp=_mm_add_ps(_mm_mul_ps(rcp, r), rcp);
#endif
    __m128 qf=_mm_mul_ps(rcp, xf);
#else
    __m128 qf= _mm_div_ps(xf, yf);
#endif
    __m128i qo= _mm_cvttps_epi32(qf);
    const __m128i me= const_v8u16<uint16_t(-1), 0, uint16_t(-1), 0,
                                  uint16_t(-1), 0, uint16_t(-1), 0>::iv();
    xt = _mm_and_si128(x, me);
    yt = _mm_and_si128(y, me);
    xf = _mm_cvtepi32_ps(xt);
    yf = _mm_cvtepi32_ps(yt);
#if USE_RCP_PS>0
    xf=_mm_add_ps(xf, offs);
    rcp=_mm_rcp_ps(yf);
#if defined (__FMA__)
    r=_mm_fnmadd_ps(rcp, yf, _mm_set1_ps(1.0f));
    rcp=_mm_fmadd_ps(rcp, r, rcp);
#else
    r=_mm_sub_ps(_mm_set1_ps(1.0f),
                 _mm_mul_ps(rcp, yf));
    rcp=_mm_add_ps(_mm_mul_ps(rcp, r), rcp);
#endif
    qf=_mm_mul_ps(rcp, xf);
#else
    qf = _mm_div_ps(xf, yf);
#endif
    __m128i q = _mm_cvttps_epi32(qf);
    qo = vpslld_const<16>::v(qo);
    q = _mm_and_si128(q, me);
    q = _mm_or_si128(q, qo);
    // set quotient to -1 where divisor is zero
    __m128i eqz= _mm_cmpeq_epi16(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        xt = _mm_mullo_epi16(q, y);
        yt = _mm_sub_epi16(x, xt);
        _mm_store_si128(rem, yt);
    }
    return q;
#endif
}

#if defined (__AVX2__)
__m256i cftal::x86::div_u16::v(__m256i x, __m256i y, __m256i* rem)
{
    __m128i lx=_mm256_castsi256_si128(x);
    __m128i ly=_mm256_castsi256_si128(y);
    __m128i* pl= rem == nullptr ?
        nullptr : reinterpret_cast<__m128i*>(rem);
    __m128i rl=v(lx, ly, pl);
    __m128i hx=_mm256_extracti128_si256(x, 1);
    __m128i hy=_mm256_extracti128_si256(y, 1);
    __m128i* ph= rem == nullptr ?
        nullptr : reinterpret_cast<__m128i*>(rem) + 1;
    __m128i rh=v(hx, hy, ph);
    return _mm256_setr_m128i(rl, rh);
}
#endif


__m128i cftal::x86::div_s16::v(__m128i x, __m128i y, __m128i* rem)
{
#if defined (__AVX2__)
    __m256i xe=_mm256_cvtepi16_epi32(x);
    __m256i ye=_mm256_cvtepi16_epi32(y);
    __m256 xf=_mm256_cvtepi32_ps(xe);
    __m256 yf=_mm256_cvtepi32_ps(ye);
#if USE_RCP_PS>0
    __m256 offs=_mm256_and_ps(xf, _mm256_set1_ps(-0.0f));
    offs=_mm256_or_ps(offs, _mm256_set1_ps(0.5f));
    xf=_mm256_add_ps(xf, offs);
    __m256 rcp=_mm256_rcp_ps(yf);
#if defined (__FMA__)
    __m256 r=_mm256_fnmadd_ps(rcp, yf, _mm256_set1_ps(1.0f));
    rcp=_mm256_fmadd_ps(rcp, r, rcp);
#else
    __m256 r=_mm256_sub_ps(_mm256_set1_ps(1.0f),
                           _mm256_mul_ps(rcp, yf));
    rcp=_mm256_add_ps(_mm256_mul_ps(rcp, r), rcp);
#endif
    __m256 qf=_mm256_mul_ps(rcp, xf);
#else
    __m256 qf=_mm256_div_ps(xf, yf);
#endif
    __m256i qi=_mm256_cvttps_epi32(qf);
    const __m256i msk=
        const_v32u8<0, 1, 4, 5, 8, 9, 12, 13,
                    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                    0, 1, 4, 5, 8, 9, 12, 13,
                    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff>::iv();
    qi= vpshufb::v(qi, msk);
    qi= perm1_v8u32<0, 1, 4, 5, 0, 1, 4, 5>::v(qi);
    __m128i q=_mm256_castsi256_si128(qi);
    // set quotient to -1 where divisor is zero
    __m128i eqz= _mm_cmpeq_epi16(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        __m128i xt = _mm_mullo_epi16(q, y);
        __m128i yt = _mm_sub_epi16(x, xt);
        _mm_store_si128(rem, yt);
    }
    return q;
#else
    // shift even elements to odd positions
    __m128i xe = vpslld_const<16>::v(x);
    __m128i ye = vpslld_const<16>::v(y);
    // convert odd elements to int32_t
    __m128i xt = vpsrad_const<16>::v(x);
    __m128i yt = vpsrad_const<16>::v(y);
    // convert even elements to int32_t
    xe = vpsrad_const<16>::v(xe);
    ye = vpsrad_const<16>::v(ye);
    __m128 xf= _mm_cvtepi32_ps(xt);
    __m128 yf= _mm_cvtepi32_ps(yt);
#if USE_RCP_PS>0
    __m128 offs=_mm_and_ps(xf, _mm_set1_ps(-0.0f));
    offs=_mm_or_ps(offs, _mm_set1_ps(0.5f));
    xf=_mm_add_ps(xf, offs);
    __m128 rcp=_mm_rcp_ps(yf);
#if defined (__FMA__)
    __m128 r=_mm_fnmadd_ps(rcp, yf, _mm_set1_ps(1.0f));
    rcp=_mm_fmadd_ps(rcp, r, rcp);
#else
    __m128 r=_mm_sub_ps(_mm_set1_ps(1.0f),
                        _mm_mul_ps(rcp, yf));
    rcp=_mm_add_ps(_mm_mul_ps(rcp, r), rcp);
#endif
    __m128 qf=_mm_mul_ps(rcp, xf);
#else
    __m128 qf= _mm_div_ps(xf, yf);
#endif
    // odd results.
    __m128i qo= _mm_cvttps_epi32(qf);
    xf = _mm_cvtepi32_ps(xe);
    yf = _mm_cvtepi32_ps(ye);
#if USE_RCP_PS>0
    offs=_mm_and_ps(xf, _mm_set1_ps(-0.0f));
    offs=_mm_or_ps(offs, _mm_set1_ps(0.5f));
    xf=_mm_add_ps(xf, offs);
    rcp=_mm_rcp_ps(yf);
#if defined (__FMA__)
    r=_mm_fnmadd_ps(rcp, yf, _mm_set1_ps(1.0f));
    rcp=_mm_fmadd_ps(rcp, r, rcp);
#else
    r=_mm_sub_ps(_mm_set1_ps(1.0f),
                    _mm_mul_ps(rcp, yf));
    rcp=_mm_add_ps(_mm_mul_ps(rcp, r), rcp);
#endif
    qf=_mm_mul_ps(rcp, xf);
#else
    qf = _mm_div_ps(xf, yf);
#endif
    // even results
    __m128i q = _mm_cvttps_epi32(qf);
    // shift left odd results
    qo = vpslld_const<16>::v(qo);
    const __m128i me= const_v8u16<uint16_t(-1), 0, uint16_t(-1), 0,
                                  uint16_t(-1), 0, uint16_t(-1), 0>::iv();
    // mask out odd positions in q
    q = _mm_and_si128(q, me);
    // combine odd and even results
    q = _mm_or_si128(q, qo);
    // set quotient to -1 where divisor is zero
    __m128i eqz= _mm_cmpeq_epi16(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem!=nullptr) {
        // multiply back and subtract
        xt = _mm_mullo_epi16(q, y);
        yt = _mm_sub_epi16(x, xt);
        _mm_store_si128(rem, yt);
    }
    return q;
#endif
}

#if defined (__AVX2__)
__m256i cftal::x86::div_s16::v(__m256i x, __m256i y, __m256i* rem)
{
    __m128i lx=_mm256_castsi256_si128(x);
    __m128i ly=_mm256_castsi256_si128(y);
    __m128i* pl= rem == nullptr ?
        nullptr : reinterpret_cast<__m128i*>(rem);
    __m128i rl=v(lx, ly, pl);
    __m128i hx=_mm256_extracti128_si256(x, 1);
    __m128i hy=_mm256_extracti128_si256(y, 1);
    __m128i* ph= rem == nullptr ?
        nullptr : reinterpret_cast<__m128i*>(rem) + 1;
    __m128i rh=v(hx, hy, ph);
    return _mm256_setr_m128i(rl, rh);
}
#endif

__m128i cftal::x86::div_s32::v(__m128i x, __m128i y, __m128i* rem)
{
#if defined (__AVX__)
    __m256d xt = _mm256_cvtepi32_pd(x);
    __m256d yt = _mm256_cvtepi32_pd(y);
    __m256d qf = _mm256_div_pd(xt, yt);
    __m128i q = _mm256_cvttpd_epi32(qf);
    __m128i t;
#else
    __m128d xt= _mm_cvtepi32_pd(x);
    __m128d yt= _mm_cvtepi32_pd(y);
    __m128d qf= _mm_div_pd(xt, yt);
    __m128i q= _mm_cvttpd_epi32(qf);
    __m128i t= _mm_unpackhi_epi64(x, x);
    xt = _mm_cvtepi32_pd(t);
    t = _mm_unpackhi_epi64(y, y);
    yt = _mm_cvtepi32_pd(t);
    qf = _mm_div_pd(xt, yt);
    t = _mm_cvttpd_epi32(qf);
    q = _mm_unpacklo_epi64(q, t);
#endif
    // set quotient to -1 where divisor is zero
    __m128i eqz= _mm_cmpeq_epi32(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem != nullptr) {
        // multiply back and subtract
        t =  vpmulld::v(q, y);
        __m128i r = _mm_sub_epi32(x, t);
        _mm_store_si128(rem, r);
    }
    return q;
}

__m128i cftal::x86::div_s32::lh(__m128i x, __m128i y, __m128i* rem)
{
    __m128d xt= _mm_cvtepi32_pd(x);
    __m128d yt= _mm_cvtepi32_pd(y);
    __m128d qf= _mm_div_pd(xt, yt);
    __m128i q= _mm_cvttpd_epi32(qf);
    // set quotient to -1 where divisor is zero
    __m128i eqz= _mm_cmpeq_epi32(y, make_zero_int::v());
    q = _mm_or_si128(q, eqz);
    if (rem != nullptr) {
        // multiply back and subtract
        __m128i t =  vpmulld::lh(q, y);
        __m128i r = _mm_sub_epi32(x, t);
        _mm_store_si128(rem, r);
    }
    return q;
}

#if defined (__AVX2__)
__m256i cftal::x86::div_s32::v(__m256i x, __m256i y, __m256i* rem)
{
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
    __m512d xf = _mm512_cvtepi32_pd(x);
    __m512d yf = _mm512_cvtepi32_pd(y);
    __m512d t = _mm512_div_pd(xf, yf);
    __m256i q = _mm512_cvttpd_epi32(t);
    // set quotient to -1 where divisor is zero
    __mmask8 eqz = _mm256_cmpeq_epi32_mask(y, _mm256_setzero_si256());
    __m256i m1=_mm256_set1_epi32(-1);
    q = _mm256_mask_blend_epi32 (eqz, q, m1);
    if (rem != nullptr) {
        __m256i r= _mm256_mullo_epi32(q, y);
        r= _mm256_sub_epi32(x, r);
        _mm256_store_si256(rem, r);
    }
    return q;
#else
    __m128i xh = _mm256_extractf128_si256(x, 1);
    __m128i yh = _mm256_extractf128_si256(y, 1);

    __m256d xf = _mm256_cvtepi32_pd(_mm256_castsi256_si128(x));
    __m256d yf = _mm256_cvtepi32_pd(_mm256_castsi256_si128(y));
    __m256d t = _mm256_div_pd(xf, yf);

    __m128i rl = _mm256_cvttpd_epi32(t);
    xf = _mm256_cvtepi32_pd(xh);
    yf = _mm256_cvtepi32_pd(yh);
    t = _mm256_div_pd(xf, yf);
    __m128i rh = _mm256_cvttpd_epi32(t);

    __m256i q= _mm256_inserti128_si256(_mm256_castsi128_si256(rl), rh, 1);
    // set quotient to -1 where divisor is zero
    __m256i eqz = _mm256_cmpeq_epi32(y, _mm256_setzero_si256());
    q = _mm256_or_si256(q, eqz);
    if (rem != nullptr) {
        __m256i r= _mm256_mullo_epi32(q, y);
        r= _mm256_sub_epi32(x, r);
        _mm256_store_si256(rem, r);
    }
    return q;
#endif
}
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
__m512i cftal::x86::div_s32::v(__m512i x, __m512i y, __m512i* rem)
{
    __m256i xh = _mm512_extracti32x8_epi32(x, 1);
    __m256i yh = _mm512_extracti32x8_epi32(y, 1);

    __m512d xf = _mm512_cvtepi32_pd(_mm512_castsi512_si256(x));
    __m512d yf = _mm512_cvtepi32_pd(_mm512_castsi512_si256(y));
    __m512d t = _mm512_div_pd(xf, yf);
    __m256i rl = _mm512_cvttpd_epi32(t);
    xf = _mm512_cvtepi32_pd(xh);
    yf = _mm512_cvtepi32_pd(yh);
    t = _mm512_div_pd(xf, yf);
    __m256i rh = _mm512_cvttpd_epi32(t);

    __m512i q= _mm512_inserti32x8(_mm512_castsi256_si512(rl), rh, 1);
    // set quotient to -1 where divisor is zero
    __mmask16 eqz = _mm512_cmpeq_epi32_mask(y, _mm512_setzero_si512());
    __m512i m1=_mm512_set1_epi32(-1);
    q = _mm512_mask_blend_epi32 (eqz, q, m1);
    if (rem != nullptr) {
        __m512i r= _mm512_mullo_epi32(q, y);
        r= _mm512_sub_epi32(x, r);
        _mm512_store_si512(rem, r);
    }
    return q;
}
#endif

__m128i cftal::x86::div_u32::v(__m128i x, __m128i y, __m128i* rem)
{
#if defined (__AVX2__)
    // add 2^31
    __m128i xs = _mm_add_epi32(x, v_sign_v4s32_msk::iv());
    __m128i ys = _mm_add_epi32(y, v_sign_v4s32_msk::iv());
    // generate dp fp constant: 2^31
    const int _2_pow_31_fp_h= (1023+31)<<20;
    const __m256d _2_pow_31 =
        const_v8u32<0, _2_pow_31_fp_h, 0, _2_pow_31_fp_h,
                    0, _2_pow_31_fp_h, 0, _2_pow_31_fp_h>::dv();
    // convert low halves to double
    __m256d xt = _mm256_cvtepi32_pd(xs);
    __m256d yt = _mm256_cvtepi32_pd(ys);
    // add 2^31
    xt = _mm256_add_pd(xt, _2_pow_31);
    yt = _mm256_add_pd(yt, _2_pow_31);
    __m256d q = _mm256_div_pd(xt, yt);
    // convert back to uint32
    // compare against 2^31
    __m256d hm= _mm256_cmp_pd(_2_pow_31, q, _CMP_LE_OS);
    __m256d corr= _mm256_and_pd(hm, _2_pow_31);
    // subtract 2^31 where necessary
    q = _mm256_sub_pd(q, corr);
    // convert
    __m256i xm= as<__m256i>(hm);
    const __m256i xm_perm= const_v8u32<1, 3, 5, 7, 0, 2, 4, 6>::iv();
    xm=_mm256_permutevar8x32_epi32(xm, xm_perm);
    // correct too large values later
    __m128i qi=_mm256_cvttpd_epi32(q);
    __m128i xml = as<__m128i>(xm);
    xml=_mm_slli_epi32(xml, 31);
    qi = _mm_xor_si128(qi, xml);
#else
    // add 2^31
    __m128i xs = _mm_add_epi32(x, v_sign_v4s32_msk::iv());
    __m128i ys = _mm_add_epi32(y, v_sign_v4s32_msk::iv());
    // generate dp fp constant: 2^31
    const int _2_pow_31_fp_h= (1023+31)<<20;
    const __m128d _2_pow_31 =
        const_v4u32<0, _2_pow_31_fp_h, 0, _2_pow_31_fp_h>::dv();
    // convert low halves to double
    __m128d xt = _mm_cvtepi32_pd(xs);
    __m128d yt = _mm_cvtepi32_pd(ys);
    // add 2^31
    xt = _mm_add_pd(xt, _2_pow_31);
    yt = _mm_add_pd(yt, _2_pow_31);
    __m128d q = _mm_div_pd(xt, yt);
    // convert back to uint32
    // compare against 2^31
    __m128d hm= _mm_cmple_pd(_2_pow_31, q);
    __m128d corr= _mm_and_pd(hm, _2_pow_31);
    // subtract 2^31 where necessary
    q = _mm_sub_pd(q, corr);
    // convert
    __m128 xml= as<__m128>(hm);
    // correct too large values later
    __m128i qil=_mm_cvttpd_epi32(q);

    // move high halves to low
    xs = _mm_unpackhi_epi64(xs, xs);
    ys = _mm_unpackhi_epi64(ys, ys);
    // convert to double
    xt = _mm_cvtepi32_pd(xs);
    yt = _mm_cvtepi32_pd(ys);
    // add 2^31
    xt = _mm_add_pd(xt, _2_pow_31);
    yt = _mm_add_pd(yt, _2_pow_31);
    q = _mm_div_pd(xt, yt);
    // convert back.
    hm = _mm_cmple_pd(_2_pow_31, q);
    corr =_mm_and_pd(hm, _2_pow_31);
    q = _mm_sub_pd(q, corr);
    __m128 xmh= as<__m128>(hm);
    // combine xml and xmh
    __m128i xm= as<__m128i>(vshufps<0, 2, 0, 2>::v(xml, xmh));
    xm = _mm_slli_epi32(xm, 31);
    __m128i qih= _mm_cvttpd_epi32(q);
    __m128i qi= _mm_unpacklo_epi64(qil, qih);
    qi = _mm_xor_si128(qi, xm);
#endif
    // set quotient to -1 where y==0
    __m128i eqz= _mm_cmpeq_epi32(y, make_zero_int::v());
    qi = _mm_or_si128(qi, eqz);
    if (rem != nullptr) {
        // multiply back and subtract
        __m128i p =  vpmulld::v(qi, y);
        __m128i r = _mm_sub_epi32(x, p);
        _mm_store_si128(rem, r);
    }
    return qi;
}

__m128i cftal::x86::div_u32::lh(__m128i x, __m128i y, __m128i* rem)
{
    // add 2^31
    __m128i xs = _mm_add_epi32(x, v_sign_v4s32_msk::iv());
    __m128i ys = _mm_add_epi32(y, v_sign_v4s32_msk::iv());
    // generate dp fp constant: 2^31
    const int _2_pow_31_fp_h= (1023+31)<<20;
    const __m128d _2_pow_31 =
        const_v4u32<0, _2_pow_31_fp_h, 0, _2_pow_31_fp_h>::dv();
    // convert low halves to double
    __m128d xt = _mm_cvtepi32_pd(xs);
    __m128d yt = _mm_cvtepi32_pd(ys);
    // add 2^31
    xt = _mm_add_pd(xt, _2_pow_31);
    yt = _mm_add_pd(yt, _2_pow_31);
    __m128d q = _mm_div_pd(xt, yt);
    // convert back to uint32
    // compare against 2^31
    __m128d hm= _mm_cmple_pd(_2_pow_31, q);
    __m128d corr= _mm_and_pd(hm, _2_pow_31);
    // subtract 2^31 where necessary
    q = _mm_sub_pd(q, corr);
    // convert
    __m128 xml= as<__m128>(hm);
    // correct too large values later
    __m128i qil=_mm_cvttpd_epi32(q);
    // combine xml and xmh
    __m128i xm= as<__m128i>(vshufps<0, 2, 0, 2>::v(xml, xml));
    xm = _mm_slli_epi32(xm, 31);
    __m128i qi= qil;
    qi = _mm_xor_si128(qi, xm);
    // set quotient to -1 where y==0
    __m128i eqz= _mm_cmpeq_epi32(y, make_zero_int::v());
    qi = _mm_or_si128(qi, eqz);
    if (rem != nullptr) {
        // multiply back and subtract
        __m128i p =  vpmulld::lh(qi, y);
        __m128i r = _mm_sub_epi32(x, p);
        _mm_store_si128(rem, r);
    }
    return qi;
}

#if defined (__AVX2__)
__m256i cftal::x86::div_u32::v(__m256i x, __m256i y, __m256i* rem)
{
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
    __m512d xf = _mm512_cvtepu32_pd(x);
    __m512d yf = _mm512_cvtepu32_pd(y);
    __m512d t = _mm512_div_pd(xf, yf);
    __m256i q = _mm512_cvttpd_epu32(t);
    // set quotient to -1 where divisor is zero
    __mmask8 eqz = _mm256_cmpeq_epu32_mask(y, _mm256_setzero_si256());
    __m256i m1=_mm256_set1_epi32(-1);
    q = _mm256_mask_blend_epi32 (eqz, q, m1);
    if (rem != nullptr) {
        __m256i r= _mm256_mullo_epi32(q, y);
        r= _mm256_sub_epi32(x, r);
        _mm256_store_si256(rem, r);
    }
    return q;
#else
    // add 2^31
    __m256i xs = _mm256_add_epi32(x, v_sign_v8s32_msk::iv());
    __m256i ys = _mm256_add_epi32(y, v_sign_v8s32_msk::iv());
    // generate dp fp constant: 2^31
    const int _2_pow_31_fp_h= (1023+31)<<20;
    __m256d _2_pow_31 = const_v8u32<0, _2_pow_31_fp_h,
                                    0, _2_pow_31_fp_h,
                                    0, _2_pow_31_fp_h,
                                    0, _2_pow_31_fp_h>::dv();
    // convert low halves to double
    __m256d xt = _mm256_cvtepi32_pd(_mm256_castsi256_si128(xs));
    __m256d yt = _mm256_cvtepi32_pd(_mm256_castsi256_si128(ys));
    // add 2^31
    xt = _mm256_add_pd(xt, _2_pow_31);
    yt = _mm256_add_pd(yt, _2_pow_31);
    __m256d q = _mm256_div_pd(xt, yt);
    // convert back to uint32
    // compare against 2^31
    __m256d hm= _mm256_cmp_pd(_2_pow_31, q, _CMP_LE_OS);
    __m256d corr= _mm256_and_pd(hm, _2_pow_31);
    // subtract 2^31 where necessary
    q = _mm256_sub_pd(q, corr);
    // convert
    __m256i xml= as<__m256i>(hm);
    const __m256i xm_perm= const_v8u32<1, 3, 5, 7, 0, 2, 4, 6>::iv();
    xml=_mm256_permutevar8x32_epi32(xml, xm_perm);
    // correct too large values later
    __m128i qil=_mm256_cvttpd_epi32(q);

    // move high halves to low
    xs = _mm256_castsi128_si256(_mm256_extracti128_si256(xs, 1));
    // xs = _mm256_unpackhi_epi64(xs, xs);
    ys = _mm256_castsi128_si256(_mm256_extracti128_si256(ys, 1));
    // ys = _mm256_unpackhi_epi64(ys, ys);
    // convert to double
    xt = _mm256_cvtepi32_pd(_mm256_castsi256_si128(xs));
    yt = _mm256_cvtepi32_pd(_mm256_castsi256_si128(ys));
    // add 2^31
    xt = _mm256_add_pd(xt, _2_pow_31);
    yt = _mm256_add_pd(yt, _2_pow_31);
    q = _mm256_div_pd(xt, yt);
    // convert back.
    hm = _mm256_cmp_pd(_2_pow_31, q, _CMP_LE_OS);
    corr =_mm256_and_pd(hm, _2_pow_31);
    q = _mm256_sub_pd(q, corr);
    __m256i xmh= as<__m256i>(hm);
    xmh=_mm256_permutevar8x32_epi32(xmh, xm_perm);
    // combine xml and xmh
    __m256i xm= _mm256_inserti128_si256(xml, _mm256_castsi256_si128(xmh), 1);
    xm = _mm256_slli_epi32(xm, 31);
    __m128i qih= _mm256_cvttpd_epi32(q);
    __m256i qi= _mm256_inserti128_si256(_mm256_castsi128_si256(qil), qih, 1);
    qi = _mm256_xor_si256(qi, xm);
    // set quotient to -1 where y==0
    __m256i eqz= _mm256_cmpeq_epi32(y, _mm256_setzero_si256());
    qi = _mm256_or_si256(qi, eqz);
    if (rem != nullptr) {
        // multiply back and subtract
        __m256i p =  vpmulld::v(qi, y);
        __m256i r = _mm256_sub_epi32(x, p);
        _mm256_store_si256(rem, r);
    }
    return qi;
#endif
}
#endif

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
__m512i cftal::x86::div_u32::v(__m512i x, __m512i y, __m512i* rem)
{
    __m256i xh = _mm512_extracti32x8_epi32(x, 1);
    __m256i yh = _mm512_extracti32x8_epi32(y, 1);

    __m512d xf = _mm512_cvtepu32_pd(_mm512_castsi512_si256(x));
    __m512d yf = _mm512_cvtepu32_pd(_mm512_castsi512_si256(y));
    __m512d t = _mm512_div_pd(xf, yf);
    __m256i rl = _mm512_cvttpd_epu32(t);
    xf = _mm512_cvtepu32_pd(xh);
    yf = _mm512_cvtepu32_pd(yh);
    t = _mm512_div_pd(xf, yf);
    __m256i rh = _mm512_cvttpd_epu32(t);

    __m512i q= _mm512_inserti32x8(_mm512_castsi256_si512(rl), rh, 1);
    // set quotient to -1 where divisor is zero
    __mmask16 eqz = _mm512_cmpeq_epu32_mask(y, _mm512_setzero_si512());
    __m512i m1=_mm512_set1_epi32(-1);
    q = _mm512_mask_blend_epi32 (eqz, q, m1);
    if (rem != nullptr) {
        __m512i r= _mm512_mullo_epi32(q, y);
        r= _mm512_sub_epi32(x, r);
        _mm512_store_si512(rem, r);
    }
    return q;
}
#endif


#endif

#if (__CFTAL_CFG_USE_RCP_DIV64__)
#if defined (__tune_amdfam10__)
#define SLOW_DIV 1
#endif
#if defined (__tune_k8__)
#define SLOW_DIV 1
#endif
#if defined (__tune_athlon__)
#define SLOW_DIV 1
#endif
#if defined (__tune_atom__)
#define SLOW_DIV 1
#endif
#endif

#if !SLOW_DIV

namespace {
    template <class _T>
    inline
    _T do_div(_T x, _T y, _T* rem)
    {
        _T q=cftal::impl::divide(x, y);
        if (rem != nullptr) {
            bool y_not_zero{y != _T{0}};
            *rem = y_not_zero ? cftal::remainder(x, y, q) : x;
        }
        return q;
    }

    template <class _R, unsigned _IDX, class _T>
    inline
    _R* rem_ptr(_T* rem)
    {
        union {
            _T* _t;
            _R* _r;
        } h;
        h._t = rem;
        return (h._r == nullptr) ? nullptr : h._r + _IDX;
    }
}

__m128i cftal::x86::div_u64::v(__m128i x, __m128i y, __m128i* rem)
{
    uint64_t q0 = do_div<uint64_t>(extract_u64<0>(x),
                                   extract_u64<0>(y),
                                   rem_ptr<uint64_t, 0>(rem));
    uint64_t q1 = do_div<uint64_t>(extract_u64<1>(x),
                                   extract_u64<1>(y),
                                   rem_ptr<uint64_t, 1>(rem));
    return _mm_set_epi64x(q1, q0);
}

__m128i cftal::x86::div_s64::v(__m128i x, __m128i y, __m128i* rem)
{
    int64_t q0 = do_div<int64_t>(extract_u64<0>(x),
                                 extract_u64<0>(y),
                                 rem_ptr<int64_t, 0>(rem));
    int64_t q1 = do_div<int64_t>(extract_u64<1>(x),
                                 extract_u64<1>(y),
                                 rem_ptr<int64_t, 1>(rem));
    return _mm_set_epi64x(q1, q0);
}

#if defined (__AVX2__)

__m256i cftal::x86::div_u64::v(__m256i x, __m256i y, __m256i* rem)
{
    uint64_t q0 = do_div<uint64_t>(extract_u64<0>(x),
                                   extract_u64<0>(y),
                                   rem_ptr<uint64_t, 0>(rem));
    uint64_t q1 = do_div<uint64_t>(extract_u64<1>(x),
                                   extract_u64<1>(y),
                                   rem_ptr<uint64_t, 1>(rem));
    uint64_t q2 = do_div<uint64_t>(extract_u64<2>(x),
                                   extract_u64<2>(y),
                                   rem_ptr<uint64_t, 2>(rem));
    uint64_t q3 = do_div<uint64_t>(extract_u64<3>(x),
                                   extract_u64<3>(y),
                                   rem_ptr<uint64_t, 3>(rem));
    return _mm256_set_epi64x(q3, q2, q1, q0);
}

__m256i cftal::x86::div_s64::v(__m256i x, __m256i y, __m256i* rem)
{
    int64_t q0 = do_div<int64_t>(extract_u64<0>(x),
                                 extract_u64<0>(y),
                                 rem_ptr<int64_t, 0>(rem));
    int64_t q1 = do_div<int64_t>(extract_u64<1>(x),
                                 extract_u64<1>(y),
                                 rem_ptr<int64_t, 1>(rem));
    int64_t q2 = do_div<int64_t>(extract_u64<2>(x),
                                 extract_u64<2>(y),
                                 rem_ptr<int64_t, 2>(rem));
    int64_t q3 = do_div<int64_t>(extract_u64<3>(x),
                                 extract_u64<3>(y),
                                 rem_ptr<int64_t, 3>(rem));
    return _mm256_set_epi64x(q3, q2, q1, q0);
}
#endif
#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__>0)
__m512i cftal::x86::div_u64::v(__m512i x, __m512i y, __m512i* rem)
{
    uint64_t q0 = do_div<uint64_t>(extract_u64<0>(x),
                                   extract_u64<0>(y),
                                   rem_ptr<uint64_t, 0>(rem));
    uint64_t q1 = do_div<uint64_t>(extract_u64<1>(x),
                                   extract_u64<1>(y),
                                   rem_ptr<uint64_t, 1>(rem));
    uint64_t q2 = do_div<uint64_t>(extract_u64<2>(x),
                                   extract_u64<2>(y),
                                   rem_ptr<uint64_t, 2>(rem));
    uint64_t q3 = do_div<uint64_t>(extract_u64<3>(x),
                                   extract_u64<3>(y),
                                   rem_ptr<uint64_t, 3>(rem));
    uint64_t q4 = do_div<uint64_t>(extract_u64<4>(x),
                                   extract_u64<4>(y),
                                   rem_ptr<uint64_t, 4>(rem));
    uint64_t q5 = do_div<uint64_t>(extract_u64<5>(x),
                                   extract_u64<5>(y),
                                   rem_ptr<uint64_t, 5>(rem));
    uint64_t q6 = do_div<uint64_t>(extract_u64<6>(x),
                                   extract_u64<6>(y),
                                   rem_ptr<uint64_t, 6>(rem));
    uint64_t q7 = do_div<uint64_t>(extract_u64<7>(x),
                                   extract_u64<7>(y),
                                   rem_ptr<uint64_t, 7>(rem));
    return _mm512_setr_epi64(q0, q1, q2, q3, q4, q5, q6, q7);
}

__m512i cftal::x86::div_s64::v(__m512i x, __m512i y, __m512i* rem)
{
    int64_t q0 = do_div<int64_t>(extract_u64<0>(x),
                                 extract_u64<0>(y),
                                 rem_ptr<int64_t, 0>(rem));
    int64_t q1 = do_div<int64_t>(extract_u64<1>(x),
                                 extract_u64<1>(y),
                                 rem_ptr<int64_t, 1>(rem));
    int64_t q2 = do_div<int64_t>(extract_u64<2>(x),
                                 extract_u64<2>(y),
                                 rem_ptr<int64_t, 2>(rem));
    int64_t q3 = do_div<int64_t>(extract_u64<3>(x),
                                 extract_u64<3>(y),
                                 rem_ptr<int64_t, 3>(rem));
    int64_t q4 = do_div<int64_t>(extract_u64<4>(x),
                                 extract_u64<4>(y),
                                 rem_ptr<int64_t, 4>(rem));
    int64_t q5 = do_div<int64_t>(extract_u64<5>(x),
                                 extract_u64<5>(y),
                                 rem_ptr<int64_t, 5>(rem));
    int64_t q6 = do_div<int64_t>(extract_u64<6>(x),
                                 extract_u64<6>(y),
                                 rem_ptr<int64_t, 6>(rem));
    int64_t q7 = do_div<int64_t>(extract_u64<7>(x),
                                 extract_u64<7>(y),
                                 rem_ptr<int64_t, 7>(rem));
    return _mm512_setr_epi64(q0, q1, q2, q3, q4, q5, q6, q7);
}
#endif
#else

namespace {

    void udiv64(uint64_t& q, uint64_t& r, uint64_t x, uint64_t y)
    {
        if (y != 0) {
            unsigned l_z = cftal::lzcnt(y);
            uint64_t nv = y << l_z;
            uint64_t inv = cftal::impl::udiv_2by1_rcp_64::
                reciprocal_word(nv);
            cftal::impl::udiv_result<uint64_t> qr(
                cftal::impl::
                udiv_2by1_rcp_64::d(x, 0, nv, inv, l_z));
            q = qr._q0;
            r = qr._r;
        } else {
            q = uint64_t(-1);
            r = x;
        }
    }

    void sdiv64(int64_t& q, int64_t& r, int64_t x, int64_t y)
    {
        int sx(x<0), sy(y<0);
        uint64_t ux(sx ? -x : x), uy(sy ? -y : y);
        uint64_t uq, ur;
        udiv64(uq, ur, ux, uy);
        q = uq;
        if (y && sx^sy)
            q = -q;
        r=ur;
        if (y && sx)
            r = -r;
    }

}

__m128i cftal::x86::div_u64::v(__m128i x, __m128i y, __m128i* rem)
{
    uint64_t q0, r0;
    udiv64(q0, r0, extract_u64<0>(x), extract_u64<0>(y));
    uint64_t q1, r1;
    udiv64(q1, r1, extract_u64<1>(x), extract_u64<1>(y));
    if (rem)
        _mm_store_si128(rem, _mm_set_epi64x(r1, r0));
    return _mm_set_epi64x(q1, q0);
}

__m128i cftal::x86::div_s64::v(__m128i x, __m128i y, __m128i* rem)
{
    int64_t q0, r0;
    sdiv64(q0, r0, extract_u64<0>(x), extract_u64<0>(y));
    int64_t q1, r1;
    sdiv64(q1, r1, extract_u64<1>(x), extract_u64<1>(y));
    if (rem)
        _mm_store_si128(rem, _mm_set_epi64x(r1, r0));
    return _mm_set_epi64x(q1, q0);
}

#if defined (__AVX2__)
__m256i cftal::x86::div_u64::v(__m256i x, __m256i y, __m256i* rem)
{
    uint64_t q0, r0;
    udiv64(q0, r0, extract_u64<0>(x), extract_u64<0>(y));
    uint64_t q1, r1;
    udiv64(q1, r1, extract_u64<1>(x), extract_u64<1>(y));
    uint64_t q2, r2;
    udiv64(q2, r2, extract_u64<2>(x), extract_u64<2>(y));
    uint64_t q3, r3;
    udiv64(q3, r3, extract_u64<3>(x), extract_u64<3>(y));
    if (rem)
        _mm256_store_si256(rem, _mm256_set_epi64x(r3, r2, r1, r0));
    return _mm256_set_epi64x(q3, q2, q1, q0);
}

__m256i cftal::x86::div_s64::v(__m256i x, __m256i y, __m256i* rem)
{
    int64_t q0, r0;
    sdiv64(q0, r0, extract_u64<0>(x), extract_u64<0>(y));
    int64_t q1, r1;
    sdiv64(q1, r1, extract_u64<1>(x), extract_u64<1>(y));
    int64_t q2, r2;
    sdiv64(q2, r2, extract_u64<2>(x), extract_u64<2>(y));
    int64_t q3, r3;
    sdiv64(q3, r3, extract_u64<3>(x), extract_u64<3>(y));
    if (rem)
        _mm256_store_si256(rem, _mm256_set_epi64x(r3, r2, r1, r0));
    return _mm256_set_epi64x(q3, q2, q1, q0);
}
#endif

#endif

#endif // __SSE2__
#if 0
extern "C" double cvt_u32_double(uint32_t t);
extern "C" double cvt_u64_double(uint64_t t);
extern "C" uint64_t cvt_double_uint64(double x);
extern "C" uint32_t cvt_double_uint32(double x);
extern "C" uint32_t cvt_float_u32(float x);
extern "C" int32_t cvt_float_i32(float x);
extern "C" float cvt_u32_float(uint32_t x);
extern "C" float cvt_i32_float(int32_t x);


double cvt_u32_double(uint32_t t)
{
    return double(t);
}

#if defined (__x86_64__)
double cvt_u64_double(uint64_t t)
{
    return double(t);
}

uint64_t cvt_double_uint64(double x)
{
    return uint64_t(x);
}
#endif

uint32_t cvt_double_uint32(double x)
{
    return uint32_t(x);
}

uint32_t cvt_float_u32(float x)
{
    return uint32_t(x);
}

int32_t cvt_float_i32(float x)
{
    return int32_t(x);
}

float cvt_u32_float(uint32_t x)
{
    return float(x);
}

float cvt_i32_float(int32_t x)
{
    return float(x);
}
#endif
