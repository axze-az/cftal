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
#if !defined (__CFTAL_VXBF16_H__)
#define __CFTAL_VXBF16_H__ 1

#if 1
#include <cftal/config.h>
#include <cftal/vec_spec.h>
#include <cftal/cvt.h>
#include <cftal/vec_cvt_bf16.h>
#include <cftal/bf16_t.h>
#include <cftal/vec_lookup.h>

namespace cftal {

#if (V4F32_SPECIALIZED>0) || ((V2F32_SPECIALIZED>0) && (V2S32_SPECIALIZED>0))
#define V4BF16_SPECIALIZED 1
#endif
#if (V8F32_SPECIALIZED>0) || ((V4F32_SPECIALIZED>0) && (V4S32_SPECIALIZED>0))
#define V8BF16_SPECIALIZED 1
#endif
#if (V16F32_SPECIALIZED>0) || ((V8F32_SPECIALIZED>0) && (V8S32_SPECIALIZED>0))
#define V16BF16_SPECIALIZED 1
#endif
#define VBF16_USE_INT_CMP 0

    template <>
    class vec<bf16_t, 1> {
        vec<mf_bf16_t, 1> _v;
        struct cvt_from_rep_tag {};
        constexpr
        vec(const vec<mf_bf16_t, 1>& f, const cvt_from_rep_tag& )
            : _v(f) {}
    public:
        static
        constexpr
        vec
        cvt_from_rep(const vec<mf_bf16_t, 1>& r) {
            return vec(r, cvt_from_rep_tag());
        }
        using value_type = bf16_t;
        using mask_value_type =std::conditional_t<
            std::is_same_v<vec<float, 1>::mask_value_type, bit>,
            bit, bf16_t>;
        using mask_type = vec<mask_value_type, 1>;
        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;

