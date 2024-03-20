//
// Copyright (C) 2010-2024 Axel Zeuner
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
#if !defined (__CFTAL_VXF16_H__)
#define __CFTAL_VXF16_H__ 1

#if !defined(__AVX512VL__) || !defined(__AVX512FP16__) || \
(__CFTAL_CFG_ENABLE_AVX512__==0)
#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/vec_cvt_f16.h>
#include <cftal/f16_t.h>
#include <cftal/vec_lookup.h>

namespace cftal {

#if (V4F32_SPECIALIZED>0) || ((V2F32_SPECIALIZED>0) && (V2S32_SPECIALIZED>0))
#define V4F16_SPECIALIZED 1
#endif
#if (V8F32_SPECIALIZED>0) || ((V4F32_SPECIALIZED>0) && (V4S32_SPECIALIZED>0))
#define V8F16_SPECIALIZED 1
#endif
#if (V16F32_SPECIALIZED>0) || ((V8F32_SPECIALIZED>0) && (V8S32_SPECIALIZED>0))
#define V16F16_SPECIALIZED 1
#endif

    template <>
    class vec<f16_t, 1> {
        vec<mf_f16_t, 1> _v;
        struct cvt_from_rep_tag {};
        vec(const vec<mf_f16_t, 1>& f, const cvt_from_rep_tag& )
            : _v(f) {}
    public:
        static
        vec
        cvt_from_rep(const vec<mf_f16_t, 1>& r) {
            return vec(r, cvt_from_rep_tag());
        }
        using value_type = f16_t;
        using mask_value_type =std::conditional_t<
            std::is_same_v<vec<float, 1>::mask_type, bit>,
            bit, f16_t
        >;
        using mask_type = vec<mask_value_type, 1>;
        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;
        vec(const f16_t& v) : _v(read_bits(v)) {}
        const vec<mf_f16_t, 1>& operator()() const { return _v; }
        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<f16_t, 1> >, _L, _R>& r) : vec(eval(r)) {}
    };

    std::ostream&
    operator<<(std::ostream& s, const vec<f16_t, 1>& v);

    template <size_t _N>
    class vec<f16_t, _N> {
        vec<mf_f16_t, _N> _v;
        struct cvt_from_rep_tag {};
        vec(const vec<mf_f16_t, _N>& s, const cvt_from_rep_tag&) : _v(s) {}
    public:
        static
        vec
        cvt_from_rep(const vec<mf_f16_t, _N>& r) {
            return vec(r, cvt_from_rep_tag());
        }

        using value_type = f16_t;
        using half_type = vec<f16_t, _N/2>;
        using mask_value_type =std::conditional_t<
            std::is_same_v<typename vec<float, _N>::mask_type, bit>,
            bit, f16_t
        >;
        using mask_type = vec<mask_value_type, _N>;
        vec() = default;
        vec(const vec& r) = default;

        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;

        vec(f16_t v) : _v(read_bits(v)) {}
        vec(const half_type& lh, const half_type& hh) :
            _v(lh(), hh()) {}
        vec(std::initializer_list<f16_t> l)
            : vec(init_list<f16_t>(l.begin(), l.end())) {}
        vec(init_list<f16_t> l) :
            _v(init_list<mf_f16_t>(
                reinterpret_cast<const mf_f16_t*>(l.begin()),
                reinterpret_cast<const mf_f16_t*>(l.end()))) {}
        half_type lh() const {
            return half_type::cvt_from_rep(low_half(_v));
        }
        half_type hh() const {
            return half_type::cvt_from_rep(high_half(_v));
        }

        const vec<mf_f16_t, _N>& operator()()  const {
            return _v;
        }

        template <template <class _U> class _OP,
                  class _L, class _R>
        vec(const expr<_OP<vec<f16_t, _N>>, _L, _R>& r) : vec(eval(r)) {}
    };


    template <>
    struct mem< vec<f16_t, 1> > {
        static
        vec<f16_t, 1> load(const f16_t* p, std::size_t n=1) {
            auto pp=reinterpret_cast<const mf_f16_t*>(p);
            return vec<f16_t, 1>::cvt_from_rep(*pp);
        }
        static
        void store(f16_t* p, const vec<f16_t, 1>& v) {
            using v_t = vec<mf_f16_t, 1>;
            mem<v_t>::store(reinterpret_cast<mf_f16_t*>(p), v());
        }
    };

    template <size_t _N>
    struct mem< vec<f16_t, _N> > {
        static
        vec<f16_t, _N> load(const f16_t* p, std::size_t n=_N) {
            using v_t= vec<mf_f16_t, _N>;
            v_t r(mem<v_t>::load(reinterpret_cast<const mf_f16_t*>(p), n));
            return vec<f16_t, _N>::cvt_from_rep(r);
        }
        static
        void store(f16_t* p, const vec<f16_t, _N>& v) {
            using v_t = vec<mf_f16_t, _N>;
            mem<v_t>::store(reinterpret_cast<mf_f16_t*>(p), v());
        }
    };

    namespace impl {

        template <size_t _N>
        const vec<bit, _N>&
        cvt_f32_msk_to_f16_msk(const vec<bit, _N>& m) {
            return m;
        }

        template <size_t _N>
        std::enable_if_t<
            std::is_same_v<
                vec<f16_t, _N>,
                typename vec<f16_t, _N>::mask_type
            >,
            vec<f16_t, _N>
        >
        cvt_f32_msk_to_f16_msk(const vec<f32_t, _N>& m) {
            const vec<mf_f16_t, 2*_N> mv=as<const vec<mf_f16_t, 2*_N> >(m);
            auto oe=odd_elements(mv);
            return vec<f16_t, _N>::cvt_from_rep(oe);
        }

#if defined (__SSE2__)
        inline
        vec<f16_t, 4>
        cvt_f32_msk_to_f16_msk(const vec<f32_t, 4>& m) {
            __m128i mi=_mm_castps_si128(m());
            __m128i ri=_mm_packs_epi32(mi, mi);
            vec<mf_f16_t, 8> r(ri);
            return vec<f16_t, 4>::cvt_from_rep(low_half(r));
        }

        inline
        vec<f16_t, 8>
        cvt_f32_msk_to_f16_msk(const vec<f32_t, 8>& m) {
            __m128i mhi=_mm_castps_si128(high_half(m)());
            __m128i mli=_mm_castps_si128(low_half(m)());
            __m128i ri=_mm_packs_epi32(mli, mhi);
            vec<mf_f16_t, 8> r(ri);
            return vec<f16_t, 8>::cvt_from_rep(r);
        }

#if defined (__AVX2__)
        inline
        vec<f16_t, 16>
        cvt_f32_msk_to_f16_msk(const vec<f32_t, 16>& m) {
            __m256i mhi=_mm256_castps_si256(high_half(m)());
            __m256i mli=_mm256_castps_si256(low_half(m)());
            __m256i ri=_mm256_packs_epi32(mli, mhi);
            ri=x86::perm_v4u64<0, 2, 1, 3>(ri);
            vec<mf_f16_t, 16> r(ri);
            return vec<f16_t, 16>::cvt_from_rep(r);
        }
#endif
#endif
    }

    template <size_t _N>
    vec<f16_t, _N/2>
    low_half(const vec<f16_t, _N>& v);

    template <size_t _N>
    vec<f16_t, _N/2>
    high_half(const vec<f16_t, _N>& v);

    template <size_t _N>
    struct arg< vec<f16_t, _N> > {
        using type = std::conditional_t<
            std::is_same_v<vec<mf_f16_t, _N>, arg_t<vec<mf_f16_t, _N> > >,
            vec<f16_t, _N>,
            const vec<f16_t, _N>&
        >;
    };

    template <>
    struct arg< vec<f16_t, 1> > {
        using type = vec<f16_t, 1>;
    };

    template <size_t _I, size_t _N>
    f16_t
    extract(const vec<f16_t, _N>& v);

    template <size_t _N>
    f16_t
    extract(const vec<f16_t, _N>& v, size_t i);

    template <size_t _I, size_t _N>
    void
    insert(vec<f16_t, _N>& v, const f16_t& vi);

    template <size_t _N>
    void
    insert(vec<f16_t, _N>& v, const f16_t& vi, size_t i);

    template <size_t _I>
    f16_t
    extract(const vec<f16_t, 1>& v);

    f16_t
    extract(const vec<f16_t, 1>& v, size_t i);

    template <size_t _I>
    void
    insert(vec<f16_t, 1>& v, const f16_t& vi);

    void
    insert(vec<f16_t, 1>& v, const f16_t& vi, size_t i);

    // abs
    template <size_t _N>
    vec<f16_t, _N>
    abs(const vec<f16_t, _N>& a);

    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    iszero(const vec<f16_t, _N>& a);

    // nan
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isnan(const vec<f16_t, _N>& a);

    // inf
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isinf(const vec<f16_t, _N>& a);

    // isfinite
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    isfinite(const vec<f16_t, _N>& a);

    // copysign
    template <size_t _N>
    vec<f16_t, _N>
    copysign(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b);

    template <size_t _N>
    vec<f16_t, _N>
    copysign(const f16_t& a, const vec<f16_t, _N>& b);

    template <size_t _N>
    vec<f16_t, _N>
    copysign(const vec<f16_t, _N>& a, const f16_t& b);

    // mulsign
    template <size_t _N>
    vec<f16_t, _N>
    mulsign(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b);

    // signbit
    template <size_t _N>
    typename vec<f16_t, _N>::mask_type
    signbit(const vec<f16_t, _N>& a);

    // max
    vec<f16_t, 1>
    max(const vec<f16_t, 1>& a, const vec<f16_t, 1>& b);

    // max
    template <size_t _N>
    vec<f16_t, _N>
    max(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b);

    // min
    vec<f16_t, 1>
    min(const vec<f16_t, 1>& a, const vec<f16_t, 1>& b);

    // min
    template <size_t _N>
    vec<f16_t, _N>
    min(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b);

    // select
    vec<f16_t, 1>
    select(const typename vec<f16_t, 1>::mask_type& m ,
           const vec<f16_t, 1>& on_true,
           const vec<f16_t, 1>& on_false);

    // select
    template <size_t _N>
    vec<f16_t, _N>
    select(const typename vec<f16_t, _N>::mask_type& m ,
           const vec<f16_t, _N>& on_true,
           const vec<f16_t, _N>& on_false);

    // select value or zero
    vec<f16_t, 1>
    select_val_or_zero(const typename vec<f16_t, 1>::mask_type& m ,
                       const vec<f16_t, 1>& on_true);

    // select value or zero
    template <size_t _N>
    vec<f16_t, _N>
    select_val_or_zero(const typename vec<f16_t, _N>::mask_type& m ,
                       const vec<f16_t, _N>& on_true);


    // select zero or value
    vec<f16_t, 1>
    select_zero_or_val(const typename vec<f16_t, 1>::mask_type& m ,
                       const vec<f16_t, 1>& on_false);

    // select zero or value
    template <size_t _N>
    vec<f16_t, _N>
    select_zero_or_val(const typename vec<f16_t, _N>::mask_type& m ,
                       const vec<f16_t, _N>& on_false);

    bool
    all_of(const vec<f16_t, 1>::mask_type& m);

    template <std::size_t _N>
    bool
    all_of(const typename vec<f16_t, _N>::mask_type& m);

    bool
    any_of(const vec<f16_t, 1>::mask_type& m);

    template <std::size_t _N>
    bool
    any_of(const typename vec<f16_t, _N>::mask_type& m);

    bool
    none_of(const vec<f16_t, 1>::mask_type& m);

    template <std::size_t _N>
    bool
    none_of(const typename vec<f16_t, _N>::mask_type& m);

    namespace op {

        template <>
        struct lt<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) < cvt_f16_to_f32(b()));
            }
        };

        template <size_t _N>
        struct lt<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) < cvt_f16_to_f32(b()));
            }
        };

        template <>
        struct le<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) <= cvt_f16_to_f32(b()));
            }
        };

        template <size_t _N>
        struct le<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) <= cvt_f16_to_f32(b()));
            }
        };

        template <>
        struct eq<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) == cvt_f16_to_f32(b()));
            }
        };

        template <size_t _N>
        struct eq<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) == cvt_f16_to_f32(b()));
            }
        };

        template <>
        struct ne<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) != cvt_f16_to_f32(b()));
            }
        };

        template <size_t _N>
        struct ne<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) != cvt_f16_to_f32(b()));
            }
        };

        template <>
        struct ge<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) >= cvt_f16_to_f32(b()));
            }
        };

        template <size_t _N>
        struct ge<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) >= cvt_f16_to_f32(b()));
            }
        };

        template <>
        struct gt<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) > cvt_f16_to_f32(b()));
            }
        };

        template <size_t _N>
        struct gt<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return impl::cvt_f32_msk_to_f16_msk(
                    cvt_f16_to_f32(a()) > cvt_f16_to_f32(b()));
            }
        };

        template <>
        struct plus<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <size_t _N>
        struct plus<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a) {
                vec<mf_f16_t, 1> t=a();
                t ^= sign_f16_msk::v.u16();
                return full_type::cvt_from_rep(t);
            }
        };

        template <size_t _N>
        struct neg<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a) {
                vec<mf_f16_t, _N> t=a();
                t ^= sign_f16_msk::v.u16();
                return full_type::cvt_from_rep(t);
            }
        };

        template <>
        struct add<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=add<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct add<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=add<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct sub<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=sub<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct sub<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=sub<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct mul<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=mul<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct mul<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=mul<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct div<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=div<vec<f32_t, 1>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct div<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fr=div<vec<f32_t, _N>>::v(fa, fb);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct fma<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fc=cvt_f16_to_f32(uc);
                auto fr=fma<vec<f32_t, 1>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct fma<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fc=cvt_f16_to_f32(uc);
                auto fr=fma<vec<f32_t, _N>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct fms<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fc=cvt_f16_to_f32(uc);
                auto fr=fms<vec<f32_t, 1>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct fms<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fc=cvt_f16_to_f32(uc);
                auto fr=fms<vec<f32_t, _N>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct fnma<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fc=cvt_f16_to_f32(uc);
                auto fr=fnma<vec<f32_t, 1>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <size_t _N>
        struct fnma<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b, const full_type& c) {
                auto ua=a(), ub=b(), uc=c();
                auto fa=cvt_f16_to_f32(ua), fb=cvt_f16_to_f32(ub);
                auto fc=cvt_f16_to_f32(uc);
                auto fr=fnma<vec<f32_t, _N>>::v(fa, fb, fc);
                return full_type::cvt_from_rep(cvt_f32_to_f16(fr));
            }
        };

        template <>
        struct bit_or<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_f16_t, 1> r= ua | ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_or<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_f16_t, _N> r= ua | ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <>
        struct bit_and<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_f16_t, 1> r= ua & ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_and<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_f16_t, _N> r= ua & ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <>
        struct bit_xor<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_f16_t, 1> r= ua ^ ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_xor<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                auto ua=a(), ub=b();
                vec<mf_f16_t, _N> r= ua ^ ub;
                return full_type::cvt_from_rep(r);
            }
        };

        template <>
        struct bit_not<vec<f16_t, 1>> {
            using full_type = vec<f16_t, 1>;
            static
            full_type
            v(const full_type& a) {
                auto ua=a();
                vec<mf_f16_t, 1> r= ~ua;
                return full_type::cvt_from_rep(r);
            }
        };

        template <size_t _N>
        struct bit_not<vec<f16_t, _N>> {
            using full_type = vec<f16_t, _N>;
            static
            full_type
            v(const full_type& a) {
                auto ua=a();
                vec<mf_f16_t, _N> r= ~ua;
                return full_type::cvt_from_rep(r);
            }
        };
    } // end namespace op

