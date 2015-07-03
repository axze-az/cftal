#if !defined (__CFTAL_VEC_T_N_H__)
#define __CFTAL_VEC_T_N_H__ 1

#include <cftal/config.h>
#include <cftal/expr.h>
#include <cftal/constants.h>
#include <cftal/init_list.h>
#include <cftal/mem.h>

namespace cftal {

    template <typename _T>
    struct arg {
        using type = const _T&;
    };

    template <typename _T, std::size_t _N >
    class /* alignas(const_min<128, sizeof(_T)*_N>::v)*/ vec {
    public:
        // value type
        using value_type = _T;
        // vector with half the length
        using half_type = vec<_T, _N/2>;
        // type of value of a mask vector
        using mask_value_type =
            typename half_type::mask_value_type;
        // vector of mask values
        using mask_type = vec<mask_value_type, _N>;

        vec() = default;
        vec(const vec& r) = default;
        vec(vec&& r) = default;
        vec& operator=(const vec& r) = default;
        vec& operator=(vec&& r) = default;

        vec(const _T& v);
        vec(const _T& v, bool splat);
        vec(std::initializer_list<_T> l);
        vec(init_list<_T> l);
        vec(const half_type& lh, bool splat=true);
        vec(const half_type& lh, const half_type& hh);
        const half_type& lh() const;
        const half_type& hh() const;

        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
            vec(const expr<_OP<_T, _N>, _L, _R>& r);

    private:
        static_assert(0==(_N & (_N-1)),
                      "vec<_T, _N>: _N is not a power of 2");
        half_type _l;
        half_type _h;
    };

    using v2f64 = vec<double, 2>;
    using v4f64 = vec<double, 4>;
    using v8f64 = vec<double, 8>;

    using v4f32 = vec<float, 4>;
    using v8f32 = vec<float, 8>;
    using v16f32= vec<float, 16>;

    using v8s16 = vec<int16_t, 8>;
    using v8u16 = vec<uint16_t, 8>;
    using v16s16= vec<int16_t, 16>;
    using v16u16= vec<uint16_t, 16>;

    using v2s32 = vec<int32_t, 2>;
    using v2u32 = vec<uint32_t, 2>;
    using v4s32 = vec<int32_t, 4>;
    using v4u32 = vec<uint32_t, 4>;
    using v8s32 = vec<int32_t, 8>;
    using v8u32 = vec<uint32_t, 8>;

    using v2s64 = vec<int64_t, 2>;
    using v2u64 = vec<uint64_t, 2>;
    using v4s64 = vec<int64_t, 4>;
    using v4u64 = vec<uint64_t, 4>;

    template <typename _T, std::size_t _N>
    const typename vec<_T, _N>::half_type&
    low_half(const vec<_T, _N>& v);

    template <typename _T, std::size_t _N>
    const typename vec<_T, _N>::half_type&
    high_half(const vec<_T, _N>& v);

    template <std::size_t _I, typename _T, std::size_t _N>
    _T extract(const vec<_T, _N>& v);

    // test if all elements lt 0 / have their MSB set
    template <typename _T, std::size_t _N>
    bool all_of(const vec<_T, _N>& v);
    // test if any element lt 0 / has its MSB set
    template <typename _T, std::size_t _N>
    bool any_of(const vec<_T, _N>& v);
    // test of no element lt 0 / MSB is not set
    template <typename _T, std::size_t _N>
    bool none_of(const vec<_T, _N>& v);

    template <typename _T, std::size_t _N>
    vec<_T, _N>
    select(const typename vec<_T, _N>::mask_type& m,
           const vec<_T, _N>& on_true,
           const vec<_T, _N>& on_false);

    template <bool _I0, bool _I1, typename _T>
    vec<_T, 2>
    select(const vec<_T, 2>& a, const vec<_T, 2>& b);

    template <bool _I0, bool _I1, bool _I2, bool _I3, typename _T>
    vec<_T, 4>
    select(const vec<_T, 4>& a, const vec<_T, 4>& b);

    template <bool _I0, bool _I1, bool _I2, bool _I3,
              bool _I4, bool _I5, bool _I6, bool _I7, typename _T>
    vec<_T, 8>
    select(const vec<_T, 8>& a, const vec<_T, 8>& b);

