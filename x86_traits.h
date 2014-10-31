#if !defined (__X86VEC_MATH_FUNC_H__)
#define __X86VEC_MATH_FUNC_H__ 1

#include <cftal/config.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>

namespace cftal {

#if 0
    template <>
    struct d_real_traits<v2f64> : public has_fma<double> {
        constexpr d_real_traits<v2f64>() = default;
        // result of a comparison operator
        typedef v2f64 cmp_result_type;
        static bool any(const cmp_result_type& b) {
            return !no_signs(b);
        }

        static v2f64 sel(const cmp_result_type& s,
                         const v2f64& on_true,
                         const v2f64& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void split(const v2f64& a,
                   v2f64& h,
                   v2f64& l) {
            const v2f64 msk=
                const_v4u32<0xf8000000U,
                            0xffffffffU,
                            0xf8000000U,
                            0xffffffffU>::dv();
            h = a & msk;
            l = a - h;
        }
    };

    template <>
    struct d_real_traits<v4f32> : public has_fma<float> {
        constexpr d_real_traits<v4f32>() = default;
        // result of a comparison operator
        typedef v4f32 cmp_result_type;
        static bool any(const cmp_result_type& b) {
            return !no_signs(b);
        }

        static v4f32 sel(const cmp_result_type& s,
                         const v4f32& on_true,
                         const v4f32& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void split(const v4f32& a,
                   v4f32& h,
                   v4f32& l) {
            const v4f32 msk=
                const_v4u32<0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U>::fv();
            h = a & msk;
            l = a - h;
        }
    };
#endif

    template <>
    struct d_real_traits<v4f64> : public has_fma<double> {
        constexpr d_real_traits<v4f64>() = default;
        // result of a comparison operator
        using cmp_result_type= typename v4f64::mask_type;
        static bool any(const cmp_result_type& b) {
            return false; // !no_signs(b);
        }

        static v4f64 sel(const cmp_result_type& s,
                         const v4f64& on_true,
                         const v4f64& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void split(const v4f64& a,
                   v4f64& h,
                   v4f64& l) {
#if !defined (__AVX__)
            const v2f64 msk_half=
                x86::const_v4u32<0xf8000000U,
                                 0xffffffffU,
                                 0xf8000000U,
                                 0xffffffffU>::dv();
            const v4f64 msk(msk_half, msk_half);
#else
            const v4f64 msk=
                x86::const_v8u32<0xf8000000U,
                                 0xffffffffU,
                                 0xf8000000U,
                                 0xffffffffU,
                                 0xf8000000U,
                                 0xffffffffU,
                                 0xf8000000U,
                                 0xffffffffU>::dv();
#endif
            h = a & msk;
            l = a - h;
        }
    };

#if 0
    template <>
    struct d_real_traits<v8f32> : public has_fma<float> {
        constexpr d_real_traits<v8f32>() = default;
        // result of a comparison operator
        typedef v8f32 cmp_result_type;
        static bool any(const cmp_result_type& b) {
            return !no_signs(b);
        }

        static v8f32 sel(const cmp_result_type& s,
                         const v8f32& on_true,
                         const v8f32& on_false) {
            return select(s, on_true, on_false);
        }

        static
        void split(const v8f32& a,
                   v8f32& h,
                   v8f32& l) {
#if defined (__AVX__)
            const v8f32 msk=
                const_v8u32<0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U>::fv();
#else
            const v4f32 lm=
                const_v4u32<0xfffff000U,
                            0xfffff000U,
                            0xfffff000U,
                            0xfffff000U>::fv();
            const v8f32 msk(lm, lm);
#endif
            h = a & msk;
            l = a - h;
        }
    };
#endif

    namespace math {

#if 0
        template <>
        struct func_traits<v2f64, v4s32> : public
        func_traits<typename v2f64::element_type,
                    typename v4s32::element_type> {
            typedef v2f64 vf_type;
            typedef v2f64 vmf_type;
            typedef v4s32 vi_type;
            typedef v4s32 vmi_type;

            static
            constexpr std::size_t NVF() {
                return sizeof(vf_type)/
                    sizeof(vf_type::element_type);
            }

            static
            constexpr std::size_t NVI() {
                return sizeof(vi_type)/
                    sizeof(vi_type::element_type);
            }

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                v4s32 xm=
                    permute<0, 0, 1, 1>(mi);
                return as<v2f64>(xm);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                v4s32 xm= as<v4s32>(mf);
                xm = permute<1, 3, 0, 2>(xm);
                return xm;
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
                vi_type ep(permute<0, 0, 1, 1>(e));
                v2u64 m= as<v2u64>(ep);
                m <<= const_shift::_52;
                return as<v2f64>(m);
            }
            static
            vi_type extract_exp(const vf_type& d) {
                v4s32 e= as<v4s32>(d);
                e >>= const_shift::_20;
                e = permute<1, 3, 0, 0>(e);
                e &= v4s32(0x7ff, 0x7ff, 0, 0);
                return e;
            }

            static
            vi_type extract_high_word(const vf_type& d) {
                v4s32 w=as<v4s32>(d);
                w= permute<1, 3, 1, 3>(w);
                return w;

            }

            static
            vi_type extract_low_word(const vf_type& d) {
                v4s32 w=as<v4s32>(d);
                w= permute<0, 2, 0, 2>(w);
                return w;
            }

            static
            vf_type combine_words(const vi_type& l,
                                  const vi_type& h) {
                v4s32 c=
                    permute<0, 4, 1, 5>(l, h);
                v2f64 r=as<vf_type>(c);
                return r;
            }

            static
            vf_type cvt_i_to_f(const vi_type& i) {
                return cvt_lo<v2f64>(i);
            }