#if defined (__AVX2__)
#if 0
    template <>
    class variable_vec_lookup_table<f16_t, int16_t, 4> {
        vec<int16_t, 4> _idx;
    public:
        variable_vec_lookup_table(const vec<int16_t, 4>& idx) : _idx(idx) {}
        vec<f16_t, 4>
        from(const f16_t* tbl) const {
            uint64_t i64=as<uint64_t>(_idx);
            __m128i i=_mm_cvtsi64_si128(i64);
            const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
            // TODO: add a method gathering only 4 values to
            // vgatherwph<__m128i, __m128i>
            __m128i r0=x86::vgatherwph<__m128i, __m128i>::v<2>(p, i);
            uint64_t r1=_mm_cvtsi128_si64(r0);
            vec<mf_f16_t, 4> r2=as<vec<mf_f16_t, 4> >(r1);
            return vec<f16_t, 4>::cvt_from_rep(r2);
        }
    };
#endif
    template <>
    class variable_vec_lookup_table<f16_t, int16_t, 8> {
        vec<int16_t, 8> _idx;
    public:
        variable_vec_lookup_table(const vec<int16_t, 8>& idx) : _idx(idx) {}
        vec<f16_t, 8>
        from(const f16_t* tbl) const {
            const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
            __m128i r=x86::vgatherwph<__m128i, __m128i>::v<2>(p, _idx());
            return vec<f16_t, 8>::cvt_from_rep(r);
        }
    };

    template <>
    class variable_vec_lookup_table<f16_t, int16_t, 16> {
        vec<int16_t, 16> _idx;
    public:
        variable_vec_lookup_table(const vec<int16_t, 16>& idx) : _idx(idx) {}
        vec<f16_t, 16>
        from(const f16_t* tbl) const {
            const uint16_t* p=reinterpret_cast<const uint16_t*>(tbl);
            __m256i r=x86::vgatherwph<__m256i, __m256i>::v<2>(p, _idx());
            return vec<f16_t, 16>::cvt_from_rep(r);
        }
    };

