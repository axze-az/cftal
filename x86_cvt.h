#if !defined (__CFTAL_X86_CVT_H__)
#define __CFTAL_X86_CVT_H__ 1

#include <cftal/x86_intrin.h>
#if defined (__SSE2__)
#include <cftal/x86_v4s32.h>
#include <cftal/x86_v2f64.h>
#endif
#if defined (__AVX__)
#include <cftal/x86_v4f64.h>
#endif
#include <utility>

namespace cftal {

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

        template <>
        struct cvt<v4s32, v2f64> {
            static v4s32 l(const v2f64& d) {
                return _mm_cvtpd_epi32(d());
            }
        };

        template <>
        struct cvt_rz<v4s32, v2f64> {
            static v4s32 l(const v2f64& d) {
                return _mm_cvttpd_epi32(d());
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
#endif
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
