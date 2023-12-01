cmake_minimum_required(VERSION 3.9)
project(cftal-src)

set(has_ipo, FALSE)
#include(CheckIPOSupport)
#check_ipo_support(RESULT has_ipo)

set (CSRCS
    mul_div_32.cc
    mul_div_64.cc
    d_real.cc
    exp_data_f32.cc
    exp_data_f64.cc
    pow_log_data_f32.cc
    pow_log_data_f64.cc
    erfc_data_f32.cc
    erfc_data_f64.cc
    lngamma_data_f32.cc
    lngamma_data_f64.cc
    j0_data_f64.cc
    y0_data_f64.cc
    j1_data_f64.cc
    y1_data_f64.cc
    j0_data_f32.cc
    y0_data_f32.cc
    j1_data_f32.cc
    y1_data_f32.cc
    math_func_f32.cc
    math_func_f64.cc
    math_common.cc
    payne_hanek.cc
    lanczos.cc
    x86_ops_1.cc
    x86_ins_ext.cc
    vec_traits.cc
    # vec <f16_t, _N>
    vXf16.cc
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
    v1f32_hf.cc
    # vec <float, 2>
    v2f32_ef.cc
    v2f32_sf.cc
    v2f32_hf.cc
    # vec <float, 4>
    v4f32_ef.cc
    v4f32_sf.cc
    v4f32_hf.cc
    # vec <float, 8>
    v8f32_ef.cc
    v8f32_sf.cc
    v8f32_hf.cc
    # vec <float, 16>
    v16f32_ef.cc
    v16f32_sf.cc
    v16f32_hf.cc
    # f16 data
    f16_cbrt_data.cc
    f16_cos_data.cc
    f16_j0_data.cc
    f16_j1_data.cc
    f16_log10_data.cc
    f16_log2_data.cc
    f16_log_data.cc
    f16_rcbrt_data.cc
    f16_rsqrt_data.cc
    f16_sin_data.cc
    f16_sqrt_data.cc
    f16_tan_data.cc
    f16_tgamma_data.cc
    f16_y0_data.cc
    f16_y1_data.cc
    # vec <f16_t, 1>
    v1f16_ef.cc
    #v1f16_sf.cc
    # vec <f16_t, 2>
    v2f16_ef.cc
    #v2f16_sf.cc
    # vec <f16_t, 4>
    v4f16_ef.cc
    #v4f16_sf.cc
    # vec <f16_t, 8>
    v8f16_ef.cc
    #v8f16_sf.cc
    # vec <f16_t, 16>
    v16f16_ef.cc
    #v16f16_sf.cc
)

