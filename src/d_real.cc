//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/d_real.h"
#include <cstring>
#include <stdexcept>

namespace cftal {

    template <typename _T>
    d_real<_T> str_to_d_real(const char* p, std::size_t n);
}

cftal::d_real<double>
cftal::str_to_d_double(const char* p)
{
    return str_to_d_real<double>(p, std::strlen(p));
}

cftal::d_real<double>
cftal::str_to_d_double(const char* p, std::size_t n)
{
    return str_to_d_real<double>(p, n);
}

cftal::d_real<float>
cftal::str_to_d_float(const char* p)
{
    return str_to_d_real<float>(p, std::strlen(p));
}

cftal::d_real<float>
cftal::str_to_d_float(const char* p, std::size_t n)
{
    return str_to_d_real<float>(p, n);
}

template <typename _T>
cftal::d_real<_T>
cftal::str_to_d_real(const char* p, std::size_t n)
{
    // using cftal::d_real;
    const char* pe=p+n;
    char ch;
    int sign = 0;
    int point = -1;
    int digits =0;
    int exponent= 0;
    int sign_exponent=0;
    int pos=0;
    int in_exp=-1;
    d_real<_T> r(0.0);

    // skip leading spaces
    while (*p == ' ' && p < pe)
        ++p;
    // skip leading zeros
    while (*p == '0' && p < pe)
        ++p;
    while (p < pe) {
        ch = *p;
        switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (in_exp>=0 ) {
                exponent *= 10;
                exponent += ch - '0';
            } else {
                r *= _T(10.0);
                r += _T(ch - '0');
                ++digits;
            }
            break;
        case '.':
            if (point >= 0)
                throw std::runtime_error("double decimal point");
            point = digits;
            break;
        case '+':
            if (in_exp>=0) {
                if (in_exp != pos-1)
                    throw std::runtime_error("double + in exponent");
                sign_exponent = +1;
            } else {
                if (digits > 0)
                    throw std::runtime_error("double + ");
                sign = +1;
            }
            break;
        case '-':
            if (in_exp>=0) {
                if (in_exp != pos-1)
                    throw std::runtime_error("double - in exponent");
                sign_exponent = -1;
            } else {
                if (digits > 0)
                    throw std::runtime_error("double - ");
                sign = -1;
            }
            break;
        case 'e':
        case 'E':
            in_exp = pos;
            break;
        default:
            throw std::runtime_error("invalid character");
        }
        ++pos;
        ++p;
    }

    if (in_exp>=0) {
        if (sign_exponent == -1)
            exponent = -exponent;
    }

    if (point >= 0) {
        exponent -= (digits - point);
    }

    if (exponent != 0) {
        d_real<_T> ex(10.0);
        d_real<_T> exi(powi(ex, exponent));
        r *= exi;
    }
    r = (sign == -1) ? -r : r;
    r += d_real<_T>(0.0);
    return r;
}

cftal::d_real<double>
cftal::operator "" _dd(const char* pp)
{
    return str_to_d_double(pp, std::strlen(pp));
}

cftal::d_real<float>
cftal::operator "" _df(const char* pp)
{
    return str_to_d_float(pp, std::strlen(pp));
}
