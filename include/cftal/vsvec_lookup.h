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
#if !defined (__CFTAL_VSVEC_LOOKUP_H__)
#define __CFTAL_VSVEC_LOOKUP_H__ 1

#include <cftal/config.h>
#include <cftal/vsvec_op.h>
#include <memory>
#include <vector>

namespace cftal {

    namespace impl {

        template <typename _T, typename _I, typename _IA>
        struct variable_vsvec_lookup_traits {
            using result_type = _T;
            using int_type = _I;
            using int_allocator_type = _IA;
            template <size_t _VEC_LEN>
            using lookup_type = // cftal::
                variable_vec_lookup_table<_T, _I, _VEC_LEN>;

            template <size_t _VEC_LEN>
            static
            vec<_T, _VEC_LEN>
            fromp(const lookup_type<_VEC_LEN>& lck, const _T* p) {
                return lck.from(p);
            }
        };

        template <size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
        struct fixed_vsvec_lookup_traits {
            using result_type = _T;
            using int_type = _I;
            using int_allocator_type = _IA;
            template <size_t _VEC_LEN>
            using lookup_type = // cftal::impl::
                fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>;

            template <size_t _VEC_LEN>
            static
            vec<_T, _VEC_LEN>
            fromp(const lookup_type<_VEC_LEN>& lck, const _T* p) {
                return lck.fromp(p);
            }
        };

        template <typename _TRAITS>
        class vsvec_lookup_table {
            using lookup_type_32 = typename _TRAITS::template lookup_type<32>;
            using lookup_type_16 = typename _TRAITS::template lookup_type<16>;
            using lookup_type_8 = typename _TRAITS::template lookup_type<8>;
            using lookup_type_4 = typename _TRAITS::template lookup_type<4>;
            using lookup_type_2 = typename _TRAITS::template lookup_type<2>;
            using lookup_type_1 = typename _TRAITS::template lookup_type<1>;
            std::vector<lookup_type_32> _lkup_32;
            std::unique_ptr<lookup_type_16> _lkup_16;
            std::unique_ptr<lookup_type_8> _lkup_8;
            std::unique_ptr<lookup_type_4> _lkup_4;
            std::unique_ptr<lookup_type_2> _lkup_2;
            std::unique_ptr<lookup_type_1> _lkup_1;
            size_t _n;
        public:
            using result_type = typename _TRAITS::result_type;
            using int_type = typename _TRAITS::int_type;
            using int_allocator_type = typename _TRAITS::int_allocator_type;
            // allocator type of vsvec returned by from
            using result_allocator_type =
                typename std::allocator_traits<int_allocator_type>::template
                    rebind_alloc<result_type>;
            // constructor
            vsvec_lookup_table(const vsvec<int_type, int_allocator_type>& idx);
            // deleted copy constructor
            vsvec_lookup_table(const vsvec_lookup_table&) = delete;
            // move constructor
            vsvec_lookup_table(vsvec_lookup_table&& r);
            // copy assignment, deleted
            vsvec_lookup_table&
            operator=(const vsvec_lookup_table&) = delete;
            // move assignment
            vsvec_lookup_table&
            operator=(vsvec_lookup_table&& r);
            // destructor is not required
            ~vsvec_lookup_table() = default;
            // perform a lookup from tbl
            vsvec<result_type, result_allocator_type>
            fromp(const result_type* tbl);
        };
    };

    template <typename _T, typename _I, typename _IA>
    class variable_vsvec_lookup_table
        : private impl::vsvec_lookup_table<
            impl::variable_vsvec_lookup_traits<_T, _I, _IA> > {
        using base_type = impl::vsvec_lookup_table<
            impl::variable_vsvec_lookup_traits<_T, _I, _IA> >;
    public:
        using _A = typename
            base_type::result_allocator_type;
        // constructor
        variable_vsvec_lookup_table(const vsvec<_I, _IA>& idx);
        // deleted copy constructor
        variable_vsvec_lookup_table(const variable_vsvec_lookup_table&) = delete;
        // move constructor
        variable_vsvec_lookup_table(variable_vsvec_lookup_table&& r);
        // copy assignment, deleted
        variable_vsvec_lookup_table&
        operator=(const variable_vsvec_lookup_table&) = delete;
        // move assignment
        variable_vsvec_lookup_table&
        operator=(variable_vsvec_lookup_table&& r);
        // destructor is not required
        ~variable_vsvec_lookup_table() = default;
        // allocator type of vsvec the returned by from
        // perform a lookup from tbl
        vsvec<_T, _A>
        from(const _T* tbl);
    };

