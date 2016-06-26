#if !defined (__CFTAL_X86_V4U64__)
#define __CFTAL_X86_V4U64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/vec_op.h>

namespace cftal {

    template <>
    class vec<uint64_t, 4> : public x86::vreg<__m256i> {
    public:
        using base_type = x86::vreg<__m256i>;

        using value_type = uint64_t;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = uint64_t;
#endif
        using mask_type= vec<mask_value_type, 4>;

        using base_type::base_type;
        vec() = default;
        vec(const vec<int64_t, 4>& v);
        // create vec{v,v}
        vec(uint64_t v);
        // create vec(l, h);
        vec(const vec<uint64_t, 2>& l, const vec<uint64_t, 2>& h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<uint64_t> l);
        // allow construction from vec<int64_t, 4>
        vec(init_list<uint64_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<uint64_t, 4>, _L, _R>& r);
    };

    template <>
    struct arg< vec<uint64_t, 4> > {
        using type = vec<uint64_t, 4>;
    };


    template <>
    struct mem< vec<uint64_t, 4> > {
        static
        vec<uint64_t, 4> load(const uint64_t* p, std::size_t n=4);
        static
        void store(uint64_t* p, const vec<uint64_t, 4>& v);
    };

    vec<uint64_t, 2>
    low_half(const vec<uint64_t, 4>& v);
    vec<uint64_t, 2>
    high_half(const vec<uint64_t, 4>& v);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<uint64_t, 4>::mask_type& v);
    bool
    any_of(const vec<uint64_t, 4>::mask_type& v);
    bool
    none_of(const vec<uint64_t, 4>::mask_type& v);
#endif

    v4u64 max(const v4u64& a, const v4u64& b);
    v4u64 min(const v4u64& a, const v4u64& b);

    vec<uint64_t, 4>
    select(const typename vec<uint64_t, 4>::mask_type& msk,
           const vec<uint64_t, 4>& on_true,
           const vec<uint64_t, 4>& on_false);

    template <bool _P0, bool _P1, bool _P2, bool _P3>
    vec<uint64_t, 4>
    select(const vec<uint64_t, 4>& on_true,
           const vec<uint64_t, 4>& on_false);

    template <int _P0, int _P1, int _P2, int _P3>
    vec<uint64_t, 4> permute(const vec<uint64_t, 4>& s);

    template <int _P0, int _P1, int _P2, int _P3>
    vec<uint64_t, 4> permute(const vec<uint64_t, 4>& s0,
                             const vec<uint64_t, 4>& s1);

    std::pair<vec<uint64_t, 4>, vec<uint64_t, 4> >
    mul_lo_hi(const vec<uint64_t, 4>& a,
              const vec<uint64_t, 4>& b);

}


// Local variables:
// mode: c++
// end:
#endif // __CFTAL_SIMD_X86_V4U64__
