//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_CVT_H__)
#define __CFTAL_CVT_H__ 1


#include <cftal/vec.h>
#include <cftal/cast.h>
#include <utility>

namespace cftal {

    namespace impl {

    }


    template <typename _D, std::size_t _DN,
              typename _S, std::size_t _SN>
    struct cvt_mask {
        static
        vec<_D, _DN>
        v(const vec<_S, _SN>& v);
    };

    template <typename _T, std::size_t _N>
    struct cvt_mask<_T, _N, _T, _N> {
        static
        vec<_T, _N>
        v(const vec<_T, _N>& v) {
            return v;
        }
    };

    template <>
    struct cvt_mask<int32_t, 2, bit, 1> {
        static
        vec<int32_t, 2>
        v(const vec<bit, 1>& v) {
            int32_t m= v() == true ? -1 : 0;
            return vec<int32_t, 2>(m);
        }
    };

    template <>
    struct cvt_mask<bit, 1, int32_t, 2> {
        static
        vec<bit, 1>
        v(const vec<int32_t, 2>& m) {
            int32_t r= low_half(m)() & high_half(m)();
            int32_t rs= r !=0;
            return vec<bit, 1>(bool(rs));
        }
    };

    template <>
    struct cvt_mask<int32_t, 1, bit, 1> {
        static
        vec<int32_t, 1>
        v(const vec<bit, 1>& v) {
            int32_t m= v() == true ? -1 : 0;
            return vec<int32_t, 1>(m);
        }
    };

    template <>
    struct cvt_mask<bit, 1, int32_t, 1> {
        static
        vec<bit, 1>
        v(const vec<int32_t, 1>& m) {
            int32_t rs= m() !=0;
            return vec<bit, 1>(bool(rs));
        }
    };

    template <>
    struct cvt_mask<int32_t, 2, bool, 1> {
        static
        vec<int32_t, 2>
        v(const vec<bool, 1>& v) {
            int32_t m= v() == true ? -1 : 0;
            return vec<int32_t, 2>(m);
        }
    };

    template <>
    struct cvt_mask<bool, 1, int32_t, 2> {
        static
        vec<bool, 1>
        v(const vec<int32_t, 2>& m) {
            int32_t r= low_half(m)() & high_half(m)();
            bool rs= r !=0;
            return vec<bool, 1>(bool(rs));
        }
    };

    template <>
    struct cvt_mask<int32_t, 1, bool, 1> {
        static
        vec<int32_t, 1>
        v(const vec<bool, 1>& v) {
            int32_t m= v() == true ? -1 : 0;
            return vec<int32_t, 1>(m);
        }
    };

    template <>
    struct cvt_mask<bool, 1, int32_t, 1> {
        static
        vec<bool, 1>
        v(const vec<int32_t, 1>& m) {
            bool rs= m() !=0;
            return vec<bool, 1>(bool(rs));
        }
    };


    template <std::size_t _N>
    struct cvt_mask<int32_t, _N, float, _N> {
        static
        vec<int32_t, _N>
        v(const vec<float, _N>& m) {
            return as<vec<int32_t, _N> >(m);
        }
    };

    template <std::size_t _N>
    struct cvt_mask<float, _N, int32_t, _N> {
        static
        vec<float, _N>
        v(const vec<int32_t, _N>& m) {
            return as<vec<float, _N> >(m);
        }
    };

    template <std::size_t _N>
    struct cvt_mask<int32_t, _N, double, _N> {
        static
        vec<int32_t, _N>
        v(const vec<double, _N>& m) {
            vec<int32_t, 2*_N> t=as<vec<int32_t, 2*_N> >(m);
            return odd_elements(t);
        }
    };

    template <std::size_t _N>
    struct cvt_mask<double, _N, int32_t, _N> {
        static
        vec<double, _N>
        v(const vec<int32_t, _N>& m) {
            vec<int32_t, 2*_N> t= combine_even_odd(m, m);
            return as<vec<double, _N> >(t);
        }
    };


    template <std::size_t _N2, std::size_t _N>
    struct cvt_mask<int32_t, _N2, double, _N> {
        static_assert(_N2 == 2*_N, "invalid parameter pair");
        static
        vec<int32_t, _N2>
        v(const vec<double, _N>& m) {
            vec<int32_t, _N2> t=as<vec<int32_t, _N2> >(m);
            return t;
        }
    };

