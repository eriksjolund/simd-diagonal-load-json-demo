project(demo-plugin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(simd-compile-options REQUIRED)
find_package(libsimdpp REQUIRED)
find_package(simd-diagonal-load REQUIRED)
find_package(CapnProto REQUIRED)

function(create_plugin)
  set(options) # empty
  set(oneValueArgs
      NUM_LOADS
      SIMDVECTOR_BITLENGTH
      NUM_VERTICAL_SUBDIVISIONS
      NUM_VERTICAL_MIXING
      MATRIX_WIDTH
      INTEGERTYPE
      SIMD_ARCH
      SIMD_ARCH2
)
  set(multiValueArgs) # empty

cmake_parse_arguments(PARSE_ARGV 0 argument "${options}" "${oneValueArgs}" "${multiValueArgs}")
  if(argument_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Programming error: This function does not expect any extra arguments")
  endif()


set (plugin_name "")
  foreach(i IN LISTS oneValueArgs)
    string(TOLOWER ${i} lowcase) 
    string(APPEND plugin_name "_${lowcase}-${argument_${i}}")
    list(APPEND templatedefines "${i}=${argument_${i}}")
  endforeach()
  
  foreach(def IN LISTS templatedefines)


    list(APPEND extra_cmake_flags "-D${def}")
  endforeach()

  try_compile(result
              ${CMAKE_CURRENT_BINARY_DIR}
	      ${CMAKE_CURRENT_SOURCE_DIR}/check-template-parameters/
	      check_template_parameters
            OUTPUT_VARIABLE outputvar  CMAKE_FLAGS "-DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}"
                           ${extra_cmake_flags})
  if (NOT result) 
    message(STATUS "${plugin_name} has wrong template parameters. ${outputvar}")
    return()
  else()
    message(STATUS "${plugin_name} has correct template parameters.")
  endif()
  
  configure_file(build_time_plugin_config.h.in ${plugin_name}/build_time_plugin_config.h @ONLY)

  list(APPEND templatedefines "plugin_name_CMAKE_VAR=\"${plugin_name}\"")

  add_library(${plugin_name} SHARED demo_plugin.cc demo_plugin.h)


 foreach(def IN LISTS templatedefines)
   target_compile_definitions(${plugin_name} PRIVATE "${def}")
  endforeach()
  target_link_libraries(${plugin_name} PRIVATE libsimdpp::${argument_SIMD_ARCH})

  target_link_libraries(${plugin_name} PRIVATE Qt5::Core)

  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load-json-demo::demo-plugin-interface)
  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load-json-demo::input-matrices)
  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load-json-demo::output-matrices)
  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load-json-demo::demo-run-options)

  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load::algorithm)
  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load::array-helper)
#target_link_libraries(${plugin_name} PRIVATE CapnProto::capnp CapnProto::capnp-json)

  target_link_libraries(${plugin_name} PRIVATE simd-diagonal-load-json-demo::capnproto-helper-funcs)

  target_include_directories(${plugin_name}    PRIVATE    ${CMAKE_CURRENT_SOURCE_DIR}  ${CMAKE_CURRENT_BINARY_DIR}/${plugin_name} )
  set_property(TARGET ${plugin_name} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${plugin_name} PROPERTY CXX_STANDARD_REQUIRED ON)

  install(TARGETS ${plugin_name} DESTINATION ${plugin_install_dir})
endfunction()

foreach(num_loads RANGE ${NUM_LOADS_MINIMUM} ${NUM_LOADS_MAXIMUM} 1)
message(STATUS "num_l")
foreach(simdvector_bitlength RANGE ${SIMDVECTOR_BITLENGTH_MINIMUM} ${SIMDVECTOR_BITLENGTH_MAXIMUM} 1)
   foreach(num_vertical_subdivisions RANGE ${NUM_VERTICAL_SUBDIVISIONS_MINIMUM} ${NUM_VERTICAL_SUBDIVISIONS_MAXIMUM} 1)
    foreach(num_vertical_mixing RANGE ${NUM_VERTICAL_MIXING_MINIMUM} ${NUM_VERTICAL_MIXING_MAXIMUM} 1)
      foreach(matrix_width RANGE ${MATRIX_WIDTH_MINIMUM} ${MATRIX_WIDTH_MAXIMUM} 1)
        foreach(integertype IN LISTS INTEGERTYPES)
          foreach(simd_arch IN LISTS SIMD_ARCHS)
            create_plugin(NUM_LOADS ${num_loads}
                          SIMDVECTOR_BITLENGTH ${simdvector_bitlength}
                          NUM_VERTICAL_SUBDIVISIONS ${num_vertical_subdivisions}
                          NUM_VERTICAL_MIXING ${num_vertical_mixing}
                          MATRIX_WIDTH ${matrix_width}
                          INTEGERTYPE ${integertype}
                          SIMD_ARCH ${simd_arch}
                          SIMD_ARCH2 ${simd_arch})
        endforeach()
      endforeach()
    endforeach()
   endforeach()   
  endforeach()
 endforeach()
endforeach()
