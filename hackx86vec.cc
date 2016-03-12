#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/d_real.h>
#include <cftal/vec_traits.h>

namespace cftal {

    namespace impl {

        template <typename _T, std::size_t _N, typename _X, std::size_t _L>
        struct lookup {
            // lookup with default value
            static
            vec<_T, _N>
            v(const vec<_T, _N>& def, const vec<int32_t, _N>& idx, const _X* p);
        };
        
        template <typename _T, std::size_t _N, typename _X>
        struct lookup<_T, _N, _X, 0> {
            // lookup with default value
            static
            vec<_T, _N>
            v(const vec<_T, _N>& def, const vec<int32_t, _N>& idx, const _X* p);
        };

    }

    // lookup with default value
    template <typename _T, std::size_t _N, typename _X, std::size_t _L>
    vec<_T, _N>
    lookup(const vec<_T, _N>& def, const vec<int32_t, _N>& idx, const _X (&r)[_L]);
}

    
template <typename _T, std::size_t _N, typename _X>
cftal::vec<_T, _N>
cftal::impl::lookup<_T, _N, _X, 0>::
v(const vec<_T, _N>& def, const vec<int32_t, _N>& idx, const _X* p)
{
    typename vec<int32_t, _N>::mask_type idx_eq_0 = idx == vec<int32_t, _N>(0);
    typename vec<_T, _N>::mask_type f_idx_eq_0=
        cvt_mask<typename vec<_T, _N>::mask_type::value_type,
                 typename vec<int32_t, _N>::mask_type::value_type, _N>::v(idx_eq_0);
    vec<_T, _N> r_idx_eq_0(p[0]);
    vec<_T, _N> r = select(f_idx_eq_0, r_idx_eq_0, def);
    return r;
}

template <typename _T, std::size_t _N, typename _X, std::size_t _L>
cftal::vec<_T, _N>
cftal::impl::lookup<_T, _N, _X, _L>::
v(const vec<_T, _N>& def, const vec<int32_t, _N>& idx, const _X* p)
{
    const std::size_t _LM1= _L -1;
    // lookup all lower values to zero:
    vec<_T, _N> rl= lookup<_T, _N, _X, _LM1>::v(def, idx, p);
    typename vec<int32_t, _N>::mask_type idx_eq_l = idx == vec<int32_t, _N>(_L);
    typename vec<_T, _N>::mask_type f_idx_eq_l=
        cvt_mask<typename vec<_T, _N>::mask_type::value_type,
                 typename vec<int32_t, _N>::mask_type::value_type, _N>::v(idx_eq_l);
    vec<_T, _N> r_idx_eq_l(p[_L]);
    vec<_T, _N> r= select(f_idx_eq_l, r_idx_eq_l, rl);
    return r;
}

template <typename _T, std::size_t _N, typename _X, std::size_t _L>
cftal::vec<_T, _N>
cftal::lookup(const vec<_T, _N>& def, const vec<int32_t, _N>& idx, const _X (&p)[_L])
{
    return impl::lookup<_T, _N, _X, _L-1>::v(def, idx, p);
}

cftal::vec<double, 4>
test_lookup(cftal::vec<int32_t, 4> idx)
{
    using namespace cftal;
    const double values[]= {0.0, 1.0, 2.0, 3.0};
    v4f64 t(-1.0);
    v4f64 l=lookup(t, idx, values);
    return l;
}

cftal::vec<double, 1>
test_lookup(cftal::vec<int32_t, 1> idx)
{
    using namespace cftal;
    const double values[]= {0.0, 1.0, 2.0, 3.0};
    v1f64 t(-1.0);
    v1f64 l=lookup(t, idx, values);
    return l;
}


int main(int argc, char** argv)
{   
    using namespace cftal;
#if 1
    const double values[]= {0.0, 1.0, 2.0, 3.0};
    v4f64 t(-1.0);
    v4s32 idx{3, 2, 1, 0};
    v4f64 l=lookup(t, idx, values);
    std::cout << std::hexfloat << std::endl;
    std::cout << t << std::endl;
    std::cout << idx << std::endl;
    std::cout << l << std::endl;

#else
    std::cout << std::hex;
    double t=0x1p51-1.0;
    std::cout << bytes8(t)._u64 << std::endl;
    double t1=t+0x1p52+0x1p51;
    std::cout << bytes8(t1)._u64 << std::endl;
    std::cout << bytes8(t1)._u32[0] << std::endl;
    double t2=-t+0x1p52+0x1p51;
    std::cout << bytes8(t2)._u64 << std::endl;
    std::cout << bytes8(t2)._u32[0] << std::endl;
    
    
    // v1f32 r=ldexp(v1f32(0x1.2352cf807b7dfp-503), v1s32(-1076));
    // double rd=std::ldexp(0x1.2352cf807b7dfp-503, -1076);
    // v1f32 r=ldexp(v1f32(0x1.a2e184p-127f), v1s32(-22));
    // float rd=std::ldexp(0x1.a2e184p-127f, -22);
    v1f32 r=ldexp(v1f32(0x1.0p-127f), v1s32(-1));
    float rd=std::ldexp(0x1.0p-127f, -1);
    // v1f64 r=ldexp(v1f64(0x1.a2e184p-1023), v1s32(+1023-1075));
    // double rd=std::ldexp(0x1.a2e184p-1023, +1023-1075);
    std::cout << std::setprecision(22);
    std::cout << std::hexfloat << r << std::endl;
    std::cout << std::hexfloat << rd << std::endl;
    // std::cout << std::numeric_limits<double>::min() << std::endl;
    // std::cout << std::sqrt(std::numeric_limits<double>::min()) << std::endl;
#endif    
    return 0;
}
