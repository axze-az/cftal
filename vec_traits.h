#if !defined (__CFTAL_VEC_TRAITS_H__)
#define __CFTAL_VEC_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/divisor.h>
#include <cftal/x86_cvt.h>
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


        template <>
        struct func_traits<v2f64, v2s32> : public
        func_traits<typename v2f64::value_type,
                    typename v4s32::value_type> {
            typedef v2f64 vf_type;
            typedef v2f64::mask_type vmf_type;
            typedef v2s32 vi_type;
            typedef v2s32::mask_type vmi_type;

            static
            constexpr std::size_t NVF() {
                return sizeof(vf_type)/
                    sizeof(vf_type::value_type);
            }

            static
            constexpr std::size_t NVI() {
                return sizeof(vi_type)/
                    sizeof(vi_type::value_type);
            }
            
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
                vi_type t= e << 20;
                v4s32 tf(t, t);
                tf = permute<0, 0, 2, 2>(tf);
                vf_type r(as<v2f64>(tf));
                r &= v2f64(exp_f64_msk::v._f64);
                return r;
                // v2u64 m= as<v2u64>(ep);
                // m <<= const_shift::_52;
                // return as<v2f64>(m);

            }
            static
            vi_type extract_exp(const vf_type& d) {
                v4s32 e= as<v4s32>(d);
                e >>= 20; // const_shift::_20;
                e = permute<1, 3, 0, 0>(e);
                e &= v4s32{0x7ff, 0x7ff, 0, 0};
                return low_half(e);
            }

            static
            vi_type extract_high_word(const vf_type& d) {
                v4s32 w=as<v4s32>(d);
                w= permute<1, 3, 1, 3>(w);
                return low_half(w);

            }

            static
            vi_type extract_low_word(const vf_type& d) {
                v4s32 w=as<v4s32>(d);
                w= permute<0, 2, 0, 2>(w);
                return low_half(w);
            }

            static
            vf_type combine_words(const vi_type& l,
                                  const vi_type& h) {
                v4s32 c(l, h);
                c= permute<0, 2, 1, 3>(c);
                // permute<0, 4, 1, 5>(l, h);
                v2f64 r=as<vf_type>(c);
                return r;
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt_lo<v2f64>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt_lo<v2s32>(f);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz_lo<v2s32>(f);
            }
        };

        template <>
        struct func_traits<v4f32, v4s32> : public
        func_traits<typename v4f32::value_type,
                    typename v4s32::value_type> {
            using vf_type = v4f32;
            using vmf_type = vf_type::mask_type;
            using vi_type = v4s32;
            using vmi_type = vi_type::mask_type;
            using dvf_type = d_real<vf_type>;

            using vhpf_type = v2f64;
            using hpf_traits = func_traits<vhpf_type, v2s32>;

            static
            constexpr std::size_t vhpf_per_vf() {
                return 2;
            }

            static
            void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
                // using namespace x86;
                r[0] = cvt_lo<v2f64>(x);
                r[1] = cvt_hi<v2f64>(x);
            }

            static
            void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
                // using namespace x86;
                vf_type lo(cvt_lo<v4f32>(hpf[0]));
                vhpf_type rest(hpf[0] - cvt_lo<v2f64>(lo));
                vf_type lo_lo(cvt_lo<v4f32>(rest));

                vf_type hi(cvt_lo<v4f32>(hpf[1]));
                rest = hpf[1] - cvt_lo<v2f64>(hi);

                vf_type hi_lo(cvt_lo<v4f32>(rest));

                vf_type msv(permute<0, 1, 4, 5>(lo, hi));
                vf_type lsv(permute<0, 1, 4, 5>(lo_lo, hi_lo));
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
#if 0
            static
            vf_type gather(const float* p, const vi_type& idx,
                           int sc) {
                return gather<vf_type>(p, idx, sc);
            }
#endif
            static
            vf_type insert_exp(const vi_type& e) {
                vi_type ep(e << 23);
                return as<v4f32>(ep);
            }
            static
            vi_type extract_exp(const vf_type& d) {
                v4s32 e= as<v4s32>(d);
                e >>= 23;
                e &= v4s32{0xff, 0xff, 0xff, 0xff};
                return e;
            }
            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<v4f32>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<v4s32>(f);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<v4s32>(f);
            }

            static
            vi_type as_int(const vf_type& f) {
                return as<v4s32>(f);
            }

            static
            vf_type as_float(const vi_type& i) {
                return as<v4f32>(i);
            }
        };

