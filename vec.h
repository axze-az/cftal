#if !defined (__CFTAL_VEC_H__)
#define __CFTAL_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>
#include <cftal/init_list.h>
#include <cftal/constants.h>
#include <cftal/expr.h>
#include <cftal/mem.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_op.h>
#include <type_traits>
#include <cmath>

namespace cftal {

    template <class _M, class _T>
    _T select(const _M& m,
              const _T& on_true, const _T& on_false);
}

template <typename _M, typename _T>
inline
_T
cftal::select(const _M& m, const _T& on_true, const _T& on_false)
{
    return m ? on_true : on_false;
}

#include <cftal/vec_t_1.h>
#include <cftal/vec_double_n.h>
#include <cftal/vec_float_n.h>


// include vector specializations
#if defined (__SSE__)
#include <cftal/x86_v4f32.h>
#endif
#if defined (__SSE2__)
#include <cftal/x86_v4s32.h>
#include <cftal/x86_v4u32.h>
#include <cftal/x86_v4s32_inl.h>
#include <cftal/x86_v4u32_inl.h>
#if 0
#include <cftal/x86_v2s64.h>
#include <cftal/x86_v2u64.h>
#endif
#include <cftal/x86_v2f64.h>
#endif
#if defined (__AVX__)
#include <cftal/x86_v8f32.h>
#include <cftal/x86_v4f64.h>
#endif
#if defined (__AVX2__)
#if 0
#include <cftal/x86_v8s32.h>
#include <cftal/x86_v8u32.h>
#include <cftal/x86_v4s64.h>
#include <cftal/x86_v4u64.h>
#endif
#endif
#if defined (__AVX512__)
#if 0
#include <cftal/x86_v16f32.h>
#include <cftal/x86_v8f64.h>
#include <cftal/x86_v16s32.h>
#include <cftal/x86_v16u32.h>
#include <cftal/x86_v8s64.h>
#include <cftal/x86_v8u64.h>
#endif
#endif

#include <cftal/x86_cvt.h>

// Local variables:
// mode: c++
// end:
#endif
