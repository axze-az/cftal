//
// Copyright (C) 2010-2025 Axel Zeuner
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
#if !defined (__CFTAL_VEC_COMPRESS_EXPAND_ELEMENTS_H__)
#define __CFTAL_VEC_COMPRESS_EXPAND_ELEMENTS_H__ 1

#include <cftal/config.h>
#include <cftal/vec_t_1.h>
#include <cftal/vec_spec.h>


namespace cftal {

    // permute the elements set in m to positions 0, 1, 2
    // return compressed vector and number of elements used in result
    template <typename _T, size_t _N>
    std::pair<vec<_T, _N>, size_t>
    compress_elements(const vec<_T, _N>& src,
                      const typename vec<_T, _N>::mask_type& m);

    // expand the elements 0, 1, 2 ... from source to the positions
    // set in m and clear the elements not set in m
    // return expanded vector and number of elements used from src
    template <typename _T, size_t _N>
    std::pair<vec<_T, _N>, size_t>
    expand_elements(const vec<_T, _N>& src,
                    const typename vec<_T, _N>::mask_type& m);

    namespace impl {

	// mask bit/elements to index
	// 0 0 0 0 --> -1 -1 -1 -1
	// 1 0 0 0      0 -1 -1 -1
	// 0 1 0 0      1 -1 -1 -1
	// 1 1 0 0      0  1 -1 -1
	// ..
	// 1 0 1 0 -->  0  2 -1 -1

        template <typename _I, size_t _N>
        struct compress_expand {
            enum {
                BITS=_N,
                PERM_CNT=1<<BITS,
                ENTRIES=PERM_CNT*BITS
            };
            alignas(vec<_I, BITS>) static const _I _compress[ENTRIES];
            alignas(vec<_I, BITS>) static const _I _expand[ENTRIES];
            static const int32_t _pop_cnt[PERM_CNT];
        };

        template <typename _I>
        struct compress_expand<_I, 2>  {
            enum {
                BITS=2,
                PERM_CNT=1<<BITS,
                ENTRIES=PERM_CNT*BITS
            };
            alignas(vec<_I, BITS>) static const _I _compress[ENTRIES];
            alignas(vec<_I, BITS>) static const _I _expand[ENTRIES];
            static const int8_t _pop_cnt[PERM_CNT];
        };

        template <typename _I>
        alignas(vec<_I, compress_expand<_I, 2>::BITS>)
        const _I
        compress_expand<_I, 2>::_compress[compress_expand<_I, 2>::ENTRIES]={
            -1, -1,
            0, -1,
            1, -1,
            0,  1
        };

        template <typename _I>
        alignas(vec<_I, compress_expand<_I, 2>::BITS>)
        const _I
        compress_expand<_I, 2>::_expand[compress_expand<_I, 2>::ENTRIES]={
            -1, -1,
            0, -1,
            -1,  0,
            0,  1
        };

        template <typename _I>
        const int8_t
        compress_expand<_I, 2>::_pop_cnt[compress_expand<_I, 2>::PERM_CNT]={
            0,
            1,
            1,
            2
        };

        template <typename _I>
        struct compress_expand<_I, 4>  {
            enum {
                BITS=4,
                PERM_CNT=1<<BITS,
                ENTRIES=PERM_CNT*BITS
            };
            alignas(vec<_I, BITS>) static const _I _compress[ENTRIES];
            alignas(vec<_I, BITS>) static const _I _expand[ENTRIES];
            static const int8_t _pop_cnt[PERM_CNT];
        };

        template <typename _I>
        alignas(vec<_I, compress_expand<_I, 4>::BITS>)
        const _I
        compress_expand<_I, 4>::_compress[compress_expand<_I, 4>::ENTRIES]={
            -1, -1, -1, -1,
            0, -1, -1, -1,
            1, -1, -1, -1,
            0,  1, -1, -1,
            2, -1, -1, -1,
            0,  2, -1, -1,
            1,  2, -1, -1,
            0,  1,  2, -1,
            3, -1, -1, -1,
            0,  3, -1, -1,
            1,  3, -1, -1,
            0,  1,  3, -1,
            2,  3, -1, -1,
            0,  2,  3, -1,
            1,  2,  3, -1,
            0,  1,  2,  3
        };

