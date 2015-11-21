project(cftal-src)

set (CSRCS mul_div_32.cc mul_div_64.cc d_real.cc math_func.cc x86_ops_1.cc
v2f64.cc v4f64.cc v4f32.cc v8f32.cc vec_traits.cc v8f64.cc)

add_library (cftal STATIC ${CSRCS})
install(TARGETS cftal
  DESTINATION lib LIBRARY
  COMPONENT devel)
#set_target_properties(cftal PROPERTIES OUTPUT_NAME "cftal")
add_library (cftal-so SHARED ${CSRCS})
set_property(TARGET cftal-so 
  PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_property(TARGET cftal-so 
  PROPERTY OUTPUT_NAME cftal)
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
