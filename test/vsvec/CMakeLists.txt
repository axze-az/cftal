project(cftal-test-vsvec)

test_prog(test-vsvec-svopt)
test_prog(test-vsvec-load-strided)

test_prog(test-vsvec-ops-f64)
test_prog(test-vsvec-ops-f32)
test_prog(test-vsvec-ops-f16)
test_prog(test-vsvec-ops-bf16)

test_prog(test-vsvec-ops-s64)
test_prog(test-vsvec-ops-u64)
test_prog(test-vsvec-ops-s32)
test_prog(test-vsvec-ops-u32)
test_prog(test-vsvec-ops-s16)
test_prog(test-vsvec-ops-u16)
test_prog(test-vsvec-ops-s8)
test_prog(test-vsvec-ops-u8)

test_prog(test-vsvec-flops)

test_prog(test-vsvec-misc)

add_executable(dev-vsvec dev-vsvec.cc)
target_add_test_libs(dev-vsvec)
