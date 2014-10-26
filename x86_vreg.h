#if !defined (__CFTAL_X86_VREG_H__)
#define __CFTAL_X86_VREG_H__ 1

#include <cftal/config.h>

namespace cftal {

        namespace x86vec {

                template <typename _T>
                struct arg { typedef _T type; };

                // wrapper around a vector register type
                template <class _R>
                class vreg {
                        _R _v;
                public:
                        typedef _X vector_type;
                        typedef void element_type;
                        vreg() = default;
                        vreg(const vreg& r) = default;
                        vreg(vreg&& r) = default;
                        vreg& operator=(const vreg& r) = default;
                        vreg& operator=(vreg&& r) = default;
                        constexpr vreg(_X x);
                        _X operator()() const;
                        _X& operator()();
                };
        }
}

template <class _X>
inline
constexpr
cftal::x86::vreg<_X>::vreg(_X x) : _v(x)
{
}

template <class _X>
inline
_X cftal::x86::vreg<_X>::operator()() const
{
        return _v;
}

template <class _X>
inline
_X& cftal::x86::vreg<_X>::operator()()
{
        return _v;
}

// Local variables:
// mode: c++
// end:
#endif