    template <std::size_t _N, std::size_t _N2>
    struct cvt_mask<double, _N, int32_t, _N2> {
        static_assert(_N2 == 2*_N, "invalid parameter pair");
        static
        vec<double, _N>
        v(const vec<int32_t, _N2>& m) {
            return as<vec<double, _N> >(m);
        }
    };

#if 0
    // convert mask vectors - the mask vector types are the same
    // for all types of vectors of the same size if
    // specializations do not exist
    template <typename _D, typename _S, std::size_t _N>
    struct cvt_mask {

        struct eq_t {};
        struct lt_t {};
        struct gt_t {};

        template <typename _DST, typename _SRC>
        struct type_sel {
            using type =
                typename std::conditional<
                (sizeof(_DST) == sizeof(_SRC)),
                eq_t,
                typename std::conditional<(sizeof(_DST)>sizeof(_SRC)),
                gt_t,
                lt_t>::type >::type;
        };

        template <typename _DST, typename _SRC,
                  std::size_t _NN, std::size_t _SRCCALE>
        struct scale_up {};

        template <typename _DST, typename _SRC, std::size_t _NN>
        struct scale_up<_DST, _SRC, _NN, 2> {
            static
            vec<_DST, _NN>
            v(const vec<_SRC, _NN>& v) {
                vec<_SRC, _NN*2> t= combine_even_odd(v, v);
                return as<vec<_DST, _NN> >(t);
            }
        };

        template <typename _DST, typename _SRC, std::size_t _NN>
        struct scale_up<_DST, _SRC, _NN, 4> {
            static
            vec<_DST, _NN>
            v(const vec<_SRC, _NN>& v) {
                vec<_SRC, _NN*2> t0= combine_even_odd(v, v);
                vec<_SRC, _NN*4> t1= combine_even_odd(t0, t0);
                return as<vec<_DST, _NN> >(t1);
            }
        };


        template <typename _DST, typename _SRC,
                  std::size_t _NN, std::size_t _SRCCALE>
        struct scale_down {};

        template <typename _DST, typename _SRC, std::size_t _NN>
        struct scale_down<_DST, _SRC, _NN, 2> {
            static
            vec<_DST, _NN>
            v(const vec<_SRC, _NN>& a) {
                vec<_DST, 2*_NN> vt= as<vec<_DST, 2*_NN> >(a);
                vec<_DST, _NN> r= odd_elements(vt);
                return r;
            }
        };

        template <typename _DST, typename _SRC, std::size_t _NN>
        struct scale_down<_DST, _SRC, _NN, 4> {
            static
            vec<_DST, _NN>
            v(const vec<_SRC, _NN>& a) {
                vec<_DST, 4*_NN> vt= as<vec<_DST, 2*_NN> >(a);
                vec<_SRC, 2*_NN> r0= odd_elements(vt);
                vec<_SRC, _NN> r= odd_elements(r0);
                return r;
            }
        };


    public:
#if 0
        // default case
        static
        vec<bit, _N>
        v(const vec<bit, _N>& s) {
            return s;
        }
#endif
        static
        vec<_D, _N>
        v(const vec<_S, _N>& s) {
            typename type_sel<_D, _S>::type t;
            return g(s, t);
        }

    private:
        static
        vec<_D, _N>
        g(const vec<_S, _N> s, eq_t) {
            return as<vec<_D, _N> >(s);
        }

        static
        vec<_D, _N>
        g(const vec<_S, _N> s, lt_t) {
            const std::size_t scale= sizeof(_S)/sizeof(_D);
            return scale_down<_D, _S, _N, scale>::v(s);
        }

        static
        vec<_D, _N>
        g(const vec<_S, _N> s, gt_t) {
            const std::size_t scale= sizeof(_D)/sizeof(_S);
            return scale_up<_D, _S, _N, scale>::v(s);
        }

    };
#endif

    namespace impl {

        // convert according to current rounding mode
        template <typename _D, typename _S>
        struct cvt {
            static
            _D l(const _S& s);
            static
            _D h(const _S& s);
        };

