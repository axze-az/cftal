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
#if !defined (__CFTAL_VEC_LOOKUP_H__)
#define __CFTAL_VEC_LOOKUP_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>

namespace cftal {

    namespace impl {

        // implementation class for variable lookup tables without
        // an array interface
        template <typename _T, typename _I, std::size_t _VEC_LEN>
        class variable_vec_lookup_table {
        private:
            variable_vec_lookup_table<_T, _I, _VEC_LEN/2> _lh;
            variable_vec_lookup_table<_T, _I, _VEC_LEN/2> _hh;
        public:
            // constructor, prepares table lookup, delegates the work
            // to _lh and _hh constructors
            variable_vec_lookup_table(const vec<_I, _VEC_LEN>& idx)
                : _lh(low_half(idx)), _hh(high_half(idx)) {}
            // perform the lookup using the prepared data
            vec<_T, _VEC_LEN>
            fromp(const _T* tbl) const {
                vec<_T, _VEC_LEN/2> lh=_lh.fromp(tbl);
                vec<_T, _VEC_LEN/2> hh=_hh.fromp(tbl);
                return vec<_T, _VEC_LEN>(lh, hh);
            }
        };

    }

    // variable lookup table for vec<_T, _VEC_LEN>.
    // with signed _I negative indices are possible
    template <typename _T, typename _I, std::size_t _VEC_LEN>
    class variable_vec_lookup_table
        : public impl::variable_vec_lookup_table<_T, _I, _VEC_LEN> {
    private:
        using base_type=
            impl::variable_vec_lookup_table<_T, _I, _VEC_LEN>;
    public:
        // constructor, prepares table lookup
        variable_vec_lookup_table(const vec<_I, _VEC_LEN>& idx)
            : base_type(idx) {}
        // perform the lookup using the prepared data
        template <size_t _TABLE_LEN>
        vec<_T, _VEC_LEN>
        from(const _T (&tbl)[_TABLE_LEN]) const {
            return base_type::fromp(tbl);
        }
        // perform the lookup using the prepared data positive and
        // negative indices
        template <size_t _TABLE_LEN>
        vec<_T, _VEC_LEN>
        from(const _T (&tbl)[_TABLE_LEN], size_t zero_offset) const {
            return base_type::fromp(tbl+zero_offset);
        }
    };

    // function to create a variable_vec_lookup_table
    template <typename _T, typename _I, std::size_t _VEC_LEN>
    variable_vec_lookup_table<_T, _I, _VEC_LEN>
    make_variable_lookup_table(const vec<_I, _VEC_LEN>& idx) {
        return variable_vec_lookup_table<_T, _I, _VEC_LEN>(idx);
    }

    namespace impl {
        // implementation class for fixed lookup tables without
        // a safe interface
        template <std::size_t _TABLE_LEN, typename _T,
                  typename _I, std::size_t _VEC_LEN>
        class fixed_vec_lookup_table {
        private:
            fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN/2> _lh;
            fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN/2> _hh;
        public:
            // constructor, prepares table lookups into _T[_TABLE_LEN]
            fixed_vec_lookup_table(const vec<_I, _VEC_LEN>& idx)
                : _lh(low_half(idx)), _hh(high_half(idx)) {}
            // perform the lookup using the prepared data
            vec<_T, _VEC_LEN>
            fromp(const _T* tbl) const {
                vec<_T, _VEC_LEN/2> lh=_lh.fromp(tbl);
                vec<_T, _VEC_LEN/2> hh=_hh.fromp(tbl);
                return vec<_T, _VEC_LEN>(lh, hh);
            }
        };
    }

    // fixed length lookup table for vec<_T, _VEC_LEN>.
    // even with signed _I negative indices are NOT possible
    // fixed_vec_lookup_table delegates work to
    // impl::fixed_vec_lookup_table
    template <std::size_t _TABLE_LEN, typename _T,
              typename _I, std::size_t _VEC_LEN>
    class fixed_vec_lookup_table
        : public impl::fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN> {
    private:
        using base_type=
            impl::fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>;
    public:
        // constructor, prepares table lookups into _T[_TABLE_LEN]
        fixed_vec_lookup_table(const vec<_I, _VEC_LEN>& idx)
            : base_type(idx) {}
        // perform the lookup using the prepared data
        vec<_T, _VEC_LEN>
        from(const _T (&tbl)[_TABLE_LEN]) const {
            return base_type::fromp(tbl);
        }
    };

    // function to create a fixed_vec_lookup_table
    template <std::size_t _TABLE_LEN, typename _T,
              typename _I, std::size_t _VEC_LEN>
    fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>
    make_fixed_lookup_table(const vec<_I, _VEC_LEN>& idx) {
        return fixed_vec_lookup_table<_TABLE_LEN, _T, _I, _VEC_LEN>(idx);
    }
}


// Local variables:
// mode: c++
// end:
#endif