    template <typename _T, typename _I, typename _A>
    variable_vsvec_lookup_table<_T, _I, _A>
    make_variable_lookup_table(const vsvec<_I, _A>& idx);

    template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
    class fixed_vsvec_lookup_table
        : private impl::vsvec_lookup_table<
            impl::fixed_vsvec_lookup_traits<_TABLE_LEN, _T, _I, _IA> > {
        using base_type = impl::vsvec_lookup_table<
            impl::fixed_vsvec_lookup_traits<_TABLE_LEN, _T, _I, _IA> >;
    public:
        using _A = typename
            base_type::result_allocator_type;
        // constructor
        fixed_vsvec_lookup_table(const vsvec<_I, _IA>& idx);
        // deleted copy constructor
        fixed_vsvec_lookup_table(const fixed_vsvec_lookup_table&) = delete;
        // move constructor
        fixed_vsvec_lookup_table(fixed_vsvec_lookup_table&& r);
        // copy assignment, deleted
        fixed_vsvec_lookup_table&
        operator=(const fixed_vsvec_lookup_table&) = delete;
        // move assignment
        fixed_vsvec_lookup_table&
        operator=(fixed_vsvec_lookup_table&& r);
        // destructor is not required
        ~fixed_vsvec_lookup_table() = default;
        // allocator type of vsvec the returned by from
        // perform a lookup from tbl
        vsvec<_T, _A>
        from(const _T (&tbl)[_TABLE_LEN]);
    };

    template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _A>
    fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _A>
    make_fixed_lookup_table(const vsvec<_I, _A>& idx);

}

template <typename _TRAITS>
cftal::impl::vsvec_lookup_table<_TRAITS>::
vsvec_lookup_table(const vsvec<int_type, int_allocator_type>& idx)
    : _n(idx.size())
{
    size_t n32o=_n/32;
    size_t i=0;
    if (n32o != 0) {
        _lkup_32.reserve(n32o);
        size_t n32=n32o*32;
        for (i=0; i<n32; i+=32) {
            vec<int_type, 32> t=idx.template loadv<32>(i);
            _lkup_32.emplace_back(t);
        }
    }
    if (_n & 16) {
        vec<int_type, 16> t=idx.template loadv<16>(i);
        _lkup_16.reset(new lookup_type_16(t));
        i += 16;
    }
    if (_n & 8) {
        vec<int_type, 8> t=idx.template loadv<8>(i);
        _lkup_8.reset(new lookup_type_8(t));
        i += 8;
    }
    if (_n & 4) {
        vec<int_type, 4> t=idx.template loadv<4>(i);
        _lkup_4.reset(new lookup_type_4(t));
        i += 4;
    }
    if (_n & 2) {
        vec<int_type, 2> t=idx.template loadv<2>(i);
        _lkup_2.reset(new lookup_type_2(t));
        i += 2;
    }
    if (_n & 1) {
        vec<int_type, 1> t=idx.template loadv<1>(i);
        _lkup_1.reset(new lookup_type_1(t));
    }
}

template <typename _TRAITS>
cftal::impl::vsvec_lookup_table<_TRAITS>::
vsvec_lookup_table(vsvec_lookup_table&& r)
    : _lkup_32(std::move(r._lkup_32)),
      _lkup_16(std::move(r._lkup_16)),
      _lkup_8(std::move(r._lkup_8)),
      _lkup_4(std::move(r._lkup_4)),
      _lkup_2(std::move(r._lkup_2)),
      _lkup_1(std::move(r._lkup_1)),
      _n(std::move(r._n))
{
}

template <typename _TRAITS>
cftal::impl::vsvec_lookup_table<_TRAITS>&
cftal::impl::vsvec_lookup_table<_TRAITS>::
operator=(vsvec_lookup_table&& r)
{
    _lkup_32=std::move(r._lkup_32);
    _lkup_16=std::move(r._lkup_16);
    _lkup_8=std::move(r._lkup_8);
    _lkup_4=std::move(r._lkup_4);
    _lkup_2=std::move(r._lkup_2);
    _lkup_1=std::move(r._lkup_1);
    _n=std::move(r._n);
    return *this;
}

