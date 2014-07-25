#if !defined (__CFTAL_SVEC_H__)
#define __CFTAL_SVEC_H__ 1

#include <cftal/config.h>

namespace cftal {
        
        namespace simd {

                namespace impl {
        
                        template <typename _T, std::size_t _N>
                        struct hw_reg {
                                hw_reg<_T, _N/2> _l;
                                hw_reg<_T, _N/2> _h;
                        };
                        
                        template <typename _T>
                        struct hw_reg<_T, 1> {
                                _T _v;
                        };

                }
                
                template <typename _T, std::size_t _N>
                class vec {
                        vec() = default;
                        vec(const vec& r) = default;
                        vec(vec&& r) = default;
                        vec& operator=(const vec& r) = default;
                        vec& operator=(vec&& r) = default;
                private:
                        static_assert(0==(_N & _N-1), "_N is not a power of 2");
                        hw_reg<_T, _N> _v;
                };
                
        }
                
}

#endif
