#if !defined (__CFTAL_Q_REAL_H__)
#define __CFTAL_Q_REAL_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>

namespace cftal {

    template <typename _T>
    class q_real {
        _T _v0;
        _T _v1;
        _T _v2;
        _T _v3;
    public:
        constexpr
        q_real(_T v)
            : _v0(v), _v1(0), _v2(0), _v3(0) {}
        constexpr
        q_real(_T v0, _T v1)
            : _v0(v0), _v1(v1), _v2(0), _v3(0) {}
        constexpr
        q_real(_T v0, _T v1, _T v2)
            : _v0(v0), _v1(v1), _v2(v2), _v3(0) {}
        constexpr
        q_real(_T v0, _T v1, _T v2, _T v3)
            : _v0(v0), _v1(v1), _v2(v2), _v3(v3) {}
        template <typename _U>
        constexpr
        q_real(const q_real<_U>& r)
            : _v0(r.v0()), _v1(r.v1()), _v2(r.v2()), _v3(r.v3()) {}
        constexpr
        q_real(const d_real<_T>& r)
            : _v0(r.h()), _v1(r.l()), _v2(0), _v3(0) {}
        constexpr
        q_real(const d_real<_T>& h, const d_real<_T>& l)
            : _v0(h.h()), _v1(h.l()), _v2(l.h()), _v3(l.l()) {}

        const _T& v0() const { return _v0; }
        const _T& v1() const { return _v1; }
        const _T& v2() const { return _v2; }
        const _T& v3() const { return _v3; }
    };

    namespace impl {
        template <typename _T>
        struct q_real_ops
            : public d_real_ops<_T, d_real_traits<_T>::fma > {
            static
            void
            renormalize(_T& r0, _T& r1, _T& r2, _T& r3,
                        const _T& s0, const _T& s1,
                        const _T& s2, const _T& s3);
            static
            void
            renormalize(_T& r0, _T& r1, _T& r2, _T& r3,
                        const _T& s0, const _T& s1,
                        const _T& s2, const _T& s3,
                        const _T& s4);
        };
    }
}

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_Q_REAL_H__
