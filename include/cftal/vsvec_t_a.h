//
// Copyright (C) 2010-2024 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_VSVEC_T_A_H__)
#define __CFTAL_VSVEC_T_A_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/expr.h>
#include <cftal/aligned_allocator.h>
#include <sstream>

namespace cftal {

    // a long vector of _T
    template <typename _T, typename _A=aligned_allocator<_T, 64> >
    class vsvec : private _A {
        using _A_traits= std::allocator_traits<_A>;
        enum {
            // short vector optimization for this number of
            // elements
            _SVOPT = sizeof(void*)/sizeof(_T)
        };
        union data_ptr {
            _T* __restrict _d;
            char _buf[sizeof(_T*)];
            data_ptr(_T* p=nullptr) : _d(p) {}
        };
        // element count
        size_t _n;
        // data pointer or space for up to _SVOPT elements
        data_ptr _dta;
        // is this object short, i.e. is buf used as space for
        // vector elements
        bool _is_short() const;
        // return the short element pointer
        _T* _short_elem_ptr();
        // return the constant short element pointer
        const _T* _short_elem_ptr() const;
        // return the long element pointer
        _T* _long_elem_ptr();
        // return the constant long element pointer
        const _T* _long_elem_ptr() const;
        // return a pointer to the elements
        _T* _elem_ptr();
        // return a constant pointer to the elements
        const _T* _elem_ptr() const;
        // allocate p[0,n)
        void _alloc(size_t n);
        // deallocate p[0,alloc)
        void _free();
        // destruct p[0,n) and deallocate p[0,_n)
        void _destroy_and_free(size_t n);
        // allocate p[0,n) and construct p[i] using s[i]
        void _alloc_and_construct(size_t n, const _T* s);
        // allocate p[0,n) and construct p[i] using s[i]
        template <typename _ITER>
        void _alloc_and_construct(size_t n, _ITER s);
        // allocate p[0,n) and construct p[i] using s
        void _alloc_and_construct(size_t n, const _T& s);
        // swap r._n, r._dta with _n, _d
        // assumes &r != this
        vsvec& _swap(vsvec& r);
        // assignment from expression template with size _N
        // at offset i_src, returns number of elements stored at
        // offset i_dst
        template <std::size_t _N,
                  typename _O, typename _AR,
                  template <class _U> class _OP,
                  class _L, class _R>
        size_t
        _assign(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r,
                size_t i_src, size_t i_dst);

        // assignment from expression template using source size n
        // the destination size is already stored in member _n
        template <typename _O, typename _AR,
                  template <class _U> class _OP,
                  class _L, class _R>
        void
        _assign(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r, size_t n);
    public:
        // element type
        using value_type = _T;
        // value type of comparison operation result type
        using mask_value_type = typename vec<_T, 1>::mask_value_type;
        // result type of comparison operations
        using mask_type =
            vsvec<mask_value_type,
                 typename std::allocator_traits<_A>::template
                 rebind_alloc<mask_value_type> >;
        // default constructor: size() == 0
        vsvec();
        // destructor
        ~vsvec();
        // copy construction
        vsvec(const vsvec& r);
        // copy construction
        template <typename _AR>
        vsvec(const vsvec<_T, _AR>& r);
        // move construction
        vsvec(vsvec&& r);
        // copy assignment
        vsvec& operator=(const vsvec& r);
        // copy assignment
        template <typename _AR>
        vsvec& operator=(const vsvec<_T, _AR>& r);
        // copy assignment of a scalar, may change the size
        // of the vector to 1
        vsvec& operator=(const _T& r);
        // move assignment
        vsvec& operator=(vsvec&& r);
        // initialize all n elements with r
        vsvec(const _T& r, size_t n=1);
        // initialize l.size() elements with l
        vsvec(std::initializer_list<_T> l);
        // constructor from range
        template <typename _ITER>
        vsvec(_ITER b, _ITER e, std::true_type);
        template <typename _ITER>
        vsvec(_ITER b, _ITER e, std::false_type);
        template <typename _ITER>
        vsvec(_ITER b, _ITER e);
        // construction from expression template
        template <typename _O, typename _AR,
                  template <class _U> class _OP,
                  class _L, class _R>
        vsvec(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r);
        // assignment from expression template
        template <typename _O, typename _AR,
                  template <class _U> class _OP,
                  class _L, class _R>
        vsvec&
        operator=(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r);
        // const iterator
        using const_iterator = const _T*;
        // iterator
        using iterator=_T*;
        // size, changes only after assignment
        size_t size() const;
        // const begin
        const_iterator begin() const;
        // const end
        const_iterator end() const;
        // const begin
        const_iterator cbegin() const;
        // const end
        const_iterator cend() const;
        // begin
        iterator begin();
        // end
        iterator end();
        // swap values with r
        void
        swap(vsvec& r);
        // r/w access operator
        _T& operator[](size_t i);
        // rp access operator
        const _T& operator[](size_t i) const;
    private:
        // return pointer to vec<_T, _N> at pos i
        template <size_t _N>
        const vec<_T, _N>* loadp(size_t i) const;
        // return pointer to vec<_T, _N> at pos i
        template <size_t _N>
        vec<_T, _N>* storep(size_t i);
    public:
        // load vec<_T, _N> from pos i
        template <size_t _N>
        vec<_T, _N> loadv(size_t i) const;
        // store vec<_T, _N> at pos i, return the number of elements
        // written
        template <size_t _N>
        size_t
        storev(size_t i, const vec<_T, _N>& v);