        vec(const bf16_t& v) : _v(read_bits(v)) {}
        explicit
        vec(const float& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        explicit
        vec(const double& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        explicit
        vec(const int16_t& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        explicit
        vec(const int32_t& v) : _v(read_bits(static_cast<bf16_t>(v))) {}

        constexpr
        const vec<mf_bf16_t, 1>& operator()() const { return _v; }
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<bf16_t, 1> >, _L, _R>& r) : vec(eval(r)) {}
    };

    std::ostream&
    operator<<(std::ostream& s, const vec<bf16_t, 1>& v);

    template <size_t _N>
    class vec<bf16_t, _N> {
        vec<mf_bf16_t, _N> _v;
        struct cvt_from_rep_tag {};
        constexpr
        vec(const vec<mf_bf16_t, _N>& s, const cvt_from_rep_tag&) : _v(s) {}
    public:
        static
        constexpr
        vec
        cvt_from_rep(const vec<mf_bf16_t, _N>& r) {
            return vec(r, cvt_from_rep_tag());
        }

        using value_type = bf16_t;
        using half_type = vec<bf16_t, _N/2>;
        using mask_value_type =std::conditional_t<
            std::is_same_v<typename vec<float, _N>::mask_value_type, bit>,
            bit, bf16_t>;
        using mask_type = vec<mask_value_type, _N>;
        vec() = default;
        vec(const vec& r) = default;

        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;

        constexpr
        vec(const bf16_t& v) : _v(read_bits(v)) {}
        explicit
        vec(const float& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        explicit
        vec(const double& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        explicit
        vec(const int16_t& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        explicit
        vec(const int32_t& v) : _v(read_bits(static_cast<bf16_t>(v))) {}
        vec(const half_type& lh, const half_type& hh) :
            _v(lh(), hh()) {}
        vec(std::initializer_list<bf16_t> l)
            : vec(init_list<bf16_t>(l.begin(), l.end())) {}
        vec(init_list<bf16_t> l) :_v(
            init_list<mf_bf16_t>(
                reinterpret_cast<const mf_bf16_t*>(l.begin()),
                reinterpret_cast<const mf_bf16_t*>(l.end()))) {
        }
        half_type lh() const {
            return half_type::cvt_from_rep(low_half(_v));
        }
        half_type hh() const {
            return half_type::cvt_from_rep(high_half(_v));
        }

        const vec<mf_bf16_t, _N>& operator()()  const {
            return _v;
        }

        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<bf16_t, _N>>, _L, _R>& r) : vec(eval(r)) {}
    };

    template <>
    struct mem< vec<bf16_t, 1> > {
        static
        vec<bf16_t, 1> load(const bf16_t* p, ssize_t n=1) {
            using v_t= vec<mf_bf16_t, 1>;
            v_t r(mem<v_t>::load(reinterpret_cast<const mf_bf16_t*>(p), n));
            return vec<bf16_t, 1>::cvt_from_rep(r);        }
        static
        void store(bf16_t* p, const vec<bf16_t, 1>& v, ssize_t n=1) {
            using v_t = vec<mf_bf16_t, 1>;
            mem<v_t>::store(reinterpret_cast<mf_bf16_t*>(p), v(), n);
        }
    };

    template <size_t _N>
    struct mem< vec<bf16_t, _N> > {
        static
        vec<bf16_t, _N> load(const bf16_t* p, ssize_t n=_N) {
            using v_t= vec<mf_bf16_t, _N>;
            v_t r(mem<v_t>::load(reinterpret_cast<const mf_bf16_t*>(p), n));
            return vec<bf16_t, _N>::cvt_from_rep(r);
        }
        static
        void store(bf16_t* p, const vec<bf16_t, _N>& v, ssize_t n=_N) {
            using v_t = vec<mf_bf16_t, _N>;
            mem<v_t>::store(reinterpret_cast<mf_bf16_t*>(p), v(), n);
        }
    };

    template <size_t _N>
    struct is_vec_specialized<vec<bf16_t, _N> >
        : public is_vec_specialized<vec<mf_bf16_t, _N> > {
    };

    namespace impl {

        template <size_t _N>
        const vec<bit, _N>&
        cvt_f32_msk_to_bf16_msk(const vec<bit, _N>& m) {
            return m;
        }

        template <size_t _N>
        std::enable_if_t<
            std::is_same_v<
                vec<bf16_t, _N>,
                typename vec<bf16_t, _N>::mask_type>,
            vec<bf16_t, _N> >
        cvt_f32_msk_to_bf16_msk(const vec<f32_t, _N>& m) {
            const vec<mf_bf16_t, 2*_N> mv=as<const vec<mf_bf16_t, 2*_N> >(m);
            auto oe=odd_elements(mv);
            return vec<bf16_t, _N>::cvt_from_rep(oe);
        }

#if defined (__SSE2__)
        inline
        vec<bf16_t, 4>
        cvt_f32_msk_to_bf16_msk(const vec<f32_t, 4>& m) {
            __m128i mi=_mm_castps_si128(m());
            __m128i ri=_mm_packs_epi32(mi, mi);
            vec<mf_bf16_t, 8> r(ri);
            return vec<bf16_t, 4>::cvt_from_rep(low_half(r));
        }

        inline
        vec<bf16_t, 8>
        cvt_f32_msk_to_bf16_msk(const vec<f32_t, 8>& m) {
            __m128i mhi=_mm_castps_si128(high_half(m)());
            __m128i mli=_mm_castps_si128(low_half(m)());
            __m128i ri=_mm_packs_epi32(mli, mhi);
            vec<mf_bf16_t, 8> r(ri);
            return vec<bf16_t, 8>::cvt_from_rep(r);
        }

#if defined (__AVX2__)
        inline
        vec<bf16_t, 16>
        cvt_f32_msk_to_bf16_msk(const vec<f32_t, 16>& m) {
            __m256i mhi=_mm256_castps_si256(high_half(m)());
            __m256i mli=_mm256_castps_si256(low_half(m)());
            __m256i ri=_mm256_packs_epi32(mli, mhi);
            ri=x86::perm_v4u64<0, 2, 1, 3>(ri);
            vec<mf_bf16_t, 16> r(ri);
            return vec<bf16_t, 16>::cvt_from_rep(r);
        }
#endif

#if defined (__SSSE3__)
        template <>
        class fixed_vec_lookup_table<8, bf16_t, int16_t, 8> {
        private:
            __m128i _msk;
        protected:
            __m128i msk() const {
                return _msk;
            }
            static
            __m128i setup_msk(const vec<int16_t, 8>& i) {
                // multiply by 2
                __m128i m=x86::vpsllw_const<1>::v(i());
                // shuffle it to lo/hi  bytes
                const __m128i& p=x86::const_v16u8< 0,  0,  2,  2,
                                                   4,  4,  6,  6,
                                                   8,  8, 10, 10,
                                                  12, 12, 14, 14>::iv();
                m=x86::vpshufb::v(m, p);
                // add one for the high bytes
                const __m128i& o=x86::const_v16u8< 0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1>::iv();
                return _mm_add_epi8(m, o);
            }

        public:
            fixed_vec_lookup_table(const vec<int16_t, 8>& idx)
                : _msk(setup_msk(idx)) {}
            vec<bf16_t, 8>
            fromp(const bf16_t* tbl) const {
                vec<bf16_t, 8> tf=mem<vec<bf16_t, 8>>::load(tbl);
                vec<mf_bf16_t, 8> t0=tf();
                vec<mf_bf16_t, 8> ri=x86::vpshufb::v(t0(), msk());
                return vec<bf16_t, 8>::cvt_from_rep(ri);
            }
        };

        template <>
        class fixed_vec_lookup_table<16, bf16_t, int16_t, 8> :
            private fixed_vec_lookup_table<8, bf16_t, int16_t, 8> {
            using base_type=fixed_vec_lookup_table<8, bf16_t, int16_t, 8>;
        private:
            __m128i _idx_gt_7;
        public:
            fixed_vec_lookup_table(const vec<int16_t, 8>& idx)
                : base_type(idx),
                  _idx_gt_7(_mm_cmpgt_epi16(idx(), _mm_set1_epi16(7))) {
            }
            vec<bf16_t, 8>
            fromp(const bf16_t* tbl) const {
                vec<bf16_t, 16> tf=mem<vec<bf16_t, 16>>::load(tbl);
                vec<mf_bf16_t, 16> ti=tf();
                vec<mf_bf16_t, 8> t0=low_half(ti), t1=high_half(ti);
                vec<mf_bf16_t, 8> ril=x86::vpshufb::v(t0(), msk());
                vec<mf_bf16_t, 8> rih=x86::vpshufb::v(t1(), msk());
                __m128i ri=x86::select_u16(_idx_gt_7, rih(), ril());
                return vec<bf16_t, 8>::cvt_from_rep(ri);
            }
        };

        template <>
        class fixed_vec_lookup_table<32, bf16_t, int16_t, 8> :
            private fixed_vec_lookup_table<8, bf16_t, int16_t, 8> {
            using base_type=fixed_vec_lookup_table<8, bf16_t, int16_t, 8>;
        private:
            __m128i _idx_gt_7;
            __m128i _idx_gt_15;
            __m128i _idx_gt_23;
        public:
            fixed_vec_lookup_table(const vec<int16_t, 8>& idx)
                : base_type(idx),
                  _idx_gt_7(_mm_cmpgt_epi16(idx(), _mm_set1_epi16(7))),
                  _idx_gt_15(_mm_cmpgt_epi16(idx(), _mm_set1_epi16(15))),
                  _idx_gt_23(_mm_cmpgt_epi16(idx(), _mm_set1_epi16(23))) {
            }
            vec<bf16_t, 8>
            fromp(const bf16_t* tbl) const {
                vec<bf16_t, 32> tf=mem<vec<bf16_t, 32> >::load(tbl);
                vec<mf_bf16_t, 32> ti=tf();
                vec<mf_bf16_t, 16> t01=low_half(ti), t23=high_half(ti);
                vec<mf_bf16_t, 8> t0=low_half(t01), t1=high_half(t01);
                vec<mf_bf16_t, 8> t2=low_half(t23), t3=high_half(t23);
                vec<mf_bf16_t, 8> r0=x86::vpshufb::v(t0(), msk());
                vec<mf_bf16_t, 8> r1=x86::vpshufb::v(t1(), msk());
                vec<mf_bf16_t, 8> r2=x86::vpshufb::v(t2(), msk());
                vec<mf_bf16_t, 8> r3=x86::vpshufb::v(t3(), msk());
                __m128i r01=x86::select_u16(_idx_gt_7, r1(), r0());
                __m128i r23=x86::select_u16(_idx_gt_23, r3(), r2());
                __m128i ri=x86::select_u16(_idx_gt_15, r23, r01);
                return vec<bf16_t, 8>::cvt_from_rep(ri);
            }
        };

#endif
#if defined (__AVX2__)
        template <>
        class fixed_vec_lookup_table<8, bf16_t, int16_t, 16> {
        private:
            __m256i _msk;
        protected:
            __m256i msk() const {
                return _msk;
            }
            static
            __m256i setup_msk(const vec<int16_t, 16>& i) {
                // multiply by 2
                __m256i it=i();
                __m256i m=x86::vpsllw_const<1>::v(it);
                // shuffle it to lo/hi  bytes
                const __m256i& p=x86::const_v32u8< 0,  0,  2,  2,
                                                   4,  4,  6,  6,
                                                   8,  8, 10, 10,
                                                  12, 12, 14, 14,
                                                   0,  0,  2,  2,
                                                   4,  4,  6,  6,
                                                   8,  8, 10, 10,
                                                  12, 12, 14, 14>::iv();
                m=x86::vpshufb::v(m, p);
                // add one for the high bytes
                const __m256i& o=x86::const_v32u8< 0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1,
                                                   0,  1,  0,  1>::iv();
                return _mm256_add_epi8(m, o);
            }

        public:
            fixed_vec_lookup_table(const vec<int16_t, 16>& idx)
                : _msk(setup_msk(idx)) {}
            vec<bf16_t, 16>
            fromp(const bf16_t* tbl) const {
                vec<bf16_t, 8> tf=mem<vec<bf16_t, 8>>::load(tbl);
                vec<mf_bf16_t, 8> ti=tf();
                vec<mf_bf16_t, 16> t0(ti, ti);
                vec<mf_bf16_t, 16> ri=x86::vpshufb::v(t0(), msk());
                return vec<bf16_t, 16>::cvt_from_rep(ri);
            }
        };

        template <>
        class fixed_vec_lookup_table<16, bf16_t, int16_t, 16> :
            private fixed_vec_lookup_table<8, bf16_t, int16_t, 16> {
            using base_type=fixed_vec_lookup_table<8, bf16_t, int16_t, 16>;
        private:
            __m256i _idx_gt_7;
        public:
            fixed_vec_lookup_table(const vec<int16_t, 16>& idx)
                : base_type(idx),
                  _idx_gt_7(_mm256_cmpgt_epi16(idx(), _mm256_set1_epi16(7))) {
            }
            vec<bf16_t, 16>
            fromp(const bf16_t* tbl) const {
                vec<bf16_t, 16> tf=mem<vec<bf16_t, 16> >::load(tbl);
                vec<mf_bf16_t, 16> ti=tf();
                vec<mf_bf16_t, 8> t0l=low_half(ti), t1l=high_half(ti);
                vec<mf_bf16_t, 16> t0(t0l, t0l);
                vec<mf_bf16_t, 16> t1(t1l, t1l);
                vec<mf_bf16_t, 16> ril=x86::vpshufb::v(t0(), msk());
                vec<mf_bf16_t, 16> rih=x86::vpshufb::v(t1(), msk());
                __m256i ri=x86::select_u16(_idx_gt_7, rih(), ril());
                return vec<bf16_t, 16>::cvt_from_rep(ri);
            }
        };

        template <>
        class fixed_vec_lookup_table<32, bf16_t, int16_t, 16> :
            private fixed_vec_lookup_table<8, bf16_t, int16_t, 16> {
            using base_type=fixed_vec_lookup_table<8, bf16_t, int16_t, 16>;
        private:
            __m256i _idx_gt_7;
            __m256i _idx_gt_15;
            __m256i _idx_gt_23;
        public:
            fixed_vec_lookup_table(const vec<int16_t, 16>& idx)
                : base_type(idx),
                  _idx_gt_7(_mm256_cmpgt_epi16(idx(), _mm256_set1_epi16(7))),
                  _idx_gt_15(_mm256_cmpgt_epi16(idx(), _mm256_set1_epi16(15))),
                  _idx_gt_23(_mm256_cmpgt_epi16(idx(), _mm256_set1_epi16(23))) {
            }
            vec<bf16_t, 16>
            fromp(const bf16_t* tbl) const {
                vec<bf16_t, 32> tf=mem<vec<bf16_t, 32> >::load(tbl);
                vec<mf_bf16_t, 32> ti=tf();
                vec<mf_bf16_t, 16> t01=low_half(ti), t23=high_half(ti);
                vec<mf_bf16_t, 8> t0l=low_half(t01), t1l=high_half(t01);
                vec<mf_bf16_t, 8> t2l=low_half(t23), t3l=high_half(t23);
                vec<mf_bf16_t, 16> t0(t0l, t0l), t1(t1l, t1l);
                vec<mf_bf16_t, 16> t2(t2l, t2l), t3(t3l, t3l);
                vec<mf_bf16_t, 16> r0=x86::vpshufb::v(t0(), msk());
                vec<mf_bf16_t, 16> r1=x86::vpshufb::v(t1(), msk());
                vec<mf_bf16_t, 16> r2=x86::vpshufb::v(t2(), msk());
                vec<mf_bf16_t, 16> r3=x86::vpshufb::v(t3(), msk());
                __m256i r01=x86::select_u16(_idx_gt_7, r1(), r0());
                __m256i r23=x86::select_u16(_idx_gt_23, r3(), r2());
                __m256i ri=x86::select_u16(_idx_gt_15, r23, r01);
                return vec<bf16_t, 16>::cvt_from_rep(ri);
            }
        };

#endif
#endif // __SSE2__
    }

    template <size_t _N>
    vec<bf16_t, _N/2>
    low_half(const vec<bf16_t, _N>& v);

    template <size_t _N>
    vec<bf16_t, _N/2>
    high_half(const vec<bf16_t, _N>& v);

    template <size_t _N>
    struct arg< vec<bf16_t, _N> > {
        using type = std::conditional_t<
            std::is_same_v<vec<mf_bf16_t, _N>, arg_t<vec<mf_bf16_t, _N> > >,
            vec<bf16_t, _N>,
            const vec<bf16_t, _N>& >;
    };

    template <>
    struct arg< vec<bf16_t, 1> > {
        using type = vec<bf16_t, 1>;
    };

    template <size_t _I, size_t _N>
    bf16_t
    extract(const vec<bf16_t, _N>& v);

    template <size_t _N>
    bf16_t
    extract(const vec<bf16_t, _N>& v, size_t i);

    template <size_t _I, size_t _N>
    void
    insert(vec<bf16_t, _N>& v, const bf16_t& vi);

    template <size_t _N>
    void
    insert(vec<bf16_t, _N>& v, const bf16_t& vi, size_t i);

    template <size_t _I>
    bf16_t
    extract(const vec<bf16_t, 1>& v);

    bf16_t
    extract(const vec<bf16_t, 1>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<bf16_t, 1>& v, const bf16_t& vi);

    void
    insert(vec<bf16_t, 1>& v, const bf16_t& vi, size_t i);

    // abs
    template <size_t _N>
    vec<bf16_t, _N>
    abs(const vec<bf16_t, _N>& a);

    template <size_t _N>
    typename vec<bf16_t, _N>::mask_type
    iszero(const vec<bf16_t, _N>& a);

    // nan
    template <size_t _N>
    typename vec<bf16_t, _N>::mask_type
    isnan(const vec<bf16_t, _N>& a);

    // inf
    template <size_t _N>
    typename vec<bf16_t, _N>::mask_type
    isinf(const vec<bf16_t, _N>& a);

    // isfinite
    template <size_t _N>
    typename vec<bf16_t, _N>::mask_type
    isfinite(const vec<bf16_t, _N>& a);

    // copysign
    template <size_t _N>
    vec<bf16_t, _N>
    copysign(const vec<bf16_t, _N>& a, const vec<bf16_t, _N>& b);

    template <size_t _N>
    vec<bf16_t, _N>
    copysign(const bf16_t& a, const vec<bf16_t, _N>& b);

    template <size_t _N>
    vec<bf16_t, _N>
    copysign(const vec<bf16_t, _N>& a, const bf16_t& b);

    // mulsign
    template <size_t _N>
    vec<bf16_t, _N>
    mulsign(const vec<bf16_t, _N>& a, const vec<bf16_t, _N>& b);

    // signbit
    template <size_t _N>
    typename vec<bf16_t, _N>::mask_type
    signbit(const vec<bf16_t, _N>& a);

    // max
    vec<bf16_t, 1>
    max(const vec<bf16_t, 1>& a, const vec<bf16_t, 1>& b);

    // max
    template <size_t _N>
    vec<bf16_t, _N>
    max(const vec<bf16_t, _N>& a, const vec<bf16_t, _N>& b);

    // min
    vec<bf16_t, 1>
    min(const vec<bf16_t, 1>& a, const vec<bf16_t, 1>& b);

    // min
    template <size_t _N>
    vec<bf16_t, _N>
    min(const vec<bf16_t, _N>& a, const vec<bf16_t, _N>& b);

    // select
    vec<bf16_t, 1>
    select(const vec<bf16_t, 1>::mask_type& m ,
           const vec<bf16_t, 1>& on_true,
           const vec<bf16_t, 1>& on_false);

    // select
    template <size_t _N>
    vec<bf16_t, _N>
    select(const typename vec<bf16_t, _N>::mask_type& m ,
           const vec<bf16_t, _N>& on_true,
           const vec<bf16_t, _N>& on_false);

    // select value or zero
    vec<bf16_t, 1>
    select_val_or_zero(const vec<bf16_t, 1>::mask_type& m ,
                       const vec<bf16_t, 1>& on_true);

    // select value or zero
    template <size_t _N>
    vec<bf16_t, _N>
    select_val_or_zero(const typename vec<bf16_t, _N>::mask_type& m ,
                       const vec<bf16_t, _N>& on_true);


    // select zero or value
    vec<bf16_t, 1>
    select_zero_or_val(const vec<bf16_t, 1>::mask_type& m ,
                       const vec<bf16_t, 1>& on_false);

    // select zero or value
    template <size_t _N>
    vec<bf16_t, _N>
    select_zero_or_val(const typename vec<bf16_t, _N>::mask_type& m ,
                       const vec<bf16_t, _N>& on_false);

#if (__AVX512VL__==0) || (__CFTAL_CFG_ENABLE_AVX512__==0)
    bool
    all_of(const vec<bf16_t, 1>::mask_type& m);

    template <std::size_t _N>
    bool
    all_of(const typename vec<bf16_t, _N>::mask_type& m);

    bool
    any_of(const vec<bf16_t, 1>::mask_type& m);

    template <std::size_t _N>
    bool
    any_of(const typename vec<bf16_t, _N>::mask_type& m);

    bool
    none_of(const vec<bf16_t, 1>::mask_type& m);

    template <std::size_t _N>
    bool
    none_of(const typename vec<bf16_t, _N>::mask_type& m);
#endif

    namespace impl {

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_not_nan_abs(vec<int16_t, _N> v) {
            return v < (exp_f32_msk::v.s16h()+1);
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_not_zero_abs(vec<int16_t, _N> v) {
            return v > int16_t(0);
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_zero_abs(vec<int16_t, _N> v) {
            return v == int16_t(0);
        }

        template <size_t _N>
        vec<int16_t, _N>
        bf16_abs(vec<int16_t, _N> v) {
            return v & not_sign_f32_msk::v.s16h();
        }

        template <size_t _N>
        vec<int16_t, _N>
        bf16_sgn(vec<int16_t, _N> v) {
            return v & sign_f32_msk::v.s16h();
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_eq(vec<int16_t, _N> a, vec<int16_t, _N> b) {
            using vi_t=vec<int16_t, _N>;
            using vmi_t=typename vi_t::mask_type;
            vi_t aa = bf16_abs(a), ab= bf16_abs(b);
            vmi_t r=
                bf16_not_nan_abs(aa) &
                bf16_not_nan_abs(ab) &
                ((a==b) | bf16_zero_abs(vi_t(aa|ab)));
            return r;
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_le(vec<int16_t, _N> a, vec<int16_t, _N> b) {
            using vi_t=vec<int16_t, _N>;
            using vmi_t=typename vi_t::mask_type;
            vi_t aa = bf16_abs(a), ab= bf16_abs(b);
            vi_t sa = bf16_sgn(a), sb= bf16_sgn(b);

            vmi_t a_neg= sa < int16_t(0);
            vmi_t eq_sgn= sa == sb;
            vmi_t b_le_a= b <= a;
            vmi_t a_le_b= a <= b;
            vmi_t a_not_nan= bf16_not_nan_abs(aa);
            vmi_t b_not_nan= bf16_not_nan_abs(ab);
            vmi_t ab_zero=bf16_zero_abs(vi_t(aa|ab));
            // result for same signs:
            vmi_t r_eq_sgn= select(a_neg, b_le_a, a_le_b);
            // result for opposite signs:
            vmi_t r_ne_sgn= a_neg | ab_zero;
            // normal result
            vmi_t r_sgn = select(eq_sgn, r_eq_sgn, r_ne_sgn);
            // masked with not nan:
            vmi_t r= a_not_nan & b_not_nan & r_sgn;
            return r;
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_lt(vec<int16_t, _N> a, vec<int16_t, _N> b) {
            using vi_t=vec<int16_t, _N>;
            using vmi_t=typename vi_t::mask_type;
            vi_t aa = bf16_abs(a), ab= bf16_abs(b);
            vi_t sa = bf16_sgn(a), sb= bf16_sgn(b);

            vmi_t a_neg= sa < int16_t(0);
            vmi_t eq_sgn= sa == sb;
            vmi_t b_lt_a= b < a;
            vmi_t a_lt_b= a < b;
            vmi_t a_not_nan= bf16_not_nan_abs(aa);
            vmi_t b_not_nan= bf16_not_nan_abs(ab);
            vmi_t ab_not_zero=bf16_not_zero_abs(vi_t(aa|ab));
            // result for same signs:
            vmi_t r_eq_sgn= select(a_neg, b_lt_a, a_lt_b);
            // result for opposite signs:
            vmi_t r_ne_sgn= a_neg & ab_not_zero;
            // normal result
            vmi_t r_sgn = select(eq_sgn, r_eq_sgn, r_ne_sgn);
            // masked with not nan:
            vmi_t r= a_not_nan & b_not_nan & r_sgn;
            return r;
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_ge(vec<int16_t, _N> a, vec<int16_t, _N> b) {
            return bf16_le(b, a);
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_gt(vec<int16_t, _N> a, vec<int16_t, _N> b) {
            return bf16_lt(b, a);
        }

        template <size_t _N>
        typename vec<int16_t, _N>::mask_type
        bf16_ne(vec<int16_t, _N> a, vec<int16_t, _N> b) {
            using vi_t=vec<int16_t, _N>;
            using vmi_t=typename vi_t::mask_type;
            vi_t aa = bf16_abs(a), ab= bf16_abs(b);
            vmi_t r=
                bf16_not_nan_abs(aa) &
                bf16_not_nan_abs(ab) &
                ((a!=b) & bf16_not_zero_abs(vi_t(aa|ab)));
            return r;
        }

        template <size_t _N>
        typename vec<bf16_t, _N>::mask_type
        bf16_lt(vec<bf16_t, _N> a, vec<bf16_t, _N> b) {
            using vmi_t=typename vec<bf16_t, _N>::mask_type;
            return vmi_t::cvt_from_rep(bf16_lt(a(), b()));
        }

        template <size_t _N>
        typename vec<bf16_t, _N>::mask_type
        bf16_le(vec<bf16_t, _N> a, vec<bf16_t, _N> b) {
            using vmi_t=typename vec<bf16_t, _N>::mask_type;
            return vmi_t::cvt_from_rep(bf16_le(a(), b()));
        }

        template <size_t _N>
        typename vec<bf16_t, _N>::mask_type
        bf16_eq(vec<bf16_t, _N> a, vec<bf16_t, _N> b) {
            using vmi_t=typename vec<bf16_t, _N>::mask_type;
            return vmi_t::cvt_from_rep(bf16_eq(a(), b()));
        }

        template <size_t _N>
        typename vec<bf16_t, _N>::mask_type
        bf16_ne(vec<bf16_t, _N> a, vec<bf16_t, _N> b) {
            using vmi_t=typename vec<bf16_t, _N>::mask_type;
            return vmi_t::cvt_from_rep(bf16_ne(a(), b()));
        }

        template <size_t _N>
        typename vec<bf16_t, _N>::mask_type
        bf16_ge(vec<bf16_t, _N> a, vec<bf16_t, _N> b) {
            using vmi_t=typename vec<bf16_t, _N>::mask_type;
            return vmi_t::cvt_from_rep(bf16_ge(a(), b()));
        }

        template <size_t _N>
        typename vec<bf16_t, _N>::mask_type
        bf16_gt(vec<bf16_t, _N> a, vec<bf16_t, _N> b) {
            using vmi_t=typename vec<bf16_t, _N>::mask_type;
            return vmi_t::cvt_from_rep(bf16_gt(a(), b()));
        }


    }


    namespace op {

        template <>
        struct lt<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_lt(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) < cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <size_t _N>
        struct lt<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_lt(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) < cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <>
        struct le<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_le(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) <= cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <size_t _N>
        struct le<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_le(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) <= cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <>
        struct eq<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_eq(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) == cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <size_t _N>
        struct eq<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_eq(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) == cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <>
        struct ne<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_ne(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) != cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <size_t _N>
        struct ne<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_ne(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) != cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <>
        struct ge<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_ge(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) >= cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <size_t _N>
        struct ge<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_ge(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) >= cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <>
        struct gt<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_gt(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) > cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <size_t _N>
        struct gt<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
#if VBF16_USE_INT_CMP> 0
                return impl::bf16_gt(a, b);
#else
                return impl::cvt_f32_msk_to_bf16_msk(
                    cvt_bf16_to_f32(a()) > cvt_bf16_to_f32(b()));
#endif
            }
        };

        template <>
        struct plus<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <size_t _N>
        struct plus<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a) {
                vec<mf_bf16_t, 1> t=a();
                t ^= sign_f32_msk::v.s16h();
                return full_type::cvt_from_rep(t);
            }
        };

        template <size_t _N>
        struct neg<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a) {
                vec<mf_bf16_t, _N> t=a();
                t ^= sign_f32_msk::v.s16h();
                return full_type::cvt_from_rep(t);
            }
        };

        template <>
        struct add<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=add<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct add<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=add<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct sub<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=sub<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct sub<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=sub<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct mul<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=mul<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct mul<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=mul<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct div<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=div<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct div<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fr=div<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct fma<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fc=cvt_bf16_to_f32(uc);
                auto fr=fma<vec<f32_t, 1>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct fma<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fc=cvt_bf16_to_f32(uc);
                auto fr=fma<vec<f32_t, _N>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct fms<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fc=cvt_bf16_to_f32(uc);
                auto fr=fms<vec<f32_t, 1>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct fms<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fc=cvt_bf16_to_f32(uc);
                auto fr=fms<vec<f32_t, _N>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct fnma<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fc=cvt_bf16_to_f32(uc);
                auto fr=fnma<vec<f32_t, 1>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <size_t _N>
        struct fnma<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_bf16_to_f32(ua), fb=cvt_bf16_to_f32(ub);
                auto fc=cvt_bf16_to_f32(uc);
                auto fr=fnma<vec<f32_t, _N>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_bf16(fr));
            }
        };

        template <>
        struct bit_or<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_bf16_t, 1> r= ua | ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_or<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_bf16_t, _N> r= ua | ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <>
        struct bit_and<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_bf16_t, 1> r= ua & ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_and<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_bf16_t, _N> r= ua & ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <>
        struct bit_xor<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_bf16_t, 1> r= ua ^ ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_xor<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_bf16_t, _N> r= ua ^ ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <>
        struct bit_not<vec<bf16_t, 1>> {
            using full_type = vec<bf16_t, 1>;
            static
            full_type
            v(const full_type& a) {
                auto ua=a();
                vec<mf_bf16_t, 1> r= ~ua;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_not<vec<bf16_t, _N>> {
            using full_type = vec<bf16_t, _N>;
            static
            full_type
            v(const full_type& a) {
                auto ua=a();
                vec<mf_bf16_t, _N> r= ~ua;
                return full_type::cvt_from_rep(r);
            }
        };
    } // end namespace op

#if defined (__AVX2__)
    namespace impl {
#if 0
        template <>
        class variable_vec_lookup_table<bf16_t, int16_t, 4> {
            vec<int16_t, 4> _idx;
        public:
            variable_vec_lookup_table(const vec<int16_t, 4>& idx) : _idx(idx) {}
            vec<bf16_t, 4>
            fromp(const bf16_t* tbl) const {
                uint64_t i64=as<uint64_t>(_idx);
                __m128i i=_mm_cvtsi64_si128(i64);
                const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
                // TODO: add a method gathering only 4 values to
                // vgatherwph<__m128i, __m128i>
                __m128i r0=x86::vgatherwph<__m128i, __m128i>::v<2>(p, i);
                uint64_t r1=_mm_cvtsi128_si64(r0);
                vec<mf_bf16_t, 4> r2=as<vec<mf_bf16_t, 4> >(r1);
                return vec<bf16_t, 4>::cvt_from_rep(r2);
            }
        };
#endif
        template <>
        class variable_vec_lookup_table<bf16_t, int16_t, 8> {
            vec<int16_t, 8> _idx;
        public:
            variable_vec_lookup_table(const vec<int16_t, 8>& idx)
                : _idx(idx) {}
            vec<bf16_t, 8>
            fromp(const bf16_t* tbl) const {
                const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
                __m128i r=x86::vgatherwph<__m128i, __m128i>::v<2>(p, _idx());
                return vec<bf16_t, 8>::cvt_from_rep(r);
            }
        };

        template <>
        class variable_vec_lookup_table<bf16_t, int16_t, 16> {
            vec<int16_t, 16> _idx;
        public:
            variable_vec_lookup_table(const vec<int16_t, 16>& idx)
                : _idx(idx) {}
            vec<bf16_t, 16>
            fromp(const bf16_t* tbl) const {
                const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
                __m256i r=x86::vgatherwph<__m256i, __m256i>::v<2>(p, _idx());
                return vec<bf16_t, 16>::cvt_from_rep(r);
            }
        };

        template <>
        class variable_vec_lookup_table<bf16_t, int32_t, 4> {
            vec<int32_t, 4> _idx;
        public:
            variable_vec_lookup_table(const vec<int32_t, 4>& idx)
                : _idx(idx) {}
            vec<bf16_t, 4>
            fromp(const bf16_t* tbl) const {
                const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
                vec<mf_bf16_t, 8> rlh=
                    x86::vgatherdph<__m128i, __m128i>::v<2>(p, _idx());
                vec<mf_bf16_t, 4> r(low_half(rlh));
                return vec<bf16_t, 4>::cvt_from_rep(r);
            }
        };

        template <>
        class variable_vec_lookup_table<bf16_t, int32_t, 8> {
            vec<int32_t, 8> _idx;
        public:
            variable_vec_lookup_table(const vec<int32_t, 8>& idx)
                : _idx(idx) {}
            vec<bf16_t, 8>
            fromp(const bf16_t* tbl) const {
                const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
                __m128i r=x86::vgatherdph<__m128i, __m256i>::v<2>(p, _idx());
                return vec<bf16_t, 8>::cvt_from_rep(r);
            }
        };

    }
#endif
    namespace impl {
        template <size_t _N>
        struct cvt<vec<float, _N>, vec<bf16_t, _N> > {
            static
            vec<float, _N> v(const vec<bf16_t, _N>& s) {
                return cvt_bf16_to_f32(s());
            }
        };

        template <size_t _N>
        struct cvt<vec<bf16_t, _N>, vec<float, _N> > {
            static
            vec<bf16_t, _N> v(const vec<float, _N>& s) {
                auto t=cvt_f32_to_bf16(s);
                return vec<bf16_t, _N>::cvt_from_rep(t);
            }
        };

        template <>
        struct cvt<vec<float, 1>, vec<bf16_t, 1> > {
            static
            vec<float, 1> v(const vec<bf16_t, 1>& s) {
                return cvt_bf16_to_f32(s());
            }
        };

        template <>
        struct cvt<vec<bf16_t, 1>, vec<float, 1> > {
            static
            vec<bf16_t, 1> v(const vec<float, 1>& s) {
                auto t=cvt_f32_to_bf16(s);
                return vec<bf16_t, 1>::cvt_from_rep(t);
            }
        };

        template <>
        struct cvt<vec<int16_t, 1>, vec<bf16_t, 1> > {
            static
            vec<int16_t, 1>
            v(const vec<bf16_t, 1>& s) {
                bf16_t v=as<bf16_t>(s());
                int32_t r=float(v);
                return r;
            }
        };

        template <>
        struct cvt<vec<bf16_t, 1>, vec<int16_t, 1> > {
            static
            vec<bf16_t, 1>
            v(const vec<int16_t, 1>& s) {
                float f=s();
                bf16_t h=static_cast<bf16_t>(f);
                return vec<bf16_t, 1>(h);
            }
        };

        template<size_t _N>
        struct cvt<vec<int16_t, _N>, vec<bf16_t, _N> > {
            static
            vec<int16_t, _N>
            v(const vec<bf16_t, _N>& s) {
                auto s0=cvt<vec<float, _N>, vec<bf16_t, _N> >::v(s);
                auto s1=cvt<vec<int32_t, _N>, vec<float, _N> >::v(s0);
                auto s2=cvt<vec<int16_t, _N>, vec<int32_t, _N> >::v(s1);
                return s2;
            }
        };

        template<size_t _N>
        struct cvt<vec<bf16_t, _N>, vec<int16_t, _N> > {
            static
            vec<bf16_t, _N>
            v(const vec<int16_t, _N>& s) {
                auto s0=cvt<vec<int32_t, _N>, vec<int16_t, _N> >::v(s);
                auto s1=cvt<vec<float, _N>, vec<int32_t, _N> >::v(s0);
                auto s2=cvt<vec<bf16_t, _N>, vec<float, _N> >::v(s1);
                return s2;
            }
        };
    }

    // inlined vector math functions for vxbf16
    template <size_t _N>
    vec<bf16_t, _N>
    rint(const vec<bf16_t, _N>& x);

    template <size_t _N>
    vec<bf16_t, _N>
    floor(const vec<bf16_t, _N>& x);

    template <size_t _N>
    vec<bf16_t, _N>
    ceil(const vec<bf16_t, _N>& x);

    template <size_t _N>
    vec<bf16_t, _N>
    trunc(const vec<bf16_t, _N>& x);

    template <size_t _N>
    vec<bf16_t, _N>
    sqrt(const vec<bf16_t, _N>& x);

    template <size_t _N>
    bf16_t
    hsum(const vec<bf16_t, _N>& x);
}

inline
std::ostream&
cftal::
operator<<(std::ostream& s, const cftal::vec<bf16_t, 1>& v)
{
    auto t=v();
    s << as<bf16_t>(t);
    return s;
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N/2>
cftal::low_half(const vec<bf16_t, _N>& s)
{
    return s.lh();
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N/2>
cftal::high_half(const vec<bf16_t, _N>& s)
{
    return s.hh();
}

template <cftal::size_t _I, size_t _N>
inline
cftal::bf16_t
cftal::extract(const vec<bf16_t, _N>& v)
{
    mf_bf16_t ri=extract<_I>(v());
    return as<bf16_t>(ri);
}

template <cftal::size_t _N>
inline
cftal::bf16_t
cftal::extract(const vec<bf16_t, _N>& v, size_t i)
{
    mf_bf16_t ri=extract(v(), i);
    return as<bf16_t>(ri);
}

template <cftal::size_t _I, size_t _N>
inline
void
cftal::insert(vec<bf16_t, _N>& v, const bf16_t& vi)
{
    mf_bf16_t vii=read_bits(vi);
    vec<mf_bf16_t, _N> r=v();
    insert<_I>(r, vii);
    v = vec<bf16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _N>
inline
void
cftal::insert(vec<bf16_t, _N>& v, const bf16_t& vi, size_t i)
{
    mf_bf16_t vii=read_bits(vi);
    vec<mf_bf16_t, _N> r=v();
    insert(r, vii, i);
    v = vec<bf16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _I>
inline
cftal::bf16_t
cftal::extract(const vec<bf16_t, 1>& v)
{
    mf_bf16_t ri=v()();
    return as<bf16_t>(ri);
}

inline
cftal::bf16_t
cftal::extract(const vec<bf16_t, 1>& v, size_t i)
{
    mf_bf16_t ri=v()();
    return as<bf16_t>(ri);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<bf16_t, 1>& v, const bf16_t& vi)
{
    mf_bf16_t vii=read_bits(vi);
    v= vec<bf16_t, 1>::cvt_from_rep(vii);
}

inline
void
cftal::insert(vec<bf16_t, 1>& v, const bf16_t& vi, size_t i)
{
    static_cast<void>(i);
    mf_bf16_t vii=read_bits(vi);
    v= vec<bf16_t, 1>::cvt_from_rep(vii);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::abs(const vec<bf16_t, _N>& a)
{
    vec<mf_bf16_t, _N> t= a() & not_sign_f32_msk::v.s16h();
    return vec<bf16_t, _N>::cvt_from_rep(t);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::bf16_t, _N>::mask_type
cftal::iszero(const vec<bf16_t, _N>& a)
{
#if 1
    // to allow common subexpression elimination with isnan/isinf
    vec<mf_bf16_t, _N> t= a() & not_sign_f32_msk::v.s16h();
#else
    vec<mf_bf16_t, _N> t= a();
    t += t;
#endif
    auto v_is_zero = t == mf_bf16_t(0);
    using m_t = typename vec<bf16_t, _N>::mask_type;
    // return m_t::cvt_from_rep(v_is_zero);
    return as<m_t>(v_is_zero);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::bf16_t, _N>::mask_type
cftal::isnan(const vec<bf16_t, _N>& a)
{
    vec<mf_bf16_t, _N> aa= a() & not_sign_f32_msk::v.s16h();
    auto v_is_nan = aa > exp_f32_msk::v.s16h();
    using m_t = typename vec<bf16_t, _N>::mask_type;
    // return m_t::cvt_from_rep(v_is_nan);
    return as<m_t>(v_is_nan);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::bf16_t, _N>::mask_type
cftal::isinf(const vec<bf16_t, _N>& a)
{
    vec<mf_bf16_t, _N> aa= a() & not_sign_f32_msk::v.s16h();
    auto v_is_inf = aa == exp_f32_msk::v.s16h();
    using m_t = typename vec<bf16_t, _N>::mask_type;
    // return m_t::cvt_from_rep(v_is_inf);
    return as<m_t>(v_is_inf);
}


template <cftal::size_t _N>
typename cftal::vec<cftal::bf16_t, _N>::mask_type
cftal::isfinite(const vec<bf16_t, _N>& a)
{
    vec<mf_bf16_t, _N> aa= a() & not_sign_f32_msk::v.s16h();
    auto v_is_finite = aa < exp_f32_msk::v.s16h();
    using m_t = typename vec<bf16_t, _N>::mask_type;
    // return m_t::cvt_from_rep(v_is_finite);
    return as<m_t>(v_is_finite);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::copysign(const vec<bf16_t, _N>& x, const vec<bf16_t, _N>& y)
{
    const mf_bf16_t abs_msk=not_sign_f32_msk::v.s16h();
    auto xi=x(), yi=y();
    vec<mf_bf16_t, _N> abs_x= xi & abs_msk;
    const mf_bf16_t sgn_msk=sign_f32_msk::v.s16h();
    vec<mf_bf16_t, _N> sgn_y= yi & sgn_msk;
    vec<mf_bf16_t, _N> r= abs_x | sgn_y;
    return vec<bf16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::copysign(const bf16_t& x, const vec<bf16_t, _N>& y)
{
    vec<bf16_t, _N> vx=x;
    return copysign(vx, y);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::copysign(const vec<bf16_t, _N>& x, const bf16_t& y)
{
    vec<bf16_t, _N> vy=y;
    return copysign(x, vy);
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::bf16_t, _N>
cftal::mulsign(const vec<bf16_t, _N>& x, const vec<bf16_t, _N>& y)
{
    using v_t = vec<mf_bf16_t, _N>;
    const mf_bf16_t msk=sign_f32_msk::v.s16h();
    v_t sgn_y = y() & msk;
    v_t r=x() ^ sgn_y;
    return vec<bf16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::bf16_t, _N>::mask_type
cftal::signbit(const vec<bf16_t, _N>& a)
{
    constexpr const mf_bf16_t z(0);
    vec<mf_bf16_t, _N> ai=a();
    typename vec<mf_bf16_t, _N>::mask_type r=ai < z;
    return as<typename vec<bf16_t, _N>::mask_type>(r);
}

inline
cftal::vec<cftal::bf16_t, 1>
cftal::max(const vec<bf16_t, 1>& a, const vec<bf16_t, 1>& b)
{
    auto f32_max=max(cvt_bf16_to_f32(a()), cvt_bf16_to_f32(b()));
    return vec<bf16_t, 1>::cvt_from_rep(cvt_f32_to_bf16(f32_max));
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::max(const vec<bf16_t, _N>& a, const vec<bf16_t, _N>& b)
{
    auto f32_max=max(cvt_bf16_to_f32(a()), cvt_bf16_to_f32(b()));
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(f32_max));
}

inline
cftal::vec<cftal::bf16_t, 1>
cftal::min(const vec<bf16_t, 1>& a, const vec<bf16_t, 1>& b)
{
    auto f32_min=min(cvt_bf16_to_f32(a()), cvt_bf16_to_f32(b()));
    return vec<bf16_t, 1>::cvt_from_rep(cvt_f32_to_bf16(f32_min));
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::min(const vec<bf16_t, _N>& a, const vec<bf16_t, _N>& b)
{
    auto f32_min=min(cvt_bf16_to_f32(a()), cvt_bf16_to_f32(b()));
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(f32_min));
}

inline
cftal::vec<cftal::bf16_t, 1>
cftal::
select(const vec<bf16_t, 1>::mask_type& m ,
       const vec<bf16_t, 1>& on_true,
       const vec<bf16_t, 1>& on_false)
{
    // here we use the fact that vec<mf_bf16_t, 1> has a copy constructor
    // and that vec<bit, 1> has a constructor from integer
    auto r=select(vec<mf_bf16_t, 1>::mask_type(m()),
                  on_true(), on_false());
    return vec<bf16_t, 1>::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::
select(const typename vec<bf16_t, _N>::mask_type& m ,
       const vec<bf16_t, _N>& on_true,
       const vec<bf16_t, _N>& on_false)
{
    // here we use the fact that vec<mf_bf16_t, _N> has a copy constructor
    // and that vec<bit, _N> has a constructor from integer
    auto r=select(typename vec<mf_bf16_t, _N>::mask_type(m()),
                  on_true(), on_false());
    return vec<bf16_t, _N>::cvt_from_rep(r);
}

inline
cftal::vec<cftal::bf16_t, 1>
cftal::
select_val_or_zero(const vec<bf16_t, 1>::mask_type& m ,
                   const vec<bf16_t, 1>& on_true)
{
    auto r=select_val_or_zero(vec<mf_bf16_t, 1>::mask_type(m()),
                              on_true());
    return vec<bf16_t, 1>::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::
select_val_or_zero(const typename vec<bf16_t, _N>::mask_type& m ,
                   const vec<bf16_t, _N>& on_true)
{
    auto r=select_val_or_zero(typename vec<mf_bf16_t, _N>::mask_type(m()),
                              on_true());
    return vec<bf16_t, _N>::cvt_from_rep(r);
}

inline
cftal::vec<cftal::bf16_t, 1>
cftal::select_zero_or_val(const vec<bf16_t, 1>::mask_type& m ,
                          const vec<bf16_t, 1>& on_false)
{
    auto r=select_zero_or_val(vec<mf_bf16_t, 1>::mask_type(m()),
                              on_false());
    return vec<bf16_t, 1>::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::bf16_t, _N>
cftal::select_zero_or_val(const typename vec<bf16_t, _N>::mask_type& m ,
                          const vec<bf16_t, _N>& on_false)
{
    auto r=select_zero_or_val(typename vec<mf_bf16_t, _N>::mask_type(m()),
                              on_false());
    return vec<bf16_t, _N>::cvt_from_rep(r);
}

#if (__AVX512VL__==0) || (__CFTAL_CFG_ENABLE_AVX512__==0)

inline
bool
cftal::all_of(const vec<bf16_t, 1>::mask_type& v)
{
    return all_of(v());
}

template <cftal::size_t _N>
inline
bool
cftal::all_of(const typename vec<bf16_t, _N>::mask_type& v)
{
    return all_of(v());
}

inline
bool
cftal::any_of(const vec<bf16_t, 1>::mask_type& v)
{
    return any_of(v());
}

template <cftal::size_t _N>
inline
bool
cftal::any_of(const typename vec<bf16_t, _N>::mask_type& v)
{
    return any_of(v());
}

inline
bool
cftal::none_of(const vec<bf16_t, 1>::mask_type& v)
{
    return none_of(v());
}

template <cftal::size_t _N>
inline
bool
cftal::none_of(const typename vec<bf16_t, _N>::mask_type& v)
{
    return none_of(v());
}
#endif

template <cftal::size_t _N>
inline
cftal::vec<cftal::bf16_t, _N>
cftal::rint(const vec<bf16_t, _N>& a)
{
    vec<float, _N> af=cvt_bf16_to_f32(a());
    vec<float, _N> rf=rint(af);
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::bf16_t, _N>
cftal::floor(const vec<bf16_t, _N>& a)
{
    vec<float, _N> af=cvt_bf16_to_f32(a());
    vec<float, _N> rf=floor(af);
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::bf16_t, _N>
cftal::ceil(const vec<bf16_t, _N>& a)
{
    vec<float, _N> af=cvt_bf16_to_f32(a());
    vec<float, _N> rf=ceil(af);
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::bf16_t, _N>
cftal::trunc(const vec<bf16_t, _N>& a)
{
    vec<float, _N> af=cvt_bf16_to_f32(a());
    vec<float, _N> rf=trunc(af);
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::bf16_t, _N>
cftal::sqrt(const vec<bf16_t, _N>& a)
{
    vec<float, _N> af=cvt_bf16_to_f32(a());
    vec<float, _N> rf=sqrt(af);
    return vec<bf16_t, _N>::cvt_from_rep(cvt_f32_to_bf16(rf));
}

template <cftal::size_t _N>
inline
cftal::bf16_t
cftal::hsum(const vec<bf16_t, _N>& a)
{
    vec<float, _N> af=cvt_bf16_to_f32(a());
    float r=hsum(af);
    return bf16_t(r);
}

#undef VBF16_USE_INT_CMP
#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_VXBF16_H__
