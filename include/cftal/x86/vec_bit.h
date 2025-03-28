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
#if !defined (__CFTAL_X86_VEC_BIT_H__)
#define __CFTAL_X86_VEC_BIT_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/vec_bit_n.h>
#include <cftal/x86/vreg.h>

namespace cftal {

#if defined (__AVX512F__) && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
#if defined (__AVX512VL__)  && (__CFTAL_CFG_ENABLE_AVX512__ > 0)
    // struct bit { enum val { _0 =0, _1 = 1 }; };
    template <>
    class vec<bit, 2> : public x86::vreg<__mmask8> {
    public:
        static constexpr const __mmask8 mask=0x3u;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 2>;
        using base_type = x86::vreg<__mmask8>;

        using x86::vreg<__mmask8>::vreg;
        vec() = default;
        // explicit vec(bool v) : base_type(v ? 0x3 : 0) {}
        // vec(std::initializer_list<bool> l);
        // vec(init_list<bool> l);
        vec(__mmask8 v) : base_type(v) {}
        constexpr vec(const bit& v) : base_type(v()!=0 ? mask : 0U) {}
        vec(const vec<bit, 1>& l, const vec<bit, 1>& h)
            : base_type((l() & 0x1) | (__mmask8(h()) << 1)) {}
    };

    template <>
    class vec<bit, 4> : public x86::vreg<__mmask8> {
    public:
        static constexpr const __mmask8 mask=0xfu;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 4>;
        using base_type = x86::vreg<__mmask8>;

        using x86::vreg<__mmask8>::vreg;
        vec() = default;
        // explicit vec(bool v) : base_type(v ? 0xf : 0) {}
        // vec(std::initializer_list<bool> l);
        // vec(init_list<bool> l);
        vec(__mmask8 v) : base_type(v) {}
        constexpr vec(const bit& v) : base_type(v()!=0 ? mask : 0U) {}
        vec(const vec<bit, 2>& l, const vec<bit, 2>& h)
            : base_type((l() & 0x3) | (__mmask8(h()) << 2)) {}
    };
#endif

    template <>
    class vec<bit, 8> : public x86::vreg<__mmask8> {
    public:
        static constexpr const __mmask8 mask=0xffu;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 8>;
        using base_type = x86::vreg<__mmask8>;

        using x86::vreg<__mmask8>::vreg;
        vec() = default;
        // explicit vec(bool v) : base_type(v ? 0xff : 0) {}
        // vec(std::initializer_list<bool> l);
        // vec(init_list<bool> l);
        constexpr vec(const bit& v) : base_type(v()!=0 ? mask : 0U) {}
        vec(__mmask8 v) : base_type(v) {}
        vec(const vec<bit, 4>& l, const vec<bit, 4>& h)
            : base_type((l() & 0xf) | (__mmask8(h()) << 4)) {}
    };

    template <>
    class vec<bit, 16> : public x86::vreg<__mmask16> {
    public:
        static constexpr const __mmask16 mask=0xffffu;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 16>;
        using base_type = x86::vreg<__mmask16>;

        using x86::vreg<__mmask16>::vreg;
        vec() = default;
        // explicit vec(bool v) : base_type(v ? 0xffff : 0) {}
        // vec(std::initializer_list<bool> l);
        // vec(init_list<bool> l);
        constexpr vec(const bit& v) : base_type(v()!=0 ? mask : 0U) {}
        vec(__mmask16 v) : base_type(v) {}
        vec(const vec<bit, 8>& l, const vec<bit, 8>& h)
            : base_type((l() & 0xff) | (__mmask16(h()) << 8)) {}
    };

#if defined (__AVX512VL__) && defined (__AVX512BW__)  \
    && (__CFTAL_CFG_ENABLE_AVX512__ > 0)

    template <>
    class vec<bit, 32> : public x86::vreg<__mmask32> {
    public:
        static constexpr const __mmask32 mask=0xffffffffu;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 32>;
        using base_type = x86::vreg<__mmask32>;

        using x86::vreg<__mmask32>::vreg;
        vec() = default;
        // explicit vec(bool v) : base_type(v ? 0xffffffff : 0) {}
        // vec(std::initializer_list<bool> l);
        // vec(init_list<bool> l);
        constexpr vec(const bit& v) : base_type(v()!=0 ? mask : 0U) {}
        vec(__mmask32 v) : base_type(v) {}
        vec(const vec<bit, 16>& l, const vec<bit, 16>& h)
            : base_type((l() & 0xffff) | (__mmask32(h()) << 16)) {}
    };

    template <>
    class vec<bit, 64> : public x86::vreg<__mmask64> {
    public:
        static constexpr const __mmask64 mask=0xffffffffffffffffULL;
        using value_type = bit;
        using mask_value_type = bit;
        using mask_type= vec<mask_value_type, 64>;
        using base_type = x86::vreg<__mmask64>;

        using x86::vreg<__mmask64>::vreg;
        vec() = default;
        // explicit vec(bool v) : base_type(v ? 0xffffffffffffffffLL : 0) {}
        // vec(std::initializer_list<bool> l);
        // vec(init_list<bool> l);
        constexpr vec(const bit& v) : base_type(v()!=0 ? mask : 0ULL) {}
        vec(__mmask64 v) : base_type(v) {}
        vec(const vec<bit, 32>& l, const vec<bit, 32>& h)
            : base_type((l() & 0xffffffff) |
                        (__mmask64(h()) << 32)) {}
    };

#endif
#endif
}

// Local variables:
// mode: c++
// end:
#endif