#if 0        
        template <>
        struct func_traits<v4f64, v4s32> : public
        func_traits<typename v4f64::value_type,
                    typename v4s32::value_type> {
            typedef v4f64 vf_type;
            typedef v4f64::mask_type vmf_type;
            typedef v4s32 vi_type;
            typedef v4s32::mask_type vmi_type;

            static
            constexpr std::size_t NVF() {
                return sizeof(vf_type)/
                    sizeof(vf_type::value_type);
            }

            static
            constexpr std::size_t NVI() {
                return sizeof(vi_type)/
                    sizeof(vi_type::value_type);
            }

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                const bool has_mask_type =
                    sizeof(vmf_type) == sizeof(vmi_type);
                return impl::mask_helper_v4<has_mask_type,
                                            vf_type,
                                            vi_type>::mi_to_mf(mi);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                const bool has_mask_type =
                    sizeof(vmf_type) == sizeof(vmi_type);
                return impl::mask_helper_v4<has_mask_type,
                                            vf_type,
                                            vi_type>::mf_to_mi(mf);
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
#if 0
            static
            vf_type gather(const double* p, const vi_type& idx,
                           int sc) {
                return gather<vf_type>(p, idx, sc);
            }
#endif
            static
            vf_type insert_exp(const vi_type& e) {
                // TODO AVX2 code
                // 52 - 32
                vi_type ep(e << 20 /* const_shift::_20*/ );
                vi_type hep(permute<2, 2, 3, 3>(ep));
                vi_type lep(permute<0, 0, 1, 1>(ep));
                v2f64 fh(as<v2f64>(hep));
                v2f64 lh(as<v2f64>(lep));
                vf_type r(lh, fh);
                r &= vf_type(exp_f64_msk::v._f64);
                return r;
            }

            static
            vi_type extract_exp(const vf_type& d) {
                // TODO AVX2 code
                const vf_type msk(exp_f64_msk::v._f64);
                vf_type m(d & msk);
                v2f64 fh(high_half(d));
                v2f64 fl(low_half(d));
                v4s32 hi(as<v4s32>(fh));
                v4s32 li(as<v4s32>(fl));
                v4s32 r(permute<1, 3, 5, 7>(li, hi));
                r >>= 20 /* const_shift::_20*/;
                return r;
            }
            static
            vi_type extract_high_word(const vf_type& d) {
                v2f64 l= low_half(d);
                v2f64 h= high_half(d);
                v4s32 il=as<v4s32>(l);
                v4s32 ih=as<v4s32>(h);
                v4s32 w=permute<1, 3, 5, 7>(il, ih);
                return w;
            }

            static
            vi_type extract_low_word(const vf_type& d) {
                v2f64 l= low_half(d);
                v2f64 h= high_half(d);
                v4s32 il=as<v4s32>(l);
                v4s32 ih=as<v4s32>(h);
                v4s32 w=permute<0, 2, 4, 6>(il, ih);
                return w;
            }

            static
            vf_type combine_words(const vi_type& l,
                                  const vi_type& h) {
                v4s32 il=permute<0, 4, 1, 5>(l, h);
                v4s32 ih=permute<2, 6, 3, 7>(l, h);
                v2f64 fl=as<v2f64>(il);
                v2f64 fh=as<v2f64>(ih);
                vf_type r(fl, fh);
                return r;
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<v4f64>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<v4s32>(f);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<v4s32>(f);
            }
        };
#endif
        
        template <>
        struct func_traits<v8f32, v8s32> : public
        func_traits<typename v8f32::value_type,
                    typename v8s32::value_type> {
            using vf_type = v8f32;
            using vmf_type = vf_type::mask_type;
            using vi_type = v8s32 ;
            using vmi_type = vi_type::mask_type;

            using dvf_type = d_real<vf_type>;

            typedef v4f64 vhpf_type;
            typedef func_traits<vhpf_type, v4s32>
            hpf_traits;

            static
            constexpr std::size_t vhpf_per_vf() {
                return 2;
            }

            static
            void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
                // using namespace x86vec;
                // using impl::cvt;
                r[1] = cvt_hi<v4f64, v8f32>(x);
                r[0] = cvt_lo<v4f64, v8f32>(x);
            }

            static
            void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
                vf_type lo(cvt_lo<v8f32, v4f64>(hpf[0]));
                vhpf_type rest(hpf[0] - cvt_lo<v4f64, v8f32>(lo));
                vf_type lo_lo(cvt_lo<v8f32, v4f64>(rest));

                vf_type hi(cvt_lo<v8f32, v4f64>(hpf[1]));
                rest = hpf[1] - cvt_lo<v4f64, v8f32>(hi);

                vf_type hi_lo(cvt_lo<v8f32, v4f64>(rest));

                vf_type msv(permute<0, 1, 2, 3, 8, 9, 10, 11>(lo, hi));
                vf_type lsv(permute<0, 1, 2, 3, 8, 9, 10, 11>(lo_lo, hi_lo));
                res = dvf_type(msv, lsv);
            }

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return as<v8f32::mask_type>(mi);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return as<v8s32::mask_type>(mf);
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
#if 0
            static
            vf_type gather(const float* p, const vi_type& idx,
                           int sc) {
                return gather<vf_type>(p, idx, sc);
            }
#endif
            static
            vf_type insert_exp(const vi_type& e) {
                vi_type ep(e << 23);
                return as<v8f32>(ep);
            }
            static
            vi_type extract_exp(const vf_type& d) {
                v8s32 e= as<v8s32>(d);
                e >>= 23;
                e &= v8s32{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
                return e;
            }
            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt<v8f32>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt<v8s32>(f);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz<v8s32>(f);
            }

            static
            vi_type as_int(const vf_type& f) {
                return as<v8s32>(f);
            }

            static
            vf_type as_float(const vi_type& i) {
                return as<v8f32>(i);
            }
        };

        // template <typename _T, std::size_t _N>
        // vec<bit, _N>
        // std_vec_mask(typename vec<_T, _N>::mask_type v);

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
        struct func_traits<vec<double, _N>, vec<int32_t, _N> >
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
                // return vmf_type(std_vec_mask(mi));
                return cftal::impl::cvt_mask<double, int32_t, _N>::v(mi);
            }

            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return cftal::impl::cvt_mask<int32_t, double_t, _N>::v(mf);
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

    }

}

// Local variables:
// mode: c++
// end:
#endif
