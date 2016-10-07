project(cftal-src)

set (CSRCS
    mul_div_32.cc
    mul_div_64.cc
    d_real.cc
    math_func_f64.cc
    math_func_f32.cc
    math_common.cc
    x86_ops_1.cc
    vec_traits.cc
    # vec <double, 1>
    v1f64_ef.cc
    v1f64_sf.cc
    # vec <double, 2>
    v2f64_ef.cc
    v2f64_sf.cc
    # vec <double, 4>
    v4f64_ef.cc
    v4f64_sf.cc
    # vec <double, 8>
    v8f64_ef.cc
    v8f64_sf.cc
    # vec <float, 1>
    v1f32_ef.cc
    v1f32_sf.cc
    # vec <float, 2>
    v2f32_ef.cc
    v2f32_sf.cc
    # vec <float, 4>
    v4f32_ef.cc
    v4f32_sf.cc
    # vec <float, 8>
    v8f32_ef.cc
    v8f32_sf.cc
    # vec <float, 16>
    v16f32_ef.cc
    v16f32_sf.cc
)

if (CFTAL_STATIC_LIB)
    add_library (cftal STATIC ${CSRCS})
    install(TARGETS cftal
        DESTINATION lib LIBRARY
        COMPONENT devel)
endif()

#set_target_properties(cftal PROPERTIES OUTPUT_NAME "cftal")
add_library (cftal-so SHARED ${CSRCS})
set_property(TARGET cftal-so
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_property(TARGET cftal-so
  PROPERTY OUTPUT_NAME cftal)
set_property(TARGET cftal-so
  PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
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
