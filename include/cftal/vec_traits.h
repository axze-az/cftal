#if !defined (__CFTAL_VEC_TRAITS_H__)
#define __CFTAL_VEC_TRAITS_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/divisor.h>
#include <cftal/vec_cvt.h>
#include <cftal/constants.h>
#include <cftal/d_real.h>
#include <cftal/x86/cast.h>
#include <cftal/d_real.h>

namespace cftal {

    template <std::size_t _N>
    struct d_real_traits<vec<double, _N> > : public has_fma<double> {
        using cmp_result_type = typename vec<double, _N>::mask_type;
        using int_type = vec<int32_t, _N>;
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

        constexpr
        static
        vec<double, _N>
        scale_div_threshold() {
            // -1022 + 53
            return vec<double, _N>(0x1.p-969);
        }

    };

    template <std::size_t _N>
    struct d_real_traits<vec<float, _N> > : public has_fma<float> {
        using cmp_result_type = typename vec<float, _N>::mask_type;
        using int_type = vec<int32_t, _N>;

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

        constexpr
        static
        vec<float, _N>
        scale_div_threshold() {
            // -126 + 24
            return 0x1.p-102f;
        }

    };

    namespace math {


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
            constexpr std::size_t NVF() {
                return _N;
            }

            static
            constexpr std::size_t NVI() {
                return _N;
            }

            static
            constexpr std::size_t vhpf_per_vf() {
                return 1;
            }

            static
            void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
                r[0] = cvt<vhpf_type, vf_type>(x);
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
                e &= vi_type(e_mask);
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
            // integer vector with the same length as vf_type
            using vi2_type = vec<int32_t, 2*_N >;
            using vmi2_type = vec<int32_t, 2* _N>;

            using vli_type = vec<int64_t, _N>;

            using dvf_type = d_real<vf_type>;

            static
            constexpr std::size_t NVF() {
                return _N;
            }

            static
            constexpr std::size_t NVI() {
                return _N;
            }

            static
            vmf_type
            vmi_to_vmf(const vmi_type& mi) {
                return
                    cvt_mask<typename vmf_type::value_type, _N,
                             typename vmi_type::value_type, _N>::v(mi);
            }

            static
            vmi_type
            vmf_to_vmi(const vmf_type& mf) {
                return
                    cvt_mask<typename vmi_type::value_type, _N,
                             typename vmf_type::value_type, _N>::v(mf);
            }

            static
            vmi2_type
            vmf_to_vmi2(const vmf_type& mf) {
                return
                    cvt_mask<typename vmi2_type::value_type, 2 * _N,
                             typename vmf_type::value_type, _N>::v(mf);
            };

            static
            vmf_type
            vmi2_to_vmf(const vmi2_type& mf) {
                return
                    cvt_mask<typename vmf_type::value_type, _N,
                             typename vmi2_type::value_type, 2*_N>::v(mf);
            };

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
            vi2_type sel(const vmi2_type& msk,
                         const vi2_type& t, const vi2_type& f) {
                return select(msk, t, f);
            }

            static
            vf_type insert_exp(const vi2_type& e) {
                vi2_type ep(e << 20);
                vf_type r= as<vf_type>(ep);
                r &= vf_type(exp_f64_msk::v._f64);
                return r;
            }

            static
            vi2_type vi_to_vi2(const vi_type& r) {
                vi2_type t=combine_even_odd(r, r);
                return t;
            }

            static
            vi_type vi2_odd_to_vi(const vi2_type& r) {
                vi_type t=odd_elements(r);
                return t;
            }

            static
            vi_type vi2_even_to_vi(const vi2_type& r) {
                vi_type t=odd_elements(r);
                return t;
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
            void
            extract_words(vi_type& low_word, vi_type& high_word,
                          const vf_type& d) {
                vec<int32_t, _N*2> di=as<vec<int32_t, _N*2> >(d);
                low_word=even_elements(di);
                high_word=odd_elements(di);
            }

            static
            void
            extract_words(vi2_type& low_word, vi2_type& high_word,
                          const vf_type& x) {
                vi2_type di=as<vi2_type>(x);
                low_word = di;
                high_word = di;
            }

            static
            vf_type
            combine_words(const vi_type& l, const vi_type& h) {
                vec<int32_t, _N*2> vi= combine_even_odd(l, h);
                vf_type r= as<vf_type>(vi);
                return r;
            }

            static
            vf_type
            combine_words(const vi2_type& l, const vi2_type& h) {
                vi2_type t= select_even_odd(l, h);
                vf_type r=as<vf_type>(t);
                return r;
            }

            static
            vf_type clear_low_word(const vf_type& d) {
                const uint64_t mu=0xffffffff00000000ULL;
                const bytes8 mf(mu);
                const vf_type m(mf._f64);
                return d & m;
            }

            static
            vli_type as_vli(const vf_type& d) {
                vli_type r=as<vli_type>(d);
                return r;
            }

            static
            vf_type as_vf(const vli_type& l) {
                vf_type r=as<vf_type>(l);
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

    }

}

// Local variables:
// mode: c++
// end:
#endif
