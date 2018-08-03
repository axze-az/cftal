//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_H__)
#define __CFTAL_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/arg.h>
#include <cftal/select.h>
#include <cftal/init_list.h>
#include <cftal/constants.h>
#include <cftal/expr.h>
#include <cftal/mem.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_mask.h>
#include <cftal/vec_op.h>
#include <cftal/vec_t_1.h>

#if defined (__ARM_NEON) || defined (__ARM_NEON__)
#include <cftal/arm/v2s32.h>
#include <cftal/arm/v2u32.h>
#include <cftal/arm/v2s64.h>
#include <cftal/arm/v2u64.h>

#include <cftal/arm/v2s32_inl.h>
#include <cftal/arm/v2u32_inl.h>
#include <cftal/arm/v2s64_inl.h>
#include <cftal/arm/v2u64_inl.h>
#endif

#if defined (__SSE2__)
// include 128 bit integer vector specializations
#include <cftal/x86/v4s32.h>
#include <cftal/x86/v4u32.h>
#include <cftal/x86/v2s64.h>
#include <cftal/x86/v2u64.h>
#include <cftal/x86/v8s16.h>
#include <cftal/x86/v8u16.h>
// include 128 bit integer vector specializations implementations
#include <cftal/x86/v4s32_inl.h>
#include <cftal/x86/v4u32_inl.h>
#include <cftal/x86/v2s64_inl.h>
#include <cftal/x86/v2u64_inl.h>
#include <cftal/x86/v8s16_inl.h>
#include <cftal/x86/v8u16_inl.h>
#endif
#if defined (__AVX2__)
// include 256 bit integer vector specializations
#include <cftal/x86/v8s32.h>
#include <cftal/x86/v8u32.h>
#include <cftal/x86/v4s64.h>
#include <cftal/x86/v4u64.h>
// include 256 bit integer vector specializations implementations
#include <cftal/x86/v8s32_inl.h>
#include <cftal/x86/v8u32_inl.h>
#include <cftal/x86/v4s64_inl.h>
#include <cftal/x86/v4u64_inl.h>
#endif

#include <cftal/vec_double_n.h>
#include <cftal/vec_float_n.h>
#include <cftal/vec_math_funcs.h>

#include <cftal/vec_cvt.h>
#include <cftal/vec_cast.h>
#include <cftal/vec_misc.h>

namespace cftal {
#if defined (__SSSE3__)
    namespace debug {
        template <typename _T>
        union ubytes {
            _T _t;
            uint8_t _b[sizeof(_T)];
            ubytes(const _T& t) : _t(t) {}
        };

        template <typename _T>
        ubytes<_T> bytes(const _T& t) {
            return ubytes<_T>(t);
        }

        template <typename _T>
        inline
        std::ostream& operator<<(std::ostream& s, const ubytes<_T>& b)
        {
            bool first=true;
            for (std::size_t i=0; i<sizeof(_T); ++i) {
                int32_t t=b._b[i];
                if (first==false) {
                    s << ' ';
                }
                s << t;
                first = false;
            }
            return s;
        }
    };

#if !defined (__AVX__)
    template <>
    class fixed_lookup_table<4, float, int32_t, 4> {
    private:
        __m128i _shuffle_bytes;
        static
        __m128i
        make_shuffle_bytes(vec<int32_t, 4> idx) {
            // vec<int32_t, 4> m= ((idx<<2) *0x01010101) + 0x03020100;
            // std::cout << debug::bytes(t) << std::endl;
            vec<int32_t, 4> idx4 = idx<<2;
            const __m128i u8u32 =
                _mm_setr_epi8( 0, 0, 0, 0,  4,  4,  4,  4,
                               8, 8, 8, 8, 12, 12, 12, 12);
            __m128i m=_mm_shuffle_epi8(idx4(), u8u32);
            // std::cout << debug::bytes(m) << std::endl;
            const __m128i offs=
                _mm_setr_epi8( 0, 1, 2, 3, 0, 1, 2, 3,
                               0, 1, 2, 3, 0, 1, 2, 3);
            m = _mm_add_epi8(m, offs);
            // std::cout << debug::bytes(m) << std::endl;
            return m;
        }
    public:
        fixed_lookup_table(vec<int32_t, 4> idx) :
            _shuffle_bytes(make_shuffle_bytes(idx)) {}
        vec<float, 4>
        from(const float (&tbl)[4]) const {
            vec<float, 4> r=mem<vec<float, 4> >::load(tbl, 4);
            __m128i ir = _mm_shuffle_epi8(_mm_castps_si128(r()),
                                          _shuffle_bytes);
            r = _mm_castsi128_ps(ir);
            return r;
        }
    };

    template <>
    class fixed_lookup_table<2, double, int32_t, 2> {
    private:
        __m128i _shuffle_bytes;
        static
        __m128i
        make_shuffle_bytes(vec<int32_t, 2> idx) {
            vec<int32_t, 4> idx4(idx, idx);
            idx4 <<= 3;
            const __m128i u8u32 =
                _mm_setr_epi8( 0, 0, 0, 0, 0, 0, 0, 0,
                               4, 4, 4, 4, 4, 4, 4, 4);
            __m128i m=_mm_shuffle_epi8(idx4(), u8u32);
            // std::cout << debug::bytes(m) << std::endl;
            const __m128i offs=
                _mm_setr_epi8( 0, 1, 2, 3, 4, 5, 6, 7,
                               0, 1, 2, 3, 4, 5, 6, 7);
            m = _mm_add_epi8(m, offs);
            // std::cout << debug::bytes(m) << std::endl;
            return m;
        }
    public:
        fixed_lookup_table(vec<int32_t, 2> idx) :
            _shuffle_bytes(make_shuffle_bytes(idx)) {}
        vec<double, 2>
        from(const double (&tbl)[2]) const {
            vec<double, 2> r=mem<vec<double, 2> >::load(tbl, 2);
            __m128i ir = _mm_shuffle_epi8(_mm_castpd_si128(r()),
                                          _shuffle_bytes);
            r = _mm_castsi128_pd(ir);
            return r;
        }
    };
#else
    template <>
    class fixed_lookup_table<4, float, int32_t, 4> {
    private:
        __m128i _perm_bytes;
        static
        __m128i
        make_perm_bytes(vec<int32_t, 4> idx) {
            return idx();
        }
    public:
        fixed_lookup_table(vec<int32_t, 4> idx) :
            _perm_bytes(make_perm_bytes(idx)) {}
        vec<float, 4>
        from(const float (&tbl)[4]) const {
            vec<float, 4> r=mem<vec<float, 4> >::load(tbl, 4);
            return _mm_permutevar_ps(r(), _perm_bytes);
        }
    };

