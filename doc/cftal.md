# The cftal Library

## List of functions and precision

The tables in this section contain the list of implemented functions and
their measured maximium deviations against the corresponding functions
from the mpfr library. The column about faithfully rounding describes 
if faithfully rounding was observed using a test data set.
All test programs use the routines from The GNU MPFR library as reference
implementation.



MPFR functions return a function value $res$ rounded to target precision
and information about the direction of the final rounding $mpfr_res$.

The formulaes

std::nextafter(res, $-\infty$), res] when $mpfr\_res > 0$

[res, std::nextafter(res, $+\infty$)]  when $mpfr\_res < 0$

[res, res] when $mpfr\_res = 0$|

describe the conversion between the values $res$ and $mpfr\_res$
and an interval.

The column $\Delta ulp$ in the subsections below shows the maximum
deviation in bits against the GNU MPFR library functions observed,
this means functions with $\Delta ulp = 0$ are correctly rounded.
Faithful rounding is achieved if the implemented function returns
one of the 2 interval borders.

### support functions

| Function | binary64 |  | binary32 | |
| --- | --- | ---| --- | ---|
| | $\Delta$ ulp | (prob.) faithfully | $\Delta$ ulp | (prob.) faithfully |
|ldexp | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|frexp | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|ilogb | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|isnan | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|isinf | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|isfinite | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|copysign | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|abs/fabs | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|floor | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|ceil | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|trunc | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|rint | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|fmin | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|fmax | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |
|nextafter | $\pm$ 0 | n/a  | $\pm$ 0 | n/a |

All these functions behave as their counterparts in the std namespace.

### power functions

| Function | binary64 |  | binary32 | |
| --- | --- | ---| --- | ---|
| | $\Delta$ ulp | (prob.) faithfully | $\Delta$ ulp | (prob.) faithfully |
|rsqrt | $\pm$ 1 | y  | $\pm$ 1 | y |
|cbrt | $\pm$ 1 | y  | $\pm$ 1 | y |
|rcbrt | $\pm$ 1 | y  | $\pm$ 1 | y |
|hypot | $\pm$ 1 | y  | $\pm$ 1 | y |
|rootn | $\pm$ 1 | y  | $\pm$ 1 | y |
|powi | $\pm$ 1 | y  | $\pm$ 1 | y |
|pow | $\pm$ 1 | y  | $\pm$ 1 | y |

The sqrt function uses the hardware instruction provided by modern processors.
The function rsqrt(x) calculates $\frac{1}{\sqrt{x}}$, the function
rcbrt(x) $\frac{1}{\sqrt[3]{x}}$.
The function rootn(x, n) calculates $\sqrt[n]{x}$ and
the function powi(x, n) calculates $x^n$, where n is an integer.

### elementary functions

| Function | binary64 |  | binary32 | |
| --- | --- | ---| --- | ---|
| | $\Delta$ ulp | (prob.) faithfully | $\Delta$ ulp | (prob.) faithfully |
|exp | $\pm$ 1 | y  | $\pm$ 1 | y |
|expm1 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp2m1 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp10 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp10m1 | $\pm$ 1 | y  | $\pm$ 1 | y |
|||||    
|sinh | $\pm$ 1 | y  | $\pm$ 1 | y |
|cosh | $\pm$ 1 | y  | $\pm$ 1 | y |
|tanh | $\pm$ 1 | y  | $\pm$ 1 | y |
|||||
|log | $\pm$ 1 | y  | $\pm$ 1 | y |
|log1p | $\pm$ 1 | y  | $\pm$ 1 | y |
|log2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|log2p1 | $\pm$ 1 | y  | $\pm$ 1 | y |
|log10 | $\pm$ 1 | y  | $\pm$ 1 | y |
|log10p1 | $\pm$ 1 | y  | $\pm$ 1 | y |
|sin | $\pm$ 1 | y  | $\pm$ 1 | y |
|cos | $\pm$ 1 | y  | $\pm$ 1 | y |
|tan | $\pm$ 1 | y  | $\pm$ 1 | y |
|||||
|asin | $\pm$ 1 | y  | $\pm$ 1 | y |
|acos | $\pm$ 1 | y  | $\pm$ 1 | y |
|atan | $\pm$ 1 | y  | $\pm$ 1 | y |
|atan2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|asinh | $\pm$ 1 | y  | $\pm$ 1 | y |
|acosh | $\pm$ 1 | y  | $\pm$ 1 | y |
|atanh | $\pm$ 1 | y  | $\pm$ 1 | y |

The functions exp2m1 and exp10m1 calculate $2^x-1$ and $10^x-1$ respectively,
the functions log2p1 and log10p1 calculate $log_{2}(1+x)$ and $log_{10}(1+x)$
respectively.

### additional elementary functions

| Function | binary64 |  | binary32 | |
| --- | --- | ---| --- | ---|
| | $\Delta$ ulp | (prob.) faithfully | $\Delta$ ulp | (prob.) faithfully |
|exp_mx2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp_px2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp2_mx2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp2_px2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp10_mx2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|exp10_px2 | $\pm$ 1 | y  | $\pm$ 1 | y |
|sig | $\pm$ 1 | y  | $\pm$ 1 | y |
|root12 | $\pm$ 1 | y  | $\pm$ 1 | y |
|sincos | $\pm$ 1 | y  | $\pm$ 1 | y |
|sinpi | $\pm$ 1 | y  | $\pm$ 1 | y |
|cospi | $\pm$ 1 | y  | $\pm$ 1 | y |
|tanpi | $\pm$ 1 | y  | $\pm$ 1 | y |
|sinpicospi | $\pm$ 1 | y  | $\pm$ 1 | y |

The function ex_mx2 calculates $e^{-x^2}$, exp_px2 calculates
$e^{x^2}$, the functions exp2\_mx2, exp2_mx2, exp10_mx2 and
exp10_mx2 calculate $2^{-x^2}$, $2^{x^2}$, $10^{-x^2}$ and 
$10^{x^2}$.

The logistic or sigmoid function sig returns $\frac{1}{1+e^{-x}}$.

The functions sinpi, cospi and tanpi calculate $\sin(\pi *x)$,
$\cos(\pi * x)$ and $\tan(\pi * x)$ respectivly. The function
sincos returns sinus and cosinus of its argument, sinpicospi returns
sinpi and cospi.

### special functions

| Function | binary64 |  | binary32 | |
| --- | --- | ---| --- | ---|
| | $\Delta$ ulp | (prob.) faithfully | $\Delta$ ulp | (prob.) faithfully |
|erf | $\pm$ 1 | y  | $\pm$ 1 | y |
|erfc | $\pm$ 1 | y  | $\pm$ 1 | y |
|tgamma | $\pm$ 1 | y  | $\pm$ 1 | y |
|lgamma | $\pm$ 100? | n  | $\pm$ 100? | n |
|j0 | $\pm$ 1? | y?  | $\pm$ 1? | y? |
|j1 | $\pm$ 1? | y?  | $\pm$ 1? | y? |
|y0 | $\pm$ 1? | y?  | $\pm$ 1? | y? |
|y1 | $\pm$ 1? | y?  | $\pm$ 1? | y? |

The function lgamma is probably faithfully rounded for non negative arguments.
