project(cftal-tests)

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
include_directories(../..)
include_directories(../include)
include_directories(./include)

set (TEST_HDRS
    ./include/cftal/test/check_asinh.h
    ./include/cftal/test/check_exp_mx2.h
    ./include/cftal/test/check_rsqrt.h
    ./include/cftal/test/check_exp10.h
    ./include/cftal/test/check_sin.h
    ./include/cftal/test/check_hypot.h
    ./include/cftal/test/intops.h
    ./include/cftal/test/check_log1p.h
    ./include/cftal/test/check_erfc.h
    ./include/cftal/test/check_tgamma.h
    ./include/cftal/test/check_sinh.h
    ./include/cftal/test/check_exp10m1.h
    ./include/cftal/test/of_math_funcs.h
    ./include/cftal/test/check_sincos.h
    ./include/cftal/test/check_log2.h
    ./include/cftal/test/check_exp10_mx2.h
    ./include/cftal/test/check_exp2m1.h
    ./include/cftal/test/check_exp_px2.h
    ./include/cftal/test/check_exp2.h
    ./include/cftal/test/check_log.h
    ./include/cftal/test/of_vec_v2.h
    ./include/cftal/test/check_acosh.h
    ./include/cftal/test/x_real.h
    ./include/cftal/test/check_root12.h
    ./include/cftal/test/check_expm1.h
    ./include/cftal/test/dint8.h
    ./include/cftal/test/check_atan2.h
    ./include/cftal/test/check_cosh.h
    ./include/cftal/test/x86.h
    ./include/cftal/test/idx.h
    ./include/cftal/test/pr_fp.h
    ./include/cftal/test/of_fp_funcs.h
    ./include/cftal/test/check_pow.h
    ./include/cftal/test/check_log10.h
    ./include/cftal/test/check_erf.h
    ./include/cftal/test/call_mpfr.h
    ./include/cftal/test/rcp_div.h
    ./include/cftal/test/of_ops.h
    ./include/cftal/test/check_exp.h
    ./include/cftal/test/of_vec_v4.h
    ./include/cftal/test/check_exp2_px2.h
    ./include/cftal/test/check_acos.h
    ./include/cftal/test/check_cos.h
    ./include/cftal/test/uniform_distribution.h
    ./include/cftal/test/check_cbrt.h
    ./include/cftal/test/check_rcbrt.h
    ./include/cftal/test/mpfr_cache.h
    ./include/cftal/test/check_tanh.h
    ./include/cftal/test/check_sqrt.h
    ./include/cftal/test/of_vec.h
    ./include/cftal/test/check_atanh.h
    ./include/cftal/test/check_asin.h
    ./include/cftal/test/check_atan.h
    ./include/cftal/test/check_exp10_px2.h
    ./include/cftal/test/check_tan.h
    ./include/cftal/test/f32_f64.h
    ./include/cftal/test/check_exp2_mx2.h
    ./include/cftal/test/of_vec_v8.h
    ./include/cftal/test/stream_save_fmt.h
    ./include/cftal/test/env_var.h
    ./include/cftal/test/work_queue.h
    ./include/cftal/test/spinlock.h
    ./include/cftal/test/program.h
    ./include/cftal/test/check_lgamma.h
    ./include/cftal/test/check_sinpi.h
    ./include/cftal/test/check_cospi.h
    ./include/cftal/test/check_tanpi.h
    ./include/cftal/test/check_sinpicospi.h
    ./include/cftal/test/check_sig.h
    ./include/cftal/test/cpu_times.h
    ./include/cftal/test/of_vec_v16.h
)

find_package(Boost REQUIRED)
if(${Boost_FOUND})
    #message ("${Boost_FOUND}")
    #message ("${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

#include(FindPkgConfig)
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
#find_library(LIBSQLITE3 sqlite3 REQUIRED)
#if (LIBSQLITE3)
#    message(${LIBSQLITE3})
#endif()
#find_file(HDRQLITE3 sqlite3.h REQUIRED)
#if (HDRQLITE3)
#    message(${HDRQLITE3})
#endif()

function(target_add_mpfr_libs arg1)
    target_link_libraries(${arg1} ${LIBMPFR})
    target_link_libraries(${arg1} ${LIBGMP})
    target_link_libraries(${arg1} Threads::Threads)
endfunction()

