cmake_minimum_required (VERSION 3.0.0)
# configurations
if(CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_CONFIGURATION_TYPES debug release profile)
   #set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
   #  "Reset the configurations to what we need"
   # FORCE)
endif()
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE release CACHE STRING
      "Choose the type of build, options are: debug release profile."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

if (UNIX)
find_program(CMAKE_C_COMPILER NAMES gcc)
find_program(CMAKE_CXX_COMPILER NAMES g++)
endif(UNIX)

project (CFTAL)
set (CFTAL_VERSION_MAJ 0)
set (CFTAL_VERSION_MIN 1)
set (CFTAL_VERSION_PLV 0)
set (CFTAL_VERSION_STR
    "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}.${CFTAL_VERSION_PLV}")

# compile flags for usage with cmake -DCMAKE_BUILD_TYPE=debug/release
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
# optimizations and debug
set (CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
set (CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} -fexpensive-optimizations")
set (CMAKE_CXX_FLAGS_PROFILE
  "${CMAKE_CXX_FLAGS_PROFILE} -pg")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

message(${CMAKE_CXX_COMPILER_ID})
message(${CMAKE_LIBRARY_ARCHITECTURE})

# debug flags are set by cmake already
#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1")

option(CFTAL_USE_CXX17 "use C++17" ON)
if(CFTAL_USE_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
else(CFTAL_USE_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif(CFTAL_USE_CXX17)

include_directories(include)

set (CSRCS mul_div_32.cc mul_div_64.cc d_real.cc math_func.cc x86_ops_1.cc
v2f64.cc v4f64.cc v4f32.cc v8f32.cc vec_traits.cc v8f64.cc)

add_library (cftal STATIC ${CSRCS})
install(TARGETS cftal
  DESTINATION lib LIBRARY
  COMPONENT devel)
#set_target_properties(cftal PROPERTIES OUTPUT_NAME "cftal")
add_library (cftal-so SHARED ${CSRCS})
set_property(TARGET cftal-so 
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_property(TARGET cftal-so 
  PROPERTY OUTPUT_NAME cftal)
set_target_properties(cftal-so PROPERTIES SOVERSION "${CFTAL_VERSION_MAJ}" 
  VERSION "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}") 
  
find_library(LIBM m)
if (LIBM)
  target_link_libraries(cftal-so ${LIBM})
endif(LIBM)
install(TARGETS cftal-so
  DESTINATION lib LIBRARY
  COMPONENT cftal
  NAMELINK_SKIP)
install(TARGETS cftal-so
  DESTINATION lib LIBRARY
  COMPONENT devel
  NAMELINK_ONLY)

# hackx86vec
set (HACKX86VEC_SRC hackx86vec.cc)
add_executable(hackx86vec ${HACKX86VEC_SRC})
target_link_libraries(hackx86vec cftal-so)

# boost_lorenz
set (BOOST_LORENZ_SRC boost_lorenz.cc)
add_executable(boost_lorenz ${BOOST_LORENZ_SRC})
target_link_libraries(boost_lorenz cftal-so)

install (TARGETS boost_lorenz
  DESTINATION bin
  COMPONENT tools)

set (CPACK_PACKAGE_NAME "libcftal")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "cftal library")
set (CPACK_PACKAGE_VENDOR "az")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "az")
#set (CPACK_GENERATOR "DEB;RPM;TBZ2")
set (CPACK_GENERATOR "DEB")
set (CPACK_PACKAGE_VERSION_MAJOR "${CFTAL_VERSION_MAJ}")
set (CPACK_PACKAGE_VERSION_MINOR "${CFTAL_VERSION_MIN}")
set (CPACK_PACKAGE_VERSION_PATCH "${CFTAL_VERSION_PLV}")
set (CPACK_PACKAGE_VERSION
  "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}:${CFTAL_VERSION_PLV}")
set (CPACK_DEBIAN_PACKAGE_PRIORITY "extra")

#set (CPACK_COMPONENTS_GROUPING IGNORE)
set(CPACK_COMPONENTS_ALL cftal devel tools)
set (CPACK_COMPONENT_CFTAL_DISPLAY_NAME "cftal-${CFTAL_VERSION_STR}")
set (CPACK_CFTAL_COMPONENT_INSTALL ON)
set (CPACK_COMPONENT_DISPLAY_DEVEL_NAME "cftal-dev")
set (CPACK_DEVEL_COMPONENT_INSTALL ON)
set (CPACK_COMPONENT_TOOLS_DISPLAY_NAME "cftal-tools")
set (CPACK_TOOLS_COMPONENT_INSTALL ON)

set(CPACK_COMPONENTS_IGNORE_GROUPS 1)

# enable component packages
set (CPACK_DEB_COMPONENT_INSTALL on)
#set (CPACK_RPM_COMPONENT_INSTALL on)

#message(${CPACK_COMPONENTS_ALL})

include (CPack)


