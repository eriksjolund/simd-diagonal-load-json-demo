include(GNUInstallDirs)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo")
set(plugin_install_dir "${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo/plugins")

function(add_my_program progname)
  add_executable(${progname} ${progname}.cc)
  set_property(TARGET ${progname} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${progname} PROPERTY CXX_STANDARD_REQUIRED ON)
  install(TARGETS ${progname} DESTINATION bin)
endfunction()

set(NUM_LOADS_MINIMUM "1" CACHE STRING "minimum NUM_LOADS (used when building plugins)")
set(NUM_LOADS_MAXIMUM "1" CACHE STRING "maximum NUM_LOADS (used when building plugins)")

set(NUM_VERTICAL_MIXING_MINIMUM "0" CACHE STRING "minimum NUM_VERTICAL_MIXING (used when building plugins)")
set(NUM_VERTICAL_MIXING_MAXIMUM "1" CACHE STRING "maximum NUM_VERTICAL_MIXING (used when building plugins)")

set(NUM_VERTICAL_SUBDIVISIONS_MINIMUM "0" CACHE STRING "minimum NUM_VERTICAL_SUBDIVISIONS (used when building plugins)")
set(NUM_VERTICAL_SUBDIVISIONS_MAXIMUM "1" CACHE STRING "maximum NUM_VERTICAL_SUBDIVISIONS (used when building plugins)")

set(SIMDVECTOR_BITLENGTH_MINIMUM "256" CACHE STRING "minimum SIMDVECTOR_BITLENGTH (used when building plugins)")
set(SIMDVECTOR_BITLENGTH_MAXIMUM "256" CACHE STRING "maximum SIMDVECTOR_BITLENGTH (used when building plugins)")

set(MATRIX_WIDTH_MINIMUM "8" CACHE STRING "minimum MATRIX_WIDTH")
set(MATRIX_WIDTH_MAXIMUM "8" CACHE STRING "maximum MATRIX_WIDTH")

set(INTEGERTYPES "uint8_t;uint32_t" CACHE STRING "semi-colon seperated list of of integer types (e.g. uint8_t;int32_t)")

set(SIMD_ARCHS "ARCH_X86_AVX2" CACHE STRING "semi-colon seperated list of of libsimdpp interface libraries (e.g. ARCH_X86_AVX2;ARCH_X86_SSE4_1). The alternatives are right now defined in the fork https://github.com/eriksjolund/libsimdpp/commits/modernize_cmake_support")

add_subdirectory(lib/defines-from-cmake-variables)
add_subdirectory(lib/capnproto-helper-funcs)
add_subdirectory(capnproto-schema/input-spec)
add_subdirectory(capnproto-schema/input-matrices)
add_subdirectory(capnproto-schema/demo-run-options)
add_subdirectory(capnproto-schema/output-matrices)

add_subdirectory(lib/check-valid-numbers)

add_subdirectory(cmd/generate-input)
add_subdirectory(lib/demo-plugin-interface)
add_subdirectory(lib/demo-pluginloader)
add_subdirectory(lib/demo-plugin)
add_subdirectory(cmd/demo)

return()




add_subdirectory(lib/protobuf-helper-funcs)

add_subdirectory(lib/output-protobuf)

















