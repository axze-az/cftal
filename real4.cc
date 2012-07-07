#define __NO_REAL4_INLINES__
#include "real.h"
#include <math.h>

#define inline
#include "real4_inlines.h"
#undef inline

namespace math {
	namespace checked {
		
		void real4_t::check_after_op_( ) const 
		{
			int fpclass( fpclassify( value_));
			check_after_op_( fpclass);
		}

		void real4_t::check_after_op_( int fpclass ) const 
		{
			if ( fpclass == FP_INFINITE )
				throw ex_overflow();
			if ( fpclass == FP_NAN )
				throw ex_invalid_op();
		}

		void real4_t::check_after_div_( const real4_t& r ) const
		{
			int fpclass( fpclassify( value_));
			check_after_div_( fpclass, r);
		}

		void real4_t::check_after_div_( int fpclass, 
						const real4_t& r ) const
		{
			if ( fpclass == FP_INFINITE  ) {
				int fpclass_other( fpclassify( r.value_ ));
				if ( fpclass_other  == FP_ZERO )
					throw ex_div_by_zero() ;
				throw ex_overflow();
			}
			if ( fpclass == FP_NAN ) {
				throw ex_invalid_op();
			}
		}
	}
}