        // inspect all elements of this
        template <typename _C>
        void
        inspect(_C& c)
            const;
    };

    template <typename _T, typename _A>
    std::ostream& operator<<(std::ostream& s, const vsvec<_T, _A>& v);

    using vxs8 = vsvec<int8_t>;
    using vxu8 = vsvec<uint8_t>;
    using vxu16 = vsvec<uint16_t>;
    using vxs16 = vsvec<int16_t>;
    using vxu32 = vsvec<uint32_t>;
    using vxs32 = vsvec<int32_t>;
    using vxu64 = vsvec<uint64_t>;
    using vxs64 = vsvec<int64_t>;
    using vxf32 = vsvec<float>;
    using vxf64 = vsvec<double>;

    template <typename _T, typename _A>
    struct expr_traits<vsvec<_T, _A> > {
        using type = const vsvec<_T, _A>&;
    };

    // evaluation of the maximum size of expressions
    template <typename _T>
    inline
    size_t eval_size(const _T&) {
        return 1;
    }

    template <typename _T, typename _A>
    inline
    size_t eval_size(const vsvec<_T, _A>& v) {
        return v.size();
    }

    template <typename _T, typename _A,
              template <class _U> class _OP,
              class _L, class _R>
    inline
    size_t eval_size(const expr<_OP<vsvec<_T, _A>>, _L, _R>& e) {
        size_t l= eval_size(e._l);
        size_t r= eval_size(e._r);
#if defined (_DEBUG)
        if ((l != r) && ((l != 1) && (r != 1))) {
            throw std::logical_error("invalid sizes");
        }
#endif
        return std::max(l, r);
    }

    template <typename _T, typename _A,
              template <class _U> class _OP,
              class _L>
    inline
    size_t eval_size(const expr<_OP<vsvec<_T, _A>>, _L, void>& e) {
        size_t l= eval_size(e._l);
        return l;
    }

    // evaluation of the result size of expressions, normally
    // this function returns eval_size
    template <typename _T>
    inline
    size_t eval_result_size(const _T& t) {
        return eval_size(t);
    }

    // compile time evaluation of the size of the result
    // compared to the size of the arguments i.e.
    // comparison of eval_size and eval_result_size
    enum class result_size {
        lt_size,
        eq_size,
        gt_size
    };

    // evaluation of the number of operands of an expression and
    // of the result size of an expression compared to the input size
    template <typename _T>
    struct operand {
        static
        constexpr
        size_t count() {
            return 1;
        }
        static
        constexpr
        result_size sizes() {
            return result_size::eq_size;
        }
    };

    template <>
    struct operand<void> {
        static
        constexpr
        size_t count() {
            return 0;
        }
        static
        constexpr
        result_size sizes() {
            return result_size::eq_size;
        }
    };

