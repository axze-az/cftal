#if !defined (__CFTAL_VEC_DOUBLE_N_H__)
#define __CFTAL_VEC_DOUBLE_N_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/d_real.h>
#include <cmath>

namespace cftal {

    template <std::size_t _N>
    vec<double, _N>
    abs(const vec<double, _N>& v);
    
    template <std::size_t _N>
    typename vec<double, _N>::mask_type
    isinf(const vec<double, _N>& v);

    template <std::size_t _N>
    typename vec<double, _N>::mask_type
    isnan(const vec<double, _N>& v);

    template <std::size_t _N>
    typename vec<double, _N>::mask_type
    isfinite(const vec<double, _N>& v);

    namespace impl {
        // TODO: fma implementations
    }  
}

template <std::size_t _N>
cftal::vec<double, _N>
cftal::abs(const vec<double, _N>& v)
{
    const vec<double, _N> msk(not_sign_f64_msk::v._f64);
    return v & msk;
}

template <std::size_t _N>
inline
typename cftal::vec<double, _N>::mask_type
cftal::isnan(const vec<double, _N>& x)
{
    // exponent = 0x7FF and significand !=0
    // x != x  if x == NAN
    return x != x;
}

template <std::size_t _N>
inline
typename cftal::vec<double, _N>::mask_type
cftal::isinf(const vec<double, _N>& x)
{
    vec<double, _N> absx(abs(x));
    const vec<double, _N> vm(exp_f64_msk::v._f64);
    return absx == vm;
}

template <std::size_t _N>
inline
typename cftal::vec<double, _N>::mask_type
cftal::isfinite(const vec<double, _N>& x)
{
    return ~(isinf(x) | isnan(x));
}


// local variables:
// mode: c++
// end:
#endif
