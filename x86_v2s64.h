#if !defined (__CFTAL_X86_V2S64__)
#define __CFTAL_X86_V2S64__ 1

#include <cftal/config.h>
#include <cftal/types.h>
#include <cftal/x86_vreg.h>
#include <cftal/vec_op.h>

namespace cftal {

    template <>
    class vec<int64_t, 2> : public x86::vreg<__m128i> {
    public:
        using base_type = x86::vreg<__m128i>;

        using value_type = int64_t;
        using mask_value_type = int64_t;
        using mask_type= vec<mask_value_type, 2>;

        using base_type::base_type;
        vec() = default;
        vec(const v4u32& v);
        // create vec{v,v,v,v}
        vec(int64_t v);
        // constructor from std::initializer_list, fills remaining
        // elements with the last one given
        vec(std::initializer_list<int64_t> l);
        // allow construction from vec<int64_t, 8>
        vec(init_list<int64_t> l);
        // expression template constructor
        template <template <class _U, std::size_t _M>
                  class _OP,
                  class _L, class _R>
        vec(const expr<_OP<int64_t, 2>, _L, _R>& r);
    };

    template <>
    struct arg< vec<int64_t, 2> > {
        using type = vec<int64_t, 2>;
    };
   
    template <>
    struct mem< vec<int64_t, 2> > {
        static
        vec<int64_t, 2> load(const int64_t* p, std::size_t n=4);
        static
        void store(int64_t* p, const vec<int64_t, 2>& v);
    };
    
    v2s64 max(const v2s64& a, const v2s64& b);
    v2s64 min(const v2s64& a, const v2s64& b);
  
    vec<int64_t, 2> 
    select(const typename vec<int64_t, 2>::mask_type& msk,
           const vec<int64_t, 2>& on_true,
           const vec<int64_t, 2>& on_false);

    template <bool _P0, bool _P1, 
              bool _P2, bool _P3>
    vec<int64_t, 2> 
    select(const vec<int64_t, 2>& on_true,
           const vec<int64_t, 2>& on_false);

    template <int64_t _P0, int64_t _P1,
              int64_t _P2, int64_t _P3>
    vec<int64_t, 2> permute(const vec<int64_t, 2>& s);

    template <int64_t _P0, int64_t _P1,
              int64_t _P2, int64_t _P3>
    vec<int64_t, 2> permute(const vec<int64_t, 2>& s0, 
                            const vec<int64_t, 2>& s1);

    std::pair<vec<int64_t, 2>, vec<int64_t, 2> >
    mul_lo_hi(const vec<int64_t, 2>& a, const vec<int64_t, 2>& b);
    
}    

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V2S64__