        template <typename _I>
        alignas(vec<_I, compress_expand<_I, 4>::BITS>)
        const _I
        compress_expand<_I, 4>::_expand[compress_expand<_I, 4>::ENTRIES]={
            -1, -1, -1, -1,
            0, -1, -1, -1,
            -1,  0, -1, -1,
            0,  1, -1, -1,
            -1, -1,  0, -1,
            0, -1,  1, -1,
            -1,  0,  1, -1,
            0,  1,  2, -1,
            -1, -1, -1,  0,
            0, -1, -1,  1,
            -1,  0, -1,  1,
            0,  1, -1,  2,
            -1, -1,  0,  1,
            0, -1,  1,  2,
            -1,  0,  1,  2,
            0,  1,  2,  3
        };

        template <typename _I>
        const int8_t
        compress_expand<_I, 4>::_pop_cnt[compress_expand<_I, 4>::PERM_CNT]={
            0,
            1,
            1,
            2,
            1,
            2,
            2,
            3,
            1,
            2,
            2,
            3,
            2,
            3,
            3,
            4
        };


        template <typename _I, size_t _N>
        struct identity_index {
            struct table {
                alignas(vec<_I, _N>) _I _idx[_N];
                table() {
                    for (size_t i=0; i<_N; ++i)
                        _idx[i]=i;
                }
            };
            static const table _tbl;
        };

        template <typename _I, size_t _N>
        const typename identity_index<_I, _N>::table
        identity_index<_I, _N>::_tbl;

        // compress vector
        // compress low half, nl elements used
        // compress high half, nh elements used
        // combine compressed low half and compressed high half
        // load index 0, 1, 2, 3, 4, 5, 6, 7
        // index: add N/2 - nl to all elements with index ge nl
        // set index to -1 where index > _N-1 or ignore these fields
        // perform permutation

        // example 0, 1, 2, 3, 4, 5, 6, 7
        // nl=2 N=8 N/2-nl=4-2=2
        //         0, 1, 4, 5, 6, 7, 8, 9
        // -1, where index > _N-1
        //         0. 1, 5, 6, 6, 7, -1, -1
        // nl= 3 N/2-nl=4-3=1
        //         0, 1, 2, 4, 5, 6, 7, 8
        // -1, where index > _N-1
        //         0. 1, 2, 4, 5, 6, 7, -1

        // expand vector
        // expand low half of mask/vector, nl elements from source
        // used
        // load index 0, 1, 2, 3, 4, 5, 6, 7
        // add nl to index --> nl, nl + 1, ....
        // permute src, i.e. shift src nl elements to the left
        // get expansion mask for high half
        // expand low half of permuted src(high half) using high half mask
        // combine expanded low half and expanded high half


        template <typename _T, size_t _N, typename _I>
	struct compress_expand_elements {
	    // return compressed vector and number of elements used in result
	    static
	    std::pair<vec<_T, _N>, size_t>
	    compress(const vec<_T, _N>& src,
		     const typename vec<_T, _N>::mask_type& m);
	    // return expanded vector and number of elements used from src
	    static
	    std::pair<vec<_T, _N>, size_t>
	    expand(const vec<_T, _N>& src,
		   const typename vec<_T, _N>::mask_type& m);
	};

        template <typename _T, typename _I>
	struct compress_expand_elements<_T, 1, _I>  {
	    // return compressed vector and number of elements used in result
	    static
	    std::pair<vec<_T, 1>, size_t>
	    compress(const vec<_T, 1>& src,
			      const typename vec<_T, 1>::mask_type& m);

