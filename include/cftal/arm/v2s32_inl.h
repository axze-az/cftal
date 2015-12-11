#if !defined (__CFTAL_ARM_V2S32_INL__)
#define __CFTAL_ARM_V2S32_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/arm/v2s32.h>
#include <cftal/arm/v2s32.h>
#include <cftal/arm/perm.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                return vmvn_s32(a());
            }
        };


        template <>
        struct lt<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vclt_s32(a(), b());
            }
        };

        template <>
        struct le<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcle_s32(a(), b());
            }
        };

        template <>
        struct eq<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vceq_s32(a(), b());
            }
        };

        template <>
        struct ne<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a==b);
            }
        };

        template <>
        struct ge<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcge_s32(a(), b());
            }
        };

        template <>
        struct gt<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return vcgt_s32(a(), b());
            }
        };

        template <>
        struct plus<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a) {
                static const full_type z{0, 0};
                return vsub_s32(z(), a());
            }
        };

        template <>
        struct add<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vadd_s32(a(), b());
            }
        };

        template <>
        struct sub<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vsub_s32(a(), b());
            }
        };

        template <>
        struct mul<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vmul_s32(a(), b());
            }
        };

        template <>
        struct div<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                // return x86::div_s32::lh(a(), b());
                return a;
            }
        };

        template <>
        struct mod<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v2s32 q(a/b);
                v2s32 r(remainder(a, b, q));
                return r;
            }
        };

        template <>
        struct fma<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int32_t, 2>::v(
                    mul<int32_t, 2>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int32_t, 2>::v(
                    mul<int32_t, 2>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int32_t, 2>::v(
                    c, mul<int32_t, 2>::v(a, b));

            }
        };

        template <>
        struct bit_or<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vorr_s32(a(), b());
            }
        };

        template <>
        struct bit_and<int32_t, 2> {
            using full_type = vec<int32_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return vand_s32(a(), b());
            }
        };

        template <>
        struct bit_xor<int32_t, 2> {
            using full_type = vec<int32_t, 2>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return veor_s32(a(), b());
            }
        };

        template <>
        struct shl<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshl_n_s32(a(), s);
            }
        };

        template <>
        struct shr<int32_t, 2> {
            using full_type = vec<int32_t, 2>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return vshr_n_s32(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int32_t, 2>::vec(const vec<uint32_t,2>& v)
    : base_type(vreinterpret_s32_u32(v()))
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(int32_t v)
    : base_type(vmov_n_s32(v))
{
}

inline
cftal::vec<cftal::int32_t, 2>::vec(vec<int32_t, 1> l, vec<int32_t, 1> h)
    : base_type(int32x2_t{l(), h()})
{
}

inline
cftal::vec<cftal::int32_t, 2>::
vec(std::initializer_list<int32_t> l)
    : vec(mem<vec<int32_t, 2> >::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int32_t, 2>::
vec(init_list<int32_t> l)
    : vec(mem<vec<int32_t, 2> >::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int32_t, 2>::vec(const expr<_OP<int32_t, 2>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int32_t, 2>
cftal::mem<cftal::vec<int32_t, 2> >::load(const int32_t* p, std::size_t s)
{
    int32x2_t v;
    switch (s) {
    default:
    case 2:
        v = vld1_s32(p);
        break;
    case 1:
        v = vld1_dup_s32(p);
        break;
    case 0:
        v =int32x2_t{0u, 0u};
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int32_t, 2> >::store(int32_t* p,
                                            const vec<int32_t, 2>& v)
{
    vst1_s32(p, v());
}

inline
cftal::vec<int32_t, 1>
cftal::low_half(const vec<int32_t, 2>& v)
{
    return vec<int32_t, 1>(vget_lane_s32(v(), 0));
}

inline
cftal::vec<int32_t, 1>
cftal::high_half(const vec<int32_t, 2>& v)
{
    return vec<int32_t, 1>(vget_lane_s32(v(), 1));
}

inline
cftal::v2s32 cftal::max(const v2s32& a, const v2s32& b)
{
    return vmax_s32(a(), b());

}

inline
cftal::v2s32 cftal::min(const v2s32& a, const v2s32& b)
{
    return vmin_s32(a(), b());
}

inline
cftal::v2s32 cftal::select(const v2s32::mask_type& m,
                           const v2s32& on_true,
                           const v2s32& on_false)
{
    return vbsl_s32(m(), on_true(), on_false());
}

template <bool _I0, bool _I1>
inline
cftal::v2s32 cftal::select(const v2s32& a, const v2s32& b)
{
    const uint32x2_t m{_I0 ? int32_t(-1) : int32_t(0),
                       _I1 ? int32_t(-1) : int32_t(0)};
    return vbsl_s32(m, a(), b());
}

template <int _I0, int _I1>
inline
cftal::v2s32 cftal::permute(const v2s32& a)
{
    return arm::perm_v2s32<_I0, _I1>(a());
}

template <int _I0, int _I1>
inline
cftal::v2s32 cftal::permute(const v2s32& a, const v2s32& b)
{
    return arm::perm_v2s32<_I0, _I1>(a(), b());
}

inline
std::pair<cftal::v2s32, cftal::v2s32>
cftal::mul_lo_hi(const v2s32& x, const v2s32& y)
{
    return std::make_pair(x, y);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2U32_INL__