    template <typename _T, typename _A,
              template <class _U, class _UA> class _OP,
              class _L, class _R>
    struct operand<expr<_OP<_T, _A>, _L, _R> > {
        static
        constexpr
        size_t count() {
            return operand<_L>::count() + operand<_R>::count();
        }
        static
        constexpr
        result_size sizes() {
            return result_size::eq_size;
        }
    };

    // evaluation of the i-th component of expressions
    template <size_t _N, typename _T>
    inline
    const _T&
    eval_i(const _T& v, size_t) {
        return v;
    }

    template <size_t _N, typename _T, typename _A>
    inline
    vec<_T, _N>
    eval_i(const vsvec<_T, _A>& v, size_t i) {
        const size_t vs=size(v);
        if (__unlikely(vs < i + _N)) {
            // Allow vectors of size 1 to behave like scalars. This
            // allows construction of vectors without explicit size.
            if (__likely(vs == 1)) {
                const _T& v0=v[0];
                return vec<_T, _N>(v0);
            }
            // determine the best condition here
            if (((i % vs) != 0)) {
                std::ostringstream s;
                s << "oops\n";
                s << "i= " << i << " N=" << _N << '\n';
                s << v << '\n';
                throw std::runtime_error(s.str());
            }
            // Allow vectors with sizes less than _N to expand their values
            _T vi[_N];
            const size_t vsmax=_N < vs ? _N : vs;
            for (size_t j = 0; j<_N; j+= vs) {
                for (size_t k=0; k<vsmax; ++k) {
                    vi[j+k]=v[k];
                }
            }
            return mem<vec<_T, _N> >::load(vi, _N);
        }
        return v.template loadv<_N>(i);
    }

    template <size_t _N,
              typename _T, typename _A,
              template <class _U> class _OP,
              class _L, class _R>
    inline
    vec<_T, _N>
    eval_i(const expr<_OP<vsvec<_T, _A>>, _L, _R>& e, size_t i) {
        return _OP<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i),
                                    eval_i<_N, _T>(e._r, i));
    }

    template <size_t _N,
              typename _T, typename _A,
              template <class _U> class _OP,
              class _L>
    inline
    vec<_T, _N>
    eval_i(const expr<_OP<vsvec<_T, _A>>, _L, void>& e, size_t i) {
        return _OP<vsvec<_T, _A>>::v(eval_i<_N, _T>(e._l, i));
    }
}

template <typename _T, typename _A>
inline
bool
cftal::vsvec<_T, _A>::vsvec::
_is_short()
    const
{
    if constexpr (_SVOPT == 1)
        return _n == _SVOPT;
    if constexpr (_SVOPT == 0)
        return false;
    return _n && _n <= _SVOPT;
}

template <typename _T, typename _A>
inline
_T*
cftal::vsvec<_T, _A>::vsvec::
_short_elem_ptr()
{
    return reinterpret_cast<_T*>(_dta._buf);
}

template <typename _T, typename _A>
inline
const _T*
cftal::vsvec<_T, _A>::vsvec::
_short_elem_ptr()
    const
{
    return reinterpret_cast<const _T*>(_dta._buf);
}

template <typename _T, typename _A>
inline
_T*
cftal::vsvec<_T, _A>::vsvec::
_long_elem_ptr()
{
    return _dta._d;
}

template <typename _T, typename _A>
inline
const _T*
cftal::vsvec<_T, _A>::vsvec::
_long_elem_ptr()
    const
{
    return _dta._d;
}

template <typename _T, typename _A>
inline
_T*
cftal::vsvec<_T, _A>::vsvec::
_elem_ptr()
{
    if (_is_short())
        return _short_elem_ptr();
    return _long_elem_ptr();
}

template <typename _T, typename _A>
inline
const _T*
cftal::vsvec<_T, _A>::vsvec::
_elem_ptr()
    const
{
    if (_is_short())
        return _short_elem_ptr();
    return _long_elem_ptr();
}

template <typename _T, typename _A>
void
cftal::vsvec<_T, _A>::vsvec::
_alloc(size_t n)
{
    if (n <= _SVOPT)
        return;
    _dta._d=_A_traits::allocate(*this, n);
}