	    // return expanded vector and number of elements used from src
	    static
	    std::pair<vec<_T, 1>, size_t>
	    expand(const vec<_T, 1>& src,
		   const typename vec<_T, 1>::mask_type& m);
	};

#define __CFTAL_USE_COMPRESS_EXPAND_SPECIALIZATIONS__ 1

#if __CFTAL_USE_COMPRESS_EXPAND_SPECIALIZATIONS__ > 0
	template <typename _T, typename _I>
	struct compress_expand_elements<_T, 2, _I>  {
	    // return compressed vector and number of elements used in result
	    static
	    std::pair<vec<_T, 2>, size_t>
	    compress(const vec<_T, 2>& src,
		     const typename vec<_T, 2>::mask_type& m);

	    // return expanded vector and number of elements used from src
	    static
	    std::pair<vec<_T, 2>, size_t>
	    expand(const vec<_T, 2>& src,
		   const typename vec<_T, 2>::mask_type& m);
	};

	template <typename _T, typename _I>
	struct compress_expand_elements<_T, 4, _I>  {
	    // return compressed vector and number of elements used in result
	    static
	    std::pair<vec<_T, 4>, size_t>
	    compress(const vec<_T, 4>& src,
		     const typename vec<_T, 4>::mask_type& m);

	    // return expanded vector and number of elements used from src
	    static
	    std::pair<vec<_T, 4>, size_t>
	    expand(const vec<_T, 4>& src,
		   const typename vec<_T, 4>::mask_type& m);
	};
#endif
    }

    // execute ag(a) only to the left n elements rounded up to the next
    // multiple of 2
    template <typename _T, size_t _N, typename _ALG>
    vec<_T, _N>
    exec_compressed(const _ALG& ag, size_t n, const vec<_T, _N>& a);

    // execute ag(a) if n > 0
    template <typename _T, typename _ALG>
    vec<_T, 1>
    exec_compressed(const _ALG& ag, size_t n, const vec<_T, 1>& a);

    template <typename _T, size_t _N, typename _ALG>
    vec<_T, _N>
    compress_exec_expand(const _ALG& alg,
                         const mask_t<vec<_T, _N> >& m,
                         const vec<_T, _N>& a);

    template <typename _T, typename _ALG>
    vec<_T, 1>
    compress_exec_expand(const _ALG& ag, const mask_t<vec<_T, 1> >& m,
                         const vec<_T, 1>& a);
}

template <typename _T, size_t _N>
std::pair<cftal::vec<_T, _N>, cftal::size_t>
cftal::
compress_elements(const vec<_T, _N>& src,
                  const typename vec<_T, _N>::mask_type& m)
{
    using i_t = preferred_index_type_t<_T>;
    return impl::compress_expand_elements<_T, _N, i_t>::compress(src, m);
}

template <typename _T, size_t _N>
std::pair<cftal::vec<_T, _N>, cftal::size_t>
cftal::
expand_elements(const vec<_T, _N>& src,
                const typename vec<_T, _N>::mask_type& m)
{
    using i_t = preferred_index_type_t<_T>;
    return impl::compress_expand_elements<_T, _N, i_t>::expand(src, m);
}

// return compressed vector and number of elements used in result
template <typename _T, size_t _N, typename _I>
std::pair<cftal::vec<_T, _N>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, _N, _I>::
compress(const vec<_T, _N>& src,
	 const typename vec<_T, _N>::mask_type& m)
{
#if 0
    if (_N==8) {
        std::cout << __PRETTY_FUNCTION__ << '\n'
                << "src: " << src << '\n'
                << "m: " << m << '\n';
    }
#endif
    constexpr const size_t _N2= _N/2;
    using i_t = vec<_I, _N>;
    using v_half_t = vec<_T, _N2>;
    using m_half_t = typename vec<_T, _N2>::mask_type;

    const v_half_t sl=low_half(src);
    const m_half_t ml=low_half(m);
    std::pair<v_half_t, size_t> rl=
	compress_expand_elements<_T, _N2, _I>::compress(sl, ml);
    _I nl=rl.second;
#if 0
    if (_N==8) {
        std::cout << "rl: " << rl.first << '\n'
                << "nl: " << nl << '\n';
    }
#endif
    const v_half_t sh=high_half(src);
    const m_half_t mh=high_half(m);
    std::pair<v_half_t, size_t> rh=
	compress_expand_elements<_T, _N2, _I>::compress(sh, mh);
    _I nh=rh.second;
#if 0
    if (_N==8) {
        std::cout << "rh: " << rh.first << '\n'
                << "nh: " << nh << '\n';
    }
#endif
    vec<_T, _N> r(rl.first, rh.first);

    // load indices with ones
    const i_t idx_identity=
        mem<i_t>::load(identity_index<_I, _N>::_tbl._idx, _N);
    _I c=_N/2 - nl;
    // index: add N/2 - nl to all elements with index ge nl
    i_t idx_c=idx_identity + c;
    i_t idx= select(idx_identity<nl, idx_identity, idx_c);
#if 0
    if (_N==8) {
        std::cout << "idx: " << idx << '\n';
    }
#endif
    // set index to -1 where index > _N-1 or ignore these fields
    idx = select(idx > _N-1, i_t(-1), idx);
#if 0
    if (_N==8) {
        std::cout << "idx: " << idx << '\n';
    }
#endif
    r=permute(r, idx);
    return std::make_pair(r, size_t(nl+nh));
}

