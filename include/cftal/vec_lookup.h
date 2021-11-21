//
// Copyright Axel Zeuner 2010-2021. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#if !defined (__CFTAL_VEC_LOOKUP_H__)
#define __CFTAL_VEC_LOOKUP_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_n.h>

namespace cftal {

    template <typename _T, typename _I, std::size_t _VEC_LEN>
    class variable_vec_lookup_table {
    private:
        variable_vec_lookup_table<_T, _I, _VEC_LEN/2> _lh;
        variable_vec_lookup_table<_T, _I, _VEC_LEN/2> _hh;
    public:
        variable_vec_lookup_table(const vec<_I, _VEC_LEN>& idx)
            : _lh(low_half(idx)), _hh(high_half(idx)) {}
        vec<_T, _VEC_LEN>
        from(const _T* tbl) const {
            vec<_T, _VEC_LEN/2> lh=_lh.from(tbl);
            vec<_T, _VEC_LEN/2> hh=_hh.from(tbl);
            return vec<_T, _VEC_LEN>(lh, hh);
        }
    };

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
        class fixed_vec_lookup_table
            : private variable_vec_lookup_table<_T, _I, _VEC_LEN> {
        private:
        protected:
            using base_type=variable_vec_lookup_table<_T, _I, _VEC_LEN>;
            // constructor, prepares table lookups into _T[_TABLE_LEN]
            fixed_vec_lookup_table(const vec<_I, _VEC_LEN>& idx)
                : base_type(idx) {}
            // perform the lookup using the prepared data
            vec<_T, _VEC_LEN>
            fromp(const _T* tbl) const {
                return base_type::from(tbl);
            }
        };
    }

    // lookup table with a fixed length, delegates work to
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
