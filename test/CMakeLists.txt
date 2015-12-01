# empty for now
project(cftal-tests)

set (TEST_SRCS 
     div.cc 
     intops.cc 
     signs.cc 
     f32_f64.cc)
include_directories(../..)
include_directories(../include)

add_library(cftal-test SHARED ${TEST_SRCS})
set_property(TARGET cftal-test 
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(cftal-test PROPERTIES
  SOVERSION "${CFTAL_VERSION_MAJ}" 
  VERSION "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}") 
target_link_libraries(cftal-test cftal-so)
enable_testing()

add_executable(gen-test-vec gen-test-vec.cc)
target_link_libraries(gen-test-vec cftal-test)

function(test_prog arg1)
  add_executable(${arg1} ${arg1}.cc)
  target_link_libraries(${arg1} cftal-test)
  add_test(NAME ${arg1} COMMAND ${arg1})
endfunction()

test_prog(test-d_real)
test_prog(test-dint8)
test_prog(test-fp-ops)
test_prog(test-cbrt)
test_prog(test-frexp)
test_prog(test-ldexp)
test_prog(test-intops)

if (CFTAL_FULL_TEST)
  test_prog(test-v2)
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
