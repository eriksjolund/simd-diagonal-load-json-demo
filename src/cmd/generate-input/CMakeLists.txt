project(generate-input)

add_my_program(${PROJECT_NAME})
find_package(simd-diagonal-load REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
target_sources(${PROJECT_NAME} PRIVATE print_generated_input.cc)

target_include_directories(${PROJECT_NAME} 
   PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
 )


target_link_libraries(generate-input PRIVATE simd-diagonal-load-json-demo::input-spec)
target_link_libraries(generate-input PRIVATE simd-diagonal-load-json-demo::input-matrices)
target_link_libraries(generate-input PRIVATE simd-diagonal-load-json-demo::capnproto-helper-funcs)
target_link_libraries(generate-input PRIVATE simd-diagonal-load::array-helper)
 
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