#endif
    namespace impl {
        template <size_t _N>
        struct cvt<vec<float, _N>, vec<f16_t, _N> > {
            static
            vec<float, _N> v(const vec<f16_t, _N>& s) {
                return cvt_f16_to_f32(s());
            }
        };

        template <size_t _N>
        struct cvt<vec<f16_t, _N>, vec<float, _N> > {
            static
            vec<f16_t, _N> v(const vec<float, _N>& s) {
                auto t=cvt_f32_to_f16(s);
                return vec<f16_t, _N>::cvt_from_rep(t);
            }
        };

        template <>
        struct cvt<vec<float, 1>, vec<f16_t, 1> > {
            static
            vec<float, 1> v(const vec<f16_t, 1>& s) {
                return cvt_f16_to_f32(s());
            }
        };

        template <>
        struct cvt<vec<f16_t, 1>, vec<float, 1> > {
            static
            vec<f16_t, 1> v(const vec<float, 1>& s) {
                auto t=cvt_f32_to_f16(s);
                return vec<f16_t, 1>::cvt_from_rep(t);
            }
        };

    }

    // vector math functions for vxf16
    template <size_t _N>
    vec<f16_t, _N>
    rint(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    floor(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    ceil(const vec<f16_t, _N>& x);

    template <size_t _N>
    vec<f16_t, _N>
    trunc(const vec<f16_t, _N>& x);

}

inline
std::ostream&
cftal::
operator<<(std::ostream& s, const cftal::vec<f16_t, 1>& v)
{
    auto t=v();
    s << as<f16_t>(t);
    return s;
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N/2>
cftal::low_half(const vec<f16_t, _N>& s)
{
    return s.lh();
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N/2>
cftal::high_half(const vec<f16_t, _N>& s)
{
    return s.hh();
}

template <cftal::size_t _I, size_t _N>
inline
cftal::f16_t
cftal::extract(const vec<f16_t, _N>& v)
{
    mf_f16_t ri=extract<_I>(v());
    return as<f16_t>(ri);
}

template <cftal::size_t _N>
inline
cftal::f16_t
cftal::extract(const vec<f16_t, _N>& v, size_t i)
{
    mf_f16_t ri=extract(v(), i);
    return as<f16_t>(ri);
}

template <cftal::size_t _I, size_t _N>
inline
void
cftal::insert(vec<f16_t, _N>& v, const f16_t& vi)
{
    mf_f16_t vii=read_bits(vi);
    vec<mf_f16_t, _N> r=v();
    insert<_I>(r, vii);
    v = vec<f16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _N>
inline
void
cftal::insert(vec<f16_t, _N>& v, const f16_t& vi, size_t i)
{
    mf_f16_t vii=read_bits(vi);
    vec<mf_f16_t, _N> r=v();
    insert(r, vii, i);
    v = vec<f16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _I>
inline
cftal::f16_t
cftal::extract(const vec<f16_t, 1>& v)
{
    mf_f16_t ri=v()();
    return as<f16_t>(ri);
}

inline
cftal::f16_t
cftal::extract(const vec<f16_t, 1>& v, size_t i)
{
    mf_f16_t ri=v()();
    return as<f16_t>(ri);
}

template <cftal::size_t _I>
inline
void
cftal::insert(vec<f16_t, 1>& v, const f16_t& vi)
{
    mf_f16_t vii=read_bits(vi);
    v= vec<f16_t, 1>::cvt_from_rep(vii);
}

inline
void
cftal::insert(vec<f16_t, 1>& v, const f16_t& vi, size_t i)
{
    static_cast<void>(i);
    mf_f16_t vii=read_bits(vi);
    v= vec<f16_t, 1>::cvt_from_rep(vii);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::abs(const vec<f16_t, _N>& a)
{
    vec<mf_f16_t, _N> t= a() & not_sign_f16_msk::v.u16();
    return vec<f16_t, _N>::cvt_from_rep(t);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::iszero(const vec<f16_t, _N>& a)
{
#if 1
    // to allow common subexpression elimination with isnan/isinf
    vec<mf_f16_t, _N> t= a() & not_sign_f16_msk::v.u16();
#else
    vec<mf_f16_t, _N> t= a();
    t += t;
#endif
    auto v_is_zero = t == mf_f16_t(0);
    using m_t = typename vec<f16_t, _N>::mask_type;
    return m_t::cvt_from_rep(v_is_zero);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::isnan(const vec<f16_t, _N>& a)
{
    vec<mf_f16_t, _N> aa= a() & not_sign_f16_msk::v.u16();
    auto v_is_nan = aa > exp_f16_msk::v.u16();
    using m_t = typename vec<f16_t, _N>::mask_type;
    return m_t::cvt_from_rep(v_is_nan);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::isinf(const vec<f16_t, _N>& a)
{
    vec<mf_f16_t, _N> aa= a() & not_sign_f16_msk::v.u16();
    auto v_is_inf = aa == exp_f16_msk::v.u16();
    using m_t = typename vec<f16_t, _N>::mask_type;
    return m_t::cvt_from_rep(v_is_inf);
}


template <cftal::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::isfinite(const vec<f16_t, _N>& a)
{
    vec<mf_f16_t, _N> aa= a() & not_sign_f16_msk::v.u16();
    auto v_is_finite = aa < exp_f16_msk::v.u16();
    using m_t = typename vec<f16_t, _N>::mask_type;
    return m_t::cvt_from_rep(v_is_finite);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::copysign(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y)
{
    const mf_f16_t abs_msk=not_sign_f16_msk::v.u16();
    auto xi=x(), yi=y();
    vec<mf_f16_t, _N> abs_x= xi & abs_msk;
    const mf_f16_t sgn_msk=sign_f16_msk::v.u16();
    vec<mf_f16_t, _N> sgn_y= yi & sgn_msk;
    vec<mf_f16_t, _N> r= abs_x | sgn_y;
    return vec<f16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::copysign(const f16_t& x, const vec<f16_t, _N>& y)
{
    vec<f16_t, _N> vx=x;
    return copysign(vx, y);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::copysign(const vec<f16_t, _N>& x, const f16_t& y)
{
    vec<f16_t, _N> vy=y;
    return copysign(x, vy);
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::mulsign(const vec<f16_t, _N>& x, const vec<f16_t, _N>& y)
{
    using v_t = vec<mf_f16_t, _N>;
    const int16_t msk=sign_f16_msk::v.s16();
    v_t sgn_y = y() & msk;
    v_t r=x() ^ sgn_y;
    return vec<f16_t, _N>::cvt_from_rep(r);
}

template <cftal::size_t _N>
typename cftal::vec<cftal::f16_t, _N>::mask_type
cftal::signbit(const vec<f16_t, _N>& a)
{
    const int16_t z(0);
    vec<int16_t, _N> ai=a();
    typename vec<int16_t, _N>::mask_type r=ai < z;
    return as<typename vec<f16_t, _N>::mask_type>(r);
}

inline
cftal::vec<cftal::f16_t, 1>
cftal::max(const vec<f16_t, 1>& a, const vec<f16_t, 1>& b)
{
    auto f32_max=max(cvt_f16_to_f32(a()), cvt_f16_to_f32(b()));
    return vec<f16_t, 1>::cvt_from_rep(cvt_f32_to_f16(f32_max));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::max(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b)
{
    auto f32_max=max(cvt_f16_to_f32(a()), cvt_f16_to_f32(b()));
    return vec<f16_t, _N>::cvt_from_rep(cvt_f32_to_f16(f32_max));
}

inline
cftal::vec<cftal::f16_t, 1>
cftal::min(const vec<f16_t, 1>& a, const vec<f16_t, 1>& b)
{
    auto f32_min=min(cvt_f16_to_f32(a()), cvt_f16_to_f32(b()));
    return vec<f16_t, 1>::cvt_from_rep(cvt_f32_to_f16(f32_min));
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::min(const vec<f16_t, _N>& a, const vec<f16_t, _N>& b)
{
    auto f32_min=min(cvt_f16_to_f32(a()), cvt_f16_to_f32(b()));
    return vec<f16_t, _N>::cvt_from_rep(cvt_f32_to_f16(f32_min));
}

inline
cftal::vec<cftal::f16_t, 1>
cftal::
select(const typename vec<f16_t, 1>::mask_type& m ,
       const vec<f16_t, 1>& on_true,
       const vec<f16_t, 1>& on_false)
{
    auto r=select(m(), on_true(), on_false());
    return vec<f16_t, 1>::mask_type::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::
select(const typename vec<f16_t, _N>::mask_type& m ,
       const vec<f16_t, _N>& on_true,
       const vec<f16_t, _N>& on_false)
{
    auto r=select(m(), on_true(), on_false());
    return vec<f16_t, _N>::mask_type::cvt_from_rep(r);
}

inline
cftal::vec<cftal::f16_t, 1>
cftal::
select_val_or_zero(const typename vec<f16_t, 1>::mask_type& m ,
                   const vec<f16_t, 1>& on_true)
{
    auto r=select_val_or_zero(m(), on_true());
    return vec<f16_t, 1>::mask_type::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::
select_val_or_zero(const typename vec<f16_t, _N>::mask_type& m ,
                   const vec<f16_t, _N>& on_true)
{
    auto r=select_val_or_zero(m(), on_true());
    return vec<f16_t, _N>::mask_type::cvt_from_rep(r);
}

inline
cftal::vec<cftal::f16_t, 1>
cftal::select_zero_or_val(const typename vec<f16_t, 1>::mask_type& m ,
                          const vec<f16_t, 1>& on_false)
{
    auto r=select_zero_or_val(m(), on_false());
    return vec<f16_t, 1>::mask_type::cvt_from_rep(r);
}

template <cftal::size_t _N>
cftal::vec<cftal::f16_t, _N>
cftal::select_zero_or_val(const typename vec<f16_t, _N>::mask_type& m ,
                          const vec<f16_t, _N>& on_false)
{
    auto r=select_zero_or_val(m(), on_false());
    return vec<f16_t, _N>::mask_type::cvt_from_rep(r);
}

inline
bool
cftal::all_of(const vec<f16_t, 1>::mask_type& v)
{
    return all_of(v());
}

template <cftal::size_t _N>
inline
bool
cftal::all_of(const typename vec<f16_t, _N>::mask_type& v)
{
    return all_of(v());
}

inline
bool
cftal::any_of(const vec<f16_t, 1>::mask_type& v)
{
    return any_of(v());
}

template <cftal::size_t _N>
inline
bool
cftal::any_of(const typename vec<f16_t, _N>::mask_type& v)
{
    return any_of(v());
}

inline
bool
cftal::none_of(const vec<f16_t, 1>::mask_type& v)
{
    return none_of(v());
}

template <cftal::size_t _N>
inline
bool
cftal::none_of(const typename vec<f16_t, _N>::mask_type& v)
{
    return none_of(v());
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::rint(const vec<f16_t, _N>& a)
{
    vec<float, _N> af=cvt_f16_to_f32(a());
    vec<float, _N> rf=rint(af);
    return vec<f16_t, _N>::cvt_from_rep(cvt_f32_to_f16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::floor(const vec<f16_t, _N>& a)
{
    vec<float, _N> af=cvt_f16_to_f32(a());
    vec<float, _N> rf=floor(af);
    return vec<f16_t, _N>::cvt_from_rep(cvt_f32_to_f16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::ceil(const vec<f16_t, _N>& a)
{
    vec<float, _N> af=cvt_f16_to_f32(a());
    vec<float, _N> rf=ceil(af);
    return vec<f16_t, _N>::cvt_from_rep(cvt_f32_to_f16(rf));
}

template <cftal::size_t _N>
inline
cftal::vec<cftal::f16_t, _N>
cftal::trunc(const vec<f16_t, _N>& a)
{
    vec<float, _N> af=cvt_f16_to_f32(a());
    vec<float, _N> rf=trunc(af);
    return vec<f16_t, _N>::cvt_from_rep(cvt_f32_to_f16(rf));
}

#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_VXF16_H__