        // convert with truncation (i.e. round to zero)
        template <typename _D, typename _S>
        struct cvt_rz {
            static
            _D l(const _S& s);
            static
            _D h(const _S& s);
        };

        template <typename _D, typename _S, std::size_t _N>
        struct cvt_rz<vec<_D, _N>, vec<_S, _N> >  {
            static const std::size_t _NHALF = _N/2;
            using cvt_rz_half_t =
                cvt_rz<vec<_D, _NHALF>, vec<_S, _NHALF> >;
            static
            vec<_D, _N>
            l(const vec<_S, _N>& s) {
                vec<_D, _NHALF> v0= cvt_rz_half_t::l(low_half(s));
                vec<_D, _NHALF> v1= cvt_rz_half_t::l(high_half(s));
                return vec<_D, _N>(v0, v1);
            }
            static
            vec<_D, _N>
            h(const vec<_S, _N>& s) {
                return l(s);
            }
        };

        template <typename _D, typename _S>
        struct cvt_rz<vec<_D, 1>, vec<_S, 1> > {
            static
            vec<_D, 1>
            l(const vec<_S, 1>& s) {
                return vec<_D, 1>(static_cast<_D>(s()));
            }
            static
            vec<_D, 1>
            h(const vec<_D, 1>& s) {
                return l(s);
            }
        };

        template <typename _D, typename _S, std::size_t _N>
        struct cvt<vec<_D, _N>, vec<_S, _N> > {
            static const std::size_t _NHALF = _N/2;
            using cvt_half_t =
                cvt<vec<_D, _NHALF>, vec<_S, _NHALF> >;
            static
            vec<_D, _N>
            l(const vec<_S, _N>& s) {
                vec<_D, _NHALF> v0= cvt_half_t::l(low_half(s));
                vec<_D, _NHALF> v1= cvt_half_t::l(high_half(s));
                return vec<_D, _N>(v0, v1);
            }
            static
            vec<_D, _N>
            h(const vec<_S, _N>& s) {
                return l(s);
            }
        };

        // widening conversions:
        template <typename _D, typename _S>
        struct cvt<vec<_D, 1>, vec<_S, 1> >
            : public cvt_rz<vec<_D, 1>, vec<_S, 1> > {};

        // narrowing specializations
        template <>
        struct cvt<vec<int32_t, 1>, vec<double, 1> > {
            static
            vec<int32_t, 1>
            l(const vec<double, 1>& s) {
                return vec<int32_t, 1>(
                    static_cast<int32_t>(std::rint(s())));
            }
            static
            vec<int32_t, 1>
            h(const vec<double, 1>& s) {
                return l(s);
            }
        };

        template<>
        struct cvt<vec<int32_t, 1>, vec<float, 1> > {
            static
            vec<int32_t, 1>
            l(const vec<float, 1>& s) {
                return vec<int32_t, 1>(
                    static_cast<int32_t>(std::rintf(s())));
            }
            static
            vec<int32_t, 1>
            h(const vec<float, 1>& s) {
                return l(s);
            }
        };


#if defined (__SSE2__)
        template <>
        struct cvt<v4f32, v2f64> {
            static v4f32 l(const v2f64& d) {
                return _mm_cvtpd_ps(d());
            }
        };

        template <>
        struct cvt<v2f64, v4f32> {
            static v2f64 l(const v4f32& d) {
                return _mm_cvtps_pd(d());
            }
            static v2f64 h(const v4f32& d) {
                return l(permute<2,3,0,1>(d));
            }
        };
#if 1
        template <>
        struct cvt<v2s32, v2f64> {
            static v2s32 l(const v2f64& d) {
                v4s32 r=_mm_cvtpd_epi32(d());
                return low_half(r);
            }
        };

        template <>
        struct cvt_rz<v2s32, v2f64> {
            static v2s32 l(const v2f64& d) {
                v4s32 r=_mm_cvttpd_epi32(d());
                return low_half(r);
            }
        };

        template <>
        struct cvt<v2f64, v2s32> {
            static v2f64 l(const v2s32& d) {
                v4s32 t(d, d);
                return _mm_cvtepi32_pd(t());
            };
        };
#endif

