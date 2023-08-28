cmake_minimum_required (VERSION 3.9)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

# configurations
if(CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_CONFIGURATION_TYPES debug release profile)
   #set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
   #  "Reset the configurations to what we need"
   # FORCE)
endif()
if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE release CACHE STRING
      "Choose the type of build, options are: debug release profile."
      FORCE)
endif()

if (UNIX)
  #message("cross compile ${CMAKE_CROSSCOMPILING}")
  #message("tool chain ${CMAKE_TOOLCHAIN_FILE}")
  if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (NOT DEFINED ENV{CC} AND NOT DEFINED CMAKE_C_COMPILER)
      find_program(CMAKE_C_COMPILER NAMES gcc)
    endif()
    if (NOT DEFINED ENV{CXX} AND NOT DEFINED CMAKE_CXX_COMPILER)
      find_program(CMAKE_CXX_COMPILER NAMES g++)
    endif()
  endif()
endif()

project (CFTAL)
set (CFTAL_VERSION_MAJ 0)
set (CFTAL_VERSION_MIN 7)
set (CFTAL_VERSION_PLV 0)
set (CFTAL_VERSION_STR
    "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}.${CFTAL_VERSION_PLV}")

# compile flags for usage with cmake -DCMAKE_BUILD_TYPE=debug/release/profile
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # warnings for all
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-attributes")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-attributes")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-tautological-compare")
    # reduce size if possible
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdata-sections")
    # never activate this
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
    # setting -ffp-contract to off produces the same results with gcc and clang
    # but the error count goes down with gcc using the default of fast
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffp-contract=fast")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fverbose-asm")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # disable some warnings
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-infinite-recursion")
    endif()
    # release
    set (CMAKE_CXX_FLAGS_RELEASE
         "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
    #set (CMAKE_CXX_FLAGS_RELEASE
    #    "${CMAKE_CXX_FLAGS_RELEASE} -ftree-vectorize")
    # strip release builds
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE
         "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
    set (CMAKE_SHARED_LINKER_FLAGS_RELEASE
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s")
    # profile
    set (CMAKE_CXX_FLAGS_PROFILE
        "${CMAKE_CXX_FLAGS_PROFILE} -pg")
    # debug flags are set by cmake already
endif()

message(${CMAKE_CXX_COMPILER_ID})
#message(${CMAKE_LIBRARY_ARCHITECTURE})
# CFTAL_GCC_ARCH
set(CFTAL_GCC_ARCH "native" CACHE STRING "argument for gcc option -march=")
set(CFTAL_GCC_TUNE "" CACHE STRING "argument for gcc option -mtune=")
if ("${CMAKE_LIBRARY_ARCHITECTURE}" MATCHES ^x86_64* )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # please note that -Os does not work for unknown reasons
        # whereas -O0, -O1, -O2, -O3 do
        set (CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=${CFTAL_GCC_ARCH}")
        set (CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -O0 -march=${CFTAL_GCC_ARCH}")
        set (CMAKE_CXX_FLAGS_PROFILE
            "${CMAKE_CXX_FLAGS_PROFILE} -O3 -march=${CFTAL_GCC_ARCH}")
        if (NOT (CFTAL_GCC_TUNE STREQUAL ""))
            set (CMAKE_CXX_FLAGS_RELEASE
                "${CMAKE_CXX_FLAGS_RELEASE} -mtune=${CFTAL_GCC_TUNE}")
            set (CMAKE_CXX_FLAGS_DEBUG
                "${CMAKE_CXX_FLAGS_DEBUG} -mtune=${CFTAL_GCC_TUNE}")
            set (CMAKE_CXX_FLAGS_PROFILE
                "${CMAKE_CXX_FLAGS_PROFILE} -mtune=${CFTAL_GCC_TUNE}")
            if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                # undefine the tune flag from arch
                if (NOT (CFTAL_GCC_ARCH STREQUAL ""))
                    set (CMAKE_CXX_FLAGS_RELEASE
                        "${CMAKE_CXX_FLAGS_RELEASE} -U__tune_${CFTAL_GCC_ARCH}__")
                    set (CMAKE_CXX_FLAGS_DEBUG
                        "${CMAKE_CXX_FLAGS_DEBUG} -U__tune_${CFTAL_GCC_ARCH}__")
                    set (CMAKE_CXX_FLAGS_PROFILE
                        "${CMAKE_CXX_FLAGS_PROFILE} -U__tune_${CFTAL_GCC_ARCH}__")
                endif()
                set (CMAKE_CXX_FLAGS_RELEASE
                    "${CMAKE_CXX_FLAGS_RELEASE} -D__tune_${CFTAL_GCC_TUNE}__=1")
                set (CMAKE_CXX_FLAGS_DEBUG
                    "${CMAKE_CXX_FLAGS_DEBUG} -D__tune_${CFTAL_GCC_TUNE}__=1")
                set (CMAKE_CXX_FLAGS_PROFILE
                    "${CMAKE_CXX_FLAGS_PROFILE} -D__tune_${CFTAL_GCC_TUNE}__=1")
            endif()
        endif()
        #set (CMAKE_CXX_FLAGS_RELEASE
        #    "${CMAKE_CXX_FLAGS_RELEASE} -march=x86-64-v3")
        #set (CMAKE_CXX_FLAGS_DEBUG
        #    "${CMAKE_CXX_FLAGS_DEBUG}  -march=x86-64-v3")
        #set (CMAKE_CXX_FLAGS_PROFILE
        #    "${CMAKE_CXX_FLAGS_PROFILE} -march=x86-64-v3")
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #    "${CMAKE_CXX_FLAGS_RELEASE} -fno-tree-ter")
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
endif()

# C++23 ?
option(CFTAL_USE_CXX23 "use C++23" ON)
# C++20 ?
option(CFTAL_USE_CXX20 "use C++20" ON)
if (CFTAL_USE_CXX2A)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++23")
else()
    if(CFTAL_USE_CXX20)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
    endif()
endif()

option(CFTAL_USE_LTO "use link time optimizations" OFF)
if (CFTAL_USE_LTO)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS_RELEASE
      "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
      "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto -fwhole-program")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE
      "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -flto")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE
      "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} -flto")
  endif()
endif()

# create static cftal library
option(CFTAL_STATIC_LIB "create static libcftal.a" OFF)
# Full test ?
option(CFTAL_FULL_TEST "perform a full test with long compile times" OFF)
# Doxygen docu ?

option(CFTAL_DOXYGEN "create documentation using doxygen" OFF)
if (CFTAL_DOXYGEN)
    cmake_policy(PUSH)
    cmake_policy(SET CMP0057 OLD)
    find_package(Doxygen)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_PREDEFINED "__AVX__" "__AVX2__" "__SSE2__" "__SSE__")
    doxygen_add_docs(
        doxygen-docs
        ${PROJECT_SOURCE_DIR}/include/
        COMMENT "Generate html pages"
    )
    cmake_policy(POP)