            static
            vi_type cvt_f_to_i(const vf_type& f) {
                return cvt_lo<v4s32>(f);
            }
            // including rounding towards zero
            static
            vi_type cvt_rz_f_to_i(const vf_type& f) {
                return cvt_rz_lo<v4s32>(f);
            }
        };


        template <>
        struct func_traits<v4f32, v4s32> : public
        func_traits<typename v4f32::element_type,
                    typename v4s32::element_type> {
            typedef v4f32 vf_type;
            typedef v4f32 vmf_type;
            typedef v4s32 vi_type;
            typedef v4s32 vmi_type;
            typedef d_real<vf_type> dvf_type;

            typedef v2f64 vhpf_type;
            typedef func_traits<vhpf_type, v4s32>
            hpf_traits;
            static
            constexpr std::size_t vhpf_per_vf() {
                return 2;
            }

            static
            void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
                using namespace x86vec;
                r[0] = cvt_lo<v2f64>(x);
                r[1] = cvt_hi<v2f64>(x);
            }

            static
            void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
                using namespace x86vec;
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
                return as<v4f32>(mi);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return as<v4s32>(mf);
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
                vi_type ep(e << const_shift::_23);
                return as<v4f32>(ep);
            }
            static
            vi_type extract_exp(const vf_type& d) {
                v4s32 e= as<v4s32>(d);
                e >>= const_shift::_23;
                e &= v4s32(0xff, 0xff, 0xff, 0xff);
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
#endif

        template <>
        struct func_traits<v4f64, v4s32> : public
        func_traits<typename v4f64::value_type,
                    typename v4s32::value_type> {
            typedef v4f64 vf_type;
            typedef v4f64 vmf_type;
            typedef v4s32 vi_type;
            typedef v4s32 vmi_type;

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
                // TODO AVX2 code
                v4s32 xml=permute<0, 0, 1, 1>(mi);
                v4s32 xmh=permute<2, 2, 3, 3>(mi);
                v2f64 dml=as<v2f64>(xml);
                v2f64 dmh=as<v2f64>(xmh);
                v4f64 r(dml, dmh);
                return r;
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                // TODO AVX2 code
                v2f64 mfl=low_half(mf);
                v2f64 mfh=high_half(mf);
                v4s32 xml=as<v4s32>(mfl);
                v4s32 xmh=as<v4s32>(mfh);
                v4s32 xm =permute<0, 2, 4, 6>(xml, xmh);
                return xm;
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
#if !defined (__AVX__)
                lh &= v_exp_v2f64_msk::dv();
                fh &= v_exp_v2f64_msk::dv();
                vf_type r(lh, fh);
#else
                vf_type r(lh, fh);
                r &= vf_type(x86::v_exp_v4f64_msk::dv());
#endif
                return r;
            }

            static
            vi_type extract_exp(const vf_type& d) {
                // TODO AVX2 code
#if !defined (__AVX__)
                vf_type m(low_half(d) & v_exp_v2f64_msk::dv(),
                          high_half(d) & v_exp_v2f64_msk::dv());
#else
                // vf_type m(d & v_exp_v4f64_msk::dv());
#endif
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

#if 0
        template <>
        struct func_traits<v8f32, v8s32> : public
        func_traits<typename v8f32::value_type,
                    typename v8s32::value_type> {
            typedef v8f32 vf_type;
            typedef v8f32 vmf_type;
            typedef v8s32 vi_type;
            typedef v8s32 vmi_type;

            typedef d_real<vf_type> dvf_type;

            typedef v4f64 vhpf_type;
            typedef func_traits<vhpf_type, v4s32>
            hpf_traits;

            static
            constexpr std::size_t vhpf_per_vf() {
                return 2;
            }

            static
            void vf_to_vhpf(const vf_type& x, vhpf_type* r) {
                using namespace x86vec;
                using impl::cvt;
                r[1] = cvt<v4f64, v8f32>::h(x);
                r[0] = cvt<v4f64, v8f32>::l(x);
            }

            static
            void vhpf_to_dvf(const vhpf_type* hpf, dvf_type& res) {
                using namespace x86vec;
                using impl::cvt;
                vf_type lo(cvt<v8f32, v4f64>::l(hpf[0]));
                vhpf_type rest(hpf[0] - cvt<v4f64, v8f32>::l(lo));
                vf_type lo_lo(cvt<v8f32, v4f64>::l(rest));

                vf_type hi(cvt<v8f32, v4f64>::l(hpf[1]));
                rest = hpf[1] - cvt<v4f64, v8f32>::l(hi);

                vf_type hi_lo(cvt<v8f32, v4f64>::l(rest));

                vf_type msv(permute<0, 1, 2, 3,
                            8, 9, 10, 11>(lo, hi));
                vf_type lsv(permute<0, 1, 2, 3,
                            8, 9, 10, 11>(lo_lo,
                                          hi_lo));
                res = dvf_type(msv, lsv);
            }

            static
            vmf_type vmi_to_vmf(const vmi_type& mi) {
                return as<v8f32>(mi);
            }
            static
            vmi_type vmf_to_vmi(const vmf_type& mf) {
                return as<v8s32>(mf);
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
                vi_type ep(e << const_shift::_23);
                return as<v8f32>(ep);
            }
            static
            vi_type extract_exp(const vf_type& d) {
                v8s32 e= as<v8s32>(d);
                e >>= const_shift::_23;
                e &= v8s32(0xff, 0xff, 0xff, 0xff,
                           0xff, 0xff, 0xff, 0xff);
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
#endif

    }

}

// Local variables:
// mode: c++
// end:
#endif
