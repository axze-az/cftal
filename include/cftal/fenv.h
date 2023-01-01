//
// Copyright (C) 2010-2023 Axel Zeuner
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
#if !defined (__CFTAL_FENV_H__)
#define __CFTAL_FENV_H__ 1

#include <cftal/config.h>
#include <fenv.h>
#if defined (__SSE__)
#include <cftal/std_types.h>
#include <cftal/x86/intrin.h>
#endif

namespace cftal {
    struct rounding_mode {
        enum type {
            nearest = 0,
            downward = 1,
            upward = 2,
            towardzero = 3,
            current = 4
        };
    };

    // switch on flush to zero and denormals are zero of intel
    // processors until the destructor is called
    class scoped_ftz_daz_mode {
#if defined (__SSE__)
        uint32_t _csr;
#endif
    public:
        scoped_ftz_daz_mode();
        ~scoped_ftz_daz_mode();
        scoped_ftz_daz_mode(const scoped_ftz_daz_mode&)=delete;
        scoped_ftz_daz_mode(scoped_ftz_daz_mode&&)=delete;
        scoped_ftz_daz_mode&
        operator=(const scoped_ftz_daz_mode&)=delete;
        scoped_ftz_daz_mode&
        operator=(scoped_ftz_daz_mode&&)=delete;
    };
}

inline
cftal::scoped_ftz_daz_mode::scoped_ftz_daz_mode()
#if defined (__SSE__)
    : _csr(_mm_getcsr())
#endif
{
#if defined (__SSE__)
    constexpr const uint32_t _MM_DAZ_MASK=1<<6;
    uint32_t ncsr=_csr | _MM_FLUSH_ZERO_MASK | _MM_DAZ_MASK;
    if (ncsr != _csr)
        _mm_setcsr(ncsr);
#endif
}

inline
cftal::scoped_ftz_daz_mode::~scoped_ftz_daz_mode()
{
#if defined (__SSE__)
    if (_mm_getcsr()!=_csr)
        _mm_setcsr(_csr);
#endif
}

// Local variables:
// mode: c++
// end:
#endif
