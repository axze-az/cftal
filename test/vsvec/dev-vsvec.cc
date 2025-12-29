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

#include <cftal/as.h>
#include <cftal/vsvec.h>
#include <iomanip>

namespace cftal {
    namespace func {

	template <typename _V, typename _W>
	struct custom_func_a1 {};
	
	template <typename _V, typename _W>
	struct custom_func_a2 {};
	
	template <typename _V, typename _W>
	struct custom_func_a3 {};

	// W must define a static method
	// template t<size_t _N>
	// vec<_T, _N>
	// v(const vec<_T, _N>& a);
	template <typename _T, typename _A,
		  template <typename _U> typename _W>
	struct custom_func_a1<vsvec<_T, _A>, _W<_T> > :
	    public _W<_T> {};

	// W must define a static method
	// template t<size_t _N>
	// vec<_T, _N>
	// v(const vec<_T, _N>& a,
	//   const vec<_T, _N>& b);
	template <typename _T, typename _A,
		  template <typename _U> typename _W>
	struct custom_func_a2<vsvec<_T, _A>, _W<_T> > :
	    public op_4_vsvec::b_base<_T, _W<_T> > {};

	// W must defined a static method
	// template t<size_t _N>
	// vec<_T, _N>
	// v(const vec<_T, _N>& a,
	//   const vec<_T, _N>& b,
	//   const vec<_T, _N>& c);
	template <typename _T, typename _A,
		  template <typename _U> typename _W>
	struct custom_func_a3<vsvec<_T, _A>, _W<_T> > :
	    public op_4_vsvec::t_base<_T, _W<_T> > {};
    }
    
#define CUSTOM_OPINFO(optype, opcount)					\
    template <typename _T, typename _A,					\
	      typename _L, typename _R,					\
	      template <typename _U> typename _W>			\
    struct operand<expr< optype <vsvec<_T, _A>, _W<_T> >, _L, _R> >{	\
        static								\
        constexpr							\
        size_t count() {						\
            return opcount;						\
        }								\
        static								\
        constexpr							\
        result_size sizes() {						\
            return result_size::eq_size;				\
        }								\
    }

    CUSTOM_OPINFO(func::custom_func_a1, 32);
    CUSTOM_OPINFO(func::custom_func_a2, 32);
    CUSTOM_OPINFO(func::custom_func_a3, 32);
    
}

int main()
{
    return 0;
}