template <typename _T, typename _A>
void
cftal::vsvec<_T, _A>::
_free()
{
    if (_n>_SVOPT) {
        _A_traits::deallocate(*this, _dta._d, _n);
    }
}

template <typename _T, typename _A>
void
cftal::vsvec<_T, _A>::
_destroy_and_free(size_t n)
{
    _T* p=_elem_ptr();
    for (size_t i=0; i<n; ++i) {
        _A_traits::destroy(*this, p+i);
    }
    _free();
}

template <typename _T, typename _A>
void
cftal::vsvec<_T, _A>::vsvec::
_alloc_and_construct(size_t n, const _T* s)
{
    _alloc(n);
    size_t i=0;
    try {
        _T* p=_elem_ptr();
        while (i<n) {
            _A_traits::construct(*this, p+i, s[i]);
            ++i;
        }
    }
    catch (...) {
        _destroy_and_free(i);
        throw;
    }
}

template <typename _T, typename _A>
template <typename _ITER>
void
cftal::vsvec<_T, _A>::vsvec::
_alloc_and_construct(size_t n, _ITER s)
{
    _alloc(n);
    size_t i=0;
    try {
        _T* p=_elem_ptr();
        while (i<n) {
            _A_traits::construct(*this, p+i, *s);
            ++s;
            ++i;
        }
    }
    catch (...) {
        _destroy_and_free(i);
        throw;
    }
}

