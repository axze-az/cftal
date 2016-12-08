#if !defined (__CFTAL_X86_V2S32__)
#define __CFTAL_X86_V2S32__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86/vreg.h>
#include <cftal/x86/vec_bit.h>
#include <cftal/x86/v2x32.h>
#include <cftal/vec_op.h>

#if 0
namespace cftal {

    template <>
    class vec<int32_t, 2> : public x86::vreg<x86::impl::s32_pair_type> {
    public:
        using base_type = x86::vreg<x86::impl::s32_pair_type>;

        using value_type = int32_t;
#if defined (__AVX512VL__)
        using mask_value_type = bit;
#else
        using mask_value_type = int32_t;
#endif
        using mask_type= vec<mask_value_type, 2>;

        // using base_type::base_type;
        vec() = default;
        vec(const vec<uint32_t,2>& v);
        // create vec{v,v}
        vec(int32_t v);
        vec(__m128i v);
        __m128i operator()() const;
        // create vec(l, h);
        vec(vec<int32_t, 1> l, vec<int32_t, 1> h);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int32_t> l);
        // allow construction from vec<int32_t, 8>
        vec(init_list<int32_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int32_t, 2>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int32_t, 2> > {
        using type = vec<int32_t, 2>;
    };

    template <>
    struct mem< vec<int32_t, 2> > {
        static
        vec<int32_t, 2> load(const int32_t* p, std::size_t n=2);
        static
        void store(int32_t* p, const vec<int32_t, 2>& v);
    };

    vec<int32_t, 1>
    low_half(const vec<int32_t, 2>& v);
    vec<int32_t, 1>
    high_half(const vec<int32_t, 2>& v);

#if !defined (__AVX512VL__)
    bool
    all_of(const vec<int32_t, 2>::mask_type& v);
    bool
    any_of(const vec<int32_t, 2>::mask_type& v);
    bool
    none_of(const vec<int32_t, 2>::mask_type& v);
#endif

    v2s32 max(const v2s32& a, const v2s32& b);
    v2s32 min(const v2s32& a, const v2s32& b);

    vec<int32_t, 2>
    select(const typename vec<int32_t, 2>::mask_type& msk,
           const vec<int32_t, 2>& on_true,
           const vec<int32_t, 2>& on_false);

    template <bool _P0, bool _P1>
    vec<int32_t, 2>
    select(const vec<int32_t, 2>& on_true,
           const vec<int32_t, 2>& on_false);

    template <int32_t _P0, int32_t _P1>
    vec<int32_t, 2> permute(const vec<int32_t, 2>& s);

    template <int32_t _P0, int32_t _P1>
    vec<int32_t, 2> permute(const vec<int32_t, 2>& s0,
                            const vec<int32_t, 2>& s1);

    std::pair<vec<int32_t, 2>, vec<int32_t, 2> >
    mul_lo_hi(const vec<int32_t, 2>& a, const vec<int32_t, 2>& b);

}
#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S32__
