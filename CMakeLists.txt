cmake_minimum_required (VERSION 3.0.0)
# configurations
if(CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_CONFIGURATION_TYPES debug release)
   #set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
   #  "Reset the configurations to what we need"
   # FORCE)
endif()

project (CFTAL)
set (CFTAL_VERSION_MAJ 0)
set (CFTAL_VERSION_MIN 1)
set (CFTAL_VERSION_PLV 0)
set (CFTAL_VERSION_STR "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}.${CFTAL_VERSION_PLV}")

# compile flags for usage with cmake -DCMAKE_BUILD_TYPE=debug/release
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
# optimizations and debug
set (CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fomit-frame-pointer")
set (CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fexpensive-optimizations")
# debug flags are set by cmake already
#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1")

option(CFTAL_USE_CXX17 "use C++17" ON)
if(CFTAL_USE_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
else(CFTAL_USE_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif(CFTAL_USE_CXX17)

include_directories(..)

set (CSRCS mul_div_32.cc mul_div_64.cc d_real.cc math_func.cc x86_ops_1.cc
v2f64.cc v4f64.cc v4f32.cc v8f32.cc vec_traits.cc v8f64.cc)

add_library (cftal STATIC ${CSRCS})
#set_target_properties(cftal PROPERTIES OUTPUT_NAME "cftal")
set (CFTAL_DLL cftal.${CFTAL_VERSION_STR})
add_library (${CFTAL_DLL} SHARED ${CSRCS})
set_property(TARGET ${CFTAL_DLL} PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)

find_library(LIBM m)
if (LIBM)
        target_link_libraries(${CFTAL_DLL} ${LIBM})
endif(LIBM)

# hackx86vec
set (HACKX86VEC_SRC hackx86vec.cc)
add_executable(hackx86vec ${HACKX86VEC_SRC})
target_link_libraries(hackx86vec ${CFTAL_DLL})

# boost_lorenz
set (BOOST_LORENZ_SRC boost_lorenz.cc)
add_executable(boost_lorenz ${BOOST_LORENZ_SRC})
target_link_libraries(boost_lorenz ${CFTAL_DLL})

install(DIRECTORY . DESTINATION include/cftal
  PATTERN "*build*" EXCLUDE
  PATTERN "check*" EXCLUDE
  PATTERN "*doc*" EXCLUDE
  PATTERN "*test*" EXCLUDE
  PATTERN "*ake*" EXCLUDE
  PATTERN "./*.h")

set (CPACK_PACKAGE_NAME "libcftal")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "cftal library")
set (CPACK_PACKAGE_VENDOR "az")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "az")
#set (CPACK_GENERATOR "DEB;RPM;TBZ2")
set (CPACK_GENERATOR "DEB")
set (CPACK_PACKAGE_VERSION_MAJ "${CFTAL_VERSION_MAJ}")
set (CPACK_PACKAGE_VERSION_MIN "${CFTAL_VERSION_LO}")
set (CPACK_PACKAGE_VERSION_PLV "${CFTAL_VERSION_PATCH}")
set (CPACK_PACKAGE_VERSION "${CFTAL_VERSION_STR}")
set (CPACK_DEBIAN_PACKAGE_PRIORITY "extra")

include (CPack)


