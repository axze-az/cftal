//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_SVVEC_BIT_A_H__)
#define __CFTAL_SVVEC_BIT_A_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec_t_a.h>
#include <stdexcept>

namespace cftal {

    namespace impl {
        // helper class for setting a single bit
        class bit_ref {
            uint64_t* _p;
            uint32_t _bit;
        public:
            // return pos / 64
            static
            uint32_t
            offset(uint32_t pos);
            // return pos % 64
            static
            uint32_t
            bitnum(uint32_t pos);
            // reference bit at p + pos
            bit_ref(uint64_t* p, size_t pos);
            // proxy setter
            bit_ref&
            operator=(const bit& r);
        };
    }

    template <typename _A>
    class vsvec<bit, _A>
        : private vsvec<uint64_t, typename std::allocator_traits<_A>::template
                                     rebind_alloc<uint64_t>> {
        using base_type=vsvec<uint64_t,
                             typename std::allocator_traits<_A>::template
                                rebind_alloc<uint64_t>>;
        size_t _size;
    public:
        using value_type = bit;
        using mask_value_type = typename vec<bit, 1>::mask_value_type;
        using mask_type = vsvec<bit, _A>;

        // default constructor: size() == 0
        vsvec();
        // destructor
        ~vsvec();
        // copy construction
        vsvec(const vsvec& r);
        // move construction
        vsvec(vsvec&& r);
        // copy assignment
        vsvec& operator=(const vsvec& r);
        // copy assignment of a scalar, may change the size
        // of the vector to 1
        vsvec& operator=(const bit& r);
        // move assignment
        vsvec& operator=(vsvec&& r);
        // initialize all n elements with r
        vsvec(const bit& r, size_t n=1);
        // initialize l.size() elements with l
        vsvec(std::initializer_list<bit> l);
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

        // size, changes only after assignment
        size_t size() const;
        // swap values with r
        void
        swap(vsvec& r);
        // r/w access operator
        impl::bit_ref operator[](size_t i);
        // ro access operator
        bit operator[](size_t i) const;
        // load vec<bit, _N> from pos i
        template <size_t _N>
        vec<bit, _N> loadv(size_t i) const;
        // store vec<_T, _N> at pos i, return the number of elements
        // written
        template <size_t _N>
        size_t
        storev(size_t i, const vec<bit, _N>& v);

        // inspect all elements of this
        template <typename _C>
        void
        inspect(_C& c)
            const;
    };
}

inline
cftal::uint32_t
cftal::impl::bit_ref::offset(uint32_t pos)
{
    // log_2(64): 6
    return pos >> 5;
}

inline
cftal::uint32_t
cftal::impl::bit_ref::bitnum(uint32_t pos)
{
    // log_2(64): 6
    return pos & 63;
}

inline
cftal::impl::bit_ref::bit_ref(uint64_t* p, size_t pos)
    : _p(p+offset(pos)), _bit(bitnum(pos))
{
}

