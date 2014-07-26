#if !defined (__CFTAL_SVEC_H__)
#define __CFTAL_SVEC_H__ 1

#include <cftal/config.h>

namespace cftal {
        
        namespace simd {

                namespace impl {
        
                        // abstraction of an emulated hardware
                        // register _T[_N] splitable into to two
                        // halves
                        template <typename _T, std::size_t _N>
                        struct hw_reg {
                                static_assert(0==(_N & _N-1), 
                                              "_N is not a power of 2");
                                using half_type = hw_reg<_T, _N/2>;
                                half_type _l;
                                half_type _h;
                                hw_reg(half_type l, half_type h) 
                                        : _l(l), _h(h) {} 
                                hw_reg(const _T& t) 
                                        : _l(t), _h(t) {}
                        };

                        // return the lower half of a hw_reg<_T, _N>
                        template <typename _T, std::size_t _N>
                        hw_reg<_T, _N/2> lhalf(const hw_reg<_T, _N>& v) {
                                return v._l;
                        }

                        // return the higher half of a hw_reg<_T, _N>
                        template <typename _T, std::size_t _N>
                        hw_reg<_T, _N/2> hhalf(const hw_reg<_T, _N>& v) {
                                return v._h;
                        }
                        
                        // specialization for a scalar register
                        template <typename _T>
                        struct hw_reg<_T, 1> {
                                _T _v;
                                hw_reg(const _T& t) : _v(t) {}
                        };

                        template <typename _T, std::size_t _N>
                        class op_add {
                                using full_type = hw_reg<_T, _N>;

                                static 
                                full_type 
                                v(const full_type& a, const full_type& b) {
                                        return full_type( 
                                                op_add<_T, _N/2>::v(lhalf(a), 
                                                                    lhalf(b)),
                                                op_add<_T, _N/2>::v(hhalf(a), 
                                                                    hhalf(b)));
                                }
                        };

                        template <typename _T>
                        class op_add<_T, 1> {
                                using full_type = hw_reg<_T, 1>;
                                
                                static
                                full_type
                                v(const full_type& a, const full_type& b) {
                                        return full_type<_T, _N>(
                                                lhalf(a) + lhalf(b),
                                                hhalf(a) + hhalf(b));
                                }
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
// Local variables:
// mode: c++
// end:
#endif
