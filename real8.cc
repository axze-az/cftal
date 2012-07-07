#include "real.h"
#include <math.h>


namespace math {
	namespace checked {
		
		real4_t real8_t::to_real4() const 
		{
			math::real4_t res( value_ );
			int fpclass( fpclassify( res ) );
			if ( (fpclass == FP_INFINITE) ||
			     (fpclass == FP_NAN))
				check_after_op_( fpclass );
			return real4_t(res);
		}

		void real8_t::check_after_op_() const
		{
			int fpclass( fpclassify (value_));
			check_after_op_( fpclass);
		}

		void real8_t::check_after_op_( int fpclass ) const 
		{
			if ( fpclass == FP_INFINITE )
				throw ex_overflow();
			// if ( fpclass == FP_NAN )
			throw ex_invalid_op();
		}

		void real8_t::check_after_div_(	const real8_t& r ) const
		{
			int fpclass( fpclassify( value_));
			check_after_div_(fpclass, r);
		}

		void real8_t::check_after_div_( int fpclass, 
						const real8_t& r ) const
		{
			if ( fpclass == FP_INFINITE  ) {
				int fpclass_other( fpclassify( r.value_ ));
				if ( fpclass_other  == FP_ZERO )
					throw ex_div_by_zero() ;
				throw ex_overflow();
			}
			// if ( fpclass == FP_NAN ) 
			throw ex_invalid_op();
		}
	}
}
