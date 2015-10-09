#if !defined (__CFTAL_VEC_TRAITS_H__)
#define __CFTAL_VEC_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/divisor.h>
#include <cftal/vec_cvt.h>
#include <cftal/x86_cast.h>
#include <cftal/d_real.h>

namespace cftal {

    template <std::size_t _N>
    struct d_real_traits<vec<double, _N> > : public has_fma<double> {
        using cmp_result_type = typename vec<double, _N>::mask_type;

        static
        bool any(const cmp_result_type& b) {
            return any_of(b);
        }

        static
        vec<double, _N>
        sel (const cmp_result_type& s,
             const vec<double, _N>& on_true,
             const vec<double, _N>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vec<double, _N> & a,
              vec<double, _N>& h,
              vec<double, _N>& l) {
            const vec<double, _N> msk(
                const_u64<0xf8000000U, 0xffffffffU>::v._f64);
            h = a & msk;
            l = a - h;
        }
    };

    template <std::size_t _N>
    struct d_real_traits<vec<float, _N> > : public has_fma<float> {
        using cmp_result_type = typename vec<float, _N>::mask_type;

        static
        bool any(const cmp_result_type& b) {
            return any_of(b);
        }

        static
        vec<float, _N>
        sel (const cmp_result_type& s,
             const vec<float, _N>& on_true,
             const vec<float, _N>& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void
        split(const vec<float, _N> & a,
              vec<float, _N>& h,
              vec<float, _N>& l) {
            const vec<float, _N> msk(
                const_u32<0xfffff000U>::v._f32);
            h = a & msk;
            l = a - h;
        }
    };

    namespace math {

        namespace impl {

            template <bool _HAS_MASK_TYPE, class _VR, class _VI>
            struct mask_helper {
                static
                typename _VR::mask_type
                mi_to_mf(const typename _VI::mask_type& mi) {
                    return as<typename _VR::mask_type>(mi);
                }
                static
                typename _VI::mask_type
                mf_to_mi(const typename _VR::mask_type& mi) {
                    return as<typename _VI::mask_type>(mi);
                }
            };

            template <bool _HAS_MASK_TYPE, class _VR, class _VI>
            struct mask_helper_v4 :
                public mask_helper<_HAS_MASK_TYPE, _VR, _VI> {
            };

            template <class  _VR, class _VI>
            struct mask_helper_v4<false, _VR, _VI> {
                static
                typename _VR::mask_type
                mi_to_mf(const typename _VI::mask_type& mi) {
                    typename _VI::mask_type xml=permute<0, 0, 1, 1>(mi);
                    typename _VI::mask_type xmh=permute<2, 2, 3, 3>(mi);
                    vec<double, 2> dml=as<vec<double, 2> >(xml);
                    vec<double, 2> dmh=as<vec<double, 2> >(xmh);
                    _VR r(dml, dmh);
                    return r;
                }
                static
                typename _VI::mask_type
                mf_to_mi(const typename _VR::mask_type& mf) {
                    v2f64 mfl=low_half(mf);
                    v2f64 mfh=high_half(mf);
                    _VI xml=as<_VI>(mfl);
                    _VI xmh=as<_VI>(mfh);
                    _VI xm =permute<0, 2, 4, 6>(xml, xmh);
                    return xm;
                }
            };

            template <bool _HAS_MASK_TYPE, class _VR, class _VI>
            struct mask_helper_v2 :
                public mask_helper<_HAS_MASK_TYPE, _VR, _VI> {
            };

            template <class  _VR, class _VI>
            struct mask_helper_v2<false, _VR, _VI> {
                static const vec<int32_t, 4> _mi_to_mf_msk[4];
                static
                typename _VR::mask_type
                mi_to_mf(const typename _VI::mask_type& mi) {
                    //int32_t l= low_half(mi)() == true ? 1 : 0;
                    // int32_t h= high_half(mi)() == true ? 2 : 0;
                    unsigned m= mi();
                    return as<_VR>(_mi_to_mf_msk[m]);
                }

                static const vec<bool, 2> _mf_to_mi_msk[4];

                static
                typename _VI::mask_type
                mf_to_mi(const typename _VR::mask_type& mf) {
                    unsigned m = read_signs(mf);
                    // return _mf_to_mi_msk[m];
                    return typename _VI::mask_type(m);
                }
            };

            template <class _VR, class _VI>
            const vec<int32_t, 4>
            mask_helper_v2<false, _VR, _VI>::_mi_to_mf_msk[4] = {
                {  0,  0,  0,  0},
                { -1, -1,  0,  0},
                {  0,  0, -1, -1},
                { -1, -1, -1, -1}
            };
            
            template <class _VR, class _VI>
            const vec<bool, 2>
            mask_helper_v2<false, _VR, _VI>::_mf_to_mi_msk[4] = {
                {false, false},
                {true, false},
                {false, true},
                {true, true}
            };
                
        }

        template <std::size_t _N>
        struct vec_func_traits_f32 : public func_traits<float, int32_t> {
            using vf_type = vec<float, _N>;
            using vmf_type = typename vf_type::mask_type;
            using vi_type = vec<int32_t, _N>;
            using vmi_type = typename vi_type::mask_type;

