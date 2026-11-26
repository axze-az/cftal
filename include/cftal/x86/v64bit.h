//
// Copyright (C) 2010-2026 Axel Zeuner
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
#if !defined (__CFTAL_X86_V64BIT_H__)
#define __CFTAL_X86_V64BIT_H__ 1

#include <cftal/config.h>

#if __CFTAL_CFG_USE_8_BYTE_VECS_ON_X86__ > 0

#include <cftal/types.h>
#include <cftal/x86/intrin.h>

namespace cftal {

    namespace x86 {

	// class representing a 64 bit vector of _T
	template <typename _T>
	struct v64bit {
	    using data_t [[gnu::vector_size(8)]] = _T;
	    data_t _d;
	    v64bit() = default;
	    v64bit(const _T& e0, const _T& e1)
		: _d{e0, e1} {}
	    v64bit(const _T& e0, const _T& e1,
		   const _T& e2, const _T& e3)
		: _d{e0, e1, e2, e3} {}
	    v64bit(const _T& e0, const _T& e1,
		 const _T& e2, const _T& e3,
		 const _T& e4, const _T& e5,
		 const _T& e6, const _T& e7)
		: _d{e0, e1, e2, e3, e4, e5, e6, e7} {}
	    v64bit(__m128 v) {
                // use the assembler to remove redundant moves
                __asm__ ("\n"
                         ".ifnc %0,%1\n\t"
                         "vmovaps %1, %0\n"
                         ".endif\n\t"
                         : "=x" (*this) : "x" (v));
	    }
	    v64bit(__m128i v) {
                // use the assembler to remove redundant moves
                __asm__ ("\n"
                         ".ifnc %0,%1\n\t"
                         "vmovdqa %1, %0\n"
                         ".endif\n\t"
                         : "=x" (*this) : "x" (v));
	    }
	    __m128 to_m128() const {
                __m128 r;
                // use the assembler to remove redundant moves
                __asm__ ("\n"
                         ".ifnc %0,%1\n\t"
                         "vmovaps %1, %0\n"
                         ".endif\n\t"
                         : "=x" (r) : "x" (*this));
		return r;
	    }
	    __m128i to_m128i() const {
                __m128i r;
                // use the assembler to remove redundant moves
                __asm__ ("\n"
                         ".ifnc %0,%1\n\t"
                         "vmovdqa %1, %0\n"
                         ".endif\n\t"
                         : "=x" (r) : "x" (*this));
		return r;
	    }
	};
    }
}
#endif

// Local variables:
// mode: c++
// end:
#endif // __CFTAL_X86_V64BIT_H__
