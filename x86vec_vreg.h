#if !defined (__X86VEC_VREG_H__)
#define __X86VEC_VREG_H__ 1

#include <x86vec_intrin.h>
#include <x86vec_select.h>
#include <x86vec_ins_ext.h>
#include <x86vec_perm.h>
#include <x86vec_load_store.h>

namespace x86vec {

        // wrapper around a vector register type
        template <class _X>
        class vreg {
                _X _v;
        public:
                typedef _X vector_type;
                typedef void element_type;
                vreg() = default;
                vreg(_X x);
		vreg& operator=(const vreg& r) = default;
                _X operator()() const;
                _X& operator()();
        };
}

template <class _X>
inline
x86vec::vreg<_X>::vreg(_X x) : _v(x)
{
}

template <class _X>
inline
_X x86vec::vreg<_X>::operator()() const
{
        return _v;
}

template <class _X>
inline
_X& x86vec::vreg<_X>::operator()()
{
        return _v;
}

// Local variables:
// mode: c++
// end:
#endif
