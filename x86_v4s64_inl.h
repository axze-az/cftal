#if !defined (__CFTAL_X86_V4S64_INL__)
#define __CFTAL_X86_V4S64_INL__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_v4s64.h>
#include <cftal/x86_v4u64.h>
#include <cftal/x86_perm.h>
#include <cftal/x86_ops_1.h>
#include <cftal/divisor.h>

namespace cftal {

    namespace op {

        template <>
        struct bit_not<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a) {
                full_type all_set(0xffffffff);
                return _mm256_xor_si256(a(), all_set());
            }
        };

        
        template <>
        struct lt<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return b > a;
            }
        };

        template <>
        struct le<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(b > a);
            }
        };

        template <>
        struct eq<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpeq_epi64(a(), b());
            }
        };

        template <>
        struct ne<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a == b);
            }
        };

        template <>
        struct ge<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return ~(a < b);
            }
        };

        template <>
        struct gt<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            using mask_type = typename full_type::mask_type;
            static
            mask_type
            v(const full_type& a, const full_type& b) {
                return _mm256_cmpgt_epi64(a(), b());
            }
        };

        template <>
        struct plus<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            const full_type&
            v(const full_type& a) {
                return a;
            }
        };

        template <>
        struct neg<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a) {
                const full_type zero(0);
                return _mm256_sub_epi64(zero(), a());
            }
        };

        template <>
        struct add<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_add_epi64(a(), b());
            }
        };

        template <>
        struct sub<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_sub_epi64(a(), b());
            }
        };

        template <>
        struct mul<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::impl::vpmullq::v(a(), b());
            }
        };

        template <>
        struct div<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return x86::div_s64::v(a(), b());
            }
        };

        template <>
        struct mod<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                v4s64 q(a/b);
                v4s64 r(remainder(a, b, q));
                return r;                
            }
        };

        template <>
        struct fma<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<int64_t, 4>::v(
                    mul<int64_t, 4>::v(a(), b()), c());
            }
        };

        template <>
        struct fms<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<int64_t, 4>::v(
                    mul<int64_t, 4>::v(a , b), c);
            }
        };

        template <>
        struct fnma<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                // return full_type(c() - a() * b());
                // return full_type(std::fma(-a(), b(), c()));
                return sub<int64_t, 4>::v(
                    c, mul<int64_t, 4>::v(a, b));
                                          
            }
        };
        
        template <>
        struct bit_or<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_or_si256(a(), b());
            }
        };

        template <>
        struct bit_and<int64_t, 4> {
            using full_type = vec<int64_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_and_si256(a(), b());
            }
        };

        template <>
        struct bit_xor<int64_t, 4> {
            using full_type = vec<int64_t, 4>;

            static
            full_type
            v(const full_type& a, const full_type& b) {
                return _mm256_xor_si256(a(), b());
            }
        };

        template <>
        struct shl<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::impl::vpsllq::v(a(), s);
            }
        };

        template <>
        struct shr<int64_t, 4> {
            using full_type = vec<int64_t, 4>;
            static
            full_type
            v(const full_type& a, unsigned s) {
                return x86::impl::vpsraq::v(a(), s);
            }
        };

    }

}

inline
cftal::vec<cftal::int64_t, 4>::vec(const vec<uint64_t, 4>& v)
    : base_type(v())
{
}

inline
cftal::vec<cftal::int64_t, 4>::vec(int64_t v)
    : base_type(_mm256_set_epi64x(v, v, v, v))
{
}


inline
cftal::vec<cftal::int64_t, 4>::
vec(std::initializer_list<int64_t> l)
    : vec(mem<v4s64>::load(l.begin(), l.size()))
{
}

inline
cftal::vec<cftal::int64_t, 4>::
vec(init_list<int64_t> l)
    : vec(mem<v4s64>::load(l.begin(), l.size()))
{
}

template <template <class _U, std::size_t _M> class _OP,
          class _L, class _R>
inline
cftal::
vec<cftal::int64_t, 4>::vec(const expr<_OP<int64_t, 4>, _L, _R>& r)
    : vec(eval(r))
{
}

inline
cftal::vec<cftal::int64_t, 4>
cftal::mem<cftal::vec<int64_t, 4> >::load(const int64_t* p, std::size_t s)
{
    __m256i v;
    switch (s) {
    default:
    case 4:
        v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
        break;
    case 3:
        v = _mm256_setr_epi64x(p[0], p[1], p[2], p[2]);
        break;
    case 2:
        v = _mm256_setr_epi64x(p[0], p[1], p[1], p[1]);
        break;
    case 1:
        v = _mm256_setr_epi64x(p[0], p[0], p[0], p[0]);
        break;
    case 0:
        v = _mm256_set_epi64x(0, 0, 0, 0);
        break;
    }
    return v;
}

inline
void
cftal::mem<cftal::vec<int64_t, 4> >::store(int64_t* p,
                                           const vec<int64_t, 4>& v)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), v());
}

inline
cftal::v4s64 cftal::max(const v4s64& a, const v4s64& b)
{
    v4s64 _gt(a > b);
    return select(_gt, a, b);
}

inline
cftal::v4s64 cftal::min(const v4s64& a, const v4s64& b)
{
    v4s64 _lt(a < b);
    return select(_lt, a, b);
}

inline
cftal::v4s64 cftal::select(const v4s64::mask_type& m,
                           const v4s64& on_true,
                           const v4s64& on_false)
{
    return x86::select(m(), on_true(), on_false());
}

template <bool _I0, bool _I1, bool _I2, bool _I3>
inline
cftal::v4s64
cftal::select(const v4s64& a, const v4s64& b)
{
    return x86::select_u64<_I0, _I1, _I2, _I3>(a(), b());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4s64 cftal::permute(const v4s64& a)
{
    return x86::perm_u64<_I0, _I1, _I2, _I3>(a());
}

template <int _I0, int _I1, int _I2, int _I3>
inline
cftal::v4s64 cftal::permute(const v4s64& a, const v4s64& b)
{
    return x86::perm_u64<_I0, _I1, _I2, _I3>(a(), b());
}

inline
std::pair<cftal::v4s64, cftal::v4s64>
cftal::mul_lo_hi(const v4s64& x, const v4s64& y)
{
    // muluh(x,y) = mulsh(x,y) + and(x, xsign(y)) + and(y, xsign(x));
    // mulsh(x,y) = muluh(x,y) - and(x, xsign(y)) - and(y, xsign(x));
    std::pair<v4u64, v4u64> ur(mul_lo_hi(v4u64(x), v4u64(y)));
    v4s64 xsgn_y= y >> 63;
    v4s64 xsgn_x= x >> 63;
    v4s64 x_and_xsgn_y = x & xsgn_y;
    v4s64 y_and_xsgn_x = y & xsgn_x;
    v4s64 ph= v4s64(ur.second) - x_and_xsgn_y - y_and_xsgn_x;
    v4s64 pl= v4s64(ur.first);
    return std::make_pair(pl, ph);
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V4S64_INL__
