project(generate-input)

add_my_program(${PROJECT_NAME})
find_package(simd-diagonal-load REQUIRED)
#target_sources(${PROJECT_NAME} PRIVATE print_generated_input.cc)                                
target_link_libraries(generate-input PRIVATE simd-diagonal-load-json-demo::protobuf-helper-funcs)
target_link_libraries(generate-input PRIVATE simd-diagonal-load-json-demo::input-protobuf)
target_link_libraries(generate-input PRIVATE simd-diagonal-load::array-helper)
 