        template <>
        struct cvt<v4s32, v2f64> {
            static v4s32 l(const v2f64& d) {
                v4s32 r=_mm_cvtpd_epi32(d());
                return r;
            }
        };

        template <>
        struct cvt_rz<v4s32, v2f64> {
            static v4s32 l(const v2f64& d) {
                v4s32 r=_mm_cvttpd_epi32(d());
                return r;
            }
        };

        template <>
        struct cvt<v2f64, v4s32> {
            static v2f64 l(const v4s32& d) {
                return _mm_cvtepi32_pd(d());
            };
            static v2f64 h(const v4s32& d) {
                return l(permute<2,3,0,1>(d));
            }
        };

        template <>
        struct cvt<v4f32, v4s32> {
            static v4f32 l(const v4s32& s) {
                return _mm_cvtepi32_ps(s());
            }
        };

#if 0
        template <>
        struct cvt<v4f32, v2s32> {
            static v4f32 l(const v2s32& s) {
                return _mm_cvtepi32_ps(s());
            }
        };
#endif

        template <>
        struct cvt<v4s32, v4f32> {
            static v4s32 l(const v4f32& s) {
                return _mm_cvtps_epi32(s());
            }
        };

        template <>
        struct cvt_rz<v4s32, v4f32> {
            static v4s32 l(const v4f32& s) {
                return _mm_cvttps_epi32(s());
            }
        };

        template <>
        struct cvt<v4s32, v4f64> {
            static v4s32 l(const v4f64& s) {
#if !defined (__AVX__)
                v2f64 sl= low_half(s);
                v2f64 sh= high_half(s);
                v4s32 il= cvt<v4s32, v2f64>::l(sl);
                v4s32 ih= cvt<v4s32, v2f64>::l(sh);
                return v4s32(permute<0, 1, 4, 5>(il, ih));
#else
                return _mm256_cvtpd_epi32(s());
#endif
            }
        };

        template <>
        struct cvt_rz<v4s32, v4f64> {
            static v4s32 l(const v4f64& s) {
#if !defined (__AVX__)
                v2f64 sl= low_half(s);
                v2f64 sh= high_half(s);
                v4s32 il= cvt_rz<v4s32, v2f64>::l(sl);
                v4s32 ih= cvt_rz<v4s32, v2f64>::l(sh);
                return v4s32(permute<0, 1, 4, 5>(il, ih));
#else
                return _mm256_cvttpd_epi32(s());
#endif
            }
        };

        template <>
        struct cvt<v4f64, v4s32> {
            static v4f64 l(const v4s32&s) {
#if !defined (__AVX__)
                v2f64 fl= cvt<v2f64, v4s32>::l(s);
                v4s32 sh= permute<2, 3, 2, 3>(s);
                v2f64 fh= cvt<v2f64, v4s32>::l(sh);
                return v4f64(fl, fh);
#else
                return _mm256_cvtepi32_pd(s());
#endif
            }
        };

        template <>
        struct cvt<v8f32, v8s32> {
            static v8f32 l(const v8s32& v) {
#if defined (__AVX__)
                __m256i vv=_mm256_insertf128_si256(
                    _mm256_castsi128_si256(low_half(v)()),
                    high_half(v)(), 1);
                __m256 f(_mm256_cvtepi32_ps(vv));
                return f;
#else
                v4f32 lh(cvt<v4f32, v4s32>::l(low_half(v)));
                v4f32 hh(cvt<v4f32, v4s32>::l(high_half(v)));
                return v8f32(lh, hh);
#endif
            }
        };

        template <>
        struct cvt<v8s32, v8f32> {
            static v8s32 l(const v8f32& v) {
#if defined(__AVX__)
                __m256i vi=_mm256_cvtps_epi32(v());
                __m128i hh(_mm256_extractf128_si256(vi, 1));
                __m128i lh(_mm256_castsi256_si128(vi));
                return v8s32(lh, hh);
#else
                v4s32 lh(cvt<v4s32, v4f32>::l(low_half(v)));
                v4s32 hh(cvt<v4s32, v4f32>::l(high_half(v)));
                return v8s32(lh, hh);
#endif
            }
        };