    template <bool _I0, bool _I1, bool _I2, bool _I3,
              bool _I4, bool _I5, bool _I6, bool _I7,
              bool _I8, bool _I9, bool _IA, bool _IB,
              bool _IC, bool _ID, bool _IE, bool _IF, typename _T>
    vec<_T, 16>
    select(const vec<_T, 16>& a, const vec<_T, 16>& b);

    template <int32_t _I0, int32_t _I1, typename _T>
    vec<_T, 2>
    permute(const vec<_T, 2>& v);

    template <int32_t _I0, int32_t _I1, typename _T>
    vec<_T, 2>
    permute(const vec<_T, 2>& v0, const vec<_T, 2>& v1);

    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              typename _T>
    vec<_T, 4>
    permute(const vec<_T, 4>& v);

    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              typename _T>
    vec<_T, 4>
    permute(const vec<_T, 4>& v0, const vec<_T, 4>& v1);

    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              typename _T>
    vec<_T, 8>
    permute(const vec<_T, 8>& v);

    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              typename _T>
    vec<_T, 8>
    permute(const vec<_T, 8>& v0, const vec<_T, 8>& v1);

    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
              int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
              typename _T>
    vec<_T, 16>
    permute(const vec<_T, 16>& v);

    template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
              int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
              int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
              int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
              typename _T>
    vec<_T, 16>
    permute(const vec<_T, 16>& v0, const vec<_T, 16>& v1);

    // helper function for even_elements, odd_elements: returns even
    // elements in low half, odd elements in high half
    template <typename _T>
    vec<_T, 4>
    sort_even_odd(const vec<_T, 4>& v);

    template <typename _T>
    vec<_T, 8>
    sort_even_odd(const vec<_T, 8>& v);

    template <typename _T>
    vec<_T, 16>
    sort_even_odd(const vec<_T, 16>& v);
    
    template <typename _T, std::size_t _N>
    vec<_T, _N/2>
    even_elements(const vec<_T, _N>& v);

    template <typename _T>
    vec<_T, 8>
    even_elements(const vec<_T, 16>& v);

    template <typename _T>
    vec<_T, 4>
    even_elements(const vec<_T, 8>& v);

    template <typename _T>
    vec<_T, 2>
    even_elements(const vec<_T, 4>& v);
    
    template <typename _T>
    vec<_T, 1>
    even_elements(const vec<_T, 2>& v);

    template <typename _T, std::size_t _N>
    vec<_T, _N/2>
    odd_elements(const vec<_T, _N>& v);

    template <typename _T>
    vec<_T, 8>
    odd_elements(const vec<_T, 16>& v);

    template <typename _T>
    vec<_T, 4>
    odd_elements(const vec<_T, 8>& v);

    template <typename _T>
    vec<_T, 2>
    odd_elements(const vec<_T, 4>& v);

    template <typename _T>
    vec<_T, 1>
    odd_elements(const vec<_T, 2>& v);
    
    template <typename _T, std::size_t _N>
    vec<_T, _N*2>
    combine_even_odd(const vec<_T, _N>& e, const vec<_T, _N>& o);

    template <typename _T>
    vec<_T, 2>
    combine_even_odd(const vec<_T, 1>& e, const vec<_T, 1>& o);
    
    template <typename _T, std::size_t _N>
    bool
    elements_equal(const vec<_T, _N>& v);

    template <typename _T>
    bool
    elements_equal(const vec<_T, 2>& v);

