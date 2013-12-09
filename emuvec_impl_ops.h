#if !defined (__EMUVEC_IMPL_OPS_H__)
#define __EMUVEC_IMPL_OPS_H__ 1

#include <cftal/config.h>
#include <cftal/mul_div.h>
#include <cmath>

namespace emuvec {

        namespace impl {

                // operator functions
                template <typename _T, typename _OP>
                inline
                void v_bi_op(_T* r, const _T* s0, _OP op, const _T* s1,
                             std::size_t n) {
                        for (std::size_t i=0; i<n; ++i)
                                r[i] = op (s0[i] , s1[i]);
                }

                template <typename _T, typename _OP>
                inline
                void v_bi_op(_T* r, const _T* s0, const _OP& op,
                             std::size_t n) {
                        for (std::size_t i=0; i<n; ++i)
                                r[i] = op (s0[i]);
                }

                template <typename _T, typename _OP>
                void v_assign_op(_T* s0_r,
                                 _OP op, const _T* s1, std::size_t n) {
                        for (std::size_t i=0; i<n; ++i)
                                s0_r[i] = op (s0_r[i] , s1[i]);
                }

                template <typename _T, typename _OP>
                void v_assign_op(_T* s0_r, _OP op, std::size_t n) {
                        for (std::size_t i=0; i<n; ++i)
                                s0_r[i] = op (s0_r[i]);
                }

                template <typename _T, typename _OP>
                inline
                void v_un_op(_T* r, _OP op, const _T* s0,
                             std::size_t n) {
                        for (std::size_t i=0; i<n; ++i)
                                r[i] = op(s0[i]);
                }

                // operators:
                template <typename _T>
                class v_sl {
                        uint32_t _s;
                public:
                        v_sl(uint32_t s) : _s(s) {}
                        _T operator()(const _T& a) const {
                                return a << _s;
                        }
                };

                template <typename _T>
                class v_sr {
                        uint32_t _s;
                public:
                        v_sr(uint32_t s) : _s(s) {}
                        _T operator()(const _T& a) const {
                                return a >> _s;
                        }
                };

                template <typename _T>
                struct v_mulhi {
                        _T operator()(const _T& a, const _T& b) 
                                const {
                                return cftal::mul_lo_hi(a, b).second;
                        }
                };

#define UN_OP(op, v_name)                                       \
                template <typename _T>                          \
                struct v_name {                                 \
                        _T operator()(const _T& a) const {      \
                                return op;                      \
                        }                                       \
                }
#define BI_OP(op, v_name)                                               \
                template <typename _T>                                  \
                struct v_name {                                         \
                        _T operator()(const _T& a, const _T& b) const { \
                                return op;                              \
                        }                                               \
                };

                UN_OP(a!=_T(0) ? _T(-1) : _T(0), v_log_not);
                UN_OP(~a, v_not);
                UN_OP(a==_T(-1) ? _T(0) : _T(-1), v_f_not);
                UN_OP(-a, v_neg);
                UN_OP(a+_T(1), v_inc);
                UN_OP(a-_T(1), v_dec);
                UN_OP(a<_T(0) ? -a : a, v_abs);
                UN_OP(std::rint(a), v_rint);
                UN_OP(std::ceil(a), v_ceil);
                UN_OP(std::floor(a), v_floor);
                UN_OP(std::trunc(a), v_trunc);
                UN_OP(std::sqrt(a), v_sqrt);
                UN_OP(std::isinf(a) ? _T(-1) : _T(0) , v_isinf);
                UN_OP(std::isnan(a) ? _T(-1) : _T(0) , v_isnan);

                BI_OP(a^b, v_xor);
                BI_OP((a==_T(-1))^(b==_T(-1)) ? _T(-1) : _T(0),
                      v_f_xor);
                BI_OP(a|b, v_or);
                BI_OP(((a==_T(-1)) || (b==_T(-1)) ? _T(-1) : _T(0)),
                      v_f_or);
                BI_OP(a&b, v_and);
                BI_OP(((a==_T(-1)) && (b==_T(-1)) ? _T(-1) : _T(0)),
                      v_f_and);
                BI_OP(a+b, v_add);
                BI_OP(a-b, v_sub);
                BI_OP(a*b, v_mul);
                BI_OP(a/b, v_fdiv);
                BI_OP(b != 0 ? a/b : _T(-1), v_idiv);
                BI_OP(b != 0 ? a%b : a, v_irem);
                BI_OP(a<b, v_lt);
                BI_OP(a<=b, v_le);
                BI_OP(a==b, v_eq);
                BI_OP(a!=b, v_ne);
                BI_OP(a>=b, v_ge);
                BI_OP(a>b, v_gt);
                BI_OP(a>b ? a : b, v_max);
                BI_OP(a<b ? a : b, v_min);
                BI_OP(std::copysign(a, b), v_copysign);

#undef UN_OP
#undef BI_OP


                template <typename _T>
                struct v_div :
                        public std::conditional<
                        std::is_floating_point<_T>::value,
                        v_fdiv<_T>, v_idiv<_T> >::type {
                };

        }
}

// Local variables:
// mode: c++
// end:
#endif
