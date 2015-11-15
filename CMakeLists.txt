cmake_minimum_required (VERSION 3.0.0)
project (CFTAL)

set (CFTAL_VERSION_MAJ 0)
set (CFTAL_VERSION_MIN 1)
set (CFTAL_VERSION_PLV 0)
set (CFTAL_VERSION_STR "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}.${CFTAL_VERSION_PLV}")

# configurations
if(CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_CONFIGURATION_TYPES debug release)
   #set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
   #  "Reset the configurations to what we need"
   # FORCE)
endif()

# compile flags for usage with cmake -DCMAKE_BUILD_TYPE=debug/release
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
# optimizations and debug
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fomit-frame-pointer")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fexpensive-optimizations")
# debug flags are set by cmake already
#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1")

option(CFTAL_USE_CXX17 "use C++17" ON)
if(CFTAL_USE_CXX17)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
else(CFTAL_USE_CXX17)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif(CFTAL_USE_CXX17)

include_directories(..)

find_library(LIBM m)
if (LIBM)
	link_libraries(${LIBM})
endif(LIBM)

set (CSRCS mul_div_32.cc mul_div_64.cc d_real.cc math_func.cc x86_ops_1.cc
v2f64.cc v4f64.cc v4f32.cc v8f32.cc vec_traits.cc v8f64.cc)

add_library (cftal STATIC ${CSRCS})
#set_target_properties(cftal PROPERTIES OUTPUT_NAME "cftal")
add_library (cftal.${CFTAL_VERSION_STR} SHARED ${CSRCS})
set_target_properties(cftal.${CFTAL_VERSION_STR} PROPERTIES COMPILE_FLAGS "-fPIC") 

set (HACKX86VEC_SRC hackx86vec.cc)

add_executable(hackx86vec ${HACKX86VEC_SRC})
target_link_libraries(hackx86vec cftal)

