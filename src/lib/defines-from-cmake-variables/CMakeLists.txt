project(defines-from-cmake-variables)
configure_file(config.h.in include/simd-diagonal-load-json-demo/defines-from-cmake-variables/config.h)
add_library(${PROJECT_NAME} INTERFACE)
add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
                           INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)
