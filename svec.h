#if !defined (__CFTAL_SVEC_H__)
#define __CFTAL_SVEC_H__ 1

#include <cftal/config.h>
#include <cftal/std_types.h>

namespace cftal {
        
        namespace simd {

                template <typename _T, std::size_t _N>
                class vec {
                public:
                        using half_type = vec<_T, _N/2>;
                        using mask_type = vec<bool, _N>;
                        vec() = default;
                        vec(const vec& r) = default;
                        vec(vec&& r) = default;
                        vec& operator=(const vec& r) = default;
                        vec& operator=(vec&& r) = default;
                        vec(const _T& v);
                        vec(const _T& v, bool splat);
                        vec(const half_type& lh, bool splat=true);
                        vec(const half_type& lh, const half_type& hh);
                        const half_type& lh() const;
                        const half_type& hh() const;
                private:
                        static_assert(0==(_N & _N-1), "_N is not a power of 2");
                        vec<_T, _N/2> _l;
                        vec<_T, _N/2> _h;
                };

                template <typename _T, std::size_t _N>
                const typename vec<_T, _N>::half_type&
                lo_half(const vec<_T, _N>& v);

                template <typename _T, std::size_t _N>
                const typename vec<_T, _N>::half_type&
                hi_half(const vec<_T, _N>& v);

                template <typename _T, std::size_t _N>
                vec<_T, _N> select(const typename vec<_T, _N>::mask_type& m,
                                   const vec<_T, _N>& on_true,
                                   const vec<_T, _N>& on_false);
                
                /* permute low and high halves of s */
                template <int _LH, int _HH,
                          typename _T, std::size_t _N>
                vec<_T, _N> permute(const vec<_T, _N>& s);

                /* permute low and high halves of s */
                template <int _LH, int _HH,
                          typename _T, std::size_t _N>
                vec<_T, _N> permute(const vec<_T, _N>& s0,
                                    const vec<_T, _N>& s1);
                



                template <typename _T>
                class vec<_T, 1> {
                public:
                        using mask_type = vec<bool, 1>;
                        vec() = default;
                        vec(const vec& r) = default;
                        vec(vec&& r) = default;
                        vec& operator=(const vec& r) = default;
                        vec& operator=(vec&& r) = default;
                        vec(const _T& v);
                        vec(const _T& v, bool splat);
                        _T operator()() const;
                private:
                        _T _v;
                };

                template <typename _T>
                vec<_T, 1> select(const typename vec<_T, 1>::mask_type& m,
                                  const vec<_T, 1>& on_true,
                                  const vec<_T, 1>& on_false);
                
                namespace ops {
                        
                        template <typename _T, std::size_t _N>
                        class op_add {
                                using full_type = vec<_T, _N>;
                                static 
                                full_type 
                                v(const full_type& a, const full_type& b) {
                                        return full_type( 
                                                op_add<_T, _N/2>::v(lo_half(a), 
                                                                    lo_half(b)),
                                                op_add<_T, _N/2>::v(hi_half(a), 
                                                                    hi_half(b)));
                                }
                        };

                        template <typename _T>
                        class op_add<_T, 1> {
                                using full_type = vec<_T, 1>;
                                static
                                full_type
                                v(const full_type& a, const full_type& b) {
                                        return full_type(a() + b());
                                }
                        };

                }
                
        }
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(const _T& v)
        : _l(v), _h(v)
{
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(const _T& v, bool splat)
        : _l(v, splat), _h(splat ? v : _T(0))
{
}

template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>::vec(const half_type& l,
                              const half_type& h)
        : _l(l), _h(h)
{
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::vec<_T, _N>::lh() const
{
        return _l;
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::vec<_T, _N>::hh() const
{
        return _h;
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::lo_half(const vec<_T, _N>& v) 
{
        return v.lh();
}

template <class _T, std::size_t _N>
inline
const typename cftal::simd::vec<_T, _N>::half_type&
cftal::simd::hi_half(const vec<_T, _N>& v)
{
        return v.hh();
}


template <class _T, std::size_t _N>
inline
cftal::simd::vec<_T, _N>
cftal::simd::select(const typename vec<_T, _N>::mask_type& m,
                    const vec<_T, _N>& on_true,
                    const vec<_T, _N>& on_false)
{
        return vec<_T, _N>();
}


// Local variables:
// mode: c++
// end:
#endif