# only for ides
SET (HDRS
    ../include/cftal/arg.h
    ../include/cftal/arm/intrin.h
    ../include/cftal/arm/perm.h
    ../include/cftal/arm/v2f32.h
    ../include/cftal/arm/v2f64.h
    ../include/cftal/arm/v2s32.h
    ../include/cftal/arm/v2s32_inl.h
    ../include/cftal/arm/v2s64.h
    ../include/cftal/arm/v2s64_inl.h
    ../include/cftal/arm/v2u32.h
    ../include/cftal/arm/v2u32_inl.h
    ../include/cftal/arm/v2u64.h
    ../include/cftal/arm/v2u64_inl.h
    ../include/cftal/as.h
    ../include/cftal/bf16.h
    ../include/cftal/bitops.h
    ../include/cftal/boost_compat.h
    ../include/cftal/config.h.in
    ../include/cftal/constants.h
    ../include/cftal/cvt_f16.h
    ../include/cftal/cvt.h
    ../include/cftal/d_int.h
    ../include/cftal/divisor.h
    ../include/cftal/d_real.h
    ../include/cftal/d_real_traits_f16.h
    ../include/cftal/d_real_traits_f32.h
    ../include/cftal/d_real_traits_f64.h
    ../include/cftal/d_real_traits.h
    ../include/cftal/expr.h
    ../include/cftal/f16_t.h
    ../include/cftal/fenv.h
    ../include/cftal/fp_expansion.h
    ../include/cftal/impl/divide.h
    ../include/cftal/impl/masks.h
    ../include/cftal/impl/vreg.h
    ../include/cftal/init_list.h
    ../include/cftal/mask.h
    ../include/cftal/math/elem_func_core_f32.h
    ../include/cftal/math/elem_func_core_f64.h
    ../include/cftal/math/elem_func.h
    ../include/cftal/math/elem_func_loprec_core_f64.h
    ../include/cftal/math/elem_func_wrapper_f32.h
    ../include/cftal/math/func_constants_f32.h
    ../include/cftal/math/func_constants_f64.h
    ../include/cftal/math/func_constants.h
    ../include/cftal/math/func_data.h
    ../include/cftal/math/func.h
    ../include/cftal/math/func_traits_f32_s32.h
    ../include/cftal/math/func_traits_f64_s32.h
    ../include/cftal/math/func_traits.h
    ../include/cftal/math/half_func.h
    ../include/cftal/math/horner.h
    ../include/cftal/math/horner_idx.h
    ../include/cftal/math/impl_d_real_constants_f32.h
    ../include/cftal/math/impl_d_real_constants_f64.h
    ../include/cftal/math/lanczos.h
    ../include/cftal/math/misc.h
    ../include/cftal/math/payne_hanek.h
    ../include/cftal/math/spec_func_core_f32.h
    ../include/cftal/math/spec_func_core_f64.h
    ../include/cftal/math/spec_func.h
    ../include/cftal/math/spec_func_loprec_core_f64.h
    ../include/cftal/math/spec_func_wrapper_f32.h
    ../include/cftal/math/vec_func_traits_f32.h
    ../include/cftal/math/vec_func_traits_f64.h
    ../include/cftal/mem.h
    ../include/cftal/mul_div.h
    ../include/cftal/select.h
    ../include/cftal/std_types.h
    ../include/cftal/t_real.h
    ../include/cftal/types.h
    ../include/cftal/type_traits.h
    ../include/cftal/vec_bit_n.h
    ../include/cftal/vec_cast_bits.h
    ../include/cftal/vec_compress_expand_elements.h
    ../include/cftal/vec_cvt_f16.h
    ../include/cftal/vec_cvt.h
    ../include/cftal/vec_double_n.h
    ../include/cftal/vec_d_real_traits_f16.h
    ../include/cftal/vec_d_real_traits_f32.h
    ../include/cftal/vec_d_real_traits_f64.h
    ../include/cftal/vec_f16.h
    ../include/cftal/vec_float_n.h
    ../include/cftal/vec.h
    ../include/cftal/vec_load_strided.h
    ../include/cftal/vec_lookup.h
    ../include/cftal/vec_mask.h
    ../include/cftal/vec_math_funcs.h
    ../include/cftal/vec_misc.h
    ../include/cftal/vec_op.h
    ../include/cftal/vec_spec.h
    ../include/cftal/vec_t_1.h
    ../include/cftal/vec_t_n.h
    ../include/cftal/x86/cast_bits.h
    ../include/cftal/x86/const.h
    ../include/cftal/x86/ins_ext.h
    ../include/cftal/x86/intrin.h
    ../include/cftal/x86/ops_0.h
    ../include/cftal/x86/ops_1.h
    ../include/cftal/x86/perm.h
    ../include/cftal/x86/select.h
    ../include/cftal/x86/v16f32.h
    ../include/cftal/x86/v16f32_inl.h
    ../include/cftal/x86/v16s16.h
    ../include/cftal/x86/v16s16_inl.h
    ../include/cftal/x86/v16s32.h
    ../include/cftal/x86/v16s32_inl.h
    ../include/cftal/x86/v16s8.h
    ../include/cftal/x86/v16s8_inl.h
    ../include/cftal/x86/v16u16.h
    ../include/cftal/x86/v16u16_inl.h
    ../include/cftal/x86/v16u32.h
    ../include/cftal/x86/v16u32_inl.h
    ../include/cftal/x86/v16u8.h
    ../include/cftal/x86/v16u8_inl.h
    ../include/cftal/x86/v2f64.h
    ../include/cftal/x86/v2f64_inl.h
    ../include/cftal/x86/v2s64.h
    ../include/cftal/x86/v2s64_inl.h
    ../include/cftal/x86/v2u64.h
    ../include/cftal/x86/v2u64_inl.h
    ../include/cftal/x86/v32s8.h
    ../include/cftal/x86/v32s8_inl.h
    ../include/cftal/x86/v32u8.h
    ../include/cftal/x86/v32u8_inl.h
    ../include/cftal/x86/v4f32.h
    ../include/cftal/x86/v4f32_inl.h
    ../include/cftal/x86/v4f64.h
    ../include/cftal/x86/v4f64_inl.h
    ../include/cftal/x86/v4s32.h
    ../include/cftal/x86/v4s32_inl.h
    ../include/cftal/x86/v4s64.h
    ../include/cftal/x86/v4s64_inl.h
    ../include/cftal/x86/v4u32.h
    ../include/cftal/x86/v4u32_inl.h
    ../include/cftal/x86/v4u64.h
    ../include/cftal/x86/v4u64_inl.h
    ../include/cftal/x86/v8f32.h
    ../include/cftal/x86/v8f32_inl.h
    ../include/cftal/x86/v8f64.h
    ../include/cftal/x86/v8f64_inl.h
    ../include/cftal/x86/v8s16.h
    ../include/cftal/x86/v8s16_inl.h
    ../include/cftal/x86/v8s32.h
    ../include/cftal/x86/v8s32_inl.h
    ../include/cftal/x86/v8s64.h
    ../include/cftal/x86/v8s64_inl.h
    ../include/cftal/x86/v8u16.h
    ../include/cftal/x86/v8u16_inl.h
    ../include/cftal/x86/v8u32.h
    ../include/cftal/x86/v8u32_inl.h
    ../include/cftal/x86/v8u64.h
    ../include/cftal/x86/v8u64_inl.h
    ../include/cftal/x86/vec_bit.h
    ../include/cftal/x86/vreg.h
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
if (has_ipo)
    set_property(TARGET cftal-so
        PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()
set_target_properties(cftal-so PROPERTIES SOVERSION "${CFTAL_VERSION_MAJ}"
  VERSION "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}")

find_library(LIBM m)
if (LIBM)
  target_link_libraries(cftal-so ${LIBM})
endif(LIBM)

if ("${CMAKE_LIBRARY_ARCHITECTURE}" MATCHES ^x86_64* )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #     "${CMAKE_CXX_FLAGS_RELEASE} -Winline")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #     "${CMAKE_CXX_FLAGS_RELEASE} --param inline-unit-growth=4000")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #     "${CMAKE_CXX_FLAGS_RELEASE} --param large-function-growth=4000")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #     "${CMAKE_CXX_FLAGS_RELEASE} --param max-inline-insns-single=8192")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #     "${CMAKE_CXX_FLAGS_RELEASE} --param large-stack-frame=16384")
        #set (CMAKE_CXX_FLAGS_RELEASE
        #     "${CMAKE_CXX_FLAGS_RELEASE} --param large-stack-frame-growth=4000")
    endif()
endif()


install(TARGETS cftal-so
  DESTINATION lib LIBRARY
  COMPONENT cftal
  NAMELINK_SKIP)
install(TARGETS cftal-so
  DESTINATION lib LIBRARY
  COMPONENT devel
  NAMELINK_ONLY)