    template <>
    class fixed_lookup_table<2, double, int32_t, 2> {
    private:
        __m128i _perm_bytes;
        static
        __m128i
        make_perm_bytes(vec<int32_t, 2> idx) {
            // the selector bit is bit 1 not bit 0
            vec<int32_t, 4> idx4(idx, idx);
            idx4 += idx4;
            __m128i t=x86::impl::vpmovzxdq::v(idx4());
            // std::cout << debug::bytes(t) << std::endl;
            return t;
        }
    public:
        fixed_lookup_table(vec<int32_t, 2> idx) :
            _perm_bytes(make_perm_bytes(idx)) {}
        vec<double, 2>
        from(const double (&tbl)[2]) const {
            vec<double, 2> r=mem<vec<double, 2> >::load(tbl, 2);
            return _mm_permutevar_pd(r(), _perm_bytes);
        }
    };
#endif
    
#if 0
    template <>
    class fixed_lookup_table<4, double, int32_t, 2> {
    private:
        struct data {
            uint32_t _idx0;
            uint32_t _idx1;
        } _dta;
        static
        data
        make_data(vec<int32_t, 2> idx) {
            uint32_t i0= low_half(idx)();
            uint32_t i1= high_half(idx)();
            return data{i0, i1};
        }
    public:
        fixed_lookup_table(vec<int32_t, 2> idx)
            : _dta(make_data(idx)) {}
        vec<double, 2>
        from(const double (&tbl)[4]) const {
            vec<double, 2> d=_mm_load_sd(tbl+_dta._idx0);
            d = _mm_loadh_pd(d(), tbl+_dta._idx1);
            return d;
        }
    };
#endif
#endif

#if defined (__AVX2__)
    template <>
    class fixed_lookup_table<4, float, int32_t, 8> {
    private:
        __m256i _perm_bytes;
        static
        __m256i
        make_perm_bytes(vec<int32_t, 8> idx) {
            return idx();
        }
    public:
        fixed_lookup_table(vec<int32_t, 8> idx) :
            _perm_bytes(make_perm_bytes(idx)) {}
        vec<float, 8>
        from(const float (&tbl)[4]) const {
            vec<float, 4> rh=mem<vec<float, 4> >::load(tbl, 4);
            __m256 r=_mm256_castps128_ps256(rh());
            r = _mm256_permutevar8x32_ps(r, _perm_bytes);
            return r;
        }
    };

    template <>
    class fixed_lookup_table<4, double, int32_t, 4> {
    private:
        __m256i _perm_bytes;
        static
        __m256i
        make_perm_bytes(vec<int32_t, 4> idx) {
            vec<int32_t, 4> i2=idx+idx;
            vec<int32_t, 8> t(i2, i2);
            t=permute<0, 0, 1, 1, 6, 6, 7, 7>(t);
            const __m256i offs=_mm256_setr_epi32(0, 1, 0, 1, 0, 1, 0, 1);
            __m256i r=_mm256_add_epi32(t(), offs);
            // std::cout << debug::bytes(r) << std::endl;
            return r;
        }
    public:
        fixed_lookup_table(vec<int32_t, 4> idx)
            : _perm_bytes(make_perm_bytes(idx)) {}
        vec<double, 4>
        from(const double (&tbl)[4]) const {
            vec<double, 4> r=mem<vec<double, 4> >::load(tbl, 4);
            __m256i ir=_mm256_permutevar8x32_epi32(_mm256_castpd_si256(r()),
                                                   _perm_bytes);
            r=_mm256_castsi256_pd(ir);
            return r;
        }
    };

    template <>
    class fixed_lookup_table<4, double, int32_t, 2>
        : private fixed_lookup_table<4, double, int32_t, 4> {
        using base_type = fixed_lookup_table<4, double, int32_t, 4>;
    public:
        fixed_lookup_table(vec<int32_t, 2> idx)
            : base_type(vec<int32_t, 4>(idx, idx)) {}
        vec<double, 2>
        from(const double (&tbl)[4]) const {
            return low_half(base_type::from(tbl));
        }
    };
        
    template <>
    class fixed_lookup_table<8, float, int32_t, 8> {
    private:
        __m256i _perm_bytes;
        static
        __m256i
        make_perm_bytes(vec<int32_t, 8> idx) {
            return idx();
        }
    public:
        fixed_lookup_table(vec<int32_t, 8> idx)
            : _perm_bytes(make_perm_bytes(idx)) {}
        vec<float, 8>
        from(const float (&tbl)[8]) const {
            vec<float, 8> r=mem<vec<float, 8> >::load(tbl, 8);
            r=_mm256_permutevar8x32_ps(r(), _perm_bytes);
            return r;
        }
    };

#endif
}

// Local variables:
// mode: c++
// end:
#endif