inline
cftal::impl::bit_ref&
cftal::impl::bit_ref::operator=(const bit& r)
{
    const uint64_t mask= 1ULL << _bit;
    if (r() != 0) {
        // set the bit
        *_p |= mask;
    } else {
        // clear the bit
        const uint64_t nmask = ~mask;
        *_p &= nmask;
    }
    return *this;
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>::vsvec()
    : base_type()
{
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>::~vsvec()
{
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>::vsvec(const vsvec& r)
    : base_type(r), _size(r._size)
{
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>::vsvec(vsvec&& r)
    : base_type(std::move(r)), _size(r._size)
{
    r._size=0;
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>&
cftal::vsvec<cftal::bit, _A>::operator=(const vsvec& r)
{
    base_type::operator=(r);
    _size = r._size;
    return *this;
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>&
cftal::vsvec<cftal::bit, _A>::operator=(vsvec&& r)
{
    base_type::operator=(std::move(r));
    _size = r._size;
    r._size=0;
    return *this;
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>::vsvec(const bit& r, size_t n)
    : base_type(r() != 0 ?
		~(typename base_type::value_type(0)) :
		(typename base_type::value_type(0)),
                impl::bit_ref::offset(
		    n+sizeof(typename base_type::value_type)*8-1)),
     _size(n)
{
}

template <typename _A>
inline
cftal::vsvec<cftal::bit, _A>::vsvec(std::initializer_list<bit> l)
    : base_type(0, impl::bit_ref::offset(
        l.size()+sizeof(typename base_type::value_type)*8-1)),
     _size(l.size())
{
    if (_size) {
        uint32_t* p=base_type::begin();
        auto b=cbegin(l);
        for (size_t i=0; i<_size; ++i, ++b) {
            impl::bit_ref t(p, i);
            t = *b;
        }
    }
}

template <typename _A>
template <typename _O, typename _AR,
          template <class _U> class _OP,
          class _L, class _R>
inline
cftal::vsvec<cftal::bit, _A>::
vsvec(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r)
    : base_type(0, impl::bit_ref::offset(
        eval_result_size(r)+sizeof(typename base_type::value_type)*8-1)),
     _size(eval_result_size(r))
{
}

template <typename _A>
template <typename _O, typename _AR,
          template <class _U> class _OP,
          class _L, class _R>
inline
cftal::vsvec<cftal::bit, _A>&
cftal::vsvec<cftal::bit, _A>::
operator=(const expr<_OP<vsvec<_O, _AR>>, _L, _R>& r)
{
    return *this;
}

template <typename _A>
inline
cftal::size_t
cftal::vsvec<cftal::bit, _A>::size() const
{
    return _size;
}

template <typename _A>
cftal::impl::bit_ref
cftal::vsvec<cftal::bit, _A>::operator[](size_t pos)
{
    typename base_type::value_type* b=base_type::begin();
    impl::bit_ref r(b, pos);
    return r;
}

template <typename _A>
cftal::bit
cftal::vsvec<cftal::bit, _A>::operator[](size_t pos)
    const
{
    using val_t = typename base_type::value_type;
    const val_t* b=base_type::begin();
    uint32_t offs=impl::bit_ref::offset(pos);
    uint32_t bitnum=impl::bit_ref::bitnum(pos);
    val_t v= b[offs];
    v >>= bitnum;
    v &= 1;
    return bit(v != 0);
}

template <typename _A>
template <cftal::size_t _N>
cftal::vec<cftal::bit, _N>
cftal::vsvec<cftal::bit, _A>::loadv(size_t pos)
    const
{
    static_assert(_N <= 64, "vector to long");
    uint32_t bitnum=impl::bit_ref::bitnum(pos);
    uint32_t offs=impl::bit_ref::offset(pos);
    if (bitnum + _N > 64 ) {
        throw std::logic_error("unaligned access, crosses uint64_t border");
    }
    uint64_t v= base_type::operator[](offs);
    if (_N < 64) {
        constexpr const uint64_t mask = (~0ULL) >> (64 - _N);
        v >>= bitnum;
        v &= mask;
    }
    return vec<cftal::bit, _N>(v);
}

template <typename _A>
template <cftal::size_t _N>
cftal::size_t
cftal::vsvec<cftal::bit, _A>::storev(size_t pos, const vec<bit, _N>& v)
{
    static_assert(_N <= 64, "vector to long");
    uint32_t bitnum=impl::bit_ref::bitnum(pos);
    uint32_t offs=impl::bit_ref::offset(pos);
    if (bitnum + _N > 64 ) {
        throw std::logic_error("unaligned access, crosses uint64_t border");
    }
    if (_N < 64) {
        uint64_t vo= base_type::operator[](offs);
        constexpr const uint64_t mask = (~0ULL) >> (64 - _N);
        constexpr const uint64_t nmask= ~mask;
        vo &= (nmask << bitnum);
        uint64_t vn= v() & mask;
        vn <<= bitnum;
        vn |= vo;
        base_type::operator[](offs)=vn;
    } else {
        base_type::operator[](offs)=v();
    }
    return _N;
}

template <typename _A>
template <typename _C>
void
cftal::vsvec<cftal::bit, _A>::inspect(_C& c)
    const
{
    constexpr const size_t _VM= max_vec_size_specialized<bit>();
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


// Local variales:
// mode: c++
// end:
#endif
