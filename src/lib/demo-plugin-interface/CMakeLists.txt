project(demo-plugin-interface)
find_package(libsimdpp REQUIRED)
find_package(simd-diagonal-load REQUIRED)
add_library(${PROJECT_NAME} INTERFACE)
add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                                     $<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME} INTERFACE simd-diagonal-load::algorithm)
target_link_libraries(${PROJECT_NAME} INTERFACE simd-diagonal-load-json-demo::input-matrices)
