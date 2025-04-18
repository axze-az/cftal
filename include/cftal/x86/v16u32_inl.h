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
#if !defined (__CFTAL_X86_V16U32_INL__)
#define __CFTAL_X86_V16U32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/v16s32.h>
#include <cftal/x86/v16u32.h>
#include <cftal/x86/perm.h>
#include <cftal/x86/ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a) {
                const full_type all_set(0xffffffff);
                return _mm512_xor_si512(a(), all_set());
            }
        };

        template <>
        struct lt<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmplt_epu32_mask(a(), b());
            }
        };

        template <>
        struct le<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmple_epu32_mask(a(), b());
            }
        };

        template <>
        struct eq<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpeq_epu32_mask(a(), b());
            }
        };

        template <>
        struct ne<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpneq_epu32_mask(a(), b());
            }
        };

        template <>
        struct ge<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpge_epu32_mask(a(), b());
            }
        };

        template <>
        struct gt<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm512_cmpgt_epu32_mask(a(), b());
            }
        };

        template <>
        struct plus<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm512_sub_epi32(zero(), a());
            }
        };

        template <>
        struct add<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_add_epi32(a(), b());
            }
        };

        template <>
        struct sub<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_sub_epi32(a(), b());
            }
        };

        template <>
        struct mul<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::vpmulld::v(a(), b());
            }
        };

        template <>
        struct div<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_u32::v(a(), b());
            }
        };

        template <>
        struct mod<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v16u32 q(a/b);
                v16u32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<vec<uint32_t, 16>>::v(
                    mul<vec<uint32_t, 16>>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<vec<uint32_t, 16>>::v(
                    mul<vec<uint32_t, 16>>::v(a , b), c);
            }
        };

        template <>
        struct fnma<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<vec<uint32_t, 16>>::v(
                    c, mul<vec<uint32_t, 16>>::v(a, b));

            }
        };

        template <>
        struct bit_or<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_or_si512(a(), b());
            }
        };

        template <>
        struct bit_and<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_and_si512(a(), b());
            }
        };

        template <>
        struct bit_xor<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm512_xor_si512(a(), b());
            }
        };

        template <>
        struct shl<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm512_slli_epi32(a(), s);
            }
        };

        template <>
        struct shr<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return _mm512_srli_epi32(a(), s);
            }
        };

        template <>
        struct vshl<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return _mm512_sllv_epi32(a(), s());
            }
        };

        template <>
        struct vshr<vec<uint32_t, 16>> {
            using full_type = vec<uint32_t, 16>;
            static
            full_type
            v(const full_type& a, const full_type& s) {
                return _mm512_srlv_epi32(a(), s());
            }
        };

    }

}

