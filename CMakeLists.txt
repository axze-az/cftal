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
  #message("cross compile ${CMAKE_CROSSCOMPILING}")
  #message("tool chain ${CMAKE_TOOLCHAIN_FILE}")
  if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (NOT DEFINED ENV{CC})
      find_program(CMAKE_C_COMPILER NAMES gcc)
    endif()
    if (NOT DEFINED ENV{CXX})
      find_program(CMAKE_CXX_COMPILER NAMES g++)
    endif()
  endif()
endif(UNIX)

project (CFTAL)
set (CFTAL_VERSION_MAJ 0)
set (CFTAL_VERSION_MIN 1)
set (CFTAL_VERSION_PLV 0)
set (CFTAL_VERSION_STR
    "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}.${CFTAL_VERSION_PLV}")

# compile flags for usage with cmake -DCMAKE_BUILD_TYPE=debug/release/profile
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # warnings for all
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    # release
    set (CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
    set (CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE} -ftree-vectorize")
    # profile
    set (CMAKE_CXX_FLAGS_PROFILE
        "${CMAKE_CXX_FLAGS_PROFILE} -pg")
    # debug flags are set by cmake already
endif()

message(${CMAKE_CXX_COMPILER_ID})
#message(${CMAKE_LIBRARY_ARCHITECTURE})
if ("${CMAKE_LIBRARY_ARCHITECTURE}" MATCHES ^x86_64* )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -fexpensive-optimizations")
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -fsched-pressure")
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -fschedule-insns")
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -fschedule-insns2")
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -finline-functions")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #    "${CMAKE_CXX_FLAGS_RELEASE} -fselective-scheduling")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #    "${CMAKE_CXX_FLAGS_RELEASE} -fselective-scheduling2")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #    "${CMAKE_CXX_FLAGS_RELEASE} -fsel-sched-pipelining")
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #    "${CMAKE_CXX_FLAGS_RELEASE} -mtune=corei7-avx")
        set (CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -march=native")
        set (CMAKE_CXX_FLAGS_PROFILE
            "${CMAKE_CXX_FLAGS_PROFILE} -march=native")
    endif()
endif()

# C++17 ?
option(CFTAL_USE_CXX17 "use C++17" ON)
if(CFTAL_USE_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
else(CFTAL_USE_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
endif(CFTAL_USE_CXX17)
# Full test ?
option(CFTAL_FULL_TEST "perform a full test with long compile times" OFF)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

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

enable_testing()

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