// return expanded vector and number of elements used from src
template <typename _T, size_t _N, typename _I>
std::pair<cftal::vec<_T, _N>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, _N, _I>::
expand(const vec<_T, _N>& src,
       const typename vec<_T, _N>::mask_type& m)
{
    constexpr const size_t _N2= _N/2;
    using i_t = vec<_I, _N>;
    using v_half_t = vec<_T, _N2>;
    using m_half_t = typename vec<_T, _N2>::mask_type;

    const v_half_t sl=low_half(src);
    const m_half_t ml=low_half(m);
    std::pair<v_half_t, size_t> rl=
	compress_expand_elements<_T, _N2, _I>::expand(sl, ml);
    // load indices with ones
    const i_t idx_identity=
        mem<i_t>::load(identity_index<_I, _N>::_tbl._idx, _N);
    // add nl to the indices
    _I nl=rl.second;
    i_t idx= idx_identity + nl;
    vec<_T, _N> psrc=permute(src, idx);
    const v_half_t sh=low_half(psrc);
    const m_half_t mh=high_half(m);
    std::pair<v_half_t, size_t> rh=
	compress_expand_elements<_T, _N2, _I>::expand(sh, mh);
    vec<_T, _N> r(rl.first, rh.first);
    return std::make_pair(r, size_t(nl) + rh.second);
}

// return compressed vector and number of elements used in result
template <typename _T, typename _I>
std::pair<cftal::vec<_T, 1>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, 1, _I>::
compress(const vec<_T, 1>& src,
	 const typename vec<_T, 1>::mask_type& m)
{
    const bool mt= mask_to_bool<_T>::v(m());
    vec<_T, 1> res= mt ? src : _T(0);
    size_t i=mt ? 1 : 0;
    return std::make_pair(res, i);
}

// return expanded vector and number of elements used from src
template <typename _T, typename _I>
std::pair<cftal::vec<_T, 1>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, 1, _I>::
expand(const vec<_T, 1>& src,
       const typename vec<_T, 1>::mask_type& m)
{
    const bool mt= mask_to_bool<_T>::v(m());
    vec<_T, 1> res=mt ? src : _T(0);
    size_t i= mt ? 1 : 0;
    return std::make_pair(res, i);
}


#if __CFTAL_USE_COMPRESS_EXPAND_SPECIALIZATIONS__ > 0
template <typename _T, typename _I>
std::pair<cftal::vec<_T, 2>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, 2, _I>::
compress(const vec<_T, 2>& src,
	 const typename vec<_T, 2>::mask_type& m)
{
    auto cm=compress_mask(m);
    using tbl_t=impl::compress_expand<_I, 2>;
    using idx_t=vec<_I, 2>;
    const idx_t idx=mem<idx_t>::load(tbl_t::_compress+2*cm());
    size_t n=tbl_t::_pop_cnt[cm()];
    vec<_T, 2> r=permute(src, idx);
    return std::make_pair(r, n);
}

