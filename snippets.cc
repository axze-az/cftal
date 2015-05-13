

template <class _T, std::size_t _N>
bool any_of<const vec<_T, _N>& s)
{
    return any_of(low_half(s)) ||
        any_of(hig_half(s));
}


#if 0
#define CBRT2 1.2599210498948731648             /* 2^(1/3) */
#define SQR_CBRT2 1.5874010519681994748         /* 2^(2/3) */

static const double factor[5] =
{
  1.0 / SQR_CBRT2,
  1.0 / CBRT2,
  1.0,
  CBRT2,
  SQR_CBRT2
};


double
__cbrt (double x)
{
  double xm, ym, u, t2;
  int xe;

  /* Reduce X.  XM now is an range 1.0 to 0.5.  */
  xm = __frexp (fabs (x), &xe);

  /* If X is not finite or is null return it (with raising exceptions
     if necessary.
     Note: *Our* version of `frexp' sets XE to zero if the argument is
     Inf or NaN.  This is not portable but faster.  */
  if (xe == 0 && fpclassify (x) <= FP_ZERO)
    return x + x;

 u = (0.354895765043919860
      + ((1.50819193781584896
         + ((-2.11499494167371287
            + ((2.44693122563534430
               + ((-1.83469277483613086
                  + (0.784932344976639262 - 0.145263899385486377 * xm) * xm)
                  * xm))
               * xm))
            * xm))
         * xm));

  t2 = u * u * u;

  ym = u * (t2 + 2.0 * xm) / (2.0 * t2 + xm) * factor[2 + xe % 3];

  return __ldexp (x > 0.0 ? ym : -ym, xe / 3);
}

template <typename _T>
inline
typename cftal::math::func<double, cftal::int32_t, _T>::vf_type
cftal::math::func<double, cftal::int32_t, _T>::cbrt(const vf_type& x)
{
#if 0
        vf_type xabs(abs(x));
        vi_type xe;
        vf_type xm(frexp(xabs, &xe)); 
        const cftal::divisor<vi_type, int32_t> div3(3);

        vf_type u((vf_type(0.354895765043919860)
                   + ((vf_type(1.50819193781584896)
                       + ((vf_type(-2.11499494167371287)
                           + ((vf_type(2.44693122563534430)
                               + ((vf_type(-1.83469277483613086)
                                   + (vf_type(0.784932344976639262) - 
                                      vf_type(0.145263899385486377) * xm) * xm)
                                  * xm))
                              * xm))
                          * xm))
                      * xm)));
        vf_type t2(u * u * u);
        /* 2^(1/3) */
        /* 2^(2/3) */
        vi_type ex(xe / div3);
        vi_type tab_idx(2 + xe % div3);
        constexpr double CBRT2(1.2599210498948731648);
        constexpr double SQR_CBRT2(1.5874010519681994748);
#if 1
        static constexpr double tab[]= {
                1.0 / SQR_CBRT2,
                1.0 / CBRT2,
                1.0,
                CBRT2,
                SQR_CBRT2
        };
        vf_type factor(_T::gather(tab, tab_idx, sizeof(double)));
#else
        const vf_type tab0(1.0 / SQR_CBRT2);
        const vf_type tab1(1.0 / CBRT2);
        const vf_type tab2(1.0);
        const vf_type tab3(CBRT2);
        const vf_type tab4(SQR_CBRT2);

        vf_type factor(tab0);
        factor = _T::sel(_T::vmi_to_vmf(tab_idx == vi_type(1)),
                         tab1, factor);
        factor = _T::sel(_T::vmi_to_vmf(tab_idx == vi_type(2)),
                         tab2, factor);
        factor = _T::sel(_T::vmi_to_vmf(tab_idx == vi_type(3)),
                         tab3, factor);
        factor = _T::sel(_T::vmi_to_vmf(tab_idx == vi_type(4)),
                         tab4, factor);
#endif
        vf_type ym(u * (t2 + vf_type(2.0) * xm) / 
                   (vf_type(2.0) * t2 + xm) * factor);
        ym=copysign(ym, x);
        vf_type r(ldexp(ym, ex));
        return r;
#else
        /* Argument reduction */
        /* separate into mantissa and exponent */
        vf_type xabs(abs(x));
        vi_type ex;
        vf_type fr = frexp(xabs, &ex);    
        cftal::divisor<vi_type, int32_t> d3(3);

        /* compute shx such that (ex - shx) is divisible by 3 */
        vi_type shx(ex % d3);
        vi_type dshx(_T::sel(shx > vi_type(0), vi_type(3), vi_type(0)));
        shx -= dshx;

        /* exponent of cube root */
        ex = (ex - shx) / d3;    
        /* 0.125 <= fr < 1.0 */
        fr = ldexp(fr, shx); 

        /* Compute seed with a quadratic qpproximation */
        /* 0.5   <= fr < 1.0 */
        fr = (vf_type(-0.46946116) * fr + vf_type(1.072302)) * fr 
                + vf_type(0.3812513);     
        /* 6 bits of precision */
        vf_type r(ldexp(fr, ex));                                          
        /* Newton-Raphson iterations */
        /* 12 bits of precision */
        const vf_type third(1.0/3.0);
        r = (r + r + xabs /(r*r)) * third;
        // r = vf_type(2.0/3.0) * r + vf_type(1.0/3.0) * x / (r * r);  
        /* 24 bits of precision */
        r = (r + r + xabs /(r*r)) * third;
        /* 48 bits of precision */
        r = (r + r + xabs /(r*r)) * third;
        /* 96 bits of precision */
        r = (r + r + xabs /(r*r)) * third;
        dvf_type rr(r);
        const dvf_type dthird(dvf_type(vf_type(1.0))/vf_type(3.0));
        rr = (rr + rr + xabs /(rr*rr)) * dthird;
        rr = (rr + rr + xabs /(rr*rr)) * dthird;
        rr = (rr + rr + xabs /(rr*rr)) * dthird;
        rr = (rr + rr + xabs /(rr*rr)) * dthird;
        rr = (rr + rr + xabs /(rr*rr)) * dthird;
        rr = (rr + rr + xabs /(rr*rr)) * dthird;
        r = rr.h() + rr.l();

        r = copysign(r, x);
        return r;
#endif
}