            using vhpf_type = vec<double, _N>;
            using hpf_traits = func_traits<vhpf_type, vi_type>;
            using dvf_type = d_real<vf_type>;

            static
            constexpr std::size_t vhpf_per_vf() {
                return 1;
            }
            
            static
            void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
                r[1] = cvt<vhpf_type, vf_type>(x);
            }

            static
            void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
                vf_type msv= cvt<vf_type>(hpf[0]);
                vf_type lsv= cvt<vf_type>(
                    vhpf_type(hpf[0] - cvt<vhpf_type>(msv)));
                res = dvf_type(msv, lsv);
            }

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return as<vmf_type>(mi);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return as<vmi_type>(mf);
            }
            static
            vi_type sel(const vmi_type& msk,
                        const vi_type& t, const vi_type& f) {
                return select(msk, t, f);
            }
            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return select(msk, t, f);
            }

            static
            vf_type insert_exp(const vi_type& e) {
                vi_type ep(e << 23);
                return as<vf_type>(ep);
            }

            static
            vi_type extract_exp(const vf_type& d) {
                vi_type e= as<vi_type>(d);
                e >>= 23;
                e &= vi_type(0xff);
                return e;
            }
            
            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<vf_type>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<vi_type>(f);
            }

            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<vi_type>(f);
            }

            static
            vi_type as_int(const vf_type& f) {
                return as<vi_type>(f);
            }

            static
            vf_type as_float(const vi_type& i) {
                return as<vf_type>(i);
            }

        };

        template <std::size_t _N>
        struct func_traits<vec<float, _N>, vec<int32_t, _N> >
            : public vec_func_traits_f32<_N> {};


        // template <std::size_t _N>
        // vec<int32_t, _N>
        // even_elements(vec<double, _N> v);

        // template <std::size_t _N>
        // vec<int32_t, _N>
        // odd_elements(vec<double, _N> v);

        // template <typename _T, std::size_t _N>
        // vec<_T, _N * 2>
        // combine_even_odd(vec<_T, _N> e, vec<_T, _N> o);
        
        template <std::size_t _N>
        struct vec_func_traits_f64 
            : public func_traits<double, int32_t> {
            using vf_type = vec<double, _N>;
            using vmf_type = typename vec<double, _N>::mask_type;
            using vi_type = vec<int32_t, _N>;
            using vmi_type = typename vec<int32_t, _N>::mask_type;
            
            static
            constexpr std::size_t NVF() {
                return _N;
            }

            static
            constexpr std::size_t NVI() {
                return _N;
            }

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return cvt_mask<double, int32_t, _N>::v(mi);
            }

            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return cvt_mask<int32_t, double_t, _N>::v(mf);
            }

            static
            vi_type sel(const vmi_type& msk,
                        const vi_type& t, const vi_type& f) {
                return select(msk, t, f);
            }
            static
            vf_type sel(const vmf_type& msk,
                        const vf_type& t, const vf_type& f) {
                return select(msk, t, f);
            }

            static
            vf_type insert_exp(const vi_type& e) {
                vi_type ep(e << 20);
                vec<int32_t, _N*2> ir(combine_even_odd(ep, ep));
                vf_type r= as<vf_type>(ir);
                r &= vf_type(exp_f64_msk::v._f64);
                return r;
            }

            static
            vi_type extract_exp(const vf_type& d) {
                const vf_type msk(exp_f64_msk::v._f64);
                vf_type m(d & msk);
                vec<int32_t, _N*2> di= as<vec<int32_t, _N*2> >(m);
                vi_type r= odd_elements(di);
                r >>= 20;
                return r;
            }
            
            static
            vi_type extract_high_word(const vf_type& d) {
                vec<int32_t, _N*2> di=as<vec<int32_t, _N*2> >(d);
                return odd_elements(di);
            }

            static
            vi_type extract_low_word(const vf_type& d) {
                vec<int32_t, _N*2> di=as<vec<int32_t, _N*2> >(d);
                return even_elements(di);
            }

            static
            vf_type combine_words(const vi_type& l,
                                  const vi_type& h) {
                vec<int32_t, _N*2> vi= combine_even_odd(l, h);
                vf_type r= as<vf_type>(vi);
                return r;
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<vf_type>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<vi_type>(f);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<vi_type>(f);
            }
        };

        template <std::size_t _N>
        struct func_traits<vec<double, _N>, vec<int32_t, _N> >
            : public vec_func_traits_f64<_N> {
        };

#if defined (__SSE2__)
        template <>
        struct func_traits<v2f64, v2s32>
            : public vec_func_traits_f64<2> {
            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                const bool has_mask_type =
                    sizeof(vmf_type) == sizeof(vmi_type);
                return impl::mask_helper_v2<has_mask_type,
                                            vf_type,
                                            vi_type>::mi_to_mf(mi);
            }

            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                const bool has_mask_type =
                    sizeof(vmf_type) == sizeof(vmi_type);
                return impl::mask_helper_v2<has_mask_type,
                                            vf_type,
                                            vi_type>::mf_to_mi(mf);
            }
        };
#endif
    }

}

// Local variables:
// mode: c++
// end:
#endif