template <typename _T, typename _A>
void
cftal::vsvec<_T, _A>::vsvec::
_alloc_and_construct(size_t n, const _T& s)
{
    _alloc(_n);
    size_t i=0;
    try {
        _T* p=_elem_ptr();
        while (i<n) {
            _A_traits::construct(*this, p+i, s);
            ++i;
        }
    }
    catch (...) {
        _destroy_and_free(i);
        throw;
    }
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>&
cftal::vsvec<_T, _A>::_swap(vsvec& r)
{
    if (!std::is_empty_v<_A>) {
        // non empty allocator:
        _A& ta=*this;
        _A& ra=r;
        std::swap(ta, ra);
    }
    bool is_short =  _n < _SVOPT;
    bool r_is_short = r._n < _SVOPT;
    if (is_short && r_is_short) {
        _T* p= _short_elem_ptr();
        _T* rp= r._short_elem_ptr();
        size_t swap_max=std::min(_n, r._n);
        for (size_t i=0; i<swap_max; ++i) {
            std::swap(p[i], rp[i]);
        }
        if (r._n > _n) {
            // move data elements from r to this
            // and destroy it
            for (size_t i=swap_max; i<r._n; ++i) {
                // new(p+i) _T(std::move(rp[i]));
                // rp[i].~_T();
                _A_traits::construct(*this, p+i, std::move(rp[i]));
                _A_traits::destroy(r, rp+i);
            }
        } else if ( r._n < _n) {
            // move data elements from this to r
            // and destroy it
            for (size_t i=swap_max; i<r._n; ++i) {
                // new(rp+i) _T(std::move(p[i]));
                // p[i].~_T();
                _A_traits::construct(r, rp+i, std::move(p[i]));
                _A_traits::destroy(*this, p+i);
            }
        }
    } else if (is_short) {
        _T* new_d= r._long_elem_ptr();
        _T* sp= _short_elem_ptr();
        _T* dp= r._short_elem_ptr();
        // move this short data elements to r
        // destroy data elements of this
        for (size_t i=0; i<_n; ++i) {
            // new(dp+i) _T(std::move(sp[i]));
            // sp[i].~_T();
            _A_traits::construct(r, dp+i, std::move(sp[i]));
            _A_traits::destroy(*this, sp+i);
        }
        _dta._d = new_d;
    } else if (r_is_short) {
        _T* r_new_d= _long_elem_ptr();
        _T* sp= r._short_elem_ptr();
        _T* dp= _short_elem_ptr();
        // move r short data elements to this
        // destroy data elements of r
        for (size_t i=0; i<r._n; ++i) {
            // new(dp+i) _T(std::move(sp[i]));
            // sp[i].~_T();
            _A_traits::construct(*this, dp+i, std::move(sp[i]));
            _A_traits::destroy(r, sp+i);
        }
        r._dta._d = r_new_d;
    } else {
        // both vectors are long
        std::swap(_dta._d, r._dta._d);
    }
    std::swap(_n, r._n);
    return *this;
}

template <typename _T, typename _A>
template <std::size_t _N,
          typename _O, typename _AR,
          template <class _U> class _OP,
          typename _L, typename _R>
inline
cftal::size_t
cftal::vsvec<_T, _A>::
_assign(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r, size_t i_src, size_t i_dst)
{
    auto v = eval_i<_N, _T>(r, i_src);
    size_t n= storev(i_dst, v);
    return n;
}

template <typename _T, typename _A>
template <typename _O,  typename _AR,
          template <class _U> class _OP,
          typename _L, typename _R>
__attribute__((__flatten__, __noinline__))
void
cftal::vsvec<_T, _A>::
_assign(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r, size_t n)
{
    constexpr
    const size_t _VEC_LEN=max_vec_size_specialized<_T>();

    using operand_t= operand< expr<_OP<vsvec<_O, _AR>>, _L, _R> >;

    constexpr
    const size_t _OP_CNT=operand_t::count();
    constexpr
    const result_size rsz=operand_t::sizes();
    constexpr
    const size_t _MAX_VEC_LEN= (rsz == result_size::gt_size) ? 32 : 64;
    constexpr
    const size_t _MIN_VEC_LEN= (rsz == result_size::lt_size) ? 2 : 1;
    constexpr
    const size_t _M0= _VEC_LEN * (
        _OP_CNT >= 8 ? 1 : _OP_CNT >= 4 ? 2 : 4);
    constexpr
    const size_t _M = _M0 > _MAX_VEC_LEN ? _MAX_VEC_LEN : _M0;

    constexpr
    const size_t _MM1= _M-1;
    size_t i_src=0;
    size_t i_dst=0;
    size_t nm= n & (~_MM1);
#pragma GCC unroll 1
#pragma clang unroll(1)
    while (i_src < nm) {
        i_dst+=_assign<_M>(r, i_src, i_dst);
        i_src+=_M;
    }
    if ((n & _MM1)!=0) {
        if constexpr (_M >32) {
            if ((n&32)!=0) {
                i_dst+= _assign<32>(r, i_src, i_dst);
                i_src+=32;
            }
        }
        if constexpr (_M >16) {
            if ((n&16)!=0) {
                i_dst+= _assign<16>(r, i_src, i_dst);
                i_src+=16;
            }
        }
        if constexpr (_M >8) {
            if ((n&8)!=0) {
                i_dst+= _assign<8>(r, i_src, i_dst);
                i_src+=8;
            }
        }
        if constexpr (_M >4) {
            if ((n&4)!=0) {
                i_dst+= _assign<4>(r, i_src, i_dst);
                i_src+=4;
            }
        }
        if constexpr (_M >2) {
            if ((n&2)!=0) {
                i_dst+= _assign<2>(r, i_src, i_dst);
                i_src+=2;
            }
        }
        if constexpr (_MIN_VEC_LEN < 2) {
            if (_M > 1 && (n&1)!=0) {
                _assign<1>(r, i_src, i_dst);
            }
        }
    }
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>::vsvec()
    : _A(), _n(0), _dta(nullptr)
{
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>::~vsvec()
{
    _destroy_and_free(_n);
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>::vsvec(const vsvec& r)
    : _A(r), _n(r.size()), _dta()
{
    _alloc_and_construct(r._n, r.begin());
}

template <typename _T, typename _A>
template <typename _AR>
cftal::vsvec<_T, _A>::vsvec(const vsvec<_T, _AR>& r)
    : _A(), _n(r.size()), _dta()
{
    _alloc_and_construct(_n, r.begin());
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>::vsvec(vsvec&& r)
    : _A(std::forward<_A>(r)),
      _n(r._n), _dta()
{
    if (r._is_short()) {
        _T* sp= r._short_elem_ptr();
        _T* dp= _short_elem_ptr();
        // move r short data elements to this
        // destroy data elements of r
        for (size_t i=0; i<r._n; ++i) {
            new(dp+i) _T(std::move(sp[i]));
            sp[i].~_T();
        }
    } else {
        _dta._d = r._dta._d;
    }
    r._n = 0;
    r._dta._d = nullptr;
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>&
cftal::vsvec<_T, _A>::operator=(const vsvec& r)
{
    if (__unlikely(this == &r))
        return *this;
    if (__unlikely(_n != r._n)) {
        vsvec t(r);
        return _swap(t);
    }
    // gcc12 warns if (n!=0) is not in front of std::copy
    if (_n != 0) {
	std::copy(r.cbegin(), r.cend(), begin());
    }
    return *this;
}

template <typename _T, typename _A>
template <typename  _AR>
cftal::vsvec<_T, _A>&
cftal::vsvec<_T, _A>::operator=(const vsvec<_T, _AR>& r)
{
    if (__unlikely(_n != r._n)) {
        vsvec t(r);
        return _swap(t);
    }
    std::copy(r.cbegin(), r.cend(), begin());
    return *this;
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>&
cftal::vsvec<_T, _A>::operator=(const _T& r)
{
    if (__unlikely(_n != 1)) {
        vsvec t(r, 1);
        return _swap(t);
    }
    *(begin())=r;
    return *this;
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>&
cftal::vsvec<_T, _A>::operator=(vsvec&& r)
{
    return _swap(r);
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>::vsvec(const _T& r, size_t n)
    : _A(), _n(n), _dta()
{
    _alloc_and_construct(n, r);
}

template <typename _T, typename _A>
cftal::vsvec<_T, _A>::vsvec(std::initializer_list<_T> l)
    : _A(), _n(l.size()), _dta()
{
    const _T* s=l.begin();
    _alloc_and_construct(_n, s);
}

template <typename _T, typename _A>
template <typename _ITER>
cftal::vsvec<_T, _A>::vsvec(_ITER b, _ITER e, std::false_type is_integer)
    : _A(), _n(std::distance(b, e)), _dta()
{
    static_cast<void>(is_integer);
    _alloc_and_construct(_n, b);
}

template <typename _T, typename _A>
template <typename _ITER>
cftal::vsvec<_T, _A>::vsvec(_ITER b, _ITER e, std::true_type is_integer)
    : vsvec(value_type(b), size_t(e))
{
    static_cast<void>(is_integer);
}

template <typename _T, typename _A>
template <typename _ITER>
cftal::vsvec<_T, _A>::vsvec(_ITER b, _ITER e)
    : vsvec(b, e, typename std::is_integral<_ITER>::type())
{
}

template <typename _T, typename _A>
template <typename _O,  typename _AR,
          template <class _U> class _OP,
          typename _L, typename _R>
cftal::vsvec<_T, _A>::
vsvec(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r)
    : _A(), _n(eval_result_size(r)), _dta()
{
    if (std::is_trivially_copyable_v<_T>)
        _alloc(_n);
    else
        _alloc_and_construct(_n, _T());
    size_t n=eval_size(r);
    _assign(r, n);
}

template <typename _T, typename _A>
template <typename _O,  typename _AR,
          template <class _U> class _OP,
          typename _L, typename _R>
cftal::vsvec<_T, _A>&
cftal::vsvec<_T, _A>::
operator=(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r)
{
    size_t nn=eval_result_size(r);
    if (__unlikely(nn != _n)) {
        vsvec t(r);
        return _swap(t);
    }
    size_t n=eval_size(r);
    _assign(r, n);
    return *this;
}

template <typename _T, typename _A>
inline
cftal::size_t
cftal::vsvec<_T, _A>::size() const
{
    return _n;
}

template <typename _T, typename _A>
inline
typename cftal::vsvec<_T, _A>::const_iterator
cftal::vsvec<_T, _A>::begin() const
{
    return _elem_ptr();
}

template <typename _T, typename _A>
inline
typename cftal::vsvec<_T, _A>::const_iterator
cftal::vsvec<_T, _A>::end() const
{
    return _elem_ptr() + _n;
}

template <typename _T, typename _A>
inline
typename cftal::vsvec<_T, _A>::const_iterator
cftal::vsvec<_T, _A>::cbegin() const
{
    return _elem_ptr();
}

template <typename _T, typename _A>
inline
typename cftal::vsvec<_T, _A>::const_iterator
cftal::vsvec<_T, _A>::cend() const
{
    return _elem_ptr() + _n;
}

template <typename _T, typename _A>
inline
typename cftal::vsvec<_T, _A>::iterator
cftal::vsvec<_T, _A>::begin()
{
    return _elem_ptr();
}

template <typename _T, typename _A>
inline
typename cftal::vsvec<_T, _A>::iterator
cftal::vsvec<_T, _A>::end()
{
    return _elem_ptr() + _n;
}

template <typename _T, typename _A>
inline
_T&
cftal::vsvec<_T, _A>::operator[](size_t i)
{
    return _elem_ptr()[i];
}

template <typename _T, typename _A>
inline
const _T&
cftal::vsvec<_T, _A>::operator[](size_t i) const
{
    return _elem_ptr()[i];
}

template <typename _T, typename _A>
template <cftal::size_t _N>
inline
const cftal::vec<_T, _N>*
cftal::vsvec<_T, _A>::loadp(size_t i) const
{
    const _T* p= _elem_ptr() + i;
    return reinterpret_cast<const cftal::vec<_T, _N>*>(p);
}

template <typename _T, typename _A>
template <cftal::size_t _N>
inline
cftal::vec<_T, _N>*
cftal::vsvec<_T, _A>::storep(size_t i)
{
    _T* p= _elem_ptr() + i;
    return reinterpret_cast<cftal::vec<_T, _N>*>(p);
}

template <typename _T, typename _A>
template <cftal::size_t _N>
inline
cftal::vec<_T, _N>
cftal::vsvec<_T, _A>::loadv(size_t i) const
{
    return *loadp<_N>(i);
}

template <typename _T, typename _A>
template <cftal::size_t _N>
inline
cftal::size_t
cftal::vsvec<_T, _A>::storev(size_t i, const vec<_T, _N>& v)
{
    *storep<_N>(i)= v;
    return _N;
}

template <typename _T, typename _A>
template <typename _C>
void
cftal::vsvec<_T, _A>::inspect(_C& c)
    const
{
    constexpr const size_t _VM= max_vec_size_specialized<_T>();
    constexpr const size_t _M= _VM * 2 > 64 ? 64 : _VM * 2;
    static_assert(_M <= 64);
    constexpr
    const size_t _MM1= _M-1;
    size_t i=0;
    size_t n=size();
#pragma GCC unroll 1
#pragma clang unroll(1)
    while (__likely(n>=_M)) {
        auto vn = loadv<_M>(i);
        if (c(vn)==false)
            return;
        i += _M;
        n -= _M;
    }
    if ((n & _MM1)!=0) {
        // should we use a template here ?
        if (_M >32 && (n&32)==32) {
            auto vn = loadv<32>(i);
            if (c(vn)==false)
                return;
            i += 32;
        }
        if (_M >16 && (n&16)==16) {
            auto vn = loadv<16>(i);
            if (c(vn)==false)
                return;
            i += 16;
        }
        if (_M >8 && (n&8)==8) {
            auto vn = loadv<8>(i);
            if (c(vn)==false)
                return;
            i += 8;
        }
        if (_M >4 && (n&4)==4) {
            auto vn = loadv<4>(i);
            if (c(vn)==false)
                return;
            i += 4;
        }
        if (_M >2 && (n&2)==2) {
            auto vn = loadv<2>(i);
            if (c(vn)==false)
                return;
            i += 2;
        }
        if (_M >1 && (n&1)==1) {
            auto vn = loadv<1>(i);
            if (c(vn)==false)
                return;
        }
    }
}

template <typename _T, typename _A>
std::ostream&
cftal::operator<<(std::ostream& s, const vsvec<_T, _A>& v)
{
    bool first=true;
    for (const auto& e: v) {
        if (first==true) {
            first = false;
        } else {
            s << ' ';
        }
        s << e;
    }
    return s;
}

// Local variables:
// mode: c++
// end:
#endif
