project(cftal-test)

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
    ./include/cftal/test/check_j0.h
    ./include/cftal/test/check_j1.h
    ./include/cftal/test/check_y0.h
    ./include/cftal/test/check_y1.h
)

find_package(Boost REQUIRED)
if(${Boost_FOUND})
    #message ("${Boost_FOUND}")
    #message ("${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(Threads REQUIRED)

#include(FindPkgConfig)
#find_library(LIBSQLITE3 sqlite3 REQUIRED)
#if (LIBSQLITE3)
#    message(${LIBSQLITE3})
#endif()
#find_file(HDRQLITE3 sqlite3.h REQUIRED)
#if (HDRQLITE3)
#    message(${HDRQLITE3})
#endif()

add_subdirectory(src)

enable_testing()

function(target_add_test_libs arg1)
    target_link_libraries(${arg1} cftal-test-so)
    target_add_mpfr_libs(${arg1})
endfunction()

function(test_prog arg1)
    #add_executable(${arg1} ${arg1}.cc ${TEST_HDRS})
    add_executable(${arg1} ${arg1}.cc)
    target_add_test_libs(${arg1})
    add_test(NAME ${arg1} COMMAND ${arg1})
endfunction()

add_subdirectory(vec)

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
test_prog(test-intops)


#add_executable(dev-func dev-func.cc)
#target_add_test_libs(dev-func)

#add_executable(dev-native dev-native.cc)
#target_add_test_libs(dev-native)

#add_executable(dev-half dev-half.cc)
#target_add_test_libs(dev-half)

add_executable(gen-test-vec gen-test-vec.cc)
