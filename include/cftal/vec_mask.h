//
// Copyright Axel Zeuner 2010-2020. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_MASK_H__)
#define __CFTAL_VEC_MASK_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>
#include <cftal/vec_t_1.h>

namespace cftal {

    namespace impl {
        template <typename _T, std::size_t _N>
        class zero_mask {
            vec<_T, _N>* _v;
            typename vec<_T, _N>::mask_type _m;
        public:
            zero_mask(vec<_T, _N>& v,
                      const typename vec<_T, _N>::mask_type& m)
                : _v(&v), _m(m) {};
            vec<_T, _N>& operator=(const vec<_T, _N>& r) const {
                const vec<_T, _N> zz(_T(0));
                *_v = select(_m, r, zz);
                return *_v;
            }
            template <class _R>
            vec<_T, _N>& operator=(const _R& r) const {
                vec<_T, _N> rr(r);
                const vec<_T, _N> zz(_T(0));
                *_v = select(_m, rr, zz);
                return *_v;
            }
        };

        template <typename _T, std::size_t _N>
        class merge_mask {
            vec<_T, _N>* _v;
            typename vec<_T, _N>::mask_type _m;
        public:
            merge_mask(vec<_T, _N>& v,
                       const typename vec<_T, _N>::mask_type& m)
                : _v(&v), _m(m) {};
            vec<_T, _N>& operator=(const vec<_T, _N>& r) const {
                *_v = select(_m, r, *_v);
                return *_v;
            }
            template <class _R>
            vec<_T, _N>& operator=(const _R& r) const {
                vec<_T, _N> rr(r);
                *_v = select(_m, rr, *_v);
                return *_v;
            }
        };


        template <class _T, std::size_t _N>
        class keep_result {
            vec<_T, _N>* _v;
        public:
            keep_result(vec<_T, _N>& v) : _v(&v) {}
            struct proxy {
                const merge_mask<_T, _N> with;
                proxy(vec<_T, _N>& v,
                      const typename vec<_T, _N>::mask_type& m)
                    : with(v, m) {}
            };
            proxy
            update_if(const typename vec<_T, _N>::mask_type& m) const {
                return proxy(*_v, m);
            }
        };


        template <class _T, std::size_t _N>
        class zero_result {
            vec<_T, _N>* _v;
        public:
            zero_result(vec<_T, _N>& v) : _v(&v) {}
            struct proxy {
                const zero_mask<_T, _N> with;
                proxy(vec<_T, _N>& v,
                      const typename vec<_T, _N>::mask_type& m)
                    : with(v, m) {}
            };
            proxy
            update_if(const typename vec<_T, _N>::mask_type& m) const {
                return proxy(*_v, m);
            }
        };

    } // namespace impl


    template <class _T, std::size_t _N>
    impl::keep_result<_T, _N>
    keep(vec<_T, _N>& v)
    {
        return impl::keep_result<_T, _N>(v);
    }

    template <class _T, std::size_t _N>
    impl::zero_result<_T, _N>
    zero(vec<_T, _N>& v)
    {
        return impl::zero_result<_T, _N>(v);
    }

    // usage information:
    // zero(r).update_if(a_gt_b).with = a + b * b * b + a;
    // keep(r).update_if(a_gt_b).with = a + b * b * b + a;

}

// local variables:
// mode: c++
// end:
#endif
