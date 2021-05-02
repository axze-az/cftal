project(cftal-utils)

include_directories(../test/include)

find_library(LIBGMP gmp REQUIRED)
if (LIBGMP)
    message(${LIBGMP})
endif()
find_library(LIBMPFR mpfr REQUIRED)
if (LIBMPFR)
    message(${LIBMPFR})
endif()
find_file(HDRMPFR mpfr.h)
if (HDRMPFR)
    message(${HDRMPFR})
endif()
# all things below are only required for the sollya extensions
find_library(LIBMPFI mpfi REQUIRED)
if (LIBMPFI)
    message(${LIBMPFI})
endif()
find_file(HDRMPFI mpfi.h REQUIRED)
if (HDRMPFI)
    message(${HDRMPFI})
endif()
find_library(LIBSOLLYA sollya OPTIONAL)
if (LIBSOLLYA)
    message(${LIBSOLLYA})
endif()
find_file(HDRSOLLYA sollya.h OPTIONAL)
if (HDRSOLLYA)
    message(${HDRSOLLYA})
endif()

if (LIBSOLLYA)
  add_library(sollya_funcs SHARED sollya_funcs.cc)
  target_link_libraries(sollya_funcs ${LIBSOLLYA})
  target_link_libraries(sollya_funcs ${LIBMPFI})
  target_link_libraries(sollya_funcs ${LIBMPFR})
  target_link_libraries(sollya_funcs ${LIBGMP})
endif()
  
function(target_add_mpfr_libs arg1)
    target_link_libraries(${arg1} ${LIBMPFR})
    target_link_libraries(${arg1} ${LIBGMP})
endfunction()

function(target_add_test_libs arg1)
    target_link_libraries(${arg1} cftal-test)
    target_add_mpfr_libs(${arg1})
endfunction()

add_executable(gen-func-data gen-func-data.cc)
target_add_test_libs(gen-func-data)

add_executable(gen-constants gen-constants.cc)
target_add_test_libs(gen-constants)

add_executable(gen-2-over-pi gen-2-over-pi.cc)
target_add_test_libs(gen-2-over-pi)

add_executable(gen-fixpoint-div gen-fixpoint-div.cc)

add_executable(gen-lanczos-tbl gen-lanczos-tbl.cc)

add_executable(check-div-x8-x16 check-div-x8-x16)

#add_custom_target(sollya-scripts ALL)

function(add_script script)
    add_custom_target(
    ${script} ALL
    #OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${script}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/${script}
            ${CMAKE_CURRENT_BINARY_DIR}
    #COMMENT ${script}
    #DEPENDS ${script}
    )
    get_directory_property(ff ADDITIONAL_MAKE_CLEAN_FILES)
    #message("${ff}")
    list(APPEND ff "${CMAKE_CURRENT_BINARY_DIR}/${script}")
    #message("${ff}")
    set_directory_properties(PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${ff}")
endfunction()

add_script(common.sollya)
add_script(single.sollya)
add_script(single-using-double.sollya)
add_script(double.sollya)
add_script(specfun-double.sollya)
add_script(specfun-single.sollya)
add_script(log.sollya)
add_script(erfc.sollya)
add_script(half.sollya)
add_script(devel.sollya)
add_script(gamma.mac)
