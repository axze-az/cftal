cmake_minimum_required(VERSION 3.10)
project(cftal-test-src)

set (TEST_SRCS
  env_var.cc
  div.cc
  rcp_div_32.cc
  rcp_div_64.cc
  intops.cc
  signs.cc
  f32_f64.cc
  of_fp_funcs.cc
  of_math_funcs.cc
  of_vec.cc
  call_mpfr.cc
  mpfr_cache.cc
  spinlock.cc
  program.cc
  cpu_times.cc
)

find_library(LIBGMP gmp REQUIRED)
if (LIBGMP)
    message(${LIBGMP})
endif()
find_library(LIBMPFR mpfr REQUIRED HINTS /usr/local/lib)
if (LIBMPFR)
    message(${LIBMPFR})
endif()
find_file(HDRMPFR mpfr.h REQUIRED HINTS /usr/local/include)
if (HDRMPFR)
    message(${HDRMPFR})
endif()
find_library(LIBLZMA lzma REQUIRED HINTS /usr/local/lib)
if (LIBLZMA)
    message(${LIBLZMA})
endif()
find_file(HDRLZMA lzma.h REQUIRED HINTS /usr/local/lib)
if (HDRLZMA)
    message(${HDRLZMA})
endif()
find_package(Threads REQUIRED)

function(target_add_mpfr_libs arg1)
    target_link_libraries(${arg1} ${LIBMPFR})
    target_link_libraries(${arg1} ${LIBGMP})
    target_link_libraries(${arg1} Threads::Threads)
endfunction()

add_library(cftal-test-so SHARED ${TEST_SRCS})
set_property(TARGET cftal-test-so
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(cftal-test-so PROPERTIES
  SOVERSION "${CFTAL_VERSION_MAJ}"
  VERSION "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}")
target_link_libraries(cftal-test-so cftal-so)
target_link_libraries(cftal-test-so stdc++fs)
target_add_mpfr_libs(cftal-test-so)
target_link_libraries(cftal-test-so ${LIBLZMA})
