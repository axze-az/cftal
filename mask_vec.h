#if !defined (__CFTAL_MASK_VEC_H__)
#define __CFTAL_MASK_VEC_H__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <type_traits>

namespace cftal {

    struct bit_mask {};
    
    template <typename _T, std::size_t _N>
    class mask_vec {      
        using utype = typename
            std::conditional<(_N>32), uint64_t,
            std::conditional<(_N>16), uint32_t,
            std::conditional<(_N>8), uint16_t,
            uint8_t> > >::type;
        utype _v;
    public:
        static const utype mask = _N-1; 
        mask_vec() = default;
        mask_vec(const mask_vec&) = default;
        mask_vec(mask_vec&&) = default;
        mask_vec& operator=(const mask_vec&) = default;
        mask_vec& operator=(mask_vec&&) = default;

        mask_vec(const mask_vec<_T, _N/2>& l, const mask_vec<_T, _N/2>& h,
                 typename std::enable_if<(_N>1)>::type* = nullptr) 
            : _v( (utype(l()) & ((_N/2)-1)) &
                  ((utype(h()) & ((_N/2)-1)) << _N/2)) {}
        template <typename _U>
        mask_vec(const mask_vec<_U, _N/2>& v) : _v(v()) {}
        mask_vec(utype v) : _v( v & mask) {}
        utype operator()() const { return _v; }
    };

    template <typename _T, std::size_t _N>
    typename std::enable_if<(_N>1), mask_vec<_T, _N/2> >::type
    low_half(const mask_vec<_T, _N>& v);

    template <typename _T, std::size_t _N>
    typename std::enable_if<(_N>1), mask_vec<_T, _N/2> >::type
    high_half(const mask_vec<_T, _N>& v);
    
    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>
    operator==(const mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>
    operator!=(const mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>
    operator~(const mask_vec<_T, _N>& a);
    
    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>
    operator^(const mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>&
    operator^=(mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);
    
    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>
    operator|(const mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>&
    operator|=(mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>
    operator&(const mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    mask_vec<_T, _N>&
    operator&=(mask_vec<_T, _N>& a, const mask_vec<_T, _N>& b);

    template <typename _T, std::size_t _N>
    bool
    all_of(const mask_vec<_T, _N>& a);

    template <typename _T, std::size_t _N>
    bool
    any_of(const mask_vec<_T, _N>& a);

    template <typename _T, std::size_t _N>
    bool
    none_of(const mask_vec<_T, _N>& a);
    
}

// Local variables:
// mode: c++
// end:
#endif
