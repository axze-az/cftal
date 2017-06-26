//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_MATH_IMPL_ESTRIN_H__)
#define __CFTAL_MATH_IMPL_ESTRIN_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <stdexcept>
#include <iterator>

namespace cftal {
    namespace math {
        namespace impl {

            template <typename _X,
                      typename _C1, typename _C0>
            _X
            estrin_1(_X x, _C1 c1, _C0 c0) {
                return (x*c1) + c0;
            }

            template <typename _X,
                      typename _C1, typename _C0>
            _X
            estrin(_X x, _C1 c1, _C0 c0) {
                return estrin_1(x, c1, c0);
            }

            template <typename _X,
                      typename _C2, typename _C1, typename _C0>
            _X
            estrin_2(_X x, _X x2, _C2 c2, _C1 c1, _C0 c0) {
                _X t1 = estrin_1(x, c1, c0);
                return t1 + x2*c2;
            }

            template <typename _X,
                      typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x, _C2 c2, _C1 c1, _C0 c0) {
                _X x2 = x*x;
                return estrin_2(x, x2, c2, c1, c0);
            }

            template <typename _X,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_3(_X x, _X x2, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_1(x, c1, c0) , t2=estrin_1(x, c3, c2);
                return t1 + x2* t2;
            }

            template <typename _X,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                return estrin_3(x, x2, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_4(_X x, _X x2, _X x4,
                     _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t=estrin_3(x, x2, c3, c2, c1, c0);
                return t + c4*x4;
            }

            template <typename _X,
                      typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                return estrin_4(x, x2, x4, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_5(_X x, _X x2, _X x4,
                     _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_1(x, c5, c4);
                return t1 + t2*x4;
            }

            template <typename _X,
                      typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2=x*x;
                _X x4=x2*x2;
                return estrin_5(x, x2, x4, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_6(_X x, _X x2, _X x4,
                     _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_2(x, x2, c6, c5, c4);
                return t1 + t2*x4;
            }

            template <typename _X,
                      typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                return estrin_6(x, x2, x4, c6, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_7(_X x, _X x2, _X x4,
                     _C7 c7,
                     _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_3(x, x2, c7, c6, c5, c4);
                return t1 + t2*x4;
            }

            template <typename _X,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C7 c7,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                return estrin_7(x, x2, x4, c7, c6, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_8(_X x, _X x2, _X x4, _X x8,
                     _C8 c8, _C7 c7,
                     _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_3(x, x2, c7, c6, c5, c4);
                _X t3= t1 + t2* x4;
                return t3 + c8*x8;
            }

            template <typename _X,
                      typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C8 c8, _C7 c7,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                _X x8= x4*x4;
                return estrin_8(x, x2, x4, x8,
                                c8, c7, c6, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_9(_X x, _X x2, _X x4, _X x8,
                     _C9 c9, _C8 c8, _C7 c7,
                     _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_3(x, x2, c7, c6, c5, c4);
                _X t3= t1 + t2* x4;
                _X t4= estrin_1(x, c9, c8);
                return t3 + t4*x8;
            }

            template <typename _X,
                      typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C9 c9, _C8 c8, _C7 c7,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                _X x8= x4*x4;
                return estrin_9(x, x2, x4, x8,
                                c9, c8, c7, c6, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C10, typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_10(_X x, _X x2, _X x4, _X x8,
                      _C10 c10, _C9 c9, _C8 c8, _C7 c7,
                      _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_3(x, x2, c7, c6, c5, c4);
                _X t3= t1 + t2* x4;
                _X t4= estrin_2(x, x2, c10, c9, c8);
                return t3 + t4*x8;
            }

            template <typename _X,
                      typename _C10, typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C10 c10, _C9 c9, _C8 c8, _C7 c7,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                _X x8= x4*x4;
                return estrin_10(x, x2, x4, x8,
                                 c10,
                                 c9, c8, c7, c6, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C11, typename _C10, typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_11(_X x, _X x2, _X x4, _X x8,
                      _C11 c11, _C10 c10, _C9 c9, _C8 c8, _C7 c7,
                      _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1= estrin_3(x, x2, c3, c2, c1, c0);
                _X t2= estrin_3(x, x2, c7, c6, c5, c4);
                _X t3= t1 + t2* x4;
                _X t4= estrin_3(x, x2, c11, c10, c9, c8);
                return t3 + t4*x8;
            }

            template <typename _X,
                      typename _C11, typename _C10, typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C11 c11, _C10 c10, _C9 c9, _C8 c8, _C7 c7,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                _X x8= x4*x4;
                return estrin_11(x, x2, x4, x8,
                                 c11, c10,
                                 c9, c8, c7, c6, c5, c4, c3, c2, c1, c0);
            }

            template <typename _X,
                      typename _C12,
                      typename _C11, typename _C10, typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin_12(_X x, _X x2, _X x4, _X x8,
                      _C12 c12,
                      _C11 c11, _C10 c10, _C9 c9, _C8 c8, _C7 c7,
                      _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X t1=estrin_3(x, x2, c3, c2, c1, c0);
                _X t2=estrin_3(x, x2, c7, c6, c5, c4);
                _X t3=t1+t2*x4;
                _X t4=estrin_4(x, x2, x4, c12, c11, c10, c9, c8);
                return t3 + t4* x8;
            }

            template <typename _X,
                      typename _C12,
                      typename _C11, typename _C10, typename _C9, typename _C8,
                      typename _C7, typename _C6, typename _C5, typename _C4,
                      typename _C3, typename _C2, typename _C1, typename _C0>
            _X
            estrin(_X x,
                   _C12 c12,
                   _C11 c11, _C10 c10, _C9 c9, _C8 c8, _C7 c7,
                   _C6 c6, _C5 c5, _C4 c4, _C3 c3, _C2 c2, _C1 c1, _C0 c0) {
                _X x2= x*x;
                _X x4= x2*x2;
                _X x8= x4*x4;
                return estrin_12(x, x2, x4, x8,
                                 c12, c11, c10,
                                 c9, c8, c7, c6, c5, c4, c3, c2, c1, c0);
            }

        }
    }
}

// local variables:
// mode: c++
// end:
#endif

