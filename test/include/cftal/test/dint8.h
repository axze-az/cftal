//
// Copyright (C) 2010-2025 Axel Zeuner
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#if !defined (__CFTAL_TEST_DINT8_H__)
#define __CFTAL_TEST_DINT8_H__ 1

#include <cftal/d_int.h>
#include <cftal/type_traits.h>
#include <functional>
#include <iostream>
#include <iomanip>

namespace cftal {

    namespace test {

        template <class _T>
        struct mul_half {
        };

        template <>
        struct mul_half<uint16_t> {
            uint16_t operator()(uint16_t a, uint16_t b)
                const {
                return a * (b & 0xFF);
            }
        };

        template <>
        struct mul_half<duint<uint8_t> > {
            duint<uint8_t> operator()(const duint<uint8_t>& a,
                                      const duint<uint8_t>& b)
                const {
                const uint8_t& l= b.l();
                return a * l;
            }
        };

        template <>
        struct mul_half<int16_t> {
            uint16_t operator()(int16_t a, int16_t b)
                const {
                int8_t d= b;
                return a * d;
            }
        };

        template <>
        struct mul_half<dint<int8_t> > {
            duint<uint8_t> operator()(const dint<int8_t>& a,
                                      const dint<int8_t>& b)
                const {
                int8_t l(b.l());
                return a * l;
            }
        };

        template <class _T>
        struct div_half {
        };

        template <>
        struct div_half<uint16_t> {
            uint16_t operator()(uint16_t a, uint16_t b)
                const {
                return a / (b & 0xFF);
            }
        };

        template <>
        struct div_half<duint<uint8_t> > {
            duint<uint8_t> operator()(const duint<uint8_t>& a,
                                      const duint<uint8_t>& b)
                const {
                const uint8_t& l= b.l();
                return a / l;
            }
        };

        template <>
        struct div_half<int16_t> {
            uint16_t operator()(int16_t a, int16_t b)
                const {
                int8_t d= b;
                return a / d;
            }
        };

        template <>
        struct div_half<dint<int8_t> > {
            duint<uint8_t> operator()(const dint<int8_t>& a,
                                      const dint<int8_t>& b)
                const {
                int8_t l(b.l());
                return a / l;
            }
        };

        template <class _T, class _RES>
        void check_res(_T u, _T v,
                       _RES res, _RES ref_res,
                       const char* msg)
        {
            if (res != ref_res) {
                std::cout << std::hex
                          << u << ' ' << msg << ' '
                          << v << " = "
                          << res << " != (expected:) "
                          << ref_res
                          << std::dec
                          << std::endl;
                std::exit(3);
            }
        }

        template <class _T, class _V,
                  template <class _U> class _OP>
        void check_bi_op(_T u, _T v, const char* msg)
        {
            _V uu(u, u>>8);
            _V vv(v, v>>8);
            _OP<_T> op1;
            _T r(op1(u, v));
            _OP<_V> op2;
            _V rr(op2(uu, vv));
            _T res((_T(rr.uh())<<8)|rr.l());
            check_res(u, v, res, r, msg);
        }

        template <class _T, class _V,
                  template <class _U> class _OP>
        void check_bi_op(const char* msg, uint32_t v0=0,
                         uint32_t v1= 0x10000)
        {
            for (uint32_t u=0; u<0x10000; ++u) {
                _T tu= u;
                if (0x3FF==(u & 0x3FF)) {
                    std::cout << msg << ' ' <<  tu << '\r'
                              << std::flush;
                }
                for (uint32_t v=v0; v<v1; ++v) {
                    _T tv=v;
                    check_bi_op<_T, _V, _OP>(tu, tv, msg);
                }
            }
            std::cout << msg << " passed\n";
        }

        template <class _T, class _V,
                  template <class _U> class _OP>
        void check_cmp_op(_T u, _T v, const char* msg)
        {
            _V uu(u, u>>8);
            _V vv(v, v>>8);
            _OP<_T> op1;
            bool r(op1(u, v));
            _OP<_V> op2;
            bool res(op2(uu, vv));
            check_res(u, v, res, r, msg);
        }

        template <class _T, class _V,
                  template <class _U> class _OP>
        void check_cmp_op(const char* msg, uint32_t v0=0)
        {
            for (uint32_t u=0; u<0x10000; ++u) {
                _T tu= u;
                if (0x3FF==(u & 0x3FF)) {
                    std::cout << msg << ' ' <<  tu << '\r'
                              << std::flush;
                }
                for (uint32_t v=v0; v<0x10000; ++v) {
                    _T tv=v;
                    check_cmp_op<_T, _V, _OP>(tu, tv, msg);
                }
            }
            std::cout << msg << " passed\n";
        }

        template <class _T, class _V>
        void check_shift()
        {
            enum { N = sizeof(_T)*8 };
            for (uint32_t u=0; u<0x10000; ++u) {
                _T tu= u;
                if (0x3FF==(u & 0x3FF)) {
                    std::cout << ">> " << tu << '\r'
                              << std::flush;
                }
                for (_T s=0; s <= N; ++s) {
                    _T r = tu >> s;
                    _V vtu(tu, tu>>8);
                    _V vr = vtu >> s;
                    _T res((_T(vr.uh())<<8)|vr.l());
                    check_res(tu, s, res, r, ">>");
                }
            }
            for (uint32_t u=0; u<0x10000; ++u) {
                _T tu= u;
                if (0x3FF==(u & 0x3FF)) {
                    std::cout << "<< " <<  tu << '\r'
                              << std::flush;
                }
                for (_T s=0; s <= N; ++s) {
                    _T r = tu << s;
                    _V vtu(tu, tu>>8);
                    _V vr = vtu << s;
                    _T res((_T(vr.uh())<<8)|vr.l());
                    check_res(tu, s, res, r, "<<");
                }
            }
            std::cout << "shift passed\n";
        }


        template <class _T, class _V>
        void check_duint_ops()
        {
            check_shift<_T,_V>();
            check_bi_op<_T, _V, std::plus>("add");
            check_bi_op<_T, _V, std::minus>("sub");
            check_bi_op<_T, _V, mul_half>("mul_half", 0, 255);
            check_bi_op<_T, _V, std::multiplies>("mul");
            check_cmp_op<_T, _V, std::less>("<");
            check_cmp_op<_T, _V, std::less_equal>("<=");
            check_cmp_op<_T, _V, std::equal_to>("==");
            check_cmp_op<_T, _V, std::not_equal_to>("!=");
            check_cmp_op<_T, _V, std::greater_equal>(">=");
            check_cmp_op<_T, _V, std::greater>(">");
            check_bi_op<_T, _V, div_half>("div_half", 1, 255);
            check_bi_op<_T, _V, std::divides>("div", 1);
        }
    }
}

// Local variables:
// mode: c++
// end:
#endif