        template <>
        struct cvt<v4f32, v4f64> {
            static v4f32 l(const v4f64& s) {
#if defined (__AVX__)
                return _mm256_cvtpd_ps(s());
#else
                v4f32 lh(cvt<v4f32, v2f64>::l(low_half(s)));
                v4f32 hh(cvt<v4f32, v2f64>::l(high_half(s)));
                v4f32 r(permute<0, 1, 4, 5>(lh, hh));
                return r;
#endif
            }
        };


        template <>
        struct cvt<v4f64, v4f32> {
            static v4f64 l(const v4f32& s) {
#if defined (__AVX__)
                return _mm256_cvtps_pd(s());
#else
                v2f64 lh(cvt<v2f64, v4f32>::l(s));
                v2f64 hh(cvt<v2f64, v4f32>::h(s));
                return v4f64(lh, hh);
#endif
            }
        };

        template <>
        struct cvt<v4f64, v8f32> {
            static v4f64 l(const v8f32& a) {
                return cvt<v4f64, v4f32>::l(low_half(a));
            }
            static v4f64 h(const v8f32& a) {
                return cvt<v4f64, v4f32>::l(high_half(a));
            }


        };

        template <>
        struct cvt<v8f32, v4f64> {
            static v8f32 l(const v4f64& a) {
                return v8f32(cvt<v4f32, v4f64>::l(a),
                             v4f32(0.0f));
            }
        };
#endif // __SSE2__
    }

    template <class _D, class _S>
    _D cvt_lo(const _S& s);
    template <class _D, class _S>
    _D cvt_hi(const _S& s);
    template <class _D, class _S>
    _D cvt(const _S& s);

    v4f32 cvt_f32(const v2f64& l, const v2f64& h);
    v8f32 cvt_f32(const v4f64& l, const v4f64& h);

    template <class _D, class _S>
    std::pair<_D, _D> cvt_widen(const _S& s);

    template <class _D, class _S>
    _D cvt_rz_lo(const _S& s);
    template <class _D, class _S>
    _D cvt_rz_hi(const _S& s);
    template <class _D, class _S>
    _D cvt_rz(const _S& s);
    template <class _D, class _S>
    std::pair<_D, _D> cvt_rz_widen(const _S& s);

}

template <class _D, class _S>
inline
_D cftal::cvt_lo(const _S& s)
{
    return impl::cvt<_D, _S>::l(s);
}

template <class _D, class _S>
inline
_D cftal::cvt_hi(const _S& s)
{
    return impl::cvt<_D, _S>::h(s);
}

template <class _D, class _S>
inline
_D cftal::cvt(const _S& s)
{
    return impl::cvt<_D, _S>::l(s);
}

template <class _D, class _S>
inline
std::pair<_D, _D> cftal::cvt_widen(const _S& s)
{
    _D l=cvt_lo<_D>(s);
    _D h=cvt_hi<_D>(s);
    return std::make_pair(l, h);
}

#if 0
inline
impl::v4f32 impl::cvt_f32(const v2f64& l, const v2f64& h)
{
    v4f32 lf(cvt<v4f32>(l));
    v4f32 hf(cvt<v4f32>(h));
    return permute<0, 1, 4, 5>(lf, hf);
}

inline
impl::v8f32 impl::cvt_f32(const v4f64& l, const v4f64& h)
{
    v4f32 lf(cvt<v4f32>(l));
    v4f32 hf(cvt<v4f32>(h));
    return v8f32(lf, hf);
}
#endif

template <class _D, class _S>
inline
_D cftal::cvt_rz_lo(const _S& s)
{
    return impl::cvt_rz<_D, _S>::l(s);
}

template <class _D, class _S>
inline
_D cftal::cvt_rz_hi(const _S& s)
{
    return impl::cvt_rz<_D, _S>::h(s);
}

template <class _D, class _S>
inline
_D cftal::cvt_rz(const _S& s)
{
    return impl::cvt_rz<_D, _S>::l(s);
}

template <class _D, class _S>
inline
std::pair<_D, _D> cftal::cvt_rz_widen(const _S& s)
{
    _D l=cvt_rz_lo<_D>(s);
    _D h=cvt_rz_hi<_D>(s);
    return std::make_pair(l, h);
}

// Local variables:
// mode: c++
// end:
#endif
