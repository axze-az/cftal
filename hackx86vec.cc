#include <cftal/vec.h>
#include <cftal/d_int.h>
#include <cftal/d_real.h>
#include <cftal/mul_div.h>
#include <cftal/vec.h>
#include <cftal/math_func.h>
#include <cftal/vec_traits.h>
#include <cftal/impl/vreg.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>


namespace cftal {

    namespace op {

        namespace x86 {

            __m128 unpack(vec<float, 2> v) {
                // const auto& d=v();
                double h= as<double>(v());
                __m128 r= _mm_castpd_ps(_mm_set_sd(h));
                return r;
            }

            vec<float, 2>
            pack(__m128 v) {
#if 1
                union v_t {
                    float _f32[2];
                    __m128 _m;
                };
                v_t h;
                h._m = v;
                return  vec<float, 2>{h._f32[0], h._f32[1]};
                // vec<float, 2> r;
                // __asm__ ("# vmovdqa %1, %0\n\t" : "=x"(r) : "0"(v));
                // return r;
#else
                return *reinterpret_cast<const vec<float,2>*>(&v);

                float l = _mm_cvtss_f32(v);
                float h= _mm_cvtss_f32(
                    cftal::x86::impl::vshufps<1, 0, 1, 0>::v(v, v));
                // vec<float, 1> vl=l;
                // vec<float, 1> vh=h;
                return vec<float, 2>{l, h};
#endif
            }

        }

        template <>
        struct add<float, 2> {
            using full_type = vec<float, 2>;
            static
            vec<float, 2>
            v(const vec<float, 2> a, const vec<float, 2> b) {
                __m128 av= x86::unpack(a), bv=x86::unpack(b);
                __m128 r= _mm_add_ps(av, bv);
                return x86::pack(r);
            }
        };

        template <>
        struct sub<float, 2> {
            using full_type = vec<float, 2>;
            static
            vec<float, 2>
            v(const vec<float, 2> a, const vec<float, 2> b) {
                __m128 av= x86::unpack(a), bv=x86::unpack(b);
                __m128 r= _mm_sub_ps(av, bv);
                return x86::pack(r);
            }
        };

        template <>
        struct mul<float, 2> {
            using full_type = vec<float, 2>;
            static
            vec<float, 2>
            v(const vec<float, 2> a, const vec<float, 2> b) {
                __m128 av= x86::unpack(a), bv=x86::unpack(b);
                __m128 r= _mm_mul_ps(av, bv);
                return x86::pack(r);
            }
        };

        template <>
        struct fma<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return add<float, 2>::v(mul<float, 2>::v(a, b), c);
            }
        };

        template <>
        struct fms<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<float, 2>::v(mul<float, 2>::v(a, b), c);
            }
        };

        template <>
        struct fnma<float, 2> {
            using full_type = vec<float, 2>;
            static
            full_type
            v(const full_type& a, const full_type& b,
              const full_type& c) {
                return sub<float, 2>::v(c, mul<float, 2>::v(a, b));
            }
        };

    }

}


cftal::vec<float, 2>
do_mul_add(cftal::vec<float, 2> a,
           cftal::vec<float, 2> b, cftal::vec<float, 2> c)
{
    return (a * b + c) + (a + b * c);
}

cftal::vec<int32_t, 2>
do_add(cftal::vec<int32_t, 2> a, cftal::vec<int32_t, 2> b)
{
    return a + b;
}

int main(int argc, char** argv)
{
    cftal::divisor<cftal::v4s32, int32_t> v4rr(3);
    cftal::v4s32 v4t=-7046431;
    cftal::v4s32 v4q=v4t/v4rr;
    std::cout << v4q << std::endl;

    using v1s32 = cftal::vec<int32_t, 1>;

    cftal::divisor<v1s32, int32_t> v1rr(3);
    v1s32 v1t=-7046431;
    v1s32 v1q=v1t/v1rr;
    std::cout << v1q << std::endl;


    cftal::divisor<cftal::v2s32, int32_t> rr(3);
    cftal::v2s32 t=-7046431;
    cftal::v2s32 q=t/rr;
    std::cout << q << std::endl;

    cftal::divisor<int32_t, int32_t> srr(3);
    int32_t st=-7046431;
    int32_t sq=st/srr;
    std::cout << sq << std::endl;
    return 0;
}