#endif

namespace dummy {

        union d_i {
            double _d;
            int32_t _i[2];  
        };

        inline
        int32_t extract_high_word(double d) {
            d_i t;
            t._d = d;
            return t._i[1];
        }

        inline
        int32_t extract_low_word(double d) {
            d_i t;
            t._d = d;
            return t._i[0];
        }

        inline
        double combine_words(int32_t l, int32_t h) {
            d_i t;
            t._i[0] = l;
            t._i[1] = h;
            return t._d;
        }

        inline
        double insert_high_word(double d, int32_t h) {
            d_i t;
            t._d = d;
            t._i[1] = h;
            return t._d;
        }

        inline
        double insert_low_word(double d, int32_t l) {
            d_i t;
            t._d = d;
            t._i[01] = l;
            return t._d;
        }


        template <class _T, unsigned _P>
        struct ipow {
            static _T v(const _T& x) {
                _T r(ipow<_T, _P/2>::v(x*x));                    
                if (_P & 1) 
                    r *= x;
                return r;
            }
        };

        template <class _T>
        struct ipow<_T, 0U> {
            static _T v(const _T& x) {
                return _T(1);
            }
        };

        template <int _I, class _T>
        _T pow(const _T& x) {
            _T r(ipow<_T, (_I < 0 ? -_I : _I) >::v(x));
            if (_I < 0 ) {
                r = _T(1.0)/r;
            }
            return r;
        }

        template <int n>
        inline float nth_root(float x)
        {
           const int ebits = 8;
           const int fbits = 23;

           int& i = (int&) x;
           const int bias = (1 << (ebits-1))-1;
           i = (i - (bias << fbits)) / n + (bias << fbits);

           return x;
        }

        template <int n>
        inline double nth_root(double x)
        {
            double g0(0.0);
            int32_t hw= extract_high_word(x);
            const int32_t bias = (1 << (11-1))-1;
            hw = (hw - (bias << 20))/n +  (bias<<20);
            g0 = insert_high_word(g0, hw);
            return g0;
#if 0
           const int ebits = 11;
           const int fbits = 52;
           int64& i = (int64&) x;
           const _int64 bias = (1 << (ebits-1))-1;
           i = (i - (bias << fbits)) / n + (bias << fbits);
           return x;
#endif
        }


        template <class _T, unsigned _R>
        struct root {

            static _T iguess(const _T& x) {
                return nth_root<_R>(x);                    
            }

            static _T nr(const _T& xi, const _T& x) {
                const _T r(_R);
                _T x_pow_nm1(ipow<_T, _R-1>::v(xi));                        
                _T en( x - xi * x_pow_nm1);
                _T den(r * x_pow_nm1);
                _T xip1( xi + en / den);

                return xip1;
            }

            static _T v(const _T& x) {
                // xi0 should contain at least 4 bits
                _T xi0(iguess(x));
                _T xi1(nr(xi0, x));
                _T xi2(nr(xi1, x));
                _T xi3(nr(xi2, x));
                _T xi4(nr(xi3, x));
                _T xi5(nr(xi4, x));
                return xi5;
#if 0
                int expo(0);
                std::frexp(xi5, &expo);
                _T xulp(std::ldexp(1.0, expo-53));
                _T xup(ipow<_T,_R>::v(xi5+xulp));
                _T xcur(ipow<_T,_R>::v(xi5));
                _T xdn(ipow<_T,_R>::v(xi5-xulp));

                _T res(xi5);
                if (abs(xup -x) < abs(xcur -x)) {
                    res = xi5+xulp;
                    xcur = xup;
                }
                if (abs(xdn -x) < abs(xcur -x)) {
                    res = xi5-xulp;
                }
#endif
            }
        };


}