inline
cftal::vec<cftal::uint32_t, 16>::vec(const vec<int32_t, 16>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::uint32_t, 16>::vec(uint32_t v)
    : base_type(_mm512_set1_epi32(v))
{
}

inline
cftal::vec<cftal::uint32_t, 16>::vec(const vec<uint32_t, 8>& l,
                                     const vec<uint32_t, 8>& h)
    : base_type(_mm512_inserti32x8(
                    _mm512_castsi256_si512(l()), h(), 1))
{
}

inline
cftal::vec<cftal::uint32_t, 16>::
vec(std::initializer_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 16> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::uint32_t, 16>::
vec(init_list<uint32_t> l)
    : vec(mem<vec<uint32_t, 16> >::load(l.begin(), l.size()))
{
}

template <template <class _U> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::uint32_t, 16>::vec(const expr<_OP<vec<uint32_t, 16> >, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::uint32_t, 16>
cftal::mem<cftal::vec<uint32_t, 16> >::load(const uint32_t* p, ssize_t s)
{
    vec<uint32_t, 16> v;
    if (s >= 16) {
        v = _mm512_loadu_si512(reinterpret_cast<const __m512i*>(p));
    } else if (s==1) {
        v = _mm512_castsi128_si512(_mm_loadu_si32(p));
    } else if (s>=2) {
        auto lh=mem<vec<uint32_t, 8> >::load(p, s);
        ssize_t sh= s>=8 ? s-8 : 0;
        auto hh=mem<vec<uint32_t, 8> >::load(p+8, sh);
        v = vec<uint32_t, 16>(lh, hh);
    } else {
        v = _mm512_set1_epi32(0);
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<uint32_t, 16> >::
store(uint32_t* p, const vec<uint32_t, 16>& v, ssize_t s)
{
    if (s>=16) {
        _mm512_storeu_si512(reinterpret_cast<__m512i*>(p), v());
    } else if (s>0) {
        mem<vec<uint32_t, 8> >::store(p, low_half(v), s);
        if (s>8) {
            mem<vec<uint32_t, 8> >::store(p+8, high_half(v), s-8);
        }
    }
}

inline
cftal::vec<uint32_t, 8>
cftal::low_half(const cftal::vec<uint32_t, 16>& v)
{
    return _mm512_castsi512_si256(v());
}

inline
cftal::vec<uint32_t, 8>
cftal::high_half(const cftal::vec<uint32_t, 16>& v)
{
    return _mm512_extracti32x8_epi32(v(), 1);
}

template <cftal::size_t _I>
inline
cftal::uint32_t
cftal::extract(const vec<uint32_t, 16>& v)
{
    return x86::extract_u32<_I>(v());
}

inline
cftal::uint32_t
cftal::extract(const vec<uint32_t, 16>& v, size_t i)
{
    return x86::extract_u32(v(), i);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<uint32_t, 16>& v, const uint32_t& vi)
{
    v= x86::insert_u32<_I>(v(), vi);
}

inline
void
cftal::insert(vec<uint32_t, 16>& v, const uint32_t& vi, size_t i)
{
    v= x86::insert_u32(v(), vi, i);
}

inline
cftal::v16u32 cftal::max(const v16u32& a, const v16u32& b)
{
    return _mm512_max_epu32(a(), b());
}

inline
cftal::v16u32 cftal::min(const v16u32& a, const v16u32& b)
{
    return _mm512_min_epu32(a(), b());
}

inline
cftal::v16u32 cftal::select(const v16u32::mask_type& m,
                            const v16u32& on_true,
                            const v16u32& on_false)
{
    return x86::select_u32(m(), on_true(), on_false());
}

inline
cftal::v16u32
cftal::select_val_or_zero(const v16u32::mask_type& m,
                          const v16u32& on_true)
{
    return _mm512_maskz_mov_epi32(m(), on_true());
}

inline
cftal::v16u32
cftal::select_zero_or_val(const v16u32::mask_type& m,
                          const v16u32& on_false)
{
    return _mm512_maskz_mov_epi32(_knot_mask16(m()), on_false());
}

template <bool _P00, bool _P01, bool _P02, bool _P03,
          bool _P04, bool _P05, bool _P06, bool _P07,
          bool _P08, bool _P09, bool _P10, bool _P11,
          bool _P12, bool _P13, bool _P14, bool _P15>
inline
cftal::v16u32 cftal::select(const v16u32& a, const v16u32& b)
{
    return x86::select_u32<_P00, _P01, _P02, _P03,
                           _P04, _P05, _P06, _P07,
                           _P08, _P09, _P10, _P11,
                           _P12, _P13, _P14, _P15> (a(), b());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16u32 cftal::permute(const v16u32& a)
{
    return x86::perm_v16u32<_P00, _P01, _P02, _P03,
                            _P04, _P05, _P06, _P07,
                            _P08, _P09, _P10, _P11,
                            _P12, _P13, _P14, _P15>(a());
}

template <int32_t _P00, int32_t _P01, int32_t _P02, int32_t _P03,
          int32_t _P04, int32_t _P05, int32_t _P06, int32_t _P07,
          int32_t _P08, int32_t _P09, int32_t _P10, int32_t _P11,
          int32_t _P12, int32_t _P13, int32_t _P14, int32_t _P15>
inline
cftal::v16u32 cftal::permute(const v16u32& a, const v16u32& b)
{
    return x86::perm_v16u32<_P00, _P01, _P02, _P03,
                            _P04, _P05, _P06, _P07,
                            _P08, _P09, _P10, _P11,
                            _P12, _P13, _P14, _P15>(a(), b());
}

inline
cftal::v16u32
cftal::permute(const v16u32& s, const v16s32& idx)
{
    return x86::permute_v16u32_v16s32(s(), idx());
}

inline
std::pair<cftal::v16u32, cftal::v16u32>
cftal::mul_lo_hi(const v16u32& x, const v16u32& y)
{
    // p0l p0h p2l p2h p4l p4h p6l p6h
    v16u32 e= _mm512_mul_epu32(x(), y());
    // p1l p1h p3l p3h p5l p5h p7l p7h
    v16u32 o= _mm512_mul_epu32(x86::vpshufd<1, 0, 3, 2>::v(x()),
			       x86::vpshufd<1, 0, 3, 2>::v(y()));
    // --------------------------------------
    v16u32 l= permute<0, 0+16,
		      2, 2+16,
		      4, 4+16,
		      6, 6+16,
		      8, 8+16,
		      10, 10+16,
		      12, 12+16,
		      14, 14+16>(e, o);
    v16u32 h= permute<1, 1+16,
		      3, 3+16,
		      5, 5+16,
		      7, 7+16,
		      9, 9+16,
		      11, 11+16,
		      13, 13+16,
		      15, 15+16>(e, o);
    return std::make_pair(l, h);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V16U32_INL__