template <typename _T, typename _I>
std::pair<cftal::vec<_T, 2>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, 2, _I>::
expand(const vec<_T, 2>& src,
       const typename vec<_T, 2>::mask_type& m)
{
    auto cm=compress_mask(m);
    using tbl_t=impl::compress_expand<_I, 2>;
    using idx_t=vec<_I, 2>;
    const idx_t idx=mem<idx_t>::load(tbl_t::_expand+2*cm());
    size_t n=tbl_t::_pop_cnt[cm()];
    vec<_T, 2> r=permute(src, idx);
    return std::make_pair(r, n);
}

template <typename _T, typename _I>
std::pair<cftal::vec<_T, 4>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, 4, _I>::
compress(const vec<_T, 4>& src,
	 const typename vec<_T, 4>::mask_type& m)
{
    auto cm=compress_mask(m);
    using tbl_t=impl::compress_expand<_I, 4>;
    using idx_t=vec<_I, 4>;
    const idx_t idx=mem<idx_t>::load(tbl_t::_compress+4*cm());
    size_t n=tbl_t::_pop_cnt[cm()];
    vec<_T, 4> r=permute(src, idx);
    return std::make_pair(r, n);
}

template <typename _T, typename _I>
std::pair<cftal::vec<_T, 4>, cftal::size_t>
cftal::impl::compress_expand_elements<_T, 4, _I>::
expand(const vec<_T, 4>& src,
       const typename vec<_T, 4>::mask_type& m)
{
    auto cm=compress_mask(m);
    using tbl_t=impl::compress_expand<_I, 4>;
    using idx_t=vec<_I, 4>;
    const idx_t idx=mem<idx_t>::load(tbl_t::_expand+4*cm());
    size_t n=tbl_t::_pop_cnt[cm()];
    vec<_T, 4> r=permute(src, idx);
    return std::make_pair(r, n);
}
#endif

template <typename _T, cftal::size_t _N, typename _ALG>
cftal::vec<_T, _N>
cftal::
exec_compressed(const _ALG& alg,
                size_t n,
                const vec<_T, _N>& a)
{
    constexpr const size_t _N2 = _N>>1;
    using v_t = vec<_T, _N>;
    using vh_t = vec<_T, _N2>;
    if (n > _N2) {
        return alg(a);
    }
    const vh_t hh(_T(0));
    vh_t lh=exec_compressed(alg, n, low_half(a));
    return v_t(lh, hh);
}

template <typename _T, typename _ALG>
cftal::vec<_T, 1>
cftal::
exec_compressed(const _ALG& alg,
                size_t n,
                const vec<_T, 1>& a)
{
    if (n)
        return alg(a);
    return vec<_T, 1>(_T(0));
}

template <typename _T, cftal::size_t _N, typename _ALG>
cftal::vec<_T, _N>
cftal::
compress_exec_expand(const _ALG& alg,
                     const mask_t<vec<_T, _N> >& m,
                     const vec<_T, _N>& a)
{
    constexpr const size_t _N2 = _N>>1;
    using v_t = vec<_T, _N>;
    using vh_t =  vec<_T, _N2>;

    vec<bit, _N> mc=compress_mask(m);
    size_t elems=popcnt(mc());
    if (elems > _N2) {
        return alg(a);
    }
    std::pair<v_t, size_t> ca_s=compress_elements(a, m);
    const vh_t hh(_T(0));
    vh_t lh=exec_compressed(alg, elems, low_half(ca_s.first));
    v_t cr(lh, hh);
    return expand_elements(cr, m).first;
}

template <typename _T, typename _ALG>
cftal::vec<_T, 1>
cftal::
compress_exec_expand(const _ALG& alg,
                     const mask_t<vec<_T, 1> >& m,
                     const vec<_T, 1>& a)
{
    if (impl::mask_to_bool<_T>::v(m())==true) {
        // if the mask is true, execute alg
        return alg(a);
    }
    return vec<_T, 1>(_T(0));
}

/*
 * Local variables:
 * mode: c++
 * end:
 */
#endif