    template <typename _T, std::size_t _N>
    vec<_T, _N>
    max(const vec<_T, _N>& a, const vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    vec<_T, _N>
    min(const vec<_T, _N>& a, const vec<_T, _N>& b);

    template <class _T, std::size_t _N>
    struct mem< vec<_T, _N> > {
        static
        vec<_T, _N> load(const _T* p, std::size_t n=_N) {
            return vec<_T,_N>(init_list<_T>(p, p+n));
        }
        static
        void store(_T* p, const vec<_T, _N>& v) {
            mem< vec<_T, _N/2> >::store(p, low_half(v));
            mem< vec<_T, _N/2> >::store(p+_N/2, high_half(v));
        }
    };
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const _T& v)
    : _l(v), _h(v)
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const _T& v, bool splat)
    : _l(v, splat), _h(splat ? v : _T(0))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(std::initializer_list<_T> l)
    : vec(init_list<_T>(l.begin(), l.end()))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(init_list<_T> l)
    : _l(init_lo_half<_T, _N>(l)),
      _h(init_hi_half<_T, _N>(l))
{
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>::vec(const half_type& l,
                        const half_type& h)
    : _l(l), _h(h)
{
}

template <typename _T, std::size_t _N>
template <template <class _U, std::size_t _M>
          class _OP,
          class _L, class _R>
cftal::vec<_T, _N>::vec(const expr<_OP<_T, _N>, _L, _R>& r)
    : vec(eval(r))
{
}


template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::vec<_T, _N>::lh() const
{
    return _l;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::vec<_T, _N>::hh() const
{
    return _h;
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::low_half(const vec<_T, _N>& v)
{
    return v.lh();
}

template <class _T, std::size_t _N>
inline
const typename cftal::vec<_T, _N>::half_type&
cftal::high_half(const vec<_T, _N>& v)
{
    return v.hh();
}

template <std::size_t _I, class _T, std::size_t _N>
inline
_T
cftal::extract(const vec<_T, _N>& v)
{
    static_assert(_I < _N, "invalid offset in extract(vec<_T, _N>)");
    _T r;
    if (_I < _N/2) {
        r = extract<_I>(low_half(v));
    } else {
        r = extract< _I ? (_I-_N/2) : 0 >(high_half(v));
    }
    return r;
}

template <class _T, std::size_t _N>
inline
bool
cftal::all_of(const vec<_T, _N>& v)
{
    return all_of(low_half(v)) && all_of(high_half(v));
}

template <class _T, std::size_t _N>
inline
bool
cftal::any_of(const vec<_T, _N>& v)
{
    return any_of(low_half(v)) || any_of(high_half(v));
}

template <class _T, std::size_t _N>
inline
bool
cftal::none_of(const vec<_T, _N>& v)
{
    return none_of(low_half(v)) && none_of(high_half(v));
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::select(const typename vec<_T, _N>::mask_type& m,
              const vec<_T, _N>& on_true,
              const vec<_T, _N>& on_false)
{
    vec<_T, _N> res(
        select(low_half(m), low_half(on_true), low_half(on_false)),
        select(high_half(m), high_half(on_true), high_half(on_false)));
    return res;
}

template <bool _I0, bool _I1, class _T>
inline
cftal::vec<_T, 2>
cftal::select(const vec<_T, 2>& a, const vec<_T, 2>& b)
{
    return vec<_T, 2>(_I0 ? low_half(a) : low_half(b),
                      _I1 ? high_half(a) : high_half(b));
}

template <bool _I0, bool _I1, bool _I2, bool _I3, class _T>
inline
cftal::vec<_T, 4>
cftal::select(const vec<_T, 4>& a, const vec<_T, 4>& b)
{
    return vec<_T, 4>(select<_I0, _I1>(low_half(a), low_half(b)),
                      select<_I2, _I3>(high_half(a), high_half(b)));
}

template <bool _I0, bool _I1, bool _I2, bool _I3,
          bool _I4, bool _I5, bool _I6, bool _I7, class _T>
inline
cftal::vec<_T, 8>
cftal::select(const vec<_T, 8>& a, const vec<_T, 8>& b)
{
    return vec<_T, 8>(select<_I0, _I1, _I2, _I3>(low_half(a), low_half(b)),
                      select<_I4, _I5, _I6, _I7>(high_half(a), high_half(b)));
}

template <bool _I0, bool _I1, bool _I2, bool _I3,
          bool _I4, bool _I5, bool _I6, bool _I7,
          bool _I8, bool _I9, bool _IA, bool _IB,
          bool _IC, bool _ID, bool _IE, bool _IF, class _T>
inline
cftal::vec<_T, 16>
cftal::select(const vec<_T, 16>& a, const vec<_T, 16>& b)
{
    return vec<_T, 16>(
        select<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(low_half(a),
                                                       low_half(b)),
        select<_I8, _I9, _IA, _IB, _IC, _ID, _IE, _IF>(high_half(a),
                                                       high_half(b)));
}

template <class _T, std::size_t _N>
inline
bool
cftal::elements_equal(const vec<_T, _N>& v)
{
    bool lh= elements_equal(low_half(v));
    bool hh= elements_equal(high_half(v));
    bool r = lh && hh;
    return r;
}

template <class _T>
inline
bool
cftal::elements_equal(const vec<_T, 2>& v)
{
    return extract<0>(v) == extract<1>(v);
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::max(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return vec<_T, _N>(max(low_half(a), low_half(b)),
                       max(high_half(a), high_half(b)));
}

template <class _T, std::size_t _N>
inline
cftal::vec<_T, _N>
cftal::min(const vec<_T, _N>& a, const vec<_T, _N>& b)
{
    return vec<_T, _N>(min(low_half(a), low_half(b)),
                       min(high_half(a), high_half(b)));
}

template <int32_t _I0, int32_t _I1, typename _T>
inline
cftal::vec<_T, 2>
cftal::permute(const vec<_T, 2>& v)
{
    const vec<_T, 1> lv= low_half(v);
    const vec<_T, 1> hv= high_half(v);
    // low half of the result vector
    // vec<_T, 1> lr = permute<_I0>(lv, hv);
    vec<_T, 1> lr = (_I0 < 0 ? vec<_T, 1>(_T(0)) :
                     (_I0 == 0 ? lv : hv));
    // high half of the result vector
    // vec<_T, 1> hr = permute<_I1>(lv, hv);
    vec<_T, 1> hr = (_I1 < 0 ? vec<_T, 1>(_T(0)) :
                     (_I1 == 0 ? lv : hv));
    return vec<_T, 2>(lr, hr);
}

template <int32_t _I0, int32_t _I1, typename _T>
inline
cftal::vec<_T, 2>
cftal::permute(const vec<_T, 2>& v0, const vec<_T, 2>& v1)
{
    // select elements from v0
    const int32_t i0= _I0 < 2 ? _I0 : -1;
    const int32_t i1= _I1 < 2 ? _I1 : -1;
    vec<_T, 2> ri = permute<i0, i1>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 2 ? _I0-2 : -1;
    const int32_t j1= _I1 >= 2 ? _I1-2 : -1;
    vec<_T, 2> rj = permute<j0, j1>(v1);
    // combine result sets:
    vec<_T, 2> r( ri | rj);
    return r;
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          typename _T>
inline
cftal::vec<_T, 4>
cftal::permute(const vec<_T, 4>& v)
{
    const vec<_T, 2> lv= low_half(v);
    const vec<_T, 2> hv= high_half(v);
    // low half of the result vector
    vec<_T, 2> lr = permute<_I0, _I1>(lv, hv);
    // high half of the result vector
    vec<_T, 2> hr = permute<_I2, _I3>(lv, hv);
    return vec<_T, 4>(lr, hr);
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          typename _T>
inline
cftal::vec<_T, 4>
cftal::permute(const vec<_T, 4>& v0, const vec<_T, 4>& v1)
{
    // select elements from v0
    const int32_t i0= _I0 < 4 ? _I0 : -1;
    const int32_t i1= _I1 < 4 ? _I1 : -1;
    const int32_t i2= _I2 < 4 ? _I2 : -1;
    const int32_t i3= _I3 < 4 ? _I3 : -1;
    vec<_T, 4> ri = permute<i0, i1, i2, i3>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 4 ? _I0-4 : -1;
    const int32_t j1= _I1 >= 4 ? _I1-4 : -1;
    const int32_t j2= _I2 >= 4 ? _I2-4 : -1;
    const int32_t j3= _I3 >= 4 ? _I3-4 : -1;
    vec<_T, 4> rj = permute<j0, j1, j2, j3>(v1);
    // combine result sets:
    vec<_T, 4> r( ri | rj);
    return r;
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          typename _T>
inline
cftal::vec<_T, 8>
cftal::permute(const vec<_T, 8>& v)
{
    const vec<_T, 4> lv= low_half(v);
    const vec<_T, 4> hv= high_half(v);
    // low half of the result vector
    vec<_T, 4> lr = permute<_I0, _I1, _I2, _I3>(lv, hv);
    // high half of the result vector
    vec<_T, 4> hr = permute<_I4, _I5, _I6, _I7>(lv, hv);
    return vec<_T, 8>(lr, hr);
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          typename _T>
inline
cftal::vec<_T, 8>
cftal::permute(const vec<_T, 8>& v0, const vec<_T, 8>& v1)
{
    // select elements from v0
    const int32_t i0= _I0 < 8 ? _I0 : -1;
    const int32_t i1= _I1 < 8 ? _I1 : -1;
    const int32_t i2= _I2 < 8 ? _I2 : -1;
    const int32_t i3= _I3 < 8 ? _I3 : -1;
    const int32_t i4= _I4 < 8 ? _I4 : -1;
    const int32_t i5= _I5 < 8 ? _I5 : -1;
    const int32_t i6= _I6 < 8 ? _I6 : -1;
    const int32_t i7= _I7 < 8 ? _I7 : -1;
    vec<_T, 8> ri = permute<i0, i1, i2, i3, i4, i5, i6, i7>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 8 ? _I0-8 : -1;
    const int32_t j1= _I1 >= 8 ? _I1-8 : -1;
    const int32_t j2= _I2 >= 8 ? _I2-8 : -1;
    const int32_t j3= _I3 >= 8 ? _I3-8 : -1;
    const int32_t j4= _I4 >= 8 ? _I4-8 : -1;
    const int32_t j5= _I5 >= 8 ? _I5-8 : -1;
    const int32_t j6= _I6 >= 8 ? _I6-8 : -1;
    const int32_t j7= _I7 >= 8 ? _I7-8 : -1;
    vec<_T, 8> rj = permute<j0, j1, j2, j3, j4, j5, j6, j7>(v1);
    // combine result sets:
    vec<_T, 8> r( ri | rj);
    return r;
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
          int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
          typename _T>
inline
cftal::vec<_T, 16>
cftal::permute(const vec<_T, 16>& v)
{
    const vec<_T, 8> lv= low_half(v);
    const vec<_T, 8> hv= high_half(v);
    // low half of the result vector
    vec<_T, 8> lr = permute<_I0, _I1, _I2, _I3, _I4, _I5, _I6, _I7>(lv, hv);
    // high half of the result vector
    vec<_T, 8> hr = permute<_I8, _I9, _IA, _IB, _IC, _ID, _IE, _IF>(lv, hv);
    return vec<_T, 16>(lr, hr);
}

template <int32_t _I0, int32_t _I1, int32_t _I2, int32_t _I3,
          int32_t _I4, int32_t _I5, int32_t _I6, int32_t _I7,
          int32_t _I8, int32_t _I9, int32_t _IA, int32_t _IB,
          int32_t _IC, int32_t _ID, int32_t _IE, int32_t _IF,
          typename _T>
inline
cftal::vec<_T, 16>
cftal::permute(const vec<_T, 16>& v0, const vec<_T, 16>& v1)
{
    // select elements from v0
    const int32_t k0= _I0 < 16 ? _I0 : -1;
    const int32_t k1= _I1 < 16 ? _I1 : -1;
    const int32_t k2= _I2 < 16 ? _I2 : -1;
    const int32_t k3= _I3 < 16 ? _I3 : -1;
    const int32_t k4= _I4 < 16 ? _I4 : -1;
    const int32_t k5= _I5 < 16 ? _I5 : -1;
    const int32_t k6= _I6 < 16 ? _I6 : -1;
    const int32_t k7= _I7 < 16 ? _I7 : -1;

    const int32_t k8= _I8 < 16 ? _I8 : -1;
    const int32_t k9= _I9 < 16 ? _I9 : -1;
    const int32_t ka= _IA < 16 ? _IA : -1;
    const int32_t kb= _IB < 16 ? _IB : -1;
    const int32_t kc= _IC < 16 ? _IC : -1;
    const int32_t kd= _ID < 16 ? _ID : -1;
    const int32_t ke= _IE < 16 ? _IE : -1;
    const int32_t kf= _IF < 16 ? _IF : -1;

    vec<_T, 16> ri = permute<k0, k1, k2, k3, k4, k5, k6, k7,
                             k8, k9, ka, kb, kc, kd, ke, kf>(v0);
    // select elements from v1
    const int32_t j0= _I0 >= 16 ? _I0-16 : -1;
    const int32_t j1= _I1 >= 16 ? _I1-16 : -1;
    const int32_t j2= _I2 >= 16 ? _I2-16 : -1;
    const int32_t j3= _I3 >= 16 ? _I3-16 : -1;
    const int32_t j4= _I4 >= 16 ? _I4-16 : -1;
    const int32_t j5= _I5 >= 16 ? _I5-16 : -1;
    const int32_t j6= _I6 >= 16 ? _I6-16 : -1;
    const int32_t j7= _I7 >= 16 ? _I7-16 : -1;

    const int32_t j8= _I8 >= 16 ? _I8 : -1;
    const int32_t j9= _I9 >= 16 ? _I9 : -1;
    const int32_t ja= _IA >= 16 ? _IA : -1;
    const int32_t jb= _IB >= 16 ? _IB : -1;
    const int32_t jc= _IC >= 16 ? _IC : -1;
    const int32_t jd= _ID >= 16 ? _ID : -1;
    const int32_t je= _IE >= 16 ? _IE : -1;
    const int32_t jf= _IF >= 16 ? _IF : -1;

    vec<_T, 16> rj = permute<j0, j1, j2, j3, j4, j5, j6, j7,
                             j8, j9, ja, jb, jc, jd, je, jf>(v1);
    // combine result sets:
    vec<_T, 16> r( ri | rj);
    return r;
}

template <typename _T>
cftal::vec<_T, 4>
cftal::sort_even_odd(const vec<_T, 4>& v)
{
    return permute<0, 2, 1, 3>(v);
}

template <typename _T>
cftal::vec<_T, 8>
cftal::sort_even_odd(const vec<_T, 8>& v)
{
    return permute<0, 2, 4, 6, 1, 3, 5, 7>(v);
}

template <typename _T>
cftal::vec<_T, 16>
cftal::sort_even_odd(const vec<_T, 16>& v)
{
    return permute<0, 2, 4, 6, 8, 10, 12, 14,
                   1, 3, 5, 7, 9, 11, 13, 15>(v);
}

template <typename _T, std::size_t _N>
cftal::vec<_T, _N/2>
cftal::even_elements(const vec<_T, _N>& v)
{
    return vec<_T, _N/2>(even_elements(low_half(v)),
                         even_elements(high_half(v)));
}

template <typename _T>
cftal::vec<_T, 8>
cftal::even_elements(const vec<_T, 16>& v)
{
    return low_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 4>
cftal::even_elements(const vec<_T, 8>& v)
{
    return low_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 2>
cftal::even_elements(const vec<_T, 4>& v)
{
    return low_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 1>
cftal::even_elements(const vec<_T, 2>& v)
{
    return low_half(v);
}

        
template <typename _T, std::size_t _N>
cftal::vec<_T, _N/2>
cftal::odd_elements(const vec<_T, _N>& v)
{
    return vec<_T, _N/2>(odd_elements(low_half(v)),
                         odd_elements(high_half(v)));
}

template <typename _T>
cftal::vec<_T, 8>
cftal::odd_elements(const vec<_T, 16>& v)
{
    return high_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 4>
cftal::odd_elements(const vec<_T, 8>& v)
{
    return high_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 2>
cftal::odd_elements(const vec<_T, 4>& v)
{
    return high_half(sort_even_odd(v));
}

template <typename _T>
cftal::vec<_T, 1>
cftal::odd_elements(const vec<_T, 2>& v)
{
    return high_half(v);
}
        

template <typename _T, std::size_t _N>
cftal::vec<_T, _N*2>
cftal::combine_even_odd(const vec<_T, _N>& e, const vec<_T, _N>& o)
{
    return vec<_T, _N*2>(combine_even_odd(low_half(e), low_half(o)),
                         combine_even_odd(high_half(e), high_half(o)));
}

template <typename _T>
cftal::vec<_T, 2>
cftal::combine_even_odd(const vec<_T, 1>& e, const vec<_T, 1>& o)
{
    return vec<_T, 2>(e, o);
}




// Local variables:
// mode: c++
// end:
#endif
