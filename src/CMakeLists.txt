include(GNUInstallDirs)                                                                                                                                 
set(plugin_install_dir "${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo/plugins")

function(add_my_program progname)
  add_executable(${progname} ${progname}.cc)
  set_property(TARGET ${progname} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${progname} PROPERTY CXX_STANDARD_REQUIRED ON)
  install(TARGETS ${progname} DESTINATION bin)
endfunction()

set(NUM_LOADS_MINIMUM "1" CACHE STRING "minimum NUM_LOADS (used when building plugins)")
set(NUM_LOADS_MAXIMUM "1" CACHE STRING "maximum NUM_LOADS (used when building plugins)")

set(NUM_MATRICES_MINIMUM "2" CACHE STRING "minimum NUM_MATRICES (used when building plugins)")
set(NUM_MATRICES_MAXIMUM "2" CACHE STRING "maximum NUM_MATRICES (used when building plugins)")

set(NUM_VERTICAL_MIXING_MINIMUM "1" CACHE STRING "minimum NUM_VERTICAL_MIXING (used when building plugins)")
set(NUM_VERTICAL_MIXING_MAXIMUM "1" CACHE STRING "maximum NUM_VERTICAL_MIXING (used when building plugins)")

set(NUM_VERTICAL_SUBDIVISIONS_MINIMUM "1" CACHE STRING "minimum NUM_VERTICAL_SUBDIVISIONS (used when building plugins)")
set(NUM_VERTICAL_SUBDIVISIONS_MAXIMUM "1" CACHE STRING "maximum NUM_VERTICAL_SUBDIVISIONS (used when building plugins)")

set(SIMDVECTOR_BITLENGTH_MINIMUM "256" CACHE STRING "minimum SIMDVECTOR_BITLENGTH (used when building plugins)")
set(SIMDVECTOR_BITLENGTH_MAXIMUM "256" CACHE STRING "maximum SIMDVECTOR_BITLENGTH (used when building plugins)")

set(MATRIX_WIDTH_MINIMUM "8" CACHE STRING "minimum MATRIX_WIDTH")
set(MATRIX_WIDTH_MAXIMUM "8" CACHE STRING "maximum MATRIX_WIDTH")

set(INTEGERTYPES "uint8_t;int32_t" CACHE STRING "semi-colon seperated list of of integer types (e.g. uint8_t;int32_t")


add_subdirectory(defines-from-cmake-variables)
add_subdirectory(check-valid-numbers)
add_subdirectory(protobuf-helper-funcs)
add_subdirectory(input-protobuf)
add_subdirectory(output-protobuf)
add_subdirectory(generate-input)
add_subdirectory(demo-plugin-interface)
add_subdirectory(demo-pluginloader)
add_subdirectory(demo-plugin)
add_subdirectory(demo)
