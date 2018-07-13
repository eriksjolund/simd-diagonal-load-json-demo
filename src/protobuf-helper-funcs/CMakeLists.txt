project(protobuf-helper-funcs)

add_library(${PROJECT_NAME} SHARED)
add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_sources(${PROJECT_NAME} PRIVATE print_json.cc)                                
target_link_libraries(${PROJECT_NAME} INTERFACE simd-diagonal-load-json-demo::input-protobuf)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo)