add_library(cftal-test SHARED ${TEST_SRCS})
set_property(TARGET cftal-test
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(cftal-test PROPERTIES
  SOVERSION "${CFTAL_VERSION_MAJ}"
  VERSION "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}")
target_link_libraries(cftal-test cftal-so)
target_link_libraries(cftal-test stdc++fs)
target_add_mpfr_libs(cftal-test)
target_link_libraries(cftal-test ${LIBLZMA})
enable_testing()

function(target_add_test_libs arg1)
    target_link_libraries(${arg1} cftal-test)
    target_add_mpfr_libs(${arg1})
endfunction()

function(test_prog arg1)
    add_executable(${arg1} ${arg1}.cc ${TEST_HDRS})
    target_add_test_libs(${arg1})
    add_test(NAME ${arg1} COMMAND ${arg1})
endfunction()

test_prog(test-tools)

test_prog(test-dint8)
test_prog(test-duint8)
test_prog(test-d_real)
test_prog(test-t_real)
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
test_prog(test-ops-vXs8)
test_prog(test-ops-vXs16)
test_prog(test-ops-vXs32)
test_prog(test-ops-vXs64)
test_prog(test-ops-vXu8)
test_prog(test-ops-vXu16)
test_prog(test-ops-vXu32)
test_prog(test-ops-vXu64)
test_prog(test-cvt-f16)
test_prog(test-ops-vXf16)
test_prog(test-frexp)
test_prog(test-ldexp)
test_prog(test-ilogb)
test_prog(test-floor)
test_prog(test-ceil)
test_prog(test-trunc)
test_prog(test-rint)
test_prog(test-intops)
test_prog(test-nextafter)

test_prog(test-poly)
test_prog(test-sqrt-f64)
test_prog(test-rsqrt-f64)
test_prog(test-cbrt-f64)
test_prog(test-rcbrt-f64)
test_prog(test-hypot-f64)
test_prog(test-exp-f64)
test_prog(test-expm1-f64)
test_prog(test-sinh-f64)
test_prog(test-cosh-f64)
test_prog(test-tanh-f64)
test_prog(test-exp2-f64)
test_prog(test-exp2m1-f64)
test_prog(test-exp10-f64)
test_prog(test-exp10m1-f64)
test_prog(test-log-f64)
test_prog(test-log1p-f64)
test_prog(test-log10-f64)
test_prog(test-log2-f64)
test_prog(test-pow-f64)
test_prog(test-powi-f64)
test_prog(test-rootn-f64)
test_prog(test-asinh-f64)
test_prog(test-acosh-f64)
test_prog(test-atanh-f64)

test_prog(test-sin-f64)
test_prog(test-cos-f64)
test_prog(test-sincos-f64)
test_prog(test-tan-f64)

test_prog(test-sinpi-f64)
test_prog(test-cospi-f64)
test_prog(test-sinpicospi-f64)
test_prog(test-tanpi-f64)

test_prog(test-atan-f64)
test_prog(test-atan2-f64)
test_prog(test-asin-f64)
test_prog(test-acos-f64)

test_prog(test-exp_mx2-f64)
test_prog(test-exp_px2-f64)
test_prog(test-exp2_mx2-f64)
test_prog(test-exp2_px2-f64)
test_prog(test-exp10_mx2-f64)
test_prog(test-exp10_px2-f64)
test_prog(test-sig-f64)

test_prog(test-root12-f64)

test_prog(test-erf-f64)
test_prog(test-erfc-f64)
test_prog(test-tgamma-f64)
test_prog(test-lgamma-f64)

test_prog(test-sqrt-f32)
test_prog(test-rsqrt-f32)
test_prog(test-cbrt-f32)
test_prog(test-rcbrt-f32)
test_prog(test-hypot-f32)
test_prog(test-exp-f32)
test_prog(test-expm1-f32)
test_prog(test-sinh-f32)
test_prog(test-cosh-f32)
test_prog(test-tanh-f32)
test_prog(test-exp2-f32)
test_prog(test-exp2m1-f32)
test_prog(test-exp10-f32)
test_prog(test-exp10m1-f32)
test_prog(test-log-f32)
test_prog(test-log1p-f32)
test_prog(test-log10-f32)
test_prog(test-log2-f32)
test_prog(test-pow-f32)
test_prog(test-powi-f32)
test_prog(test-rootn-f32)
test_prog(test-asinh-f32)
test_prog(test-acosh-f32)
test_prog(test-atanh-f32)

test_prog(test-sin-f32)
test_prog(test-cos-f32)
test_prog(test-sincos-f32)
test_prog(test-tan-f32)

test_prog(test-sinpi-f32)
test_prog(test-cospi-f32)
test_prog(test-sinpicospi-f32)
test_prog(test-tanpi-f32)

test_prog(test-atan-f32)
test_prog(test-atan2-f32)
test_prog(test-asin-f32)
test_prog(test-acos-f32)

test_prog(test-exp_mx2-f32)
test_prog(test-exp_px2-f32)
test_prog(test-exp2_mx2-f32)
test_prog(test-exp2_px2-f32)
test_prog(test-exp10_mx2-f32)
test_prog(test-exp10_px2-f32)
test_prog(test-sig-f32)

test_prog(test-root12-f32)

test_prog(test-erf-f32)
test_prog(test-erfc-f32)
test_prog(test-tgamma-f32)
test_prog(test-lgamma-f32)

test_prog(test-half-f32)

test_prog(test-v2)

if (CFTAL_FULL_TEST)
  #test_prog(test-v2)
  test_prog(test-v4f64)
  test_prog(test-v4s64)
  test_prog(test-v4u64)
  test_prog(test-v4f32)
  test_prog(test-v4s32)
  test_prog(test-v4u32)
  test_prog(test-v8s16)
  test_prog(test-v8u16)
  test_prog(test-v8f32)
  test_prog(test-v8s32)
  test_prog(test-v8u32)
  test_prog(test-v16s8)
  test_prog(test-v16u8)
  test_prog(test-v16s16)
  test_prog(test-v16u16)
  test_prog(test-v32s8)
  test_prog(test-v32u8)
endif()

#add_executable(dev-func dev-func.cc)
#target_add_test_libs(dev-func)

#add_executable(dev-native dev-native.cc)
#target_add_test_libs(dev-native)

#add_executable(dev-half dev-half.cc)
#target_add_test_libs(dev-half)

add_executable(gen-test-vec gen-test-vec.cc)
