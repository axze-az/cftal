#define __NO_REAL16_INLINES__
#include "real.h"
#include <math.h>

#define inline
#include "real16_inlines.h"
#undef inline

namespace math {
	namespace checked {
		real8_t real16_t::to_real8() const 
		{
			math::real8_t res( value_ );
			int fpclass( fpclassify( res ) );
			if ( (fpclass == FP_INFINITE) ||
			     (fpclass == FP_NAN))
				check_after_op_(  );
			return real8_t(res);
		}

		real4_t real16_t::to_real4() const 
		{
			math::real4_t res( value_ );
			int fpclass( fpclassify( res ) );
			if ( (fpclass == FP_INFINITE) ||
			     (fpclass == FP_NAN))
				check_after_op_( fpclass );
			return real4_t(res);
		}

		void real16_t::check_after_op_( ) const 
		{
			int fpclass( fpclassify (value_) );
			check_after_op_( fpclass);
		}

		void real16_t::check_after_op_( int fpclass ) const 
		{
			if ( fpclass == FP_INFINITE )
				throw ex_overflow();
			if ( fpclass == FP_NAN )
				throw ex_invalid_op();
		}

		void real16_t::check_after_div_( const real16_t& r ) const
		{
			int fpclass( fpclassify (value_) );
			check_after_div_( fpclass, r);
		}

		void real16_t::check_after_div_( int fpclass, 
						 const real16_t& r ) const
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