typedef unsigned __int128 u128_t;

u128_t sll(u128_t r, unsigned s)
{
        return r<<s;
}

cftal::uint128_t add1(const cftal::uint128_t& r)
{
        return r + 1;
}

cftal::uint128_t slli17(cftal::uint128_t r)
{
        return r<<128;
}

u128_t ssli17(u128_t r)
{
        return r<<17;
}

u128_t ssli96(u128_t r)
{
        return r<<96;
}

u128_t neg(u128_t r)
{
        return -r;
}

cftal::uint128_t neg(cftal::uint128_t r)
{
        return -r;
}

bool lt(u128_t a, u128_t b)
{
        return a < b;
}

bool lt(cftal::uint128_t a, cftal::uint128_t b)
{
        return a < b;
}

cftal::uint128_t sub(cftal::uint128_t a, cftal::uint128_t b)
{
        return a *b;
}

cftal::uint128_t sub(cftal::uint128_t a, std::uint64_t b)
{
        return a *b;
}

cftal::uint128_t sub(std::uint64_t a, cftal::uint128_t b)
{
        return a - b;
}

x86vec::v4u32 mul(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return a*b;
}

x86vec::v4s32 mul(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return a*b;
}

x86vec::v4u32 mulhi(x86vec::v4u32 a, x86vec::v4u32 b)
{
        return mulh(a, b);
}

x86vec::v4s32 mulhi(x86vec::v4s32 a, x86vec::v4s32 b)
{
        return mulh(a, b);
}

x86vec::v2u64 mul(x86vec::v2u64 a, x86vec::v2u64 b)
{
        return a*b;
}

x86vec::v2s64 mul(x86vec::v2s64 a, x86vec::v2s64 b)
{
        return a*b;
}

x86vec::v2u64 mulhi(x86vec::v2u64 a, x86vec::v2u64 b)
{
        return mulh(a,b);
}

x86vec::v2s64 mulhi(x86vec::v2s64 a, x86vec::v2s64 b)
{
        return mulh(a, b);
}

std::pair<x86vec::v2u64, x86vec::v2u64>
mulwide(x86vec::v2u64 a, x86vec::v2u64 b)
{
        return wide_mul(a, b);
}

std::pair<x86vec::v2s64, x86vec::v2s64>
mulwide(x86vec::v2s64 a, x86vec::v2s64 b)
{
        return wide_mul(a, b);
}


std::pair<x86vec::v2u64, x86vec::v2u64>
square(x86vec::v2u64 a)
{
        return wide_mul(a, a);
}

std::pair<x86vec::v2s64, x86vec::v2s64>
square(x86vec::v2s64 a)
{
        return wide_mul(a, a);
}

typedef unsigned long long u64b;
typedef __uint128_t u128b;

u64b rng_hash_128(u64b *s)
{
        u64b c = 7319936632422683419ULL;
        u64b x = s[1];
        u64b y = s[0];
        u128b xx;

        /* Increment 128bit LCG */
        s[0] += c;
        s[1] += (s[0] < c) + y;

        /* Default threaded option of xoring seed location */
        x ^= (u64b) s;

        /* Hash result */
        xx = (u128b)x * c;
        x = xx ^ y ^ (xx >> 64);
        xx = (u128b)x * c;
        return xx + y + (xx >> 64);
}

void test_div()
{
        using namespace x86vec;
        using test::pr_v2u64;

        v2u64::element_type vi(0UL);
        v2u64 u(3300917957719651597UL, 17331437524411346996UL);
        v2u64 v(vi);
        divisor<v2u64, uint64_t> vd(vi);
        
        v2u64 q_div(u/v), r_div(u % v);
        v2u64 q_cdiv(u/vd), r_cdiv(u % vd); 

        v2u64 q_cmp_div(q_cdiv == q_div);
        v2u64 r_cmp_div(r_div == r_cdiv);

        if (!all_signs(q_cmp_div) || !all_signs(r_cmp_div)) {
                std::cout << "div " << std::endl
                          << pr_v2u64(u()) << " / "
                          << vi << std::endl
                          << "Q_DIV:  "
                          << pr_v2u64(q_div()) << std::endl
                          << "R_DIV:  "
                          << pr_v2u64(r_div()) << std::endl
                          << "Q_CDIV: "
                          << pr_v2u64(q_cdiv()) << std::endl
                          << "R_CDIV: "
                          << pr_v2u64(r_cdiv()) << std::endl;
        }
}
