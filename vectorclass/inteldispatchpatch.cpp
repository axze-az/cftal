/************************  inteldispatchpatch.cpp   ***************************
| Author:        Agner Fog
| Date created:  2012-05-30
| Last modified: 2012-05-30
| Version:       1.00 Beta
| Project:       vector classes
| Description:
| Example of alternative CPU dispatcher for Intel SVML function library
|
| (c) Copyright 2012 GNU General Public License http://www.gnu.org/licenses
\*****************************************************************************/


#include "instrset.h"                  // define instrset_detect()

#ifdef __cplusplus
extern "C" {                           // Avoid C++ name mangling
#endif

// Global variable indicating cpu
int __intel_cpu_indicator = 0; 

// CPU dispatcher function
void __intel_cpu_indicator_init() {
   // Get CPU level from instrset_detect function
   switch (instrset_detect()) {
   case 0:                             // No special instruction set supported
      __intel_cpu_indicator = 1;
      break;
   case 1:                             // SSE supported
      __intel_cpu_indicator = 0x80;
      break;
   case 2:                             // SSE2 supported
      __intel_cpu_indicator = 0x200;
      break;
   case 3:                             // SSE3 supported
      __intel_cpu_indicator = 0x800;
      break;
   case 4:                             // Supplementary-SSE3 supported
      __intel_cpu_indicator = 0x1000;
      break;
   case 5:                             // SSE4.1 supported
      __intel_cpu_indicator = 0x2000;
      break;
   case 6:                             // SSE4.2 and POPCNT supported
      __intel_cpu_indicator = 0x8000;
      break;
   case 7:                             // AVX supported
   default:
      __intel_cpu_indicator = 0x20000;
      break;
   }
}
#ifdef __cplusplus
}   // End of extern "C"
#endif
