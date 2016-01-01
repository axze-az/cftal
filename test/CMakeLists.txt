# empty for now
project(cftal-tests)


set (TEST_SRCS
  div.cc
  rcp_div_32.cc
  rcp_div_64.cc
  intops.cc
  signs.cc
  f32_f64.cc
  snippets.cc
  of_math_funcs.cc
)
include_directories(../..)
include_directories(../include)

find_package(Boost REQUIRED)
if(${Boost_FOUND})
    #message ("${Boost_FOUND}")
    #message ("${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

#include(FindPkgConfig)
find_library(LIBGMP gmp)
if (LIBGMP)
    message(${LIBGMP})
endif()
find_library(LIBMPFR mpfr)
if (LIBMPFR)
    message(${LIBMPFR})
endif()
find_file(HDRMPFR mpfr.h)
if (HDRMPFR)
    message(${HDRMPFR})
endif()

add_library(cftal-test SHARED ${TEST_SRCS})
set_property(TARGET cftal-test
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(cftal-test PROPERTIES
  SOVERSION "${CFTAL_VERSION_MAJ}"
  VERSION "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}")
target_link_libraries(cftal-test cftal-so)
target_link_libraries(cftal-test stdc++fs)
enable_testing()

add_executable(gen-test-vec gen-test-vec.cc)
target_link_libraries(gen-test-vec cftal-test)

function(test_prog arg1)
  add_executable(${arg1} ${arg1}.cc)
  target_link_libraries(${arg1} cftal-test)
  add_test(NAME ${arg1} COMMAND ${arg1})
endfunction()

test_prog(test-dint8)
test_prog(test-duint8)
test_prog(test-d_real)
test_prog(test-div-u64)
test_prog(test-div-s64)
test_prog(test-rcp-div-u32)
test_prog(test-rcp-div-u64)
test_prog(test-div-u32)
test_prog(test-div-s32)
test_prog(test-div-u16)
test_prog(test-div-s16)
#test_prog(test-fp-ops)
test_prog(test-ops-vXf32)
test_prog(test-ops-vXf64)
test_prog(test-ops-vXs16)
test_prog(test-ops-vXs32)
test_prog(test-ops-vXs64)
test_prog(test-ops-vXu16)
test_prog(test-ops-vXu32)
test_prog(test-ops-vXu64)
test_prog(test-cbrt)
test_prog(test-frexp)
test_prog(test-ldexp)
test_prog(test-ilogb)
test_prog(test-floor)
test_prog(test-ceil)
test_prog(test-trunc)
test_prog(test-rint)
test_prog(test-intops)
test_prog(test-exp-f64)
test_prog(test-expm1-f64)
test_prog(test-log-f64)
test_prog(test-pow-f64)
test_prog(test-v2)

if (CFTAL_FULL_TEST)
  #test_prog(test-v2)
  test_prog(test-v4f64)
  test_prog(test-v4s64)
  test_prog(test-v4u64)
  test_prog(test-v4s32)
  test_prog(test-v4u32)
  test_prog(test-v8s16)
  test_prog(test-v8u16)
  test_prog(test-v8f32)
  test_prog(test-v8s32)
  test_prog(test-v8u32)
endif()
