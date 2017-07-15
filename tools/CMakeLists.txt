project(cftal-tools)

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
add_executable(gen-approx gen-approx.cc)
target_add_test_libs(gen-approx)
add_executable(gen-fixpoint-div gen-fixpoint-div.cc)

#add_custom_target(sollya-scripts ALL)

function(add_script script)
add_custom_target(
  ${script} ALL
  #OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${script}
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_CURRENT_SOURCE_DIR}/${script}
          ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${script}
  )
get_directory_property(ff ADDITIONAL_MAKE_CLEAN_FILES)
message("${ff}")
set(ff "${ff};${CMAKE_CURRENT_BINARY_DIR}/${script}")
message("${ff}")
set_directory_properties(PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${ff}")
endfunction()

add_script(common.sollya)
add_script(single.sollya)
add_script(double.sollya)
add_script(specfun-double.sollya)
add_script(specfun-single.sollya)
add_script(devel.sollya)