template <typename _TRAITS>
cftal::
vsvec<typename cftal::impl::vsvec_lookup_table<_TRAITS>::result_type,
     typename cftal::impl::vsvec_lookup_table<_TRAITS>::result_allocator_type>
cftal::impl::vsvec_lookup_table<_TRAITS>::
fromp(const result_type* p)
{
    vsvec<result_type, result_allocator_type>  r(result_type(), _n);
    size_t i=0;
    size_t n32=_lkup_32.size();
    if (n32 != 0) {
        for (size_t j=0; j<n32; ++j, i+=32) {
            vec<result_type, 32> t=_TRAITS::fromp(_lkup_32[j], p);
            r.storev(i, t);
        }
    }
    if (_lkup_16 != nullptr) {
        vec<result_type, 16> t=_TRAITS::fromp(*_lkup_16, p);
        r.storev(i, t);
        i += 16;
    }
    if (_lkup_8 != nullptr) {
        vec<result_type, 8> t=_TRAITS::fromp(*_lkup_8, p);
        r.storev(i, t);
        i += 8;
    }
    if (_lkup_4 != nullptr) {
        vec<result_type, 4> t=_TRAITS::fromp(*_lkup_4, p);
        r.storev(i, t);
        i += 4;
    }
    if (_lkup_2 != nullptr) {
        vec<result_type, 2> t=_TRAITS::fromp(*_lkup_2, p);
        r.storev(i, t);
        i += 2;
    }
    if (_lkup_1 != nullptr) {
        vec<result_type, 1> t=_TRAITS::fromp(*_lkup_1, p);
        r.storev(i, t);
    }
    return r;
}


template <typename _T, typename _I, typename _IA>
cftal::variable_vsvec_lookup_table<_T, _I, _IA>::
variable_vsvec_lookup_table(const vsvec<_I, _IA>& idx)
    : base_type(idx)
{
}

template <typename _T, typename _I, typename _IA>
cftal::variable_vsvec_lookup_table<_T, _I, _IA>::
variable_vsvec_lookup_table(variable_vsvec_lookup_table&& r)
    : base_type(std::forward(r))
{
}

template <typename _T, typename _I, typename _IA>
cftal::variable_vsvec_lookup_table<_T, _I, _IA>&
cftal::variable_vsvec_lookup_table<_T, _I, _IA>::
operator=(variable_vsvec_lookup_table&& r)
{
    base_type::operator=(std::forward(r));
    return *this;
}

template <typename _T, typename _I, typename _IA>
cftal::vsvec<_T,
            typename cftal::variable_vsvec_lookup_table<_T, _I, _IA>::_A >
cftal::variable_vsvec_lookup_table<_T, _I, _IA>::
from(const _T* p)
{
    return base_type::fromp(p);
}

template <typename _T, typename _I, typename _IA>
cftal::variable_vsvec_lookup_table<_T, _I, _IA>
cftal::make_variable_lookup_table(const vsvec<_I, _IA>& idx)
{
    return variable_vsvec_lookup_table<_T, _I, _IA>(idx);
}


template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>::
fixed_vsvec_lookup_table(const vsvec<_I, _IA>& idx)
    : base_type(idx)
{
}

template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>::
fixed_vsvec_lookup_table(fixed_vsvec_lookup_table&& r)
    : base_type(std::forward(r))
{
}

template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>&
cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>::
operator=(fixed_vsvec_lookup_table&& r)
{
    base_type::operator=(std::forward(r));
    return *this;
}

template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
cftal::vsvec<_T,
            typename cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>::_A >
cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>::
from(const _T (&tbl)[_TABLE_LEN])
{
    return base_type::fromp(tbl);
}

template <std::size_t _TABLE_LEN, typename _T, typename _I, typename _IA>
cftal::fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>
cftal::make_fixed_lookup_table(const vsvec<_I, _IA>& idx)
{
    return fixed_vsvec_lookup_table<_TABLE_LEN, _T, _I, _IA>(idx);
}

#endif