endif()

set(CFTAL_CFG_USE_VF64_FOR_VF32 0)
option(CFTAL_CONFIG_USE_VF64_FOR_VF32
       "use double precision vectors in float vector functions" OFF)
#message("CFTAL_CONFIG_USE_VF64_FOR_VF32: ${CFTAL_CONFIG_USE_VF64_FOR_VF32}")
if (CFTAL_CONFIG_USE_VF64_FOR_VF32)
    message("using double precision vectors in float functions")
    set(CFTAL_CFG_USE_VF64_FOR_VF32 1)
else()
    message("not using double precision vectors in float functions")
endif()

set(CFTAL_CFG_ENABLE_AVX512 0)
option(CFTAL_CONFIG_ENABLE_AVX512
       "allow usage of AVX512XX" OFF)
if (CFTAL_CONFIG_ENABLE_AVX512)
    message("using avx512")
    set(CFTAL_CFG_ENABLE_AVX512 1)
else()
    message("not using avx512")
endif()

include_directories(include)
include_directories(test/include)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/cftal)
include_directories(${PROJECT_BINARY_DIR}/include)

configure_file("include/cftal/config.h.in"
               "${PROJECT_BINARY_DIR}/include/cftal/config.h")

add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(test)
add_subdirectory(utils)

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


